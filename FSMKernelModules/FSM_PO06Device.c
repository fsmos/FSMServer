/*!
\file
\brief Модуль взаимодествия с пультом ПО-06
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

#include "FSM/FSMDevice/FSM_DeviceProcess.h"


struct FSM_DeviceFunctionTree dft;
struct FSM_PO06Device FSMPO06Dev[FSM_PO06DeviceTreeSize];
struct FSM_SendCmd sendcmd;
 struct FSM_AudioStream fsmas;
 
#ifdef  DEBUG_CALL_STACK 
uint64_t debug_this5;
extern uint64_t debug_global;
#define DEBUG_CALL_STACK_SetStack debug_this5=(debug_this5<<8) 
#define DEBUG_CALL_STACK_THIS 5
#define DEBUG_CALL_STACK_GLOBSET debug_global =(debug_global<<8)|(DEBUG_CALL_STACK_THIS);

typedef enum debug_function
{
    init_on=0x00,
    init_off=0x01,
    exit_on=0x02,
    exit_off=0x03,
    get_ssi_init=0x04,
    get_ssi_exit=0x05,
    get_por_init=0x06,
    get_por_exit=0x07,
    get_asp6_init=0x08,
    get_asp6_exit=0x09,
    
}debug_fun ;
#endif 

void FSM_PO06SendStreaminfo(unsigned short id,struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
    short plen;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_ssi_init);
#endif

    memset(&sendcmd,0,sizeof(struct FSM_SendCmd));
    sendcmd.opcode=SendCmdToDevice;
    sendcmd.IDDevice=from_dt->IDDevice;
    sendcmd.cmd=FSMPO06SendStream;
    sendcmd.countparam=1;
    ((unsigned short*)sendcmd.Data)[0]=id;
    if(to_dt->debug) printk( KERN_INFO "FSM Send %u ,%u \n",sendcmd.Data[0],sendcmd.Data[1]); 
    sendcmd.CRC=0;
    plen=sizeof(struct FSM_SendCmd)-sizeof(sendcmd.Data)+2;
   if(to_dt!=0)  to_dt->dt->Proc((char*)&sendcmd,plen,to_dt,from_dt);
  
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_ssi_exit);
#endif
              
}

void FSM_PO06Recive(char* data,short len, struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
    int i;
   
    struct FSM_SendCmdTS* scmd=(struct FSM_SendCmdTS*)data;
        // char datas[2];
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_por_init);
#endif
    
    switch(data[0])
      {
                        
        case RegDevice: ///< Регистрация устройства
        FSM_Statstic_SetStatus(to_dt,"ok");
        for(i=0;i<FSM_PO06DeviceTreeSize;i++)
          {
              if(FSMPO06Dev[i].iddev==to_dt->IDDevice)
              {
                 FSM_PO06SendStreaminfo(FSMPO06Dev[i].idstream,from_dt,to_dt);
                 return; 
              }
          }
          for(i=0;i<FSM_PO06DeviceTreeSize;i++)
          {
          if(FSMPO06Dev[i].reg==0)
          {
             FSMPO06Dev[i].reg=1;
             FSMPO06Dev[i].ethdev=FSM_FindEthernetDevice(to_dt->IDDevice);
             fsmas.iddev=to_dt->IDDevice;
             //fsmas.ToProcess=FSM_PO06RecivePacket;
             //fsmas.ToUser=FSM_E1SendPacket;
             fsmas.TransportDevice= FSMPO06Dev[i].ethdev->numdev;
             fsmas.TransportDeviceType=FSM_EthernetID2;
             fsmas.Data=&FSMPO06Dev[i];
             FSMPO06Dev[i].idstream=FSM_AudioStreamRegistr(fsmas);
             FSMPO06Dev[i].iddev=to_dt->IDDevice;
             to_dt->data=&FSMPO06Dev[i];
             to_dt->config=&FSMPO06Dev[i].po06set;
             FSM_PO06SendStreaminfo(FSMPO06Dev[i].idstream,from_dt,to_dt);
             printk( KERN_INFO "FSMPO06 Device Added %u \n",to_dt->IDDevice); 
             
             FSM_P2P_Connect(FSMPO06Dev[i].idstream, 2);
             
             
   //datas[0]=0xd0;
   //datas[1]=0xd1;
   //FSM_AudioStreamToUser(0,datas,2); 
             break;
          }
           
          
          }
          break;
          case DelLisr:
          for(i=0;i<FSM_E1DeviceTreeSize;i++)
          {
          if((FSMPO06Dev[i].reg==1)&&( FSMPO06Dev[i].iddev==to_dt->IDDevice))
          {
          
             FSM_AudioStreamUnRegistr(FSMPO06Dev[i].idstream);
             FSMPO06Dev[i].reg=0;
           if(to_dt->debug) printk( KERN_INFO "FSMPO06 Device Deleted %u \n",to_dt->IDDevice); 
             break;
          }
          }
          break;
          case AnsPing:///< Пинг
          break;
          case SendCmdToServer: ///< Отправка команды серверу
          switch(scmd->cmd)
          {
              case FSMPO06ConnectToDevE1:
             // ((struct FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idcon=FSM_P2P_Connect(((struct FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idstream, ((struct FSM_E1Device*)(FSM_FindDevice(((struct FSMPO06CommCons*)scmd->Data)->id)->data))->streams_id[((struct FSMPO06CommCons*)scmd->Data)->channel]);
              break;
              case FSMPO06DisConnectToDevE1:
              FSM_P2P_Disconnect(((struct FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idcon);
              break;
              case AnsGetSettingClientPo06:
           if(to_dt->debug)   printk( KERN_INFO "FSM_Set Recv %i\n",scmd->IDDevice);
              memcpy(&((struct fsm_po06_setting*)(FSM_FindDevice(scmd->IDDevice)->config))->fsm_p006_su_s,scmd->Data,FSM_FindDevice(scmd->IDDevice)->dt->config_len);
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
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_por_exit);
#endif

    if(to_dt->debug) printk( KERN_INFO "RPack %u \n" ,len); 
}
EXPORT_SYMBOL(FSM_PO06Recive);
void ApplaySettingPO06(struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_asp6_init);
#endif

    memset(&sendcmd,0,sizeof(sendcmd));
    if(to_dt->debug) printk( KERN_INFO "FSM_Set\n" ); 
    sendcmd.cmd=SetSettingClientPo06;
    sendcmd.countparam=1;
    sendcmd.IDDevice=to_dt->IDDevice;
    sendcmd.CRC=0;
    sendcmd.opcode=SendCmdToDevice;
    memcpy(&sendcmd.Data,&(((struct FSM_PO06Device*)to_dt->data)->po06set.fsm_p006_su_s),sizeof(struct fsm_po06_subscriber));
    from_dt->dt->Proc((char*)&sendcmd,sizeof(struct FSM_SendCmd)-sizeof(sendcmd.Data)+sizeof(struct fsm_po06_subscriber),from_dt,to_dt);

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_asp6_exit);
#endif
}

static int __init FSM_PO06_init(void)
{
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(init_on);
#endif

   dft.aplayp=ApplaySettingPO06;
   dft.type=(unsigned char)AudioDevice;
   dft.VidDevice=(unsigned char)CommunicationDevice;
   dft.PodVidDevice=(unsigned char)CCK;
   dft.KodDevice=(unsigned char)PO06;
   dft.Proc=FSM_PO06Recive;
   dft.config_len=sizeof(struct fsm_po06_setting);
   FSM_DeviceClassRegister(dft);
   printk( KERN_INFO "FSM PO06 Module loaded\n" ); 
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(init_off);
#endif

   return 0;  
}

static void __exit FSM_PO06_exit(void)
{
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(exit_on);
#endif

   FSM_ClassDeRegister(dft);  
   printk( KERN_INFO "FSM PO06 Module unloaded\n" );
   

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(exit_off);
#endif
}

module_init(FSM_PO06_init);
module_exit(FSM_PO06_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM PO06 Module");
MODULE_LICENSE("GPL");