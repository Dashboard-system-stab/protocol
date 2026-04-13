#ifndef MICROJETDRIVERINTERFACE_H
#define MICROJETDRIVERINTERFACE_H

#include <stdint.h>
#include "microjet_def.h"

#ifdef __cplusplus
extern "C"{
#endif

/*
Definition of data processing function
Return value:
    MJ_ACCEPT      - packet succesfuly procesed as MicroJet message
    MJ_REJECT_SRC  - packet rejected due unaceptable SRC field in MicroJet message
    MJ_REJECT_DST  - packet rejected due unaceptable DST field in MicroJet message
    MJ_REJECT_ID   - packet rejected due unaceptable ID field in MicroJet message
    MJ_REJECT_SIZE - packet rejected because payload too small for MicroJet message
    MJ_PROC_FAIL   - packet rejected due error occurs on packet processing
arguments:
    1 - mac - pointer to array of six byte of MAC address
    2 - src_ip - source IP address in network byte order
*/
typedef mj_msg_proc_res_t (*mj_msg_proc_fcn)(uint8_t *payload, uint16_t size, uint32_t ts_s, uint32_t ts_ns);

/*
Data transmit end callback function definition.
Return value
    None
arguments:
    1 - st - result of data transmit. Should be:
             MJ_OK - if transfer done succesfuly
             MJ_FAIL - otherwise
    
    2 - tx_s - seconds part of frame transmission timestamp
    3 - tx_ns - nanoseconds part of frame transmission timestamp
                Note: On STM devices this value is not in decimal.
                Value needs to be converted with about 0.46 ns precision.
*/
typedef void (*mj_tx_end_cb)(mj_status_t st, uint32_t tx_s, uint32_t tx_ns);

typedef struct mj_udp4_transport_interface{
    /*
    Allocate byte to store MicroJet message, recived over udp4 transport
    Return value:
        pointer to data on succesfully allocation or NULL otherwise
    arguments:
        1 - dir  - direction of message ( IN or OUT)
        1 - size - requested number of bytes to allocate
    */
    uint8_t* (*alloc)(uint16_t size);

    /*
    Free memory, allocated by "alloc" function
    Return value:
        None
    arguments:
        1 - dir - direction of message ( IN or OUT)
        1 - ptr - pointer to freed data
    */
    void (*free)(uint8_t *ptr);
    /* 
    Register ethernet interface with requested MAC and IP.
    Return value:
        pointer to interface or NULL if interface not created
    arguments:
        1 - mac - pointer to array of six byte of MAC address
        2 - src_ip - source IP address in network byte order
    */
    void* (*create_interface)(const uint8_t* mac, uint32_t src_ip);

    /*
    Register callback function that driver should call when udp4 packet with specific destination IP and port is recived
    Return value:
        MJ_OK - if callback function is succesfully registered by driver
        MJ_FAILED - otherwise
    arguments:
        1 - des_ip   - destination IP address in network byte order
        2 - dst_port - destination port in network byte order
        3 - p_fcn    - pointer to callback function
    */
    mj_status_t (*register_callback)(uint32_t des_ip, uint16_t dst_port, mj_msg_proc_fcn p_fcn);

    /*
    Register output udp4 packet with specific parameters and payload.
    Return value:
        pointer to udp4 packet or NULL if packet not registered 
    arguments:
        1 - eth_int  - pointer to ethernet interface, created by "create_interface" function 
        2 - des_ip   - destination IP address in network byte order
        3 - dst_port - destination port in network byte order
        4 - src_port - source port in network byte order
        5 - payload  - pointer to payload, allocated by "alloc" fcn
        6 - size     - size of payload in bytes
    */
    void * (*create_out_pkt)(void *eth_int, uint32_t des_ip, uint16_t dst_port, uint16_t src_port, uint8_t *payload, uint16_t size);

    /*
    Set udp4 packet Differentiated Services Code Point (DSCP).
    arguments:
        1 - pkt   - pointer to upd4 packet, registered by "create_out_pkt" function
        2 - dscp  - six bit dscp value
    */
    void (*set_dscp)(void *pkt, uint8_t dscp);

    /*
    Transmit packet (or plane to transmit after "call pool_tx"), registered by "create_out_pkt" function
    Return value:
        None
    arguments:
        1 - pkt   - pointer to upd4 packet, registered by "create_out_pkt" function 
        2 - p_fcn - pointer to transmit end callback function
                    if p_fcn not NULL: After transfer is done driver should call "p_fcn"
                    with "MJ_OK" arg if transfer done correctly or "MJ_FAIL" if transfer failed
    addition check is requred cd may be NULL
    */
    void (*tx)(void *pkt, mj_tx_end_cb p_fcn);

    /*
    Return pointer to payload data of udp4 packet, registered by "create_out_pkt" function
    Return value:
        pointer to udp4 packet payload or NULL if packet not registered 
    arguments:
        1 - pkt   - pointer to upd4 packet, registered by "create_out_pkt" function
    */
    uint8_t * (*get_payload)(void *pkt);

    /*
    Set pointer to payload data of udp4 packet, registered by "create_out_pkt" function
    Return value:
        None
    arguments:
        1 - pkt - pointer to upd4 packet, registered by "create_out_pkt" function
        2 - payload - pointer to new payload 
    */ 
    void (*set_payload)(void *pkt, uint8_t *payload);

    /*
    Request to send membersip report to joun multicast group
    Return value:
        None
    arguments:
        1 - eth_int  - pointer to ethernet interface, created by "create_interface" function 
        2 - group_ip - multicast IP address in network byte order
    */
    void (*join_group)(void *eth_int, uint32_t group_ip);
    

    /* Start transmit sequence, if not requared or unsupported set to NULL */
    void (*pool_tx)(void);

}mj_udp4_transport_interface_t;

typedef struct mj_drv_interface{
    mj_udp4_transport_interface_t udp4;
    /* Get timestamp */
    uint32_t (*timestamp)(uint32_t *sec, uint32_t *nan_sec);
} mj_drv_interface_t;

#ifdef __cplusplus
}
#endif
#endif /* MICROJETDRIVERINTERFACE_H */