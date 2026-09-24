
#include "signaltree.h"

static TreeNode *cvs_prm_req_ptr = 0;
static TreeNode *mon_cmd_req_ptr = 0;
static TreeNode *mon_prm_req_ptr = 0;

static TreeNode *wp_imu_state_ptr = 0;

static QStringList devList()
{
    QStringList devs;
	devs.append("imu_sensor");
	devs.append("w_imu_sensor");
	devs.append("gyroscope_sensor");
	devs.append("w_avs_vn");
	devs.append("w_avs_gn");
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
	ids.append(0x8A15);
	ids.append(0xB9AD);
	ids.append(0xDD1D);
	ids.append(0x8DD3);
	ids.append(0xBFA);
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
 
        case 0xCFDFEA32:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x6857720E:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xFC8E9524:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x5B060D18:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xB676D072:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x987BF304:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x7BA2FE2C:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xBC56B400:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xC0AA259A:
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
 
        case 0xF88316A1:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x87A52B5F:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x4A709CD8:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xEA688EF1:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0x1B17DB91:
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
 
        case 0xBDFA8C51:
            val[size-1] = 0;
            return QVariant(cp866ToQString((char *)val,size));
 
        case 0xA9E451E8:
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
    if (id == 0xCFDFEA32)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x6857720E)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xFC8E9524)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x5B060D18)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xB676D072)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x987BF304)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x7BA2FE2C)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xBC56B400)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xC0AA259A)
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
    if (id == 0xF88316A1)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x87A52B5F)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x4A709CD8)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xEA688EF1)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0x1B17DB91)
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
    if (id == 0xBDFA8C51)
    {
        QByteArray byte_str = qStringToCP866(data.toString());
        memcpy(val,(void *)(byte_str.data()), (size_t)(byte_str.size()) > size ? size : byte_str.size());
 
    } else 
    if (id == 0xA9E451E8)
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


TreeNode * create_w_imu_sensor_in_tree(mj_w_imu_sensor_t * mj_ptr)
{
static mj_w_imu_sensor_t *mj = mj_ptr;
TreeNode * node = new TreeNode("INPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
TreeNode * cvs_node = node->add("cvs",[](){return QVariant();});
cvs_node->isDev = true;
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
return node;
};


TreeNode * create_w_imu_sensor_out_tree(mj_w_imu_sensor_t * mj_ptr)
{
static mj_w_imu_sensor_t * mj = mj_ptr;
TreeNode * node = new TreeNode("OUTPUT",[](){return QVariant();});
node->devIDs = devIDs;
node->devList = devList;
wp_imu_state_ptr = node->add("wp_imu_state",[](){return QVariant(mj->out.wp_imu_state.msg->hdr.cnt);});
wp_imu_state_ptr->tx_enable = &mj->out.wp_imu_state.tx_enable;

node->lch()->add("omega",[](){return QVariant();});
node->lch()->lch()->add("x",[](){return QVariant(mj->out.wp_imu_state.msg->omega.x);})->setData =  [](QVariant data){ mj->out.wp_imu_state.msg->omega.x=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("y",[](){return QVariant(mj->out.wp_imu_state.msg->omega.y);})->setData =  [](QVariant data){ mj->out.wp_imu_state.msg->omega.y=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("z",[](){return QVariant(mj->out.wp_imu_state.msg->omega.z);})->setData =  [](QVariant data){ mj->out.wp_imu_state.msg->omega.z=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("a",[](){return QVariant();});
node->lch()->lch()->add("x",[](){return QVariant(mj->out.wp_imu_state.msg->a.x);})->setData =  [](QVariant data){ mj->out.wp_imu_state.msg->a.x=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("y",[](){return QVariant(mj->out.wp_imu_state.msg->a.y);})->setData =  [](QVariant data){ mj->out.wp_imu_state.msg->a.y=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->lch()->add("z",[](){return QVariant(mj->out.wp_imu_state.msg->a.z);})->setData =  [](QVariant data){ mj->out.wp_imu_state.msg->a.z=data.value<float>();return;};
node->lch()->lch()->lch()->editable = true;
node->lch()->add("temp",[](){return QVariant(mj->out.wp_imu_state.msg->temp);})->setData =  [](QVariant data){ mj->out.wp_imu_state.msg->temp=data.value<float>();return;};
node->lch()->lch()->editable = true;
node->lch()->add("is_valid",[](){return QVariant(mj->out.wp_imu_state.msg->is_valid);})->setData =  [](QVariant data){ mj->out.wp_imu_state.msg->is_valid=data.value<bool>();return;};
node->lch()->lch()->editable = true;

return node;
};

TreeNode * create_w_imu_sensor_params_tree(mj_w_imu_sensor_t * mj_ptr){
static mj_w_imu_sensor_t * mj = mj_ptr;
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
node->lch()->lch()->values.append("com_if_bup_tel_mcast");
node->lch()->lch()->intval.append(0xCFDFEA32);
node->lch()->lch()->values.append("com_if_ld_mcast");
node->lch()->lch()->intval.append(0xBC56B400);
node->lch()->lch()->values.append("com_if_bup_ctrl_mcast");
node->lch()->lch()->intval.append(0xF88316A1);
node->lch()->lch()->values.append("com_if_target_track_mcast");
node->lch()->lch()->intval.append(0x87A52B5F);
node->lch()->lch()->values.append("com_if_bup_data_mcast");
node->lch()->lch()->intval.append(0x4A709CD8);
node->lch()->lch()->values.append("com_if_srv_mcast");
node->lch()->lch()->intval.append(0xEA688EF1);
node->lch()->lch()->values.append("com_if_pion_data_mcast");
node->lch()->lch()->intval.append(0x1B17DB91);
node->lch()->lch()->values.append("com_if_pion_heater_ctrl_mcast");
node->lch()->lch()->intval.append(0x95EE7424);
node->lch()->lch()->values.append("com_if_pion_power_ctrl_mcast");
node->lch()->lch()->intval.append(0xB9DD1547);
node->lch()->lch()->values.append("com_if_pion_heater_data_mcast");
node->lch()->lch()->intval.append(0x271DFE5D);
node->lch()->lch()->values.append("com_if_pion_power_data_mcast");
node->lch()->lch()->intval.append(0xB2E9F3E);
node->lch()->lch()->values.append("com_if_pion_state_mcast");
node->lch()->lch()->intval.append(0xBDFA8C51);
node->lch()->lch()->values.append("com_if_pion_ctrl_mcast");
node->lch()->lch()->intval.append(0xA9E451E8);
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
node->lch()->lch()->values.append("com_if_bup_tel_mcast");
node->lch()->lch()->intval.append(0xCFDFEA32);
node->lch()->lch()->values.append("com_if_bup_srv_mcast");
node->lch()->lch()->intval.append(0x6857720E);
node->lch()->lch()->values.append("com_if_pion_tel_mcast");
node->lch()->lch()->intval.append(0xFC8E9524);
node->lch()->lch()->values.append("com_if_pion_srv_mcast");
node->lch()->lch()->intval.append(0x5B060D18);
node->lch()->lch()->values.append("com_if_imu_sens_mcast");
node->lch()->lch()->intval.append(0xB676D072);
node->lch()->lch()->values.append("com_if_gyro_sens_mcast");
node->lch()->lch()->intval.append(0x987BF304);
node->lch()->lch()->values.append("com_if_wp_sens_mcast");
node->lch()->lch()->intval.append(0x7BA2FE2C);
node->lch()->lch()->values.append("com_if_ld_mcast");
node->lch()->lch()->intval.append(0xBC56B400);
node->lch()->lch()->values.append("com_if_pion_sens_mcast");
node->lch()->lch()->intval.append(0xC0AA259A);
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
node->lch()->lch()->values.append("com_if_bup_ctrl_mcast");
node->lch()->lch()->intval.append(0xF88316A1);
node->lch()->lch()->values.append("com_if_target_track_mcast");
node->lch()->lch()->intval.append(0x87A52B5F);
node->lch()->lch()->values.append("com_if_bup_data_mcast");
node->lch()->lch()->intval.append(0x4A709CD8);
node->lch()->lch()->values.append("com_if_srv_mcast");
node->lch()->lch()->intval.append(0xEA688EF1);
node->lch()->lch()->values.append("com_if_pion_data_mcast");
node->lch()->lch()->intval.append(0x1B17DB91);
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
node->lch()->lch()->values.append("com_if_pion_state_mcast");
node->lch()->lch()->intval.append(0xBDFA8C51);
node->lch()->lch()->values.append("com_if_pion_ctrl_mcast");
node->lch()->lch()->intval.append(0xA9E451E8);
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
return node;
};