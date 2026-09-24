
#include "signaltree.h"

static TreeNode *mon_driver_ctrl_ptr = 0;

static TreeNode *driver_state_ptr = 0;

static QStringList devList()
{
    QStringList devs;
	devs.append("mon");
	devs.append("model_bro");
    devs.append("ALL");
    devs.append("NONE");
    return devs;
}

static QVector<int32_t> devIDs()
{
    QVector<int32_t> ids;
	ids.append(0x6C99);
	ids.append(0x3A5E);
    ids.append(0xFFFF);
    ids.append(0);
    return ids;
}

// Convert QString to CP866-encoded char array (QByteArray for simplicity and safety)
static QByteArray qStringToCP866(const QString& input) {
    QTextCodec* codec = QTextCodec::codecForName("IBM866");
    if (!codec) {
        throw std::runtime_error("Failed to find CP866 codec");
    }
    QByteArray result = codec->fromUnicode(input);
    result.append('\0');
    return result;
}

// Convert CP866-encoded char array to QString
static QString cp866ToQString(const char* input, size_t size) {
    QTextCodec* codec = QTextCodec::codecForName("IBM866");
    if (!codec) {
        throw std::runtime_error("Failed to find CP866 codec");
    }
    return codec->toUnicode(input, strnlen(input, size-1));
}

static QVariant prm2QVariant(uint32_t id, uint8_t* val, size_t size)
{
    switch(id){
        case 0xF1C25D6:
            return QVariant(*(int*)val);
 
        case 0x881D02DE:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xBCCBC6F8:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x17EAC676:
            return QVariant(*(int*)val);
 
        default:
            return QVariant();
    }
}

static void QVariant2prm(uint32_t id, uint8_t* val, size_t size, QVariant data)
{
    if (id == 0xF1C25D6)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x881D02DE)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xBCCBC6F8)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x17EAC676)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    {
        
    }
}


TreeNode * create_model_bro_in_tree(mj_model_bro_t * mj_ptr)
{
static mj_model_bro_t *mj = mj_ptr;
TreeNode * node = new TreeNode("INPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
TreeNode * mon_node = node->add("mon",[](){return QVariant();});
mon_node->isDev = true;
mon_driver_ctrl_ptr = node->lch()->add("driver_ctrl",[](){return QVariant(mj->in.mon.driver_ctrl.msg->hdr.cnt);});
mon_driver_ctrl_ptr->state = []()->int32_t{return mj->in.mon.driver_ctrl.state;};
mon_driver_ctrl_ptr->msgId = ID_DRIVER_CTRL;
mon_driver_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.driver_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.driver_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("Ua",[](){return QVariant(mj->in.mon.driver_ctrl.msg->Ua);});
node->lch()->lch()->add("Ub",[](){return QVariant(mj->in.mon.driver_ctrl.msg->Ub);});
node->lch()->lch()->add("Uc",[](){return QVariant(mj->in.mon.driver_ctrl.msg->Uc);});
mj->in.mon.driver_ctrl.upd_cb = [](){ mon_driver_ctrl_ptr->upd(mj->in.mon.driver_ctrl.ts_s, mj->in.mon.driver_ctrl.ts_ns);};
return node;
};


TreeNode * create_model_bro_out_tree(mj_model_bro_t * mj_ptr)
{
static mj_model_bro_t * mj = mj_ptr;
TreeNode * node = new TreeNode("OUTPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
driver_state_ptr = node->add("driver_state",[](){return QVariant(mj->out.driver_state.msg->hdr.cnt);});
driver_state_ptr->tx_enable = &mj->out.driver_state.tx_enable;

node->lch()->add("Ia",[](){return QVariant(mj->out.driver_state.msg->Ia);})->setData =  [](QVariant data){ mj->out.driver_state.msg->Ia=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("Ib",[](){return QVariant(mj->out.driver_state.msg->Ib);})->setData =  [](QVariant data){ mj->out.driver_state.msg->Ib=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("Ic",[](){return QVariant(mj->out.driver_state.msg->Ic);})->setData =  [](QVariant data){ mj->out.driver_state.msg->Ic=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("r_angle",[](){return QVariant(mj->out.driver_state.msg->r_angle);})->setData =  [](QVariant data){ mj->out.driver_state.msg->r_angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("Vdc",[](){return QVariant(mj->out.driver_state.msg->Vdc);})->setData =  [](QVariant data){ mj->out.driver_state.msg->Vdc=data.value<float>();return;};
node->lch()->lch()->editable = true;

return node;
};

TreeNode * create_model_bro_params_tree(mj_model_bro_t * mj_ptr){
static mj_model_bro_t * mj = mj_ptr;
TreeNode * node = new TreeNode("PARAMETERS",[](){return QVariant();});
auto mon_ptr = node->add("mon",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
mon_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
node->lch()->add("type",[](){return QVariant((int32_t)(mj->out.prm_req.msg->type));})->setData =  [](QVariant data){ mj->out.prm_req.msg->type=(parameter_request_type)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("READ");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->values.append("WRITE");
node->lch()->lch()->intval.append(1);
node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.prm_req.msg->id));})->setData =  [](QVariant data){ mj->out.prm_req.msg->id=(uint32_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("service_mode");
node->lch()->lch()->intval.append(0xF1C25D6);
node->lch()->lch()->values.append("com_if_bro_mcast");
node->lch()->lch()->intval.append(0x881D02DE);
node->lch()->lch()->values.append("com_if_mon_mcast");
node->lch()->lch()->intval.append(0xBCCBC6F8);
node->lch()->lch()->values.append("dev_id");
node->lch()->lch()->intval.append(0x17EAC676);
node->lch()->add("val",[](){return QVariant(prm2QVariant(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val)));})->setData =  [](QVariant data){ QVariant2prm(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val),data);return;};
node->lch()->lch()->editable = true;
return node;
};