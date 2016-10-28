/*!
\file
\brief Модуль контроля питания
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#include <linux/init.h>
#include <linux/module.h>

#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_DeviceFunctionTree FSMCPC_dft;
struct FSM_CPC_Device FSMCPCDev[FSM_CPCDeviceTreeSize];
struct FSM_SendCmd FSMCPC_sendcmd;

#define FSM_CPC_EL_count 3
static struct fsm_signal_info FSM_CPC_EL[] = 
{  
    {0,"CurrentOff_5","5В Источник без нагрузки"},
    {1,"CurrentOff_12","12В Источник без нагрузки"},
    {2,"CurrentOff_24","24В Источник без нагрузки"},
};



void FSM_OnPower_5(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    
}
void FSM_OnPower_12(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    
}
void FSM_OnPower_24(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    
}
void FSM_OffPower_5(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    
}
void FSM_OffPower_12(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    
}
void FSM_OffPower_24(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    
}

#define FSM_CPC_SL_count 6
static struct fsm_slot_hndl FSM_CPC_SL[] =
{
    {0,"On5V","Включить 5В",FSM_OnPower_5},
    {1,"On12V","Включить 12В",FSM_OnPower_12},
    {2,"On24V","Включить 24В",FSM_OnPower_24},
    {3,"Off5V","Выключить 5В",FSM_OffPower_5},
    {4,"Off12V","Выключить 12В",FSM_OffPower_12},
    {5,"Off24V","Выключить 24В",FSM_OffPower_24},
};

void FSM_CPCRecive(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    int i,j;

    struct FSM_SendCmdTS* scmd = (struct FSM_SendCmdTS*)data;
    // char datas[2];

    switch(data[0]) {

    case RegDevice: ///< Регистрация устройства
        FSM_Statstic_SetStatus(to_dt, "ok");
        for(i = 0; i < FSM_CPCDeviceTreeSize; i++) {
            if(FSMCPCDev[i].iddev == to_dt->IDDevice) {
                return;
            }
        }
        for(i = 0; i < FSM_CPCDeviceTreeSize; i++) {
            if(FSMCPCDev[i].reg == 0) {
                FSMCPCDev[i].reg = 1;
                FSMCPCDev[i].iddev = to_dt->IDDevice;
                to_dt->data = &FSMCPCDev[i];
                // fsmdt->config=&FSMSkyNetDev[i].po06set;
                printk(KERN_INFO "FSM CPC Device Added %u \n", to_dt->IDDevice);
                for(j=0;j<FSM_CPC_EL_count;j++)
                {
                    to_dt->signal[i].info=(struct fsm_signal_info*)&(FSM_CPC_EL[i]);
                }
                break;
            }
        }
        break;
    case DelLisr:
        for(i = 0; i < FSM_CPCDeviceTreeSize; i++) {
            if((FSMCPCDev[i].reg == 1) && (FSMCPCDev[i].iddev == to_dt->IDDevice)) {
                FSMCPCDev[i].reg = 0;
                printk(KERN_INFO "FSM CPC Device Deleted %u \n", to_dt->IDDevice);
                break;
            }
        }
        break;
    case AnsPing: ///< Пинг
        break;
        
    case SendCmdToServer: ///< Отправка команды серверу
        switch(scmd->cmd) {
        case AnsGetSettingSwitch:
            printk(KERN_INFO "FSM_Set Recv %i\n", scmd->IDDevice);
            break;
        }
        break;
    case SendTxtMassage: ///< Отправка текстового сообщения
        break;
    case Alern: ///<Тревога
        break;
    case Warning: ///<Предупреждение
        break;
    case Trouble: ///<Сбой
        break;
    case Beep: ///<Звук
        break;
    default:
        break;
    }

    printk(KERN_INFO "RPack %u \n", len);
}
EXPORT_SYMBOL(FSM_CPCRecive);
void ApplaySettingCPC(struct FSM_DeviceTree* df)
{
    memset(&FSMCPC_sendcmd, 0, sizeof(FSMCPC_sendcmd));
    printk(KERN_INFO "FSM_Set\n");
    FSMCPC_sendcmd.cmd = SetSettingCPC;
    FSMCPC_sendcmd.countparam = 1;
    FSMCPC_sendcmd.IDDevice = df->IDDevice;
    FSMCPC_sendcmd.CRC = 0;
    FSMCPC_sendcmd.opcode = SendCmdToDevice;
    // memcpy(&sendcmd.Data,&(((struct FSM_PO06Device*)df->data)->po06set.fsm_p006_su_s),sizeof(struct
    // fsm_po06_subscriber));
    //(FSM_FindDevice(FSM_EthernetID))->dt->Proc((char*)&sendcmd,sizeof(struct
    // FSM_SendCmd)-sizeof(sendcmd.Data)+sizeof(struct fsm_po06_subscriber),df);
}

static int __init FSM_SkyNet_init(void)
{
    FSMCPC_dft.aplayp = (ApplayProcess)ApplaySettingCPC;
    FSMCPC_dft.type = (unsigned char)AvtoElSheet;
    FSMCPC_dft.VidDevice = (unsigned char)CPC;
    FSMCPC_dft.PodVidDevice = (unsigned char)CPC_12_24_5V;
    FSMCPC_dft.KodDevice = (unsigned char)CPC_STM32F103;
    FSMCPC_dft.Proc = FSM_CPCRecive;
    FSMCPC_dft.signal_count=FSM_CPC_EL_count;
    FSMCPC_dft.slot=FSM_CPC_SL;
    FSMCPC_dft.slot_count=FSM_CPC_SL_count;
    // dft.config_len=sizeof(struct fsm_po06_setting);
    FSM_DeviceClassRegister(FSMCPC_dft);
    printk(KERN_INFO "FSM CPC Module loaded\n");
    return 0;
}

static void __exit FSM_SkyNet_exit(void)
{
    printk(KERN_INFO "FSM CPC Module unloaded\n");
}

module_init(FSM_SkyNet_init);
module_exit(FSM_SkyNet_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM CPC Module");
MODULE_LICENSE("GPL");