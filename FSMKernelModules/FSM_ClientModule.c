/*!
\file
\brief Модуль клиент статистики
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
#include "FSM/FSMDevice/fsm_statusstruct.h"



struct sock *nl_sk = NULL; 
struct FSM_DeviceTree dt;
struct fsm_ethernet_dev fsdev;

 unsigned int FSM_Send_Ethernet_Package(void * data, int len, struct fsm_ethernet_dev *fsmdev)
{

  struct net_device *dev = fsmdev->dev;
  struct sk_buff *skb;
  int hlen = LL_RESERVED_SPACE(dev);
  int tlen = dev->needed_tailroom; 
  if(fsmdev==0) return 1;
  skb = alloc_skb(len + hlen + tlen, GFP_ATOMIC);
  skb_reserve(skb, hlen);
  skb->dev = dev;
  //skb->protocol = fsmdev.eth.h_proto;
  skb_reset_network_header(skb);
  memcpy(skb_put(skb, len),data,len);
  if(dev_hard_header(skb, dev, __constant_htons(FSM_PROTO_ID_R), fsmdev->destmac, dev->dev_addr, skb->len)<0) goto out;
  if(dev_queue_xmit(skb)<0) goto out;
  return 0;

 out:
	kfree_skb(skb);
	return 0;
}
EXPORT_SYMBOL(FSM_Send_Ethernet_Package);

int FSMClientProtocol_pack_rcv( struct sk_buff *skb, struct net_device *dev, 
                   struct packet_type *pt, struct net_device *odev ) { 
     char dats= ((char*)skb->data)[0];
     struct ethhdr *eth=eth_hdr(skb);
    
     if (skb->pkt_type == PACKET_OTHERHOST || skb->pkt_type == PACKET_LOOPBACK) return 0;
     printk( KERN_ERR "RegDev %u\n",dats);
     switch(dats)
      {
          case RegDevice: ///< Регистрация устройства
          break;
          case AnsDelList: ///< Подтверждение удаления устройства из списка
          break;
          case AnsPing:///< Пинг
          break;
          case SendCmdToDevice:///< Отправка команды устройству
          break;
          case AnsSendCmdToDevice: ///< Подтверждение приёма команды устройством
          break;
          case RqToDevice:///< Ответ на команду устройством
          break;
          case AnsRqToDevice: ///< Подтверждение приёма команды сервером
          break;
          case SendCmdToServer: ///< Отправка команды серверу
           break;
          case SendTxtMassage: ///< Отправка текстового сообщения
           break;
          case AnsSendTxtMassage: ///< Подтверждение приёма текстового сообщения
           break;
          case SendTxtEncMassage: ///< Отправка зашифрованного текстового сообщения
           break;
          case AnsSendTxtEncMassage: ///< Подтверждение приёма зашифрованного текстового сообщения
           break;
          case SendAudio:///< Передача аудио данных
          break;
          case SendVideo:///< Передача видео данных
           break;
          case SendBinData:///< Передача бинарных данных
           break;
          case AnsSendBinData:///< Подтверждение приёма бинарных данных
           break;
          case SendSMS: ///< Отправить СМС
           break;
          case SendAnsSMS: ///< Подтверждение СМС
          break;
          case SendSMStoDev: ///< Передача СМС устройству
          break;
          case SendAnsSMStoDev: ///< Подтверждение СМС устройством
          break;
          case SendEncSMS: ///< Отправить зашифрованного СМС
          break;
          case SendAnsEncSMS: ///<Подтверждение зашифрованного СМС
          break;
          case SendEncSMStoDev:///< Отправить зашифрованного СМС устройству
          break;
          case SendAnsEncSMStoDev:///< Подтверждение зашифрованного СМС  устройства
          break;
          case SendEmail:  ///< Отправка email
          break;
          case AnsEmail: ///<Подтверждение email
          break;
          case SendEmailtoDevice: ///<Передача email устройству
          break;
          case AnsSendEmailtoDevice: ///<Подтверждение email устройством
          break;
          case SendEncEmail: ///<Отправить зашифрованного email
          break;
          case AnsEncEmail: ///<Подтверждение зашифрованного email
          break;
          case SendEncEmailtoDev: ///< Отправить зашифрованного email устройству
          break;
          case AnsEncEmailtoDev: ///< Подтверждение зашифрованного email   устройства
          break;
          case SocSend: ///< Отправка сообщение в социальную сеть
          break;
          case AnsSocSend: ///< Подтверждение сообщения в социальную сеть
          break;
          case SocSendtoDev:///< Передача сообщения в социальную сеть устройству
          break;
          case AnsSocSendtoDev:///< Подтверждение   сообщения в социальную сеть устройством
          break;
          case SocEncSend: ///< Отправить зашифрованного сообщения в социальную сеть
          break;
          case AnsSocEncSend: ///< Подтверждение зашифрованного сообщения в социальную сеть
          break;
          case SocEncSendtoDev: ///<	Отправить зашифрованного сообщения в социальную сеть устройству
          break;
          case AnsSocEncSendtoDev: ///<	Подтверждение зашифрованного сообщения в социальную сеть   устройства
          break;
          case Alern: ///<Тревога
          break;
          case Warning: ///<Предупреждение
          break;
          case Trouble: ///<Сбой
          break;
          case Beep: ///<Звук
          break;
      }                 
                    
                       
                
   
   printk( KERN_ERR "packet received with length: %u\n", skb->len );
   
   
   //FSM_Send_Ethernet_Package(odev,dts,3,fsdev);
   return skb->len; 
}; 


static struct packet_type FSMClientProtocol_proto = { 
   .type =	cpu_to_be16( FSM_PROTO_ID ),  // may be: __constant_htons( TEST_PROTO_ID ), 
   .func = FSMClientProtocol_pack_rcv, 
}; 




 
static int __init FSM_ClientModule_init(void)
{
    struct FSM_DeviceRegistr regp;
   dev_add_pack( &FSMClientProtocol_proto ); 
   regp.IDDevice=(unsigned short)FSM_StatisicID;
   regp.VidDevice=(unsigned char)FSMDeviceConfig;
   regp.PodVidDevice=(unsigned char)ComputerStatistic;
   regp.KodDevice=(unsigned char)PCx86;
   regp.type=(unsigned char)StatisticandConfig;
   regp.opcode=RegDevice;
   regp.CRC=0;
   //FSM_DeviceRegister(regp);
   memset(&fsdev,0,sizeof(fsdev));
   printk( KERN_INFO "FSMClientProtocol module loaded\n" ); 
   return 0;  
}

static void __exit FSM_ClientModule_exit(void)
{  
    struct FSM_DeviceDelete delp;
    dev_remove_pack( &FSMClientProtocol_proto ); 
   printk( KERN_INFO "FSM Client module unloaded\n" );  
}

module_init(FSM_ClientModule_init);
module_exit(FSM_ClientModule_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Client Module");
MODULE_LICENSE("GPL");