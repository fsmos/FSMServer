/*!
\file
\brief Драйвер E1
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
#include <FSM/FSMEthernet/FSMEthernetHeader.h> 


struct FSM_DeviceFunctionTree dft;
struct FSM_DeviceTree* FSME1Ethernet;
struct FSM_E1Device FSME1Dev[FSM_E1DeviceTreeSize];
struct FSM_SendAudioData sade1;
struct FSM_SendCmd sendcmd;

#ifdef  DEBUG_CALL_STACK 
uint64_t debug_this6;
extern uint64_t debug_global;
#define DEBUG_CALL_STACK_SetStack debug_this6=(debug_this6<<8) 
#define DEBUG_CALL_STACK_THIS 6
#define DEBUG_CALL_STACK_GLOBSET debug_global =(debug_global<<8)|(DEBUG_CALL_STACK_THIS);

typedef enum debug_function
{
    init_on=0x00,
    init_off=0x01,
    exit_on=0x02,
    exit_off=0x03,
    get_ssi_init=0x04,
    get_ssi_exit=0x05,
    get_e1r_init=0x06,
    get_e1r_exit=0x07,
    get_e1rp_init=0x08,
    get_e1rp_exit=0x09,
    
}debug_fun ;
#endif 

void FSM_E1RecivePacket(char* data,short len)
{ 
   int i=0;
   int j=0;
   unsigned short st;
   unsigned short* E1SI;
   struct FSM_SendAudioData * FSMAPk=(struct FSM_SendAudioData * )data;
   struct FSME1Pkt * pkt= (struct FSME1Pkt *)FSMAPk->Data;
   struct FSME1Pkt * pktout= (struct FSME1Pkt *)sade1.Data;
   char* datar=pktout->Data;
   unsigned short size=0;
   struct FSM_E1Device* fsmdat=FSM_AudioStreamData(FSMAPk->IDDevice);
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_e1rp_init);
#endif
  
   if(fsmdat!=0)
   {
      E1SI=fsmdat->streams_id;
   }
   else
   {
       return;
   }
   
   // printk( KERN_INFO "Stream Recived %u \n",pkt->channels); 
   
   for(i=0;i<pkt->count;i++)
   {
        for(j=0;j<pkt->channels;j++)
        {
            st=E1SI[j];
           FSM_FIFOAudioStreamWrite((pkt->Data+(pkt->channels*i)+j),1,st);
        }
   }

     sade1.IDDevice=FSMAPk->IDDevice;
     pktout->count=pkt->count;
     pktout->channels=pkt->channels;
     for(i=0;i<pktout->count;i++)
     {
       for(j=0;j<pktout->channels;j++)  
       { 
           if(size>=1024) break; 
           FSM_FIFOAudioStreamRead(datar,1,E1SI[j]);
           datar++;
           size++;
          
       }
     }
    sade1.len=size+2;
    FSM_AudioStreamToUser(FSMAPk->IDDevice,(char*)&sade1,sizeof(struct FSM_SendAudioData)-sizeof(sade1.Data)+sade1.len);

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_e1rp_exit);
#endif
}


void FSM_E1SendStreaminfo(unsigned short id,struct FSM_DeviceTree* fsmdt)
{
    short plen;

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_ssi_init);
#endif

    memset(&sendcmd,0,sizeof(struct FSM_SendCmd));
    sendcmd.opcode=SendCmdToDevice;
    sendcmd.IDDevice=fsmdt->IDDevice;
    sendcmd.cmd=FSME1SendStream;
    sendcmd.countparam=1;
    ((unsigned short*)sendcmd.Data)[0]=id;
    sendcmd.CRC=0;
     plen=sizeof(struct FSM_SendCmd)-sizeof(sendcmd.Data)+2;
   if(FSME1Ethernet!=0)  FSME1Ethernet->dt->Proc((char*)&sendcmd,plen,fsmdt);
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_ssi_exit);
#endif       
}

void FSM_E1Recive(char* data,short len, struct FSM_DeviceTree* fsmdt)
{
    int i,j;
    struct FSM_AudioStream fsmas;

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_e1r_init);
#endif

    switch(data[0])
      {
                        
        case RegDevice: ///< Регистрация устройства
        FSM_Statstic_SetStatus(fsmdt,"ok");
          for(i=0;i<FSM_E1DeviceTreeSize;i++)
          {
              if(FSME1Dev[i].iddev==fsmdt->IDDevice)
              {
                 FSM_E1SendStreaminfo(FSME1Dev[i].idstream,fsmdt);
                 return; 
              }
          }
          for(i=0;i<FSM_E1DeviceTreeSize;i++)
          {
          if(FSME1Dev[i].reg==0)
          {
             FSME1Dev[i].reg=1;
             FSME1Dev[i].ethdev=FSM_FindEthernetDevice(fsmdt->IDDevice);
             fsmas.iddev=fsmdt->IDDevice;
             
             fsmas.ToProcess=FSM_E1RecivePacket;
             //fsmas.ToUser=FSM_E1SendPacket;
             fsmas.TransportDevice=FSME1Dev[i].ethdev->numdev;
             fsmas.TransportDeviceType=FSM_EthernetID;
             fsmas.Data=&FSME1Dev[i];
             FSME1Dev[i].idstream=FSM_AudioStreamRegistr(fsmas);
             FSME1Dev[i].iddev=fsmdt->IDDevice;
             fsmas.ToProcess=0;
             fsmas.TransportDevice=0;
             fsmas.TransportDeviceType=FSM_FifoID;
             fsmdt->data=&FSME1Dev[i];
             for(j=0;j<32;j++)
             {
             FSM_FIFOAudioStreamRegistr(fsmas,&(FSME1Dev[i].streams_id[j]));
              //printk( KERN_INFO "FSM %u \n",FSME1Dev[i].streams_id[j]); 
             }
             FSM_E1SendStreaminfo(FSME1Dev[i].idstream,fsmdt);
             printk( KERN_INFO "FSME1 Device Added %u \n",fsmdt->IDDevice); 
             
             break;
          }
           
          
          }
          break;
          case DelLisr:
          for(i=0;i<FSM_E1DeviceTreeSize;i++)
          {
          if((FSME1Dev[i].reg==1)&&( FSME1Dev[i].iddev==fsmdt->IDDevice))
          {
          
             FSM_AudioStreamUnRegistr(FSME1Dev[i].idstream);
             FSME1Dev[i].reg=0;
             printk( KERN_INFO "FSME1 Device Deleted %u \n",fsmdt->IDDevice); 
             break;
          }
          }
          break;
          case AnsPing:///< Пинг
          break;
          case SendCmdToServer: ///< Отправка команды серверу
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
    DEBUG_CALL_STACK_SetStack|(get_e1r_exit);
#endif
    
    printk( KERN_INFO "RPack %u \n" ,len); 
}
EXPORT_SYMBOL(FSM_E1Recive);

static int __init FSME1Protocol_init(void)
{
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(init_on);
#endif

   memset(&FSME1Dev,0,sizeof(FSME1Dev));
   sade1.codec=0;
   sade1.CRC=0;
   sade1.len=160;
   sade1.opcode=SendAudio;
   dft.type=(unsigned char)AudioDevice;
   dft.VidDevice=(unsigned char)CommunicationDevice;
   dft.PodVidDevice=(unsigned char)CCK;
   dft.KodDevice=(unsigned char)MN524;
   dft.Proc=FSM_E1Recive;
   dft.config_len=0;
   FSM_DeviceClassRegister(dft);
   //fsme1pkt2.channels=7

   FSME1Ethernet = FSM_FindDevice(FSM_EthernetID);
   if(FSME1Ethernet == 0 )
   {
          printk( KERN_INFO "FSME1Protocol module not loaded\n" ); 
          return 1;
   }
   printk( KERN_INFO "FSME1Protocol module loaded\n" ); 
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(init_off);
#endif

   return 0;  
}

static void __exit FSME1Protocol_exit(void)
{
   #ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(exit_on);
#endif

    FSM_ClassDeRegister(dft);
   printk( KERN_INFO "FSME1Protocol module unloaded\n" );  
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(exit_off);
#endif
}

module_init(FSME1Protocol_init);
module_exit(FSME1Protocol_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM E1 Protocol Module");
MODULE_LICENSE("GPL");