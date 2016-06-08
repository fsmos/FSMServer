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

#ifdef  DEBUG_CALL_STACK 
uint64_t debug_this7;
extern uint64_t debug_global;
#define DEBUG_CALL_STACK_SetStack debug_this7=(debug_this7<<8) 
#define DEBUG_CALL_STACK_THIS 7
#define DEBUG_CALL_STACK_GLOBSET debug_global =(debug_global<<8)|(DEBUG_CALL_STACK_THIS);

typedef enum debug_function
{
    init_on=0x00,
    init_off=0x01,
    exit_on=0x02,
    exit_off=0x03,
    get_fp2p_init=0x04,
    get_fp2p_exit=0x05,
    get_cmp_init=0x06,
    get_cmp_exit=0x07,
    get_dc_init=0x08,
    get_dc_exit=0x09,
    
}debug_fun ;
#endif 

unsigned short  FSM_P2P_Connect(unsigned short id1,unsigned short id2)
{
    int i=0;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_fp2p_init);
#endif

    
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
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_fp2p_exit);
#endif

    return 0xffff;
}
EXPORT_SYMBOL(FSM_P2P_Connect);
void FSM_P2P_Disconnect(unsigned short idcon)
{
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_dc_init);
#endif

    fsmabon[idcon].reg=0;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_dc_exit);
#endif
    

}
EXPORT_SYMBOL(FSM_P2P_Disconnect);
void  FSM_Commutator_Process(char* data,short len)
{
  struct FSM_SendAudioData * FSMAPk=(struct FSM_SendAudioData * )data;
  unsigned short idcon;

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_cmp_init);
#endif
  
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
  
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_cmp_exit);
#endif
   
  //fsmabon[idcon].idcon
}
EXPORT_SYMBOL(FSM_Commutator_Process);

static int __init FSM_Commutator_init(void)
{
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(init_on);
#endif

   printk( KERN_INFO "FSM Commutator Module loaded\n" ); 
   return 0;  
   
  
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(init_off);
#endif

}

static void __exit FSM_Commutator_exit(void)
{

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(exit_on);
#endif

   printk( KERN_INFO "FSM Commutator Module unloaded\n" );  
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(exit_off);
#endif

}

module_init(FSM_Commutator_init);
module_exit(FSM_Commutator_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Commutator Module");
MODULE_LICENSE("GPL");