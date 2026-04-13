#include "mj_aufd_spec.h"

#define IN_INT_COUNT 2

static uint32_t group_addr[IN_INT_COUNT*2];

static const uint8_t devMac[6] = { 0x2,0x0,0x0,0x0,0x0,0x1 };

static uint32_t ticks = 0;
static void *ethInt = NULL;
static mj_drv_interface_t * p_drv = NULL;
static uint16_t self_dev_id = BRO30_AUFD;

static mj_aufd_t mj_handle;

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


static void * out_bup_ctrl_pkt = NULL;
static void out_bup_ctrl_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.bup_ctrl.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.bup_ctrl.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.bup_ctrl.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.bup_ctrl.msg->hdr.dst = dst;
    mj_handle.out.bup_ctrl.msg->hdr.cnt++;
    p_drv->udp4.tx(out_bup_ctrl_pkt,NULL);
}

static void * out_bup_multi_control_pkt = NULL;
static void out_bup_multi_control_tx_fcn(uint16_t dst)
{
    uint32_t _temp_ns = 0;
    mj_handle.out.bup_multi_control.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.bup_multi_control.msg->hdr.ts_s,&_temp_ns);
    mj_handle.out.bup_multi_control.msg->hdr.ts_ns = _temp_ns;
    mj_handle.out.bup_multi_control.msg->hdr.dst = dst;
    mj_handle.out.bup_multi_control.msg->hdr.cnt++;
    p_drv->udp4.tx(out_bup_multi_control_pkt,NULL);
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


static aufd_prm_t _aufd_prm;

mj_prm_status_t aufd_prm_write(int id, void *data)
{
    switch (id){
        case PRM_BOOL_SERVICE_MODE:
            memcpy(&(_aufd_prm.service_mode),data,sizeof(_aufd_prm.service_mode));
            return MJ_PRM_OK;
        case PRM_STRING_FACTORY_DATE:
            memcpy(&(_aufd_prm.factory_date),data,sizeof(_aufd_prm.factory_date));
            return MJ_PRM_OK;
        case PRM_STRING_FACTORY_NUMBER:
            memcpy(&(_aufd_prm.factory_number),data,sizeof(_aufd_prm.factory_number));
            return MJ_PRM_OK;
        case PRM_STRING_DESCRIPTION:
            memcpy(&(_aufd_prm.description),data,sizeof(_aufd_prm.description));
            return MJ_PRM_OK;
        case PRM_INT_DEV_ID:
            memcpy(&(_aufd_prm.dev_id),data,sizeof(_aufd_prm.dev_id));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_REQ:
            memcpy(&(_aufd_prm.com_if_srv_mcast_req),data,sizeof(_aufd_prm.com_if_srv_mcast_req));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_ANS:
            memcpy(&(_aufd_prm.com_if_srv_mcast_ans),data,sizeof(_aufd_prm.com_if_srv_mcast_ans));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST:
            memcpy(&(_aufd_prm.com_if_bro_bup_ctrl_mcast),data,sizeof(_aufd_prm.com_if_bro_bup_ctrl_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST:
            memcpy(&(_aufd_prm.com_if_bro_bup_data_mcast),data,sizeof(_aufd_prm.com_if_bro_bup_data_mcast));
            return MJ_PRM_OK;
        default:
            return MJ_PRM_UNKNOW;
    }
}

mj_prm_status_t aufd_prm_read(int id, void *data)
{
    switch (id){
        case PRM_BOOL_SERVICE_MODE:
            memcpy(data,&_aufd_prm.service_mode,sizeof(_aufd_prm.service_mode));
            return MJ_PRM_OK;
        case PRM_STRING_FACTORY_DATE:
            memcpy(data,&_aufd_prm.factory_date,sizeof(_aufd_prm.factory_date));
            return MJ_PRM_OK;
        case PRM_STRING_FACTORY_NUMBER:
            memcpy(data,&_aufd_prm.factory_number,sizeof(_aufd_prm.factory_number));
            return MJ_PRM_OK;
        case PRM_STRING_DESCRIPTION:
            memcpy(data,&_aufd_prm.description,sizeof(_aufd_prm.description));
            return MJ_PRM_OK;
        case PRM_INT_DEV_ID:
            memcpy(data,&_aufd_prm.dev_id,sizeof(_aufd_prm.dev_id));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_REQ:
            memcpy(data,&_aufd_prm.com_if_srv_mcast_req,sizeof(_aufd_prm.com_if_srv_mcast_req));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_ANS:
            memcpy(data,&_aufd_prm.com_if_srv_mcast_ans,sizeof(_aufd_prm.com_if_srv_mcast_ans));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST:
            memcpy(data,&_aufd_prm.com_if_bro_bup_ctrl_mcast,sizeof(_aufd_prm.com_if_bro_bup_ctrl_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST:
            memcpy(data,&_aufd_prm.com_if_bro_bup_data_mcast,sizeof(_aufd_prm.com_if_bro_bup_data_mcast));
            return MJ_PRM_OK;
        default:
            return MJ_PRM_UNKNOW;
    }
}

static const uint32_t _prm_ids[9] = {
    PRM_BOOL_SERVICE_MODE,
    PRM_STRING_FACTORY_DATE,
    PRM_STRING_FACTORY_NUMBER,
    PRM_STRING_DESCRIPTION,
    PRM_INT_DEV_ID,
    PRM_STRING_COM_IF_SRV_MCAST_REQ,
    PRM_STRING_COM_IF_SRV_MCAST_ANS,
    PRM_STRING_COM_IF_BRO_BUP_CTRL_MCAST,
    PRM_STRING_COM_IF_BRO_BUP_DATA_MCAST
};

static const uint32_t * aufd_prm_list(uint32_t *size)
{
    *size = 9;
    return _prm_ids;
}


static uint32_t *_join_ip = NULL;
static volatile bool _send_join_done = true;
static uint32_t _join_send_tick = 0;

static void tick_fcn()
{
    uint32_t _temp_ns = 0;

    if (!_send_join_done && _join_ip) {
        p_drv->udp4.join_group(ethInt, *_join_ip);
        _join_send_tick = ticks;
        _send_join_done = true;
    }
    p_drv->udp4.pool_tx();
    ticks++;
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


static mj_msg_proc_res_t srv_mcast_req_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
            // msg_req
            case ID_MSG_REQ:
                if (size == sizeof(msg_request_msg_t))
                {
                    switch (hdr->src)
                    {
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
            default:
                return MJ_REJECT_ID;    
        }
    }
    return MJ_REJECT_DST; 
}


static void loop_fcn()
{
    uint32_t c_time = ticks;

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

    if((((int32_t)(c_time - mon_msg_req_rx_tick)) > 4000)){
        mj_handle.in.mon.msg_req.state = MJ_MSG_OBSOLETE;
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
    if(in_mon_msg_req_updated == 1)
    {
        if(mj_handle.in.mon.msg_req.upd_cb){mj_handle.in.mon.msg_req.upd_cb();}
        in_mon_msg_req_updated = 0;
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

mj_status_t mj_aufd_prm_init(mj_aufd_t ** ptr){
        /* PRM */
    _aufd_prm.service_mode = 0;
    /* prms[p] */
    const uint8_t default_factory_date[] = { 0x8d,0x85,0x92,0x20,0x88,0x8d,0x94,0x8e,0x90,0x8c,0x80,0x96,0x88,0x88,0x21, 0x00};
    memcpy(&(_aufd_prm.factory_date), default_factory_date, sizeof(default_factory_date) > 32 ? 32 : sizeof(default_factory_date));
    /* prms[p] */
    const uint8_t default_factory_number[] = { 0x8d,0x85,0x92,0x20,0x88,0x8d,0x94,0x8e,0x90,0x8c,0x80,0x96,0x88,0x88,0x21, 0x00};
    memcpy(&(_aufd_prm.factory_number), default_factory_number, sizeof(default_factory_number) > 32 ? 32 : sizeof(default_factory_number));
    /* prms[p] */
    const uint8_t default_description[] = { 0x8d,0x85,0x92,0x20,0x88,0x8d,0x94,0x8e,0x90,0x8c,0x80,0x96,0x88,0x88,0x21, 0x00};
    memcpy(&(_aufd_prm.description), default_description, sizeof(default_description) > 32 ? 32 : sizeof(default_description));
    _aufd_prm.dev_id = 62902;
    /* prms[p] */
    const uint8_t default_com_if_srv_mcast_req[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x32,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_aufd_prm.com_if_srv_mcast_req), default_com_if_srv_mcast_req, sizeof(default_com_if_srv_mcast_req) > 32 ? 32 : sizeof(default_com_if_srv_mcast_req));
    /* prms[p] */
    const uint8_t default_com_if_srv_mcast_ans[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x32,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x32, 0x00};
    memcpy(&(_aufd_prm.com_if_srv_mcast_ans), default_com_if_srv_mcast_ans, sizeof(default_com_if_srv_mcast_ans) > 32 ? 32 : sizeof(default_com_if_srv_mcast_ans));
    /* prms[p] */
    const uint8_t default_com_if_bro_bup_ctrl_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_aufd_prm.com_if_bro_bup_ctrl_mcast), default_com_if_bro_bup_ctrl_mcast, sizeof(default_com_if_bro_bup_ctrl_mcast) > 32 ? 32 : sizeof(default_com_if_bro_bup_ctrl_mcast));
    /* prms[p] */
    const uint8_t default_com_if_bro_bup_data_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x31,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x32, 0x00};
    memcpy(&(_aufd_prm.com_if_bro_bup_data_mcast), default_com_if_bro_bup_data_mcast, sizeof(default_com_if_bro_bup_data_mcast) > 32 ? 32 : sizeof(default_com_if_bro_bup_data_mcast));
    mj_handle.prm.ptr = &_aufd_prm;
    mj_handle.prm.read = aufd_prm_read;
    mj_handle.prm.write = aufd_prm_write;
    mj_handle.prm.list = aufd_prm_list;
    *ptr = &mj_handle;
    return MJ_OK;
}

mj_status_t mj_aufd_init(mj_drv_interface_t *drv, mj_aufd_t ** ptr)
{
    //memset(&mj_handle,0,sizeof(mj_handle));
    if (mj_handle.prm.ptr == NULL){
        mj_aufd_prm_init(ptr);
    }
    self_dev_id = mj_handle.prm.ptr->dev_id;
    p_drv = drv;
    ethInt = p_drv->udp4.create_interface(devMac, AUFD_IP);
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
    if (p_drv->udp4.register_callback(bro_bup_data_mcast_ip_be, bro_bup_data_mcast_port_be, bro_bup_data_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(srv_mcast_req_ip_be, srv_mcast_req_port_be, srv_mcast_req_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }

    group_addr[0] = bro_bup_data_mcast_ip_be; // bro_bup_data_mcast
    group_addr[1] = 0;
    group_addr[2] = srv_mcast_req_ip_be; // srv_mcast_req
    group_addr[3] = 0;

    /* OUT */
    /** bup_ctrl */
    if ((mj_handle.out.bup_ctrl.msg = (bup_drv_control_msg_t *)p_drv->udp4.alloc(sizeof(bup_drv_control_msg_t))))
    {
        if(bup_drv_control_type_check(mj_handle.out.bup_ctrl.msg) == MJ_CHECK_OK)
        {
            out_bup_ctrl_pkt = p_drv->udp4.create_out_pkt(ethInt,bro_bup_ctrl_mcast_ip_be, bro_bup_ctrl_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.bup_ctrl.msg, sizeof(bup_drv_control_msg_t));
            if (out_bup_ctrl_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.bup_ctrl.msg->hdr.src = self_dev_id;
            mj_handle.out.bup_ctrl.msg->hdr.cnt = 0;
            mj_handle.out.bup_ctrl.msg->hdr.id = ID_BUP_CTRL;
            mj_handle.out.bup_ctrl.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.bup_ctrl.tx = out_bup_ctrl_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.bup_ctrl.msg);
            return MJ_INTEGRITY_FAIL;
        }
    }else{
        return MJ_UDP4_ALOC_FAIL;
    }

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
            mj_handle.out.bup_multi_control.msg->hdr.dst = BRO30_NONE;
            mj_handle.out.bup_multi_control.tx = out_bup_multi_control_tx_fcn;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.bup_multi_control.msg);
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


    mj_handle.tick = tick_fcn;
    mj_handle.loop = loop_fcn;
    *ptr = &mj_handle;

    return MJ_OK;
}