#ifndef BUP_DCU_LST_DEV_SPEC_H
#define BUP_DCU_LST_DEV_SPEC_H

#include "mjsysspec.h"
#include "mjutils.h"

#ifdef __cplusplus
 extern "C" {
#endif


typedef struct bup_dcu_lst_prm{
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
     /** com_if_bro_bup_srv_mcast [-] */
     char com_if_bro_bup_srv_mcast[32];
     /** com_if_im_bro_drive_mcast [-] */
     char com_if_im_bro_drive_mcast[32];
     /** com_if_im_bro_drive_ctrl_mcast [-] */
     char com_if_im_bro_drive_ctrl_mcast[32];
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
     /** load_speed_kd [-] */
     float load_speed_kd;
     /** load_speed_kt [-] */
     float load_speed_kt;
     /** load_speed_kf [-] */
     float load_speed_kf;
     /** load_speed_err_lim [-] */
     float load_speed_err_lim;
     /** load_speed_out_lim [-] */
     float load_speed_out_lim;
     /** load_speed_out_rate_lim [-] */
     float load_speed_out_rate_lim;
     /** load_speed_err_rate_lim [-] */
     float load_speed_err_rate_lim;
     /** rotor_speed_kp [-] */
     float rotor_speed_kp;
     /** rotor_speed_ki [-] */
     float rotor_speed_ki;
     /** rotor_speed_kd [-] */
     float rotor_speed_kd;
     /** rotor_speed_kt [-] */
     float rotor_speed_kt;
     /** rotor_speed_kf [-] */
     float rotor_speed_kf;
     /** rotor_speed_err_lim [-] */
     float rotor_speed_err_lim;
     /** rotor_speed_out_lim [-] */
     float rotor_speed_out_lim;
     /** rotor_speed_out_rate_lim [-] */
     float rotor_speed_out_rate_lim;
     /** rotor_speed_err_rate_lim [-] */
     float rotor_speed_err_rate_lim;
     /** rotor_ang_kp [-] */
     float rotor_ang_kp;
     /** rotor_ang_ki [-] */
     float rotor_ang_ki;
     /** rotor_ang_kd [-] */
     float rotor_ang_kd;
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
     /** factory_date [-] */
     char factory_date[32];
     /** factory_number [-] */
     char factory_number[32];
     /** description [-] */
     char description[32];
} bup_dcu_lst_prm_t;

typedef struct mj_bup_dcu_lst
{
     /** bup_dcu_lst input messages */
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

     /** bup_dcu_lst output messages */
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
          /** formular */
          struct 
          {
               formular_info_msg_t *msg;
               void (*tx)(uint16_t);
          } formular;
          /** im_bro_drive_ctrl */
          struct 
          {
               im_bro_drive_ctrl_msg_t *msg;
               mj_msg_state_t (*lock)(mj_msg_state_t state);
               bool tx_enable;
          } im_bro_drive_ctrl;
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
     /** bup_dcu_lst parameters */
     struct
     {
          bup_dcu_lst_prm_t *ptr;
          mj_prm_status_t  (*write)(int id, void *data);
          mj_prm_status_t  (*read)(int id, void *data);
          const uint32_t * (*list)(uint32_t *size);
          void (*upd_cb)(int id);
     } prm;
     /** Communication loop fcn shold be call in main loop */
     void (*loop)(void);
     /** Communication tic function. must be called once per 250us */
     void (*tick)(void);
}mj_bup_dcu_lst_t;

/** MicroJet librarary initialization, should be run once.
 *  Return MJ_OK if all check are passed and all initialization is done coorectly otherwise return MJ_FAIL
 */
mj_status_t mj_bup_dcu_lst_init(mj_drv_interface_t *drv, mj_bup_dcu_lst_t ** ptr);

#ifdef __cplusplus
}
#endif
#endif /* BUP_DCU_LST_DEV_SPEC_H */