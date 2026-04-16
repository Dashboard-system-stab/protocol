#ifndef COM_DRIVER_H
#define COM_DRIVER_H

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <linux/if.h>
#include <linux/if_packet.h>
#include <linux/icmp.h>
#include <linux/tcp.h>
#include <linux/sockios.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include "stdint.h"
#include "linux/ip.h"
#include "linux/udp.h"
#include "netinet/ether.h"
#include <poll.h>

#include "mjdriver_interface.h"

#ifdef __cplusplus
extern "C" {
#endif


#define BUF_SIZE 1024
#define ETHER_TYPE	0x0800
#define IP_DF 0x4000
#define MAX_CALLBACKS 32
#define SEND_INTERVAL 250 //microseconds

typedef struct {
    uint8_t mac[6];
    uint32_t ip;
} eth_int_t;

typedef struct {
    struct ether_header eh;
    struct iphdr iph;
    struct udphdr udph;
    void * payload;
    uint16_t payloadSize;
} packet_t;

typedef struct{
    struct ether_header eth;
    struct extended_ip_header{
        struct iphdr ip;
        uint8_t ip_options[4];
    }__attribute__((packed))ip_ext;
    uint8_t type;
    uint8_t maxRespTime;
    uint16_t csum;
    uint32_t groupAddr;
} __attribute__((packed)) igmp2Msg_t;


typedef struct {
    struct sockaddr * address;
    int socket;
} socket_info;

// Structure to hold callback information
typedef struct{
    uint32_t dest_ip;
    uint16_t dest_port;
    mj_msg_proc_fcn cb; // This is the function pointer of type udp4cb
} CallbackInfo;

typedef struct{
    pthread_t thread_id;
    bool enable;
    int socket;
    int core;
    struct sockaddr_ll socket_address;
}tx_conf;

typedef struct{
    pthread_t thread_id;
    bool enable;
    int socket;
    int core;
    bool is_running;
    struct sockaddr_ll socket_address;
}rx_conf;

int setThreadPriority(pthread_t thread_id, int priority_offset, struct sched_param * param);

int setThreadAffininty(pthread_t thread_id, int thread_core, struct sched_param * param, char * name);

void * transmitFunction(void * args);

void setLoggerCallback(void(*func)(uint8_t *, size_t, struct timespec));

void setEthernetInterfaceName(char * name);

__UINT64_TYPE__ getTimeUs();

socket_info getSocketInfo();

bool getTxStatus();

void setTxStatus(bool value);

mj_msg_proc_res_t processPacket(uint8_t * buffer, uint64_t time_us);

bool bufferHandler(uint8_t * buffer, void ** payload,size_t * payload_size,  mj_msg_proc_fcn (*fnc));

bool getRxStatus();

void setRxStatus(bool value);

bool getPtpStatus();

void setPtpStatus(bool value);

void init_mjdrv(mj_drv_interface_t * idrv);

void deinit_mjdrv();

void reinit_mjdrv();

void mj_set_loop_fcn(void (*loop_fcn)(void));

void mjdrv_set_ptp_tick(void (*tick_fcn)(void));

#ifdef __cplusplus
}
#endif
#endif // COM_DRIVER_H
