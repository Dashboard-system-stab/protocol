#ifndef IM_BRO_DEV_SPEC_H
#define IM_BRO_DEV_SPEC_H

#include "mjsysspec.h"
#include "mjutils.h"

#ifdef __cplusplus
 extern "C" {
#endif


typedef struct im_bro_prm{
     /** service_mode [-] */
     bool service_mode;
     /** Vdc [V] */
     float Vdc;
     /** dev_id [-] */
     int dev_id;
     /** com_if_srv_mcast_req [-] */
     char com_if_srv_mcast_req[32];
     /** com_if_srv_mcast_ans [-] */
     char com_if_srv_mcast_ans[32];
     /** com_if_im_bro_drive_mcast [-] */
     char com_if_im_bro_drive_mcast[32];
     /** com_if_im_bro_drive_ctrl_mcast [-] */
     char com_if_im_bro_drive_ctrl_mcast[32];
} im_bro_prm_t;

typedef struct mj_im_bro
{
     /** im_bro input messages */
     struct
     {
          /** Messages from aufd device*/
          struct {
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
          } bup_dcu_lfd;
          /** Messages from bup_dcu_lrd device*/
          struct {
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
          } bup_dcu_lrd;
          /** Messages from bup_dcu_lst device*/
          struct {
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
          } bup_dcu_lst;
          /** Messages from bup_dcu_rfd device*/
          struct {
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
          } bup_dcu_rfd;
          /** Messages from bup_dcu_rrd device*/
          struct {
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
          } bup_dcu_rrd;
          /** Messages from bup_dcu_rst device*/
          struct {
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
          } bup_dcu_rst;
          /** Messages from dcu device*/
          struct {
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
          } dcu;
          /** Messages from mon device*/
          struct {
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

     /** im_bro output messages */
     struct 
     {
          /** im_bro_drivers_sens */
          struct 
          {
               drivers_sens_msg_t *msg;
               mj_msg_state_t (*lock)(mj_msg_state_t state);
               bool tx_enable;
          } im_bro_drivers_sens;
          /** prm_ans */
          struct 
          {
               parameter_answer_msg_t *msg;
               void (*tx)(uint16_t);
          } prm_ans;
     } out;
     /** im_bro parameters */
     struct
     {
          im_bro_prm_t *ptr;
          mj_prm_status_t  (*write)(int id, void *data);
          mj_prm_status_t  (*read)(int id, void *data);
          const uint32_t * (*list)(uint32_t *size);
          void (*upd_cb)(int id);
     } prm;
     /** Communication loop fcn shold be call in main loop */
     void (*loop)(void);
     /** Communication tic function. must be called once per 250us */
     void (*tick)(void);
}mj_im_bro_t;

/** MicroJet librarary initialization, should be run once.
 *  Return MJ_OK if all check are passed and all initialization is done coorectly otherwise return MJ_FAIL
 */
mj_status_t mj_im_bro_init(mj_drv_interface_t *drv, mj_im_bro_t ** ptr);

#ifdef __cplusplus
}
#endif
#endif /* IM_BRO_DEV_SPEC_H */