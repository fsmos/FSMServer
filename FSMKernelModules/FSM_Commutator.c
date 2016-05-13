/*!
\file
\brief Модуль коммутатор
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSMAudio/FSM_AudioStream.h"
#include "FSM/FSMEthernet/FSMEthernetHeader.h"
#include "FSM/FSM_Commutator/FSM_Commutator.h"

struct FSM_P2P_abonent fsmabon[FSM_P2P_abonent_count];

unsigned short  FSM_P2P_Connect(unsigned short id1,unsigned short id2)
{
    int i=0;
    for(i=0;i<FSM_P2P_abonent_count;i++)
    {
       if(fsmabon[i].reg==0)
       {
           fsmabon[i].reg=1;
           fsmabon[i].idstream1=id1;
           fsmabon[i].idstream2=id2;
           fsmabon[i].idcon=i;
           FSM_AudioStreamSetIDConnect(id1,i,p2p);
           FSM_AudioStreamSetToProcess(id1,FSM_Commutator_Process);
           FSM_AudioStreamSetIDConnect(id2,i,p2p);
           FSM_AudioStreamSetToProcess(id2,FSM_Commutator_Process);
           return i;
       }
    }
    return 0xffff;
}
EXPORT_SYMBOL(FSM_P2P_Connect);
void FSM_P2P_Disconnect(unsigned short idcon)
{
    fsmabon[idcon].reg=0;
}
EXPORT_SYMBOL(FSM_P2P_Disconnect);
void  FSM_Commutator_Process(char* data,short len)
{
  struct FSM_SendAudioData * FSMAPk=(struct FSM_SendAudioData * )data;
  unsigned short idcon;
  idcon=FSM_AudioStreamGETIDConnect(FSMAPk->IDDevice);
  if(idcon==0xffff) return;
  //printk( KERN_INFO "FSM IDCon %i \n",idcon ); 
  switch(FSM_AudioStreamGETTypeConnect(FSMAPk->IDDevice))
  {
      case p2p:
      if(FSMAPk->IDDevice==fsmabon[idcon].idstream1)
      {
         FSMAPk->IDDevice=fsmabon[idcon].idstream2;
        FSM_AudioStreamToUser(fsmabon[idcon].idstream2,data,sizeof(struct FSM_SendAudioData)-sizeof(FSMAPk->Data)+FSMAPk->len); 
      }
      else
      {
          FSMAPk->IDDevice=fsmabon[idcon].idstream1;
          FSM_AudioStreamToUser(fsmabon[idcon].idstream1,(char*)FSMAPk,sizeof(struct FSM_SendAudioData)-sizeof(FSMAPk->Data)+FSMAPk->len); 
      }
      break;
  }
   
  //fsmabon[idcon].idcon
}
EXPORT_SYMBOL(FSM_Commutator_Process);

static int __init FSM_Commutator_init(void)
{
   printk( KERN_INFO "FSM Commutator Module loaded\n" ); 
   return 0;  
}

static void __exit FSM_Commutator_exit(void)
{
   printk( KERN_INFO "FSM Commutator Module unloaded\n" );  
}

module_init(FSM_Commutator_init);
module_exit(FSM_Commutator_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Commutator Module");
MODULE_LICENSE("GPL");