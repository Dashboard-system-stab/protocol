#ifndef __MICROJET_DEF_H_
#define __MICROJET_DEF_H_

#include <stdint.h>

typedef enum mj_status{
    MJ_OK = 0,
    MJ_FAIL = -1,
    MJ_ETH_FAIL = -2,

    MJ_UDP4_CB_FAIL = -3,
    MJ_UDP4_ALOC_FAIL = -4,
    MJ_UDP4_PKT_FAIL = -5,

    MJ_INTEGRITY_FAIL = -6,

    MJ_ETH_SOCKET_FAIL = -7,
    MJ_ETH_INTRERFACE_FAIL = -8,
    MJ_ETH_NAME_FAIL = -9
} mj_status_t;

typedef enum mj_direction_en{
    MJ_OUT,
    MJ_IN
}mj_direction_t;

typedef enum mj_msg_proc_res_en{
    MJ_ACCEPT,
    MJ_REJECT_SRC,
    MJ_REJECT_DST,
    MJ_REJECT_ID,
    MJ_REJECT_SIZE,
    MJ_REJECT_OVF,
    MJ_PROC_FAIL
}mj_msg_proc_res_t;

typedef enum mj_msg_state{
    MJ_MSG_ACTUAL,
    MJ_MSG_OBSOLETE,
    MJ_MSG_WRONGTYPE,
    MJ_MSG_LOCK,
    MJ_MSG_UNLOCK,
    MJ_MSG_UNDEFINED
} mj_msg_state_t;

typedef enum check_result{
    MJ_CHECK_OK,
    MJ_CHECK_FAIL
} mj_check_result_t;

typedef enum mj_prm_status{
    MJ_PRM_OK,
    MJ_PRM_UNKNOW
} mj_prm_status_t;

typedef struct{
    uint16_t src;
    uint16_t dst;
    uint16_t id;
    uint16_t cnt;
    uint32_t ts_s;
    union{
        struct{
            uint32_t ts_ns:30;
            uint32_t ts_status:2;
        };
        uint32_t ts_low;
    };
} mj_msg_header_t;

#endif