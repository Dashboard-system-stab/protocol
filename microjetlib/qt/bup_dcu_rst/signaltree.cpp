
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
 
        case 0xF6D4B455:
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
 
        case 0xE1A9A300:
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
 
        case 0xD479AC6:
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
    if (id == 0xF6D4B455)
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
    if (id == 0xE1A9A300)
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
    if (id == 0xD479AC6)
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


TreeNode * create_bup_dcu_rst_in_tree(mj_bup_dcu_rst_t * mj_ptr)
{
static mj_bup_dcu_rst_t *mj = mj_ptr;
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


TreeNode * create_bup_dcu_rst_out_tree(mj_bup_dcu_rst_t * mj_ptr)
{
static mj_bup_dcu_rst_t * mj = mj_ptr;
TreeNode * node = new TreeNode("OUTPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
return node;
};

TreeNode * create_bup_dcu_rst_params_tree(mj_bup_dcu_rst_t * mj_ptr){
static mj_bup_dcu_rst_t * mj = mj_ptr;
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