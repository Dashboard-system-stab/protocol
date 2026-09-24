
#include "signaltree.h"

static TreeNode *aufd_bup_ctrl_ptr = 0;
static TreeNode *aufd_bup_multi_control_ptr = 0;
static TreeNode *aufd_cmd_req_ptr = 0;
static TreeNode *aufd_msg_req_ptr = 0;
static TreeNode *aufd_prm_req_ptr = 0;
static TreeNode *bup_dcu_lfd_drive_master_ctrl_ptr = 0;
static TreeNode *bup_dcu_lfd_drive_slave_fb_ptr = 0;
static TreeNode *bup_dcu_lrd_drive_master_ctrl_ptr = 0;
static TreeNode *bup_dcu_lrd_drive_slave_fb_ptr = 0;
static TreeNode *bup_dcu_rfd_drive_master_ctrl_ptr = 0;
static TreeNode *bup_dcu_rfd_drive_slave_fb_ptr = 0;
static TreeNode *bup_dcu_rrd_drive_master_ctrl_ptr = 0;
static TreeNode *bup_dcu_rrd_drive_slave_fb_ptr = 0;
static TreeNode *bup_dcu_rst_drive_master_ctrl_ptr = 0;
static TreeNode *bup_dcu_rst_drive_slave_fb_ptr = 0;
static TreeNode *dcu_drive_master_ctrl_ptr = 0;
static TreeNode *dcu_drive_slave_fb_ptr = 0;
static TreeNode *im_bro_im_bro_drivers_sens_ptr = 0;
static TreeNode *mon_bup_multi_control_ptr = 0;
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
 
        case 0xB67F1E8:
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
 
        case 0x47B4E0EE:
            return QVariant(*(float*)val);
 
        case 0xE4CCE479:
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
 
        case 0xB815CE97:
            return QVariant(*(float*)val);
 
        case 0x4608CFD6:
            return QVariant(*(float*)val);
 
        case 0x697055A4:
            return QVariant(*(float*)val);
 
        case 0x96EC79E6:
            return QVariant(*(bool*)val);
 
        case 0x380A69BE:
            return QVariant(*(float*)val);
 
        case 0x1C9C8B96:
            return QVariant(*(float*)val);
 
        case 0x8A30CBEA:
            return QVariant(*(float*)val);
 
        case 0xA768C0A5:
            return QVariant(*(float*)val);
 
        case 0x155262F1:
            return QVariant(*(float*)val);
 
        case 0xDAE373A7:
            return QVariant(*(float*)val);
 
        case 0x15AB5439:
            return QVariant(*(float*)val);
 
        case 0x5277826D:
            return QVariant(*(float*)val);
 
        case 0xC6B60F77:
            return QVariant(*(float*)val);
 
        case 0xE9CE9505:
            return QVariant(*(float*)val);
 
        case 0x665CAA19:
            return QVariant(*(float*)val);
 
        case 0x69B9B702:
            return QVariant(*(bool*)val);
 
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
 
        case 0xC044682E:
            return QVariant(*(float*)val);
 
        case 0x86EE36E2:
            return QVariant(*(float*)val);
 
        case 0xA996AC90:
            return QVariant(*(float*)val);
 
        case 0xE4BC057D:
            return QVariant(*(float*)val);
 
        case 0xC02AE755:
            return QVariant(*(float*)val);
 
        case 0x5686A729:
            return QVariant(*(float*)val);
 
        case 0x7BDEAC66:
            return QVariant(*(float*)val);
 
        case 0xC9E40E32:
            return QVariant(*(float*)val);
 
        case 0x2073EC66:
            return QVariant(*(float*)val);
 
        case 0x67AF3A32:
            return QVariant(*(float*)val);
 
        case 0x4261C897:
            return QVariant(*(float*)val);
 
        case 0x53169F2D:
            return QVariant(*(float*)val);
 
        case 0x7C6E055F:
            return QVariant(*(float*)val);
 
        case 0x56EE8F6:
            return QVariant(*(float*)val);
 
        case 0x21F80ADE:
            return QVariant(*(float*)val);
 
        case 0xB7544AA2:
            return QVariant(*(float*)val);
 
        case 0x9A0C41ED:
            return QVariant(*(float*)val);
 
        case 0x2836E3B9:
            return QVariant(*(float*)val);
 
        case 0xC995954D:
            return QVariant(*(float*)val);
 
        case 0x8E494319:
            return QVariant(*(float*)val);
 
        case 0xAB87B1BC:
            return QVariant(*(float*)val);
 
        case 0xE37276C4:
            return QVariant(*(float*)val);
 
        case 0xCC0AECB6:
            return QVariant(*(float*)val);
 
        case 0xE8701AA:
            return QVariant(*(int*)val);
 
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
 
        case 0x7121BD4C:
            return QVariant(*(float*)val);
 
        case 0x7EC4A057:
            return QVariant(*(bool*)val);
 
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
 
        case 0x5BF96276:
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
    if (id == 0xB67F1E8)
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
    if (id == 0x47B4E0EE)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE4CCE479)
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
    if (id == 0xB815CE97)
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
    if (id == 0x96EC79E6)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x380A69BE)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x1C9C8B96)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8A30CBEA)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA768C0A5)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x155262F1)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xDAE373A7)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x15AB5439)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5277826D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xC6B60F77)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE9CE9505)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x665CAA19)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x69B9B702)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
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
    if (id == 0xC044682E)
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
    if (id == 0xE4BC057D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xC02AE755)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5686A729)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7BDEAC66)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xC9E40E32)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x2073EC66)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x67AF3A32)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4261C897)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x53169F2D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7C6E055F)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x56EE8F6)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x21F80ADE)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xB7544AA2)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9A0C41ED)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x2836E3B9)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xC995954D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8E494319)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xAB87B1BC)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE37276C4)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xCC0AECB6)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE8701AA)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
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
    if (id == 0x7121BD4C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7EC4A057)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
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
    if (id == 0x5BF96276)
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


TreeNode * create_bup_dcu_lst_in_tree(mj_bup_dcu_lst_t * mj_ptr)
{
static mj_bup_dcu_lst_t *mj = mj_ptr;
TreeNode * node = new TreeNode("INPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
TreeNode * aufd_node = node->add("aufd",[](){return QVariant();});
aufd_node->isDev = true;
aufd_bup_ctrl_ptr = node->lch()->add("bup_ctrl",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->hdr.cnt);});
aufd_bup_ctrl_ptr->state = []()->int32_t{return mj->in.aufd.bup_ctrl.state;};
aufd_bup_ctrl_ptr->msgId = ID_BUP_CTRL;
aufd_bup_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.bup_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.bup_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("dr",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.aufd.bup_ctrl.msg->dr.mode));},[](){return (drv_ctrl_mode_str(mj->in.aufd.bup_ctrl.msg->dr.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->dr.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->dr.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->dr.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.aufd.bup_ctrl.msg->dr.current);});
mj->in.aufd.bup_ctrl.upd_cb = [](){ aufd_bup_ctrl_ptr->upd(mj->in.aufd.bup_ctrl.ts_s, mj->in.aufd.bup_ctrl.ts_ns);};
aufd_bup_multi_control_ptr = node->lch()->add("bup_multi_control",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->hdr.cnt);});
aufd_bup_multi_control_ptr->state = []()->int32_t{return mj->in.aufd.bup_multi_control.state;};
aufd_bup_multi_control_ptr->msgId = ID_BUP_MULTI_CONTROL;
aufd_bup_multi_control_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.aufd.bup_multi_control.msg->hdr.ts_s)+static_cast<double>(mj->in.aufd.bup_multi_control.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("lfd",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.aufd.bup_multi_control.msg->lfd.mode));},[](){return (drv_ctrl_mode_str(mj->in.aufd.bup_multi_control.msg->lfd.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lfd.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lfd.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lfd.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lfd.current);});
node->lch()->lch()->add("lrd",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.aufd.bup_multi_control.msg->lrd.mode));},[](){return (drv_ctrl_mode_str(mj->in.aufd.bup_multi_control.msg->lrd.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lrd.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lrd.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lrd.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lrd.current);});
node->lch()->lch()->add("lst",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.aufd.bup_multi_control.msg->lst.mode));},[](){return (drv_ctrl_mode_str(mj->in.aufd.bup_multi_control.msg->lst.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lst.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lst.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lst.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->lst.current);});
node->lch()->lch()->add("rfd",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.aufd.bup_multi_control.msg->rfd.mode));},[](){return (drv_ctrl_mode_str(mj->in.aufd.bup_multi_control.msg->rfd.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rfd.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rfd.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rfd.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rfd.current);});
node->lch()->lch()->add("rrd",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.aufd.bup_multi_control.msg->rrd.mode));},[](){return (drv_ctrl_mode_str(mj->in.aufd.bup_multi_control.msg->rrd.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rrd.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rrd.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rrd.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rrd.current);});
node->lch()->lch()->add("rst",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.aufd.bup_multi_control.msg->rst.mode));},[](){return (drv_ctrl_mode_str(mj->in.aufd.bup_multi_control.msg->rst.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rst.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rst.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rst.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.aufd.bup_multi_control.msg->rst.current);});
mj->in.aufd.bup_multi_control.upd_cb = [](){ aufd_bup_multi_control_ptr->upd(mj->in.aufd.bup_multi_control.ts_s, mj->in.aufd.bup_multi_control.ts_ns);};
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
TreeNode * bup_dcu_lfd_node = node->add("bup_dcu_lfd",[](){return QVariant();});
bup_dcu_lfd_node->isDev = true;
bup_dcu_lfd_drive_master_ctrl_ptr = node->lch()->add("drive_master_ctrl",[](){return QVariant(mj->in.bup_dcu_lfd.drive_master_ctrl.msg->hdr.cnt);});
bup_dcu_lfd_drive_master_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.drive_master_ctrl.state;};
bup_dcu_lfd_drive_master_ctrl_ptr->msgId = ID_DRIVE_MASTER_CTRL;
bup_dcu_lfd_drive_master_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.drive_master_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.drive_master_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("current",[](){return QVariant(mj->in.bup_dcu_lfd.drive_master_ctrl.msg->current);});
mj->in.bup_dcu_lfd.drive_master_ctrl.upd_cb = [](){ bup_dcu_lfd_drive_master_ctrl_ptr->upd(mj->in.bup_dcu_lfd.drive_master_ctrl.ts_s, mj->in.bup_dcu_lfd.drive_master_ctrl.ts_ns);};
bup_dcu_lfd_drive_slave_fb_ptr = node->lch()->add("drive_slave_fb",[](){return QVariant(mj->in.bup_dcu_lfd.drive_slave_fb.msg->hdr.cnt);});
bup_dcu_lfd_drive_slave_fb_ptr->state = []()->int32_t{return mj->in.bup_dcu_lfd.drive_slave_fb.state;};
bup_dcu_lfd_drive_slave_fb_ptr->msgId = ID_DRIVE_SLAVE_FB;
bup_dcu_lfd_drive_slave_fb_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lfd.drive_slave_fb.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lfd.drive_slave_fb.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("rotor_speed",[](){return QVariant(mj->in.bup_dcu_lfd.drive_slave_fb.msg->rotor_speed);});
mj->in.bup_dcu_lfd.drive_slave_fb.upd_cb = [](){ bup_dcu_lfd_drive_slave_fb_ptr->upd(mj->in.bup_dcu_lfd.drive_slave_fb.ts_s, mj->in.bup_dcu_lfd.drive_slave_fb.ts_ns);};
TreeNode * bup_dcu_lrd_node = node->add("bup_dcu_lrd",[](){return QVariant();});
bup_dcu_lrd_node->isDev = true;
bup_dcu_lrd_drive_master_ctrl_ptr = node->lch()->add("drive_master_ctrl",[](){return QVariant(mj->in.bup_dcu_lrd.drive_master_ctrl.msg->hdr.cnt);});
bup_dcu_lrd_drive_master_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.drive_master_ctrl.state;};
bup_dcu_lrd_drive_master_ctrl_ptr->msgId = ID_DRIVE_MASTER_CTRL;
bup_dcu_lrd_drive_master_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.drive_master_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.drive_master_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("current",[](){return QVariant(mj->in.bup_dcu_lrd.drive_master_ctrl.msg->current);});
mj->in.bup_dcu_lrd.drive_master_ctrl.upd_cb = [](){ bup_dcu_lrd_drive_master_ctrl_ptr->upd(mj->in.bup_dcu_lrd.drive_master_ctrl.ts_s, mj->in.bup_dcu_lrd.drive_master_ctrl.ts_ns);};
bup_dcu_lrd_drive_slave_fb_ptr = node->lch()->add("drive_slave_fb",[](){return QVariant(mj->in.bup_dcu_lrd.drive_slave_fb.msg->hdr.cnt);});
bup_dcu_lrd_drive_slave_fb_ptr->state = []()->int32_t{return mj->in.bup_dcu_lrd.drive_slave_fb.state;};
bup_dcu_lrd_drive_slave_fb_ptr->msgId = ID_DRIVE_SLAVE_FB;
bup_dcu_lrd_drive_slave_fb_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_lrd.drive_slave_fb.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_lrd.drive_slave_fb.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("rotor_speed",[](){return QVariant(mj->in.bup_dcu_lrd.drive_slave_fb.msg->rotor_speed);});
mj->in.bup_dcu_lrd.drive_slave_fb.upd_cb = [](){ bup_dcu_lrd_drive_slave_fb_ptr->upd(mj->in.bup_dcu_lrd.drive_slave_fb.ts_s, mj->in.bup_dcu_lrd.drive_slave_fb.ts_ns);};
TreeNode * bup_dcu_rfd_node = node->add("bup_dcu_rfd",[](){return QVariant();});
bup_dcu_rfd_node->isDev = true;
bup_dcu_rfd_drive_master_ctrl_ptr = node->lch()->add("drive_master_ctrl",[](){return QVariant(mj->in.bup_dcu_rfd.drive_master_ctrl.msg->hdr.cnt);});
bup_dcu_rfd_drive_master_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.drive_master_ctrl.state;};
bup_dcu_rfd_drive_master_ctrl_ptr->msgId = ID_DRIVE_MASTER_CTRL;
bup_dcu_rfd_drive_master_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.drive_master_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.drive_master_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("current",[](){return QVariant(mj->in.bup_dcu_rfd.drive_master_ctrl.msg->current);});
mj->in.bup_dcu_rfd.drive_master_ctrl.upd_cb = [](){ bup_dcu_rfd_drive_master_ctrl_ptr->upd(mj->in.bup_dcu_rfd.drive_master_ctrl.ts_s, mj->in.bup_dcu_rfd.drive_master_ctrl.ts_ns);};
bup_dcu_rfd_drive_slave_fb_ptr = node->lch()->add("drive_slave_fb",[](){return QVariant(mj->in.bup_dcu_rfd.drive_slave_fb.msg->hdr.cnt);});
bup_dcu_rfd_drive_slave_fb_ptr->state = []()->int32_t{return mj->in.bup_dcu_rfd.drive_slave_fb.state;};
bup_dcu_rfd_drive_slave_fb_ptr->msgId = ID_DRIVE_SLAVE_FB;
bup_dcu_rfd_drive_slave_fb_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rfd.drive_slave_fb.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rfd.drive_slave_fb.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("rotor_speed",[](){return QVariant(mj->in.bup_dcu_rfd.drive_slave_fb.msg->rotor_speed);});
mj->in.bup_dcu_rfd.drive_slave_fb.upd_cb = [](){ bup_dcu_rfd_drive_slave_fb_ptr->upd(mj->in.bup_dcu_rfd.drive_slave_fb.ts_s, mj->in.bup_dcu_rfd.drive_slave_fb.ts_ns);};
TreeNode * bup_dcu_rrd_node = node->add("bup_dcu_rrd",[](){return QVariant();});
bup_dcu_rrd_node->isDev = true;
bup_dcu_rrd_drive_master_ctrl_ptr = node->lch()->add("drive_master_ctrl",[](){return QVariant(mj->in.bup_dcu_rrd.drive_master_ctrl.msg->hdr.cnt);});
bup_dcu_rrd_drive_master_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.drive_master_ctrl.state;};
bup_dcu_rrd_drive_master_ctrl_ptr->msgId = ID_DRIVE_MASTER_CTRL;
bup_dcu_rrd_drive_master_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.drive_master_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.drive_master_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("current",[](){return QVariant(mj->in.bup_dcu_rrd.drive_master_ctrl.msg->current);});
mj->in.bup_dcu_rrd.drive_master_ctrl.upd_cb = [](){ bup_dcu_rrd_drive_master_ctrl_ptr->upd(mj->in.bup_dcu_rrd.drive_master_ctrl.ts_s, mj->in.bup_dcu_rrd.drive_master_ctrl.ts_ns);};
bup_dcu_rrd_drive_slave_fb_ptr = node->lch()->add("drive_slave_fb",[](){return QVariant(mj->in.bup_dcu_rrd.drive_slave_fb.msg->hdr.cnt);});
bup_dcu_rrd_drive_slave_fb_ptr->state = []()->int32_t{return mj->in.bup_dcu_rrd.drive_slave_fb.state;};
bup_dcu_rrd_drive_slave_fb_ptr->msgId = ID_DRIVE_SLAVE_FB;
bup_dcu_rrd_drive_slave_fb_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rrd.drive_slave_fb.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rrd.drive_slave_fb.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("rotor_speed",[](){return QVariant(mj->in.bup_dcu_rrd.drive_slave_fb.msg->rotor_speed);});
mj->in.bup_dcu_rrd.drive_slave_fb.upd_cb = [](){ bup_dcu_rrd_drive_slave_fb_ptr->upd(mj->in.bup_dcu_rrd.drive_slave_fb.ts_s, mj->in.bup_dcu_rrd.drive_slave_fb.ts_ns);};
TreeNode * bup_dcu_rst_node = node->add("bup_dcu_rst",[](){return QVariant();});
bup_dcu_rst_node->isDev = true;
bup_dcu_rst_drive_master_ctrl_ptr = node->lch()->add("drive_master_ctrl",[](){return QVariant(mj->in.bup_dcu_rst.drive_master_ctrl.msg->hdr.cnt);});
bup_dcu_rst_drive_master_ctrl_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.drive_master_ctrl.state;};
bup_dcu_rst_drive_master_ctrl_ptr->msgId = ID_DRIVE_MASTER_CTRL;
bup_dcu_rst_drive_master_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.drive_master_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.drive_master_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("current",[](){return QVariant(mj->in.bup_dcu_rst.drive_master_ctrl.msg->current);});
mj->in.bup_dcu_rst.drive_master_ctrl.upd_cb = [](){ bup_dcu_rst_drive_master_ctrl_ptr->upd(mj->in.bup_dcu_rst.drive_master_ctrl.ts_s, mj->in.bup_dcu_rst.drive_master_ctrl.ts_ns);};
bup_dcu_rst_drive_slave_fb_ptr = node->lch()->add("drive_slave_fb",[](){return QVariant(mj->in.bup_dcu_rst.drive_slave_fb.msg->hdr.cnt);});
bup_dcu_rst_drive_slave_fb_ptr->state = []()->int32_t{return mj->in.bup_dcu_rst.drive_slave_fb.state;};
bup_dcu_rst_drive_slave_fb_ptr->msgId = ID_DRIVE_SLAVE_FB;
bup_dcu_rst_drive_slave_fb_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.bup_dcu_rst.drive_slave_fb.msg->hdr.ts_s)+static_cast<double>(mj->in.bup_dcu_rst.drive_slave_fb.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("rotor_speed",[](){return QVariant(mj->in.bup_dcu_rst.drive_slave_fb.msg->rotor_speed);});
mj->in.bup_dcu_rst.drive_slave_fb.upd_cb = [](){ bup_dcu_rst_drive_slave_fb_ptr->upd(mj->in.bup_dcu_rst.drive_slave_fb.ts_s, mj->in.bup_dcu_rst.drive_slave_fb.ts_ns);};
TreeNode * dcu_node = node->add("dcu",[](){return QVariant();});
dcu_node->isDev = true;
dcu_drive_master_ctrl_ptr = node->lch()->add("drive_master_ctrl",[](){return QVariant(mj->in.dcu.drive_master_ctrl.msg->hdr.cnt);});
dcu_drive_master_ctrl_ptr->state = []()->int32_t{return mj->in.dcu.drive_master_ctrl.state;};
dcu_drive_master_ctrl_ptr->msgId = ID_DRIVE_MASTER_CTRL;
dcu_drive_master_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.drive_master_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.drive_master_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("current",[](){return QVariant(mj->in.dcu.drive_master_ctrl.msg->current);});
mj->in.dcu.drive_master_ctrl.upd_cb = [](){ dcu_drive_master_ctrl_ptr->upd(mj->in.dcu.drive_master_ctrl.ts_s, mj->in.dcu.drive_master_ctrl.ts_ns);};
dcu_drive_slave_fb_ptr = node->lch()->add("drive_slave_fb",[](){return QVariant(mj->in.dcu.drive_slave_fb.msg->hdr.cnt);});
dcu_drive_slave_fb_ptr->state = []()->int32_t{return mj->in.dcu.drive_slave_fb.state;};
dcu_drive_slave_fb_ptr->msgId = ID_DRIVE_SLAVE_FB;
dcu_drive_slave_fb_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.dcu.drive_slave_fb.msg->hdr.ts_s)+static_cast<double>(mj->in.dcu.drive_slave_fb.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("rotor_speed",[](){return QVariant(mj->in.dcu.drive_slave_fb.msg->rotor_speed);});
mj->in.dcu.drive_slave_fb.upd_cb = [](){ dcu_drive_slave_fb_ptr->upd(mj->in.dcu.drive_slave_fb.ts_s, mj->in.dcu.drive_slave_fb.ts_ns);};
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
mon_bup_multi_control_ptr = node->lch()->add("bup_multi_control",[](){return QVariant(mj->in.mon.bup_multi_control.msg->hdr.cnt);});
mon_bup_multi_control_ptr->state = []()->int32_t{return mj->in.mon.bup_multi_control.state;};
mon_bup_multi_control_ptr->msgId = ID_BUP_MULTI_CONTROL;
mon_bup_multi_control_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.bup_multi_control.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.bup_multi_control.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("lfd",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.bup_multi_control.msg->lfd.mode));},[](){return (drv_ctrl_mode_str(mj->in.mon.bup_multi_control.msg->lfd.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lfd.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lfd.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lfd.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lfd.current);});
node->lch()->lch()->add("lrd",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.bup_multi_control.msg->lrd.mode));},[](){return (drv_ctrl_mode_str(mj->in.mon.bup_multi_control.msg->lrd.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lrd.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lrd.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lrd.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lrd.current);});
node->lch()->lch()->add("lst",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.bup_multi_control.msg->lst.mode));},[](){return (drv_ctrl_mode_str(mj->in.mon.bup_multi_control.msg->lst.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lst.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lst.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lst.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.mon.bup_multi_control.msg->lst.current);});
node->lch()->lch()->add("rfd",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.bup_multi_control.msg->rfd.mode));},[](){return (drv_ctrl_mode_str(mj->in.mon.bup_multi_control.msg->rfd.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rfd.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rfd.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rfd.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rfd.current);});
node->lch()->lch()->add("rrd",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.bup_multi_control.msg->rrd.mode));},[](){return (drv_ctrl_mode_str(mj->in.mon.bup_multi_control.msg->rrd.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rrd.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rrd.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rrd.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rrd.current);});
node->lch()->lch()->add("rst",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.bup_multi_control.msg->rst.mode));},[](){return (drv_ctrl_mode_str(mj->in.mon.bup_multi_control.msg->rst.mode));});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rst.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rst.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rst.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.mon.bup_multi_control.msg->rst.current);});
mj->in.mon.bup_multi_control.upd_cb = [](){ mon_bup_multi_control_ptr->upd(mj->in.mon.bup_multi_control.ts_s, mj->in.mon.bup_multi_control.ts_ns);};
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


TreeNode * create_bup_dcu_lst_out_tree(mj_bup_dcu_lst_t * mj_ptr)
{
static mj_bup_dcu_lst_t * mj = mj_ptr;
TreeNode * node = new TreeNode("OUTPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
return node;
};

TreeNode * create_bup_dcu_lst_params_tree(mj_bup_dcu_lst_t * mj_ptr){
static mj_bup_dcu_lst_t * mj = mj_ptr;
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
node->lch()->lch()->values.append("ohp_hyst");
node->lch()->lch()->intval.append(0xB67F1E8);
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
node->lch()->lch()->values.append("load_speed_flt_fc");
node->lch()->lch()->intval.append(0x47B4E0EE);
node->lch()->lch()->values.append("rotor_speed_flt_fc");
node->lch()->lch()->intval.append(0xE4CCE479);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kb");
node->lch()->lch()->intval.append(0xF6D4B455);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_int_lim");
node->lch()->lch()->intval.append(0xB815CE97);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("load_ang_rev");
node->lch()->lch()->intval.append(0x96EC79E6);
node->lch()->lch()->values.append("load_ang_kp");
node->lch()->lch()->intval.append(0x380A69BE);
node->lch()->lch()->values.append("load_ang_ki");
node->lch()->lch()->intval.append(0x1C9C8B96);
node->lch()->lch()->values.append("load_ang_kb");
node->lch()->lch()->intval.append(0x8A30CBEA);
node->lch()->lch()->values.append("load_ang_kt");
node->lch()->lch()->intval.append(0xA768C0A5);
node->lch()->lch()->values.append("load_ang_kf");
node->lch()->lch()->intval.append(0x155262F1);
node->lch()->lch()->values.append("load_ang_kd");
node->lch()->lch()->intval.append(0xDAE373A7);
node->lch()->lch()->values.append("load_ang_err_lim");
node->lch()->lch()->intval.append(0x15AB5439);
node->lch()->lch()->values.append("load_ang_out_lim");
node->lch()->lch()->intval.append(0x5277826D);
node->lch()->lch()->values.append("load_ang_out_rate_lim");
node->lch()->lch()->intval.append(0xC6B60F77);
node->lch()->lch()->values.append("load_ang_err_rate_lim");
node->lch()->lch()->intval.append(0xE9CE9505);
node->lch()->lch()->values.append("load_ang_dz");
node->lch()->lch()->intval.append(0x665CAA19);
node->lch()->lch()->values.append("load_ang_dz_en");
node->lch()->lch()->intval.append(0x69B9B702);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kb");
node->lch()->lch()->intval.append(0xE1A9A300);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_int_lim");
node->lch()->lch()->intval.append(0xC044682E);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_speed_master_common_kp");
node->lch()->lch()->intval.append(0xE4BC057D);
node->lch()->lch()->values.append("rotor_speed_master_common_ki");
node->lch()->lch()->intval.append(0xC02AE755);
node->lch()->lch()->values.append("rotor_speed_master_common_kb");
node->lch()->lch()->intval.append(0x5686A729);
node->lch()->lch()->values.append("rotor_speed_master_common_kt");
node->lch()->lch()->intval.append(0x7BDEAC66);
node->lch()->lch()->values.append("rotor_speed_master_common_kf");
node->lch()->lch()->intval.append(0xC9E40E32);
node->lch()->lch()->values.append("rotor_speed_master_common_err_lim");
node->lch()->lch()->intval.append(0x2073EC66);
node->lch()->lch()->values.append("rotor_speed_master_common_out_lim");
node->lch()->lch()->intval.append(0x67AF3A32);
node->lch()->lch()->values.append("rotor_speed_master_common_int_lim");
node->lch()->lch()->intval.append(0x4261C897);
node->lch()->lch()->values.append("rotor_speed_master_common_out_rate_lim");
node->lch()->lch()->intval.append(0x53169F2D);
node->lch()->lch()->values.append("rotor_speed_master_common_err_rate_lim");
node->lch()->lch()->intval.append(0x7C6E055F);
node->lch()->lch()->values.append("rotor_speed_master_diff_kp");
node->lch()->lch()->intval.append(0x56EE8F6);
node->lch()->lch()->values.append("rotor_speed_master_diff_ki");
node->lch()->lch()->intval.append(0x21F80ADE);
node->lch()->lch()->values.append("rotor_speed_master_diff_kb");
node->lch()->lch()->intval.append(0xB7544AA2);
node->lch()->lch()->values.append("rotor_speed_master_diff_kt");
node->lch()->lch()->intval.append(0x9A0C41ED);
node->lch()->lch()->values.append("rotor_speed_master_diff_kf");
node->lch()->lch()->intval.append(0x2836E3B9);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_lim");
node->lch()->lch()->intval.append(0xC995954D);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_lim");
node->lch()->lch()->intval.append(0x8E494319);
node->lch()->lch()->values.append("rotor_speed_master_diff_int_lim");
node->lch()->lch()->intval.append(0xAB87B1BC);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_rate_lim");
node->lch()->lch()->intval.append(0xE37276C4);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_rate_lim");
node->lch()->lch()->intval.append(0xCC0AECB6);
node->lch()->lch()->values.append("rotor_speed_role");
node->lch()->lch()->intval.append(0xE8701AA);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kb");
node->lch()->lch()->intval.append(0xD479AC6);
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
node->lch()->lch()->values.append("rotor_ang_dz");
node->lch()->lch()->intval.append(0x7121BD4C);
node->lch()->lch()->values.append("rotor_ang_dz_en");
node->lch()->lch()->intval.append(0x7EC4A057);
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
node->lch()->lch()->values.append("com_if_bup_internal_mcast");
node->lch()->lch()->intval.append(0x5BF96276);
node->lch()->lch()->values.append("com_if_bro_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6F720C87);
node->lch()->lch()->values.append("com_if_im_bro_drive_mcast");
node->lch()->lch()->intval.append(0x64B26340);
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
node->lch()->lch()->values.append("ohp_hyst");
node->lch()->lch()->intval.append(0xB67F1E8);
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
node->lch()->lch()->values.append("load_speed_flt_fc");
node->lch()->lch()->intval.append(0x47B4E0EE);
node->lch()->lch()->values.append("rotor_speed_flt_fc");
node->lch()->lch()->intval.append(0xE4CCE479);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kb");
node->lch()->lch()->intval.append(0xF6D4B455);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_int_lim");
node->lch()->lch()->intval.append(0xB815CE97);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("load_ang_rev");
node->lch()->lch()->intval.append(0x96EC79E6);
node->lch()->lch()->values.append("load_ang_kp");
node->lch()->lch()->intval.append(0x380A69BE);
node->lch()->lch()->values.append("load_ang_ki");
node->lch()->lch()->intval.append(0x1C9C8B96);
node->lch()->lch()->values.append("load_ang_kb");
node->lch()->lch()->intval.append(0x8A30CBEA);
node->lch()->lch()->values.append("load_ang_kt");
node->lch()->lch()->intval.append(0xA768C0A5);
node->lch()->lch()->values.append("load_ang_kf");
node->lch()->lch()->intval.append(0x155262F1);
node->lch()->lch()->values.append("load_ang_kd");
node->lch()->lch()->intval.append(0xDAE373A7);
node->lch()->lch()->values.append("load_ang_err_lim");
node->lch()->lch()->intval.append(0x15AB5439);
node->lch()->lch()->values.append("load_ang_out_lim");
node->lch()->lch()->intval.append(0x5277826D);
node->lch()->lch()->values.append("load_ang_out_rate_lim");
node->lch()->lch()->intval.append(0xC6B60F77);
node->lch()->lch()->values.append("load_ang_err_rate_lim");
node->lch()->lch()->intval.append(0xE9CE9505);
node->lch()->lch()->values.append("load_ang_dz");
node->lch()->lch()->intval.append(0x665CAA19);
node->lch()->lch()->values.append("load_ang_dz_en");
node->lch()->lch()->intval.append(0x69B9B702);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kb");
node->lch()->lch()->intval.append(0xE1A9A300);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_int_lim");
node->lch()->lch()->intval.append(0xC044682E);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_speed_master_common_kp");
node->lch()->lch()->intval.append(0xE4BC057D);
node->lch()->lch()->values.append("rotor_speed_master_common_ki");
node->lch()->lch()->intval.append(0xC02AE755);
node->lch()->lch()->values.append("rotor_speed_master_common_kb");
node->lch()->lch()->intval.append(0x5686A729);
node->lch()->lch()->values.append("rotor_speed_master_common_kt");
node->lch()->lch()->intval.append(0x7BDEAC66);
node->lch()->lch()->values.append("rotor_speed_master_common_kf");
node->lch()->lch()->intval.append(0xC9E40E32);
node->lch()->lch()->values.append("rotor_speed_master_common_err_lim");
node->lch()->lch()->intval.append(0x2073EC66);
node->lch()->lch()->values.append("rotor_speed_master_common_out_lim");
node->lch()->lch()->intval.append(0x67AF3A32);
node->lch()->lch()->values.append("rotor_speed_master_common_int_lim");
node->lch()->lch()->intval.append(0x4261C897);
node->lch()->lch()->values.append("rotor_speed_master_common_out_rate_lim");
node->lch()->lch()->intval.append(0x53169F2D);
node->lch()->lch()->values.append("rotor_speed_master_common_err_rate_lim");
node->lch()->lch()->intval.append(0x7C6E055F);
node->lch()->lch()->values.append("rotor_speed_master_diff_kp");
node->lch()->lch()->intval.append(0x56EE8F6);
node->lch()->lch()->values.append("rotor_speed_master_diff_ki");
node->lch()->lch()->intval.append(0x21F80ADE);
node->lch()->lch()->values.append("rotor_speed_master_diff_kb");
node->lch()->lch()->intval.append(0xB7544AA2);
node->lch()->lch()->values.append("rotor_speed_master_diff_kt");
node->lch()->lch()->intval.append(0x9A0C41ED);
node->lch()->lch()->values.append("rotor_speed_master_diff_kf");
node->lch()->lch()->intval.append(0x2836E3B9);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_lim");
node->lch()->lch()->intval.append(0xC995954D);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_lim");
node->lch()->lch()->intval.append(0x8E494319);
node->lch()->lch()->values.append("rotor_speed_master_diff_int_lim");
node->lch()->lch()->intval.append(0xAB87B1BC);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_rate_lim");
node->lch()->lch()->intval.append(0xE37276C4);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_rate_lim");
node->lch()->lch()->intval.append(0xCC0AECB6);
node->lch()->lch()->values.append("rotor_speed_role");
node->lch()->lch()->intval.append(0xE8701AA);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kb");
node->lch()->lch()->intval.append(0xD479AC6);
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
node->lch()->lch()->values.append("rotor_ang_dz");
node->lch()->lch()->intval.append(0x7121BD4C);
node->lch()->lch()->values.append("rotor_ang_dz_en");
node->lch()->lch()->intval.append(0x7EC4A057);
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
node->lch()->lch()->values.append("com_if_bup_internal_mcast");
node->lch()->lch()->intval.append(0x5BF96276);
node->lch()->lch()->values.append("com_if_bro_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6F720C87);
node->lch()->lch()->values.append("com_if_im_bro_drive_mcast");
node->lch()->lch()->intval.append(0x64B26340);
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
node->lch()->lch()->values.append("ohp_hyst");
node->lch()->lch()->intval.append(0xB67F1E8);
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
node->lch()->lch()->values.append("load_speed_flt_fc");
node->lch()->lch()->intval.append(0x47B4E0EE);
node->lch()->lch()->values.append("rotor_speed_flt_fc");
node->lch()->lch()->intval.append(0xE4CCE479);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kb");
node->lch()->lch()->intval.append(0xF6D4B455);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_int_lim");
node->lch()->lch()->intval.append(0xB815CE97);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("load_ang_rev");
node->lch()->lch()->intval.append(0x96EC79E6);
node->lch()->lch()->values.append("load_ang_kp");
node->lch()->lch()->intval.append(0x380A69BE);
node->lch()->lch()->values.append("load_ang_ki");
node->lch()->lch()->intval.append(0x1C9C8B96);
node->lch()->lch()->values.append("load_ang_kb");
node->lch()->lch()->intval.append(0x8A30CBEA);
node->lch()->lch()->values.append("load_ang_kt");
node->lch()->lch()->intval.append(0xA768C0A5);
node->lch()->lch()->values.append("load_ang_kf");
node->lch()->lch()->intval.append(0x155262F1);
node->lch()->lch()->values.append("load_ang_kd");
node->lch()->lch()->intval.append(0xDAE373A7);
node->lch()->lch()->values.append("load_ang_err_lim");
node->lch()->lch()->intval.append(0x15AB5439);
node->lch()->lch()->values.append("load_ang_out_lim");
node->lch()->lch()->intval.append(0x5277826D);
node->lch()->lch()->values.append("load_ang_out_rate_lim");
node->lch()->lch()->intval.append(0xC6B60F77);
node->lch()->lch()->values.append("load_ang_err_rate_lim");
node->lch()->lch()->intval.append(0xE9CE9505);
node->lch()->lch()->values.append("load_ang_dz");
node->lch()->lch()->intval.append(0x665CAA19);
node->lch()->lch()->values.append("load_ang_dz_en");
node->lch()->lch()->intval.append(0x69B9B702);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kb");
node->lch()->lch()->intval.append(0xE1A9A300);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_int_lim");
node->lch()->lch()->intval.append(0xC044682E);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_speed_master_common_kp");
node->lch()->lch()->intval.append(0xE4BC057D);
node->lch()->lch()->values.append("rotor_speed_master_common_ki");
node->lch()->lch()->intval.append(0xC02AE755);
node->lch()->lch()->values.append("rotor_speed_master_common_kb");
node->lch()->lch()->intval.append(0x5686A729);
node->lch()->lch()->values.append("rotor_speed_master_common_kt");
node->lch()->lch()->intval.append(0x7BDEAC66);
node->lch()->lch()->values.append("rotor_speed_master_common_kf");
node->lch()->lch()->intval.append(0xC9E40E32);
node->lch()->lch()->values.append("rotor_speed_master_common_err_lim");
node->lch()->lch()->intval.append(0x2073EC66);
node->lch()->lch()->values.append("rotor_speed_master_common_out_lim");
node->lch()->lch()->intval.append(0x67AF3A32);
node->lch()->lch()->values.append("rotor_speed_master_common_int_lim");
node->lch()->lch()->intval.append(0x4261C897);
node->lch()->lch()->values.append("rotor_speed_master_common_out_rate_lim");
node->lch()->lch()->intval.append(0x53169F2D);
node->lch()->lch()->values.append("rotor_speed_master_common_err_rate_lim");
node->lch()->lch()->intval.append(0x7C6E055F);
node->lch()->lch()->values.append("rotor_speed_master_diff_kp");
node->lch()->lch()->intval.append(0x56EE8F6);
node->lch()->lch()->values.append("rotor_speed_master_diff_ki");
node->lch()->lch()->intval.append(0x21F80ADE);
node->lch()->lch()->values.append("rotor_speed_master_diff_kb");
node->lch()->lch()->intval.append(0xB7544AA2);
node->lch()->lch()->values.append("rotor_speed_master_diff_kt");
node->lch()->lch()->intval.append(0x9A0C41ED);
node->lch()->lch()->values.append("rotor_speed_master_diff_kf");
node->lch()->lch()->intval.append(0x2836E3B9);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_lim");
node->lch()->lch()->intval.append(0xC995954D);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_lim");
node->lch()->lch()->intval.append(0x8E494319);
node->lch()->lch()->values.append("rotor_speed_master_diff_int_lim");
node->lch()->lch()->intval.append(0xAB87B1BC);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_rate_lim");
node->lch()->lch()->intval.append(0xE37276C4);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_rate_lim");
node->lch()->lch()->intval.append(0xCC0AECB6);
node->lch()->lch()->values.append("rotor_speed_role");
node->lch()->lch()->intval.append(0xE8701AA);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kb");
node->lch()->lch()->intval.append(0xD479AC6);
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
node->lch()->lch()->values.append("rotor_ang_dz");
node->lch()->lch()->intval.append(0x7121BD4C);
node->lch()->lch()->values.append("rotor_ang_dz_en");
node->lch()->lch()->intval.append(0x7EC4A057);
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
node->lch()->lch()->values.append("com_if_bup_internal_mcast");
node->lch()->lch()->intval.append(0x5BF96276);
node->lch()->lch()->values.append("com_if_bro_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6F720C87);
node->lch()->lch()->values.append("com_if_im_bro_drive_mcast");
node->lch()->lch()->intval.append(0x64B26340);
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
node->lch()->lch()->values.append("ohp_hyst");
node->lch()->lch()->intval.append(0xB67F1E8);
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
node->lch()->lch()->values.append("load_speed_flt_fc");
node->lch()->lch()->intval.append(0x47B4E0EE);
node->lch()->lch()->values.append("rotor_speed_flt_fc");
node->lch()->lch()->intval.append(0xE4CCE479);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kb");
node->lch()->lch()->intval.append(0xF6D4B455);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_int_lim");
node->lch()->lch()->intval.append(0xB815CE97);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("load_ang_rev");
node->lch()->lch()->intval.append(0x96EC79E6);
node->lch()->lch()->values.append("load_ang_kp");
node->lch()->lch()->intval.append(0x380A69BE);
node->lch()->lch()->values.append("load_ang_ki");
node->lch()->lch()->intval.append(0x1C9C8B96);
node->lch()->lch()->values.append("load_ang_kb");
node->lch()->lch()->intval.append(0x8A30CBEA);
node->lch()->lch()->values.append("load_ang_kt");
node->lch()->lch()->intval.append(0xA768C0A5);
node->lch()->lch()->values.append("load_ang_kf");
node->lch()->lch()->intval.append(0x155262F1);
node->lch()->lch()->values.append("load_ang_kd");
node->lch()->lch()->intval.append(0xDAE373A7);
node->lch()->lch()->values.append("load_ang_err_lim");
node->lch()->lch()->intval.append(0x15AB5439);
node->lch()->lch()->values.append("load_ang_out_lim");
node->lch()->lch()->intval.append(0x5277826D);
node->lch()->lch()->values.append("load_ang_out_rate_lim");
node->lch()->lch()->intval.append(0xC6B60F77);
node->lch()->lch()->values.append("load_ang_err_rate_lim");
node->lch()->lch()->intval.append(0xE9CE9505);
node->lch()->lch()->values.append("load_ang_dz");
node->lch()->lch()->intval.append(0x665CAA19);
node->lch()->lch()->values.append("load_ang_dz_en");
node->lch()->lch()->intval.append(0x69B9B702);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kb");
node->lch()->lch()->intval.append(0xE1A9A300);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_int_lim");
node->lch()->lch()->intval.append(0xC044682E);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_speed_master_common_kp");
node->lch()->lch()->intval.append(0xE4BC057D);
node->lch()->lch()->values.append("rotor_speed_master_common_ki");
node->lch()->lch()->intval.append(0xC02AE755);
node->lch()->lch()->values.append("rotor_speed_master_common_kb");
node->lch()->lch()->intval.append(0x5686A729);
node->lch()->lch()->values.append("rotor_speed_master_common_kt");
node->lch()->lch()->intval.append(0x7BDEAC66);
node->lch()->lch()->values.append("rotor_speed_master_common_kf");
node->lch()->lch()->intval.append(0xC9E40E32);
node->lch()->lch()->values.append("rotor_speed_master_common_err_lim");
node->lch()->lch()->intval.append(0x2073EC66);
node->lch()->lch()->values.append("rotor_speed_master_common_out_lim");
node->lch()->lch()->intval.append(0x67AF3A32);
node->lch()->lch()->values.append("rotor_speed_master_common_int_lim");
node->lch()->lch()->intval.append(0x4261C897);
node->lch()->lch()->values.append("rotor_speed_master_common_out_rate_lim");
node->lch()->lch()->intval.append(0x53169F2D);
node->lch()->lch()->values.append("rotor_speed_master_common_err_rate_lim");
node->lch()->lch()->intval.append(0x7C6E055F);
node->lch()->lch()->values.append("rotor_speed_master_diff_kp");
node->lch()->lch()->intval.append(0x56EE8F6);
node->lch()->lch()->values.append("rotor_speed_master_diff_ki");
node->lch()->lch()->intval.append(0x21F80ADE);
node->lch()->lch()->values.append("rotor_speed_master_diff_kb");
node->lch()->lch()->intval.append(0xB7544AA2);
node->lch()->lch()->values.append("rotor_speed_master_diff_kt");
node->lch()->lch()->intval.append(0x9A0C41ED);
node->lch()->lch()->values.append("rotor_speed_master_diff_kf");
node->lch()->lch()->intval.append(0x2836E3B9);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_lim");
node->lch()->lch()->intval.append(0xC995954D);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_lim");
node->lch()->lch()->intval.append(0x8E494319);
node->lch()->lch()->values.append("rotor_speed_master_diff_int_lim");
node->lch()->lch()->intval.append(0xAB87B1BC);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_rate_lim");
node->lch()->lch()->intval.append(0xE37276C4);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_rate_lim");
node->lch()->lch()->intval.append(0xCC0AECB6);
node->lch()->lch()->values.append("rotor_speed_role");
node->lch()->lch()->intval.append(0xE8701AA);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kb");
node->lch()->lch()->intval.append(0xD479AC6);
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
node->lch()->lch()->values.append("rotor_ang_dz");
node->lch()->lch()->intval.append(0x7121BD4C);
node->lch()->lch()->values.append("rotor_ang_dz_en");
node->lch()->lch()->intval.append(0x7EC4A057);
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
node->lch()->lch()->values.append("com_if_bup_internal_mcast");
node->lch()->lch()->intval.append(0x5BF96276);
node->lch()->lch()->values.append("com_if_bro_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6F720C87);
node->lch()->lch()->values.append("com_if_im_bro_drive_mcast");
node->lch()->lch()->intval.append(0x64B26340);
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
node->lch()->lch()->values.append("ohp_hyst");
node->lch()->lch()->intval.append(0xB67F1E8);
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
node->lch()->lch()->values.append("load_speed_flt_fc");
node->lch()->lch()->intval.append(0x47B4E0EE);
node->lch()->lch()->values.append("rotor_speed_flt_fc");
node->lch()->lch()->intval.append(0xE4CCE479);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kb");
node->lch()->lch()->intval.append(0xF6D4B455);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_int_lim");
node->lch()->lch()->intval.append(0xB815CE97);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("load_ang_rev");
node->lch()->lch()->intval.append(0x96EC79E6);
node->lch()->lch()->values.append("load_ang_kp");
node->lch()->lch()->intval.append(0x380A69BE);
node->lch()->lch()->values.append("load_ang_ki");
node->lch()->lch()->intval.append(0x1C9C8B96);
node->lch()->lch()->values.append("load_ang_kb");
node->lch()->lch()->intval.append(0x8A30CBEA);
node->lch()->lch()->values.append("load_ang_kt");
node->lch()->lch()->intval.append(0xA768C0A5);
node->lch()->lch()->values.append("load_ang_kf");
node->lch()->lch()->intval.append(0x155262F1);
node->lch()->lch()->values.append("load_ang_kd");
node->lch()->lch()->intval.append(0xDAE373A7);
node->lch()->lch()->values.append("load_ang_err_lim");
node->lch()->lch()->intval.append(0x15AB5439);
node->lch()->lch()->values.append("load_ang_out_lim");
node->lch()->lch()->intval.append(0x5277826D);
node->lch()->lch()->values.append("load_ang_out_rate_lim");
node->lch()->lch()->intval.append(0xC6B60F77);
node->lch()->lch()->values.append("load_ang_err_rate_lim");
node->lch()->lch()->intval.append(0xE9CE9505);
node->lch()->lch()->values.append("load_ang_dz");
node->lch()->lch()->intval.append(0x665CAA19);
node->lch()->lch()->values.append("load_ang_dz_en");
node->lch()->lch()->intval.append(0x69B9B702);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kb");
node->lch()->lch()->intval.append(0xE1A9A300);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_int_lim");
node->lch()->lch()->intval.append(0xC044682E);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_speed_master_common_kp");
node->lch()->lch()->intval.append(0xE4BC057D);
node->lch()->lch()->values.append("rotor_speed_master_common_ki");
node->lch()->lch()->intval.append(0xC02AE755);
node->lch()->lch()->values.append("rotor_speed_master_common_kb");
node->lch()->lch()->intval.append(0x5686A729);
node->lch()->lch()->values.append("rotor_speed_master_common_kt");
node->lch()->lch()->intval.append(0x7BDEAC66);
node->lch()->lch()->values.append("rotor_speed_master_common_kf");
node->lch()->lch()->intval.append(0xC9E40E32);
node->lch()->lch()->values.append("rotor_speed_master_common_err_lim");
node->lch()->lch()->intval.append(0x2073EC66);
node->lch()->lch()->values.append("rotor_speed_master_common_out_lim");
node->lch()->lch()->intval.append(0x67AF3A32);
node->lch()->lch()->values.append("rotor_speed_master_common_int_lim");
node->lch()->lch()->intval.append(0x4261C897);
node->lch()->lch()->values.append("rotor_speed_master_common_out_rate_lim");
node->lch()->lch()->intval.append(0x53169F2D);
node->lch()->lch()->values.append("rotor_speed_master_common_err_rate_lim");
node->lch()->lch()->intval.append(0x7C6E055F);
node->lch()->lch()->values.append("rotor_speed_master_diff_kp");
node->lch()->lch()->intval.append(0x56EE8F6);
node->lch()->lch()->values.append("rotor_speed_master_diff_ki");
node->lch()->lch()->intval.append(0x21F80ADE);
node->lch()->lch()->values.append("rotor_speed_master_diff_kb");
node->lch()->lch()->intval.append(0xB7544AA2);
node->lch()->lch()->values.append("rotor_speed_master_diff_kt");
node->lch()->lch()->intval.append(0x9A0C41ED);
node->lch()->lch()->values.append("rotor_speed_master_diff_kf");
node->lch()->lch()->intval.append(0x2836E3B9);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_lim");
node->lch()->lch()->intval.append(0xC995954D);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_lim");
node->lch()->lch()->intval.append(0x8E494319);
node->lch()->lch()->values.append("rotor_speed_master_diff_int_lim");
node->lch()->lch()->intval.append(0xAB87B1BC);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_rate_lim");
node->lch()->lch()->intval.append(0xE37276C4);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_rate_lim");
node->lch()->lch()->intval.append(0xCC0AECB6);
node->lch()->lch()->values.append("rotor_speed_role");
node->lch()->lch()->intval.append(0xE8701AA);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kb");
node->lch()->lch()->intval.append(0xD479AC6);
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
node->lch()->lch()->values.append("rotor_ang_dz");
node->lch()->lch()->intval.append(0x7121BD4C);
node->lch()->lch()->values.append("rotor_ang_dz_en");
node->lch()->lch()->intval.append(0x7EC4A057);
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
node->lch()->lch()->values.append("com_if_bup_internal_mcast");
node->lch()->lch()->intval.append(0x5BF96276);
node->lch()->lch()->values.append("com_if_bro_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6F720C87);
node->lch()->lch()->values.append("com_if_im_bro_drive_mcast");
node->lch()->lch()->intval.append(0x64B26340);
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
node->lch()->lch()->values.append("ohp_hyst");
node->lch()->lch()->intval.append(0xB67F1E8);
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
node->lch()->lch()->values.append("load_speed_flt_fc");
node->lch()->lch()->intval.append(0x47B4E0EE);
node->lch()->lch()->values.append("rotor_speed_flt_fc");
node->lch()->lch()->intval.append(0xE4CCE479);
node->lch()->lch()->values.append("load_speed_kp");
node->lch()->lch()->intval.append(0x44EE1601);
node->lch()->lch()->values.append("load_speed_ki");
node->lch()->lch()->intval.append(0x6078F429);
node->lch()->lch()->values.append("load_speed_kb");
node->lch()->lch()->intval.append(0xF6D4B455);
node->lch()->lch()->values.append("load_speed_kt");
node->lch()->lch()->intval.append(0xDB8CBF1A);
node->lch()->lch()->values.append("load_speed_kf");
node->lch()->lch()->intval.append(0x69B61D4E);
node->lch()->lch()->values.append("load_speed_err_lim");
node->lch()->lch()->intval.append(0xDA07EA66);
node->lch()->lch()->values.append("load_speed_out_lim");
node->lch()->lch()->intval.append(0x9DDB3C32);
node->lch()->lch()->values.append("load_speed_int_lim");
node->lch()->lch()->intval.append(0xB815CE97);
node->lch()->lch()->values.append("load_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x4608CFD6);
node->lch()->lch()->values.append("load_speed_err_rate_lim");
node->lch()->lch()->intval.append(0x697055A4);
node->lch()->lch()->values.append("load_ang_rev");
node->lch()->lch()->intval.append(0x96EC79E6);
node->lch()->lch()->values.append("load_ang_kp");
node->lch()->lch()->intval.append(0x380A69BE);
node->lch()->lch()->values.append("load_ang_ki");
node->lch()->lch()->intval.append(0x1C9C8B96);
node->lch()->lch()->values.append("load_ang_kb");
node->lch()->lch()->intval.append(0x8A30CBEA);
node->lch()->lch()->values.append("load_ang_kt");
node->lch()->lch()->intval.append(0xA768C0A5);
node->lch()->lch()->values.append("load_ang_kf");
node->lch()->lch()->intval.append(0x155262F1);
node->lch()->lch()->values.append("load_ang_kd");
node->lch()->lch()->intval.append(0xDAE373A7);
node->lch()->lch()->values.append("load_ang_err_lim");
node->lch()->lch()->intval.append(0x15AB5439);
node->lch()->lch()->values.append("load_ang_out_lim");
node->lch()->lch()->intval.append(0x5277826D);
node->lch()->lch()->values.append("load_ang_out_rate_lim");
node->lch()->lch()->intval.append(0xC6B60F77);
node->lch()->lch()->values.append("load_ang_err_rate_lim");
node->lch()->lch()->intval.append(0xE9CE9505);
node->lch()->lch()->values.append("load_ang_dz");
node->lch()->lch()->intval.append(0x665CAA19);
node->lch()->lch()->values.append("load_ang_dz_en");
node->lch()->lch()->intval.append(0x69B9B702);
node->lch()->lch()->values.append("rotor_speed_kp");
node->lch()->lch()->intval.append(0x53930154);
node->lch()->lch()->values.append("rotor_speed_ki");
node->lch()->lch()->intval.append(0x7705E37C);
node->lch()->lch()->values.append("rotor_speed_kb");
node->lch()->lch()->intval.append(0xE1A9A300);
node->lch()->lch()->values.append("rotor_speed_kt");
node->lch()->lch()->intval.append(0xCCF1A84F);
node->lch()->lch()->values.append("rotor_speed_kf");
node->lch()->lch()->intval.append(0x7ECB0A1B);
node->lch()->lch()->values.append("rotor_speed_err_lim");
node->lch()->lch()->intval.append(0xA2564CDF);
node->lch()->lch()->values.append("rotor_speed_out_lim");
node->lch()->lch()->intval.append(0xE58A9A8B);
node->lch()->lch()->values.append("rotor_speed_int_lim");
node->lch()->lch()->intval.append(0xC044682E);
node->lch()->lch()->values.append("rotor_speed_out_rate_lim");
node->lch()->lch()->intval.append(0x86EE36E2);
node->lch()->lch()->values.append("rotor_speed_err_rate_lim");
node->lch()->lch()->intval.append(0xA996AC90);
node->lch()->lch()->values.append("rotor_speed_master_common_kp");
node->lch()->lch()->intval.append(0xE4BC057D);
node->lch()->lch()->values.append("rotor_speed_master_common_ki");
node->lch()->lch()->intval.append(0xC02AE755);
node->lch()->lch()->values.append("rotor_speed_master_common_kb");
node->lch()->lch()->intval.append(0x5686A729);
node->lch()->lch()->values.append("rotor_speed_master_common_kt");
node->lch()->lch()->intval.append(0x7BDEAC66);
node->lch()->lch()->values.append("rotor_speed_master_common_kf");
node->lch()->lch()->intval.append(0xC9E40E32);
node->lch()->lch()->values.append("rotor_speed_master_common_err_lim");
node->lch()->lch()->intval.append(0x2073EC66);
node->lch()->lch()->values.append("rotor_speed_master_common_out_lim");
node->lch()->lch()->intval.append(0x67AF3A32);
node->lch()->lch()->values.append("rotor_speed_master_common_int_lim");
node->lch()->lch()->intval.append(0x4261C897);
node->lch()->lch()->values.append("rotor_speed_master_common_out_rate_lim");
node->lch()->lch()->intval.append(0x53169F2D);
node->lch()->lch()->values.append("rotor_speed_master_common_err_rate_lim");
node->lch()->lch()->intval.append(0x7C6E055F);
node->lch()->lch()->values.append("rotor_speed_master_diff_kp");
node->lch()->lch()->intval.append(0x56EE8F6);
node->lch()->lch()->values.append("rotor_speed_master_diff_ki");
node->lch()->lch()->intval.append(0x21F80ADE);
node->lch()->lch()->values.append("rotor_speed_master_diff_kb");
node->lch()->lch()->intval.append(0xB7544AA2);
node->lch()->lch()->values.append("rotor_speed_master_diff_kt");
node->lch()->lch()->intval.append(0x9A0C41ED);
node->lch()->lch()->values.append("rotor_speed_master_diff_kf");
node->lch()->lch()->intval.append(0x2836E3B9);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_lim");
node->lch()->lch()->intval.append(0xC995954D);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_lim");
node->lch()->lch()->intval.append(0x8E494319);
node->lch()->lch()->values.append("rotor_speed_master_diff_int_lim");
node->lch()->lch()->intval.append(0xAB87B1BC);
node->lch()->lch()->values.append("rotor_speed_master_diff_out_rate_lim");
node->lch()->lch()->intval.append(0xE37276C4);
node->lch()->lch()->values.append("rotor_speed_master_diff_err_rate_lim");
node->lch()->lch()->intval.append(0xCC0AECB6);
node->lch()->lch()->values.append("rotor_speed_role");
node->lch()->lch()->intval.append(0xE8701AA);
node->lch()->lch()->values.append("rotor_ang_kp");
node->lch()->lch()->intval.append(0xBF7D3892);
node->lch()->lch()->values.append("rotor_ang_ki");
node->lch()->lch()->intval.append(0x9BEBDABA);
node->lch()->lch()->values.append("rotor_ang_kb");
node->lch()->lch()->intval.append(0xD479AC6);
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
node->lch()->lch()->values.append("rotor_ang_dz");
node->lch()->lch()->intval.append(0x7121BD4C);
node->lch()->lch()->values.append("rotor_ang_dz_en");
node->lch()->lch()->intval.append(0x7EC4A057);
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
node->lch()->lch()->values.append("com_if_bup_internal_mcast");
node->lch()->lch()->intval.append(0x5BF96276);
node->lch()->lch()->values.append("com_if_bro_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6F720C87);
node->lch()->lch()->values.append("com_if_im_bro_drive_mcast");
node->lch()->lch()->intval.append(0x64B26340);
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
node->lch()->lch()->values.append("com_if_bro_bup_ctrl_mcast");
node->lch()->lch()->intval.append(0xDDFE2DA4);
node->lch()->lch()->values.append("com_if_bro_bup_data_mcast");
node->lch()->lch()->intval.append(0x6F0DA7DD);
node->lch()->lch()->values.append("com_if_bup_internal_mcast");
node->lch()->lch()->intval.append(0x5BF96276);
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