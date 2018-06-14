#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include <linux/fs.h> 
//#include <asm/uaccess.h>   // Needed by segment descriptors

struct FSM_DeviceFunctionTree FSMStCTL_dft;
struct FSM_DeviceTree* FSMStCTL_dftv;
struct FSM_SendCmd FSMStCTL_fsmsc;

void
FSM_FSMStCTLRecive(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{

    struct FSM_SendCmdTS* fscts = (struct FSM_SendCmdTS*)data;
    //int i;
    // printk( KERN_INFO "FSM SIOCTL,%u \n",fscts->opcode );

    switch(data[0]) {
    case RegDevice:
        FSM_Statstic_SetStatus(to_dt, "ok");
        break;
    case SendCmdToServer: ///< Отправка команды серверу
        break;
    case PacketFromUserSpace: ///< Отправка команды серверу
        switch(fscts->cmd) 
        {
        }
        break;

     
    }
}

static int __init FSMFlash_init(void)
{
    struct FSM_DeviceRegistr regp;
    FSMStCTL_dft.aplayp = 0;
    FSMStCTL_dft.type = (unsigned char)StatisticandConfig;
    FSMStCTL_dft.VidDevice = (unsigned char)FSMDeviceStatistic;
    FSMStCTL_dft.PodVidDevice = (unsigned char)FSM_Statistic;
    FSMStCTL_dft.KodDevice = (unsigned char)CTL_FSM_Statistic;
    FSMStCTL_dft.Proc = FSM_FSMStCTLRecive;
    FSMStCTL_dft.config_len = 0;
    FSM_DeviceClassRegister(FSMStCTL_dft);

    regp.IDDevice = FSM_StatisticCTL;
    regp.VidDevice = FSMStCTL_dft.VidDevice;
    regp.PodVidDevice = FSMStCTL_dft.PodVidDevice;
    regp.KodDevice = FSMStCTL_dft.KodDevice;
    regp.type = FSMStCTL_dft.type;
    regp.opcode = RegDevice;
    regp.CRC = 0;
    FSM_DeviceRegister(regp);
    printk(KERN_INFO "FSM Statistic CTL loaded\n");
    return 0;
}
static void __exit FSMFlash_exit(void)
{
    FSM_ClassDeRegister(FSMStCTL_dft);
    printk(KERN_INFO "FSM Statistic CTL module unloaded\n");
}
module_init(FSMFlash_init);
module_exit(FSMFlash_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Statistic CTL Module");
MODULE_LICENSE("GPL");