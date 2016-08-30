#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_DeviceFunctionTree dft;
struct SettingTreeInfo FSMDevSetTree[FSM_DeviceSettingTreeSize];
struct FSM_GetTreeList fsmgetts;
void FSM_SendReuestDevTree(struct FSM_DeviceTree* to_dt)
{
    fsmgetts.CRC=0;
    fsmgetts.IDDevice=to_dt->IDDevice;
    fsmgetts.opcode=FSM_Setting_GetTree;
    to_dt->TrDev->dt->Proc((char*)&fsmgetts,FSMH_Header_Size_GetTreeList, to_dt->TrDev, to_dt);
}
EXPORT_SYMBOL(FSM_SendReuestDevTree); 

void FSM_SetTreeAdd(struct FSM_DeviceTree* to_dt)
{
    int i=0;
    for(i=0;i<FSM_DeviceSettingTreeSize;i++)
    {
        if((FSMDevSetTree[i].id==to_dt->IDDevice)&&(FSMDevSetTree[i].reg==1))
        {
            FSM_SendReuestDevTree(to_dt);
            return;
        }
    }
    for(i=0;i<FSM_DeviceSettingTreeSize;i++)
    {
        if(FSMDevSetTree[i].reg==0)
        {
            FSMDevSetTree[i].id=to_dt->IDDevice;
            FSMDevSetTree[i].reg=1;
            FSMDevSetTree[i].dt=to_dt;
            FSM_SendReuestDevTree(to_dt);
            return;
        }
    }
}
EXPORT_SYMBOL(FSM_SetTreeAdd);
 
void FSM_TreeRecive(char* data,short len,  struct FSM_DeviceTree* to_dt)
{
    int i;
    switch(data[0])
    {
    case Ans_FSM_Setting_GetTree:
    for(i=0;i<FSM_DeviceSettingTreeSize;i++)
    {
        if((FSMDevSetTree[i].id==to_dt->IDDevice)&&(FSMDevSetTree[i].reg==1))
        {
            FSMDevSetTree[i].type=(char)(((struct FSM_AnsGetTreeList*)data)->size);
            memcpy(FSMDevSetTree[i].fsmdtl,((struct FSM_AnsGetTreeList*)data)->Data, FSMDevSetTree[i].type*sizeof(struct FSM_SetTreeElementFS));
            return;
        }
    }
    break;
    }
}
EXPORT_SYMBOL(FSM_TreeRecive);  


void FSM_SettingTreeControlDeviceRecive(char* data,short len,  struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{

    struct FSM_SendCmdTS* fscts= (struct FSM_SendCmdTS*)data;  
    int i;  
   // printk( KERN_INFO "FSM SIOCTL,%u \n",fscts->opcode ); 

    switch(data[0])
    {
    case RegDevice:
        FSM_Statstic_SetStatus(to_dt,"ok");
    break;
    case SendCmdToServer: ///< Отправка команды серверу
    break;
    case PacketFromUserSpace: ///< Отправка команды серверу
        switch(fscts->cmd)
        {
            case FSM_DevTreeSetGet:
            for(i=0;i<FSM_DeviceSettingTreeSize;i++)
            {
            if((FSMDevSetTree[i].id==to_dt->IDDevice)&&(FSMDevSetTree[i].reg==1))
            {
            fscts->countparam=FSMDevSetTree[i].type;
            memcpy(fscts->Data,FSMDevSetTree[i].fsmdtl, FSMDevSetTree[i].type*sizeof(struct FSM_SetTreeElementFS));
            return;
            }
            }
            break;
        }
    break;
    }
}


static int __init FSMCCKControlDevice_init(void)
{
   struct FSM_DeviceRegistr regp;
   dft.aplayp=0;
   dft.type=(unsigned char)StatisticandConfig;
   dft.VidDevice=(unsigned char)FSMDeviceConfig;
   dft.PodVidDevice=(unsigned char)FSM_SettingTree_D;
   dft.KodDevice=(unsigned char)CTL_FSM_SettingTree_D;
   dft.Proc=FSM_SettingTreeControlDeviceRecive;
   dft.config_len=0;
   FSM_DeviceClassRegister(dft);
   
   
   regp.IDDevice=FSM_TreeSettingID;
   regp.VidDevice=dft.VidDevice;
   regp.PodVidDevice= dft.PodVidDevice;
   regp.KodDevice=dft.KodDevice;
   regp.type=dft.type;
   regp.opcode=RegDevice;
   regp.CRC=0;
   FSM_DeviceRegister(regp);
   printk( KERN_INFO "FSM CCK ControlDevice loaded\n" ); 
   return 0;  
}
static void __exit FSMCCKControlDevice_exit(void)
{  
   FSM_ClassDeRegister(dft);
   printk( KERN_INFO "FSM CCK ControlDevice module unloaded\n" );
}

module_init(FSMCCKControlDevice_init);
module_exit(FSMCCKControlDevice_exit);