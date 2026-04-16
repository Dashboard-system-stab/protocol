/*
 * Author: Korotkov M.I.
 *
 * Date: 10.12.2024
 *
 * */

#include "ptp.h"
#include "math.h"
#include "microjet_driver.h"
#include "mjsysspec.h"

in_addr_t ptp_primary = 0;
mj_drv_interface_t * drv_p = NULL;

void * out_ptp_announce_pkt = NULL;
static ptp_announce_t * announce_pkt = NULL;

void * out_ptp_sync_pkt = NULL;
static ptp_sync_t * sync_pkt = NULL;

void * out_ptp_follow_up_pkt = NULL;
static ptp_follow_up_t * follow_up_pkt = NULL;

void * out_ptp_delay_resp_pkt = NULL;
static ptp_delay_respond_t * delay_resp_pkt;

static uint32_t ptp_join_counter = 0;
static uint32_t ptp_announce_counter = 0;
static uint32_t ptp_sync_counter = 0;
static uint32_t ptp_delay_req_counter = 0;

static uint32_t ptp_join_counter_limit = 0;
static uint32_t ptp_announce_counter_limit = 0;
static uint32_t ptp_sync_counter_limit = 0;
static uint32_t ptp_delay_req_counter_limit = 0;

static uint16_t ptp_announce_sequence_cnt = 0;
static uint16_t ptp_sync_sequence_cnt = 0;

static uint64_t ptp_announce_await_tick = 0;

/*
 * IEEE 1588-2008 7.5.2.2.3
 * For non EUI-64 devices needs to have address technology bytes
 * First byte must have value 0xFF
 * Second byte for common devices have value 0xFE
*/
uint8_t ptp_addressTechnology[2] = {0xff,0xfe};

ptp_default_DS_t defaultDS;
ptp_current_DS_t currentDS;
ptp_parent_DS_t parentDS;
ptp_time_properties_DS_t timePropertiesDS;
ptp_port_DS_t portDS;

ptp_dev_info ptp_dev_stats[16] = {0};

extern eth_int_t * current_eth_if;
extern void mj_set_ttl(void * pack, uint8_t ttl);


void htons_u48(uint8_t * dest, uint8_t * src){
    if(dest && src){
        uint8_t temp[6];
        memcpy(temp,src,sizeof(uint8_t)*6);
        for (int idx = 0; idx <= 5; ++idx) {
            dest[idx] = temp[5-idx];
        }
    }

    return;
}


void ptp_SendFollowUp(){
    if(out_ptp_follow_up_pkt){
        struct timespec ts;
        timespec_get(&ts, TIME_UTC);

        follow_up_pkt->preciseOriginTimestamp.seconds.u48 = ts.tv_sec;
        htons_u48(follow_up_pkt->preciseOriginTimestamp.seconds.u8, follow_up_pkt->preciseOriginTimestamp.seconds.u8);

        follow_up_pkt->preciseOriginTimestamp.nanoseconds = ts.tv_nsec;
        follow_up_pkt->preciseOriginTimestamp.nanoseconds = htonl(follow_up_pkt->preciseOriginTimestamp.nanoseconds);

        follow_up_pkt->header.sequenceId = htons(ptp_sync_sequence_cnt);
        drv_p->udp4.tx(out_ptp_follow_up_pkt,NULL);
    }

    return;
}

void ptp_SendSync(){
    if(out_ptp_sync_pkt){
        sync_pkt->header.sequenceId = htons(ptp_sync_sequence_cnt);
        drv_p->udp4.tx(out_ptp_sync_pkt,ptp_SendFollowUp);
        ptp_sync_sequence_cnt++;
    }

    return;
}


void ptp_SendDelayRespond(){
    if(out_ptp_delay_resp_pkt){
        drv_p->udp4.tx(out_ptp_delay_resp_pkt,NULL);
    }

    return;
}


void ptp_SendAnnounce(){
    if(out_ptp_announce_pkt){
        struct timespec ts;
        timespec_get(&ts, TIME_UTC);

        announce_pkt->originTimestamp.seconds.u48 = ts.tv_sec;
        htons_u48(announce_pkt->originTimestamp.seconds.u8,announce_pkt->originTimestamp.seconds.u8);

        announce_pkt->originTimestamp.nanoseconds = ts.tv_nsec;
        announce_pkt->originTimestamp.nanoseconds = htonl(announce_pkt->originTimestamp.nanoseconds);

        announce_pkt->header.sequenceId = htons(ptp_announce_sequence_cnt);

        drv_p->udp4.tx(out_ptp_announce_pkt, NULL);
        ptp_announce_sequence_cnt++;
    }

    return;
}


void ptp_tick(){
    if(ptp_announce_counter >= ptp_announce_counter_limit){
        ptp_SendAnnounce();
        ptp_announce_counter = 0;
    }
    ptp_announce_counter++;

    if(ptp_sync_counter >= ptp_sync_counter_limit){
        ptp_SendSync();
        ptp_sync_counter = 0;
    }
    ptp_sync_counter++;

    if(ptp_join_counter >= ptp_join_counter_limit){
        drv_p->udp4.join_group(current_eth_if,ptp_primary);
        ptp_join_counter = 0;
    }
    ptp_join_counter++;

    return;
}

void ptp_CreateAnnounce(){
    ptp_header_t header;
    header.transport_specific = 0x00;
    header.messageType = PTP_ANNOUNCE;
    header.reserved_1 = 0x00;
    header.versionPTP = portDS.versionNumber;
    header.messageLength = htons(sizeof(ptp_announce_t));
    header.domainNumber = defaultDS.domainNumber;
    header.reserved_2 = 0x00;
    header.flags.u16 = 0;
    header.flags.ptp_timescale = timePropertiesDS.ptpTimescale;
    header.correction = 0x00;
    header.reserved_3 = 0;
    memcpy(header.sourcePortIdentity.clockIdentity.u8,portDS.portIdentity.clockIdentity.u8,sizeof(portDS.portIdentity.clockIdentity.u8));
    header.sourcePortIdentity.portNumber = htons(0x01);
    header.sequenceId = 0;
    header.control = PTP_MESSAGE_CONTROL_OTHER;
    header.logMessageInterval = portDS.logAnnouncementInterval;

    announce_pkt->header = header;
    announce_pkt->originTimestamp.nanoseconds = 0x0;
    announce_pkt->originTimestamp.seconds.u48 = 0x0;
    announce_pkt->currentUtcOffset = timePropertiesDS.currentUTCOffset;
    announce_pkt->reserved_1 = 0x00;
    announce_pkt->grandmasterPriority1 = parentDS.grandmasterPriority_1;
    announce_pkt->grandmasterClockQuality = parentDS.grandmasterClockQuality;
    announce_pkt->grandmasterPriority2 = parentDS.grandmasterPriority_2;
    memcpy(announce_pkt->grandmasterIdentity.u8,parentDS.grandmasterIdentity.u8,sizeof(uint8_t)*8);
    announce_pkt->stepsRemoved = htons(currentDS.stepsRemoved);
    announce_pkt->timeSource = timePropertiesDS.timeSource;

    return;
}

void ptp_CreateSync(){
    ptp_header_t header;
    header.transport_specific = 0x00;
    header.messageType = PTP_SYNC;
    header.reserved_1 = 0x00;
    header.versionPTP = portDS.versionNumber;
    header.messageLength = htons(sizeof(ptp_sync_t));
    header.domainNumber = defaultDS.domainNumber;
    header.reserved_2 = 0x00;
    header.flags.u16 = 0;
    header.flags.ptp_two_step = defaultDS.twoStepFlag;
    header.correction = 0x00;
    header.reserved_3 = 0;
    memcpy(header.sourcePortIdentity.clockIdentity.u8,portDS.portIdentity.clockIdentity.u8,sizeof(portDS.portIdentity.clockIdentity.u8));
    header.sourcePortIdentity.portNumber = htons(0x01);
    header.sequenceId = 0x00;
    header.control = PTP_MESSAGE_CONTROL_SYNC;
    header.logMessageInterval = 0;

    sync_pkt->header = header;
    sync_pkt->originTimestamp.nanoseconds = 0x0;
    sync_pkt->originTimestamp.seconds.u48 = 0x0;

    return;
}

void ptp_CreateFollowUp(){
    ptp_header_t header;
    header.transport_specific = 0x00;
    header.messageType = PTP_FOLLOW_UP;
    header.reserved_1 = 0x00;
    header.versionPTP = 0x02;
    header.messageLength = htons(sizeof(ptp_follow_up_t));
    header.domainNumber = 0x00;
    header.reserved_2 = 0x00;
    header.flags.u16 = 0;
    header.correction = 0x00;
    header.reserved_3 = 0;
    memcpy(header.sourcePortIdentity.clockIdentity.u8,portDS.portIdentity.clockIdentity.u8,sizeof(portDS.portIdentity.clockIdentity.u8));
    header.sourcePortIdentity.portNumber = htons(0x01);
    header.sequenceId = 0;
    header.control = PTP_MESSAGE_CONTROL_FOLLOW_UP;
    header.logMessageInterval = 0;

    follow_up_pkt->header = header;
    follow_up_pkt->preciseOriginTimestamp.nanoseconds = 0x0;
    follow_up_pkt->preciseOriginTimestamp.seconds.u48 = 0x0;

    return;
}

void ptp_CreateDelayResp(){
    ptp_header_t header;
    header.transport_specific = 0x00;
    header.messageType = PTP_DELAY_RESP;
    header.reserved_1 = 0x00;
    header.versionPTP = 0x02;
    header.messageLength = htons(sizeof(ptp_delay_respond_t));
    header.domainNumber = 0x00;
    header.reserved_2 = 0x00;
    header.flags.u16 = 0;
    header.correction = 0x00;
    header.reserved_3 = 0;
    memcpy(header.sourcePortIdentity.clockIdentity.u8,portDS.portIdentity.clockIdentity.u8,sizeof(portDS.portIdentity.clockIdentity.u8));
    header.sourcePortIdentity.portNumber = htons(0x01);
    header.sequenceId = 0;
    header.control = PTP_MESSAGE_CONTROL_DELAY_RESP;
    header.logMessageInterval = 0;

    delay_resp_pkt->header = header;
    delay_resp_pkt->recieveTimestamp.nanoseconds = 0x0;
    delay_resp_pkt->recieveTimestamp.seconds.u48 = 0x0;
    memset(delay_resp_pkt->requestingPortIdentity.clockIdentity.u8,0,8);
    delay_resp_pkt->requestingPortIdentity.portNumber = 0;
    return;
}



void ptp_InitializeDatasets(){
    //Initializing values of Default dataset
    defaultDS.twoStepFlag = true;
    memcpy(defaultDS.clockIdentity.vendor,current_eth_if->mac,3);
    memcpy(defaultDS.clockIdentity.addressTechnology, ptp_addressTechnology, 2);
    memcpy(defaultDS.clockIdentity.id, current_eth_if->mac+3,3);
    defaultDS.numberPorts = 1;
    defaultDS.clockQuality.clockClass = PTP_CLOCK_CLASS_SYNC_TO_APPLICATION_SPECIFIC_TIME_SOURCE;
    defaultDS.clockQuality.clockAccuracy = PTP_CLOCK_ACCURACY_10_MS;
    defaultDS.clockQuality.offsetScaledLogVariance = htons(65535);
    defaultDS.priority_1 = 128;
    defaultDS.priority_2 = 248;
    defaultDS.domainNumber = 0;
    defaultDS.slaveOnly = false;

    //Initializing values of Current dataset
    currentDS.stepsRemoved = 0;
    currentDS.offsetFromMaster = 0;
    currentDS.meanPathDelay = 0;

    //Initializing values of Parent dataset
    memcpy(parentDS.parentPortIdentity.clockIdentity.u8,defaultDS.clockIdentity.u8,sizeof(defaultDS.clockIdentity.u8));
    parentDS.parentPortIdentity.portNumber = 0;
    parentDS.parentStats = false;
    parentDS.observedParentOffsetScaledLogVariance = 0xffff;
    parentDS.observedParentClockPhaseChangeRate = 0x7fffffff;
    memcpy(parentDS.grandmasterIdentity.u8,defaultDS.clockIdentity.u8,sizeof(defaultDS.clockIdentity.u8));
    parentDS.grandmasterClockQuality = defaultDS.clockQuality;
    parentDS.grandmasterPriority_1 = defaultDS.priority_1;
    parentDS.grandmasterPriority_2 = defaultDS.priority_2;

    //Initializing values of TimeProperties dataset
    timePropertiesDS.currentUTCOffset = 37;
    timePropertiesDS.currentUtcOffsetValid = true;
    timePropertiesDS.leap59 = false;
    timePropertiesDS.leap61 = false;
    timePropertiesDS.timeTraceability = true;
    timePropertiesDS.frequencyTraceability = false;
    timePropertiesDS.ptpTimescale = true;
    timePropertiesDS.timeSource = PTP_CLOCK_SOURCE_INTERNAL_OSCILLATOR;

    //Initializing values of Port dataset
    memcpy(portDS.portIdentity.clockIdentity.vendor,current_eth_if->mac,sizeof(uint8_t)*3);
    memcpy(portDS.portIdentity.clockIdentity.addressTechnology,ptp_addressTechnology,sizeof(uint8_t)*2);
    memcpy(portDS.portIdentity.clockIdentity.id,current_eth_if->mac+sizeof(uint8_t)*3,sizeof(uint8_t)*3);
    portDS.portState = PTP_PORT_STATE_INITIALIZING;
    portDS.logMinDelayReqInterval = 0; // 1 second = log2(1)
    portDS.peerMeanPathDelay = 0;
    portDS.logAnnouncementInterval = 1; // 2 seconds = log2(2)
    portDS.announceReceiptTimeout = 5000; //ms
    portDS.logSyncInterval = 0; // 1 second = log2(1)
    portDS.delayMechanism = PTP_DELAY_MECHANISM_E2E;
    portDS.logMinPdelayReqInterval = 0; // 1 second = log2(1)
    portDS.versionNumber = 0x02;

    return;
}



void ptp_CalculateMjIntervals(){
    uint16_t time_per_tick_us = SEND_INTERVAL;

    float announce_desired_time_s = exp2f(portDS.logAnnouncementInterval);
    ptp_announce_counter_limit = lroundf((announce_desired_time_s*1e6)/time_per_tick_us);
    ptp_announce_counter = ptp_announce_counter_limit;

    float sync_desired_time_s = exp2f(portDS.logSyncInterval);
    ptp_sync_counter_limit = lroundf((sync_desired_time_s*1e6)/time_per_tick_us);
    ptp_sync_counter = ptp_sync_counter_limit;

    float delay_req_desired_time_s = exp2f(portDS.logMinDelayReqInterval);
    ptp_delay_req_counter_limit = lroundf((delay_req_desired_time_s*1e6)/time_per_tick_us);
    ptp_delay_req_counter = ptp_delay_req_counter_limit;

    uint16_t join_desired_time_s = 5;
    ptp_join_counter_limit = (join_desired_time_s*1e6)/time_per_tick_us;
    ptp_join_counter = ptp_join_counter_limit;

    return;
}

static mj_msg_proc_res_t ptp_EventCallback(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns){
    (void)size;
    (void)ts_s;
    (void)ts_ns;
    mj_msg_proc_res_t cb_result = MJ_REJECT_ID;
    // Save current system tick value
    struct timespec ptp_msg_rx_tick;
    timespec_get(&ptp_msg_rx_tick, TIME_UTC);

    ptp_header_t * header = (ptp_header_t *)data;

    uint16_t msg_type = header->messageType;
    uint32_t device_id = header->reserved_3;

    switch (msg_type)
    {
        case PTP_SYNC:
        {
            if (portDS.portState == PTP_PORT_STATE_SLAVE)
            {
                // Check if master uses 2-step sync (with FollowUp message)
                if(header->flags.ptp_two_step == 1){
                    // Save message sequence id
                    // Set flag that we await FollowUP
                }
            }
            break;
        }
        case PTP_DELAY_REQ:
        {
            // Check if we are in master mode -> only master can reply on that message
            if (portDS.portState == PTP_PORT_STATE_MASTER)
            {
                // Cast pointer to data to delay request type
                ptp_delay_request_t * del_req = (ptp_delay_request_t *)data;

                // Copy the sequenceId field from the Delay_Req
                // message to the sequenceId field of the Delay_Resp message
                delay_resp_pkt->header.sequenceId = del_req->header.sequenceId;

                // Copy the sourcePortIdentity field from the Delay_Req
                // message to the requestingPortIdentity field of the Delay_Resp message
                memcpy(&(delay_resp_pkt->header.sourcePortIdentity),&(del_req->header.sourcePortIdentity),10);

                // Copy the domainNumber field from the Delay_Req message
                // to the domainNumber field of the Delay_Resp message
                delay_resp_pkt->header.domainNumber = del_req->header.domainNumber;

                // Set the correctionField of the Delay_Resp message to 0
                delay_resp_pkt->header.correction = 0;

                // Add the correctionField of the Delay_Req message to
                // the correctionField of the Delay_Resp message
                delay_resp_pkt->header.correction += del_req->header.correction;

                // Set the receiveTimestamp field of the Delay_Resp message to
                // the seconds and nanoseconds portion of the time t4

                delay_resp_pkt->recieveTimestamp.nanoseconds = htonl(ptp_msg_rx_tick.tv_nsec);
                delay_resp_pkt->recieveTimestamp.seconds.u48 = ptp_msg_rx_tick.tv_sec;
                htons_u48(delay_resp_pkt->recieveTimestamp.seconds.u8,delay_resp_pkt->recieveTimestamp.seconds.u8);

                // Issue the Delay_Resp message
                ptp_SendDelayRespond();

            }
            break;
        }
        default:
        {
            break;
        }
    }

    return cb_result;
}

static mj_msg_proc_res_t ptp_GeneralCallback(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns){
    (void)size;
    (void)ts_s;
    (void)ts_ns;

    mj_msg_proc_res_t cb_result = MJ_REJECT_ID;
    // Save current system tick value
    uint64_t ptp_msg_rx_tick = getTimeUs();

    ptp_header_t * header = (ptp_header_t *)data;
    uint32_t device_id = header->reserved_3;
    uint16_t msg_type = header->messageType;
    switch(msg_type){
        case PTP_ANNOUNCE:
        {
            if (portDS.portState == PTP_PORT_STATE_LISTENING)
            {
                long time_delta_ms =  (ptp_msg_rx_tick - ptp_announce_await_tick)/1000L;
                // Check if we are looking for announce by timeout
                bool ptp_announce_wait_time_check = time_delta_ms <= portDS.announceReceiptTimeout;
                if (ptp_announce_wait_time_check)
                {
                    // If we were, then set port state to "SLAVE"
                    portDS.portState = PTP_PORT_STATE_SLAVE;
                }
                else
                {
                    // In case we recieved announce after timeout set port mode to "PASSIVE"
                    portDS.portState = PTP_PORT_STATE_PASSIVE;
                }
            }
            break;
        }
        case PTP_DELAY_RESP:
        {
            if (portDS.portState == PTP_PORT_STATE_SLAVE)
            {
                // Get current sys tick
                // Check id of message to verify that it is what we want
                // Calculate difference between sending DelayReq and recieving DelayResp
                // Apply delay
            }
            break;
        }
        case PTP_FOLLOW_UP:
        {
            // Check if we are waiting for FollowUp
            // Check that message id is corrent
            // Extract timestamp
            // Apply timestamp to device clock
            break;
        }
        default:
        {
            break;
        }
    }

    return cb_result;
}


// This function initializes PTP in driver
// It creates packes of each type and registers PTP callback in driver
void ptp_init(mj_drv_interface_t *drv){
    drv_p = drv;
    if(current_eth_if){

        ptp_InitializeDatasets();
        ptp_CalculateMjIntervals();

        ptp_primary = inet_addr("224.0.1.129");

        announce_pkt = calloc(1,sizeof(ptp_announce_t));
        out_ptp_announce_pkt = drv->udp4.create_out_pkt(current_eth_if,
                                                        ptp_primary,
                                                        0x4001,
                                                        0x00,
                                                        (uint8_t*)announce_pkt,
                                                        sizeof(ptp_announce_t));
        if(out_ptp_announce_pkt){
            mj_set_ttl(out_ptp_announce_pkt,5);
            ptp_CreateAnnounce();
        }

        sync_pkt = calloc(1,sizeof(ptp_sync_t));
        out_ptp_sync_pkt = drv->udp4.create_out_pkt(current_eth_if,
                                                    ptp_primary,
                                                    0x3f01,
                                                    0x00,
                                                    (uint8_t*)sync_pkt,
                                                    sizeof(ptp_sync_t));
        if(out_ptp_sync_pkt){
            mj_set_ttl(out_ptp_sync_pkt,5);
            ptp_CreateSync();
        }

        follow_up_pkt = calloc(1,sizeof(ptp_follow_up_t));
        out_ptp_follow_up_pkt = drv->udp4.create_out_pkt(current_eth_if,
                                                         ptp_primary,
                                                         0x4001,
                                                         0x00,
                                                         (uint8_t*)follow_up_pkt,
                                                         sizeof(ptp_follow_up_t));
        if(out_ptp_follow_up_pkt){
            mj_set_ttl(out_ptp_follow_up_pkt,5);
            ptp_CreateFollowUp();
        }


        /** DELAY RESPOND MESSAGE */
        delay_resp_pkt = calloc(1,sizeof(ptp_delay_respond_t));
        out_ptp_delay_resp_pkt = drv->udp4.create_out_pkt(current_eth_if,
                                                          ptp_primary,
                                                          0x4001,
                                                          0x00,
                                                          (uint8_t *)delay_resp_pkt,
                                                          sizeof(ptp_delay_respond_t));
        if (out_ptp_delay_resp_pkt)
        {
            mj_set_ttl(out_ptp_delay_resp_pkt, 5);
            ptp_CreateDelayResp();
        }

        mjdrv_set_ptp_tick(ptp_tick);
        portDS.portState = PTP_PORT_STATE_MASTER;
        drv_p->udp4.register_callback(ptp_primary,0x3f01,ptp_EventCallback);
        drv_p->udp4.register_callback(ptp_primary,0x4001,ptp_GeneralCallback);
    }
    else{
        char * msg = (char *)"PTP: Error: No inizialized interface";
        write(2,msg,strlen(msg));
    }
    return;
}

// Deinitialize PTP
void ptp_deinit(){
    // Set ptp tick to nullptr to prevent any new PTP messages
    mjdrv_set_ptp_tick(NULL);

    // Free allocated memory that was allocated for PTP messages

    if(out_ptp_announce_pkt){
        free(out_ptp_announce_pkt);
    }
    if(announce_pkt){
        free(announce_pkt);
    }

    if(out_ptp_sync_pkt){
        free(out_ptp_sync_pkt);
    }

    if(sync_pkt){
        free(sync_pkt);
    }

    if(out_ptp_follow_up_pkt){
        free(out_ptp_follow_up_pkt);
    }

    if(follow_up_pkt){
        free(follow_up_pkt);
    }

    return;
}
