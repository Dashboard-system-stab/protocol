
#include "signaltree.h"

static TreeNode *aufd_bup_ctrl_ptr = 0;
static TreeNode *aufd_cmd_req_ptr = 0;
static TreeNode *aufd_msg_req_ptr = 0;
static TreeNode *aufd_prm_req_ptr = 0;
static TreeNode *im_bro_im_bro_drivers_sens_ptr = 0;
static TreeNode *mon_bup_srv_ctrl_ptr = 0;
static TreeNode *mon_cmd_req_ptr = 0;
static TreeNode *mon_msg_req_ptr = 0;
static TreeNode *mon_prm_req_ptr = 0;

static TreeNode *bup_state_ptr = 0;
static TreeNode *cmd_ans_ptr = 0;
static TreeNode *dbg_ptr = 0;
static TreeNode *dcu_tel_ptr = 0;
static TreeNode *formular_ptr = 0;
static TreeNode *im_bro_drive_ctrl_ptr = 0;
static TreeNode *msg_ans_ptr = 0;
static TreeNode *prm_ans_ptr = 0;
static TreeNode *ptp_state_ptr = 0;

static QStringList devList()
{
    QStringList devs;
	devs.append("aufd");
	devs.append("dcu");
	devs.append("bup_dcu_lfd");
	devs.append("bup_dcu_rfd");
	devs.append("bup_dcu_lrd");
	devs.append("bup_dcu_rrd");
	devs.append("bup_dcu_lst");
	devs.append("bup_dcu_rst");
	devs.append("mon");
	devs.append("im_bro");
    devs.append("ALL");
    devs.append("NONE");
    return devs;
}

static QVector<int32_t> devIDs()
{
    QVector<int32_t> ids;
	ids.append(0xF5B6);
	ids.append(0xB8FE);
	ids.append(0xFA82);
	ids.append(0xD334);
	ids.append(0x57F6);
	ids.append(0x7E40);
	ids.append(0x7659);
	ids.append(0x5FEF);
	ids.append(0x6C99);
	ids.append(0x1D4C);
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
        case 0x311FD2BA:
            return QVariant(*(bool*)val);
 
        case 0x84A7BB67:
            return QVariant(*(bool*)val);
 
        case 0xC17D8050:
            return QVariant(*(bool*)val);
 
        case 0x7F45547:
            return QVariant(*(float*)val);
 
        case 0xF366F564:
            return QVariant(*(float*)val);
 
        case 0x800F3056:
            return QVariant(*(float*)val);
 
        case 0x4A0AB355:
            return QVariant(*(float*)val);
 
        case 0x55DA9773:
            return QVariant(*(float*)val);
 
        case 0x5C57D2B7:
            return QVariant(*(float*)val);
 
        case 0x501D05A4:
            return QVariant(*(float*)val);
 
        case 0x54F313B1:
            return QVariant(*(bool*)val);
 
        case 0xFC9F76B6:
            return QVariant(*(bool*)val);
 
        case 0x310908E7:
            return QVariant(*(bool*)val);
 
        case 0x74C112A:
            return QVariant(*(float*)val);
 
        case 0x12DB50AA:
            return QVariant(*(float*)val);
 
        case 0xA57FD22E:
            return QVariant(*(float*)val);
 
        case 0x393E0A69:
            return QVariant(*(int*)val);
 
        case 0xD478FE43:
            return QVariant(*(float*)val);
 
        case 0x5B351473:
            return QVariant(*(float*)val);
 
        case 0x920D8F3B:
            return QVariant(*(float*)val);
 
        case 0xD31E0ACB:
            return QVariant(*(int*)val);
 
        case 0x64399A99:
            return QVariant(*(float*)val);
 
        case 0x955BB624:
            return QVariant(*(int*)val);
 
        case 0x323FC775:
            return QVariant(*(float*)val);
 
        case 0x16A9255D:
            return QVariant(*(float*)val);
 
        case 0x80056521:
            return QVariant(*(float*)val);
 
        case 0xAD5D6E6E:
            return QVariant(*(float*)val);
 
        case 0x1F67CC3A:
            return QVariant(*(float*)val);
 
        case 0x9841D378:
            return QVariant(*(float*)val);
 
        case 0xCAF1DD24:
            return QVariant(*(float*)val);
 
        case 0x8D2D0B70:
            return QVariant(*(float*)val);
 
        case 0x41824DD2:
            return QVariant(*(float*)val);
 
        case 0x6EFAD7A0:
            return QVariant(*(float*)val);
 
        case 0x44EE1601:
            return QVariant(*(float*)val);
 
        case 0x6078F429:
            return QVariant(*(float*)val);
 
        case 0xA6070C18:
            return QVariant(*(float*)val);
 
        case 0xDB8CBF1A:
            return QVariant(*(float*)val);
 
        case 0x69B61D4E:
            return QVariant(*(float*)val);
 
        case 0xDA07EA66:
            return QVariant(*(float*)val);
 
        case 0x9DDB3C32:
            return QVariant(*(float*)val);
 
        case 0x4608CFD6:
            return QVariant(*(float*)val);
 
        case 0x697055A4:
            return QVariant(*(float*)val);
 
        case 0x53930154:
            return QVariant(*(float*)val);
 
        case 0x7705E37C:
            return QVariant(*(float*)val);
 
        case 0xB17A1B4D:
            return QVariant(*(float*)val);
 
        case 0xCCF1A84F:
            return QVariant(*(float*)val);
 
        case 0x7ECB0A1B:
            return QVariant(*(float*)val);
 
        case 0xA2564CDF:
            return QVariant(*(float*)val);
 
        case 0xE58A9A8B:
            return QVariant(*(float*)val);
 
        case 0x86EE36E2:
            return QVariant(*(float*)val);
 
        case 0xA996AC90:
            return QVariant(*(float*)val);
 
        case 0xBF7D3892:
            return QVariant(*(float*)val);
 
        case 0x9BEBDABA:
            return QVariant(*(float*)val);
 
        case 0x5D94228B:
            return QVariant(*(float*)val);
 
        case 0x201F9189:
            return QVariant(*(float*)val);
 
        case 0x922533DD:
            return QVariant(*(float*)val);
 
        case 0x74081F2D:
            return QVariant(*(float*)val);
 
        case 0x33D4C979:
            return QVariant(*(float*)val);
 
        case 0x28CABE88:
            return QVariant(*(float*)val);
 
        case 0x7B224FA:
            return QVariant(*(float*)val);
 
        case 0xE54327C5:
            return QVariant(*(bool*)val);
 
        case 0x70B25BB3:
            return QVariant(*(float*)val);
 
        case 0x5424B99B:
            return QVariant(*(float*)val);
 
        case 0x925B41AA:
            return QVariant(*(float*)val);
 
        case 0xA92645D2:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xC8EE09D4:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x4D7787A8:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x4DDDD1EE:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x52F653D2:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xDDFE2DA4:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x6F0DA7DD:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x6F720C87:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x64B26340:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x3C3707BD:
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
    if (id == 0x311FD2BA)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x84A7BB67)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xC17D8050)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x7F45547)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xF366F564)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x800F3056)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4A0AB355)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x55DA9773)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5C57D2B7)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x501D05A4)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x54F313B1)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xFC9F76B6)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x310908E7)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x74C112A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x12DB50AA)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA57FD22E)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x393E0A69)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xD478FE43)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5B351473)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x920D8F3B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD31E0ACB)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x64399A99)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x955BB624)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x323FC775)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x16A9255D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x80056521)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xAD5D6E6E)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x1F67CC3A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9841D378)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xCAF1DD24)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8D2D0B70)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x41824DD2)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x6EFAD7A0)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x44EE1601)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x6078F429)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA6070C18)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xDB8CBF1A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x69B61D4E)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xDA07EA66)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9DDB3C32)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4608CFD6)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x697055A4)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x53930154)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7705E37C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xB17A1B4D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xCCF1A84F)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7ECB0A1B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA2564CDF)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE58A9A8B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x86EE36E2)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA996AC90)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xBF7D3892)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9BEBDABA)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5D94228B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x201F9189)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x922533DD)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x74081F2D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x33D4C979)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x28CABE88)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7B224FA)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE54327C5)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x70B25BB3)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5424B99B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x925B41AA)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA92645D2)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xC8EE09D4)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x4D7787A8)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x4DDDD1EE)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x52F653D2)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xDDFE2DA4)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x6F0DA7DD)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x6F720C87)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x64B26340)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x3C3707BD)
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


TreeNode * create_dcu_in_tree(mj_dcu_t * mj_ptr)
{
static mj_dcu_t *mj = mj_ptr;
TreeNode * node = new TreeNode("INPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
TreeNode * aufd_node = node->add("aufd",[](){return QVariant();});
aufd_node->isDev = true;
aufd_bup_ctrl_ptr = node->lch()->add("bup_ctrl",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->hdr.cnt);});
aufd_bup_ctrl_ptr->state = []()->int32_t{return mj->in.aufd.bup_ctrl.state;};
aufd_bup_ctrl_ptr->msgId = ID_BUP_CTRL;
aufd_bup_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.bup_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.bup_ctrl.msg->hdr.ts_ns)/1e9);});

aufd_bup_ctrl_ptr->isReq = true;
aufd_bup_ctrl_ptr->srcId = BRO30_AUFD;
node->lch()->lch()->add("dr",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.aufd.bup_ctrl.msg->dr.mode));},[](){return (drv_ctrl_mode_str(mj->in.aufd.bup_ctrl.msg->dr.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->dr.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->dr.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->dr.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->dr.current);});
mj->in.aufd.bup_ctrl.upd_cb = [](){ aufd_bup_ctrl_ptr->upd(mj->in.aufd.bup_ctrl.ts_s, mj->in.aufd.bup_ctrl.ts_ns);};
aufd_cmd_req_ptr = node->lch()->add("cmd_req",[](){return QVariant(mj->in.aufd.cmd_req.msg->hdr.cnt);});
aufd_cmd_req_ptr->state = []()->int32_t{return mj->in.aufd.cmd_req.state;};
aufd_cmd_req_ptr->msgId = ID_CMD_REQ;
aufd_cmd_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.cmd_req.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.cmd_req.msg->hdr.ts_ns)/1e9);});

aufd_cmd_req_ptr->isReq = true;
aufd_cmd_req_ptr->srcId = BRO30_AUFD;
node->lch()->lch()->add("type",[](){return QVariant((int32_t)(mj->in.aufd.cmd_req.msg->type));},[](){return (command_type_str(mj->in.aufd.cmd_req.msg->type));});
mj->in.aufd.cmd_req.upd_cb = [](){ aufd_cmd_req_ptr->upd(mj->in.aufd.cmd_req.ts_s, mj->in.aufd.cmd_req.ts_ns);};
aufd_msg_req_ptr = node->lch()->add("msg_req",[](){return QVariant(mj->in.aufd.msg_req.msg->hdr.cnt);});
aufd_msg_req_ptr->state = []()->int32_t{return mj->in.aufd.msg_req.state;};
aufd_msg_req_ptr->msgId = ID_MSG_REQ;
aufd_msg_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.msg_req.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.msg_req.msg->hdr.ts_ns)/1e9);});

aufd_msg_req_ptr->isReq = true;
aufd_msg_req_ptr->srcId = BRO30_AUFD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.aufd.msg_req.msg->id));},[](){return (mj_get_msg_name(mj->in.aufd.msg_req.msg->id));});
mj->in.aufd.msg_req.upd_cb = [](){ aufd_msg_req_ptr->upd(mj->in.aufd.msg_req.ts_s, mj->in.aufd.msg_req.ts_ns);};
aufd_prm_req_ptr = node->lch()->add("prm_req",[](){return QVariant(mj->in.aufd.prm_req.msg->hdr.cnt);});
aufd_prm_req_ptr->state = []()->int32_t{return mj->in.aufd.prm_req.state;};
aufd_prm_req_ptr->msgId = ID_PRM_REQ;
aufd_prm_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.prm_req.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.prm_req.msg->hdr.ts_ns)/1e9);});

aufd_prm_req_ptr->isReq = true;
aufd_prm_req_ptr->srcId = BRO30_AUFD;
node->lch()->lch()->add("type",[](){return QVariant((int32_t)(mj->in.aufd.prm_req.msg->type));},[](){return (parameter_request_type_str(mj->in.aufd.prm_req.msg->type));});
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.aufd.prm_req.msg->id));},[](){return (mj_get_prm_name(mj->in.aufd.prm_req.msg->id));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.aufd.prm_req.msg->id,(uint8_t*)mj->in.aufd.prm_req.msg->val,sizeof(mj->in.aufd.prm_req.msg->val)));});
mj->in.aufd.prm_req.upd_cb = [](){ aufd_prm_req_ptr->upd(mj->in.aufd.prm_req.ts_s, mj->in.aufd.prm_req.ts_ns);};
TreeNode * im_bro_node = node->add("im_bro",[](){return QVariant();});
im_bro_node->isDev = true;
im_bro_im_bro_drivers_sens_ptr = node->lch()->add("im_bro_drivers_sens",[](){return QVariant(mj->in.im_bro.im_bro_drivers_sens.msg->hdr.cnt);});
im_bro_im_bro_drivers_sens_ptr->state = []()->int32_t{return mj->in.im_bro.im_bro_drivers_sens.state;};
im_bro_im_bro_drivers_sens_ptr->msgId = ID_IM_BRO_DRIVERS_SENS;
im_bro_im_bro_drivers_sens_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.im_bro.im_bro_drivers_sens.msg->hdr.ts_s)+static_cast<double>(mj->in.im_bro.im_bro_drivers_sens.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("currents_gn",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.im_bro.im_bro_drivers_sens.msg->currents_gn[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.im_bro.im_bro_drivers_sens.msg->currents_gn[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.im_bro.im_bro_drivers_sens.msg->currents_gn[2]);});
node->lch()->lch()->add("rotor_angle_gn",[](){return QVariant(mj->in.im_bro.im_bro_drivers_sens.msg->rotor_angle_gn);});
node->lch()->lch()->add("v_nom",[](){return QVariant(mj->in.im_bro.im_bro_drivers_sens.msg->v_nom);});
mj->in.im_bro.im_bro_drivers_sens.upd_cb = [](){ im_bro_im_bro_drivers_sens_ptr->upd(mj->in.im_bro.im_bro_drivers_sens.ts_s, mj->in.im_bro.im_bro_drivers_sens.ts_ns);};
TreeNode * mon_node = node->add("mon",[](){return QVariant();});
mon_node->isDev = true;
mon_bup_srv_ctrl_ptr = node->lch()->add("bup_srv_ctrl",[](){return QVariant(mj->in.mon.bup_srv_ctrl.msg->hdr.cnt);});
mon_bup_srv_ctrl_ptr->state = []()->int32_t{return mj->in.mon.bup_srv_ctrl.state;};
mon_bup_srv_ctrl_ptr->msgId = ID_BUP_SRV_CTRL;
mon_bup_srv_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.bup_srv_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.bup_srv_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("dr",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.bup_srv_ctrl.msg->dr.mode));},[](){return (drv_ctrl_mode_str(mj->in.mon.bup_srv_ctrl.msg->dr.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.mon.bup_srv_ctrl.msg->dr.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.mon.bup_srv_ctrl.msg->dr.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.mon.bup_srv_ctrl.msg->dr.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.mon.bup_srv_ctrl.msg->dr.current);});
mj->in.mon.bup_srv_ctrl.upd_cb = [](){ mon_bup_srv_ctrl_ptr->upd(mj->in.mon.bup_srv_ctrl.ts_s, mj->in.mon.bup_srv_ctrl.ts_ns);};
mon_cmd_req_ptr = node->lch()->add("cmd_req",[](){return QVariant(mj->in.mon.cmd_req.msg->hdr.cnt);});
mon_cmd_req_ptr->state = []()->int32_t{return mj->in.mon.cmd_req.state;};
mon_cmd_req_ptr->msgId = ID_CMD_REQ;
mon_cmd_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.cmd_req.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.cmd_req.msg->hdr.ts_ns)/1e9);});

mon_cmd_req_ptr->isReq = true;
mon_cmd_req_ptr->srcId = BRO30_MON;
node->lch()->lch()->add("type",[](){return QVariant((int32_t)(mj->in.mon.cmd_req.msg->type));},[](){return (command_type_str(mj->in.mon.cmd_req.msg->type));});
mj->in.mon.cmd_req.upd_cb = [](){ mon_cmd_req_ptr->upd(mj->in.mon.cmd_req.ts_s, mj->in.mon.cmd_req.ts_ns);};
mon_msg_req_ptr = node->lch()->add("msg_req",[](){return QVariant(mj->in.mon.msg_req.msg->hdr.cnt);});
mon_msg_req_ptr->state = []()->int32_t{return mj->in.mon.msg_req.state;};
mon_msg_req_ptr->msgId = ID_MSG_REQ;
mon_msg_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.msg_req.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.msg_req.msg->hdr.ts_ns)/1e9);});

mon_msg_req_ptr->isReq = true;
mon_msg_req_ptr->srcId = BRO30_MON;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.mon.msg_req.msg->id));},[](){return (mj_get_msg_name(mj->in.mon.msg_req.msg->id));});
mj->in.mon.msg_req.upd_cb = [](){ mon_msg_req_ptr->upd(mj->in.mon.msg_req.ts_s, mj->in.mon.msg_req.ts_ns);};
mon_prm_req_ptr = node->lch()->add("prm_req",[](){return QVariant(mj->in.mon.prm_req.msg->hdr.cnt);});
mon_prm_req_ptr->state = []()->int32_t{return mj->in.mon.prm_req.state;};
mon_prm_req_ptr->msgId = ID_PRM_REQ;
mon_prm_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.prm_req.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.prm_req.msg->hdr.ts_ns)/1e9);});

mon_prm_req_ptr->isReq = true;
mon_prm_req_ptr->srcId = BRO30_MON;
node->lch()->lch()->add("type",[](){return QVariant((int32_t)(mj->in.mon.prm_req.msg->type));},[](){return (parameter_request_type_str(mj->in.mon.prm_req.msg->type));});
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.mon.prm_req.msg->id));},[](){return (mj_get_prm_name(mj->in.mon.prm_req.msg->id));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.mon.prm_req.msg->id,(uint8_t*)mj->in.mon.prm_req.msg->val,sizeof(mj->in.mon.prm_req.msg->val)));});
mj->in.mon.prm_req.upd_cb = [](){ mon_prm_req_ptr->upd(mj->in.mon.prm_req.ts_s, mj->in.mon.prm_req.ts_ns);};
return node;
};


TreeNode * create_dcu_out_tree(mj_dcu_t * mj_ptr)
{
static mj_dcu_t * mj = mj_ptr;
TreeNode * node = new TreeNode("OUTPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
bup_state_ptr = node->add("bup_state",[](){return QVariant(mj->out.bup_state.msg->hdr.cnt);});
bup_state_ptr->tx = [](uint16_t dst){mj->out.bup_state.tx(dst);};

node->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.bup_state.msg->mode));},[](){return (drv_ctrl_mode_str(mj->out.bup_state.msg->mode));})->setData =  [](QVariant data){ mj->out.bup_state.msg->mode=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FREEMOVE");
node->lch()->lch()->values.append("HOLD");
node->lch()->lch()->values.append("ANGLE");
node->lch()->lch()->values.append("SPEED");
node->lch()->lch()->values.append("RSPEED");
node->lch()->lch()->values.append("VOLTAGE");
node->lch()->lch()->values.append("SYNCHRO");
node->lch()->lch()->values.append("CURRENT");
node->lch()->lch()->values.append("VOLTAGE_A");
node->lch()->lch()->values.append("VOLTAGE_B");
node->lch()->lch()->values.append("VOLTAGE_C");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(6);
node->lch()->lch()->intval.append(7);
node->lch()->lch()->intval.append(8);
node->lch()->lch()->intval.append(9);
node->lch()->lch()->intval.append(10);
node->lch()->lch()->intval.append(11);
node->lch()->lch()->intval.append(12);
node->lch()->add("error",[](){return QVariant((int32_t)(mj->out.bup_state.msg->error));},[](){return (drv_ctrl_error_str(mj->out.bup_state.msg->error));})->setData =  [](QVariant data){ mj->out.bup_state.msg->error=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("NONE");
node->lch()->lch()->values.append("BLOCK");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("POWER");
node->lch()->lch()->values.append("CTRL");
node->lch()->lch()->values.append("OLP");
node->lch()->lch()->values.append("OCP");
node->lch()->lch()->values.append("UVP");
node->lch()->lch()->values.append("SCP");
node->lch()->lch()->values.append("MODE");
node->lch()->lch()->values.append("INV");
node->lch()->lch()->values.append("LANG");
node->lch()->lch()->values.append("RANG");
node->lch()->lch()->values.append("OHP");
node->lch()->lch()->values.append("BRAKE");
node->lch()->lch()->values.append("ROTOR_SENS");
node->lch()->lch()->values.append("MCON");
node->lch()->lch()->values.append("SERVICE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(6);
node->lch()->lch()->intval.append(7);
node->lch()->lch()->intval.append(8);
node->lch()->lch()->intval.append(9);
node->lch()->lch()->intval.append(10);
node->lch()->lch()->intval.append(11);
node->lch()->lch()->intval.append(12);
node->lch()->lch()->intval.append(13);
node->lch()->lch()->intval.append(14);
node->lch()->lch()->intval.append(15);
node->lch()->lch()->intval.append(16);
node->lch()->lch()->intval.append(17);
node->lch()->lch()->intval.append(18);
node->lch()->add("status",[](){return QVariant((int32_t)(mj->out.bup_state.msg->status));},[](){return (dcu_status_str(mj->out.bup_state.msg->status));})->setData =  [](QVariant data){ mj->out.bup_state.msg->status=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("PREPARE");
node->lch()->lch()->values.append("CUR_CALIB");
node->lch()->lch()->values.append("DISARM");
node->lch()->lch()->values.append("ARM");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(-1);
node->lch()->add("limit",[](){return QVariant((int32_t)(mj->out.bup_state.msg->limit));},[](){return (move_limit_state_str(mj->out.bup_state.msg->limit));})->setData =  [](QVariant data){ mj->out.bup_state.msg->limit=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("NONE");
node->lch()->lch()->values.append("LIMIT_UP");
node->lch()->lch()->values.append("LIMIT_DOWN");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->add("angle",[](){return QVariant(mj->out.bup_state.msg->angle);})->setData =  [](QVariant data){ mj->out.bup_state.msg->angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("speed",[](){return QVariant(mj->out.bup_state.msg->speed);})->setData =  [](QVariant data){ mj->out.bup_state.msg->speed=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("stator_temp",[](){return QVariant(mj->out.bup_state.msg->stator_temp);})->setData =  [](QVariant data){ mj->out.bup_state.msg->stator_temp=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->out.bup_state.msg->brake_state));},[](){return (rotor_brake_state_str(mj->out.bup_state.msg->brake_state));})->setData =  [](QVariant data){ mj->out.bup_state.msg->brake_state=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("CLOSE");
node->lch()->lch()->values.append("RELEASE");
node->lch()->lch()->values.append("FAIL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->add("power_voltage",[](){return QVariant(mj->out.bup_state.msg->power_voltage);})->setData =  [](QVariant data){ mj->out.bup_state.msg->power_voltage=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("id",[](){return QVariant(mj->out.bup_state.msg->id);})->setData =  [](QVariant data){ mj->out.bup_state.msg->id=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("iq",[](){return QVariant(mj->out.bup_state.msg->iq);})->setData =  [](QVariant data){ mj->out.bup_state.msg->iq=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("electrical_power",[](){return QVariant(mj->out.bup_state.msg->electrical_power);})->setData =  [](QVariant data){ mj->out.bup_state.msg->electrical_power=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->out.bup_state.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->out.bup_state.msg->load_sens_state));})->setData =  [](QVariant data){ mj->out.bup_state.msg->load_sens_state=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("PREPARE");
node->lch()->lch()->values.append("UNCONNECTED");
node->lch()->lch()->values.append("NORMAL");
node->lch()->lch()->values.append("WARNING");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(-1);
node->lch()->add("load_sens_angle",[](){return QVariant(mj->out.bup_state.msg->load_sens_angle);})->setData =  [](QVariant data){ mj->out.bup_state.msg->load_sens_angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_sens_speed",[](){return QVariant(mj->out.bup_state.msg->load_sens_speed);})->setData =  [](QVariant data){ mj->out.bup_state.msg->load_sens_speed=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->out.bup_state.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->out.bup_state.msg->rotor_sens_state));})->setData =  [](QVariant data){ mj->out.bup_state.msg->rotor_sens_state=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("PREPARE");
node->lch()->lch()->values.append("UNCONNECTED");
node->lch()->lch()->values.append("NORMAL");
node->lch()->lch()->values.append("WARNING");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(-1);
node->lch()->add("rotor_sens_angle",[](){return QVariant(mj->out.bup_state.msg->rotor_sens_angle);})->setData =  [](QVariant data){ mj->out.bup_state.msg->rotor_sens_angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("rotor_sens_speed",[](){return QVariant(mj->out.bup_state.msg->rotor_sens_speed);})->setData =  [](QVariant data){ mj->out.bup_state.msg->rotor_sens_speed=data.value<float>();return;};
node->lch()->lch()->editable = true;

cmd_ans_ptr = node->add("cmd_ans",[](){return QVariant(mj->out.cmd_ans.msg->hdr.cnt);});
cmd_ans_ptr->tx = [](uint16_t dst){mj->out.cmd_ans.tx(dst);};

node->lch()->add("command",[](){return QVariant((int32_t)(mj->out.cmd_ans.msg->command));},[](){return (command_type_str(mj->out.cmd_ans.msg->command));})->setData =  [](QVariant data){ mj->out.cmd_ans.msg->command=(command_type)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("SWRESET");
node->lch()->lch()->values.append("SAVEPRM");
node->lch()->lch()->values.append("SET_HOME_POSITION");
node->lch()->lch()->values.append("SET_UP_LIMIT");
node->lch()->lch()->values.append("SET_DOWN_LIMIT");
node->lch()->lch()->values.append("SET_EL_ZERO");
node->lch()->lch()->values.append("OPERATION_TIME_RESET");
node->lch()->lch()->values.append("INTEGRATOR_RESET");
node->lch()->lch()->values.append("FIRMWARE_UPGRADE");
node->lch()->lch()->values.append("FIRMWARE_VERIFY");
node->lch()->lch()->values.append("CURRENT_SENSOR_CALIB");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(6);
node->lch()->lch()->intval.append(7);
node->lch()->lch()->intval.append(8);
node->lch()->lch()->intval.append(9);
node->lch()->lch()->intval.append(10);
node->lch()->add("state",[](){return QVariant((int32_t)(mj->out.cmd_ans.msg->state));},[](){return (command_state_str(mj->out.cmd_ans.msg->state));})->setData =  [](QVariant data){ mj->out.cmd_ans.msg->state=(command_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("ACCEPT");
node->lch()->lch()->values.append("INPROGRESS");
node->lch()->lch()->values.append("DONE");
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("FORBITTEN");
node->lch()->lch()->values.append("NOT_IMPLEMENTED");
node->lch()->lch()->values.append("ERROR");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(-4);
node->lch()->lch()->intval.append(-5);
node->lch()->add("cnt",[](){return QVariant(mj->out.cmd_ans.msg->cnt);})->setData =  [](QVariant data){ mj->out.cmd_ans.msg->cnt=data.value<uint32_t>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("info",[](){return QVariant(cp866ToQString(mj->out.cmd_ans.msg->info,sizeof(mj->out.cmd_ans.msg->info)));})->setData =  [](QVariant data){ memcpy(mj->out.cmd_ans.msg->info,data.value<QString>().toStdString().c_str(),32);return;};
node->lch()->lch()->editable = true;

dbg_ptr = node->add("dbg",[](){return QVariant(mj->out.dbg.msg->hdr.cnt);});
dbg_ptr->tx_enable = &mj->out.dbg.tx_enable;

node->lch()->add("fval",[](){return QVariant();});
node->lch()->lch()->add("[0]",[](){return QVariant(mj->out.dbg.msg->fval[0]);})->setData =  [](QVariant data){ mj->out.dbg.msg->fval[0]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("[1]",[](){return QVariant(mj->out.dbg.msg->fval[1]);})->setData =  [](QVariant data){ mj->out.dbg.msg->fval[1]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("[2]",[](){return QVariant(mj->out.dbg.msg->fval[2]);})->setData =  [](QVariant data){ mj->out.dbg.msg->fval[2]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("[3]",[](){return QVariant(mj->out.dbg.msg->fval[3]);})->setData =  [](QVariant data){ mj->out.dbg.msg->fval[3]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("[4]",[](){return QVariant(mj->out.dbg.msg->fval[4]);})->setData =  [](QVariant data){ mj->out.dbg.msg->fval[4]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;

dcu_tel_ptr = node->add("dcu_tel",[](){return QVariant(mj->out.dcu_tel.msg->hdr.cnt);});
dcu_tel_ptr->tx_enable = &mj->out.dcu_tel.tx_enable;

node->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->mode));},[](){return (drv_ctrl_mode_str(mj->out.dcu_tel.msg->mode));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->mode=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FREEMOVE");
node->lch()->lch()->values.append("HOLD");
node->lch()->lch()->values.append("ANGLE");
node->lch()->lch()->values.append("SPEED");
node->lch()->lch()->values.append("RSPEED");
node->lch()->lch()->values.append("VOLTAGE");
node->lch()->lch()->values.append("SYNCHRO");
node->lch()->lch()->values.append("CURRENT");
node->lch()->lch()->values.append("VOLTAGE_A");
node->lch()->lch()->values.append("VOLTAGE_B");
node->lch()->lch()->values.append("VOLTAGE_C");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(6);
node->lch()->lch()->intval.append(7);
node->lch()->lch()->intval.append(8);
node->lch()->lch()->intval.append(9);
node->lch()->lch()->intval.append(10);
node->lch()->lch()->intval.append(11);
node->lch()->lch()->intval.append(12);
node->lch()->add("status",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->status));},[](){return (dcu_status_str(mj->out.dcu_tel.msg->status));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->status=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("PREPARE");
node->lch()->lch()->values.append("CUR_CALIB");
node->lch()->lch()->values.append("DISARM");
node->lch()->lch()->values.append("ARM");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(-1);
node->lch()->add("err",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->err));},[](){return (drv_ctrl_error_str(mj->out.dcu_tel.msg->err));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->err=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("NONE");
node->lch()->lch()->values.append("BLOCK");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("POWER");
node->lch()->lch()->values.append("CTRL");
node->lch()->lch()->values.append("OLP");
node->lch()->lch()->values.append("OCP");
node->lch()->lch()->values.append("UVP");
node->lch()->lch()->values.append("SCP");
node->lch()->lch()->values.append("MODE");
node->lch()->lch()->values.append("INV");
node->lch()->lch()->values.append("LANG");
node->lch()->lch()->values.append("RANG");
node->lch()->lch()->values.append("OHP");
node->lch()->lch()->values.append("BRAKE");
node->lch()->lch()->values.append("ROTOR_SENS");
node->lch()->lch()->values.append("MCON");
node->lch()->lch()->values.append("SERVICE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(6);
node->lch()->lch()->intval.append(7);
node->lch()->lch()->intval.append(8);
node->lch()->lch()->intval.append(9);
node->lch()->lch()->intval.append(10);
node->lch()->lch()->intval.append(11);
node->lch()->lch()->intval.append(12);
node->lch()->lch()->intval.append(13);
node->lch()->lch()->intval.append(14);
node->lch()->lch()->intval.append(15);
node->lch()->lch()->intval.append(16);
node->lch()->lch()->intval.append(17);
node->lch()->lch()->intval.append(18);
node->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->out.dcu_tel.msg->load_sens_state));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->load_sens_state=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("PREPARE");
node->lch()->lch()->values.append("UNCONNECTED");
node->lch()->lch()->values.append("NORMAL");
node->lch()->lch()->values.append("WARNING");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(-1);
node->lch()->add("load_sens_angle",[](){return QVariant(mj->out.dcu_tel.msg->load_sens_angle);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->load_sens_angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_sens_speed",[](){return QVariant(mj->out.dcu_tel.msg->load_sens_speed);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->load_sens_speed=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("power_vdc",[](){return QVariant(mj->out.dcu_tel.msg->power_vdc);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->power_vdc=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("current",[](){return QVariant();});
node->lch()->lch()->add("a",[](){return QVariant(mj->out.dcu_tel.msg->current.a);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->current.a=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("b",[](){return QVariant(mj->out.dcu_tel.msg->current.b);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->current.b=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("c",[](){return QVariant(mj->out.dcu_tel.msg->current.c);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->current.c=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("pwm",[](){return QVariant();});
node->lch()->lch()->add("a",[](){return QVariant(mj->out.dcu_tel.msg->pwm.a);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->pwm.a=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("b",[](){return QVariant(mj->out.dcu_tel.msg->pwm.b);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->pwm.b=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("c",[](){return QVariant(mj->out.dcu_tel.msg->pwm.c);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->pwm.c=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("park_current",[](){return QVariant();});
node->lch()->lch()->add("d",[](){return QVariant(mj->out.dcu_tel.msg->park_current.d);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->park_current.d=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("q",[](){return QVariant(mj->out.dcu_tel.msg->park_current.q);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->park_current.q=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("park_voltage",[](){return QVariant();});
node->lch()->lch()->add("d",[](){return QVariant(mj->out.dcu_tel.msg->park_voltage.d);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->park_voltage.d=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("q",[](){return QVariant(mj->out.dcu_tel.msg->park_voltage.q);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->park_voltage.q=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("stator_temp",[](){return QVariant(mj->out.dcu_tel.msg->stator_temp);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->stator_temp=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->brake_state));},[](){return (rotor_brake_state_str(mj->out.dcu_tel.msg->brake_state));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->brake_state=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("CLOSE");
node->lch()->lch()->values.append("RELEASE");
node->lch()->lch()->values.append("FAIL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->add("ibrk",[](){return QVariant(mj->out.dcu_tel.msg->ibrk);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->ibrk=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("power_voltage",[](){return QVariant(mj->out.dcu_tel.msg->power_voltage);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->power_voltage=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("id",[](){return QVariant(mj->out.dcu_tel.msg->id);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->id=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("iq",[](){return QVariant(mj->out.dcu_tel.msg->iq);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->iq=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("electrical_power",[](){return QVariant(mj->out.dcu_tel.msg->electrical_power);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->electrical_power=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("ang_pid_err",[](){return QVariant(mj->out.dcu_tel.msg->ang_pid_err);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->ang_pid_err=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("ang_pid_in",[](){return QVariant(mj->out.dcu_tel.msg->ang_pid_in);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->ang_pid_in=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("ang_pid_out",[](){return QVariant(mj->out.dcu_tel.msg->ang_pid_out);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->ang_pid_out=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("ang_pid_intgr",[](){return QVariant(mj->out.dcu_tel.msg->ang_pid_intgr);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->ang_pid_intgr=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("rotor_spd_pid_err",[](){return QVariant(mj->out.dcu_tel.msg->rotor_spd_pid_err);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->rotor_spd_pid_err=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("rotor_spd_pid_in",[](){return QVariant(mj->out.dcu_tel.msg->rotor_spd_pid_in);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->rotor_spd_pid_in=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("rotor_spd_pid_out",[](){return QVariant(mj->out.dcu_tel.msg->rotor_spd_pid_out);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->rotor_spd_pid_out=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("rotor_spd_pid_intgr",[](){return QVariant(mj->out.dcu_tel.msg->rotor_spd_pid_intgr);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->rotor_spd_pid_intgr=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_spd_pid_err",[](){return QVariant(mj->out.dcu_tel.msg->load_spd_pid_err);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->load_spd_pid_err=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_spd_pid_in",[](){return QVariant(mj->out.dcu_tel.msg->load_spd_pid_in);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->load_spd_pid_in=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_spd_pid_out",[](){return QVariant(mj->out.dcu_tel.msg->load_spd_pid_out);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->load_spd_pid_out=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_spd_pid_intgr",[](){return QVariant(mj->out.dcu_tel.msg->load_spd_pid_intgr);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->load_spd_pid_intgr=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("curr_pid_err",[](){return QVariant(mj->out.dcu_tel.msg->curr_pid_err);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->curr_pid_err=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("curr_pid_in",[](){return QVariant(mj->out.dcu_tel.msg->curr_pid_in);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->curr_pid_in=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("curr_pid_out",[](){return QVariant(mj->out.dcu_tel.msg->curr_pid_out);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->curr_pid_out=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("curr_pid_intgr",[](){return QVariant(mj->out.dcu_tel.msg->curr_pid_intgr);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->curr_pid_intgr=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->out.dcu_tel.msg->rotor_sens_state));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->rotor_sens_state=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("PREPARE");
node->lch()->lch()->values.append("UNCONNECTED");
node->lch()->lch()->values.append("NORMAL");
node->lch()->lch()->values.append("WARNING");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(-1);
node->lch()->add("rotor_sens_angle",[](){return QVariant(mj->out.dcu_tel.msg->rotor_sens_angle);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->rotor_sens_angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("rotor_sens_speed",[](){return QVariant(mj->out.dcu_tel.msg->rotor_sens_speed);})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->rotor_sens_speed=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("on",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->on));},[](){return (relay_signal_state_str(mj->out.dcu_tel.msg->on));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->on=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("HIGH");
node->lch()->lch()->values.append("LOW");
node->lch()->lch()->values.append("GAP");
node->lch()->lch()->values.append("OCP");
node->lch()->lch()->values.append("FAIL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(-2);
node->lch()->add("manual",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->manual));},[](){return (relay_signal_state_str(mj->out.dcu_tel.msg->manual));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->manual=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("HIGH");
node->lch()->lch()->values.append("LOW");
node->lch()->lch()->values.append("GAP");
node->lch()->lch()->values.append("OCP");
node->lch()->lch()->values.append("FAIL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(-2);
node->lch()->add("block",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->block));},[](){return (relay_signal_state_str(mj->out.dcu_tel.msg->block));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->block=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("HIGH");
node->lch()->lch()->values.append("LOW");
node->lch()->lch()->values.append("GAP");
node->lch()->lch()->values.append("OCP");
node->lch()->lch()->values.append("FAIL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(-2);
node->lch()->add("sync",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->sync));},[](){return (relay_signal_state_str(mj->out.dcu_tel.msg->sync));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->sync=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("HIGH");
node->lch()->lch()->values.append("LOW");
node->lch()->lch()->values.append("GAP");
node->lch()->lch()->values.append("OCP");
node->lch()->lch()->values.append("FAIL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(-2);
node->lch()->add("inv_octw",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->inv_octw));},[](){return (relay_signal_state_str(mj->out.dcu_tel.msg->inv_octw));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->inv_octw=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("HIGH");
node->lch()->lch()->values.append("LOW");
node->lch()->lch()->values.append("GAP");
node->lch()->lch()->values.append("OCP");
node->lch()->lch()->values.append("FAIL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(-2);
node->lch()->add("inv_fault",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->inv_fault));},[](){return (relay_signal_state_str(mj->out.dcu_tel.msg->inv_fault));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->inv_fault=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("HIGH");
node->lch()->lch()->values.append("LOW");
node->lch()->lch()->values.append("GAP");
node->lch()->lch()->values.append("OCP");
node->lch()->lch()->values.append("FAIL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(-2);
node->lch()->add("en_gate",[](){return QVariant((int32_t)(mj->out.dcu_tel.msg->en_gate));},[](){return (relay_signal_state_str(mj->out.dcu_tel.msg->en_gate));})->setData =  [](QVariant data){ mj->out.dcu_tel.msg->en_gate=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("HIGH");
node->lch()->lch()->values.append("LOW");
node->lch()->lch()->values.append("GAP");
node->lch()->lch()->values.append("OCP");
node->lch()->lch()->values.append("FAIL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(-2);

formular_ptr = node->add("formular",[](){return QVariant(mj->out.formular.msg->hdr.cnt);});
formular_ptr->tx = [](uint16_t dst){mj->out.formular.tx(dst);};

node->lch()->add("description",[](){return QVariant(cp866ToQString(mj->out.formular.msg->description,sizeof(mj->out.formular.msg->description)));})->setData =  [](QVariant data){ memcpy(mj->out.formular.msg->description,data.value<QString>().toStdString().c_str(),32);return;};
node->lch()->lch()->editable = true;
node->lch()->add("factory_number",[](){return QVariant(cp866ToQString(mj->out.formular.msg->factory_number,sizeof(mj->out.formular.msg->factory_number)));})->setData =  [](QVariant data){ memcpy(mj->out.formular.msg->factory_number,data.value<QString>().toStdString().c_str(),32);return;};
node->lch()->lch()->editable = true;
node->lch()->add("factory_date",[](){return QVariant(cp866ToQString(mj->out.formular.msg->factory_date,sizeof(mj->out.formular.msg->factory_date)));})->setData =  [](QVariant data){ memcpy(mj->out.formular.msg->factory_date,data.value<QString>().toStdString().c_str(),32);return;};
node->lch()->lch()->editable = true;
node->lch()->add("software_version",[](){return QVariant(cp866ToQString(mj->out.formular.msg->software_version,sizeof(mj->out.formular.msg->software_version)));})->setData =  [](QVariant data){ memcpy(mj->out.formular.msg->software_version,data.value<QString>().toStdString().c_str(),32);return;};
node->lch()->lch()->editable = true;
node->lch()->add("protocol_version",[](){return QVariant(cp866ToQString(mj->out.formular.msg->protocol_version,sizeof(mj->out.formular.msg->protocol_version)));})->setData =  [](QVariant data){ memcpy(mj->out.formular.msg->protocol_version,data.value<QString>().toStdString().c_str(),32);return;};
node->lch()->lch()->editable = true;
node->lch()->add("GUID",[](){return QVariant(cp866ToQString(mj->out.formular.msg->GUID,sizeof(mj->out.formular.msg->GUID)));})->setData =  [](QVariant data){ memcpy(mj->out.formular.msg->GUID,data.value<QString>().toStdString().c_str(),32);return;};
node->lch()->lch()->editable = true;
node->lch()->add("operation_time",[](){return QVariant(mj->out.formular.msg->operation_time);})->setData =  [](QVariant data){ mj->out.formular.msg->operation_time=data.value<int32_t>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("software_checksum",[](){return QVariant(cp866ToQString(mj->out.formular.msg->software_checksum,sizeof(mj->out.formular.msg->software_checksum)));})->setData =  [](QVariant data){ memcpy(mj->out.formular.msg->software_checksum,data.value<QString>().toStdString().c_str(),64);return;};
node->lch()->lch()->editable = true;
node->lch()->add("code",[](){return QVariant(mj->out.formular.msg->code);})->setData =  [](QVariant data){ mj->out.formular.msg->code=data.value<uint8_t>();return;};
node->lch()->lch()->editable = true;

im_bro_drive_ctrl_ptr = node->add("im_bro_drive_ctrl",[](){return QVariant(mj->out.im_bro_drive_ctrl.msg->hdr.cnt);});
im_bro_drive_ctrl_ptr->tx_enable = &mj->out.im_bro_drive_ctrl.tx_enable;

node->lch()->add("voltage",[](){return QVariant();});
node->lch()->lch()->add("[0]",[](){return QVariant(mj->out.im_bro_drive_ctrl.msg->voltage[0]);})->setData =  [](QVariant data){ mj->out.im_bro_drive_ctrl.msg->voltage[0]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("[1]",[](){return QVariant(mj->out.im_bro_drive_ctrl.msg->voltage[1]);})->setData =  [](QVariant data){ mj->out.im_bro_drive_ctrl.msg->voltage[1]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("[2]",[](){return QVariant(mj->out.im_bro_drive_ctrl.msg->voltage[2]);})->setData =  [](QVariant data){ mj->out.im_bro_drive_ctrl.msg->voltage[2]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("connected",[](){return QVariant(mj->out.im_bro_drive_ctrl.msg->connected);})->setData =  [](QVariant data){ mj->out.im_bro_drive_ctrl.msg->connected=data.value<bool>();return;};
node->lch()->lch()->editable = true;

msg_ans_ptr = node->add("msg_ans",[](){return QVariant(mj->out.msg_ans.msg->hdr.cnt);});
msg_ans_ptr->tx = [](uint16_t dst){mj->out.msg_ans.tx(dst);};

node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.msg_ans.msg->id));},[](){return (mj_get_msg_name(mj->out.msg_ans.msg->id));})->setData =  [](QVariant data){ ;return;};
node->lch()->lch()->editable = true;
node->lch()->add("cnt",[](){return QVariant(mj->out.msg_ans.msg->cnt);})->setData =  [](QVariant data){ mj->out.msg_ans.msg->cnt=data.value<uint32_t>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("state",[](){return QVariant((int32_t)(mj->out.msg_ans.msg->state));},[](){return (msg_state_str(mj->out.msg_ans.msg->state));})->setData =  [](QVariant data){ mj->out.msg_ans.msg->state=(msg_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("CONFIRMED");
node->lch()->lch()->values.append("SEND");
node->lch()->lch()->values.append("WRONGCODE");
node->lch()->lch()->values.append("ISPERIODIC");
node->lch()->lch()->values.append("IMPOSSIBLE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(-2);
node->lch()->lch()->intval.append(-3);

prm_ans_ptr = node->add("prm_ans",[](){return QVariant(mj->out.prm_ans.msg->hdr.cnt);});
prm_ans_ptr->tx = [](uint16_t dst){mj->out.prm_ans.tx(dst);};

node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->out.prm_ans.msg->id));})->setData =  [](QVariant data){ mj->out.prm_ans.msg->id=(uint32_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("service_mode");
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->values.append("Vdc");
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->values.append("cur_lim");
node->lch()->lch()->values.append("drv_limit_up");
node->lch()->lch()->values.append("drv_limit_down");
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->values.append("ohp_lvl");
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->values.append("pole_pairs");
node->lch()->lch()->values.append("ph_resistance");
node->lch()->lch()->values.append("ph_inductance");
node->lch()->lch()->values.append("brake_unlock_voltage");
node->lch()->lch()->values.append("brake_unlock_time");
node->lch()->lch()->values.append("brake_hold_voltage");
node->lch()->lch()->values.append("brake_lock_time");
node->lch()->lch()->values.append("curr_kp");
node->lch()->lch()->values.append("curr_ki");
node->lch()->lch()->values.append("curr_kb");
node->lch()->lch()->values.append("curr_kt");
node->lch()->lch()->values.append("curr_kf");
node->lch()->lch()->values.append("curr_fc");
node->lch()->lch()->values.append("curr_err_lim");
node->lch()->lch()->values.append("curr_out_lim");
node->lch()->lch()->values.append("curr_out_rate_lim");
node->lch()->lch()->values.append("curr_err_rate_lim");
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->values.append("load_speed_kd");
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->values.append("rotor_speed_kd");
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->values.append("rotor_ang_kd");
node->lch()->lch()->values.append("rotor_ang_kt");
node->lch()->lch()->values.append("rotor_ang_kf");
node->lch()->lch()->values.append("rotor_ang_err_lim");
node->lch()->lch()->values.append("rotor_ang_out_lim");
node->lch()->lch()->values.append("rotor_ang_out_rate_lim");
node->lch()->lch()->values.append("rotor_ang_err_rate_lim");
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->values.append("factory_date");
node->lch()->lch()->values.append("factory_number");
node->lch()->lch()->values.append("description");
node->lch()->lch()->values.append("com_if_srv_mcast_req");
node->lch()->lch()->values.append("com_if_srv_mcast_ans");
node->lch()->lch()->values.append("com_if_bro_bup_ctrl_mcast");
node->lch()->lch()->values.append("com_if_bro_bup_data_mcast");
node->lch()->lch()->values.append("com_if_bro_bup_srv_mcast");
node->lch()->lch()->values.append("com_if_im_bro_drive_mcast");
node->lch()->lch()->values.append("com_if_im_bro_drive_ctrl_mcast");
node->lch()->lch()->values.append("dev_id");
node->lch()->lch()->intval.append(0x311FD2BA);
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->intval.append(0x7F45547);
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->intval.append(0x55DA9773);
node->lch()->lch()->intval.append(0x5C57D2B7);
node->lch()->lch()->intval.append(0x501D05A4);
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->intval.append(0x12DB50AA);
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->intval.append(0x393E0A69);
node->lch()->lch()->intval.append(0xD478FE43);
node->lch()->lch()->intval.append(0x5B351473);
node->lch()->lch()->intval.append(0x920D8F3B);
node->lch()->lch()->intval.append(0xD31E0ACB);
node->lch()->lch()->intval.append(0x64399A99);
node->lch()->lch()->intval.append(0x955BB624);
node->lch()->lch()->intval.append(0x323FC775);
node->lch()->lch()->intval.append(0x16A9255D);
node->lch()->lch()->intval.append(0x80056521);
node->lch()->lch()->intval.append(0xAD5D6E6E);
node->lch()->lch()->intval.append(0x1F67CC3A);
node->lch()->lch()->intval.append(0x9841D378);
node->lch()->lch()->intval.append(0xCAF1DD24);
node->lch()->lch()->intval.append(0x8D2D0B70);
node->lch()->lch()->intval.append(0x41824DD2);
node->lch()->lch()->intval.append(0x6EFAD7A0);
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->intval.append(0xA6070C18);
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->intval.append(0xB17A1B4D);
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->intval.append(0x5D94228B);
node->lch()->lch()->intval.append(0x201F9189);
node->lch()->lch()->intval.append(0x922533DD);
node->lch()->lch()->intval.append(0x74081F2D);
node->lch()->lch()->intval.append(0x33D4C979);
node->lch()->lch()->intval.append(0x28CABE88);
node->lch()->lch()->intval.append(0x7B224FA);
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->intval.append(0x925B41AA);
node->lch()->lch()->intval.append(0xA92645D2);
node->lch()->lch()->intval.append(0xC8EE09D4);
node->lch()->lch()->intval.append(0x4D7787A8);
node->lch()->lch()->intval.append(0x4DDDD1EE);
node->lch()->lch()->intval.append(0x52F653D2);
node->lch()->lch()->intval.append(0xDDFE2DA4);
node->lch()->lch()->intval.append(0x6F0DA7DD);
node->lch()->lch()->intval.append(0x6F720C87);
node->lch()->lch()->intval.append(0x64B26340);
node->lch()->lch()->intval.append(0x3C3707BD);
node->lch()->lch()->intval.append(0x17EAC676);
node->lch()->add("ans",[](){return QVariant((int32_t)(mj->out.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->out.prm_ans.msg->ans));})->setData =  [](QVariant data){ mj->out.prm_ans.msg->ans=(parameter_status)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("OK");
node->lch()->lch()->values.append("UNKNOWPRM");
node->lch()->lch()->values.append("WRITE_FAILED");
node->lch()->lch()->values.append("READ_ONLY");
node->lch()->lch()->values.append("NOT_SUPPORTED");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(-4);
node->lch()->lch()->intval.append(-5);
node->lch()->lch()->intval.append(-6);
node->lch()->add("val",[](){return QVariant(prm2QVariant(mj->out.prm_ans.msg->id,(uint8_t*)mj->out.prm_ans.msg->val,sizeof(mj->out.prm_ans.msg->val)));})->setData =  [](QVariant data){ QVariant2prm(mj->out.prm_ans.msg->id,(uint8_t*)mj->out.prm_ans.msg->val,sizeof(mj->out.prm_ans.msg->val),data);return;};
node->lch()->lch()->editable = true;

ptp_state_ptr = node->add("ptp_state",[](){return QVariant(mj->out.ptp_state.msg->hdr.cnt);});
ptp_state_ptr->tx_enable = &mj->out.ptp_state.tx_enable;

node->lch()->add("is_master",[](){return QVariant(mj->out.ptp_state.msg->is_master);})->setData =  [](QVariant data){ mj->out.ptp_state.msg->is_master=data.value<bool>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("path_delay",[](){return QVariant(mj->out.ptp_state.msg->path_delay);})->setData =  [](QVariant data){ mj->out.ptp_state.msg->path_delay=data.value<int32_t>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("offset_ns",[](){return QVariant(mj->out.ptp_state.msg->offset_ns);})->setData =  [](QVariant data){ mj->out.ptp_state.msg->offset_ns=data.value<int32_t>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("mean_offset_ns",[](){return QVariant(mj->out.ptp_state.msg->mean_offset_ns);})->setData =  [](QVariant data){ mj->out.ptp_state.msg->mean_offset_ns=data.value<int32_t>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("state",[](){return QVariant((int32_t)(mj->out.ptp_state.msg->state));},[](){return (sync_state_str(mj->out.ptp_state.msg->state));})->setData =  [](QVariant data){ mj->out.ptp_state.msg->state=(sync_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("FAILED");
node->lch()->lch()->values.append("FREERUN");
node->lch()->lch()->values.append("UNSYNC");
node->lch()->lch()->values.append("SYNC");
node->lch()->lch()->intval.append(-1);
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);

return node;
};

TreeNode * create_dcu_params_tree(mj_dcu_t * mj_ptr){
static mj_dcu_t * mj = mj_ptr;
TreeNode * node = new TreeNode("PARAMETERS",[](){return QVariant();});
auto aufd_ptr = node->add("aufd",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
aufd_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
node->lch()->add("type",[](){return QVariant((int32_t)(mj->out.prm_req.msg->type));})->setData =  [](QVariant data){ mj->out.prm_req.msg->type=(parameter_request_type)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("READ");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->values.append("WRITE");
node->lch()->lch()->intval.append(1);
node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.prm_req.msg->id));})->setData =  [](QVariant data){ mj->out.prm_req.msg->id=(uint32_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("service_mode");
node->lch()->lch()->intval.append(0x311FD2BA);
node->lch()->lch()->values.append("factory_date");
node->lch()->lch()->intval.append(0xA92645D2);
node->lch()->lch()->values.append("factory_number");
node->lch()->lch()->intval.append(0xC8EE09D4);
node->lch()->lch()->values.append("description");
node->lch()->lch()->intval.append(0x4D7787A8);
node->lch()->lch()->values.append("com_if_srv_mcast_req");
node->lch()->lch()->intval.append(0x4DDDD1EE);
node->lch()->lch()->values.append("com_if_srv_mcast_ans");
node->lch()->lch()->intval.append(0x52F653D2);
node->lch()->lch()->values.append("com_if_bro_bup_ctrl_mcast");
node->lch()->lch()->intval.append(0xDDFE2DA4);
node->lch()->lch()->values.append("com_if_bro_bup_data_mcast");
node->lch()->lch()->intval.append(0x6F0DA7DD);
node->lch()->lch()->values.append("dev_id");
node->lch()->lch()->intval.append(0x17EAC676);
node->lch()->add("val",[](){return QVariant(prm2QVariant(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val)));})->setData =  [](QVariant data){ QVariant2prm(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val),data);return;};
node->lch()->lch()->editable = true;
auto im_bro_ptr = node->add("im_bro",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
im_bro_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
node->lch()->add("type",[](){return QVariant((int32_t)(mj->out.prm_req.msg->type));})->setData =  [](QVariant data){ mj->out.prm_req.msg->type=(parameter_request_type)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("READ");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->values.append("WRITE");
node->lch()->lch()->intval.append(1);
node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.prm_req.msg->id));})->setData =  [](QVariant data){ mj->out.prm_req.msg->id=(uint32_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("service_mode");
node->lch()->lch()->intval.append(0x311FD2BA);
node->lch()->lch()->values.append("Vdc");
node->lch()->lch()->intval.append(0x7F45547);
node->lch()->lch()->values.append("com_if_srv_mcast_req");
node->lch()->lch()->intval.append(0x4DDDD1EE);
node->lch()->lch()->values.append("com_if_srv_mcast_ans");
node->lch()->lch()->intval.append(0x52F653D2);
node->lch()->lch()->values.append("com_if_im_bro_drive_mcast");
node->lch()->lch()->intval.append(0x64B26340);
node->lch()->lch()->values.append("com_if_im_bro_drive_ctrl_mcast");
node->lch()->lch()->intval.append(0x3C3707BD);
node->lch()->lch()->values.append("dev_id");
node->lch()->lch()->intval.append(0x17EAC676);
node->lch()->add("val",[](){return QVariant(prm2QVariant(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val)));})->setData =  [](QVariant data){ QVariant2prm(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val),data);return;};
node->lch()->lch()->editable = true;
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
node->lch()->lch()->intval.append(0x311FD2BA);
node->lch()->lch()->values.append("com_if_srv_mcast_req");
node->lch()->lch()->intval.append(0x4DDDD1EE);
node->lch()->lch()->values.append("com_if_srv_mcast_ans");
node->lch()->lch()->intval.append(0x52F653D2);
node->lch()->lch()->values.append("com_if_bro_bup_data_mcast");
node->lch()->lch()->intval.append(0x6F0DA7DD);
node->lch()->lch()->values.append("com_if_bro_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6F720C87);
node->lch()->lch()->values.append("com_if_im_bro_drive_mcast");
node->lch()->lch()->intval.append(0x64B26340);
node->lch()->lch()->values.append("com_if_im_bro_drive_ctrl_mcast");
node->lch()->lch()->intval.append(0x3C3707BD);
node->lch()->lch()->values.append("dev_id");
node->lch()->lch()->intval.append(0x17EAC676);
node->lch()->add("val",[](){return QVariant(prm2QVariant(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val)));})->setData =  [](QVariant data){ QVariant2prm(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val),data);return;};
node->lch()->lch()->editable = true;
return node;
};