#include "mjtypes.h"


mj_check_result_t bup_drv_control_type_check(bup_drv_control_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->dr.mode)) - baseAddr) == 0) &&
        (sizeof(ptr->dr.mode) == 4) &&

        (((mj_ptr_t)(&(ptr->dr.angle)) - baseAddr) == 4) &&
        (sizeof(ptr->dr.angle) == 4) &&

        (((mj_ptr_t)(&(ptr->dr.speed)) - baseAddr) == 8) &&
        (sizeof(ptr->dr.speed) == 4) &&

        (((mj_ptr_t)(&(ptr->dr.voltage)) - baseAddr) == 12) &&
        (sizeof(ptr->dr.voltage) == 4) &&

        (((mj_ptr_t)(&(ptr->dr.current)) - baseAddr) == 16) &&
        (sizeof(ptr->dr.current) == 4)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t bup_drv_multi_control_type_check(bup_drv_multi_control_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->lfd.mode)) - baseAddr) == 0) &&
        (sizeof(ptr->lfd.mode) == 4) &&

        (((mj_ptr_t)(&(ptr->lfd.angle)) - baseAddr) == 4) &&
        (sizeof(ptr->lfd.angle) == 4) &&

        (((mj_ptr_t)(&(ptr->lfd.speed)) - baseAddr) == 8) &&
        (sizeof(ptr->lfd.speed) == 4) &&

        (((mj_ptr_t)(&(ptr->lfd.voltage)) - baseAddr) == 12) &&
        (sizeof(ptr->lfd.voltage) == 4) &&

        (((mj_ptr_t)(&(ptr->lfd.current)) - baseAddr) == 16) &&
        (sizeof(ptr->lfd.current) == 4) &&

        (((mj_ptr_t)(&(ptr->lrd.mode)) - baseAddr) == 20) &&
        (sizeof(ptr->lrd.mode) == 4) &&

        (((mj_ptr_t)(&(ptr->lrd.angle)) - baseAddr) == 24) &&
        (sizeof(ptr->lrd.angle) == 4) &&

        (((mj_ptr_t)(&(ptr->lrd.speed)) - baseAddr) == 28) &&
        (sizeof(ptr->lrd.speed) == 4) &&

        (((mj_ptr_t)(&(ptr->lrd.voltage)) - baseAddr) == 32) &&
        (sizeof(ptr->lrd.voltage) == 4) &&

        (((mj_ptr_t)(&(ptr->lrd.current)) - baseAddr) == 36) &&
        (sizeof(ptr->lrd.current) == 4) &&

        (((mj_ptr_t)(&(ptr->lst.mode)) - baseAddr) == 40) &&
        (sizeof(ptr->lst.mode) == 4) &&

        (((mj_ptr_t)(&(ptr->lst.angle)) - baseAddr) == 44) &&
        (sizeof(ptr->lst.angle) == 4) &&

        (((mj_ptr_t)(&(ptr->lst.speed)) - baseAddr) == 48) &&
        (sizeof(ptr->lst.speed) == 4) &&

        (((mj_ptr_t)(&(ptr->lst.voltage)) - baseAddr) == 52) &&
        (sizeof(ptr->lst.voltage) == 4) &&

        (((mj_ptr_t)(&(ptr->lst.current)) - baseAddr) == 56) &&
        (sizeof(ptr->lst.current) == 4) &&

        (((mj_ptr_t)(&(ptr->rfd.mode)) - baseAddr) == 60) &&
        (sizeof(ptr->rfd.mode) == 4) &&

        (((mj_ptr_t)(&(ptr->rfd.angle)) - baseAddr) == 64) &&
        (sizeof(ptr->rfd.angle) == 4) &&

        (((mj_ptr_t)(&(ptr->rfd.speed)) - baseAddr) == 68) &&
        (sizeof(ptr->rfd.speed) == 4) &&

        (((mj_ptr_t)(&(ptr->rfd.voltage)) - baseAddr) == 72) &&
        (sizeof(ptr->rfd.voltage) == 4) &&

        (((mj_ptr_t)(&(ptr->rfd.current)) - baseAddr) == 76) &&
        (sizeof(ptr->rfd.current) == 4) &&

        (((mj_ptr_t)(&(ptr->rrd.mode)) - baseAddr) == 80) &&
        (sizeof(ptr->rrd.mode) == 4) &&

        (((mj_ptr_t)(&(ptr->rrd.angle)) - baseAddr) == 84) &&
        (sizeof(ptr->rrd.angle) == 4) &&

        (((mj_ptr_t)(&(ptr->rrd.speed)) - baseAddr) == 88) &&
        (sizeof(ptr->rrd.speed) == 4) &&

        (((mj_ptr_t)(&(ptr->rrd.voltage)) - baseAddr) == 92) &&
        (sizeof(ptr->rrd.voltage) == 4) &&

        (((mj_ptr_t)(&(ptr->rrd.current)) - baseAddr) == 96) &&
        (sizeof(ptr->rrd.current) == 4) &&

        (((mj_ptr_t)(&(ptr->rst.mode)) - baseAddr) == 100) &&
        (sizeof(ptr->rst.mode) == 4) &&

        (((mj_ptr_t)(&(ptr->rst.angle)) - baseAddr) == 104) &&
        (sizeof(ptr->rst.angle) == 4) &&

        (((mj_ptr_t)(&(ptr->rst.speed)) - baseAddr) == 108) &&
        (sizeof(ptr->rst.speed) == 4) &&

        (((mj_ptr_t)(&(ptr->rst.voltage)) - baseAddr) == 112) &&
        (sizeof(ptr->rst.voltage) == 4) &&

        (((mj_ptr_t)(&(ptr->rst.current)) - baseAddr) == 116) &&
        (sizeof(ptr->rst.current) == 4)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t bup_drv_state_type_check(bup_drv_state_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->mode)) - baseAddr) == 0) &&
        (sizeof(ptr->mode) == 1) &&

        (((mj_ptr_t)(&(ptr->error)) - baseAddr) == 1) &&
        (sizeof(ptr->error) == 1) &&

        (((mj_ptr_t)(&(ptr->status)) - baseAddr) == 2) &&
        (sizeof(ptr->status) == 1) &&

        (((mj_ptr_t)(&(ptr->limit)) - baseAddr) == 3) &&
        (sizeof(ptr->limit) == 1) &&

        (((mj_ptr_t)(&(ptr->angle)) - baseAddr) == 4) &&
        (sizeof(ptr->angle) == 4) &&

        (((mj_ptr_t)(&(ptr->speed)) - baseAddr) == 8) &&
        (sizeof(ptr->speed) == 4) &&

        (((mj_ptr_t)(&(ptr->stator_temp)) - baseAddr) == 12) &&
        (sizeof(ptr->stator_temp) == 4) &&

        (((mj_ptr_t)(&(ptr->brake_state)) - baseAddr) == 16) &&
        (sizeof(ptr->brake_state) == 1) &&

        (((mj_ptr_t)(&(ptr->power_voltage)) - baseAddr) == 20) &&
        (sizeof(ptr->power_voltage) == 4) &&

        (((mj_ptr_t)(&(ptr->id)) - baseAddr) == 24) &&
        (sizeof(ptr->id) == 4) &&

        (((mj_ptr_t)(&(ptr->iq)) - baseAddr) == 28) &&
        (sizeof(ptr->iq) == 4) &&

        (((mj_ptr_t)(&(ptr->electrical_power)) - baseAddr) == 32) &&
        (sizeof(ptr->electrical_power) == 4) &&

        (((mj_ptr_t)(&(ptr->load_sens_state)) - baseAddr) == 36) &&
        (sizeof(ptr->load_sens_state) == 1) &&

        (((mj_ptr_t)(&(ptr->load_sens_angle)) - baseAddr) == 40) &&
        (sizeof(ptr->load_sens_angle) == 4) &&

        (((mj_ptr_t)(&(ptr->load_sens_speed)) - baseAddr) == 44) &&
        (sizeof(ptr->load_sens_speed) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_sens_state)) - baseAddr) == 48) &&
        (sizeof(ptr->rotor_sens_state) == 1) &&

        (((mj_ptr_t)(&(ptr->rotor_sens_angle)) - baseAddr) == 52) &&
        (sizeof(ptr->rotor_sens_angle) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_sens_speed)) - baseAddr) == 56) &&
        (sizeof(ptr->rotor_sens_speed) == 4)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t command_answer_type_check(command_answer_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->command)) - baseAddr) == 0) &&
        (sizeof(ptr->command) == 4) &&

        (((mj_ptr_t)(&(ptr->state)) - baseAddr) == 4) &&
        (sizeof(ptr->state) == 4) &&

        (((mj_ptr_t)(&(ptr->cnt)) - baseAddr) == 8) &&
        (sizeof(ptr->cnt) == 4) &&

        (((mj_ptr_t)(&(ptr->info)) - baseAddr) == 12) &&
        (sizeof(ptr->info) == 32)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t command_request_type_check(command_request_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->type)) - baseAddr) == 0) &&
        (sizeof(ptr->type) == 4)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t dbg_data_type_check(dbg_data_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->fval)) - baseAddr) == 0) &&
        (sizeof(ptr->fval) == 20)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t dcu_telemetry_type_check(dcu_telemetry_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->mode)) - baseAddr) == 0) &&
        (sizeof(ptr->mode) == 1) &&

        (((mj_ptr_t)(&(ptr->status)) - baseAddr) == 1) &&
        (sizeof(ptr->status) == 1) &&

        (((mj_ptr_t)(&(ptr->err)) - baseAddr) == 2) &&
        (sizeof(ptr->err) == 1) &&

        (((mj_ptr_t)(&(ptr->load_sens_state)) - baseAddr) == 3) &&
        (sizeof(ptr->load_sens_state) == 1) &&

        (((mj_ptr_t)(&(ptr->load_sens_angle)) - baseAddr) == 4) &&
        (sizeof(ptr->load_sens_angle) == 4) &&

        (((mj_ptr_t)(&(ptr->load_sens_speed)) - baseAddr) == 8) &&
        (sizeof(ptr->load_sens_speed) == 4) &&

        (((mj_ptr_t)(&(ptr->power_vdc)) - baseAddr) == 12) &&
        (sizeof(ptr->power_vdc) == 4) &&

        (((mj_ptr_t)(&(ptr->current.a)) - baseAddr) == 16) &&
        (sizeof(ptr->current.a) == 4) &&

        (((mj_ptr_t)(&(ptr->current.b)) - baseAddr) == 20) &&
        (sizeof(ptr->current.b) == 4) &&

        (((mj_ptr_t)(&(ptr->current.c)) - baseAddr) == 24) &&
        (sizeof(ptr->current.c) == 4) &&

        (((mj_ptr_t)(&(ptr->pwm.a)) - baseAddr) == 28) &&
        (sizeof(ptr->pwm.a) == 4) &&

        (((mj_ptr_t)(&(ptr->pwm.b)) - baseAddr) == 32) &&
        (sizeof(ptr->pwm.b) == 4) &&

        (((mj_ptr_t)(&(ptr->pwm.c)) - baseAddr) == 36) &&
        (sizeof(ptr->pwm.c) == 4) &&

        (((mj_ptr_t)(&(ptr->park_voltage.d)) - baseAddr) == 40) &&
        (sizeof(ptr->park_voltage.d) == 4) &&

        (((mj_ptr_t)(&(ptr->park_voltage.q)) - baseAddr) == 44) &&
        (sizeof(ptr->park_voltage.q) == 4) &&

        (((mj_ptr_t)(&(ptr->park_current.d)) - baseAddr) == 48) &&
        (sizeof(ptr->park_current.d) == 4) &&

        (((mj_ptr_t)(&(ptr->park_current.q)) - baseAddr) == 52) &&
        (sizeof(ptr->park_current.q) == 4) &&

        (((mj_ptr_t)(&(ptr->ibrk)) - baseAddr) == 56) &&
        (sizeof(ptr->ibrk) == 4) &&

        (((mj_ptr_t)(&(ptr->stator_temp)) - baseAddr) == 60) &&
        (sizeof(ptr->stator_temp) == 4) &&

        (((mj_ptr_t)(&(ptr->brake_state)) - baseAddr) == 64) &&
        (sizeof(ptr->brake_state) == 1) &&

        (((mj_ptr_t)(&(ptr->power_voltage)) - baseAddr) == 68) &&
        (sizeof(ptr->power_voltage) == 4) &&

        (((mj_ptr_t)(&(ptr->electrical_power)) - baseAddr) == 72) &&
        (sizeof(ptr->electrical_power) == 4) &&

        (((mj_ptr_t)(&(ptr->ang_pid_state.err)) - baseAddr) == 76) &&
        (sizeof(ptr->ang_pid_state.err) == 4) &&

        (((mj_ptr_t)(&(ptr->ang_pid_state.cor_err)) - baseAddr) == 80) &&
        (sizeof(ptr->ang_pid_state.cor_err) == 4) &&

        (((mj_ptr_t)(&(ptr->ang_pid_state.feed_forward)) - baseAddr) == 84) &&
        (sizeof(ptr->ang_pid_state.feed_forward) == 4) &&

        (((mj_ptr_t)(&(ptr->ang_pid_state.track)) - baseAddr) == 88) &&
        (sizeof(ptr->ang_pid_state.track) == 4) &&

        (((mj_ptr_t)(&(ptr->ang_pid_state.back)) - baseAddr) == 92) &&
        (sizeof(ptr->ang_pid_state.back) == 4) &&

        (((mj_ptr_t)(&(ptr->ang_pid_state.int_val)) - baseAddr) == 96) &&
        (sizeof(ptr->ang_pid_state.int_val) == 4) &&

        (((mj_ptr_t)(&(ptr->ang_pid_state.out)) - baseAddr) == 100) &&
        (sizeof(ptr->ang_pid_state.out) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_spd_pid_state.err)) - baseAddr) == 104) &&
        (sizeof(ptr->rotor_spd_pid_state.err) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_spd_pid_state.cor_err)) - baseAddr) == 108) &&
        (sizeof(ptr->rotor_spd_pid_state.cor_err) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_spd_pid_state.feed_forward)) - baseAddr) == 112) &&
        (sizeof(ptr->rotor_spd_pid_state.feed_forward) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_spd_pid_state.track)) - baseAddr) == 116) &&
        (sizeof(ptr->rotor_spd_pid_state.track) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_spd_pid_state.back)) - baseAddr) == 120) &&
        (sizeof(ptr->rotor_spd_pid_state.back) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_spd_pid_state.int_val)) - baseAddr) == 124) &&
        (sizeof(ptr->rotor_spd_pid_state.int_val) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_spd_pid_state.out)) - baseAddr) == 128) &&
        (sizeof(ptr->rotor_spd_pid_state.out) == 4) &&

        (((mj_ptr_t)(&(ptr->load_spd_pid_state.err)) - baseAddr) == 132) &&
        (sizeof(ptr->load_spd_pid_state.err) == 4) &&

        (((mj_ptr_t)(&(ptr->load_spd_pid_state.cor_err)) - baseAddr) == 136) &&
        (sizeof(ptr->load_spd_pid_state.cor_err) == 4) &&

        (((mj_ptr_t)(&(ptr->load_spd_pid_state.feed_forward)) - baseAddr) == 140) &&
        (sizeof(ptr->load_spd_pid_state.feed_forward) == 4) &&

        (((mj_ptr_t)(&(ptr->load_spd_pid_state.track)) - baseAddr) == 144) &&
        (sizeof(ptr->load_spd_pid_state.track) == 4) &&

        (((mj_ptr_t)(&(ptr->load_spd_pid_state.back)) - baseAddr) == 148) &&
        (sizeof(ptr->load_spd_pid_state.back) == 4) &&

        (((mj_ptr_t)(&(ptr->load_spd_pid_state.int_val)) - baseAddr) == 152) &&
        (sizeof(ptr->load_spd_pid_state.int_val) == 4) &&

        (((mj_ptr_t)(&(ptr->load_spd_pid_state.out)) - baseAddr) == 156) &&
        (sizeof(ptr->load_spd_pid_state.out) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_q_pid_state.err)) - baseAddr) == 160) &&
        (sizeof(ptr->curr_q_pid_state.err) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_q_pid_state.cor_err)) - baseAddr) == 164) &&
        (sizeof(ptr->curr_q_pid_state.cor_err) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_q_pid_state.feed_forward)) - baseAddr) == 168) &&
        (sizeof(ptr->curr_q_pid_state.feed_forward) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_q_pid_state.track)) - baseAddr) == 172) &&
        (sizeof(ptr->curr_q_pid_state.track) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_q_pid_state.back)) - baseAddr) == 176) &&
        (sizeof(ptr->curr_q_pid_state.back) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_q_pid_state.int_val)) - baseAddr) == 180) &&
        (sizeof(ptr->curr_q_pid_state.int_val) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_q_pid_state.out)) - baseAddr) == 184) &&
        (sizeof(ptr->curr_q_pid_state.out) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_d_pid_state.err)) - baseAddr) == 188) &&
        (sizeof(ptr->curr_d_pid_state.err) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_d_pid_state.cor_err)) - baseAddr) == 192) &&
        (sizeof(ptr->curr_d_pid_state.cor_err) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_d_pid_state.feed_forward)) - baseAddr) == 196) &&
        (sizeof(ptr->curr_d_pid_state.feed_forward) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_d_pid_state.track)) - baseAddr) == 200) &&
        (sizeof(ptr->curr_d_pid_state.track) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_d_pid_state.back)) - baseAddr) == 204) &&
        (sizeof(ptr->curr_d_pid_state.back) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_d_pid_state.int_val)) - baseAddr) == 208) &&
        (sizeof(ptr->curr_d_pid_state.int_val) == 4) &&

        (((mj_ptr_t)(&(ptr->curr_d_pid_state.out)) - baseAddr) == 212) &&
        (sizeof(ptr->curr_d_pid_state.out) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_sens_state)) - baseAddr) == 216) &&
        (sizeof(ptr->rotor_sens_state) == 1) &&

        (((mj_ptr_t)(&(ptr->rotor_sens_angle)) - baseAddr) == 220) &&
        (sizeof(ptr->rotor_sens_angle) == 4) &&

        (((mj_ptr_t)(&(ptr->rotor_sens_speed)) - baseAddr) == 224) &&
        (sizeof(ptr->rotor_sens_speed) == 4) &&

        (((mj_ptr_t)(&(ptr->on)) - baseAddr) == 228) &&
        (sizeof(ptr->on) == 1) &&

        (((mj_ptr_t)(&(ptr->manual)) - baseAddr) == 229) &&
        (sizeof(ptr->manual) == 1) &&

        (((mj_ptr_t)(&(ptr->block)) - baseAddr) == 230) &&
        (sizeof(ptr->block) == 1) &&

        (((mj_ptr_t)(&(ptr->sync)) - baseAddr) == 231) &&
        (sizeof(ptr->sync) == 1) &&

        (((mj_ptr_t)(&(ptr->inv_octw)) - baseAddr) == 232) &&
        (sizeof(ptr->inv_octw) == 1) &&

        (((mj_ptr_t)(&(ptr->inv_fault)) - baseAddr) == 233) &&
        (sizeof(ptr->inv_fault) == 1) &&

        (((mj_ptr_t)(&(ptr->en_gate)) - baseAddr) == 234) &&
        (sizeof(ptr->en_gate) == 1)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t drivers_sens_type_check(drivers_sens_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->currents_gn)) - baseAddr) == 0) &&
        (sizeof(ptr->currents_gn) == 12) &&

        (((mj_ptr_t)(&(ptr->rotor_angle_gn)) - baseAddr) == 12) &&
        (sizeof(ptr->rotor_angle_gn) == 4) &&

        (((mj_ptr_t)(&(ptr->v_nom)) - baseAddr) == 16) &&
        (sizeof(ptr->v_nom) == 4)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t formular_info_type_check(formular_info_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->description)) - baseAddr) == 0) &&
        (sizeof(ptr->description) == 32) &&

        (((mj_ptr_t)(&(ptr->factory_number)) - baseAddr) == 32) &&
        (sizeof(ptr->factory_number) == 32) &&

        (((mj_ptr_t)(&(ptr->factory_date)) - baseAddr) == 64) &&
        (sizeof(ptr->factory_date) == 32) &&

        (((mj_ptr_t)(&(ptr->software_version)) - baseAddr) == 96) &&
        (sizeof(ptr->software_version) == 32) &&

        (((mj_ptr_t)(&(ptr->protocol_version)) - baseAddr) == 128) &&
        (sizeof(ptr->protocol_version) == 32) &&

        (((mj_ptr_t)(&(ptr->GUID)) - baseAddr) == 160) &&
        (sizeof(ptr->GUID) == 32) &&

        (((mj_ptr_t)(&(ptr->operation_time)) - baseAddr) == 192) &&
        (sizeof(ptr->operation_time) == 4) &&

        (((mj_ptr_t)(&(ptr->software_checksum)) - baseAddr) == 196) &&
        (sizeof(ptr->software_checksum) == 64) &&

        (((mj_ptr_t)(&(ptr->code)) - baseAddr) == 260) &&
        (sizeof(ptr->code) == 1)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t im_bro_drive_ctrl_type_check(im_bro_drive_ctrl_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->voltage)) - baseAddr) == 0) &&
        (sizeof(ptr->voltage) == 12) &&

        (((mj_ptr_t)(&(ptr->connected)) - baseAddr) == 12) &&
        (sizeof(ptr->connected) == 1)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t msg_answer_type_check(msg_answer_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->id)) - baseAddr) == 0) &&
        (sizeof(ptr->id) == 2) &&

        (((mj_ptr_t)(&(ptr->cnt)) - baseAddr) == 4) &&
        (sizeof(ptr->cnt) == 4) &&

        (((mj_ptr_t)(&(ptr->state)) - baseAddr) == 8) &&
        (sizeof(ptr->state) == 4)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t msg_request_type_check(msg_request_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->id)) - baseAddr) == 0) &&
        (sizeof(ptr->id) == 2)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t parameter_answer_type_check(parameter_answer_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->id)) - baseAddr) == 0) &&
        (sizeof(ptr->id) == 4) &&

        (((mj_ptr_t)(&(ptr->ans)) - baseAddr) == 4) &&
        (sizeof(ptr->ans) == 4) &&

        (((mj_ptr_t)(&(ptr->val)) - baseAddr) == 8) &&
        (sizeof(ptr->val) == 32)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t parameter_request_type_check(parameter_request_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->type)) - baseAddr) == 0) &&
        (sizeof(ptr->type) == 4) &&

        (((mj_ptr_t)(&(ptr->id)) - baseAddr) == 4) &&
        (sizeof(ptr->id) == 4) &&

        (((mj_ptr_t)(&(ptr->val)) - baseAddr) == 8) &&
        (sizeof(ptr->val) == 32)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
mj_check_result_t ptp_info_type_check(ptp_info_msg_t * ptr)
{
	mj_ptr_t baseAddr = (mj_ptr_t)(&ptr->hdr.ts_low) + (mj_ptr_t)(sizeof(ptr->hdr.ts_low));
    if ((baseAddr - ((mj_ptr_t)(ptr)) == MJ_HEADER_SIZE) &&
        (((mj_ptr_t)(&(ptr->is_master)) - baseAddr) == 0) &&
        (sizeof(ptr->is_master) == 1) &&

        (((mj_ptr_t)(&(ptr->path_delay)) - baseAddr) == 4) &&
        (sizeof(ptr->path_delay) == 4) &&

        (((mj_ptr_t)(&(ptr->offset_ns)) - baseAddr) == 8) &&
        (sizeof(ptr->offset_ns) == 4) &&

        (((mj_ptr_t)(&(ptr->mean_offset_ns)) - baseAddr) == 12) &&
        (sizeof(ptr->mean_offset_ns) == 4) &&

        (((mj_ptr_t)(&(ptr->state)) - baseAddr) == 16) &&
        (sizeof(ptr->state) == 4)
    )
    {
        return MJ_CHECK_OK;
    }
    return MJ_CHECK_FAIL;
}
