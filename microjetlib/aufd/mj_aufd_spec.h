#ifndef AUFD_DEV_SPEC_H
#define AUFD_DEV_SPEC_H

#include "mjsysspec.h"
#include "mjutils.h"

#ifdef __cplusplus
 extern "C" {
#endif


typedef struct aufd_prm{
     /** service_mode [-] */
     bool service_mode;
     /** factory_date [-] */
     char factory_date[32];
     /** factory_number [-] */
     char factory_number[32];
     /** description [-] */
     char description[32];
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
} aufd_prm_t;

typedef struct mj_aufd
{
     /** aufd input messages */
     struct
     {
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
          } dcu;
          /** Messages from mon device*/
          struct {
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
          } mon;
     } in;

     /** aufd output messages */
     struct 
     {
          /** bup_ctrl */
          struct 
          {
               bup_drv_control_msg_t *msg;
               void (*tx)(uint16_t);
          } bup_ctrl;
          /** bup_multi_control */
          struct 
          {
               bup_drv_multi_control_msg_t *msg;
               void (*tx)(uint16_t);
          } bup_multi_control;
          /** cmd_ans */
          struct 
          {
               command_answer_msg_t *msg;
               void (*tx)(uint16_t);
          } cmd_ans;
          /** cmd_req */
          struct 
          {
               command_request_msg_t *msg;
               void (*tx)(uint16_t);
          } cmd_req;
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
          /** msg_req */
          struct 
          {
               msg_request_msg_t *msg;
               void (*tx)(uint16_t);
          } msg_req;
          /** prm_ans */
          struct 
          {
               parameter_answer_msg_t *msg;
               void (*tx)(uint16_t);
          } prm_ans;
          /** prm_req */
          struct 
          {
               parameter_request_msg_t *msg;
               void (*tx)(uint16_t);
          } prm_req;
     } out;
     /** aufd parameters */
     struct
     {
          aufd_prm_t *ptr;
          mj_prm_status_t  (*write)(int id, void *data);
          mj_prm_status_t  (*read)(int id, void *data);
          const uint32_t * (*list)(uint32_t *size);
          void (*upd_cb)(int id);
     } prm;
     /** Communication loop fcn shold be call in main loop */
     void (*loop)(void);
     /** Communication tic function. must be called once per 250us */
     void (*tick)(void);
}mj_aufd_t;

/** MicroJet librarary initialization, should be run once.
 *  Return MJ_OK if all check are passed and all initialization is done coorectly otherwise return MJ_FAIL
 */
mj_status_t mj_aufd_init(mj_drv_interface_t *drv, mj_aufd_t ** ptr);

#ifdef __cplusplus
}
#endif
#endif /* AUFD_DEV_SPEC_H */