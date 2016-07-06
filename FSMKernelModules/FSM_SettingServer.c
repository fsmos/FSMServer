/*!
\file
\brief Модуль сервер настроек 
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/

#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMAudio/FSM_AudioStream.h"
#include <FSM/FSMEthernet/FSMEthernetHeader.h> 
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSMDevice/fsm_statusstruct.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSM_Client/FSM_client.h"

struct FSM_SendCmd scmdt;
struct fsm_Setting_Setting fsmSSS;


void FSM_SettingRecive(char* data,short len,  struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
    struct fsm_devices_config* fsmset;
    struct FSM_DeviceTree* fsdt;
    int i,j;
    short hlen;
  //  unsigned short tmp;
    struct FSM_SendCmdTS* fscts= (struct FSM_SendCmdTS*)data;    
    

    switch(data[0])
    {
         case RegDevice:
            FSM_Statstic_SetStatus(to_dt,"ok");
            to_dt->config=&fsmSSS;
            fsmSSS.fsmcs.id=to_dt->IDDevice;
         break;
         case SendCmdToServer: ///< Отправка команды серверу
         fsmset=FSM_GetSetting();
         switch(fscts->cmd)
         {
         //printk( KERN_INFO "FSM Cmd %u\n",fscts->cmd); 
          case GetSet:
          hlen=sizeof(struct FSM_SendCmd)-sizeof(scmdt.Data)+sizeof(struct fsm_device_config);
          scmdt.cmd=AnsGetSet;
          scmdt.countparam=1;
          scmdt.IDDevice=fscts->IDDevice;
          scmdt.CRC=0;
          scmdt.opcode=SendCmdToDevice;
          
          for(i=0;i<srow_cnt;i++)
           {
               for(j=0;j<scolumn_cnt;j++)
               {
                   if(fsmset->setel[i][j].IDDevice!=0)
                   {
                   memcpy(scmdt.Data,&fsmset->setel[i][j],sizeof(struct fsm_device_config));
                   from_dt->dt->Proc((char*)&scmdt,hlen,from_dt,to_dt);
                      //printk( KERN_INFO "FSM Send %u %s\n",fsmstate->statel[i][j].devid,fsmstate->statel[i][j].fsmdevcode);
                   }

               }
           }
           break;
           case SetSetting:
          //  printk( KERN_INFO "FSM_Setting_Applay\n" ); 
           FSM_Setting_Applay(FSM_FindDevice(((struct fsm_device_config*)fscts->Data)->IDDevice),((struct fsm_device_config*)fscts->Data)->config);
           break;
        
         }
    break;
    }
     
}
void ApplaySetting(struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
     
    // printk( KERN_INFO "FSM_Set\n" ); 
      scmdt.cmd=SetSettingClient;
          scmdt.countparam=1;
          scmdt.IDDevice=to_dt->IDDevice;
          scmdt.CRC=0;
          scmdt.opcode=SendCmdToDevice;
          memcpy(&scmdt.Data,&fsmSSS.fsmcs,sizeof(struct fsm_Setting_Setting ));
          from_dt->dt->Proc((char*)&scmdt,sizeof(struct FSM_SendCmd),from_dt,to_dt);
}
struct FSM_DeviceFunctionTree dft;
static int __init FSM_Setting_Server_init(void)
{
   dft.type=(unsigned char)StatisticandConfig;
   dft.VidDevice=(unsigned char)FSMDeviceConfig;
   dft.PodVidDevice=(unsigned char)ComputerStatistic;
   dft.KodDevice=(unsigned char)PCx86;
   dft.Proc=FSM_SettingRecive;
   dft.config_len=sizeof(struct fsm_Setting_Setting);
   dft.aplayp=ApplaySetting;
   FSM_DeviceClassRegister(dft);
   printk( KERN_INFO "FSM Setting Server loaded\n" ); 
   return 0;  
}

static void __exit FSM_Setting_Server_exit(void)
{
   printk( KERN_INFO "FSM  Setting Server unloaded\n" );  
}

module_init(FSM_Setting_Server_init);
module_exit(FSM_Setting_Server_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Setting Server Module");
MODULE_LICENSE("GPL");