#include "mjutils.h"

const char* parameter_request_type_str(int32_t val) {
    switch(val) {
        case PARAMETER_REQUEST_TYPE_READ: return "READ";
        case PARAMETER_REQUEST_TYPE_WRITE: return "WRITE";
        default: return "???";
    }
}

const char* parameter_status_str(int32_t val) {
    switch(val) {
        case PARAMETER_STATUS_OK: return "OK";
        case PARAMETER_STATUS_UNKNOWPRM: return "UNKNOWPRM";
        case PARAMETER_STATUS_WRITE_FAILED: return "WRITE_FAILED";
        case PARAMETER_STATUS_READ_ONLY: return "READ_ONLY";
        case PARAMETER_STATUS_NOT_SUPPORTED: return "NOT_SUPPORTED";
        default: return "???";
    }
}

const char* command_type_str(int32_t val) {
    switch(val) {
        case COMMAND_TYPE_SWRESET: return "SWRESET";
        case COMMAND_TYPE_SAVEPRM: return "SAVEPRM";
        case COMMAND_TYPE_SET_HOME_POSITION: return "SET_HOME_POSITION";
        case COMMAND_TYPE_SET_UP_LIMIT: return "SET_UP_LIMIT";
        case COMMAND_TYPE_SET_DOWN_LIMIT: return "SET_DOWN_LIMIT";
        case COMMAND_TYPE_SET_EL_ZERO: return "SET_EL_ZERO";
        case COMMAND_TYPE_OPERATION_TIME_RESET: return "OPERATION_TIME_RESET";
        case COMMAND_TYPE_INTEGRATOR_RESET: return "INTEGRATOR_RESET";
        case COMMAND_TYPE_FIRMWARE_UPGRADE: return "FIRMWARE_UPGRADE";
        case COMMAND_TYPE_FIRMWARE_VERIFY: return "FIRMWARE_VERIFY";
        case COMMAND_TYPE_CURRENT_SENSOR_CALIB: return "CURRENT_SENSOR_CALIB";
        default: return "???";
    }
}

const char* command_state_str(int32_t val) {
    switch(val) {
        case COMMAND_STATE_ACCEPT: return "ACCEPT";
        case COMMAND_STATE_INPROGRESS: return "INPROGRESS";
        case COMMAND_STATE_DONE: return "DONE";
        case COMMAND_STATE_UNKNOW: return "UNKNOW";
        case COMMAND_STATE_FORBITTEN: return "FORBITTEN";
        case COMMAND_STATE_NOT_IMPLEMENTED: return "NOT_IMPLEMENTED";
        case COMMAND_STATE_ERROR: return "ERROR";
        default: return "???";
    }
}

const char* msg_state_str(int32_t val) {
    switch(val) {
        case MSG_STATE_CONFIRMED: return "CONFIRMED";
        case MSG_STATE_SEND: return "SEND";
        case MSG_STATE_WRONGCODE: return "WRONGCODE";
        case MSG_STATE_ISPERIODIC: return "ISPERIODIC";
        case MSG_STATE_IMPOSSIBLE: return "IMPOSSIBLE";
        default: return "???";
    }
}

const char* drv_ctrl_mode_str(int32_t val) {
    switch(val) {
        case DRV_CTRL_MODE_UNKNOWN: return "UNKNOWN";
        case DRV_CTRL_MODE_OFF: return "OFF";
        case DRV_CTRL_MODE_FREEMOVE: return "FREEMOVE";
        case DRV_CTRL_MODE_HOLD: return "HOLD";
        case DRV_CTRL_MODE_ANGLE: return "ANGLE";
        case DRV_CTRL_MODE_SPEED: return "SPEED";
        case DRV_CTRL_MODE_RSPEED: return "RSPEED";
        case DRV_CTRL_MODE_VOLTAGE: return "VOLTAGE";
        case DRV_CTRL_MODE_SYNCHRO: return "SYNCHRO";
        case DRV_CTRL_MODE_CURRENT: return "CURRENT";
        case DRV_CTRL_MODE_VOLTAGE_A: return "VOLTAGE_A";
        case DRV_CTRL_MODE_VOLTAGE_B: return "VOLTAGE_B";
        case DRV_CTRL_MODE_VOLTAGE_C: return "VOLTAGE_C";
        default: return "???";
    }
}

const char* drv_ctrl_error_str(int32_t val) {
    switch(val) {
        case DRV_CTRL_ERROR_UNKNOWN: return "UNKNOWN";
        case DRV_CTRL_ERROR_NONE: return "NONE";
        case DRV_CTRL_ERROR_BLOCK: return "BLOCK";
        case DRV_CTRL_ERROR_OFF: return "OFF";
        case DRV_CTRL_ERROR_POWER: return "POWER";
        case DRV_CTRL_ERROR_CTRL: return "CTRL";
        case DRV_CTRL_ERROR_OLP: return "OLP";
        case DRV_CTRL_ERROR_OCP: return "OCP";
        case DRV_CTRL_ERROR_UVP: return "UVP";
        case DRV_CTRL_ERROR_SCP: return "SCP";
        case DRV_CTRL_ERROR_MODE: return "MODE";
        case DRV_CTRL_ERROR_INV: return "INV";
        case DRV_CTRL_ERROR_LANG: return "LANG";
        case DRV_CTRL_ERROR_RANG: return "RANG";
        case DRV_CTRL_ERROR_OHP: return "OHP";
        case DRV_CTRL_ERROR_BRAKE: return "BRAKE";
        case DRV_CTRL_ERROR_ROTOR_SENS: return "ROTOR_SENS";
        case DRV_CTRL_ERROR_MCON: return "MCON";
        case DRV_CTRL_ERROR_SERVICE: return "SERVICE";
        default: return "???";
    }
}

const char* relay_signal_state_str(int32_t val) {
    switch(val) {
        case RELAY_SIGNAL_STATE_UNKNOWN: return "UNKNOWN";
        case RELAY_SIGNAL_STATE_HIGH: return "HIGH";
        case RELAY_SIGNAL_STATE_LOW: return "LOW";
        case RELAY_SIGNAL_STATE_GAP: return "GAP";
        case RELAY_SIGNAL_STATE_OCP: return "OCP";
        case RELAY_SIGNAL_STATE_FAIL: return "FAIL";
        default: return "???";
    }
}

const char* rotor_ang_sens_status_str(int32_t val) {
    switch(val) {
        case ROTOR_ANG_SENS_STATUS_UNKNOW: return "UNKNOW";
        case ROTOR_ANG_SENS_STATUS_PREPARE: return "PREPARE";
        case ROTOR_ANG_SENS_STATUS_UNCONNECTED: return "UNCONNECTED";
        case ROTOR_ANG_SENS_STATUS_NORMAL: return "NORMAL";
        case ROTOR_ANG_SENS_STATUS_WARNING: return "WARNING";
        case ROTOR_ANG_SENS_STATUS_FAULT: return "FAULT";
        default: return "???";
    }
}

const char* load_ang_sens_status_str(int32_t val) {
    switch(val) {
        case LOAD_ANG_SENS_STATUS_UNKNOW: return "UNKNOW";
        case LOAD_ANG_SENS_STATUS_PREPARE: return "PREPARE";
        case LOAD_ANG_SENS_STATUS_UNCONNECTED: return "UNCONNECTED";
        case LOAD_ANG_SENS_STATUS_NORMAL: return "NORMAL";
        case LOAD_ANG_SENS_STATUS_WARNING: return "WARNING";
        case LOAD_ANG_SENS_STATUS_FAULT: return "FAULT";
        default: return "???";
    }
}

const char* inverter_mode_str(int32_t val) {
    switch(val) {
        case INVERTER_MODE_UNKNOW: return "UNKNOW";
        case INVERTER_MODE_OFF: return "OFF";
        case INVERTER_MODE_OK: return "OK";
        case INVERTER_MODE_ENABLING: return "ENABLING";
        case INVERTER_MODE_DISABLING: return "DISABLING";
        case INVERTER_MODE_FAULT: return "FAULT";
        case INVERTER_MODE_CALIBRATION: return "CALIBRATION";
        case INVERTER_MODE_CONNECTION_CHECK: return "CONNECTION_CHECK";
        default: return "???";
    }
}

const char* dcu_status_str(int32_t val) {
    switch(val) {
        case DCU_STATUS_UNKNOWN: return "UNKNOWN";
        case DCU_STATUS_OFF: return "OFF";
        case DCU_STATUS_PREPARE: return "PREPARE";
        case DCU_STATUS_CUR_CALIB: return "CUR_CALIB";
        case DCU_STATUS_DISARM: return "DISARM";
        case DCU_STATUS_ARM: return "ARM";
        case DCU_STATUS_FAULT: return "FAULT";
        default: return "???";
    }
}

const char* rotor_brake_state_str(int32_t val) {
    switch(val) {
        case ROTOR_BRAKE_STATE_UNKNOWN: return "UNKNOWN";
        case ROTOR_BRAKE_STATE_CLOSE: return "CLOSE";
        case ROTOR_BRAKE_STATE_RELEASE: return "RELEASE";
        case ROTOR_BRAKE_STATE_FAIL: return "FAIL";
        default: return "???";
    }
}

const char* move_limit_state_str(int32_t val) {
    switch(val) {
        case MOVE_LIMIT_STATE_UNKNOW: return "UNKNOW";
        case MOVE_LIMIT_STATE_NONE: return "NONE";
        case MOVE_LIMIT_STATE_LIMIT_UP: return "LIMIT_UP";
        case MOVE_LIMIT_STATE_LIMIT_DOWN: return "LIMIT_DOWN";
        default: return "???";
    }
}

const char* transit_proc_status_str(int32_t val) {
    switch(val) {
        case TRANSIT_PROC_STATUS_UNKNOW: return "UNKNOW";
        case TRANSIT_PROC_STATUS_NONE: return "NONE";
        case TRANSIT_PROC_STATUS_INPROGRESS: return "INPROGRESS";
        case TRANSIT_PROC_STATUS_DONE: return "DONE";
        default: return "???";
    }
}

const char* sync_state_str(int32_t val) {
    switch(val) {
        case SYNC_STATE_FAILED: return "FAILED";
        case SYNC_STATE_FREERUN: return "FREERUN";
        case SYNC_STATE_UNSYNC: return "UNSYNC";
        case SYNC_STATE_SYNC: return "SYNC";
        default: return "???";
    }
}

const char* mj_get_prm_name(int32_t val)
{
    switch(val) {
        case PRM_BOOL_SERVICE_MODE: return "service_mode";
        case PRM_BOOL_DBG_MODE: return "dbg_mode";
        case PRM_BOOL_PTP_STAT: return "ptp_stat";
        case PRM_FLOAT_VDC: return "Vdc";
        case PRM_FLOAT_VDC_SCALE: return "vdc_scale";
        case PRM_FLOAT_VDC_MIN: return "vdc_min";
        case PRM_FLOAT_OCP_LVL: return "ocp_lvl";
        case PRM_FLOAT_CUR_LIM: return "cur_lim";
        case PRM_FLOAT_DRV_LIMIT_UP: return "drv_limit_up";
        case PRM_FLOAT_DRV_LIMIT_DOWN: return "drv_limit_down";
        case PRM_BOOL_DRV_ANG_REVERSE: return "drv_ang_reverse";
        case PRM_BOOL_DRV_CURRENT_REVERSE: return "drv_current_reverse";
        case PRM_BOOL_DRV_VOLTAGE_REVERSE: return "drv_voltage_reverse";
        case PRM_FLOAT_DRV_ZERO: return "drv_zero";
        case PRM_FLOAT_OHP_LVL: return "ohp_lvl";
        case PRM_FLOAT_OHP_HYST: return "ohp_hyst";
        case PRM_FLOAT_EL_ZERO: return "el_zero";
        case PRM_INT_POLE_PAIRS: return "pole_pairs";
        case PRM_FLOAT_PH_RESISTANCE: return "ph_resistance";
        case PRM_FLOAT_PH_INDUCTANCE: return "ph_inductance";
        case PRM_FLOAT_BRAKE_UNLOCK_VOLTAGE: return "brake_unlock_voltage";
        case PRM_INT_BRAKE_UNLOCK_TIME: return "brake_unlock_time";
        case PRM_FLOAT_BRAKE_HOLD_VOLTAGE: return "brake_hold_voltage";
        case PRM_INT_BRAKE_LOCK_TIME: return "brake_lock_time";
        case PRM_FLOAT_CURR_KP: return "curr_kp";
        case PRM_FLOAT_CURR_KI: return "curr_ki";
        case PRM_FLOAT_CURR_KB: return "curr_kb";
        case PRM_FLOAT_CURR_KT: return "curr_kt";
        case PRM_FLOAT_CURR_KF: return "curr_kf";
        case PRM_FLOAT_CURR_FC: return "curr_fc";
        case PRM_FLOAT_CURR_ERR_LIM: return "curr_err_lim";
        case PRM_FLOAT_CURR_OUT_LIM: return "curr_out_lim";
        case PRM_FLOAT_CURR_OUT_RATE_LIM: return "curr_out_rate_lim";
        case PRM_FLOAT_CURR_ERR_RATE_LIM: return "curr_err_rate_lim";
        case PRM_FLOAT_LOAD_SPEED_FLT_FC: return "load_speed_flt_fc";
        case PRM_FLOAT_ROTOR_SPEED_FLT_FC: return "rotor_speed_flt_fc";
        case PRM_FLOAT_LOAD_SPEED_KP: return "load_speed_kp";
        case PRM_FLOAT_LOAD_SPEED_KI: return "load_speed_ki";
        case PRM_FLOAT_LOAD_SPEED_KB: return "load_speed_kb";
        case PRM_FLOAT_LOAD_SPEED_KT: return "load_speed_kt";
        case PRM_FLOAT_LOAD_SPEED_KF: return "load_speed_kf";
        case PRM_FLOAT_LOAD_SPEED_ERR_LIM: return "load_speed_err_lim";
        case PRM_FLOAT_LOAD_SPEED_OUT_LIM: return "load_speed_out_lim";
        case PRM_FLOAT_LOAD_SPEED_INT_LIM: return "load_speed_int_lim";
        case PRM_FLOAT_LOAD_SPEED_OUT_RATE_LIM: return "load_speed_out_rate_lim";
        case PRM_FLOAT_LOAD_SPEED_ERR_RATE_LIM: return "load_speed_err_rate_lim";
        case PRM_BOOL_LOAD_ANG_REV: return "load_ang_rev";
        case PRM_FLOAT_LOAD_ANG_KP: return "load_ang_kp";
        case PRM_FLOAT_LOAD_ANG_KI: return "load_ang_ki";
        case PRM_FLOAT_LOAD_ANG_KB: return "load_ang_kb";
        case PRM_FLOAT_LOAD_ANG_KT: return "load_ang_kt";
        case PRM_FLOAT_LOAD_ANG_KF: return "load_ang_kf";
        case PRM_FLOAT_LOAD_ANG_KD: return "load_ang_kd";
        case PRM_FLOAT_LOAD_ANG_ERR_LIM: return "load_ang_err_lim";
        case PRM_FLOAT_LOAD_ANG_OUT_LIM: return "load_ang_out_lim";
        case PRM_FLOAT_LOAD_ANG_OUT_RATE_LIM: return "load_ang_out_rate_lim";
        case PRM_FLOAT_LOAD_ANG_ERR_RATE_LIM: return "load_ang_err_rate_lim";
        case PRM_FLOAT_LOAD_ANG_DZ: return "load_ang_dz";
        case PRM_BOOL_LOAD_ANG_DZ_EN: return "load_ang_dz_en";
        case PRM_FLOAT_ROTOR_SPEED_KP: return "rotor_speed_kp";
        case PRM_FLOAT_ROTOR_SPEED_KI: return "rotor_speed_ki";
        case PRM_FLOAT_ROTOR_SPEED_KB: return "rotor_speed_kb";
        case PRM_FLOAT_ROTOR_SPEED_KT: return "rotor_speed_kt";
        case PRM_FLOAT_ROTOR_SPEED_KF: return "rotor_speed_kf";
        case PRM_FLOAT_ROTOR_SPEED_ERR_LIM: return "rotor_speed_err_lim";
        case PRM_FLOAT_ROTOR_SPEED_OUT_LIM: return "rotor_speed_out_lim";
        case PRM_FLOAT_ROTOR_SPEED_INT_LIM: return "rotor_speed_int_lim";
        case PRM_FLOAT_ROTOR_SPEED_OUT_RATE_LIM: return "rotor_speed_out_rate_lim";
        case PRM_FLOAT_ROTOR_SPEED_ERR_RATE_LIM: return "rotor_speed_err_rate_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KP: return "rotor_speed_master_common_kp";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KI: return "rotor_speed_master_common_ki";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KB: return "rotor_speed_master_common_kb";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KT: return "rotor_speed_master_common_kt";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KF: return "rotor_speed_master_common_kf";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_ERR_LIM: return "rotor_speed_master_common_err_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_OUT_LIM: return "rotor_speed_master_common_out_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_INT_LIM: return "rotor_speed_master_common_int_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_OUT_RATE_LIM: return "rotor_speed_master_common_out_rate_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_ERR_RATE_LIM: return "rotor_speed_master_common_err_rate_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KP: return "rotor_speed_master_diff_kp";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KI: return "rotor_speed_master_diff_ki";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KB: return "rotor_speed_master_diff_kb";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KT: return "rotor_speed_master_diff_kt";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KF: return "rotor_speed_master_diff_kf";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_ERR_LIM: return "rotor_speed_master_diff_err_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_OUT_LIM: return "rotor_speed_master_diff_out_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_INT_LIM: return "rotor_speed_master_diff_int_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_OUT_RATE_LIM: return "rotor_speed_master_diff_out_rate_lim";
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_ERR_RATE_LIM: return "rotor_speed_master_diff_err_rate_lim";
        case PRM_INT_ROTOR_SPEED_ROLE: return "rotor_speed_role";
        case PRM_FLOAT_ROTOR_ANG_KP: return "rotor_ang_kp";
        case PRM_FLOAT_ROTOR_ANG_KI: return "rotor_ang_ki";
        case PRM_FLOAT_ROTOR_ANG_KB: return "rotor_ang_kb";
        case PRM_FLOAT_ROTOR_ANG_KT: return "rotor_ang_kt";
        case PRM_FLOAT_ROTOR_ANG_KF: return "rotor_ang_kf";
        case PRM_FLOAT_ROTOR_ANG_ERR_LIM: return "rotor_ang_err_lim";
        case PRM_FLOAT_ROTOR_ANG_OUT_LIM: return "rotor_ang_out_lim";
        case PRM_FLOAT_ROTOR_ANG_OUT_RATE_LIM: return "rotor_ang_out_rate_lim";
        case PRM_FLOAT_ROTOR_ANG_ERR_RATE_LIM: return "rotor_ang_err_rate_lim";
        case PRM_FLOAT_ROTOR_ANG_DZ: return "rotor_ang_dz";
        case PRM_BOOL_ROTOR_ANG_DZ_EN: return "rotor_ang_dz_en";
        case PRM_BOOL_IM_MODE: return "im_mode";
        case PRM_FLOAT_PTP_KP: return "ptp_kp";
        case PRM_FLOAT_PTP_KI: return "ptp_ki";
        case PRM_FLOAT_PTP_KD: return "ptp_kd";
        case PRM_STRING_FACTORY_DATE: return "factory_date";
        case PRM_STRING_FACTORY_NUMBER: return "factory_number";
        case PRM_STRING_DESCRIPTION: return "description";
        case PRM_STRING_COM_IF_SRV_MCAST_REQ: return "com_if_srv_mcast_req";
        case PRM_STRING_COM_IF_SRV_MCAST_ANS: return "com_if_srv_mcast_ans";
        case PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST: return "com_if_bro_bup_ctrl_mcast";
        case PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST: return "com_if_bro_bup_data_mcast";
        case PRM_STRING_COM_IF_BUP_INTERNAL_MCAST: return "com_if_bup_internal_mcast";
        case PRM_STRING_COM_IF_BRO_BUP_SRV_MCAST: return "com_if_bro_bup_srv_mcast";
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST: return "com_if_im_bro_drive_mcast";
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_CTRL_MCAST: return "com_if_im_bro_drive_ctrl_mcast";
        case PRM_INT_DEV_ID: return "dev_id";
        default: return "???";
    }
}

const char* mj_get_dev_name(int32_t val)
{
    switch(val) {
        case BRO30_AUFD: return "aufd";
        case BRO30_DCU: return "dcu";
        case BRO30_BUP_DCU_LFD: return "bup_dcu_lfd";
        case BRO30_BUP_DCU_RFD: return "bup_dcu_rfd";
        case BRO30_BUP_DCU_LRD: return "bup_dcu_lrd";
        case BRO30_BUP_DCU_RRD: return "bup_dcu_rrd";
        case BRO30_BUP_DCU_LST: return "bup_dcu_lst";
        case BRO30_BUP_DCU_RST: return "bup_dcu_rst";
        case BRO30_MON: return "mon";
        case BRO30_IM_BRO: return "im_bro";
        case 0xFFFF: return "ALL";
        case 0: return "NONE";
        default: return "???";
    }
}

const char* mj_get_msg_name(int32_t val)
{
    switch(val) {
        case ID_PRM_REQ: return "prm_req";
        case ID_PRM_ANS: return "prm_ans";
        case ID_CMD_REQ: return "cmd_req";
        case ID_CMD_ANS: return "cmd_ans";
        case ID_MSG_REQ: return "msg_req";
        case ID_MSG_ANS: return "msg_ans";
        case ID_DBG: return "dbg";
        case ID_DCU_TEL: return "dcu_tel";
        case ID_BUP_STATE: return "bup_state";
        case ID_DRIVE_SLAVE_FB: return "drive_slave_fb";
        case ID_DRIVE_MASTER_CTRL: return "drive_master_ctrl";
        case ID_BUP_CTRL: return "bup_ctrl";
        case ID_BUP_MULTI_CONTROL: return "bup_multi_control";
        case ID_BUP_SRV_CTRL: return "bup_srv_ctrl";
        case ID_IM_BRO_DRIVE_CTRL: return "im_bro_drive_ctrl";
        case ID_IM_BRO_DRIVERS_SENS: return "im_bro_drivers_sens";
        case ID_PTP_STATE: return "ptp_state";
        case ID_FORMULAR: return "formular";
        default: return "???";
    }
}

int mj_str_if_to_int(const char* str, uint32_t *ip, uint16_t *port)
{
    unsigned int b1, b2, b3, b4, p;
    if (!str || !ip || !port){
        return -1;
    }

    if (sscanf(str, "%u.%u.%u.%u:%u", &b4, &b3, &b2, &b1, &p) != 5){
        return -2;
    }

    if (b1 > 255 || b2 > 255 || b3 > 255 || b4 > 255 || p > 65535)
    {
        return -3;
    }

    *ip = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
    *port = (uint16_t)(((p & 0xFF) << 8) | (p >> 8));
    return 0;
}

int mj_int_if_to_str(uint32_t ip, uint16_t port, char* buf, size_t buf_len)
{
    unsigned int b1, b2, b3, b4;
    b1 = (ip >> 24) & 0xFF;
    b2 = (ip >> 16) & 0xFF;
    b3 = (ip >> 8) & 0xFF;
    b4 = (ip) & 0xFF;
    snprintf(buf, buf_len, "%u.%u.%u.%u:%u",b1,b2,b3,b4,port);
    return 0;
}