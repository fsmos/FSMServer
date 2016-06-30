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
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSMAudio/FSM_AudioStream.h"
#include "FSM/FSM_Commutator/FSM_Commutator.h"
#include <FSM/FSMEthernet/FSMEthernetHeader.h> 


struct FSM_DeviceFunctionTree dft;
struct FSM_DeviceTree* FSMMN825Ethernet;
struct FSM_MN825Device FSMMN825Dev[FSM_PO06DeviceTreeSize];
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

void FSM_MN825SendStreaminfo(unsigned short id,struct FSM_DeviceTree* fsmdt)
{
    short plen;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_ssi_init);
#endif

    memset(&sendcmd,0,sizeof(struct FSM_SendCmd));
    sendcmd.opcode=SendCmdToDevice;
    sendcmd.IDDevice=fsmdt->IDDevice;
    sendcmd.cmd=FSMPO06SendStream;
    sendcmd.countparam=1;
    ((unsigned short*)sendcmd.Data)[0]=id;
    printk( KERN_INFO "FSM Send %u ,%u \n",sendcmd.Data[0],sendcmd.Data[1]); 
    sendcmd.CRC=0;
    plen=sizeof(struct FSM_SendCmd)-sizeof(sendcmd.Data)+2;
   if(FSMMN825Ethernet!=0)  FSMMN825Ethernet->dt->Proc((char*)&sendcmd,plen,fsmdt);
  
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_ssi_exit);
#endif
              
}

void FSM_MN825Recive(char* data,short len, struct FSM_DeviceTree* fsmdt)
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
        FSM_Statstic_SetStatus(fsmdt,"ok");
        for(i=0;i<FSM_MN825DeviceTreeSize;i++)
          {
              if(FSMMN825Dev[i].iddev==fsmdt->IDDevice)
              {
                 FSM_MN825SendStreaminfo(FSMMN825Dev[i].idstream,fsmdt);
                 return; 
              }
          }
          for(i=0;i<FSM_MN825DeviceTreeSize;i++)
          {
          if(FSMMN825Dev[i].reg==0)
          {
             FSMMN825Dev[i].reg=1;
             FSMMN825Dev[i].ethdev=FSM_FindEthernetDevice(fsmdt->IDDevice);
             fsmas.iddev=fsmdt->IDDevice;
             //fsmas.ToProcess=FSM_PO06RecivePacket;
             //fsmas.ToUser=FSM_E1SendPacket;
             fsmas.TransportDevice= FSMMN825Dev[i].ethdev->numdev;
             fsmas.TransportDeviceType=FSM_EthernetID;
             fsmas.Data=&FSMMN825Dev[i];
             FSMMN825Dev[i].idstream=FSM_AudioStreamRegistr(fsmas);
             FSMMN825Dev[i].iddev=fsmdt->IDDevice;
             fsmdt->data=&FSMMN825Dev[i];
             fsmdt->config=&FSMMN825Dev[i].mn825set;
             FSM_MN825SendStreaminfo(FSMMN825Dev[i].idstream,fsmdt);
             printk( KERN_INFO "FSMPO06 Device Added %u \n",fsmdt->IDDevice); ;
             
             
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
          if((FSMMN825Dev[i].reg==1)&&( FSMMN825Dev[i].iddev==fsmdt->IDDevice))
          {
          
             FSM_AudioStreamUnRegistr(FSMMN825Dev[i].idstream);
             FSMMN825Dev[i].reg=0;
             printk( KERN_INFO "FSM MN825 Device Deleted %u \n",fsmdt->IDDevice); 
             break;
          }
          }
          break;
          case AnsPing:///< Пинг
          break;
          case SendCmdToServer: ///< Отправка команды серверу
          switch(scmd->cmd)
          {
              case FSMMN825ConnectToDevE1:
             // ((struct FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idcon=FSM_P2P_Connect(((struct FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idstream, ((struct FSM_E1Device*)(FSM_FindDevice(((struct FSMPO06CommCons*)scmd->Data)->id)->data))->streams_id[((struct FSMPO06CommCons*)scmd->Data)->channel]);
              break;
              case FSMMN825DisConnectToDevE1:
              FSM_P2P_Disconnect(((struct FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idcon);
              break;
              case AnsGetSettingClientMN825:
              printk( KERN_INFO "FSM_Set Recv %i\n",scmd->IDDevice);
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

    printk( KERN_INFO "RPack %u \n" ,len); 
}
EXPORT_SYMBOL(FSM_MN825Recive);
void ApplaySettingMN825(struct FSM_DeviceTree* df)
{
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_asp6_init);
#endif

    memset(&sendcmd,0,sizeof(sendcmd));
    printk( KERN_INFO "FSM_Set\n" ); 
    sendcmd.cmd=SetSettingClientMN825;
    sendcmd.countparam=1;
    sendcmd.IDDevice=df->IDDevice;
    sendcmd.CRC=0;
    sendcmd.opcode=SendCmdToDevice;
    memcpy(&sendcmd.Data,&(((struct FSM_MN825Device*)df->data)->mn825set.fsm_mn825_su_s),sizeof(struct fsm_mn825_subscriber));
    (FSM_FindDevice(FSM_EthernetID))->dt->Proc((char*)&sendcmd,sizeof(struct FSM_SendCmd)-sizeof(sendcmd.Data)+sizeof(struct fsm_mn825_subscriber),df);

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_asp6_exit);
#endif
}

static int __init FSM_MN825_init(void)
{
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(init_on);
#endif

   dft.aplayp=ApplaySettingMN825;
   dft.type=(unsigned char)AudioDevice;
   dft.VidDevice=(unsigned char)CommunicationDevice;
   dft.PodVidDevice=(unsigned char)CCK;
   dft.KodDevice=(unsigned char)MN825;
   dft.Proc=FSM_MN825Recive;
   dft.config_len=sizeof(struct fsm_mn825_setting);
   FSM_DeviceClassRegister(dft);
   FSMMN825Ethernet = FSM_FindDevice(FSM_EthernetID);
   if(FSMMN825Ethernet == 0 )
   {
          printk( KERN_INFO "FSM MN825 module not loaded\n" ); 
          return 1;
   }
   printk( KERN_INFO "FSM MN825 Module loaded\n" ); 
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(init_off);
#endif

   return 0;  
}

static void __exit FSM_MN825_exit(void)
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

module_init(FSM_MN825_init);
module_exit(FSM_MN825_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM MN825 Module");
MODULE_LICENSE("GPL");