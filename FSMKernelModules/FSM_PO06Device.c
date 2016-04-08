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
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/netdevice.h>
#include <asm/uaccess.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/miscdevice.h> 
#include <linux/if_arp.h>
#include <linux/kernel.h>
#include <net/sock.h>
#include <linux/net.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/skbuff.h> 
#include <linux/socket.h>
#include <linux/net.h>
#include <net/sock.h>
#include <linux/etherdevice.h> 
#include "FSM/FSMAudio/FSM_AudioStream.h"
#include <FSM/FSMEthernet/FSMEthernetHeader.h> 
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSMAudio/FSM_AudioStream.h"


struct FSM_DeviceFunctionTree dft;
struct FSM_DeviceTree* FSMPO06Ethernet;
struct FSM_PO06Device FSMPO06Dev[FSM_PO06DeviceTreeSize];


void FSM_PO06RecivePacket(char* data,short len)
{
  // printk( KERN_INFO "Stream Recived %u \n",len); 
   FSM_AudioStreamToUser(0,data,len); 
  
}

void FSM_PO06SendStreaminfo(unsigned short id,struct FSM_DeviceTree* fsmdt)
{
    short plen;
    struct FSM_SendCmd sendcmd;
    memset(&sendcmd,0,sizeof(struct FSM_SendCmd));
    sendcmd.opcode=SendCmdToDevice;
    sendcmd.IDDevice=fsmdt->IDDevice;
    sendcmd.cmd=FSMPO06SendStream;
    sendcmd.countparam=1;
    ((unsigned short*)sendcmd.Data)[0]=id;
    printk( KERN_INFO "FSM Send %u ,%u \n",sendcmd.Data[0],sendcmd.Data[1]); 
    sendcmd.CRC=0;
    plen=sizeof(struct FSM_SendCmd)-sizeof(sendcmd.Data)+2;
   if(FSMPO06Ethernet!=0)  FSMPO06Ethernet->dt->Proc((char*)&sendcmd,plen,fsmdt);
                
}

void FSM_PO06Recive(char* data,short len, struct FSM_DeviceTree* fsmdt)
{
    int i;
    struct FSM_AudioStream fsmas;
        // char datas[2];
         
    switch(data[0])
      {
                        
        case RegDevice: ///< Регистрация устройства
        for(i=0;i<FSM_PO06DeviceTreeSize;i++)
          {
              if(FSMPO06Dev[i].iddev==fsmdt->IDDevice)
              {
                 FSM_PO06SendStreaminfo(FSMPO06Dev[i].idstream,fsmdt);
                 return; 
              }
          }
          for(i=0;i<FSM_PO06DeviceTreeSize;i++)
          {
          if(FSMPO06Dev[i].reg==0)
          {
             FSMPO06Dev[i].reg=1;
             FSMPO06Dev[i].ethdev=FSM_FindEthernetDevice(fsmdt->IDDevice);
             fsmas.iddev=fsmdt->IDDevice;
             fsmas.ToProcess=FSM_PO06RecivePacket;
             //fsmas.ToUser=FSM_E1SendPacket;
             fsmas.TransportDevice= FSMPO06Dev[i].ethdev->numdev;
             fsmas.TransportDeviceType=FSM_EthernetID;
             FSMPO06Dev[i].idstream=FSM_AudioStreamRegistr(fsmas);
             FSMPO06Dev[i].iddev=fsmdt->IDDevice;
             FSM_PO06SendStreaminfo(FSMPO06Dev[i].idstream,fsmdt);
             printk( KERN_INFO "FSMPO06 Device Added %u \n",fsmdt->IDDevice); 
        
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
          if((FSMPO06Dev[i].reg==1)&&( FSMPO06Dev[i].iddev==fsmdt->IDDevice))
          {
          
             FSM_AudioStreamUnRegistr(FSMPO06Dev[i].idstream);
             FSMPO06Dev[i].reg=0;
             printk( KERN_INFO "FSMPO06 Device Deleted %u \n",fsmdt->IDDevice); 
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
EXPORT_SYMBOL(FSM_PO06Recive);

static int __init FSM_PO06_init(void)
{
   dft.type=(unsigned char)AudioDevice;
   dft.VidDevice=(unsigned char)CommunicationDevice;
   dft.PodVidDevice=(unsigned char)CCK;
   dft.KodDevice=(unsigned char)PO06;
   dft.Proc=FSM_PO06Recive;
   FSM_DeviceClassRegister(dft);
   FSMPO06Ethernet = FSM_FindDevice(FSM_EthernetID);
   if(FSMPO06Ethernet == 0 )
   {
          printk( KERN_INFO "FSME1Protocol module not loaded\n" ); 
          return 1;
   }
   printk( KERN_INFO "FSM PO06 Module loaded\n" ); 
   return 0;  
}

static void __exit FSM_PO06_exit(void)
{
   printk( KERN_INFO "FSM PO06 Module unloaded\n" );  
}

module_init(FSM_PO06_init);
module_exit(FSM_PO06_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM PO06 Module");
MODULE_LICENSE("GPL");