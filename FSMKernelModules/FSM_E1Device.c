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

void FSM_E1RecivePacket(char* data,short len)
{
   printk( KERN_INFO "Stream Recived %u \n",len); 

}

void FSM_E1SendStreaminfo(unsigned short id,struct FSM_DeviceTree* fsmdt)
{
    short plen;
    struct FSM_SendCmd sendcmd;
    sendcmd.opcode=SendCmdToDevice;
    sendcmd.IDDevice=fsmdt->IDDevice;
    sendcmd.cmd=FSME1SendStream;
    sendcmd.countparam=1;
    ((unsigned short*)sendcmd.Data)[0]=id;
    sendcmd.CRC=0;
   if(FSME1Ethernet!=0)  FSME1Ethernet->dt->Proc((char*)&sendcmd,plen,fsmdt);
                
}

void FSM_E1Recive(char* data,short len, struct FSM_DeviceTree* fsmdt)
{
    int i;
    struct FSM_AudioStream fsmas;

    switch(data[0])
      {
                        
        case RegDevice: ///< Регистрация устройства
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
             FSME1Dev[i].idstream=FSM_AudioStreamRegistr(fsmas);
             FSME1Dev[i].iddev=fsmdt->IDDevice;
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
    
    
    printk( KERN_INFO "RPack %u \n" ,len); 
}
EXPORT_SYMBOL(FSM_E1Recive);

static int __init FSME1Protocol_init(void)
{
   dft.type=(unsigned char)AudioDevice;
   dft.VidDevice=(unsigned char)CommunicationDevice;
   dft.PodVidDevice=(unsigned char)CCK;
   dft.KodDevice=(unsigned char)MN524;
   dft.Proc=FSM_E1Recive;
   FSM_DeviceClassRegister(dft);
   FSME1Ethernet = FSM_FindDevice(FSM_EthernetID);
   if(FSME1Ethernet == 0 )
   {
          printk( KERN_INFO "FSME1Protocol module not loaded\n" ); 
          return 1;
   }
   printk( KERN_INFO "FSME1Protocol module loaded\n" ); 
   return 0;  
}

static void __exit FSME1Protocol_exit(void)
{
    FSM_ClassDeRegister(dft);
   printk( KERN_INFO "FSME1Protocol module unloaded\n" );  
}

module_init(FSME1Protocol_init);
module_exit(FSME1Protocol_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM E1 Protocol Module");
MODULE_LICENSE("GPL");