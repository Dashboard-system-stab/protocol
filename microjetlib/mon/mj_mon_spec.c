#include "mj_mon_spec.h"

#define IN_INT_COUNT 7

static uint32_t group_addr[IN_INT_COUNT*2];

static const uint8_t devMac[6] = { 0x2,0x0,0x0,0x0,0x0,0x8 };

static uint32_t ticks = 0;
static void *ethInt = NULL;
static mj_drv_interface_t * p_drv = NULL;
static uint16_t self_dev_id = BRO30_MON;

static mj_mon_t mj_handle;

static uint32_t aufd_bup_multi_control_rx_tick = UINT32_MAX - 241.0;
static uint8_t  in_aufd_bup_multi_control_lock_cnt = 0;
static bup_drv_multi_control_msg_t* in_aufd_bup_multi_control_delayed_ptr = NULL;
static uint32_t aufd_bup_multi_control_delayed_ts_s = 0;
static uint32_t aufd_bup_multi_control_delayed_ts_ns = 0;
static uint8_t  in_aufd_bup_multi_control_updated = 0;
static uint32_t  in_aufd_bup_multi_control_total = 0;
static uint32_t  in_aufd_bup_multi_control_miss = 0;
static uint16_t  in_aufd_bup_multi_control_last_cnt = 0;
static mj_msg_state_t in_aufd_bup_multi_control_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_aufd_bup_multi_control_lock_cnt < 255)
        {
            in_aufd_bup_multi_control_lock_cnt++;
        }
    }else{
        if (in_aufd_bup_multi_control_lock_cnt > 0)
        {
            if ((in_aufd_bup_multi_control_lock_cnt == 1) && (in_aufd_bup_multi_control_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.aufd.bup_multi_control.msg);
                mj_handle.in.aufd.bup_multi_control.msg = (bup_drv_multi_control_msg_t*)(in_aufd_bup_multi_control_delayed_ptr);
                mj_handle.in.aufd.bup_multi_control.ts_s = aufd_bup_multi_control_delayed_ts_s;
                mj_handle.in.aufd.bup_multi_control.ts_ns = aufd_bup_multi_control_delayed_ts_ns;
                aufd_bup_multi_control_rx_tick = ticks;
                mj_handle.in.aufd.bup_multi_control.state = MJ_MSG_ACTUAL;
                in_aufd_bup_multi_control_updated = 1;
                p_drv->udp4.free(old_buff);
                in_aufd_bup_multi_control_delayed_ptr = NULL;
            }
            in_aufd_bup_multi_control_lock_cnt--;
        }
    }
    return in_aufd_bup_multi_control_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_aufd_bup_multi_control_copy_fcn(void *dst)
{
    in_aufd_bup_multi_control_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.aufd.bup_multi_control.msg), sizeof(bup_drv_multi_control_msg_t));
    in_aufd_bup_multi_control_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t aufd_cmd_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_aufd_cmd_ans_lock_cnt = 0;
static command_answer_msg_t* in_aufd_cmd_ans_delayed_ptr = NULL;
static uint32_t aufd_cmd_ans_delayed_ts_s = 0;
static uint32_t aufd_cmd_ans_delayed_ts_ns = 0;
static uint8_t  in_aufd_cmd_ans_updated = 0;
static uint32_t  in_aufd_cmd_ans_total = 0;
static uint32_t  in_aufd_cmd_ans_miss = 0;
static uint16_t  in_aufd_cmd_ans_last_cnt = 0;
static mj_msg_state_t in_aufd_cmd_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_aufd_cmd_ans_lock_cnt < 255)
        {
            in_aufd_cmd_ans_lock_cnt++;
        }
    }else{
        if (in_aufd_cmd_ans_lock_cnt > 0)
        {
            if ((in_aufd_cmd_ans_lock_cnt == 1) && (in_aufd_cmd_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.aufd.cmd_ans.msg);
                mj_handle.in.aufd.cmd_ans.msg = (command_answer_msg_t*)(in_aufd_cmd_ans_delayed_ptr);
                mj_handle.in.aufd.cmd_ans.ts_s = aufd_cmd_ans_delayed_ts_s;
                mj_handle.in.aufd.cmd_ans.ts_ns = aufd_cmd_ans_delayed_ts_ns;
                aufd_cmd_ans_rx_tick = ticks;
                mj_handle.in.aufd.cmd_ans.state = MJ_MSG_ACTUAL;
                in_aufd_cmd_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_aufd_cmd_ans_delayed_ptr = NULL;
            }
            in_aufd_cmd_ans_lock_cnt--;
        }
    }
    return in_aufd_cmd_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_aufd_cmd_ans_copy_fcn(void *dst)
{
    in_aufd_cmd_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.aufd.cmd_ans.msg), sizeof(command_answer_msg_t));
    in_aufd_cmd_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t aufd_formular_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_aufd_formular_lock_cnt = 0;
static formular_info_msg_t* in_aufd_formular_delayed_ptr = NULL;
static uint32_t aufd_formular_delayed_ts_s = 0;
static uint32_t aufd_formular_delayed_ts_ns = 0;
static uint8_t  in_aufd_formular_updated = 0;
static uint32_t  in_aufd_formular_total = 0;
static uint32_t  in_aufd_formular_miss = 0;
static uint16_t  in_aufd_formular_last_cnt = 0;
static mj_msg_state_t in_aufd_formular_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_aufd_formular_lock_cnt < 255)
        {
            in_aufd_formular_lock_cnt++;
        }
    }else{
        if (in_aufd_formular_lock_cnt > 0)
        {
            if ((in_aufd_formular_lock_cnt == 1) && (in_aufd_formular_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.aufd.formular.msg);
                mj_handle.in.aufd.formular.msg = (formular_info_msg_t*)(in_aufd_formular_delayed_ptr);
                mj_handle.in.aufd.formular.ts_s = aufd_formular_delayed_ts_s;
                mj_handle.in.aufd.formular.ts_ns = aufd_formular_delayed_ts_ns;
                aufd_formular_rx_tick = ticks;
                mj_handle.in.aufd.formular.state = MJ_MSG_ACTUAL;
                in_aufd_formular_updated = 1;
                p_drv->udp4.free(old_buff);
                in_aufd_formular_delayed_ptr = NULL;
            }
            in_aufd_formular_lock_cnt--;
        }
    }
    return in_aufd_formular_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_aufd_formular_copy_fcn(void *dst)
{
    in_aufd_formular_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.aufd.formular.msg), sizeof(formular_info_msg_t));
    in_aufd_formular_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t aufd_msg_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_aufd_msg_ans_lock_cnt = 0;
static msg_answer_msg_t* in_aufd_msg_ans_delayed_ptr = NULL;
static uint32_t aufd_msg_ans_delayed_ts_s = 0;
static uint32_t aufd_msg_ans_delayed_ts_ns = 0;
static uint8_t  in_aufd_msg_ans_updated = 0;
static uint32_t  in_aufd_msg_ans_total = 0;
static uint32_t  in_aufd_msg_ans_miss = 0;
static uint16_t  in_aufd_msg_ans_last_cnt = 0;
static mj_msg_state_t in_aufd_msg_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_aufd_msg_ans_lock_cnt < 255)
        {
            in_aufd_msg_ans_lock_cnt++;
        }
    }else{
        if (in_aufd_msg_ans_lock_cnt > 0)
        {
            if ((in_aufd_msg_ans_lock_cnt == 1) && (in_aufd_msg_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.aufd.msg_ans.msg);
                mj_handle.in.aufd.msg_ans.msg = (msg_answer_msg_t*)(in_aufd_msg_ans_delayed_ptr);
                mj_handle.in.aufd.msg_ans.ts_s = aufd_msg_ans_delayed_ts_s;
                mj_handle.in.aufd.msg_ans.ts_ns = aufd_msg_ans_delayed_ts_ns;
                aufd_msg_ans_rx_tick = ticks;
                mj_handle.in.aufd.msg_ans.state = MJ_MSG_ACTUAL;
                in_aufd_msg_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_aufd_msg_ans_delayed_ptr = NULL;
            }
            in_aufd_msg_ans_lock_cnt--;
        }
    }
    return in_aufd_msg_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_aufd_msg_ans_copy_fcn(void *dst)
{
    in_aufd_msg_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.aufd.msg_ans.msg), sizeof(msg_answer_msg_t));
    in_aufd_msg_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t aufd_prm_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_aufd_prm_ans_lock_cnt = 0;
static parameter_answer_msg_t* in_aufd_prm_ans_delayed_ptr = NULL;
static uint32_t aufd_prm_ans_delayed_ts_s = 0;
static uint32_t aufd_prm_ans_delayed_ts_ns = 0;
static uint8_t  in_aufd_prm_ans_updated = 0;
static uint32_t  in_aufd_prm_ans_total = 0;
static uint32_t  in_aufd_prm_ans_miss = 0;
static uint16_t  in_aufd_prm_ans_last_cnt = 0;
static mj_msg_state_t in_aufd_prm_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_aufd_prm_ans_lock_cnt < 255)
        {
            in_aufd_prm_ans_lock_cnt++;
        }
    }else{
        if (in_aufd_prm_ans_lock_cnt > 0)
        {
            if ((in_aufd_prm_ans_lock_cnt == 1) && (in_aufd_prm_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.aufd.prm_ans.msg);
                mj_handle.in.aufd.prm_ans.msg = (parameter_answer_msg_t*)(in_aufd_prm_ans_delayed_ptr);
                mj_handle.in.aufd.prm_ans.ts_s = aufd_prm_ans_delayed_ts_s;
                mj_handle.in.aufd.prm_ans.ts_ns = aufd_prm_ans_delayed_ts_ns;
                aufd_prm_ans_rx_tick = ticks;
                mj_handle.in.aufd.prm_ans.state = MJ_MSG_ACTUAL;
                in_aufd_prm_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_aufd_prm_ans_delayed_ptr = NULL;
            }
            in_aufd_prm_ans_lock_cnt--;
        }
    }
    return in_aufd_prm_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_aufd_prm_ans_copy_fcn(void *dst)
{
    in_aufd_prm_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.aufd.prm_ans.msg), sizeof(parameter_answer_msg_t));
    in_aufd_prm_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_bup_state_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lfd_bup_state_lock_cnt = 0;
static bup_drv_state_msg_t* in_bup_dcu_lfd_bup_state_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_bup_state_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_bup_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_bup_state_updated = 0;
static uint32_t  in_bup_dcu_lfd_bup_state_total = 0;
static uint32_t  in_bup_dcu_lfd_bup_state_miss = 0;
static uint16_t  in_bup_dcu_lfd_bup_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_bup_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_bup_state_lock_cnt < 255)
        {
            in_bup_dcu_lfd_bup_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_bup_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_bup_state_lock_cnt == 1) && (in_bup_dcu_lfd_bup_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.bup_state.msg);
                mj_handle.in.bup_dcu_lfd.bup_state.msg = (bup_drv_state_msg_t*)(in_bup_dcu_lfd_bup_state_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.bup_state.ts_s = bup_dcu_lfd_bup_state_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.bup_state.ts_ns = bup_dcu_lfd_bup_state_delayed_ts_ns;
                bup_dcu_lfd_bup_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.bup_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_bup_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_bup_state_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_bup_state_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_bup_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_bup_state_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_bup_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.bup_state.msg), sizeof(bup_drv_state_msg_t));
    in_bup_dcu_lfd_bup_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_cmd_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lfd_cmd_ans_lock_cnt = 0;
static command_answer_msg_t* in_bup_dcu_lfd_cmd_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_cmd_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_cmd_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_cmd_ans_updated = 0;
static uint32_t  in_bup_dcu_lfd_cmd_ans_total = 0;
static uint32_t  in_bup_dcu_lfd_cmd_ans_miss = 0;
static uint16_t  in_bup_dcu_lfd_cmd_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_cmd_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_cmd_ans_lock_cnt < 255)
        {
            in_bup_dcu_lfd_cmd_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_cmd_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_cmd_ans_lock_cnt == 1) && (in_bup_dcu_lfd_cmd_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.cmd_ans.msg);
                mj_handle.in.bup_dcu_lfd.cmd_ans.msg = (command_answer_msg_t*)(in_bup_dcu_lfd_cmd_ans_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.cmd_ans.ts_s = bup_dcu_lfd_cmd_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.cmd_ans.ts_ns = bup_dcu_lfd_cmd_ans_delayed_ts_ns;
                bup_dcu_lfd_cmd_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.cmd_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_cmd_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_cmd_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_cmd_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_cmd_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_cmd_ans_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_cmd_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.cmd_ans.msg), sizeof(command_answer_msg_t));
    in_bup_dcu_lfd_cmd_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_dbg_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_lfd_dbg_lock_cnt = 0;
static dbg_data_msg_t* in_bup_dcu_lfd_dbg_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_dbg_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_dbg_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_dbg_updated = 0;
static uint32_t  in_bup_dcu_lfd_dbg_total = 0;
static uint32_t  in_bup_dcu_lfd_dbg_miss = 0;
static uint16_t  in_bup_dcu_lfd_dbg_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_dbg_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_dbg_lock_cnt < 255)
        {
            in_bup_dcu_lfd_dbg_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_dbg_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_dbg_lock_cnt == 1) && (in_bup_dcu_lfd_dbg_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.dbg.msg);
                mj_handle.in.bup_dcu_lfd.dbg.msg = (dbg_data_msg_t*)(in_bup_dcu_lfd_dbg_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.dbg.ts_s = bup_dcu_lfd_dbg_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.dbg.ts_ns = bup_dcu_lfd_dbg_delayed_ts_ns;
                bup_dcu_lfd_dbg_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.dbg.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_dbg_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_dbg_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_dbg_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_dbg_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_dbg_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_dbg_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.dbg.msg), sizeof(dbg_data_msg_t));
    in_bup_dcu_lfd_dbg_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_dcu_tel_rx_tick = UINT32_MAX - 4.0;
static uint8_t  in_bup_dcu_lfd_dcu_tel_lock_cnt = 0;
static dcu_telemetry_msg_t* in_bup_dcu_lfd_dcu_tel_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_dcu_tel_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_dcu_tel_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_dcu_tel_updated = 0;
static uint32_t  in_bup_dcu_lfd_dcu_tel_total = 0;
static uint32_t  in_bup_dcu_lfd_dcu_tel_miss = 0;
static uint16_t  in_bup_dcu_lfd_dcu_tel_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_dcu_tel_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_dcu_tel_lock_cnt < 255)
        {
            in_bup_dcu_lfd_dcu_tel_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_dcu_tel_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_dcu_tel_lock_cnt == 1) && (in_bup_dcu_lfd_dcu_tel_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.dcu_tel.msg);
                mj_handle.in.bup_dcu_lfd.dcu_tel.msg = (dcu_telemetry_msg_t*)(in_bup_dcu_lfd_dcu_tel_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.dcu_tel.ts_s = bup_dcu_lfd_dcu_tel_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.dcu_tel.ts_ns = bup_dcu_lfd_dcu_tel_delayed_ts_ns;
                bup_dcu_lfd_dcu_tel_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.dcu_tel.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_dcu_tel_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_dcu_tel_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_dcu_tel_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_dcu_tel_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_dcu_tel_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_dcu_tel_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.dcu_tel.msg), sizeof(dcu_telemetry_msg_t));
    in_bup_dcu_lfd_dcu_tel_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_drive_master_ctrl_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_lfd_drive_master_ctrl_lock_cnt = 0;
static drive_master_ctrl_msg_t* in_bup_dcu_lfd_drive_master_ctrl_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_drive_master_ctrl_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_drive_master_ctrl_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_drive_master_ctrl_updated = 0;
static uint32_t  in_bup_dcu_lfd_drive_master_ctrl_total = 0;
static uint32_t  in_bup_dcu_lfd_drive_master_ctrl_miss = 0;
static uint16_t  in_bup_dcu_lfd_drive_master_ctrl_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_drive_master_ctrl_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_drive_master_ctrl_lock_cnt < 255)
        {
            in_bup_dcu_lfd_drive_master_ctrl_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_drive_master_ctrl_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_drive_master_ctrl_lock_cnt == 1) && (in_bup_dcu_lfd_drive_master_ctrl_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg);
                mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t*)(in_bup_dcu_lfd_drive_master_ctrl_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.drive_master_ctrl.ts_s = bup_dcu_lfd_drive_master_ctrl_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.drive_master_ctrl.ts_ns = bup_dcu_lfd_drive_master_ctrl_delayed_ts_ns;
                bup_dcu_lfd_drive_master_ctrl_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_drive_master_ctrl_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_drive_master_ctrl_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_drive_master_ctrl_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_drive_master_ctrl_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_drive_master_ctrl_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_drive_master_ctrl_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg), sizeof(drive_master_ctrl_msg_t));
    in_bup_dcu_lfd_drive_master_ctrl_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_drive_slave_fb_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_lfd_drive_slave_fb_lock_cnt = 0;
static drive_slave_fb_msg_t* in_bup_dcu_lfd_drive_slave_fb_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_drive_slave_fb_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_drive_slave_fb_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_drive_slave_fb_updated = 0;
static uint32_t  in_bup_dcu_lfd_drive_slave_fb_total = 0;
static uint32_t  in_bup_dcu_lfd_drive_slave_fb_miss = 0;
static uint16_t  in_bup_dcu_lfd_drive_slave_fb_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_drive_slave_fb_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_drive_slave_fb_lock_cnt < 255)
        {
            in_bup_dcu_lfd_drive_slave_fb_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_drive_slave_fb_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_drive_slave_fb_lock_cnt == 1) && (in_bup_dcu_lfd_drive_slave_fb_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg);
                mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg = (drive_slave_fb_msg_t*)(in_bup_dcu_lfd_drive_slave_fb_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.drive_slave_fb.ts_s = bup_dcu_lfd_drive_slave_fb_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.drive_slave_fb.ts_ns = bup_dcu_lfd_drive_slave_fb_delayed_ts_ns;
                bup_dcu_lfd_drive_slave_fb_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.drive_slave_fb.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_drive_slave_fb_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_drive_slave_fb_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_drive_slave_fb_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_drive_slave_fb_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_drive_slave_fb_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_drive_slave_fb_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg), sizeof(drive_slave_fb_msg_t));
    in_bup_dcu_lfd_drive_slave_fb_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_formular_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lfd_formular_lock_cnt = 0;
static formular_info_msg_t* in_bup_dcu_lfd_formular_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_formular_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_formular_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_formular_updated = 0;
static uint32_t  in_bup_dcu_lfd_formular_total = 0;
static uint32_t  in_bup_dcu_lfd_formular_miss = 0;
static uint16_t  in_bup_dcu_lfd_formular_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_formular_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_formular_lock_cnt < 255)
        {
            in_bup_dcu_lfd_formular_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_formular_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_formular_lock_cnt == 1) && (in_bup_dcu_lfd_formular_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.formular.msg);
                mj_handle.in.bup_dcu_lfd.formular.msg = (formular_info_msg_t*)(in_bup_dcu_lfd_formular_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.formular.ts_s = bup_dcu_lfd_formular_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.formular.ts_ns = bup_dcu_lfd_formular_delayed_ts_ns;
                bup_dcu_lfd_formular_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.formular.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_formular_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_formular_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_formular_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_formular_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_formular_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_formular_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.formular.msg), sizeof(formular_info_msg_t));
    in_bup_dcu_lfd_formular_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_msg_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lfd_msg_ans_lock_cnt = 0;
static msg_answer_msg_t* in_bup_dcu_lfd_msg_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_msg_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_msg_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_msg_ans_updated = 0;
static uint32_t  in_bup_dcu_lfd_msg_ans_total = 0;
static uint32_t  in_bup_dcu_lfd_msg_ans_miss = 0;
static uint16_t  in_bup_dcu_lfd_msg_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_msg_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_msg_ans_lock_cnt < 255)
        {
            in_bup_dcu_lfd_msg_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_msg_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_msg_ans_lock_cnt == 1) && (in_bup_dcu_lfd_msg_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.msg_ans.msg);
                mj_handle.in.bup_dcu_lfd.msg_ans.msg = (msg_answer_msg_t*)(in_bup_dcu_lfd_msg_ans_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.msg_ans.ts_s = bup_dcu_lfd_msg_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.msg_ans.ts_ns = bup_dcu_lfd_msg_ans_delayed_ts_ns;
                bup_dcu_lfd_msg_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.msg_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_msg_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_msg_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_msg_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_msg_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_msg_ans_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_msg_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.msg_ans.msg), sizeof(msg_answer_msg_t));
    in_bup_dcu_lfd_msg_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_prm_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lfd_prm_ans_lock_cnt = 0;
static parameter_answer_msg_t* in_bup_dcu_lfd_prm_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_prm_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_prm_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_prm_ans_updated = 0;
static uint32_t  in_bup_dcu_lfd_prm_ans_total = 0;
static uint32_t  in_bup_dcu_lfd_prm_ans_miss = 0;
static uint16_t  in_bup_dcu_lfd_prm_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_prm_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_prm_ans_lock_cnt < 255)
        {
            in_bup_dcu_lfd_prm_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_prm_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_prm_ans_lock_cnt == 1) && (in_bup_dcu_lfd_prm_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.prm_ans.msg);
                mj_handle.in.bup_dcu_lfd.prm_ans.msg = (parameter_answer_msg_t*)(in_bup_dcu_lfd_prm_ans_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.prm_ans.ts_s = bup_dcu_lfd_prm_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.prm_ans.ts_ns = bup_dcu_lfd_prm_ans_delayed_ts_ns;
                bup_dcu_lfd_prm_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.prm_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_prm_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_prm_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_prm_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_prm_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_prm_ans_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_prm_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.prm_ans.msg), sizeof(parameter_answer_msg_t));
    in_bup_dcu_lfd_prm_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lfd_ptp_state_rx_tick = UINT32_MAX - 6001.0;
static uint8_t  in_bup_dcu_lfd_ptp_state_lock_cnt = 0;
static ptp_info_msg_t* in_bup_dcu_lfd_ptp_state_delayed_ptr = NULL;
static uint32_t bup_dcu_lfd_ptp_state_delayed_ts_s = 0;
static uint32_t bup_dcu_lfd_ptp_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lfd_ptp_state_updated = 0;
static uint32_t  in_bup_dcu_lfd_ptp_state_total = 0;
static uint32_t  in_bup_dcu_lfd_ptp_state_miss = 0;
static uint16_t  in_bup_dcu_lfd_ptp_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lfd_ptp_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lfd_ptp_state_lock_cnt < 255)
        {
            in_bup_dcu_lfd_ptp_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lfd_ptp_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_lfd_ptp_state_lock_cnt == 1) && (in_bup_dcu_lfd_ptp_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lfd.ptp_state.msg);
                mj_handle.in.bup_dcu_lfd.ptp_state.msg = (ptp_info_msg_t*)(in_bup_dcu_lfd_ptp_state_delayed_ptr);
                mj_handle.in.bup_dcu_lfd.ptp_state.ts_s = bup_dcu_lfd_ptp_state_delayed_ts_s;
                mj_handle.in.bup_dcu_lfd.ptp_state.ts_ns = bup_dcu_lfd_ptp_state_delayed_ts_ns;
                bup_dcu_lfd_ptp_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_lfd.ptp_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lfd_ptp_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lfd_ptp_state_delayed_ptr = NULL;
            }
            in_bup_dcu_lfd_ptp_state_lock_cnt--;
        }
    }
    return in_bup_dcu_lfd_ptp_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lfd_ptp_state_copy_fcn(void *dst)
{
    in_bup_dcu_lfd_ptp_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lfd.ptp_state.msg), sizeof(ptp_info_msg_t));
    in_bup_dcu_lfd_ptp_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_bup_state_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lrd_bup_state_lock_cnt = 0;
static bup_drv_state_msg_t* in_bup_dcu_lrd_bup_state_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_bup_state_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_bup_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_bup_state_updated = 0;
static uint32_t  in_bup_dcu_lrd_bup_state_total = 0;
static uint32_t  in_bup_dcu_lrd_bup_state_miss = 0;
static uint16_t  in_bup_dcu_lrd_bup_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_bup_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_bup_state_lock_cnt < 255)
        {
            in_bup_dcu_lrd_bup_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_bup_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_bup_state_lock_cnt == 1) && (in_bup_dcu_lrd_bup_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.bup_state.msg);
                mj_handle.in.bup_dcu_lrd.bup_state.msg = (bup_drv_state_msg_t*)(in_bup_dcu_lrd_bup_state_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.bup_state.ts_s = bup_dcu_lrd_bup_state_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.bup_state.ts_ns = bup_dcu_lrd_bup_state_delayed_ts_ns;
                bup_dcu_lrd_bup_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.bup_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_bup_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_bup_state_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_bup_state_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_bup_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_bup_state_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_bup_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.bup_state.msg), sizeof(bup_drv_state_msg_t));
    in_bup_dcu_lrd_bup_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_cmd_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lrd_cmd_ans_lock_cnt = 0;
static command_answer_msg_t* in_bup_dcu_lrd_cmd_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_cmd_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_cmd_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_cmd_ans_updated = 0;
static uint32_t  in_bup_dcu_lrd_cmd_ans_total = 0;
static uint32_t  in_bup_dcu_lrd_cmd_ans_miss = 0;
static uint16_t  in_bup_dcu_lrd_cmd_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_cmd_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_cmd_ans_lock_cnt < 255)
        {
            in_bup_dcu_lrd_cmd_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_cmd_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_cmd_ans_lock_cnt == 1) && (in_bup_dcu_lrd_cmd_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.cmd_ans.msg);
                mj_handle.in.bup_dcu_lrd.cmd_ans.msg = (command_answer_msg_t*)(in_bup_dcu_lrd_cmd_ans_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.cmd_ans.ts_s = bup_dcu_lrd_cmd_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.cmd_ans.ts_ns = bup_dcu_lrd_cmd_ans_delayed_ts_ns;
                bup_dcu_lrd_cmd_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.cmd_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_cmd_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_cmd_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_cmd_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_cmd_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_cmd_ans_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_cmd_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.cmd_ans.msg), sizeof(command_answer_msg_t));
    in_bup_dcu_lrd_cmd_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_dbg_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_lrd_dbg_lock_cnt = 0;
static dbg_data_msg_t* in_bup_dcu_lrd_dbg_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_dbg_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_dbg_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_dbg_updated = 0;
static uint32_t  in_bup_dcu_lrd_dbg_total = 0;
static uint32_t  in_bup_dcu_lrd_dbg_miss = 0;
static uint16_t  in_bup_dcu_lrd_dbg_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_dbg_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_dbg_lock_cnt < 255)
        {
            in_bup_dcu_lrd_dbg_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_dbg_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_dbg_lock_cnt == 1) && (in_bup_dcu_lrd_dbg_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.dbg.msg);
                mj_handle.in.bup_dcu_lrd.dbg.msg = (dbg_data_msg_t*)(in_bup_dcu_lrd_dbg_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.dbg.ts_s = bup_dcu_lrd_dbg_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.dbg.ts_ns = bup_dcu_lrd_dbg_delayed_ts_ns;
                bup_dcu_lrd_dbg_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.dbg.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_dbg_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_dbg_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_dbg_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_dbg_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_dbg_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_dbg_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.dbg.msg), sizeof(dbg_data_msg_t));
    in_bup_dcu_lrd_dbg_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_dcu_tel_rx_tick = UINT32_MAX - 4.0;
static uint8_t  in_bup_dcu_lrd_dcu_tel_lock_cnt = 0;
static dcu_telemetry_msg_t* in_bup_dcu_lrd_dcu_tel_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_dcu_tel_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_dcu_tel_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_dcu_tel_updated = 0;
static uint32_t  in_bup_dcu_lrd_dcu_tel_total = 0;
static uint32_t  in_bup_dcu_lrd_dcu_tel_miss = 0;
static uint16_t  in_bup_dcu_lrd_dcu_tel_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_dcu_tel_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_dcu_tel_lock_cnt < 255)
        {
            in_bup_dcu_lrd_dcu_tel_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_dcu_tel_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_dcu_tel_lock_cnt == 1) && (in_bup_dcu_lrd_dcu_tel_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.dcu_tel.msg);
                mj_handle.in.bup_dcu_lrd.dcu_tel.msg = (dcu_telemetry_msg_t*)(in_bup_dcu_lrd_dcu_tel_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.dcu_tel.ts_s = bup_dcu_lrd_dcu_tel_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.dcu_tel.ts_ns = bup_dcu_lrd_dcu_tel_delayed_ts_ns;
                bup_dcu_lrd_dcu_tel_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.dcu_tel.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_dcu_tel_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_dcu_tel_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_dcu_tel_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_dcu_tel_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_dcu_tel_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_dcu_tel_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.dcu_tel.msg), sizeof(dcu_telemetry_msg_t));
    in_bup_dcu_lrd_dcu_tel_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_drive_master_ctrl_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_lrd_drive_master_ctrl_lock_cnt = 0;
static drive_master_ctrl_msg_t* in_bup_dcu_lrd_drive_master_ctrl_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_drive_master_ctrl_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_drive_master_ctrl_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_drive_master_ctrl_updated = 0;
static uint32_t  in_bup_dcu_lrd_drive_master_ctrl_total = 0;
static uint32_t  in_bup_dcu_lrd_drive_master_ctrl_miss = 0;
static uint16_t  in_bup_dcu_lrd_drive_master_ctrl_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_drive_master_ctrl_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_drive_master_ctrl_lock_cnt < 255)
        {
            in_bup_dcu_lrd_drive_master_ctrl_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_drive_master_ctrl_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_drive_master_ctrl_lock_cnt == 1) && (in_bup_dcu_lrd_drive_master_ctrl_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg);
                mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t*)(in_bup_dcu_lrd_drive_master_ctrl_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.drive_master_ctrl.ts_s = bup_dcu_lrd_drive_master_ctrl_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.drive_master_ctrl.ts_ns = bup_dcu_lrd_drive_master_ctrl_delayed_ts_ns;
                bup_dcu_lrd_drive_master_ctrl_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_drive_master_ctrl_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_drive_master_ctrl_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_drive_master_ctrl_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_drive_master_ctrl_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_drive_master_ctrl_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_drive_master_ctrl_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg), sizeof(drive_master_ctrl_msg_t));
    in_bup_dcu_lrd_drive_master_ctrl_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_drive_slave_fb_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_lrd_drive_slave_fb_lock_cnt = 0;
static drive_slave_fb_msg_t* in_bup_dcu_lrd_drive_slave_fb_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_drive_slave_fb_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_drive_slave_fb_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_drive_slave_fb_updated = 0;
static uint32_t  in_bup_dcu_lrd_drive_slave_fb_total = 0;
static uint32_t  in_bup_dcu_lrd_drive_slave_fb_miss = 0;
static uint16_t  in_bup_dcu_lrd_drive_slave_fb_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_drive_slave_fb_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_drive_slave_fb_lock_cnt < 255)
        {
            in_bup_dcu_lrd_drive_slave_fb_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_drive_slave_fb_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_drive_slave_fb_lock_cnt == 1) && (in_bup_dcu_lrd_drive_slave_fb_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg);
                mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg = (drive_slave_fb_msg_t*)(in_bup_dcu_lrd_drive_slave_fb_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.drive_slave_fb.ts_s = bup_dcu_lrd_drive_slave_fb_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.drive_slave_fb.ts_ns = bup_dcu_lrd_drive_slave_fb_delayed_ts_ns;
                bup_dcu_lrd_drive_slave_fb_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.drive_slave_fb.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_drive_slave_fb_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_drive_slave_fb_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_drive_slave_fb_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_drive_slave_fb_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_drive_slave_fb_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_drive_slave_fb_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg), sizeof(drive_slave_fb_msg_t));
    in_bup_dcu_lrd_drive_slave_fb_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_formular_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lrd_formular_lock_cnt = 0;
static formular_info_msg_t* in_bup_dcu_lrd_formular_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_formular_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_formular_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_formular_updated = 0;
static uint32_t  in_bup_dcu_lrd_formular_total = 0;
static uint32_t  in_bup_dcu_lrd_formular_miss = 0;
static uint16_t  in_bup_dcu_lrd_formular_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_formular_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_formular_lock_cnt < 255)
        {
            in_bup_dcu_lrd_formular_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_formular_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_formular_lock_cnt == 1) && (in_bup_dcu_lrd_formular_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.formular.msg);
                mj_handle.in.bup_dcu_lrd.formular.msg = (formular_info_msg_t*)(in_bup_dcu_lrd_formular_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.formular.ts_s = bup_dcu_lrd_formular_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.formular.ts_ns = bup_dcu_lrd_formular_delayed_ts_ns;
                bup_dcu_lrd_formular_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.formular.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_formular_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_formular_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_formular_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_formular_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_formular_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_formular_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.formular.msg), sizeof(formular_info_msg_t));
    in_bup_dcu_lrd_formular_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_msg_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lrd_msg_ans_lock_cnt = 0;
static msg_answer_msg_t* in_bup_dcu_lrd_msg_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_msg_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_msg_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_msg_ans_updated = 0;
static uint32_t  in_bup_dcu_lrd_msg_ans_total = 0;
static uint32_t  in_bup_dcu_lrd_msg_ans_miss = 0;
static uint16_t  in_bup_dcu_lrd_msg_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_msg_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_msg_ans_lock_cnt < 255)
        {
            in_bup_dcu_lrd_msg_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_msg_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_msg_ans_lock_cnt == 1) && (in_bup_dcu_lrd_msg_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.msg_ans.msg);
                mj_handle.in.bup_dcu_lrd.msg_ans.msg = (msg_answer_msg_t*)(in_bup_dcu_lrd_msg_ans_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.msg_ans.ts_s = bup_dcu_lrd_msg_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.msg_ans.ts_ns = bup_dcu_lrd_msg_ans_delayed_ts_ns;
                bup_dcu_lrd_msg_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.msg_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_msg_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_msg_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_msg_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_msg_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_msg_ans_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_msg_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.msg_ans.msg), sizeof(msg_answer_msg_t));
    in_bup_dcu_lrd_msg_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_prm_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lrd_prm_ans_lock_cnt = 0;
static parameter_answer_msg_t* in_bup_dcu_lrd_prm_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_prm_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_prm_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_prm_ans_updated = 0;
static uint32_t  in_bup_dcu_lrd_prm_ans_total = 0;
static uint32_t  in_bup_dcu_lrd_prm_ans_miss = 0;
static uint16_t  in_bup_dcu_lrd_prm_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_prm_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_prm_ans_lock_cnt < 255)
        {
            in_bup_dcu_lrd_prm_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_prm_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_prm_ans_lock_cnt == 1) && (in_bup_dcu_lrd_prm_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.prm_ans.msg);
                mj_handle.in.bup_dcu_lrd.prm_ans.msg = (parameter_answer_msg_t*)(in_bup_dcu_lrd_prm_ans_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.prm_ans.ts_s = bup_dcu_lrd_prm_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.prm_ans.ts_ns = bup_dcu_lrd_prm_ans_delayed_ts_ns;
                bup_dcu_lrd_prm_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.prm_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_prm_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_prm_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_prm_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_prm_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_prm_ans_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_prm_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.prm_ans.msg), sizeof(parameter_answer_msg_t));
    in_bup_dcu_lrd_prm_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lrd_ptp_state_rx_tick = UINT32_MAX - 6001.0;
static uint8_t  in_bup_dcu_lrd_ptp_state_lock_cnt = 0;
static ptp_info_msg_t* in_bup_dcu_lrd_ptp_state_delayed_ptr = NULL;
static uint32_t bup_dcu_lrd_ptp_state_delayed_ts_s = 0;
static uint32_t bup_dcu_lrd_ptp_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lrd_ptp_state_updated = 0;
static uint32_t  in_bup_dcu_lrd_ptp_state_total = 0;
static uint32_t  in_bup_dcu_lrd_ptp_state_miss = 0;
static uint16_t  in_bup_dcu_lrd_ptp_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lrd_ptp_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lrd_ptp_state_lock_cnt < 255)
        {
            in_bup_dcu_lrd_ptp_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lrd_ptp_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_lrd_ptp_state_lock_cnt == 1) && (in_bup_dcu_lrd_ptp_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lrd.ptp_state.msg);
                mj_handle.in.bup_dcu_lrd.ptp_state.msg = (ptp_info_msg_t*)(in_bup_dcu_lrd_ptp_state_delayed_ptr);
                mj_handle.in.bup_dcu_lrd.ptp_state.ts_s = bup_dcu_lrd_ptp_state_delayed_ts_s;
                mj_handle.in.bup_dcu_lrd.ptp_state.ts_ns = bup_dcu_lrd_ptp_state_delayed_ts_ns;
                bup_dcu_lrd_ptp_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_lrd.ptp_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lrd_ptp_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lrd_ptp_state_delayed_ptr = NULL;
            }
            in_bup_dcu_lrd_ptp_state_lock_cnt--;
        }
    }
    return in_bup_dcu_lrd_ptp_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lrd_ptp_state_copy_fcn(void *dst)
{
    in_bup_dcu_lrd_ptp_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lrd.ptp_state.msg), sizeof(ptp_info_msg_t));
    in_bup_dcu_lrd_ptp_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_bup_state_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lst_bup_state_lock_cnt = 0;
static bup_drv_state_msg_t* in_bup_dcu_lst_bup_state_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_bup_state_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_bup_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_bup_state_updated = 0;
static uint32_t  in_bup_dcu_lst_bup_state_total = 0;
static uint32_t  in_bup_dcu_lst_bup_state_miss = 0;
static uint16_t  in_bup_dcu_lst_bup_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_bup_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_bup_state_lock_cnt < 255)
        {
            in_bup_dcu_lst_bup_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_bup_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_bup_state_lock_cnt == 1) && (in_bup_dcu_lst_bup_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.bup_state.msg);
                mj_handle.in.bup_dcu_lst.bup_state.msg = (bup_drv_state_msg_t*)(in_bup_dcu_lst_bup_state_delayed_ptr);
                mj_handle.in.bup_dcu_lst.bup_state.ts_s = bup_dcu_lst_bup_state_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.bup_state.ts_ns = bup_dcu_lst_bup_state_delayed_ts_ns;
                bup_dcu_lst_bup_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.bup_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_bup_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_bup_state_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_bup_state_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_bup_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_bup_state_copy_fcn(void *dst)
{
    in_bup_dcu_lst_bup_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.bup_state.msg), sizeof(bup_drv_state_msg_t));
    in_bup_dcu_lst_bup_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_cmd_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lst_cmd_ans_lock_cnt = 0;
static command_answer_msg_t* in_bup_dcu_lst_cmd_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_cmd_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_cmd_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_cmd_ans_updated = 0;
static uint32_t  in_bup_dcu_lst_cmd_ans_total = 0;
static uint32_t  in_bup_dcu_lst_cmd_ans_miss = 0;
static uint16_t  in_bup_dcu_lst_cmd_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_cmd_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_cmd_ans_lock_cnt < 255)
        {
            in_bup_dcu_lst_cmd_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_cmd_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_cmd_ans_lock_cnt == 1) && (in_bup_dcu_lst_cmd_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.cmd_ans.msg);
                mj_handle.in.bup_dcu_lst.cmd_ans.msg = (command_answer_msg_t*)(in_bup_dcu_lst_cmd_ans_delayed_ptr);
                mj_handle.in.bup_dcu_lst.cmd_ans.ts_s = bup_dcu_lst_cmd_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.cmd_ans.ts_ns = bup_dcu_lst_cmd_ans_delayed_ts_ns;
                bup_dcu_lst_cmd_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.cmd_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_cmd_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_cmd_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_cmd_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_cmd_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_cmd_ans_copy_fcn(void *dst)
{
    in_bup_dcu_lst_cmd_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.cmd_ans.msg), sizeof(command_answer_msg_t));
    in_bup_dcu_lst_cmd_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_dbg_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_lst_dbg_lock_cnt = 0;
static dbg_data_msg_t* in_bup_dcu_lst_dbg_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_dbg_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_dbg_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_dbg_updated = 0;
static uint32_t  in_bup_dcu_lst_dbg_total = 0;
static uint32_t  in_bup_dcu_lst_dbg_miss = 0;
static uint16_t  in_bup_dcu_lst_dbg_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_dbg_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_dbg_lock_cnt < 255)
        {
            in_bup_dcu_lst_dbg_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_dbg_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_dbg_lock_cnt == 1) && (in_bup_dcu_lst_dbg_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.dbg.msg);
                mj_handle.in.bup_dcu_lst.dbg.msg = (dbg_data_msg_t*)(in_bup_dcu_lst_dbg_delayed_ptr);
                mj_handle.in.bup_dcu_lst.dbg.ts_s = bup_dcu_lst_dbg_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.dbg.ts_ns = bup_dcu_lst_dbg_delayed_ts_ns;
                bup_dcu_lst_dbg_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.dbg.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_dbg_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_dbg_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_dbg_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_dbg_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_dbg_copy_fcn(void *dst)
{
    in_bup_dcu_lst_dbg_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.dbg.msg), sizeof(dbg_data_msg_t));
    in_bup_dcu_lst_dbg_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_dcu_tel_rx_tick = UINT32_MAX - 4.0;
static uint8_t  in_bup_dcu_lst_dcu_tel_lock_cnt = 0;
static dcu_telemetry_msg_t* in_bup_dcu_lst_dcu_tel_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_dcu_tel_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_dcu_tel_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_dcu_tel_updated = 0;
static uint32_t  in_bup_dcu_lst_dcu_tel_total = 0;
static uint32_t  in_bup_dcu_lst_dcu_tel_miss = 0;
static uint16_t  in_bup_dcu_lst_dcu_tel_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_dcu_tel_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_dcu_tel_lock_cnt < 255)
        {
            in_bup_dcu_lst_dcu_tel_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_dcu_tel_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_dcu_tel_lock_cnt == 1) && (in_bup_dcu_lst_dcu_tel_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.dcu_tel.msg);
                mj_handle.in.bup_dcu_lst.dcu_tel.msg = (dcu_telemetry_msg_t*)(in_bup_dcu_lst_dcu_tel_delayed_ptr);
                mj_handle.in.bup_dcu_lst.dcu_tel.ts_s = bup_dcu_lst_dcu_tel_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.dcu_tel.ts_ns = bup_dcu_lst_dcu_tel_delayed_ts_ns;
                bup_dcu_lst_dcu_tel_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.dcu_tel.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_dcu_tel_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_dcu_tel_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_dcu_tel_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_dcu_tel_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_dcu_tel_copy_fcn(void *dst)
{
    in_bup_dcu_lst_dcu_tel_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.dcu_tel.msg), sizeof(dcu_telemetry_msg_t));
    in_bup_dcu_lst_dcu_tel_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_drive_master_ctrl_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_lst_drive_master_ctrl_lock_cnt = 0;
static drive_master_ctrl_msg_t* in_bup_dcu_lst_drive_master_ctrl_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_drive_master_ctrl_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_drive_master_ctrl_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_drive_master_ctrl_updated = 0;
static uint32_t  in_bup_dcu_lst_drive_master_ctrl_total = 0;
static uint32_t  in_bup_dcu_lst_drive_master_ctrl_miss = 0;
static uint16_t  in_bup_dcu_lst_drive_master_ctrl_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_drive_master_ctrl_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_drive_master_ctrl_lock_cnt < 255)
        {
            in_bup_dcu_lst_drive_master_ctrl_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_drive_master_ctrl_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_drive_master_ctrl_lock_cnt == 1) && (in_bup_dcu_lst_drive_master_ctrl_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg);
                mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg = (drive_master_ctrl_msg_t*)(in_bup_dcu_lst_drive_master_ctrl_delayed_ptr);
                mj_handle.in.bup_dcu_lst.drive_master_ctrl.ts_s = bup_dcu_lst_drive_master_ctrl_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.drive_master_ctrl.ts_ns = bup_dcu_lst_drive_master_ctrl_delayed_ts_ns;
                bup_dcu_lst_drive_master_ctrl_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_drive_master_ctrl_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_drive_master_ctrl_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_drive_master_ctrl_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_drive_master_ctrl_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_drive_master_ctrl_copy_fcn(void *dst)
{
    in_bup_dcu_lst_drive_master_ctrl_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg), sizeof(drive_master_ctrl_msg_t));
    in_bup_dcu_lst_drive_master_ctrl_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_drive_slave_fb_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_lst_drive_slave_fb_lock_cnt = 0;
static drive_slave_fb_msg_t* in_bup_dcu_lst_drive_slave_fb_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_drive_slave_fb_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_drive_slave_fb_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_drive_slave_fb_updated = 0;
static uint32_t  in_bup_dcu_lst_drive_slave_fb_total = 0;
static uint32_t  in_bup_dcu_lst_drive_slave_fb_miss = 0;
static uint16_t  in_bup_dcu_lst_drive_slave_fb_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_drive_slave_fb_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_drive_slave_fb_lock_cnt < 255)
        {
            in_bup_dcu_lst_drive_slave_fb_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_drive_slave_fb_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_drive_slave_fb_lock_cnt == 1) && (in_bup_dcu_lst_drive_slave_fb_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.drive_slave_fb.msg);
                mj_handle.in.bup_dcu_lst.drive_slave_fb.msg = (drive_slave_fb_msg_t*)(in_bup_dcu_lst_drive_slave_fb_delayed_ptr);
                mj_handle.in.bup_dcu_lst.drive_slave_fb.ts_s = bup_dcu_lst_drive_slave_fb_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.drive_slave_fb.ts_ns = bup_dcu_lst_drive_slave_fb_delayed_ts_ns;
                bup_dcu_lst_drive_slave_fb_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.drive_slave_fb.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_drive_slave_fb_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_drive_slave_fb_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_drive_slave_fb_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_drive_slave_fb_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_drive_slave_fb_copy_fcn(void *dst)
{
    in_bup_dcu_lst_drive_slave_fb_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.drive_slave_fb.msg), sizeof(drive_slave_fb_msg_t));
    in_bup_dcu_lst_drive_slave_fb_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_formular_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lst_formular_lock_cnt = 0;
static formular_info_msg_t* in_bup_dcu_lst_formular_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_formular_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_formular_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_formular_updated = 0;
static uint32_t  in_bup_dcu_lst_formular_total = 0;
static uint32_t  in_bup_dcu_lst_formular_miss = 0;
static uint16_t  in_bup_dcu_lst_formular_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_formular_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_formular_lock_cnt < 255)
        {
            in_bup_dcu_lst_formular_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_formular_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_formular_lock_cnt == 1) && (in_bup_dcu_lst_formular_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.formular.msg);
                mj_handle.in.bup_dcu_lst.formular.msg = (formular_info_msg_t*)(in_bup_dcu_lst_formular_delayed_ptr);
                mj_handle.in.bup_dcu_lst.formular.ts_s = bup_dcu_lst_formular_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.formular.ts_ns = bup_dcu_lst_formular_delayed_ts_ns;
                bup_dcu_lst_formular_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.formular.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_formular_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_formular_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_formular_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_formular_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_formular_copy_fcn(void *dst)
{
    in_bup_dcu_lst_formular_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.formular.msg), sizeof(formular_info_msg_t));
    in_bup_dcu_lst_formular_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_msg_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lst_msg_ans_lock_cnt = 0;
static msg_answer_msg_t* in_bup_dcu_lst_msg_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_msg_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_msg_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_msg_ans_updated = 0;
static uint32_t  in_bup_dcu_lst_msg_ans_total = 0;
static uint32_t  in_bup_dcu_lst_msg_ans_miss = 0;
static uint16_t  in_bup_dcu_lst_msg_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_msg_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_msg_ans_lock_cnt < 255)
        {
            in_bup_dcu_lst_msg_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_msg_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_msg_ans_lock_cnt == 1) && (in_bup_dcu_lst_msg_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.msg_ans.msg);
                mj_handle.in.bup_dcu_lst.msg_ans.msg = (msg_answer_msg_t*)(in_bup_dcu_lst_msg_ans_delayed_ptr);
                mj_handle.in.bup_dcu_lst.msg_ans.ts_s = bup_dcu_lst_msg_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.msg_ans.ts_ns = bup_dcu_lst_msg_ans_delayed_ts_ns;
                bup_dcu_lst_msg_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.msg_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_msg_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_msg_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_msg_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_msg_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_msg_ans_copy_fcn(void *dst)
{
    in_bup_dcu_lst_msg_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.msg_ans.msg), sizeof(msg_answer_msg_t));
    in_bup_dcu_lst_msg_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_prm_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_lst_prm_ans_lock_cnt = 0;
static parameter_answer_msg_t* in_bup_dcu_lst_prm_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_prm_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_prm_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_prm_ans_updated = 0;
static uint32_t  in_bup_dcu_lst_prm_ans_total = 0;
static uint32_t  in_bup_dcu_lst_prm_ans_miss = 0;
static uint16_t  in_bup_dcu_lst_prm_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_prm_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_prm_ans_lock_cnt < 255)
        {
            in_bup_dcu_lst_prm_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_prm_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_prm_ans_lock_cnt == 1) && (in_bup_dcu_lst_prm_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.prm_ans.msg);
                mj_handle.in.bup_dcu_lst.prm_ans.msg = (parameter_answer_msg_t*)(in_bup_dcu_lst_prm_ans_delayed_ptr);
                mj_handle.in.bup_dcu_lst.prm_ans.ts_s = bup_dcu_lst_prm_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.prm_ans.ts_ns = bup_dcu_lst_prm_ans_delayed_ts_ns;
                bup_dcu_lst_prm_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.prm_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_prm_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_prm_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_prm_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_prm_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_prm_ans_copy_fcn(void *dst)
{
    in_bup_dcu_lst_prm_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.prm_ans.msg), sizeof(parameter_answer_msg_t));
    in_bup_dcu_lst_prm_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_lst_ptp_state_rx_tick = UINT32_MAX - 6001.0;
static uint8_t  in_bup_dcu_lst_ptp_state_lock_cnt = 0;
static ptp_info_msg_t* in_bup_dcu_lst_ptp_state_delayed_ptr = NULL;
static uint32_t bup_dcu_lst_ptp_state_delayed_ts_s = 0;
static uint32_t bup_dcu_lst_ptp_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_lst_ptp_state_updated = 0;
static uint32_t  in_bup_dcu_lst_ptp_state_total = 0;
static uint32_t  in_bup_dcu_lst_ptp_state_miss = 0;
static uint16_t  in_bup_dcu_lst_ptp_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_lst_ptp_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_lst_ptp_state_lock_cnt < 255)
        {
            in_bup_dcu_lst_ptp_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_lst_ptp_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_lst_ptp_state_lock_cnt == 1) && (in_bup_dcu_lst_ptp_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_lst.ptp_state.msg);
                mj_handle.in.bup_dcu_lst.ptp_state.msg = (ptp_info_msg_t*)(in_bup_dcu_lst_ptp_state_delayed_ptr);
                mj_handle.in.bup_dcu_lst.ptp_state.ts_s = bup_dcu_lst_ptp_state_delayed_ts_s;
                mj_handle.in.bup_dcu_lst.ptp_state.ts_ns = bup_dcu_lst_ptp_state_delayed_ts_ns;
                bup_dcu_lst_ptp_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_lst.ptp_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_lst_ptp_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_lst_ptp_state_delayed_ptr = NULL;
            }
            in_bup_dcu_lst_ptp_state_lock_cnt--;
        }
    }
    return in_bup_dcu_lst_ptp_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_lst_ptp_state_copy_fcn(void *dst)
{
    in_bup_dcu_lst_ptp_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_lst.ptp_state.msg), sizeof(ptp_info_msg_t));
    in_bup_dcu_lst_ptp_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_bup_state_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rfd_bup_state_lock_cnt = 0;
static bup_drv_state_msg_t* in_bup_dcu_rfd_bup_state_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_bup_state_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_bup_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_bup_state_updated = 0;
static uint32_t  in_bup_dcu_rfd_bup_state_total = 0;
static uint32_t  in_bup_dcu_rfd_bup_state_miss = 0;
static uint16_t  in_bup_dcu_rfd_bup_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_bup_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_bup_state_lock_cnt < 255)
        {
            in_bup_dcu_rfd_bup_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_bup_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_bup_state_lock_cnt == 1) && (in_bup_dcu_rfd_bup_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.bup_state.msg);
                mj_handle.in.bup_dcu_rfd.bup_state.msg = (bup_drv_state_msg_t*)(in_bup_dcu_rfd_bup_state_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.bup_state.ts_s = bup_dcu_rfd_bup_state_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.bup_state.ts_ns = bup_dcu_rfd_bup_state_delayed_ts_ns;
                bup_dcu_rfd_bup_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.bup_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_bup_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_bup_state_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_bup_state_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_bup_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_bup_state_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_bup_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.bup_state.msg), sizeof(bup_drv_state_msg_t));
    in_bup_dcu_rfd_bup_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_cmd_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rfd_cmd_ans_lock_cnt = 0;
static command_answer_msg_t* in_bup_dcu_rfd_cmd_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_cmd_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_cmd_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_cmd_ans_updated = 0;
static uint32_t  in_bup_dcu_rfd_cmd_ans_total = 0;
static uint32_t  in_bup_dcu_rfd_cmd_ans_miss = 0;
static uint16_t  in_bup_dcu_rfd_cmd_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_cmd_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_cmd_ans_lock_cnt < 255)
        {
            in_bup_dcu_rfd_cmd_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_cmd_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_cmd_ans_lock_cnt == 1) && (in_bup_dcu_rfd_cmd_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.cmd_ans.msg);
                mj_handle.in.bup_dcu_rfd.cmd_ans.msg = (command_answer_msg_t*)(in_bup_dcu_rfd_cmd_ans_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.cmd_ans.ts_s = bup_dcu_rfd_cmd_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.cmd_ans.ts_ns = bup_dcu_rfd_cmd_ans_delayed_ts_ns;
                bup_dcu_rfd_cmd_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.cmd_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_cmd_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_cmd_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_cmd_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_cmd_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_cmd_ans_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_cmd_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.cmd_ans.msg), sizeof(command_answer_msg_t));
    in_bup_dcu_rfd_cmd_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_dbg_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_rfd_dbg_lock_cnt = 0;
static dbg_data_msg_t* in_bup_dcu_rfd_dbg_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_dbg_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_dbg_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_dbg_updated = 0;
static uint32_t  in_bup_dcu_rfd_dbg_total = 0;
static uint32_t  in_bup_dcu_rfd_dbg_miss = 0;
static uint16_t  in_bup_dcu_rfd_dbg_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_dbg_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_dbg_lock_cnt < 255)
        {
            in_bup_dcu_rfd_dbg_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_dbg_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_dbg_lock_cnt == 1) && (in_bup_dcu_rfd_dbg_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.dbg.msg);
                mj_handle.in.bup_dcu_rfd.dbg.msg = (dbg_data_msg_t*)(in_bup_dcu_rfd_dbg_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.dbg.ts_s = bup_dcu_rfd_dbg_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.dbg.ts_ns = bup_dcu_rfd_dbg_delayed_ts_ns;
                bup_dcu_rfd_dbg_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.dbg.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_dbg_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_dbg_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_dbg_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_dbg_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_dbg_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_dbg_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.dbg.msg), sizeof(dbg_data_msg_t));
    in_bup_dcu_rfd_dbg_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_dcu_tel_rx_tick = UINT32_MAX - 4.0;
static uint8_t  in_bup_dcu_rfd_dcu_tel_lock_cnt = 0;
static dcu_telemetry_msg_t* in_bup_dcu_rfd_dcu_tel_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_dcu_tel_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_dcu_tel_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_dcu_tel_updated = 0;
static uint32_t  in_bup_dcu_rfd_dcu_tel_total = 0;
static uint32_t  in_bup_dcu_rfd_dcu_tel_miss = 0;
static uint16_t  in_bup_dcu_rfd_dcu_tel_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_dcu_tel_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_dcu_tel_lock_cnt < 255)
        {
            in_bup_dcu_rfd_dcu_tel_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_dcu_tel_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_dcu_tel_lock_cnt == 1) && (in_bup_dcu_rfd_dcu_tel_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.dcu_tel.msg);
                mj_handle.in.bup_dcu_rfd.dcu_tel.msg = (dcu_telemetry_msg_t*)(in_bup_dcu_rfd_dcu_tel_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.dcu_tel.ts_s = bup_dcu_rfd_dcu_tel_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.dcu_tel.ts_ns = bup_dcu_rfd_dcu_tel_delayed_ts_ns;
                bup_dcu_rfd_dcu_tel_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.dcu_tel.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_dcu_tel_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_dcu_tel_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_dcu_tel_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_dcu_tel_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_dcu_tel_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_dcu_tel_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.dcu_tel.msg), sizeof(dcu_telemetry_msg_t));
    in_bup_dcu_rfd_dcu_tel_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_drive_master_ctrl_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_rfd_drive_master_ctrl_lock_cnt = 0;
static drive_master_ctrl_msg_t* in_bup_dcu_rfd_drive_master_ctrl_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_drive_master_ctrl_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_drive_master_ctrl_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_drive_master_ctrl_updated = 0;
static uint32_t  in_bup_dcu_rfd_drive_master_ctrl_total = 0;
static uint32_t  in_bup_dcu_rfd_drive_master_ctrl_miss = 0;
static uint16_t  in_bup_dcu_rfd_drive_master_ctrl_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_drive_master_ctrl_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_drive_master_ctrl_lock_cnt < 255)
        {
            in_bup_dcu_rfd_drive_master_ctrl_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_drive_master_ctrl_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_drive_master_ctrl_lock_cnt == 1) && (in_bup_dcu_rfd_drive_master_ctrl_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg);
                mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t*)(in_bup_dcu_rfd_drive_master_ctrl_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.drive_master_ctrl.ts_s = bup_dcu_rfd_drive_master_ctrl_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.drive_master_ctrl.ts_ns = bup_dcu_rfd_drive_master_ctrl_delayed_ts_ns;
                bup_dcu_rfd_drive_master_ctrl_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_drive_master_ctrl_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_drive_master_ctrl_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_drive_master_ctrl_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_drive_master_ctrl_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_drive_master_ctrl_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_drive_master_ctrl_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg), sizeof(drive_master_ctrl_msg_t));
    in_bup_dcu_rfd_drive_master_ctrl_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_drive_slave_fb_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_rfd_drive_slave_fb_lock_cnt = 0;
static drive_slave_fb_msg_t* in_bup_dcu_rfd_drive_slave_fb_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_drive_slave_fb_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_drive_slave_fb_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_drive_slave_fb_updated = 0;
static uint32_t  in_bup_dcu_rfd_drive_slave_fb_total = 0;
static uint32_t  in_bup_dcu_rfd_drive_slave_fb_miss = 0;
static uint16_t  in_bup_dcu_rfd_drive_slave_fb_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_drive_slave_fb_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_drive_slave_fb_lock_cnt < 255)
        {
            in_bup_dcu_rfd_drive_slave_fb_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_drive_slave_fb_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_drive_slave_fb_lock_cnt == 1) && (in_bup_dcu_rfd_drive_slave_fb_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg);
                mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg = (drive_slave_fb_msg_t*)(in_bup_dcu_rfd_drive_slave_fb_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.drive_slave_fb.ts_s = bup_dcu_rfd_drive_slave_fb_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.drive_slave_fb.ts_ns = bup_dcu_rfd_drive_slave_fb_delayed_ts_ns;
                bup_dcu_rfd_drive_slave_fb_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.drive_slave_fb.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_drive_slave_fb_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_drive_slave_fb_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_drive_slave_fb_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_drive_slave_fb_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_drive_slave_fb_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_drive_slave_fb_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg), sizeof(drive_slave_fb_msg_t));
    in_bup_dcu_rfd_drive_slave_fb_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_formular_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rfd_formular_lock_cnt = 0;
static formular_info_msg_t* in_bup_dcu_rfd_formular_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_formular_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_formular_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_formular_updated = 0;
static uint32_t  in_bup_dcu_rfd_formular_total = 0;
static uint32_t  in_bup_dcu_rfd_formular_miss = 0;
static uint16_t  in_bup_dcu_rfd_formular_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_formular_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_formular_lock_cnt < 255)
        {
            in_bup_dcu_rfd_formular_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_formular_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_formular_lock_cnt == 1) && (in_bup_dcu_rfd_formular_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.formular.msg);
                mj_handle.in.bup_dcu_rfd.formular.msg = (formular_info_msg_t*)(in_bup_dcu_rfd_formular_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.formular.ts_s = bup_dcu_rfd_formular_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.formular.ts_ns = bup_dcu_rfd_formular_delayed_ts_ns;
                bup_dcu_rfd_formular_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.formular.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_formular_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_formular_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_formular_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_formular_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_formular_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_formular_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.formular.msg), sizeof(formular_info_msg_t));
    in_bup_dcu_rfd_formular_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_msg_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rfd_msg_ans_lock_cnt = 0;
static msg_answer_msg_t* in_bup_dcu_rfd_msg_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_msg_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_msg_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_msg_ans_updated = 0;
static uint32_t  in_bup_dcu_rfd_msg_ans_total = 0;
static uint32_t  in_bup_dcu_rfd_msg_ans_miss = 0;
static uint16_t  in_bup_dcu_rfd_msg_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_msg_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_msg_ans_lock_cnt < 255)
        {
            in_bup_dcu_rfd_msg_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_msg_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_msg_ans_lock_cnt == 1) && (in_bup_dcu_rfd_msg_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.msg_ans.msg);
                mj_handle.in.bup_dcu_rfd.msg_ans.msg = (msg_answer_msg_t*)(in_bup_dcu_rfd_msg_ans_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.msg_ans.ts_s = bup_dcu_rfd_msg_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.msg_ans.ts_ns = bup_dcu_rfd_msg_ans_delayed_ts_ns;
                bup_dcu_rfd_msg_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.msg_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_msg_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_msg_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_msg_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_msg_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_msg_ans_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_msg_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.msg_ans.msg), sizeof(msg_answer_msg_t));
    in_bup_dcu_rfd_msg_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_prm_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rfd_prm_ans_lock_cnt = 0;
static parameter_answer_msg_t* in_bup_dcu_rfd_prm_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_prm_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_prm_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_prm_ans_updated = 0;
static uint32_t  in_bup_dcu_rfd_prm_ans_total = 0;
static uint32_t  in_bup_dcu_rfd_prm_ans_miss = 0;
static uint16_t  in_bup_dcu_rfd_prm_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_prm_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_prm_ans_lock_cnt < 255)
        {
            in_bup_dcu_rfd_prm_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_prm_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_prm_ans_lock_cnt == 1) && (in_bup_dcu_rfd_prm_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.prm_ans.msg);
                mj_handle.in.bup_dcu_rfd.prm_ans.msg = (parameter_answer_msg_t*)(in_bup_dcu_rfd_prm_ans_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.prm_ans.ts_s = bup_dcu_rfd_prm_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.prm_ans.ts_ns = bup_dcu_rfd_prm_ans_delayed_ts_ns;
                bup_dcu_rfd_prm_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.prm_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_prm_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_prm_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_prm_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_prm_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_prm_ans_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_prm_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.prm_ans.msg), sizeof(parameter_answer_msg_t));
    in_bup_dcu_rfd_prm_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rfd_ptp_state_rx_tick = UINT32_MAX - 6001.0;
static uint8_t  in_bup_dcu_rfd_ptp_state_lock_cnt = 0;
static ptp_info_msg_t* in_bup_dcu_rfd_ptp_state_delayed_ptr = NULL;
static uint32_t bup_dcu_rfd_ptp_state_delayed_ts_s = 0;
static uint32_t bup_dcu_rfd_ptp_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rfd_ptp_state_updated = 0;
static uint32_t  in_bup_dcu_rfd_ptp_state_total = 0;
static uint32_t  in_bup_dcu_rfd_ptp_state_miss = 0;
static uint16_t  in_bup_dcu_rfd_ptp_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rfd_ptp_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rfd_ptp_state_lock_cnt < 255)
        {
            in_bup_dcu_rfd_ptp_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rfd_ptp_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_rfd_ptp_state_lock_cnt == 1) && (in_bup_dcu_rfd_ptp_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rfd.ptp_state.msg);
                mj_handle.in.bup_dcu_rfd.ptp_state.msg = (ptp_info_msg_t*)(in_bup_dcu_rfd_ptp_state_delayed_ptr);
                mj_handle.in.bup_dcu_rfd.ptp_state.ts_s = bup_dcu_rfd_ptp_state_delayed_ts_s;
                mj_handle.in.bup_dcu_rfd.ptp_state.ts_ns = bup_dcu_rfd_ptp_state_delayed_ts_ns;
                bup_dcu_rfd_ptp_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_rfd.ptp_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rfd_ptp_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rfd_ptp_state_delayed_ptr = NULL;
            }
            in_bup_dcu_rfd_ptp_state_lock_cnt--;
        }
    }
    return in_bup_dcu_rfd_ptp_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rfd_ptp_state_copy_fcn(void *dst)
{
    in_bup_dcu_rfd_ptp_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rfd.ptp_state.msg), sizeof(ptp_info_msg_t));
    in_bup_dcu_rfd_ptp_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_bup_state_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rrd_bup_state_lock_cnt = 0;
static bup_drv_state_msg_t* in_bup_dcu_rrd_bup_state_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_bup_state_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_bup_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_bup_state_updated = 0;
static uint32_t  in_bup_dcu_rrd_bup_state_total = 0;
static uint32_t  in_bup_dcu_rrd_bup_state_miss = 0;
static uint16_t  in_bup_dcu_rrd_bup_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_bup_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_bup_state_lock_cnt < 255)
        {
            in_bup_dcu_rrd_bup_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_bup_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_bup_state_lock_cnt == 1) && (in_bup_dcu_rrd_bup_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.bup_state.msg);
                mj_handle.in.bup_dcu_rrd.bup_state.msg = (bup_drv_state_msg_t*)(in_bup_dcu_rrd_bup_state_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.bup_state.ts_s = bup_dcu_rrd_bup_state_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.bup_state.ts_ns = bup_dcu_rrd_bup_state_delayed_ts_ns;
                bup_dcu_rrd_bup_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.bup_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_bup_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_bup_state_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_bup_state_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_bup_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_bup_state_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_bup_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.bup_state.msg), sizeof(bup_drv_state_msg_t));
    in_bup_dcu_rrd_bup_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_cmd_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rrd_cmd_ans_lock_cnt = 0;
static command_answer_msg_t* in_bup_dcu_rrd_cmd_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_cmd_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_cmd_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_cmd_ans_updated = 0;
static uint32_t  in_bup_dcu_rrd_cmd_ans_total = 0;
static uint32_t  in_bup_dcu_rrd_cmd_ans_miss = 0;
static uint16_t  in_bup_dcu_rrd_cmd_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_cmd_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_cmd_ans_lock_cnt < 255)
        {
            in_bup_dcu_rrd_cmd_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_cmd_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_cmd_ans_lock_cnt == 1) && (in_bup_dcu_rrd_cmd_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.cmd_ans.msg);
                mj_handle.in.bup_dcu_rrd.cmd_ans.msg = (command_answer_msg_t*)(in_bup_dcu_rrd_cmd_ans_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.cmd_ans.ts_s = bup_dcu_rrd_cmd_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.cmd_ans.ts_ns = bup_dcu_rrd_cmd_ans_delayed_ts_ns;
                bup_dcu_rrd_cmd_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.cmd_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_cmd_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_cmd_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_cmd_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_cmd_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_cmd_ans_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_cmd_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.cmd_ans.msg), sizeof(command_answer_msg_t));
    in_bup_dcu_rrd_cmd_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_dbg_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_rrd_dbg_lock_cnt = 0;
static dbg_data_msg_t* in_bup_dcu_rrd_dbg_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_dbg_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_dbg_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_dbg_updated = 0;
static uint32_t  in_bup_dcu_rrd_dbg_total = 0;
static uint32_t  in_bup_dcu_rrd_dbg_miss = 0;
static uint16_t  in_bup_dcu_rrd_dbg_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_dbg_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_dbg_lock_cnt < 255)
        {
            in_bup_dcu_rrd_dbg_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_dbg_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_dbg_lock_cnt == 1) && (in_bup_dcu_rrd_dbg_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.dbg.msg);
                mj_handle.in.bup_dcu_rrd.dbg.msg = (dbg_data_msg_t*)(in_bup_dcu_rrd_dbg_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.dbg.ts_s = bup_dcu_rrd_dbg_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.dbg.ts_ns = bup_dcu_rrd_dbg_delayed_ts_ns;
                bup_dcu_rrd_dbg_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.dbg.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_dbg_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_dbg_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_dbg_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_dbg_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_dbg_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_dbg_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.dbg.msg), sizeof(dbg_data_msg_t));
    in_bup_dcu_rrd_dbg_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_dcu_tel_rx_tick = UINT32_MAX - 4.0;
static uint8_t  in_bup_dcu_rrd_dcu_tel_lock_cnt = 0;
static dcu_telemetry_msg_t* in_bup_dcu_rrd_dcu_tel_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_dcu_tel_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_dcu_tel_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_dcu_tel_updated = 0;
static uint32_t  in_bup_dcu_rrd_dcu_tel_total = 0;
static uint32_t  in_bup_dcu_rrd_dcu_tel_miss = 0;
static uint16_t  in_bup_dcu_rrd_dcu_tel_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_dcu_tel_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_dcu_tel_lock_cnt < 255)
        {
            in_bup_dcu_rrd_dcu_tel_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_dcu_tel_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_dcu_tel_lock_cnt == 1) && (in_bup_dcu_rrd_dcu_tel_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.dcu_tel.msg);
                mj_handle.in.bup_dcu_rrd.dcu_tel.msg = (dcu_telemetry_msg_t*)(in_bup_dcu_rrd_dcu_tel_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.dcu_tel.ts_s = bup_dcu_rrd_dcu_tel_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.dcu_tel.ts_ns = bup_dcu_rrd_dcu_tel_delayed_ts_ns;
                bup_dcu_rrd_dcu_tel_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.dcu_tel.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_dcu_tel_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_dcu_tel_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_dcu_tel_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_dcu_tel_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_dcu_tel_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_dcu_tel_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.dcu_tel.msg), sizeof(dcu_telemetry_msg_t));
    in_bup_dcu_rrd_dcu_tel_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_drive_master_ctrl_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_rrd_drive_master_ctrl_lock_cnt = 0;
static drive_master_ctrl_msg_t* in_bup_dcu_rrd_drive_master_ctrl_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_drive_master_ctrl_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_drive_master_ctrl_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_drive_master_ctrl_updated = 0;
static uint32_t  in_bup_dcu_rrd_drive_master_ctrl_total = 0;
static uint32_t  in_bup_dcu_rrd_drive_master_ctrl_miss = 0;
static uint16_t  in_bup_dcu_rrd_drive_master_ctrl_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_drive_master_ctrl_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_drive_master_ctrl_lock_cnt < 255)
        {
            in_bup_dcu_rrd_drive_master_ctrl_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_drive_master_ctrl_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_drive_master_ctrl_lock_cnt == 1) && (in_bup_dcu_rrd_drive_master_ctrl_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg);
                mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t*)(in_bup_dcu_rrd_drive_master_ctrl_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.drive_master_ctrl.ts_s = bup_dcu_rrd_drive_master_ctrl_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.drive_master_ctrl.ts_ns = bup_dcu_rrd_drive_master_ctrl_delayed_ts_ns;
                bup_dcu_rrd_drive_master_ctrl_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_drive_master_ctrl_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_drive_master_ctrl_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_drive_master_ctrl_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_drive_master_ctrl_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_drive_master_ctrl_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_drive_master_ctrl_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg), sizeof(drive_master_ctrl_msg_t));
    in_bup_dcu_rrd_drive_master_ctrl_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_drive_slave_fb_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_rrd_drive_slave_fb_lock_cnt = 0;
static drive_slave_fb_msg_t* in_bup_dcu_rrd_drive_slave_fb_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_drive_slave_fb_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_drive_slave_fb_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_drive_slave_fb_updated = 0;
static uint32_t  in_bup_dcu_rrd_drive_slave_fb_total = 0;
static uint32_t  in_bup_dcu_rrd_drive_slave_fb_miss = 0;
static uint16_t  in_bup_dcu_rrd_drive_slave_fb_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_drive_slave_fb_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_drive_slave_fb_lock_cnt < 255)
        {
            in_bup_dcu_rrd_drive_slave_fb_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_drive_slave_fb_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_drive_slave_fb_lock_cnt == 1) && (in_bup_dcu_rrd_drive_slave_fb_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg);
                mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg = (drive_slave_fb_msg_t*)(in_bup_dcu_rrd_drive_slave_fb_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.drive_slave_fb.ts_s = bup_dcu_rrd_drive_slave_fb_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.drive_slave_fb.ts_ns = bup_dcu_rrd_drive_slave_fb_delayed_ts_ns;
                bup_dcu_rrd_drive_slave_fb_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.drive_slave_fb.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_drive_slave_fb_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_drive_slave_fb_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_drive_slave_fb_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_drive_slave_fb_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_drive_slave_fb_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_drive_slave_fb_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg), sizeof(drive_slave_fb_msg_t));
    in_bup_dcu_rrd_drive_slave_fb_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_formular_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rrd_formular_lock_cnt = 0;
static formular_info_msg_t* in_bup_dcu_rrd_formular_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_formular_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_formular_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_formular_updated = 0;
static uint32_t  in_bup_dcu_rrd_formular_total = 0;
static uint32_t  in_bup_dcu_rrd_formular_miss = 0;
static uint16_t  in_bup_dcu_rrd_formular_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_formular_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_formular_lock_cnt < 255)
        {
            in_bup_dcu_rrd_formular_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_formular_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_formular_lock_cnt == 1) && (in_bup_dcu_rrd_formular_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.formular.msg);
                mj_handle.in.bup_dcu_rrd.formular.msg = (formular_info_msg_t*)(in_bup_dcu_rrd_formular_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.formular.ts_s = bup_dcu_rrd_formular_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.formular.ts_ns = bup_dcu_rrd_formular_delayed_ts_ns;
                bup_dcu_rrd_formular_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.formular.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_formular_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_formular_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_formular_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_formular_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_formular_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_formular_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.formular.msg), sizeof(formular_info_msg_t));
    in_bup_dcu_rrd_formular_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_msg_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rrd_msg_ans_lock_cnt = 0;
static msg_answer_msg_t* in_bup_dcu_rrd_msg_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_msg_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_msg_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_msg_ans_updated = 0;
static uint32_t  in_bup_dcu_rrd_msg_ans_total = 0;
static uint32_t  in_bup_dcu_rrd_msg_ans_miss = 0;
static uint16_t  in_bup_dcu_rrd_msg_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_msg_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_msg_ans_lock_cnt < 255)
        {
            in_bup_dcu_rrd_msg_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_msg_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_msg_ans_lock_cnt == 1) && (in_bup_dcu_rrd_msg_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.msg_ans.msg);
                mj_handle.in.bup_dcu_rrd.msg_ans.msg = (msg_answer_msg_t*)(in_bup_dcu_rrd_msg_ans_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.msg_ans.ts_s = bup_dcu_rrd_msg_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.msg_ans.ts_ns = bup_dcu_rrd_msg_ans_delayed_ts_ns;
                bup_dcu_rrd_msg_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.msg_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_msg_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_msg_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_msg_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_msg_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_msg_ans_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_msg_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.msg_ans.msg), sizeof(msg_answer_msg_t));
    in_bup_dcu_rrd_msg_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_prm_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rrd_prm_ans_lock_cnt = 0;
static parameter_answer_msg_t* in_bup_dcu_rrd_prm_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_prm_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_prm_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_prm_ans_updated = 0;
static uint32_t  in_bup_dcu_rrd_prm_ans_total = 0;
static uint32_t  in_bup_dcu_rrd_prm_ans_miss = 0;
static uint16_t  in_bup_dcu_rrd_prm_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_prm_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_prm_ans_lock_cnt < 255)
        {
            in_bup_dcu_rrd_prm_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_prm_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_prm_ans_lock_cnt == 1) && (in_bup_dcu_rrd_prm_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.prm_ans.msg);
                mj_handle.in.bup_dcu_rrd.prm_ans.msg = (parameter_answer_msg_t*)(in_bup_dcu_rrd_prm_ans_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.prm_ans.ts_s = bup_dcu_rrd_prm_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.prm_ans.ts_ns = bup_dcu_rrd_prm_ans_delayed_ts_ns;
                bup_dcu_rrd_prm_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.prm_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_prm_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_prm_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_prm_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_prm_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_prm_ans_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_prm_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.prm_ans.msg), sizeof(parameter_answer_msg_t));
    in_bup_dcu_rrd_prm_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rrd_ptp_state_rx_tick = UINT32_MAX - 6001.0;
static uint8_t  in_bup_dcu_rrd_ptp_state_lock_cnt = 0;
static ptp_info_msg_t* in_bup_dcu_rrd_ptp_state_delayed_ptr = NULL;
static uint32_t bup_dcu_rrd_ptp_state_delayed_ts_s = 0;
static uint32_t bup_dcu_rrd_ptp_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rrd_ptp_state_updated = 0;
static uint32_t  in_bup_dcu_rrd_ptp_state_total = 0;
static uint32_t  in_bup_dcu_rrd_ptp_state_miss = 0;
static uint16_t  in_bup_dcu_rrd_ptp_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rrd_ptp_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rrd_ptp_state_lock_cnt < 255)
        {
            in_bup_dcu_rrd_ptp_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rrd_ptp_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_rrd_ptp_state_lock_cnt == 1) && (in_bup_dcu_rrd_ptp_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rrd.ptp_state.msg);
                mj_handle.in.bup_dcu_rrd.ptp_state.msg = (ptp_info_msg_t*)(in_bup_dcu_rrd_ptp_state_delayed_ptr);
                mj_handle.in.bup_dcu_rrd.ptp_state.ts_s = bup_dcu_rrd_ptp_state_delayed_ts_s;
                mj_handle.in.bup_dcu_rrd.ptp_state.ts_ns = bup_dcu_rrd_ptp_state_delayed_ts_ns;
                bup_dcu_rrd_ptp_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_rrd.ptp_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rrd_ptp_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rrd_ptp_state_delayed_ptr = NULL;
            }
            in_bup_dcu_rrd_ptp_state_lock_cnt--;
        }
    }
    return in_bup_dcu_rrd_ptp_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rrd_ptp_state_copy_fcn(void *dst)
{
    in_bup_dcu_rrd_ptp_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rrd.ptp_state.msg), sizeof(ptp_info_msg_t));
    in_bup_dcu_rrd_ptp_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_bup_state_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rst_bup_state_lock_cnt = 0;
static bup_drv_state_msg_t* in_bup_dcu_rst_bup_state_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_bup_state_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_bup_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_bup_state_updated = 0;
static uint32_t  in_bup_dcu_rst_bup_state_total = 0;
static uint32_t  in_bup_dcu_rst_bup_state_miss = 0;
static uint16_t  in_bup_dcu_rst_bup_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_bup_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_bup_state_lock_cnt < 255)
        {
            in_bup_dcu_rst_bup_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_bup_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_bup_state_lock_cnt == 1) && (in_bup_dcu_rst_bup_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.bup_state.msg);
                mj_handle.in.bup_dcu_rst.bup_state.msg = (bup_drv_state_msg_t*)(in_bup_dcu_rst_bup_state_delayed_ptr);
                mj_handle.in.bup_dcu_rst.bup_state.ts_s = bup_dcu_rst_bup_state_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.bup_state.ts_ns = bup_dcu_rst_bup_state_delayed_ts_ns;
                bup_dcu_rst_bup_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.bup_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_bup_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_bup_state_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_bup_state_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_bup_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_bup_state_copy_fcn(void *dst)
{
    in_bup_dcu_rst_bup_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.bup_state.msg), sizeof(bup_drv_state_msg_t));
    in_bup_dcu_rst_bup_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_cmd_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rst_cmd_ans_lock_cnt = 0;
static command_answer_msg_t* in_bup_dcu_rst_cmd_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_cmd_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_cmd_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_cmd_ans_updated = 0;
static uint32_t  in_bup_dcu_rst_cmd_ans_total = 0;
static uint32_t  in_bup_dcu_rst_cmd_ans_miss = 0;
static uint16_t  in_bup_dcu_rst_cmd_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_cmd_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_cmd_ans_lock_cnt < 255)
        {
            in_bup_dcu_rst_cmd_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_cmd_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_cmd_ans_lock_cnt == 1) && (in_bup_dcu_rst_cmd_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.cmd_ans.msg);
                mj_handle.in.bup_dcu_rst.cmd_ans.msg = (command_answer_msg_t*)(in_bup_dcu_rst_cmd_ans_delayed_ptr);
                mj_handle.in.bup_dcu_rst.cmd_ans.ts_s = bup_dcu_rst_cmd_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.cmd_ans.ts_ns = bup_dcu_rst_cmd_ans_delayed_ts_ns;
                bup_dcu_rst_cmd_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.cmd_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_cmd_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_cmd_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_cmd_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_cmd_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_cmd_ans_copy_fcn(void *dst)
{
    in_bup_dcu_rst_cmd_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.cmd_ans.msg), sizeof(command_answer_msg_t));
    in_bup_dcu_rst_cmd_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_dbg_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_rst_dbg_lock_cnt = 0;
static dbg_data_msg_t* in_bup_dcu_rst_dbg_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_dbg_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_dbg_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_dbg_updated = 0;
static uint32_t  in_bup_dcu_rst_dbg_total = 0;
static uint32_t  in_bup_dcu_rst_dbg_miss = 0;
static uint16_t  in_bup_dcu_rst_dbg_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_dbg_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_dbg_lock_cnt < 255)
        {
            in_bup_dcu_rst_dbg_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_dbg_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_dbg_lock_cnt == 1) && (in_bup_dcu_rst_dbg_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.dbg.msg);
                mj_handle.in.bup_dcu_rst.dbg.msg = (dbg_data_msg_t*)(in_bup_dcu_rst_dbg_delayed_ptr);
                mj_handle.in.bup_dcu_rst.dbg.ts_s = bup_dcu_rst_dbg_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.dbg.ts_ns = bup_dcu_rst_dbg_delayed_ts_ns;
                bup_dcu_rst_dbg_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.dbg.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_dbg_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_dbg_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_dbg_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_dbg_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_dbg_copy_fcn(void *dst)
{
    in_bup_dcu_rst_dbg_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.dbg.msg), sizeof(dbg_data_msg_t));
    in_bup_dcu_rst_dbg_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_dcu_tel_rx_tick = UINT32_MAX - 4.0;
static uint8_t  in_bup_dcu_rst_dcu_tel_lock_cnt = 0;
static dcu_telemetry_msg_t* in_bup_dcu_rst_dcu_tel_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_dcu_tel_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_dcu_tel_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_dcu_tel_updated = 0;
static uint32_t  in_bup_dcu_rst_dcu_tel_total = 0;
static uint32_t  in_bup_dcu_rst_dcu_tel_miss = 0;
static uint16_t  in_bup_dcu_rst_dcu_tel_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_dcu_tel_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_dcu_tel_lock_cnt < 255)
        {
            in_bup_dcu_rst_dcu_tel_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_dcu_tel_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_dcu_tel_lock_cnt == 1) && (in_bup_dcu_rst_dcu_tel_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.dcu_tel.msg);
                mj_handle.in.bup_dcu_rst.dcu_tel.msg = (dcu_telemetry_msg_t*)(in_bup_dcu_rst_dcu_tel_delayed_ptr);
                mj_handle.in.bup_dcu_rst.dcu_tel.ts_s = bup_dcu_rst_dcu_tel_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.dcu_tel.ts_ns = bup_dcu_rst_dcu_tel_delayed_ts_ns;
                bup_dcu_rst_dcu_tel_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.dcu_tel.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_dcu_tel_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_dcu_tel_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_dcu_tel_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_dcu_tel_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_dcu_tel_copy_fcn(void *dst)
{
    in_bup_dcu_rst_dcu_tel_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.dcu_tel.msg), sizeof(dcu_telemetry_msg_t));
    in_bup_dcu_rst_dcu_tel_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_drive_master_ctrl_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_rst_drive_master_ctrl_lock_cnt = 0;
static drive_master_ctrl_msg_t* in_bup_dcu_rst_drive_master_ctrl_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_drive_master_ctrl_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_drive_master_ctrl_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_drive_master_ctrl_updated = 0;
static uint32_t  in_bup_dcu_rst_drive_master_ctrl_total = 0;
static uint32_t  in_bup_dcu_rst_drive_master_ctrl_miss = 0;
static uint16_t  in_bup_dcu_rst_drive_master_ctrl_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_drive_master_ctrl_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_drive_master_ctrl_lock_cnt < 255)
        {
            in_bup_dcu_rst_drive_master_ctrl_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_drive_master_ctrl_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_drive_master_ctrl_lock_cnt == 1) && (in_bup_dcu_rst_drive_master_ctrl_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg);
                mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg = (drive_master_ctrl_msg_t*)(in_bup_dcu_rst_drive_master_ctrl_delayed_ptr);
                mj_handle.in.bup_dcu_rst.drive_master_ctrl.ts_s = bup_dcu_rst_drive_master_ctrl_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.drive_master_ctrl.ts_ns = bup_dcu_rst_drive_master_ctrl_delayed_ts_ns;
                bup_dcu_rst_drive_master_ctrl_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_drive_master_ctrl_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_drive_master_ctrl_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_drive_master_ctrl_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_drive_master_ctrl_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_drive_master_ctrl_copy_fcn(void *dst)
{
    in_bup_dcu_rst_drive_master_ctrl_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg), sizeof(drive_master_ctrl_msg_t));
    in_bup_dcu_rst_drive_master_ctrl_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_drive_slave_fb_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_bup_dcu_rst_drive_slave_fb_lock_cnt = 0;
static drive_slave_fb_msg_t* in_bup_dcu_rst_drive_slave_fb_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_drive_slave_fb_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_drive_slave_fb_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_drive_slave_fb_updated = 0;
static uint32_t  in_bup_dcu_rst_drive_slave_fb_total = 0;
static uint32_t  in_bup_dcu_rst_drive_slave_fb_miss = 0;
static uint16_t  in_bup_dcu_rst_drive_slave_fb_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_drive_slave_fb_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_drive_slave_fb_lock_cnt < 255)
        {
            in_bup_dcu_rst_drive_slave_fb_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_drive_slave_fb_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_drive_slave_fb_lock_cnt == 1) && (in_bup_dcu_rst_drive_slave_fb_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.drive_slave_fb.msg);
                mj_handle.in.bup_dcu_rst.drive_slave_fb.msg = (drive_slave_fb_msg_t*)(in_bup_dcu_rst_drive_slave_fb_delayed_ptr);
                mj_handle.in.bup_dcu_rst.drive_slave_fb.ts_s = bup_dcu_rst_drive_slave_fb_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.drive_slave_fb.ts_ns = bup_dcu_rst_drive_slave_fb_delayed_ts_ns;
                bup_dcu_rst_drive_slave_fb_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.drive_slave_fb.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_drive_slave_fb_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_drive_slave_fb_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_drive_slave_fb_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_drive_slave_fb_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_drive_slave_fb_copy_fcn(void *dst)
{
    in_bup_dcu_rst_drive_slave_fb_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.drive_slave_fb.msg), sizeof(drive_slave_fb_msg_t));
    in_bup_dcu_rst_drive_slave_fb_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_formular_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rst_formular_lock_cnt = 0;
static formular_info_msg_t* in_bup_dcu_rst_formular_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_formular_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_formular_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_formular_updated = 0;
static uint32_t  in_bup_dcu_rst_formular_total = 0;
static uint32_t  in_bup_dcu_rst_formular_miss = 0;
static uint16_t  in_bup_dcu_rst_formular_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_formular_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_formular_lock_cnt < 255)
        {
            in_bup_dcu_rst_formular_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_formular_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_formular_lock_cnt == 1) && (in_bup_dcu_rst_formular_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.formular.msg);
                mj_handle.in.bup_dcu_rst.formular.msg = (formular_info_msg_t*)(in_bup_dcu_rst_formular_delayed_ptr);
                mj_handle.in.bup_dcu_rst.formular.ts_s = bup_dcu_rst_formular_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.formular.ts_ns = bup_dcu_rst_formular_delayed_ts_ns;
                bup_dcu_rst_formular_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.formular.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_formular_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_formular_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_formular_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_formular_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_formular_copy_fcn(void *dst)
{
    in_bup_dcu_rst_formular_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.formular.msg), sizeof(formular_info_msg_t));
    in_bup_dcu_rst_formular_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_msg_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rst_msg_ans_lock_cnt = 0;
static msg_answer_msg_t* in_bup_dcu_rst_msg_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_msg_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_msg_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_msg_ans_updated = 0;
static uint32_t  in_bup_dcu_rst_msg_ans_total = 0;
static uint32_t  in_bup_dcu_rst_msg_ans_miss = 0;
static uint16_t  in_bup_dcu_rst_msg_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_msg_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_msg_ans_lock_cnt < 255)
        {
            in_bup_dcu_rst_msg_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_msg_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_msg_ans_lock_cnt == 1) && (in_bup_dcu_rst_msg_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.msg_ans.msg);
                mj_handle.in.bup_dcu_rst.msg_ans.msg = (msg_answer_msg_t*)(in_bup_dcu_rst_msg_ans_delayed_ptr);
                mj_handle.in.bup_dcu_rst.msg_ans.ts_s = bup_dcu_rst_msg_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.msg_ans.ts_ns = bup_dcu_rst_msg_ans_delayed_ts_ns;
                bup_dcu_rst_msg_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.msg_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_msg_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_msg_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_msg_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_msg_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_msg_ans_copy_fcn(void *dst)
{
    in_bup_dcu_rst_msg_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.msg_ans.msg), sizeof(msg_answer_msg_t));
    in_bup_dcu_rst_msg_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_prm_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_bup_dcu_rst_prm_ans_lock_cnt = 0;
static parameter_answer_msg_t* in_bup_dcu_rst_prm_ans_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_prm_ans_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_prm_ans_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_prm_ans_updated = 0;
static uint32_t  in_bup_dcu_rst_prm_ans_total = 0;
static uint32_t  in_bup_dcu_rst_prm_ans_miss = 0;
static uint16_t  in_bup_dcu_rst_prm_ans_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_prm_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_prm_ans_lock_cnt < 255)
        {
            in_bup_dcu_rst_prm_ans_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_prm_ans_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_prm_ans_lock_cnt == 1) && (in_bup_dcu_rst_prm_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.prm_ans.msg);
                mj_handle.in.bup_dcu_rst.prm_ans.msg = (parameter_answer_msg_t*)(in_bup_dcu_rst_prm_ans_delayed_ptr);
                mj_handle.in.bup_dcu_rst.prm_ans.ts_s = bup_dcu_rst_prm_ans_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.prm_ans.ts_ns = bup_dcu_rst_prm_ans_delayed_ts_ns;
                bup_dcu_rst_prm_ans_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.prm_ans.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_prm_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_prm_ans_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_prm_ans_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_prm_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_prm_ans_copy_fcn(void *dst)
{
    in_bup_dcu_rst_prm_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.prm_ans.msg), sizeof(parameter_answer_msg_t));
    in_bup_dcu_rst_prm_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t bup_dcu_rst_ptp_state_rx_tick = UINT32_MAX - 6001.0;
static uint8_t  in_bup_dcu_rst_ptp_state_lock_cnt = 0;
static ptp_info_msg_t* in_bup_dcu_rst_ptp_state_delayed_ptr = NULL;
static uint32_t bup_dcu_rst_ptp_state_delayed_ts_s = 0;
static uint32_t bup_dcu_rst_ptp_state_delayed_ts_ns = 0;
static uint8_t  in_bup_dcu_rst_ptp_state_updated = 0;
static uint32_t  in_bup_dcu_rst_ptp_state_total = 0;
static uint32_t  in_bup_dcu_rst_ptp_state_miss = 0;
static uint16_t  in_bup_dcu_rst_ptp_state_last_cnt = 0;
static mj_msg_state_t in_bup_dcu_rst_ptp_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_bup_dcu_rst_ptp_state_lock_cnt < 255)
        {
            in_bup_dcu_rst_ptp_state_lock_cnt++;
        }
    }else{
        if (in_bup_dcu_rst_ptp_state_lock_cnt > 0)
        {
            if ((in_bup_dcu_rst_ptp_state_lock_cnt == 1) && (in_bup_dcu_rst_ptp_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.bup_dcu_rst.ptp_state.msg);
                mj_handle.in.bup_dcu_rst.ptp_state.msg = (ptp_info_msg_t*)(in_bup_dcu_rst_ptp_state_delayed_ptr);
                mj_handle.in.bup_dcu_rst.ptp_state.ts_s = bup_dcu_rst_ptp_state_delayed_ts_s;
                mj_handle.in.bup_dcu_rst.ptp_state.ts_ns = bup_dcu_rst_ptp_state_delayed_ts_ns;
                bup_dcu_rst_ptp_state_rx_tick = ticks;
                mj_handle.in.bup_dcu_rst.ptp_state.state = MJ_MSG_ACTUAL;
                in_bup_dcu_rst_ptp_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_bup_dcu_rst_ptp_state_delayed_ptr = NULL;
            }
            in_bup_dcu_rst_ptp_state_lock_cnt--;
        }
    }
    return in_bup_dcu_rst_ptp_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_bup_dcu_rst_ptp_state_copy_fcn(void *dst)
{
    in_bup_dcu_rst_ptp_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.bup_dcu_rst.ptp_state.msg), sizeof(ptp_info_msg_t));
    in_bup_dcu_rst_ptp_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_bup_state_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_dcu_bup_state_lock_cnt = 0;
static bup_drv_state_msg_t* in_dcu_bup_state_delayed_ptr = NULL;
static uint32_t dcu_bup_state_delayed_ts_s = 0;
static uint32_t dcu_bup_state_delayed_ts_ns = 0;
static uint8_t  in_dcu_bup_state_updated = 0;
static uint32_t  in_dcu_bup_state_total = 0;
static uint32_t  in_dcu_bup_state_miss = 0;
static uint16_t  in_dcu_bup_state_last_cnt = 0;
static mj_msg_state_t in_dcu_bup_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_bup_state_lock_cnt < 255)
        {
            in_dcu_bup_state_lock_cnt++;
        }
    }else{
        if (in_dcu_bup_state_lock_cnt > 0)
        {
            if ((in_dcu_bup_state_lock_cnt == 1) && (in_dcu_bup_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.bup_state.msg);
                mj_handle.in.dcu.bup_state.msg = (bup_drv_state_msg_t*)(in_dcu_bup_state_delayed_ptr);
                mj_handle.in.dcu.bup_state.ts_s = dcu_bup_state_delayed_ts_s;
                mj_handle.in.dcu.bup_state.ts_ns = dcu_bup_state_delayed_ts_ns;
                dcu_bup_state_rx_tick = ticks;
                mj_handle.in.dcu.bup_state.state = MJ_MSG_ACTUAL;
                in_dcu_bup_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_bup_state_delayed_ptr = NULL;
            }
            in_dcu_bup_state_lock_cnt--;
        }
    }
    return in_dcu_bup_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_bup_state_copy_fcn(void *dst)
{
    in_dcu_bup_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.bup_state.msg), sizeof(bup_drv_state_msg_t));
    in_dcu_bup_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_cmd_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_dcu_cmd_ans_lock_cnt = 0;
static command_answer_msg_t* in_dcu_cmd_ans_delayed_ptr = NULL;
static uint32_t dcu_cmd_ans_delayed_ts_s = 0;
static uint32_t dcu_cmd_ans_delayed_ts_ns = 0;
static uint8_t  in_dcu_cmd_ans_updated = 0;
static uint32_t  in_dcu_cmd_ans_total = 0;
static uint32_t  in_dcu_cmd_ans_miss = 0;
static uint16_t  in_dcu_cmd_ans_last_cnt = 0;
static mj_msg_state_t in_dcu_cmd_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_cmd_ans_lock_cnt < 255)
        {
            in_dcu_cmd_ans_lock_cnt++;
        }
    }else{
        if (in_dcu_cmd_ans_lock_cnt > 0)
        {
            if ((in_dcu_cmd_ans_lock_cnt == 1) && (in_dcu_cmd_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.cmd_ans.msg);
                mj_handle.in.dcu.cmd_ans.msg = (command_answer_msg_t*)(in_dcu_cmd_ans_delayed_ptr);
                mj_handle.in.dcu.cmd_ans.ts_s = dcu_cmd_ans_delayed_ts_s;
                mj_handle.in.dcu.cmd_ans.ts_ns = dcu_cmd_ans_delayed_ts_ns;
                dcu_cmd_ans_rx_tick = ticks;
                mj_handle.in.dcu.cmd_ans.state = MJ_MSG_ACTUAL;
                in_dcu_cmd_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_cmd_ans_delayed_ptr = NULL;
            }
            in_dcu_cmd_ans_lock_cnt--;
        }
    }
    return in_dcu_cmd_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_cmd_ans_copy_fcn(void *dst)
{
    in_dcu_cmd_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.cmd_ans.msg), sizeof(command_answer_msg_t));
    in_dcu_cmd_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_dbg_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_dcu_dbg_lock_cnt = 0;
static dbg_data_msg_t* in_dcu_dbg_delayed_ptr = NULL;
static uint32_t dcu_dbg_delayed_ts_s = 0;
static uint32_t dcu_dbg_delayed_ts_ns = 0;
static uint8_t  in_dcu_dbg_updated = 0;
static uint32_t  in_dcu_dbg_total = 0;
static uint32_t  in_dcu_dbg_miss = 0;
static uint16_t  in_dcu_dbg_last_cnt = 0;
static mj_msg_state_t in_dcu_dbg_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_dbg_lock_cnt < 255)
        {
            in_dcu_dbg_lock_cnt++;
        }
    }else{
        if (in_dcu_dbg_lock_cnt > 0)
        {
            if ((in_dcu_dbg_lock_cnt == 1) && (in_dcu_dbg_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.dbg.msg);
                mj_handle.in.dcu.dbg.msg = (dbg_data_msg_t*)(in_dcu_dbg_delayed_ptr);
                mj_handle.in.dcu.dbg.ts_s = dcu_dbg_delayed_ts_s;
                mj_handle.in.dcu.dbg.ts_ns = dcu_dbg_delayed_ts_ns;
                dcu_dbg_rx_tick = ticks;
                mj_handle.in.dcu.dbg.state = MJ_MSG_ACTUAL;
                in_dcu_dbg_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_dbg_delayed_ptr = NULL;
            }
            in_dcu_dbg_lock_cnt--;
        }
    }
    return in_dcu_dbg_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_dbg_copy_fcn(void *dst)
{
    in_dcu_dbg_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.dbg.msg), sizeof(dbg_data_msg_t));
    in_dcu_dbg_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_dcu_tel_rx_tick = UINT32_MAX - 4.0;
static uint8_t  in_dcu_dcu_tel_lock_cnt = 0;
static dcu_telemetry_msg_t* in_dcu_dcu_tel_delayed_ptr = NULL;
static uint32_t dcu_dcu_tel_delayed_ts_s = 0;
static uint32_t dcu_dcu_tel_delayed_ts_ns = 0;
static uint8_t  in_dcu_dcu_tel_updated = 0;
static uint32_t  in_dcu_dcu_tel_total = 0;
static uint32_t  in_dcu_dcu_tel_miss = 0;
static uint16_t  in_dcu_dcu_tel_last_cnt = 0;
static mj_msg_state_t in_dcu_dcu_tel_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_dcu_tel_lock_cnt < 255)
        {
            in_dcu_dcu_tel_lock_cnt++;
        }
    }else{
        if (in_dcu_dcu_tel_lock_cnt > 0)
        {
            if ((in_dcu_dcu_tel_lock_cnt == 1) && (in_dcu_dcu_tel_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.dcu_tel.msg);
                mj_handle.in.dcu.dcu_tel.msg = (dcu_telemetry_msg_t*)(in_dcu_dcu_tel_delayed_ptr);
                mj_handle.in.dcu.dcu_tel.ts_s = dcu_dcu_tel_delayed_ts_s;
                mj_handle.in.dcu.dcu_tel.ts_ns = dcu_dcu_tel_delayed_ts_ns;
                dcu_dcu_tel_rx_tick = ticks;
                mj_handle.in.dcu.dcu_tel.state = MJ_MSG_ACTUAL;
                in_dcu_dcu_tel_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_dcu_tel_delayed_ptr = NULL;
            }
            in_dcu_dcu_tel_lock_cnt--;
        }
    }
    return in_dcu_dcu_tel_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_dcu_tel_copy_fcn(void *dst)
{
    in_dcu_dcu_tel_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.dcu_tel.msg), sizeof(dcu_telemetry_msg_t));
    in_dcu_dcu_tel_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_drive_master_ctrl_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_dcu_drive_master_ctrl_lock_cnt = 0;
static drive_master_ctrl_msg_t* in_dcu_drive_master_ctrl_delayed_ptr = NULL;
static uint32_t dcu_drive_master_ctrl_delayed_ts_s = 0;
static uint32_t dcu_drive_master_ctrl_delayed_ts_ns = 0;
static uint8_t  in_dcu_drive_master_ctrl_updated = 0;
static uint32_t  in_dcu_drive_master_ctrl_total = 0;
static uint32_t  in_dcu_drive_master_ctrl_miss = 0;
static uint16_t  in_dcu_drive_master_ctrl_last_cnt = 0;
static mj_msg_state_t in_dcu_drive_master_ctrl_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_drive_master_ctrl_lock_cnt < 255)
        {
            in_dcu_drive_master_ctrl_lock_cnt++;
        }
    }else{
        if (in_dcu_drive_master_ctrl_lock_cnt > 0)
        {
            if ((in_dcu_drive_master_ctrl_lock_cnt == 1) && (in_dcu_drive_master_ctrl_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.drive_master_ctrl.msg);
                mj_handle.in.dcu.drive_master_ctrl.msg = (drive_master_ctrl_msg_t*)(in_dcu_drive_master_ctrl_delayed_ptr);
                mj_handle.in.dcu.drive_master_ctrl.ts_s = dcu_drive_master_ctrl_delayed_ts_s;
                mj_handle.in.dcu.drive_master_ctrl.ts_ns = dcu_drive_master_ctrl_delayed_ts_ns;
                dcu_drive_master_ctrl_rx_tick = ticks;
                mj_handle.in.dcu.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                in_dcu_drive_master_ctrl_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_drive_master_ctrl_delayed_ptr = NULL;
            }
            in_dcu_drive_master_ctrl_lock_cnt--;
        }
    }
    return in_dcu_drive_master_ctrl_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_drive_master_ctrl_copy_fcn(void *dst)
{
    in_dcu_drive_master_ctrl_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.drive_master_ctrl.msg), sizeof(drive_master_ctrl_msg_t));
    in_dcu_drive_master_ctrl_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_drive_slave_fb_rx_tick = UINT32_MAX - 13.0;
static uint8_t  in_dcu_drive_slave_fb_lock_cnt = 0;
static drive_slave_fb_msg_t* in_dcu_drive_slave_fb_delayed_ptr = NULL;
static uint32_t dcu_drive_slave_fb_delayed_ts_s = 0;
static uint32_t dcu_drive_slave_fb_delayed_ts_ns = 0;
static uint8_t  in_dcu_drive_slave_fb_updated = 0;
static uint32_t  in_dcu_drive_slave_fb_total = 0;
static uint32_t  in_dcu_drive_slave_fb_miss = 0;
static uint16_t  in_dcu_drive_slave_fb_last_cnt = 0;
static mj_msg_state_t in_dcu_drive_slave_fb_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_drive_slave_fb_lock_cnt < 255)
        {
            in_dcu_drive_slave_fb_lock_cnt++;
        }
    }else{
        if (in_dcu_drive_slave_fb_lock_cnt > 0)
        {
            if ((in_dcu_drive_slave_fb_lock_cnt == 1) && (in_dcu_drive_slave_fb_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.drive_slave_fb.msg);
                mj_handle.in.dcu.drive_slave_fb.msg = (drive_slave_fb_msg_t*)(in_dcu_drive_slave_fb_delayed_ptr);
                mj_handle.in.dcu.drive_slave_fb.ts_s = dcu_drive_slave_fb_delayed_ts_s;
                mj_handle.in.dcu.drive_slave_fb.ts_ns = dcu_drive_slave_fb_delayed_ts_ns;
                dcu_drive_slave_fb_rx_tick = ticks;
                mj_handle.in.dcu.drive_slave_fb.state = MJ_MSG_ACTUAL;
                in_dcu_drive_slave_fb_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_drive_slave_fb_delayed_ptr = NULL;
            }
            in_dcu_drive_slave_fb_lock_cnt--;
        }
    }
    return in_dcu_drive_slave_fb_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_drive_slave_fb_copy_fcn(void *dst)
{
    in_dcu_drive_slave_fb_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.drive_slave_fb.msg), sizeof(drive_slave_fb_msg_t));
    in_dcu_drive_slave_fb_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_formular_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_dcu_formular_lock_cnt = 0;
static formular_info_msg_t* in_dcu_formular_delayed_ptr = NULL;
static uint32_t dcu_formular_delayed_ts_s = 0;
static uint32_t dcu_formular_delayed_ts_ns = 0;
static uint8_t  in_dcu_formular_updated = 0;
static uint32_t  in_dcu_formular_total = 0;
static uint32_t  in_dcu_formular_miss = 0;
static uint16_t  in_dcu_formular_last_cnt = 0;
static mj_msg_state_t in_dcu_formular_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_formular_lock_cnt < 255)
        {
            in_dcu_formular_lock_cnt++;
        }
    }else{
        if (in_dcu_formular_lock_cnt > 0)
        {
            if ((in_dcu_formular_lock_cnt == 1) && (in_dcu_formular_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.formular.msg);
                mj_handle.in.dcu.formular.msg = (formular_info_msg_t*)(in_dcu_formular_delayed_ptr);
                mj_handle.in.dcu.formular.ts_s = dcu_formular_delayed_ts_s;
                mj_handle.in.dcu.formular.ts_ns = dcu_formular_delayed_ts_ns;
                dcu_formular_rx_tick = ticks;
                mj_handle.in.dcu.formular.state = MJ_MSG_ACTUAL;
                in_dcu_formular_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_formular_delayed_ptr = NULL;
            }
            in_dcu_formular_lock_cnt--;
        }
    }
    return in_dcu_formular_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_formular_copy_fcn(void *dst)
{
    in_dcu_formular_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.formular.msg), sizeof(formular_info_msg_t));
    in_dcu_formular_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_msg_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_dcu_msg_ans_lock_cnt = 0;
static msg_answer_msg_t* in_dcu_msg_ans_delayed_ptr = NULL;
static uint32_t dcu_msg_ans_delayed_ts_s = 0;
static uint32_t dcu_msg_ans_delayed_ts_ns = 0;
static uint8_t  in_dcu_msg_ans_updated = 0;
static uint32_t  in_dcu_msg_ans_total = 0;
static uint32_t  in_dcu_msg_ans_miss = 0;
static uint16_t  in_dcu_msg_ans_last_cnt = 0;
static mj_msg_state_t in_dcu_msg_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_msg_ans_lock_cnt < 255)
        {
            in_dcu_msg_ans_lock_cnt++;
        }
    }else{
        if (in_dcu_msg_ans_lock_cnt > 0)
        {
            if ((in_dcu_msg_ans_lock_cnt == 1) && (in_dcu_msg_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.msg_ans.msg);
                mj_handle.in.dcu.msg_ans.msg = (msg_answer_msg_t*)(in_dcu_msg_ans_delayed_ptr);
                mj_handle.in.dcu.msg_ans.ts_s = dcu_msg_ans_delayed_ts_s;
                mj_handle.in.dcu.msg_ans.ts_ns = dcu_msg_ans_delayed_ts_ns;
                dcu_msg_ans_rx_tick = ticks;
                mj_handle.in.dcu.msg_ans.state = MJ_MSG_ACTUAL;
                in_dcu_msg_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_msg_ans_delayed_ptr = NULL;
            }
            in_dcu_msg_ans_lock_cnt--;
        }
    }
    return in_dcu_msg_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_msg_ans_copy_fcn(void *dst)
{
    in_dcu_msg_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.msg_ans.msg), sizeof(msg_answer_msg_t));
    in_dcu_msg_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_prm_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_dcu_prm_ans_lock_cnt = 0;
static parameter_answer_msg_t* in_dcu_prm_ans_delayed_ptr = NULL;
static uint32_t dcu_prm_ans_delayed_ts_s = 0;
static uint32_t dcu_prm_ans_delayed_ts_ns = 0;
static uint8_t  in_dcu_prm_ans_updated = 0;
static uint32_t  in_dcu_prm_ans_total = 0;
static uint32_t  in_dcu_prm_ans_miss = 0;
static uint16_t  in_dcu_prm_ans_last_cnt = 0;
static mj_msg_state_t in_dcu_prm_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_prm_ans_lock_cnt < 255)
        {
            in_dcu_prm_ans_lock_cnt++;
        }
    }else{
        if (in_dcu_prm_ans_lock_cnt > 0)
        {
            if ((in_dcu_prm_ans_lock_cnt == 1) && (in_dcu_prm_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.prm_ans.msg);
                mj_handle.in.dcu.prm_ans.msg = (parameter_answer_msg_t*)(in_dcu_prm_ans_delayed_ptr);
                mj_handle.in.dcu.prm_ans.ts_s = dcu_prm_ans_delayed_ts_s;
                mj_handle.in.dcu.prm_ans.ts_ns = dcu_prm_ans_delayed_ts_ns;
                dcu_prm_ans_rx_tick = ticks;
                mj_handle.in.dcu.prm_ans.state = MJ_MSG_ACTUAL;
                in_dcu_prm_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_prm_ans_delayed_ptr = NULL;
            }
            in_dcu_prm_ans_lock_cnt--;
        }
    }
    return in_dcu_prm_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_prm_ans_copy_fcn(void *dst)
{
    in_dcu_prm_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.prm_ans.msg), sizeof(parameter_answer_msg_t));
    in_dcu_prm_ans_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t dcu_ptp_state_rx_tick = UINT32_MAX - 6001.0;
static uint8_t  in_dcu_ptp_state_lock_cnt = 0;
static ptp_info_msg_t* in_dcu_ptp_state_delayed_ptr = NULL;
static uint32_t dcu_ptp_state_delayed_ts_s = 0;
static uint32_t dcu_ptp_state_delayed_ts_ns = 0;
static uint8_t  in_dcu_ptp_state_updated = 0;
static uint32_t  in_dcu_ptp_state_total = 0;
static uint32_t  in_dcu_ptp_state_miss = 0;
static uint16_t  in_dcu_ptp_state_last_cnt = 0;
static mj_msg_state_t in_dcu_ptp_state_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_dcu_ptp_state_lock_cnt < 255)
        {
            in_dcu_ptp_state_lock_cnt++;
        }
    }else{
        if (in_dcu_ptp_state_lock_cnt > 0)
        {
            if ((in_dcu_ptp_state_lock_cnt == 1) && (in_dcu_ptp_state_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.dcu.ptp_state.msg);
                mj_handle.in.dcu.ptp_state.msg = (ptp_info_msg_t*)(in_dcu_ptp_state_delayed_ptr);
                mj_handle.in.dcu.ptp_state.ts_s = dcu_ptp_state_delayed_ts_s;
                mj_handle.in.dcu.ptp_state.ts_ns = dcu_ptp_state_delayed_ts_ns;
                dcu_ptp_state_rx_tick = ticks;
                mj_handle.in.dcu.ptp_state.state = MJ_MSG_ACTUAL;
                in_dcu_ptp_state_updated = 1;
                p_drv->udp4.free(old_buff);
                in_dcu_ptp_state_delayed_ptr = NULL;
            }
            in_dcu_ptp_state_lock_cnt--;
        }
    }
    return in_dcu_ptp_state_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_dcu_ptp_state_copy_fcn(void *dst)
{
    in_dcu_ptp_state_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.dcu.ptp_state.msg), sizeof(ptp_info_msg_t));
    in_dcu_ptp_state_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t im_bro_im_bro_drivers_sens_rx_tick = UINT32_MAX - 4.0;
static uint8_t  in_im_bro_im_bro_drivers_sens_lock_cnt = 0;
static drivers_sens_msg_t* in_im_bro_im_bro_drivers_sens_delayed_ptr = NULL;
static uint32_t im_bro_im_bro_drivers_sens_delayed_ts_s = 0;
static uint32_t im_bro_im_bro_drivers_sens_delayed_ts_ns = 0;
static uint8_t  in_im_bro_im_bro_drivers_sens_updated = 0;
static uint32_t  in_im_bro_im_bro_drivers_sens_total = 0;
static uint32_t  in_im_bro_im_bro_drivers_sens_miss = 0;
static uint16_t  in_im_bro_im_bro_drivers_sens_last_cnt = 0;
static mj_msg_state_t in_im_bro_im_bro_drivers_sens_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_im_bro_im_bro_drivers_sens_lock_cnt < 255)
        {
            in_im_bro_im_bro_drivers_sens_lock_cnt++;
        }
    }else{
        if (in_im_bro_im_bro_drivers_sens_lock_cnt > 0)
        {
            if ((in_im_bro_im_bro_drivers_sens_lock_cnt == 1) && (in_im_bro_im_bro_drivers_sens_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.im_bro.im_bro_drivers_sens.msg);
                mj_handle.in.im_bro.im_bro_drivers_sens.msg = (drivers_sens_msg_t*)(in_im_bro_im_bro_drivers_sens_delayed_ptr);
                mj_handle.in.im_bro.im_bro_drivers_sens.ts_s = im_bro_im_bro_drivers_sens_delayed_ts_s;
                mj_handle.in.im_bro.im_bro_drivers_sens.ts_ns = im_bro_im_bro_drivers_sens_delayed_ts_ns;
                im_bro_im_bro_drivers_sens_rx_tick = ticks;
                mj_handle.in.im_bro.im_bro_drivers_sens.state = MJ_MSG_ACTUAL;
                in_im_bro_im_bro_drivers_sens_updated = 1;
                p_drv->udp4.free(old_buff);
                in_im_bro_im_bro_drivers_sens_delayed_ptr = NULL;
            }
            in_im_bro_im_bro_drivers_sens_lock_cnt--;
        }
    }
    return in_im_bro_im_bro_drivers_sens_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_im_bro_im_bro_drivers_sens_copy_fcn(void *dst)
{
    in_im_bro_im_bro_drivers_sens_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.im_bro.im_bro_drivers_sens.msg), sizeof(drivers_sens_msg_t));
    in_im_bro_im_bro_drivers_sens_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t im_bro_prm_ans_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_im_bro_prm_ans_lock_cnt = 0;
static parameter_answer_msg_t* in_im_bro_prm_ans_delayed_ptr = NULL;
static uint32_t im_bro_prm_ans_delayed_ts_s = 0;
static uint32_t im_bro_prm_ans_delayed_ts_ns = 0;
static uint8_t  in_im_bro_prm_ans_updated = 0;
static uint32_t  in_im_bro_prm_ans_total = 0;
static uint32_t  in_im_bro_prm_ans_miss = 0;
static uint16_t  in_im_bro_prm_ans_last_cnt = 0;
static mj_msg_state_t in_im_bro_prm_ans_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_im_bro_prm_ans_lock_cnt < 255)
        {
            in_im_bro_prm_ans_lock_cnt++;
        }
    }else{
        if (in_im_bro_prm_ans_lock_cnt > 0)
        {
            if ((in_im_bro_prm_ans_lock_cnt == 1) && (in_im_bro_prm_ans_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.im_bro.prm_ans.msg);
                mj_handle.in.im_bro.prm_ans.msg = (parameter_answer_msg_t*)(in_im_bro_prm_ans_delayed_ptr);
                mj_handle.in.im_bro.prm_ans.ts_s = im_bro_prm_ans_delayed_ts_s;
                mj_handle.in.im_bro.prm_ans.ts_ns = im_bro_prm_ans_delayed_ts_ns;
                im_bro_prm_ans_rx_tick = ticks;
                mj_handle.in.im_bro.prm_ans.state = MJ_MSG_ACTUAL;
                in_im_bro_prm_ans_updated = 1;
                p_drv->udp4.free(old_buff);
                in_im_bro_prm_ans_delayed_ptr = NULL;
            }
            in_im_bro_prm_ans_lock_cnt--;
        }
    }
    return in_im_bro_prm_ans_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_im_bro_prm_ans_copy_fcn(void *dst)
{
    in_im_bro_prm_ans_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.im_bro.prm_ans.msg), sizeof(parameter_answer_msg_t));
    in_im_bro_prm_ans_lock_fcn(MJ_MSG_UNLOCK);
}


static void * out_bup_multi_control_pkt = NULL;
static bup_drv_multi_control_msg_t * p_out_bup_multi_control_msg = NULL;
static mj_msg_state_t out_bup_multi_control_lock_fcn(mj_msg_state_t state)
{
    mj_msg_state_t res = MJ_MSG_UNDEFINED;
    if (state == MJ_MSG_LOCK)
    {
        if (p_out_bup_multi_control_msg == NULL)
        {
            if ((p_out_bup_multi_control_msg = (bup_drv_multi_control_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_multi_control_msg_t))))
            {
                memcpy((void *)p_out_bup_multi_control_msg, (void *)(mj_handle.out.bup_multi_control.msg), sizeof(bup_drv_multi_control_msg_t));
                p_drv->udp4.set_payload(out_bup_multi_control_pkt, (uint8_t *)p_out_bup_multi_control_msg);
                res = MJ_MSG_LOCK;
            }else{
                res = MJ_MSG_UNLOCK;
            }
        }else{
            res = MJ_MSG_LOCK;
        }
    }else{
        res = MJ_MSG_LOCK;
        if (p_out_bup_multi_control_msg)
        {
            p_drv->udp4.set_payload(out_bup_multi_control_pkt, (uint8_t *)mj_handle.out.bup_multi_control.msg);
            p_drv->udp4.free((uint8_t *)p_out_bup_multi_control_msg);
            p_out_bup_multi_control_msg = NULL;
            res = MJ_MSG_UNLOCK;
        }else{
            res = MJ_MSG_UNLOCK;
        }
    }
    return res;
}

static void * out_bup_srv_ctrl_pkt = NULL;
static bup_drv_control_msg_t * p_out_bup_srv_ctrl_msg = NULL;
static mj_msg_state_t out_bup_srv_ctrl_lock_fcn(mj_msg_state_t state)
{
    mj_msg_state_t res = MJ_MSG_UNDEFINED;
    if (state == MJ_MSG_LOCK)
    {
        if (p_out_bup_srv_ctrl_msg == NULL)
        {
            if ((p_out_bup_srv_ctrl_msg = (bup_drv_control_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_control_msg_t))))
            {
                memcpy((void *)p_out_bup_srv_ctrl_msg, (void *)(mj_handle.out.bup_srv_ctrl.msg), sizeof(bup_drv_control_msg_t));
                p_drv->udp4.set_payload(out_bup_srv_ctrl_pkt, (uint8_t *)p_out_bup_srv_ctrl_msg);
                res = MJ_MSG_LOCK;
            }else{
                res = MJ_MSG_UNLOCK;
            }
        }else{
            res = MJ_MSG_LOCK;
        }
    }else{
        res = MJ_MSG_LOCK;
        if (p_out_bup_srv_ctrl_msg)
        {
            p_drv->udp4.set_payload(out_bup_srv_ctrl_pkt, (uint8_t *)mj_handle.out.bup_srv_ctrl.msg);
            p_drv->udp4.free((uint8_t *)p_out_bup_srv_ctrl_msg);
            p_out_bup_srv_ctrl_msg = NULL;
            res = MJ_MSG_UNLOCK;
        }else{
            res = MJ_MSG_UNLOCK;
        }
    }
    return res;
}

static void * out_cmd_req_pkt = NULL;
static void out_cmd_req_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.cmd_req.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.cmd_req.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.cmd_req.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.cmd_req.msg->hdr.dst = dst;
    mj_handle.out.cmd_req.msg->hdr.cnt++;
    p_drv->udp4.tx(out_cmd_req_pkt,NULL);
}

static void * out_msg_req_pkt = NULL;
static void out_msg_req_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.msg_req.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.msg_req.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.msg_req.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.msg_req.msg->hdr.dst = dst;
    mj_handle.out.msg_req.msg->hdr.cnt++;
    p_drv->udp4.tx(out_msg_req_pkt,NULL);
}

static void * out_prm_req_pkt = NULL;
static void out_prm_req_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.prm_req.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.prm_req.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.prm_req.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.prm_req.msg->hdr.dst = dst;
    mj_handle.out.prm_req.msg->hdr.cnt++;
    p_drv->udp4.tx(out_prm_req_pkt,NULL);
}


static mon_prm_t _mon_prm;

mj_prm_status_t mon_prm_write(int id, void *data)
{
    switch (id){
        case PRM_BOOL_SERVICE_MODE:
            memcpy(&(_mon_prm.service_mode),data,sizeof(_mon_prm.service_mode));
            return MJ_PRM_OK;
        case PRM_INT_DEV_ID:
            memcpy(&(_mon_prm.dev_id),data,sizeof(_mon_prm.dev_id));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_REQ:
            memcpy(&(_mon_prm.com_if_srv_mcast_req),data,sizeof(_mon_prm.com_if_srv_mcast_req));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_ANS:
            memcpy(&(_mon_prm.com_if_srv_mcast_ans),data,sizeof(_mon_prm.com_if_srv_mcast_ans));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST:
            memcpy(&(_mon_prm.com_if_bro_bup_ctrl_mcast),data,sizeof(_mon_prm.com_if_bro_bup_ctrl_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST:
            memcpy(&(_mon_prm.com_if_bro_bup_data_mcast),data,sizeof(_mon_prm.com_if_bro_bup_data_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BUP_INTERNAL_MCAST:
            memcpy(&(_mon_prm.com_if_bup_internal_mcast),data,sizeof(_mon_prm.com_if_bup_internal_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_SRV_MCAST:
            memcpy(&(_mon_prm.com_if_bro_bup_srv_mcast),data,sizeof(_mon_prm.com_if_bro_bup_srv_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST:
            memcpy(&(_mon_prm.com_if_im_bro_drive_mcast),data,sizeof(_mon_prm.com_if_im_bro_drive_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_CTRL_MCAST:
            memcpy(&(_mon_prm.com_if_im_bro_drive_ctrl_mcast),data,sizeof(_mon_prm.com_if_im_bro_drive_ctrl_mcast));
            return MJ_PRM_OK;
        default:
            return MJ_PRM_UNKNOW;
    }
}

mj_prm_status_t mon_prm_read(int id, void *data)
{
    switch (id){
        case PRM_BOOL_SERVICE_MODE:
            memcpy(data,&_mon_prm.service_mode,sizeof(_mon_prm.service_mode));
            return MJ_PRM_OK;
        case PRM_INT_DEV_ID:
            memcpy(data,&_mon_prm.dev_id,sizeof(_mon_prm.dev_id));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_REQ:
            memcpy(data,&_mon_prm.com_if_srv_mcast_req,sizeof(_mon_prm.com_if_srv_mcast_req));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_ANS:
            memcpy(data,&_mon_prm.com_if_srv_mcast_ans,sizeof(_mon_prm.com_if_srv_mcast_ans));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST:
            memcpy(data,&_mon_prm.com_if_bro_bup_ctrl_mcast,sizeof(_mon_prm.com_if_bro_bup_ctrl_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST:
            memcpy(data,&_mon_prm.com_if_bro_bup_data_mcast,sizeof(_mon_prm.com_if_bro_bup_data_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BUP_INTERNAL_MCAST:
            memcpy(data,&_mon_prm.com_if_bup_internal_mcast,sizeof(_mon_prm.com_if_bup_internal_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_SRV_MCAST:
            memcpy(data,&_mon_prm.com_if_bro_bup_srv_mcast,sizeof(_mon_prm.com_if_bro_bup_srv_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST:
            memcpy(data,&_mon_prm.com_if_im_bro_drive_mcast,sizeof(_mon_prm.com_if_im_bro_drive_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_CTRL_MCAST:
            memcpy(data,&_mon_prm.com_if_im_bro_drive_ctrl_mcast,sizeof(_mon_prm.com_if_im_bro_drive_ctrl_mcast));
            return MJ_PRM_OK;
        default:
            return MJ_PRM_UNKNOW;
    }
}

static const uint32_t _prm_ids[10] = {
    PRM_BOOL_SERVICE_MODE,
    PRM_INT_DEV_ID,
    PRM_STRING_COM_IF_SRV_MCAST_REQ,
    PRM_STRING_COM_IF_SRV_MCAST_ANS,
    PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST,
    PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST,
    PRM_STRING_COM_IF_BUP_INTERNAL_MCAST,
    PRM_STRING_COM_IF_BRO_BUP_SRV_MCAST,
    PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST,
    PRM_STRING_COM_IF_IM_BRO_DRIVE_CTRL_MCAST
};

static const uint32_t * mon_prm_list(uint32_t *size)
{
    *size = 10;
    return _prm_ids;
}

static uint32_t _20000_us_cnt = 0;
static uint32_t _20000_us_tick = 80;

static uint32_t *_join_ip = NULL;
static volatile bool _send_join_done = true;
static uint32_t _join_send_tick = 0;

static void tick_fcn()
{
    uint32_t _temp_ns = 0;

    /* Each 20.0 ms  */
    if (_20000_us_tick >= 80)
    {
        _20000_us_cnt++;
        if (mj_handle.out.bup_multi_control.tx_enable){
            mj_handle.out.bup_multi_control.msg->hdr.cnt = _20000_us_cnt;
            mj_handle.out.bup_multi_control.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.bup_multi_control.msg->hdr.ts_s,&_temp_ns);
            mj_handle.out.bup_multi_control.msg->hdr.ts_ns = _temp_ns;
            p_drv->udp4.tx(out_bup_multi_control_pkt,NULL);
        }
        if (mj_handle.out.bup_srv_ctrl.tx_enable){
            mj_handle.out.bup_srv_ctrl.msg->hdr.cnt = _20000_us_cnt;
            mj_handle.out.bup_srv_ctrl.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.bup_srv_ctrl.msg->hdr.ts_s,&_temp_ns);
            mj_handle.out.bup_srv_ctrl.msg->hdr.ts_ns = _temp_ns;
            p_drv->udp4.tx(out_bup_srv_ctrl_pkt,NULL);
        }
        _20000_us_tick = 0;
    }
    _20000_us_tick++;

    if (!_send_join_done && _join_ip) {
        p_drv->udp4.join_group(ethInt, *_join_ip);
        _join_send_tick = ticks;
        _send_join_done = true;
    }
    p_drv->udp4.pool_tx();
    ticks++;
}


static mj_msg_proc_res_t bro_bup_ctrl_mcast_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
            // bup_multi_control
            case ID_BUP_MULTI_CONTROL:
                if (size == sizeof(bup_drv_multi_control_msg_t))
                {
                    switch (hdr->src)
                    {
                        // bup_multi_control from aufd
                        case BRO30_AUFD:
                            if (in_aufd_bup_multi_control_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.aufd.bup_multi_control.msg;
                                mj_handle.in.aufd.bup_multi_control.msg = (bup_drv_multi_control_msg_t *)data;
                                mj_handle.in.aufd.bup_multi_control.ts_s  = ts_s;
                                mj_handle.in.aufd.bup_multi_control.ts_ns = ts_ns;
                                in_aufd_bup_multi_control_updated = 1;
                                in_aufd_bup_multi_control_total++;
                                uint16_t cnt_diff = (mj_handle.in.aufd.bup_multi_control.msg->hdr.cnt - in_aufd_bup_multi_control_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_aufd_bup_multi_control_miss += cnt_diff;
                                }
                                in_aufd_bup_multi_control_last_cnt = mj_handle.in.aufd.bup_multi_control.msg->hdr.cnt;
                                aufd_bup_multi_control_rx_tick = ticks;
                                mj_handle.in.aufd.bup_multi_control.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_aufd_bup_multi_control_delayed_ptr == NULL)
                                {
                                    in_aufd_bup_multi_control_delayed_ptr = (bup_drv_multi_control_msg_t *)data;
                                    aufd_bup_multi_control_delayed_ts_s = ts_s;
                                    aufd_bup_multi_control_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.aufd.bup_multi_control.irq){
                                mj_handle.in.aufd.bup_multi_control.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            default:
                return MJ_REJECT_ID;    
        }
    }
    return MJ_REJECT_DST; 
}


static mj_msg_proc_res_t bro_bup_data_mcast_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
            // bup_state
            case ID_BUP_STATE:
                if (size == sizeof(bup_drv_state_msg_t))
                {
                    switch (hdr->src)
                    {
                        // bup_state from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_bup_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.bup_state.msg;
                                mj_handle.in.bup_dcu_lfd.bup_state.msg = (bup_drv_state_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.bup_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.bup_state.ts_ns = ts_ns;
                                in_bup_dcu_lfd_bup_state_updated = 1;
                                in_bup_dcu_lfd_bup_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.bup_state.msg->hdr.cnt - in_bup_dcu_lfd_bup_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_bup_state_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_bup_state_last_cnt = mj_handle.in.bup_dcu_lfd.bup_state.msg->hdr.cnt;
                                bup_dcu_lfd_bup_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.bup_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_bup_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_bup_state_delayed_ptr = (bup_drv_state_msg_t *)data;
                                    bup_dcu_lfd_bup_state_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_bup_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.bup_state.irq){
                                mj_handle.in.bup_dcu_lfd.bup_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // bup_state from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_bup_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.bup_state.msg;
                                mj_handle.in.bup_dcu_lrd.bup_state.msg = (bup_drv_state_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.bup_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.bup_state.ts_ns = ts_ns;
                                in_bup_dcu_lrd_bup_state_updated = 1;
                                in_bup_dcu_lrd_bup_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.bup_state.msg->hdr.cnt - in_bup_dcu_lrd_bup_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_bup_state_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_bup_state_last_cnt = mj_handle.in.bup_dcu_lrd.bup_state.msg->hdr.cnt;
                                bup_dcu_lrd_bup_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.bup_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_bup_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_bup_state_delayed_ptr = (bup_drv_state_msg_t *)data;
                                    bup_dcu_lrd_bup_state_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_bup_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.bup_state.irq){
                                mj_handle.in.bup_dcu_lrd.bup_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // bup_state from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_bup_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.bup_state.msg;
                                mj_handle.in.bup_dcu_lst.bup_state.msg = (bup_drv_state_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.bup_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.bup_state.ts_ns = ts_ns;
                                in_bup_dcu_lst_bup_state_updated = 1;
                                in_bup_dcu_lst_bup_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.bup_state.msg->hdr.cnt - in_bup_dcu_lst_bup_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_bup_state_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_bup_state_last_cnt = mj_handle.in.bup_dcu_lst.bup_state.msg->hdr.cnt;
                                bup_dcu_lst_bup_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.bup_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_bup_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_bup_state_delayed_ptr = (bup_drv_state_msg_t *)data;
                                    bup_dcu_lst_bup_state_delayed_ts_s = ts_s;
                                    bup_dcu_lst_bup_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.bup_state.irq){
                                mj_handle.in.bup_dcu_lst.bup_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // bup_state from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_bup_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.bup_state.msg;
                                mj_handle.in.bup_dcu_rfd.bup_state.msg = (bup_drv_state_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.bup_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.bup_state.ts_ns = ts_ns;
                                in_bup_dcu_rfd_bup_state_updated = 1;
                                in_bup_dcu_rfd_bup_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.bup_state.msg->hdr.cnt - in_bup_dcu_rfd_bup_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_bup_state_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_bup_state_last_cnt = mj_handle.in.bup_dcu_rfd.bup_state.msg->hdr.cnt;
                                bup_dcu_rfd_bup_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.bup_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_bup_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_bup_state_delayed_ptr = (bup_drv_state_msg_t *)data;
                                    bup_dcu_rfd_bup_state_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_bup_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.bup_state.irq){
                                mj_handle.in.bup_dcu_rfd.bup_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // bup_state from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_bup_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.bup_state.msg;
                                mj_handle.in.bup_dcu_rrd.bup_state.msg = (bup_drv_state_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.bup_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.bup_state.ts_ns = ts_ns;
                                in_bup_dcu_rrd_bup_state_updated = 1;
                                in_bup_dcu_rrd_bup_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.bup_state.msg->hdr.cnt - in_bup_dcu_rrd_bup_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_bup_state_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_bup_state_last_cnt = mj_handle.in.bup_dcu_rrd.bup_state.msg->hdr.cnt;
                                bup_dcu_rrd_bup_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.bup_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_bup_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_bup_state_delayed_ptr = (bup_drv_state_msg_t *)data;
                                    bup_dcu_rrd_bup_state_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_bup_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.bup_state.irq){
                                mj_handle.in.bup_dcu_rrd.bup_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // bup_state from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_bup_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.bup_state.msg;
                                mj_handle.in.bup_dcu_rst.bup_state.msg = (bup_drv_state_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.bup_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.bup_state.ts_ns = ts_ns;
                                in_bup_dcu_rst_bup_state_updated = 1;
                                in_bup_dcu_rst_bup_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.bup_state.msg->hdr.cnt - in_bup_dcu_rst_bup_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_bup_state_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_bup_state_last_cnt = mj_handle.in.bup_dcu_rst.bup_state.msg->hdr.cnt;
                                bup_dcu_rst_bup_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.bup_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_bup_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_bup_state_delayed_ptr = (bup_drv_state_msg_t *)data;
                                    bup_dcu_rst_bup_state_delayed_ts_s = ts_s;
                                    bup_dcu_rst_bup_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.bup_state.irq){
                                mj_handle.in.bup_dcu_rst.bup_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // bup_state from dcu
                        case BRO30_DCU:
                            if (in_dcu_bup_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.bup_state.msg;
                                mj_handle.in.dcu.bup_state.msg = (bup_drv_state_msg_t *)data;
                                mj_handle.in.dcu.bup_state.ts_s  = ts_s;
                                mj_handle.in.dcu.bup_state.ts_ns = ts_ns;
                                in_dcu_bup_state_updated = 1;
                                in_dcu_bup_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.bup_state.msg->hdr.cnt - in_dcu_bup_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_bup_state_miss += cnt_diff;
                                }
                                in_dcu_bup_state_last_cnt = mj_handle.in.dcu.bup_state.msg->hdr.cnt;
                                dcu_bup_state_rx_tick = ticks;
                                mj_handle.in.dcu.bup_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_bup_state_delayed_ptr == NULL)
                                {
                                    in_dcu_bup_state_delayed_ptr = (bup_drv_state_msg_t *)data;
                                    dcu_bup_state_delayed_ts_s = ts_s;
                                    dcu_bup_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.bup_state.irq){
                                mj_handle.in.dcu.bup_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            default:
                return MJ_REJECT_ID;    
        }
    }
    return MJ_REJECT_DST; 
}


static mj_msg_proc_res_t bro_bup_srv_mcast_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
            // dbg
            case ID_DBG:
                if (size == sizeof(dbg_data_msg_t))
                {
                    switch (hdr->src)
                    {
                        // dbg from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_dbg_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.dbg.msg;
                                mj_handle.in.bup_dcu_lfd.dbg.msg = (dbg_data_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.dbg.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.dbg.ts_ns = ts_ns;
                                in_bup_dcu_lfd_dbg_updated = 1;
                                in_bup_dcu_lfd_dbg_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.dbg.msg->hdr.cnt - in_bup_dcu_lfd_dbg_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_dbg_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_dbg_last_cnt = mj_handle.in.bup_dcu_lfd.dbg.msg->hdr.cnt;
                                bup_dcu_lfd_dbg_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.dbg.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_dbg_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_dbg_delayed_ptr = (dbg_data_msg_t *)data;
                                    bup_dcu_lfd_dbg_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_dbg_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.dbg.irq){
                                mj_handle.in.bup_dcu_lfd.dbg.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dbg from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_dbg_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.dbg.msg;
                                mj_handle.in.bup_dcu_lrd.dbg.msg = (dbg_data_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.dbg.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.dbg.ts_ns = ts_ns;
                                in_bup_dcu_lrd_dbg_updated = 1;
                                in_bup_dcu_lrd_dbg_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.dbg.msg->hdr.cnt - in_bup_dcu_lrd_dbg_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_dbg_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_dbg_last_cnt = mj_handle.in.bup_dcu_lrd.dbg.msg->hdr.cnt;
                                bup_dcu_lrd_dbg_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.dbg.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_dbg_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_dbg_delayed_ptr = (dbg_data_msg_t *)data;
                                    bup_dcu_lrd_dbg_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_dbg_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.dbg.irq){
                                mj_handle.in.bup_dcu_lrd.dbg.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dbg from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_dbg_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.dbg.msg;
                                mj_handle.in.bup_dcu_lst.dbg.msg = (dbg_data_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.dbg.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.dbg.ts_ns = ts_ns;
                                in_bup_dcu_lst_dbg_updated = 1;
                                in_bup_dcu_lst_dbg_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.dbg.msg->hdr.cnt - in_bup_dcu_lst_dbg_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_dbg_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_dbg_last_cnt = mj_handle.in.bup_dcu_lst.dbg.msg->hdr.cnt;
                                bup_dcu_lst_dbg_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.dbg.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_dbg_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_dbg_delayed_ptr = (dbg_data_msg_t *)data;
                                    bup_dcu_lst_dbg_delayed_ts_s = ts_s;
                                    bup_dcu_lst_dbg_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.dbg.irq){
                                mj_handle.in.bup_dcu_lst.dbg.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dbg from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_dbg_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.dbg.msg;
                                mj_handle.in.bup_dcu_rfd.dbg.msg = (dbg_data_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.dbg.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.dbg.ts_ns = ts_ns;
                                in_bup_dcu_rfd_dbg_updated = 1;
                                in_bup_dcu_rfd_dbg_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.dbg.msg->hdr.cnt - in_bup_dcu_rfd_dbg_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_dbg_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_dbg_last_cnt = mj_handle.in.bup_dcu_rfd.dbg.msg->hdr.cnt;
                                bup_dcu_rfd_dbg_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.dbg.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_dbg_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_dbg_delayed_ptr = (dbg_data_msg_t *)data;
                                    bup_dcu_rfd_dbg_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_dbg_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.dbg.irq){
                                mj_handle.in.bup_dcu_rfd.dbg.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dbg from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_dbg_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.dbg.msg;
                                mj_handle.in.bup_dcu_rrd.dbg.msg = (dbg_data_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.dbg.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.dbg.ts_ns = ts_ns;
                                in_bup_dcu_rrd_dbg_updated = 1;
                                in_bup_dcu_rrd_dbg_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.dbg.msg->hdr.cnt - in_bup_dcu_rrd_dbg_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_dbg_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_dbg_last_cnt = mj_handle.in.bup_dcu_rrd.dbg.msg->hdr.cnt;
                                bup_dcu_rrd_dbg_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.dbg.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_dbg_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_dbg_delayed_ptr = (dbg_data_msg_t *)data;
                                    bup_dcu_rrd_dbg_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_dbg_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.dbg.irq){
                                mj_handle.in.bup_dcu_rrd.dbg.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dbg from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_dbg_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.dbg.msg;
                                mj_handle.in.bup_dcu_rst.dbg.msg = (dbg_data_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.dbg.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.dbg.ts_ns = ts_ns;
                                in_bup_dcu_rst_dbg_updated = 1;
                                in_bup_dcu_rst_dbg_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.dbg.msg->hdr.cnt - in_bup_dcu_rst_dbg_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_dbg_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_dbg_last_cnt = mj_handle.in.bup_dcu_rst.dbg.msg->hdr.cnt;
                                bup_dcu_rst_dbg_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.dbg.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_dbg_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_dbg_delayed_ptr = (dbg_data_msg_t *)data;
                                    bup_dcu_rst_dbg_delayed_ts_s = ts_s;
                                    bup_dcu_rst_dbg_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.dbg.irq){
                                mj_handle.in.bup_dcu_rst.dbg.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dbg from dcu
                        case BRO30_DCU:
                            if (in_dcu_dbg_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.dbg.msg;
                                mj_handle.in.dcu.dbg.msg = (dbg_data_msg_t *)data;
                                mj_handle.in.dcu.dbg.ts_s  = ts_s;
                                mj_handle.in.dcu.dbg.ts_ns = ts_ns;
                                in_dcu_dbg_updated = 1;
                                in_dcu_dbg_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.dbg.msg->hdr.cnt - in_dcu_dbg_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_dbg_miss += cnt_diff;
                                }
                                in_dcu_dbg_last_cnt = mj_handle.in.dcu.dbg.msg->hdr.cnt;
                                dcu_dbg_rx_tick = ticks;
                                mj_handle.in.dcu.dbg.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_dbg_delayed_ptr == NULL)
                                {
                                    in_dcu_dbg_delayed_ptr = (dbg_data_msg_t *)data;
                                    dcu_dbg_delayed_ts_s = ts_s;
                                    dcu_dbg_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.dbg.irq){
                                mj_handle.in.dcu.dbg.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            // dcu_tel
            case ID_DCU_TEL:
                if (size == sizeof(dcu_telemetry_msg_t))
                {
                    switch (hdr->src)
                    {
                        // dcu_tel from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_dcu_tel_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.dcu_tel.msg;
                                mj_handle.in.bup_dcu_lfd.dcu_tel.msg = (dcu_telemetry_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.dcu_tel.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.dcu_tel.ts_ns = ts_ns;
                                in_bup_dcu_lfd_dcu_tel_updated = 1;
                                in_bup_dcu_lfd_dcu_tel_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.dcu_tel.msg->hdr.cnt - in_bup_dcu_lfd_dcu_tel_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_dcu_tel_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_dcu_tel_last_cnt = mj_handle.in.bup_dcu_lfd.dcu_tel.msg->hdr.cnt;
                                bup_dcu_lfd_dcu_tel_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.dcu_tel.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_dcu_tel_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_dcu_tel_delayed_ptr = (dcu_telemetry_msg_t *)data;
                                    bup_dcu_lfd_dcu_tel_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_dcu_tel_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.dcu_tel.irq){
                                mj_handle.in.bup_dcu_lfd.dcu_tel.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dcu_tel from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_dcu_tel_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.dcu_tel.msg;
                                mj_handle.in.bup_dcu_lrd.dcu_tel.msg = (dcu_telemetry_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.dcu_tel.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.dcu_tel.ts_ns = ts_ns;
                                in_bup_dcu_lrd_dcu_tel_updated = 1;
                                in_bup_dcu_lrd_dcu_tel_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.dcu_tel.msg->hdr.cnt - in_bup_dcu_lrd_dcu_tel_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_dcu_tel_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_dcu_tel_last_cnt = mj_handle.in.bup_dcu_lrd.dcu_tel.msg->hdr.cnt;
                                bup_dcu_lrd_dcu_tel_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.dcu_tel.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_dcu_tel_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_dcu_tel_delayed_ptr = (dcu_telemetry_msg_t *)data;
                                    bup_dcu_lrd_dcu_tel_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_dcu_tel_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.dcu_tel.irq){
                                mj_handle.in.bup_dcu_lrd.dcu_tel.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dcu_tel from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_dcu_tel_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.dcu_tel.msg;
                                mj_handle.in.bup_dcu_lst.dcu_tel.msg = (dcu_telemetry_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.dcu_tel.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.dcu_tel.ts_ns = ts_ns;
                                in_bup_dcu_lst_dcu_tel_updated = 1;
                                in_bup_dcu_lst_dcu_tel_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.dcu_tel.msg->hdr.cnt - in_bup_dcu_lst_dcu_tel_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_dcu_tel_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_dcu_tel_last_cnt = mj_handle.in.bup_dcu_lst.dcu_tel.msg->hdr.cnt;
                                bup_dcu_lst_dcu_tel_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.dcu_tel.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_dcu_tel_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_dcu_tel_delayed_ptr = (dcu_telemetry_msg_t *)data;
                                    bup_dcu_lst_dcu_tel_delayed_ts_s = ts_s;
                                    bup_dcu_lst_dcu_tel_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.dcu_tel.irq){
                                mj_handle.in.bup_dcu_lst.dcu_tel.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dcu_tel from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_dcu_tel_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.dcu_tel.msg;
                                mj_handle.in.bup_dcu_rfd.dcu_tel.msg = (dcu_telemetry_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.dcu_tel.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.dcu_tel.ts_ns = ts_ns;
                                in_bup_dcu_rfd_dcu_tel_updated = 1;
                                in_bup_dcu_rfd_dcu_tel_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.dcu_tel.msg->hdr.cnt - in_bup_dcu_rfd_dcu_tel_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_dcu_tel_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_dcu_tel_last_cnt = mj_handle.in.bup_dcu_rfd.dcu_tel.msg->hdr.cnt;
                                bup_dcu_rfd_dcu_tel_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.dcu_tel.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_dcu_tel_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_dcu_tel_delayed_ptr = (dcu_telemetry_msg_t *)data;
                                    bup_dcu_rfd_dcu_tel_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_dcu_tel_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.dcu_tel.irq){
                                mj_handle.in.bup_dcu_rfd.dcu_tel.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dcu_tel from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_dcu_tel_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.dcu_tel.msg;
                                mj_handle.in.bup_dcu_rrd.dcu_tel.msg = (dcu_telemetry_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.dcu_tel.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.dcu_tel.ts_ns = ts_ns;
                                in_bup_dcu_rrd_dcu_tel_updated = 1;
                                in_bup_dcu_rrd_dcu_tel_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.dcu_tel.msg->hdr.cnt - in_bup_dcu_rrd_dcu_tel_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_dcu_tel_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_dcu_tel_last_cnt = mj_handle.in.bup_dcu_rrd.dcu_tel.msg->hdr.cnt;
                                bup_dcu_rrd_dcu_tel_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.dcu_tel.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_dcu_tel_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_dcu_tel_delayed_ptr = (dcu_telemetry_msg_t *)data;
                                    bup_dcu_rrd_dcu_tel_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_dcu_tel_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.dcu_tel.irq){
                                mj_handle.in.bup_dcu_rrd.dcu_tel.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dcu_tel from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_dcu_tel_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.dcu_tel.msg;
                                mj_handle.in.bup_dcu_rst.dcu_tel.msg = (dcu_telemetry_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.dcu_tel.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.dcu_tel.ts_ns = ts_ns;
                                in_bup_dcu_rst_dcu_tel_updated = 1;
                                in_bup_dcu_rst_dcu_tel_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.dcu_tel.msg->hdr.cnt - in_bup_dcu_rst_dcu_tel_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_dcu_tel_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_dcu_tel_last_cnt = mj_handle.in.bup_dcu_rst.dcu_tel.msg->hdr.cnt;
                                bup_dcu_rst_dcu_tel_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.dcu_tel.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_dcu_tel_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_dcu_tel_delayed_ptr = (dcu_telemetry_msg_t *)data;
                                    bup_dcu_rst_dcu_tel_delayed_ts_s = ts_s;
                                    bup_dcu_rst_dcu_tel_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.dcu_tel.irq){
                                mj_handle.in.bup_dcu_rst.dcu_tel.irq(data);
                            }
                            return MJ_ACCEPT;
                        // dcu_tel from dcu
                        case BRO30_DCU:
                            if (in_dcu_dcu_tel_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.dcu_tel.msg;
                                mj_handle.in.dcu.dcu_tel.msg = (dcu_telemetry_msg_t *)data;
                                mj_handle.in.dcu.dcu_tel.ts_s  = ts_s;
                                mj_handle.in.dcu.dcu_tel.ts_ns = ts_ns;
                                in_dcu_dcu_tel_updated = 1;
                                in_dcu_dcu_tel_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.dcu_tel.msg->hdr.cnt - in_dcu_dcu_tel_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_dcu_tel_miss += cnt_diff;
                                }
                                in_dcu_dcu_tel_last_cnt = mj_handle.in.dcu.dcu_tel.msg->hdr.cnt;
                                dcu_dcu_tel_rx_tick = ticks;
                                mj_handle.in.dcu.dcu_tel.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_dcu_tel_delayed_ptr == NULL)
                                {
                                    in_dcu_dcu_tel_delayed_ptr = (dcu_telemetry_msg_t *)data;
                                    dcu_dcu_tel_delayed_ts_s = ts_s;
                                    dcu_dcu_tel_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.dcu_tel.irq){
                                mj_handle.in.dcu.dcu_tel.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            // ptp_state
            case ID_PTP_STATE:
                if (size == sizeof(ptp_info_msg_t))
                {
                    switch (hdr->src)
                    {
                        // ptp_state from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_ptp_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.ptp_state.msg;
                                mj_handle.in.bup_dcu_lfd.ptp_state.msg = (ptp_info_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.ptp_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.ptp_state.ts_ns = ts_ns;
                                in_bup_dcu_lfd_ptp_state_updated = 1;
                                in_bup_dcu_lfd_ptp_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.ptp_state.msg->hdr.cnt - in_bup_dcu_lfd_ptp_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_ptp_state_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_ptp_state_last_cnt = mj_handle.in.bup_dcu_lfd.ptp_state.msg->hdr.cnt;
                                bup_dcu_lfd_ptp_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.ptp_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_ptp_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_ptp_state_delayed_ptr = (ptp_info_msg_t *)data;
                                    bup_dcu_lfd_ptp_state_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_ptp_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.ptp_state.irq){
                                mj_handle.in.bup_dcu_lfd.ptp_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // ptp_state from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_ptp_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.ptp_state.msg;
                                mj_handle.in.bup_dcu_lrd.ptp_state.msg = (ptp_info_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.ptp_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.ptp_state.ts_ns = ts_ns;
                                in_bup_dcu_lrd_ptp_state_updated = 1;
                                in_bup_dcu_lrd_ptp_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.ptp_state.msg->hdr.cnt - in_bup_dcu_lrd_ptp_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_ptp_state_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_ptp_state_last_cnt = mj_handle.in.bup_dcu_lrd.ptp_state.msg->hdr.cnt;
                                bup_dcu_lrd_ptp_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.ptp_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_ptp_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_ptp_state_delayed_ptr = (ptp_info_msg_t *)data;
                                    bup_dcu_lrd_ptp_state_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_ptp_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.ptp_state.irq){
                                mj_handle.in.bup_dcu_lrd.ptp_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // ptp_state from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_ptp_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.ptp_state.msg;
                                mj_handle.in.bup_dcu_lst.ptp_state.msg = (ptp_info_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.ptp_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.ptp_state.ts_ns = ts_ns;
                                in_bup_dcu_lst_ptp_state_updated = 1;
                                in_bup_dcu_lst_ptp_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.ptp_state.msg->hdr.cnt - in_bup_dcu_lst_ptp_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_ptp_state_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_ptp_state_last_cnt = mj_handle.in.bup_dcu_lst.ptp_state.msg->hdr.cnt;
                                bup_dcu_lst_ptp_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.ptp_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_ptp_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_ptp_state_delayed_ptr = (ptp_info_msg_t *)data;
                                    bup_dcu_lst_ptp_state_delayed_ts_s = ts_s;
                                    bup_dcu_lst_ptp_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.ptp_state.irq){
                                mj_handle.in.bup_dcu_lst.ptp_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // ptp_state from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_ptp_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.ptp_state.msg;
                                mj_handle.in.bup_dcu_rfd.ptp_state.msg = (ptp_info_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.ptp_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.ptp_state.ts_ns = ts_ns;
                                in_bup_dcu_rfd_ptp_state_updated = 1;
                                in_bup_dcu_rfd_ptp_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.ptp_state.msg->hdr.cnt - in_bup_dcu_rfd_ptp_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_ptp_state_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_ptp_state_last_cnt = mj_handle.in.bup_dcu_rfd.ptp_state.msg->hdr.cnt;
                                bup_dcu_rfd_ptp_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.ptp_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_ptp_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_ptp_state_delayed_ptr = (ptp_info_msg_t *)data;
                                    bup_dcu_rfd_ptp_state_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_ptp_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.ptp_state.irq){
                                mj_handle.in.bup_dcu_rfd.ptp_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // ptp_state from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_ptp_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.ptp_state.msg;
                                mj_handle.in.bup_dcu_rrd.ptp_state.msg = (ptp_info_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.ptp_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.ptp_state.ts_ns = ts_ns;
                                in_bup_dcu_rrd_ptp_state_updated = 1;
                                in_bup_dcu_rrd_ptp_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.ptp_state.msg->hdr.cnt - in_bup_dcu_rrd_ptp_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_ptp_state_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_ptp_state_last_cnt = mj_handle.in.bup_dcu_rrd.ptp_state.msg->hdr.cnt;
                                bup_dcu_rrd_ptp_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.ptp_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_ptp_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_ptp_state_delayed_ptr = (ptp_info_msg_t *)data;
                                    bup_dcu_rrd_ptp_state_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_ptp_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.ptp_state.irq){
                                mj_handle.in.bup_dcu_rrd.ptp_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // ptp_state from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_ptp_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.ptp_state.msg;
                                mj_handle.in.bup_dcu_rst.ptp_state.msg = (ptp_info_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.ptp_state.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.ptp_state.ts_ns = ts_ns;
                                in_bup_dcu_rst_ptp_state_updated = 1;
                                in_bup_dcu_rst_ptp_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.ptp_state.msg->hdr.cnt - in_bup_dcu_rst_ptp_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_ptp_state_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_ptp_state_last_cnt = mj_handle.in.bup_dcu_rst.ptp_state.msg->hdr.cnt;
                                bup_dcu_rst_ptp_state_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.ptp_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_ptp_state_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_ptp_state_delayed_ptr = (ptp_info_msg_t *)data;
                                    bup_dcu_rst_ptp_state_delayed_ts_s = ts_s;
                                    bup_dcu_rst_ptp_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.ptp_state.irq){
                                mj_handle.in.bup_dcu_rst.ptp_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        // ptp_state from dcu
                        case BRO30_DCU:
                            if (in_dcu_ptp_state_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.ptp_state.msg;
                                mj_handle.in.dcu.ptp_state.msg = (ptp_info_msg_t *)data;
                                mj_handle.in.dcu.ptp_state.ts_s  = ts_s;
                                mj_handle.in.dcu.ptp_state.ts_ns = ts_ns;
                                in_dcu_ptp_state_updated = 1;
                                in_dcu_ptp_state_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.ptp_state.msg->hdr.cnt - in_dcu_ptp_state_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_ptp_state_miss += cnt_diff;
                                }
                                in_dcu_ptp_state_last_cnt = mj_handle.in.dcu.ptp_state.msg->hdr.cnt;
                                dcu_ptp_state_rx_tick = ticks;
                                mj_handle.in.dcu.ptp_state.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_ptp_state_delayed_ptr == NULL)
                                {
                                    in_dcu_ptp_state_delayed_ptr = (ptp_info_msg_t *)data;
                                    dcu_ptp_state_delayed_ts_s = ts_s;
                                    dcu_ptp_state_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.ptp_state.irq){
                                mj_handle.in.dcu.ptp_state.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            default:
                return MJ_REJECT_ID;    
        }
    }
    return MJ_REJECT_DST; 
}


static mj_msg_proc_res_t bup_internal_mcast_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
            // drive_master_ctrl
            case ID_DRIVE_MASTER_CTRL:
                if (size == sizeof(drive_master_ctrl_msg_t))
                {
                    switch (hdr->src)
                    {
                        // drive_master_ctrl from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_drive_master_ctrl_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg;
                                mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.drive_master_ctrl.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.drive_master_ctrl.ts_ns = ts_ns;
                                in_bup_dcu_lfd_drive_master_ctrl_updated = 1;
                                in_bup_dcu_lfd_drive_master_ctrl_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg->hdr.cnt - in_bup_dcu_lfd_drive_master_ctrl_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_drive_master_ctrl_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_drive_master_ctrl_last_cnt = mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg->hdr.cnt;
                                bup_dcu_lfd_drive_master_ctrl_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_drive_master_ctrl_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_drive_master_ctrl_delayed_ptr = (drive_master_ctrl_msg_t *)data;
                                    bup_dcu_lfd_drive_master_ctrl_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_drive_master_ctrl_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.drive_master_ctrl.irq){
                                mj_handle.in.bup_dcu_lfd.drive_master_ctrl.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_master_ctrl from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_drive_master_ctrl_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg;
                                mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.drive_master_ctrl.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.drive_master_ctrl.ts_ns = ts_ns;
                                in_bup_dcu_lrd_drive_master_ctrl_updated = 1;
                                in_bup_dcu_lrd_drive_master_ctrl_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg->hdr.cnt - in_bup_dcu_lrd_drive_master_ctrl_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_drive_master_ctrl_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_drive_master_ctrl_last_cnt = mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg->hdr.cnt;
                                bup_dcu_lrd_drive_master_ctrl_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_drive_master_ctrl_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_drive_master_ctrl_delayed_ptr = (drive_master_ctrl_msg_t *)data;
                                    bup_dcu_lrd_drive_master_ctrl_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_drive_master_ctrl_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.drive_master_ctrl.irq){
                                mj_handle.in.bup_dcu_lrd.drive_master_ctrl.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_master_ctrl from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_drive_master_ctrl_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg;
                                mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.drive_master_ctrl.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.drive_master_ctrl.ts_ns = ts_ns;
                                in_bup_dcu_lst_drive_master_ctrl_updated = 1;
                                in_bup_dcu_lst_drive_master_ctrl_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg->hdr.cnt - in_bup_dcu_lst_drive_master_ctrl_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_drive_master_ctrl_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_drive_master_ctrl_last_cnt = mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg->hdr.cnt;
                                bup_dcu_lst_drive_master_ctrl_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_drive_master_ctrl_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_drive_master_ctrl_delayed_ptr = (drive_master_ctrl_msg_t *)data;
                                    bup_dcu_lst_drive_master_ctrl_delayed_ts_s = ts_s;
                                    bup_dcu_lst_drive_master_ctrl_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.drive_master_ctrl.irq){
                                mj_handle.in.bup_dcu_lst.drive_master_ctrl.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_master_ctrl from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_drive_master_ctrl_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg;
                                mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.drive_master_ctrl.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.drive_master_ctrl.ts_ns = ts_ns;
                                in_bup_dcu_rfd_drive_master_ctrl_updated = 1;
                                in_bup_dcu_rfd_drive_master_ctrl_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg->hdr.cnt - in_bup_dcu_rfd_drive_master_ctrl_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_drive_master_ctrl_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_drive_master_ctrl_last_cnt = mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg->hdr.cnt;
                                bup_dcu_rfd_drive_master_ctrl_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_drive_master_ctrl_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_drive_master_ctrl_delayed_ptr = (drive_master_ctrl_msg_t *)data;
                                    bup_dcu_rfd_drive_master_ctrl_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_drive_master_ctrl_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.drive_master_ctrl.irq){
                                mj_handle.in.bup_dcu_rfd.drive_master_ctrl.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_master_ctrl from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_drive_master_ctrl_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg;
                                mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.drive_master_ctrl.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.drive_master_ctrl.ts_ns = ts_ns;
                                in_bup_dcu_rrd_drive_master_ctrl_updated = 1;
                                in_bup_dcu_rrd_drive_master_ctrl_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg->hdr.cnt - in_bup_dcu_rrd_drive_master_ctrl_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_drive_master_ctrl_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_drive_master_ctrl_last_cnt = mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg->hdr.cnt;
                                bup_dcu_rrd_drive_master_ctrl_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_drive_master_ctrl_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_drive_master_ctrl_delayed_ptr = (drive_master_ctrl_msg_t *)data;
                                    bup_dcu_rrd_drive_master_ctrl_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_drive_master_ctrl_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.drive_master_ctrl.irq){
                                mj_handle.in.bup_dcu_rrd.drive_master_ctrl.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_master_ctrl from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_drive_master_ctrl_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg;
                                mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.drive_master_ctrl.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.drive_master_ctrl.ts_ns = ts_ns;
                                in_bup_dcu_rst_drive_master_ctrl_updated = 1;
                                in_bup_dcu_rst_drive_master_ctrl_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg->hdr.cnt - in_bup_dcu_rst_drive_master_ctrl_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_drive_master_ctrl_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_drive_master_ctrl_last_cnt = mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg->hdr.cnt;
                                bup_dcu_rst_drive_master_ctrl_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_drive_master_ctrl_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_drive_master_ctrl_delayed_ptr = (drive_master_ctrl_msg_t *)data;
                                    bup_dcu_rst_drive_master_ctrl_delayed_ts_s = ts_s;
                                    bup_dcu_rst_drive_master_ctrl_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.drive_master_ctrl.irq){
                                mj_handle.in.bup_dcu_rst.drive_master_ctrl.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_master_ctrl from dcu
                        case BRO30_DCU:
                            if (in_dcu_drive_master_ctrl_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.drive_master_ctrl.msg;
                                mj_handle.in.dcu.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)data;
                                mj_handle.in.dcu.drive_master_ctrl.ts_s  = ts_s;
                                mj_handle.in.dcu.drive_master_ctrl.ts_ns = ts_ns;
                                in_dcu_drive_master_ctrl_updated = 1;
                                in_dcu_drive_master_ctrl_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.drive_master_ctrl.msg->hdr.cnt - in_dcu_drive_master_ctrl_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_drive_master_ctrl_miss += cnt_diff;
                                }
                                in_dcu_drive_master_ctrl_last_cnt = mj_handle.in.dcu.drive_master_ctrl.msg->hdr.cnt;
                                dcu_drive_master_ctrl_rx_tick = ticks;
                                mj_handle.in.dcu.drive_master_ctrl.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_drive_master_ctrl_delayed_ptr == NULL)
                                {
                                    in_dcu_drive_master_ctrl_delayed_ptr = (drive_master_ctrl_msg_t *)data;
                                    dcu_drive_master_ctrl_delayed_ts_s = ts_s;
                                    dcu_drive_master_ctrl_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.drive_master_ctrl.irq){
                                mj_handle.in.dcu.drive_master_ctrl.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            // drive_slave_fb
            case ID_DRIVE_SLAVE_FB:
                if (size == sizeof(drive_slave_fb_msg_t))
                {
                    switch (hdr->src)
                    {
                        // drive_slave_fb from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_drive_slave_fb_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg;
                                mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg = (drive_slave_fb_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.drive_slave_fb.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.drive_slave_fb.ts_ns = ts_ns;
                                in_bup_dcu_lfd_drive_slave_fb_updated = 1;
                                in_bup_dcu_lfd_drive_slave_fb_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg->hdr.cnt - in_bup_dcu_lfd_drive_slave_fb_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_drive_slave_fb_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_drive_slave_fb_last_cnt = mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg->hdr.cnt;
                                bup_dcu_lfd_drive_slave_fb_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.drive_slave_fb.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_drive_slave_fb_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_drive_slave_fb_delayed_ptr = (drive_slave_fb_msg_t *)data;
                                    bup_dcu_lfd_drive_slave_fb_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_drive_slave_fb_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.drive_slave_fb.irq){
                                mj_handle.in.bup_dcu_lfd.drive_slave_fb.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_slave_fb from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_drive_slave_fb_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg;
                                mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg = (drive_slave_fb_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.drive_slave_fb.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.drive_slave_fb.ts_ns = ts_ns;
                                in_bup_dcu_lrd_drive_slave_fb_updated = 1;
                                in_bup_dcu_lrd_drive_slave_fb_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg->hdr.cnt - in_bup_dcu_lrd_drive_slave_fb_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_drive_slave_fb_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_drive_slave_fb_last_cnt = mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg->hdr.cnt;
                                bup_dcu_lrd_drive_slave_fb_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.drive_slave_fb.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_drive_slave_fb_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_drive_slave_fb_delayed_ptr = (drive_slave_fb_msg_t *)data;
                                    bup_dcu_lrd_drive_slave_fb_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_drive_slave_fb_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.drive_slave_fb.irq){
                                mj_handle.in.bup_dcu_lrd.drive_slave_fb.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_slave_fb from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_drive_slave_fb_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.drive_slave_fb.msg;
                                mj_handle.in.bup_dcu_lst.drive_slave_fb.msg = (drive_slave_fb_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.drive_slave_fb.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.drive_slave_fb.ts_ns = ts_ns;
                                in_bup_dcu_lst_drive_slave_fb_updated = 1;
                                in_bup_dcu_lst_drive_slave_fb_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.drive_slave_fb.msg->hdr.cnt - in_bup_dcu_lst_drive_slave_fb_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_drive_slave_fb_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_drive_slave_fb_last_cnt = mj_handle.in.bup_dcu_lst.drive_slave_fb.msg->hdr.cnt;
                                bup_dcu_lst_drive_slave_fb_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.drive_slave_fb.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_drive_slave_fb_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_drive_slave_fb_delayed_ptr = (drive_slave_fb_msg_t *)data;
                                    bup_dcu_lst_drive_slave_fb_delayed_ts_s = ts_s;
                                    bup_dcu_lst_drive_slave_fb_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.drive_slave_fb.irq){
                                mj_handle.in.bup_dcu_lst.drive_slave_fb.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_slave_fb from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_drive_slave_fb_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg;
                                mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg = (drive_slave_fb_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.drive_slave_fb.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.drive_slave_fb.ts_ns = ts_ns;
                                in_bup_dcu_rfd_drive_slave_fb_updated = 1;
                                in_bup_dcu_rfd_drive_slave_fb_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg->hdr.cnt - in_bup_dcu_rfd_drive_slave_fb_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_drive_slave_fb_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_drive_slave_fb_last_cnt = mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg->hdr.cnt;
                                bup_dcu_rfd_drive_slave_fb_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.drive_slave_fb.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_drive_slave_fb_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_drive_slave_fb_delayed_ptr = (drive_slave_fb_msg_t *)data;
                                    bup_dcu_rfd_drive_slave_fb_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_drive_slave_fb_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.drive_slave_fb.irq){
                                mj_handle.in.bup_dcu_rfd.drive_slave_fb.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_slave_fb from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_drive_slave_fb_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg;
                                mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg = (drive_slave_fb_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.drive_slave_fb.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.drive_slave_fb.ts_ns = ts_ns;
                                in_bup_dcu_rrd_drive_slave_fb_updated = 1;
                                in_bup_dcu_rrd_drive_slave_fb_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg->hdr.cnt - in_bup_dcu_rrd_drive_slave_fb_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_drive_slave_fb_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_drive_slave_fb_last_cnt = mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg->hdr.cnt;
                                bup_dcu_rrd_drive_slave_fb_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.drive_slave_fb.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_drive_slave_fb_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_drive_slave_fb_delayed_ptr = (drive_slave_fb_msg_t *)data;
                                    bup_dcu_rrd_drive_slave_fb_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_drive_slave_fb_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.drive_slave_fb.irq){
                                mj_handle.in.bup_dcu_rrd.drive_slave_fb.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_slave_fb from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_drive_slave_fb_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.drive_slave_fb.msg;
                                mj_handle.in.bup_dcu_rst.drive_slave_fb.msg = (drive_slave_fb_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.drive_slave_fb.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.drive_slave_fb.ts_ns = ts_ns;
                                in_bup_dcu_rst_drive_slave_fb_updated = 1;
                                in_bup_dcu_rst_drive_slave_fb_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.drive_slave_fb.msg->hdr.cnt - in_bup_dcu_rst_drive_slave_fb_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_drive_slave_fb_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_drive_slave_fb_last_cnt = mj_handle.in.bup_dcu_rst.drive_slave_fb.msg->hdr.cnt;
                                bup_dcu_rst_drive_slave_fb_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.drive_slave_fb.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_drive_slave_fb_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_drive_slave_fb_delayed_ptr = (drive_slave_fb_msg_t *)data;
                                    bup_dcu_rst_drive_slave_fb_delayed_ts_s = ts_s;
                                    bup_dcu_rst_drive_slave_fb_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.drive_slave_fb.irq){
                                mj_handle.in.bup_dcu_rst.drive_slave_fb.irq(data);
                            }
                            return MJ_ACCEPT;
                        // drive_slave_fb from dcu
                        case BRO30_DCU:
                            if (in_dcu_drive_slave_fb_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.drive_slave_fb.msg;
                                mj_handle.in.dcu.drive_slave_fb.msg = (drive_slave_fb_msg_t *)data;
                                mj_handle.in.dcu.drive_slave_fb.ts_s  = ts_s;
                                mj_handle.in.dcu.drive_slave_fb.ts_ns = ts_ns;
                                in_dcu_drive_slave_fb_updated = 1;
                                in_dcu_drive_slave_fb_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.drive_slave_fb.msg->hdr.cnt - in_dcu_drive_slave_fb_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_drive_slave_fb_miss += cnt_diff;
                                }
                                in_dcu_drive_slave_fb_last_cnt = mj_handle.in.dcu.drive_slave_fb.msg->hdr.cnt;
                                dcu_drive_slave_fb_rx_tick = ticks;
                                mj_handle.in.dcu.drive_slave_fb.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_drive_slave_fb_delayed_ptr == NULL)
                                {
                                    in_dcu_drive_slave_fb_delayed_ptr = (drive_slave_fb_msg_t *)data;
                                    dcu_drive_slave_fb_delayed_ts_s = ts_s;
                                    dcu_drive_slave_fb_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.drive_slave_fb.irq){
                                mj_handle.in.dcu.drive_slave_fb.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            default:
                return MJ_REJECT_ID;    
        }
    }
    return MJ_REJECT_DST; 
}


static mj_msg_proc_res_t im_bro_drive_ctrl_mcast_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
            // im_bro_drive_ctrl
            case ID_IM_BRO_DRIVE_CTRL:
            default:
                return MJ_REJECT_ID;    
        }
    }
    return MJ_REJECT_DST; 
}


static mj_msg_proc_res_t im_bro_drive_mcast_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
            // im_bro_drivers_sens
            case ID_IM_BRO_DRIVERS_SENS:
                if (size == sizeof(drivers_sens_msg_t))
                {
                    switch (hdr->src)
                    {
                        // im_bro_drivers_sens from im_bro
                        case BRO30_IM_BRO:
                            if (in_im_bro_im_bro_drivers_sens_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.im_bro.im_bro_drivers_sens.msg;
                                mj_handle.in.im_bro.im_bro_drivers_sens.msg = (drivers_sens_msg_t *)data;
                                mj_handle.in.im_bro.im_bro_drivers_sens.ts_s  = ts_s;
                                mj_handle.in.im_bro.im_bro_drivers_sens.ts_ns = ts_ns;
                                in_im_bro_im_bro_drivers_sens_updated = 1;
                                in_im_bro_im_bro_drivers_sens_total++;
                                uint16_t cnt_diff = (mj_handle.in.im_bro.im_bro_drivers_sens.msg->hdr.cnt - in_im_bro_im_bro_drivers_sens_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_im_bro_im_bro_drivers_sens_miss += cnt_diff;
                                }
                                in_im_bro_im_bro_drivers_sens_last_cnt = mj_handle.in.im_bro.im_bro_drivers_sens.msg->hdr.cnt;
                                im_bro_im_bro_drivers_sens_rx_tick = ticks;
                                mj_handle.in.im_bro.im_bro_drivers_sens.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_im_bro_im_bro_drivers_sens_delayed_ptr == NULL)
                                {
                                    in_im_bro_im_bro_drivers_sens_delayed_ptr = (drivers_sens_msg_t *)data;
                                    im_bro_im_bro_drivers_sens_delayed_ts_s = ts_s;
                                    im_bro_im_bro_drivers_sens_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.im_bro.im_bro_drivers_sens.irq){
                                mj_handle.in.im_bro.im_bro_drivers_sens.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            default:
                return MJ_REJECT_ID;    
        }
    }
    return MJ_REJECT_DST; 
}


static mj_msg_proc_res_t srv_mcast_ans_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
            // cmd_ans
            case ID_CMD_ANS:
                if (size == sizeof(command_answer_msg_t))
                {
                    switch (hdr->src)
                    {
                        // cmd_ans from aufd
                        case BRO30_AUFD:
                            if (in_aufd_cmd_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.aufd.cmd_ans.msg;
                                mj_handle.in.aufd.cmd_ans.msg = (command_answer_msg_t *)data;
                                mj_handle.in.aufd.cmd_ans.ts_s  = ts_s;
                                mj_handle.in.aufd.cmd_ans.ts_ns = ts_ns;
                                in_aufd_cmd_ans_updated = 1;
                                in_aufd_cmd_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.aufd.cmd_ans.msg->hdr.cnt - in_aufd_cmd_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_aufd_cmd_ans_miss += cnt_diff;
                                }
                                in_aufd_cmd_ans_last_cnt = mj_handle.in.aufd.cmd_ans.msg->hdr.cnt;
                                aufd_cmd_ans_rx_tick = ticks;
                                mj_handle.in.aufd.cmd_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_aufd_cmd_ans_delayed_ptr == NULL)
                                {
                                    in_aufd_cmd_ans_delayed_ptr = (command_answer_msg_t *)data;
                                    aufd_cmd_ans_delayed_ts_s = ts_s;
                                    aufd_cmd_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.aufd.cmd_ans.irq){
                                mj_handle.in.aufd.cmd_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // cmd_ans from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_cmd_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.cmd_ans.msg;
                                mj_handle.in.bup_dcu_lfd.cmd_ans.msg = (command_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.cmd_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.cmd_ans.ts_ns = ts_ns;
                                in_bup_dcu_lfd_cmd_ans_updated = 1;
                                in_bup_dcu_lfd_cmd_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.cmd_ans.msg->hdr.cnt - in_bup_dcu_lfd_cmd_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_cmd_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_cmd_ans_last_cnt = mj_handle.in.bup_dcu_lfd.cmd_ans.msg->hdr.cnt;
                                bup_dcu_lfd_cmd_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.cmd_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_cmd_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_cmd_ans_delayed_ptr = (command_answer_msg_t *)data;
                                    bup_dcu_lfd_cmd_ans_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_cmd_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.cmd_ans.irq){
                                mj_handle.in.bup_dcu_lfd.cmd_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // cmd_ans from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_cmd_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.cmd_ans.msg;
                                mj_handle.in.bup_dcu_lrd.cmd_ans.msg = (command_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.cmd_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.cmd_ans.ts_ns = ts_ns;
                                in_bup_dcu_lrd_cmd_ans_updated = 1;
                                in_bup_dcu_lrd_cmd_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.cmd_ans.msg->hdr.cnt - in_bup_dcu_lrd_cmd_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_cmd_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_cmd_ans_last_cnt = mj_handle.in.bup_dcu_lrd.cmd_ans.msg->hdr.cnt;
                                bup_dcu_lrd_cmd_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.cmd_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_cmd_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_cmd_ans_delayed_ptr = (command_answer_msg_t *)data;
                                    bup_dcu_lrd_cmd_ans_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_cmd_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.cmd_ans.irq){
                                mj_handle.in.bup_dcu_lrd.cmd_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // cmd_ans from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_cmd_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.cmd_ans.msg;
                                mj_handle.in.bup_dcu_lst.cmd_ans.msg = (command_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.cmd_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.cmd_ans.ts_ns = ts_ns;
                                in_bup_dcu_lst_cmd_ans_updated = 1;
                                in_bup_dcu_lst_cmd_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.cmd_ans.msg->hdr.cnt - in_bup_dcu_lst_cmd_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_cmd_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_cmd_ans_last_cnt = mj_handle.in.bup_dcu_lst.cmd_ans.msg->hdr.cnt;
                                bup_dcu_lst_cmd_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.cmd_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_cmd_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_cmd_ans_delayed_ptr = (command_answer_msg_t *)data;
                                    bup_dcu_lst_cmd_ans_delayed_ts_s = ts_s;
                                    bup_dcu_lst_cmd_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.cmd_ans.irq){
                                mj_handle.in.bup_dcu_lst.cmd_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // cmd_ans from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_cmd_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.cmd_ans.msg;
                                mj_handle.in.bup_dcu_rfd.cmd_ans.msg = (command_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.cmd_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.cmd_ans.ts_ns = ts_ns;
                                in_bup_dcu_rfd_cmd_ans_updated = 1;
                                in_bup_dcu_rfd_cmd_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.cmd_ans.msg->hdr.cnt - in_bup_dcu_rfd_cmd_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_cmd_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_cmd_ans_last_cnt = mj_handle.in.bup_dcu_rfd.cmd_ans.msg->hdr.cnt;
                                bup_dcu_rfd_cmd_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.cmd_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_cmd_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_cmd_ans_delayed_ptr = (command_answer_msg_t *)data;
                                    bup_dcu_rfd_cmd_ans_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_cmd_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.cmd_ans.irq){
                                mj_handle.in.bup_dcu_rfd.cmd_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // cmd_ans from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_cmd_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.cmd_ans.msg;
                                mj_handle.in.bup_dcu_rrd.cmd_ans.msg = (command_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.cmd_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.cmd_ans.ts_ns = ts_ns;
                                in_bup_dcu_rrd_cmd_ans_updated = 1;
                                in_bup_dcu_rrd_cmd_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.cmd_ans.msg->hdr.cnt - in_bup_dcu_rrd_cmd_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_cmd_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_cmd_ans_last_cnt = mj_handle.in.bup_dcu_rrd.cmd_ans.msg->hdr.cnt;
                                bup_dcu_rrd_cmd_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.cmd_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_cmd_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_cmd_ans_delayed_ptr = (command_answer_msg_t *)data;
                                    bup_dcu_rrd_cmd_ans_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_cmd_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.cmd_ans.irq){
                                mj_handle.in.bup_dcu_rrd.cmd_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // cmd_ans from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_cmd_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.cmd_ans.msg;
                                mj_handle.in.bup_dcu_rst.cmd_ans.msg = (command_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.cmd_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.cmd_ans.ts_ns = ts_ns;
                                in_bup_dcu_rst_cmd_ans_updated = 1;
                                in_bup_dcu_rst_cmd_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.cmd_ans.msg->hdr.cnt - in_bup_dcu_rst_cmd_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_cmd_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_cmd_ans_last_cnt = mj_handle.in.bup_dcu_rst.cmd_ans.msg->hdr.cnt;
                                bup_dcu_rst_cmd_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.cmd_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_cmd_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_cmd_ans_delayed_ptr = (command_answer_msg_t *)data;
                                    bup_dcu_rst_cmd_ans_delayed_ts_s = ts_s;
                                    bup_dcu_rst_cmd_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.cmd_ans.irq){
                                mj_handle.in.bup_dcu_rst.cmd_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // cmd_ans from dcu
                        case BRO30_DCU:
                            if (in_dcu_cmd_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.cmd_ans.msg;
                                mj_handle.in.dcu.cmd_ans.msg = (command_answer_msg_t *)data;
                                mj_handle.in.dcu.cmd_ans.ts_s  = ts_s;
                                mj_handle.in.dcu.cmd_ans.ts_ns = ts_ns;
                                in_dcu_cmd_ans_updated = 1;
                                in_dcu_cmd_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.cmd_ans.msg->hdr.cnt - in_dcu_cmd_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_cmd_ans_miss += cnt_diff;
                                }
                                in_dcu_cmd_ans_last_cnt = mj_handle.in.dcu.cmd_ans.msg->hdr.cnt;
                                dcu_cmd_ans_rx_tick = ticks;
                                mj_handle.in.dcu.cmd_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_cmd_ans_delayed_ptr == NULL)
                                {
                                    in_dcu_cmd_ans_delayed_ptr = (command_answer_msg_t *)data;
                                    dcu_cmd_ans_delayed_ts_s = ts_s;
                                    dcu_cmd_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.cmd_ans.irq){
                                mj_handle.in.dcu.cmd_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            // formular
            case ID_FORMULAR:
                if (size == sizeof(formular_info_msg_t))
                {
                    switch (hdr->src)
                    {
                        // formular from aufd
                        case BRO30_AUFD:
                            if (in_aufd_formular_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.aufd.formular.msg;
                                mj_handle.in.aufd.formular.msg = (formular_info_msg_t *)data;
                                mj_handle.in.aufd.formular.ts_s  = ts_s;
                                mj_handle.in.aufd.formular.ts_ns = ts_ns;
                                in_aufd_formular_updated = 1;
                                in_aufd_formular_total++;
                                uint16_t cnt_diff = (mj_handle.in.aufd.formular.msg->hdr.cnt - in_aufd_formular_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_aufd_formular_miss += cnt_diff;
                                }
                                in_aufd_formular_last_cnt = mj_handle.in.aufd.formular.msg->hdr.cnt;
                                aufd_formular_rx_tick = ticks;
                                mj_handle.in.aufd.formular.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_aufd_formular_delayed_ptr == NULL)
                                {
                                    in_aufd_formular_delayed_ptr = (formular_info_msg_t *)data;
                                    aufd_formular_delayed_ts_s = ts_s;
                                    aufd_formular_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.aufd.formular.irq){
                                mj_handle.in.aufd.formular.irq(data);
                            }
                            return MJ_ACCEPT;
                        // formular from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_formular_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.formular.msg;
                                mj_handle.in.bup_dcu_lfd.formular.msg = (formular_info_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.formular.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.formular.ts_ns = ts_ns;
                                in_bup_dcu_lfd_formular_updated = 1;
                                in_bup_dcu_lfd_formular_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.formular.msg->hdr.cnt - in_bup_dcu_lfd_formular_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_formular_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_formular_last_cnt = mj_handle.in.bup_dcu_lfd.formular.msg->hdr.cnt;
                                bup_dcu_lfd_formular_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.formular.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_formular_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_formular_delayed_ptr = (formular_info_msg_t *)data;
                                    bup_dcu_lfd_formular_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_formular_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.formular.irq){
                                mj_handle.in.bup_dcu_lfd.formular.irq(data);
                            }
                            return MJ_ACCEPT;
                        // formular from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_formular_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.formular.msg;
                                mj_handle.in.bup_dcu_lrd.formular.msg = (formular_info_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.formular.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.formular.ts_ns = ts_ns;
                                in_bup_dcu_lrd_formular_updated = 1;
                                in_bup_dcu_lrd_formular_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.formular.msg->hdr.cnt - in_bup_dcu_lrd_formular_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_formular_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_formular_last_cnt = mj_handle.in.bup_dcu_lrd.formular.msg->hdr.cnt;
                                bup_dcu_lrd_formular_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.formular.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_formular_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_formular_delayed_ptr = (formular_info_msg_t *)data;
                                    bup_dcu_lrd_formular_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_formular_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.formular.irq){
                                mj_handle.in.bup_dcu_lrd.formular.irq(data);
                            }
                            return MJ_ACCEPT;
                        // formular from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_formular_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.formular.msg;
                                mj_handle.in.bup_dcu_lst.formular.msg = (formular_info_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.formular.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.formular.ts_ns = ts_ns;
                                in_bup_dcu_lst_formular_updated = 1;
                                in_bup_dcu_lst_formular_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.formular.msg->hdr.cnt - in_bup_dcu_lst_formular_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_formular_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_formular_last_cnt = mj_handle.in.bup_dcu_lst.formular.msg->hdr.cnt;
                                bup_dcu_lst_formular_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.formular.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_formular_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_formular_delayed_ptr = (formular_info_msg_t *)data;
                                    bup_dcu_lst_formular_delayed_ts_s = ts_s;
                                    bup_dcu_lst_formular_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.formular.irq){
                                mj_handle.in.bup_dcu_lst.formular.irq(data);
                            }
                            return MJ_ACCEPT;
                        // formular from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_formular_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.formular.msg;
                                mj_handle.in.bup_dcu_rfd.formular.msg = (formular_info_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.formular.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.formular.ts_ns = ts_ns;
                                in_bup_dcu_rfd_formular_updated = 1;
                                in_bup_dcu_rfd_formular_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.formular.msg->hdr.cnt - in_bup_dcu_rfd_formular_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_formular_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_formular_last_cnt = mj_handle.in.bup_dcu_rfd.formular.msg->hdr.cnt;
                                bup_dcu_rfd_formular_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.formular.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_formular_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_formular_delayed_ptr = (formular_info_msg_t *)data;
                                    bup_dcu_rfd_formular_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_formular_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.formular.irq){
                                mj_handle.in.bup_dcu_rfd.formular.irq(data);
                            }
                            return MJ_ACCEPT;
                        // formular from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_formular_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.formular.msg;
                                mj_handle.in.bup_dcu_rrd.formular.msg = (formular_info_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.formular.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.formular.ts_ns = ts_ns;
                                in_bup_dcu_rrd_formular_updated = 1;
                                in_bup_dcu_rrd_formular_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.formular.msg->hdr.cnt - in_bup_dcu_rrd_formular_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_formular_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_formular_last_cnt = mj_handle.in.bup_dcu_rrd.formular.msg->hdr.cnt;
                                bup_dcu_rrd_formular_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.formular.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_formular_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_formular_delayed_ptr = (formular_info_msg_t *)data;
                                    bup_dcu_rrd_formular_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_formular_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.formular.irq){
                                mj_handle.in.bup_dcu_rrd.formular.irq(data);
                            }
                            return MJ_ACCEPT;
                        // formular from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_formular_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.formular.msg;
                                mj_handle.in.bup_dcu_rst.formular.msg = (formular_info_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.formular.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.formular.ts_ns = ts_ns;
                                in_bup_dcu_rst_formular_updated = 1;
                                in_bup_dcu_rst_formular_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.formular.msg->hdr.cnt - in_bup_dcu_rst_formular_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_formular_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_formular_last_cnt = mj_handle.in.bup_dcu_rst.formular.msg->hdr.cnt;
                                bup_dcu_rst_formular_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.formular.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_formular_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_formular_delayed_ptr = (formular_info_msg_t *)data;
                                    bup_dcu_rst_formular_delayed_ts_s = ts_s;
                                    bup_dcu_rst_formular_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.formular.irq){
                                mj_handle.in.bup_dcu_rst.formular.irq(data);
                            }
                            return MJ_ACCEPT;
                        // formular from dcu
                        case BRO30_DCU:
                            if (in_dcu_formular_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.formular.msg;
                                mj_handle.in.dcu.formular.msg = (formular_info_msg_t *)data;
                                mj_handle.in.dcu.formular.ts_s  = ts_s;
                                mj_handle.in.dcu.formular.ts_ns = ts_ns;
                                in_dcu_formular_updated = 1;
                                in_dcu_formular_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.formular.msg->hdr.cnt - in_dcu_formular_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_formular_miss += cnt_diff;
                                }
                                in_dcu_formular_last_cnt = mj_handle.in.dcu.formular.msg->hdr.cnt;
                                dcu_formular_rx_tick = ticks;
                                mj_handle.in.dcu.formular.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_formular_delayed_ptr == NULL)
                                {
                                    in_dcu_formular_delayed_ptr = (formular_info_msg_t *)data;
                                    dcu_formular_delayed_ts_s = ts_s;
                                    dcu_formular_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.formular.irq){
                                mj_handle.in.dcu.formular.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            // msg_ans
            case ID_MSG_ANS:
                if (size == sizeof(msg_answer_msg_t))
                {
                    switch (hdr->src)
                    {
                        // msg_ans from aufd
                        case BRO30_AUFD:
                            if (in_aufd_msg_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.aufd.msg_ans.msg;
                                mj_handle.in.aufd.msg_ans.msg = (msg_answer_msg_t *)data;
                                mj_handle.in.aufd.msg_ans.ts_s  = ts_s;
                                mj_handle.in.aufd.msg_ans.ts_ns = ts_ns;
                                in_aufd_msg_ans_updated = 1;
                                in_aufd_msg_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.aufd.msg_ans.msg->hdr.cnt - in_aufd_msg_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_aufd_msg_ans_miss += cnt_diff;
                                }
                                in_aufd_msg_ans_last_cnt = mj_handle.in.aufd.msg_ans.msg->hdr.cnt;
                                aufd_msg_ans_rx_tick = ticks;
                                mj_handle.in.aufd.msg_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_aufd_msg_ans_delayed_ptr == NULL)
                                {
                                    in_aufd_msg_ans_delayed_ptr = (msg_answer_msg_t *)data;
                                    aufd_msg_ans_delayed_ts_s = ts_s;
                                    aufd_msg_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.aufd.msg_ans.irq){
                                mj_handle.in.aufd.msg_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // msg_ans from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_msg_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.msg_ans.msg;
                                mj_handle.in.bup_dcu_lfd.msg_ans.msg = (msg_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.msg_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.msg_ans.ts_ns = ts_ns;
                                in_bup_dcu_lfd_msg_ans_updated = 1;
                                in_bup_dcu_lfd_msg_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.msg_ans.msg->hdr.cnt - in_bup_dcu_lfd_msg_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_msg_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_msg_ans_last_cnt = mj_handle.in.bup_dcu_lfd.msg_ans.msg->hdr.cnt;
                                bup_dcu_lfd_msg_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.msg_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_msg_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_msg_ans_delayed_ptr = (msg_answer_msg_t *)data;
                                    bup_dcu_lfd_msg_ans_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_msg_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.msg_ans.irq){
                                mj_handle.in.bup_dcu_lfd.msg_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // msg_ans from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_msg_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.msg_ans.msg;
                                mj_handle.in.bup_dcu_lrd.msg_ans.msg = (msg_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.msg_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.msg_ans.ts_ns = ts_ns;
                                in_bup_dcu_lrd_msg_ans_updated = 1;
                                in_bup_dcu_lrd_msg_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.msg_ans.msg->hdr.cnt - in_bup_dcu_lrd_msg_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_msg_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_msg_ans_last_cnt = mj_handle.in.bup_dcu_lrd.msg_ans.msg->hdr.cnt;
                                bup_dcu_lrd_msg_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.msg_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_msg_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_msg_ans_delayed_ptr = (msg_answer_msg_t *)data;
                                    bup_dcu_lrd_msg_ans_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_msg_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.msg_ans.irq){
                                mj_handle.in.bup_dcu_lrd.msg_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // msg_ans from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_msg_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.msg_ans.msg;
                                mj_handle.in.bup_dcu_lst.msg_ans.msg = (msg_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.msg_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.msg_ans.ts_ns = ts_ns;
                                in_bup_dcu_lst_msg_ans_updated = 1;
                                in_bup_dcu_lst_msg_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.msg_ans.msg->hdr.cnt - in_bup_dcu_lst_msg_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_msg_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_msg_ans_last_cnt = mj_handle.in.bup_dcu_lst.msg_ans.msg->hdr.cnt;
                                bup_dcu_lst_msg_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.msg_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_msg_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_msg_ans_delayed_ptr = (msg_answer_msg_t *)data;
                                    bup_dcu_lst_msg_ans_delayed_ts_s = ts_s;
                                    bup_dcu_lst_msg_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.msg_ans.irq){
                                mj_handle.in.bup_dcu_lst.msg_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // msg_ans from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_msg_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.msg_ans.msg;
                                mj_handle.in.bup_dcu_rfd.msg_ans.msg = (msg_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.msg_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.msg_ans.ts_ns = ts_ns;
                                in_bup_dcu_rfd_msg_ans_updated = 1;
                                in_bup_dcu_rfd_msg_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.msg_ans.msg->hdr.cnt - in_bup_dcu_rfd_msg_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_msg_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_msg_ans_last_cnt = mj_handle.in.bup_dcu_rfd.msg_ans.msg->hdr.cnt;
                                bup_dcu_rfd_msg_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.msg_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_msg_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_msg_ans_delayed_ptr = (msg_answer_msg_t *)data;
                                    bup_dcu_rfd_msg_ans_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_msg_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.msg_ans.irq){
                                mj_handle.in.bup_dcu_rfd.msg_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // msg_ans from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_msg_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.msg_ans.msg;
                                mj_handle.in.bup_dcu_rrd.msg_ans.msg = (msg_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.msg_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.msg_ans.ts_ns = ts_ns;
                                in_bup_dcu_rrd_msg_ans_updated = 1;
                                in_bup_dcu_rrd_msg_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.msg_ans.msg->hdr.cnt - in_bup_dcu_rrd_msg_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_msg_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_msg_ans_last_cnt = mj_handle.in.bup_dcu_rrd.msg_ans.msg->hdr.cnt;
                                bup_dcu_rrd_msg_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.msg_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_msg_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_msg_ans_delayed_ptr = (msg_answer_msg_t *)data;
                                    bup_dcu_rrd_msg_ans_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_msg_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.msg_ans.irq){
                                mj_handle.in.bup_dcu_rrd.msg_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // msg_ans from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_msg_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.msg_ans.msg;
                                mj_handle.in.bup_dcu_rst.msg_ans.msg = (msg_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.msg_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.msg_ans.ts_ns = ts_ns;
                                in_bup_dcu_rst_msg_ans_updated = 1;
                                in_bup_dcu_rst_msg_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.msg_ans.msg->hdr.cnt - in_bup_dcu_rst_msg_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_msg_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_msg_ans_last_cnt = mj_handle.in.bup_dcu_rst.msg_ans.msg->hdr.cnt;
                                bup_dcu_rst_msg_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.msg_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_msg_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_msg_ans_delayed_ptr = (msg_answer_msg_t *)data;
                                    bup_dcu_rst_msg_ans_delayed_ts_s = ts_s;
                                    bup_dcu_rst_msg_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.msg_ans.irq){
                                mj_handle.in.bup_dcu_rst.msg_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // msg_ans from dcu
                        case BRO30_DCU:
                            if (in_dcu_msg_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.msg_ans.msg;
                                mj_handle.in.dcu.msg_ans.msg = (msg_answer_msg_t *)data;
                                mj_handle.in.dcu.msg_ans.ts_s  = ts_s;
                                mj_handle.in.dcu.msg_ans.ts_ns = ts_ns;
                                in_dcu_msg_ans_updated = 1;
                                in_dcu_msg_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.msg_ans.msg->hdr.cnt - in_dcu_msg_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_msg_ans_miss += cnt_diff;
                                }
                                in_dcu_msg_ans_last_cnt = mj_handle.in.dcu.msg_ans.msg->hdr.cnt;
                                dcu_msg_ans_rx_tick = ticks;
                                mj_handle.in.dcu.msg_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_msg_ans_delayed_ptr == NULL)
                                {
                                    in_dcu_msg_ans_delayed_ptr = (msg_answer_msg_t *)data;
                                    dcu_msg_ans_delayed_ts_s = ts_s;
                                    dcu_msg_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.msg_ans.irq){
                                mj_handle.in.dcu.msg_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            // prm_ans
            case ID_PRM_ANS:
                if (size == sizeof(parameter_answer_msg_t))
                {
                    switch (hdr->src)
                    {
                        // prm_ans from aufd
                        case BRO30_AUFD:
                            if (in_aufd_prm_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.aufd.prm_ans.msg;
                                mj_handle.in.aufd.prm_ans.msg = (parameter_answer_msg_t *)data;
                                mj_handle.in.aufd.prm_ans.ts_s  = ts_s;
                                mj_handle.in.aufd.prm_ans.ts_ns = ts_ns;
                                in_aufd_prm_ans_updated = 1;
                                in_aufd_prm_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.aufd.prm_ans.msg->hdr.cnt - in_aufd_prm_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_aufd_prm_ans_miss += cnt_diff;
                                }
                                in_aufd_prm_ans_last_cnt = mj_handle.in.aufd.prm_ans.msg->hdr.cnt;
                                aufd_prm_ans_rx_tick = ticks;
                                mj_handle.in.aufd.prm_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_aufd_prm_ans_delayed_ptr == NULL)
                                {
                                    in_aufd_prm_ans_delayed_ptr = (parameter_answer_msg_t *)data;
                                    aufd_prm_ans_delayed_ts_s = ts_s;
                                    aufd_prm_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.aufd.prm_ans.irq){
                                mj_handle.in.aufd.prm_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // prm_ans from bup_dcu_lfd
                        case BRO30_BUP_DCU_LFD:
                            if (in_bup_dcu_lfd_prm_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lfd.prm_ans.msg;
                                mj_handle.in.bup_dcu_lfd.prm_ans.msg = (parameter_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_lfd.prm_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lfd.prm_ans.ts_ns = ts_ns;
                                in_bup_dcu_lfd_prm_ans_updated = 1;
                                in_bup_dcu_lfd_prm_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lfd.prm_ans.msg->hdr.cnt - in_bup_dcu_lfd_prm_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lfd_prm_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_lfd_prm_ans_last_cnt = mj_handle.in.bup_dcu_lfd.prm_ans.msg->hdr.cnt;
                                bup_dcu_lfd_prm_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lfd.prm_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lfd_prm_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lfd_prm_ans_delayed_ptr = (parameter_answer_msg_t *)data;
                                    bup_dcu_lfd_prm_ans_delayed_ts_s = ts_s;
                                    bup_dcu_lfd_prm_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lfd.prm_ans.irq){
                                mj_handle.in.bup_dcu_lfd.prm_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // prm_ans from bup_dcu_lrd
                        case BRO30_BUP_DCU_LRD:
                            if (in_bup_dcu_lrd_prm_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lrd.prm_ans.msg;
                                mj_handle.in.bup_dcu_lrd.prm_ans.msg = (parameter_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_lrd.prm_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lrd.prm_ans.ts_ns = ts_ns;
                                in_bup_dcu_lrd_prm_ans_updated = 1;
                                in_bup_dcu_lrd_prm_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lrd.prm_ans.msg->hdr.cnt - in_bup_dcu_lrd_prm_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lrd_prm_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_lrd_prm_ans_last_cnt = mj_handle.in.bup_dcu_lrd.prm_ans.msg->hdr.cnt;
                                bup_dcu_lrd_prm_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lrd.prm_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lrd_prm_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lrd_prm_ans_delayed_ptr = (parameter_answer_msg_t *)data;
                                    bup_dcu_lrd_prm_ans_delayed_ts_s = ts_s;
                                    bup_dcu_lrd_prm_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lrd.prm_ans.irq){
                                mj_handle.in.bup_dcu_lrd.prm_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // prm_ans from bup_dcu_lst
                        case BRO30_BUP_DCU_LST:
                            if (in_bup_dcu_lst_prm_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_lst.prm_ans.msg;
                                mj_handle.in.bup_dcu_lst.prm_ans.msg = (parameter_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_lst.prm_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_lst.prm_ans.ts_ns = ts_ns;
                                in_bup_dcu_lst_prm_ans_updated = 1;
                                in_bup_dcu_lst_prm_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_lst.prm_ans.msg->hdr.cnt - in_bup_dcu_lst_prm_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_lst_prm_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_lst_prm_ans_last_cnt = mj_handle.in.bup_dcu_lst.prm_ans.msg->hdr.cnt;
                                bup_dcu_lst_prm_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_lst.prm_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_lst_prm_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_lst_prm_ans_delayed_ptr = (parameter_answer_msg_t *)data;
                                    bup_dcu_lst_prm_ans_delayed_ts_s = ts_s;
                                    bup_dcu_lst_prm_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_lst.prm_ans.irq){
                                mj_handle.in.bup_dcu_lst.prm_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // prm_ans from bup_dcu_rfd
                        case BRO30_BUP_DCU_RFD:
                            if (in_bup_dcu_rfd_prm_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rfd.prm_ans.msg;
                                mj_handle.in.bup_dcu_rfd.prm_ans.msg = (parameter_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_rfd.prm_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rfd.prm_ans.ts_ns = ts_ns;
                                in_bup_dcu_rfd_prm_ans_updated = 1;
                                in_bup_dcu_rfd_prm_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rfd.prm_ans.msg->hdr.cnt - in_bup_dcu_rfd_prm_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rfd_prm_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_rfd_prm_ans_last_cnt = mj_handle.in.bup_dcu_rfd.prm_ans.msg->hdr.cnt;
                                bup_dcu_rfd_prm_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rfd.prm_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rfd_prm_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rfd_prm_ans_delayed_ptr = (parameter_answer_msg_t *)data;
                                    bup_dcu_rfd_prm_ans_delayed_ts_s = ts_s;
                                    bup_dcu_rfd_prm_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rfd.prm_ans.irq){
                                mj_handle.in.bup_dcu_rfd.prm_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // prm_ans from bup_dcu_rrd
                        case BRO30_BUP_DCU_RRD:
                            if (in_bup_dcu_rrd_prm_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rrd.prm_ans.msg;
                                mj_handle.in.bup_dcu_rrd.prm_ans.msg = (parameter_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_rrd.prm_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rrd.prm_ans.ts_ns = ts_ns;
                                in_bup_dcu_rrd_prm_ans_updated = 1;
                                in_bup_dcu_rrd_prm_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rrd.prm_ans.msg->hdr.cnt - in_bup_dcu_rrd_prm_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rrd_prm_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_rrd_prm_ans_last_cnt = mj_handle.in.bup_dcu_rrd.prm_ans.msg->hdr.cnt;
                                bup_dcu_rrd_prm_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rrd.prm_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rrd_prm_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rrd_prm_ans_delayed_ptr = (parameter_answer_msg_t *)data;
                                    bup_dcu_rrd_prm_ans_delayed_ts_s = ts_s;
                                    bup_dcu_rrd_prm_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rrd.prm_ans.irq){
                                mj_handle.in.bup_dcu_rrd.prm_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // prm_ans from bup_dcu_rst
                        case BRO30_BUP_DCU_RST:
                            if (in_bup_dcu_rst_prm_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.bup_dcu_rst.prm_ans.msg;
                                mj_handle.in.bup_dcu_rst.prm_ans.msg = (parameter_answer_msg_t *)data;
                                mj_handle.in.bup_dcu_rst.prm_ans.ts_s  = ts_s;
                                mj_handle.in.bup_dcu_rst.prm_ans.ts_ns = ts_ns;
                                in_bup_dcu_rst_prm_ans_updated = 1;
                                in_bup_dcu_rst_prm_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.bup_dcu_rst.prm_ans.msg->hdr.cnt - in_bup_dcu_rst_prm_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_bup_dcu_rst_prm_ans_miss += cnt_diff;
                                }
                                in_bup_dcu_rst_prm_ans_last_cnt = mj_handle.in.bup_dcu_rst.prm_ans.msg->hdr.cnt;
                                bup_dcu_rst_prm_ans_rx_tick = ticks;
                                mj_handle.in.bup_dcu_rst.prm_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_bup_dcu_rst_prm_ans_delayed_ptr == NULL)
                                {
                                    in_bup_dcu_rst_prm_ans_delayed_ptr = (parameter_answer_msg_t *)data;
                                    bup_dcu_rst_prm_ans_delayed_ts_s = ts_s;
                                    bup_dcu_rst_prm_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.bup_dcu_rst.prm_ans.irq){
                                mj_handle.in.bup_dcu_rst.prm_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // prm_ans from dcu
                        case BRO30_DCU:
                            if (in_dcu_prm_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.dcu.prm_ans.msg;
                                mj_handle.in.dcu.prm_ans.msg = (parameter_answer_msg_t *)data;
                                mj_handle.in.dcu.prm_ans.ts_s  = ts_s;
                                mj_handle.in.dcu.prm_ans.ts_ns = ts_ns;
                                in_dcu_prm_ans_updated = 1;
                                in_dcu_prm_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.dcu.prm_ans.msg->hdr.cnt - in_dcu_prm_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_dcu_prm_ans_miss += cnt_diff;
                                }
                                in_dcu_prm_ans_last_cnt = mj_handle.in.dcu.prm_ans.msg->hdr.cnt;
                                dcu_prm_ans_rx_tick = ticks;
                                mj_handle.in.dcu.prm_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_dcu_prm_ans_delayed_ptr == NULL)
                                {
                                    in_dcu_prm_ans_delayed_ptr = (parameter_answer_msg_t *)data;
                                    dcu_prm_ans_delayed_ts_s = ts_s;
                                    dcu_prm_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.dcu.prm_ans.irq){
                                mj_handle.in.dcu.prm_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        // prm_ans from im_bro
                        case BRO30_IM_BRO:
                            if (in_im_bro_prm_ans_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.im_bro.prm_ans.msg;
                                mj_handle.in.im_bro.prm_ans.msg = (parameter_answer_msg_t *)data;
                                mj_handle.in.im_bro.prm_ans.ts_s  = ts_s;
                                mj_handle.in.im_bro.prm_ans.ts_ns = ts_ns;
                                in_im_bro_prm_ans_updated = 1;
                                in_im_bro_prm_ans_total++;
                                uint16_t cnt_diff = (mj_handle.in.im_bro.prm_ans.msg->hdr.cnt - in_im_bro_prm_ans_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_im_bro_prm_ans_miss += cnt_diff;
                                }
                                in_im_bro_prm_ans_last_cnt = mj_handle.in.im_bro.prm_ans.msg->hdr.cnt;
                                im_bro_prm_ans_rx_tick = ticks;
                                mj_handle.in.im_bro.prm_ans.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_im_bro_prm_ans_delayed_ptr == NULL)
                                {
                                    in_im_bro_prm_ans_delayed_ptr = (parameter_answer_msg_t *)data;
                                    im_bro_prm_ans_delayed_ts_s = ts_s;
                                    im_bro_prm_ans_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.im_bro.prm_ans.irq){
                                mj_handle.in.im_bro.prm_ans.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            default:
                return MJ_REJECT_ID;    
        }
    }
    return MJ_REJECT_DST; 
}


static void loop_fcn()
{
    uint32_t c_time = ticks;

    if((((int32_t)(c_time - aufd_bup_multi_control_rx_tick)) > 240)){
        mj_handle.in.aufd.bup_multi_control.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_bup_state_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lfd.bup_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_bup_state_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lrd.bup_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_bup_state_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lst.bup_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_bup_state_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rfd.bup_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_bup_state_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rrd.bup_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_bup_state_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rst.bup_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_bup_state_rx_tick)) > 4000)){
        mj_handle.in.dcu.bup_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - aufd_cmd_ans_rx_tick)) > 4000)){
        mj_handle.in.aufd.cmd_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_cmd_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lfd.cmd_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_cmd_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lrd.cmd_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_cmd_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lst.cmd_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_cmd_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rfd.cmd_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_cmd_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rrd.cmd_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_cmd_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rst.cmd_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_cmd_ans_rx_tick)) > 4000)){
        mj_handle.in.dcu.cmd_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_dbg_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_lfd.dbg.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_dbg_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_lrd.dbg.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_dbg_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_lst.dbg.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_dbg_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_rfd.dbg.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_dbg_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_rrd.dbg.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_dbg_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_rst.dbg.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_dbg_rx_tick)) > 12)){
        mj_handle.in.dcu.dbg.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_dcu_tel_rx_tick)) > 3)){
        mj_handle.in.bup_dcu_lfd.dcu_tel.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_dcu_tel_rx_tick)) > 3)){
        mj_handle.in.bup_dcu_lrd.dcu_tel.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_dcu_tel_rx_tick)) > 3)){
        mj_handle.in.bup_dcu_lst.dcu_tel.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_dcu_tel_rx_tick)) > 3)){
        mj_handle.in.bup_dcu_rfd.dcu_tel.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_dcu_tel_rx_tick)) > 3)){
        mj_handle.in.bup_dcu_rrd.dcu_tel.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_dcu_tel_rx_tick)) > 3)){
        mj_handle.in.bup_dcu_rst.dcu_tel.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_dcu_tel_rx_tick)) > 3)){
        mj_handle.in.dcu.dcu_tel.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_drive_master_ctrl_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_lfd.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_drive_master_ctrl_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_lrd.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_drive_master_ctrl_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_lst.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_drive_master_ctrl_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_rfd.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_drive_master_ctrl_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_rrd.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_drive_master_ctrl_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_rst.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_drive_master_ctrl_rx_tick)) > 12)){
        mj_handle.in.dcu.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_drive_slave_fb_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_lfd.drive_slave_fb.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_drive_slave_fb_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_lrd.drive_slave_fb.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_drive_slave_fb_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_lst.drive_slave_fb.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_drive_slave_fb_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_rfd.drive_slave_fb.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_drive_slave_fb_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_rrd.drive_slave_fb.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_drive_slave_fb_rx_tick)) > 12)){
        mj_handle.in.bup_dcu_rst.drive_slave_fb.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_drive_slave_fb_rx_tick)) > 12)){
        mj_handle.in.dcu.drive_slave_fb.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - aufd_formular_rx_tick)) > 4000)){
        mj_handle.in.aufd.formular.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_formular_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lfd.formular.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_formular_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lrd.formular.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_formular_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lst.formular.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_formular_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rfd.formular.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_formular_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rrd.formular.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_formular_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rst.formular.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_formular_rx_tick)) > 4000)){
        mj_handle.in.dcu.formular.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - im_bro_im_bro_drivers_sens_rx_tick)) > 3)){
        mj_handle.in.im_bro.im_bro_drivers_sens.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - aufd_msg_ans_rx_tick)) > 4000)){
        mj_handle.in.aufd.msg_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_msg_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lfd.msg_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_msg_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lrd.msg_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_msg_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lst.msg_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_msg_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rfd.msg_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_msg_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rrd.msg_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_msg_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rst.msg_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_msg_ans_rx_tick)) > 4000)){
        mj_handle.in.dcu.msg_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - aufd_prm_ans_rx_tick)) > 4000)){
        mj_handle.in.aufd.prm_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_prm_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lfd.prm_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_prm_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lrd.prm_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_prm_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_lst.prm_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_prm_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rfd.prm_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_prm_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rrd.prm_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_prm_ans_rx_tick)) > 4000)){
        mj_handle.in.bup_dcu_rst.prm_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_prm_ans_rx_tick)) > 4000)){
        mj_handle.in.dcu.prm_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - im_bro_prm_ans_rx_tick)) > 4000)){
        mj_handle.in.im_bro.prm_ans.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lfd_ptp_state_rx_tick)) > 6000)){
        mj_handle.in.bup_dcu_lfd.ptp_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lrd_ptp_state_rx_tick)) > 6000)){
        mj_handle.in.bup_dcu_lrd.ptp_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_lst_ptp_state_rx_tick)) > 6000)){
        mj_handle.in.bup_dcu_lst.ptp_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rfd_ptp_state_rx_tick)) > 6000)){
        mj_handle.in.bup_dcu_rfd.ptp_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rrd_ptp_state_rx_tick)) > 6000)){
        mj_handle.in.bup_dcu_rrd.ptp_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - bup_dcu_rst_ptp_state_rx_tick)) > 6000)){
        mj_handle.in.bup_dcu_rst.ptp_state.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - dcu_ptp_state_rx_tick)) > 6000)){
        mj_handle.in.dcu.ptp_state.state = MJ_MSG_OBSOLETE;
    }

    if(in_aufd_bup_multi_control_updated == 1)
    {
        if(mj_handle.in.aufd.bup_multi_control.upd_cb){mj_handle.in.aufd.bup_multi_control.upd_cb();}
        in_aufd_bup_multi_control_updated = 0;
    }
    if(in_bup_dcu_lfd_bup_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.bup_state.upd_cb){mj_handle.in.bup_dcu_lfd.bup_state.upd_cb();}
        in_bup_dcu_lfd_bup_state_updated = 0;
    }
    if(in_bup_dcu_lrd_bup_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.bup_state.upd_cb){mj_handle.in.bup_dcu_lrd.bup_state.upd_cb();}
        in_bup_dcu_lrd_bup_state_updated = 0;
    }
    if(in_bup_dcu_lst_bup_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.bup_state.upd_cb){mj_handle.in.bup_dcu_lst.bup_state.upd_cb();}
        in_bup_dcu_lst_bup_state_updated = 0;
    }
    if(in_bup_dcu_rfd_bup_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.bup_state.upd_cb){mj_handle.in.bup_dcu_rfd.bup_state.upd_cb();}
        in_bup_dcu_rfd_bup_state_updated = 0;
    }
    if(in_bup_dcu_rrd_bup_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.bup_state.upd_cb){mj_handle.in.bup_dcu_rrd.bup_state.upd_cb();}
        in_bup_dcu_rrd_bup_state_updated = 0;
    }
    if(in_bup_dcu_rst_bup_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.bup_state.upd_cb){mj_handle.in.bup_dcu_rst.bup_state.upd_cb();}
        in_bup_dcu_rst_bup_state_updated = 0;
    }
    if(in_dcu_bup_state_updated == 1)
    {
        if(mj_handle.in.dcu.bup_state.upd_cb){mj_handle.in.dcu.bup_state.upd_cb();}
        in_dcu_bup_state_updated = 0;
    }
    if(in_aufd_cmd_ans_updated == 1)
    {
        if(mj_handle.in.aufd.cmd_ans.upd_cb){mj_handle.in.aufd.cmd_ans.upd_cb();}
        in_aufd_cmd_ans_updated = 0;
    }
    if(in_bup_dcu_lfd_cmd_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.cmd_ans.upd_cb){mj_handle.in.bup_dcu_lfd.cmd_ans.upd_cb();}
        in_bup_dcu_lfd_cmd_ans_updated = 0;
    }
    if(in_bup_dcu_lrd_cmd_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.cmd_ans.upd_cb){mj_handle.in.bup_dcu_lrd.cmd_ans.upd_cb();}
        in_bup_dcu_lrd_cmd_ans_updated = 0;
    }
    if(in_bup_dcu_lst_cmd_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.cmd_ans.upd_cb){mj_handle.in.bup_dcu_lst.cmd_ans.upd_cb();}
        in_bup_dcu_lst_cmd_ans_updated = 0;
    }
    if(in_bup_dcu_rfd_cmd_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.cmd_ans.upd_cb){mj_handle.in.bup_dcu_rfd.cmd_ans.upd_cb();}
        in_bup_dcu_rfd_cmd_ans_updated = 0;
    }
    if(in_bup_dcu_rrd_cmd_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.cmd_ans.upd_cb){mj_handle.in.bup_dcu_rrd.cmd_ans.upd_cb();}
        in_bup_dcu_rrd_cmd_ans_updated = 0;
    }
    if(in_bup_dcu_rst_cmd_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.cmd_ans.upd_cb){mj_handle.in.bup_dcu_rst.cmd_ans.upd_cb();}
        in_bup_dcu_rst_cmd_ans_updated = 0;
    }
    if(in_dcu_cmd_ans_updated == 1)
    {
        if(mj_handle.in.dcu.cmd_ans.upd_cb){mj_handle.in.dcu.cmd_ans.upd_cb();}
        in_dcu_cmd_ans_updated = 0;
    }
    if(in_bup_dcu_lfd_dbg_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.dbg.upd_cb){mj_handle.in.bup_dcu_lfd.dbg.upd_cb();}
        in_bup_dcu_lfd_dbg_updated = 0;
    }
    if(in_bup_dcu_lrd_dbg_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.dbg.upd_cb){mj_handle.in.bup_dcu_lrd.dbg.upd_cb();}
        in_bup_dcu_lrd_dbg_updated = 0;
    }
    if(in_bup_dcu_lst_dbg_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.dbg.upd_cb){mj_handle.in.bup_dcu_lst.dbg.upd_cb();}
        in_bup_dcu_lst_dbg_updated = 0;
    }
    if(in_bup_dcu_rfd_dbg_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.dbg.upd_cb){mj_handle.in.bup_dcu_rfd.dbg.upd_cb();}
        in_bup_dcu_rfd_dbg_updated = 0;
    }
    if(in_bup_dcu_rrd_dbg_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.dbg.upd_cb){mj_handle.in.bup_dcu_rrd.dbg.upd_cb();}
        in_bup_dcu_rrd_dbg_updated = 0;
    }
    if(in_bup_dcu_rst_dbg_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.dbg.upd_cb){mj_handle.in.bup_dcu_rst.dbg.upd_cb();}
        in_bup_dcu_rst_dbg_updated = 0;
    }
    if(in_dcu_dbg_updated == 1)
    {
        if(mj_handle.in.dcu.dbg.upd_cb){mj_handle.in.dcu.dbg.upd_cb();}
        in_dcu_dbg_updated = 0;
    }
    if(in_bup_dcu_lfd_dcu_tel_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.dcu_tel.upd_cb){mj_handle.in.bup_dcu_lfd.dcu_tel.upd_cb();}
        in_bup_dcu_lfd_dcu_tel_updated = 0;
    }
    if(in_bup_dcu_lrd_dcu_tel_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.dcu_tel.upd_cb){mj_handle.in.bup_dcu_lrd.dcu_tel.upd_cb();}
        in_bup_dcu_lrd_dcu_tel_updated = 0;
    }
    if(in_bup_dcu_lst_dcu_tel_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.dcu_tel.upd_cb){mj_handle.in.bup_dcu_lst.dcu_tel.upd_cb();}
        in_bup_dcu_lst_dcu_tel_updated = 0;
    }
    if(in_bup_dcu_rfd_dcu_tel_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.dcu_tel.upd_cb){mj_handle.in.bup_dcu_rfd.dcu_tel.upd_cb();}
        in_bup_dcu_rfd_dcu_tel_updated = 0;
    }
    if(in_bup_dcu_rrd_dcu_tel_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.dcu_tel.upd_cb){mj_handle.in.bup_dcu_rrd.dcu_tel.upd_cb();}
        in_bup_dcu_rrd_dcu_tel_updated = 0;
    }
    if(in_bup_dcu_rst_dcu_tel_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.dcu_tel.upd_cb){mj_handle.in.bup_dcu_rst.dcu_tel.upd_cb();}
        in_bup_dcu_rst_dcu_tel_updated = 0;
    }
    if(in_dcu_dcu_tel_updated == 1)
    {
        if(mj_handle.in.dcu.dcu_tel.upd_cb){mj_handle.in.dcu.dcu_tel.upd_cb();}
        in_dcu_dcu_tel_updated = 0;
    }
    if(in_bup_dcu_lfd_drive_master_ctrl_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.drive_master_ctrl.upd_cb){mj_handle.in.bup_dcu_lfd.drive_master_ctrl.upd_cb();}
        in_bup_dcu_lfd_drive_master_ctrl_updated = 0;
    }
    if(in_bup_dcu_lrd_drive_master_ctrl_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.drive_master_ctrl.upd_cb){mj_handle.in.bup_dcu_lrd.drive_master_ctrl.upd_cb();}
        in_bup_dcu_lrd_drive_master_ctrl_updated = 0;
    }
    if(in_bup_dcu_lst_drive_master_ctrl_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.drive_master_ctrl.upd_cb){mj_handle.in.bup_dcu_lst.drive_master_ctrl.upd_cb();}
        in_bup_dcu_lst_drive_master_ctrl_updated = 0;
    }
    if(in_bup_dcu_rfd_drive_master_ctrl_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.drive_master_ctrl.upd_cb){mj_handle.in.bup_dcu_rfd.drive_master_ctrl.upd_cb();}
        in_bup_dcu_rfd_drive_master_ctrl_updated = 0;
    }
    if(in_bup_dcu_rrd_drive_master_ctrl_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.drive_master_ctrl.upd_cb){mj_handle.in.bup_dcu_rrd.drive_master_ctrl.upd_cb();}
        in_bup_dcu_rrd_drive_master_ctrl_updated = 0;
    }
    if(in_bup_dcu_rst_drive_master_ctrl_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.drive_master_ctrl.upd_cb){mj_handle.in.bup_dcu_rst.drive_master_ctrl.upd_cb();}
        in_bup_dcu_rst_drive_master_ctrl_updated = 0;
    }
    if(in_dcu_drive_master_ctrl_updated == 1)
    {
        if(mj_handle.in.dcu.drive_master_ctrl.upd_cb){mj_handle.in.dcu.drive_master_ctrl.upd_cb();}
        in_dcu_drive_master_ctrl_updated = 0;
    }
    if(in_bup_dcu_lfd_drive_slave_fb_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.drive_slave_fb.upd_cb){mj_handle.in.bup_dcu_lfd.drive_slave_fb.upd_cb();}
        in_bup_dcu_lfd_drive_slave_fb_updated = 0;
    }
    if(in_bup_dcu_lrd_drive_slave_fb_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.drive_slave_fb.upd_cb){mj_handle.in.bup_dcu_lrd.drive_slave_fb.upd_cb();}
        in_bup_dcu_lrd_drive_slave_fb_updated = 0;
    }
    if(in_bup_dcu_lst_drive_slave_fb_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.drive_slave_fb.upd_cb){mj_handle.in.bup_dcu_lst.drive_slave_fb.upd_cb();}
        in_bup_dcu_lst_drive_slave_fb_updated = 0;
    }
    if(in_bup_dcu_rfd_drive_slave_fb_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.drive_slave_fb.upd_cb){mj_handle.in.bup_dcu_rfd.drive_slave_fb.upd_cb();}
        in_bup_dcu_rfd_drive_slave_fb_updated = 0;
    }
    if(in_bup_dcu_rrd_drive_slave_fb_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.drive_slave_fb.upd_cb){mj_handle.in.bup_dcu_rrd.drive_slave_fb.upd_cb();}
        in_bup_dcu_rrd_drive_slave_fb_updated = 0;
    }
    if(in_bup_dcu_rst_drive_slave_fb_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.drive_slave_fb.upd_cb){mj_handle.in.bup_dcu_rst.drive_slave_fb.upd_cb();}
        in_bup_dcu_rst_drive_slave_fb_updated = 0;
    }
    if(in_dcu_drive_slave_fb_updated == 1)
    {
        if(mj_handle.in.dcu.drive_slave_fb.upd_cb){mj_handle.in.dcu.drive_slave_fb.upd_cb();}
        in_dcu_drive_slave_fb_updated = 0;
    }
    if(in_aufd_formular_updated == 1)
    {
        if(mj_handle.in.aufd.formular.upd_cb){mj_handle.in.aufd.formular.upd_cb();}
        in_aufd_formular_updated = 0;
    }
    if(in_bup_dcu_lfd_formular_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.formular.upd_cb){mj_handle.in.bup_dcu_lfd.formular.upd_cb();}
        in_bup_dcu_lfd_formular_updated = 0;
    }
    if(in_bup_dcu_lrd_formular_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.formular.upd_cb){mj_handle.in.bup_dcu_lrd.formular.upd_cb();}
        in_bup_dcu_lrd_formular_updated = 0;
    }
    if(in_bup_dcu_lst_formular_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.formular.upd_cb){mj_handle.in.bup_dcu_lst.formular.upd_cb();}
        in_bup_dcu_lst_formular_updated = 0;
    }
    if(in_bup_dcu_rfd_formular_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.formular.upd_cb){mj_handle.in.bup_dcu_rfd.formular.upd_cb();}
        in_bup_dcu_rfd_formular_updated = 0;
    }
    if(in_bup_dcu_rrd_formular_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.formular.upd_cb){mj_handle.in.bup_dcu_rrd.formular.upd_cb();}
        in_bup_dcu_rrd_formular_updated = 0;
    }
    if(in_bup_dcu_rst_formular_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.formular.upd_cb){mj_handle.in.bup_dcu_rst.formular.upd_cb();}
        in_bup_dcu_rst_formular_updated = 0;
    }
    if(in_dcu_formular_updated == 1)
    {
        if(mj_handle.in.dcu.formular.upd_cb){mj_handle.in.dcu.formular.upd_cb();}
        in_dcu_formular_updated = 0;
    }
    if(in_im_bro_im_bro_drivers_sens_updated == 1)
    {
        if(mj_handle.in.im_bro.im_bro_drivers_sens.upd_cb){mj_handle.in.im_bro.im_bro_drivers_sens.upd_cb();}
        in_im_bro_im_bro_drivers_sens_updated = 0;
    }
    if(in_aufd_msg_ans_updated == 1)
    {
        if(mj_handle.in.aufd.msg_ans.upd_cb){mj_handle.in.aufd.msg_ans.upd_cb();}
        in_aufd_msg_ans_updated = 0;
    }
    if(in_bup_dcu_lfd_msg_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.msg_ans.upd_cb){mj_handle.in.bup_dcu_lfd.msg_ans.upd_cb();}
        in_bup_dcu_lfd_msg_ans_updated = 0;
    }
    if(in_bup_dcu_lrd_msg_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.msg_ans.upd_cb){mj_handle.in.bup_dcu_lrd.msg_ans.upd_cb();}
        in_bup_dcu_lrd_msg_ans_updated = 0;
    }
    if(in_bup_dcu_lst_msg_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.msg_ans.upd_cb){mj_handle.in.bup_dcu_lst.msg_ans.upd_cb();}
        in_bup_dcu_lst_msg_ans_updated = 0;
    }
    if(in_bup_dcu_rfd_msg_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.msg_ans.upd_cb){mj_handle.in.bup_dcu_rfd.msg_ans.upd_cb();}
        in_bup_dcu_rfd_msg_ans_updated = 0;
    }
    if(in_bup_dcu_rrd_msg_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.msg_ans.upd_cb){mj_handle.in.bup_dcu_rrd.msg_ans.upd_cb();}
        in_bup_dcu_rrd_msg_ans_updated = 0;
    }
    if(in_bup_dcu_rst_msg_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.msg_ans.upd_cb){mj_handle.in.bup_dcu_rst.msg_ans.upd_cb();}
        in_bup_dcu_rst_msg_ans_updated = 0;
    }
    if(in_dcu_msg_ans_updated == 1)
    {
        if(mj_handle.in.dcu.msg_ans.upd_cb){mj_handle.in.dcu.msg_ans.upd_cb();}
        in_dcu_msg_ans_updated = 0;
    }
    if(in_aufd_prm_ans_updated == 1)
    {
        if(mj_handle.in.aufd.prm_ans.upd_cb){mj_handle.in.aufd.prm_ans.upd_cb();}
        in_aufd_prm_ans_updated = 0;
    }
    if(in_bup_dcu_lfd_prm_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.prm_ans.upd_cb){mj_handle.in.bup_dcu_lfd.prm_ans.upd_cb();}
        in_bup_dcu_lfd_prm_ans_updated = 0;
    }
    if(in_bup_dcu_lrd_prm_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.prm_ans.upd_cb){mj_handle.in.bup_dcu_lrd.prm_ans.upd_cb();}
        in_bup_dcu_lrd_prm_ans_updated = 0;
    }
    if(in_bup_dcu_lst_prm_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.prm_ans.upd_cb){mj_handle.in.bup_dcu_lst.prm_ans.upd_cb();}
        in_bup_dcu_lst_prm_ans_updated = 0;
    }
    if(in_bup_dcu_rfd_prm_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.prm_ans.upd_cb){mj_handle.in.bup_dcu_rfd.prm_ans.upd_cb();}
        in_bup_dcu_rfd_prm_ans_updated = 0;
    }
    if(in_bup_dcu_rrd_prm_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.prm_ans.upd_cb){mj_handle.in.bup_dcu_rrd.prm_ans.upd_cb();}
        in_bup_dcu_rrd_prm_ans_updated = 0;
    }
    if(in_bup_dcu_rst_prm_ans_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.prm_ans.upd_cb){mj_handle.in.bup_dcu_rst.prm_ans.upd_cb();}
        in_bup_dcu_rst_prm_ans_updated = 0;
    }
    if(in_dcu_prm_ans_updated == 1)
    {
        if(mj_handle.in.dcu.prm_ans.upd_cb){mj_handle.in.dcu.prm_ans.upd_cb();}
        in_dcu_prm_ans_updated = 0;
    }
    if(in_im_bro_prm_ans_updated == 1)
    {
        if(mj_handle.in.im_bro.prm_ans.upd_cb){mj_handle.in.im_bro.prm_ans.upd_cb();}
        in_im_bro_prm_ans_updated = 0;
    }
    if(in_bup_dcu_lfd_ptp_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lfd.ptp_state.upd_cb){mj_handle.in.bup_dcu_lfd.ptp_state.upd_cb();}
        in_bup_dcu_lfd_ptp_state_updated = 0;
    }
    if(in_bup_dcu_lrd_ptp_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lrd.ptp_state.upd_cb){mj_handle.in.bup_dcu_lrd.ptp_state.upd_cb();}
        in_bup_dcu_lrd_ptp_state_updated = 0;
    }
    if(in_bup_dcu_lst_ptp_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_lst.ptp_state.upd_cb){mj_handle.in.bup_dcu_lst.ptp_state.upd_cb();}
        in_bup_dcu_lst_ptp_state_updated = 0;
    }
    if(in_bup_dcu_rfd_ptp_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rfd.ptp_state.upd_cb){mj_handle.in.bup_dcu_rfd.ptp_state.upd_cb();}
        in_bup_dcu_rfd_ptp_state_updated = 0;
    }
    if(in_bup_dcu_rrd_ptp_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rrd.ptp_state.upd_cb){mj_handle.in.bup_dcu_rrd.ptp_state.upd_cb();}
        in_bup_dcu_rrd_ptp_state_updated = 0;
    }
    if(in_bup_dcu_rst_ptp_state_updated == 1)
    {
        if(mj_handle.in.bup_dcu_rst.ptp_state.upd_cb){mj_handle.in.bup_dcu_rst.ptp_state.upd_cb();}
        in_bup_dcu_rst_ptp_state_updated = 0;
    }
    if(in_dcu_ptp_state_updated == 1)
    {
        if(mj_handle.in.dcu.ptp_state.upd_cb){mj_handle.in.dcu.ptp_state.upd_cb();}
        in_dcu_ptp_state_updated = 0;
    }

if (_send_join_done) {
    if (_join_ip) {
        for(int i = 0; i < IN_INT_COUNT; i++) {
            if ((*_join_ip) == group_addr[i*2]) {
                group_addr[i*2+1] = _join_send_tick;
            }
        }
        _join_ip = NULL;
    }else{
        for(int i = 0; i < IN_INT_COUNT; i++) {
            if ((ticks - group_addr[i*2+1]) > MJ_IPMCAST_PERIOD_TICK) {
                _join_ip = &group_addr[i*2];
                _send_join_done = false;
                break;
            }
        }
    }
}
}

mj_status_t mj_mon_prm_init(mj_mon_t ** ptr){
        /* PRM */
    _mon_prm.service_mode = 0;
    _mon_prm.dev_id = 27801;
    /* prms[p] */
    const uint8_t default_com_if_srv_mcast_req[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x32,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_mon_prm.com_if_srv_mcast_req), default_com_if_srv_mcast_req, sizeof(default_com_if_srv_mcast_req) > 32 ? 32 : sizeof(default_com_if_srv_mcast_req));
    /* prms[p] */
    const uint8_t default_com_if_srv_mcast_ans[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x32,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x32, 0x00};
    memcpy(&(_mon_prm.com_if_srv_mcast_ans), default_com_if_srv_mcast_ans, sizeof(default_com_if_srv_mcast_ans) > 32 ? 32 : sizeof(default_com_if_srv_mcast_ans));
    /* prms[p] */
    const uint8_t default_com_if_bro_bup_ctrl_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_mon_prm.com_if_bro_bup_ctrl_mcast), default_com_if_bro_bup_ctrl_mcast, sizeof(default_com_if_bro_bup_ctrl_mcast) > 32 ? 32 : sizeof(default_com_if_bro_bup_ctrl_mcast));
    /* prms[p] */
    const uint8_t default_com_if_bro_bup_data_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x32, 0x00};
    memcpy(&(_mon_prm.com_if_bro_bup_data_mcast), default_com_if_bro_bup_data_mcast, sizeof(default_com_if_bro_bup_data_mcast) > 32 ? 32 : sizeof(default_com_if_bro_bup_data_mcast));
    /* prms[p] */
    const uint8_t default_com_if_bup_internal_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x31,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x32, 0x00};
    memcpy(&(_mon_prm.com_if_bup_internal_mcast), default_com_if_bup_internal_mcast, sizeof(default_com_if_bup_internal_mcast) > 32 ? 32 : sizeof(default_com_if_bup_internal_mcast));
    /* prms[p] */
    const uint8_t default_com_if_bro_bup_srv_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_mon_prm.com_if_bro_bup_srv_mcast), default_com_if_bro_bup_srv_mcast, sizeof(default_com_if_bro_bup_srv_mcast) > 32 ? 32 : sizeof(default_com_if_bro_bup_srv_mcast));
    /* prms[p] */
    const uint8_t default_com_if_im_bro_drive_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x39,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_mon_prm.com_if_im_bro_drive_mcast), default_com_if_im_bro_drive_mcast, sizeof(default_com_if_im_bro_drive_mcast) > 32 ? 32 : sizeof(default_com_if_im_bro_drive_mcast));
    /* prms[p] */
    const uint8_t default_com_if_im_bro_drive_ctrl_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x39,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_mon_prm.com_if_im_bro_drive_ctrl_mcast), default_com_if_im_bro_drive_ctrl_mcast, sizeof(default_com_if_im_bro_drive_ctrl_mcast) > 32 ? 32 : sizeof(default_com_if_im_bro_drive_ctrl_mcast));
    mj_handle.prm.ptr = &_mon_prm;
    mj_handle.prm.read = mon_prm_read;
    mj_handle.prm.write = mon_prm_write;
    mj_handle.prm.list = mon_prm_list;
    *ptr = &mj_handle;
    return MJ_OK;
}

mj_status_t mj_mon_init(mj_drv_interface_t *drv, mj_mon_t ** ptr)
{
    //memset(&mj_handle,0,sizeof(mj_handle));
    if (mj_handle.prm.ptr == NULL){
        mj_mon_prm_init(ptr);
    }
    self_dev_id = mj_handle.prm.ptr->dev_id;
    p_drv = drv;
    ethInt = p_drv->udp4.create_interface(devMac, MON_IP);
    if (ethInt == NULL){return MJ_ETH_FAIL;};

    uint32_t bro_bup_ctrl_mcast_ip_be = BRO_BUP_CTRL_MCAST_IP;
    uint16_t bro_bup_ctrl_mcast_port_be = 0x69bf;
    if (mj_str_if_to_int(mj_handle.prm.ptr->com_if_bro_bup_ctrl_mcast, &bro_bup_ctrl_mcast_ip_be, &bro_bup_ctrl_mcast_port_be) != 0){
        return MJ_UDP4_CB_FAIL;
    }
    uint32_t bro_bup_data_mcast_ip_be = BRO_BUP_DATA_MCAST_IP;
    uint16_t bro_bup_data_mcast_port_be = 0x6abf;
    if (mj_str_if_to_int(mj_handle.prm.ptr->com_if_bro_bup_data_mcast, &bro_bup_data_mcast_ip_be, &bro_bup_data_mcast_port_be) != 0){
        return MJ_UDP4_CB_FAIL;
    }
    uint32_t bro_bup_srv_mcast_ip_be = BRO_BUP_SRV_MCAST_IP;
    uint16_t bro_bup_srv_mcast_port_be = 0x69bf;
    if (mj_str_if_to_int(mj_handle.prm.ptr->com_if_bro_bup_srv_mcast, &bro_bup_srv_mcast_ip_be, &bro_bup_srv_mcast_port_be) != 0){
        return MJ_UDP4_CB_FAIL;
    }
    uint32_t bup_internal_mcast_ip_be = BUP_INTERNAL_MCAST_IP;
    uint16_t bup_internal_mcast_port_be = 0x6abf;
    if (mj_str_if_to_int(mj_handle.prm.ptr->com_if_bup_internal_mcast, &bup_internal_mcast_ip_be, &bup_internal_mcast_port_be) != 0){
        return MJ_UDP4_CB_FAIL;
    }
    uint32_t im_bro_drive_ctrl_mcast_ip_be = IM_BRO_DRIVE_CTRL_MCAST_IP;
    uint16_t im_bro_drive_ctrl_mcast_port_be = 0x69bf;
    if (mj_str_if_to_int(mj_handle.prm.ptr->com_if_im_bro_drive_ctrl_mcast, &im_bro_drive_ctrl_mcast_ip_be, &im_bro_drive_ctrl_mcast_port_be) != 0){
        return MJ_UDP4_CB_FAIL;
    }
    uint32_t im_bro_drive_mcast_ip_be = IM_BRO_DRIVE_MCAST_IP;
    uint16_t im_bro_drive_mcast_port_be = 0x69bf;
    if (mj_str_if_to_int(mj_handle.prm.ptr->com_if_im_bro_drive_mcast, &im_bro_drive_mcast_ip_be, &im_bro_drive_mcast_port_be) != 0){
        return MJ_UDP4_CB_FAIL;
    }
    uint32_t srv_mcast_ans_ip_be = SRV_MCAST_ANS_IP;
    uint16_t srv_mcast_ans_port_be = 0x6abf;
    if (mj_str_if_to_int(mj_handle.prm.ptr->com_if_srv_mcast_ans, &srv_mcast_ans_ip_be, &srv_mcast_ans_port_be) != 0){
        return MJ_UDP4_CB_FAIL;
    }
    uint32_t srv_mcast_req_ip_be = SRV_MCAST_REQ_IP;
    uint16_t srv_mcast_req_port_be = 0x69bf;
    if (mj_str_if_to_int(mj_handle.prm.ptr->com_if_srv_mcast_req, &srv_mcast_req_ip_be, &srv_mcast_req_port_be) != 0){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(bro_bup_ctrl_mcast_ip_be, bro_bup_ctrl_mcast_port_be, bro_bup_ctrl_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(bro_bup_data_mcast_ip_be, bro_bup_data_mcast_port_be, bro_bup_data_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(bro_bup_srv_mcast_ip_be, bro_bup_srv_mcast_port_be, bro_bup_srv_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(bup_internal_mcast_ip_be, bup_internal_mcast_port_be, bup_internal_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(im_bro_drive_ctrl_mcast_ip_be, im_bro_drive_ctrl_mcast_port_be, im_bro_drive_ctrl_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(im_bro_drive_mcast_ip_be, im_bro_drive_mcast_port_be, im_bro_drive_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(srv_mcast_ans_ip_be, srv_mcast_ans_port_be, srv_mcast_ans_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }

    group_addr[0] = bro_bup_ctrl_mcast_ip_be; // bro_bup_ctrl_mcast
    group_addr[1] = 0;
    group_addr[2] = bro_bup_data_mcast_ip_be; // bro_bup_data_mcast
    group_addr[3] = 0;
    group_addr[4] = bro_bup_srv_mcast_ip_be; // bro_bup_srv_mcast
    group_addr[5] = 0;
    group_addr[6] = bup_internal_mcast_ip_be; // bup_internal_mcast
    group_addr[7] = 0;
    group_addr[8] = im_bro_drive_ctrl_mcast_ip_be; // im_bro_drive_ctrl_mcast
    group_addr[9] = 0;
    group_addr[10] = im_bro_drive_mcast_ip_be; // im_bro_drive_mcast
    group_addr[11] = 0;
    group_addr[12] = srv_mcast_ans_ip_be; // srv_mcast_ans
    group_addr[13] = 0;

    /* OUT */
    /** bup_multi_control */
    if ((mj_handle.out.bup_multi_control.msg = (bup_drv_multi_control_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_multi_control_msg_t))))
    {
        if(bup_drv_multi_control_type_check(mj_handle.out.bup_multi_control.msg) == MJ_CHECK_OK)
        {
            out_bup_multi_control_pkt = p_drv->udp4.create_out_pkt(ethInt,bro_bup_ctrl_mcast_ip_be, bro_bup_ctrl_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.bup_multi_control.msg, sizeof(bup_drv_multi_control_msg_t));
            if (out_bup_multi_control_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.bup_multi_control.msg->hdr.src = self_dev_id;
            mj_handle.out.bup_multi_control.msg->hdr.cnt = 0;
            mj_handle.out.bup_multi_control.msg->hdr.id = ID_BUP_MULTI_CONTROL;
            mj_handle.out.bup_multi_control.msg->hdr.dst = BRO30_ALL;
            mj_handle.out.bup_multi_control.lock = out_bup_multi_control_lock_fcn;
            mj_handle.out.bup_multi_control.tx_enable = true;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.bup_multi_control.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** bup_srv_ctrl */
    if ((mj_handle.out.bup_srv_ctrl.msg = (bup_drv_control_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_control_msg_t))))
    {
        if(bup_drv_control_type_check(mj_handle.out.bup_srv_ctrl.msg) == MJ_CHECK_OK)
        {
            out_bup_srv_ctrl_pkt = p_drv->udp4.create_out_pkt(ethInt,bro_bup_srv_mcast_ip_be, bro_bup_srv_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.bup_srv_ctrl.msg, sizeof(bup_drv_control_msg_t));
            if (out_bup_srv_ctrl_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.bup_srv_ctrl.msg->hdr.src = self_dev_id;
            mj_handle.out.bup_srv_ctrl.msg->hdr.cnt = 0;
            mj_handle.out.bup_srv_ctrl.msg->hdr.id = ID_BUP_SRV_CTRL;
            mj_handle.out.bup_srv_ctrl.msg->hdr.dst = BRO30_ALL;
            mj_handle.out.bup_srv_ctrl.lock = out_bup_srv_ctrl_lock_fcn;
            mj_handle.out.bup_srv_ctrl.tx_enable = true;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.bup_srv_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** cmd_req */
    if ((mj_handle.out.cmd_req.msg = (command_request_msg_t *)p_drv->udp4.alloc(sizeof(command_request_msg_t))))
    {
        if(command_request_type_check(mj_handle.out.cmd_req.msg) == MJ_CHECK_OK)
        {
            out_cmd_req_pkt = p_drv->udp4.create_out_pkt(ethInt,srv_mcast_req_ip_be, srv_mcast_req_port_be, 0x00,(uint8_t*)mj_handle.out.cmd_req.msg, sizeof(command_request_msg_t));
            if (out_cmd_req_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.cmd_req.msg->hdr.src = self_dev_id;
            mj_handle.out.cmd_req.msg->hdr.cnt = 0;
            mj_handle.out.cmd_req.msg->hdr.id = ID_CMD_REQ;
            mj_handle.out.cmd_req.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.cmd_req.tx = out_cmd_req_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.cmd_req.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** msg_req */
    if ((mj_handle.out.msg_req.msg = (msg_request_msg_t *)p_drv->udp4.alloc(sizeof(msg_request_msg_t))))
    {
        if(msg_request_type_check(mj_handle.out.msg_req.msg) == MJ_CHECK_OK)
        {
            out_msg_req_pkt = p_drv->udp4.create_out_pkt(ethInt,srv_mcast_req_ip_be, srv_mcast_req_port_be, 0x00,(uint8_t*)mj_handle.out.msg_req.msg, sizeof(msg_request_msg_t));
            if (out_msg_req_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.msg_req.msg->hdr.src = self_dev_id;
            mj_handle.out.msg_req.msg->hdr.cnt = 0;
            mj_handle.out.msg_req.msg->hdr.id = ID_MSG_REQ;
            p_drv->udp4.set_dscp(out_msg_req_pkt,8);
            mj_handle.out.msg_req.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.msg_req.tx = out_msg_req_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.msg_req.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** prm_req */
    if ((mj_handle.out.prm_req.msg = (parameter_request_msg_t *)p_drv->udp4.alloc(sizeof(parameter_request_msg_t))))
    {
        if(parameter_request_type_check(mj_handle.out.prm_req.msg) == MJ_CHECK_OK)
        {
            out_prm_req_pkt = p_drv->udp4.create_out_pkt(ethInt,srv_mcast_req_ip_be, srv_mcast_req_port_be, 0x00,(uint8_t*)mj_handle.out.prm_req.msg, sizeof(parameter_request_msg_t));
            if (out_prm_req_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.prm_req.msg->hdr.src = self_dev_id;
            mj_handle.out.prm_req.msg->hdr.cnt = 0;
            mj_handle.out.prm_req.msg->hdr.id = ID_PRM_REQ;
            p_drv->udp4.set_dscp(out_prm_req_pkt,8);
            mj_handle.out.prm_req.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.prm_req.tx = out_prm_req_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.prm_req.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }


    /* IN */
    if ((mj_handle.in.aufd.bup_multi_control.msg = (bup_drv_multi_control_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_multi_control_msg_t)))){
        if(bup_drv_multi_control_type_check(mj_handle.in.aufd.bup_multi_control.msg) == MJ_CHECK_OK){
            mj_handle.in.aufd.bup_multi_control.msg->hdr.src = BRO30_NONE;
            mj_handle.in.aufd.bup_multi_control.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.aufd.bup_multi_control.msg->hdr.cnt = 0;
            mj_handle.in.aufd.bup_multi_control.msg->hdr.id = 0;
            mj_handle.in.aufd.bup_multi_control.lock = in_aufd_bup_multi_control_lock_fcn;
            mj_handle.in.aufd.bup_multi_control.copy = in_aufd_bup_multi_control_copy_fcn;
            mj_handle.in.aufd.bup_multi_control.upd_cb = NULL;
            mj_handle.in.aufd.bup_multi_control.irq = NULL;
            mj_handle.in.aufd.bup_multi_control.state = MJ_MSG_OBSOLETE;
            mj_handle.in.aufd.bup_multi_control.total = &in_aufd_bup_multi_control_total;
            mj_handle.in.aufd.bup_multi_control.miss = &in_aufd_bup_multi_control_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.aufd.bup_multi_control.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.aufd.cmd_ans.msg = (command_answer_msg_t *)p_drv->udp4.alloc(sizeof(command_answer_msg_t)))){
        if(command_answer_type_check(mj_handle.in.aufd.cmd_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.aufd.cmd_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.aufd.cmd_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.aufd.cmd_ans.msg->hdr.cnt = 0;
            mj_handle.in.aufd.cmd_ans.msg->hdr.id = 0;
            mj_handle.in.aufd.cmd_ans.lock = in_aufd_cmd_ans_lock_fcn;
            mj_handle.in.aufd.cmd_ans.copy = in_aufd_cmd_ans_copy_fcn;
            mj_handle.in.aufd.cmd_ans.upd_cb = NULL;
            mj_handle.in.aufd.cmd_ans.irq = NULL;
            mj_handle.in.aufd.cmd_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.aufd.cmd_ans.total = &in_aufd_cmd_ans_total;
            mj_handle.in.aufd.cmd_ans.miss = &in_aufd_cmd_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.aufd.cmd_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.aufd.formular.msg = (formular_info_msg_t *)p_drv->udp4.alloc(sizeof(formular_info_msg_t)))){
        if(formular_info_type_check(mj_handle.in.aufd.formular.msg) == MJ_CHECK_OK){
            mj_handle.in.aufd.formular.msg->hdr.src = BRO30_NONE;
            mj_handle.in.aufd.formular.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.aufd.formular.msg->hdr.cnt = 0;
            mj_handle.in.aufd.formular.msg->hdr.id = 0;
            mj_handle.in.aufd.formular.lock = in_aufd_formular_lock_fcn;
            mj_handle.in.aufd.formular.copy = in_aufd_formular_copy_fcn;
            mj_handle.in.aufd.formular.upd_cb = NULL;
            mj_handle.in.aufd.formular.irq = NULL;
            mj_handle.in.aufd.formular.state = MJ_MSG_OBSOLETE;
            mj_handle.in.aufd.formular.total = &in_aufd_formular_total;
            mj_handle.in.aufd.formular.miss = &in_aufd_formular_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.aufd.formular.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.aufd.msg_ans.msg = (msg_answer_msg_t *)p_drv->udp4.alloc(sizeof(msg_answer_msg_t)))){
        if(msg_answer_type_check(mj_handle.in.aufd.msg_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.aufd.msg_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.aufd.msg_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.aufd.msg_ans.msg->hdr.cnt = 0;
            mj_handle.in.aufd.msg_ans.msg->hdr.id = 0;
            mj_handle.in.aufd.msg_ans.lock = in_aufd_msg_ans_lock_fcn;
            mj_handle.in.aufd.msg_ans.copy = in_aufd_msg_ans_copy_fcn;
            mj_handle.in.aufd.msg_ans.upd_cb = NULL;
            mj_handle.in.aufd.msg_ans.irq = NULL;
            mj_handle.in.aufd.msg_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.aufd.msg_ans.total = &in_aufd_msg_ans_total;
            mj_handle.in.aufd.msg_ans.miss = &in_aufd_msg_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.aufd.msg_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.aufd.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t)))){
        if(parameter_answer_type_check(mj_handle.in.aufd.prm_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.aufd.prm_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.aufd.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.aufd.prm_ans.msg->hdr.cnt = 0;
            mj_handle.in.aufd.prm_ans.msg->hdr.id = 0;
            mj_handle.in.aufd.prm_ans.lock = in_aufd_prm_ans_lock_fcn;
            mj_handle.in.aufd.prm_ans.copy = in_aufd_prm_ans_copy_fcn;
            mj_handle.in.aufd.prm_ans.upd_cb = NULL;
            mj_handle.in.aufd.prm_ans.irq = NULL;
            mj_handle.in.aufd.prm_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.aufd.prm_ans.total = &in_aufd_prm_ans_total;
            mj_handle.in.aufd.prm_ans.miss = &in_aufd_prm_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.aufd.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.bup_state.msg = (bup_drv_state_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_state_msg_t)))){
        if(bup_drv_state_type_check(mj_handle.in.bup_dcu_lfd.bup_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.bup_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.bup_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.bup_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.bup_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.bup_state.lock = in_bup_dcu_lfd_bup_state_lock_fcn;
            mj_handle.in.bup_dcu_lfd.bup_state.copy = in_bup_dcu_lfd_bup_state_copy_fcn;
            mj_handle.in.bup_dcu_lfd.bup_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.bup_state.irq = NULL;
            mj_handle.in.bup_dcu_lfd.bup_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.bup_state.total = &in_bup_dcu_lfd_bup_state_total;
            mj_handle.in.bup_dcu_lfd.bup_state.miss = &in_bup_dcu_lfd_bup_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.bup_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.cmd_ans.msg = (command_answer_msg_t *)p_drv->udp4.alloc(sizeof(command_answer_msg_t)))){
        if(command_answer_type_check(mj_handle.in.bup_dcu_lfd.cmd_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.cmd_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.cmd_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.cmd_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.cmd_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.cmd_ans.lock = in_bup_dcu_lfd_cmd_ans_lock_fcn;
            mj_handle.in.bup_dcu_lfd.cmd_ans.copy = in_bup_dcu_lfd_cmd_ans_copy_fcn;
            mj_handle.in.bup_dcu_lfd.cmd_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.cmd_ans.irq = NULL;
            mj_handle.in.bup_dcu_lfd.cmd_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.cmd_ans.total = &in_bup_dcu_lfd_cmd_ans_total;
            mj_handle.in.bup_dcu_lfd.cmd_ans.miss = &in_bup_dcu_lfd_cmd_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.cmd_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.dbg.msg = (dbg_data_msg_t *)p_drv->udp4.alloc(sizeof(dbg_data_msg_t)))){
        if(dbg_data_type_check(mj_handle.in.bup_dcu_lfd.dbg.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.dbg.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.dbg.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.dbg.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.dbg.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.dbg.lock = in_bup_dcu_lfd_dbg_lock_fcn;
            mj_handle.in.bup_dcu_lfd.dbg.copy = in_bup_dcu_lfd_dbg_copy_fcn;
            mj_handle.in.bup_dcu_lfd.dbg.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.dbg.irq = NULL;
            mj_handle.in.bup_dcu_lfd.dbg.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.dbg.total = &in_bup_dcu_lfd_dbg_total;
            mj_handle.in.bup_dcu_lfd.dbg.miss = &in_bup_dcu_lfd_dbg_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.dbg.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.dcu_tel.msg = (dcu_telemetry_msg_t *)p_drv->udp4.alloc(sizeof(dcu_telemetry_msg_t)))){
        if(dcu_telemetry_type_check(mj_handle.in.bup_dcu_lfd.dcu_tel.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.dcu_tel.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.dcu_tel.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.dcu_tel.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.dcu_tel.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.dcu_tel.lock = in_bup_dcu_lfd_dcu_tel_lock_fcn;
            mj_handle.in.bup_dcu_lfd.dcu_tel.copy = in_bup_dcu_lfd_dcu_tel_copy_fcn;
            mj_handle.in.bup_dcu_lfd.dcu_tel.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.dcu_tel.irq = NULL;
            mj_handle.in.bup_dcu_lfd.dcu_tel.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.dcu_tel.total = &in_bup_dcu_lfd_dcu_tel_total;
            mj_handle.in.bup_dcu_lfd.dcu_tel.miss = &in_bup_dcu_lfd_dcu_tel_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.dcu_tel.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)p_drv->udp4.alloc(sizeof(drive_master_ctrl_msg_t)))){
        if(drive_master_ctrl_type_check(mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.lock = in_bup_dcu_lfd_drive_master_ctrl_lock_fcn;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.copy = in_bup_dcu_lfd_drive_master_ctrl_copy_fcn;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.irq = NULL;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.total = &in_bup_dcu_lfd_drive_master_ctrl_total;
            mj_handle.in.bup_dcu_lfd.drive_master_ctrl.miss = &in_bup_dcu_lfd_drive_master_ctrl_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.drive_master_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg = (drive_slave_fb_msg_t *)p_drv->udp4.alloc(sizeof(drive_slave_fb_msg_t)))){
        if(drive_slave_fb_type_check(mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.lock = in_bup_dcu_lfd_drive_slave_fb_lock_fcn;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.copy = in_bup_dcu_lfd_drive_slave_fb_copy_fcn;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.irq = NULL;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.total = &in_bup_dcu_lfd_drive_slave_fb_total;
            mj_handle.in.bup_dcu_lfd.drive_slave_fb.miss = &in_bup_dcu_lfd_drive_slave_fb_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.drive_slave_fb.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.formular.msg = (formular_info_msg_t *)p_drv->udp4.alloc(sizeof(formular_info_msg_t)))){
        if(formular_info_type_check(mj_handle.in.bup_dcu_lfd.formular.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.formular.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.formular.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.formular.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.formular.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.formular.lock = in_bup_dcu_lfd_formular_lock_fcn;
            mj_handle.in.bup_dcu_lfd.formular.copy = in_bup_dcu_lfd_formular_copy_fcn;
            mj_handle.in.bup_dcu_lfd.formular.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.formular.irq = NULL;
            mj_handle.in.bup_dcu_lfd.formular.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.formular.total = &in_bup_dcu_lfd_formular_total;
            mj_handle.in.bup_dcu_lfd.formular.miss = &in_bup_dcu_lfd_formular_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.formular.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.msg_ans.msg = (msg_answer_msg_t *)p_drv->udp4.alloc(sizeof(msg_answer_msg_t)))){
        if(msg_answer_type_check(mj_handle.in.bup_dcu_lfd.msg_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.msg_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.msg_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.msg_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.msg_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.msg_ans.lock = in_bup_dcu_lfd_msg_ans_lock_fcn;
            mj_handle.in.bup_dcu_lfd.msg_ans.copy = in_bup_dcu_lfd_msg_ans_copy_fcn;
            mj_handle.in.bup_dcu_lfd.msg_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.msg_ans.irq = NULL;
            mj_handle.in.bup_dcu_lfd.msg_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.msg_ans.total = &in_bup_dcu_lfd_msg_ans_total;
            mj_handle.in.bup_dcu_lfd.msg_ans.miss = &in_bup_dcu_lfd_msg_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.msg_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t)))){
        if(parameter_answer_type_check(mj_handle.in.bup_dcu_lfd.prm_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.prm_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.prm_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.prm_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.prm_ans.lock = in_bup_dcu_lfd_prm_ans_lock_fcn;
            mj_handle.in.bup_dcu_lfd.prm_ans.copy = in_bup_dcu_lfd_prm_ans_copy_fcn;
            mj_handle.in.bup_dcu_lfd.prm_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.prm_ans.irq = NULL;
            mj_handle.in.bup_dcu_lfd.prm_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.prm_ans.total = &in_bup_dcu_lfd_prm_ans_total;
            mj_handle.in.bup_dcu_lfd.prm_ans.miss = &in_bup_dcu_lfd_prm_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lfd.ptp_state.msg = (ptp_info_msg_t *)p_drv->udp4.alloc(sizeof(ptp_info_msg_t)))){
        if(ptp_info_type_check(mj_handle.in.bup_dcu_lfd.ptp_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lfd.ptp_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.ptp_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lfd.ptp_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lfd.ptp_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lfd.ptp_state.lock = in_bup_dcu_lfd_ptp_state_lock_fcn;
            mj_handle.in.bup_dcu_lfd.ptp_state.copy = in_bup_dcu_lfd_ptp_state_copy_fcn;
            mj_handle.in.bup_dcu_lfd.ptp_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_lfd.ptp_state.irq = NULL;
            mj_handle.in.bup_dcu_lfd.ptp_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lfd.ptp_state.total = &in_bup_dcu_lfd_ptp_state_total;
            mj_handle.in.bup_dcu_lfd.ptp_state.miss = &in_bup_dcu_lfd_ptp_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lfd.ptp_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.bup_state.msg = (bup_drv_state_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_state_msg_t)))){
        if(bup_drv_state_type_check(mj_handle.in.bup_dcu_lrd.bup_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.bup_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.bup_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.bup_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.bup_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.bup_state.lock = in_bup_dcu_lrd_bup_state_lock_fcn;
            mj_handle.in.bup_dcu_lrd.bup_state.copy = in_bup_dcu_lrd_bup_state_copy_fcn;
            mj_handle.in.bup_dcu_lrd.bup_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.bup_state.irq = NULL;
            mj_handle.in.bup_dcu_lrd.bup_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.bup_state.total = &in_bup_dcu_lrd_bup_state_total;
            mj_handle.in.bup_dcu_lrd.bup_state.miss = &in_bup_dcu_lrd_bup_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.bup_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.cmd_ans.msg = (command_answer_msg_t *)p_drv->udp4.alloc(sizeof(command_answer_msg_t)))){
        if(command_answer_type_check(mj_handle.in.bup_dcu_lrd.cmd_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.cmd_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.cmd_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.cmd_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.cmd_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.cmd_ans.lock = in_bup_dcu_lrd_cmd_ans_lock_fcn;
            mj_handle.in.bup_dcu_lrd.cmd_ans.copy = in_bup_dcu_lrd_cmd_ans_copy_fcn;
            mj_handle.in.bup_dcu_lrd.cmd_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.cmd_ans.irq = NULL;
            mj_handle.in.bup_dcu_lrd.cmd_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.cmd_ans.total = &in_bup_dcu_lrd_cmd_ans_total;
            mj_handle.in.bup_dcu_lrd.cmd_ans.miss = &in_bup_dcu_lrd_cmd_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.cmd_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.dbg.msg = (dbg_data_msg_t *)p_drv->udp4.alloc(sizeof(dbg_data_msg_t)))){
        if(dbg_data_type_check(mj_handle.in.bup_dcu_lrd.dbg.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.dbg.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.dbg.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.dbg.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.dbg.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.dbg.lock = in_bup_dcu_lrd_dbg_lock_fcn;
            mj_handle.in.bup_dcu_lrd.dbg.copy = in_bup_dcu_lrd_dbg_copy_fcn;
            mj_handle.in.bup_dcu_lrd.dbg.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.dbg.irq = NULL;
            mj_handle.in.bup_dcu_lrd.dbg.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.dbg.total = &in_bup_dcu_lrd_dbg_total;
            mj_handle.in.bup_dcu_lrd.dbg.miss = &in_bup_dcu_lrd_dbg_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.dbg.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.dcu_tel.msg = (dcu_telemetry_msg_t *)p_drv->udp4.alloc(sizeof(dcu_telemetry_msg_t)))){
        if(dcu_telemetry_type_check(mj_handle.in.bup_dcu_lrd.dcu_tel.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.dcu_tel.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.dcu_tel.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.dcu_tel.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.dcu_tel.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.dcu_tel.lock = in_bup_dcu_lrd_dcu_tel_lock_fcn;
            mj_handle.in.bup_dcu_lrd.dcu_tel.copy = in_bup_dcu_lrd_dcu_tel_copy_fcn;
            mj_handle.in.bup_dcu_lrd.dcu_tel.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.dcu_tel.irq = NULL;
            mj_handle.in.bup_dcu_lrd.dcu_tel.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.dcu_tel.total = &in_bup_dcu_lrd_dcu_tel_total;
            mj_handle.in.bup_dcu_lrd.dcu_tel.miss = &in_bup_dcu_lrd_dcu_tel_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.dcu_tel.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)p_drv->udp4.alloc(sizeof(drive_master_ctrl_msg_t)))){
        if(drive_master_ctrl_type_check(mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.lock = in_bup_dcu_lrd_drive_master_ctrl_lock_fcn;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.copy = in_bup_dcu_lrd_drive_master_ctrl_copy_fcn;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.irq = NULL;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.total = &in_bup_dcu_lrd_drive_master_ctrl_total;
            mj_handle.in.bup_dcu_lrd.drive_master_ctrl.miss = &in_bup_dcu_lrd_drive_master_ctrl_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.drive_master_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg = (drive_slave_fb_msg_t *)p_drv->udp4.alloc(sizeof(drive_slave_fb_msg_t)))){
        if(drive_slave_fb_type_check(mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.lock = in_bup_dcu_lrd_drive_slave_fb_lock_fcn;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.copy = in_bup_dcu_lrd_drive_slave_fb_copy_fcn;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.irq = NULL;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.total = &in_bup_dcu_lrd_drive_slave_fb_total;
            mj_handle.in.bup_dcu_lrd.drive_slave_fb.miss = &in_bup_dcu_lrd_drive_slave_fb_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.drive_slave_fb.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.formular.msg = (formular_info_msg_t *)p_drv->udp4.alloc(sizeof(formular_info_msg_t)))){
        if(formular_info_type_check(mj_handle.in.bup_dcu_lrd.formular.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.formular.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.formular.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.formular.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.formular.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.formular.lock = in_bup_dcu_lrd_formular_lock_fcn;
            mj_handle.in.bup_dcu_lrd.formular.copy = in_bup_dcu_lrd_formular_copy_fcn;
            mj_handle.in.bup_dcu_lrd.formular.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.formular.irq = NULL;
            mj_handle.in.bup_dcu_lrd.formular.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.formular.total = &in_bup_dcu_lrd_formular_total;
            mj_handle.in.bup_dcu_lrd.formular.miss = &in_bup_dcu_lrd_formular_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.formular.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.msg_ans.msg = (msg_answer_msg_t *)p_drv->udp4.alloc(sizeof(msg_answer_msg_t)))){
        if(msg_answer_type_check(mj_handle.in.bup_dcu_lrd.msg_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.msg_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.msg_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.msg_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.msg_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.msg_ans.lock = in_bup_dcu_lrd_msg_ans_lock_fcn;
            mj_handle.in.bup_dcu_lrd.msg_ans.copy = in_bup_dcu_lrd_msg_ans_copy_fcn;
            mj_handle.in.bup_dcu_lrd.msg_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.msg_ans.irq = NULL;
            mj_handle.in.bup_dcu_lrd.msg_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.msg_ans.total = &in_bup_dcu_lrd_msg_ans_total;
            mj_handle.in.bup_dcu_lrd.msg_ans.miss = &in_bup_dcu_lrd_msg_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.msg_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t)))){
        if(parameter_answer_type_check(mj_handle.in.bup_dcu_lrd.prm_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.prm_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.prm_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.prm_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.prm_ans.lock = in_bup_dcu_lrd_prm_ans_lock_fcn;
            mj_handle.in.bup_dcu_lrd.prm_ans.copy = in_bup_dcu_lrd_prm_ans_copy_fcn;
            mj_handle.in.bup_dcu_lrd.prm_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.prm_ans.irq = NULL;
            mj_handle.in.bup_dcu_lrd.prm_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.prm_ans.total = &in_bup_dcu_lrd_prm_ans_total;
            mj_handle.in.bup_dcu_lrd.prm_ans.miss = &in_bup_dcu_lrd_prm_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lrd.ptp_state.msg = (ptp_info_msg_t *)p_drv->udp4.alloc(sizeof(ptp_info_msg_t)))){
        if(ptp_info_type_check(mj_handle.in.bup_dcu_lrd.ptp_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lrd.ptp_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.ptp_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lrd.ptp_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lrd.ptp_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lrd.ptp_state.lock = in_bup_dcu_lrd_ptp_state_lock_fcn;
            mj_handle.in.bup_dcu_lrd.ptp_state.copy = in_bup_dcu_lrd_ptp_state_copy_fcn;
            mj_handle.in.bup_dcu_lrd.ptp_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_lrd.ptp_state.irq = NULL;
            mj_handle.in.bup_dcu_lrd.ptp_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lrd.ptp_state.total = &in_bup_dcu_lrd_ptp_state_total;
            mj_handle.in.bup_dcu_lrd.ptp_state.miss = &in_bup_dcu_lrd_ptp_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lrd.ptp_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.bup_state.msg = (bup_drv_state_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_state_msg_t)))){
        if(bup_drv_state_type_check(mj_handle.in.bup_dcu_lst.bup_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.bup_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.bup_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.bup_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.bup_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.bup_state.lock = in_bup_dcu_lst_bup_state_lock_fcn;
            mj_handle.in.bup_dcu_lst.bup_state.copy = in_bup_dcu_lst_bup_state_copy_fcn;
            mj_handle.in.bup_dcu_lst.bup_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.bup_state.irq = NULL;
            mj_handle.in.bup_dcu_lst.bup_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.bup_state.total = &in_bup_dcu_lst_bup_state_total;
            mj_handle.in.bup_dcu_lst.bup_state.miss = &in_bup_dcu_lst_bup_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.bup_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.cmd_ans.msg = (command_answer_msg_t *)p_drv->udp4.alloc(sizeof(command_answer_msg_t)))){
        if(command_answer_type_check(mj_handle.in.bup_dcu_lst.cmd_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.cmd_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.cmd_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.cmd_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.cmd_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.cmd_ans.lock = in_bup_dcu_lst_cmd_ans_lock_fcn;
            mj_handle.in.bup_dcu_lst.cmd_ans.copy = in_bup_dcu_lst_cmd_ans_copy_fcn;
            mj_handle.in.bup_dcu_lst.cmd_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.cmd_ans.irq = NULL;
            mj_handle.in.bup_dcu_lst.cmd_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.cmd_ans.total = &in_bup_dcu_lst_cmd_ans_total;
            mj_handle.in.bup_dcu_lst.cmd_ans.miss = &in_bup_dcu_lst_cmd_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.cmd_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.dbg.msg = (dbg_data_msg_t *)p_drv->udp4.alloc(sizeof(dbg_data_msg_t)))){
        if(dbg_data_type_check(mj_handle.in.bup_dcu_lst.dbg.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.dbg.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.dbg.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.dbg.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.dbg.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.dbg.lock = in_bup_dcu_lst_dbg_lock_fcn;
            mj_handle.in.bup_dcu_lst.dbg.copy = in_bup_dcu_lst_dbg_copy_fcn;
            mj_handle.in.bup_dcu_lst.dbg.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.dbg.irq = NULL;
            mj_handle.in.bup_dcu_lst.dbg.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.dbg.total = &in_bup_dcu_lst_dbg_total;
            mj_handle.in.bup_dcu_lst.dbg.miss = &in_bup_dcu_lst_dbg_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.dbg.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.dcu_tel.msg = (dcu_telemetry_msg_t *)p_drv->udp4.alloc(sizeof(dcu_telemetry_msg_t)))){
        if(dcu_telemetry_type_check(mj_handle.in.bup_dcu_lst.dcu_tel.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.dcu_tel.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.dcu_tel.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.dcu_tel.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.dcu_tel.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.dcu_tel.lock = in_bup_dcu_lst_dcu_tel_lock_fcn;
            mj_handle.in.bup_dcu_lst.dcu_tel.copy = in_bup_dcu_lst_dcu_tel_copy_fcn;
            mj_handle.in.bup_dcu_lst.dcu_tel.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.dcu_tel.irq = NULL;
            mj_handle.in.bup_dcu_lst.dcu_tel.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.dcu_tel.total = &in_bup_dcu_lst_dcu_tel_total;
            mj_handle.in.bup_dcu_lst.dcu_tel.miss = &in_bup_dcu_lst_dcu_tel_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.dcu_tel.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)p_drv->udp4.alloc(sizeof(drive_master_ctrl_msg_t)))){
        if(drive_master_ctrl_type_check(mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.lock = in_bup_dcu_lst_drive_master_ctrl_lock_fcn;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.copy = in_bup_dcu_lst_drive_master_ctrl_copy_fcn;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.irq = NULL;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.total = &in_bup_dcu_lst_drive_master_ctrl_total;
            mj_handle.in.bup_dcu_lst.drive_master_ctrl.miss = &in_bup_dcu_lst_drive_master_ctrl_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.drive_master_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.drive_slave_fb.msg = (drive_slave_fb_msg_t *)p_drv->udp4.alloc(sizeof(drive_slave_fb_msg_t)))){
        if(drive_slave_fb_type_check(mj_handle.in.bup_dcu_lst.drive_slave_fb.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.drive_slave_fb.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.lock = in_bup_dcu_lst_drive_slave_fb_lock_fcn;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.copy = in_bup_dcu_lst_drive_slave_fb_copy_fcn;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.irq = NULL;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.total = &in_bup_dcu_lst_drive_slave_fb_total;
            mj_handle.in.bup_dcu_lst.drive_slave_fb.miss = &in_bup_dcu_lst_drive_slave_fb_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.drive_slave_fb.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.formular.msg = (formular_info_msg_t *)p_drv->udp4.alloc(sizeof(formular_info_msg_t)))){
        if(formular_info_type_check(mj_handle.in.bup_dcu_lst.formular.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.formular.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.formular.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.formular.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.formular.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.formular.lock = in_bup_dcu_lst_formular_lock_fcn;
            mj_handle.in.bup_dcu_lst.formular.copy = in_bup_dcu_lst_formular_copy_fcn;
            mj_handle.in.bup_dcu_lst.formular.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.formular.irq = NULL;
            mj_handle.in.bup_dcu_lst.formular.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.formular.total = &in_bup_dcu_lst_formular_total;
            mj_handle.in.bup_dcu_lst.formular.miss = &in_bup_dcu_lst_formular_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.formular.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.msg_ans.msg = (msg_answer_msg_t *)p_drv->udp4.alloc(sizeof(msg_answer_msg_t)))){
        if(msg_answer_type_check(mj_handle.in.bup_dcu_lst.msg_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.msg_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.msg_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.msg_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.msg_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.msg_ans.lock = in_bup_dcu_lst_msg_ans_lock_fcn;
            mj_handle.in.bup_dcu_lst.msg_ans.copy = in_bup_dcu_lst_msg_ans_copy_fcn;
            mj_handle.in.bup_dcu_lst.msg_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.msg_ans.irq = NULL;
            mj_handle.in.bup_dcu_lst.msg_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.msg_ans.total = &in_bup_dcu_lst_msg_ans_total;
            mj_handle.in.bup_dcu_lst.msg_ans.miss = &in_bup_dcu_lst_msg_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.msg_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t)))){
        if(parameter_answer_type_check(mj_handle.in.bup_dcu_lst.prm_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.prm_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.prm_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.prm_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.prm_ans.lock = in_bup_dcu_lst_prm_ans_lock_fcn;
            mj_handle.in.bup_dcu_lst.prm_ans.copy = in_bup_dcu_lst_prm_ans_copy_fcn;
            mj_handle.in.bup_dcu_lst.prm_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.prm_ans.irq = NULL;
            mj_handle.in.bup_dcu_lst.prm_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.prm_ans.total = &in_bup_dcu_lst_prm_ans_total;
            mj_handle.in.bup_dcu_lst.prm_ans.miss = &in_bup_dcu_lst_prm_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_lst.ptp_state.msg = (ptp_info_msg_t *)p_drv->udp4.alloc(sizeof(ptp_info_msg_t)))){
        if(ptp_info_type_check(mj_handle.in.bup_dcu_lst.ptp_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_lst.ptp_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.ptp_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_lst.ptp_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_lst.ptp_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_lst.ptp_state.lock = in_bup_dcu_lst_ptp_state_lock_fcn;
            mj_handle.in.bup_dcu_lst.ptp_state.copy = in_bup_dcu_lst_ptp_state_copy_fcn;
            mj_handle.in.bup_dcu_lst.ptp_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_lst.ptp_state.irq = NULL;
            mj_handle.in.bup_dcu_lst.ptp_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_lst.ptp_state.total = &in_bup_dcu_lst_ptp_state_total;
            mj_handle.in.bup_dcu_lst.ptp_state.miss = &in_bup_dcu_lst_ptp_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_lst.ptp_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.bup_state.msg = (bup_drv_state_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_state_msg_t)))){
        if(bup_drv_state_type_check(mj_handle.in.bup_dcu_rfd.bup_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.bup_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.bup_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.bup_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.bup_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.bup_state.lock = in_bup_dcu_rfd_bup_state_lock_fcn;
            mj_handle.in.bup_dcu_rfd.bup_state.copy = in_bup_dcu_rfd_bup_state_copy_fcn;
            mj_handle.in.bup_dcu_rfd.bup_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.bup_state.irq = NULL;
            mj_handle.in.bup_dcu_rfd.bup_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.bup_state.total = &in_bup_dcu_rfd_bup_state_total;
            mj_handle.in.bup_dcu_rfd.bup_state.miss = &in_bup_dcu_rfd_bup_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.bup_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.cmd_ans.msg = (command_answer_msg_t *)p_drv->udp4.alloc(sizeof(command_answer_msg_t)))){
        if(command_answer_type_check(mj_handle.in.bup_dcu_rfd.cmd_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.cmd_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.cmd_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.cmd_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.cmd_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.cmd_ans.lock = in_bup_dcu_rfd_cmd_ans_lock_fcn;
            mj_handle.in.bup_dcu_rfd.cmd_ans.copy = in_bup_dcu_rfd_cmd_ans_copy_fcn;
            mj_handle.in.bup_dcu_rfd.cmd_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.cmd_ans.irq = NULL;
            mj_handle.in.bup_dcu_rfd.cmd_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.cmd_ans.total = &in_bup_dcu_rfd_cmd_ans_total;
            mj_handle.in.bup_dcu_rfd.cmd_ans.miss = &in_bup_dcu_rfd_cmd_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.cmd_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.dbg.msg = (dbg_data_msg_t *)p_drv->udp4.alloc(sizeof(dbg_data_msg_t)))){
        if(dbg_data_type_check(mj_handle.in.bup_dcu_rfd.dbg.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.dbg.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.dbg.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.dbg.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.dbg.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.dbg.lock = in_bup_dcu_rfd_dbg_lock_fcn;
            mj_handle.in.bup_dcu_rfd.dbg.copy = in_bup_dcu_rfd_dbg_copy_fcn;
            mj_handle.in.bup_dcu_rfd.dbg.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.dbg.irq = NULL;
            mj_handle.in.bup_dcu_rfd.dbg.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.dbg.total = &in_bup_dcu_rfd_dbg_total;
            mj_handle.in.bup_dcu_rfd.dbg.miss = &in_bup_dcu_rfd_dbg_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.dbg.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.dcu_tel.msg = (dcu_telemetry_msg_t *)p_drv->udp4.alloc(sizeof(dcu_telemetry_msg_t)))){
        if(dcu_telemetry_type_check(mj_handle.in.bup_dcu_rfd.dcu_tel.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.dcu_tel.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.dcu_tel.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.dcu_tel.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.dcu_tel.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.dcu_tel.lock = in_bup_dcu_rfd_dcu_tel_lock_fcn;
            mj_handle.in.bup_dcu_rfd.dcu_tel.copy = in_bup_dcu_rfd_dcu_tel_copy_fcn;
            mj_handle.in.bup_dcu_rfd.dcu_tel.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.dcu_tel.irq = NULL;
            mj_handle.in.bup_dcu_rfd.dcu_tel.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.dcu_tel.total = &in_bup_dcu_rfd_dcu_tel_total;
            mj_handle.in.bup_dcu_rfd.dcu_tel.miss = &in_bup_dcu_rfd_dcu_tel_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.dcu_tel.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)p_drv->udp4.alloc(sizeof(drive_master_ctrl_msg_t)))){
        if(drive_master_ctrl_type_check(mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.lock = in_bup_dcu_rfd_drive_master_ctrl_lock_fcn;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.copy = in_bup_dcu_rfd_drive_master_ctrl_copy_fcn;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.irq = NULL;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.total = &in_bup_dcu_rfd_drive_master_ctrl_total;
            mj_handle.in.bup_dcu_rfd.drive_master_ctrl.miss = &in_bup_dcu_rfd_drive_master_ctrl_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.drive_master_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg = (drive_slave_fb_msg_t *)p_drv->udp4.alloc(sizeof(drive_slave_fb_msg_t)))){
        if(drive_slave_fb_type_check(mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.lock = in_bup_dcu_rfd_drive_slave_fb_lock_fcn;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.copy = in_bup_dcu_rfd_drive_slave_fb_copy_fcn;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.irq = NULL;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.total = &in_bup_dcu_rfd_drive_slave_fb_total;
            mj_handle.in.bup_dcu_rfd.drive_slave_fb.miss = &in_bup_dcu_rfd_drive_slave_fb_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.drive_slave_fb.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.formular.msg = (formular_info_msg_t *)p_drv->udp4.alloc(sizeof(formular_info_msg_t)))){
        if(formular_info_type_check(mj_handle.in.bup_dcu_rfd.formular.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.formular.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.formular.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.formular.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.formular.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.formular.lock = in_bup_dcu_rfd_formular_lock_fcn;
            mj_handle.in.bup_dcu_rfd.formular.copy = in_bup_dcu_rfd_formular_copy_fcn;
            mj_handle.in.bup_dcu_rfd.formular.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.formular.irq = NULL;
            mj_handle.in.bup_dcu_rfd.formular.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.formular.total = &in_bup_dcu_rfd_formular_total;
            mj_handle.in.bup_dcu_rfd.formular.miss = &in_bup_dcu_rfd_formular_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.formular.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.msg_ans.msg = (msg_answer_msg_t *)p_drv->udp4.alloc(sizeof(msg_answer_msg_t)))){
        if(msg_answer_type_check(mj_handle.in.bup_dcu_rfd.msg_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.msg_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.msg_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.msg_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.msg_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.msg_ans.lock = in_bup_dcu_rfd_msg_ans_lock_fcn;
            mj_handle.in.bup_dcu_rfd.msg_ans.copy = in_bup_dcu_rfd_msg_ans_copy_fcn;
            mj_handle.in.bup_dcu_rfd.msg_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.msg_ans.irq = NULL;
            mj_handle.in.bup_dcu_rfd.msg_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.msg_ans.total = &in_bup_dcu_rfd_msg_ans_total;
            mj_handle.in.bup_dcu_rfd.msg_ans.miss = &in_bup_dcu_rfd_msg_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.msg_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t)))){
        if(parameter_answer_type_check(mj_handle.in.bup_dcu_rfd.prm_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.prm_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.prm_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.prm_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.prm_ans.lock = in_bup_dcu_rfd_prm_ans_lock_fcn;
            mj_handle.in.bup_dcu_rfd.prm_ans.copy = in_bup_dcu_rfd_prm_ans_copy_fcn;
            mj_handle.in.bup_dcu_rfd.prm_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.prm_ans.irq = NULL;
            mj_handle.in.bup_dcu_rfd.prm_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.prm_ans.total = &in_bup_dcu_rfd_prm_ans_total;
            mj_handle.in.bup_dcu_rfd.prm_ans.miss = &in_bup_dcu_rfd_prm_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rfd.ptp_state.msg = (ptp_info_msg_t *)p_drv->udp4.alloc(sizeof(ptp_info_msg_t)))){
        if(ptp_info_type_check(mj_handle.in.bup_dcu_rfd.ptp_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rfd.ptp_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.ptp_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rfd.ptp_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rfd.ptp_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rfd.ptp_state.lock = in_bup_dcu_rfd_ptp_state_lock_fcn;
            mj_handle.in.bup_dcu_rfd.ptp_state.copy = in_bup_dcu_rfd_ptp_state_copy_fcn;
            mj_handle.in.bup_dcu_rfd.ptp_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_rfd.ptp_state.irq = NULL;
            mj_handle.in.bup_dcu_rfd.ptp_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rfd.ptp_state.total = &in_bup_dcu_rfd_ptp_state_total;
            mj_handle.in.bup_dcu_rfd.ptp_state.miss = &in_bup_dcu_rfd_ptp_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rfd.ptp_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.bup_state.msg = (bup_drv_state_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_state_msg_t)))){
        if(bup_drv_state_type_check(mj_handle.in.bup_dcu_rrd.bup_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.bup_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.bup_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.bup_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.bup_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.bup_state.lock = in_bup_dcu_rrd_bup_state_lock_fcn;
            mj_handle.in.bup_dcu_rrd.bup_state.copy = in_bup_dcu_rrd_bup_state_copy_fcn;
            mj_handle.in.bup_dcu_rrd.bup_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.bup_state.irq = NULL;
            mj_handle.in.bup_dcu_rrd.bup_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.bup_state.total = &in_bup_dcu_rrd_bup_state_total;
            mj_handle.in.bup_dcu_rrd.bup_state.miss = &in_bup_dcu_rrd_bup_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.bup_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.cmd_ans.msg = (command_answer_msg_t *)p_drv->udp4.alloc(sizeof(command_answer_msg_t)))){
        if(command_answer_type_check(mj_handle.in.bup_dcu_rrd.cmd_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.cmd_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.cmd_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.cmd_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.cmd_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.cmd_ans.lock = in_bup_dcu_rrd_cmd_ans_lock_fcn;
            mj_handle.in.bup_dcu_rrd.cmd_ans.copy = in_bup_dcu_rrd_cmd_ans_copy_fcn;
            mj_handle.in.bup_dcu_rrd.cmd_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.cmd_ans.irq = NULL;
            mj_handle.in.bup_dcu_rrd.cmd_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.cmd_ans.total = &in_bup_dcu_rrd_cmd_ans_total;
            mj_handle.in.bup_dcu_rrd.cmd_ans.miss = &in_bup_dcu_rrd_cmd_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.cmd_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.dbg.msg = (dbg_data_msg_t *)p_drv->udp4.alloc(sizeof(dbg_data_msg_t)))){
        if(dbg_data_type_check(mj_handle.in.bup_dcu_rrd.dbg.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.dbg.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.dbg.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.dbg.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.dbg.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.dbg.lock = in_bup_dcu_rrd_dbg_lock_fcn;
            mj_handle.in.bup_dcu_rrd.dbg.copy = in_bup_dcu_rrd_dbg_copy_fcn;
            mj_handle.in.bup_dcu_rrd.dbg.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.dbg.irq = NULL;
            mj_handle.in.bup_dcu_rrd.dbg.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.dbg.total = &in_bup_dcu_rrd_dbg_total;
            mj_handle.in.bup_dcu_rrd.dbg.miss = &in_bup_dcu_rrd_dbg_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.dbg.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.dcu_tel.msg = (dcu_telemetry_msg_t *)p_drv->udp4.alloc(sizeof(dcu_telemetry_msg_t)))){
        if(dcu_telemetry_type_check(mj_handle.in.bup_dcu_rrd.dcu_tel.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.dcu_tel.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.dcu_tel.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.dcu_tel.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.dcu_tel.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.dcu_tel.lock = in_bup_dcu_rrd_dcu_tel_lock_fcn;
            mj_handle.in.bup_dcu_rrd.dcu_tel.copy = in_bup_dcu_rrd_dcu_tel_copy_fcn;
            mj_handle.in.bup_dcu_rrd.dcu_tel.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.dcu_tel.irq = NULL;
            mj_handle.in.bup_dcu_rrd.dcu_tel.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.dcu_tel.total = &in_bup_dcu_rrd_dcu_tel_total;
            mj_handle.in.bup_dcu_rrd.dcu_tel.miss = &in_bup_dcu_rrd_dcu_tel_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.dcu_tel.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)p_drv->udp4.alloc(sizeof(drive_master_ctrl_msg_t)))){
        if(drive_master_ctrl_type_check(mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.lock = in_bup_dcu_rrd_drive_master_ctrl_lock_fcn;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.copy = in_bup_dcu_rrd_drive_master_ctrl_copy_fcn;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.irq = NULL;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.total = &in_bup_dcu_rrd_drive_master_ctrl_total;
            mj_handle.in.bup_dcu_rrd.drive_master_ctrl.miss = &in_bup_dcu_rrd_drive_master_ctrl_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.drive_master_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg = (drive_slave_fb_msg_t *)p_drv->udp4.alloc(sizeof(drive_slave_fb_msg_t)))){
        if(drive_slave_fb_type_check(mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.lock = in_bup_dcu_rrd_drive_slave_fb_lock_fcn;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.copy = in_bup_dcu_rrd_drive_slave_fb_copy_fcn;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.irq = NULL;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.total = &in_bup_dcu_rrd_drive_slave_fb_total;
            mj_handle.in.bup_dcu_rrd.drive_slave_fb.miss = &in_bup_dcu_rrd_drive_slave_fb_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.drive_slave_fb.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.formular.msg = (formular_info_msg_t *)p_drv->udp4.alloc(sizeof(formular_info_msg_t)))){
        if(formular_info_type_check(mj_handle.in.bup_dcu_rrd.formular.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.formular.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.formular.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.formular.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.formular.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.formular.lock = in_bup_dcu_rrd_formular_lock_fcn;
            mj_handle.in.bup_dcu_rrd.formular.copy = in_bup_dcu_rrd_formular_copy_fcn;
            mj_handle.in.bup_dcu_rrd.formular.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.formular.irq = NULL;
            mj_handle.in.bup_dcu_rrd.formular.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.formular.total = &in_bup_dcu_rrd_formular_total;
            mj_handle.in.bup_dcu_rrd.formular.miss = &in_bup_dcu_rrd_formular_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.formular.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.msg_ans.msg = (msg_answer_msg_t *)p_drv->udp4.alloc(sizeof(msg_answer_msg_t)))){
        if(msg_answer_type_check(mj_handle.in.bup_dcu_rrd.msg_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.msg_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.msg_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.msg_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.msg_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.msg_ans.lock = in_bup_dcu_rrd_msg_ans_lock_fcn;
            mj_handle.in.bup_dcu_rrd.msg_ans.copy = in_bup_dcu_rrd_msg_ans_copy_fcn;
            mj_handle.in.bup_dcu_rrd.msg_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.msg_ans.irq = NULL;
            mj_handle.in.bup_dcu_rrd.msg_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.msg_ans.total = &in_bup_dcu_rrd_msg_ans_total;
            mj_handle.in.bup_dcu_rrd.msg_ans.miss = &in_bup_dcu_rrd_msg_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.msg_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t)))){
        if(parameter_answer_type_check(mj_handle.in.bup_dcu_rrd.prm_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.prm_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.prm_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.prm_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.prm_ans.lock = in_bup_dcu_rrd_prm_ans_lock_fcn;
            mj_handle.in.bup_dcu_rrd.prm_ans.copy = in_bup_dcu_rrd_prm_ans_copy_fcn;
            mj_handle.in.bup_dcu_rrd.prm_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.prm_ans.irq = NULL;
            mj_handle.in.bup_dcu_rrd.prm_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.prm_ans.total = &in_bup_dcu_rrd_prm_ans_total;
            mj_handle.in.bup_dcu_rrd.prm_ans.miss = &in_bup_dcu_rrd_prm_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rrd.ptp_state.msg = (ptp_info_msg_t *)p_drv->udp4.alloc(sizeof(ptp_info_msg_t)))){
        if(ptp_info_type_check(mj_handle.in.bup_dcu_rrd.ptp_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rrd.ptp_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.ptp_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rrd.ptp_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rrd.ptp_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rrd.ptp_state.lock = in_bup_dcu_rrd_ptp_state_lock_fcn;
            mj_handle.in.bup_dcu_rrd.ptp_state.copy = in_bup_dcu_rrd_ptp_state_copy_fcn;
            mj_handle.in.bup_dcu_rrd.ptp_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_rrd.ptp_state.irq = NULL;
            mj_handle.in.bup_dcu_rrd.ptp_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rrd.ptp_state.total = &in_bup_dcu_rrd_ptp_state_total;
            mj_handle.in.bup_dcu_rrd.ptp_state.miss = &in_bup_dcu_rrd_ptp_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rrd.ptp_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.bup_state.msg = (bup_drv_state_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_state_msg_t)))){
        if(bup_drv_state_type_check(mj_handle.in.bup_dcu_rst.bup_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.bup_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.bup_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.bup_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.bup_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.bup_state.lock = in_bup_dcu_rst_bup_state_lock_fcn;
            mj_handle.in.bup_dcu_rst.bup_state.copy = in_bup_dcu_rst_bup_state_copy_fcn;
            mj_handle.in.bup_dcu_rst.bup_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.bup_state.irq = NULL;
            mj_handle.in.bup_dcu_rst.bup_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.bup_state.total = &in_bup_dcu_rst_bup_state_total;
            mj_handle.in.bup_dcu_rst.bup_state.miss = &in_bup_dcu_rst_bup_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.bup_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.cmd_ans.msg = (command_answer_msg_t *)p_drv->udp4.alloc(sizeof(command_answer_msg_t)))){
        if(command_answer_type_check(mj_handle.in.bup_dcu_rst.cmd_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.cmd_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.cmd_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.cmd_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.cmd_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.cmd_ans.lock = in_bup_dcu_rst_cmd_ans_lock_fcn;
            mj_handle.in.bup_dcu_rst.cmd_ans.copy = in_bup_dcu_rst_cmd_ans_copy_fcn;
            mj_handle.in.bup_dcu_rst.cmd_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.cmd_ans.irq = NULL;
            mj_handle.in.bup_dcu_rst.cmd_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.cmd_ans.total = &in_bup_dcu_rst_cmd_ans_total;
            mj_handle.in.bup_dcu_rst.cmd_ans.miss = &in_bup_dcu_rst_cmd_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.cmd_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.dbg.msg = (dbg_data_msg_t *)p_drv->udp4.alloc(sizeof(dbg_data_msg_t)))){
        if(dbg_data_type_check(mj_handle.in.bup_dcu_rst.dbg.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.dbg.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.dbg.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.dbg.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.dbg.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.dbg.lock = in_bup_dcu_rst_dbg_lock_fcn;
            mj_handle.in.bup_dcu_rst.dbg.copy = in_bup_dcu_rst_dbg_copy_fcn;
            mj_handle.in.bup_dcu_rst.dbg.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.dbg.irq = NULL;
            mj_handle.in.bup_dcu_rst.dbg.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.dbg.total = &in_bup_dcu_rst_dbg_total;
            mj_handle.in.bup_dcu_rst.dbg.miss = &in_bup_dcu_rst_dbg_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.dbg.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.dcu_tel.msg = (dcu_telemetry_msg_t *)p_drv->udp4.alloc(sizeof(dcu_telemetry_msg_t)))){
        if(dcu_telemetry_type_check(mj_handle.in.bup_dcu_rst.dcu_tel.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.dcu_tel.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.dcu_tel.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.dcu_tel.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.dcu_tel.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.dcu_tel.lock = in_bup_dcu_rst_dcu_tel_lock_fcn;
            mj_handle.in.bup_dcu_rst.dcu_tel.copy = in_bup_dcu_rst_dcu_tel_copy_fcn;
            mj_handle.in.bup_dcu_rst.dcu_tel.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.dcu_tel.irq = NULL;
            mj_handle.in.bup_dcu_rst.dcu_tel.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.dcu_tel.total = &in_bup_dcu_rst_dcu_tel_total;
            mj_handle.in.bup_dcu_rst.dcu_tel.miss = &in_bup_dcu_rst_dcu_tel_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.dcu_tel.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)p_drv->udp4.alloc(sizeof(drive_master_ctrl_msg_t)))){
        if(drive_master_ctrl_type_check(mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.lock = in_bup_dcu_rst_drive_master_ctrl_lock_fcn;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.copy = in_bup_dcu_rst_drive_master_ctrl_copy_fcn;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.irq = NULL;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.total = &in_bup_dcu_rst_drive_master_ctrl_total;
            mj_handle.in.bup_dcu_rst.drive_master_ctrl.miss = &in_bup_dcu_rst_drive_master_ctrl_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.drive_master_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.drive_slave_fb.msg = (drive_slave_fb_msg_t *)p_drv->udp4.alloc(sizeof(drive_slave_fb_msg_t)))){
        if(drive_slave_fb_type_check(mj_handle.in.bup_dcu_rst.drive_slave_fb.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.drive_slave_fb.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.lock = in_bup_dcu_rst_drive_slave_fb_lock_fcn;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.copy = in_bup_dcu_rst_drive_slave_fb_copy_fcn;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.irq = NULL;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.total = &in_bup_dcu_rst_drive_slave_fb_total;
            mj_handle.in.bup_dcu_rst.drive_slave_fb.miss = &in_bup_dcu_rst_drive_slave_fb_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.drive_slave_fb.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.formular.msg = (formular_info_msg_t *)p_drv->udp4.alloc(sizeof(formular_info_msg_t)))){
        if(formular_info_type_check(mj_handle.in.bup_dcu_rst.formular.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.formular.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.formular.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.formular.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.formular.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.formular.lock = in_bup_dcu_rst_formular_lock_fcn;
            mj_handle.in.bup_dcu_rst.formular.copy = in_bup_dcu_rst_formular_copy_fcn;
            mj_handle.in.bup_dcu_rst.formular.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.formular.irq = NULL;
            mj_handle.in.bup_dcu_rst.formular.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.formular.total = &in_bup_dcu_rst_formular_total;
            mj_handle.in.bup_dcu_rst.formular.miss = &in_bup_dcu_rst_formular_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.formular.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.msg_ans.msg = (msg_answer_msg_t *)p_drv->udp4.alloc(sizeof(msg_answer_msg_t)))){
        if(msg_answer_type_check(mj_handle.in.bup_dcu_rst.msg_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.msg_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.msg_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.msg_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.msg_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.msg_ans.lock = in_bup_dcu_rst_msg_ans_lock_fcn;
            mj_handle.in.bup_dcu_rst.msg_ans.copy = in_bup_dcu_rst_msg_ans_copy_fcn;
            mj_handle.in.bup_dcu_rst.msg_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.msg_ans.irq = NULL;
            mj_handle.in.bup_dcu_rst.msg_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.msg_ans.total = &in_bup_dcu_rst_msg_ans_total;
            mj_handle.in.bup_dcu_rst.msg_ans.miss = &in_bup_dcu_rst_msg_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.msg_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t)))){
        if(parameter_answer_type_check(mj_handle.in.bup_dcu_rst.prm_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.prm_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.prm_ans.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.prm_ans.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.prm_ans.lock = in_bup_dcu_rst_prm_ans_lock_fcn;
            mj_handle.in.bup_dcu_rst.prm_ans.copy = in_bup_dcu_rst_prm_ans_copy_fcn;
            mj_handle.in.bup_dcu_rst.prm_ans.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.prm_ans.irq = NULL;
            mj_handle.in.bup_dcu_rst.prm_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.prm_ans.total = &in_bup_dcu_rst_prm_ans_total;
            mj_handle.in.bup_dcu_rst.prm_ans.miss = &in_bup_dcu_rst_prm_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.bup_dcu_rst.ptp_state.msg = (ptp_info_msg_t *)p_drv->udp4.alloc(sizeof(ptp_info_msg_t)))){
        if(ptp_info_type_check(mj_handle.in.bup_dcu_rst.ptp_state.msg) == MJ_CHECK_OK){
            mj_handle.in.bup_dcu_rst.ptp_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.ptp_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.bup_dcu_rst.ptp_state.msg->hdr.cnt = 0;
            mj_handle.in.bup_dcu_rst.ptp_state.msg->hdr.id = 0;
            mj_handle.in.bup_dcu_rst.ptp_state.lock = in_bup_dcu_rst_ptp_state_lock_fcn;
            mj_handle.in.bup_dcu_rst.ptp_state.copy = in_bup_dcu_rst_ptp_state_copy_fcn;
            mj_handle.in.bup_dcu_rst.ptp_state.upd_cb = NULL;
            mj_handle.in.bup_dcu_rst.ptp_state.irq = NULL;
            mj_handle.in.bup_dcu_rst.ptp_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.bup_dcu_rst.ptp_state.total = &in_bup_dcu_rst_ptp_state_total;
            mj_handle.in.bup_dcu_rst.ptp_state.miss = &in_bup_dcu_rst_ptp_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.bup_dcu_rst.ptp_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.bup_state.msg = (bup_drv_state_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_state_msg_t)))){
        if(bup_drv_state_type_check(mj_handle.in.dcu.bup_state.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.bup_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.bup_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.bup_state.msg->hdr.cnt = 0;
            mj_handle.in.dcu.bup_state.msg->hdr.id = 0;
            mj_handle.in.dcu.bup_state.lock = in_dcu_bup_state_lock_fcn;
            mj_handle.in.dcu.bup_state.copy = in_dcu_bup_state_copy_fcn;
            mj_handle.in.dcu.bup_state.upd_cb = NULL;
            mj_handle.in.dcu.bup_state.irq = NULL;
            mj_handle.in.dcu.bup_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.bup_state.total = &in_dcu_bup_state_total;
            mj_handle.in.dcu.bup_state.miss = &in_dcu_bup_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.bup_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.cmd_ans.msg = (command_answer_msg_t *)p_drv->udp4.alloc(sizeof(command_answer_msg_t)))){
        if(command_answer_type_check(mj_handle.in.dcu.cmd_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.cmd_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.cmd_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.cmd_ans.msg->hdr.cnt = 0;
            mj_handle.in.dcu.cmd_ans.msg->hdr.id = 0;
            mj_handle.in.dcu.cmd_ans.lock = in_dcu_cmd_ans_lock_fcn;
            mj_handle.in.dcu.cmd_ans.copy = in_dcu_cmd_ans_copy_fcn;
            mj_handle.in.dcu.cmd_ans.upd_cb = NULL;
            mj_handle.in.dcu.cmd_ans.irq = NULL;
            mj_handle.in.dcu.cmd_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.cmd_ans.total = &in_dcu_cmd_ans_total;
            mj_handle.in.dcu.cmd_ans.miss = &in_dcu_cmd_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.cmd_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.dbg.msg = (dbg_data_msg_t *)p_drv->udp4.alloc(sizeof(dbg_data_msg_t)))){
        if(dbg_data_type_check(mj_handle.in.dcu.dbg.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.dbg.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.dbg.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.dbg.msg->hdr.cnt = 0;
            mj_handle.in.dcu.dbg.msg->hdr.id = 0;
            mj_handle.in.dcu.dbg.lock = in_dcu_dbg_lock_fcn;
            mj_handle.in.dcu.dbg.copy = in_dcu_dbg_copy_fcn;
            mj_handle.in.dcu.dbg.upd_cb = NULL;
            mj_handle.in.dcu.dbg.irq = NULL;
            mj_handle.in.dcu.dbg.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.dbg.total = &in_dcu_dbg_total;
            mj_handle.in.dcu.dbg.miss = &in_dcu_dbg_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.dbg.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.dcu_tel.msg = (dcu_telemetry_msg_t *)p_drv->udp4.alloc(sizeof(dcu_telemetry_msg_t)))){
        if(dcu_telemetry_type_check(mj_handle.in.dcu.dcu_tel.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.dcu_tel.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.dcu_tel.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.dcu_tel.msg->hdr.cnt = 0;
            mj_handle.in.dcu.dcu_tel.msg->hdr.id = 0;
            mj_handle.in.dcu.dcu_tel.lock = in_dcu_dcu_tel_lock_fcn;
            mj_handle.in.dcu.dcu_tel.copy = in_dcu_dcu_tel_copy_fcn;
            mj_handle.in.dcu.dcu_tel.upd_cb = NULL;
            mj_handle.in.dcu.dcu_tel.irq = NULL;
            mj_handle.in.dcu.dcu_tel.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.dcu_tel.total = &in_dcu_dcu_tel_total;
            mj_handle.in.dcu.dcu_tel.miss = &in_dcu_dcu_tel_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.dcu_tel.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)p_drv->udp4.alloc(sizeof(drive_master_ctrl_msg_t)))){
        if(drive_master_ctrl_type_check(mj_handle.in.dcu.drive_master_ctrl.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.drive_master_ctrl.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.drive_master_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.drive_master_ctrl.msg->hdr.cnt = 0;
            mj_handle.in.dcu.drive_master_ctrl.msg->hdr.id = 0;
            mj_handle.in.dcu.drive_master_ctrl.lock = in_dcu_drive_master_ctrl_lock_fcn;
            mj_handle.in.dcu.drive_master_ctrl.copy = in_dcu_drive_master_ctrl_copy_fcn;
            mj_handle.in.dcu.drive_master_ctrl.upd_cb = NULL;
            mj_handle.in.dcu.drive_master_ctrl.irq = NULL;
            mj_handle.in.dcu.drive_master_ctrl.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.drive_master_ctrl.total = &in_dcu_drive_master_ctrl_total;
            mj_handle.in.dcu.drive_master_ctrl.miss = &in_dcu_drive_master_ctrl_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.drive_master_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.drive_slave_fb.msg = (drive_slave_fb_msg_t *)p_drv->udp4.alloc(sizeof(drive_slave_fb_msg_t)))){
        if(drive_slave_fb_type_check(mj_handle.in.dcu.drive_slave_fb.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.drive_slave_fb.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.drive_slave_fb.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.drive_slave_fb.msg->hdr.cnt = 0;
            mj_handle.in.dcu.drive_slave_fb.msg->hdr.id = 0;
            mj_handle.in.dcu.drive_slave_fb.lock = in_dcu_drive_slave_fb_lock_fcn;
            mj_handle.in.dcu.drive_slave_fb.copy = in_dcu_drive_slave_fb_copy_fcn;
            mj_handle.in.dcu.drive_slave_fb.upd_cb = NULL;
            mj_handle.in.dcu.drive_slave_fb.irq = NULL;
            mj_handle.in.dcu.drive_slave_fb.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.drive_slave_fb.total = &in_dcu_drive_slave_fb_total;
            mj_handle.in.dcu.drive_slave_fb.miss = &in_dcu_drive_slave_fb_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.drive_slave_fb.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.formular.msg = (formular_info_msg_t *)p_drv->udp4.alloc(sizeof(formular_info_msg_t)))){
        if(formular_info_type_check(mj_handle.in.dcu.formular.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.formular.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.formular.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.formular.msg->hdr.cnt = 0;
            mj_handle.in.dcu.formular.msg->hdr.id = 0;
            mj_handle.in.dcu.formular.lock = in_dcu_formular_lock_fcn;
            mj_handle.in.dcu.formular.copy = in_dcu_formular_copy_fcn;
            mj_handle.in.dcu.formular.upd_cb = NULL;
            mj_handle.in.dcu.formular.irq = NULL;
            mj_handle.in.dcu.formular.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.formular.total = &in_dcu_formular_total;
            mj_handle.in.dcu.formular.miss = &in_dcu_formular_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.formular.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.msg_ans.msg = (msg_answer_msg_t *)p_drv->udp4.alloc(sizeof(msg_answer_msg_t)))){
        if(msg_answer_type_check(mj_handle.in.dcu.msg_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.msg_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.msg_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.msg_ans.msg->hdr.cnt = 0;
            mj_handle.in.dcu.msg_ans.msg->hdr.id = 0;
            mj_handle.in.dcu.msg_ans.lock = in_dcu_msg_ans_lock_fcn;
            mj_handle.in.dcu.msg_ans.copy = in_dcu_msg_ans_copy_fcn;
            mj_handle.in.dcu.msg_ans.upd_cb = NULL;
            mj_handle.in.dcu.msg_ans.irq = NULL;
            mj_handle.in.dcu.msg_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.msg_ans.total = &in_dcu_msg_ans_total;
            mj_handle.in.dcu.msg_ans.miss = &in_dcu_msg_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.msg_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t)))){
        if(parameter_answer_type_check(mj_handle.in.dcu.prm_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.prm_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.prm_ans.msg->hdr.cnt = 0;
            mj_handle.in.dcu.prm_ans.msg->hdr.id = 0;
            mj_handle.in.dcu.prm_ans.lock = in_dcu_prm_ans_lock_fcn;
            mj_handle.in.dcu.prm_ans.copy = in_dcu_prm_ans_copy_fcn;
            mj_handle.in.dcu.prm_ans.upd_cb = NULL;
            mj_handle.in.dcu.prm_ans.irq = NULL;
            mj_handle.in.dcu.prm_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.prm_ans.total = &in_dcu_prm_ans_total;
            mj_handle.in.dcu.prm_ans.miss = &in_dcu_prm_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.dcu.ptp_state.msg = (ptp_info_msg_t *)p_drv->udp4.alloc(sizeof(ptp_info_msg_t)))){
        if(ptp_info_type_check(mj_handle.in.dcu.ptp_state.msg) == MJ_CHECK_OK){
            mj_handle.in.dcu.ptp_state.msg->hdr.src = BRO30_NONE;
            mj_handle.in.dcu.ptp_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.dcu.ptp_state.msg->hdr.cnt = 0;
            mj_handle.in.dcu.ptp_state.msg->hdr.id = 0;
            mj_handle.in.dcu.ptp_state.lock = in_dcu_ptp_state_lock_fcn;
            mj_handle.in.dcu.ptp_state.copy = in_dcu_ptp_state_copy_fcn;
            mj_handle.in.dcu.ptp_state.upd_cb = NULL;
            mj_handle.in.dcu.ptp_state.irq = NULL;
            mj_handle.in.dcu.ptp_state.state = MJ_MSG_OBSOLETE;
            mj_handle.in.dcu.ptp_state.total = &in_dcu_ptp_state_total;
            mj_handle.in.dcu.ptp_state.miss = &in_dcu_ptp_state_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.dcu.ptp_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.im_bro.im_bro_drivers_sens.msg = (drivers_sens_msg_t *)p_drv->udp4.alloc(sizeof(drivers_sens_msg_t)))){
        if(drivers_sens_type_check(mj_handle.in.im_bro.im_bro_drivers_sens.msg) == MJ_CHECK_OK){
            mj_handle.in.im_bro.im_bro_drivers_sens.msg->hdr.src = BRO30_NONE;
            mj_handle.in.im_bro.im_bro_drivers_sens.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.im_bro.im_bro_drivers_sens.msg->hdr.cnt = 0;
            mj_handle.in.im_bro.im_bro_drivers_sens.msg->hdr.id = 0;
            mj_handle.in.im_bro.im_bro_drivers_sens.lock = in_im_bro_im_bro_drivers_sens_lock_fcn;
            mj_handle.in.im_bro.im_bro_drivers_sens.copy = in_im_bro_im_bro_drivers_sens_copy_fcn;
            mj_handle.in.im_bro.im_bro_drivers_sens.upd_cb = NULL;
            mj_handle.in.im_bro.im_bro_drivers_sens.irq = NULL;
            mj_handle.in.im_bro.im_bro_drivers_sens.state = MJ_MSG_OBSOLETE;
            mj_handle.in.im_bro.im_bro_drivers_sens.total = &in_im_bro_im_bro_drivers_sens_total;
            mj_handle.in.im_bro.im_bro_drivers_sens.miss = &in_im_bro_im_bro_drivers_sens_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.im_bro.im_bro_drivers_sens.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.im_bro.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t)))){
        if(parameter_answer_type_check(mj_handle.in.im_bro.prm_ans.msg) == MJ_CHECK_OK){
            mj_handle.in.im_bro.prm_ans.msg->hdr.src = BRO30_NONE;
            mj_handle.in.im_bro.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.im_bro.prm_ans.msg->hdr.cnt = 0;
            mj_handle.in.im_bro.prm_ans.msg->hdr.id = 0;
            mj_handle.in.im_bro.prm_ans.lock = in_im_bro_prm_ans_lock_fcn;
            mj_handle.in.im_bro.prm_ans.copy = in_im_bro_prm_ans_copy_fcn;
            mj_handle.in.im_bro.prm_ans.upd_cb = NULL;
            mj_handle.in.im_bro.prm_ans.irq = NULL;
            mj_handle.in.im_bro.prm_ans.state = MJ_MSG_OBSOLETE;
            mj_handle.in.im_bro.prm_ans.total = &in_im_bro_prm_ans_total;
            mj_handle.in.im_bro.prm_ans.miss = &in_im_bro_prm_ans_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.im_bro.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }


    mj_handle.tick = tick_fcn;
    mj_handle.loop = loop_fcn;
    *ptr = &mj_handle;

    return MJ_OK;
}