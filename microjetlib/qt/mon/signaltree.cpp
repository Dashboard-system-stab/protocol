
#include "signaltree.h"

static TreeNode *aufd_cmd_ans_ptr = 0;
static TreeNode *aufd_formular_ptr = 0;
static TreeNode *aufd_msg_ans_ptr = 0;
static TreeNode *aufd_prm_ans_ptr = 0;
static TreeNode *bup_dcu_lfd_bup_state_ptr = 0;
static TreeNode *bup_dcu_lfd_cmd_ans_ptr = 0;
static TreeNode *bup_dcu_lfd_dbg_ptr = 0;
static TreeNode *bup_dcu_lfd_dcu_tel_ptr = 0;
static TreeNode *bup_dcu_lfd_formular_ptr = 0;
static TreeNode *bup_dcu_lfd_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_lfd_msg_ans_ptr = 0;
static TreeNode *bup_dcu_lfd_prm_ans_ptr = 0;
static TreeNode *bup_dcu_lfd_ptp_state_ptr = 0;
static TreeNode *bup_dcu_lrd_bup_state_ptr = 0;
static TreeNode *bup_dcu_lrd_cmd_ans_ptr = 0;
static TreeNode *bup_dcu_lrd_dbg_ptr = 0;
static TreeNode *bup_dcu_lrd_dcu_tel_ptr = 0;
static TreeNode *bup_dcu_lrd_formular_ptr = 0;
static TreeNode *bup_dcu_lrd_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_lrd_msg_ans_ptr = 0;
static TreeNode *bup_dcu_lrd_prm_ans_ptr = 0;
static TreeNode *bup_dcu_lrd_ptp_state_ptr = 0;
static TreeNode *bup_dcu_lst_bup_state_ptr = 0;
static TreeNode *bup_dcu_lst_cmd_ans_ptr = 0;
static TreeNode *bup_dcu_lst_dbg_ptr = 0;
static TreeNode *bup_dcu_lst_dcu_tel_ptr = 0;
static TreeNode *bup_dcu_lst_formular_ptr = 0;
static TreeNode *bup_dcu_lst_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_lst_msg_ans_ptr = 0;
static TreeNode *bup_dcu_lst_prm_ans_ptr = 0;
static TreeNode *bup_dcu_lst_ptp_state_ptr = 0;
static TreeNode *bup_dcu_rfd_bup_state_ptr = 0;
static TreeNode *bup_dcu_rfd_cmd_ans_ptr = 0;
static TreeNode *bup_dcu_rfd_dbg_ptr = 0;
static TreeNode *bup_dcu_rfd_dcu_tel_ptr = 0;
static TreeNode *bup_dcu_rfd_formular_ptr = 0;
static TreeNode *bup_dcu_rfd_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_rfd_msg_ans_ptr = 0;
static TreeNode *bup_dcu_rfd_prm_ans_ptr = 0;
static TreeNode *bup_dcu_rfd_ptp_state_ptr = 0;
static TreeNode *bup_dcu_rrd_bup_state_ptr = 0;
static TreeNode *bup_dcu_rrd_cmd_ans_ptr = 0;
static TreeNode *bup_dcu_rrd_dbg_ptr = 0;
static TreeNode *bup_dcu_rrd_dcu_tel_ptr = 0;
static TreeNode *bup_dcu_rrd_formular_ptr = 0;
static TreeNode *bup_dcu_rrd_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_rrd_msg_ans_ptr = 0;
static TreeNode *bup_dcu_rrd_prm_ans_ptr = 0;
static TreeNode *bup_dcu_rrd_ptp_state_ptr = 0;
static TreeNode *bup_dcu_rst_bup_state_ptr = 0;
static TreeNode *bup_dcu_rst_cmd_ans_ptr = 0;
static TreeNode *bup_dcu_rst_dbg_ptr = 0;
static TreeNode *bup_dcu_rst_dcu_tel_ptr = 0;
static TreeNode *bup_dcu_rst_formular_ptr = 0;
static TreeNode *bup_dcu_rst_im_bro_drive_ctrl_ptr = 0;
static TreeNode *bup_dcu_rst_msg_ans_ptr = 0;
static TreeNode *bup_dcu_rst_prm_ans_ptr = 0;
static TreeNode *bup_dcu_rst_ptp_state_ptr = 0;
static TreeNode *dcu_bup_state_ptr = 0;
static TreeNode *dcu_cmd_ans_ptr = 0;
static TreeNode *dcu_dbg_ptr = 0;
static TreeNode *dcu_dcu_tel_ptr = 0;
static TreeNode *dcu_formular_ptr = 0;
static TreeNode *dcu_im_bro_drive_ctrl_ptr = 0;
static TreeNode *dcu_msg_ans_ptr = 0;
static TreeNode *dcu_prm_ans_ptr = 0;
static TreeNode *dcu_ptp_state_ptr = 0;
static TreeNode *im_bro_im_bro_drivers_sens_ptr = 0;
static TreeNode *im_bro_prm_ans_ptr = 0;

static TreeNode *bup_srv_ctrl_ptr = 0;
static TreeNode *cmd_req_ptr = 0;
static TreeNode *msg_req_ptr = 0;
static TreeNode *prm_req_ptr = 0;

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


TreeNode * create_mon_in_tree(mj_mon_t * mj_ptr)
{
static mj_mon_t *mj = mj_ptr;
TreeNode * node = new TreeNode("INPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
TreeNode * aufd_node = node->add("aufd",[](){return QVariant();});
aufd_node->isDev = true;
aufd_cmd_ans_ptr = node->lch()->add("cmd_ans",[](){return QVariant(mj->in.aufd.cmd_ans.msg->hdr.cnt);});
aufd_cmd_ans_ptr->state = []()->int32_t{return mj->in.aufd.cmd_ans.state;};
aufd_cmd_ans_ptr->msgId = ID_CMD_ANS;
aufd_cmd_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.cmd_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.cmd_ans.msg->hdr.ts_ns)/1e9);});

aufd_cmd_ans_ptr->isReq = true;
aufd_cmd_ans_ptr->srcId = BRO30_AUFD;
node->lch()->lch()->add("command",[](){return QVariant((int32_t)(mj->in.aufd.cmd_ans.msg->command));},[](){return (command_type_str(mj->in.aufd.cmd_ans.msg->command));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.aufd.cmd_ans.msg->state));},[](){return (command_state_str(mj->in.aufd.cmd_ans.msg->state));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.aufd.cmd_ans.msg->cnt);});
node->lch()->lch()->add("info",[](){return QVariant(cp866ToQString(mj->in.aufd.cmd_ans.msg->info,sizeof(mj->in.aufd.cmd_ans.msg->info)));});
mj->in.aufd.cmd_ans.upd_cb = [](){ aufd_cmd_ans_ptr->upd(mj->in.aufd.cmd_ans.ts_s, mj->in.aufd.cmd_ans.ts_ns);};
aufd_formular_ptr = node->lch()->add("formular",[](){return QVariant(mj->in.aufd.formular.msg->hdr.cnt);});
aufd_formular_ptr->state = []()->int32_t{return mj->in.aufd.formular.state;};
aufd_formular_ptr->msgId = ID_FORMULAR;
aufd_formular_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.formular.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.formular.msg->hdr.ts_ns)/1e9);});

aufd_formular_ptr->isReq = true;
aufd_formular_ptr->srcId = BRO30_AUFD;
node->lch()->lch()->add("description",[](){return QVariant(cp866ToQString(mj->in.aufd.formular.msg->description,sizeof(mj->in.aufd.formular.msg->description)));});
node->lch()->lch()->add("factory_number",[](){return QVariant(cp866ToQString(mj->in.aufd.formular.msg->factory_number,sizeof(mj->in.aufd.formular.msg->factory_number)));});
node->lch()->lch()->add("factory_date",[](){return QVariant(cp866ToQString(mj->in.aufd.formular.msg->factory_date,sizeof(mj->in.aufd.formular.msg->factory_date)));});
node->lch()->lch()->add("software_version",[](){return QVariant(cp866ToQString(mj->in.aufd.formular.msg->software_version,sizeof(mj->in.aufd.formular.msg->software_version)));});
node->lch()->lch()->add("protocol_version",[](){return QVariant(cp866ToQString(mj->in.aufd.formular.msg->protocol_version,sizeof(mj->in.aufd.formular.msg->protocol_version)));});
node->lch()->lch()->add("GUID",[](){return QVariant(cp866ToQString(mj->in.aufd.formular.msg->GUID,sizeof(mj->in.aufd.formular.msg->GUID)));});
node->lch()->lch()->add("operation_time",[](){return QVariant(mj->in.aufd.formular.msg->operation_time);});
node->lch()->lch()->add("software_checksum",[](){return QVariant(cp866ToQString(mj->in.aufd.formular.msg->software_checksum,sizeof(mj->in.aufd.formular.msg->software_checksum)));});
node->lch()->lch()->add("code",[](){return QVariant(mj->in.aufd.formular.msg->code);});
mj->in.aufd.formular.upd_cb = [](){ aufd_formular_ptr->upd(mj->in.aufd.formular.ts_s, mj->in.aufd.formular.ts_ns);};
aufd_msg_ans_ptr = node->lch()->add("msg_ans",[](){return QVariant(mj->in.aufd.msg_ans.msg->hdr.cnt);});
aufd_msg_ans_ptr->state = []()->int32_t{return mj->in.aufd.msg_ans.state;};
aufd_msg_ans_ptr->msgId = ID_MSG_ANS;
aufd_msg_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.msg_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.msg_ans.msg->hdr.ts_ns)/1e9);});

aufd_msg_ans_ptr->isReq = true;
aufd_msg_ans_ptr->srcId = BRO30_AUFD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.aufd.msg_ans.msg->id));},[](){return (mj_get_msg_name(mj->in.aufd.msg_ans.msg->id));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.aufd.msg_ans.msg->cnt);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.aufd.msg_ans.msg->state));},[](){return (msg_state_str(mj->in.aufd.msg_ans.msg->state));});
mj->in.aufd.msg_ans.upd_cb = [](){ aufd_msg_ans_ptr->upd(mj->in.aufd.msg_ans.ts_s, mj->in.aufd.msg_ans.ts_ns);};
aufd_prm_ans_ptr = node->lch()->add("prm_ans",[](){return QVariant(mj->in.aufd.prm_ans.msg->hdr.cnt);});
aufd_prm_ans_ptr->state = []()->int32_t{return mj->in.aufd.prm_ans.state;};
aufd_prm_ans_ptr->msgId = ID_PRM_ANS;
aufd_prm_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.prm_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.prm_ans.msg->hdr.ts_ns)/1e9);});

aufd_prm_ans_ptr->isReq = true;
aufd_prm_ans_ptr->srcId = BRO30_AUFD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.aufd.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->in.aufd.prm_ans.msg->id));});
node->lch()->lch()->add("ans",[](){return QVariant((int32_t)(mj->in.aufd.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->in.aufd.prm_ans.msg->ans));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.aufd.prm_ans.msg->id,(uint8_t*)mj->in.aufd.prm_ans.msg->val,sizeof(mj->in.aufd.prm_ans.msg->val)));});
mj->in.aufd.prm_ans.upd_cb = [](){ aufd_prm_ans_ptr->upd(mj->in.aufd.prm_ans.ts_s, mj->in.aufd.prm_ans.ts_ns);};
TreeNode * bup_dcu_lfd_node = node->add("bup_dcu_lfd",[](){return QVariant();});
bup_dcu_lfd_node->isDev = true;
bup_dcu_lfd_bup_state_ptr = node->lch()->add("bup_state",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->hdr.cnt);});
bup_dcu_lfd_bup_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.bup_state.state;};
bup_dcu_lfd_bup_state_ptr->msgId = ID_BUP_STATE;
bup_dcu_lfd_bup_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.bup_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.bup_state.msg->hdr.ts_ns)/1e9);});

bup_dcu_lfd_bup_state_ptr->isReq = true;
bup_dcu_lfd_bup_state_ptr->srcId = BRO30_BUP_DCU_LFD;
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.bup_state.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_lfd.bup_state.msg->mode));});
node->lch()->lch()->add("error",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.bup_state.msg->error));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_lfd.bup_state.msg->error));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.bup_state.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_lfd.bup_state.msg->status));});
node->lch()->lch()->add("limit",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.bup_state.msg->limit));},[](){return (move_limit_state_str(mj->in.bup_dcu_lfd.bup_state.msg->limit));});
node->lch()->lch()->add("angle",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->angle);});
node->lch()->lch()->add("speed",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->speed);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.bup_state.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_lfd.bup_state.msg->brake_state));});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->electrical_power);});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.bup_state.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_lfd.bup_state.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->load_sens_speed);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.bup_state.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_lfd.bup_state.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_lfd.bup_state.msg->rotor_sens_speed);});
mj->in.bup_dcu_lfd.bup_state.upd_cb = [](){ bup_dcu_lfd_bup_state_ptr->upd(mj->in.bup_dcu_lfd.bup_state.ts_s, mj->in.bup_dcu_lfd.bup_state.ts_ns);};
bup_dcu_lfd_cmd_ans_ptr = node->lch()->add("cmd_ans",[](){return QVariant(mj->in.bup_dcu_lfd.cmd_ans.msg->hdr.cnt);});
bup_dcu_lfd_cmd_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.cmd_ans.state;};
bup_dcu_lfd_cmd_ans_ptr->msgId = ID_CMD_ANS;
bup_dcu_lfd_cmd_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.cmd_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.cmd_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_lfd_cmd_ans_ptr->isReq = true;
bup_dcu_lfd_cmd_ans_ptr->srcId = BRO30_BUP_DCU_LFD;
node->lch()->lch()->add("command",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.cmd_ans.msg->command));},[](){return (command_type_str(mj->in.bup_dcu_lfd.cmd_ans.msg->command));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.cmd_ans.msg->state));},[](){return (command_state_str(mj->in.bup_dcu_lfd.cmd_ans.msg->state));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_lfd.cmd_ans.msg->cnt);});
node->lch()->lch()->add("info",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lfd.cmd_ans.msg->info,sizeof(mj->in.bup_dcu_lfd.cmd_ans.msg->info)));});
mj->in.bup_dcu_lfd.cmd_ans.upd_cb = [](){ bup_dcu_lfd_cmd_ans_ptr->upd(mj->in.bup_dcu_lfd.cmd_ans.ts_s, mj->in.bup_dcu_lfd.cmd_ans.ts_ns);};
bup_dcu_lfd_dbg_ptr = node->lch()->add("dbg",[](){return QVariant(mj->in.bup_dcu_lfd.dbg.msg->hdr.cnt);});
bup_dcu_lfd_dbg_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.dbg.state;};
bup_dcu_lfd_dbg_ptr->msgId = ID_DBG;
bup_dcu_lfd_dbg_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.dbg.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.dbg.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("fval",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_lfd.dbg.msg->fval[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_lfd.dbg.msg->fval[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_lfd.dbg.msg->fval[2]);});
node->lch()->lch()->lch()->add("[3]",[](){return QVariant(mj->in.bup_dcu_lfd.dbg.msg->fval[3]);});
node->lch()->lch()->lch()->add("[4]",[](){return QVariant(mj->in.bup_dcu_lfd.dbg.msg->fval[4]);});
mj->in.bup_dcu_lfd.dbg.upd_cb = [](){ bup_dcu_lfd_dbg_ptr->upd(mj->in.bup_dcu_lfd.dbg.ts_s, mj->in.bup_dcu_lfd.dbg.ts_ns);};
bup_dcu_lfd_dcu_tel_ptr = node->lch()->add("dcu_tel",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->hdr.cnt);});
bup_dcu_lfd_dcu_tel_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.dcu_tel.state;};
bup_dcu_lfd_dcu_tel_ptr->msgId = ID_DCU_TEL;
bup_dcu_lfd_dcu_tel_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.dcu_tel.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.dcu_tel.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_lfd.dcu_tel.msg->mode));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_lfd.dcu_tel.msg->status));});
node->lch()->lch()->add("err",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->err));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_lfd.dcu_tel.msg->err));});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_lfd.dcu_tel.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->load_sens_speed);});
node->lch()->lch()->add("power_vdc",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->power_vdc);});
node->lch()->lch()->add("current",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->current.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->current.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->current.c);});
node->lch()->lch()->add("pwm",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->pwm.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->pwm.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->pwm.c);});
node->lch()->lch()->add("park_current",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->park_current.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->park_current.q);});
node->lch()->lch()->add("park_voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->park_voltage.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->park_voltage.q);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_lfd.dcu_tel.msg->brake_state));});
node->lch()->lch()->add("ibrk",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->ibrk);});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->electrical_power);});
node->lch()->lch()->add("ang_pid_err",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->ang_pid_err);});
node->lch()->lch()->add("ang_pid_in",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->ang_pid_in);});
node->lch()->lch()->add("ang_pid_out",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->ang_pid_out);});
node->lch()->lch()->add("ang_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->ang_pid_intgr);});
node->lch()->lch()->add("rotor_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->rotor_spd_pid_err);});
node->lch()->lch()->add("rotor_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->rotor_spd_pid_in);});
node->lch()->lch()->add("rotor_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->rotor_spd_pid_out);});
node->lch()->lch()->add("rotor_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->rotor_spd_pid_intgr);});
node->lch()->lch()->add("load_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->load_spd_pid_err);});
node->lch()->lch()->add("load_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->load_spd_pid_in);});
node->lch()->lch()->add("load_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->load_spd_pid_out);});
node->lch()->lch()->add("load_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->load_spd_pid_intgr);});
node->lch()->lch()->add("curr_pid_err",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->curr_pid_err);});
node->lch()->lch()->add("curr_pid_in",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->curr_pid_in);});
node->lch()->lch()->add("curr_pid_out",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->curr_pid_out);});
node->lch()->lch()->add("curr_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->curr_pid_intgr);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_lfd.dcu_tel.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_lfd.dcu_tel.msg->rotor_sens_speed);});
node->lch()->lch()->add("on",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->on));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lfd.dcu_tel.msg->on));});
node->lch()->lch()->add("manual",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->manual));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lfd.dcu_tel.msg->manual));});
node->lch()->lch()->add("block",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->block));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lfd.dcu_tel.msg->block));});
node->lch()->lch()->add("sync",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->sync));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lfd.dcu_tel.msg->sync));});
node->lch()->lch()->add("inv_octw",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->inv_octw));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lfd.dcu_tel.msg->inv_octw));});
node->lch()->lch()->add("inv_fault",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->inv_fault));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lfd.dcu_tel.msg->inv_fault));});
node->lch()->lch()->add("en_gate",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.dcu_tel.msg->en_gate));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lfd.dcu_tel.msg->en_gate));});
mj->in.bup_dcu_lfd.dcu_tel.upd_cb = [](){ bup_dcu_lfd_dcu_tel_ptr->upd(mj->in.bup_dcu_lfd.dcu_tel.ts_s, mj->in.bup_dcu_lfd.dcu_tel.ts_ns);};
bup_dcu_lfd_formular_ptr = node->lch()->add("formular",[](){return QVariant(mj->in.bup_dcu_lfd.formular.msg->hdr.cnt);});
bup_dcu_lfd_formular_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.formular.state;};
bup_dcu_lfd_formular_ptr->msgId = ID_FORMULAR;
bup_dcu_lfd_formular_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.formular.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.formular.msg->hdr.ts_ns)/1e9);});

bup_dcu_lfd_formular_ptr->isReq = true;
bup_dcu_lfd_formular_ptr->srcId = BRO30_BUP_DCU_LFD;
node->lch()->lch()->add("description",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lfd.formular.msg->description,sizeof(mj->in.bup_dcu_lfd.formular.msg->description)));});
node->lch()->lch()->add("factory_number",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lfd.formular.msg->factory_number,sizeof(mj->in.bup_dcu_lfd.formular.msg->factory_number)));});
node->lch()->lch()->add("factory_date",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lfd.formular.msg->factory_date,sizeof(mj->in.bup_dcu_lfd.formular.msg->factory_date)));});
node->lch()->lch()->add("software_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lfd.formular.msg->software_version,sizeof(mj->in.bup_dcu_lfd.formular.msg->software_version)));});
node->lch()->lch()->add("protocol_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lfd.formular.msg->protocol_version,sizeof(mj->in.bup_dcu_lfd.formular.msg->protocol_version)));});
node->lch()->lch()->add("GUID",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lfd.formular.msg->GUID,sizeof(mj->in.bup_dcu_lfd.formular.msg->GUID)));});
node->lch()->lch()->add("operation_time",[](){return QVariant(mj->in.bup_dcu_lfd.formular.msg->operation_time);});
node->lch()->lch()->add("software_checksum",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lfd.formular.msg->software_checksum,sizeof(mj->in.bup_dcu_lfd.formular.msg->software_checksum)));});
node->lch()->lch()->add("code",[](){return QVariant(mj->in.bup_dcu_lfd.formular.msg->code);});
mj->in.bup_dcu_lfd.formular.upd_cb = [](){ bup_dcu_lfd_formular_ptr->upd(mj->in.bup_dcu_lfd.formular.ts_s, mj->in.bup_dcu_lfd.formular.ts_ns);};
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
bup_dcu_lfd_msg_ans_ptr = node->lch()->add("msg_ans",[](){return QVariant(mj->in.bup_dcu_lfd.msg_ans.msg->hdr.cnt);});
bup_dcu_lfd_msg_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.msg_ans.state;};
bup_dcu_lfd_msg_ans_ptr->msgId = ID_MSG_ANS;
bup_dcu_lfd_msg_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.msg_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.msg_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_lfd_msg_ans_ptr->isReq = true;
bup_dcu_lfd_msg_ans_ptr->srcId = BRO30_BUP_DCU_LFD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.msg_ans.msg->id));},[](){return (mj_get_msg_name(mj->in.bup_dcu_lfd.msg_ans.msg->id));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_lfd.msg_ans.msg->cnt);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.msg_ans.msg->state));},[](){return (msg_state_str(mj->in.bup_dcu_lfd.msg_ans.msg->state));});
mj->in.bup_dcu_lfd.msg_ans.upd_cb = [](){ bup_dcu_lfd_msg_ans_ptr->upd(mj->in.bup_dcu_lfd.msg_ans.ts_s, mj->in.bup_dcu_lfd.msg_ans.ts_ns);};
bup_dcu_lfd_prm_ans_ptr = node->lch()->add("prm_ans",[](){return QVariant(mj->in.bup_dcu_lfd.prm_ans.msg->hdr.cnt);});
bup_dcu_lfd_prm_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.prm_ans.state;};
bup_dcu_lfd_prm_ans_ptr->msgId = ID_PRM_ANS;
bup_dcu_lfd_prm_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.prm_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.prm_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_lfd_prm_ans_ptr->isReq = true;
bup_dcu_lfd_prm_ans_ptr->srcId = BRO30_BUP_DCU_LFD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->in.bup_dcu_lfd.prm_ans.msg->id));});
node->lch()->lch()->add("ans",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->in.bup_dcu_lfd.prm_ans.msg->ans));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.bup_dcu_lfd.prm_ans.msg->id,(uint8_t*)mj->in.bup_dcu_lfd.prm_ans.msg->val,sizeof(mj->in.bup_dcu_lfd.prm_ans.msg->val)));});
mj->in.bup_dcu_lfd.prm_ans.upd_cb = [](){ bup_dcu_lfd_prm_ans_ptr->upd(mj->in.bup_dcu_lfd.prm_ans.ts_s, mj->in.bup_dcu_lfd.prm_ans.ts_ns);};
bup_dcu_lfd_ptp_state_ptr = node->lch()->add("ptp_state",[](){return QVariant(mj->in.bup_dcu_lfd.ptp_state.msg->hdr.cnt);});
bup_dcu_lfd_ptp_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.ptp_state.state;};
bup_dcu_lfd_ptp_state_ptr->msgId = ID_PTP_STATE;
bup_dcu_lfd_ptp_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.ptp_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.ptp_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("is_master",[](){return QVariant(mj->in.bup_dcu_lfd.ptp_state.msg->is_master);});
node->lch()->lch()->add("path_delay",[](){return QVariant(mj->in.bup_dcu_lfd.ptp_state.msg->path_delay);});
node->lch()->lch()->add("offset_ns",[](){return QVariant(mj->in.bup_dcu_lfd.ptp_state.msg->offset_ns);});
node->lch()->lch()->add("mean_offset_ns",[](){return QVariant(mj->in.bup_dcu_lfd.ptp_state.msg->mean_offset_ns);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lfd.ptp_state.msg->state));},[](){return (sync_state_str(mj->in.bup_dcu_lfd.ptp_state.msg->state));});
mj->in.bup_dcu_lfd.ptp_state.upd_cb = [](){ bup_dcu_lfd_ptp_state_ptr->upd(mj->in.bup_dcu_lfd.ptp_state.ts_s, mj->in.bup_dcu_lfd.ptp_state.ts_ns);};
TreeNode * bup_dcu_lrd_node = node->add("bup_dcu_lrd",[](){return QVariant();});
bup_dcu_lrd_node->isDev = true;
bup_dcu_lrd_bup_state_ptr = node->lch()->add("bup_state",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->hdr.cnt);});
bup_dcu_lrd_bup_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.bup_state.state;};
bup_dcu_lrd_bup_state_ptr->msgId = ID_BUP_STATE;
bup_dcu_lrd_bup_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.bup_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.bup_state.msg->hdr.ts_ns)/1e9);});

bup_dcu_lrd_bup_state_ptr->isReq = true;
bup_dcu_lrd_bup_state_ptr->srcId = BRO30_BUP_DCU_LRD;
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.bup_state.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_lrd.bup_state.msg->mode));});
node->lch()->lch()->add("error",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.bup_state.msg->error));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_lrd.bup_state.msg->error));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.bup_state.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_lrd.bup_state.msg->status));});
node->lch()->lch()->add("limit",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.bup_state.msg->limit));},[](){return (move_limit_state_str(mj->in.bup_dcu_lrd.bup_state.msg->limit));});
node->lch()->lch()->add("angle",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->angle);});
node->lch()->lch()->add("speed",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->speed);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.bup_state.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_lrd.bup_state.msg->brake_state));});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->electrical_power);});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.bup_state.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_lrd.bup_state.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->load_sens_speed);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.bup_state.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_lrd.bup_state.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_lrd.bup_state.msg->rotor_sens_speed);});
mj->in.bup_dcu_lrd.bup_state.upd_cb = [](){ bup_dcu_lrd_bup_state_ptr->upd(mj->in.bup_dcu_lrd.bup_state.ts_s, mj->in.bup_dcu_lrd.bup_state.ts_ns);};
bup_dcu_lrd_cmd_ans_ptr = node->lch()->add("cmd_ans",[](){return QVariant(mj->in.bup_dcu_lrd.cmd_ans.msg->hdr.cnt);});
bup_dcu_lrd_cmd_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.cmd_ans.state;};
bup_dcu_lrd_cmd_ans_ptr->msgId = ID_CMD_ANS;
bup_dcu_lrd_cmd_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.cmd_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.cmd_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_lrd_cmd_ans_ptr->isReq = true;
bup_dcu_lrd_cmd_ans_ptr->srcId = BRO30_BUP_DCU_LRD;
node->lch()->lch()->add("command",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.cmd_ans.msg->command));},[](){return (command_type_str(mj->in.bup_dcu_lrd.cmd_ans.msg->command));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.cmd_ans.msg->state));},[](){return (command_state_str(mj->in.bup_dcu_lrd.cmd_ans.msg->state));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_lrd.cmd_ans.msg->cnt);});
node->lch()->lch()->add("info",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lrd.cmd_ans.msg->info,sizeof(mj->in.bup_dcu_lrd.cmd_ans.msg->info)));});
mj->in.bup_dcu_lrd.cmd_ans.upd_cb = [](){ bup_dcu_lrd_cmd_ans_ptr->upd(mj->in.bup_dcu_lrd.cmd_ans.ts_s, mj->in.bup_dcu_lrd.cmd_ans.ts_ns);};
bup_dcu_lrd_dbg_ptr = node->lch()->add("dbg",[](){return QVariant(mj->in.bup_dcu_lrd.dbg.msg->hdr.cnt);});
bup_dcu_lrd_dbg_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.dbg.state;};
bup_dcu_lrd_dbg_ptr->msgId = ID_DBG;
bup_dcu_lrd_dbg_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.dbg.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.dbg.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("fval",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_lrd.dbg.msg->fval[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_lrd.dbg.msg->fval[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_lrd.dbg.msg->fval[2]);});
node->lch()->lch()->lch()->add("[3]",[](){return QVariant(mj->in.bup_dcu_lrd.dbg.msg->fval[3]);});
node->lch()->lch()->lch()->add("[4]",[](){return QVariant(mj->in.bup_dcu_lrd.dbg.msg->fval[4]);});
mj->in.bup_dcu_lrd.dbg.upd_cb = [](){ bup_dcu_lrd_dbg_ptr->upd(mj->in.bup_dcu_lrd.dbg.ts_s, mj->in.bup_dcu_lrd.dbg.ts_ns);};
bup_dcu_lrd_dcu_tel_ptr = node->lch()->add("dcu_tel",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->hdr.cnt);});
bup_dcu_lrd_dcu_tel_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.dcu_tel.state;};
bup_dcu_lrd_dcu_tel_ptr->msgId = ID_DCU_TEL;
bup_dcu_lrd_dcu_tel_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.dcu_tel.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.dcu_tel.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_lrd.dcu_tel.msg->mode));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_lrd.dcu_tel.msg->status));});
node->lch()->lch()->add("err",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->err));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_lrd.dcu_tel.msg->err));});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_lrd.dcu_tel.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->load_sens_speed);});
node->lch()->lch()->add("power_vdc",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->power_vdc);});
node->lch()->lch()->add("current",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->current.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->current.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->current.c);});
node->lch()->lch()->add("pwm",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->pwm.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->pwm.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->pwm.c);});
node->lch()->lch()->add("park_current",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->park_current.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->park_current.q);});
node->lch()->lch()->add("park_voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->park_voltage.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->park_voltage.q);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_lrd.dcu_tel.msg->brake_state));});
node->lch()->lch()->add("ibrk",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->ibrk);});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->electrical_power);});
node->lch()->lch()->add("ang_pid_err",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->ang_pid_err);});
node->lch()->lch()->add("ang_pid_in",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->ang_pid_in);});
node->lch()->lch()->add("ang_pid_out",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->ang_pid_out);});
node->lch()->lch()->add("ang_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->ang_pid_intgr);});
node->lch()->lch()->add("rotor_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->rotor_spd_pid_err);});
node->lch()->lch()->add("rotor_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->rotor_spd_pid_in);});
node->lch()->lch()->add("rotor_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->rotor_spd_pid_out);});
node->lch()->lch()->add("rotor_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->rotor_spd_pid_intgr);});
node->lch()->lch()->add("load_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->load_spd_pid_err);});
node->lch()->lch()->add("load_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->load_spd_pid_in);});
node->lch()->lch()->add("load_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->load_spd_pid_out);});
node->lch()->lch()->add("load_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->load_spd_pid_intgr);});
node->lch()->lch()->add("curr_pid_err",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->curr_pid_err);});
node->lch()->lch()->add("curr_pid_in",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->curr_pid_in);});
node->lch()->lch()->add("curr_pid_out",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->curr_pid_out);});
node->lch()->lch()->add("curr_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->curr_pid_intgr);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_lrd.dcu_tel.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_lrd.dcu_tel.msg->rotor_sens_speed);});
node->lch()->lch()->add("on",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->on));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lrd.dcu_tel.msg->on));});
node->lch()->lch()->add("manual",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->manual));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lrd.dcu_tel.msg->manual));});
node->lch()->lch()->add("block",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->block));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lrd.dcu_tel.msg->block));});
node->lch()->lch()->add("sync",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->sync));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lrd.dcu_tel.msg->sync));});
node->lch()->lch()->add("inv_octw",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->inv_octw));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lrd.dcu_tel.msg->inv_octw));});
node->lch()->lch()->add("inv_fault",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->inv_fault));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lrd.dcu_tel.msg->inv_fault));});
node->lch()->lch()->add("en_gate",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.dcu_tel.msg->en_gate));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lrd.dcu_tel.msg->en_gate));});
mj->in.bup_dcu_lrd.dcu_tel.upd_cb = [](){ bup_dcu_lrd_dcu_tel_ptr->upd(mj->in.bup_dcu_lrd.dcu_tel.ts_s, mj->in.bup_dcu_lrd.dcu_tel.ts_ns);};
bup_dcu_lrd_formular_ptr = node->lch()->add("formular",[](){return QVariant(mj->in.bup_dcu_lrd.formular.msg->hdr.cnt);});
bup_dcu_lrd_formular_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.formular.state;};
bup_dcu_lrd_formular_ptr->msgId = ID_FORMULAR;
bup_dcu_lrd_formular_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.formular.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.formular.msg->hdr.ts_ns)/1e9);});

bup_dcu_lrd_formular_ptr->isReq = true;
bup_dcu_lrd_formular_ptr->srcId = BRO30_BUP_DCU_LRD;
node->lch()->lch()->add("description",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lrd.formular.msg->description,sizeof(mj->in.bup_dcu_lrd.formular.msg->description)));});
node->lch()->lch()->add("factory_number",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lrd.formular.msg->factory_number,sizeof(mj->in.bup_dcu_lrd.formular.msg->factory_number)));});
node->lch()->lch()->add("factory_date",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lrd.formular.msg->factory_date,sizeof(mj->in.bup_dcu_lrd.formular.msg->factory_date)));});
node->lch()->lch()->add("software_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lrd.formular.msg->software_version,sizeof(mj->in.bup_dcu_lrd.formular.msg->software_version)));});
node->lch()->lch()->add("protocol_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lrd.formular.msg->protocol_version,sizeof(mj->in.bup_dcu_lrd.formular.msg->protocol_version)));});
node->lch()->lch()->add("GUID",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lrd.formular.msg->GUID,sizeof(mj->in.bup_dcu_lrd.formular.msg->GUID)));});
node->lch()->lch()->add("operation_time",[](){return QVariant(mj->in.bup_dcu_lrd.formular.msg->operation_time);});
node->lch()->lch()->add("software_checksum",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lrd.formular.msg->software_checksum,sizeof(mj->in.bup_dcu_lrd.formular.msg->software_checksum)));});
node->lch()->lch()->add("code",[](){return QVariant(mj->in.bup_dcu_lrd.formular.msg->code);});
mj->in.bup_dcu_lrd.formular.upd_cb = [](){ bup_dcu_lrd_formular_ptr->upd(mj->in.bup_dcu_lrd.formular.ts_s, mj->in.bup_dcu_lrd.formular.ts_ns);};
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
bup_dcu_lrd_msg_ans_ptr = node->lch()->add("msg_ans",[](){return QVariant(mj->in.bup_dcu_lrd.msg_ans.msg->hdr.cnt);});
bup_dcu_lrd_msg_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.msg_ans.state;};
bup_dcu_lrd_msg_ans_ptr->msgId = ID_MSG_ANS;
bup_dcu_lrd_msg_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.msg_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.msg_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_lrd_msg_ans_ptr->isReq = true;
bup_dcu_lrd_msg_ans_ptr->srcId = BRO30_BUP_DCU_LRD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.msg_ans.msg->id));},[](){return (mj_get_msg_name(mj->in.bup_dcu_lrd.msg_ans.msg->id));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_lrd.msg_ans.msg->cnt);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.msg_ans.msg->state));},[](){return (msg_state_str(mj->in.bup_dcu_lrd.msg_ans.msg->state));});
mj->in.bup_dcu_lrd.msg_ans.upd_cb = [](){ bup_dcu_lrd_msg_ans_ptr->upd(mj->in.bup_dcu_lrd.msg_ans.ts_s, mj->in.bup_dcu_lrd.msg_ans.ts_ns);};
bup_dcu_lrd_prm_ans_ptr = node->lch()->add("prm_ans",[](){return QVariant(mj->in.bup_dcu_lrd.prm_ans.msg->hdr.cnt);});
bup_dcu_lrd_prm_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.prm_ans.state;};
bup_dcu_lrd_prm_ans_ptr->msgId = ID_PRM_ANS;
bup_dcu_lrd_prm_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.prm_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.prm_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_lrd_prm_ans_ptr->isReq = true;
bup_dcu_lrd_prm_ans_ptr->srcId = BRO30_BUP_DCU_LRD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->in.bup_dcu_lrd.prm_ans.msg->id));});
node->lch()->lch()->add("ans",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->in.bup_dcu_lrd.prm_ans.msg->ans));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.bup_dcu_lrd.prm_ans.msg->id,(uint8_t*)mj->in.bup_dcu_lrd.prm_ans.msg->val,sizeof(mj->in.bup_dcu_lrd.prm_ans.msg->val)));});
mj->in.bup_dcu_lrd.prm_ans.upd_cb = [](){ bup_dcu_lrd_prm_ans_ptr->upd(mj->in.bup_dcu_lrd.prm_ans.ts_s, mj->in.bup_dcu_lrd.prm_ans.ts_ns);};
bup_dcu_lrd_ptp_state_ptr = node->lch()->add("ptp_state",[](){return QVariant(mj->in.bup_dcu_lrd.ptp_state.msg->hdr.cnt);});
bup_dcu_lrd_ptp_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.ptp_state.state;};
bup_dcu_lrd_ptp_state_ptr->msgId = ID_PTP_STATE;
bup_dcu_lrd_ptp_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.ptp_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.ptp_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("is_master",[](){return QVariant(mj->in.bup_dcu_lrd.ptp_state.msg->is_master);});
node->lch()->lch()->add("path_delay",[](){return QVariant(mj->in.bup_dcu_lrd.ptp_state.msg->path_delay);});
node->lch()->lch()->add("offset_ns",[](){return QVariant(mj->in.bup_dcu_lrd.ptp_state.msg->offset_ns);});
node->lch()->lch()->add("mean_offset_ns",[](){return QVariant(mj->in.bup_dcu_lrd.ptp_state.msg->mean_offset_ns);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lrd.ptp_state.msg->state));},[](){return (sync_state_str(mj->in.bup_dcu_lrd.ptp_state.msg->state));});
mj->in.bup_dcu_lrd.ptp_state.upd_cb = [](){ bup_dcu_lrd_ptp_state_ptr->upd(mj->in.bup_dcu_lrd.ptp_state.ts_s, mj->in.bup_dcu_lrd.ptp_state.ts_ns);};
TreeNode * bup_dcu_lst_node = node->add("bup_dcu_lst",[](){return QVariant();});
bup_dcu_lst_node->isDev = true;
bup_dcu_lst_bup_state_ptr = node->lch()->add("bup_state",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->hdr.cnt);});
bup_dcu_lst_bup_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_lst.bup_state.state;};
bup_dcu_lst_bup_state_ptr->msgId = ID_BUP_STATE;
bup_dcu_lst_bup_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lst.bup_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lst.bup_state.msg->hdr.ts_ns)/1e9);});

bup_dcu_lst_bup_state_ptr->isReq = true;
bup_dcu_lst_bup_state_ptr->srcId = BRO30_BUP_DCU_LST;
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.bup_state.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_lst.bup_state.msg->mode));});
node->lch()->lch()->add("error",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.bup_state.msg->error));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_lst.bup_state.msg->error));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.bup_state.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_lst.bup_state.msg->status));});
node->lch()->lch()->add("limit",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.bup_state.msg->limit));},[](){return (move_limit_state_str(mj->in.bup_dcu_lst.bup_state.msg->limit));});
node->lch()->lch()->add("angle",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->angle);});
node->lch()->lch()->add("speed",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->speed);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.bup_state.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_lst.bup_state.msg->brake_state));});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->electrical_power);});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.bup_state.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_lst.bup_state.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->load_sens_speed);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.bup_state.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_lst.bup_state.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_lst.bup_state.msg->rotor_sens_speed);});
mj->in.bup_dcu_lst.bup_state.upd_cb = [](){ bup_dcu_lst_bup_state_ptr->upd(mj->in.bup_dcu_lst.bup_state.ts_s, mj->in.bup_dcu_lst.bup_state.ts_ns);};
bup_dcu_lst_cmd_ans_ptr = node->lch()->add("cmd_ans",[](){return QVariant(mj->in.bup_dcu_lst.cmd_ans.msg->hdr.cnt);});
bup_dcu_lst_cmd_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_lst.cmd_ans.state;};
bup_dcu_lst_cmd_ans_ptr->msgId = ID_CMD_ANS;
bup_dcu_lst_cmd_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lst.cmd_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lst.cmd_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_lst_cmd_ans_ptr->isReq = true;
bup_dcu_lst_cmd_ans_ptr->srcId = BRO30_BUP_DCU_LST;
node->lch()->lch()->add("command",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.cmd_ans.msg->command));},[](){return (command_type_str(mj->in.bup_dcu_lst.cmd_ans.msg->command));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.cmd_ans.msg->state));},[](){return (command_state_str(mj->in.bup_dcu_lst.cmd_ans.msg->state));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_lst.cmd_ans.msg->cnt);});
node->lch()->lch()->add("info",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lst.cmd_ans.msg->info,sizeof(mj->in.bup_dcu_lst.cmd_ans.msg->info)));});
mj->in.bup_dcu_lst.cmd_ans.upd_cb = [](){ bup_dcu_lst_cmd_ans_ptr->upd(mj->in.bup_dcu_lst.cmd_ans.ts_s, mj->in.bup_dcu_lst.cmd_ans.ts_ns);};
bup_dcu_lst_dbg_ptr = node->lch()->add("dbg",[](){return QVariant(mj->in.bup_dcu_lst.dbg.msg->hdr.cnt);});
bup_dcu_lst_dbg_ptr->state = []()->int32_t{return mj->in.bup_dcu_lst.dbg.state;};
bup_dcu_lst_dbg_ptr->msgId = ID_DBG;
bup_dcu_lst_dbg_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lst.dbg.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lst.dbg.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("fval",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_lst.dbg.msg->fval[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_lst.dbg.msg->fval[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_lst.dbg.msg->fval[2]);});
node->lch()->lch()->lch()->add("[3]",[](){return QVariant(mj->in.bup_dcu_lst.dbg.msg->fval[3]);});
node->lch()->lch()->lch()->add("[4]",[](){return QVariant(mj->in.bup_dcu_lst.dbg.msg->fval[4]);});
mj->in.bup_dcu_lst.dbg.upd_cb = [](){ bup_dcu_lst_dbg_ptr->upd(mj->in.bup_dcu_lst.dbg.ts_s, mj->in.bup_dcu_lst.dbg.ts_ns);};
bup_dcu_lst_dcu_tel_ptr = node->lch()->add("dcu_tel",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->hdr.cnt);});
bup_dcu_lst_dcu_tel_ptr->state = []()->int32_t{return mj->in.bup_dcu_lst.dcu_tel.state;};
bup_dcu_lst_dcu_tel_ptr->msgId = ID_DCU_TEL;
bup_dcu_lst_dcu_tel_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lst.dcu_tel.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lst.dcu_tel.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_lst.dcu_tel.msg->mode));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_lst.dcu_tel.msg->status));});
node->lch()->lch()->add("err",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->err));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_lst.dcu_tel.msg->err));});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_lst.dcu_tel.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->load_sens_speed);});
node->lch()->lch()->add("power_vdc",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->power_vdc);});
node->lch()->lch()->add("current",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->current.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->current.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->current.c);});
node->lch()->lch()->add("pwm",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->pwm.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->pwm.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->pwm.c);});
node->lch()->lch()->add("park_current",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->park_current.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->park_current.q);});
node->lch()->lch()->add("park_voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->park_voltage.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->park_voltage.q);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_lst.dcu_tel.msg->brake_state));});
node->lch()->lch()->add("ibrk",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->ibrk);});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->electrical_power);});
node->lch()->lch()->add("ang_pid_err",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->ang_pid_err);});
node->lch()->lch()->add("ang_pid_in",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->ang_pid_in);});
node->lch()->lch()->add("ang_pid_out",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->ang_pid_out);});
node->lch()->lch()->add("ang_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->ang_pid_intgr);});
node->lch()->lch()->add("rotor_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->rotor_spd_pid_err);});
node->lch()->lch()->add("rotor_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->rotor_spd_pid_in);});
node->lch()->lch()->add("rotor_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->rotor_spd_pid_out);});
node->lch()->lch()->add("rotor_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->rotor_spd_pid_intgr);});
node->lch()->lch()->add("load_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->load_spd_pid_err);});
node->lch()->lch()->add("load_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->load_spd_pid_in);});
node->lch()->lch()->add("load_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->load_spd_pid_out);});
node->lch()->lch()->add("load_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->load_spd_pid_intgr);});
node->lch()->lch()->add("curr_pid_err",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->curr_pid_err);});
node->lch()->lch()->add("curr_pid_in",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->curr_pid_in);});
node->lch()->lch()->add("curr_pid_out",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->curr_pid_out);});
node->lch()->lch()->add("curr_pid_intgr",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->curr_pid_intgr);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_lst.dcu_tel.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_lst.dcu_tel.msg->rotor_sens_speed);});
node->lch()->lch()->add("on",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->on));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lst.dcu_tel.msg->on));});
node->lch()->lch()->add("manual",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->manual));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lst.dcu_tel.msg->manual));});
node->lch()->lch()->add("block",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->block));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lst.dcu_tel.msg->block));});
node->lch()->lch()->add("sync",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->sync));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lst.dcu_tel.msg->sync));});
node->lch()->lch()->add("inv_octw",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->inv_octw));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lst.dcu_tel.msg->inv_octw));});
node->lch()->lch()->add("inv_fault",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->inv_fault));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lst.dcu_tel.msg->inv_fault));});
node->lch()->lch()->add("en_gate",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.dcu_tel.msg->en_gate));},[](){return (relay_signal_state_str(mj->in.bup_dcu_lst.dcu_tel.msg->en_gate));});
mj->in.bup_dcu_lst.dcu_tel.upd_cb = [](){ bup_dcu_lst_dcu_tel_ptr->upd(mj->in.bup_dcu_lst.dcu_tel.ts_s, mj->in.bup_dcu_lst.dcu_tel.ts_ns);};
bup_dcu_lst_formular_ptr = node->lch()->add("formular",[](){return QVariant(mj->in.bup_dcu_lst.formular.msg->hdr.cnt);});
bup_dcu_lst_formular_ptr->state = []()->int32_t{return mj->in.bup_dcu_lst.formular.state;};
bup_dcu_lst_formular_ptr->msgId = ID_FORMULAR;
bup_dcu_lst_formular_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lst.formular.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lst.formular.msg->hdr.ts_ns)/1e9);});

bup_dcu_lst_formular_ptr->isReq = true;
bup_dcu_lst_formular_ptr->srcId = BRO30_BUP_DCU_LST;
node->lch()->lch()->add("description",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lst.formular.msg->description,sizeof(mj->in.bup_dcu_lst.formular.msg->description)));});
node->lch()->lch()->add("factory_number",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lst.formular.msg->factory_number,sizeof(mj->in.bup_dcu_lst.formular.msg->factory_number)));});
node->lch()->lch()->add("factory_date",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lst.formular.msg->factory_date,sizeof(mj->in.bup_dcu_lst.formular.msg->factory_date)));});
node->lch()->lch()->add("software_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lst.formular.msg->software_version,sizeof(mj->in.bup_dcu_lst.formular.msg->software_version)));});
node->lch()->lch()->add("protocol_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lst.formular.msg->protocol_version,sizeof(mj->in.bup_dcu_lst.formular.msg->protocol_version)));});
node->lch()->lch()->add("GUID",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lst.formular.msg->GUID,sizeof(mj->in.bup_dcu_lst.formular.msg->GUID)));});
node->lch()->lch()->add("operation_time",[](){return QVariant(mj->in.bup_dcu_lst.formular.msg->operation_time);});
node->lch()->lch()->add("software_checksum",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_lst.formular.msg->software_checksum,sizeof(mj->in.bup_dcu_lst.formular.msg->software_checksum)));});
node->lch()->lch()->add("code",[](){return QVariant(mj->in.bup_dcu_lst.formular.msg->code);});
mj->in.bup_dcu_lst.formular.upd_cb = [](){ bup_dcu_lst_formular_ptr->upd(mj->in.bup_dcu_lst.formular.ts_s, mj->in.bup_dcu_lst.formular.ts_ns);};
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
bup_dcu_lst_msg_ans_ptr = node->lch()->add("msg_ans",[](){return QVariant(mj->in.bup_dcu_lst.msg_ans.msg->hdr.cnt);});
bup_dcu_lst_msg_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_lst.msg_ans.state;};
bup_dcu_lst_msg_ans_ptr->msgId = ID_MSG_ANS;
bup_dcu_lst_msg_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lst.msg_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lst.msg_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_lst_msg_ans_ptr->isReq = true;
bup_dcu_lst_msg_ans_ptr->srcId = BRO30_BUP_DCU_LST;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.msg_ans.msg->id));},[](){return (mj_get_msg_name(mj->in.bup_dcu_lst.msg_ans.msg->id));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_lst.msg_ans.msg->cnt);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.msg_ans.msg->state));},[](){return (msg_state_str(mj->in.bup_dcu_lst.msg_ans.msg->state));});
mj->in.bup_dcu_lst.msg_ans.upd_cb = [](){ bup_dcu_lst_msg_ans_ptr->upd(mj->in.bup_dcu_lst.msg_ans.ts_s, mj->in.bup_dcu_lst.msg_ans.ts_ns);};
bup_dcu_lst_prm_ans_ptr = node->lch()->add("prm_ans",[](){return QVariant(mj->in.bup_dcu_lst.prm_ans.msg->hdr.cnt);});
bup_dcu_lst_prm_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_lst.prm_ans.state;};
bup_dcu_lst_prm_ans_ptr->msgId = ID_PRM_ANS;
bup_dcu_lst_prm_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lst.prm_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lst.prm_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_lst_prm_ans_ptr->isReq = true;
bup_dcu_lst_prm_ans_ptr->srcId = BRO30_BUP_DCU_LST;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->in.bup_dcu_lst.prm_ans.msg->id));});
node->lch()->lch()->add("ans",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->in.bup_dcu_lst.prm_ans.msg->ans));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.bup_dcu_lst.prm_ans.msg->id,(uint8_t*)mj->in.bup_dcu_lst.prm_ans.msg->val,sizeof(mj->in.bup_dcu_lst.prm_ans.msg->val)));});
mj->in.bup_dcu_lst.prm_ans.upd_cb = [](){ bup_dcu_lst_prm_ans_ptr->upd(mj->in.bup_dcu_lst.prm_ans.ts_s, mj->in.bup_dcu_lst.prm_ans.ts_ns);};
bup_dcu_lst_ptp_state_ptr = node->lch()->add("ptp_state",[](){return QVariant(mj->in.bup_dcu_lst.ptp_state.msg->hdr.cnt);});
bup_dcu_lst_ptp_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_lst.ptp_state.state;};
bup_dcu_lst_ptp_state_ptr->msgId = ID_PTP_STATE;
bup_dcu_lst_ptp_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lst.ptp_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lst.ptp_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("is_master",[](){return QVariant(mj->in.bup_dcu_lst.ptp_state.msg->is_master);});
node->lch()->lch()->add("path_delay",[](){return QVariant(mj->in.bup_dcu_lst.ptp_state.msg->path_delay);});
node->lch()->lch()->add("offset_ns",[](){return QVariant(mj->in.bup_dcu_lst.ptp_state.msg->offset_ns);});
node->lch()->lch()->add("mean_offset_ns",[](){return QVariant(mj->in.bup_dcu_lst.ptp_state.msg->mean_offset_ns);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_lst.ptp_state.msg->state));},[](){return (sync_state_str(mj->in.bup_dcu_lst.ptp_state.msg->state));});
mj->in.bup_dcu_lst.ptp_state.upd_cb = [](){ bup_dcu_lst_ptp_state_ptr->upd(mj->in.bup_dcu_lst.ptp_state.ts_s, mj->in.bup_dcu_lst.ptp_state.ts_ns);};
TreeNode * bup_dcu_rfd_node = node->add("bup_dcu_rfd",[](){return QVariant();});
bup_dcu_rfd_node->isDev = true;
bup_dcu_rfd_bup_state_ptr = node->lch()->add("bup_state",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->hdr.cnt);});
bup_dcu_rfd_bup_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.bup_state.state;};
bup_dcu_rfd_bup_state_ptr->msgId = ID_BUP_STATE;
bup_dcu_rfd_bup_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.bup_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.bup_state.msg->hdr.ts_ns)/1e9);});

bup_dcu_rfd_bup_state_ptr->isReq = true;
bup_dcu_rfd_bup_state_ptr->srcId = BRO30_BUP_DCU_RFD;
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.bup_state.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_rfd.bup_state.msg->mode));});
node->lch()->lch()->add("error",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.bup_state.msg->error));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_rfd.bup_state.msg->error));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.bup_state.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_rfd.bup_state.msg->status));});
node->lch()->lch()->add("limit",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.bup_state.msg->limit));},[](){return (move_limit_state_str(mj->in.bup_dcu_rfd.bup_state.msg->limit));});
node->lch()->lch()->add("angle",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->angle);});
node->lch()->lch()->add("speed",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->speed);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.bup_state.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_rfd.bup_state.msg->brake_state));});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->electrical_power);});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.bup_state.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_rfd.bup_state.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->load_sens_speed);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.bup_state.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_rfd.bup_state.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_rfd.bup_state.msg->rotor_sens_speed);});
mj->in.bup_dcu_rfd.bup_state.upd_cb = [](){ bup_dcu_rfd_bup_state_ptr->upd(mj->in.bup_dcu_rfd.bup_state.ts_s, mj->in.bup_dcu_rfd.bup_state.ts_ns);};
bup_dcu_rfd_cmd_ans_ptr = node->lch()->add("cmd_ans",[](){return QVariant(mj->in.bup_dcu_rfd.cmd_ans.msg->hdr.cnt);});
bup_dcu_rfd_cmd_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.cmd_ans.state;};
bup_dcu_rfd_cmd_ans_ptr->msgId = ID_CMD_ANS;
bup_dcu_rfd_cmd_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.cmd_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.cmd_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_rfd_cmd_ans_ptr->isReq = true;
bup_dcu_rfd_cmd_ans_ptr->srcId = BRO30_BUP_DCU_RFD;
node->lch()->lch()->add("command",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.cmd_ans.msg->command));},[](){return (command_type_str(mj->in.bup_dcu_rfd.cmd_ans.msg->command));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.cmd_ans.msg->state));},[](){return (command_state_str(mj->in.bup_dcu_rfd.cmd_ans.msg->state));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_rfd.cmd_ans.msg->cnt);});
node->lch()->lch()->add("info",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rfd.cmd_ans.msg->info,sizeof(mj->in.bup_dcu_rfd.cmd_ans.msg->info)));});
mj->in.bup_dcu_rfd.cmd_ans.upd_cb = [](){ bup_dcu_rfd_cmd_ans_ptr->upd(mj->in.bup_dcu_rfd.cmd_ans.ts_s, mj->in.bup_dcu_rfd.cmd_ans.ts_ns);};
bup_dcu_rfd_dbg_ptr = node->lch()->add("dbg",[](){return QVariant(mj->in.bup_dcu_rfd.dbg.msg->hdr.cnt);});
bup_dcu_rfd_dbg_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.dbg.state;};
bup_dcu_rfd_dbg_ptr->msgId = ID_DBG;
bup_dcu_rfd_dbg_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.dbg.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.dbg.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("fval",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_rfd.dbg.msg->fval[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_rfd.dbg.msg->fval[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_rfd.dbg.msg->fval[2]);});
node->lch()->lch()->lch()->add("[3]",[](){return QVariant(mj->in.bup_dcu_rfd.dbg.msg->fval[3]);});
node->lch()->lch()->lch()->add("[4]",[](){return QVariant(mj->in.bup_dcu_rfd.dbg.msg->fval[4]);});
mj->in.bup_dcu_rfd.dbg.upd_cb = [](){ bup_dcu_rfd_dbg_ptr->upd(mj->in.bup_dcu_rfd.dbg.ts_s, mj->in.bup_dcu_rfd.dbg.ts_ns);};
bup_dcu_rfd_dcu_tel_ptr = node->lch()->add("dcu_tel",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->hdr.cnt);});
bup_dcu_rfd_dcu_tel_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.dcu_tel.state;};
bup_dcu_rfd_dcu_tel_ptr->msgId = ID_DCU_TEL;
bup_dcu_rfd_dcu_tel_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.dcu_tel.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.dcu_tel.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_rfd.dcu_tel.msg->mode));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_rfd.dcu_tel.msg->status));});
node->lch()->lch()->add("err",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->err));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_rfd.dcu_tel.msg->err));});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_rfd.dcu_tel.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->load_sens_speed);});
node->lch()->lch()->add("power_vdc",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->power_vdc);});
node->lch()->lch()->add("current",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->current.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->current.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->current.c);});
node->lch()->lch()->add("pwm",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->pwm.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->pwm.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->pwm.c);});
node->lch()->lch()->add("park_current",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->park_current.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->park_current.q);});
node->lch()->lch()->add("park_voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->park_voltage.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->park_voltage.q);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_rfd.dcu_tel.msg->brake_state));});
node->lch()->lch()->add("ibrk",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->ibrk);});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->electrical_power);});
node->lch()->lch()->add("ang_pid_err",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->ang_pid_err);});
node->lch()->lch()->add("ang_pid_in",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->ang_pid_in);});
node->lch()->lch()->add("ang_pid_out",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->ang_pid_out);});
node->lch()->lch()->add("ang_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->ang_pid_intgr);});
node->lch()->lch()->add("rotor_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->rotor_spd_pid_err);});
node->lch()->lch()->add("rotor_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->rotor_spd_pid_in);});
node->lch()->lch()->add("rotor_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->rotor_spd_pid_out);});
node->lch()->lch()->add("rotor_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->rotor_spd_pid_intgr);});
node->lch()->lch()->add("load_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->load_spd_pid_err);});
node->lch()->lch()->add("load_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->load_spd_pid_in);});
node->lch()->lch()->add("load_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->load_spd_pid_out);});
node->lch()->lch()->add("load_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->load_spd_pid_intgr);});
node->lch()->lch()->add("curr_pid_err",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->curr_pid_err);});
node->lch()->lch()->add("curr_pid_in",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->curr_pid_in);});
node->lch()->lch()->add("curr_pid_out",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->curr_pid_out);});
node->lch()->lch()->add("curr_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->curr_pid_intgr);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_rfd.dcu_tel.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_rfd.dcu_tel.msg->rotor_sens_speed);});
node->lch()->lch()->add("on",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->on));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rfd.dcu_tel.msg->on));});
node->lch()->lch()->add("manual",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->manual));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rfd.dcu_tel.msg->manual));});
node->lch()->lch()->add("block",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->block));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rfd.dcu_tel.msg->block));});
node->lch()->lch()->add("sync",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->sync));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rfd.dcu_tel.msg->sync));});
node->lch()->lch()->add("inv_octw",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->inv_octw));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rfd.dcu_tel.msg->inv_octw));});
node->lch()->lch()->add("inv_fault",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->inv_fault));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rfd.dcu_tel.msg->inv_fault));});
node->lch()->lch()->add("en_gate",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.dcu_tel.msg->en_gate));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rfd.dcu_tel.msg->en_gate));});
mj->in.bup_dcu_rfd.dcu_tel.upd_cb = [](){ bup_dcu_rfd_dcu_tel_ptr->upd(mj->in.bup_dcu_rfd.dcu_tel.ts_s, mj->in.bup_dcu_rfd.dcu_tel.ts_ns);};
bup_dcu_rfd_formular_ptr = node->lch()->add("formular",[](){return QVariant(mj->in.bup_dcu_rfd.formular.msg->hdr.cnt);});
bup_dcu_rfd_formular_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.formular.state;};
bup_dcu_rfd_formular_ptr->msgId = ID_FORMULAR;
bup_dcu_rfd_formular_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.formular.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.formular.msg->hdr.ts_ns)/1e9);});

bup_dcu_rfd_formular_ptr->isReq = true;
bup_dcu_rfd_formular_ptr->srcId = BRO30_BUP_DCU_RFD;
node->lch()->lch()->add("description",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rfd.formular.msg->description,sizeof(mj->in.bup_dcu_rfd.formular.msg->description)));});
node->lch()->lch()->add("factory_number",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rfd.formular.msg->factory_number,sizeof(mj->in.bup_dcu_rfd.formular.msg->factory_number)));});
node->lch()->lch()->add("factory_date",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rfd.formular.msg->factory_date,sizeof(mj->in.bup_dcu_rfd.formular.msg->factory_date)));});
node->lch()->lch()->add("software_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rfd.formular.msg->software_version,sizeof(mj->in.bup_dcu_rfd.formular.msg->software_version)));});
node->lch()->lch()->add("protocol_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rfd.formular.msg->protocol_version,sizeof(mj->in.bup_dcu_rfd.formular.msg->protocol_version)));});
node->lch()->lch()->add("GUID",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rfd.formular.msg->GUID,sizeof(mj->in.bup_dcu_rfd.formular.msg->GUID)));});
node->lch()->lch()->add("operation_time",[](){return QVariant(mj->in.bup_dcu_rfd.formular.msg->operation_time);});
node->lch()->lch()->add("software_checksum",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rfd.formular.msg->software_checksum,sizeof(mj->in.bup_dcu_rfd.formular.msg->software_checksum)));});
node->lch()->lch()->add("code",[](){return QVariant(mj->in.bup_dcu_rfd.formular.msg->code);});
mj->in.bup_dcu_rfd.formular.upd_cb = [](){ bup_dcu_rfd_formular_ptr->upd(mj->in.bup_dcu_rfd.formular.ts_s, mj->in.bup_dcu_rfd.formular.ts_ns);};
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
bup_dcu_rfd_msg_ans_ptr = node->lch()->add("msg_ans",[](){return QVariant(mj->in.bup_dcu_rfd.msg_ans.msg->hdr.cnt);});
bup_dcu_rfd_msg_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.msg_ans.state;};
bup_dcu_rfd_msg_ans_ptr->msgId = ID_MSG_ANS;
bup_dcu_rfd_msg_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.msg_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.msg_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_rfd_msg_ans_ptr->isReq = true;
bup_dcu_rfd_msg_ans_ptr->srcId = BRO30_BUP_DCU_RFD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.msg_ans.msg->id));},[](){return (mj_get_msg_name(mj->in.bup_dcu_rfd.msg_ans.msg->id));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_rfd.msg_ans.msg->cnt);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.msg_ans.msg->state));},[](){return (msg_state_str(mj->in.bup_dcu_rfd.msg_ans.msg->state));});
mj->in.bup_dcu_rfd.msg_ans.upd_cb = [](){ bup_dcu_rfd_msg_ans_ptr->upd(mj->in.bup_dcu_rfd.msg_ans.ts_s, mj->in.bup_dcu_rfd.msg_ans.ts_ns);};
bup_dcu_rfd_prm_ans_ptr = node->lch()->add("prm_ans",[](){return QVariant(mj->in.bup_dcu_rfd.prm_ans.msg->hdr.cnt);});
bup_dcu_rfd_prm_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.prm_ans.state;};
bup_dcu_rfd_prm_ans_ptr->msgId = ID_PRM_ANS;
bup_dcu_rfd_prm_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.prm_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.prm_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_rfd_prm_ans_ptr->isReq = true;
bup_dcu_rfd_prm_ans_ptr->srcId = BRO30_BUP_DCU_RFD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->in.bup_dcu_rfd.prm_ans.msg->id));});
node->lch()->lch()->add("ans",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->in.bup_dcu_rfd.prm_ans.msg->ans));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.bup_dcu_rfd.prm_ans.msg->id,(uint8_t*)mj->in.bup_dcu_rfd.prm_ans.msg->val,sizeof(mj->in.bup_dcu_rfd.prm_ans.msg->val)));});
mj->in.bup_dcu_rfd.prm_ans.upd_cb = [](){ bup_dcu_rfd_prm_ans_ptr->upd(mj->in.bup_dcu_rfd.prm_ans.ts_s, mj->in.bup_dcu_rfd.prm_ans.ts_ns);};
bup_dcu_rfd_ptp_state_ptr = node->lch()->add("ptp_state",[](){return QVariant(mj->in.bup_dcu_rfd.ptp_state.msg->hdr.cnt);});
bup_dcu_rfd_ptp_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.ptp_state.state;};
bup_dcu_rfd_ptp_state_ptr->msgId = ID_PTP_STATE;
bup_dcu_rfd_ptp_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.ptp_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.ptp_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("is_master",[](){return QVariant(mj->in.bup_dcu_rfd.ptp_state.msg->is_master);});
node->lch()->lch()->add("path_delay",[](){return QVariant(mj->in.bup_dcu_rfd.ptp_state.msg->path_delay);});
node->lch()->lch()->add("offset_ns",[](){return QVariant(mj->in.bup_dcu_rfd.ptp_state.msg->offset_ns);});
node->lch()->lch()->add("mean_offset_ns",[](){return QVariant(mj->in.bup_dcu_rfd.ptp_state.msg->mean_offset_ns);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rfd.ptp_state.msg->state));},[](){return (sync_state_str(mj->in.bup_dcu_rfd.ptp_state.msg->state));});
mj->in.bup_dcu_rfd.ptp_state.upd_cb = [](){ bup_dcu_rfd_ptp_state_ptr->upd(mj->in.bup_dcu_rfd.ptp_state.ts_s, mj->in.bup_dcu_rfd.ptp_state.ts_ns);};
TreeNode * bup_dcu_rrd_node = node->add("bup_dcu_rrd",[](){return QVariant();});
bup_dcu_rrd_node->isDev = true;
bup_dcu_rrd_bup_state_ptr = node->lch()->add("bup_state",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->hdr.cnt);});
bup_dcu_rrd_bup_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.bup_state.state;};
bup_dcu_rrd_bup_state_ptr->msgId = ID_BUP_STATE;
bup_dcu_rrd_bup_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.bup_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.bup_state.msg->hdr.ts_ns)/1e9);});

bup_dcu_rrd_bup_state_ptr->isReq = true;
bup_dcu_rrd_bup_state_ptr->srcId = BRO30_BUP_DCU_RRD;
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.bup_state.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_rrd.bup_state.msg->mode));});
node->lch()->lch()->add("error",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.bup_state.msg->error));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_rrd.bup_state.msg->error));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.bup_state.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_rrd.bup_state.msg->status));});
node->lch()->lch()->add("limit",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.bup_state.msg->limit));},[](){return (move_limit_state_str(mj->in.bup_dcu_rrd.bup_state.msg->limit));});
node->lch()->lch()->add("angle",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->angle);});
node->lch()->lch()->add("speed",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->speed);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.bup_state.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_rrd.bup_state.msg->brake_state));});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->electrical_power);});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.bup_state.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_rrd.bup_state.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->load_sens_speed);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.bup_state.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_rrd.bup_state.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_rrd.bup_state.msg->rotor_sens_speed);});
mj->in.bup_dcu_rrd.bup_state.upd_cb = [](){ bup_dcu_rrd_bup_state_ptr->upd(mj->in.bup_dcu_rrd.bup_state.ts_s, mj->in.bup_dcu_rrd.bup_state.ts_ns);};
bup_dcu_rrd_cmd_ans_ptr = node->lch()->add("cmd_ans",[](){return QVariant(mj->in.bup_dcu_rrd.cmd_ans.msg->hdr.cnt);});
bup_dcu_rrd_cmd_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.cmd_ans.state;};
bup_dcu_rrd_cmd_ans_ptr->msgId = ID_CMD_ANS;
bup_dcu_rrd_cmd_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.cmd_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.cmd_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_rrd_cmd_ans_ptr->isReq = true;
bup_dcu_rrd_cmd_ans_ptr->srcId = BRO30_BUP_DCU_RRD;
node->lch()->lch()->add("command",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.cmd_ans.msg->command));},[](){return (command_type_str(mj->in.bup_dcu_rrd.cmd_ans.msg->command));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.cmd_ans.msg->state));},[](){return (command_state_str(mj->in.bup_dcu_rrd.cmd_ans.msg->state));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_rrd.cmd_ans.msg->cnt);});
node->lch()->lch()->add("info",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rrd.cmd_ans.msg->info,sizeof(mj->in.bup_dcu_rrd.cmd_ans.msg->info)));});
mj->in.bup_dcu_rrd.cmd_ans.upd_cb = [](){ bup_dcu_rrd_cmd_ans_ptr->upd(mj->in.bup_dcu_rrd.cmd_ans.ts_s, mj->in.bup_dcu_rrd.cmd_ans.ts_ns);};
bup_dcu_rrd_dbg_ptr = node->lch()->add("dbg",[](){return QVariant(mj->in.bup_dcu_rrd.dbg.msg->hdr.cnt);});
bup_dcu_rrd_dbg_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.dbg.state;};
bup_dcu_rrd_dbg_ptr->msgId = ID_DBG;
bup_dcu_rrd_dbg_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.dbg.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.dbg.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("fval",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_rrd.dbg.msg->fval[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_rrd.dbg.msg->fval[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_rrd.dbg.msg->fval[2]);});
node->lch()->lch()->lch()->add("[3]",[](){return QVariant(mj->in.bup_dcu_rrd.dbg.msg->fval[3]);});
node->lch()->lch()->lch()->add("[4]",[](){return QVariant(mj->in.bup_dcu_rrd.dbg.msg->fval[4]);});
mj->in.bup_dcu_rrd.dbg.upd_cb = [](){ bup_dcu_rrd_dbg_ptr->upd(mj->in.bup_dcu_rrd.dbg.ts_s, mj->in.bup_dcu_rrd.dbg.ts_ns);};
bup_dcu_rrd_dcu_tel_ptr = node->lch()->add("dcu_tel",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->hdr.cnt);});
bup_dcu_rrd_dcu_tel_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.dcu_tel.state;};
bup_dcu_rrd_dcu_tel_ptr->msgId = ID_DCU_TEL;
bup_dcu_rrd_dcu_tel_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.dcu_tel.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.dcu_tel.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_rrd.dcu_tel.msg->mode));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_rrd.dcu_tel.msg->status));});
node->lch()->lch()->add("err",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->err));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_rrd.dcu_tel.msg->err));});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_rrd.dcu_tel.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->load_sens_speed);});
node->lch()->lch()->add("power_vdc",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->power_vdc);});
node->lch()->lch()->add("current",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->current.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->current.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->current.c);});
node->lch()->lch()->add("pwm",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->pwm.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->pwm.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->pwm.c);});
node->lch()->lch()->add("park_current",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->park_current.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->park_current.q);});
node->lch()->lch()->add("park_voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->park_voltage.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->park_voltage.q);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_rrd.dcu_tel.msg->brake_state));});
node->lch()->lch()->add("ibrk",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->ibrk);});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->electrical_power);});
node->lch()->lch()->add("ang_pid_err",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->ang_pid_err);});
node->lch()->lch()->add("ang_pid_in",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->ang_pid_in);});
node->lch()->lch()->add("ang_pid_out",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->ang_pid_out);});
node->lch()->lch()->add("ang_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->ang_pid_intgr);});
node->lch()->lch()->add("rotor_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->rotor_spd_pid_err);});
node->lch()->lch()->add("rotor_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->rotor_spd_pid_in);});
node->lch()->lch()->add("rotor_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->rotor_spd_pid_out);});
node->lch()->lch()->add("rotor_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->rotor_spd_pid_intgr);});
node->lch()->lch()->add("load_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->load_spd_pid_err);});
node->lch()->lch()->add("load_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->load_spd_pid_in);});
node->lch()->lch()->add("load_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->load_spd_pid_out);});
node->lch()->lch()->add("load_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->load_spd_pid_intgr);});
node->lch()->lch()->add("curr_pid_err",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->curr_pid_err);});
node->lch()->lch()->add("curr_pid_in",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->curr_pid_in);});
node->lch()->lch()->add("curr_pid_out",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->curr_pid_out);});
node->lch()->lch()->add("curr_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->curr_pid_intgr);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_rrd.dcu_tel.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_rrd.dcu_tel.msg->rotor_sens_speed);});
node->lch()->lch()->add("on",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->on));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rrd.dcu_tel.msg->on));});
node->lch()->lch()->add("manual",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->manual));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rrd.dcu_tel.msg->manual));});
node->lch()->lch()->add("block",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->block));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rrd.dcu_tel.msg->block));});
node->lch()->lch()->add("sync",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->sync));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rrd.dcu_tel.msg->sync));});
node->lch()->lch()->add("inv_octw",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->inv_octw));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rrd.dcu_tel.msg->inv_octw));});
node->lch()->lch()->add("inv_fault",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->inv_fault));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rrd.dcu_tel.msg->inv_fault));});
node->lch()->lch()->add("en_gate",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.dcu_tel.msg->en_gate));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rrd.dcu_tel.msg->en_gate));});
mj->in.bup_dcu_rrd.dcu_tel.upd_cb = [](){ bup_dcu_rrd_dcu_tel_ptr->upd(mj->in.bup_dcu_rrd.dcu_tel.ts_s, mj->in.bup_dcu_rrd.dcu_tel.ts_ns);};
bup_dcu_rrd_formular_ptr = node->lch()->add("formular",[](){return QVariant(mj->in.bup_dcu_rrd.formular.msg->hdr.cnt);});
bup_dcu_rrd_formular_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.formular.state;};
bup_dcu_rrd_formular_ptr->msgId = ID_FORMULAR;
bup_dcu_rrd_formular_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.formular.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.formular.msg->hdr.ts_ns)/1e9);});

bup_dcu_rrd_formular_ptr->isReq = true;
bup_dcu_rrd_formular_ptr->srcId = BRO30_BUP_DCU_RRD;
node->lch()->lch()->add("description",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rrd.formular.msg->description,sizeof(mj->in.bup_dcu_rrd.formular.msg->description)));});
node->lch()->lch()->add("factory_number",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rrd.formular.msg->factory_number,sizeof(mj->in.bup_dcu_rrd.formular.msg->factory_number)));});
node->lch()->lch()->add("factory_date",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rrd.formular.msg->factory_date,sizeof(mj->in.bup_dcu_rrd.formular.msg->factory_date)));});
node->lch()->lch()->add("software_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rrd.formular.msg->software_version,sizeof(mj->in.bup_dcu_rrd.formular.msg->software_version)));});
node->lch()->lch()->add("protocol_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rrd.formular.msg->protocol_version,sizeof(mj->in.bup_dcu_rrd.formular.msg->protocol_version)));});
node->lch()->lch()->add("GUID",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rrd.formular.msg->GUID,sizeof(mj->in.bup_dcu_rrd.formular.msg->GUID)));});
node->lch()->lch()->add("operation_time",[](){return QVariant(mj->in.bup_dcu_rrd.formular.msg->operation_time);});
node->lch()->lch()->add("software_checksum",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rrd.formular.msg->software_checksum,sizeof(mj->in.bup_dcu_rrd.formular.msg->software_checksum)));});
node->lch()->lch()->add("code",[](){return QVariant(mj->in.bup_dcu_rrd.formular.msg->code);});
mj->in.bup_dcu_rrd.formular.upd_cb = [](){ bup_dcu_rrd_formular_ptr->upd(mj->in.bup_dcu_rrd.formular.ts_s, mj->in.bup_dcu_rrd.formular.ts_ns);};
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
bup_dcu_rrd_msg_ans_ptr = node->lch()->add("msg_ans",[](){return QVariant(mj->in.bup_dcu_rrd.msg_ans.msg->hdr.cnt);});
bup_dcu_rrd_msg_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.msg_ans.state;};
bup_dcu_rrd_msg_ans_ptr->msgId = ID_MSG_ANS;
bup_dcu_rrd_msg_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.msg_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.msg_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_rrd_msg_ans_ptr->isReq = true;
bup_dcu_rrd_msg_ans_ptr->srcId = BRO30_BUP_DCU_RRD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.msg_ans.msg->id));},[](){return (mj_get_msg_name(mj->in.bup_dcu_rrd.msg_ans.msg->id));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_rrd.msg_ans.msg->cnt);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.msg_ans.msg->state));},[](){return (msg_state_str(mj->in.bup_dcu_rrd.msg_ans.msg->state));});
mj->in.bup_dcu_rrd.msg_ans.upd_cb = [](){ bup_dcu_rrd_msg_ans_ptr->upd(mj->in.bup_dcu_rrd.msg_ans.ts_s, mj->in.bup_dcu_rrd.msg_ans.ts_ns);};
bup_dcu_rrd_prm_ans_ptr = node->lch()->add("prm_ans",[](){return QVariant(mj->in.bup_dcu_rrd.prm_ans.msg->hdr.cnt);});
bup_dcu_rrd_prm_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.prm_ans.state;};
bup_dcu_rrd_prm_ans_ptr->msgId = ID_PRM_ANS;
bup_dcu_rrd_prm_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.prm_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.prm_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_rrd_prm_ans_ptr->isReq = true;
bup_dcu_rrd_prm_ans_ptr->srcId = BRO30_BUP_DCU_RRD;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->in.bup_dcu_rrd.prm_ans.msg->id));});
node->lch()->lch()->add("ans",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->in.bup_dcu_rrd.prm_ans.msg->ans));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.bup_dcu_rrd.prm_ans.msg->id,(uint8_t*)mj->in.bup_dcu_rrd.prm_ans.msg->val,sizeof(mj->in.bup_dcu_rrd.prm_ans.msg->val)));});
mj->in.bup_dcu_rrd.prm_ans.upd_cb = [](){ bup_dcu_rrd_prm_ans_ptr->upd(mj->in.bup_dcu_rrd.prm_ans.ts_s, mj->in.bup_dcu_rrd.prm_ans.ts_ns);};
bup_dcu_rrd_ptp_state_ptr = node->lch()->add("ptp_state",[](){return QVariant(mj->in.bup_dcu_rrd.ptp_state.msg->hdr.cnt);});
bup_dcu_rrd_ptp_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.ptp_state.state;};
bup_dcu_rrd_ptp_state_ptr->msgId = ID_PTP_STATE;
bup_dcu_rrd_ptp_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.ptp_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.ptp_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("is_master",[](){return QVariant(mj->in.bup_dcu_rrd.ptp_state.msg->is_master);});
node->lch()->lch()->add("path_delay",[](){return QVariant(mj->in.bup_dcu_rrd.ptp_state.msg->path_delay);});
node->lch()->lch()->add("offset_ns",[](){return QVariant(mj->in.bup_dcu_rrd.ptp_state.msg->offset_ns);});
node->lch()->lch()->add("mean_offset_ns",[](){return QVariant(mj->in.bup_dcu_rrd.ptp_state.msg->mean_offset_ns);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rrd.ptp_state.msg->state));},[](){return (sync_state_str(mj->in.bup_dcu_rrd.ptp_state.msg->state));});
mj->in.bup_dcu_rrd.ptp_state.upd_cb = [](){ bup_dcu_rrd_ptp_state_ptr->upd(mj->in.bup_dcu_rrd.ptp_state.ts_s, mj->in.bup_dcu_rrd.ptp_state.ts_ns);};
TreeNode * bup_dcu_rst_node = node->add("bup_dcu_rst",[](){return QVariant();});
bup_dcu_rst_node->isDev = true;
bup_dcu_rst_bup_state_ptr = node->lch()->add("bup_state",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->hdr.cnt);});
bup_dcu_rst_bup_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.bup_state.state;};
bup_dcu_rst_bup_state_ptr->msgId = ID_BUP_STATE;
bup_dcu_rst_bup_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.bup_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.bup_state.msg->hdr.ts_ns)/1e9);});

bup_dcu_rst_bup_state_ptr->isReq = true;
bup_dcu_rst_bup_state_ptr->srcId = BRO30_BUP_DCU_RST;
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.bup_state.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_rst.bup_state.msg->mode));});
node->lch()->lch()->add("error",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.bup_state.msg->error));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_rst.bup_state.msg->error));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.bup_state.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_rst.bup_state.msg->status));});
node->lch()->lch()->add("limit",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.bup_state.msg->limit));},[](){return (move_limit_state_str(mj->in.bup_dcu_rst.bup_state.msg->limit));});
node->lch()->lch()->add("angle",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->angle);});
node->lch()->lch()->add("speed",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->speed);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.bup_state.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_rst.bup_state.msg->brake_state));});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->electrical_power);});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.bup_state.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_rst.bup_state.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->load_sens_speed);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.bup_state.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_rst.bup_state.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_rst.bup_state.msg->rotor_sens_speed);});
mj->in.bup_dcu_rst.bup_state.upd_cb = [](){ bup_dcu_rst_bup_state_ptr->upd(mj->in.bup_dcu_rst.bup_state.ts_s, mj->in.bup_dcu_rst.bup_state.ts_ns);};
bup_dcu_rst_cmd_ans_ptr = node->lch()->add("cmd_ans",[](){return QVariant(mj->in.bup_dcu_rst.cmd_ans.msg->hdr.cnt);});
bup_dcu_rst_cmd_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.cmd_ans.state;};
bup_dcu_rst_cmd_ans_ptr->msgId = ID_CMD_ANS;
bup_dcu_rst_cmd_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.cmd_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.cmd_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_rst_cmd_ans_ptr->isReq = true;
bup_dcu_rst_cmd_ans_ptr->srcId = BRO30_BUP_DCU_RST;
node->lch()->lch()->add("command",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.cmd_ans.msg->command));},[](){return (command_type_str(mj->in.bup_dcu_rst.cmd_ans.msg->command));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.cmd_ans.msg->state));},[](){return (command_state_str(mj->in.bup_dcu_rst.cmd_ans.msg->state));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_rst.cmd_ans.msg->cnt);});
node->lch()->lch()->add("info",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rst.cmd_ans.msg->info,sizeof(mj->in.bup_dcu_rst.cmd_ans.msg->info)));});
mj->in.bup_dcu_rst.cmd_ans.upd_cb = [](){ bup_dcu_rst_cmd_ans_ptr->upd(mj->in.bup_dcu_rst.cmd_ans.ts_s, mj->in.bup_dcu_rst.cmd_ans.ts_ns);};
bup_dcu_rst_dbg_ptr = node->lch()->add("dbg",[](){return QVariant(mj->in.bup_dcu_rst.dbg.msg->hdr.cnt);});
bup_dcu_rst_dbg_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.dbg.state;};
bup_dcu_rst_dbg_ptr->msgId = ID_DBG;
bup_dcu_rst_dbg_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.dbg.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.dbg.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("fval",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.bup_dcu_rst.dbg.msg->fval[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.bup_dcu_rst.dbg.msg->fval[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.bup_dcu_rst.dbg.msg->fval[2]);});
node->lch()->lch()->lch()->add("[3]",[](){return QVariant(mj->in.bup_dcu_rst.dbg.msg->fval[3]);});
node->lch()->lch()->lch()->add("[4]",[](){return QVariant(mj->in.bup_dcu_rst.dbg.msg->fval[4]);});
mj->in.bup_dcu_rst.dbg.upd_cb = [](){ bup_dcu_rst_dbg_ptr->upd(mj->in.bup_dcu_rst.dbg.ts_s, mj->in.bup_dcu_rst.dbg.ts_ns);};
bup_dcu_rst_dcu_tel_ptr = node->lch()->add("dcu_tel",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->hdr.cnt);});
bup_dcu_rst_dcu_tel_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.dcu_tel.state;};
bup_dcu_rst_dcu_tel_ptr->msgId = ID_DCU_TEL;
bup_dcu_rst_dcu_tel_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.dcu_tel.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.dcu_tel.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.bup_dcu_rst.dcu_tel.msg->mode));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->status));},[](){return (dcu_status_str(mj->in.bup_dcu_rst.dcu_tel.msg->status));});
node->lch()->lch()->add("err",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->err));},[](){return (drv_ctrl_error_str(mj->in.bup_dcu_rst.dcu_tel.msg->err));});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.bup_dcu_rst.dcu_tel.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->load_sens_speed);});
node->lch()->lch()->add("power_vdc",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->power_vdc);});
node->lch()->lch()->add("current",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->current.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->current.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->current.c);});
node->lch()->lch()->add("pwm",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->pwm.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->pwm.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->pwm.c);});
node->lch()->lch()->add("park_current",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->park_current.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->park_current.q);});
node->lch()->lch()->add("park_voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->park_voltage.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->park_voltage.q);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.bup_dcu_rst.dcu_tel.msg->brake_state));});
node->lch()->lch()->add("ibrk",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->ibrk);});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->electrical_power);});
node->lch()->lch()->add("ang_pid_err",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->ang_pid_err);});
node->lch()->lch()->add("ang_pid_in",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->ang_pid_in);});
node->lch()->lch()->add("ang_pid_out",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->ang_pid_out);});
node->lch()->lch()->add("ang_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->ang_pid_intgr);});
node->lch()->lch()->add("rotor_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->rotor_spd_pid_err);});
node->lch()->lch()->add("rotor_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->rotor_spd_pid_in);});
node->lch()->lch()->add("rotor_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->rotor_spd_pid_out);});
node->lch()->lch()->add("rotor_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->rotor_spd_pid_intgr);});
node->lch()->lch()->add("load_spd_pid_err",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->load_spd_pid_err);});
node->lch()->lch()->add("load_spd_pid_in",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->load_spd_pid_in);});
node->lch()->lch()->add("load_spd_pid_out",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->load_spd_pid_out);});
node->lch()->lch()->add("load_spd_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->load_spd_pid_intgr);});
node->lch()->lch()->add("curr_pid_err",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->curr_pid_err);});
node->lch()->lch()->add("curr_pid_in",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->curr_pid_in);});
node->lch()->lch()->add("curr_pid_out",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->curr_pid_out);});
node->lch()->lch()->add("curr_pid_intgr",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->curr_pid_intgr);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.bup_dcu_rst.dcu_tel.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.bup_dcu_rst.dcu_tel.msg->rotor_sens_speed);});
node->lch()->lch()->add("on",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->on));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rst.dcu_tel.msg->on));});
node->lch()->lch()->add("manual",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->manual));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rst.dcu_tel.msg->manual));});
node->lch()->lch()->add("block",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->block));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rst.dcu_tel.msg->block));});
node->lch()->lch()->add("sync",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->sync));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rst.dcu_tel.msg->sync));});
node->lch()->lch()->add("inv_octw",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->inv_octw));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rst.dcu_tel.msg->inv_octw));});
node->lch()->lch()->add("inv_fault",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->inv_fault));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rst.dcu_tel.msg->inv_fault));});
node->lch()->lch()->add("en_gate",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.dcu_tel.msg->en_gate));},[](){return (relay_signal_state_str(mj->in.bup_dcu_rst.dcu_tel.msg->en_gate));});
mj->in.bup_dcu_rst.dcu_tel.upd_cb = [](){ bup_dcu_rst_dcu_tel_ptr->upd(mj->in.bup_dcu_rst.dcu_tel.ts_s, mj->in.bup_dcu_rst.dcu_tel.ts_ns);};
bup_dcu_rst_formular_ptr = node->lch()->add("formular",[](){return QVariant(mj->in.bup_dcu_rst.formular.msg->hdr.cnt);});
bup_dcu_rst_formular_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.formular.state;};
bup_dcu_rst_formular_ptr->msgId = ID_FORMULAR;
bup_dcu_rst_formular_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.formular.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.formular.msg->hdr.ts_ns)/1e9);});

bup_dcu_rst_formular_ptr->isReq = true;
bup_dcu_rst_formular_ptr->srcId = BRO30_BUP_DCU_RST;
node->lch()->lch()->add("description",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rst.formular.msg->description,sizeof(mj->in.bup_dcu_rst.formular.msg->description)));});
node->lch()->lch()->add("factory_number",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rst.formular.msg->factory_number,sizeof(mj->in.bup_dcu_rst.formular.msg->factory_number)));});
node->lch()->lch()->add("factory_date",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rst.formular.msg->factory_date,sizeof(mj->in.bup_dcu_rst.formular.msg->factory_date)));});
node->lch()->lch()->add("software_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rst.formular.msg->software_version,sizeof(mj->in.bup_dcu_rst.formular.msg->software_version)));});
node->lch()->lch()->add("protocol_version",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rst.formular.msg->protocol_version,sizeof(mj->in.bup_dcu_rst.formular.msg->protocol_version)));});
node->lch()->lch()->add("GUID",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rst.formular.msg->GUID,sizeof(mj->in.bup_dcu_rst.formular.msg->GUID)));});
node->lch()->lch()->add("operation_time",[](){return QVariant(mj->in.bup_dcu_rst.formular.msg->operation_time);});
node->lch()->lch()->add("software_checksum",[](){return QVariant(cp866ToQString(mj->in.bup_dcu_rst.formular.msg->software_checksum,sizeof(mj->in.bup_dcu_rst.formular.msg->software_checksum)));});
node->lch()->lch()->add("code",[](){return QVariant(mj->in.bup_dcu_rst.formular.msg->code);});
mj->in.bup_dcu_rst.formular.upd_cb = [](){ bup_dcu_rst_formular_ptr->upd(mj->in.bup_dcu_rst.formular.ts_s, mj->in.bup_dcu_rst.formular.ts_ns);};
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
bup_dcu_rst_msg_ans_ptr = node->lch()->add("msg_ans",[](){return QVariant(mj->in.bup_dcu_rst.msg_ans.msg->hdr.cnt);});
bup_dcu_rst_msg_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.msg_ans.state;};
bup_dcu_rst_msg_ans_ptr->msgId = ID_MSG_ANS;
bup_dcu_rst_msg_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.msg_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.msg_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_rst_msg_ans_ptr->isReq = true;
bup_dcu_rst_msg_ans_ptr->srcId = BRO30_BUP_DCU_RST;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.msg_ans.msg->id));},[](){return (mj_get_msg_name(mj->in.bup_dcu_rst.msg_ans.msg->id));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.bup_dcu_rst.msg_ans.msg->cnt);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.msg_ans.msg->state));},[](){return (msg_state_str(mj->in.bup_dcu_rst.msg_ans.msg->state));});
mj->in.bup_dcu_rst.msg_ans.upd_cb = [](){ bup_dcu_rst_msg_ans_ptr->upd(mj->in.bup_dcu_rst.msg_ans.ts_s, mj->in.bup_dcu_rst.msg_ans.ts_ns);};
bup_dcu_rst_prm_ans_ptr = node->lch()->add("prm_ans",[](){return QVariant(mj->in.bup_dcu_rst.prm_ans.msg->hdr.cnt);});
bup_dcu_rst_prm_ans_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.prm_ans.state;};
bup_dcu_rst_prm_ans_ptr->msgId = ID_PRM_ANS;
bup_dcu_rst_prm_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.prm_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.prm_ans.msg->hdr.ts_ns)/1e9);});

bup_dcu_rst_prm_ans_ptr->isReq = true;
bup_dcu_rst_prm_ans_ptr->srcId = BRO30_BUP_DCU_RST;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->in.bup_dcu_rst.prm_ans.msg->id));});
node->lch()->lch()->add("ans",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->in.bup_dcu_rst.prm_ans.msg->ans));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.bup_dcu_rst.prm_ans.msg->id,(uint8_t*)mj->in.bup_dcu_rst.prm_ans.msg->val,sizeof(mj->in.bup_dcu_rst.prm_ans.msg->val)));});
mj->in.bup_dcu_rst.prm_ans.upd_cb = [](){ bup_dcu_rst_prm_ans_ptr->upd(mj->in.bup_dcu_rst.prm_ans.ts_s, mj->in.bup_dcu_rst.prm_ans.ts_ns);};
bup_dcu_rst_ptp_state_ptr = node->lch()->add("ptp_state",[](){return QVariant(mj->in.bup_dcu_rst.ptp_state.msg->hdr.cnt);});
bup_dcu_rst_ptp_state_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.ptp_state.state;};
bup_dcu_rst_ptp_state_ptr->msgId = ID_PTP_STATE;
bup_dcu_rst_ptp_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.ptp_state.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.ptp_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("is_master",[](){return QVariant(mj->in.bup_dcu_rst.ptp_state.msg->is_master);});
node->lch()->lch()->add("path_delay",[](){return QVariant(mj->in.bup_dcu_rst.ptp_state.msg->path_delay);});
node->lch()->lch()->add("offset_ns",[](){return QVariant(mj->in.bup_dcu_rst.ptp_state.msg->offset_ns);});
node->lch()->lch()->add("mean_offset_ns",[](){return QVariant(mj->in.bup_dcu_rst.ptp_state.msg->mean_offset_ns);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.bup_dcu_rst.ptp_state.msg->state));},[](){return (sync_state_str(mj->in.bup_dcu_rst.ptp_state.msg->state));});
mj->in.bup_dcu_rst.ptp_state.upd_cb = [](){ bup_dcu_rst_ptp_state_ptr->upd(mj->in.bup_dcu_rst.ptp_state.ts_s, mj->in.bup_dcu_rst.ptp_state.ts_ns);};
TreeNode * dcu_node = node->add("dcu",[](){return QVariant();});
dcu_node->isDev = true;
dcu_bup_state_ptr = node->lch()->add("bup_state",[](){return QVariant(mj->in.dcu.bup_state.msg->hdr.cnt);});
dcu_bup_state_ptr->state = []()->int32_t{return mj->in.dcu.bup_state.state;};
dcu_bup_state_ptr->msgId = ID_BUP_STATE;
dcu_bup_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.bup_state.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.bup_state.msg->hdr.ts_ns)/1e9);});

dcu_bup_state_ptr->isReq = true;
dcu_bup_state_ptr->srcId = BRO30_DCU;
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.dcu.bup_state.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.dcu.bup_state.msg->mode));});
node->lch()->lch()->add("error",[](){return QVariant((int32_t)(mj->in.dcu.bup_state.msg->error));},[](){return (drv_ctrl_error_str(mj->in.dcu.bup_state.msg->error));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.dcu.bup_state.msg->status));},[](){return (dcu_status_str(mj->in.dcu.bup_state.msg->status));});
node->lch()->lch()->add("limit",[](){return QVariant((int32_t)(mj->in.dcu.bup_state.msg->limit));},[](){return (move_limit_state_str(mj->in.dcu.bup_state.msg->limit));});
node->lch()->lch()->add("angle",[](){return QVariant(mj->in.dcu.bup_state.msg->angle);});
node->lch()->lch()->add("speed",[](){return QVariant(mj->in.dcu.bup_state.msg->speed);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.dcu.bup_state.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.dcu.bup_state.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.dcu.bup_state.msg->brake_state));});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.dcu.bup_state.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.dcu.bup_state.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.dcu.bup_state.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.dcu.bup_state.msg->electrical_power);});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.dcu.bup_state.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.dcu.bup_state.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.dcu.bup_state.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.dcu.bup_state.msg->load_sens_speed);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.dcu.bup_state.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.dcu.bup_state.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.dcu.bup_state.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.dcu.bup_state.msg->rotor_sens_speed);});
mj->in.dcu.bup_state.upd_cb = [](){ dcu_bup_state_ptr->upd(mj->in.dcu.bup_state.ts_s, mj->in.dcu.bup_state.ts_ns);};
dcu_cmd_ans_ptr = node->lch()->add("cmd_ans",[](){return QVariant(mj->in.dcu.cmd_ans.msg->hdr.cnt);});
dcu_cmd_ans_ptr->state = []()->int32_t{return mj->in.dcu.cmd_ans.state;};
dcu_cmd_ans_ptr->msgId = ID_CMD_ANS;
dcu_cmd_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.cmd_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.cmd_ans.msg->hdr.ts_ns)/1e9);});

dcu_cmd_ans_ptr->isReq = true;
dcu_cmd_ans_ptr->srcId = BRO30_DCU;
node->lch()->lch()->add("command",[](){return QVariant((int32_t)(mj->in.dcu.cmd_ans.msg->command));},[](){return (command_type_str(mj->in.dcu.cmd_ans.msg->command));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.dcu.cmd_ans.msg->state));},[](){return (command_state_str(mj->in.dcu.cmd_ans.msg->state));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.dcu.cmd_ans.msg->cnt);});
node->lch()->lch()->add("info",[](){return QVariant(cp866ToQString(mj->in.dcu.cmd_ans.msg->info,sizeof(mj->in.dcu.cmd_ans.msg->info)));});
mj->in.dcu.cmd_ans.upd_cb = [](){ dcu_cmd_ans_ptr->upd(mj->in.dcu.cmd_ans.ts_s, mj->in.dcu.cmd_ans.ts_ns);};
dcu_dbg_ptr = node->lch()->add("dbg",[](){return QVariant(mj->in.dcu.dbg.msg->hdr.cnt);});
dcu_dbg_ptr->state = []()->int32_t{return mj->in.dcu.dbg.state;};
dcu_dbg_ptr->msgId = ID_DBG;
dcu_dbg_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.dbg.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.dbg.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("fval",[](){return QVariant();});
node->lch()->lch()->lch()->add("[0]",[](){return QVariant(mj->in.dcu.dbg.msg->fval[0]);});
node->lch()->lch()->lch()->add("[1]",[](){return QVariant(mj->in.dcu.dbg.msg->fval[1]);});
node->lch()->lch()->lch()->add("[2]",[](){return QVariant(mj->in.dcu.dbg.msg->fval[2]);});
node->lch()->lch()->lch()->add("[3]",[](){return QVariant(mj->in.dcu.dbg.msg->fval[3]);});
node->lch()->lch()->lch()->add("[4]",[](){return QVariant(mj->in.dcu.dbg.msg->fval[4]);});
mj->in.dcu.dbg.upd_cb = [](){ dcu_dbg_ptr->upd(mj->in.dcu.dbg.ts_s, mj->in.dcu.dbg.ts_ns);};
dcu_dcu_tel_ptr = node->lch()->add("dcu_tel",[](){return QVariant(mj->in.dcu.dcu_tel.msg->hdr.cnt);});
dcu_dcu_tel_ptr->state = []()->int32_t{return mj->in.dcu.dcu_tel.state;};
dcu_dcu_tel_ptr->msgId = ID_DCU_TEL;
dcu_dcu_tel_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.dcu_tel.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.dcu_tel.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->mode));},[](){return (drv_ctrl_mode_str(mj->in.dcu.dcu_tel.msg->mode));});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->status));},[](){return (dcu_status_str(mj->in.dcu.dcu_tel.msg->status));});
node->lch()->lch()->add("err",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->err));},[](){return (drv_ctrl_error_str(mj->in.dcu.dcu_tel.msg->err));});
node->lch()->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->load_sens_state));},[](){return (load_ang_sens_status_str(mj->in.dcu.dcu_tel.msg->load_sens_state));});
node->lch()->lch()->add("load_sens_angle",[](){return QVariant(mj->in.dcu.dcu_tel.msg->load_sens_angle);});
node->lch()->lch()->add("load_sens_speed",[](){return QVariant(mj->in.dcu.dcu_tel.msg->load_sens_speed);});
node->lch()->lch()->add("power_vdc",[](){return QVariant(mj->in.dcu.dcu_tel.msg->power_vdc);});
node->lch()->lch()->add("current",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.dcu.dcu_tel.msg->current.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.dcu.dcu_tel.msg->current.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.dcu.dcu_tel.msg->current.c);});
node->lch()->lch()->add("pwm",[](){return QVariant();});
node->lch()->lch()->lch()->add("a",[](){return QVariant(mj->in.dcu.dcu_tel.msg->pwm.a);});
node->lch()->lch()->lch()->add("b",[](){return QVariant(mj->in.dcu.dcu_tel.msg->pwm.b);});
node->lch()->lch()->lch()->add("c",[](){return QVariant(mj->in.dcu.dcu_tel.msg->pwm.c);});
node->lch()->lch()->add("park_current",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.dcu.dcu_tel.msg->park_current.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.dcu.dcu_tel.msg->park_current.q);});
node->lch()->lch()->add("park_voltage",[](){return QVariant();});
node->lch()->lch()->lch()->add("d",[](){return QVariant(mj->in.dcu.dcu_tel.msg->park_voltage.d);});
node->lch()->lch()->lch()->add("q",[](){return QVariant(mj->in.dcu.dcu_tel.msg->park_voltage.q);});
node->lch()->lch()->add("stator_temp",[](){return QVariant(mj->in.dcu.dcu_tel.msg->stator_temp);});
node->lch()->lch()->add("brake_state",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->brake_state));},[](){return (rotor_brake_state_str(mj->in.dcu.dcu_tel.msg->brake_state));});
node->lch()->lch()->add("ibrk",[](){return QVariant(mj->in.dcu.dcu_tel.msg->ibrk);});
node->lch()->lch()->add("power_voltage",[](){return QVariant(mj->in.dcu.dcu_tel.msg->power_voltage);});
node->lch()->lch()->add("id",[](){return QVariant(mj->in.dcu.dcu_tel.msg->id);});
node->lch()->lch()->add("iq",[](){return QVariant(mj->in.dcu.dcu_tel.msg->iq);});
node->lch()->lch()->add("electrical_power",[](){return QVariant(mj->in.dcu.dcu_tel.msg->electrical_power);});
node->lch()->lch()->add("ang_pid_err",[](){return QVariant(mj->in.dcu.dcu_tel.msg->ang_pid_err);});
node->lch()->lch()->add("ang_pid_in",[](){return QVariant(mj->in.dcu.dcu_tel.msg->ang_pid_in);});
node->lch()->lch()->add("ang_pid_out",[](){return QVariant(mj->in.dcu.dcu_tel.msg->ang_pid_out);});
node->lch()->lch()->add("ang_pid_intgr",[](){return QVariant(mj->in.dcu.dcu_tel.msg->ang_pid_intgr);});
node->lch()->lch()->add("rotor_spd_pid_err",[](){return QVariant(mj->in.dcu.dcu_tel.msg->rotor_spd_pid_err);});
node->lch()->lch()->add("rotor_spd_pid_in",[](){return QVariant(mj->in.dcu.dcu_tel.msg->rotor_spd_pid_in);});
node->lch()->lch()->add("rotor_spd_pid_out",[](){return QVariant(mj->in.dcu.dcu_tel.msg->rotor_spd_pid_out);});
node->lch()->lch()->add("rotor_spd_pid_intgr",[](){return QVariant(mj->in.dcu.dcu_tel.msg->rotor_spd_pid_intgr);});
node->lch()->lch()->add("load_spd_pid_err",[](){return QVariant(mj->in.dcu.dcu_tel.msg->load_spd_pid_err);});
node->lch()->lch()->add("load_spd_pid_in",[](){return QVariant(mj->in.dcu.dcu_tel.msg->load_spd_pid_in);});
node->lch()->lch()->add("load_spd_pid_out",[](){return QVariant(mj->in.dcu.dcu_tel.msg->load_spd_pid_out);});
node->lch()->lch()->add("load_spd_pid_intgr",[](){return QVariant(mj->in.dcu.dcu_tel.msg->load_spd_pid_intgr);});
node->lch()->lch()->add("curr_pid_err",[](){return QVariant(mj->in.dcu.dcu_tel.msg->curr_pid_err);});
node->lch()->lch()->add("curr_pid_in",[](){return QVariant(mj->in.dcu.dcu_tel.msg->curr_pid_in);});
node->lch()->lch()->add("curr_pid_out",[](){return QVariant(mj->in.dcu.dcu_tel.msg->curr_pid_out);});
node->lch()->lch()->add("curr_pid_intgr",[](){return QVariant(mj->in.dcu.dcu_tel.msg->curr_pid_intgr);});
node->lch()->lch()->add("rotor_sens_state",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->rotor_sens_state));},[](){return (rotor_ang_sens_status_str(mj->in.dcu.dcu_tel.msg->rotor_sens_state));});
node->lch()->lch()->add("rotor_sens_angle",[](){return QVariant(mj->in.dcu.dcu_tel.msg->rotor_sens_angle);});
node->lch()->lch()->add("rotor_sens_speed",[](){return QVariant(mj->in.dcu.dcu_tel.msg->rotor_sens_speed);});
node->lch()->lch()->add("on",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->on));},[](){return (relay_signal_state_str(mj->in.dcu.dcu_tel.msg->on));});
node->lch()->lch()->add("manual",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->manual));},[](){return (relay_signal_state_str(mj->in.dcu.dcu_tel.msg->manual));});
node->lch()->lch()->add("block",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->block));},[](){return (relay_signal_state_str(mj->in.dcu.dcu_tel.msg->block));});
node->lch()->lch()->add("sync",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->sync));},[](){return (relay_signal_state_str(mj->in.dcu.dcu_tel.msg->sync));});
node->lch()->lch()->add("inv_octw",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->inv_octw));},[](){return (relay_signal_state_str(mj->in.dcu.dcu_tel.msg->inv_octw));});
node->lch()->lch()->add("inv_fault",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->inv_fault));},[](){return (relay_signal_state_str(mj->in.dcu.dcu_tel.msg->inv_fault));});
node->lch()->lch()->add("en_gate",[](){return QVariant((int32_t)(mj->in.dcu.dcu_tel.msg->en_gate));},[](){return (relay_signal_state_str(mj->in.dcu.dcu_tel.msg->en_gate));});
mj->in.dcu.dcu_tel.upd_cb = [](){ dcu_dcu_tel_ptr->upd(mj->in.dcu.dcu_tel.ts_s, mj->in.dcu.dcu_tel.ts_ns);};
dcu_formular_ptr = node->lch()->add("formular",[](){return QVariant(mj->in.dcu.formular.msg->hdr.cnt);});
dcu_formular_ptr->state = []()->int32_t{return mj->in.dcu.formular.state;};
dcu_formular_ptr->msgId = ID_FORMULAR;
dcu_formular_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.formular.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.formular.msg->hdr.ts_ns)/1e9);});

dcu_formular_ptr->isReq = true;
dcu_formular_ptr->srcId = BRO30_DCU;
node->lch()->lch()->add("description",[](){return QVariant(cp866ToQString(mj->in.dcu.formular.msg->description,sizeof(mj->in.dcu.formular.msg->description)));});
node->lch()->lch()->add("factory_number",[](){return QVariant(cp866ToQString(mj->in.dcu.formular.msg->factory_number,sizeof(mj->in.dcu.formular.msg->factory_number)));});
node->lch()->lch()->add("factory_date",[](){return QVariant(cp866ToQString(mj->in.dcu.formular.msg->factory_date,sizeof(mj->in.dcu.formular.msg->factory_date)));});
node->lch()->lch()->add("software_version",[](){return QVariant(cp866ToQString(mj->in.dcu.formular.msg->software_version,sizeof(mj->in.dcu.formular.msg->software_version)));});
node->lch()->lch()->add("protocol_version",[](){return QVariant(cp866ToQString(mj->in.dcu.formular.msg->protocol_version,sizeof(mj->in.dcu.formular.msg->protocol_version)));});
node->lch()->lch()->add("GUID",[](){return QVariant(cp866ToQString(mj->in.dcu.formular.msg->GUID,sizeof(mj->in.dcu.formular.msg->GUID)));});
node->lch()->lch()->add("operation_time",[](){return QVariant(mj->in.dcu.formular.msg->operation_time);});
node->lch()->lch()->add("software_checksum",[](){return QVariant(cp866ToQString(mj->in.dcu.formular.msg->software_checksum,sizeof(mj->in.dcu.formular.msg->software_checksum)));});
node->lch()->lch()->add("code",[](){return QVariant(mj->in.dcu.formular.msg->code);});
mj->in.dcu.formular.upd_cb = [](){ dcu_formular_ptr->upd(mj->in.dcu.formular.ts_s, mj->in.dcu.formular.ts_ns);};
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
dcu_msg_ans_ptr = node->lch()->add("msg_ans",[](){return QVariant(mj->in.dcu.msg_ans.msg->hdr.cnt);});
dcu_msg_ans_ptr->state = []()->int32_t{return mj->in.dcu.msg_ans.state;};
dcu_msg_ans_ptr->msgId = ID_MSG_ANS;
dcu_msg_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.msg_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.msg_ans.msg->hdr.ts_ns)/1e9);});

dcu_msg_ans_ptr->isReq = true;
dcu_msg_ans_ptr->srcId = BRO30_DCU;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.dcu.msg_ans.msg->id));},[](){return (mj_get_msg_name(mj->in.dcu.msg_ans.msg->id));});
node->lch()->lch()->add("cnt",[](){return QVariant(mj->in.dcu.msg_ans.msg->cnt);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.dcu.msg_ans.msg->state));},[](){return (msg_state_str(mj->in.dcu.msg_ans.msg->state));});
mj->in.dcu.msg_ans.upd_cb = [](){ dcu_msg_ans_ptr->upd(mj->in.dcu.msg_ans.ts_s, mj->in.dcu.msg_ans.ts_ns);};
dcu_prm_ans_ptr = node->lch()->add("prm_ans",[](){return QVariant(mj->in.dcu.prm_ans.msg->hdr.cnt);});
dcu_prm_ans_ptr->state = []()->int32_t{return mj->in.dcu.prm_ans.state;};
dcu_prm_ans_ptr->msgId = ID_PRM_ANS;
dcu_prm_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.prm_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.prm_ans.msg->hdr.ts_ns)/1e9);});

dcu_prm_ans_ptr->isReq = true;
dcu_prm_ans_ptr->srcId = BRO30_DCU;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.dcu.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->in.dcu.prm_ans.msg->id));});
node->lch()->lch()->add("ans",[](){return QVariant((int32_t)(mj->in.dcu.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->in.dcu.prm_ans.msg->ans));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.dcu.prm_ans.msg->id,(uint8_t*)mj->in.dcu.prm_ans.msg->val,sizeof(mj->in.dcu.prm_ans.msg->val)));});
mj->in.dcu.prm_ans.upd_cb = [](){ dcu_prm_ans_ptr->upd(mj->in.dcu.prm_ans.ts_s, mj->in.dcu.prm_ans.ts_ns);};
dcu_ptp_state_ptr = node->lch()->add("ptp_state",[](){return QVariant(mj->in.dcu.ptp_state.msg->hdr.cnt);});
dcu_ptp_state_ptr->state = []()->int32_t{return mj->in.dcu.ptp_state.state;};
dcu_ptp_state_ptr->msgId = ID_PTP_STATE;
dcu_ptp_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.ptp_state.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.ptp_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("is_master",[](){return QVariant(mj->in.dcu.ptp_state.msg->is_master);});
node->lch()->lch()->add("path_delay",[](){return QVariant(mj->in.dcu.ptp_state.msg->path_delay);});
node->lch()->lch()->add("offset_ns",[](){return QVariant(mj->in.dcu.ptp_state.msg->offset_ns);});
node->lch()->lch()->add("mean_offset_ns",[](){return QVariant(mj->in.dcu.ptp_state.msg->mean_offset_ns);});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.dcu.ptp_state.msg->state));},[](){return (sync_state_str(mj->in.dcu.ptp_state.msg->state));});
mj->in.dcu.ptp_state.upd_cb = [](){ dcu_ptp_state_ptr->upd(mj->in.dcu.ptp_state.ts_s, mj->in.dcu.ptp_state.ts_ns);};
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
im_bro_prm_ans_ptr = node->lch()->add("prm_ans",[](){return QVariant(mj->in.im_bro.prm_ans.msg->hdr.cnt);});
im_bro_prm_ans_ptr->state = []()->int32_t{return mj->in.im_bro.prm_ans.state;};
im_bro_prm_ans_ptr->msgId = ID_PRM_ANS;
im_bro_prm_ans_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.im_bro.prm_ans.msg->hdr.ts_s)+static_cast<double>(mj->in.im_bro.prm_ans.msg->hdr.ts_ns)/1e9);});

im_bro_prm_ans_ptr->isReq = true;
im_bro_prm_ans_ptr->srcId = BRO30_IM_BRO;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.im_bro.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->in.im_bro.prm_ans.msg->id));});
node->lch()->lch()->add("ans",[](){return QVariant((int32_t)(mj->in.im_bro.prm_ans.msg->ans));},[](){return (parameter_status_str(mj->in.im_bro.prm_ans.msg->ans));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.im_bro.prm_ans.msg->id,(uint8_t*)mj->in.im_bro.prm_ans.msg->val,sizeof(mj->in.im_bro.prm_ans.msg->val)));});
mj->in.im_bro.prm_ans.upd_cb = [](){ im_bro_prm_ans_ptr->upd(mj->in.im_bro.prm_ans.ts_s, mj->in.im_bro.prm_ans.ts_ns);};
return node;
};


TreeNode * create_mon_out_tree(mj_mon_t * mj_ptr)
{
static mj_mon_t * mj = mj_ptr;
TreeNode * node = new TreeNode("OUTPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
bup_srv_ctrl_ptr = node->add("bup_srv_ctrl",[](){return QVariant(mj->out.bup_srv_ctrl.msg->hdr.cnt);});
bup_srv_ctrl_ptr->tx_enable = &mj->out.bup_srv_ctrl.tx_enable;

node->lch()->add("dr",[](){return QVariant();});
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.bup_srv_ctrl.msg->dr.mode));},[](){return (drv_ctrl_mode_str(mj->out.bup_srv_ctrl.msg->dr.mode));})->setData =  [](QVariant data){ mj->out.bup_srv_ctrl.msg->dr.mode=(drv_ctrl_mode)(data.value<int32_t>());return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->lch()->values.append("OFF");
node->lch()->lch()->lch()->values.append("FREEMOVE");
node->lch()->lch()->lch()->values.append("HOLD");
node->lch()->lch()->lch()->values.append("ANGLE");
node->lch()->lch()->lch()->values.append("SPEED");
node->lch()->lch()->lch()->values.append("RSPEED");
node->lch()->lch()->lch()->values.append("VOLTAGE");
node->lch()->lch()->lch()->values.append("SYNCHRO");
node->lch()->lch()->lch()->values.append("CURRENT");
node->lch()->lch()->lch()->values.append("VOLTAGE_A");
node->lch()->lch()->lch()->values.append("VOLTAGE_B");
node->lch()->lch()->lch()->values.append("VOLTAGE_C");
node->lch()->lch()->lch()->intval.append(0);
node->lch()->lch()->lch()->intval.append(1);
node->lch()->lch()->lch()->intval.append(2);
node->lch()->lch()->lch()->intval.append(3);
node->lch()->lch()->lch()->intval.append(4);
node->lch()->lch()->lch()->intval.append(5);
node->lch()->lch()->lch()->intval.append(6);
node->lch()->lch()->lch()->intval.append(7);
node->lch()->lch()->lch()->intval.append(8);
node->lch()->lch()->lch()->intval.append(9);
node->lch()->lch()->lch()->intval.append(10);
node->lch()->lch()->lch()->intval.append(11);
node->lch()->lch()->lch()->intval.append(12);
node->lch()->lch()->add("angle",[](){return QVariant(mj->out.bup_srv_ctrl.msg->dr.angle);})->setData =  [](QVariant data){ mj->out.bup_srv_ctrl.msg->dr.angle=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("speed",[](){return QVariant(mj->out.bup_srv_ctrl.msg->dr.speed);})->setData =  [](QVariant data){ mj->out.bup_srv_ctrl.msg->dr.speed=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("voltage",[](){return QVariant(mj->out.bup_srv_ctrl.msg->dr.voltage);})->setData =  [](QVariant data){ mj->out.bup_srv_ctrl.msg->dr.voltage=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("current",[](){return QVariant(mj->out.bup_srv_ctrl.msg->dr.current);})->setData =  [](QVariant data){ mj->out.bup_srv_ctrl.msg->dr.current=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;

cmd_req_ptr = node->add("cmd_req",[](){return QVariant(mj->out.cmd_req.msg->hdr.cnt);});
cmd_req_ptr->tx = [](uint16_t dst){mj->out.cmd_req.tx(dst);};

node->lch()->add("type",[](){return QVariant((int32_t)(mj->out.cmd_req.msg->type));},[](){return (command_type_str(mj->out.cmd_req.msg->type));})->setData =  [](QVariant data){ mj->out.cmd_req.msg->type=(command_type)(data.value<int32_t>());return;};
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

msg_req_ptr = node->add("msg_req",[](){return QVariant(mj->out.msg_req.msg->hdr.cnt);});
msg_req_ptr->tx = [](uint16_t dst){mj->out.msg_req.tx(dst);};

node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.msg_req.msg->id));},[](){return (mj_get_msg_name(mj->out.msg_req.msg->id));})->setData =  [](QVariant data){ ;return;};
node->lch()->lch()->editable = true;

prm_req_ptr = node->add("prm_req",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
prm_req_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};

node->lch()->add("type",[](){return QVariant((int32_t)(mj->out.prm_req.msg->type));},[](){return (parameter_request_type_str(mj->out.prm_req.msg->type));})->setData =  [](QVariant data){ mj->out.prm_req.msg->type=(parameter_request_type)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("READ");
node->lch()->lch()->values.append("WRITE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.prm_req.msg->id));},[](){return (mj_get_prm_name(mj->out.prm_req.msg->id));})->setData =  [](QVariant data){ mj->out.prm_req.msg->id=(uint32_t)(data.value<int32_t>());return;};
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
node->lch()->add("val",[](){return QVariant(prm2QVariant(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val)));})->setData =  [](QVariant data){ QVariant2prm(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val),data);return;};
node->lch()->lch()->editable = true;

return node;
};

TreeNode * create_mon_params_tree(mj_mon_t * mj_ptr){
static mj_mon_t * mj = mj_ptr;
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
return node;
};