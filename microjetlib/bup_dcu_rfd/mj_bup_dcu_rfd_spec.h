#ifndef BUP_DCU_RFD_DEV_SPEC_H
#define BUP_DCU_RFD_DEV_SPEC_H

#include "mjsysspec.h"
#include "mjutils.h"

#ifdef __cplusplus
 extern "C" {
#endif


typedef struct bup_dcu_rfd_prm{
     /** dev_id [-] */
     int dev_id;
     /** com_if_srv_mcast_req [-] */
     char com_if_srv_mcast_req[32];
     /** com_if_srv_mcast_ans [-] */
     char com_if_srv_mcast_ans[32];
     /** com_if_bro_bup_ctrl_mcast [-] */
     char com_if_bro_bup_ctrl_mcast[32];
     /** com_if_bro_bup_data_mcast [-] */
     char com_if_bro_bup_data_mcast[32];
     /** com_if_bup_internal_mcast [-] */
     char com_if_bup_internal_mcast[32];
     /** com_if_bro_bup_srv_mcast [-] */
     char com_if_bro_bup_srv_mcast[32];
     /** com_if_im_bro_drive_mcast [-] */
     char com_if_im_bro_drive_mcast[32];
     /** service_mode [-] */
     bool service_mode;
     /** dbg_mode [-] */
     bool dbg_mode;
     /** ptp_stat [-] */
     bool ptp_stat;
     /** vdc_scale [-] */
     float vdc_scale;
     /** ocp_lvl [A] */
     float ocp_lvl;
     /** cur_lim [A] */
     float cur_lim;
     /** drv_ang_reverse [-] */
     bool drv_ang_reverse;
     /** drv_current_reverse [-] */
     bool drv_current_reverse;
     /** drv_voltage_reverse [-] */
     bool drv_voltage_reverse;
     /** drv_zero [rad] */
     float drv_zero;
     /** vdc_min [V] */
     float vdc_min;
     /** im_mode [-] */
     bool im_mode;
     /** ptp_kp [-] */
     float ptp_kp;
     /** ptp_ki [-] */
     float ptp_ki;
     /** ptp_kd [-] */
     float ptp_kd;
     /** ohp_lvl [C] */
     float ohp_lvl;
     /** ohp_hyst [C] */
     float ohp_hyst;
     /** el_zero [rad] */
     float el_zero;
     /** pole_pairs [-] */
     int pole_pairs;
     /** ph_resistance [-] */
     float ph_resistance;
     /** ph_inductance [-] */
     float ph_inductance;
     /** brake_unlock_voltage [V] */
     float brake_unlock_voltage;
     /** brake_unlock_time [ms] */
     int brake_unlock_time;
     /** brake_hold_voltage [V] */
     float brake_hold_voltage;
     /** brake_lock_time [ms] */
     int brake_lock_time;
     /** curr_kp [-] */
     float curr_kp;
     /** curr_ki [-] */
     float curr_ki;
     /** curr_kb [-] */
     float curr_kb;
     /** curr_kt [-] */
     float curr_kt;
     /** curr_kf [-] */
     float curr_kf;
     /** curr_fc [-] */
     float curr_fc;
     /** curr_err_lim [-] */
     float curr_err_lim;
     /** curr_out_lim [-] */
     float curr_out_lim;
     /** curr_out_rate_lim [-] */
     float curr_out_rate_lim;
     /** curr_err_rate_lim [-] */
     float curr_err_rate_lim;
     /** load_speed_kp [-] */
     float load_speed_kp;
     /** load_speed_ki [-] */
     float load_speed_ki;
     /** load_speed_kb [-] */
     float load_speed_kb;
     /** load_speed_kt [-] */
     float load_speed_kt;
     /** load_speed_kf [-] */
     float load_speed_kf;
     /** load_speed_err_lim [-] */
     float load_speed_err_lim;
     /** load_speed_out_lim [-] */
     float load_speed_out_lim;
     /** load_speed_int_lim [-] */
     float load_speed_int_lim;
     /** load_speed_out_rate_lim [-] */
     float load_speed_out_rate_lim;
     /** load_speed_err_rate_lim [-] */
     float load_speed_err_rate_lim;
     /** load_speed_flt_fc [-] */
     float load_speed_flt_fc;
     /** rotor_speed_flt_fc [-] */
     float rotor_speed_flt_fc;
     /** load_ang_kp [-] */
     float load_ang_kp;
     /** load_ang_ki [-] */
     float load_ang_ki;
     /** load_ang_kb [-] */
     float load_ang_kb;
     /** load_ang_kt [-] */
     float load_ang_kt;
     /** load_ang_kf [-] */
     float load_ang_kf;
     /** load_ang_rev [-] */
     bool load_ang_rev;
     /** load_ang_kd [-] */
     float load_ang_kd;
     /** load_ang_err_lim [-] */
     float load_ang_err_lim;
     /** load_ang_out_lim [-] */
     float load_ang_out_lim;
     /** load_ang_out_rate_lim [-] */
     float load_ang_out_rate_lim;
     /** load_ang_err_rate_lim [-] */
     float load_ang_err_rate_lim;
     /** load_ang_dz [rad] */
     float load_ang_dz;
     /** load_ang_dz_en [-] */
     bool load_ang_dz_en;
     /** rotor_speed_kp [-] */
     float rotor_speed_kp;
     /** rotor_speed_ki [-] */
     float rotor_speed_ki;
     /** rotor_speed_kb [-] */
     float rotor_speed_kb;
     /** rotor_speed_kt [-] */
     float rotor_speed_kt;
     /** rotor_speed_kf [-] */
     float rotor_speed_kf;
     /** rotor_speed_err_lim [-] */
     float rotor_speed_err_lim;
     /** rotor_speed_out_lim [-] */
     float rotor_speed_out_lim;
     /** rotor_speed_int_lim [-] */
     float rotor_speed_int_lim;
     /** rotor_speed_out_rate_lim [-] */
     float rotor_speed_out_rate_lim;
     /** rotor_speed_err_rate_lim [-] */
     float rotor_speed_err_rate_lim;
     /** rotor_speed_master_common_kp [-] */
     float rotor_speed_master_common_kp;
     /** rotor_speed_master_common_ki [-] */
     float rotor_speed_master_common_ki;
     /** rotor_speed_master_common_kb [-] */
     float rotor_speed_master_common_kb;
     /** rotor_speed_master_common_kt [-] */
     float rotor_speed_master_common_kt;
     /** rotor_speed_master_common_kf [-] */
     float rotor_speed_master_common_kf;
     /** rotor_speed_master_common_err_lim [-] */
     float rotor_speed_master_common_err_lim;
     /** rotor_speed_master_common_out_lim [-] */
     float rotor_speed_master_common_out_lim;
     /** rotor_speed_master_common_int_lim [-] */
     float rotor_speed_master_common_int_lim;
     /** rotor_speed_master_common_out_rate_lim [-] */
     float rotor_speed_master_common_out_rate_lim;
     /** rotor_speed_master_common_err_rate_lim [-] */
     float rotor_speed_master_common_err_rate_lim;
     /** rotor_speed_master_diff_kp [-] */
     float rotor_speed_master_diff_kp;
     /** rotor_speed_master_diff_ki [-] */
     float rotor_speed_master_diff_ki;
     /** rotor_speed_master_diff_kb [-] */
     float rotor_speed_master_diff_kb;
     /** rotor_speed_master_diff_kt [-] */
     float rotor_speed_master_diff_kt;
     /** rotor_speed_master_diff_kf [-] */
     float rotor_speed_master_diff_kf;
     /** rotor_speed_master_diff_err_lim [-] */
     float rotor_speed_master_diff_err_lim;
     /** rotor_speed_master_diff_out_lim [-] */
     float rotor_speed_master_diff_out_lim;
     /** rotor_speed_master_diff_int_lim [-] */
     float rotor_speed_master_diff_int_lim;
     /** rotor_speed_master_diff_out_rate_lim [-] */
     float rotor_speed_master_diff_out_rate_lim;
     /** rotor_speed_master_diff_err_rate_lim [-] */
     float rotor_speed_master_diff_err_rate_lim;
     /** rotor_speed_role [-] */
     int rotor_speed_role;
     /** rotor_ang_kp [-] */
     float rotor_ang_kp;
     /** rotor_ang_ki [-] */
     float rotor_ang_ki;
     /** rotor_ang_kb [-] */
     float rotor_ang_kb;
     /** rotor_ang_kt [-] */
     float rotor_ang_kt;
     /** rotor_ang_kf [-] */
     float rotor_ang_kf;
     /** rotor_ang_err_lim [-] */
     float rotor_ang_err_lim;
     /** rotor_ang_out_lim [-] */
     float rotor_ang_out_lim;
     /** rotor_ang_out_rate_lim [-] */
     float rotor_ang_out_rate_lim;
     /** rotor_ang_err_rate_lim [-] */
     float rotor_ang_err_rate_lim;
     /** rotor_ang_dz [rad] */
     float rotor_ang_dz;
     /** rotor_ang_dz_en [-] */
     bool rotor_ang_dz_en;
     /** factory_date [-] */
     char factory_date[32];
     /** factory_number [-] */
     char factory_number[32];
     /** description [-] */
     char description[32];
} bup_dcu_rfd_prm_t;

typedef struct mj_bup_dcu_rfd
{
     /** bup_dcu_rfd input messages */
     struct
     {
          /** Messages from aufd device*/
          struct {
               /** bup_ctrl from aufd*/
               struct
               {
                    bup_drv_control_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_ctrl;
               /** bup_multi_control from aufd*/
               struct
               {
                    bup_drv_multi_control_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_multi_control;
               /** cmd_req from aufd*/
               struct
               {
                    command_request_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_req;
               /** msg_req from aufd*/
               struct
               {
                    msg_request_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_req;
               /** prm_req from aufd*/
               struct
               {
                    parameter_request_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_req;
          } aufd;
          /** Messages from bup_dcu_lfd device*/
          struct {
               /** drive_master_ctrl from bup_dcu_lfd*/
               struct
               {
                    drive_master_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_master_ctrl;
               /** drive_slave_fb from bup_dcu_lfd*/
               struct
               {
                    drive_slave_fb_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_slave_fb;
          } bup_dcu_lfd;
          /** Messages from bup_dcu_lrd device*/
          struct {
               /** drive_master_ctrl from bup_dcu_lrd*/
               struct
               {
                    drive_master_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_master_ctrl;
               /** drive_slave_fb from bup_dcu_lrd*/
               struct
               {
                    drive_slave_fb_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_slave_fb;
          } bup_dcu_lrd;
          /** Messages from bup_dcu_lst device*/
          struct {
               /** drive_master_ctrl from bup_dcu_lst*/
               struct
               {
                    drive_master_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_master_ctrl;
               /** drive_slave_fb from bup_dcu_lst*/
               struct
               {
                    drive_slave_fb_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_slave_fb;
          } bup_dcu_lst;
          /** Messages from bup_dcu_rrd device*/
          struct {
               /** drive_master_ctrl from bup_dcu_rrd*/
               struct
               {
                    drive_master_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_master_ctrl;
               /** drive_slave_fb from bup_dcu_rrd*/
               struct
               {
                    drive_slave_fb_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_slave_fb;
          } bup_dcu_rrd;
          /** Messages from bup_dcu_rst device*/
          struct {
               /** drive_master_ctrl from bup_dcu_rst*/
               struct
               {
                    drive_master_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_master_ctrl;
               /** drive_slave_fb from bup_dcu_rst*/
               struct
               {
                    drive_slave_fb_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_slave_fb;
          } bup_dcu_rst;
          /** Messages from dcu device*/
          struct {
               /** drive_master_ctrl from dcu*/
               struct
               {
                    drive_master_ctrl_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_master_ctrl;
               /** drive_slave_fb from dcu*/
               struct
               {
                    drive_slave_fb_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } drive_slave_fb;
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
          } im_bro;
          /** Messages from mon device*/
          struct {
               /** bup_multi_control from mon*/
               struct
               {
                    bup_drv_multi_control_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_multi_control;
               /** bup_srv_ctrl from mon*/
               struct
               {
                    bup_drv_control_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } bup_srv_ctrl;
               /** cmd_req from mon*/
               struct
               {
                    command_request_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } cmd_req;
               /** msg_req from mon*/
               struct
               {
                    msg_request_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } msg_req;
               /** prm_req from mon*/
               struct
               {
                    parameter_request_msg_t *msg;
                    void (*copy)(void *dst);
                    void (*upd_cb)(void);
                    void (*irq)(void *);
                    mj_msg_state_t (*lock)(mj_msg_state_t state);
                    mj_msg_state_t state;
                    uint32_t *total;
                    uint32_t *miss;
                    uint32_t ts_s;
                    uint32_t ts_ns;
               } prm_req;
          } mon;
     } in;

     /** bup_dcu_rfd output messages */
     struct 
     {
          /** bup_state */
          struct 
          {
               bup_drv_state_msg_t *msg;
               void (*tx)(uint16_t);
          } bup_state;
          /** cmd_ans */
          struct 
          {
               command_answer_msg_t *msg;
               void (*tx)(uint16_t);
          } cmd_ans;
          /** dbg */
          struct 
          {
               dbg_data_msg_t *msg;
               mj_msg_state_t (*lock)(mj_msg_state_t state);
               bool tx_enable;
          } dbg;
          /** dcu_tel */
          struct 
          {
               dcu_telemetry_msg_t *msg;
               mj_msg_state_t (*lock)(mj_msg_state_t state);
               bool tx_enable;
          } dcu_tel;
          /** drive_master_ctrl */
          struct 
          {
               drive_master_ctrl_msg_t *msg;
               mj_msg_state_t (*lock)(mj_msg_state_t state);
               bool tx_enable;
          } drive_master_ctrl;
          /** drive_slave_fb */
          struct 
          {
               drive_slave_fb_msg_t *msg;
               mj_msg_state_t (*lock)(mj_msg_state_t state);
               bool tx_enable;
          } drive_slave_fb;
          /** formular */
          struct 
          {
               formular_info_msg_t *msg;
               void (*tx)(uint16_t);
          } formular;
          /** msg_ans */
          struct 
          {
               msg_answer_msg_t *msg;
               void (*tx)(uint16_t);
          } msg_ans;
          /** prm_ans */
          struct 
          {
               parameter_answer_msg_t *msg;
               void (*tx)(uint16_t);
          } prm_ans;
          /** ptp_state */
          struct 
          {
               ptp_info_msg_t *msg;
               mj_msg_state_t (*lock)(mj_msg_state_t state);
               bool tx_enable;
          } ptp_state;
     } out;
     /** bup_dcu_rfd parameters */
     struct
     {
          bup_dcu_rfd_prm_t *ptr;
          mj_prm_status_t  (*write)(int id, void *data);
          mj_prm_status_t  (*read)(int id, void *data);
          const uint32_t * (*list)(uint32_t *size);
          void (*upd_cb)(int id);
     } prm;
     /** Communication loop fcn shold be call in main loop */
     void (*loop)(void);
     /** Communication tic function. must be called once per 250us */
     void (*tick)(void);
}mj_bup_dcu_rfd_t;

/** MicroJet librarary initialization, should be run once.
 *  Return MJ_OK if all check are passed and all initialization is done coorectly otherwise return MJ_FAIL
 */
mj_status_t mj_bup_dcu_rfd_init(mj_drv_interface_t *drv, mj_bup_dcu_rfd_t ** ptr);

#ifdef __cplusplus
}
#endif
#endif /* BUP_DCU_RFD_DEV_SPEC_H */