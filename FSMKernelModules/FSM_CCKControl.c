#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_DeviceFunctionTree dft;
struct CCKDeviceInfo CCKDev[FSM_CCKTreeSize];

void FSM_CCKControlDeviceRecive(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    // struct fsm_devices_config* fsmset;
    //   struct FSM_DeviceTree* fsdt;
    //  int i,j;
    // short hlen;
    //  unsigned short tmp;
    struct FSM_SendCmdTS* fscts = (struct FSM_SendCmdTS*)data;
    // printk( KERN_INFO "FSM SIOCTL,%u \n",fscts->opcode );

    switch(data[0]) {
    case RegDevice:
        FSM_Statstic_SetStatus(to_dt, "ok");
        break;
    case SendCmdToServer: ///< Отправка команды серверу
        switch(fscts->cmd) {
        }
        break;
    case PacketFromUserSpace: ///< Отправка команды серверу
        switch(fscts->cmd) {
        case FSM_CCKGetInfo:
            memcpy(fscts->Data, &CCKDev, sizeof(CCKDev));
            // printk( KERN_INFO "FSM CCK RC\n" );
            break;
        }
        break;
    }
}

void FSMCCK_AddDeviceInfo(struct CCKDeviceInfo* CCK)
{
    int i;
    for(i = 0; i < FSM_CCKTreeSize; i++) {
        if((CCKDev[i].id == CCK->id) && (CCKDev[i].reg == 1)) {
            CCKDev[i].ip[0] = CCK->ip[0];
            CCKDev[i].ip[1] = CCK->ip[1];
            CCKDev[i].ip[2] = CCK->ip[2];
            CCKDev[i].ip[3] = CCK->ip[3];
            CCKDev[i].Position = CCK->Position;
            CCKDev[i].type = CCK->type;
            CCKDev[i].crc32 = CCK->crc32;
            CCKDev[i].ramstate = CCK->ramstate;
            CCKDev[i].dstlen = CCK->dstlen;
            return;
        }
    }
    for(i = 0; i < FSM_CCKTreeSize; i++) {
        if(CCKDev[i].reg == 0) {
            CCKDev[i].reg = 1;
            CCKDev[i].n = i;
            CCKDev[i].id = CCK->id;
            CCKDev[i].ip[0] = CCK->ip[0];
            CCKDev[i].ip[1] = CCK->ip[1];
            CCKDev[i].ip[2] = CCK->ip[2];
            CCKDev[i].ip[3] = CCK->ip[3];
            CCKDev[i].Position = CCK->Position;
            CCKDev[i].type = CCK->type;
            CCKDev[i].crc32 = CCK->crc32;
            CCKDev[i].ramstate = CCK->ramstate;
            CCKDev[i].dstlen = CCK->dstlen;
            // printk( KERN_INFO "FSM CCK Device Added\n" );
            return;
        }
    }
}
EXPORT_SYMBOL(FSMCCK_AddDeviceInfo);

static int __init FSMCCKControlDevice_init(void)
{
    struct FSM_DeviceRegistr regp;
    dft.aplayp = 0;
    dft.type = (unsigned char)AudioDevice;
    dft.VidDevice = (unsigned char)CommunicationDevice;
    dft.PodVidDevice = (unsigned char)ControlCCK;
    dft.KodDevice = (unsigned char)ControlCCKServer;
    dft.Proc = FSM_CCKControlDeviceRecive;
    dft.config_len = 0;
    FSM_DeviceClassRegister(dft);

    regp.IDDevice = FSM_CCKControlID;
    regp.VidDevice = dft.VidDevice;
    regp.PodVidDevice = dft.PodVidDevice;
    regp.KodDevice = dft.KodDevice;
    regp.type = dft.type;
    regp.opcode = RegDevice;
    regp.CRC = 0;
    FSM_DeviceRegister(regp);
    printk(KERN_INFO "FSM CCK ControlDevice loaded\n");
    return 0;
}
static void __exit FSMCCKControlDevice_exit(void)
{
    FSM_ClassDeRegister(dft);
    printk(KERN_INFO "FSM CCK ControlDevice module unloaded\n");
}

module_init(FSMCCKControlDevice_init);
module_exit(FSMCCKControlDevice_exit);