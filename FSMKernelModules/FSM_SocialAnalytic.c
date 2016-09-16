/*!
\file
\brief Модуль анализа соц сетей
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSM_SA/FSM_SA.h"

struct FSM_DeviceFunctionTree dft;
struct FSM_SADevice FSMSADev[FSM_SADeviceTreeSize];
struct FSM_SendCmd sendcmd;
struct FSM_AudioStream fsmas;

#ifdef DEBUG_CALL_STACK
uint64_t debug_this5;
extern uint64_t debug_global;
#define DEBUG_CALL_STACK_SetStack debug_this5 = (debug_this5 << 8)
#define DEBUG_CALL_STACK_THIS 5
#define DEBUG_CALL_STACK_GLOBSET debug_global = (debug_global << 8) | (DEBUG_CALL_STACK_THIS);

typedef enum debug_function {
    init_on = 0x00,
    init_off = 0x01,
    exit_on = 0x02,
    exit_off = 0x03,
    get_ssi_init = 0x04,
    get_ssi_exit = 0x05,
    get_por_init = 0x06,
    get_por_exit = 0x07,
    get_asp6_init = 0x08,
    get_asp6_exit = 0x09,

} debug_fun;
#endif

int AnalizData(char* Data, unsigned short len)
{
    return 0;
}

void FSM_SASRecive(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    int i;

    struct FSM_SendCmdTS* scmd = (struct FSM_SendCmdTS*)data;
// char datas[2];
#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (get_por_init);
#endif

    switch(data[0]) {

    case RegDevice: ///< Регистрация устройства
        FSM_Statstic_SetStatus(to_dt, "ok");
        for(i = 0; i < FSM_PO08DeviceTreeSize; i++) {
            if(FSMSADev[i].iddev == to_dt->IDDevice) {
                return;
            }
        }
        for(i = 0; i < FSM_SADeviceTreeSize; i++) {
            if(FSMSADev[i].reg == 0) {
                FSMSADev[i].reg = 1;
                FSMSADev[i].ethdev = FSM_FindEthernetDevice(to_dt->IDDevice);
                to_dt->data = &FSMSADev[i];
                to_dt->config = &FSMSADev[i].saset;
                break;
            }
        }
        break;
    case DelLisr:
        for(i = 0; i < FSM_SADeviceTreeSize; i++) {
            if((FSMSADev[i].reg == 1) && (FSMSADev[i].iddev == to_dt->IDDevice)) {

                FSMSADev[i].reg = 0;
                printk(KERN_INFO "FSM SA Device Deleted %u \n", to_dt->IDDevice);
                break;
            }
        }
        break;
    case AnsPing: ///< Пинг
        break;
    case SendCmdToServer: ///< Отправка команды серверу
        switch(scmd->cmd) {
        case FSMSA_IDK:

            break;
        }

        break;
    case SendTxtMassage: ///< Отправка текстового сообщения
        break;
    case Alern: ///<Тревога
        switch(((struct FSM_AlernSignal*)data)->ID) {
        }
        break;
    case Warning: ///<Предупреждение
        switch(((struct FSM_WarningSignal*)data)->ID) {
        case FSM_CCK_Server_Connect_Error:
            break;
        }
        break;
    case Trouble: ///<Сбой
        switch(((struct FSM_TroubleSignal*)data)->ID) {
        case FSM_CCK_Memory_Test_Filed:
            break;
        }
        break;
    case Beep: ///<Звук
        break;
    default:
        break;
    }

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (get_por_exit);
#endif

    printk(KERN_INFO "RPack %u \n", len);
}
EXPORT_SYMBOL(FSM_SASRecive);

void ApplaySettingSA(struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
}

static int __init FSM_PO08_init(void)
{

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (init_on);
#endif

    dft.aplayp = ApplaySettingSA;
    dft.type = (unsigned char)SocialAnalytica;
    dft.VidDevice = (unsigned char)FSMSA_Analiz;
    dft.PodVidDevice = (unsigned char)FSMSA_AnalizData;
    dft.KodDevice = (unsigned char)FSMSA_AnalizDataServer;
    dft.Proc = FSM_SASRecive;
    dft.config_len = sizeof(struct fsm_sa_setting);
    FSM_DeviceClassRegister(dft);
    printk(KERN_INFO "FSM SA Module loaded\n");

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (init_off);
#endif

    return 0;
}

static void __exit FSM_PO08_exit(void)
{
#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (exit_on);
#endif

    FSM_ClassDeRegister(dft);
    printk(KERN_INFO "FSM SA Module unloaded\n");

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (exit_off);
#endif
}

module_init(FSM_PO08_init);
module_exit(FSM_PO08_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM SA Module");
MODULE_LICENSE("GPL");