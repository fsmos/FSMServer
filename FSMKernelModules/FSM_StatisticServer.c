/*!
\file
\brief Модуль сервер статистики
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

struct FSM_SendCmd scmdt;


void FSM_StatisticRecive(char* data,short len, struct FSM_DeviceTree* fsmdt)
{
   
    struct fsm_statusstruct* fsmstate;
    struct FSM_DeviceTree* fsdt;
    int i,j;
    short hlen;
    struct FSM_SendCmdTS* fscts= (struct FSM_SendCmdTS*)data;    
    

    switch(data[0])
    {
         case RegDevice:
            FSM_Statstic_SetStatus(fsmdt,"ok");
         break;
         case SendCmdToServer: ///< Отправка команды серверу
         fsmstate=FSM_GetStatistic();
         fsdt= FSM_FindDevice(fscts->IDDevice);
         switch(fscts->cmd)
         {
         //printk( KERN_INFO "FSM Cmd %u\n",fscts->cmd); 
          case GetStatistic:
          hlen=sizeof(struct FSM_SendCmd)-sizeof(scmdt.Data)+sizeof(struct fsm_status_element);
          scmdt.cmd=AnsGetStatistic;
          scmdt.countparam=1;
          scmdt.IDDevice=fscts->IDDevice;
          scmdt.CRC=0;
          scmdt.opcode=SendCmdToDevice;
          
          for(i=0;i<srow_cnt;i++)
           {
               for(j=0;j<scolumn_cnt;j++)
               {
                   if(fsmstate->statel[i][j].devid!=0)
                   {
                   memcpy(scmdt.Data,&fsmstate->statel[i][j],sizeof(struct fsm_status_element));
                   fsmdt->dt->Proc((char*)&scmdt,hlen,fsdt);
                      //printk( KERN_INFO "FSM Send %u %s\n",fsmstate->statel[i][j].devid,fsmstate->statel[i][j].fsmdevcode);
                   }

               }
           }
           memset(scmdt.Data,0,sizeof(struct fsm_status_element));
           scmdt.cmd=SendSettingFull;
           fsmdt->dt->Proc((char*)&scmdt,hlen,fsdt);
           break;
        
         }
    break;
    }
     
}
struct FSM_DeviceFunctionTree dft;
static int __init FSM_Statistic_Server_init(void)
{
   dft.type=(unsigned char)StatisticandConfig;
   dft.VidDevice=(unsigned char)FSMDeviceStatistic;
   dft.PodVidDevice=(unsigned char)ComputerStatistic;
   dft.KodDevice=(unsigned char)PCx86;
   dft.Proc=FSM_StatisticRecive;
   dft.config_len=0;
   FSM_DeviceClassRegister(dft);
   printk( KERN_INFO "FSM Statistic Server loaded\n" ); 
   return 0;  
}

static void __exit FSM_Statistic_Server_exit(void)
{
   printk( KERN_INFO "FSM  Statistic Server unloaded\n" );  
}

module_init(FSM_Statistic_Server_init);
module_exit(FSM_Statistic_Server_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Statistic Server Module");
MODULE_LICENSE("GPL");