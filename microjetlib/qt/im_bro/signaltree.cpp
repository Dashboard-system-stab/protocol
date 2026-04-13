
#include "signaltree.h"

static TreeNode *aufd_prm_req_ptr = 0;
static TreeNode *bup_dcu_lfd_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_lrd_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_lst_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_rfd_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_rrd_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_rst_im_bro_drive_ctrl_ptr = 0;
static TreeNode *dcu_im_bro_drive_ctrl_ptr = 0;
static TreeNode *mon_prm_req_ptr = 0;

static TreeNode *im_bro_drivers_sens_ptr = 0;
static TreeNode *prm_ans_ptr = 0;

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


TreeNode * create_im_bro_in_tree(mj_im_bro_t * mj_ptr)
{
static mj_im_bro_t *mj = mj_ptr;
TreeNode * node = new TreeNode("INPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
TreeNode * aufd_node = node->add("aufd",[](){return QVariant();});
aufd_node->isDev = true;
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
TreeNode * bup_dcu_lfd_node = node->add("bup_dcu_lfd",[](){return QVariant();});
bup_dcu_lfd_node->isDev = true;
bup_dcu_lfd_im_bro_drive_ctrl_ptr = node->lch()->add("im_bro_drive_ctrl",[](){return QVariant(mj->in.bup_dcu_lfd.im_bro_drive_ctrl.msg->hdr.cnt);});
bup_dcu_lfd_im_bro_drive_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.im_bro_drive_ctrl.state;};
bup_dcu_lfd_im_bro_drive_ctrl_ptr->msgId = ID_IM_BRO_DRIVE_CTRL;
bup_dcu_lfd_im_bro_drive_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.im_bro_drive_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.im_bro_drive_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_lfd.im_bro_drive_ctrl.msg->voltage[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_lfd.im_bro_drive_ctrl.msg->voltage[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_lfd.im_bro_drive_ctrl.msg->voltage[2]);});
node->lch()->lch()->add("connected",[](){return QVariant(mj->in.bup_dcu_lfd.im_bro_drive_ctrl.msg->connected);});
mj->in.bup_dcu_lfd.im_bro_drive_ctrl.upd_cb = [](){ bup_dcu_lfd_im_bro_drive_ctrl_ptr->upd(mj->in.bup_dcu_lfd.im_bro_drive_ctrl.ts_s, mj->in.bup_dcu_lfd.im_bro_drive_ctrl.ts_ns);};
TreeNode * bup_dcu_lrd_node = node->add("bup_dcu_lrd",[](){return QVariant();});
bup_dcu_lrd_node->isDev = true;
bup_dcu_lrd_im_bro_drive_ctrl_ptr = node->lch()->add("im_bro_drive_ctrl",[](){return QVariant(mj->in.bup_dcu_lrd.im_bro_drive_ctrl.msg->hdr.cnt);});
bup_dcu_lrd_im_bro_drive_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.im_bro_drive_ctrl.state;};
bup_dcu_lrd_im_bro_drive_ctrl_ptr->msgId = ID_IM_BRO_DRIVE_CTRL;
bup_dcu_lrd_im_bro_drive_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.im_bro_drive_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.im_bro_drive_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_lrd.im_bro_drive_ctrl.msg->voltage[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_lrd.im_bro_drive_ctrl.msg->voltage[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_lrd.im_bro_drive_ctrl.msg->voltage[2]);});
node->lch()->lch()->add("connected",[](){return QVariant(mj->in.bup_dcu_lrd.im_bro_drive_ctrl.msg->connected);});
mj->in.bup_dcu_lrd.im_bro_drive_ctrl.upd_cb = [](){ bup_dcu_lrd_im_bro_drive_ctrl_ptr->upd(mj->in.bup_dcu_lrd.im_bro_drive_ctrl.ts_s, mj->in.bup_dcu_lrd.im_bro_drive_ctrl.ts_ns);};
TreeNode * bup_dcu_lst_node = node->add("bup_dcu_lst",[](){return QVariant();});
bup_dcu_lst_node->isDev = true;
bup_dcu_lst_im_bro_drive_ctrl_ptr = node->lch()->add("im_bro_drive_ctrl",[](){return QVariant(mj->in.bup_dcu_lst.im_bro_drive_ctrl.msg->hdr.cnt);});
bup_dcu_lst_im_bro_drive_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_lst.im_bro_drive_ctrl.state;};
bup_dcu_lst_im_bro_drive_ctrl_ptr->msgId = ID_IM_BRO_DRIVE_CTRL;
bup_dcu_lst_im_bro_drive_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lst.im_bro_drive_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lst.im_bro_drive_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_lst.im_bro_drive_ctrl.msg->voltage[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_lst.im_bro_drive_ctrl.msg->voltage[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_lst.im_bro_drive_ctrl.msg->voltage[2]);});
node->lch()->lch()->add("connected",[](){return QVariant(mj->in.bup_dcu_lst.im_bro_drive_ctrl.msg->connected);});
mj->in.bup_dcu_lst.im_bro_drive_ctrl.upd_cb = [](){ bup_dcu_lst_im_bro_drive_ctrl_ptr->upd(mj->in.bup_dcu_lst.im_bro_drive_ctrl.ts_s, mj->in.bup_dcu_lst.im_bro_drive_ctrl.ts_ns);};
TreeNode * bup_dcu_rfd_node = node->add("bup_dcu_rfd",[](){return QVariant();});
bup_dcu_rfd_node->isDev = true;
bup_dcu_rfd_im_bro_drive_ctrl_ptr = node->lch()->add("im_bro_drive_ctrl",[](){return QVariant(mj->in.bup_dcu_rfd.im_bro_drive_ctrl.msg->hdr.cnt);});
bup_dcu_rfd_im_bro_drive_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.im_bro_drive_ctrl.state;};
bup_dcu_rfd_im_bro_drive_ctrl_ptr->msgId = ID_IM_BRO_DRIVE_CTRL;
bup_dcu_rfd_im_bro_drive_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.im_bro_drive_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.im_bro_drive_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_rfd.im_bro_drive_ctrl.msg->voltage[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_rfd.im_bro_drive_ctrl.msg->voltage[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_rfd.im_bro_drive_ctrl.msg->voltage[2]);});
node->lch()->lch()->add("connected",[](){return QVariant(mj->in.bup_dcu_rfd.im_bro_drive_ctrl.msg->connected);});
mj->in.bup_dcu_rfd.im_bro_drive_ctrl.upd_cb = [](){ bup_dcu_rfd_im_bro_drive_ctrl_ptr->upd(mj->in.bup_dcu_rfd.im_bro_drive_ctrl.ts_s, mj->in.bup_dcu_rfd.im_bro_drive_ctrl.ts_ns);};
TreeNode * bup_dcu_rrd_node = node->add("bup_dcu_rrd",[](){return QVariant();});
bup_dcu_rrd_node->isDev = true;
bup_dcu_rrd_im_bro_drive_ctrl_ptr = node->lch()->add("im_bro_drive_ctrl",[](){return QVariant(mj->in.bup_dcu_rrd.im_bro_drive_ctrl.msg->hdr.cnt);});
bup_dcu_rrd_im_bro_drive_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.im_bro_drive_ctrl.state;};
bup_dcu_rrd_im_bro_drive_ctrl_ptr->msgId = ID_IM_BRO_DRIVE_CTRL;
bup_dcu_rrd_im_bro_drive_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.im_bro_drive_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.im_bro_drive_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_rrd.im_bro_drive_ctrl.msg->voltage[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_rrd.im_bro_drive_ctrl.msg->voltage[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_rrd.im_bro_drive_ctrl.msg->voltage[2]);});
node->lch()->lch()->add("connected",[](){return QVariant(mj->in.bup_dcu_rrd.im_bro_drive_ctrl.msg->connected);});
mj->in.bup_dcu_rrd.im_bro_drive_ctrl.upd_cb = [](){ bup_dcu_rrd_im_bro_drive_ctrl_ptr->upd(mj->in.bup_dcu_rrd.im_bro_drive_ctrl.ts_s, mj->in.bup_dcu_rrd.im_bro_drive_ctrl.ts_ns);};
TreeNode * bup_dcu_rst_node = node->add("bup_dcu_rst",[](){return QVariant();});
bup_dcu_rst_node->isDev = true;
bup_dcu_rst_im_bro_drive_ctrl_ptr = node->lch()->add("im_bro_drive_ctrl",[](){return QVariant(mj->in.bup_dcu_rst.im_bro_drive_ctrl.msg->hdr.cnt);});
bup_dcu_rst_im_bro_drive_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.im_bro_drive_ctrl.state;};
bup_dcu_rst_im_bro_drive_ctrl_ptr->msgId = ID_IM_BRO_DRIVE_CTRL;
bup_dcu_rst_im_bro_drive_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.im_bro_drive_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.im_bro_drive_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_rst.im_bro_drive_ctrl.msg->voltage[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_rst.im_bro_drive_ctrl.msg->voltage[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_rst.im_bro_drive_ctrl.msg->voltage[2]);});
node->lch()->lch()->add("connected",[](){return QVariant(mj->in.bup_dcu_rst.im_bro_drive_ctrl.msg->connected);});
mj->in.bup_dcu_rst.im_bro_drive_ctrl.upd_cb = [](){ bup_dcu_rst_im_bro_drive_ctrl_ptr->upd(mj->in.bup_dcu_rst.im_bro_drive_ctrl.ts_s, mj->in.bup_dcu_rst.im_bro_drive_ctrl.ts_ns);};
TreeNode * dcu_node = node->add("dcu",[](){return QVariant();});
dcu_node->isDev = true;
dcu_im_bro_drive_ctrl_ptr = node->lch()->add("im_bro_drive_ctrl",[](){return QVariant(mj->in.dcu.im_bro_drive_ctrl.msg->hdr.cnt);});
dcu_im_bro_drive_ctrl_ptr->state = []()->int32_t{return mj->in.dcu.im_bro_drive_ctrl.state;};
dcu_im_bro_drive_ctrl_ptr->msgId = ID_IM_BRO_DRIVE_CTRL;
dcu_im_bro_drive_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.im_bro_drive_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.im_bro_drive_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.dcu.im_bro_drive_ctrl.msg->voltage[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.dcu.im_bro_drive_ctrl.msg->voltage[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.dcu.im_bro_drive_ctrl.msg->voltage[2]);});
node->lch()->lch()->add("connected",[](){return QVariant(mj->in.dcu.im_bro_drive_ctrl.msg->connected);});
mj->in.dcu.im_bro_drive_ctrl.upd_cb = [](){ dcu_im_bro_drive_ctrl_ptr->upd(mj->in.dcu.im_bro_drive_ctrl.ts_s, mj->in.dcu.im_bro_drive_ctrl.ts_ns);};
TreeNode * mon_node = node->add("mon",[](){return QVariant();});
mon_node->isDev = true;
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


TreeNode * create_im_bro_out_tree(mj_im_bro_t * mj_ptr)
{
static mj_im_bro_t * mj = mj_ptr;
TreeNode * node = new TreeNode("OUTPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
im_bro_drivers_sens_ptr = node->add("im_bro_drivers_sens",[](){return QVariant(mj->out.im_bro_drivers_sens.msg->hdr.cnt);});
im_bro_drivers_sens_ptr->tx_enable = &mj->out.im_bro_drivers_sens.tx_enable;

node->lch()->add("currents_gn",[](){return QVariant();});
node->lch()->lch()->add("[0]",[](){return QVariant(mj->out.im_bro_drivers_sens.msg->currents_gn[0]);})->setData =  [](QVariant data){ mj->out.im_bro_drivers_sens.msg->currents_gn[0]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("[1]",[](){return QVariant(mj->out.im_bro_drivers_sens.msg->currents_gn[1]);})->setData =  [](QVariant data){ mj->out.im_bro_drivers_sens.msg->currents_gn[1]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("[2]",[](){return QVariant(mj->out.im_bro_drivers_sens.msg->currents_gn[2]);})->setData =  [](QVariant data){ mj->out.im_bro_drivers_sens.msg->currents_gn[2]=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("rotor_angle_gn",[](){return QVariant(mj->out.im_bro_drivers_sens.msg->rotor_angle_gn);})->setData =  [](QVariant data){ mj->out.im_bro_drivers_sens.msg->rotor_angle_gn=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("v_nom",[](){return QVariant(mj->out.im_bro_drivers_sens.msg->v_nom);})->setData =  [](QVariant data){ mj->out.im_bro_drivers_sens.msg->v_nom=data.value<float>();return;};
node->lch()->lch()->editable = true;

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

return node;
};

TreeNode * create_im_bro_params_tree(mj_im_bro_t * mj_ptr){
static mj_im_bro_t * mj = mj_ptr;
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
auto bup_dcu_lfd_ptr = node->add("bup_dcu_lfd",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
bup_dcu_lfd_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
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
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->values.append("cur_lim");
node->lch()->lch()->intval.append(0x55DA9773);
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->values.append("ohp_lvl");
node->lch()->lch()->intval.append(0x12DB50AA);
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->values.append("pole_pairs");
node->lch()->lch()->intval.append(0x393E0A69);
node->lch()->lch()->values.append("ph_resistance");
node->lch()->lch()->intval.append(0xD478FE43);
node->lch()->lch()->values.append("ph_inductance");
node->lch()->lch()->intval.append(0x5B351473);
node->lch()->lch()->values.append("brake_unlock_voltage");
node->lch()->lch()->intval.append(0x920D8F3B);
node->lch()->lch()->values.append("brake_unlock_time");
node->lch()->lch()->intval.append(0xD31E0ACB);
node->lch()->lch()->values.append("brake_hold_voltage");
node->lch()->lch()->intval.append(0x64399A99);
node->lch()->lch()->values.append("brake_lock_time");
node->lch()->lch()->intval.append(0x955BB624);
node->lch()->lch()->values.append("curr_kp");
node->lch()->lch()->intval.append(0x323FC775);
node->lch()->lch()->values.append("curr_ki");
node->lch()->lch()->intval.append(0x16A9255D);
node->lch()->lch()->values.append("curr_kb");
node->lch()->lch()->intval.append(0x80056521);
node->lch()->lch()->values.append("curr_kt");
node->lch()->lch()->intval.append(0xAD5D6E6E);
node->lch()->lch()->values.append("curr_kf");
node->lch()->lch()->intval.append(0x1F67CC3A);
node->lch()->lch()->values.append("curr_fc");
node->lch()->lch()->intval.append(0x9841D378);
node->lch()->lch()->values.append("curr_err_lim");
node->lch()->lch()->intval.append(0xCAF1DD24);
node->lch()->lch()->values.append("curr_out_lim");
node->lch()->lch()->intval.append(0x8D2D0B70);
node->lch()->lch()->values.append("curr_out_rate_lim");
node->lch()->lch()->intval.append(0x41824DD2);
node->lch()->lch()->values.append("curr_err_rate_lim");
node->lch()->lch()->intval.append(0x6EFAD7A0);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kd");
node->lch()->lch()->intval.append(0xA6070C18);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kd");
node->lch()->lch()->intval.append(0xB17A1B4D);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kd");
node->lch()->lch()->intval.append(0x5D94228B);
node->lch()->lch()->values.append("rotor_ang_kt");
node->lch()->lch()->intval.append(0x201F9189);
node->lch()->lch()->values.append("rotor_ang_kf");
node->lch()->lch()->intval.append(0x922533DD);
node->lch()->lch()->values.append("rotor_ang_err_lim");
node->lch()->lch()->intval.append(0x74081F2D);
node->lch()->lch()->values.append("rotor_ang_out_lim");
node->lch()->lch()->intval.append(0x33D4C979);
node->lch()->lch()->values.append("rotor_ang_out_rate_lim");
node->lch()->lch()->intval.append(0x28CABE88);
node->lch()->lch()->values.append("rotor_ang_err_rate_lim");
node->lch()->lch()->intval.append(0x7B224FA);
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->intval.append(0x925B41AA);
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
auto bup_dcu_lrd_ptr = node->add("bup_dcu_lrd",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
bup_dcu_lrd_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
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
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->values.append("cur_lim");
node->lch()->lch()->intval.append(0x55DA9773);
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->values.append("ohp_lvl");
node->lch()->lch()->intval.append(0x12DB50AA);
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->values.append("pole_pairs");
node->lch()->lch()->intval.append(0x393E0A69);
node->lch()->lch()->values.append("ph_resistance");
node->lch()->lch()->intval.append(0xD478FE43);
node->lch()->lch()->values.append("ph_inductance");
node->lch()->lch()->intval.append(0x5B351473);
node->lch()->lch()->values.append("brake_unlock_voltage");
node->lch()->lch()->intval.append(0x920D8F3B);
node->lch()->lch()->values.append("brake_unlock_time");
node->lch()->lch()->intval.append(0xD31E0ACB);
node->lch()->lch()->values.append("brake_hold_voltage");
node->lch()->lch()->intval.append(0x64399A99);
node->lch()->lch()->values.append("brake_lock_time");
node->lch()->lch()->intval.append(0x955BB624);
node->lch()->lch()->values.append("curr_kp");
node->lch()->lch()->intval.append(0x323FC775);
node->lch()->lch()->values.append("curr_ki");
node->lch()->lch()->intval.append(0x16A9255D);
node->lch()->lch()->values.append("curr_kb");
node->lch()->lch()->intval.append(0x80056521);
node->lch()->lch()->values.append("curr_kt");
node->lch()->lch()->intval.append(0xAD5D6E6E);
node->lch()->lch()->values.append("curr_kf");
node->lch()->lch()->intval.append(0x1F67CC3A);
node->lch()->lch()->values.append("curr_fc");
node->lch()->lch()->intval.append(0x9841D378);
node->lch()->lch()->values.append("curr_err_lim");
node->lch()->lch()->intval.append(0xCAF1DD24);
node->lch()->lch()->values.append("curr_out_lim");
node->lch()->lch()->intval.append(0x8D2D0B70);
node->lch()->lch()->values.append("curr_out_rate_lim");
node->lch()->lch()->intval.append(0x41824DD2);
node->lch()->lch()->values.append("curr_err_rate_lim");
node->lch()->lch()->intval.append(0x6EFAD7A0);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kd");
node->lch()->lch()->intval.append(0xA6070C18);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kd");
node->lch()->lch()->intval.append(0xB17A1B4D);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kd");
node->lch()->lch()->intval.append(0x5D94228B);
node->lch()->lch()->values.append("rotor_ang_kt");
node->lch()->lch()->intval.append(0x201F9189);
node->lch()->lch()->values.append("rotor_ang_kf");
node->lch()->lch()->intval.append(0x922533DD);
node->lch()->lch()->values.append("rotor_ang_err_lim");
node->lch()->lch()->intval.append(0x74081F2D);
node->lch()->lch()->values.append("rotor_ang_out_lim");
node->lch()->lch()->intval.append(0x33D4C979);
node->lch()->lch()->values.append("rotor_ang_out_rate_lim");
node->lch()->lch()->intval.append(0x28CABE88);
node->lch()->lch()->values.append("rotor_ang_err_rate_lim");
node->lch()->lch()->intval.append(0x7B224FA);
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->intval.append(0x925B41AA);
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
auto bup_dcu_lst_ptr = node->add("bup_dcu_lst",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
bup_dcu_lst_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
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
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->values.append("cur_lim");
node->lch()->lch()->intval.append(0x55DA9773);
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->values.append("ohp_lvl");
node->lch()->lch()->intval.append(0x12DB50AA);
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->values.append("pole_pairs");
node->lch()->lch()->intval.append(0x393E0A69);
node->lch()->lch()->values.append("ph_resistance");
node->lch()->lch()->intval.append(0xD478FE43);
node->lch()->lch()->values.append("ph_inductance");
node->lch()->lch()->intval.append(0x5B351473);
node->lch()->lch()->values.append("brake_unlock_voltage");
node->lch()->lch()->intval.append(0x920D8F3B);
node->lch()->lch()->values.append("brake_unlock_time");
node->lch()->lch()->intval.append(0xD31E0ACB);
node->lch()->lch()->values.append("brake_hold_voltage");
node->lch()->lch()->intval.append(0x64399A99);
node->lch()->lch()->values.append("brake_lock_time");
node->lch()->lch()->intval.append(0x955BB624);
node->lch()->lch()->values.append("curr_kp");
node->lch()->lch()->intval.append(0x323FC775);
node->lch()->lch()->values.append("curr_ki");
node->lch()->lch()->intval.append(0x16A9255D);
node->lch()->lch()->values.append("curr_kb");
node->lch()->lch()->intval.append(0x80056521);
node->lch()->lch()->values.append("curr_kt");
node->lch()->lch()->intval.append(0xAD5D6E6E);
node->lch()->lch()->values.append("curr_kf");
node->lch()->lch()->intval.append(0x1F67CC3A);
node->lch()->lch()->values.append("curr_fc");
node->lch()->lch()->intval.append(0x9841D378);
node->lch()->lch()->values.append("curr_err_lim");
node->lch()->lch()->intval.append(0xCAF1DD24);
node->lch()->lch()->values.append("curr_out_lim");
node->lch()->lch()->intval.append(0x8D2D0B70);
node->lch()->lch()->values.append("curr_out_rate_lim");
node->lch()->lch()->intval.append(0x41824DD2);
node->lch()->lch()->values.append("curr_err_rate_lim");
node->lch()->lch()->intval.append(0x6EFAD7A0);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kd");
node->lch()->lch()->intval.append(0xA6070C18);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kd");
node->lch()->lch()->intval.append(0xB17A1B4D);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kd");
node->lch()->lch()->intval.append(0x5D94228B);
node->lch()->lch()->values.append("rotor_ang_kt");
node->lch()->lch()->intval.append(0x201F9189);
node->lch()->lch()->values.append("rotor_ang_kf");
node->lch()->lch()->intval.append(0x922533DD);
node->lch()->lch()->values.append("rotor_ang_err_lim");
node->lch()->lch()->intval.append(0x74081F2D);
node->lch()->lch()->values.append("rotor_ang_out_lim");
node->lch()->lch()->intval.append(0x33D4C979);
node->lch()->lch()->values.append("rotor_ang_out_rate_lim");
node->lch()->lch()->intval.append(0x28CABE88);
node->lch()->lch()->values.append("rotor_ang_err_rate_lim");
node->lch()->lch()->intval.append(0x7B224FA);
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->intval.append(0x925B41AA);
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
auto bup_dcu_rfd_ptr = node->add("bup_dcu_rfd",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
bup_dcu_rfd_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
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
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->values.append("cur_lim");
node->lch()->lch()->intval.append(0x55DA9773);
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->values.append("ohp_lvl");
node->lch()->lch()->intval.append(0x12DB50AA);
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->values.append("pole_pairs");
node->lch()->lch()->intval.append(0x393E0A69);
node->lch()->lch()->values.append("ph_resistance");
node->lch()->lch()->intval.append(0xD478FE43);
node->lch()->lch()->values.append("ph_inductance");
node->lch()->lch()->intval.append(0x5B351473);
node->lch()->lch()->values.append("brake_unlock_voltage");
node->lch()->lch()->intval.append(0x920D8F3B);
node->lch()->lch()->values.append("brake_unlock_time");
node->lch()->lch()->intval.append(0xD31E0ACB);
node->lch()->lch()->values.append("brake_hold_voltage");
node->lch()->lch()->intval.append(0x64399A99);
node->lch()->lch()->values.append("brake_lock_time");
node->lch()->lch()->intval.append(0x955BB624);
node->lch()->lch()->values.append("curr_kp");
node->lch()->lch()->intval.append(0x323FC775);
node->lch()->lch()->values.append("curr_ki");
node->lch()->lch()->intval.append(0x16A9255D);
node->lch()->lch()->values.append("curr_kb");
node->lch()->lch()->intval.append(0x80056521);
node->lch()->lch()->values.append("curr_kt");
node->lch()->lch()->intval.append(0xAD5D6E6E);
node->lch()->lch()->values.append("curr_kf");
node->lch()->lch()->intval.append(0x1F67CC3A);
node->lch()->lch()->values.append("curr_fc");
node->lch()->lch()->intval.append(0x9841D378);
node->lch()->lch()->values.append("curr_err_lim");
node->lch()->lch()->intval.append(0xCAF1DD24);
node->lch()->lch()->values.append("curr_out_lim");
node->lch()->lch()->intval.append(0x8D2D0B70);
node->lch()->lch()->values.append("curr_out_rate_lim");
node->lch()->lch()->intval.append(0x41824DD2);
node->lch()->lch()->values.append("curr_err_rate_lim");
node->lch()->lch()->intval.append(0x6EFAD7A0);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kd");
node->lch()->lch()->intval.append(0xA6070C18);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kd");
node->lch()->lch()->intval.append(0xB17A1B4D);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kd");
node->lch()->lch()->intval.append(0x5D94228B);
node->lch()->lch()->values.append("rotor_ang_kt");
node->lch()->lch()->intval.append(0x201F9189);
node->lch()->lch()->values.append("rotor_ang_kf");
node->lch()->lch()->intval.append(0x922533DD);
node->lch()->lch()->values.append("rotor_ang_err_lim");
node->lch()->lch()->intval.append(0x74081F2D);
node->lch()->lch()->values.append("rotor_ang_out_lim");
node->lch()->lch()->intval.append(0x33D4C979);
node->lch()->lch()->values.append("rotor_ang_out_rate_lim");
node->lch()->lch()->intval.append(0x28CABE88);
node->lch()->lch()->values.append("rotor_ang_err_rate_lim");
node->lch()->lch()->intval.append(0x7B224FA);
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->intval.append(0x925B41AA);
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
auto bup_dcu_rrd_ptr = node->add("bup_dcu_rrd",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
bup_dcu_rrd_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
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
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->values.append("cur_lim");
node->lch()->lch()->intval.append(0x55DA9773);
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->values.append("ohp_lvl");
node->lch()->lch()->intval.append(0x12DB50AA);
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->values.append("pole_pairs");
node->lch()->lch()->intval.append(0x393E0A69);
node->lch()->lch()->values.append("ph_resistance");
node->lch()->lch()->intval.append(0xD478FE43);
node->lch()->lch()->values.append("ph_inductance");
node->lch()->lch()->intval.append(0x5B351473);
node->lch()->lch()->values.append("brake_unlock_voltage");
node->lch()->lch()->intval.append(0x920D8F3B);
node->lch()->lch()->values.append("brake_unlock_time");
node->lch()->lch()->intval.append(0xD31E0ACB);
node->lch()->lch()->values.append("brake_hold_voltage");
node->lch()->lch()->intval.append(0x64399A99);
node->lch()->lch()->values.append("brake_lock_time");
node->lch()->lch()->intval.append(0x955BB624);
node->lch()->lch()->values.append("curr_kp");
node->lch()->lch()->intval.append(0x323FC775);
node->lch()->lch()->values.append("curr_ki");
node->lch()->lch()->intval.append(0x16A9255D);
node->lch()->lch()->values.append("curr_kb");
node->lch()->lch()->intval.append(0x80056521);
node->lch()->lch()->values.append("curr_kt");
node->lch()->lch()->intval.append(0xAD5D6E6E);
node->lch()->lch()->values.append("curr_kf");
node->lch()->lch()->intval.append(0x1F67CC3A);
node->lch()->lch()->values.append("curr_fc");
node->lch()->lch()->intval.append(0x9841D378);
node->lch()->lch()->values.append("curr_err_lim");
node->lch()->lch()->intval.append(0xCAF1DD24);
node->lch()->lch()->values.append("curr_out_lim");
node->lch()->lch()->intval.append(0x8D2D0B70);
node->lch()->lch()->values.append("curr_out_rate_lim");
node->lch()->lch()->intval.append(0x41824DD2);
node->lch()->lch()->values.append("curr_err_rate_lim");
node->lch()->lch()->intval.append(0x6EFAD7A0);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kd");
node->lch()->lch()->intval.append(0xA6070C18);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kd");
node->lch()->lch()->intval.append(0xB17A1B4D);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kd");
node->lch()->lch()->intval.append(0x5D94228B);
node->lch()->lch()->values.append("rotor_ang_kt");
node->lch()->lch()->intval.append(0x201F9189);
node->lch()->lch()->values.append("rotor_ang_kf");
node->lch()->lch()->intval.append(0x922533DD);
node->lch()->lch()->values.append("rotor_ang_err_lim");
node->lch()->lch()->intval.append(0x74081F2D);
node->lch()->lch()->values.append("rotor_ang_out_lim");
node->lch()->lch()->intval.append(0x33D4C979);
node->lch()->lch()->values.append("rotor_ang_out_rate_lim");
node->lch()->lch()->intval.append(0x28CABE88);
node->lch()->lch()->values.append("rotor_ang_err_rate_lim");
node->lch()->lch()->intval.append(0x7B224FA);
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->intval.append(0x925B41AA);
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
auto bup_dcu_rst_ptr = node->add("bup_dcu_rst",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
bup_dcu_rst_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
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
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->values.append("cur_lim");
node->lch()->lch()->intval.append(0x55DA9773);
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->values.append("ohp_lvl");
node->lch()->lch()->intval.append(0x12DB50AA);
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->values.append("pole_pairs");
node->lch()->lch()->intval.append(0x393E0A69);
node->lch()->lch()->values.append("ph_resistance");
node->lch()->lch()->intval.append(0xD478FE43);
node->lch()->lch()->values.append("ph_inductance");
node->lch()->lch()->intval.append(0x5B351473);
node->lch()->lch()->values.append("brake_unlock_voltage");
node->lch()->lch()->intval.append(0x920D8F3B);
node->lch()->lch()->values.append("brake_unlock_time");
node->lch()->lch()->intval.append(0xD31E0ACB);
node->lch()->lch()->values.append("brake_hold_voltage");
node->lch()->lch()->intval.append(0x64399A99);
node->lch()->lch()->values.append("brake_lock_time");
node->lch()->lch()->intval.append(0x955BB624);
node->lch()->lch()->values.append("curr_kp");
node->lch()->lch()->intval.append(0x323FC775);
node->lch()->lch()->values.append("curr_ki");
node->lch()->lch()->intval.append(0x16A9255D);
node->lch()->lch()->values.append("curr_kb");
node->lch()->lch()->intval.append(0x80056521);
node->lch()->lch()->values.append("curr_kt");
node->lch()->lch()->intval.append(0xAD5D6E6E);
node->lch()->lch()->values.append("curr_kf");
node->lch()->lch()->intval.append(0x1F67CC3A);
node->lch()->lch()->values.append("curr_fc");
node->lch()->lch()->intval.append(0x9841D378);
node->lch()->lch()->values.append("curr_err_lim");
node->lch()->lch()->intval.append(0xCAF1DD24);
node->lch()->lch()->values.append("curr_out_lim");
node->lch()->lch()->intval.append(0x8D2D0B70);
node->lch()->lch()->values.append("curr_out_rate_lim");
node->lch()->lch()->intval.append(0x41824DD2);
node->lch()->lch()->values.append("curr_err_rate_lim");
node->lch()->lch()->intval.append(0x6EFAD7A0);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kd");
node->lch()->lch()->intval.append(0xA6070C18);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kd");
node->lch()->lch()->intval.append(0xB17A1B4D);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kd");
node->lch()->lch()->intval.append(0x5D94228B);
node->lch()->lch()->values.append("rotor_ang_kt");
node->lch()->lch()->intval.append(0x201F9189);
node->lch()->lch()->values.append("rotor_ang_kf");
node->lch()->lch()->intval.append(0x922533DD);
node->lch()->lch()->values.append("rotor_ang_err_lim");
node->lch()->lch()->intval.append(0x74081F2D);
node->lch()->lch()->values.append("rotor_ang_out_lim");
node->lch()->lch()->intval.append(0x33D4C979);
node->lch()->lch()->values.append("rotor_ang_out_rate_lim");
node->lch()->lch()->intval.append(0x28CABE88);
node->lch()->lch()->values.append("rotor_ang_err_rate_lim");
node->lch()->lch()->intval.append(0x7B224FA);
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->intval.append(0x925B41AA);
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
auto dcu_ptr = node->add("dcu",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
dcu_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
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
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->values.append("cur_lim");
node->lch()->lch()->intval.append(0x55DA9773);
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->values.append("ohp_lvl");
node->lch()->lch()->intval.append(0x12DB50AA);
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->values.append("pole_pairs");
node->lch()->lch()->intval.append(0x393E0A69);
node->lch()->lch()->values.append("ph_resistance");
node->lch()->lch()->intval.append(0xD478FE43);
node->lch()->lch()->values.append("ph_inductance");
node->lch()->lch()->intval.append(0x5B351473);
node->lch()->lch()->values.append("brake_unlock_voltage");
node->lch()->lch()->intval.append(0x920D8F3B);
node->lch()->lch()->values.append("brake_unlock_time");
node->lch()->lch()->intval.append(0xD31E0ACB);
node->lch()->lch()->values.append("brake_hold_voltage");
node->lch()->lch()->intval.append(0x64399A99);
node->lch()->lch()->values.append("brake_lock_time");
node->lch()->lch()->intval.append(0x955BB624);
node->lch()->lch()->values.append("curr_kp");
node->lch()->lch()->intval.append(0x323FC775);
node->lch()->lch()->values.append("curr_ki");
node->lch()->lch()->intval.append(0x16A9255D);
node->lch()->lch()->values.append("curr_kb");
node->lch()->lch()->intval.append(0x80056521);
node->lch()->lch()->values.append("curr_kt");
node->lch()->lch()->intval.append(0xAD5D6E6E);
node->lch()->lch()->values.append("curr_kf");
node->lch()->lch()->intval.append(0x1F67CC3A);
node->lch()->lch()->values.append("curr_fc");
node->lch()->lch()->intval.append(0x9841D378);
node->lch()->lch()->values.append("curr_err_lim");
node->lch()->lch()->intval.append(0xCAF1DD24);
node->lch()->lch()->values.append("curr_out_lim");
node->lch()->lch()->intval.append(0x8D2D0B70);
node->lch()->lch()->values.append("curr_out_rate_lim");
node->lch()->lch()->intval.append(0x41824DD2);
node->lch()->lch()->values.append("curr_err_rate_lim");
node->lch()->lch()->intval.append(0x6EFAD7A0);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kd");
node->lch()->lch()->intval.append(0xA6070C18);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kd");
node->lch()->lch()->intval.append(0xB17A1B4D);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kd");
node->lch()->lch()->intval.append(0x5D94228B);
node->lch()->lch()->values.append("rotor_ang_kt");
node->lch()->lch()->intval.append(0x201F9189);
node->lch()->lch()->values.append("rotor_ang_kf");
node->lch()->lch()->intval.append(0x922533DD);
node->lch()->lch()->values.append("rotor_ang_err_lim");
node->lch()->lch()->intval.append(0x74081F2D);
node->lch()->lch()->values.append("rotor_ang_out_lim");
node->lch()->lch()->intval.append(0x33D4C979);
node->lch()->lch()->values.append("rotor_ang_out_rate_lim");
node->lch()->lch()->intval.append(0x28CABE88);
node->lch()->lch()->values.append("rotor_ang_err_rate_lim");
node->lch()->lch()->intval.append(0x7B224FA);
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->intval.append(0x925B41AA);
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