
#include "signaltree.h"

static TreeNode *cvs_n_tv_heater_state_ptr = 0;
static TreeNode *cvs_pion_heater_ctrl_ptr = 0;
static TreeNode *cvs_pion_power_ctrl_ptr = 0;
static TreeNode *cvs_pion_state_ptr = 0;
static TreeNode *cvs_prm_req_ptr = 0;
static TreeNode *cvs_tp_heater_state_ptr = 0;
static TreeNode *cvs_track_state_ptr = 0;
static TreeNode *cvs_w_tv_heater_state_ptr = 0;
static TreeNode *mon_cmd_req_ptr = 0;
static TreeNode *mon_msg_req_ptr = 0;
static TreeNode *mon_pion_heater_ctrl_ptr = 0;
static TreeNode *mon_pion_power_ctrl_ptr = 0;
static TreeNode *mon_pion_srv_drv_ctrl_ptr = 0;
static TreeNode *mon_prm_req_ptr = 0;
static TreeNode *pion_mku_vn_aim_ang_vn_sens_state_ptr = 0;
static TreeNode *pion_mku_vn_ld_heater_state_ptr = 0;
static TreeNode *pion_mku_vn_pion_power_status_ptr = 0;

static TreeNode *aim_ang_gn_sens_state_ptr = 0;
static TreeNode *cmd_ans_ptr = 0;
static TreeNode *dbg_ptr = 0;
static TreeNode *formular_ptr = 0;
static TreeNode *ld_answer_ptr = 0;
static TreeNode *mku_tel_ptr = 0;
static TreeNode *msg_ans_ptr = 0;
static TreeNode *n_tv_heater_state_ptr = 0;
static TreeNode *pion_ctrl_ptr = 0;
static TreeNode *pion_drv_gn_state_ptr = 0;
static TreeNode *pion_heater_ctrl_ptr = 0;
static TreeNode *pion_power_ctrl_ptr = 0;
static TreeNode *pion_power_status_ptr = 0;
static TreeNode *prm_ans_ptr = 0;
static TreeNode *ptp_state_ptr = 0;
static TreeNode *tp_heater_state_ptr = 0;
static TreeNode *w_tv_heater_state_ptr = 0;

static QStringList devList()
{
    QStringList devs;
	devs.append("wp_imu");
	devs.append("pion_mku_vn");
	devs.append("pion_mku_gn");
	devs.append("bup_dcu_vn");
	devs.append("bup_dcu_gn");
	devs.append("bup_ifu");
	devs.append("mon");
	devs.append("trg");
	devs.append("cvs");
	devs.append("model_drivers");
	devs.append("model_trig");
	devs.append("model_load");
	devs.append("bup_tcu");
	devs.append("bup_pcm");
    devs.append("ALL");
    devs.append("NONE");
    return devs;
}

static QVector<int32_t> devIDs()
{
    QVector<int32_t> ids;
	ids.append(0xA38E);
	ids.append(0x382F);
	ids.append(0xBE06);
	ids.append(0xBBB4);
	ids.append(0x3D9D);
	ids.append(0x5616);
	ids.append(0x6C99);
	ids.append(0xB5C8);
	ids.append(0xBEB1);
	ids.append(0xBDF);
	ids.append(0x39CB);
	ids.append(0x5A87);
	ids.append(0xD657);
	ids.append(0x1F08);
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
        case 0x1EE5D873:
            return QVariant(*(float*)val);
 
        case 0xB84A2AAE:
            return QVariant(*(int*)val);
 
        case 0x5EB1D6A2:
            return QVariant(*(int*)val);
 
        case 0x191EC7B1:
            return QVariant(*(int*)val);
 
        case 0xC6AA70E:
            return QVariant(*(int*)val);
 
        case 0x59F62361:
            return QVariant(*(int*)val);
 
        case 0x70AD98CA:
            return QVariant(*(int*)val);
 
        case 0x22CDAD7A:
            return QVariant(*(int*)val);
 
        case 0x372CD6A3:
            return QVariant(*(int*)val);
 
        case 0x724B2E63:
            return QVariant(*(int*)val);
 
        case 0xB06B673E:
            return QVariant(*(int*)val);
 
        case 0xF50C9FFE:
            return QVariant(*(int*)val);
 
        case 0x424C6256:
            return QVariant(*(int*)val);
 
        case 0x72B9A96:
            return QVariant(*(int*)val);
 
        case 0x552DD596:
            return QVariant(*(int*)val);
 
        case 0x104A2D56:
            return QVariant(*(int*)val);
 
        case 0x4A3FF3D3:
            return QVariant(*(int*)val);
 
        case 0xF580B13:
            return QVariant(*(int*)val);
 
        case 0xD36BB580:
            return QVariant(*(int*)val);
 
        case 0x960C4D40:
            return QVariant(*(int*)val);
 
        case 0xAECF9AA9:
            return QVariant(*(int*)val);
 
        case 0xEBA86269:
            return QVariant(*(int*)val);
 
        case 0x7E4D151D:
            return QVariant(*(int*)val);
 
        case 0x3B2AEDDD:
            return QVariant(*(int*)val);
 
        case 0xDE1AF569:
            return QVariant(*(bool*)val);
 
        case 0xA92645D2:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xC8EE09D4:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x4D7787A8:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x311FD2BA:
            return QVariant(*(bool*)val);
 
        case 0xE54327C5:
            return QVariant(*(bool*)val);
 
        case 0x84A7BB67:
            return QVariant(*(bool*)val);
 
        case 0xC17D8050:
            return QVariant(*(bool*)val);
 
        case 0x2371F357:
            return QVariant(*(int*)val);
 
        case 0xF366F564:
            return QVariant(*(float*)val);
 
        case 0x1FC0BE48:
            return QVariant(*(bool*)val);
 
        case 0xC808D4F3:
            return QVariant(*(float*)val);
 
        case 0x32EFE130:
            return QVariant(*(float*)val);
 
        case 0x3738409D:
            return QVariant(*(float*)val);
 
        case 0xD93B241B:
            return QVariant(*(float*)val);
 
        case 0x7D6BFDE6:
            return QVariant(*(float*)val);
 
        case 0x69D41D8C:
            return QVariant(*(float*)val);
 
        case 0xAFDFC864:
            return QVariant(*(float*)val);
 
        case 0x8B492A4C:
            return QVariant(*(float*)val);
 
        case 0x1DE56A30:
            return QVariant(*(float*)val);
 
        case 0x75A8CBE:
            return QVariant(*(float*)val);
 
        case 0xB2C8E5CC:
            return QVariant(*(float*)val);
 
        case 0x97061769:
            return QVariant(*(float*)val);
 
        case 0xF5B606B6:
            return QVariant(*(float*)val);
 
        case 0x6CCAF151:
            return QVariant(*(float*)val);
 
        case 0x485C1379:
            return QVariant(*(float*)val);
 
        case 0xDEF05305:
            return QVariant(*(float*)val);
 
        case 0x5F51997A:
            return QVariant(*(float*)val);
 
        case 0x7A9F6BDF:
            return QVariant(*(float*)val);
 
        case 0xFD1C2D54:
            return QVariant(*(float*)val);
 
        case 0xD02A8F9C:
            return QVariant(*(float*)val);
 
        case 0xF221BB53:
            return QVariant(*(float*)val);
 
        case 0x8B117320:
            return QVariant(*(float*)val);
 
        case 0xEC285B9D:
            return QVariant(*(float*)val);
 
        case 0x680E6C7F:
            return QVariant(*(float*)val);
 
        case 0x9FAE934A:
            return QVariant(*(float*)val);
 
        case 0x94409FDF:
            return QVariant(*(float*)val);
 
        case 0x8F52D59D:
            return QVariant(*(float*)val);
 
        case 0x5367BD80:
            return QVariant(*(float*)val);
 
        case 0x130904AD:
            return QVariant(*(float*)val);
 
        case 0x379FE685:
            return QVariant(*(float*)val);
 
        case 0xA133A6F9:
            return QVariant(*(float*)val);
 
        case 0xEFE1A46:
            return QVariant(*(float*)val);
 
        case 0xD1CC20CA:
            return QVariant(*(float*)val);
 
        case 0x34A03BCA:
            return QVariant(*(float*)val);
 
        case 0x5C8D187B:
            return QVariant(*(float*)val);
 
        case 0x4832F811:
            return QVariant(*(float*)val);
 
        case 0x1A328A4:
            return QVariant(*(float*)val);
 
        case 0xE5FC7D1D:
            return QVariant(*(float*)val);
 
        case 0x2CDADFF6:
            return QVariant(*(bool*)val);
 
        case 0x5DC2B375:
            return QVariant(*(float*)val);
 
        case 0x3616DF10:
            return QVariant(*(float*)val);
 
        case 0x38C06AE5:
            return QVariant(*(float*)val);
 
        case 0x8EA754D7:
            return QVariant(*(int*)val);
 
        case 0xC434A0D3:
            return QVariant(*(bool*)val);
 
        case 0xEA2EAEC7:
            return QVariant(*(float*)val);
 
        case 0xC7B887BF:
            return QVariant(*(float*)val);
 
        case 0x3D2BB69C:
            return QVariant(*(float*)val);
 
        case 0x76A77EDB:
            return QVariant(*(float*)val);
 
        case 0x5F9E600A:
            return QVariant(*(float*)val);
 
        case 0x8BE30201:
            return QVariant(*(int*)val);
 
        case 0xD94F2803:
            return QVariant(*(float*)val);
 
        case 0x6777563E:
            return QVariant(*(float*)val);
 
        case 0xB6FD8005:
            return QVariant(*(float*)val);
 
        case 0xA83AFFF1:
            return QVariant(*(float*)val);
 
        case 0x541D492A:
            return QVariant(*(float*)val);
 
        case 0xD4CDEB67:
            return QVariant(*(float*)val);
 
        case 0x8F486F03:
            return QVariant(*(float*)val);
 
        case 0x4B6F9372:
            return QVariant(*(float*)val);
 
        case 0x713A2226:
            return QVariant(*(float*)val);
 
        case 0x9BD7FE96:
            return QVariant(*(float*)val);
 
        case 0x177E5548:
            return QVariant(*(float*)val);
 
        case 0xD5F6F1E5:
            return QVariant(*(float*)val);
 
        case 0xBBE09029:
            return QVariant(*(float*)val);
 
        case 0xF16013CD:
            return QVariant(*(float*)val);
 
        case 0x328D84D4:
            return QVariant(*(int*)val);
 
        case 0x9B7D8EC:
            return QVariant(*(bool*)val);
 
        case 0x2C0A778F:
            return QVariant(*(float*)val);
 
        case 0x7DCAC375:
            return QVariant(*(float*)val);
 
        case 0xC080A0D3:
            return QVariant(*(float*)val);
 
        case 0x5FE209C8:
            return QVariant(*(float*)val);
 
        case 0x5E9A3A63:
            return QVariant(*(float*)val);
 
        case 0xD566A4C5:
            return QVariant(*(float*)val);
 
        case 0x4A040DDE:
            return QVariant(*(float*)val);
 
        case 0xFF16CE21:
            return QVariant(*(bool*)val);
 
        case 0x5AD712BA:
            return QVariant(*(int*)val);
 
        case 0xFE4EAF05:
            return QVariant(*(float*)val);
 
        case 0x10FA6DB4:
            return QVariant(*(float*)val);
 
        case 0x8D919959:
            return QVariant(*(bool*)val);
 
        case 0x64ADD15C:
            return QVariant(*(int*)val);
 
        case 0xCAC729F0:
            return QVariant(*(int*)val);
 
        case 0x6042DEB7:
            return QVariant(*(int*)val);
 
        case 0x2C0615FB:
            return QVariant(*(int*)val);
 
        case 0xE3AE1CBB:
            return QVariant(*(int*)val);
 
        case 0x4F11C4CC:
            return QVariant(*(int*)val);
 
        case 0xB9BB8B0D:
            return QVariant(*(int*)val);
 
        case 0xF6BC1251:
            return QVariant(*(int*)val);
 
        case 0xAEC0C821:
            return QVariant(*(int*)val);
 
        case 0x6168C161:
            return QVariant(*(int*)val);
 
        case 0x3B82EC9B:
            return QVariant(*(float*)val);
 
        case 0xDBD19E97:
            return QVariant(*(float*)val);
 
        case 0x70822561:
            return QVariant(*(float*)val);
 
        case 0xDC1E42F7:
            return QVariant(*(float*)val);
 
        case 0x13AF53A1:
            return QVariant(*(float*)val);
 
        case 0x7D45C918:
            return QVariant(*(float*)val);
 
        case 0x129B961F:
            return QVariant(*(float*)val);
 
        case 0x4A12BD87:
            return QVariant(*(int*)val);
 
        case 0x85BAB4C7:
            return QVariant(*(int*)val);
 
        case 0xC0DD4C07:
            return QVariant(*(int*)val);
 
        case 0xDD7FCAC:
            return QVariant(*(int*)val);
 
        case 0x7853C445:
            return QVariant(*(int*)val);
 
        case 0x9330952A:
            return QVariant(*(int*)val);
 
        case 0x81CE8659:
            return QVariant(*(int*)val);
 
        case 0x327A9E98:
            return QVariant(*(float*)val);
 
        case 0x3999AD5F:
            return QVariant(*(float*)val);
 
        case 0x4E25F56E:
            return QVariant(*(float*)val);
 
        case 0xE394CBC1:
            return QVariant(*(float*)val);
 
        case 0x15470387:
            return QVariant(*(float*)val);
 
        case 0x373947FE:
            return QVariant(*(float*)val);
 
        case 0x9A887951:
            return QVariant(*(float*)val);
 
        case 0x6C5BB117:
            return QVariant(*(float*)val);
 
        case 0xFBDE3B20:
            return QVariant(*(float*)val);
 
        case 0x4947081B:
            return QVariant(*(float*)val);
 
        case 0x1F5986CD:
            return QVariant(*(float*)val);
 
        case 0xB0138FA5:
            return QVariant(*(float*)val);
 
        case 0x69C4EFD3:
            return QVariant(*(float*)val);
 
        case 0x6594610D:
            return QVariant(*(int*)val);
 
        case 0xCAD0F98B:
            return QVariant(*(float*)val);
 
        case 0xDB7E81B5:
            return QVariant(*(float*)val);
 
        case 0x617E69D9:
            return QVariant(*(float*)val);
 
        case 0xE16FCC9B:
            return QVariant(*(float*)val);
 
        case 0x28B21F5C:
            return QVariant(*(float*)val);
 
        case 0x46D9457C:
            return QVariant(*(float*)val);
 
        case 0x9E6CE739:
            return QVariant(*(float*)val);
 
        case 0xD02A15D0:
            return QVariant(*(float*)val);
 
        case 0x4A0AB355:
            return QVariant(*(float*)val);
 
        case 0xD0AC7199:
            return QVariant(*(float*)val);
 
        case 0xBF4A83EC:
            return QVariant(*(int*)val);
 
        case 0xD9A71003:
            return QVariant(*(int*)val);
 
        case 0x403E7CB:
            return QVariant(*(int*)val);
 
        case 0x284A2867:
            return QVariant(*(int*)val);
 
        case 0x8B770214:
            return QVariant(*(int*)val);
 
        case 0x159C62A8:
            return QVariant(*(int*)val);
 
        case 0x1D19E932:
            return QVariant(*(bool*)val);
 
        case 0x5C57D2B7:
            return QVariant(*(float*)val);
 
        case 0x501D05A4:
            return QVariant(*(float*)val);
 
        case 0x74C112A:
            return QVariant(*(float*)val);
 
        case 0xA57FD22E:
            return QVariant(*(float*)val);
 
        case 0xBBD3E88F:
            return QVariant(*(float*)val);
 
        case 0x54F313B1:
            return QVariant(*(bool*)val);
 
        case 0xD543F9FE:
            return QVariant(*(bool*)val);
 
        case 0x2CF660C2:
            return QVariant(*(float*)val);
 
        case 0xC4CA33B0:
            return QVariant(*(float*)val);
 
        case 0xF449C211:
            return QVariant(*(float*)val);
 
        case 0x38430DA2:
            return QVariant(*(bool*)val);
 
        case 0x491BE8E9:
            return QVariant(*(bool*)val);
 
        case 0xFC9F76B6:
            return QVariant(*(bool*)val);
 
        case 0x310908E7:
            return QVariant(*(bool*)val);
 
        case 0x9D6ACA45:
            return QVariant(*(bool*)val);
 
        case 0x161CBA22:
            return QVariant(*(float*)val);
 
        case 0xD443BE16:
            return QVariant(*(float*)val);
 
        case 0x35045471:
            return QVariant(*(float*)val);
 
        case 0x507A3C3C:
            return QVariant(*(float*)val);
 
        case 0xDA0658A:
            return QVariant(*(float*)val);
 
        case 0xC7865F20:
            return QVariant(*(float*)val);
 
        case 0x5A8BE1ED:
            return QVariant(*(float*)val);
 
        case 0x800F3056:
            return QVariant(*(float*)val);
 
        case 0xC2BB8B97:
            return QVariant(*(bool*)val);
 
        case 0x4586160E:
            return QVariant(*(float*)val);
 
        case 0x4C62D80B:
            return QVariant(*(float*)val);
 
        case 0x82675000:
            return QVariant(*(float*)val);
 
        case 0xA8331120:
            return QVariant(*(float*)val);
 
        case 0x9C7C61E3:
            return QVariant(*(float*)val);
 
        case 0x236B85E1:
            return QVariant(*(float*)val);
 
        case 0xEC7DAD1B:
            return QVariant(*(float*)val);
 
        case 0xE48AC3EF:
            return QVariant(*(float*)val);
 
        case 0x19FA383F:
            return QVariant(*(int*)val);
 
        case 0xF6087766:
            return QVariant(*(int*)val);
 
        case 0x2DB93F34:
            return QVariant(*(int*)val);
 
        case 0x591F83F3:
            return QVariant(*(float*)val);
 
        case 0x8B93B334:
            return QVariant(*(float*)val);
 
        case 0x9610F8C5:
            return QVariant(*(float*)val);
 
        case 0x1012BC5C:
            return QVariant(*(int*)val);
 
        case 0x76CF657E:
            return QVariant(*(int*)val);
 
        case 0xC5398A3B:
            return QVariant(*(int*)val);
 
        case 0x41647D9:
            return QVariant(*(float*)val);
 
        case 0x6313063B:
            return QVariant(*(float*)val);
 
        case 0x9FF87CA6:
            return QVariant(*(float*)val);
 
        case 0xEDECAE82:
            return QVariant(*(float*)val);
 
        case 0xED7C0BE8:
            return QVariant(*(int*)val);
 
        case 0x5CCB6F4A:
            return QVariant(*(int*)val);
 
        case 0xF4670D59:
            return QVariant(*(int*)val);
 
        case 0xA82F7F43:
            return QVariant(*(float*)val);
 
        case 0x194385F0:
            return QVariant(*(float*)val);
 
        case 0xCAF60192:
            return QVariant(*(float*)val);
 
        case 0x4343E577:
            return QVariant(*(float*)val);
 
        case 0x3080C855:
            return QVariant(*(float*)val);
 
        case 0xE8384A70:
            return QVariant(*(float*)val);
 
        case 0x81F147A8:
            return QVariant(*(float*)val);
 
        case 0x2C377F17:
            return QVariant(*(float*)val);
 
        case 0x8AF08272:
            return QVariant(*(float*)val);
 
        case 0x8D5727F8:
            return QVariant(*(bool*)val);
 
        case 0xE95FB2D8:
            return QVariant(*(bool*)val);
 
        case 0xCFEF85CF:
            return QVariant(*(bool*)val);
 
        case 0x253A968F:
            return QVariant(*(bool*)val);
 
        case 0x2513CD21:
            return QVariant(*(bool*)val);
 
        case 0x715DBFFD:
            return QVariant(*(bool*)val);
 
        case 0xDDAB77E0:
            return QVariant(*(bool*)val);
 
        case 0x12037EA0:
            return QVariant(*(bool*)val);
 
        case 0x57648660:
            return QVariant(*(bool*)val);
 
        case 0x8D53E797:
            return QVariant(*(bool*)val);
 
        case 0x579374D5:
            return QVariant(*(bool*)val);
 
        case 0x983B7D95:
            return QVariant(*(bool*)val);
 
        case 0xDD5C8555:
            return QVariant(*(bool*)val);
 
        case 0x76BE4A2:
            return QVariant(*(bool*)val);
 
        case 0x171202ED:
            return QVariant(*(int*)val);
 
        case 0xD02F610F:
            return QVariant(*(int*)val);
 
        case 0x64BC560E:
            return QVariant(*(int*)val);
 
        case 0x2FDFD0F1:
            return QVariant(*(bool*)val);
 
        case 0x5EA26FE2:
            return QVariant(*(float*)val);
 
        case 0x4406A555:
            return QVariant(*(bool*)val);
 
        case 0x394E7C5C:
            return QVariant(*(int*)val);
 
        case 0xE6557BB2:
            return QVariant(*(bool*)val);
 
        case 0x8EABF9AC:
            return QVariant(*(float*)val);
 
        case 0x2D08847A:
            return QVariant(*(float*)val);
 
        case 0xEAA275A8:
            return QVariant(*(float*)val);
 
        case 0xEBA6B47:
            return QVariant(*(float*)val);
 
        case 0x5041D4FA:
            return QVariant(*(float*)val);
 
        case 0x994D9878:
            return QVariant(*(float*)val);
 
        case 0x248659F:
            return QVariant(*(float*)val);
 
        case 0x4B62DD3C:
            return QVariant(*(float*)val);
 
        case 0x83E3E832:
            return QVariant(*(float*)val);
 
        case 0x54705DB8:
            return QVariant(*(float*)val);
 
        case 0x5F2CAF5:
            return QVariant(*(float*)val);
 
        case 0x6A4D4E0F:
            return QVariant(*(float*)val);
 
        case 0x55589777:
            return QVariant(*(float*)val);
 
        case 0xCB51AC10:
            return QVariant(*(float*)val);
 
        case 0xE961B362:
            return QVariant(*(float*)val);
 
        case 0xF9668FCB:
            return QVariant(*(float*)val);
 
        case 0x9036E515:
            return QVariant(*(float*)val);
 
        case 0x78A9C6C0:
            return QVariant(*(float*)val);
 
        case 0x25C5CC22:
            return QVariant(*(float*)val);
 
        case 0x8F7E8D1:
            return QVariant(*(float*)val);
 
        case 0x14316E6E:
            return QVariant(*(bool*)val);
 
        case 0xCD982C6C:
            return QVariant(*(float*)val);
 
        case 0x8761BC9D:
            return QVariant(*(float*)val);
 
        case 0x41378FDB:
            return QVariant(*(float*)val);
 
        case 0x591CDF49:
            return QVariant(*(float*)val);
 
        case 0xDBAC2D6A:
            return QVariant(*(float*)val);
 
        case 0x9F70AD00:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x5C825B85:
            return QVariant(*(int*)val);
 
        case 0x2D734DD3:
            return QVariant(*(float*)val);
 
        case 0xE7D0A39B:
            return QVariant(*(float*)val);
 
        case 0x87EE734B:
            return QVariant(*(float*)val);
 
        case 0x9080AC90:
            return QVariant(*(int*)val);
 
        case 0x416429AD:
            return QVariant(*(int*)val);
 
        case 0x7BD0A249:
            return QVariant(*(int*)val);
 
        case 0xA059930B:
            return QVariant(*(int*)val);
 
        case 0x54C8A1CA:
            return QVariant(*(int*)val);
 
        case 0x9854F45F:
            return QVariant(*(int*)val);
 
        case 0xA0EDED65:
            return QVariant(*(int*)val);
 
        case 0x4D4EA0F7:
            return QVariant(*(int*)val);
 
        case 0x9C6B2E94:
            return QVariant(*(int*)val);
 
        case 0x5A671E3B:
            return QVariant(*(int*)val);
 
        case 0xA7F68FC0:
            return QVariant(*(int*)val);
 
        case 0x8536FFBB:
            return QVariant(*(float*)val);
 
        case 0x6ABA5290:
            return QVariant(*(float*)val);
 
        case 0xD02F5519:
            return QVariant(*(float*)val);
 
        case 0xFB7DDC79:
            return QVariant(*(float*)val);
 
        case 0x70B25BB3:
            return QVariant(*(float*)val);
 
        case 0x5424B99B:
            return QVariant(*(float*)val);
 
        case 0x925B41AA:
            return QVariant(*(float*)val);
 
        case 0x46293BCC:
            return QVariant(*(float*)val);
 
        case 0xF88316A1:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x4A709CD8:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xA9E451E8:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x1B17DB91:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xBDFA8C51:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x7BA2FE2C:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x51771EC9:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xE38494B0:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xC0AA259A:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x87A52B5F:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x3568B4DA:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xBE85653F:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xE703366F:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x9E21915:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x87AEAD2D:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xBBEFE16E:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x95EE7424:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xB9DD1547:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x271DFE5D:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xB2E9F3E:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x6857720E:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x5B060D18:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xEA688EF1:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xE1990506:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x335FAA57:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x3998C1DF:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x1664ADB7:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x2A1ED2C7:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xF0968B18:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x7928C2E0:
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
    if (id == 0x1EE5D873)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xB84A2AAE)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x5EB1D6A2)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x191EC7B1)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xC6AA70E)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x59F62361)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x70AD98CA)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x22CDAD7A)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x372CD6A3)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x724B2E63)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xB06B673E)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xF50C9FFE)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x424C6256)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x72B9A96)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x552DD596)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x104A2D56)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x4A3FF3D3)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xF580B13)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xD36BB580)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x960C4D40)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xAECF9AA9)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xEBA86269)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x7E4D151D)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x3B2AEDDD)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xDE1AF569)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
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
    if (id == 0x311FD2BA)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xE54327C5)
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
    if (id == 0x2371F357)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xF366F564)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x1FC0BE48)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xC808D4F3)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x32EFE130)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x3738409D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD93B241B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7D6BFDE6)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x69D41D8C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xAFDFC864)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8B492A4C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x1DE56A30)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x75A8CBE)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xB2C8E5CC)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x97061769)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xF5B606B6)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x6CCAF151)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x485C1379)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xDEF05305)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5F51997A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7A9F6BDF)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xFD1C2D54)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD02A8F9C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xF221BB53)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8B117320)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xEC285B9D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x680E6C7F)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9FAE934A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x94409FDF)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8F52D59D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5367BD80)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x130904AD)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x379FE685)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA133A6F9)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xEFE1A46)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD1CC20CA)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x34A03BCA)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5C8D187B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4832F811)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x1A328A4)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE5FC7D1D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x2CDADFF6)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x5DC2B375)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x3616DF10)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x38C06AE5)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8EA754D7)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xC434A0D3)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xEA2EAEC7)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xC7B887BF)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x3D2BB69C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x76A77EDB)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5F9E600A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8BE30201)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xD94F2803)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x6777563E)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xB6FD8005)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA83AFFF1)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x541D492A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD4CDEB67)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8F486F03)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4B6F9372)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x713A2226)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9BD7FE96)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x177E5548)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD5F6F1E5)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xBBE09029)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xF16013CD)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x328D84D4)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x9B7D8EC)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x2C0A778F)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7DCAC375)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xC080A0D3)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5FE209C8)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5E9A3A63)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD566A4C5)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4A040DDE)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xFF16CE21)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x5AD712BA)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xFE4EAF05)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x10FA6DB4)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8D919959)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x64ADD15C)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xCAC729F0)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x6042DEB7)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x2C0615FB)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xE3AE1CBB)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x4F11C4CC)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xB9BB8B0D)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xF6BC1251)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xAEC0C821)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x6168C161)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x3B82EC9B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xDBD19E97)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x70822561)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xDC1E42F7)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x13AF53A1)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x7D45C918)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x129B961F)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4A12BD87)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x85BAB4C7)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xC0DD4C07)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xDD7FCAC)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x7853C445)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x9330952A)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x81CE8659)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x327A9E98)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x3999AD5F)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4E25F56E)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE394CBC1)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x15470387)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x373947FE)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9A887951)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x6C5BB117)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xFBDE3B20)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4947081B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x1F5986CD)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xB0138FA5)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x69C4EFD3)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x6594610D)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xCAD0F98B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xDB7E81B5)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x617E69D9)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE16FCC9B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x28B21F5C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x46D9457C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9E6CE739)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD02A15D0)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4A0AB355)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD0AC7199)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xBF4A83EC)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xD9A71003)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x403E7CB)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x284A2867)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x8B770214)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x159C62A8)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x1D19E932)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
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
    if (id == 0x74C112A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA57FD22E)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xBBD3E88F)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x54F313B1)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xD543F9FE)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x2CF660C2)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xC4CA33B0)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xF449C211)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x38430DA2)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x491BE8E9)
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
    if (id == 0x9D6ACA45)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x161CBA22)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD443BE16)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x35045471)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x507A3C3C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xDA0658A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xC7865F20)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5A8BE1ED)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x800F3056)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xC2BB8B97)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x4586160E)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4C62D80B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x82675000)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xA8331120)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9C7C61E3)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x236B85E1)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xEC7DAD1B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE48AC3EF)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x19FA383F)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xF6087766)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x2DB93F34)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x591F83F3)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8B93B334)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9610F8C5)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x1012BC5C)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x76CF657E)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xC5398A3B)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x41647D9)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x6313063B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9FF87CA6)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xEDECAE82)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xED7C0BE8)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x5CCB6F4A)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xF4670D59)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xA82F7F43)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x194385F0)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xCAF60192)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4343E577)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x3080C855)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE8384A70)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x81F147A8)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x2C377F17)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8AF08272)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8D5727F8)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xE95FB2D8)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xCFEF85CF)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x253A968F)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x2513CD21)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x715DBFFD)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xDDAB77E0)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x12037EA0)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x57648660)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x8D53E797)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x579374D5)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x983B7D95)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xDD5C8555)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x76BE4A2)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x171202ED)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xD02F610F)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x64BC560E)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x2FDFD0F1)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x5EA26FE2)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4406A555)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x394E7C5C)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xE6557BB2)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0x8EABF9AC)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x2D08847A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xEAA275A8)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xEBA6B47)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5041D4FA)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x994D9878)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x248659F)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x4B62DD3C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x83E3E832)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x54705DB8)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x5F2CAF5)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x6A4D4E0F)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x55589777)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xCB51AC10)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE961B362)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xF9668FCB)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9036E515)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x78A9C6C0)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x25C5CC22)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8F7E8D1)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x14316E6E)
    {
        bool val_ = data.value<bool>();
        memcpy(val,&(val_),sizeof(bool));
 
    } else 
    if (id == 0xCD982C6C)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x8761BC9D)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x41378FDB)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x591CDF49)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xDBAC2D6A)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9F70AD00)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x5C825B85)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x2D734DD3)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xE7D0A39B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x87EE734B)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x9080AC90)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x416429AD)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x7BD0A249)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xA059930B)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x54C8A1CA)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x9854F45F)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xA0EDED65)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x4D4EA0F7)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x9C6B2E94)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x5A671E3B)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0xA7F68FC0)
    {
        int val_ = data.value<int>();
        memcpy(val,&(val_),sizeof(int));
 
    } else 
    if (id == 0x8536FFBB)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0x6ABA5290)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xD02F5519)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xFB7DDC79)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
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
    if (id == 0x46293BCC)
    {
        float val_ = data.value<float>();
        memcpy(val,&(val_),sizeof(float));
 
    } else 
    if (id == 0xF88316A1)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x4A709CD8)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xA9E451E8)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x1B17DB91)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xBDFA8C51)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x7BA2FE2C)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x51771EC9)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xE38494B0)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xC0AA259A)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x87A52B5F)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x3568B4DA)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xBE85653F)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xE703366F)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x9E21915)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x87AEAD2D)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xBBEFE16E)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x95EE7424)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xB9DD1547)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x271DFE5D)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xB2E9F3E)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x6857720E)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x5B060D18)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xEA688EF1)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xE1990506)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x335FAA57)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x3998C1DF)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x1664ADB7)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x2A1ED2C7)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xF0968B18)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x7928C2E0)
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


TreeNode * create_pion_mku_gn_in_tree(mj_pion_mku_gn_t * mj_ptr)
{
static mj_pion_mku_gn_t *mj = mj_ptr;
TreeNode * node = new TreeNode("INPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
TreeNode * cvs_node = node->add("cvs",[](){return QVariant();});
cvs_node->isDev = true;
cvs_n_tv_heater_state_ptr = node->lch()->add("n_tv_heater_state",[](){return QVariant(mj->in.cvs.n_tv_heater_state.msg->hdr.cnt);});
cvs_n_tv_heater_state_ptr->state = []()->int32_t{return mj->in.cvs.n_tv_heater_state.state;};
cvs_n_tv_heater_state_ptr->msgId = ID_N_TV_HEATER_STATE;
cvs_n_tv_heater_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.cvs.n_tv_heater_state.msg->hdr.ts_s)+static_cast<double>(mj->in.cvs.n_tv_heater_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.cvs.n_tv_heater_state.msg->mode));},[](){return (heater_mode_str(mj->in.cvs.n_tv_heater_state.msg->mode));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.cvs.n_tv_heater_state.msg->state));},[](){return (heater_status_str(mj->in.cvs.n_tv_heater_state.msg->state));});
node->lch()->lch()->add("temp",[](){return QVariant(mj->in.cvs.n_tv_heater_state.msg->temp);});
mj->in.cvs.n_tv_heater_state.upd_cb = [](){ cvs_n_tv_heater_state_ptr->upd(mj->in.cvs.n_tv_heater_state.ts_s, mj->in.cvs.n_tv_heater_state.ts_ns);};
cvs_pion_heater_ctrl_ptr = node->lch()->add("pion_heater_ctrl",[](){return QVariant(mj->in.cvs.pion_heater_ctrl.msg->hdr.cnt);});
cvs_pion_heater_ctrl_ptr->state = []()->int32_t{return mj->in.cvs.pion_heater_ctrl.state;};
cvs_pion_heater_ctrl_ptr->msgId = ID_PION_HEATER_CTRL;
cvs_pion_heater_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.cvs.pion_heater_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.cvs.pion_heater_ctrl.msg->hdr.ts_ns)/1e9);});

cvs_pion_heater_ctrl_ptr->isReq = true;
cvs_pion_heater_ctrl_ptr->srcId = KAUZU_CVS;
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.cvs.pion_heater_ctrl.msg->mode));},[](){return (heater_mode_str(mj->in.cvs.pion_heater_ctrl.msg->mode));});
node->lch()->lch()->add("place",[](){return QVariant((int32_t)(mj->in.cvs.pion_heater_ctrl.msg->place));},[](){return (heater_place_str(mj->in.cvs.pion_heater_ctrl.msg->place));});
mj->in.cvs.pion_heater_ctrl.upd_cb = [](){ cvs_pion_heater_ctrl_ptr->upd(mj->in.cvs.pion_heater_ctrl.ts_s, mj->in.cvs.pion_heater_ctrl.ts_ns);};
cvs_pion_power_ctrl_ptr = node->lch()->add("pion_power_ctrl",[](){return QVariant(mj->in.cvs.pion_power_ctrl.msg->hdr.cnt);});
cvs_pion_power_ctrl_ptr->state = []()->int32_t{return mj->in.cvs.pion_power_ctrl.state;};
cvs_pion_power_ctrl_ptr->msgId = ID_PION_POWER_CTRL;
cvs_pion_power_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.cvs.pion_power_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.cvs.pion_power_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("cam_narrow_tv",[](){return QVariant((int32_t)(mj->in.cvs.pion_power_ctrl.msg->cam_narrow_tv));},[](){return (power_line_state_str(mj->in.cvs.pion_power_ctrl.msg->cam_narrow_tv));});
node->lch()->lch()->add("cam_wide_tv",[](){return QVariant((int32_t)(mj->in.cvs.pion_power_ctrl.msg->cam_wide_tv));},[](){return (power_line_state_str(mj->in.cvs.pion_power_ctrl.msg->cam_wide_tv));});
node->lch()->lch()->add("cam_tp",[](){return QVariant((int32_t)(mj->in.cvs.pion_power_ctrl.msg->cam_tp));},[](){return (power_line_state_str(mj->in.cvs.pion_power_ctrl.msg->cam_tp));});
node->lch()->lch()->add("ld",[](){return QVariant((int32_t)(mj->in.cvs.pion_power_ctrl.msg->ld));},[](){return (power_line_state_str(mj->in.cvs.pion_power_ctrl.msg->ld));});
node->lch()->lch()->add("cvs",[](){return QVariant((int32_t)(mj->in.cvs.pion_power_ctrl.msg->cvs));},[](){return (power_line_state_str(mj->in.cvs.pion_power_ctrl.msg->cvs));});
node->lch()->lch()->add("gyro",[](){return QVariant((int32_t)(mj->in.cvs.pion_power_ctrl.msg->gyro));},[](){return (power_line_state_str(mj->in.cvs.pion_power_ctrl.msg->gyro));});
node->lch()->lch()->add("line_5v",[](){return QVariant((int32_t)(mj->in.cvs.pion_power_ctrl.msg->line_5v));},[](){return (power_line_state_str(mj->in.cvs.pion_power_ctrl.msg->line_5v));});
node->lch()->lch()->add("adcu_vn",[](){return QVariant((int32_t)(mj->in.cvs.pion_power_ctrl.msg->adcu_vn));},[](){return (power_line_state_str(mj->in.cvs.pion_power_ctrl.msg->adcu_vn));});
mj->in.cvs.pion_power_ctrl.upd_cb = [](){ cvs_pion_power_ctrl_ptr->upd(mj->in.cvs.pion_power_ctrl.ts_s, mj->in.cvs.pion_power_ctrl.ts_ns);};
cvs_pion_state_ptr = node->lch()->add("pion_state",[](){return QVariant(mj->in.cvs.pion_state.msg->hdr.cnt);});
cvs_pion_state_ptr->state = []()->int32_t{return mj->in.cvs.pion_state.state;};
cvs_pion_state_ptr->msgId = ID_PION_STATE;
cvs_pion_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.cvs.pion_state.msg->hdr.ts_s)+static_cast<double>(mj->in.cvs.pion_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.cvs.pion_state.msg->mode));},[](){return (aim_mode_str(mj->in.cvs.pion_state.msg->mode));});
node->lch()->lch()->add("arret_state",[](){return QVariant((int32_t)(mj->in.cvs.pion_state.msg->arret_state));},[](){return (aim_arret_state_str(mj->in.cvs.pion_state.msg->arret_state));});
node->lch()->lch()->add("arret_ev",[](){return QVariant((int32_t)(mj->in.cvs.pion_state.msg->arret_ev));},[](){return (aim_arret_event_str(mj->in.cvs.pion_state.msg->arret_ev));});
node->lch()->lch()->add("tv",[](){return QVariant((int32_t)(mj->in.cvs.pion_state.msg->tv));},[](){return (aim_fov_type_str(mj->in.cvs.pion_state.msg->tv));});
node->lch()->lch()->add("tp",[](){return QVariant((int32_t)(mj->in.cvs.pion_state.msg->tp));},[](){return (aim_fov_type_str(mj->in.cvs.pion_state.msg->tp));});
mj->in.cvs.pion_state.upd_cb = [](){ cvs_pion_state_ptr->upd(mj->in.cvs.pion_state.ts_s, mj->in.cvs.pion_state.ts_ns);};
cvs_prm_req_ptr = node->lch()->add("prm_req",[](){return QVariant(mj->in.cvs.prm_req.msg->hdr.cnt);});
cvs_prm_req_ptr->state = []()->int32_t{return mj->in.cvs.prm_req.state;};
cvs_prm_req_ptr->msgId = ID_PRM_REQ;
cvs_prm_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.cvs.prm_req.msg->hdr.ts_s)+static_cast<double>(mj->in.cvs.prm_req.msg->hdr.ts_ns)/1e9);});

cvs_prm_req_ptr->isReq = true;
cvs_prm_req_ptr->srcId = KAUZU_CVS;
node->lch()->lch()->add("type",[](){return QVariant((int32_t)(mj->in.cvs.prm_req.msg->type));},[](){return (parameter_request_type_str(mj->in.cvs.prm_req.msg->type));});
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.cvs.prm_req.msg->id));},[](){return (mj_get_prm_name(mj->in.cvs.prm_req.msg->id));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.cvs.prm_req.msg->id,(uint8_t*)mj->in.cvs.prm_req.msg->val,sizeof(mj->in.cvs.prm_req.msg->val)));});
mj->in.cvs.prm_req.upd_cb = [](){ cvs_prm_req_ptr->upd(mj->in.cvs.prm_req.ts_s, mj->in.cvs.prm_req.ts_ns);};
cvs_tp_heater_state_ptr = node->lch()->add("tp_heater_state",[](){return QVariant(mj->in.cvs.tp_heater_state.msg->hdr.cnt);});
cvs_tp_heater_state_ptr->state = []()->int32_t{return mj->in.cvs.tp_heater_state.state;};
cvs_tp_heater_state_ptr->msgId = ID_TP_HEATER_STATE;
cvs_tp_heater_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.cvs.tp_heater_state.msg->hdr.ts_s)+static_cast<double>(mj->in.cvs.tp_heater_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.cvs.tp_heater_state.msg->mode));},[](){return (heater_mode_str(mj->in.cvs.tp_heater_state.msg->mode));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.cvs.tp_heater_state.msg->state));},[](){return (heater_status_str(mj->in.cvs.tp_heater_state.msg->state));});
node->lch()->lch()->add("temp",[](){return QVariant(mj->in.cvs.tp_heater_state.msg->temp);});
mj->in.cvs.tp_heater_state.upd_cb = [](){ cvs_tp_heater_state_ptr->upd(mj->in.cvs.tp_heater_state.ts_s, mj->in.cvs.tp_heater_state.ts_ns);};
cvs_track_state_ptr = node->lch()->add("track_state",[](){return QVariant(mj->in.cvs.track_state.msg->hdr.cnt);});
cvs_track_state_ptr->state = []()->int32_t{return mj->in.cvs.track_state.state;};
cvs_track_state_ptr->msgId = ID_TRACK_STATE;
cvs_track_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.cvs.track_state.msg->hdr.ts_s)+static_cast<double>(mj->in.cvs.track_state.msg->hdr.ts_ns)/1e9);});

cvs_track_state_ptr->isReq = true;
cvs_track_state_ptr->srcId = KAUZU_CVS;
node->lch()->lch()->add("az",[](){return QVariant(mj->in.cvs.track_state.msg->az);});
node->lch()->lch()->add("el",[](){return QVariant(mj->in.cvs.track_state.msg->el);});
node->lch()->lch()->add("err_az",[](){return QVariant(mj->in.cvs.track_state.msg->err_az);});
node->lch()->lch()->add("err_um",[](){return QVariant(mj->in.cvs.track_state.msg->err_um);});
node->lch()->lch()->add("delay",[](){return QVariant(mj->in.cvs.track_state.msg->delay);});
node->lch()->lch()->add("pos",[](){return QVariant();});
node->lch()->lch()->lch()->add("x",[](){return QVariant(mj->in.cvs.track_state.msg->pos.x);});
node->lch()->lch()->lch()->add("y",[](){return QVariant(mj->in.cvs.track_state.msg->pos.y);});
node->lch()->lch()->lch()->add("z",[](){return QVariant(mj->in.cvs.track_state.msg->pos.z);});
node->lch()->lch()->add("vel",[](){return QVariant();});
node->lch()->lch()->lch()->add("x",[](){return QVariant(mj->in.cvs.track_state.msg->vel.x);});
node->lch()->lch()->lch()->add("y",[](){return QVariant(mj->in.cvs.track_state.msg->vel.y);});
node->lch()->lch()->lch()->add("z",[](){return QVariant(mj->in.cvs.track_state.msg->vel.z);});
node->lch()->lch()->add("cart_is_ready",[](){return QVariant(mj->in.cvs.track_state.msg->cart_is_ready);});
node->lch()->lch()->add("trk_channel",[](){return QVariant((int32_t)(mj->in.cvs.track_state.msg->trk_channel));},[](){return (channel_modes_str(mj->in.cvs.track_state.msg->trk_channel));});
mj->in.cvs.track_state.upd_cb = [](){ cvs_track_state_ptr->upd(mj->in.cvs.track_state.ts_s, mj->in.cvs.track_state.ts_ns);};
cvs_w_tv_heater_state_ptr = node->lch()->add("w_tv_heater_state",[](){return QVariant(mj->in.cvs.w_tv_heater_state.msg->hdr.cnt);});
cvs_w_tv_heater_state_ptr->state = []()->int32_t{return mj->in.cvs.w_tv_heater_state.state;};
cvs_w_tv_heater_state_ptr->msgId = ID_W_TV_HEATER_STATE;
cvs_w_tv_heater_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.cvs.w_tv_heater_state.msg->hdr.ts_s)+static_cast<double>(mj->in.cvs.w_tv_heater_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.cvs.w_tv_heater_state.msg->mode));},[](){return (heater_mode_str(mj->in.cvs.w_tv_heater_state.msg->mode));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.cvs.w_tv_heater_state.msg->state));},[](){return (heater_status_str(mj->in.cvs.w_tv_heater_state.msg->state));});
node->lch()->lch()->add("temp",[](){return QVariant(mj->in.cvs.w_tv_heater_state.msg->temp);});
mj->in.cvs.w_tv_heater_state.upd_cb = [](){ cvs_w_tv_heater_state_ptr->upd(mj->in.cvs.w_tv_heater_state.ts_s, mj->in.cvs.w_tv_heater_state.ts_ns);};
TreeNode * mon_node = node->add("mon",[](){return QVariant();});
mon_node->isDev = true;
mon_cmd_req_ptr = node->lch()->add("cmd_req",[](){return QVariant(mj->in.mon.cmd_req.msg->hdr.cnt);});
mon_cmd_req_ptr->state = []()->int32_t{return mj->in.mon.cmd_req.state;};
mon_cmd_req_ptr->msgId = ID_CMD_REQ;
mon_cmd_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.cmd_req.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.cmd_req.msg->hdr.ts_ns)/1e9);});

mon_cmd_req_ptr->isReq = true;
mon_cmd_req_ptr->srcId = KAUZU_MON;
node->lch()->lch()->add("type",[](){return QVariant((int32_t)(mj->in.mon.cmd_req.msg->type));},[](){return (command_type_str(mj->in.mon.cmd_req.msg->type));});
mj->in.mon.cmd_req.upd_cb = [](){ mon_cmd_req_ptr->upd(mj->in.mon.cmd_req.ts_s, mj->in.mon.cmd_req.ts_ns);};
mon_msg_req_ptr = node->lch()->add("msg_req",[](){return QVariant(mj->in.mon.msg_req.msg->hdr.cnt);});
mon_msg_req_ptr->state = []()->int32_t{return mj->in.mon.msg_req.state;};
mon_msg_req_ptr->msgId = ID_MSG_REQ;
mon_msg_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.msg_req.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.msg_req.msg->hdr.ts_ns)/1e9);});

mon_msg_req_ptr->isReq = true;
mon_msg_req_ptr->srcId = KAUZU_MON;
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.mon.msg_req.msg->id));},[](){return (mj_get_msg_name(mj->in.mon.msg_req.msg->id));});
mj->in.mon.msg_req.upd_cb = [](){ mon_msg_req_ptr->upd(mj->in.mon.msg_req.ts_s, mj->in.mon.msg_req.ts_ns);};
mon_pion_heater_ctrl_ptr = node->lch()->add("pion_heater_ctrl",[](){return QVariant(mj->in.mon.pion_heater_ctrl.msg->hdr.cnt);});
mon_pion_heater_ctrl_ptr->state = []()->int32_t{return mj->in.mon.pion_heater_ctrl.state;};
mon_pion_heater_ctrl_ptr->msgId = ID_PION_HEATER_CTRL;
mon_pion_heater_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.pion_heater_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.pion_heater_ctrl.msg->hdr.ts_ns)/1e9);});

mon_pion_heater_ctrl_ptr->isReq = true;
mon_pion_heater_ctrl_ptr->srcId = KAUZU_MON;
node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.pion_heater_ctrl.msg->mode));},[](){return (heater_mode_str(mj->in.mon.pion_heater_ctrl.msg->mode));});
node->lch()->lch()->add("place",[](){return QVariant((int32_t)(mj->in.mon.pion_heater_ctrl.msg->place));},[](){return (heater_place_str(mj->in.mon.pion_heater_ctrl.msg->place));});
mj->in.mon.pion_heater_ctrl.upd_cb = [](){ mon_pion_heater_ctrl_ptr->upd(mj->in.mon.pion_heater_ctrl.ts_s, mj->in.mon.pion_heater_ctrl.ts_ns);};
mon_pion_power_ctrl_ptr = node->lch()->add("pion_power_ctrl",[](){return QVariant(mj->in.mon.pion_power_ctrl.msg->hdr.cnt);});
mon_pion_power_ctrl_ptr->state = []()->int32_t{return mj->in.mon.pion_power_ctrl.state;};
mon_pion_power_ctrl_ptr->msgId = ID_PION_POWER_CTRL;
mon_pion_power_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.pion_power_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.pion_power_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("cam_narrow_tv",[](){return QVariant((int32_t)(mj->in.mon.pion_power_ctrl.msg->cam_narrow_tv));},[](){return (power_line_state_str(mj->in.mon.pion_power_ctrl.msg->cam_narrow_tv));});
node->lch()->lch()->add("cam_wide_tv",[](){return QVariant((int32_t)(mj->in.mon.pion_power_ctrl.msg->cam_wide_tv));},[](){return (power_line_state_str(mj->in.mon.pion_power_ctrl.msg->cam_wide_tv));});
node->lch()->lch()->add("cam_tp",[](){return QVariant((int32_t)(mj->in.mon.pion_power_ctrl.msg->cam_tp));},[](){return (power_line_state_str(mj->in.mon.pion_power_ctrl.msg->cam_tp));});
node->lch()->lch()->add("ld",[](){return QVariant((int32_t)(mj->in.mon.pion_power_ctrl.msg->ld));},[](){return (power_line_state_str(mj->in.mon.pion_power_ctrl.msg->ld));});
node->lch()->lch()->add("cvs",[](){return QVariant((int32_t)(mj->in.mon.pion_power_ctrl.msg->cvs));},[](){return (power_line_state_str(mj->in.mon.pion_power_ctrl.msg->cvs));});
node->lch()->lch()->add("gyro",[](){return QVariant((int32_t)(mj->in.mon.pion_power_ctrl.msg->gyro));},[](){return (power_line_state_str(mj->in.mon.pion_power_ctrl.msg->gyro));});
node->lch()->lch()->add("line_5v",[](){return QVariant((int32_t)(mj->in.mon.pion_power_ctrl.msg->line_5v));},[](){return (power_line_state_str(mj->in.mon.pion_power_ctrl.msg->line_5v));});
node->lch()->lch()->add("adcu_vn",[](){return QVariant((int32_t)(mj->in.mon.pion_power_ctrl.msg->adcu_vn));},[](){return (power_line_state_str(mj->in.mon.pion_power_ctrl.msg->adcu_vn));});
mj->in.mon.pion_power_ctrl.upd_cb = [](){ mon_pion_power_ctrl_ptr->upd(mj->in.mon.pion_power_ctrl.ts_s, mj->in.mon.pion_power_ctrl.ts_ns);};
mon_pion_srv_drv_ctrl_ptr = node->lch()->add("pion_srv_drv_ctrl",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->hdr.cnt);});
mon_pion_srv_drv_ctrl_ptr->state = []()->int32_t{return mj->in.mon.pion_srv_drv_ctrl.state;};
mon_pion_srv_drv_ctrl_ptr->msgId = ID_PION_SRV_DRV_CTRL;
mon_pion_srv_drv_ctrl_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.pion_srv_drv_ctrl.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.pion_srv_drv_ctrl.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("az",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.pion_srv_drv_ctrl.msg->az.mode));},[](){return (drv_ctrl_mode_str(mj->in.mon.pion_srv_drv_ctrl.msg->az.mode));});
node->lch()->lch()->lch()->add("err",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->az.err);});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->az.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->az.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->az.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->az.current);});
node->lch()->lch()->add("el",[](){return QVariant();});
node->lch()->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.mon.pion_srv_drv_ctrl.msg->el.mode));},[](){return (drv_ctrl_mode_str(mj->in.mon.pion_srv_drv_ctrl.msg->el.mode));});
node->lch()->lch()->lch()->add("err",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->el.err);});
node->lch()->lch()->lch()->add("angle",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->el.angle);});
node->lch()->lch()->lch()->add("speed",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->el.speed);});
node->lch()->lch()->lch()->add("voltage",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->el.voltage);});
node->lch()->lch()->lch()->add("current",[](){return QVariant(mj->in.mon.pion_srv_drv_ctrl.msg->el.current);});
mj->in.mon.pion_srv_drv_ctrl.upd_cb = [](){ mon_pion_srv_drv_ctrl_ptr->upd(mj->in.mon.pion_srv_drv_ctrl.ts_s, mj->in.mon.pion_srv_drv_ctrl.ts_ns);};
mon_prm_req_ptr = node->lch()->add("prm_req",[](){return QVariant(mj->in.mon.prm_req.msg->hdr.cnt);});
mon_prm_req_ptr->state = []()->int32_t{return mj->in.mon.prm_req.state;};
mon_prm_req_ptr->msgId = ID_PRM_REQ;
mon_prm_req_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.mon.prm_req.msg->hdr.ts_s)+static_cast<double>(mj->in.mon.prm_req.msg->hdr.ts_ns)/1e9);});

mon_prm_req_ptr->isReq = true;
mon_prm_req_ptr->srcId = KAUZU_MON;
node->lch()->lch()->add("type",[](){return QVariant((int32_t)(mj->in.mon.prm_req.msg->type));},[](){return (parameter_request_type_str(mj->in.mon.prm_req.msg->type));});
node->lch()->lch()->add("id",[](){return QVariant((int32_t)(mj->in.mon.prm_req.msg->id));},[](){return (mj_get_prm_name(mj->in.mon.prm_req.msg->id));});
node->lch()->lch()->add("val",[](){return QVariant(prm2QVariant(mj->in.mon.prm_req.msg->id,(uint8_t*)mj->in.mon.prm_req.msg->val,sizeof(mj->in.mon.prm_req.msg->val)));});
mj->in.mon.prm_req.upd_cb = [](){ mon_prm_req_ptr->upd(mj->in.mon.prm_req.ts_s, mj->in.mon.prm_req.ts_ns);};
TreeNode * pion_mku_vn_node = node->add("pion_mku_vn",[](){return QVariant();});
pion_mku_vn_node->isDev = true;
pion_mku_vn_aim_ang_vn_sens_state_ptr = node->lch()->add("aim_ang_vn_sens_state",[](){return QVariant(mj->in.pion_mku_vn.aim_ang_vn_sens_state.msg->hdr.cnt);});
pion_mku_vn_aim_ang_vn_sens_state_ptr->state = []()->int32_t{return mj->in.pion_mku_vn.aim_ang_vn_sens_state.state;};
pion_mku_vn_aim_ang_vn_sens_state_ptr->msgId = ID_AIM_ANG_VN_SENS_STATE;
pion_mku_vn_aim_ang_vn_sens_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.pion_mku_vn.aim_ang_vn_sens_state.msg->hdr.ts_s)+static_cast<double>(mj->in.pion_mku_vn.aim_ang_vn_sens_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("angle",[](){return QVariant(mj->in.pion_mku_vn.aim_ang_vn_sens_state.msg->angle);});
node->lch()->lch()->add("status",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.aim_ang_vn_sens_state.msg->status));},[](){return (ang_sens_status_str(mj->in.pion_mku_vn.aim_ang_vn_sens_state.msg->status));});
mj->in.pion_mku_vn.aim_ang_vn_sens_state.upd_cb = [](){ pion_mku_vn_aim_ang_vn_sens_state_ptr->upd(mj->in.pion_mku_vn.aim_ang_vn_sens_state.ts_s, mj->in.pion_mku_vn.aim_ang_vn_sens_state.ts_ns);};
pion_mku_vn_ld_heater_state_ptr = node->lch()->add("ld_heater_state",[](){return QVariant(mj->in.pion_mku_vn.ld_heater_state.msg->hdr.cnt);});
pion_mku_vn_ld_heater_state_ptr->state = []()->int32_t{return mj->in.pion_mku_vn.ld_heater_state.state;};
pion_mku_vn_ld_heater_state_ptr->msgId = ID_LD_HEATER_STATE;
pion_mku_vn_ld_heater_state_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.pion_mku_vn.ld_heater_state.msg->hdr.ts_s)+static_cast<double>(mj->in.pion_mku_vn.ld_heater_state.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("mode",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.ld_heater_state.msg->mode));},[](){return (heater_mode_str(mj->in.pion_mku_vn.ld_heater_state.msg->mode));});
node->lch()->lch()->add("state",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.ld_heater_state.msg->state));},[](){return (heater_status_str(mj->in.pion_mku_vn.ld_heater_state.msg->state));});
node->lch()->lch()->add("temp",[](){return QVariant(mj->in.pion_mku_vn.ld_heater_state.msg->temp);});
mj->in.pion_mku_vn.ld_heater_state.upd_cb = [](){ pion_mku_vn_ld_heater_state_ptr->upd(mj->in.pion_mku_vn.ld_heater_state.ts_s, mj->in.pion_mku_vn.ld_heater_state.ts_ns);};
pion_mku_vn_pion_power_status_ptr = node->lch()->add("pion_power_status",[](){return QVariant(mj->in.pion_mku_vn.pion_power_status.msg->hdr.cnt);});
pion_mku_vn_pion_power_status_ptr->state = []()->int32_t{return mj->in.pion_mku_vn.pion_power_status.state;};
pion_mku_vn_pion_power_status_ptr->msgId = ID_PION_POWER_STATUS;
pion_mku_vn_pion_power_status_ptr->add("time",[](){return QVariant(static_cast<double>(mj->in.pion_mku_vn.pion_power_status.msg->hdr.ts_s)+static_cast<double>(mj->in.pion_mku_vn.pion_power_status.msg->hdr.ts_ns)/1e9);});

node->lch()->lch()->add("cam_narrow_tv",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.pion_power_status.msg->cam_narrow_tv));},[](){return (power_line_state_str(mj->in.pion_mku_vn.pion_power_status.msg->cam_narrow_tv));});
node->lch()->lch()->add("cam_wide_tv",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.pion_power_status.msg->cam_wide_tv));},[](){return (power_line_state_str(mj->in.pion_mku_vn.pion_power_status.msg->cam_wide_tv));});
node->lch()->lch()->add("cam_tp",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.pion_power_status.msg->cam_tp));},[](){return (power_line_state_str(mj->in.pion_mku_vn.pion_power_status.msg->cam_tp));});
node->lch()->lch()->add("ld",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.pion_power_status.msg->ld));},[](){return (power_line_state_str(mj->in.pion_mku_vn.pion_power_status.msg->ld));});
node->lch()->lch()->add("cvs",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.pion_power_status.msg->cvs));},[](){return (power_line_state_str(mj->in.pion_mku_vn.pion_power_status.msg->cvs));});
node->lch()->lch()->add("gyro",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.pion_power_status.msg->gyro));},[](){return (power_line_state_str(mj->in.pion_mku_vn.pion_power_status.msg->gyro));});
node->lch()->lch()->add("line_5v",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.pion_power_status.msg->line_5v));},[](){return (power_line_state_str(mj->in.pion_mku_vn.pion_power_status.msg->line_5v));});
node->lch()->lch()->add("adcu_vn",[](){return QVariant((int32_t)(mj->in.pion_mku_vn.pion_power_status.msg->adcu_vn));},[](){return (power_line_state_str(mj->in.pion_mku_vn.pion_power_status.msg->adcu_vn));});
mj->in.pion_mku_vn.pion_power_status.upd_cb = [](){ pion_mku_vn_pion_power_status_ptr->upd(mj->in.pion_mku_vn.pion_power_status.ts_s, mj->in.pion_mku_vn.pion_power_status.ts_ns);};
return node;
};


TreeNode * create_pion_mku_gn_out_tree(mj_pion_mku_gn_t * mj_ptr)
{
static mj_pion_mku_gn_t * mj = mj_ptr;
TreeNode * node = new TreeNode("OUTPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
aim_ang_gn_sens_state_ptr = node->add("aim_ang_gn_sens_state",[](){return QVariant(mj->out.aim_ang_gn_sens_state.msg->hdr.cnt);});
aim_ang_gn_sens_state_ptr->tx_enable = &mj->out.aim_ang_gn_sens_state.tx_enable;

node->lch()->add("angle",[](){return QVariant(mj->out.aim_ang_gn_sens_state.msg->angle);})->setData =  [](QVariant data){ mj->out.aim_ang_gn_sens_state.msg->angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("status",[](){return QVariant((int32_t)(mj->out.aim_ang_gn_sens_state.msg->status));},[](){return (ang_sens_status_str(mj->out.aim_ang_gn_sens_state.msg->status));})->setData =  [](QVariant data){ mj->out.aim_ang_gn_sens_state.msg->status=(ang_sens_status)(data.value<int32_t>());return;};
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

cmd_ans_ptr = node->add("cmd_ans",[](){return QVariant(mj->out.cmd_ans.msg->hdr.cnt);});
cmd_ans_ptr->tx = [](uint16_t dst){mj->out.cmd_ans.tx(dst);};

node->lch()->add("command",[](){return QVariant((int32_t)(mj->out.cmd_ans.msg->command));},[](){return (command_type_str(mj->out.cmd_ans.msg->command));})->setData =  [](QVariant data){ mj->out.cmd_ans.msg->command=(command_type)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("SWRESET");
node->lch()->lch()->values.append("SAVEPRM");
node->lch()->lch()->values.append("SET_HOME_POSITION");
node->lch()->lch()->values.append("SET_UP_LIMIT");
node->lch()->lch()->values.append("SET_DOWN_LIMIT");
node->lch()->lch()->values.append("SET_LOAD_POSITION");
node->lch()->lch()->values.append("SET_ARM_POSITION");
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
node->lch()->lch()->intval.append(11);
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

ld_answer_ptr = node->add("ld_answer",[](){return QVariant(mj->out.ld_answer.msg->hdr.cnt);});
ld_answer_ptr->tx = [](uint16_t dst){mj->out.ld_answer.tx(dst);};

node->lch()->add("range_ans",[](){return QVariant(mj->out.ld_answer.msg->range_ans);})->setData =  [](QVariant data){ mj->out.ld_answer.msg->range_ans=data.value<float>();return;};
node->lch()->lch()->editable = true;

mku_tel_ptr = node->add("mku_tel",[](){return QVariant(mj->out.mku_tel.msg->hdr.cnt);});
mku_tel_ptr->tx_enable = &mj->out.mku_tel.tx_enable;

node->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.mku_tel.msg->mode));},[](){return (drv_ctrl_mode_str(mj->out.mku_tel.msg->mode));})->setData =  [](QVariant data){ mj->out.mku_tel.msg->mode=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FREEMOVE");
node->lch()->lch()->values.append("HOLD");
node->lch()->lch()->values.append("ANGLE");
node->lch()->lch()->values.append("SPEED");
node->lch()->lch()->values.append("RSPEED");
node->lch()->lch()->values.append("STAB");
node->lch()->lch()->values.append("AIM_TRACK");
node->lch()->lch()->values.append("TRG_TRACK");
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
node->lch()->lch()->intval.append(13);
node->lch()->lch()->intval.append(14);
node->lch()->lch()->intval.append(15);
node->lch()->add("error",[](){return QVariant((int32_t)(mj->out.mku_tel.msg->error));},[](){return (drv_ctrl_error_str(mj->out.mku_tel.msg->error));})->setData =  [](QVariant data){ mj->out.mku_tel.msg->error=(int8_t)(data.value<int32_t>());return;};
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
node->lch()->lch()->values.append("GYRO");
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
node->lch()->add("status",[](){return QVariant((int32_t)(mj->out.mku_tel.msg->status));},[](){return (dcu_status_str(mj->out.mku_tel.msg->status));})->setData =  [](QVariant data){ mj->out.mku_tel.msg->status=(int8_t)(data.value<int32_t>());return;};
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
node->lch()->add("limit",[](){return QVariant((int32_t)(mj->out.mku_tel.msg->limit));},[](){return (move_limit_state_str(mj->out.mku_tel.msg->limit));})->setData =  [](QVariant data){ mj->out.mku_tel.msg->limit=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("NONE");
node->lch()->lch()->values.append("LIMIT_UP");
node->lch()->lch()->values.append("LIMIT_DOWN");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->add("power_vdc",[](){return QVariant(mj->out.mku_tel.msg->power_vdc);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->power_vdc=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("current",[](){return QVariant();});
node->lch()->lch()->add("a",[](){return QVariant(mj->out.mku_tel.msg->current.a);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->current.a=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("b",[](){return QVariant(mj->out.mku_tel.msg->current.b);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->current.b=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("c",[](){return QVariant(mj->out.mku_tel.msg->current.c);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->current.c=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("pwm",[](){return QVariant();});
node->lch()->lch()->add("a",[](){return QVariant(mj->out.mku_tel.msg->pwm.a);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->pwm.a=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("b",[](){return QVariant(mj->out.mku_tel.msg->pwm.b);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->pwm.b=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("c",[](){return QVariant(mj->out.mku_tel.msg->pwm.c);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->pwm.c=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("park_current",[](){return QVariant();});
node->lch()->lch()->add("d",[](){return QVariant(mj->out.mku_tel.msg->park_current.d);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->park_current.d=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("q",[](){return QVariant(mj->out.mku_tel.msg->park_current.q);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->park_current.q=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("park_voltage",[](){return QVariant();});
node->lch()->lch()->add("d",[](){return QVariant(mj->out.mku_tel.msg->park_voltage.d);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->park_voltage.d=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("q",[](){return QVariant(mj->out.mku_tel.msg->park_voltage.q);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->park_voltage.q=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("gyro_angle",[](){return QVariant(mj->out.mku_tel.msg->gyro_angle);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->gyro_angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("gyro_speed",[](){return QVariant(mj->out.mku_tel.msg->gyro_speed);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->gyro_speed=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("temp",[](){return QVariant(mj->out.mku_tel.msg->temp);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->temp=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_sens_angle",[](){return QVariant(mj->out.mku_tel.msg->load_sens_angle);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->load_sens_angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_sens_speed",[](){return QVariant(mj->out.mku_tel.msg->load_sens_speed);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->load_sens_speed=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("load_sens_state",[](){return QVariant((int32_t)(mj->out.mku_tel.msg->load_sens_state));},[](){return (ang_sens_status_str(mj->out.mku_tel.msg->load_sens_state));})->setData =  [](QVariant data){ mj->out.mku_tel.msg->load_sens_state=(int8_t)(data.value<int32_t>());return;};
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
node->lch()->add("v1_2ok",[](){return QVariant(mj->out.mku_tel.msg->v1_2ok);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->v1_2ok=data.value<bool>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("v1_8ok",[](){return QVariant(mj->out.mku_tel.msg->v1_8ok);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->v1_8ok=data.value<bool>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("v2_5ok",[](){return QVariant(mj->out.mku_tel.msg->v2_5ok);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->v2_5ok=data.value<bool>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("v5ok",[](){return QVariant(mj->out.mku_tel.msg->v5ok);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->v5ok=data.value<bool>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("v12ok",[](){return QVariant(mj->out.mku_tel.msg->v12ok);})->setData =  [](QVariant data){ mj->out.mku_tel.msg->v12ok=data.value<bool>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("sync",[](){return QVariant((int32_t)(mj->out.mku_tel.msg->sync));},[](){return (relay_signal_state_str(mj->out.mku_tel.msg->sync));})->setData =  [](QVariant data){ mj->out.mku_tel.msg->sync=(int8_t)(data.value<int32_t>());return;};
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

n_tv_heater_state_ptr = node->add("n_tv_heater_state",[](){return QVariant(mj->out.n_tv_heater_state.msg->hdr.cnt);});
n_tv_heater_state_ptr->tx_enable = &mj->out.n_tv_heater_state.tx_enable;

node->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.n_tv_heater_state.msg->mode));},[](){return (heater_mode_str(mj->out.n_tv_heater_state.msg->mode));})->setData =  [](QVariant data){ mj->out.n_tv_heater_state.msg->mode=(heater_mode)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("AUTO");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->add("state",[](){return QVariant((int32_t)(mj->out.n_tv_heater_state.msg->state));},[](){return (heater_status_str(mj->out.n_tv_heater_state.msg->state));})->setData =  [](QVariant data){ mj->out.n_tv_heater_state.msg->state=(heater_status)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->add("temp",[](){return QVariant(mj->out.n_tv_heater_state.msg->temp);})->setData =  [](QVariant data){ mj->out.n_tv_heater_state.msg->temp=data.value<float>();return;};
node->lch()->lch()->editable = true;

pion_ctrl_ptr = node->add("pion_ctrl",[](){return QVariant(mj->out.pion_ctrl.msg->hdr.cnt);});
pion_ctrl_ptr->tx_enable = &mj->out.pion_ctrl.tx_enable;

node->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.pion_ctrl.msg->mode));},[](){return (aim_mode_str(mj->out.pion_ctrl.msg->mode));})->setData =  [](QVariant data){ mj->out.pion_ctrl.msg->mode=(aim_mode)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("INIT");
node->lch()->lch()->values.append("STANDBY");
node->lch()->lch()->values.append("MAIN");
node->lch()->lch()->values.append("TECH");
node->lch()->lch()->values.append("ADJUST");
node->lch()->lch()->values.append("FINISH");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(5);
node->lch()->lch()->intval.append(6);
node->lch()->lch()->intval.append(7);
node->lch()->add("code",[](){return QVariant(mj->out.pion_ctrl.msg->code);})->setData =  [](QVariant data){ mj->out.pion_ctrl.msg->code=data.value<int32_t>();return;};
node->lch()->lch()->editable = true;

pion_drv_gn_state_ptr = node->add("pion_drv_gn_state",[](){return QVariant(mj->out.pion_drv_gn_state.msg->hdr.cnt);});
pion_drv_gn_state_ptr->tx = [](uint16_t dst){mj->out.pion_drv_gn_state.tx(dst);};

node->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.pion_drv_gn_state.msg->mode));},[](){return (drv_ctrl_mode_str(mj->out.pion_drv_gn_state.msg->mode));})->setData =  [](QVariant data){ mj->out.pion_drv_gn_state.msg->mode=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FREEMOVE");
node->lch()->lch()->values.append("HOLD");
node->lch()->lch()->values.append("ANGLE");
node->lch()->lch()->values.append("SPEED");
node->lch()->lch()->values.append("RSPEED");
node->lch()->lch()->values.append("STAB");
node->lch()->lch()->values.append("AIM_TRACK");
node->lch()->lch()->values.append("TRG_TRACK");
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
node->lch()->lch()->intval.append(13);
node->lch()->lch()->intval.append(14);
node->lch()->lch()->intval.append(15);
node->lch()->add("error",[](){return QVariant((int32_t)(mj->out.pion_drv_gn_state.msg->error));},[](){return (drv_ctrl_error_str(mj->out.pion_drv_gn_state.msg->error));})->setData =  [](QVariant data){ mj->out.pion_drv_gn_state.msg->error=(int8_t)(data.value<int32_t>());return;};
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
node->lch()->lch()->values.append("GYRO");
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
node->lch()->add("status",[](){return QVariant((int32_t)(mj->out.pion_drv_gn_state.msg->status));},[](){return (dcu_status_str(mj->out.pion_drv_gn_state.msg->status));})->setData =  [](QVariant data){ mj->out.pion_drv_gn_state.msg->status=(int8_t)(data.value<int32_t>());return;};
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
node->lch()->add("limit",[](){return QVariant((int32_t)(mj->out.pion_drv_gn_state.msg->limit));},[](){return (move_limit_state_str(mj->out.pion_drv_gn_state.msg->limit));})->setData =  [](QVariant data){ mj->out.pion_drv_gn_state.msg->limit=(int8_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("NONE");
node->lch()->lch()->values.append("LIMIT_UP");
node->lch()->lch()->values.append("LIMIT_DOWN");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->add("angle",[](){return QVariant(mj->out.pion_drv_gn_state.msg->angle);})->setData =  [](QVariant data){ mj->out.pion_drv_gn_state.msg->angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("speed",[](){return QVariant(mj->out.pion_drv_gn_state.msg->speed);})->setData =  [](QVariant data){ mj->out.pion_drv_gn_state.msg->speed=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("g_angle",[](){return QVariant(mj->out.pion_drv_gn_state.msg->g_angle);})->setData =  [](QVariant data){ mj->out.pion_drv_gn_state.msg->g_angle=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("g_speed",[](){return QVariant(mj->out.pion_drv_gn_state.msg->g_speed);})->setData =  [](QVariant data){ mj->out.pion_drv_gn_state.msg->g_speed=data.value<float>();return;};
node->lch()->lch()->editable = true;

pion_heater_ctrl_ptr = node->add("pion_heater_ctrl",[](){return QVariant(mj->out.pion_heater_ctrl.msg->hdr.cnt);});
pion_heater_ctrl_ptr->tx = [](uint16_t dst){mj->out.pion_heater_ctrl.tx(dst);};

node->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.pion_heater_ctrl.msg->mode));},[](){return (heater_mode_str(mj->out.pion_heater_ctrl.msg->mode));})->setData =  [](QVariant data){ mj->out.pion_heater_ctrl.msg->mode=(heater_mode)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("AUTO");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->add("place",[](){return QVariant((int32_t)(mj->out.pion_heater_ctrl.msg->place));},[](){return (heater_place_str(mj->out.pion_heater_ctrl.msg->place));})->setData =  [](QVariant data){ mj->out.pion_heater_ctrl.msg->place=(heater_place)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOW");
node->lch()->lch()->values.append("NARROW_TV");
node->lch()->lch()->values.append("WIDE_TV");
node->lch()->lch()->values.append("TP");
node->lch()->lch()->values.append("LD");
node->lch()->lch()->values.append("ALL");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->lch()->intval.append(5);

pion_power_ctrl_ptr = node->add("pion_power_ctrl",[](){return QVariant(mj->out.pion_power_ctrl.msg->hdr.cnt);});
pion_power_ctrl_ptr->tx_enable = &mj->out.pion_power_ctrl.tx_enable;

node->lch()->add("cam_narrow_tv",[](){return QVariant((int32_t)(mj->out.pion_power_ctrl.msg->cam_narrow_tv));},[](){return (power_line_state_str(mj->out.pion_power_ctrl.msg->cam_narrow_tv));})->setData =  [](QVariant data){ mj->out.pion_power_ctrl.msg->cam_narrow_tv=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("cam_wide_tv",[](){return QVariant((int32_t)(mj->out.pion_power_ctrl.msg->cam_wide_tv));},[](){return (power_line_state_str(mj->out.pion_power_ctrl.msg->cam_wide_tv));})->setData =  [](QVariant data){ mj->out.pion_power_ctrl.msg->cam_wide_tv=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("cam_tp",[](){return QVariant((int32_t)(mj->out.pion_power_ctrl.msg->cam_tp));},[](){return (power_line_state_str(mj->out.pion_power_ctrl.msg->cam_tp));})->setData =  [](QVariant data){ mj->out.pion_power_ctrl.msg->cam_tp=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("ld",[](){return QVariant((int32_t)(mj->out.pion_power_ctrl.msg->ld));},[](){return (power_line_state_str(mj->out.pion_power_ctrl.msg->ld));})->setData =  [](QVariant data){ mj->out.pion_power_ctrl.msg->ld=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("cvs",[](){return QVariant((int32_t)(mj->out.pion_power_ctrl.msg->cvs));},[](){return (power_line_state_str(mj->out.pion_power_ctrl.msg->cvs));})->setData =  [](QVariant data){ mj->out.pion_power_ctrl.msg->cvs=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("gyro",[](){return QVariant((int32_t)(mj->out.pion_power_ctrl.msg->gyro));},[](){return (power_line_state_str(mj->out.pion_power_ctrl.msg->gyro));})->setData =  [](QVariant data){ mj->out.pion_power_ctrl.msg->gyro=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("line_5v",[](){return QVariant((int32_t)(mj->out.pion_power_ctrl.msg->line_5v));},[](){return (power_line_state_str(mj->out.pion_power_ctrl.msg->line_5v));})->setData =  [](QVariant data){ mj->out.pion_power_ctrl.msg->line_5v=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("adcu_vn",[](){return QVariant((int32_t)(mj->out.pion_power_ctrl.msg->adcu_vn));},[](){return (power_line_state_str(mj->out.pion_power_ctrl.msg->adcu_vn));})->setData =  [](QVariant data){ mj->out.pion_power_ctrl.msg->adcu_vn=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);

pion_power_status_ptr = node->add("pion_power_status",[](){return QVariant(mj->out.pion_power_status.msg->hdr.cnt);});
pion_power_status_ptr->tx_enable = &mj->out.pion_power_status.tx_enable;

node->lch()->add("cam_narrow_tv",[](){return QVariant((int32_t)(mj->out.pion_power_status.msg->cam_narrow_tv));},[](){return (power_line_state_str(mj->out.pion_power_status.msg->cam_narrow_tv));})->setData =  [](QVariant data){ mj->out.pion_power_status.msg->cam_narrow_tv=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("cam_wide_tv",[](){return QVariant((int32_t)(mj->out.pion_power_status.msg->cam_wide_tv));},[](){return (power_line_state_str(mj->out.pion_power_status.msg->cam_wide_tv));})->setData =  [](QVariant data){ mj->out.pion_power_status.msg->cam_wide_tv=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("cam_tp",[](){return QVariant((int32_t)(mj->out.pion_power_status.msg->cam_tp));},[](){return (power_line_state_str(mj->out.pion_power_status.msg->cam_tp));})->setData =  [](QVariant data){ mj->out.pion_power_status.msg->cam_tp=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("ld",[](){return QVariant((int32_t)(mj->out.pion_power_status.msg->ld));},[](){return (power_line_state_str(mj->out.pion_power_status.msg->ld));})->setData =  [](QVariant data){ mj->out.pion_power_status.msg->ld=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("cvs",[](){return QVariant((int32_t)(mj->out.pion_power_status.msg->cvs));},[](){return (power_line_state_str(mj->out.pion_power_status.msg->cvs));})->setData =  [](QVariant data){ mj->out.pion_power_status.msg->cvs=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("gyro",[](){return QVariant((int32_t)(mj->out.pion_power_status.msg->gyro));},[](){return (power_line_state_str(mj->out.pion_power_status.msg->gyro));})->setData =  [](QVariant data){ mj->out.pion_power_status.msg->gyro=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("line_5v",[](){return QVariant((int32_t)(mj->out.pion_power_status.msg->line_5v));},[](){return (power_line_state_str(mj->out.pion_power_status.msg->line_5v));})->setData =  [](QVariant data){ mj->out.pion_power_status.msg->line_5v=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);
node->lch()->add("adcu_vn",[](){return QVariant((int32_t)(mj->out.pion_power_status.msg->adcu_vn));},[](){return (power_line_state_str(mj->out.pion_power_status.msg->adcu_vn));})->setData =  [](QVariant data){ mj->out.pion_power_status.msg->adcu_vn=(power_line_state)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("UNKNOWN");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->values.append("UNUSE");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->lch()->intval.append(3);
node->lch()->lch()->intval.append(4);

prm_ans_ptr = node->add("prm_ans",[](){return QVariant(mj->out.prm_ans.msg->hdr.cnt);});
prm_ans_ptr->tx = [](uint16_t dst){mj->out.prm_ans.tx(dst);};

node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.prm_ans.msg->id));},[](){return (mj_get_prm_name(mj->out.prm_ans.msg->id));})->setData =  [](QVariant data){ mj->out.prm_ans.msg->id=(uint32_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("drv_parking_pos");
node->lch()->lch()->values.append("cfg_motor_type");
node->lch()->lch()->values.append("cfg_angle_sensor_type");
node->lch()->lch()->values.append("cfg_gyro_type");
node->lch()->lch()->values.append("cfg_rotor_sensor_type");
node->lch()->lch()->values.append("cfg_brake_type");
node->lch()->lch()->values.append("cfg_asrc_type");
node->lch()->lch()->values.append("cfg_temp_sensor_type");
node->lch()->lch()->values.append("cfg_cam_wide_tv_offset_x");
node->lch()->lch()->values.append("cfg_cam_wide_tv_offset_y");
node->lch()->lch()->values.append("cfg_cam_narrow_tv_offset_y");
node->lch()->lch()->values.append("cfg_cam_narrow_tv_offset_x");
node->lch()->lch()->values.append("cfg_cam_tp_offset_x");
node->lch()->lch()->values.append("cfg_cam_tp_offset_y");
node->lch()->lch()->values.append("cfg_cm_observe_offset_x");
node->lch()->lch()->values.append("cfg_cm_observe_offset_y");
node->lch()->lch()->values.append("cfg_cm_observeX2_offset_x");
node->lch()->lch()->values.append("cfg_cm_observeX2_offset_y");
node->lch()->lch()->values.append("cfg_cm_wide_offset_x");
node->lch()->lch()->values.append("cfg_cm_wide_offset_y");
node->lch()->lch()->values.append("cfg_cm_narrow_offset_x");
node->lch()->lch()->values.append("cfg_cm_narrow_offset_y");
node->lch()->lch()->values.append("cfg_cm_narrowX2_offset_x");
node->lch()->lch()->values.append("cfg_cm_narrowX2_offset_y");
node->lch()->lch()->values.append("test_mode");
node->lch()->lch()->values.append("factory_date");
node->lch()->lch()->values.append("factory_number");
node->lch()->lch()->values.append("description");
node->lch()->lch()->values.append("service_mode");
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->values.append("adc_shift");
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->values.append("manual_power_control");
node->lch()->lch()->values.append("ctrl_ang_pos_gain");
node->lch()->lch()->values.append("ctrl_ang_pos_pid_kp");
node->lch()->lch()->values.append("ctrl_ang_pos_pid_ktr");
node->lch()->lch()->values.append("ctrl_ang_damping");
node->lch()->lch()->values.append("ctrl_ang_damping_th");
node->lch()->lch()->values.append("ctrl_ang_speed_gain");
node->lch()->lch()->values.append("ctrl_ang_speed_pid_kp");
node->lch()->lch()->values.append("ctrl_ang_speed_pid_ki");
node->lch()->lch()->values.append("ctrl_ang_speed_pid_kb");
node->lch()->lch()->values.append("ctrl_ang_speed_pid_ktr");
node->lch()->lch()->values.append("ctrl_ang_speed_pid_int_lim");
node->lch()->lch()->values.append("ctrl_ang_speed_pid_out_lim");
node->lch()->lch()->values.append("ctrl_ang_current_gain");
node->lch()->lch()->values.append("ctrl_ang_curent_pid_kp");
node->lch()->lch()->values.append("ctrl_ang_curent_pid_ki");
node->lch()->lch()->values.append("ctrl_ang_curent_pid_kb");
node->lch()->lch()->values.append("ctrl_ang_curent_pid_int_lim");
node->lch()->lch()->values.append("ctrl_ang_curent_pid_out_lim");
node->lch()->lch()->values.append("ctrl_speed_pos_gain");
node->lch()->lch()->values.append("ctrl_speed_pos_pid_kp");
node->lch()->lch()->values.append("ctrl_speed_pos_pid_ktr");
node->lch()->lch()->values.append("ctrl_speed_speed_gain");
node->lch()->lch()->values.append("ctrl_speed_current_gain");
node->lch()->lch()->values.append("ctrl_speed_damping");
node->lch()->lch()->values.append("ctrl_speed_damping_th");
node->lch()->lch()->values.append("ctrl_speed_accel_lim");
node->lch()->lch()->values.append("ctrl_speed_flt");
node->lch()->lch()->values.append("ctrl_trk_pos_gain");
node->lch()->lch()->values.append("ctrl_trk_pos_pid_kp");
node->lch()->lch()->values.append("ctrl_trk_pos_pid_ki");
node->lch()->lch()->values.append("ctrl_trk_pos_pid_kb");
node->lch()->lch()->values.append("ctrl_trk_pos_pid_int_lim");
node->lch()->lch()->values.append("ctrl_trk_pos_pid_ktr");
node->lch()->lch()->values.append("ctrl_trk_damping");
node->lch()->lch()->values.append("ctrl_trk_damping_th");
node->lch()->lch()->values.append("ctrl_trk_speed_gain");
node->lch()->lch()->values.append("ctrl_trk_current_gain");
node->lch()->lch()->values.append("ctrl_trk_speed_lim");
node->lch()->lch()->values.append("ctrl_trk_err_is_spherical");
node->lch()->lch()->values.append("ctrl_trk_tv_delay");
node->lch()->lch()->values.append("ctrl_trk_tp_delay");
node->lch()->lch()->values.append("ctrl_trk_lim_th");
node->lch()->lch()->values.append("ctrl_use_cart_trj");
node->lch()->lch()->values.append("ctrl_use_pid");
node->lch()->lch()->values.append("ctrl_load_obs_gain");
node->lch()->lch()->values.append("ctrl_fire_pos_gain");
node->lch()->lch()->values.append("ctrl_fire_speed_gain");
node->lch()->lch()->values.append("ctrl_fire_current_gain");
node->lch()->lch()->values.append("ctrl_fire_obs_gain");
node->lch()->lch()->values.append("ctrl_force_delay");
node->lch()->lch()->values.append("ctrl_torque_obs_gain");
node->lch()->lch()->values.append("ctrl_ref_obs_gain");
node->lch()->lch()->values.append("ctrl_curent_max");
node->lch()->lch()->values.append("ctrl_v_max");
node->lch()->lch()->values.append("ctrl_ss_err_th");
node->lch()->lch()->values.append("ctrl_ss_spd_th");
node->lch()->lch()->values.append("ctrl_ss_flt");
node->lch()->lch()->values.append("ctrl_ss_lead_delay_ms");
node->lch()->lch()->values.append("ctrl_bp_flt_gain");
node->lch()->lch()->values.append("ctrl_trg_meas_sigma");
node->lch()->lch()->values.append("ctrl_trg_process_sigma");
node->lch()->lch()->values.append("ctrl_trg_px0");
node->lch()->lch()->values.append("ctrl_trg_pv0");
node->lch()->lch()->values.append("ctrl_trg_pa0");
node->lch()->lch()->values.append("ctrl_cvs_gyro_cs");
node->lch()->lch()->values.append("ctrl_gyro_cs");
node->lch()->lch()->values.append("ctrl_local_spd_flt");
node->lch()->lch()->values.append("ctrl_curent_lp");
node->lch()->lch()->values.append("ctrl_curent_notch_lp");
node->lch()->lch()->values.append("ctrl_curent_notch_hp");
node->lch()->lch()->values.append("ctrl_speed_lp");
node->lch()->lch()->values.append("ctrl_speed_notch_lp");
node->lch()->lch()->values.append("ctrl_speed_notch_hp");
node->lch()->lch()->values.append("ctrl_syncro");
node->lch()->lch()->values.append("ctrl_syncro_point");
node->lch()->lch()->values.append("ctrl_limit_th");
node->lch()->lch()->values.append("ctrl_limit_th_speed");
node->lch()->lch()->values.append("ctrl_limit_enable");
node->lch()->lch()->values.append("fire_full_voltage");
node->lch()->lch()->values.append("fire_hold_voltage");
node->lch()->lch()->values.append("fire_full_time");
node->lch()->lch()->values.append("fire_full_time_a");
node->lch()->lch()->values.append("fire_full_time_b");
node->lch()->lch()->values.append("fire_down_time");
node->lch()->lch()->values.append("fire_max_time");
node->lch()->lch()->values.append("fire_delay");
node->lch()->lch()->values.append("fire_delay_a");
node->lch()->lch()->values.append("fire_delay_b");
node->lch()->lch()->values.append("trig_current_ftl");
node->lch()->lch()->values.append("trig_full_current");
node->lch()->lch()->values.append("trig_hold_current");
node->lch()->lch()->values.append("trig_K");
node->lch()->lch()->values.append("trig_I");
node->lch()->lch()->values.append("trig_max_voltage");
node->lch()->lch()->values.append("trig_demag_lvl");
node->lch()->lch()->values.append("fire_repeat_temp1");
node->lch()->lch()->values.append("fire_repeat_temp2");
node->lch()->lch()->values.append("fire_repeat_temp3");
node->lch()->lch()->values.append("fire_single_time");
node->lch()->lch()->values.append("fire_short_time");
node->lch()->lch()->values.append("fire_long_time");
node->lch()->lch()->values.append("fire_mode");
node->lch()->lch()->values.append("gyro_offset");
node->lch()->lch()->values.append("gyro_aim_offset");
node->lch()->lch()->values.append("gyro_offsetX");
node->lch()->lch()->values.append("gyro_offsetY");
node->lch()->lch()->values.append("gyro_offsetZ");
node->lch()->lch()->values.append("accel_offsetX");
node->lch()->lch()->values.append("accel_offsetY");
node->lch()->lch()->values.append("accel_offsetZ");
node->lch()->lch()->values.append("gyro_scale");
node->lch()->lch()->values.append("gyro_filt");
node->lch()->lch()->values.append("gyro_alpha");
node->lch()->lch()->values.append("gyro_beta");
node->lch()->lch()->values.append("gyro_gamma");
node->lch()->lch()->values.append("gyro_mode");
node->lch()->lch()->values.append("gyro_comp_gain");
node->lch()->lch()->values.append("gyro_comp_lim");
node->lch()->lch()->values.append("gyro_comp_db");
node->lch()->lch()->values.append("gyro_cross_coef");
node->lch()->lch()->values.append("gyro_cross_angle");
node->lch()->lch()->values.append("gyro_aim_cross_coef");
node->lch()->lch()->values.append("gyro_aim_cross_angle");
node->lch()->lch()->values.append("ocp_react_time");
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->values.append("ocp_cooldown_time");
node->lch()->lch()->values.append("sens_cur_a_fine_offset");
node->lch()->lch()->values.append("sens_cur_b_fine_offset");
node->lch()->lch()->values.append("sens_cur_c_fine_offset");
node->lch()->lch()->values.append("sens_cur_a_coarse_offset");
node->lch()->lch()->values.append("sens_cur_b_coarse_offset");
node->lch()->lch()->values.append("sens_cur_c_coarse_offset");
node->lch()->lch()->values.append("sens_cur_calibrated");
node->lch()->lch()->values.append("drv_limit_up");
node->lch()->lch()->values.append("drv_limit_down");
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->values.append("drv_gbx_ration");
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->values.append("ld_enable");
node->lch()->lch()->values.append("brk_release_voltage");
node->lch()->lch()->values.append("brk_hold_voltage");
node->lch()->lch()->values.append("brk_release_time");
node->lch()->lch()->values.append("drv_rotor_reverse");
node->lch()->lch()->values.append("drv_gyro_reverse");
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->values.append("drv_aim_gyro_reverse");
node->lch()->lch()->values.append("load_inertia");
node->lch()->lch()->values.append("load_friction_coeff");
node->lch()->lch()->values.append("load_max_speed");
node->lch()->lch()->values.append("motor_armature_resistance");
node->lch()->lch()->values.append("motor_armature_inductance");
node->lch()->lch()->values.append("motor_bemf");
node->lch()->lch()->values.append("motor_moment_constant");
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->values.append("estimator_type");
node->lch()->lch()->values.append("kalman_q_angle");
node->lch()->lch()->values.append("kalman_q_velocity");
node->lch()->lch()->values.append("kalman_q_current");
node->lch()->lch()->values.append("kalman_q_tl");
node->lch()->lch()->values.append("kalman_q_vd");
node->lch()->lch()->values.append("kalman_r_angle");
node->lch()->lch()->values.append("kalman_r_velocity");
node->lch()->lch()->values.append("kalman_r_current");
node->lch()->lch()->values.append("height_pix_tp");
node->lch()->lch()->values.append("height_pix_tvsh");
node->lch()->lch()->values.append("height_pix_tvu");
node->lch()->lch()->values.append("height_rad_tp");
node->lch()->lch()->values.append("height_rad_tvsh");
node->lch()->lch()->values.append("height_rad_tvu");
node->lch()->lch()->values.append("width_pix_tp");
node->lch()->lch()->values.append("width_pix_tvsh");
node->lch()->lch()->values.append("width_pix_tvu");
node->lch()->lch()->values.append("width_rad_tp");
node->lch()->lch()->values.append("width_rad_tvsh");
node->lch()->lch()->values.append("width_rad_tvu");
node->lch()->lch()->values.append("radius_ld");
node->lch()->lch()->values.append("pix_width_ld");
node->lch()->lch()->values.append("pix_height_ld");
node->lch()->lch()->values.append("cvs_delay");
node->lch()->lch()->values.append("x_oeb");
node->lch()->lch()->values.append("y_oeb");
node->lch()->lch()->values.append("z_oeb");
node->lch()->lch()->values.append("oeb_trans_shift");
node->lch()->lch()->values.append("zu_x");
node->lch()->lch()->values.append("zu_y");
node->lch()->lch()->values.append("zu_z");
node->lch()->lch()->values.append("lead_gn");
node->lch()->lch()->values.append("lead_vn");
node->lch()->lch()->values.append("lead_static");
node->lch()->lch()->values.append("dcu_angles_flag");
node->lch()->lch()->values.append("oeb_divergence_flag");
node->lch()->lch()->values.append("guns_deflection_flag");
node->lch()->lch()->values.append("muzzle_dispersion_flag");
node->lch()->lch()->values.append("muzzle_bracking_flag");
node->lch()->lch()->values.append("used_pipe1");
node->lch()->lch()->values.append("used_pipe2");
node->lch()->lch()->values.append("used_pipe3");
node->lch()->lch()->values.append("used_pipe4");
node->lch()->lch()->values.append("recoil_active_pipe1");
node->lch()->lch()->values.append("recoil_active_pipe2");
node->lch()->lch()->values.append("recoil_active_pipe3");
node->lch()->lch()->values.append("recoil_active_pipe4");
node->lch()->lch()->values.append("all_recoil_enable");
node->lch()->lch()->values.append("bullet_type");
node->lch()->lch()->values.append("fire_interval");
node->lch()->lch()->values.append("inert_mode_flag");
node->lch()->lch()->values.append("approx_error_threshold");
node->lch()->lch()->values.append("ld_delay_mode");
node->lch()->lch()->values.append("approx_type");
node->lch()->lch()->values.append("torque_platform_on");
node->lch()->lch()->values.append("torque_platform_gain");
node->lch()->lch()->values.append("angle_gn_std");
node->lch()->lch()->values.append("angle_vn_std");
node->lch()->lch()->values.append("range_std");
node->lch()->lch()->values.append("init_pos_std");
node->lch()->lch()->values.append("init_vel_std");
node->lch()->lch()->values.append("init_acc_std");
node->lch()->lch()->values.append("geometry_threshold");
node->lch()->lch()->values.append("geometry_factor");
node->lch()->lch()->values.append("vel_min");
node->lch()->lch()->values.append("vel_max");
node->lch()->lch()->values.append("accel_direct_std");
node->lch()->lch()->values.append("accel_min_turn_std");
node->lch()->lch()->values.append("accel_max_turn_std");
node->lch()->lch()->values.append("nis_threshold");
node->lch()->lch()->values.append("nis_gain");
node->lch()->lch()->values.append("maneuver_timescale_min");
node->lch()->lch()->values.append("maneuver_timescale_max");
node->lch()->lch()->values.append("singer_min_std");
node->lch()->lch()->values.append("singer_max_std");
node->lch()->lch()->values.append("shield_mode");
node->lch()->lch()->values.append("shield_width");
node->lch()->lch()->values.append("shield_height");
node->lch()->lch()->values.append("flight_altitude");
node->lch()->lch()->values.append("forecast_distance");
node->lch()->lch()->values.append("proportional_сoefficient");
node->lch()->lch()->values.append("waypoints");
node->lch()->lch()->values.append("trajectory_type");
node->lch()->lch()->values.append("turning_radius");
node->lch()->lch()->values.append("velocity");
node->lch()->lch()->values.append("stl_scale");
node->lch()->lch()->values.append("fire_t_full_auto_ms");
node->lch()->lch()->values.append("fire_t_full_long_ms");
node->lch()->lch()->values.append("fire_t_full_short_ms");
node->lch()->lch()->values.append("fire_t_fall_ms");
node->lch()->lch()->values.append("fire_t_cooldown_ms");
node->lch()->lch()->values.append("fire_t_max_ms");
node->lch()->lch()->values.append("fire_temp1_interval_ms");
node->lch()->lch()->values.append("fire_temp2_interval_ms");
node->lch()->lch()->values.append("fire_voltage_max");
node->lch()->lch()->values.append("fire_voltage_hold");
node->lch()->lch()->values.append("fire_voltage_base");
node->lch()->lch()->values.append("cvs_trj_forecast_time");
node->lch()->lch()->values.append("vg901_resolution");
node->lch()->lch()->values.append("vg901_offset");
node->lch()->lch()->values.append("vg901_coefficient");
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->values.append("pwm_max");
node->lch()->lch()->values.append("com_if_bup_ctrl_mcast");
node->lch()->lch()->values.append("com_if_bup_data_mcast");
node->lch()->lch()->values.append("com_if_pion_ctrl_mcast");
node->lch()->lch()->values.append("com_if_pion_data_mcast");
node->lch()->lch()->values.append("com_if_pion_state_mcast");
node->lch()->lch()->values.append("com_if_wp_sens_mcast");
node->lch()->lch()->values.append("com_if_ld_ctrl_mcast");
node->lch()->lch()->values.append("com_if_ld_data_mcast");
node->lch()->lch()->values.append("com_if_pion_sens_mcast");
node->lch()->lch()->values.append("com_if_target_track_mcast");
node->lch()->lch()->values.append("com_if_tcu_data_mcast");
node->lch()->lch()->values.append("com_if_dcu_vn_data_mcast");
node->lch()->lch()->values.append("com_if_dcu_gn_data_mcast");
node->lch()->lch()->values.append("com_if_ifu_data_mcast");
node->lch()->lch()->values.append("com_if_pcm_data_mcast");
node->lch()->lch()->values.append("com_if_pion_drv_ctrl_mcast");
node->lch()->lch()->values.append("com_if_pion_heater_ctrl_mcast");
node->lch()->lch()->values.append("com_if_pion_power_ctrl_mcast");
node->lch()->lch()->values.append("com_if_pion_heater_data_mcast");
node->lch()->lch()->values.append("com_if_pion_power_data_mcast");
node->lch()->lch()->values.append("com_if_bup_srv_mcast");
node->lch()->lch()->values.append("com_if_pion_srv_mcast");
node->lch()->lch()->values.append("com_if_srv_mcast");
node->lch()->lch()->values.append("com_if_im_zu_data_mcast");
node->lch()->lch()->values.append("com_if_im_zu_state_mcast");
node->lch()->lch()->values.append("com_if_im_drive_ctrl_mcast");
node->lch()->lch()->values.append("com_if_im_drive_mcast");
node->lch()->lch()->values.append("com_if_im_cvs_mcast");
node->lch()->lch()->values.append("com_if_im_target_mcast");
node->lch()->lch()->values.append("com_if_im_trig_mcast");
node->lch()->lch()->values.append("dev_id");
node->lch()->lch()->intval.append(0x1EE5D873);
node->lch()->lch()->intval.append(0xB84A2AAE);
node->lch()->lch()->intval.append(0x5EB1D6A2);
node->lch()->lch()->intval.append(0x191EC7B1);
node->lch()->lch()->intval.append(0xC6AA70E);
node->lch()->lch()->intval.append(0x59F62361);
node->lch()->lch()->intval.append(0x70AD98CA);
node->lch()->lch()->intval.append(0x22CDAD7A);
node->lch()->lch()->intval.append(0x372CD6A3);
node->lch()->lch()->intval.append(0x724B2E63);
node->lch()->lch()->intval.append(0xB06B673E);
node->lch()->lch()->intval.append(0xF50C9FFE);
node->lch()->lch()->intval.append(0x424C6256);
node->lch()->lch()->intval.append(0x72B9A96);
node->lch()->lch()->intval.append(0x552DD596);
node->lch()->lch()->intval.append(0x104A2D56);
node->lch()->lch()->intval.append(0x4A3FF3D3);
node->lch()->lch()->intval.append(0xF580B13);
node->lch()->lch()->intval.append(0xD36BB580);
node->lch()->lch()->intval.append(0x960C4D40);
node->lch()->lch()->intval.append(0xAECF9AA9);
node->lch()->lch()->intval.append(0xEBA86269);
node->lch()->lch()->intval.append(0x7E4D151D);
node->lch()->lch()->intval.append(0x3B2AEDDD);
node->lch()->lch()->intval.append(0xDE1AF569);
node->lch()->lch()->intval.append(0xA92645D2);
node->lch()->lch()->intval.append(0xC8EE09D4);
node->lch()->lch()->intval.append(0x4D7787A8);
node->lch()->lch()->intval.append(0x311FD2BA);
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->intval.append(0x2371F357);
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->intval.append(0x1FC0BE48);
node->lch()->lch()->intval.append(0xC808D4F3);
node->lch()->lch()->intval.append(0x32EFE130);
node->lch()->lch()->intval.append(0x3738409D);
node->lch()->lch()->intval.append(0xD93B241B);
node->lch()->lch()->intval.append(0x7D6BFDE6);
node->lch()->lch()->intval.append(0x69D41D8C);
node->lch()->lch()->intval.append(0xAFDFC864);
node->lch()->lch()->intval.append(0x8B492A4C);
node->lch()->lch()->intval.append(0x1DE56A30);
node->lch()->lch()->intval.append(0x75A8CBE);
node->lch()->lch()->intval.append(0xB2C8E5CC);
node->lch()->lch()->intval.append(0x97061769);
node->lch()->lch()->intval.append(0xF5B606B6);
node->lch()->lch()->intval.append(0x6CCAF151);
node->lch()->lch()->intval.append(0x485C1379);
node->lch()->lch()->intval.append(0xDEF05305);
node->lch()->lch()->intval.append(0x5F51997A);
node->lch()->lch()->intval.append(0x7A9F6BDF);
node->lch()->lch()->intval.append(0xFD1C2D54);
node->lch()->lch()->intval.append(0xD02A8F9C);
node->lch()->lch()->intval.append(0xF221BB53);
node->lch()->lch()->intval.append(0x8B117320);
node->lch()->lch()->intval.append(0xEC285B9D);
node->lch()->lch()->intval.append(0x680E6C7F);
node->lch()->lch()->intval.append(0x9FAE934A);
node->lch()->lch()->intval.append(0x94409FDF);
node->lch()->lch()->intval.append(0x8F52D59D);
node->lch()->lch()->intval.append(0x5367BD80);
node->lch()->lch()->intval.append(0x130904AD);
node->lch()->lch()->intval.append(0x379FE685);
node->lch()->lch()->intval.append(0xA133A6F9);
node->lch()->lch()->intval.append(0xEFE1A46);
node->lch()->lch()->intval.append(0xD1CC20CA);
node->lch()->lch()->intval.append(0x34A03BCA);
node->lch()->lch()->intval.append(0x5C8D187B);
node->lch()->lch()->intval.append(0x4832F811);
node->lch()->lch()->intval.append(0x1A328A4);
node->lch()->lch()->intval.append(0xE5FC7D1D);
node->lch()->lch()->intval.append(0x2CDADFF6);
node->lch()->lch()->intval.append(0x5DC2B375);
node->lch()->lch()->intval.append(0x3616DF10);
node->lch()->lch()->intval.append(0x38C06AE5);
node->lch()->lch()->intval.append(0x8EA754D7);
node->lch()->lch()->intval.append(0xC434A0D3);
node->lch()->lch()->intval.append(0xEA2EAEC7);
node->lch()->lch()->intval.append(0xC7B887BF);
node->lch()->lch()->intval.append(0x3D2BB69C);
node->lch()->lch()->intval.append(0x76A77EDB);
node->lch()->lch()->intval.append(0x5F9E600A);
node->lch()->lch()->intval.append(0x8BE30201);
node->lch()->lch()->intval.append(0xD94F2803);
node->lch()->lch()->intval.append(0x6777563E);
node->lch()->lch()->intval.append(0xB6FD8005);
node->lch()->lch()->intval.append(0xA83AFFF1);
node->lch()->lch()->intval.append(0x541D492A);
node->lch()->lch()->intval.append(0xD4CDEB67);
node->lch()->lch()->intval.append(0x8F486F03);
node->lch()->lch()->intval.append(0x4B6F9372);
node->lch()->lch()->intval.append(0x713A2226);
node->lch()->lch()->intval.append(0x9BD7FE96);
node->lch()->lch()->intval.append(0x177E5548);
node->lch()->lch()->intval.append(0xD5F6F1E5);
node->lch()->lch()->intval.append(0xBBE09029);
node->lch()->lch()->intval.append(0xF16013CD);
node->lch()->lch()->intval.append(0x328D84D4);
node->lch()->lch()->intval.append(0x9B7D8EC);
node->lch()->lch()->intval.append(0x2C0A778F);
node->lch()->lch()->intval.append(0x7DCAC375);
node->lch()->lch()->intval.append(0xC080A0D3);
node->lch()->lch()->intval.append(0x5FE209C8);
node->lch()->lch()->intval.append(0x5E9A3A63);
node->lch()->lch()->intval.append(0xD566A4C5);
node->lch()->lch()->intval.append(0x4A040DDE);
node->lch()->lch()->intval.append(0xFF16CE21);
node->lch()->lch()->intval.append(0x5AD712BA);
node->lch()->lch()->intval.append(0xFE4EAF05);
node->lch()->lch()->intval.append(0x10FA6DB4);
node->lch()->lch()->intval.append(0x8D919959);
node->lch()->lch()->intval.append(0x64ADD15C);
node->lch()->lch()->intval.append(0xCAC729F0);
node->lch()->lch()->intval.append(0x6042DEB7);
node->lch()->lch()->intval.append(0x2C0615FB);
node->lch()->lch()->intval.append(0xE3AE1CBB);
node->lch()->lch()->intval.append(0x4F11C4CC);
node->lch()->lch()->intval.append(0xB9BB8B0D);
node->lch()->lch()->intval.append(0xF6BC1251);
node->lch()->lch()->intval.append(0xAEC0C821);
node->lch()->lch()->intval.append(0x6168C161);
node->lch()->lch()->intval.append(0x3B82EC9B);
node->lch()->lch()->intval.append(0xDBD19E97);
node->lch()->lch()->intval.append(0x70822561);
node->lch()->lch()->intval.append(0xDC1E42F7);
node->lch()->lch()->intval.append(0x13AF53A1);
node->lch()->lch()->intval.append(0x7D45C918);
node->lch()->lch()->intval.append(0x129B961F);
node->lch()->lch()->intval.append(0x4A12BD87);
node->lch()->lch()->intval.append(0x85BAB4C7);
node->lch()->lch()->intval.append(0xC0DD4C07);
node->lch()->lch()->intval.append(0xDD7FCAC);
node->lch()->lch()->intval.append(0x7853C445);
node->lch()->lch()->intval.append(0x9330952A);
node->lch()->lch()->intval.append(0x81CE8659);
node->lch()->lch()->intval.append(0x327A9E98);
node->lch()->lch()->intval.append(0x3999AD5F);
node->lch()->lch()->intval.append(0x4E25F56E);
node->lch()->lch()->intval.append(0xE394CBC1);
node->lch()->lch()->intval.append(0x15470387);
node->lch()->lch()->intval.append(0x373947FE);
node->lch()->lch()->intval.append(0x9A887951);
node->lch()->lch()->intval.append(0x6C5BB117);
node->lch()->lch()->intval.append(0xFBDE3B20);
node->lch()->lch()->intval.append(0x4947081B);
node->lch()->lch()->intval.append(0x1F5986CD);
node->lch()->lch()->intval.append(0xB0138FA5);
node->lch()->lch()->intval.append(0x69C4EFD3);
node->lch()->lch()->intval.append(0x6594610D);
node->lch()->lch()->intval.append(0xCAD0F98B);
node->lch()->lch()->intval.append(0xDB7E81B5);
node->lch()->lch()->intval.append(0x617E69D9);
node->lch()->lch()->intval.append(0xE16FCC9B);
node->lch()->lch()->intval.append(0x28B21F5C);
node->lch()->lch()->intval.append(0x46D9457C);
node->lch()->lch()->intval.append(0x9E6CE739);
node->lch()->lch()->intval.append(0xD02A15D0);
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->intval.append(0xD0AC7199);
node->lch()->lch()->intval.append(0xBF4A83EC);
node->lch()->lch()->intval.append(0xD9A71003);
node->lch()->lch()->intval.append(0x403E7CB);
node->lch()->lch()->intval.append(0x284A2867);
node->lch()->lch()->intval.append(0x8B770214);
node->lch()->lch()->intval.append(0x159C62A8);
node->lch()->lch()->intval.append(0x1D19E932);
node->lch()->lch()->intval.append(0x5C57D2B7);
node->lch()->lch()->intval.append(0x501D05A4);
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->intval.append(0xBBD3E88F);
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->intval.append(0xD543F9FE);
node->lch()->lch()->intval.append(0x2CF660C2);
node->lch()->lch()->intval.append(0xC4CA33B0);
node->lch()->lch()->intval.append(0xF449C211);
node->lch()->lch()->intval.append(0x38430DA2);
node->lch()->lch()->intval.append(0x491BE8E9);
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->intval.append(0x9D6ACA45);
node->lch()->lch()->intval.append(0x161CBA22);
node->lch()->lch()->intval.append(0xD443BE16);
node->lch()->lch()->intval.append(0x35045471);
node->lch()->lch()->intval.append(0x507A3C3C);
node->lch()->lch()->intval.append(0xDA0658A);
node->lch()->lch()->intval.append(0xC7865F20);
node->lch()->lch()->intval.append(0x5A8BE1ED);
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->intval.append(0xC2BB8B97);
node->lch()->lch()->intval.append(0x4586160E);
node->lch()->lch()->intval.append(0x4C62D80B);
node->lch()->lch()->intval.append(0x82675000);
node->lch()->lch()->intval.append(0xA8331120);
node->lch()->lch()->intval.append(0x9C7C61E3);
node->lch()->lch()->intval.append(0x236B85E1);
node->lch()->lch()->intval.append(0xEC7DAD1B);
node->lch()->lch()->intval.append(0xE48AC3EF);
node->lch()->lch()->intval.append(0x19FA383F);
node->lch()->lch()->intval.append(0xF6087766);
node->lch()->lch()->intval.append(0x2DB93F34);
node->lch()->lch()->intval.append(0x591F83F3);
node->lch()->lch()->intval.append(0x8B93B334);
node->lch()->lch()->intval.append(0x9610F8C5);
node->lch()->lch()->intval.append(0x1012BC5C);
node->lch()->lch()->intval.append(0x76CF657E);
node->lch()->lch()->intval.append(0xC5398A3B);
node->lch()->lch()->intval.append(0x41647D9);
node->lch()->lch()->intval.append(0x6313063B);
node->lch()->lch()->intval.append(0x9FF87CA6);
node->lch()->lch()->intval.append(0xEDECAE82);
node->lch()->lch()->intval.append(0xED7C0BE8);
node->lch()->lch()->intval.append(0x5CCB6F4A);
node->lch()->lch()->intval.append(0xF4670D59);
node->lch()->lch()->intval.append(0xA82F7F43);
node->lch()->lch()->intval.append(0x194385F0);
node->lch()->lch()->intval.append(0xCAF60192);
node->lch()->lch()->intval.append(0x4343E577);
node->lch()->lch()->intval.append(0x3080C855);
node->lch()->lch()->intval.append(0xE8384A70);
node->lch()->lch()->intval.append(0x81F147A8);
node->lch()->lch()->intval.append(0x2C377F17);
node->lch()->lch()->intval.append(0x8AF08272);
node->lch()->lch()->intval.append(0x8D5727F8);
node->lch()->lch()->intval.append(0xE95FB2D8);
node->lch()->lch()->intval.append(0xCFEF85CF);
node->lch()->lch()->intval.append(0x253A968F);
node->lch()->lch()->intval.append(0x2513CD21);
node->lch()->lch()->intval.append(0x715DBFFD);
node->lch()->lch()->intval.append(0xDDAB77E0);
node->lch()->lch()->intval.append(0x12037EA0);
node->lch()->lch()->intval.append(0x57648660);
node->lch()->lch()->intval.append(0x8D53E797);
node->lch()->lch()->intval.append(0x579374D5);
node->lch()->lch()->intval.append(0x983B7D95);
node->lch()->lch()->intval.append(0xDD5C8555);
node->lch()->lch()->intval.append(0x76BE4A2);
node->lch()->lch()->intval.append(0x171202ED);
node->lch()->lch()->intval.append(0xD02F610F);
node->lch()->lch()->intval.append(0x64BC560E);
node->lch()->lch()->intval.append(0x2FDFD0F1);
node->lch()->lch()->intval.append(0x5EA26FE2);
node->lch()->lch()->intval.append(0x4406A555);
node->lch()->lch()->intval.append(0x394E7C5C);
node->lch()->lch()->intval.append(0xE6557BB2);
node->lch()->lch()->intval.append(0x8EABF9AC);
node->lch()->lch()->intval.append(0x2D08847A);
node->lch()->lch()->intval.append(0xEAA275A8);
node->lch()->lch()->intval.append(0xEBA6B47);
node->lch()->lch()->intval.append(0x5041D4FA);
node->lch()->lch()->intval.append(0x994D9878);
node->lch()->lch()->intval.append(0x248659F);
node->lch()->lch()->intval.append(0x4B62DD3C);
node->lch()->lch()->intval.append(0x83E3E832);
node->lch()->lch()->intval.append(0x54705DB8);
node->lch()->lch()->intval.append(0x5F2CAF5);
node->lch()->lch()->intval.append(0x6A4D4E0F);
node->lch()->lch()->intval.append(0x55589777);
node->lch()->lch()->intval.append(0xCB51AC10);
node->lch()->lch()->intval.append(0xE961B362);
node->lch()->lch()->intval.append(0xF9668FCB);
node->lch()->lch()->intval.append(0x9036E515);
node->lch()->lch()->intval.append(0x78A9C6C0);
node->lch()->lch()->intval.append(0x25C5CC22);
node->lch()->lch()->intval.append(0x8F7E8D1);
node->lch()->lch()->intval.append(0x14316E6E);
node->lch()->lch()->intval.append(0xCD982C6C);
node->lch()->lch()->intval.append(0x8761BC9D);
node->lch()->lch()->intval.append(0x41378FDB);
node->lch()->lch()->intval.append(0x591CDF49);
node->lch()->lch()->intval.append(0xDBAC2D6A);
node->lch()->lch()->intval.append(0x9F70AD00);
node->lch()->lch()->intval.append(0x5C825B85);
node->lch()->lch()->intval.append(0x2D734DD3);
node->lch()->lch()->intval.append(0xE7D0A39B);
node->lch()->lch()->intval.append(0x87EE734B);
node->lch()->lch()->intval.append(0x9080AC90);
node->lch()->lch()->intval.append(0x416429AD);
node->lch()->lch()->intval.append(0x7BD0A249);
node->lch()->lch()->intval.append(0xA059930B);
node->lch()->lch()->intval.append(0x54C8A1CA);
node->lch()->lch()->intval.append(0x9854F45F);
node->lch()->lch()->intval.append(0xA0EDED65);
node->lch()->lch()->intval.append(0x4D4EA0F7);
node->lch()->lch()->intval.append(0x9C6B2E94);
node->lch()->lch()->intval.append(0x5A671E3B);
node->lch()->lch()->intval.append(0xA7F68FC0);
node->lch()->lch()->intval.append(0x8536FFBB);
node->lch()->lch()->intval.append(0x6ABA5290);
node->lch()->lch()->intval.append(0xD02F5519);
node->lch()->lch()->intval.append(0xFB7DDC79);
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->intval.append(0x925B41AA);
node->lch()->lch()->intval.append(0x46293BCC);
node->lch()->lch()->intval.append(0xF88316A1);
node->lch()->lch()->intval.append(0x4A709CD8);
node->lch()->lch()->intval.append(0xA9E451E8);
node->lch()->lch()->intval.append(0x1B17DB91);
node->lch()->lch()->intval.append(0xBDFA8C51);
node->lch()->lch()->intval.append(0x7BA2FE2C);
node->lch()->lch()->intval.append(0x51771EC9);
node->lch()->lch()->intval.append(0xE38494B0);
node->lch()->lch()->intval.append(0xC0AA259A);
node->lch()->lch()->intval.append(0x87A52B5F);
node->lch()->lch()->intval.append(0x3568B4DA);
node->lch()->lch()->intval.append(0xBE85653F);
node->lch()->lch()->intval.append(0xE703366F);
node->lch()->lch()->intval.append(0x9E21915);
node->lch()->lch()->intval.append(0x87AEAD2D);
node->lch()->lch()->intval.append(0xBBEFE16E);
node->lch()->lch()->intval.append(0x95EE7424);
node->lch()->lch()->intval.append(0xB9DD1547);
node->lch()->lch()->intval.append(0x271DFE5D);
node->lch()->lch()->intval.append(0xB2E9F3E);
node->lch()->lch()->intval.append(0x6857720E);
node->lch()->lch()->intval.append(0x5B060D18);
node->lch()->lch()->intval.append(0xEA688EF1);
node->lch()->lch()->intval.append(0xE1990506);
node->lch()->lch()->intval.append(0x335FAA57);
node->lch()->lch()->intval.append(0x3998C1DF);
node->lch()->lch()->intval.append(0x1664ADB7);
node->lch()->lch()->intval.append(0x2A1ED2C7);
node->lch()->lch()->intval.append(0xF0968B18);
node->lch()->lch()->intval.append(0x7928C2E0);
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

tp_heater_state_ptr = node->add("tp_heater_state",[](){return QVariant(mj->out.tp_heater_state.msg->hdr.cnt);});
tp_heater_state_ptr->tx_enable = &mj->out.tp_heater_state.tx_enable;

node->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.tp_heater_state.msg->mode));},[](){return (heater_mode_str(mj->out.tp_heater_state.msg->mode));})->setData =  [](QVariant data){ mj->out.tp_heater_state.msg->mode=(heater_mode)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("AUTO");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->add("state",[](){return QVariant((int32_t)(mj->out.tp_heater_state.msg->state));},[](){return (heater_status_str(mj->out.tp_heater_state.msg->state));})->setData =  [](QVariant data){ mj->out.tp_heater_state.msg->state=(heater_status)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->add("temp",[](){return QVariant(mj->out.tp_heater_state.msg->temp);})->setData =  [](QVariant data){ mj->out.tp_heater_state.msg->temp=data.value<float>();return;};
node->lch()->lch()->editable = true;

w_tv_heater_state_ptr = node->add("w_tv_heater_state",[](){return QVariant(mj->out.w_tv_heater_state.msg->hdr.cnt);});
w_tv_heater_state_ptr->tx_enable = &mj->out.w_tv_heater_state.tx_enable;

node->lch()->add("mode",[](){return QVariant((int32_t)(mj->out.w_tv_heater_state.msg->mode));},[](){return (heater_mode_str(mj->out.w_tv_heater_state.msg->mode));})->setData =  [](QVariant data){ mj->out.w_tv_heater_state.msg->mode=(heater_mode)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("AUTO");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->add("state",[](){return QVariant((int32_t)(mj->out.w_tv_heater_state.msg->state));},[](){return (heater_status_str(mj->out.w_tv_heater_state.msg->state));})->setData =  [](QVariant data){ mj->out.w_tv_heater_state.msg->state=(heater_status)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("OFF");
node->lch()->lch()->values.append("ON");
node->lch()->lch()->values.append("FAULT");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->intval.append(1);
node->lch()->lch()->intval.append(2);
node->lch()->add("temp",[](){return QVariant(mj->out.w_tv_heater_state.msg->temp);})->setData =  [](QVariant data){ mj->out.w_tv_heater_state.msg->temp=data.value<float>();return;};
node->lch()->lch()->editable = true;

return node;
};

TreeNode * create_pion_mku_gn_params_tree(mj_pion_mku_gn_t * mj_ptr){
static mj_pion_mku_gn_t * mj = mj_ptr;
TreeNode * node = new TreeNode("PARAMETERS",[](){return QVariant();});
auto cvs_ptr = node->add("cvs",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
cvs_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
node->lch()->add("type",[](){return QVariant((int32_t)(mj->out.prm_req.msg->type));})->setData =  [](QVariant data){ mj->out.prm_req.msg->type=(parameter_request_type)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("READ");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->values.append("WRITE");
node->lch()->lch()->intval.append(1);
node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.prm_req.msg->id));})->setData =  [](QVariant data){ mj->out.prm_req.msg->id=(uint32_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("factory_date");
node->lch()->lch()->intval.append(0xA92645D2);
node->lch()->lch()->values.append("factory_number");
node->lch()->lch()->intval.append(0xC8EE09D4);
node->lch()->lch()->values.append("description");
node->lch()->lch()->intval.append(0x4D7787A8);
node->lch()->lch()->values.append("service_mode");
node->lch()->lch()->intval.append(0x311FD2BA);
node->lch()->lch()->values.append("height_pix_tp");
node->lch()->lch()->intval.append(0x19FA383F);
node->lch()->lch()->values.append("height_pix_tvsh");
node->lch()->lch()->intval.append(0xF6087766);
node->lch()->lch()->values.append("height_pix_tvu");
node->lch()->lch()->intval.append(0x2DB93F34);
node->lch()->lch()->values.append("height_rad_tp");
node->lch()->lch()->intval.append(0x591F83F3);
node->lch()->lch()->values.append("height_rad_tvsh");
node->lch()->lch()->intval.append(0x8B93B334);
node->lch()->lch()->values.append("height_rad_tvu");
node->lch()->lch()->intval.append(0x9610F8C5);
node->lch()->lch()->values.append("width_pix_tp");
node->lch()->lch()->intval.append(0x1012BC5C);
node->lch()->lch()->values.append("width_pix_tvsh");
node->lch()->lch()->intval.append(0x76CF657E);
node->lch()->lch()->values.append("width_pix_tvu");
node->lch()->lch()->intval.append(0xC5398A3B);
node->lch()->lch()->values.append("width_rad_tp");
node->lch()->lch()->intval.append(0x41647D9);
node->lch()->lch()->values.append("width_rad_tvsh");
node->lch()->lch()->intval.append(0x6313063B);
node->lch()->lch()->values.append("width_rad_tvu");
node->lch()->lch()->intval.append(0x9FF87CA6);
node->lch()->lch()->values.append("radius_ld");
node->lch()->lch()->intval.append(0xEDECAE82);
node->lch()->lch()->values.append("pix_width_ld");
node->lch()->lch()->intval.append(0xED7C0BE8);
node->lch()->lch()->values.append("pix_height_ld");
node->lch()->lch()->intval.append(0x5CCB6F4A);
node->lch()->lch()->values.append("cvs_delay");
node->lch()->lch()->intval.append(0xF4670D59);
node->lch()->lch()->values.append("zu_x");
node->lch()->lch()->intval.append(0x3080C855);
node->lch()->lch()->values.append("zu_y");
node->lch()->lch()->intval.append(0xE8384A70);
node->lch()->lch()->values.append("zu_z");
node->lch()->lch()->intval.append(0x81F147A8);
node->lch()->lch()->values.append("lead_gn");
node->lch()->lch()->intval.append(0x2C377F17);
node->lch()->lch()->values.append("lead_vn");
node->lch()->lch()->intval.append(0x8AF08272);
node->lch()->lch()->values.append("lead_static");
node->lch()->lch()->intval.append(0x8D5727F8);
node->lch()->lch()->values.append("dcu_angles_flag");
node->lch()->lch()->intval.append(0xE95FB2D8);
node->lch()->lch()->values.append("inert_mode_flag");
node->lch()->lch()->intval.append(0x2FDFD0F1);
node->lch()->lch()->values.append("approx_error_threshold");
node->lch()->lch()->intval.append(0x5EA26FE2);
node->lch()->lch()->values.append("ld_delay_mode");
node->lch()->lch()->intval.append(0x4406A555);
node->lch()->lch()->values.append("approx_type");
node->lch()->lch()->intval.append(0x394E7C5C);
node->lch()->lch()->values.append("angle_gn_std");
node->lch()->lch()->intval.append(0x2D08847A);
node->lch()->lch()->values.append("angle_vn_std");
node->lch()->lch()->intval.append(0xEAA275A8);
node->lch()->lch()->values.append("range_std");
node->lch()->lch()->intval.append(0xEBA6B47);
node->lch()->lch()->values.append("init_pos_std");
node->lch()->lch()->intval.append(0x5041D4FA);
node->lch()->lch()->values.append("init_vel_std");
node->lch()->lch()->intval.append(0x994D9878);
node->lch()->lch()->values.append("init_acc_std");
node->lch()->lch()->intval.append(0x248659F);
node->lch()->lch()->values.append("geometry_threshold");
node->lch()->lch()->intval.append(0x4B62DD3C);
node->lch()->lch()->values.append("geometry_factor");
node->lch()->lch()->intval.append(0x83E3E832);
node->lch()->lch()->values.append("vel_min");
node->lch()->lch()->intval.append(0x54705DB8);
node->lch()->lch()->values.append("vel_max");
node->lch()->lch()->intval.append(0x5F2CAF5);
node->lch()->lch()->values.append("accel_direct_std");
node->lch()->lch()->intval.append(0x6A4D4E0F);
node->lch()->lch()->values.append("accel_min_turn_std");
node->lch()->lch()->intval.append(0x55589777);
node->lch()->lch()->values.append("accel_max_turn_std");
node->lch()->lch()->intval.append(0xCB51AC10);
node->lch()->lch()->values.append("nis_threshold");
node->lch()->lch()->intval.append(0xE961B362);
node->lch()->lch()->values.append("nis_gain");
node->lch()->lch()->intval.append(0xF9668FCB);
node->lch()->lch()->values.append("maneuver_timescale_min");
node->lch()->lch()->intval.append(0x9036E515);
node->lch()->lch()->values.append("maneuver_timescale_max");
node->lch()->lch()->intval.append(0x78A9C6C0);
node->lch()->lch()->values.append("singer_min_std");
node->lch()->lch()->intval.append(0x25C5CC22);
node->lch()->lch()->values.append("singer_max_std");
node->lch()->lch()->intval.append(0x8F7E8D1);
node->lch()->lch()->values.append("cvs_trj_forecast_time");
node->lch()->lch()->intval.append(0x8536FFBB);
node->lch()->lch()->values.append("com_if_bup_ctrl_mcast");
node->lch()->lch()->intval.append(0xF88316A1);
node->lch()->lch()->values.append("com_if_bup_data_mcast");
node->lch()->lch()->intval.append(0x4A709CD8);
node->lch()->lch()->values.append("com_if_pion_ctrl_mcast");
node->lch()->lch()->intval.append(0xA9E451E8);
node->lch()->lch()->values.append("com_if_pion_data_mcast");
node->lch()->lch()->intval.append(0x1B17DB91);
node->lch()->lch()->values.append("com_if_pion_state_mcast");
node->lch()->lch()->intval.append(0xBDFA8C51);
node->lch()->lch()->values.append("com_if_ld_data_mcast");
node->lch()->lch()->intval.append(0xE38494B0);
node->lch()->lch()->values.append("com_if_target_track_mcast");
node->lch()->lch()->intval.append(0x87A52B5F);
node->lch()->lch()->values.append("com_if_pion_heater_ctrl_mcast");
node->lch()->lch()->intval.append(0x95EE7424);
node->lch()->lch()->values.append("com_if_pion_power_ctrl_mcast");
node->lch()->lch()->intval.append(0xB9DD1547);
node->lch()->lch()->values.append("com_if_pion_heater_data_mcast");
node->lch()->lch()->intval.append(0x271DFE5D);
node->lch()->lch()->values.append("com_if_pion_power_data_mcast");
node->lch()->lch()->intval.append(0xB2E9F3E);
node->lch()->lch()->values.append("com_if_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6857720E);
node->lch()->lch()->values.append("com_if_srv_mcast");
node->lch()->lch()->intval.append(0xEA688EF1);
node->lch()->lch()->values.append("com_if_im_zu_state_mcast");
node->lch()->lch()->intval.append(0x335FAA57);
node->lch()->lch()->values.append("com_if_im_drive_mcast");
node->lch()->lch()->intval.append(0x1664ADB7);
node->lch()->lch()->values.append("com_if_im_cvs_mcast");
node->lch()->lch()->intval.append(0x2A1ED2C7);
node->lch()->lch()->values.append("com_if_im_target_mcast");
node->lch()->lch()->intval.append(0xF0968B18);
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
node->lch()->lch()->values.append("com_if_bup_ctrl_mcast");
node->lch()->lch()->intval.append(0xF88316A1);
node->lch()->lch()->values.append("com_if_bup_data_mcast");
node->lch()->lch()->intval.append(0x4A709CD8);
node->lch()->lch()->values.append("com_if_pion_ctrl_mcast");
node->lch()->lch()->intval.append(0xA9E451E8);
node->lch()->lch()->values.append("com_if_pion_data_mcast");
node->lch()->lch()->intval.append(0x1B17DB91);
node->lch()->lch()->values.append("com_if_pion_state_mcast");
node->lch()->lch()->intval.append(0xBDFA8C51);
node->lch()->lch()->values.append("com_if_wp_sens_mcast");
node->lch()->lch()->intval.append(0x7BA2FE2C);
node->lch()->lch()->values.append("com_if_ld_ctrl_mcast");
node->lch()->lch()->intval.append(0x51771EC9);
node->lch()->lch()->values.append("com_if_ld_data_mcast");
node->lch()->lch()->intval.append(0xE38494B0);
node->lch()->lch()->values.append("com_if_pion_sens_mcast");
node->lch()->lch()->intval.append(0xC0AA259A);
node->lch()->lch()->values.append("com_if_target_track_mcast");
node->lch()->lch()->intval.append(0x87A52B5F);
node->lch()->lch()->values.append("com_if_tcu_data_mcast");
node->lch()->lch()->intval.append(0x3568B4DA);
node->lch()->lch()->values.append("com_if_dcu_vn_data_mcast");
node->lch()->lch()->intval.append(0xBE85653F);
node->lch()->lch()->values.append("com_if_dcu_gn_data_mcast");
node->lch()->lch()->intval.append(0xE703366F);
node->lch()->lch()->values.append("com_if_ifu_data_mcast");
node->lch()->lch()->intval.append(0x9E21915);
node->lch()->lch()->values.append("com_if_pcm_data_mcast");
node->lch()->lch()->intval.append(0x87AEAD2D);
node->lch()->lch()->values.append("com_if_pion_drv_ctrl_mcast");
node->lch()->lch()->intval.append(0xBBEFE16E);
node->lch()->lch()->values.append("com_if_pion_heater_ctrl_mcast");
node->lch()->lch()->intval.append(0x95EE7424);
node->lch()->lch()->values.append("com_if_pion_power_ctrl_mcast");
node->lch()->lch()->intval.append(0xB9DD1547);
node->lch()->lch()->values.append("com_if_pion_heater_data_mcast");
node->lch()->lch()->intval.append(0x271DFE5D);
node->lch()->lch()->values.append("com_if_pion_power_data_mcast");
node->lch()->lch()->intval.append(0xB2E9F3E);
node->lch()->lch()->values.append("com_if_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6857720E);
node->lch()->lch()->values.append("com_if_pion_srv_mcast");
node->lch()->lch()->intval.append(0x5B060D18);
node->lch()->lch()->values.append("com_if_srv_mcast");
node->lch()->lch()->intval.append(0xEA688EF1);
node->lch()->lch()->values.append("com_if_im_zu_data_mcast");
node->lch()->lch()->intval.append(0xE1990506);
node->lch()->lch()->values.append("com_if_im_zu_state_mcast");
node->lch()->lch()->intval.append(0x335FAA57);
node->lch()->lch()->values.append("com_if_im_drive_ctrl_mcast");
node->lch()->lch()->intval.append(0x3998C1DF);
node->lch()->lch()->values.append("com_if_im_drive_mcast");
node->lch()->lch()->intval.append(0x1664ADB7);
node->lch()->lch()->values.append("com_if_im_cvs_mcast");
node->lch()->lch()->intval.append(0x2A1ED2C7);
node->lch()->lch()->values.append("com_if_im_target_mcast");
node->lch()->lch()->intval.append(0xF0968B18);
node->lch()->lch()->values.append("com_if_im_trig_mcast");
node->lch()->lch()->intval.append(0x7928C2E0);
node->lch()->lch()->values.append("dev_id");
node->lch()->lch()->intval.append(0x17EAC676);
node->lch()->add("val",[](){return QVariant(prm2QVariant(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val)));})->setData =  [](QVariant data){ QVariant2prm(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val),data);return;};
node->lch()->lch()->editable = true;
auto pion_mku_vn_ptr = node->add("pion_mku_vn",[](){return QVariant(mj->out.prm_req.msg->hdr.cnt);});
pion_mku_vn_ptr->tx = [](uint16_t dst){mj->out.prm_req.tx(dst);};
node->lch()->add("type",[](){return QVariant((int32_t)(mj->out.prm_req.msg->type));})->setData =  [](QVariant data){ mj->out.prm_req.msg->type=(parameter_request_type)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("READ");
node->lch()->lch()->intval.append(0);
node->lch()->lch()->values.append("WRITE");
node->lch()->lch()->intval.append(1);
node->lch()->add("id",[](){return QVariant((int32_t)(mj->out.prm_req.msg->id));})->setData =  [](QVariant data){ mj->out.prm_req.msg->id=(uint32_t)(data.value<int32_t>());return;};
node->lch()->lch()->editable = true;
node->lch()->lch()->values.append("drv_parking_pos");
node->lch()->lch()->intval.append(0x1EE5D873);
node->lch()->lch()->values.append("cfg_motor_type");
node->lch()->lch()->intval.append(0xB84A2AAE);
node->lch()->lch()->values.append("cfg_angle_sensor_type");
node->lch()->lch()->intval.append(0x5EB1D6A2);
node->lch()->lch()->values.append("cfg_gyro_type");
node->lch()->lch()->intval.append(0x191EC7B1);
node->lch()->lch()->values.append("cfg_rotor_sensor_type");
node->lch()->lch()->intval.append(0xC6AA70E);
node->lch()->lch()->values.append("cfg_brake_type");
node->lch()->lch()->intval.append(0x59F62361);
node->lch()->lch()->values.append("cfg_asrc_type");
node->lch()->lch()->intval.append(0x70AD98CA);
node->lch()->lch()->values.append("cfg_temp_sensor_type");
node->lch()->lch()->intval.append(0x22CDAD7A);
node->lch()->lch()->values.append("cfg_cam_wide_tv_offset_x");
node->lch()->lch()->intval.append(0x372CD6A3);
node->lch()->lch()->values.append("cfg_cam_wide_tv_offset_y");
node->lch()->lch()->intval.append(0x724B2E63);
node->lch()->lch()->values.append("cfg_cam_narrow_tv_offset_y");
node->lch()->lch()->intval.append(0xB06B673E);
node->lch()->lch()->values.append("cfg_cam_narrow_tv_offset_x");
node->lch()->lch()->intval.append(0xF50C9FFE);
node->lch()->lch()->values.append("cfg_cam_tp_offset_x");
node->lch()->lch()->intval.append(0x424C6256);
node->lch()->lch()->values.append("cfg_cam_tp_offset_y");
node->lch()->lch()->intval.append(0x72B9A96);
node->lch()->lch()->values.append("test_mode");
node->lch()->lch()->intval.append(0xDE1AF569);
node->lch()->lch()->values.append("service_mode");
node->lch()->lch()->intval.append(0x311FD2BA);
node->lch()->lch()->values.append("im_mode");
node->lch()->lch()->intval.append(0xE54327C5);
node->lch()->lch()->values.append("dbg_mode");
node->lch()->lch()->intval.append(0x84A7BB67);
node->lch()->lch()->values.append("ptp_stat");
node->lch()->lch()->intval.append(0xC17D8050);
node->lch()->lch()->values.append("adc_shift");
node->lch()->lch()->intval.append(0x2371F357);
node->lch()->lch()->values.append("vdc_scale");
node->lch()->lch()->intval.append(0xF366F564);
node->lch()->lch()->values.append("ctrl_ang_pos_gain");
node->lch()->lch()->intval.append(0xC808D4F3);
node->lch()->lch()->values.append("ctrl_ang_damping");
node->lch()->lch()->intval.append(0xD93B241B);
node->lch()->lch()->values.append("ctrl_ang_damping_th");
node->lch()->lch()->intval.append(0x7D6BFDE6);
node->lch()->lch()->values.append("ctrl_ang_speed_gain");
node->lch()->lch()->intval.append(0x69D41D8C);
node->lch()->lch()->values.append("ctrl_ang_current_gain");
node->lch()->lch()->intval.append(0xF5B606B6);
node->lch()->lch()->values.append("ctrl_speed_pos_gain");
node->lch()->lch()->intval.append(0xFD1C2D54);
node->lch()->lch()->values.append("ctrl_speed_speed_gain");
node->lch()->lch()->intval.append(0x8B117320);
node->lch()->lch()->values.append("ctrl_speed_current_gain");
node->lch()->lch()->intval.append(0xEC285B9D);
node->lch()->lch()->values.append("ctrl_speed_damping");
node->lch()->lch()->intval.append(0x680E6C7F);
node->lch()->lch()->values.append("ctrl_speed_damping_th");
node->lch()->lch()->intval.append(0x9FAE934A);
node->lch()->lch()->values.append("ctrl_speed_accel_lim");
node->lch()->lch()->intval.append(0x94409FDF);
node->lch()->lch()->values.append("ctrl_speed_flt");
node->lch()->lch()->intval.append(0x8F52D59D);
node->lch()->lch()->values.append("ctrl_trk_pos_gain");
node->lch()->lch()->intval.append(0x5367BD80);
node->lch()->lch()->values.append("ctrl_trk_damping");
node->lch()->lch()->intval.append(0x34A03BCA);
node->lch()->lch()->values.append("ctrl_trk_damping_th");
node->lch()->lch()->intval.append(0x5C8D187B);
node->lch()->lch()->values.append("ctrl_trk_speed_gain");
node->lch()->lch()->intval.append(0x4832F811);
node->lch()->lch()->values.append("ctrl_trk_current_gain");
node->lch()->lch()->intval.append(0x1A328A4);
node->lch()->lch()->values.append("ctrl_trk_speed_lim");
node->lch()->lch()->intval.append(0xE5FC7D1D);
node->lch()->lch()->values.append("ctrl_trk_err_is_spherical");
node->lch()->lch()->intval.append(0x2CDADFF6);
node->lch()->lch()->values.append("ctrl_trk_tv_delay");
node->lch()->lch()->intval.append(0x5DC2B375);
node->lch()->lch()->values.append("ctrl_trk_tp_delay");
node->lch()->lch()->intval.append(0x3616DF10);
node->lch()->lch()->values.append("ctrl_trk_lim_th");
node->lch()->lch()->intval.append(0x38C06AE5);
node->lch()->lch()->values.append("ctrl_use_cart_trj");
node->lch()->lch()->intval.append(0x8EA754D7);
node->lch()->lch()->values.append("ctrl_load_obs_gain");
node->lch()->lch()->intval.append(0xEA2EAEC7);
node->lch()->lch()->values.append("ctrl_fire_pos_gain");
node->lch()->lch()->intval.append(0xC7B887BF);
node->lch()->lch()->values.append("ctrl_fire_speed_gain");
node->lch()->lch()->intval.append(0x3D2BB69C);
node->lch()->lch()->values.append("ctrl_fire_current_gain");
node->lch()->lch()->intval.append(0x76A77EDB);
node->lch()->lch()->values.append("ctrl_fire_obs_gain");
node->lch()->lch()->intval.append(0x5F9E600A);
node->lch()->lch()->values.append("ctrl_force_delay");
node->lch()->lch()->intval.append(0x8BE30201);
node->lch()->lch()->values.append("ctrl_torque_obs_gain");
node->lch()->lch()->intval.append(0xD94F2803);
node->lch()->lch()->values.append("ctrl_ref_obs_gain");
node->lch()->lch()->intval.append(0x6777563E);
node->lch()->lch()->values.append("ctrl_curent_max");
node->lch()->lch()->intval.append(0xB6FD8005);
node->lch()->lch()->values.append("ctrl_v_max");
node->lch()->lch()->intval.append(0xA83AFFF1);
node->lch()->lch()->values.append("ctrl_ss_err_th");
node->lch()->lch()->intval.append(0x541D492A);
node->lch()->lch()->values.append("ctrl_ss_spd_th");
node->lch()->lch()->intval.append(0xD4CDEB67);
node->lch()->lch()->values.append("ctrl_ss_flt");
node->lch()->lch()->intval.append(0x8F486F03);
node->lch()->lch()->values.append("ctrl_ss_lead_delay_ms");
node->lch()->lch()->intval.append(0x4B6F9372);
node->lch()->lch()->values.append("ctrl_syncro");
node->lch()->lch()->intval.append(0xFF16CE21);
node->lch()->lch()->values.append("ctrl_syncro_point");
node->lch()->lch()->intval.append(0x5AD712BA);
node->lch()->lch()->values.append("ctrl_limit_th");
node->lch()->lch()->intval.append(0xFE4EAF05);
node->lch()->lch()->values.append("ctrl_limit_enable");
node->lch()->lch()->intval.append(0x8D919959);
node->lch()->lch()->values.append("fire_full_voltage");
node->lch()->lch()->intval.append(0x64ADD15C);
node->lch()->lch()->values.append("fire_hold_voltage");
node->lch()->lch()->intval.append(0xCAC729F0);
node->lch()->lch()->values.append("fire_full_time");
node->lch()->lch()->intval.append(0x6042DEB7);
node->lch()->lch()->values.append("fire_down_time");
node->lch()->lch()->intval.append(0x4F11C4CC);
node->lch()->lch()->values.append("fire_max_time");
node->lch()->lch()->intval.append(0xB9BB8B0D);
node->lch()->lch()->values.append("fire_delay");
node->lch()->lch()->intval.append(0xF6BC1251);
node->lch()->lch()->values.append("fire_repeat_temp1");
node->lch()->lch()->intval.append(0x4A12BD87);
node->lch()->lch()->values.append("fire_repeat_temp2");
node->lch()->lch()->intval.append(0x85BAB4C7);
node->lch()->lch()->values.append("fire_repeat_temp3");
node->lch()->lch()->intval.append(0xC0DD4C07);
node->lch()->lch()->values.append("fire_single_time");
node->lch()->lch()->intval.append(0xDD7FCAC);
node->lch()->lch()->values.append("fire_short_time");
node->lch()->lch()->intval.append(0x7853C445);
node->lch()->lch()->values.append("fire_long_time");
node->lch()->lch()->intval.append(0x9330952A);
node->lch()->lch()->values.append("fire_mode");
node->lch()->lch()->intval.append(0x81CE8659);
node->lch()->lch()->values.append("gyro_offset");
node->lch()->lch()->intval.append(0x327A9E98);
node->lch()->lch()->values.append("gyro_offsetX");
node->lch()->lch()->intval.append(0x4E25F56E);
node->lch()->lch()->values.append("gyro_offsetY");
node->lch()->lch()->intval.append(0xE394CBC1);
node->lch()->lch()->values.append("gyro_offsetZ");
node->lch()->lch()->intval.append(0x15470387);
node->lch()->lch()->values.append("gyro_scale");
node->lch()->lch()->intval.append(0xFBDE3B20);
node->lch()->lch()->values.append("gyro_filt");
node->lch()->lch()->intval.append(0x4947081B);
node->lch()->lch()->values.append("gyro_alpha");
node->lch()->lch()->intval.append(0x1F5986CD);
node->lch()->lch()->values.append("gyro_beta");
node->lch()->lch()->intval.append(0xB0138FA5);
node->lch()->lch()->values.append("gyro_gamma");
node->lch()->lch()->intval.append(0x69C4EFD3);
node->lch()->lch()->values.append("ocp_react_time");
node->lch()->lch()->intval.append(0xD02A15D0);
node->lch()->lch()->values.append("ocp_lvl");
node->lch()->lch()->intval.append(0x4A0AB355);
node->lch()->lch()->values.append("ocp_cooldown_time");
node->lch()->lch()->intval.append(0xD0AC7199);
node->lch()->lch()->values.append("drv_limit_up");
node->lch()->lch()->intval.append(0x5C57D2B7);
node->lch()->lch()->values.append("drv_limit_down");
node->lch()->lch()->intval.append(0x501D05A4);
node->lch()->lch()->values.append("drv_zero");
node->lch()->lch()->intval.append(0x74C112A);
node->lch()->lch()->values.append("el_zero");
node->lch()->lch()->intval.append(0xA57FD22E);
node->lch()->lch()->values.append("drv_gbx_ration");
node->lch()->lch()->intval.append(0xBBD3E88F);
node->lch()->lch()->values.append("drv_ang_reverse");
node->lch()->lch()->intval.append(0x54F313B1);
node->lch()->lch()->values.append("ld_enable");
node->lch()->lch()->intval.append(0xD543F9FE);
node->lch()->lch()->values.append("brk_release_voltage");
node->lch()->lch()->intval.append(0x2CF660C2);
node->lch()->lch()->values.append("brk_hold_voltage");
node->lch()->lch()->intval.append(0xC4CA33B0);
node->lch()->lch()->values.append("brk_release_time");
node->lch()->lch()->intval.append(0xF449C211);
node->lch()->lch()->values.append("drv_rotor_reverse");
node->lch()->lch()->intval.append(0x38430DA2);
node->lch()->lch()->values.append("drv_gyro_reverse");
node->lch()->lch()->intval.append(0x491BE8E9);
node->lch()->lch()->values.append("drv_current_reverse");
node->lch()->lch()->intval.append(0xFC9F76B6);
node->lch()->lch()->values.append("drv_voltage_reverse");
node->lch()->lch()->intval.append(0x310908E7);
node->lch()->lch()->values.append("load_inertia");
node->lch()->lch()->intval.append(0x161CBA22);
node->lch()->lch()->values.append("load_friction_coeff");
node->lch()->lch()->intval.append(0xD443BE16);
node->lch()->lch()->values.append("load_max_speed");
node->lch()->lch()->intval.append(0x35045471);
node->lch()->lch()->values.append("motor_armature_resistance");
node->lch()->lch()->intval.append(0x507A3C3C);
node->lch()->lch()->values.append("motor_armature_inductance");
node->lch()->lch()->intval.append(0xDA0658A);
node->lch()->lch()->values.append("motor_bemf");
node->lch()->lch()->intval.append(0xC7865F20);
node->lch()->lch()->values.append("motor_moment_constant");
node->lch()->lch()->intval.append(0x5A8BE1ED);
node->lch()->lch()->values.append("vdc_min");
node->lch()->lch()->intval.append(0x800F3056);
node->lch()->lch()->values.append("estimator_type");
node->lch()->lch()->intval.append(0xC2BB8B97);
node->lch()->lch()->values.append("kalman_q_angle");
node->lch()->lch()->intval.append(0x4586160E);
node->lch()->lch()->values.append("kalman_q_velocity");
node->lch()->lch()->intval.append(0x4C62D80B);
node->lch()->lch()->values.append("kalman_q_current");
node->lch()->lch()->intval.append(0x82675000);
node->lch()->lch()->values.append("kalman_q_tl");
node->lch()->lch()->intval.append(0xA8331120);
node->lch()->lch()->values.append("kalman_q_vd");
node->lch()->lch()->intval.append(0x9C7C61E3);
node->lch()->lch()->values.append("kalman_r_angle");
node->lch()->lch()->intval.append(0x236B85E1);
node->lch()->lch()->values.append("kalman_r_velocity");
node->lch()->lch()->intval.append(0xEC7DAD1B);
node->lch()->lch()->values.append("kalman_r_current");
node->lch()->lch()->intval.append(0xE48AC3EF);
node->lch()->lch()->values.append("ptp_kp");
node->lch()->lch()->intval.append(0x70B25BB3);
node->lch()->lch()->values.append("ptp_ki");
node->lch()->lch()->intval.append(0x5424B99B);
node->lch()->lch()->values.append("ptp_kd");
node->lch()->lch()->intval.append(0x925B41AA);
node->lch()->lch()->values.append("com_if_pion_data_mcast");
node->lch()->lch()->intval.append(0x1B17DB91);
node->lch()->lch()->values.append("com_if_ld_ctrl_mcast");
node->lch()->lch()->intval.append(0x51771EC9);
node->lch()->lch()->values.append("com_if_ld_data_mcast");
node->lch()->lch()->intval.append(0xE38494B0);
node->lch()->lch()->values.append("com_if_pion_sens_mcast");
node->lch()->lch()->intval.append(0xC0AA259A);
node->lch()->lch()->values.append("com_if_target_track_mcast");
node->lch()->lch()->intval.append(0x87A52B5F);
node->lch()->lch()->values.append("com_if_pion_drv_ctrl_mcast");
node->lch()->lch()->intval.append(0xBBEFE16E);
node->lch()->lch()->values.append("com_if_pion_heater_ctrl_mcast");
node->lch()->lch()->intval.append(0x95EE7424);
node->lch()->lch()->values.append("com_if_pion_power_ctrl_mcast");
node->lch()->lch()->intval.append(0xB9DD1547);
node->lch()->lch()->values.append("com_if_pion_heater_data_mcast");
node->lch()->lch()->intval.append(0x271DFE5D);
node->lch()->lch()->values.append("com_if_pion_power_data_mcast");
node->lch()->lch()->intval.append(0xB2E9F3E);
node->lch()->lch()->values.append("com_if_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6857720E);
node->lch()->lch()->values.append("com_if_pion_srv_mcast");
node->lch()->lch()->intval.append(0x5B060D18);
node->lch()->lch()->values.append("com_if_srv_mcast");
node->lch()->lch()->intval.append(0xEA688EF1);
node->lch()->lch()->values.append("dev_id");
node->lch()->lch()->intval.append(0x17EAC676);
node->lch()->add("val",[](){return QVariant(prm2QVariant(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val)));})->setData =  [](QVariant data){ QVariant2prm(mj->out.prm_req.msg->id,(uint8_t*)mj->out.prm_req.msg->val,sizeof(mj->out.prm_req.msg->val),data);return;};
node->lch()->lch()->editable = true;
return node;
};