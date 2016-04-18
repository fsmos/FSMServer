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
struct FSM_E1Device
{
    char reg;
    unsigned short iddev;
    int idstream;
    struct fsm_ethernet_dev* ethdev;
};
struct FSM_PO06Device
{
    char reg;
    unsigned short iddev;
    int idstream;
    struct fsm_ethernet_dev* ethdev;
};

enum FSME1Command /*0*****125*/
{
    FSME1SendStream=1
};
enum FSMPO06Command /*0*****125*/
{
    FSMPO06SendStream=1
};

struct FSME1Pkt
{
    char channels;
    char count;
    char Data[254];
};
struct FSME1Buff
{
    unsigned short count;
    char Data[31][320];
};
#endif	/* FCM_AUDIODEVICECLASS_H */

