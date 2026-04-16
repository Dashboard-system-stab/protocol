/*
 *
 * Author: Korotkov M.I.
 *
 * Date: 10.12.2024
 *
 */

#ifndef PTP_H
#define PTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mjdriver_interface.h"
#include "stdbool.h"

typedef union uint48{
    uint64_t u48:48;
    uint8_t u8[6];
}__attribute__((packed))uint48_t;



typedef struct ptp_timestamp{
    uint48_t seconds;
    uint32_t nanoseconds;
}__attribute__((packed))ptp_timestamp_t;



typedef union ptp_clock_identity{
    /** For EUI-48 (Eth MAC) devices */
    struct{
        uint8_t vendor[3];
        uint8_t addressTechnology[2];
        uint8_t id[3];
    }__attribute__((packed));
    uint8_t u8[8];
}ptp_clock_identity_t;



typedef struct ptp_port_identity{
    ptp_clock_identity_t clockIdentity;
    uint16_t portNumber;
}__attribute__((packed))ptp_port_identity_t;



typedef struct ptp_port_address{
    uint16_t networkProtocol;
    uint16_t addressLength;
    uint8_t *address;
}__attribute__((packed))ptp_port_address_t;



typedef enum ptp_clock_class{
    //Cannot be slaves
    PTP_CLOCK_CLASS_SYNC_TO_PRIMARY_TIME_SOURCE = 6,
    PTP_CLOCK_CLASS_UNSYNC_TO_PRIMARY_TIME_SOURCE_HOLDOVER = 7,
    PTP_CLOCK_CLASS_SYNC_TO_APPLICATION_SPECIFIC_TIME_SOURCE = 13,
    PTP_CLOCK_CLASS_UNSYNC_TO_APPLICATION_SPECIFIC_TIME_SOURCE_HOLDOVER = 14,
    PTP_CLOCK_CLASS_UNSYNC_TO_PRIMARY_TIME_SOURCE_NO_HOLDOVER_SPEC = 52,
    PTP_CLOCK_CLASS_UNSYNC_TO_APPLICATION_SPECIFIC_TIME_SOURCE_NO_HOLDOVER_SPEC = 58,
    //Could be slaves
    PTP_CLOCK_CLASS_UNSYNC_TO_PRIMARY_TIME_SOURCE_NOT_HOLDOVER_MODE = 187,
    PTP_CLOCK_CLASS_UNSYNC_TO_APPLICATION_SPECIFIC_TIME_SOURCE_NOT_HOLDOVER_MODE = 14,
    PTP_CLOCK_CLASS_DEFAULT = 248,
}ptp_clock_class_t;



typedef enum ptp_clock_accuracy{
    PTP_CLOCK_ACCURACY_25_NS = 0x20,
    PTP_CLOCK_ACCURACY_100_NS,
    PTP_CLOCK_ACCURACY_250_NS,
    PTP_CLOCK_ACCURACY_1_US,
    PTP_CLOCK_ACCURACY_2_5_US,
    PTP_CLOCK_ACCURACY_10_US,
    PTP_CLOCK_ACCURACY_25_US,
    PTP_CLOCK_ACCURACY_100_US,
    PTP_CLOCK_ACCURACY_250_US,
    PTP_CLOCK_ACCURACY_1_MS,
    PTP_CLOCK_ACCURACY_2_5_MS,
    PTP_CLOCK_ACCURACY_10_MS,
    PTP_CLOCK_ACCURACY_25_MS,
    PTP_CLOCK_ACCURACY_100_MS,
    PTP_CLOCK_ACCURACY_250_MS,
    PTP_CLOCK_ACCURACY_1_S,
    PTP_CLOCK_ACCURACY_10_S,
    PTP_CLOCK_ACCURACY_MORETHAN_10_S,
    PTP_CLOCK_ACCURACY_UNKNOWN = 0xFE
}ptp_clock_accuracy_t;



typedef struct ptp_clock_quality{
    uint8_t clockClass;
    ptp_clock_accuracy_t clockAccuracy:8;
    uint16_t offsetScaledLogVariance;
}__attribute__((packed))ptp_clock_quality_t;



typedef enum ptp_tlvType{
    PTP_TLVTYPE_RESERVED = 0x0,
    PTP_TLVTYPE_MANAGEMENT,
    PTP_TLVTYPE_ERROR_STATUS,
    PTP_TLVTYPE_ORGANIZATION_EXTENSION,
    PTP_TLVTYPE_REQUEST_UNICAST_TRANSMISSION,
    PTP_TLVTYPE_GRANT_UNICAST_TRANSMISSION,
    PTP_TLVTYPE_CANCEL_UNICAST_TRANSMISSION,
    PTP_TLVTYPE_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION,
    PTP_TLVTYPE_PATH_TRACE,
    PTP_TLVTYPE_ALTERNATE_TIME_OFFSET_INDICATIOR,
    PTP_TLVTYPE_AUTHENTICATION = 0x2000,
    PTP_TLVTYPE_AUTHENTICATION_CHALLENGE,
    PTP_TLVTYPE_SECURITY_ASSOCIATION_UPDATE,
    PTP_TLVTYPE_CUM_FREQ_SCALE_FACTOR_OFFEST
}ptp_tlvType_t;



typedef struct ptp_tlv{
    ptp_tlvType_t   tlvType;
    uint16_t length;
    uint8_t *value;
}__attribute__((packed))ptp_tlv_t;



typedef struct ptp_text{
    uint8_t length;
    uint8_t *text;
}__attribute__((packed))ptp_text_t;



typedef enum ptp_severity_code{
    PTP_SEVERITY_EMEGENCY,
    PTP_SEVERITY_ALERT,
    PTP_SEVERITY_CRITICAL,
    PTP_SEVERITY_ERROR,
    PTP_SEVERITY_WARNING,
    PTP_SEVERITY_NOTICE,
    PTP_SEVERITY_INFOMATIONAL,
    PTP_SEVERITY_DEBUG
}ptp_severity_code_t;



typedef struct ptp_fault_record{
    uint16_t length;
    ptp_timestamp_t faultTime;
    ptp_severity_code_t severityCode;
    ptp_text_t faultName;
    ptp_text_t faultValue;
    ptp_text_t faultDescription;
}__attribute__((packed))ptp_fault_record_t;



typedef enum ptp_messages{
    PTP_SYNC = 0x00,
    PTP_DELAY_REQ,
    PTP_PDELAY_REQ,
    PTP_PDELAY_RESP,
    PTP_FOLLOW_UP = 0x08,
    PTP_DELAY_RESP,
    PTP_PDELAY_RESP_FOLLOW_UP,
    PTP_ANNOUNCE,
    PTP_SIGNALING,
    PTP_MANAGEMENT
}ptp_messages_t;



typedef enum ptp_message_control_field{
    PTP_MESSAGE_CONTROL_SYNC = 0x00,
    PTP_MESSAGE_CONTROL_DELAY_REQ,
    PTP_MESSAGE_CONTROL_FOLLOW_UP,
    PTP_MESSAGE_CONTROL_DELAY_RESP,
    PTP_MESSAGE_CONTROL_MANAGEMENT,
    PTP_MESSAGE_CONTROL_OTHER
}ptp_message_control_field_t;



typedef enum ptp_clock_source{
    PTP_CLOCK_SOURCE_ATOMIC = 0x10,
    PTP_CLOCK_SOURCE_GPS = 0x20,
    PTP_CLOCK_SOURCE_TERRESTRIAL_RADIO = 0x30,
    PTP_CLOCK_SOURCE_PTP = 0x40,
    PTP_CLOCK_SOURCE_NTP = 0x50,
    PTP_CLOCK_SOURCE_HAND_SET = 0x60,
    PTP_CLOCK_SOURCE_OTHER = 0x90,
    PTP_CLOCK_SOURCE_INTERNAL_OSCILLATOR = 0xA0
}ptp_clock_source_t;



typedef enum ptp_port_state{
    PTP_PORT_STATE_INITIALIZING = 0x01,
    PTP_PORT_STATE_FAULTY,
    PTP_PORT_STATE_DISABLED,
    PTP_PORT_STATE_LISTENING,
    PTP_PORT_STATE_PRE_MASTER,
    PTP_PORT_STATE_MASTER,
    PTP_PORT_STATE_PASSIVE,
    PTP_PORT_STATE_UNCALIBRATED,
    PTP_PORT_STATE_SLAVE,
    PTP_PORT_STATE_RESERVED
}ptp_port_state_t;



typedef enum ptp_delay_mechanism{
    PTP_DELAY_MECHANISM_E2E = 0x01,
    PTP_DELAY_MECHANISM_P2P = 0x02,
    PTP_DELAY_MECHANISM_DISABLED = 0xFE
}ptp_delay_mechanism_t;



/** IEEE 1588-2008 8.2.1 clock Default dataset */
typedef struct ptp_default_DS{
    bool twoStepFlag;
    ptp_clock_identity_t clockIdentity;
    uint16_t numberPorts;
    ptp_clock_quality_t clockQuality;

    // Two priorities for best-master algorithm
    uint8_t priority_1; // IEEE 1588-2008 7.6.2.2
    uint8_t priority_2; // IEEE 1588-2008 7.6.2.3

    uint8_t domainNumber;
    bool slaveOnly;
}ptp_default_DS_t;



/** IEEE 1588-2008 8.2.2 clock General dataset */
typedef struct ptp_current_DS{
    uint32_t stepsRemoved;
    uint32_t offsetFromMaster;
    int64_t meanPathDelay;
}ptp_current_DS_t;



/** IEEE 1588-2008 8.2.3 clock Parent dataset */
typedef struct ptp_parent_DS{
    ptp_port_identity_t parentPortIdentity;
    bool parentStats;
    uint16_t observedParentOffsetScaledLogVariance;
    uint64_t observedParentClockPhaseChangeRate;
    ptp_clock_identity_t grandmasterIdentity;
    ptp_clock_quality_t grandmasterClockQuality;
    uint8_t grandmasterPriority_1;
    uint8_t grandmasterPriority_2;
}ptp_parent_DS_t;



/** IEEE 1588-2008 8.2.3 clock Parent dataset */
typedef struct ptp_time_properties_DS{
    uint8_t currentUTCOffset;
    bool currentUtcOffsetValid;
    bool leap59;
    bool leap61;
    bool timeTraceability;
    bool frequencyTraceability;
    bool ptpTimescale;
    ptp_clock_source_t timeSource;
}ptp_time_properties_DS_t;



/** IEEE 1588-2008 8.2.4 clock Port dataset */
typedef struct ptp_port_DS{
    ptp_port_identity_t portIdentity;
    ptp_port_state_t portState;
    int8_t logMinDelayReqInterval;
    int64_t peerMeanPathDelay;
    int8_t logAnnouncementInterval;
    int64_t announceReceiptTimeout;
    int8_t logSyncInterval;
    ptp_delay_mechanism_t delayMechanism;
    int8_t logMinPdelayReqInterval;
    uint8_t versionNumber;
}ptp_port_DS_t;



typedef struct ptp_common_header{
    struct{
        ptp_messages_t messageType:4;
        uint8_t transport_specific:4;
    }__attribute__((packed));
    uint8_t	versionPTP:4,reserved_1:4;
    uint16_t messageLength;
    uint8_t domainNumber;
    uint8_t reserved_2;
    union{
        struct{
            uint8_t ptp_alternate_master:1,
                ptp_two_step:1,
                ptp_unicast:1,
                flags_padding_1:1,
                ptp_profile_specific_1:1,
                ptp_profile_specific_2:1,
                ptp_security:1,
                flags_padding_2:1;

            uint8_t   ptp_LI_61:1,
                ptp_LI_59:1,
                ptp_utc_reasonable:1,
                ptp_timescale:1,
                ptp_time_traceable:1,
                ptp_frequency_traceability:1,
                ptp_syncronization_uncertain:1,
                flags_padding_3:1;
        }__attribute__((packed));
        uint16_t u16;
        uint8_t u8[2];
    }flags;

    int64_t correction;
    // Here stored microjet device id
    uint32_t reserved_3;
    struct{
        ptp_clock_identity_t clockIdentity;
        uint16_t portNumber;
    }__attribute__((packed))sourcePortIdentity;
    uint16_t sequenceId;
    ptp_message_control_field_t control:8;
    int8_t logMessageInterval;
}__attribute__((packed))ptp_header_t;



typedef struct ptp_announce{
    ptp_header_t header;
    ptp_timestamp_t originTimestamp;
    int16_t currentUtcOffset;
    uint8_t reserved_1;
    uint8_t grandmasterPriority1;
    ptp_clock_quality_t grandmasterClockQuality;
    uint8_t grandmasterPriority2;
    ptp_clock_identity_t grandmasterIdentity;
    uint16_t stepsRemoved;
    ptp_clock_source_t timeSource:8;
}__attribute__((packed))ptp_announce_t;



typedef struct ptp_sync{
    ptp_header_t header;
    ptp_timestamp_t originTimestamp;
}__attribute__((packed))ptp_sync_t;



typedef struct ptp_follow_up{
    ptp_header_t header;
    ptp_timestamp_t preciseOriginTimestamp;
}__attribute__((packed))ptp_follow_up_t;



typedef struct ptp_delay_request{
    ptp_header_t header;
    ptp_timestamp_t originTimestamp;
    uint8_t reserved[10];
}__attribute__((packed))ptp_delay_request_t;



typedef struct ptp_delay_respond{
    ptp_header_t header;
    ptp_timestamp_t recieveTimestamp;
    ptp_port_identity_t requestingPortIdentity;
}__attribute__((packed))ptp_delay_respond_t;



typedef struct ptp_pdelay_request{
    ptp_header_t header;
    ptp_timestamp_t originTimestamp;
    uint8_t reserved[10];
}__attribute__((packed))ptp_pdelay_request_t;



typedef struct ptp_pdelay_respond{
    ptp_header_t header;
    ptp_timestamp_t requestReceiptTimestamp;
    ptp_port_identity_t requestingPortIdentity;
}__attribute__((packed))ptp_pdelay_respond_t;



typedef struct ptp_pdelay_respond_follow_up{
    ptp_header_t header;
    ptp_timestamp_t responseOriginTimestamp;
    ptp_port_identity_t requestingPortIdentity;
}__attribute__((packed))ptp_pdelay_respond_follow_up_t;



typedef struct ptp_signaling{
    ptp_header_t header;
    ptp_port_identity_t targetPortIdentity;
    uint8_t tlvCount;
    ptp_tlv_t *tlvArray;
}__attribute__((packed))ptp_signaling_t;



typedef enum ptp_management_actions{
    PTP_MANAGEMENT_ACTION_GET = 0x0,
    PTP_MANAGEMENT_ACTION_SET,
    PTP_MANAGEMENT_ACTION_RESPONSE,
    PTP_MANAGEMENT_ACTION_COMMAND,
    PTP_MANAGEMENT_ACTION_ACKNOWLEDGE
}ptp_management_actions_t;



typedef union ptp_management_action_field{
    struct{
        ptp_management_actions_t action:4;
        uint8_t ptp_reserved:4;
    }__attribute__((packed));
    uint8_t u8;
}__attribute__((packed))ptp_management_action_field_t;



typedef enum ptp_management_id{
    PTP_MANAGEMENT_ID_NULL_MANAGEMENT = 0x0,
    PTP_MANAGEMENT_ID_CLOCK_DESCRIPTION,
    PTP_MANAGEMENT_ID_USER_DESCRIPTION,
    PTP_MANAGEMENT_ID_SAVE_IN_NON_VOLATILE_STORAGE,
    PTP_MANAGEMENT_ID_RESET_NON_VOLATIVE_STORAGE,
    PTP_MANAGEMENT_ID_INITIALIZE,
    PTP_MANAGEMENT_ID_FAULT_LOG,
    PTP_MANAGEMENT_ID_FAULT_LOG_RESET,
    PTP_MANAGEMENT_ID_DEFAULT_DATA_SET = 0x2000,
    PTP_MANAGEMENT_ID_CURRENT_DATA_SET,
    PTP_MANAGEMENT_ID_PARENT_DATA_SET,
    PTP_MANAGEMENT_ID_TIME_PROPERTIES_DATA_SET,
    PTP_MANAGEMENT_ID_PORT_DATA_SET,
    PTP_MANAGEMENT_ID_PRIORITY1,
    PTP_MANAGEMENT_ID_PRIORITY2,
    PTP_MANAGEMENT_ID_DOMAIN,
    PTP_MANAGEMENT_ID_SLAVE_ONLY,
    PTP_MANAGEMENT_ID_LOG_ANNOUNCE_INTERVAL,
    PTP_MANAGEMENT_ID_ANNOUNCE_RECEIPT_TIMEOUT,
    PTP_MANAGEMENT_ID_LOG_SYNC_INTERVAL,
    PTP_MANAGEMENT_ID_VERSION_NUMBER,
    PTP_MANAGEMENT_ID_ENABLE_PORT,
    PTP_MANAGEMENT_ID_DISABLE_PORT,
    PTP_MANAGEMENT_ID_TIME,
    PTP_MANAGEMENT_ID_CLOCK_ACCURACY,
    PTP_MANAGEMENT_ID_UTC_PROPERTIES,
    PTP_MANAGEMENT_ID_TRACEABILITY_PROPERTIES,
    PTP_MANAGEMENT_ID_TIMESCALE_PROPERTIES,
    PTP_MANAGEMENT_ID_UNICAST_NEGOTIATION_ENABLE,
    PTP_MANAGEMENT_ID_PATH_TRACE_LIST,
    PTP_MANAGEMENT_ID_PATH_TRACE_ENABLE,
    PTP_MANAGEMENT_ID_GRANDMASTER_CLUSTER_TREE,
    PTP_MANAGEMENT_ID_UNICAST_MASTER_TABLE,
    PTP_MANAGEMENT_ID_UNICAST_MAX_TABLE_SIZE,
    PTP_MANAGEMENT_ID_ACCEPTABLE_MASTER_TABLE,
    PTP_MANAGEMENT_ID_ACCEPTABLE_MASTER_TABLE_ENABLE,
    PTP_MANAGEMENT_ID_ACCEPTABLE_MASTER_MAX_TABLE_SIZE,
    PTP_MANAGEMENT_ID_ALTERNATE_MASTER,
    PTP_MANAGEMENT_ID_ALTERNATE_TIME_OFFSET_ENABLE,
    PTP_MANAGEMENT_ID_ALTERNATE_TIME_OFFSET_NAME,
    PTP_MANAGEMENT_ID_ALTERNATE_TIME_OFFSET_MAX_KEY,
    PTP_MANAGEMENT_ID_ALTERNATE_TIME_OFFSET_PROPERTIES,
    PTP_MANAGEMENT_ID_TRANSPARENT_CLOCK_DEFAULT_DATA_SET = 0x4000,
    PTP_MANAGEMENT_ID_TRANSPARENT_CLOCK_PORT_DATA_SET,
    PTP_MANAGEMENT_ID_PRIMARY_DOMAIN,
    PTP_MANAGEMENT_ID_DELAY_MECHANISM = 0x6000,
    PTP_MANAGEMENT_ID_LOG_MIN_PDELAY_REQ_INTERVAL
}ptp_management_id_t;



typedef struct ptp_managementTLV{
    ptp_tlvType_t tlvType;
    uint16_t length;
    ptp_management_id_t managementId;
    uint8_t data_length;
    uint8_t *data_p;
}__attribute__((packed))ptp_managementTLV_t;



typedef struct ptp_management{
    ptp_header_t header;
    ptp_port_identity_t targetPortIdentity;
    uint8_t startingBoundatyHops;
    uint8_t boundaryHops;
    ptp_management_action_field_t action;
    uint8_t reserved;
    uint8_t managementTLVcount;
    ptp_managementTLV_t *managementTLVarray;
}__attribute__((packed))ptp_management_t;

typedef struct{
    uint16_t id;
    uint32_t ts_s;
    uint32_t ts_ns;
}ptp_dev_info;

void ptp_init(mj_drv_interface_t *drv);

ptp_dev_info ptp_GetDeviceTimestamp(uint16_t dev_id);

#ifdef __cplusplus
}
#endif

#endif // PTP_H
