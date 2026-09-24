#ifndef __H_MJUTILS_H
#define __H_MJUTILS_H
#include "mjsysspec.h"

#ifdef __cplusplus
 extern "C" {
#endif

const char* parameter_request_type_str(int32_t val);
const char* parameter_status_str(int32_t val);
const char* command_type_str(int32_t val);
const char* command_state_str(int32_t val);
const char* msg_state_str(int32_t val);
const char* drv_ctrl_mode_str(int32_t val);
const char* drv_ctrl_error_str(int32_t val);
const char* relay_signal_state_str(int32_t val);
const char* rotor_ang_sens_status_str(int32_t val);
const char* load_ang_sens_status_str(int32_t val);
const char* inverter_mode_str(int32_t val);
const char* dcu_status_str(int32_t val);
const char* rotor_brake_state_str(int32_t val);
const char* move_limit_state_str(int32_t val);
const char* transit_proc_status_str(int32_t val);
const char* sync_state_str(int32_t val);

const char* mj_get_prm_name(int32_t val);
const char* mj_get_dev_name(int32_t val);
const char* mj_get_msg_name(int32_t val);
#ifdef __cplusplus
}
#endif

int mj_str_if_to_int(const char* str, uint32_t *ip, uint16_t *port);
int mj_int_if_to_str(uint32_t ip, uint16_t port, char* buf, size_t buf_len);

#endif /** __H_MJUTILS_H */