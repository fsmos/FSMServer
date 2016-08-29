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


struct CCKDeviceInfo CCKDevE;
struct FSM_DeviceFunctionTree dft;
struct FSM_PO07Device FSMPO07Dev[FSM_PO06DeviceTreeSize];
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

void FSM_PO07SendStreaminfo(unsigned short id, struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
    short plen;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_ssi_init);
#endif

    memset(&sendcmd,0,sizeof(struct FSM_SendCmd));
    sendcmd.opcode=SendCmdToDevice;
    sendcmd.IDDevice=from_dt->IDDevice;
    sendcmd.cmd=FSMPO07SendStream;
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

void FSM_PO07Recive(char* data,short len,  struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
    int i;
    
    struct FSM_SendCmdTS* scmd=(struct FSM_SendCmdTS*)data;
   // struct FSM_SendMessage* sctt=(struct FSM_SendMessage*)data;
        // char datas[2];
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_por_init);
#endif
    
    switch(data[0])
      {
                        
        case RegDevice: ///< Регистрация устройства
        FSM_Statstic_SetStatus(to_dt,"ok");
        for(i=0;i<FSM_PO07DeviceTreeSize;i++)
          {
              if(FSMPO07Dev[i].iddev==to_dt->IDDevice)
              {
                 FSM_PO07SendStreaminfo(FSMPO07Dev[i].idstream,from_dt,to_dt);
                 return; 
              }
          }
          for(i=0;i<FSM_PO07DeviceTreeSize;i++)
          {
          if(FSMPO07Dev[i].reg==0)
          {
             FSMPO07Dev[i].reg=1;
             FSMPO07Dev[i].ethdev=FSM_FindEthernetDevice(to_dt->IDDevice);
             fsmas.iddev=to_dt->IDDevice;
             //fsmas.ToProcess=FSM_PO06RecivePacket;
             //fsmas.ToUser=FSM_E1SendPacket;
             fsmas.TransportDevice= FSMPO07Dev[i].ethdev->numdev;
             fsmas.TransportDeviceType=FSM_EthernetID2;
             fsmas.Data=&FSMPO07Dev[i];
             FSMPO07Dev[i].idstream=FSM_AudioStreamRegistr(fsmas);
             FSMPO07Dev[i].iddev=to_dt->IDDevice;
             to_dt->data=&FSMPO07Dev[i];
             to_dt->config=&FSMPO07Dev[i].po07set;
             FSM_PO07SendStreaminfo(FSMPO07Dev[i].idstream,from_dt,to_dt);
             if(to_dt->debug) printk( KERN_INFO "FSM PO07 Device Added %u \n",to_dt->IDDevice); ;
             
             
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
          if((FSMPO07Dev[i].reg==1)&&( FSMPO07Dev[i].iddev==to_dt->IDDevice))
          {
          
             FSM_AudioStreamUnRegistr(FSMPO07Dev[i].idstream);
             FSMPO07Dev[i].reg=0;
             if(to_dt->debug) printk( KERN_INFO "FSM PO07 Device Deleted %u \n",to_dt->IDDevice); 
             break;
          }
          }
          break;
          case AnsPing:///< Пинг
          break;
          case SendCmdToServer: ///< Отправка команды серверу
          switch(scmd->cmd)
          {
              case FSMPO07ConnectToDevE1:
             // ((struct FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idcon=FSM_P2P_Connect(((struct FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idstream, ((struct FSM_E1Device*)(FSM_FindDevice(((struct FSMPO06CommCons*)scmd->Data)->id)->data))->streams_id[((struct FSMPO06CommCons*)scmd->Data)->channel]);
              break;
              case FSMPO07DisConnectToDevE1:
              FSM_P2P_Disconnect(((struct FSM_PO06Device*)(to_dt->data))->idcon);
              break;
              case AnsGetSettingClientPO07:
              if(to_dt->debug) printk( KERN_INFO "FSM_Set Recv %i\n",scmd->IDDevice);
              memcpy(&((struct fsm_po07_setting*)(to_dt->config))->fsm_p007_su_s,scmd->Data,to_dt->dt->config_len);
              break;
              case FSMPo07SendIP:
              CCKDevE.id=scmd->IDDevice;
              CCKDevE.ip[0]=scmd->Data[0];
              CCKDevE.ip[1]=scmd->Data[1];
              CCKDevE.ip[2]=scmd->Data[2];
              CCKDevE.ip[3]=scmd->Data[3];
              CCKDevE.type=PO07;
              CCKDevE.Position=scmd->Data[4];
              FSMCCK_AddDeviceInfo(&CCKDevE);
              if(to_dt->debug) printk( KERN_INFO "FSM PO07 ID%i Asterisk IP %i.%i.%i.%i\n ",scmd->IDDevice, scmd->Data[0],scmd->Data[1],scmd->Data[2],scmd->Data[3]);
              break;
          }
          
           break;
          case SendTxtMassage: ///< Отправка текстового сообщения
           //printk( KERN_INFO "%s",sctt->Data );
           
           break;
          case PacketFromUserSpace:
          switch(scmd->cmd)
          {
          case FSMPo07AudioRun:
          case FSMPo07Reset:
          case FSMPo07Reregister:
          scmd->IDDevice=to_dt->IDDevice;
          scmd->opcode=SendCmdToDevice;
          to_dt->TrDev->dt->Proc((char*)scmd,FSMH_Header_Size_SendCmd, to_dt->TrDev, to_dt);
          break;
          case FSMPo07GetCRC:
          
          break;
          }
          break;
          case Alern: ///<Тревога
          switch(((struct FSM_AlernSignal*)data)->ID)
          {
              
          }
          break;
          case Warning: ///<Предупреждение
          switch(((struct FSM_WarningSignal*)data)->ID)
          {
               case FSM_CCK_Server_Connect_Error:
              printk( KERN_WARNING "PO07 %u: Server Not Connect \n",((struct FSM_Header*)(data))->IDDevice); 
              break;
          }
          break;
          case Trouble: ///<Сбой
          switch(((struct FSM_TroubleSignal*)data)->ID)
          {
              case FSM_CCK_Memory_Test_Filed:
              printk( KERN_ERR "PO07 %u: Memory Error \n",((struct FSM_Header*)(data))->IDDevice); 
              break;
          }
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
EXPORT_SYMBOL(FSM_PO07Recive);
void ApplaySettingPO07(struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_asp6_init);
#endif

    memset(&sendcmd,0,sizeof(sendcmd));
    printk( KERN_INFO "FSM_Set\n" ); 
    sendcmd.cmd=SetSettingClientPO07;
    sendcmd.countparam=1;
    sendcmd.IDDevice=to_dt->IDDevice;
    sendcmd.CRC=0;
    sendcmd.opcode=SendCmdToDevice;
    memcpy(&sendcmd.Data,&(((struct FSM_PO07Device*)to_dt->data)->po07set.fsm_p007_su_s),sizeof(struct fsm_po07_subscriber));
    from_dt->dt->Proc((char*)&sendcmd,sizeof(struct FSM_SendCmd)-sizeof(sendcmd.Data)+sizeof(struct fsm_po07_subscriber),from_dt,to_dt);

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_asp6_exit);
#endif
}

static int __init FSM_PO07_init(void)
{
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(init_on);
#endif

   dft.aplayp=ApplaySettingPO07;
   dft.type=(unsigned char)AudioDevice;
   dft.VidDevice=(unsigned char)CommunicationDevice;
   dft.PodVidDevice=(unsigned char)CCK;
   dft.KodDevice=(unsigned char)PO07;
   dft.Proc=FSM_PO07Recive;
   dft.config_len=sizeof(struct fsm_po07_setting);
   FSM_DeviceClassRegister(dft);
   printk( KERN_INFO "FSM PO07 Module loaded\n" ); 
   FSM_SendEventToAllDev(FSM_CCK_MN845_Started);
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(init_off);
#endif

 return 0;  
}

static void __exit FSM_PO07_exit(void)
{
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(exit_on);
#endif

   FSM_ClassDeRegister(dft);  
   printk( KERN_INFO "FSM PO07 Module unloaded\n" );
   

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(exit_off);
#endif
}

module_init(FSM_PO07_init);
module_exit(FSM_PO07_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM PO07 Module");
MODULE_LICENSE("GPL");