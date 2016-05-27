/*!
\file
\brief Набор данных FSM Аудиоустроство
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#ifndef FCM_AUDIODEVICECLASS_H
#define	FCM_AUDIODEVICECLASS_H
/*!
\brief Вид устроства
*/
enum FSMAD_VidDevice
{
    CommunicationDevice=1 ///< Устроства связи
};
/*!
\brief ПодВид устроства
*/
enum FSMAD_PodVidDevice
{
   CCK=1 ///< СЦК
};
/*!
\brief Род устроства
*/
enum FSMAD_RodDevice
{
    MN921=1,///< MN921
    MN825=2,///< MN825
    PO07=3,///< PO07
    PO08=4,///< PO08
    PO06=5,///< PO06
    MN524=6,///< MN524
};
struct FSME1Buff
{
    unsigned short count;
    char Data[31][320];
};
struct FSM_E1Device
{
    char reg;
    unsigned short iddev;
    int idstream;
    struct fsm_ethernet_dev* ethdev;
    unsigned short streams_id[32];
    //struct FSME1Buff E1buffs;
};
struct fsm_po06_serversetting
{
    
};
struct fsm_po06_abonent
{
	unsigned short id;
	unsigned short idchannel;
};

struct fsm_po06_subscriber
{
	unsigned short idch1;
	unsigned short idch2;
	struct fsm_po06_abonent fsm_ab[2][12];
};
struct fsm_po06_setting
{
    struct fsm_po06_subscriber fsm_p006_su_s;
    //struct fsm_po06_serversetting fsm_p006_se_s;
};
struct FSM_PO06Device
{
    char reg;
    unsigned short iddev;
    int idstream;
    int idcon;
    struct fsm_ethernet_dev* ethdev;
    struct fsm_po06_setting po06set;
};

enum FSME1Command /*0*****125*/
{
    FSME1SendStream=1
};
enum FSMPO06Command /*0*****125*/
{
    FSMPO06SendStream=1,
    FSMPO06ConnectToDevE1=2,
    FSMPO06DisConnectToDevE1=3,
    SetSettingClientPo06=4,
    AnsSetSettingClientPo06=5,
    GetSettingClientPo06=6,
    AnsGetSettingClientPo06=7
};

struct FSME1Pkt
{
    char channels;
    char count;
    char Data[1024]; 
}__attribute__((__packed__ ));
void FSM_E1SendPacket(char* Data1,unsigned char len);


struct FSMPO06CommCons
{
    unsigned short id;
    unsigned short channel;
};




#endif	/* FCM_AUDIODEVICECLASS_H */