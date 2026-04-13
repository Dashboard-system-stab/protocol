#ifndef MON_DEV_SPEC_H
#define MON_DEV_SPEC_H

#include "mjsysspec.h"
#include "mjutils.h"

#ifdef __cplusplus
 extern "C" {
#endif


typedef struct mon_prm{
     /** service_mode [-] */
     bool service_mode;
     /** dev_id [-] */
     int dev_id;
     /** com_if_srv_mcast_req [-] */
     char com_if_srv_mcast_req[32];
     /** com_if_srv_mcast_ans [-] */
     char com_if_srv_mcast_ans[32];
     /** com_if_bro_bup_data_mcast [-] */
     char com_if_bro_bup_data_mcast[32];
     /** com_if_bro_bup_srv_mcast [-] */
     char com_if_bro_bup_srv_mcast[32];
     /** com_if_im_bro_drive_mcast [-] */
     char com_if_im_bro_drive_mcast[32];
     /** com_if_im_bro_drive_ctrl_mcast [-] */
     char com_if_im_bro_drive_ctrl_mcast[32];
} mon_prm_t;

typedef struct mj_mon
{
     /** mon input messages */
     struct
     {
          /** Messages from aufd device*/
          struct {
               /** cmd_ans from aufd*/
               struct
               {
                    command_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_ans;
               /** formular from aufd*/
               struct
               {
                    formular_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } formular;
               /** msg_ans from aufd*/
               struct
               {
                    msg_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_ans;
               /** prm_ans from aufd*/
               struct
               {
                    parameter_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_ans;
          } aufd;
          /** Messages from bup_dcu_lfd device*/
          struct {
               /** bup_state from bup_dcu_lfd*/
               struct
               {
                    bup_drv_state_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_state;
               /** cmd_ans from bup_dcu_lfd*/
               struct
               {
                    command_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_ans;
               /** dbg from bup_dcu_lfd*/
               struct
               {
                    dbg_data_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dbg;
               /** dcu_tel from bup_dcu_lfd*/
               struct
               {
                    dcu_telemetry_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dcu_tel;
               /** formular from bup_dcu_lfd*/
               struct
               {
                    formular_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } formular;
               /** im_bro_drive_ctrl from bup_dcu_lfd*/
               struct
               {
                    im_bro_drive_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } im_bro_drive_ctrl;
               /** msg_ans from bup_dcu_lfd*/
               struct
               {
                    msg_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_ans;
               /** prm_ans from bup_dcu_lfd*/
               struct
               {
                    parameter_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_ans;
               /** ptp_state from bup_dcu_lfd*/
               struct
               {
                    ptp_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } ptp_state;
          } bup_dcu_lfd;
          /** Messages from bup_dcu_lrd device*/
          struct {
               /** bup_state from bup_dcu_lrd*/
               struct
               {
                    bup_drv_state_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_state;
               /** cmd_ans from bup_dcu_lrd*/
               struct
               {
                    command_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_ans;
               /** dbg from bup_dcu_lrd*/
               struct
               {
                    dbg_data_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dbg;
               /** dcu_tel from bup_dcu_lrd*/
               struct
               {
                    dcu_telemetry_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dcu_tel;
               /** formular from bup_dcu_lrd*/
               struct
               {
                    formular_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } formular;
               /** im_bro_drive_ctrl from bup_dcu_lrd*/
               struct
               {
                    im_bro_drive_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } im_bro_drive_ctrl;
               /** msg_ans from bup_dcu_lrd*/
               struct
               {
                    msg_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_ans;
               /** prm_ans from bup_dcu_lrd*/
               struct
               {
                    parameter_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_ans;
               /** ptp_state from bup_dcu_lrd*/
               struct
               {
                    ptp_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } ptp_state;
          } bup_dcu_lrd;
          /** Messages from bup_dcu_lst device*/
          struct {
               /** bup_state from bup_dcu_lst*/
               struct
               {
                    bup_drv_state_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_state;
               /** cmd_ans from bup_dcu_lst*/
               struct
               {
                    command_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_ans;
               /** dbg from bup_dcu_lst*/
               struct
               {
                    dbg_data_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dbg;
               /** dcu_tel from bup_dcu_lst*/
               struct
               {
                    dcu_telemetry_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dcu_tel;
               /** formular from bup_dcu_lst*/
               struct
               {
                    formular_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } formular;
               /** im_bro_drive_ctrl from bup_dcu_lst*/
               struct
               {
                    im_bro_drive_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } im_bro_drive_ctrl;
               /** msg_ans from bup_dcu_lst*/
               struct
               {
                    msg_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_ans;
               /** prm_ans from bup_dcu_lst*/
               struct
               {
                    parameter_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_ans;
               /** ptp_state from bup_dcu_lst*/
               struct
               {
                    ptp_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } ptp_state;
          } bup_dcu_lst;
          /** Messages from bup_dcu_rfd device*/
          struct {
               /** bup_state from bup_dcu_rfd*/
               struct
               {
                    bup_drv_state_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_state;
               /** cmd_ans from bup_dcu_rfd*/
               struct
               {
                    command_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_ans;
               /** dbg from bup_dcu_rfd*/
               struct
               {
                    dbg_data_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dbg;
               /** dcu_tel from bup_dcu_rfd*/
               struct
               {
                    dcu_telemetry_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dcu_tel;
               /** formular from bup_dcu_rfd*/
               struct
               {
                    formular_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } formular;
               /** im_bro_drive_ctrl from bup_dcu_rfd*/
               struct
               {
                    im_bro_drive_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } im_bro_drive_ctrl;
               /** msg_ans from bup_dcu_rfd*/
               struct
               {
                    msg_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_ans;
               /** prm_ans from bup_dcu_rfd*/
               struct
               {
                    parameter_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_ans;
               /** ptp_state from bup_dcu_rfd*/
               struct
               {
                    ptp_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } ptp_state;
          } bup_dcu_rfd;
          /** Messages from bup_dcu_rrd device*/
          struct {
               /** bup_state from bup_dcu_rrd*/
               struct
               {
                    bup_drv_state_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_state;
               /** cmd_ans from bup_dcu_rrd*/
               struct
               {
                    command_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_ans;
               /** dbg from bup_dcu_rrd*/
               struct
               {
                    dbg_data_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dbg;
               /** dcu_tel from bup_dcu_rrd*/
               struct
               {
                    dcu_telemetry_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dcu_tel;
               /** formular from bup_dcu_rrd*/
               struct
               {
                    formular_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } formular;
               /** im_bro_drive_ctrl from bup_dcu_rrd*/
               struct
               {
                    im_bro_drive_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } im_bro_drive_ctrl;
               /** msg_ans from bup_dcu_rrd*/
               struct
               {
                    msg_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_ans;
               /** prm_ans from bup_dcu_rrd*/
               struct
               {
                    parameter_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_ans;
               /** ptp_state from bup_dcu_rrd*/
               struct
               {
                    ptp_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } ptp_state;
          } bup_dcu_rrd;
          /** Messages from bup_dcu_rst device*/
          struct {
               /** bup_state from bup_dcu_rst*/
               struct
               {
                    bup_drv_state_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_state;
               /** cmd_ans from bup_dcu_rst*/
               struct
               {
                    command_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_ans;
               /** dbg from bup_dcu_rst*/
               struct
               {
                    dbg_data_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dbg;
               /** dcu_tel from bup_dcu_rst*/
               struct
               {
                    dcu_telemetry_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dcu_tel;
               /** formular from bup_dcu_rst*/
               struct
               {
                    formular_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } formular;
               /** im_bro_drive_ctrl from bup_dcu_rst*/
               struct
               {
                    im_bro_drive_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } im_bro_drive_ctrl;
               /** msg_ans from bup_dcu_rst*/
               struct
               {
                    msg_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_ans;
               /** prm_ans from bup_dcu_rst*/
               struct
               {
                    parameter_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_ans;
               /** ptp_state from bup_dcu_rst*/
               struct
               {
                    ptp_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } ptp_state;
          } bup_dcu_rst;
          /** Messages from dcu device*/
          struct {
               /** bup_state from dcu*/
               struct
               {
                    bup_drv_state_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_state;
               /** cmd_ans from dcu*/
               struct
               {
                    command_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_ans;
               /** dbg from dcu*/
               struct
               {
                    dbg_data_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dbg;
               /** dcu_tel from dcu*/
               struct
               {
                    dcu_telemetry_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } dcu_tel;
               /** formular from dcu*/
               struct
               {
                    formular_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } formular;
               /** im_bro_drive_ctrl from dcu*/
               struct
               {
                    im_bro_drive_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } im_bro_drive_ctrl;
               /** msg_ans from dcu*/
               struct
               {
                    msg_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_ans;
               /** prm_ans from dcu*/
               struct
               {
                    parameter_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_ans;
               /** ptp_state from dcu*/
               struct
               {
                    ptp_info_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } ptp_state;
          } dcu;
          /** Messages from im_bro device*/
          struct {
               /** im_bro_drivers_sens from im_bro*/
               struct
               {
                    drivers_sens_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } im_bro_drivers_sens;
               /** prm_ans from im_bro*/
               struct
               {
                    parameter_answer_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_ans;
          } im_bro;
     } in;

     /** mon output messages */
     struct 
     {
          /** bup_srv_ctrl */
          struct 
          {
               bup_drv_control_msg_t *msg;
               mj_msg_state_t (*lock)(mj_msg_state_t state);
               bool tx_enable;
          } bup_srv_ctrl;
          /** cmd_req */
          struct 
          {
               command_request_msg_t *msg;
               void (*tx)(uint16_t);
          } cmd_req;
          /** msg_req */
          struct 
          {
               msg_request_msg_t *msg;
               void (*tx)(uint16_t);
          } msg_req;
          /** prm_req */
          struct 
          {
               parameter_request_msg_t *msg;
               void (*tx)(uint16_t);
          } prm_req;
     } out;
     /** mon parameters */
     struct
     {
          mon_prm_t *ptr;
          mj_prm_status_t  (*write)(int id, void *data);
          mj_prm_status_t  (*read)(int id, void *data);
          const uint32_t * (*list)(uint32_t *size);
          void (*upd_cb)(int id);
     } prm;
     /** Communication loop fcn shold be call in main loop */
     void (*loop)(void);
     /** Communication tic function. must be called once per 250us */
     void (*tick)(void);
}mj_mon_t;

/** MicroJet librarary initialization, should be run once.
 *  Return MJ_OK if all check are passed and all initialization is done coorectly otherwise return MJ_FAIL
 */
mj_status_t mj_mon_init(mj_drv_interface_t *drv, mj_mon_t ** ptr);

#ifdef __cplusplus
}
#endif
#endif /* MON_DEV_SPEC_H */