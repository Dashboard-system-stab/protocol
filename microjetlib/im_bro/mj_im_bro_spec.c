#include "mj_im_bro_spec.h"

#define IN_INT_COUNT 2

static uint32_t group_addr[IN_INT_COUNT*2];

static const uint8_t devMac[6] = { 0x2,0x0,0x0,0x0,0x0,0x9 };

static uint32_t ticks = 0;
static void *ethInt = NULL;
static mj_drv_interface_t * p_drv = NULL;
static uint16_t self_dev_id = BRO30_IM_BRO;

static mj_im_bro_t mj_handle;

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


static void * out_im_bro_drivers_sens_pkt = NULL;
static drivers_sens_msg_t * p_out_im_bro_drivers_sens_msg = NULL;
static mj_msg_state_t out_im_bro_drivers_sens_lock_fcn(mj_msg_state_t state)
{
    mj_msg_state_t res = MJ_MSG_UNDEFINED;
    if (state == MJ_MSG_LOCK)
    {
        if (p_out_im_bro_drivers_sens_msg == NULL)
        {
            if ((p_out_im_bro_drivers_sens_msg = (drivers_sens_msg_t *)p_drv->udp4.alloc(sizeof(drivers_sens_msg_t))))
            {
                memcpy((void *)p_out_im_bro_drivers_sens_msg, (void *)(mj_handle.out.im_bro_drivers_sens.msg), sizeof(drivers_sens_msg_t));
                p_drv->udp4.set_payload(out_im_bro_drivers_sens_pkt, (uint8_t *)p_out_im_bro_drivers_sens_msg);
                res = MJ_MSG_LOCK;
            }else{
                res = MJ_MSG_UNLOCK;
            }
        }else{
            res = MJ_MSG_LOCK;
        }
    }else{
        res = MJ_MSG_LOCK;
        if (p_out_im_bro_drivers_sens_msg)
        {
            p_drv->udp4.set_payload(out_im_bro_drivers_sens_pkt, (uint8_t *)mj_handle.out.im_bro_drivers_sens.msg);
            p_drv->udp4.free((uint8_t *)p_out_im_bro_drivers_sens_msg);
            p_out_im_bro_drivers_sens_msg = NULL;
            res = MJ_MSG_UNLOCK;
        }else{
            res = MJ_MSG_UNLOCK;
        }
    }
    return res;
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


static im_bro_prm_t _im_bro_prm;

mj_prm_status_t im_bro_prm_write(int id, void *data)
{
    switch (id){
        case PRM_BOOL_SERVICE_MODE:
            memcpy(&(_im_bro_prm.service_mode),data,sizeof(_im_bro_prm.service_mode));
            return MJ_PRM_OK;
        case PRM_FLOAT_VDC:
            memcpy(&(_im_bro_prm.Vdc),data,sizeof(_im_bro_prm.Vdc));
            return MJ_PRM_OK;
        case PRM_INT_DEV_ID:
            memcpy(&(_im_bro_prm.dev_id),data,sizeof(_im_bro_prm.dev_id));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_REQ:
            memcpy(&(_im_bro_prm.com_if_srv_mcast_req),data,sizeof(_im_bro_prm.com_if_srv_mcast_req));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_ANS:
            memcpy(&(_im_bro_prm.com_if_srv_mcast_ans),data,sizeof(_im_bro_prm.com_if_srv_mcast_ans));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST:
            memcpy(&(_im_bro_prm.com_if_im_bro_drive_mcast),data,sizeof(_im_bro_prm.com_if_im_bro_drive_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_CTRL_MCAST:
            memcpy(&(_im_bro_prm.com_if_im_bro_drive_ctrl_mcast),data,sizeof(_im_bro_prm.com_if_im_bro_drive_ctrl_mcast));
            return MJ_PRM_OK;
        default:
            return MJ_PRM_UNKNOW;
    }
}

mj_prm_status_t im_bro_prm_read(int id, void *data)
{
    switch (id){
        case PRM_BOOL_SERVICE_MODE:
            memcpy(data,&_im_bro_prm.service_mode,sizeof(_im_bro_prm.service_mode));
            return MJ_PRM_OK;
        case PRM_FLOAT_VDC:
            memcpy(data,&_im_bro_prm.Vdc,sizeof(_im_bro_prm.Vdc));
            return MJ_PRM_OK;
        case PRM_INT_DEV_ID:
            memcpy(data,&_im_bro_prm.dev_id,sizeof(_im_bro_prm.dev_id));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_REQ:
            memcpy(data,&_im_bro_prm.com_if_srv_mcast_req,sizeof(_im_bro_prm.com_if_srv_mcast_req));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_SRV_MCAST_ANS:
            memcpy(data,&_im_bro_prm.com_if_srv_mcast_ans,sizeof(_im_bro_prm.com_if_srv_mcast_ans));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST:
            memcpy(data,&_im_bro_prm.com_if_im_bro_drive_mcast,sizeof(_im_bro_prm.com_if_im_bro_drive_mcast));
            return MJ_PRM_OK;
        case PRM_STRING_COM_IF_IM_BRO_DRIVE_CTRL_MCAST:
            memcpy(data,&_im_bro_prm.com_if_im_bro_drive_ctrl_mcast,sizeof(_im_bro_prm.com_if_im_bro_drive_ctrl_mcast));
            return MJ_PRM_OK;
        default:
            return MJ_PRM_UNKNOW;
    }
}

static const uint32_t _prm_ids[7] = {
    PRM_BOOL_SERVICE_MODE,
    PRM_FLOAT_VDC,
    PRM_INT_DEV_ID,
    PRM_STRING_COM_IF_SRV_MCAST_REQ,
    PRM_STRING_COM_IF_SRV_MCAST_ANS,
    PRM_STRING_COM_IF_IM_BRO_DRIVE_MCAST,
    PRM_STRING_COM_IF_IM_BRO_DRIVE_CTRL_MCAST
};

static const uint32_t * im_bro_prm_list(uint32_t *size)
{
    *size = 7;
    return _prm_ids;
}

static uint32_t _250_us_cnt = 0;
static uint32_t _250_us_tick = 1;

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
        if (mj_handle.out.im_bro_drivers_sens.tx_enable){
            mj_handle.out.im_bro_drivers_sens.msg->hdr.cnt = _250_us_cnt;
            mj_handle.out.im_bro_drivers_sens.msg->hdr.ts_status = p_drv->timestamp(&mj_handle.out.im_bro_drivers_sens.msg->hdr.ts_s,&_temp_ns);
            mj_handle.out.im_bro_drivers_sens.msg->hdr.ts_ns = _temp_ns;
            p_drv->udp4.tx(out_im_bro_drivers_sens_pkt,NULL);
        }
        _250_us_tick = 0;
    }
    _250_us_tick++;

    if (!_send_join_done && _join_ip) {
        p_drv->udp4.join_group(ethInt, *_join_ip);
        _join_send_tick = ticks;
        _send_join_done = true;
    }
    p_drv->udp4.pool_tx();
    ticks++;
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


static mj_msg_proc_res_t srv_mcast_req_cb(uint8_t* data, uint16_t size, uint32_t ts_s, uint32_t ts_ns)
{
    mj_msg_header_t *hdr = (mj_msg_header_t*)data;
    if ((hdr->dst == BRO30_ALL) || (hdr->dst == self_dev_id))
    {
        uint8_t *old_buff = NULL;
        switch (hdr->id)
        {
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

    if((((int32_t)(c_time - aufd_prm_req_rx_tick)) > 4000)){
        mj_handle.in.aufd.prm_req.state = MJ_MSG_OBSOLETE;
    }

    if((((int32_t)(c_time - mon_prm_req_rx_tick)) > 4000)){
        mj_handle.in.mon.prm_req.state = MJ_MSG_OBSOLETE;
    }

    if(in_aufd_prm_req_updated == 1)
    {
        if(mj_handle.in.aufd.prm_req.upd_cb){mj_handle.in.aufd.prm_req.upd_cb();}
        in_aufd_prm_req_updated = 0;
        bro30_prm_id_k prmId = mj_handle.in.aufd.prm_req.msg->id;
        parameter_request_type_k rtype = mj_handle.in.aufd.prm_req.msg->type;
        bool is_prm_writed = false;
        if (rtype == PARAMETER_REQUEST_TYPE_WRITE){
            if (im_bro_prm_write(prmId, mj_handle.in.aufd.prm_req.msg->val) == MJ_PRM_OK){
                is_prm_writed = true;
            }
        }
        mj_handle.out.prm_ans.msg->id = prmId;
        if (im_bro_prm_read(prmId, mj_handle.out.prm_ans.msg->val) == MJ_PRM_OK){
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
            if (im_bro_prm_write(prmId, mj_handle.in.mon.prm_req.msg->val) == MJ_PRM_OK){
                is_prm_writed = true;
            }
        }
        mj_handle.out.prm_ans.msg->id = prmId;
        if (im_bro_prm_read(prmId, mj_handle.out.prm_ans.msg->val) == MJ_PRM_OK){
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

mj_status_t mj_im_bro_prm_init(mj_im_bro_t ** ptr){
        /* PRM */
    _im_bro_prm.service_mode = 0;
    _im_bro_prm.Vdc = 48;
    _im_bro_prm.dev_id = 7500;
    /* prms[p] */
    const uint8_t default_com_if_srv_mcast_req[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x32,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_im_bro_prm.com_if_srv_mcast_req), default_com_if_srv_mcast_req, sizeof(default_com_if_srv_mcast_req) > 32 ? 32 : sizeof(default_com_if_srv_mcast_req));
    /* prms[p] */
    const uint8_t default_com_if_srv_mcast_ans[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x32,0x30,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x32, 0x00};
    memcpy(&(_im_bro_prm.com_if_srv_mcast_ans), default_com_if_srv_mcast_ans, sizeof(default_com_if_srv_mcast_ans) > 32 ? 32 : sizeof(default_com_if_srv_mcast_ans));
    /* prms[p] */
    const uint8_t default_com_if_im_bro_drive_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x39,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_im_bro_prm.com_if_im_bro_drive_mcast), default_com_if_im_bro_drive_mcast, sizeof(default_com_if_im_bro_drive_mcast) > 32 ? 32 : sizeof(default_com_if_im_bro_drive_mcast));
    /* prms[p] */
    const uint8_t default_com_if_im_bro_drive_ctrl_mcast[] = { 0x32,0x33,0x39,0x2e,0x32,0x30,0x30,0x2e,0x39,0x30,0x2e,0x31,0x3a,0x34,0x39,0x30,0x30,0x31, 0x00};
    memcpy(&(_im_bro_prm.com_if_im_bro_drive_ctrl_mcast), default_com_if_im_bro_drive_ctrl_mcast, sizeof(default_com_if_im_bro_drive_ctrl_mcast) > 32 ? 32 : sizeof(default_com_if_im_bro_drive_ctrl_mcast));
    mj_handle.prm.ptr = &_im_bro_prm;
    mj_handle.prm.read = im_bro_prm_read;
    mj_handle.prm.write = im_bro_prm_write;
    mj_handle.prm.list = im_bro_prm_list;
    *ptr = &mj_handle;
    return MJ_OK;
}

mj_status_t mj_im_bro_init(mj_drv_interface_t *drv, mj_im_bro_t ** ptr)
{
    //memset(&mj_handle,0,sizeof(mj_handle));
    if (mj_handle.prm.ptr == NULL){
        mj_im_bro_prm_init(ptr);
    }
    self_dev_id = mj_handle.prm.ptr->dev_id;
    p_drv = drv;
    ethInt = p_drv->udp4.create_interface(devMac, IM_BRO_IP);
    if (ethInt == NULL){return MJ_ETH_FAIL;};

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
    if (p_drv->udp4.register_callback(im_bro_drive_ctrl_mcast_ip_be, im_bro_drive_ctrl_mcast_port_be, im_bro_drive_ctrl_mcast_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }
    if (p_drv->udp4.register_callback(srv_mcast_req_ip_be, srv_mcast_req_port_be, srv_mcast_req_cb) != MJ_OK){
        return MJ_UDP4_CB_FAIL;
    }

    group_addr[0] = im_bro_drive_ctrl_mcast_ip_be; // im_bro_drive_ctrl_mcast
    group_addr[1] = 0;
    group_addr[2] = srv_mcast_req_ip_be; // srv_mcast_req
    group_addr[3] = 0;

    /* OUT */
    /** im_bro_drivers_sens */
    if ((mj_handle.out.im_bro_drivers_sens.msg = (drivers_sens_msg_t *)p_drv->udp4.alloc(sizeof(drivers_sens_msg_t))))
    {
        if(drivers_sens_type_check(mj_handle.out.im_bro_drivers_sens.msg) == MJ_CHECK_OK)
        {
            out_im_bro_drivers_sens_pkt = p_drv->udp4.create_out_pkt(ethInt,im_bro_drive_mcast_ip_be, im_bro_drive_mcast_port_be, 0x00,(uint8_t*)mj_handle.out.im_bro_drivers_sens.msg, sizeof(drivers_sens_msg_t));
            if (out_im_bro_drivers_sens_pkt == NULL){return MJ_UDP4_PKT_FAIL;}
            mj_handle.out.im_bro_drivers_sens.msg->hdr.src = self_dev_id;
            mj_handle.out.im_bro_drivers_sens.msg->hdr.cnt = 0;
            mj_handle.out.im_bro_drivers_sens.msg->hdr.id = ID_IM_BRO_DRIVERS_SENS;
            mj_handle.out.im_bro_drivers_sens.msg->hdr.dst = BRO30_ALL;
            mj_handle.out.im_bro_drivers_sens.lock = out_im_bro_drivers_sens_lock_fcn;
            mj_handle.out.im_bro_drivers_sens.tx_enable = true;
        }else{
            p_drv->udp4.free((uint8_t *)mj_handle.out.im_bro_drivers_sens.msg);
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


    /* IN */
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