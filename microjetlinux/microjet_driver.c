/*
 * com_driver.c
 *
 *  Created on: 9 июн. 2023 г.
 *    Author: sinitsyn
*/
#define _GNU_SOURCE

#include "microjet_driver.h"
#include "ptp.h"

tx_conf tx;
rx_conf rx;

// Global array of callbacks
static CallbackInfo callbacks[MAX_CALLBACKS];
// Current amount of callbacks
static int num_callbacks = 0;


eth_int_t * current_eth_if = NULL;
char * interface_name = NULL;
void (*p_loop_fcn)(void) = NULL;
void (*ptp_tick_fcn)(void) = NULL;
void (*logFunction_p)(uint8_t *, size_t, struct timespec) = NULL;
bool ptp_state = false;

static struct ifreq if_idx;
static struct ifreq if_req;
void mj_get_print_buf(char **ptr, size_t *size)
{
    *ptr = NULL;
    *size = 0;
    return;
}

void mj_set_loop_fcn(void (*loop_fcn)(void))
{
    p_loop_fcn = loop_fcn;
    return;
}

void mjdrv_set_ptp_tick(void (*tick_fcn)(void)){
    ptp_tick_fcn = tick_fcn;
    return;
}

void mj_send_print_buf(uint8_t *header, size_t h_size, char *ptr, size_t size)
{
    (void)header;(void)h_size;(void)ptr;(void)size;
    //  eth_transmit2(header, h_size, (uint8_t *)ptr,size, NULL, 0);
    return;
}

void setLoggerCallback(void(*func)(uint8_t *, size_t, struct timespec)){
    logFunction_p = func;
    return;
}

uint64_t getTimeUs(){
    uint64_t us = 0;
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    us = ts.tv_sec * 1e6;
    us += ts.tv_nsec/1e3;
    return us;
}


bool getTxStatus(){
    return tx.enable;
}

void setTxStatus(bool value){
    tx.enable = value;
    return;
}

bool getRxStatus(){
    return rx.enable;
}

void setRxStatus(bool value){
    rx.enable = value;
    return;
}


extern ptp_port_DS_t portDS;
void setPtpStatus(bool value){
    if(value){
        portDS.portState = PTP_PORT_STATE_MASTER;
    }else{
        portDS.portState = PTP_PORT_STATE_PASSIVE;
    }
    ptp_state = value;
    return;
}

bool getPtpStatus(){
    return ptp_state;
}

uint16_t csum(const uint16_t *message, int length) {
    uint32_t checksum = 0;

    for (int i = 0; i < length; i++) {
        checksum += __builtin_bswap16(message[i]);
        if (checksum > 0xFFFF) {
            checksum = (checksum & 0xFFFF) + 1; // fold 32-bit sum to 16 bits
        }
    }

    return __builtin_bswap16(~checksum); // complement and truncate to 16 bits
}


packet_t * createUDPpack(eth_int_t *p_eth, uint32_t dest_ip, uint16_t dest_port, uint16_t src_port, uint8_t *payload, size_t size){

    packet_t *p_pack = (packet_t *)malloc(sizeof(packet_t)); // allocate mamory for new packet
    p_pack->payload = payload;
    p_pack->payloadSize = size;

    // ETH Header
    memcpy(p_pack->eh.ether_shost,p_eth->mac,6); //copy mac to ethernet header

    if ((dest_ip & 0xF0) == 0xE0) {
        p_pack->eh.ether_dhost[0] = 0x01;
        p_pack->eh.ether_dhost[1] = 0x00;
        p_pack->eh.ether_dhost[2] = 0x5E;
        p_pack->eh.ether_dhost[3] = (dest_ip >> 8) & 0x7F;
        p_pack->eh.ether_dhost[4] = (dest_ip >> 16) & 0xFF;
        p_pack->eh.ether_dhost[5] = (dest_ip >> 24) & 0xFF;
        p_pack->iph.ttl = 1; // hops
    } else {
        p_pack->eh.ether_dhost[0] = 0xFF;
        p_pack->eh.ether_dhost[1] = 0xFF;
        p_pack->eh.ether_dhost[2] = 0xFF;
        p_pack->eh.ether_dhost[3] = 0xFF;
        p_pack->eh.ether_dhost[4] = 0xFF;
        p_pack->eh.ether_dhost[5] = 0xFF;
        p_pack->iph.ttl = 10; // hops
    }

    p_pack->eh.ether_type = htons(ETH_P_IP); // set type

    // IP Header
    p_pack->iph.ihl = 5;
    p_pack->iph.version = 4;
    p_pack->iph.tos = 0; // Low delay
    p_pack->iph.id = 0;
    p_pack->iph.protocol = 17; // UDP
    p_pack->iph.saddr = p_eth->ip;   // Source IP address
    p_pack->iph.daddr = dest_ip;   // Destination IP address

    // Length of IP payload and header
    p_pack->iph.tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + p_pack->payloadSize);

    p_pack->iph.frag_off = 0;
    p_pack->iph.check = 0;

    // Calculate IP checksum on completed header
    void * ip_copy = malloc(sizeof(p_pack->iph));
    memcpy(ip_copy,&(p_pack->iph),sizeof(p_pack->iph));
    p_pack->iph.check = csum((uint16_t *)ip_copy, sizeof(struct iphdr)/2);

    free(ip_copy);

    // UDP Header
    p_pack->udph.source = src_port;
    p_pack->udph.dest = dest_port;
    p_pack->udph.check = 0;
    p_pack->udph.len = htons(p_pack->payloadSize  + sizeof(struct udphdr));

    return p_pack;
}

uint8_t * bufUDP(packet_t * pack, size_t * buffer_size){
    *buffer_size = sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr) + pack->payloadSize;
    uint8_t * sendbuf = (uint8_t *)malloc(*buffer_size);

    // Copy Ethernet header, IP header, and UDP header into send buffer
    memcpy(sendbuf, &(pack->eh), sizeof(struct ether_header));
    memcpy(sendbuf + sizeof(struct ether_header), &(pack->iph), sizeof(struct iphdr));
    memcpy(sendbuf + sizeof(struct ether_header) + sizeof(struct iphdr), &(pack->udph), sizeof(struct udphdr));

    // Copy payload to send buffer
    memcpy(sendbuf + sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr), pack->payload, pack->payloadSize);

    // Create UDP pseudo-header
    struct {
        uint32_t source_ip;
        uint32_t dstIp;
        uint8_t zeroPadding;
        uint8_t protocol;
        uint16_t udpLen;
    } UDP_pseudoheader;

    UDP_pseudoheader.source_ip =  pack->iph.saddr;
    UDP_pseudoheader.dstIp =  pack->iph.daddr;
    UDP_pseudoheader.zeroPadding = 0x00;
    UDP_pseudoheader.protocol = IPPROTO_UDP;
    UDP_pseudoheader.udpLen = htons(pack->payloadSize  + sizeof(struct udphdr));

    // Create buffer for pseudo-header, UDP header, and payload
    int pseudo_buffer_size = sizeof(UDP_pseudoheader) + sizeof(struct udphdr) + pack->payloadSize;
    uint8_t *pseudo_buffer = (uint8_t*)malloc(pseudo_buffer_size);
    memset(pseudo_buffer, 0, pseudo_buffer_size);
    memcpy(pseudo_buffer, &UDP_pseudoheader, sizeof(UDP_pseudoheader));
    memcpy(pseudo_buffer + sizeof(UDP_pseudoheader), &(pack->udph), sizeof(struct udphdr));
    memcpy(pseudo_buffer + sizeof(UDP_pseudoheader) + sizeof(struct udphdr), pack->payload, pack->payloadSize);

    // Recalculate UDP checksum
    struct udphdr *udph = (struct udphdr *)(pseudo_buffer + sizeof(UDP_pseudoheader));
    udph->check = 0;
    udph->check = csum((uint16_t *)pseudo_buffer, pseudo_buffer_size / 2);

    // Copy the recalculated checksum back to the send buffer
    memcpy(sendbuf + sizeof(struct ether_header) + sizeof(struct iphdr) + offsetof(struct udphdr, check), &(udph->check), sizeof(udph->check));

    free(pseudo_buffer);

    return sendbuf;
}

void mj_txpool()
{
    return;
}


int setThreadPriority(pthread_t thread_id, int priority_offset, struct sched_param * param){
    // Set the scheduling policy to FIFO
    int policy = SCHED_FIFO;
    // Set the priority
    param->sched_priority = sched_get_priority_max(SCHED_FIFO) - priority_offset;
    if(pthread_setschedparam(thread_id, policy, param) != 0) {
        perror("MJDRV: CRITICAL: Failed to set thread priority");
        return -1;
    }
    return 0;
}

int setThreadAffininty(pthread_t thread_id, int thread_core, struct sched_param * param, char * name){
    // Create a cpu_set_t object that will hold the CPU affinity information
    cpu_set_t cpuset;
    // Clear the cpu set, so that it doesn't have any CPUs selected
    CPU_ZERO(&cpuset);
    // Add the current CPU (indicated by 'thread_core') to the cpu set
    CPU_SET(thread_core, &cpuset);
    // Set the CPU affinity for the current thread.
    if(pthread_setaffinity_np(thread_id, sizeof(cpu_set_t), &cpuset)!= 0) {
        perror("MJDRV: CRITICAL: Failed to set thread affinity");
        return -1;
    }
    cpu_set_t get_cpuset;
    CPU_ZERO(&get_cpuset);
    int ret = pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &get_cpuset);
    if (ret != 0) {
        fprintf(stderr, "MJDRV: Error getting CPU affinity: %s\n", strerror(ret));
    } else {
        for (int i = 0; i < CPU_SETSIZE; i++) {
            if (CPU_ISSET(i, &get_cpuset)) {
                char msg[128];
                sprintf(msg,"MJDRV: %s thread is running on CPU %d (%d) with priority %d\n",name, i, tx.core, param->sched_priority);
                write(2,msg,strlen(msg));
            }
        }
    }
    return 0;
}


void * transmitFunction(void *arg){
    tx.thread_id = pthread_self();
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    struct sched_param param;

    char * name = (char *)"TX";
    setThreadPriority(tx.thread_id, 3, &param);
    setThreadAffininty(tx.thread_id, tx.core, &param, name);

    struct timespec timer;
    clock_gettime(CLOCK_MONOTONIC, &timer);
    struct timespec interval;
    interval.tv_sec = 0;
    interval.tv_nsec = SEND_INTERVAL * 1000;

    void (*p_fcn)(void) = arg;

    while(1){
        // Check if another thread calling us for cancel
        pthread_testcancel();
        // Call MJ Loop function if set
        if (p_loop_fcn)
        {
            p_loop_fcn();
        }

        // Check for TX state
        if(tx.enable){
            // Call MJ tick function
            p_fcn();
            
            if(ptp_state){
                if (ptp_tick_fcn)
                {
                    // Call PTP tick function
                    ptp_tick_fcn();
                }
        }
        }

        // Increment target time by interval
        timer.tv_nsec += interval.tv_nsec;
        // Wrap nanoseconds to seconds
        while (timer.tv_nsec >= 1e9)
        {
            timer.tv_nsec -= 1e9;
            timer.tv_sec++;
        }
        // Sleep until target time
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &timer, NULL);
    }

    return arg;
}

CallbackInfo * getCallbacks(){
    return callbacks;
}

bool bufferHandler(uint8_t * buffer, void ** payload,size_t * payload_size, mj_msg_proc_fcn (*fnc)){
    bool check_result = false;
    struct iphdr *iph = (struct iphdr *) (buffer + sizeof(struct ether_header));
    struct udphdr *udph = (struct udphdr *) (buffer + sizeof(struct iphdr) + sizeof(struct ether_header));
    if(iph->protocol == 17 && iph->saddr != current_eth_if->ip){
        for(int j = 0; j < num_callbacks; j++){
            if(iph->daddr == callbacks[j].dest_ip){
                if(udph->dest == callbacks[j].dest_port){
                    *payload = (buffer +sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr));
                    *payload_size = ntohs(udph->len)-sizeof(struct udphdr);
                    *fnc = callbacks[j].cb;
                    check_result = true;
                    break;
                }
            }
        }
    }
    return check_result;
}


mj_msg_proc_res_t processPacket(uint8_t * buffer, uint64_t time_us){
    void * payload = NULL;
    size_t payload_size = 0;
    mj_msg_proc_fcn fnc = NULL;
    mj_msg_proc_res_t result = MJ_PROC_FAIL;
    uint32_t ts_s, ts_ns;
    // Extract seconds
    ts_s = (uint32_t)(time_us/1000000UL);
    // Extract microseconds and save in nanoseconds
    ts_ns = (uint32_t)(time_us % 1000000UL)*1000;
    struct timespec proc_time = {ts_s, ts_ns};

    if(bufferHandler(buffer,&payload,&payload_size, &fnc)){
        // That data passes to callback our function
        uint8_t *cbData = (uint8_t *)malloc(payload_size);
        memcpy(cbData, payload, payload_size);
        result = fnc(cbData, payload_size, ts_s, ts_ns);
        if(logFunction_p != NULL){
            size_t buffer_size = payload_size + sizeof(struct udphdr) + sizeof(struct iphdr) + sizeof(struct ether_header);
            logFunction_p(buffer, buffer_size, proc_time);
        }
    }
    return result;
}


void * receiveFunction(void * args) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    struct sched_param param;

    char * name = (char *)"RX";
    setThreadPriority(rx.thread_id, 0, &param);
    setThreadAffininty(rx.thread_id, rx.core, &param, name);

    int buffer_size = 0;
    uint8_t recieve_buffer[BUF_SIZE];

    struct pollfd poll_attr;
    poll_attr.events = POLL_IN;
    poll_attr.revents = POLLERR;
    poll_attr.fd = rx.socket;

    struct timespec rx_time;

    while(1){
        pthread_testcancel();
        if(rx.enable){
            poll(&poll_attr,1,1000);
            //run recvfrom to listen the socket
            buffer_size = recvfrom(rx.socket, recieve_buffer, BUF_SIZE, 0, NULL, NULL);
            if(buffer_size > 0){ //when recieve packet -> check its length and pass it to handler
                // Get packet rx time from socket in timespec format (bash: man 7 socket and data digging)
                ioctl(rx.socket, SIOCGSTAMPNS, &rx_time);

                mj_msg_proc_fcn fnc; //callback function
                void * payload;
                size_t payload_size;

                //handler needs to check IP, Protocol, Port and extract data
                if(bufferHandler(recieve_buffer,&payload,&payload_size, &fnc)){
                    //That data passes to callback function
                    uint8_t * cbData = (uint8_t *) malloc(payload_size);
                    memcpy(cbData, payload, payload_size);
                    if(fnc(cbData, payload_size, rx_time.tv_sec, rx_time.tv_nsec) == MJ_ACCEPT){
                        //save this packet to binaries if logger service is enabled
                        if(logFunction_p != NULL){
                            logFunction_p(recieve_buffer, buffer_size, rx_time);
                        }
                    }
                    else free(cbData); //If data doesn't needed -> free memory from it
                }
            }

            else if (buffer_size == -1) {
                perror("MJDRV: Error in recvfrom()");
            }
        }else{
            sleep(1);
        }
    }

    return args;
}

int getSocket(){
    int socket_to_listen = 0;

    // Open PF_PACKET socket, listening for EtherType ETHER_TYPE
    if ((socket_to_listen = socket(PF_PACKET, SOCK_RAW, htons(ETHER_TYPE))) == -1){
        perror("MJDRV: CRITICAL: Unable to open listening socket");
        return -1;
    }

    struct ifreq ifopts;

    // Set interface to promiscuous mode
    strncpy(ifopts.ifr_name, interface_name, IFNAMSIZ-1);
    ioctl(socket_to_listen, SIOCGIFFLAGS, &ifopts);
    ifopts.ifr_flags |= IFF_PROMISC; // set promiscuous mode
    ioctl(socket_to_listen, SIOCSIFFLAGS, &ifopts);

    // Получение индекса интерфейса
    if (ioctl(socket_to_listen, SIOCGIFINDEX, &ifopts) == -1) {
        close(socket_to_listen);
        return -1;
    }

    struct timeval read_timeout;
    read_timeout.tv_sec = 0;
    read_timeout.tv_usec = 250;
    if(setsockopt(socket_to_listen, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof(read_timeout))){
        perror("MJDRV: CRITICAL: An error occured trying to set socket timeout");
        close(socket_to_listen);
        return -1;
    }

    if(setsockopt(socket_to_listen, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifopts, sizeof(ifopts))){
        perror("MJDRV: CRITICAL: An error occured trying to bind socket to the interface");
        close(socket_to_listen);
        return -1;
    }

//    if(setsockopt(socket_to_listen, SOL_SOCKET, SO_TIMESTAMPING_NEW, (void *)&ifopts, sizeof(ifopts))){
//        close(socket_to_listen);
//        return -1;
//    }

    // Привязка сокета к интерфейсу
    memset(&rx.socket_address, 0, sizeof(rx.socket_address));
    rx.socket_address.sll_family = AF_PACKET;
    rx.socket_address.sll_ifindex = ifopts.ifr_ifindex;
    rx.socket_address.sll_protocol = htons(ETH_P_ALL);
    rx.socket_address.sll_halen = ETH_ALEN;

    if (bind(socket_to_listen, (struct sockaddr *)&rx.socket_address, sizeof(rx.socket_address)) == -1) {
        perror("MJDRV: CRITICAL: Could not bind RX socket to interface");
        close(socket_to_listen);
        return -1;
    }

    return socket_to_listen;
}

uint8_t * bufIGMP(igmp2Msg_t * pack, size_t * buffer_size){
    *buffer_size = sizeof(*pack);
    uint8_t * sendbuf = (uint8_t *)malloc(*buffer_size);

    memcpy(sendbuf,&(pack->eth),sizeof(struct ether_header));
    memcpy(sendbuf + sizeof(struct ether_header),&(pack->ip_ext),sizeof(struct iphdr));
    memcpy(sendbuf + sizeof(struct ether_header) + sizeof(struct iphdr),pack->ip_ext.ip_options,4);
    memcpy(sendbuf + sizeof(struct ether_header) + sizeof(struct iphdr) + 4,&(pack->type),8);
    return sendbuf;
}


void mj_IGMPtx(igmp2Msg_t * p_igmp){
    size_t buffer_size = 0;
    uint8_t * sendbuf = bufIGMP(p_igmp, &buffer_size);


    if (sendto(tx.socket, sendbuf, buffer_size, 0, (struct sockaddr*)&tx.socket_address, sizeof(struct sockaddr_ll)) < 0){
        printf("MJDRV: Send failed (IGMP PACKET)\n");
    }else{
        if (logFunction_p != NULL){
            struct timespec tx_time;
            timespec_get(&tx_time,TIME_UTC);
            logFunction_p(sendbuf, buffer_size,tx_time);
        }
    }
    free(sendbuf);
    return;
}

void igmp2_createJoin(eth_int_t *interface, igmp2Msg_t *msg, uint32_t group_ip)
{
    // ETH Header
    memcpy(msg->eth.ether_shost, interface->mac, 6);
    msg->eth.ether_type = htons(ETH_P_IP); // IPv4 type
    msg->eth.ether_dhost[0] = 0x01;
    msg->eth.ether_dhost[1] = 0x00;
    msg->eth.ether_dhost[2] = 0x5E;
    msg->eth.ether_dhost[3] = (group_ip >> 8) & 0x7F;
    msg->eth.ether_dhost[4] = (group_ip >> 16) & 0xFF;
    msg->eth.ether_dhost[5] = (group_ip >> 24) & 0xFF;

    // IP Header
    msg->ip_ext.ip.ttl = 1;
    msg->ip_ext.ip.id = 0;
    msg->ip_ext.ip.version = 4;
    /*
     * 24 bytes because 4 bytes allocated for IP Header options
     * that must be used for IGMP as said in RFC 2236:
     *
     * All IGMP messages described in this document are sent with IP
     * TTL 1, and contain the IP Router Alert option [RFC 2113] in their IP
     * header.
     *
    */
    msg->ip_ext.ip.ihl = 6;

    msg->ip_ext.ip.protocol = IPPROTO_IGMP;
    msg->ip_ext.ip.saddr = interface->ip;
    msg->ip_ext.ip.daddr = group_ip; // As said in RFC 2236
    msg->ip_ext.ip.frag_off = htons(IP_DF); //Without it packet looks like LLC type
    msg->ip_ext.ip.tot_len = htons(sizeof(igmp2Msg_t) - sizeof(struct ether_header));
    msg->ip_ext.ip.check = 0;

    msg->ip_ext.ip_options[0] = 0x94; // IP Router Alert option
    msg->ip_ext.ip_options[1] = 0x04; // Length of IP options
    msg->ip_ext.ip_options[2] = 0x00; // Basically padding
    msg->ip_ext.ip_options[3] = 0x00; // -/-


    //Calculating checksum without possible error
    void * ip_copy = malloc(sizeof(msg->ip_ext));
    memcpy(ip_copy,&(msg->ip_ext),sizeof(msg->ip_ext));

    msg->ip_ext.ip.check = csum((uint16_t*)ip_copy, (sizeof(struct iphdr) + 4) / 2);

    free(ip_copy);

    //IGMP Header
    msg->type = 0x16; // IGMPv2 Membership report
    msg->maxRespTime = 0; // Doesn't matter for this type of message
    msg->groupAddr = group_ip;
    msg->csum = 0;
    msg->csum = csum((uint16_t*)&msg->type, sizeof(igmp2Msg_t) / 2 - sizeof(struct ether_header) / 2 - (sizeof(struct iphdr)+sizeof(uint8_t)*4) / 2);
    return;
}


void setEthernetInterfaceName(char *name) {
    // Free previously allocated memory if any
    if (interface_name) {
        free(interface_name);
    }

    // Allocate memory for interface_name
    interface_name = (char *)malloc(strlen(name)+1);
    if (!interface_name) {
        // Handle memory allocation failure
        perror("MJDRV: Failed to allocate memory for interface_name");
        return;
    }

    // Copy the data
    strcpy(interface_name,name);

    char info_msg[128];
    sprintf(info_msg,"MJDRV: Set interface name: %s\n",interface_name);
    write(2,info_msg,strlen(info_msg));

    return;
}

void mj_drvInit()
{  
    //Transmitter start configuration
    tx.core = 3;

    //Receiver start configuration
    rx.core = 1;

    if(interface_name){
        const int len = strnlen(interface_name, IFNAMSIZ);

        // Open RAW socket to send on
        if ((tx.socket = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1){
            perror("MJDRV: CRITICAL: TX Socket was not created");
            return;
        }

        // Get the index of the interface to send on
        memset(&if_idx, 0, sizeof(struct ifreq));
        strncpy(if_idx.ifr_name, interface_name, len);
        if (ioctl(tx.socket, SIOCGIFINDEX, &if_idx) < 0){
            perror("MJDRV: CRITICAL: Could not get TX interface index");
            close(tx.socket);
            return;
        }
        int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
        memset(&if_req, 0, sizeof(struct ifreq));
        strncpy(if_req.ifr_name, interface_name, len);
        if (ioctl(fd, SIOCGIFHWADDR, &if_req) < 0){
            perror("MJDRV: CRITICAL: Could not get interface hw adress");
            close(fd);
            return;
        }
        close(fd);

        if(setsockopt(tx.socket, SOL_SOCKET, SO_BINDTODEVICE, (void *)&if_idx, sizeof(if_idx))){
            perror("MJDRV: CRITICAL: An error occured trying to bind socket to the interface");
            close(tx.socket);
            return;
        }

        // Привязка сокета к интерфейсу
        memset(&tx.socket_address, 0, sizeof(tx.socket_address));
        tx.socket_address.sll_family = AF_PACKET;
        tx.socket_address.sll_ifindex = if_idx.ifr_ifindex;
        tx.socket_address.sll_protocol = htons(ETH_P_ALL);
        tx.socket_address.sll_halen = ETH_ALEN;

        rx.socket = getSocket();
    }
    else{
        perror("MJDRV: CRITICAL: No interface name");
    }
    return;
}

void reinit_mjdrv(){
    close(tx.socket);
    close(rx.socket);
    mj_drvInit();
    return;
}

void deinit_mjdrv(){
    setTxStatus(false);
    setRxStatus(false);
    pthread_cancel(tx.thread_id);
    pthread_cancel(rx.thread_id);
    close(tx.socket);
    close(rx.socket);
    return;
}

socket_info getSocketInfo(){
    socket_info current_socket;
    current_socket.address = (struct sockaddr*)&tx.socket_address;
    current_socket.socket = tx.socket;
    return current_socket;
}

static uint8_t* mj_alloc(uint16_t size)
{
    void * p = malloc(size);
    memset(p,0,size);
    return p;
}

void mj_free(uint8_t *ptr)
{
    if (ptr)
    {
        free(ptr);
    }
    return;
}

static void * mj_regEthInterface(const uint8_t *mac, uint32_t source_ip){
    eth_int_t *p_eth = (eth_int_t *)malloc(sizeof(eth_int_t));
    memcpy(p_eth->mac,if_req.ifr_ifru.ifru_hwaddr.sa_data,6);
    p_eth->ip = source_ip;
    current_eth_if = p_eth;
    return ((void*)(p_eth));
}

static void * mj_regUdp4Pkt(void *ethInt, uint32_t dest_ip, uint16_t dest_port, uint16_t src_port, uint8_t *payload, uint16_t size)
{
    if (!ethInt)
    {
        return NULL;
    }

    eth_int_t *p_eth = (eth_int_t*)(ethInt); //get struct of recieved interface
    packet_t * pack = createUDPpack(p_eth, dest_ip, dest_port, src_port, payload, size);
    return ((void *)(pack));
}

uint8_t * mj_getUdp4Payload(void *pkt)
{
    packet_t *p_pack = (packet_t *)pkt;
    return p_pack->payload;
}

void mj_mcastJoin(void *ethInt, uint32_t IP)
{
    eth_int_t *p_eth = (eth_int_t *) ethInt;
    igmp2Msg_t *p_igmp = (igmp2Msg_t*)malloc(sizeof(igmp2Msg_t));
    igmp2_createJoin(p_eth,p_igmp,IP);
    mj_IGMPtx(p_igmp);
    free(p_igmp);
    return;
}

mj_status_t mj_regUdp4Cb(uint32_t dest_ip, uint16_t dest_port, mj_msg_proc_fcn callback){
    // Check if there's a room for another callback
    if (num_callbacks >= MAX_CALLBACKS){
        return MJ_FAIL;
    }

    // Save callback information
    callbacks[num_callbacks].dest_ip = dest_ip;
    callbacks[num_callbacks].dest_port = dest_port;
    callbacks[num_callbacks].cb = callback; // Store the function pointer

    //Check for running receiver thread
    if (!rx.is_running){
        //Start a new thread to catch packets and process them with callbacks
        pthread_create(&rx.thread_id, NULL, receiveFunction, NULL);
        //Change status
        rx.is_running = true;
    }

    num_callbacks++;

    return MJ_OK;
}

void mj_setUdp4PayloadPtr(void *pkt, uint8_t *payload)
{
    packet_t *p_pack = (packet_t *)pkt;
    p_pack->payload = payload; // Set the payload pointer
    return;
}


void mj_udp4tx(void * pack, mj_tx_end_cb cb){
    static uint16_t send_fail_counter = 0;
    size_t buffer_size;
    packet_t *p_pack = (packet_t *)pack;
    uint8_t *sendbuf = bufUDP(p_pack, &buffer_size);

    if (sendto(tx.socket, sendbuf, buffer_size, 0, (struct sockaddr*)&tx.socket_address, sizeof(struct sockaddr_ll)) < 0){
        printf("MJDRV: Send failed (UDP PACKET) #%u\n", send_fail_counter);
        send_fail_counter++;
    }else{
        struct timespec tx_time;
        timespec_get(&tx_time,TIME_UTC);
        if (logFunction_p != NULL){
            logFunction_p(sendbuf, buffer_size, tx_time);
        }
        if (cb){
            cb(MJ_OK,tx_time.tv_sec,tx_time.tv_nsec);
        }
    }

    free(sendbuf);
    return;
}

void mj_set_dscp(void * pack, uint8_t dscp){
    packet_t *p_pack = (packet_t *)pack;
    uint8_t tos = p_pack->iph.tos & 0x03;
    p_pack->iph.tos = (dscp << 2) | tos;

    // Recalculate IP Header checksum after changing its field
    p_pack->iph.check = 0;
    void * ip_copy = malloc(sizeof(p_pack->iph));
    memcpy(ip_copy,&(p_pack->iph),sizeof(p_pack->iph));
    p_pack->iph.check = csum((uint16_t *)ip_copy, sizeof(p_pack->iph)/2);
    free(ip_copy);

    return;
}

void mj_set_ttl(void * pack, uint8_t ttl){
    packet_t *p_pack = (packet_t *)pack;
    p_pack->iph.ttl = ttl;

    // Recalculate IP Header checksum after changing its field
    p_pack->iph.check = 0;
    void * ip_copy = malloc(sizeof(p_pack->iph));
    memcpy(ip_copy,&(p_pack->iph),sizeof(p_pack->iph));
    p_pack->iph.check = csum((uint16_t *)ip_copy, sizeof(p_pack->iph)/2);
    free(ip_copy);

    return;
}

uint32_t mj_get_timestamp(uint32_t *sec, uint32_t *nan_sec){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    *sec = ts.tv_sec;
    *nan_sec = ts.tv_nsec;
    return 1; // Уточнить что ожидается на выходе
}

void init_mjdrv(mj_drv_interface_t * idrv)
{
    mj_drvInit();
    idrv->udp4.alloc = mj_alloc;
    idrv->udp4.create_interface = mj_regEthInterface;
    idrv->udp4.create_out_pkt = mj_regUdp4Pkt;
    idrv->udp4.free = mj_free;
    idrv->udp4.get_payload = mj_getUdp4Payload;
    idrv->udp4.join_group = mj_mcastJoin;
    idrv->udp4.pool_tx = mj_txpool;
    idrv->udp4.register_callback = mj_regUdp4Cb;
    idrv->udp4.set_payload = mj_setUdp4PayloadPtr;
    idrv->udp4.tx = mj_udp4tx;
    idrv->udp4.set_dscp = mj_set_dscp;
    idrv->timestamp = mj_get_timestamp;
    return;
}
