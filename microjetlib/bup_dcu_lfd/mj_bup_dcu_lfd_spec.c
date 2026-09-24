#include "mj_bup_dcu_lfd_spec.h"

#define IN_INT_COUNT 5

static uint32_t group_addr[IN_INT_COUNT*2];

static const uint8_t devMac[6] = { 0x2,0x0,0x0,0x0,0x0,0x1 };

static uint32_t ticks = 0;
static void *ethInt = NULL;
static mj_drv_interface_t * p_drv = NULL;
static uint16_t self_dev_id = BRO30_BUP_DCU_LFD;

static mj_bup_dcu_lfd_t mj_handle;

static uint32_t aufd_bup_ctrl_rx_tick = UINT32_MAX - 241.0;
static uint8_t  in_aufd_bup_ctrl_lock_cnt = 0;
static bup_drv_control_msg_t* in_aufd_bup_ctrl_delayed_ptr = NULL;
static uint32_t aufd_bup_ctrl_delayed_ts_s = 0;
static uint32_t aufd_bup_ctrl_delayed_ts_ns = 0;
static uint8_t  in_aufd_bup_ctrl_updated = 0;
static uint32_t  in_aufd_bup_ctrl_total = 0;
static uint32_t  in_aufd_bup_ctrl_miss = 0;
static uint16_t  in_aufd_bup_ctrl_last_cnt = 0;
static mj_msg_state_t in_aufd_bup_ctrl_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_aufd_bup_ctrl_lock_cnt < 255)
        {
            in_aufd_bup_ctrl_lock_cnt++;
        }
    }else{
        if (in_aufd_bup_ctrl_lock_cnt > 0)
        {
            if ((in_aufd_bup_ctrl_lock_cnt == 1) && (in_aufd_bup_ctrl_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.aufd.bup_ctrl.msg);
                mj_handle.in.aufd.bup_ctrl.msg = (bup_drv_control_msg_t*)(in_aufd_bup_ctrl_delayed_ptr);
                mj_handle.in.aufd.bup_ctrl.ts_s = aufd_bup_ctrl_delayed_ts_s;
                mj_handle.in.aufd.bup_ctrl.ts_ns = aufd_bup_ctrl_delayed_ts_ns;
                aufd_bup_ctrl_rx_tick = ticks;
                mj_handle.in.aufd.bup_ctrl.state = MJ_MSG_ACTUAL;
                in_aufd_bup_ctrl_updated = 1;
                p_drv->udp4.free(old_buff);
                in_aufd_bup_ctrl_delayed_ptr = NULL;
            }
            in_aufd_bup_ctrl_lock_cnt--;
        }
    }
    return in_aufd_bup_ctrl_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_aufd_bup_ctrl_copy_fcn(void *dst)
{
    in_aufd_bup_ctrl_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.aufd.bup_ctrl.msg), sizeof(bup_drv_control_msg_t));
    in_aufd_bup_ctrl_lock_fcn(MJ_MSG_UNLOCK);
}

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

static uint32_t aufd_cmd_req_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_aufd_cmd_req_lock_cnt = 0;
static command_request_msg_t* in_aufd_cmd_req_delayed_ptr = NULL;
static uint32_t aufd_cmd_req_delayed_ts_s = 0;
static uint32_t aufd_cmd_req_delayed_ts_ns = 0;
static uint8_t  in_aufd_cmd_req_updated = 0;
static uint32_t  in_aufd_cmd_req_total = 0;
static uint32_t  in_aufd_cmd_req_miss = 0;
static uint16_t  in_aufd_cmd_req_last_cnt = 0;
static mj_msg_state_t in_aufd_cmd_req_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_aufd_cmd_req_lock_cnt < 255)
        {
            in_aufd_cmd_req_lock_cnt++;
        }
    }else{
        if (in_aufd_cmd_req_lock_cnt > 0)
        {
            if ((in_aufd_cmd_req_lock_cnt == 1) && (in_aufd_cmd_req_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.aufd.cmd_req.msg);
                mj_handle.in.aufd.cmd_req.msg = (command_request_msg_t*)(in_aufd_cmd_req_delayed_ptr);
                mj_handle.in.aufd.cmd_req.ts_s = aufd_cmd_req_delayed_ts_s;
                mj_handle.in.aufd.cmd_req.ts_ns = aufd_cmd_req_delayed_ts_ns;
                aufd_cmd_req_rx_tick = ticks;
                mj_handle.in.aufd.cmd_req.state = MJ_MSG_ACTUAL;
                in_aufd_cmd_req_updated = 1;
                p_drv->udp4.free(old_buff);
                in_aufd_cmd_req_delayed_ptr = NULL;
            }
            in_aufd_cmd_req_lock_cnt--;
        }
    }
    return in_aufd_cmd_req_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_aufd_cmd_req_copy_fcn(void *dst)
{
    in_aufd_cmd_req_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.aufd.cmd_req.msg), sizeof(command_request_msg_t));
    in_aufd_cmd_req_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t aufd_msg_req_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_aufd_msg_req_lock_cnt = 0;
static msg_request_msg_t* in_aufd_msg_req_delayed_ptr = NULL;
static uint32_t aufd_msg_req_delayed_ts_s = 0;
static uint32_t aufd_msg_req_delayed_ts_ns = 0;
static uint8_t  in_aufd_msg_req_updated = 0;
static uint32_t  in_aufd_msg_req_total = 0;
static uint32_t  in_aufd_msg_req_miss = 0;
static uint16_t  in_aufd_msg_req_last_cnt = 0;
static mj_msg_state_t in_aufd_msg_req_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_aufd_msg_req_lock_cnt < 255)
        {
            in_aufd_msg_req_lock_cnt++;
        }
    }else{
        if (in_aufd_msg_req_lock_cnt > 0)
        {
            if ((in_aufd_msg_req_lock_cnt == 1) && (in_aufd_msg_req_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.aufd.msg_req.msg);
                mj_handle.in.aufd.msg_req.msg = (msg_request_msg_t*)(in_aufd_msg_req_delayed_ptr);
                mj_handle.in.aufd.msg_req.ts_s = aufd_msg_req_delayed_ts_s;
                mj_handle.in.aufd.msg_req.ts_ns = aufd_msg_req_delayed_ts_ns;
                aufd_msg_req_rx_tick = ticks;
                mj_handle.in.aufd.msg_req.state = MJ_MSG_ACTUAL;
                in_aufd_msg_req_updated = 1;
                p_drv->udp4.free(old_buff);
                in_aufd_msg_req_delayed_ptr = NULL;
            }
            in_aufd_msg_req_lock_cnt--;
        }
    }
    return in_aufd_msg_req_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_aufd_msg_req_copy_fcn(void *dst)
{
    in_aufd_msg_req_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.aufd.msg_req.msg), sizeof(msg_request_msg_t));
    in_aufd_msg_req_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t aufd_prm_req_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_aufd_prm_req_lock_cnt = 0;
static parameter_request_msg_t* in_aufd_prm_req_delayed_ptr = NULL;
static uint32_t aufd_prm_req_delayed_ts_s = 0;
static uint32_t aufd_prm_req_delayed_ts_ns = 0;
static uint8_t  in_aufd_prm_req_updated = 0;
static uint32_t  in_aufd_prm_req_total = 0;
static uint32_t  in_aufd_prm_req_miss = 0;
static uint16_t  in_aufd_prm_req_last_cnt = 0;
static mj_msg_state_t in_aufd_prm_req_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_aufd_prm_req_lock_cnt < 255)
        {
            in_aufd_prm_req_lock_cnt++;
        }
    }else{
        if (in_aufd_prm_req_lock_cnt > 0)
        {
            if ((in_aufd_prm_req_lock_cnt == 1) && (in_aufd_prm_req_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.aufd.prm_req.msg);
                mj_handle.in.aufd.prm_req.msg = (parameter_request_msg_t*)(in_aufd_prm_req_delayed_ptr);
                mj_handle.in.aufd.prm_req.ts_s = aufd_prm_req_delayed_ts_s;
                mj_handle.in.aufd.prm_req.ts_ns = aufd_prm_req_delayed_ts_ns;
                aufd_prm_req_rx_tick = ticks;
                mj_handle.in.aufd.prm_req.state = MJ_MSG_ACTUAL;
                in_aufd_prm_req_updated = 1;
                p_drv->udp4.free(old_buff);
                in_aufd_prm_req_delayed_ptr = NULL;
            }
            in_aufd_prm_req_lock_cnt--;
        }
    }
    return in_aufd_prm_req_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_aufd_prm_req_copy_fcn(void *dst)
{
    in_aufd_prm_req_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.aufd.prm_req.msg), sizeof(parameter_request_msg_t));
    in_aufd_prm_req_lock_fcn(MJ_MSG_UNLOCK);
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

static uint32_t mon_bup_multi_control_rx_tick = UINT32_MAX - 241.0;
static uint8_t  in_mon_bup_multi_control_lock_cnt = 0;
static bup_drv_multi_control_msg_t* in_mon_bup_multi_control_delayed_ptr = NULL;
static uint32_t mon_bup_multi_control_delayed_ts_s = 0;
static uint32_t mon_bup_multi_control_delayed_ts_ns = 0;
static uint8_t  in_mon_bup_multi_control_updated = 0;
static uint32_t  in_mon_bup_multi_control_total = 0;
static uint32_t  in_mon_bup_multi_control_miss = 0;
static uint16_t  in_mon_bup_multi_control_last_cnt = 0;
static mj_msg_state_t in_mon_bup_multi_control_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_mon_bup_multi_control_lock_cnt < 255)
        {
            in_mon_bup_multi_control_lock_cnt++;
        }
    }else{
        if (in_mon_bup_multi_control_lock_cnt > 0)
        {
            if ((in_mon_bup_multi_control_lock_cnt == 1) && (in_mon_bup_multi_control_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.mon.bup_multi_control.msg);
                mj_handle.in.mon.bup_multi_control.msg = (bup_drv_multi_control_msg_t*)(in_mon_bup_multi_control_delayed_ptr);
                mj_handle.in.mon.bup_multi_control.ts_s = mon_bup_multi_control_delayed_ts_s;
                mj_handle.in.mon.bup_multi_control.ts_ns = mon_bup_multi_control_delayed_ts_ns;
                mon_bup_multi_control_rx_tick = ticks;
                mj_handle.in.mon.bup_multi_control.state = MJ_MSG_ACTUAL;
                in_mon_bup_multi_control_updated = 1;
                p_drv->udp4.free(old_buff);
                in_mon_bup_multi_control_delayed_ptr = NULL;
            }
            in_mon_bup_multi_control_lock_cnt--;
        }
    }
    return in_mon_bup_multi_control_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_mon_bup_multi_control_copy_fcn(void *dst)
{
    in_mon_bup_multi_control_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.mon.bup_multi_control.msg), sizeof(bup_drv_multi_control_msg_t));
    in_mon_bup_multi_control_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t mon_bup_srv_ctrl_rx_tick = UINT32_MAX - 241.0;
static uint8_t  in_mon_bup_srv_ctrl_lock_cnt = 0;
static bup_drv_control_msg_t* in_mon_bup_srv_ctrl_delayed_ptr = NULL;
static uint32_t mon_bup_srv_ctrl_delayed_ts_s = 0;
static uint32_t mon_bup_srv_ctrl_delayed_ts_ns = 0;
static uint8_t  in_mon_bup_srv_ctrl_updated = 0;
static uint32_t  in_mon_bup_srv_ctrl_total = 0;
static uint32_t  in_mon_bup_srv_ctrl_miss = 0;
static uint16_t  in_mon_bup_srv_ctrl_last_cnt = 0;
static mj_msg_state_t in_mon_bup_srv_ctrl_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_mon_bup_srv_ctrl_lock_cnt < 255)
        {
            in_mon_bup_srv_ctrl_lock_cnt++;
        }
    }else{
        if (in_mon_bup_srv_ctrl_lock_cnt > 0)
        {
            if ((in_mon_bup_srv_ctrl_lock_cnt == 1) && (in_mon_bup_srv_ctrl_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.mon.bup_srv_ctrl.msg);
                mj_handle.in.mon.bup_srv_ctrl.msg = (bup_drv_control_msg_t*)(in_mon_bup_srv_ctrl_delayed_ptr);
                mj_handle.in.mon.bup_srv_ctrl.ts_s = mon_bup_srv_ctrl_delayed_ts_s;
                mj_handle.in.mon.bup_srv_ctrl.ts_ns = mon_bup_srv_ctrl_delayed_ts_ns;
                mon_bup_srv_ctrl_rx_tick = ticks;
                mj_handle.in.mon.bup_srv_ctrl.state = MJ_MSG_ACTUAL;
                in_mon_bup_srv_ctrl_updated = 1;
                p_drv->udp4.free(old_buff);
                in_mon_bup_srv_ctrl_delayed_ptr = NULL;
            }
            in_mon_bup_srv_ctrl_lock_cnt--;
        }
    }
    return in_mon_bup_srv_ctrl_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_mon_bup_srv_ctrl_copy_fcn(void *dst)
{
    in_mon_bup_srv_ctrl_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.mon.bup_srv_ctrl.msg), sizeof(bup_drv_control_msg_t));
    in_mon_bup_srv_ctrl_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t mon_cmd_req_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_mon_cmd_req_lock_cnt = 0;
static command_request_msg_t* in_mon_cmd_req_delayed_ptr = NULL;
static uint32_t mon_cmd_req_delayed_ts_s = 0;
static uint32_t mon_cmd_req_delayed_ts_ns = 0;
static uint8_t  in_mon_cmd_req_updated = 0;
static uint32_t  in_mon_cmd_req_total = 0;
static uint32_t  in_mon_cmd_req_miss = 0;
static uint16_t  in_mon_cmd_req_last_cnt = 0;
static mj_msg_state_t in_mon_cmd_req_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_mon_cmd_req_lock_cnt < 255)
        {
            in_mon_cmd_req_lock_cnt++;
        }
    }else{
        if (in_mon_cmd_req_lock_cnt > 0)
        {
            if ((in_mon_cmd_req_lock_cnt == 1) && (in_mon_cmd_req_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.mon.cmd_req.msg);
                mj_handle.in.mon.cmd_req.msg = (command_request_msg_t*)(in_mon_cmd_req_delayed_ptr);
                mj_handle.in.mon.cmd_req.ts_s = mon_cmd_req_delayed_ts_s;
                mj_handle.in.mon.cmd_req.ts_ns = mon_cmd_req_delayed_ts_ns;
                mon_cmd_req_rx_tick = ticks;
                mj_handle.in.mon.cmd_req.state = MJ_MSG_ACTUAL;
                in_mon_cmd_req_updated = 1;
                p_drv->udp4.free(old_buff);
                in_mon_cmd_req_delayed_ptr = NULL;
            }
            in_mon_cmd_req_lock_cnt--;
        }
    }
    return in_mon_cmd_req_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_mon_cmd_req_copy_fcn(void *dst)
{
    in_mon_cmd_req_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.mon.cmd_req.msg), sizeof(command_request_msg_t));
    in_mon_cmd_req_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t mon_msg_req_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_mon_msg_req_lock_cnt = 0;
static msg_request_msg_t* in_mon_msg_req_delayed_ptr = NULL;
static uint32_t mon_msg_req_delayed_ts_s = 0;
static uint32_t mon_msg_req_delayed_ts_ns = 0;
static uint8_t  in_mon_msg_req_updated = 0;
static uint32_t  in_mon_msg_req_total = 0;
static uint32_t  in_mon_msg_req_miss = 0;
static uint16_t  in_mon_msg_req_last_cnt = 0;
static mj_msg_state_t in_mon_msg_req_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_mon_msg_req_lock_cnt < 255)
        {
            in_mon_msg_req_lock_cnt++;
        }
    }else{
        if (in_mon_msg_req_lock_cnt > 0)
        {
            if ((in_mon_msg_req_lock_cnt == 1) && (in_mon_msg_req_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.mon.msg_req.msg);
                mj_handle.in.mon.msg_req.msg = (msg_request_msg_t*)(in_mon_msg_req_delayed_ptr);
                mj_handle.in.mon.msg_req.ts_s = mon_msg_req_delayed_ts_s;
                mj_handle.in.mon.msg_req.ts_ns = mon_msg_req_delayed_ts_ns;
                mon_msg_req_rx_tick = ticks;
                mj_handle.in.mon.msg_req.state = MJ_MSG_ACTUAL;
                in_mon_msg_req_updated = 1;
                p_drv->udp4.free(old_buff);
                in_mon_msg_req_delayed_ptr = NULL;
            }
            in_mon_msg_req_lock_cnt--;
        }
    }
    return in_mon_msg_req_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_mon_msg_req_copy_fcn(void *dst)
{
    in_mon_msg_req_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.mon.msg_req.msg), sizeof(msg_request_msg_t));
    in_mon_msg_req_lock_fcn(MJ_MSG_UNLOCK);
}

static uint32_t mon_prm_req_rx_tick = UINT32_MAX - 1.0;
static uint8_t  in_mon_prm_req_lock_cnt = 0;
static parameter_request_msg_t* in_mon_prm_req_delayed_ptr = NULL;
static uint32_t mon_prm_req_delayed_ts_s = 0;
static uint32_t mon_prm_req_delayed_ts_ns = 0;
static uint8_t  in_mon_prm_req_updated = 0;
static uint32_t  in_mon_prm_req_total = 0;
static uint32_t  in_mon_prm_req_miss = 0;
static uint16_t  in_mon_prm_req_last_cnt = 0;
static mj_msg_state_t in_mon_prm_req_lock_fcn(mj_msg_state_t state)
{
    if (state == MJ_MSG_LOCK)
    {
        if (in_mon_prm_req_lock_cnt < 255)
        {
            in_mon_prm_req_lock_cnt++;
        }
    }else{
        if (in_mon_prm_req_lock_cnt > 0)
        {
            if ((in_mon_prm_req_lock_cnt == 1) && (in_mon_prm_req_delayed_ptr))
            {
                uint8_t* old_buff = (uint8_t*)(mj_handle.in.mon.prm_req.msg);
                mj_handle.in.mon.prm_req.msg = (parameter_request_msg_t*)(in_mon_prm_req_delayed_ptr);
                mj_handle.in.mon.prm_req.ts_s = mon_prm_req_delayed_ts_s;
                mj_handle.in.mon.prm_req.ts_ns = mon_prm_req_delayed_ts_ns;
                mon_prm_req_rx_tick = ticks;
                mj_handle.in.mon.prm_req.state = MJ_MSG_ACTUAL;
                in_mon_prm_req_updated = 1;
                p_drv->udp4.free(old_buff);
                in_mon_prm_req_delayed_ptr = NULL;
            }
            in_mon_prm_req_lock_cnt--;
        }
    }
    return in_mon_prm_req_lock_cnt > 0 ? MJ_MSG_LOCK : MJ_MSG_UNLOCK;
}

static void in_mon_prm_req_copy_fcn(void *dst)
{
    in_mon_prm_req_lock_fcn(MJ_MSG_LOCK);
    memcpy(dst, (void *)(mj_handle.in.mon.prm_req.msg), sizeof(parameter_request_msg_t));
    in_mon_prm_req_lock_fcn(MJ_MSG_UNLOCK);
}


static void * out_bup_state_pkt = NULL;
static void out_bup_state_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.bup_state.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.bup_state.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.bup_state.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.bup_state.msg->hdr.dst = dst;
    mj_handle.out.bup_state.msg->hdr.cnt++;
    p_drv->udp4.tx(out_bup_state_pkt,NULL);
}

static void * out_cmd_ans_pkt = NULL;
static void out_cmd_ans_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.cmd_ans.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.cmd_ans.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.cmd_ans.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.cmd_ans.msg->hdr.dst = dst;
    mj_handle.out.cmd_ans.msg->hdr.cnt++;
    p_drv->udp4.tx(out_cmd_ans_pkt,NULL);
}

static void * out_dbg_pkt = NULL;
static dbg_data_msg_t * p_out_dbg_msg = NULL;
static mj_msg_state_t out_dbg_lock_fcn(mj_msg_state_t state)
{
    mj_msg_state_t res = MJ_MSG_UNDEFINED;
    if (state == MJ_MSG_LOCK)
    {
        if (p_out_dbg_msg == NULL)
        {
            if ((p_out_dbg_msg = (dbg_data_msg_t *)p_drv->udp4.alloc(sizeof(dbg_data_msg_t))))
            {
                memcpy((void *)p_out_dbg_msg, (void *)(mj_handle.out.dbg.msg), sizeof(dbg_data_msg_t));
                p_drv->udp4.set_payload(out_dbg_pkt, (uint8_t *)p_out_dbg_msg);
                res = MJ_MSG_LOCK;
            }else{
                res = MJ_MSG_UNLOCK;
            }
        }else{
            res = MJ_MSG_LOCK;
        }
    }else{
        res = MJ_MSG_LOCK;
        if (p_out_dbg_msg)
        {
            p_drv->udp4.set_payload(out_dbg_pkt, (uint8_t *)mj_handle.out.dbg.msg);
            p_drv->udp4.free((uint8_t *)p_out_dbg_msg);
            p_out_dbg_msg = NULL;
            res = MJ_MSG_UNLOCK;
        }else{
            res = MJ_MSG_UNLOCK;
        }
    }
    return res;
}

static void * out_dcu_tel_pkt = NULL;
static dcu_telemetry_msg_t * p_out_dcu_tel_msg = NULL;
static mj_msg_state_t out_dcu_tel_lock_fcn(mj_msg_state_t state)
{
    mj_msg_state_t res = MJ_MSG_UNDEFINED;
    if (state == MJ_MSG_LOCK)
    {
        if (p_out_dcu_tel_msg == NULL)
        {
            if ((p_out_dcu_tel_msg = (dcu_telemetry_msg_t *)p_drv->udp4.alloc(sizeof(dcu_telemetry_msg_t))))
            {
                memcpy((void *)p_out_dcu_tel_msg, (void *)(mj_handle.out.dcu_tel.msg), sizeof(dcu_telemetry_msg_t));
                p_drv->udp4.set_payload(out_dcu_tel_pkt, (uint8_t *)p_out_dcu_tel_msg);
                res = MJ_MSG_LOCK;
            }else{
                res = MJ_MSG_UNLOCK;
            }
        }else{
            res = MJ_MSG_LOCK;
        }
    }else{
        res = MJ_MSG_LOCK;
        if (p_out_dcu_tel_msg)
        {
            p_drv->udp4.set_payload(out_dcu_tel_pkt, (uint8_t *)mj_handle.out.dcu_tel.msg);
            p_drv->udp4.free((uint8_t *)p_out_dcu_tel_msg);
            p_out_dcu_tel_msg = NULL;
            res = MJ_MSG_UNLOCK;
        }else{
            res = MJ_MSG_UNLOCK;
        }
    }
    return res;
}

static void * out_drive_master_ctrl_pkt = NULL;
static drive_master_ctrl_msg_t * p_out_drive_master_ctrl_msg = NULL;
static mj_msg_state_t out_drive_master_ctrl_lock_fcn(mj_msg_state_t state)
{
    mj_msg_state_t res = MJ_MSG_UNDEFINED;
    if (state == MJ_MSG_LOCK)
    {
        if (p_out_drive_master_ctrl_msg == NULL)
        {
            if ((p_out_drive_master_ctrl_msg = (drive_master_ctrl_msg_t *)p_drv->udp4.alloc(sizeof(drive_master_ctrl_msg_t))))
            {
                memcpy((void *)p_out_drive_master_ctrl_msg, (void *)(mj_handle.out.drive_master_ctrl.msg), sizeof(drive_master_ctrl_msg_t));
                p_drv->udp4.set_payload(out_drive_master_ctrl_pkt, (uint8_t *)p_out_drive_master_ctrl_msg);
                res = MJ_MSG_LOCK;
            }else{
                res = MJ_MSG_UNLOCK;
            }
        }else{
            res = MJ_MSG_LOCK;
        }
    }else{
        res = MJ_MSG_LOCK;
        if (p_out_drive_master_ctrl_msg)
        {
            p_drv->udp4.set_payload(out_drive_master_ctrl_pkt, (uint8_t *)mj_handle.out.drive_master_ctrl.msg);
            p_drv->udp4.free((uint8_t *)p_out_drive_master_ctrl_msg);
            p_out_drive_master_ctrl_msg = NULL;
            res = MJ_MSG_UNLOCK;
        }else{
            res = MJ_MSG_UNLOCK;
        }
    }
    return res;
}

static void * out_drive_slave_fb_pkt = NULL;
static drive_slave_fb_msg_t * p_out_drive_slave_fb_msg = NULL;
static mj_msg_state_t out_drive_slave_fb_lock_fcn(mj_msg_state_t state)
{
    mj_msg_state_t res = MJ_MSG_UNDEFINED;
    if (state == MJ_MSG_LOCK)
    {
        if (p_out_drive_slave_fb_msg == NULL)
        {
            if ((p_out_drive_slave_fb_msg = (drive_slave_fb_msg_t *)p_drv->udp4.alloc(sizeof(drive_slave_fb_msg_t))))
            {
                memcpy((void *)p_out_drive_slave_fb_msg, (void *)(mj_handle.out.drive_slave_fb.msg), sizeof(drive_slave_fb_msg_t));
                p_drv->udp4.set_payload(out_drive_slave_fb_pkt, (uint8_t *)p_out_drive_slave_fb_msg);
                res = MJ_MSG_LOCK;
            }else{
                res = MJ_MSG_UNLOCK;
            }
        }else{
            res = MJ_MSG_LOCK;
        }
    }else{
        res = MJ_MSG_LOCK;
        if (p_out_drive_slave_fb_msg)
        {
            p_drv->udp4.set_payload(out_drive_slave_fb_pkt, (uint8_t *)mj_handle.out.drive_slave_fb.msg);
            p_drv->udp4.free((uint8_t *)p_out_drive_slave_fb_msg);
            p_out_drive_slave_fb_msg = NULL;
            res = MJ_MSG_UNLOCK;
        }else{
            res = MJ_MSG_UNLOCK;
        }
    }
    return res;
}

static void * out_formular_pkt = NULL;
static void out_formular_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.formular.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.formular.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.formular.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.formular.msg->hdr.dst = dst;
    mj_handle.out.formular.msg->hdr.cnt++;
    p_drv->udp4.tx(out_formular_pkt,NULL);
}

static void * out_msg_ans_pkt = NULL;
static void out_msg_ans_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.msg_ans.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.msg_ans.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.msg_ans.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.msg_ans.msg->hdr.dst = dst;
    mj_handle.out.msg_ans.msg->hdr.cnt++;
    p_drv->udp4.tx(out_msg_ans_pkt,NULL);
}

static void * out_prm_ans_pkt = NULL;
static void out_prm_ans_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.prm_ans.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.prm_ans.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.prm_ans.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.prm_ans.msg->hdr.dst = dst;
    mj_handle.out.prm_ans.msg->hdr.cnt++;
    p_drv->udp4.tx(out_prm_ans_pkt,NULL);
}

static void * out_ptp_state_pkt = NULL;
static ptp_info_msg_t * p_out_ptp_state_msg = NULL;
static mj_msg_state_t out_ptp_state_lock_fcn(mj_msg_state_t state)
{
    mj_msg_state_t res = MJ_MSG_UNDEFINED;
    if (state == MJ_MSG_LOCK)
    {
        if (p_out_ptp_state_msg == NULL)
        {
            if ((p_out_ptp_state_msg = (ptp_info_msg_t *)p_drv->udp4.alloc(sizeof(ptp_info_msg_t))))
            {
                memcpy((void *)p_out_ptp_state_msg, (void *)(mj_handle.out.ptp_state.msg), sizeof(ptp_info_msg_t));
                p_drv->udp4.set_payload(out_ptp_state_pkt, (uint8_t *)p_out_ptp_state_msg);
                res = MJ_MSG_LOCK;
            }else{
                res = MJ_MSG_UNLOCK;
            }
        }else{
            res = MJ_MSG_LOCK;
        }
    }else{
        res = MJ_MSG_LOCK;
        if (p_out_ptp_state_msg)
        {
            p_drv->udp4.set_payload(out_ptp_state_pkt, (uint8_t *)mj_handle.out.ptp_state.msg);
            p_drv->udp4.free((uint8_t *)p_out_ptp_state_msg);
            p_out_ptp_state_msg = NULL;
            res = MJ_MSG_UNLOCK;
        }else{
            res = MJ_MSG_UNLOCK;
        }
    }
    return res;
}


static bup_dcu_lfd_prm_t _bup_dcu_lfd_prm;

mj_prm_status_t bup_dcu_lfd_prm_write(int id, void *data)
{
    switch (id){
        case PRM_BOOL_SERVICE_MODE:
            memcpy(&(_bup_dcu_lfd_prm.service_mode),data,sizeof(_bup_dcu_lfd_prm.service_mode));
            return MJ_PRM_OK;
        case PRM_BOOL_DBG_MODE:
            memcpy(&(_bup_dcu_lfd_prm.dbg_mode),data,sizeof(_bup_dcu_lfd_prm.dbg_mode));
            return MJ_PRM_OK;
        case PRM_BOOL_PTP_STAT:
            memcpy(&(_bup_dcu_lfd_prm.ptp_stat),data,sizeof(_bup_dcu_lfd_prm.ptp_stat));
            return MJ_PRM_OK;
        case PRM_FLOAT_VDC_SCALE:
            memcpy(&(_bup_dcu_lfd_prm.vdc_scale),data,sizeof(_bup_dcu_lfd_prm.vdc_scale));
            return MJ_PRM_OK;
        case PRM_FLOAT_OCP_LVL:
            memcpy(&(_bup_dcu_lfd_prm.ocp_lvl),data,sizeof(_bup_dcu_lfd_prm.ocp_lvl));
            return MJ_PRM_OK;
        case PRM_FLOAT_CUR_LIM:
            memcpy(&(_bup_dcu_lfd_prm.cur_lim),data,sizeof(_bup_dcu_lfd_prm.cur_lim));
            return MJ_PRM_OK;
        case PRM_BOOL_DRV_ANG_REVERSE:
            memcpy(&(_bup_dcu_lfd_prm.drv_ang_reverse),data,sizeof(_bup_dcu_lfd_prm.drv_ang_reverse));
            return MJ_PRM_OK;
        case PRM_BOOL_DRV_CURRENT_REVERSE:
            memcpy(&(_bup_dcu_lfd_prm.drv_current_reverse),data,sizeof(_bup_dcu_lfd_prm.drv_current_reverse));
            return MJ_PRM_OK;
        case PRM_BOOL_DRV_VOLTAGE_REVERSE:
            memcpy(&(_bup_dcu_lfd_prm.drv_voltage_reverse),data,sizeof(_bup_dcu_lfd_prm.drv_voltage_reverse));
            return MJ_PRM_OK;
        case PRM_FLOAT_DRV_ZERO:
            memcpy(&(_bup_dcu_lfd_prm.drv_zero),data,sizeof(_bup_dcu_lfd_prm.drv_zero));
            return MJ_PRM_OK;
        case PRM_FLOAT_VDC_MIN:
            memcpy(&(_bup_dcu_lfd_prm.vdc_min),data,sizeof(_bup_dcu_lfd_prm.vdc_min));
            return MJ_PRM_OK;
        case PRM_BOOL_IM_MODE:
            memcpy(&(_bup_dcu_lfd_prm.im_mode),data,sizeof(_bup_dcu_lfd_prm.im_mode));
            return MJ_PRM_OK;
        case PRM_FLOAT_PTP_KP:
            memcpy(&(_bup_dcu_lfd_prm.ptp_kp),data,sizeof(_bup_dcu_lfd_prm.ptp_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_PTP_KI:
            memcpy(&(_bup_dcu_lfd_prm.ptp_ki),data,sizeof(_bup_dcu_lfd_prm.ptp_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_PTP_KD:
            memcpy(&(_bup_dcu_lfd_prm.ptp_kd),data,sizeof(_bup_dcu_lfd_prm.ptp_kd));
            return MJ_PRM_OK;
        case PRM_FLOAT_OHP_LVL:
            memcpy(&(_bup_dcu_lfd_prm.ohp_lvl),data,sizeof(_bup_dcu_lfd_prm.ohp_lvl));
            return MJ_PRM_OK;
        case PRM_FLOAT_OHP_HYST:
            memcpy(&(_bup_dcu_lfd_prm.ohp_hyst),data,sizeof(_bup_dcu_lfd_prm.ohp_hyst));
            return MJ_PRM_OK;
        case PRM_FLOAT_EL_ZERO:
            memcpy(&(_bup_dcu_lfd_prm.el_zero),data,sizeof(_bup_dcu_lfd_prm.el_zero));
            return MJ_PRM_OK;
        case PRM_INT_POLE_PAIRS:
            memcpy(&(_bup_dcu_lfd_prm.pole_pairs),data,sizeof(_bup_dcu_lfd_prm.pole_pairs));
            return MJ_PRM_OK;
        case PRM_FLOAT_PH_RESISTANCE:
            memcpy(&(_bup_dcu_lfd_prm.ph_resistance),data,sizeof(_bup_dcu_lfd_prm.ph_resistance));
            return MJ_PRM_OK;
        case PRM_FLOAT_PH_INDUCTANCE:
            memcpy(&(_bup_dcu_lfd_prm.ph_inductance),data,sizeof(_bup_dcu_lfd_prm.ph_inductance));
            return MJ_PRM_OK;
        case PRM_FLOAT_BRAKE_UNLOCK_VOLTAGE:
            memcpy(&(_bup_dcu_lfd_prm.brake_unlock_voltage),data,sizeof(_bup_dcu_lfd_prm.brake_unlock_voltage));
            return MJ_PRM_OK;
        case PRM_INT_BRAKE_UNLOCK_TIME:
            memcpy(&(_bup_dcu_lfd_prm.brake_unlock_time),data,sizeof(_bup_dcu_lfd_prm.brake_unlock_time));
            return MJ_PRM_OK;
        case PRM_FLOAT_BRAKE_HOLD_VOLTAGE:
            memcpy(&(_bup_dcu_lfd_prm.brake_hold_voltage),data,sizeof(_bup_dcu_lfd_prm.brake_hold_voltage));
            return MJ_PRM_OK;
        case PRM_INT_BRAKE_LOCK_TIME:
            memcpy(&(_bup_dcu_lfd_prm.brake_lock_time),data,sizeof(_bup_dcu_lfd_prm.brake_lock_time));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KP:
            memcpy(&(_bup_dcu_lfd_prm.curr_kp),data,sizeof(_bup_dcu_lfd_prm.curr_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KI:
            memcpy(&(_bup_dcu_lfd_prm.curr_ki),data,sizeof(_bup_dcu_lfd_prm.curr_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KB:
            memcpy(&(_bup_dcu_lfd_prm.curr_kb),data,sizeof(_bup_dcu_lfd_prm.curr_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KT:
            memcpy(&(_bup_dcu_lfd_prm.curr_kt),data,sizeof(_bup_dcu_lfd_prm.curr_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KF:
            memcpy(&(_bup_dcu_lfd_prm.curr_kf),data,sizeof(_bup_dcu_lfd_prm.curr_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_FC:
            memcpy(&(_bup_dcu_lfd_prm.curr_fc),data,sizeof(_bup_dcu_lfd_prm.curr_fc));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_ERR_LIM:
            memcpy(&(_bup_dcu_lfd_prm.curr_err_lim),data,sizeof(_bup_dcu_lfd_prm.curr_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_OUT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.curr_out_lim),data,sizeof(_bup_dcu_lfd_prm.curr_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_OUT_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.curr_out_rate_lim),data,sizeof(_bup_dcu_lfd_prm.curr_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_ERR_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.curr_err_rate_lim),data,sizeof(_bup_dcu_lfd_prm.curr_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KP:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_kp),data,sizeof(_bup_dcu_lfd_prm.load_speed_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KI:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_ki),data,sizeof(_bup_dcu_lfd_prm.load_speed_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KB:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_kb),data,sizeof(_bup_dcu_lfd_prm.load_speed_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KT:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_kt),data,sizeof(_bup_dcu_lfd_prm.load_speed_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KF:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_kf),data,sizeof(_bup_dcu_lfd_prm.load_speed_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_ERR_LIM:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_err_lim),data,sizeof(_bup_dcu_lfd_prm.load_speed_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_OUT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_out_lim),data,sizeof(_bup_dcu_lfd_prm.load_speed_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_INT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_int_lim),data,sizeof(_bup_dcu_lfd_prm.load_speed_int_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_OUT_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_out_rate_lim),data,sizeof(_bup_dcu_lfd_prm.load_speed_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_ERR_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_err_rate_lim),data,sizeof(_bup_dcu_lfd_prm.load_speed_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_FLT_FC:
            memcpy(&(_bup_dcu_lfd_prm.load_speed_flt_fc),data,sizeof(_bup_dcu_lfd_prm.load_speed_flt_fc));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_FLT_FC:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_flt_fc),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_flt_fc));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KP:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_kp),data,sizeof(_bup_dcu_lfd_prm.load_ang_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KI:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_ki),data,sizeof(_bup_dcu_lfd_prm.load_ang_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KB:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_kb),data,sizeof(_bup_dcu_lfd_prm.load_ang_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KT:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_kt),data,sizeof(_bup_dcu_lfd_prm.load_ang_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KF:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_kf),data,sizeof(_bup_dcu_lfd_prm.load_ang_kf));
            return MJ_PRM_OK;
        case PRM_BOOL_LOAD_ANG_REV:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_rev),data,sizeof(_bup_dcu_lfd_prm.load_ang_rev));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KD:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_kd),data,sizeof(_bup_dcu_lfd_prm.load_ang_kd));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_ERR_LIM:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_err_lim),data,sizeof(_bup_dcu_lfd_prm.load_ang_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_OUT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_out_lim),data,sizeof(_bup_dcu_lfd_prm.load_ang_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_OUT_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_out_rate_lim),data,sizeof(_bup_dcu_lfd_prm.load_ang_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_ERR_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_err_rate_lim),data,sizeof(_bup_dcu_lfd_prm.load_ang_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_DZ:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_dz),data,sizeof(_bup_dcu_lfd_prm.load_ang_dz));
            return MJ_PRM_OK;
        case PRM_BOOL_LOAD_ANG_DZ_EN:
            memcpy(&(_bup_dcu_lfd_prm.load_ang_dz_en),data,sizeof(_bup_dcu_lfd_prm.load_ang_dz_en));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KP:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_kp),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KI:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_ki),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KB:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_kb),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KT:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_kt),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KF:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_kf),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_ERR_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_err_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_OUT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_out_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_INT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_int_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_int_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_OUT_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_out_rate_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_ERR_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_err_rate_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KP:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_kp),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KI:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_ki),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KB:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_kb),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KT:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_kt),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KF:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_kf),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_ERR_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_err_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_OUT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_out_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_INT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_int_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_int_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_OUT_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_out_rate_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_ERR_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_common_err_rate_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KP:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_kp),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KI:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_ki),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KB:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_kb),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KT:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_kt),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KF:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_kf),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_ERR_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_err_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_OUT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_out_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_INT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_int_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_int_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_OUT_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_out_rate_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_ERR_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_master_diff_err_rate_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_INT_ROTOR_SPEED_ROLE:
            memcpy(&(_bup_dcu_lfd_prm.rotor_speed_role),data,sizeof(_bup_dcu_lfd_prm.rotor_speed_role));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KP:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_kp),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KI:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_ki),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KB:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_kb),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KT:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_kt),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KF:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_kf),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_ERR_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_err_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_OUT_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_out_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_OUT_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_out_rate_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_ERR_RATE_LIM:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_err_rate_lim),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_DZ:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_dz),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_dz));
            return MJ_PRM_OK;
        case PRM_BOOL_ROTOR_ANG_DZ_EN:
            memcpy(&(_bup_dcu_lfd_prm.rotor_ang_dz_en),data,sizeof(_bup_dcu_lfd_prm.rotor_ang_dz_en));
            return MJ_PRM_OK;
        case PRM_STRING_FACTORY_DATE:
            memcpy(&(_bup_dcu_lfd_prm.factory_date),data,sizeof(_bup_dcu_lfd_prm.factory_date));
            return MJ_PRM_OK;
        case PRM_STRING_FACTORY_NUMBER:
            memcpy(&(_bup_dcu_lfd_prm.factory_number),data,sizeof(_bup_dcu_lfd_prm.factory_number));
            return MJ_PRM_OK;
        case PRM_STRING_DESCRIPTION:
            memcpy(&(_bup_dcu_lfd_prm.description),data,sizeof(_bup_dcu_lfd_prm.description));
            return MJ_PRM_OK;
        case PRM_INT_DEV_ID:
            memcpy(&(_bup_dcu_lfd_prm.dev_id),data,sizeof(_bup_dcu_lfd_prm.dev_id));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_REQ:
            memcpy(&(_bup_dcu_lfd_prm.com_if_srv_mcast_req),data,sizeof(_bup_dcu_lfd_prm.com_if_srv_mcast_req));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_ANS:
            memcpy(&(_bup_dcu_lfd_prm.com_if_srv_mcast_ans),data,sizeof(_bup_dcu_lfd_prm.com_if_srv_mcast_ans));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST:
            memcpy(&(_bup_dcu_lfd_prm.com_if_bro_bup_ctrl_mcast),data,sizeof(_bup_dcu_lfd_prm.com_if_bro_bup_ctrl_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST:
            memcpy(&(_bup_dcu_lfd_prm.com_if_bro_bup_data_mcast),data,sizeof(_bup_dcu_lfd_prm.com_if_bro_bup_data_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BUP_INTERNAL_MCAST:
            memcpy(&(_bup_dcu_lfd_prm.com_if_bup_internal_mcast),data,sizeof(_bup_dcu_lfd_prm.com_if_bup_internal_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_SRV_MCAST:
            memcpy(&(_bup_dcu_lfd_prm.com_if_bro_bup_srv_mcast),data,sizeof(_bup_dcu_lfd_prm.com_if_bro_bup_srv_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST:
            memcpy(&(_bup_dcu_lfd_prm.com_if_im_bro_drive_mcast),data,sizeof(_bup_dcu_lfd_prm.com_if_im_bro_drive_mcast));
            return MJ_PRM_OK;
        default:
            return MJ_PRM_UNKNOW;
    }
}

mj_prm_status_t bup_dcu_lfd_prm_read(int id, void *data)
{
    switch (id){
        case PRM_BOOL_SERVICE_MODE:
            memcpy(data,&_bup_dcu_lfd_prm.service_mode,sizeof(_bup_dcu_lfd_prm.service_mode));
            return MJ_PRM_OK;
        case PRM_BOOL_DBG_MODE:
            memcpy(data,&_bup_dcu_lfd_prm.dbg_mode,sizeof(_bup_dcu_lfd_prm.dbg_mode));
            return MJ_PRM_OK;
        case PRM_BOOL_PTP_STAT:
            memcpy(data,&_bup_dcu_lfd_prm.ptp_stat,sizeof(_bup_dcu_lfd_prm.ptp_stat));
            return MJ_PRM_OK;
        case PRM_FLOAT_VDC_SCALE:
            memcpy(data,&_bup_dcu_lfd_prm.vdc_scale,sizeof(_bup_dcu_lfd_prm.vdc_scale));
            return MJ_PRM_OK;
        case PRM_FLOAT_OCP_LVL:
            memcpy(data,&_bup_dcu_lfd_prm.ocp_lvl,sizeof(_bup_dcu_lfd_prm.ocp_lvl));
            return MJ_PRM_OK;
        case PRM_FLOAT_CUR_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.cur_lim,sizeof(_bup_dcu_lfd_prm.cur_lim));
            return MJ_PRM_OK;
        case PRM_BOOL_DRV_ANG_REVERSE:
            memcpy(data,&_bup_dcu_lfd_prm.drv_ang_reverse,sizeof(_bup_dcu_lfd_prm.drv_ang_reverse));
            return MJ_PRM_OK;
        case PRM_BOOL_DRV_CURRENT_REVERSE:
            memcpy(data,&_bup_dcu_lfd_prm.drv_current_reverse,sizeof(_bup_dcu_lfd_prm.drv_current_reverse));
            return MJ_PRM_OK;
        case PRM_BOOL_DRV_VOLTAGE_REVERSE:
            memcpy(data,&_bup_dcu_lfd_prm.drv_voltage_reverse,sizeof(_bup_dcu_lfd_prm.drv_voltage_reverse));
            return MJ_PRM_OK;
        case PRM_FLOAT_DRV_ZERO:
            memcpy(data,&_bup_dcu_lfd_prm.drv_zero,sizeof(_bup_dcu_lfd_prm.drv_zero));
            return MJ_PRM_OK;
        case PRM_FLOAT_VDC_MIN:
            memcpy(data,&_bup_dcu_lfd_prm.vdc_min,sizeof(_bup_dcu_lfd_prm.vdc_min));
            return MJ_PRM_OK;
        case PRM_BOOL_IM_MODE:
            memcpy(data,&_bup_dcu_lfd_prm.im_mode,sizeof(_bup_dcu_lfd_prm.im_mode));
            return MJ_PRM_OK;
        case PRM_FLOAT_PTP_KP:
            memcpy(data,&_bup_dcu_lfd_prm.ptp_kp,sizeof(_bup_dcu_lfd_prm.ptp_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_PTP_KI:
            memcpy(data,&_bup_dcu_lfd_prm.ptp_ki,sizeof(_bup_dcu_lfd_prm.ptp_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_PTP_KD:
            memcpy(data,&_bup_dcu_lfd_prm.ptp_kd,sizeof(_bup_dcu_lfd_prm.ptp_kd));
            return MJ_PRM_OK;
        case PRM_FLOAT_OHP_LVL:
            memcpy(data,&_bup_dcu_lfd_prm.ohp_lvl,sizeof(_bup_dcu_lfd_prm.ohp_lvl));
            return MJ_PRM_OK;
        case PRM_FLOAT_OHP_HYST:
            memcpy(data,&_bup_dcu_lfd_prm.ohp_hyst,sizeof(_bup_dcu_lfd_prm.ohp_hyst));
            return MJ_PRM_OK;
        case PRM_FLOAT_EL_ZERO:
            memcpy(data,&_bup_dcu_lfd_prm.el_zero,sizeof(_bup_dcu_lfd_prm.el_zero));
            return MJ_PRM_OK;
        case PRM_INT_POLE_PAIRS:
            memcpy(data,&_bup_dcu_lfd_prm.pole_pairs,sizeof(_bup_dcu_lfd_prm.pole_pairs));
            return MJ_PRM_OK;
        case PRM_FLOAT_PH_RESISTANCE:
            memcpy(data,&_bup_dcu_lfd_prm.ph_resistance,sizeof(_bup_dcu_lfd_prm.ph_resistance));
            return MJ_PRM_OK;
        case PRM_FLOAT_PH_INDUCTANCE:
            memcpy(data,&_bup_dcu_lfd_prm.ph_inductance,sizeof(_bup_dcu_lfd_prm.ph_inductance));
            return MJ_PRM_OK;
        case PRM_FLOAT_BRAKE_UNLOCK_VOLTAGE:
            memcpy(data,&_bup_dcu_lfd_prm.brake_unlock_voltage,sizeof(_bup_dcu_lfd_prm.brake_unlock_voltage));
            return MJ_PRM_OK;
        case PRM_INT_BRAKE_UNLOCK_TIME:
            memcpy(data,&_bup_dcu_lfd_prm.brake_unlock_time,sizeof(_bup_dcu_lfd_prm.brake_unlock_time));
            return MJ_PRM_OK;
        case PRM_FLOAT_BRAKE_HOLD_VOLTAGE:
            memcpy(data,&_bup_dcu_lfd_prm.brake_hold_voltage,sizeof(_bup_dcu_lfd_prm.brake_hold_voltage));
            return MJ_PRM_OK;
        case PRM_INT_BRAKE_LOCK_TIME:
            memcpy(data,&_bup_dcu_lfd_prm.brake_lock_time,sizeof(_bup_dcu_lfd_prm.brake_lock_time));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KP:
            memcpy(data,&_bup_dcu_lfd_prm.curr_kp,sizeof(_bup_dcu_lfd_prm.curr_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KI:
            memcpy(data,&_bup_dcu_lfd_prm.curr_ki,sizeof(_bup_dcu_lfd_prm.curr_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KB:
            memcpy(data,&_bup_dcu_lfd_prm.curr_kb,sizeof(_bup_dcu_lfd_prm.curr_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KT:
            memcpy(data,&_bup_dcu_lfd_prm.curr_kt,sizeof(_bup_dcu_lfd_prm.curr_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_KF:
            memcpy(data,&_bup_dcu_lfd_prm.curr_kf,sizeof(_bup_dcu_lfd_prm.curr_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_FC:
            memcpy(data,&_bup_dcu_lfd_prm.curr_fc,sizeof(_bup_dcu_lfd_prm.curr_fc));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_ERR_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.curr_err_lim,sizeof(_bup_dcu_lfd_prm.curr_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_OUT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.curr_out_lim,sizeof(_bup_dcu_lfd_prm.curr_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_OUT_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.curr_out_rate_lim,sizeof(_bup_dcu_lfd_prm.curr_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_CURR_ERR_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.curr_err_rate_lim,sizeof(_bup_dcu_lfd_prm.curr_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KP:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_kp,sizeof(_bup_dcu_lfd_prm.load_speed_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KI:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_ki,sizeof(_bup_dcu_lfd_prm.load_speed_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KB:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_kb,sizeof(_bup_dcu_lfd_prm.load_speed_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KT:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_kt,sizeof(_bup_dcu_lfd_prm.load_speed_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_KF:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_kf,sizeof(_bup_dcu_lfd_prm.load_speed_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_ERR_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_err_lim,sizeof(_bup_dcu_lfd_prm.load_speed_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_OUT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_out_lim,sizeof(_bup_dcu_lfd_prm.load_speed_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_INT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_int_lim,sizeof(_bup_dcu_lfd_prm.load_speed_int_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_OUT_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_out_rate_lim,sizeof(_bup_dcu_lfd_prm.load_speed_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_ERR_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_err_rate_lim,sizeof(_bup_dcu_lfd_prm.load_speed_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_SPEED_FLT_FC:
            memcpy(data,&_bup_dcu_lfd_prm.load_speed_flt_fc,sizeof(_bup_dcu_lfd_prm.load_speed_flt_fc));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_FLT_FC:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_flt_fc,sizeof(_bup_dcu_lfd_prm.rotor_speed_flt_fc));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KP:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_kp,sizeof(_bup_dcu_lfd_prm.load_ang_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KI:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_ki,sizeof(_bup_dcu_lfd_prm.load_ang_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KB:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_kb,sizeof(_bup_dcu_lfd_prm.load_ang_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KT:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_kt,sizeof(_bup_dcu_lfd_prm.load_ang_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KF:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_kf,sizeof(_bup_dcu_lfd_prm.load_ang_kf));
            return MJ_PRM_OK;
        case PRM_BOOL_LOAD_ANG_REV:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_rev,sizeof(_bup_dcu_lfd_prm.load_ang_rev));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_KD:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_kd,sizeof(_bup_dcu_lfd_prm.load_ang_kd));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_ERR_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_err_lim,sizeof(_bup_dcu_lfd_prm.load_ang_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_OUT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_out_lim,sizeof(_bup_dcu_lfd_prm.load_ang_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_OUT_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_out_rate_lim,sizeof(_bup_dcu_lfd_prm.load_ang_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_ERR_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_err_rate_lim,sizeof(_bup_dcu_lfd_prm.load_ang_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_LOAD_ANG_DZ:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_dz,sizeof(_bup_dcu_lfd_prm.load_ang_dz));
            return MJ_PRM_OK;
        case PRM_BOOL_LOAD_ANG_DZ_EN:
            memcpy(data,&_bup_dcu_lfd_prm.load_ang_dz_en,sizeof(_bup_dcu_lfd_prm.load_ang_dz_en));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KP:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_kp,sizeof(_bup_dcu_lfd_prm.rotor_speed_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KI:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_ki,sizeof(_bup_dcu_lfd_prm.rotor_speed_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KB:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_kb,sizeof(_bup_dcu_lfd_prm.rotor_speed_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KT:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_kt,sizeof(_bup_dcu_lfd_prm.rotor_speed_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_KF:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_kf,sizeof(_bup_dcu_lfd_prm.rotor_speed_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_ERR_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_err_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_OUT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_out_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_INT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_int_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_int_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_OUT_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_out_rate_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_ERR_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_err_rate_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KP:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_kp,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KI:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_ki,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KB:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_kb,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KT:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_kt,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KF:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_kf,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_ERR_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_err_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_OUT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_out_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_INT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_int_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_int_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_OUT_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_out_rate_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_ERR_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_common_err_rate_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_common_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KP:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_kp,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KI:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_ki,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KB:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_kb,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KT:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_kt,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KF:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_kf,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_ERR_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_err_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_OUT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_out_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_INT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_int_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_int_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_OUT_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_out_rate_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_ERR_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_master_diff_err_rate_lim,sizeof(_bup_dcu_lfd_prm.rotor_speed_master_diff_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_INT_ROTOR_SPEED_ROLE:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_speed_role,sizeof(_bup_dcu_lfd_prm.rotor_speed_role));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KP:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_kp,sizeof(_bup_dcu_lfd_prm.rotor_ang_kp));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KI:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_ki,sizeof(_bup_dcu_lfd_prm.rotor_ang_ki));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KB:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_kb,sizeof(_bup_dcu_lfd_prm.rotor_ang_kb));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KT:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_kt,sizeof(_bup_dcu_lfd_prm.rotor_ang_kt));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_KF:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_kf,sizeof(_bup_dcu_lfd_prm.rotor_ang_kf));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_ERR_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_err_lim,sizeof(_bup_dcu_lfd_prm.rotor_ang_err_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_OUT_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_out_lim,sizeof(_bup_dcu_lfd_prm.rotor_ang_out_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_OUT_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_out_rate_lim,sizeof(_bup_dcu_lfd_prm.rotor_ang_out_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_ERR_RATE_LIM:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_err_rate_lim,sizeof(_bup_dcu_lfd_prm.rotor_ang_err_rate_lim));
            return MJ_PRM_OK;
        case PRM_FLOAT_ROTOR_ANG_DZ:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_dz,sizeof(_bup_dcu_lfd_prm.rotor_ang_dz));
            return MJ_PRM_OK;
        case PRM_BOOL_ROTOR_ANG_DZ_EN:
            memcpy(data,&_bup_dcu_lfd_prm.rotor_ang_dz_en,sizeof(_bup_dcu_lfd_prm.rotor_ang_dz_en));
            return MJ_PRM_OK;
        case PRM_STRING_FACTORY_DATE:
            memcpy(data,&_bup_dcu_lfd_prm.factory_date,sizeof(_bup_dcu_lfd_prm.factory_date));
            return MJ_PRM_OK;
        case PRM_STRING_FACTORY_NUMBER:
            memcpy(data,&_bup_dcu_lfd_prm.factory_number,sizeof(_bup_dcu_lfd_prm.factory_number));
            return MJ_PRM_OK;
        case PRM_STRING_DESCRIPTION:
            memcpy(data,&_bup_dcu_lfd_prm.description,sizeof(_bup_dcu_lfd_prm.description));
            return MJ_PRM_OK;
        case PRM_INT_DEV_ID:
            memcpy(data,&_bup_dcu_lfd_prm.dev_id,sizeof(_bup_dcu_lfd_prm.dev_id));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_REQ:
            memcpy(data,&_bup_dcu_lfd_prm.com_if_srv_mcast_req,sizeof(_bup_dcu_lfd_prm.com_if_srv_mcast_req));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_ANS:
            memcpy(data,&_bup_dcu_lfd_prm.com_if_srv_mcast_ans,sizeof(_bup_dcu_lfd_prm.com_if_srv_mcast_ans));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST:
            memcpy(data,&_bup_dcu_lfd_prm.com_if_bro_bup_ctrl_mcast,sizeof(_bup_dcu_lfd_prm.com_if_bro_bup_ctrl_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST:
            memcpy(data,&_bup_dcu_lfd_prm.com_if_bro_bup_data_mcast,sizeof(_bup_dcu_lfd_prm.com_if_bro_bup_data_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BUP_INTERNAL_MCAST:
            memcpy(data,&_bup_dcu_lfd_prm.com_if_bup_internal_mcast,sizeof(_bup_dcu_lfd_prm.com_if_bup_internal_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_SRV_MCAST:
            memcpy(data,&_bup_dcu_lfd_prm.com_if_bro_bup_srv_mcast,sizeof(_bup_dcu_lfd_prm.com_if_bro_bup_srv_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST:
            memcpy(data,&_bup_dcu_lfd_prm.com_if_im_bro_drive_mcast,sizeof(_bup_dcu_lfd_prm.com_if_im_bro_drive_mcast));
            return MJ_PRM_OK;
        default:
            return MJ_PRM_UNKNOW;
    }
}

static const uint32_t _prm_ids[113] = {
    PRM_BOOL_SERVICE_MODE,
    PRM_BOOL_DBG_MODE,
    PRM_BOOL_PTP_STAT,
    PRM_FLOAT_VDC_SCALE,
    PRM_FLOAT_OCP_LVL,
    PRM_FLOAT_CUR_LIM,
    PRM_BOOL_DRV_ANG_REVERSE,
    PRM_BOOL_DRV_CURRENT_REVERSE,
    PRM_BOOL_DRV_VOLTAGE_REVERSE,
    PRM_FLOAT_DRV_ZERO,
    PRM_FLOAT_VDC_MIN,
    PRM_BOOL_IM_MODE,
    PRM_FLOAT_PTP_KP,
    PRM_FLOAT_PTP_KI,
    PRM_FLOAT_PTP_KD,
    PRM_FLOAT_OHP_LVL,
    PRM_FLOAT_OHP_HYST,
    PRM_FLOAT_EL_ZERO,
    PRM_INT_POLE_PAIRS,
    PRM_FLOAT_PH_RESISTANCE,
    PRM_FLOAT_PH_INDUCTANCE,
    PRM_FLOAT_BRAKE_UNLOCK_VOLTAGE,
    PRM_INT_BRAKE_UNLOCK_TIME,
    PRM_FLOAT_BRAKE_HOLD_VOLTAGE,
    PRM_INT_BRAKE_LOCK_TIME,
    PRM_FLOAT_CURR_KP,
    PRM_FLOAT_CURR_KI,
    PRM_FLOAT_CURR_KB,
    PRM_FLOAT_CURR_KT,
    PRM_FLOAT_CURR_KF,
    PRM_FLOAT_CURR_FC,
    PRM_FLOAT_CURR_ERR_LIM,
    PRM_FLOAT_CURR_OUT_LIM,
    PRM_FLOAT_CURR_OUT_RATE_LIM,
    PRM_FLOAT_CURR_ERR_RATE_LIM,
    PRM_FLOAT_LOAD_SPEED_KP,
    PRM_FLOAT_LOAD_SPEED_KI,
    PRM_FLOAT_LOAD_SPEED_KB,
    PRM_FLOAT_LOAD_SPEED_KT,
    PRM_FLOAT_LOAD_SPEED_KF,
    PRM_FLOAT_LOAD_SPEED_ERR_LIM,
    PRM_FLOAT_LOAD_SPEED_OUT_LIM,
    PRM_FLOAT_LOAD_SPEED_INT_LIM,
    PRM_FLOAT_LOAD_SPEED_OUT_RATE_LIM,
    PRM_FLOAT_LOAD_SPEED_ERR_RATE_LIM,
    PRM_FLOAT_LOAD_SPEED_FLT_FC,
    PRM_FLOAT_ROTOR_SPEED_FLT_FC,
    PRM_FLOAT_LOAD_ANG_KP,
    PRM_FLOAT_LOAD_ANG_KI,
    PRM_FLOAT_LOAD_ANG_KB,
    PRM_FLOAT_LOAD_ANG_KT,
    PRM_FLOAT_LOAD_ANG_KF,
    PRM_BOOL_LOAD_ANG_REV,
    PRM_FLOAT_LOAD_ANG_KD,
    PRM_FLOAT_LOAD_ANG_ERR_LIM,
    PRM_FLOAT_LOAD_ANG_OUT_LIM,
    PRM_FLOAT_LOAD_ANG_OUT_RATE_LIM,
    PRM_FLOAT_LOAD_ANG_ERR_RATE_LIM,
    PRM_FLOAT_LOAD_ANG_DZ,
    PRM_BOOL_LOAD_ANG_DZ_EN,
    PRM_FLOAT_ROTOR_SPEED_KP,
    PRM_FLOAT_ROTOR_SPEED_KI,
    PRM_FLOAT_ROTOR_SPEED_KB,
    PRM_FLOAT_ROTOR_SPEED_KT,
    PRM_FLOAT_ROTOR_SPEED_KF,
    PRM_FLOAT_ROTOR_SPEED_ERR_LIM,
    PRM_FLOAT_ROTOR_SPEED_OUT_LIM,
    PRM_FLOAT_ROTOR_SPEED_INT_LIM,
    PRM_FLOAT_ROTOR_SPEED_OUT_RATE_LIM,
    PRM_FLOAT_ROTOR_SPEED_ERR_RATE_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KP,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KI,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KB,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KT,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_KF,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_ERR_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_OUT_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_INT_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_OUT_RATE_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_COMMON_ERR_RATE_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KP,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KI,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KB,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KT,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_KF,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_ERR_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_OUT_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_INT_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_OUT_RATE_LIM,
    PRM_FLOAT_ROTOR_SPEED_MASTER_DIFF_ERR_RATE_LIM,
    PRM_INT_ROTOR_SPEED_ROLE,
    PRM_FLOAT_ROTOR_ANG_KP,
    PRM_FLOAT_ROTOR_ANG_KI,
    PRM_FLOAT_ROTOR_ANG_KB,
    PRM_FLOAT_ROTOR_ANG_KT,
    PRM_FLOAT_ROTOR_ANG_KF,
    PRM_FLOAT_ROTOR_ANG_ERR_LIM,
    PRM_FLOAT_ROTOR_ANG_OUT_LIM,
    PRM_FLOAT_ROTOR_ANG_OUT_RATE_LIM,
    PRM_FLOAT_ROTOR_ANG_ERR_RATE_LIM,
    PRM_FLOAT_ROTOR_ANG_DZ,
    PRM_BOOL_ROTOR_ANG_DZ_EN,
    PRM_STRING_FACTORY_DATE,
    PRM_STRING_FACTORY_NUMBER,
    PRM_STRING_DESCRIPTION,
    PRM_INT_DEV_ID,
    PRM_STRING_COM_IF_SRV_MCAST_REQ,
    PRM_STRING_COM_IF_SRV_MCAST_ANS,
    PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST,
    PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST,
    PRM_STRING_COM_IF_BUP_INTERNAL_MCAST,
    PRM_STRING_COM_IF_BRO_BUP_SRV_MCAST,
    PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST
};

static const uint32_t * bup_dcu_lfd_prm_list(uint32_t *size)
{
    *size = 113;
    return _prm_ids;
}

static uint32_t _250_us_cnt = 0;
static uint32_t _250_us_tick = 1;
static uint32_t _1000_us_cnt = 0;
static uint32_t _1000_us_tick = 4;
static uint32_t _500000_us_cnt = 0;
static uint32_t _500000_us_tick = 2000;

static uint32_t *_join_ip = NULL;
static volatile bool _send_join_done = true;
static uint32_t _join_send_tick = 0;

static void tick_fcn()
{
    uint32_t _temp_ns = 0;

    /* Each 0.25 ms  */
    if (_250_us_tick >= 1)
    {
        _250_us_cnt++;
        if (mj_handle.out.dcu_tel.tx_enable){
            mj_handle.out.dcu_tel.msg->hdr.cnt = _250_us_cnt;
            mj_handle.out.dcu_tel.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.dcu_tel.msg->hdr.ts_s,&_temp_ns);
            mj_handle.out.dcu_tel.msg->hdr.ts_ns = _temp_ns;
            p_drv->udp4.tx(out_dcu_tel_pkt,NULL);
        }
        _250_us_tick = 0;
    }
    _250_us_tick++;

    /* Each 1.0 ms  */
    if (_1000_us_tick >= 4)
    {
        _1000_us_cnt++;
        if (mj_handle.out.dbg.tx_enable){
            mj_handle.out.dbg.msg->hdr.cnt = _1000_us_cnt;
            mj_handle.out.dbg.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.dbg.msg->hdr.ts_s,&_temp_ns);
            mj_handle.out.dbg.msg->hdr.ts_ns = _temp_ns;
            p_drv->udp4.tx(out_dbg_pkt,NULL);
        }
        if (mj_handle.out.drive_master_ctrl.tx_enable){
            mj_handle.out.drive_master_ctrl.msg->hdr.cnt = _1000_us_cnt;
            mj_handle.out.drive_master_ctrl.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.drive_master_ctrl.msg->hdr.ts_s,&_temp_ns);
            mj_handle.out.drive_master_ctrl.msg->hdr.ts_ns = _temp_ns;
            p_drv->udp4.tx(out_drive_master_ctrl_pkt,NULL);
        }
        if (mj_handle.out.drive_slave_fb.tx_enable){
            mj_handle.out.drive_slave_fb.msg->hdr.cnt = _1000_us_cnt;
            mj_handle.out.drive_slave_fb.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.drive_slave_fb.msg->hdr.ts_s,&_temp_ns);
            mj_handle.out.drive_slave_fb.msg->hdr.ts_ns = _temp_ns;
            p_drv->udp4.tx(out_drive_slave_fb_pkt,NULL);
        }
        _1000_us_tick = 0;
    }
    _1000_us_tick++;

    /* Each 500.0 ms  */
    if (_500000_us_tick >= 2000)
    {
        _500000_us_cnt++;
        if (mj_handle.out.ptp_state.tx_enable){
            mj_handle.out.ptp_state.msg->hdr.cnt = _500000_us_cnt;
            mj_handle.out.ptp_state.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.ptp_state.msg->hdr.ts_s,&_temp_ns);
            mj_handle.out.ptp_state.msg->hdr.ts_ns = _temp_ns;
            p_drv->udp4.tx(out_ptp_state_pkt,NULL);
        }
        _500000_us_tick = 0;
    }
    _500000_us_tick++;

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
            // bup_ctrl
            case ID_BUP_CTRL:
                if (size == sizeof(bup_drv_control_msg_t))
                {
                    switch (hdr->src)
                    {
                        // bup_ctrl from aufd
                        case BRO30_AUFD:
                            if (in_aufd_bup_ctrl_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.aufd.bup_ctrl.msg;
                                mj_handle.in.aufd.bup_ctrl.msg = (bup_drv_control_msg_t *)data;
                                mj_handle.in.aufd.bup_ctrl.ts_s  = ts_s;
                                mj_handle.in.aufd.bup_ctrl.ts_ns = ts_ns;
                                in_aufd_bup_ctrl_updated = 1;
                                in_aufd_bup_ctrl_total++;
                                uint16_t cnt_diff = (mj_handle.in.aufd.bup_ctrl.msg->hdr.cnt - in_aufd_bup_ctrl_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_aufd_bup_ctrl_miss += cnt_diff;
                                }
                                in_aufd_bup_ctrl_last_cnt = mj_handle.in.aufd.bup_ctrl.msg->hdr.cnt;
                                aufd_bup_ctrl_rx_tick = ticks;
                                mj_handle.in.aufd.bup_ctrl.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_aufd_bup_ctrl_delayed_ptr == NULL)
                                {
                                    in_aufd_bup_ctrl_delayed_ptr = (bup_drv_control_msg_t *)data;
                                    aufd_bup_ctrl_delayed_ts_s = ts_s;
                                    aufd_bup_ctrl_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.aufd.bup_ctrl.irq){
                                mj_handle.in.aufd.bup_ctrl.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
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
                        // bup_multi_control from mon
                        case BRO30_MON:
                            if (in_mon_bup_multi_control_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.mon.bup_multi_control.msg;
                                mj_handle.in.mon.bup_multi_control.msg = (bup_drv_multi_control_msg_t *)data;
                                mj_handle.in.mon.bup_multi_control.ts_s  = ts_s;
                                mj_handle.in.mon.bup_multi_control.ts_ns = ts_ns;
                                in_mon_bup_multi_control_updated = 1;
                                in_mon_bup_multi_control_total++;
                                uint16_t cnt_diff = (mj_handle.in.mon.bup_multi_control.msg->hdr.cnt - in_mon_bup_multi_control_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_mon_bup_multi_control_miss += cnt_diff;
                                }
                                in_mon_bup_multi_control_last_cnt = mj_handle.in.mon.bup_multi_control.msg->hdr.cnt;
                                mon_bup_multi_control_rx_tick = ticks;
                                mj_handle.in.mon.bup_multi_control.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_mon_bup_multi_control_delayed_ptr == NULL)
                                {
                                    in_mon_bup_multi_control_delayed_ptr = (bup_drv_multi_control_msg_t *)data;
                                    mon_bup_multi_control_delayed_ts_s = ts_s;
                                    mon_bup_multi_control_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.mon.bup_multi_control.irq){
                                mj_handle.in.mon.bup_multi_control.irq(data);
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
            // bup_srv_ctrl
            case ID_BUP_SRV_CTRL:
                if (size == sizeof(bup_drv_control_msg_t))
                {
                    switch (hdr->src)
                    {
                        // bup_srv_ctrl from mon
                        case BRO30_MON:
                            if (in_mon_bup_srv_ctrl_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.mon.bup_srv_ctrl.msg;
                                mj_handle.in.mon.bup_srv_ctrl.msg = (bup_drv_control_msg_t *)data;
                                mj_handle.in.mon.bup_srv_ctrl.ts_s  = ts_s;
                                mj_handle.in.mon.bup_srv_ctrl.ts_ns = ts_ns;
                                in_mon_bup_srv_ctrl_updated = 1;
                                in_mon_bup_srv_ctrl_total++;
                                uint16_t cnt_diff = (mj_handle.in.mon.bup_srv_ctrl.msg->hdr.cnt - in_mon_bup_srv_ctrl_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_mon_bup_srv_ctrl_miss += cnt_diff;
                                }
                                in_mon_bup_srv_ctrl_last_cnt = mj_handle.in.mon.bup_srv_ctrl.msg->hdr.cnt;
                                mon_bup_srv_ctrl_rx_tick = ticks;
                                mj_handle.in.mon.bup_srv_ctrl.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_mon_bup_srv_ctrl_delayed_ptr == NULL)
                                {
                                    in_mon_bup_srv_ctrl_delayed_ptr = (bup_drv_control_msg_t *)data;
                                    mon_bup_srv_ctrl_delayed_ts_s = ts_s;
                                    mon_bup_srv_ctrl_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.mon.bup_srv_ctrl.irq){
                                mj_handle.in.mon.bup_srv_ctrl.irq(data);
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


static mj_msg_proc_res_t srv_mcast_req_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
            // cmd_req
            case ID_CMD_REQ:
                if (size == sizeof(command_request_msg_t))
                {
                    switch (hdr->src)
                    {
                        // cmd_req from aufd
                        case BRO30_AUFD:
                            if (in_aufd_cmd_req_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.aufd.cmd_req.msg;
                                mj_handle.in.aufd.cmd_req.msg = (command_request_msg_t *)data;
                                mj_handle.in.aufd.cmd_req.ts_s  = ts_s;
                                mj_handle.in.aufd.cmd_req.ts_ns = ts_ns;
                                in_aufd_cmd_req_updated = 1;
                                in_aufd_cmd_req_total++;
                                uint16_t cnt_diff = (mj_handle.in.aufd.cmd_req.msg->hdr.cnt - in_aufd_cmd_req_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_aufd_cmd_req_miss += cnt_diff;
                                }
                                in_aufd_cmd_req_last_cnt = mj_handle.in.aufd.cmd_req.msg->hdr.cnt;
                                aufd_cmd_req_rx_tick = ticks;
                                mj_handle.in.aufd.cmd_req.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_aufd_cmd_req_delayed_ptr == NULL)
                                {
                                    in_aufd_cmd_req_delayed_ptr = (command_request_msg_t *)data;
                                    aufd_cmd_req_delayed_ts_s = ts_s;
                                    aufd_cmd_req_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.aufd.cmd_req.irq){
                                mj_handle.in.aufd.cmd_req.irq(data);
                            }
                            return MJ_ACCEPT;
                        // cmd_req from mon
                        case BRO30_MON:
                            if (in_mon_cmd_req_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.mon.cmd_req.msg;
                                mj_handle.in.mon.cmd_req.msg = (command_request_msg_t *)data;
                                mj_handle.in.mon.cmd_req.ts_s  = ts_s;
                                mj_handle.in.mon.cmd_req.ts_ns = ts_ns;
                                in_mon_cmd_req_updated = 1;
                                in_mon_cmd_req_total++;
                                uint16_t cnt_diff = (mj_handle.in.mon.cmd_req.msg->hdr.cnt - in_mon_cmd_req_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_mon_cmd_req_miss += cnt_diff;
                                }
                                in_mon_cmd_req_last_cnt = mj_handle.in.mon.cmd_req.msg->hdr.cnt;
                                mon_cmd_req_rx_tick = ticks;
                                mj_handle.in.mon.cmd_req.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_mon_cmd_req_delayed_ptr == NULL)
                                {
                                    in_mon_cmd_req_delayed_ptr = (command_request_msg_t *)data;
                                    mon_cmd_req_delayed_ts_s = ts_s;
                                    mon_cmd_req_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.mon.cmd_req.irq){
                                mj_handle.in.mon.cmd_req.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            // msg_req
            case ID_MSG_REQ:
                if (size == sizeof(msg_request_msg_t))
                {
                    switch (hdr->src)
                    {
                        // msg_req from aufd
                        case BRO30_AUFD:
                            if (in_aufd_msg_req_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.aufd.msg_req.msg;
                                mj_handle.in.aufd.msg_req.msg = (msg_request_msg_t *)data;
                                mj_handle.in.aufd.msg_req.ts_s  = ts_s;
                                mj_handle.in.aufd.msg_req.ts_ns = ts_ns;
                                in_aufd_msg_req_updated = 1;
                                in_aufd_msg_req_total++;
                                uint16_t cnt_diff = (mj_handle.in.aufd.msg_req.msg->hdr.cnt - in_aufd_msg_req_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_aufd_msg_req_miss += cnt_diff;
                                }
                                in_aufd_msg_req_last_cnt = mj_handle.in.aufd.msg_req.msg->hdr.cnt;
                                aufd_msg_req_rx_tick = ticks;
                                mj_handle.in.aufd.msg_req.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_aufd_msg_req_delayed_ptr == NULL)
                                {
                                    in_aufd_msg_req_delayed_ptr = (msg_request_msg_t *)data;
                                    aufd_msg_req_delayed_ts_s = ts_s;
                                    aufd_msg_req_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.aufd.msg_req.irq){
                                mj_handle.in.aufd.msg_req.irq(data);
                            }
                            return MJ_ACCEPT;
                        // msg_req from mon
                        case BRO30_MON:
                            if (in_mon_msg_req_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.mon.msg_req.msg;
                                mj_handle.in.mon.msg_req.msg = (msg_request_msg_t *)data;
                                mj_handle.in.mon.msg_req.ts_s  = ts_s;
                                mj_handle.in.mon.msg_req.ts_ns = ts_ns;
                                in_mon_msg_req_updated = 1;
                                in_mon_msg_req_total++;
                                uint16_t cnt_diff = (mj_handle.in.mon.msg_req.msg->hdr.cnt - in_mon_msg_req_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_mon_msg_req_miss += cnt_diff;
                                }
                                in_mon_msg_req_last_cnt = mj_handle.in.mon.msg_req.msg->hdr.cnt;
                                mon_msg_req_rx_tick = ticks;
                                mj_handle.in.mon.msg_req.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_mon_msg_req_delayed_ptr == NULL)
                                {
                                    in_mon_msg_req_delayed_ptr = (msg_request_msg_t *)data;
                                    mon_msg_req_delayed_ts_s = ts_s;
                                    mon_msg_req_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.mon.msg_req.irq){
                                mj_handle.in.mon.msg_req.irq(data);
                            }
                            return MJ_ACCEPT;
                        default:
                            return MJ_REJECT_SRC;
                    }
                }else{
                    return MJ_REJECT_SIZE;
                }
            break;
            // prm_req
            case ID_PRM_REQ:
                if (size == sizeof(parameter_request_msg_t))
                {
                    switch (hdr->src)
                    {
                        // prm_req from aufd
                        case BRO30_AUFD:
                            if (in_aufd_prm_req_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.aufd.prm_req.msg;
                                mj_handle.in.aufd.prm_req.msg = (parameter_request_msg_t *)data;
                                mj_handle.in.aufd.prm_req.ts_s  = ts_s;
                                mj_handle.in.aufd.prm_req.ts_ns = ts_ns;
                                in_aufd_prm_req_updated = 1;
                                in_aufd_prm_req_total++;
                                uint16_t cnt_diff = (mj_handle.in.aufd.prm_req.msg->hdr.cnt - in_aufd_prm_req_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_aufd_prm_req_miss += cnt_diff;
                                }
                                in_aufd_prm_req_last_cnt = mj_handle.in.aufd.prm_req.msg->hdr.cnt;
                                aufd_prm_req_rx_tick = ticks;
                                mj_handle.in.aufd.prm_req.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_aufd_prm_req_delayed_ptr == NULL)
                                {
                                    in_aufd_prm_req_delayed_ptr = (parameter_request_msg_t *)data;
                                    aufd_prm_req_delayed_ts_s = ts_s;
                                    aufd_prm_req_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.aufd.prm_req.irq){
                                mj_handle.in.aufd.prm_req.irq(data);
                            }
                            return MJ_ACCEPT;
                        // prm_req from mon
                        case BRO30_MON:
                            if (in_mon_prm_req_lock_cnt == 0)
                            {
                                old_buff = (uint8_t*)mj_handle.in.mon.prm_req.msg;
                                mj_handle.in.mon.prm_req.msg = (parameter_request_msg_t *)data;
                                mj_handle.in.mon.prm_req.ts_s  = ts_s;
                                mj_handle.in.mon.prm_req.ts_ns = ts_ns;
                                in_mon_prm_req_updated = 1;
                                in_mon_prm_req_total++;
                                uint16_t cnt_diff = (mj_handle.in.mon.prm_req.msg->hdr.cnt - in_mon_prm_req_last_cnt);
                                if (cnt_diff > 1)
                                {
                                    in_mon_prm_req_miss += cnt_diff;
                                }
                                in_mon_prm_req_last_cnt = mj_handle.in.mon.prm_req.msg->hdr.cnt;
                                mon_prm_req_rx_tick = ticks;
                                mj_handle.in.mon.prm_req.state = MJ_MSG_ACTUAL;
                                p_drv->udp4.free(old_buff);
                            }else{
                                if (in_mon_prm_req_delayed_ptr == NULL)
                                {
                                    in_mon_prm_req_delayed_ptr = (parameter_request_msg_t *)data;
                                    mon_prm_req_delayed_ts_s = ts_s;
                                    mon_prm_req_delayed_ts_s = ts_ns;;
                                }else{
                                    return MJ_REJECT_OVF;
                                }
                            }
                            if (mj_handle.in.mon.prm_req.irq){
                                mj_handle.in.mon.prm_req.irq(data);
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

    if((((int32_t)(c_time - aufd_bup_ctrl_rx_tick)) > 240)){
        mj_handle.in.aufd.bup_ctrl.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - aufd_bup_multi_control_rx_tick)) > 240)){
        mj_handle.in.aufd.bup_multi_control.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - mon_bup_multi_control_rx_tick)) > 240)){
        mj_handle.in.mon.bup_multi_control.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - mon_bup_srv_ctrl_rx_tick)) > 240)){
        mj_handle.in.mon.bup_srv_ctrl.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - aufd_cmd_req_rx_tick)) > 4000)){
        mj_handle.in.aufd.cmd_req.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - mon_cmd_req_rx_tick)) > 4000)){
        mj_handle.in.mon.cmd_req.state = MJ_MSG_OBSOLETE;
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

    if((((int32_t)(c_time - im_bro_im_bro_drivers_sens_rx_tick)) > 3)){
        mj_handle.in.im_bro.im_bro_drivers_sens.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - aufd_msg_req_rx_tick)) > 4000)){
        mj_handle.in.aufd.msg_req.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - mon_msg_req_rx_tick)) > 4000)){
        mj_handle.in.mon.msg_req.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - aufd_prm_req_rx_tick)) > 4000)){
        mj_handle.in.aufd.prm_req.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - mon_prm_req_rx_tick)) > 4000)){
        mj_handle.in.mon.prm_req.state = MJ_MSG_OBSOLETE;
    }

    if(in_aufd_bup_ctrl_updated == 1)
    {
        if(mj_handle.in.aufd.bup_ctrl.upd_cb){mj_handle.in.aufd.bup_ctrl.upd_cb();}
        in_aufd_bup_ctrl_updated = 0;
    }
    if(in_aufd_bup_multi_control_updated == 1)
    {
        if(mj_handle.in.aufd.bup_multi_control.upd_cb){mj_handle.in.aufd.bup_multi_control.upd_cb();}
        in_aufd_bup_multi_control_updated = 0;
    }
    if(in_mon_bup_multi_control_updated == 1)
    {
        if(mj_handle.in.mon.bup_multi_control.upd_cb){mj_handle.in.mon.bup_multi_control.upd_cb();}
        in_mon_bup_multi_control_updated = 0;
    }
    if(in_mon_bup_srv_ctrl_updated == 1)
    {
        if(mj_handle.in.mon.bup_srv_ctrl.upd_cb){mj_handle.in.mon.bup_srv_ctrl.upd_cb();}
        in_mon_bup_srv_ctrl_updated = 0;
    }
    if(in_aufd_cmd_req_updated == 1)
    {
        if(mj_handle.in.aufd.cmd_req.upd_cb){mj_handle.in.aufd.cmd_req.upd_cb();}
        in_aufd_cmd_req_updated = 0;
    }
    if(in_mon_cmd_req_updated == 1)
    {
        if(mj_handle.in.mon.cmd_req.upd_cb){mj_handle.in.mon.cmd_req.upd_cb();}
        in_mon_cmd_req_updated = 0;
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
    if(in_im_bro_im_bro_drivers_sens_updated == 1)
    {
        if(mj_handle.in.im_bro.im_bro_drivers_sens.upd_cb){mj_handle.in.im_bro.im_bro_drivers_sens.upd_cb();}
        in_im_bro_im_bro_drivers_sens_updated = 0;
    }
    if(in_aufd_msg_req_updated == 1)
    {
        if(mj_handle.in.aufd.msg_req.upd_cb){mj_handle.in.aufd.msg_req.upd_cb();}
        in_aufd_msg_req_updated = 0;
    }
    if(in_mon_msg_req_updated == 1)
    {
        if(mj_handle.in.mon.msg_req.upd_cb){mj_handle.in.mon.msg_req.upd_cb();}
        in_mon_msg_req_updated = 0;
    }
    if(in_aufd_prm_req_updated == 1)
    {
        if(mj_handle.in.aufd.prm_req.upd_cb){mj_handle.in.aufd.prm_req.upd_cb();}
        in_aufd_prm_req_updated = 0;
        bro30_prm_id_k prmId = mj_handle.in.aufd.prm_req.msg->id;
        parameter_request_type_k rtype = mj_handle.in.aufd.prm_req.msg->type;
        bool is_prm_writed = false;
        if (rtype == PARAMETER_REQUEST_TYPE_WRITE){
            if (bup_dcu_lfd_prm_write(prmId, mj_handle.in.aufd.prm_req.msg->val) == MJ_PRM_OK){
                is_prm_writed = true;
            }
        }
        mj_handle.out.prm_ans.msg->id = prmId;
        if (bup_dcu_lfd_prm_read(prmId, mj_handle.out.prm_ans.msg->val) == MJ_PRM_OK){
            mj_handle.out.prm_ans.msg->ans = PARAMETER_STATUS_OK;
        } else {
            mj_handle.out.prm_ans.msg->ans = PARAMETER_STATUS_UNKNOWPRM;
        }
        if (is_prm_writed && mj_handle.prm.upd_cb){
            mj_handle.prm.upd_cb(prmId);
        }
        mj_handle.out.prm_ans.tx(mj_handle.in.aufd.prm_req.msg->hdr.src);
    }
    if(in_mon_prm_req_updated == 1)
    {
        if(mj_handle.in.mon.prm_req.upd_cb){mj_handle.in.mon.prm_req.upd_cb();}
        in_mon_prm_req_updated = 0;
        bro30_prm_id_k prmId = mj_handle.in.mon.prm_req.msg->id;
        parameter_request_type_k rtype = mj_handle.in.mon.prm_req.msg->type;
        bool is_prm_writed = false;
        if (rtype == PARAMETER_REQUEST_TYPE_WRITE){
            if (bup_dcu_lfd_prm_write(prmId, mj_handle.in.mon.prm_req.msg->val) == MJ_PRM_OK){
                is_prm_writed = true;
            }
        }
        mj_handle.out.prm_ans.msg->id = prmId;
        if (bup_dcu_lfd_prm_read(prmId, mj_handle.out.prm_ans.msg->val) == MJ_PRM_OK){
            mj_handle.out.prm_ans.msg->ans = PARAMETER_STATUS_OK;
        } else {
            mj_handle.out.prm_ans.msg->ans = PARAMETER_STATUS_UNKNOWPRM;
        }
        if (is_prm_writed && mj_handle.prm.upd_cb){
            mj_handle.prm.upd_cb(prmId);
        }
        mj_handle.out.prm_ans.tx(mj_handle.in.mon.prm_req.msg->hdr.src);
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

mj_status_t mj_bup_dcu_lfd_prm_init(mj_bup_dcu_lfd_t ** ptr){
        /* PRM */
    _bup_dcu_lfd_prm.dev_id = 64130;
    /* prms[p] */
    const uint8_t default_com_if_srv_mcast_req[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x32,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.com_if_srv_mcast_req), default_com_if_srv_mcast_req, sizeof(default_com_if_srv_mcast_req) > 32 ? 32 : sizeof(default_com_if_srv_mcast_req));
    /* prms[p] */
    const uint8_t default_com_if_srv_mcast_ans[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x32,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x32, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.com_if_srv_mcast_ans), default_com_if_srv_mcast_ans, sizeof(default_com_if_srv_mcast_ans) > 32 ? 32 : sizeof(default_com_if_srv_mcast_ans));
    /* prms[p] */
    const uint8_t default_com_if_bro_bup_ctrl_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.com_if_bro_bup_ctrl_mcast), default_com_if_bro_bup_ctrl_mcast, sizeof(default_com_if_bro_bup_ctrl_mcast) > 32 ? 32 : sizeof(default_com_if_bro_bup_ctrl_mcast));
    /* prms[p] */
    const uint8_t default_com_if_bro_bup_data_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x32, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.com_if_bro_bup_data_mcast), default_com_if_bro_bup_data_mcast, sizeof(default_com_if_bro_bup_data_mcast) > 32 ? 32 : sizeof(default_com_if_bro_bup_data_mcast));
    /* prms[p] */
    const uint8_t default_com_if_bup_internal_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x31,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x32, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.com_if_bup_internal_mcast), default_com_if_bup_internal_mcast, sizeof(default_com_if_bup_internal_mcast) > 32 ? 32 : sizeof(default_com_if_bup_internal_mcast));
    /* prms[p] */
    const uint8_t default_com_if_bro_bup_srv_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.com_if_bro_bup_srv_mcast), default_com_if_bro_bup_srv_mcast, sizeof(default_com_if_bro_bup_srv_mcast) > 32 ? 32 : sizeof(default_com_if_bro_bup_srv_mcast));
    /* prms[p] */
    const uint8_t default_com_if_im_bro_drive_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x39,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.com_if_im_bro_drive_mcast), default_com_if_im_bro_drive_mcast, sizeof(default_com_if_im_bro_drive_mcast) > 32 ? 32 : sizeof(default_com_if_im_bro_drive_mcast));
    _bup_dcu_lfd_prm.service_mode = 0;
    _bup_dcu_lfd_prm.dbg_mode = 0;
    _bup_dcu_lfd_prm.ptp_stat = 0;
    _bup_dcu_lfd_prm.vdc_scale = 0.017724609;
    _bup_dcu_lfd_prm.ocp_lvl = 115;
    _bup_dcu_lfd_prm.cur_lim = 95;
    _bup_dcu_lfd_prm.drv_ang_reverse = 0;
    _bup_dcu_lfd_prm.drv_current_reverse = 0;
    _bup_dcu_lfd_prm.drv_voltage_reverse = 0;
    _bup_dcu_lfd_prm.drv_zero = 0;
    _bup_dcu_lfd_prm.vdc_min = 10;
    _bup_dcu_lfd_prm.im_mode = 0;
    _bup_dcu_lfd_prm.ptp_kp = 0.0;
    _bup_dcu_lfd_prm.ptp_ki = 0.0;
    _bup_dcu_lfd_prm.ptp_kd = 0.0;
    _bup_dcu_lfd_prm.ohp_lvl = 0.0;
    _bup_dcu_lfd_prm.ohp_hyst = 5.0;
    _bup_dcu_lfd_prm.el_zero = 0.0;
    _bup_dcu_lfd_prm.pole_pairs = 0;
    _bup_dcu_lfd_prm.ph_resistance = 0.0;
    _bup_dcu_lfd_prm.ph_inductance = 0.0;
    _bup_dcu_lfd_prm.brake_unlock_voltage = 0.0;
    _bup_dcu_lfd_prm.brake_unlock_time = 0;
    _bup_dcu_lfd_prm.brake_hold_voltage = 0.0;
    _bup_dcu_lfd_prm.brake_lock_time = 0;
    _bup_dcu_lfd_prm.curr_kp = 0.0;
    _bup_dcu_lfd_prm.curr_ki = 0.0;
    _bup_dcu_lfd_prm.curr_kb = 0.0;
    _bup_dcu_lfd_prm.curr_kt = 0.0;
    _bup_dcu_lfd_prm.curr_kf = 0.0;
    _bup_dcu_lfd_prm.curr_fc = 0.0;
    _bup_dcu_lfd_prm.curr_err_lim = 0.0;
    _bup_dcu_lfd_prm.curr_out_lim = 0.0;
    _bup_dcu_lfd_prm.curr_out_rate_lim = 0.0;
    _bup_dcu_lfd_prm.curr_err_rate_lim = 0.0;
    _bup_dcu_lfd_prm.load_speed_kp = 0.0;
    _bup_dcu_lfd_prm.load_speed_ki = 0.0;
    _bup_dcu_lfd_prm.load_speed_kb = 0.0;
    _bup_dcu_lfd_prm.load_speed_kt = 0.0;
    _bup_dcu_lfd_prm.load_speed_kf = 0.0;
    _bup_dcu_lfd_prm.load_speed_err_lim = 0.0;
    _bup_dcu_lfd_prm.load_speed_out_lim = 0.0;
    _bup_dcu_lfd_prm.load_speed_int_lim = 0.0;
    _bup_dcu_lfd_prm.load_speed_out_rate_lim = 0.0;
    _bup_dcu_lfd_prm.load_speed_err_rate_lim = 0.0;
    _bup_dcu_lfd_prm.load_speed_flt_fc = 0;
    _bup_dcu_lfd_prm.rotor_speed_flt_fc = 0;
    _bup_dcu_lfd_prm.load_ang_kp = 0.0;
    _bup_dcu_lfd_prm.load_ang_ki = 0.0;
    _bup_dcu_lfd_prm.load_ang_kb = 0.0;
    _bup_dcu_lfd_prm.load_ang_kt = 0.0;
    _bup_dcu_lfd_prm.load_ang_kf = 0.0;
    _bup_dcu_lfd_prm.load_ang_rev = 0;
    _bup_dcu_lfd_prm.load_ang_kd = 0.0;
    _bup_dcu_lfd_prm.load_ang_err_lim = 0.0;
    _bup_dcu_lfd_prm.load_ang_out_lim = 0.0;
    _bup_dcu_lfd_prm.load_ang_out_rate_lim = 0.0;
    _bup_dcu_lfd_prm.load_ang_err_rate_lim = 0.0;
    _bup_dcu_lfd_prm.load_ang_dz = 0.0;
    _bup_dcu_lfd_prm.load_ang_dz_en = 0;
    _bup_dcu_lfd_prm.rotor_speed_kp = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_ki = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_kb = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_kt = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_kf = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_err_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_out_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_int_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_out_rate_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_err_rate_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_kp = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_ki = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_kb = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_kt = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_kf = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_err_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_out_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_int_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_out_rate_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_common_err_rate_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_kp = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_ki = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_kb = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_kt = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_kf = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_err_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_out_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_int_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_out_rate_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_master_diff_err_rate_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_speed_role = 0;
    _bup_dcu_lfd_prm.rotor_ang_kp = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_ki = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_kb = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_kt = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_kf = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_err_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_out_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_out_rate_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_err_rate_lim = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_dz = 0.0;
    _bup_dcu_lfd_prm.rotor_ang_dz_en = 0;
    /* prms[p] */
    const uint8_t default_factory_date[] = { 0x8d,0x85,0x92,0x20,0x88,0x8d,0x94,0x8e,0x90,0x8c,0x80,0x96,0x88,0x88,0x21, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.factory_date), default_factory_date, sizeof(default_factory_date) > 32 ? 32 : sizeof(default_factory_date));
    /* prms[p] */
    const uint8_t default_factory_number[] = { 0x8d,0x85,0x92,0x20,0x88,0x8d,0x94,0x8e,0x90,0x8c,0x80,0x96,0x88,0x88,0x21, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.factory_number), default_factory_number, sizeof(default_factory_number) > 32 ? 32 : sizeof(default_factory_number));
    /* prms[p] */
    const uint8_t default_description[] = { 0x8d,0x85,0x92,0x20,0x88,0x8d,0x94,0x8e,0x90,0x8c,0x80,0x96,0x88,0x88,0x21, 0x00};
    memcpy(&(_bup_dcu_lfd_prm.description), default_description, sizeof(default_description) > 32 ? 32 : sizeof(default_description));
    mj_handle.prm.ptr = &_bup_dcu_lfd_prm;
    mj_handle.prm.read = bup_dcu_lfd_prm_read;
    mj_handle.prm.write = bup_dcu_lfd_prm_write;
    mj_handle.prm.list = bup_dcu_lfd_prm_list;
    *ptr = &mj_handle;
    return MJ_OK;
}

mj_status_t mj_bup_dcu_lfd_init(mj_drv_interface_t *drv, mj_bup_dcu_lfd_t ** ptr)
{
    //memset(&mj_handle,0,sizeof(mj_handle));
    if (mj_handle.prm.ptr == NULL){
        mj_bup_dcu_lfd_prm_init(ptr);
    }
    self_dev_id = mj_handle.prm.ptr->dev_id;
    p_drv = drv;
    ethInt = p_drv->udp4.create_interface(devMac, BUP_DCU_LFD_IP);
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
    if (p_drv->udp4.register_callback(bro_bup_srv_mcast_ip_be, bro_bup_srv_mcast_port_be, bro_bup_srv_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(bup_internal_mcast_ip_be, bup_internal_mcast_port_be, bup_internal_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(im_bro_drive_mcast_ip_be, im_bro_drive_mcast_port_be, im_bro_drive_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(srv_mcast_req_ip_be, srv_mcast_req_port_be, srv_mcast_req_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }

    group_addr[0] = bro_bup_ctrl_mcast_ip_be; // bro_bup_ctrl_mcast
    group_addr[1] = 0;
    group_addr[2] = bro_bup_srv_mcast_ip_be; // bro_bup_srv_mcast
    group_addr[3] = 0;
    group_addr[4] = bup_internal_mcast_ip_be; // bup_internal_mcast
    group_addr[5] = 0;
    group_addr[6] = im_bro_drive_mcast_ip_be; // im_bro_drive_mcast
    group_addr[7] = 0;
    group_addr[8] = srv_mcast_req_ip_be; // srv_mcast_req
    group_addr[9] = 0;

    /* OUT */
    /** bup_state */
    if ((mj_handle.out.bup_state.msg = (bup_drv_state_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_state_msg_t))))
    {
        if(bup_drv_state_type_check(mj_handle.out.bup_state.msg) == MJ_CHECK_OK)
        {
            out_bup_state_pkt = p_drv->udp4.create_out_pkt(ethInt,bro_bup_data_mcast_ip_be, bro_bup_data_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.bup_state.msg, sizeof(bup_drv_state_msg_t));
            if (out_bup_state_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.bup_state.msg->hdr.src = self_dev_id;
            mj_handle.out.bup_state.msg->hdr.cnt = 0;
            mj_handle.out.bup_state.msg->hdr.id = ID_BUP_STATE;
            mj_handle.out.bup_state.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.bup_state.tx = out_bup_state_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.bup_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** cmd_ans */
    if ((mj_handle.out.cmd_ans.msg = (command_answer_msg_t *)p_drv->udp4.alloc(sizeof(command_answer_msg_t))))
    {
        if(command_answer_type_check(mj_handle.out.cmd_ans.msg) == MJ_CHECK_OK)
        {
            out_cmd_ans_pkt = p_drv->udp4.create_out_pkt(ethInt,srv_mcast_ans_ip_be, srv_mcast_ans_port_be, 0x00,(uint8_t*)mj_handle.out.cmd_ans.msg, sizeof(command_answer_msg_t));
            if (out_cmd_ans_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.cmd_ans.msg->hdr.src = self_dev_id;
            mj_handle.out.cmd_ans.msg->hdr.cnt = 0;
            mj_handle.out.cmd_ans.msg->hdr.id = ID_CMD_ANS;
            mj_handle.out.cmd_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.cmd_ans.tx = out_cmd_ans_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.cmd_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** dbg */
    if ((mj_handle.out.dbg.msg = (dbg_data_msg_t *)p_drv->udp4.alloc(sizeof(dbg_data_msg_t))))
    {
        if(dbg_data_type_check(mj_handle.out.dbg.msg) == MJ_CHECK_OK)
        {
            out_dbg_pkt = p_drv->udp4.create_out_pkt(ethInt,bro_bup_srv_mcast_ip_be, bro_bup_srv_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.dbg.msg, sizeof(dbg_data_msg_t));
            if (out_dbg_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.dbg.msg->hdr.src = self_dev_id;
            mj_handle.out.dbg.msg->hdr.cnt = 0;
            mj_handle.out.dbg.msg->hdr.id = ID_DBG;
            mj_handle.out.dbg.msg->hdr.dst = BRO30_ALL;
            mj_handle.out.dbg.lock = out_dbg_lock_fcn;
            mj_handle.out.dbg.tx_enable = true;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.dbg.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** dcu_tel */
    if ((mj_handle.out.dcu_tel.msg = (dcu_telemetry_msg_t *)p_drv->udp4.alloc(sizeof(dcu_telemetry_msg_t))))
    {
        if(dcu_telemetry_type_check(mj_handle.out.dcu_tel.msg) == MJ_CHECK_OK)
        {
            out_dcu_tel_pkt = p_drv->udp4.create_out_pkt(ethInt,bro_bup_srv_mcast_ip_be, bro_bup_srv_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.dcu_tel.msg, sizeof(dcu_telemetry_msg_t));
            if (out_dcu_tel_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.dcu_tel.msg->hdr.src = self_dev_id;
            mj_handle.out.dcu_tel.msg->hdr.cnt = 0;
            mj_handle.out.dcu_tel.msg->hdr.id = ID_DCU_TEL;
            mj_handle.out.dcu_tel.msg->hdr.dst = BRO30_ALL;
            mj_handle.out.dcu_tel.lock = out_dcu_tel_lock_fcn;
            mj_handle.out.dcu_tel.tx_enable = true;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.dcu_tel.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** drive_master_ctrl */
    if ((mj_handle.out.drive_master_ctrl.msg = (drive_master_ctrl_msg_t *)p_drv->udp4.alloc(sizeof(drive_master_ctrl_msg_t))))
    {
        if(drive_master_ctrl_type_check(mj_handle.out.drive_master_ctrl.msg) == MJ_CHECK_OK)
        {
            out_drive_master_ctrl_pkt = p_drv->udp4.create_out_pkt(ethInt,bup_internal_mcast_ip_be, bup_internal_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.drive_master_ctrl.msg, sizeof(drive_master_ctrl_msg_t));
            if (out_drive_master_ctrl_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.drive_master_ctrl.msg->hdr.src = self_dev_id;
            mj_handle.out.drive_master_ctrl.msg->hdr.cnt = 0;
            mj_handle.out.drive_master_ctrl.msg->hdr.id = ID_DRIVE_MASTER_CTRL;
            mj_handle.out.drive_master_ctrl.msg->hdr.dst = BRO30_ALL;
            mj_handle.out.drive_master_ctrl.lock = out_drive_master_ctrl_lock_fcn;
            mj_handle.out.drive_master_ctrl.tx_enable = true;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.drive_master_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** drive_slave_fb */
    if ((mj_handle.out.drive_slave_fb.msg = (drive_slave_fb_msg_t *)p_drv->udp4.alloc(sizeof(drive_slave_fb_msg_t))))
    {
        if(drive_slave_fb_type_check(mj_handle.out.drive_slave_fb.msg) == MJ_CHECK_OK)
        {
            out_drive_slave_fb_pkt = p_drv->udp4.create_out_pkt(ethInt,bup_internal_mcast_ip_be, bup_internal_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.drive_slave_fb.msg, sizeof(drive_slave_fb_msg_t));
            if (out_drive_slave_fb_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.drive_slave_fb.msg->hdr.src = self_dev_id;
            mj_handle.out.drive_slave_fb.msg->hdr.cnt = 0;
            mj_handle.out.drive_slave_fb.msg->hdr.id = ID_DRIVE_SLAVE_FB;
            mj_handle.out.drive_slave_fb.msg->hdr.dst = BRO30_ALL;
            mj_handle.out.drive_slave_fb.lock = out_drive_slave_fb_lock_fcn;
            mj_handle.out.drive_slave_fb.tx_enable = true;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.drive_slave_fb.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** formular */
    if ((mj_handle.out.formular.msg = (formular_info_msg_t *)p_drv->udp4.alloc(sizeof(formular_info_msg_t))))
    {
        if(formular_info_type_check(mj_handle.out.formular.msg) == MJ_CHECK_OK)
        {
            out_formular_pkt = p_drv->udp4.create_out_pkt(ethInt,srv_mcast_ans_ip_be, srv_mcast_ans_port_be, 0x00,(uint8_t*)mj_handle.out.formular.msg, sizeof(formular_info_msg_t));
            if (out_formular_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.formular.msg->hdr.src = self_dev_id;
            mj_handle.out.formular.msg->hdr.cnt = 0;
            mj_handle.out.formular.msg->hdr.id = ID_FORMULAR;
            mj_handle.out.formular.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.formular.tx = out_formular_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.formular.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** msg_ans */
    if ((mj_handle.out.msg_ans.msg = (msg_answer_msg_t *)p_drv->udp4.alloc(sizeof(msg_answer_msg_t))))
    {
        if(msg_answer_type_check(mj_handle.out.msg_ans.msg) == MJ_CHECK_OK)
        {
            out_msg_ans_pkt = p_drv->udp4.create_out_pkt(ethInt,srv_mcast_ans_ip_be, srv_mcast_ans_port_be, 0x00,(uint8_t*)mj_handle.out.msg_ans.msg, sizeof(msg_answer_msg_t));
            if (out_msg_ans_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.msg_ans.msg->hdr.src = self_dev_id;
            mj_handle.out.msg_ans.msg->hdr.cnt = 0;
            mj_handle.out.msg_ans.msg->hdr.id = ID_MSG_ANS;
            p_drv->udp4.set_dscp(out_msg_ans_pkt,8);
            mj_handle.out.msg_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.msg_ans.tx = out_msg_ans_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.msg_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** prm_ans */
    if ((mj_handle.out.prm_ans.msg = (parameter_answer_msg_t *)p_drv->udp4.alloc(sizeof(parameter_answer_msg_t))))
    {
        if(parameter_answer_type_check(mj_handle.out.prm_ans.msg) == MJ_CHECK_OK)
        {
            out_prm_ans_pkt = p_drv->udp4.create_out_pkt(ethInt,srv_mcast_ans_ip_be, srv_mcast_ans_port_be, 0x00,(uint8_t*)mj_handle.out.prm_ans.msg, sizeof(parameter_answer_msg_t));
            if (out_prm_ans_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.prm_ans.msg->hdr.src = self_dev_id;
            mj_handle.out.prm_ans.msg->hdr.cnt = 0;
            mj_handle.out.prm_ans.msg->hdr.id = ID_PRM_ANS;
            p_drv->udp4.set_dscp(out_prm_ans_pkt,8);
            mj_handle.out.prm_ans.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.prm_ans.tx = out_prm_ans_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.prm_ans.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    /** ptp_state */
    if ((mj_handle.out.ptp_state.msg = (ptp_info_msg_t *)p_drv->udp4.alloc(sizeof(ptp_info_msg_t))))
    {
        if(ptp_info_type_check(mj_handle.out.ptp_state.msg) == MJ_CHECK_OK)
        {
            out_ptp_state_pkt = p_drv->udp4.create_out_pkt(ethInt,bro_bup_srv_mcast_ip_be, bro_bup_srv_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.ptp_state.msg, sizeof(ptp_info_msg_t));
            if (out_ptp_state_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.ptp_state.msg->hdr.src = self_dev_id;
            mj_handle.out.ptp_state.msg->hdr.cnt = 0;
            mj_handle.out.ptp_state.msg->hdr.id = ID_PTP_STATE;
            mj_handle.out.ptp_state.msg->hdr.dst = BRO30_ALL;
            mj_handle.out.ptp_state.lock = out_ptp_state_lock_fcn;
            mj_handle.out.ptp_state.tx_enable = true;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.ptp_state.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }


    /* IN */
    if ((mj_handle.in.aufd.bup_ctrl.msg = (bup_drv_control_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_control_msg_t)))){
        if(bup_drv_control_type_check(mj_handle.in.aufd.bup_ctrl.msg) == MJ_CHECK_OK){
            mj_handle.in.aufd.bup_ctrl.msg->hdr.src = BRO30_NONE;
            mj_handle.in.aufd.bup_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.aufd.bup_ctrl.msg->hdr.cnt = 0;
            mj_handle.in.aufd.bup_ctrl.msg->hdr.id = 0;
            mj_handle.in.aufd.bup_ctrl.lock = in_aufd_bup_ctrl_lock_fcn;
            mj_handle.in.aufd.bup_ctrl.copy = in_aufd_bup_ctrl_copy_fcn;
            mj_handle.in.aufd.bup_ctrl.upd_cb = NULL;
            mj_handle.in.aufd.bup_ctrl.irq = NULL;
            mj_handle.in.aufd.bup_ctrl.state = MJ_MSG_OBSOLETE;
            mj_handle.in.aufd.bup_ctrl.total = &in_aufd_bup_ctrl_total;
            mj_handle.in.aufd.bup_ctrl.miss = &in_aufd_bup_ctrl_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.aufd.bup_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

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

    if ((mj_handle.in.aufd.cmd_req.msg = (command_request_msg_t *)p_drv->udp4.alloc(sizeof(command_request_msg_t)))){
        if(command_request_type_check(mj_handle.in.aufd.cmd_req.msg) == MJ_CHECK_OK){
            mj_handle.in.aufd.cmd_req.msg->hdr.src = BRO30_NONE;
            mj_handle.in.aufd.cmd_req.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.aufd.cmd_req.msg->hdr.cnt = 0;
            mj_handle.in.aufd.cmd_req.msg->hdr.id = 0;
            mj_handle.in.aufd.cmd_req.lock = in_aufd_cmd_req_lock_fcn;
            mj_handle.in.aufd.cmd_req.copy = in_aufd_cmd_req_copy_fcn;
            mj_handle.in.aufd.cmd_req.upd_cb = NULL;
            mj_handle.in.aufd.cmd_req.irq = NULL;
            mj_handle.in.aufd.cmd_req.state = MJ_MSG_OBSOLETE;
            mj_handle.in.aufd.cmd_req.total = &in_aufd_cmd_req_total;
            mj_handle.in.aufd.cmd_req.miss = &in_aufd_cmd_req_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.aufd.cmd_req.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.aufd.msg_req.msg = (msg_request_msg_t *)p_drv->udp4.alloc(sizeof(msg_request_msg_t)))){
        if(msg_request_type_check(mj_handle.in.aufd.msg_req.msg) == MJ_CHECK_OK){
            mj_handle.in.aufd.msg_req.msg->hdr.src = BRO30_NONE;
            mj_handle.in.aufd.msg_req.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.aufd.msg_req.msg->hdr.cnt = 0;
            mj_handle.in.aufd.msg_req.msg->hdr.id = 0;
            mj_handle.in.aufd.msg_req.lock = in_aufd_msg_req_lock_fcn;
            mj_handle.in.aufd.msg_req.copy = in_aufd_msg_req_copy_fcn;
            mj_handle.in.aufd.msg_req.upd_cb = NULL;
            mj_handle.in.aufd.msg_req.irq = NULL;
            mj_handle.in.aufd.msg_req.state = MJ_MSG_OBSOLETE;
            mj_handle.in.aufd.msg_req.total = &in_aufd_msg_req_total;
            mj_handle.in.aufd.msg_req.miss = &in_aufd_msg_req_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.aufd.msg_req.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.aufd.prm_req.msg = (parameter_request_msg_t *)p_drv->udp4.alloc(sizeof(parameter_request_msg_t)))){
        if(parameter_request_type_check(mj_handle.in.aufd.prm_req.msg) == MJ_CHECK_OK){
            mj_handle.in.aufd.prm_req.msg->hdr.src = BRO30_NONE;
            mj_handle.in.aufd.prm_req.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.aufd.prm_req.msg->hdr.cnt = 0;
            mj_handle.in.aufd.prm_req.msg->hdr.id = 0;
            mj_handle.in.aufd.prm_req.lock = in_aufd_prm_req_lock_fcn;
            mj_handle.in.aufd.prm_req.copy = in_aufd_prm_req_copy_fcn;
            mj_handle.in.aufd.prm_req.upd_cb = NULL;
            mj_handle.in.aufd.prm_req.irq = NULL;
            mj_handle.in.aufd.prm_req.state = MJ_MSG_OBSOLETE;
            mj_handle.in.aufd.prm_req.total = &in_aufd_prm_req_total;
            mj_handle.in.aufd.prm_req.miss = &in_aufd_prm_req_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.aufd.prm_req.msg);
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

    if ((mj_handle.in.mon.bup_multi_control.msg = (bup_drv_multi_control_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_multi_control_msg_t)))){
        if(bup_drv_multi_control_type_check(mj_handle.in.mon.bup_multi_control.msg) == MJ_CHECK_OK){
            mj_handle.in.mon.bup_multi_control.msg->hdr.src = BRO30_NONE;
            mj_handle.in.mon.bup_multi_control.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.mon.bup_multi_control.msg->hdr.cnt = 0;
            mj_handle.in.mon.bup_multi_control.msg->hdr.id = 0;
            mj_handle.in.mon.bup_multi_control.lock = in_mon_bup_multi_control_lock_fcn;
            mj_handle.in.mon.bup_multi_control.copy = in_mon_bup_multi_control_copy_fcn;
            mj_handle.in.mon.bup_multi_control.upd_cb = NULL;
            mj_handle.in.mon.bup_multi_control.irq = NULL;
            mj_handle.in.mon.bup_multi_control.state = MJ_MSG_OBSOLETE;
            mj_handle.in.mon.bup_multi_control.total = &in_mon_bup_multi_control_total;
            mj_handle.in.mon.bup_multi_control.miss = &in_mon_bup_multi_control_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.mon.bup_multi_control.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.mon.bup_srv_ctrl.msg = (bup_drv_control_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_control_msg_t)))){
        if(bup_drv_control_type_check(mj_handle.in.mon.bup_srv_ctrl.msg) == MJ_CHECK_OK){
            mj_handle.in.mon.bup_srv_ctrl.msg->hdr.src = BRO30_NONE;
            mj_handle.in.mon.bup_srv_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.mon.bup_srv_ctrl.msg->hdr.cnt = 0;
            mj_handle.in.mon.bup_srv_ctrl.msg->hdr.id = 0;
            mj_handle.in.mon.bup_srv_ctrl.lock = in_mon_bup_srv_ctrl_lock_fcn;
            mj_handle.in.mon.bup_srv_ctrl.copy = in_mon_bup_srv_ctrl_copy_fcn;
            mj_handle.in.mon.bup_srv_ctrl.upd_cb = NULL;
            mj_handle.in.mon.bup_srv_ctrl.irq = NULL;
            mj_handle.in.mon.bup_srv_ctrl.state = MJ_MSG_OBSOLETE;
            mj_handle.in.mon.bup_srv_ctrl.total = &in_mon_bup_srv_ctrl_total;
            mj_handle.in.mon.bup_srv_ctrl.miss = &in_mon_bup_srv_ctrl_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.mon.bup_srv_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.mon.cmd_req.msg = (command_request_msg_t *)p_drv->udp4.alloc(sizeof(command_request_msg_t)))){
        if(command_request_type_check(mj_handle.in.mon.cmd_req.msg) == MJ_CHECK_OK){
            mj_handle.in.mon.cmd_req.msg->hdr.src = BRO30_NONE;
            mj_handle.in.mon.cmd_req.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.mon.cmd_req.msg->hdr.cnt = 0;
            mj_handle.in.mon.cmd_req.msg->hdr.id = 0;
            mj_handle.in.mon.cmd_req.lock = in_mon_cmd_req_lock_fcn;
            mj_handle.in.mon.cmd_req.copy = in_mon_cmd_req_copy_fcn;
            mj_handle.in.mon.cmd_req.upd_cb = NULL;
            mj_handle.in.mon.cmd_req.irq = NULL;
            mj_handle.in.mon.cmd_req.state = MJ_MSG_OBSOLETE;
            mj_handle.in.mon.cmd_req.total = &in_mon_cmd_req_total;
            mj_handle.in.mon.cmd_req.miss = &in_mon_cmd_req_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.mon.cmd_req.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.mon.msg_req.msg = (msg_request_msg_t *)p_drv->udp4.alloc(sizeof(msg_request_msg_t)))){
        if(msg_request_type_check(mj_handle.in.mon.msg_req.msg) == MJ_CHECK_OK){
            mj_handle.in.mon.msg_req.msg->hdr.src = BRO30_NONE;
            mj_handle.in.mon.msg_req.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.mon.msg_req.msg->hdr.cnt = 0;
            mj_handle.in.mon.msg_req.msg->hdr.id = 0;
            mj_handle.in.mon.msg_req.lock = in_mon_msg_req_lock_fcn;
            mj_handle.in.mon.msg_req.copy = in_mon_msg_req_copy_fcn;
            mj_handle.in.mon.msg_req.upd_cb = NULL;
            mj_handle.in.mon.msg_req.irq = NULL;
            mj_handle.in.mon.msg_req.state = MJ_MSG_OBSOLETE;
            mj_handle.in.mon.msg_req.total = &in_mon_msg_req_total;
            mj_handle.in.mon.msg_req.miss = &in_mon_msg_req_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.mon.msg_req.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

    if ((mj_handle.in.mon.prm_req.msg = (parameter_request_msg_t *)p_drv->udp4.alloc(sizeof(parameter_request_msg_t)))){
        if(parameter_request_type_check(mj_handle.in.mon.prm_req.msg) == MJ_CHECK_OK){
            mj_handle.in.mon.prm_req.msg->hdr.src = BRO30_NONE;
            mj_handle.in.mon.prm_req.msg->hdr.dst = BRO30_NONE;
            mj_handle.in.mon.prm_req.msg->hdr.cnt = 0;
            mj_handle.in.mon.prm_req.msg->hdr.id = 0;
            mj_handle.in.mon.prm_req.lock = in_mon_prm_req_lock_fcn;
            mj_handle.in.mon.prm_req.copy = in_mon_prm_req_copy_fcn;
            mj_handle.in.mon.prm_req.upd_cb = NULL;
            mj_handle.in.mon.prm_req.irq = NULL;
            mj_handle.in.mon.prm_req.state = MJ_MSG_OBSOLETE;
            mj_handle.in.mon.prm_req.total = &in_mon_prm_req_total;
            mj_handle.in.mon.prm_req.miss = &in_mon_prm_req_miss;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.in.mon.prm_req.msg);
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