/*!
\file
\brief Модуль взаимодествия с Ethernet
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
#include <FSM/FSMEthernet/FSMEthernetHeader.h> 
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"



struct sock *nl_sk = NULL; 
struct FSM_DeviceFunctionTree dft;
struct FSM_DeviceTree* dt;
struct fsm_ethernet_dev fsdev[FSM_EthernetDeviceTreeSize];

static unsigned int FSM_Send_Ethernet_Package(void * data, int len, struct fsm_ethernet_dev *fsmdev)
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
int FSM_RegisterEthernetDevice(struct FSM_DeviceRegistr *fsmrg, struct net_device *dev, char* mac)
{
    int i=0;
    for(i=0;i<FSM_EthernetDeviceTreeSize;i++)
    {
        if((fsmrg->IDDevice==fsdev[i].id)&&(fsdev[i].reg==1)) return 1;
    }
    for(i=0;i<FSM_EthernetDeviceTreeSize;i++)
    {
        if(fsdev[i].reg==0) 
        {
            fsdev[i].dev=dev;
            fsdev[i].id=fsmrg->IDDevice;
            fsdev[i].reg=1;
            memcpy(fsdev[i].destmac,mac,6);
            printk( KERN_INFO "FSM Ethernet Device Registred %u \n",fsmrg->IDDevice); 
            return 0;
        }
    }
    return 2;
}
struct fsm_ethernet_dev*  FSM_FindEthernetDevice(unsigned short id)
{
    int i;
    for(i=0;i<FSM_EthernetDeviceTreeSize;i++)
    {
        if((id==fsdev[i].id)&&(fsdev[i].reg==1)) return &fsdev[i];
    }
    return 0;
}
int  FSM_DeleteEthernetDevice(unsigned short id)
{
    int i;
    for(i=0;i<FSM_EthernetDeviceTreeSize;i++)
    {
        if((id==fsdev[i].id)&&(fsdev[i].reg==1)) 
        {
                fsdev[i].reg=0;
                 printk( KERN_INFO "FSM Ethernet Device UnRegistred %u \n",id); 
                return 0;
        }
    }
    return 1;
}
void FSM_EthernetSendPckt(char* data,short len, struct FSM_DeviceTree* fsmdt)
{
    FSM_Send_Ethernet_Package(data,len,FSM_FindEthernetDevice(fsmdt->IDDevice));
}


int FSMClientProtocol_pack_rcv( struct sk_buff *skb, struct net_device *dev, 
                   struct packet_type *pt, struct net_device *odev ) { 
     struct FSM_DeviceTree* dftv;
     char dats= ((char*)skb->data)[0];
     struct ethhdr *eth=eth_hdr(skb);
    
     if (skb->pkt_type == PACKET_OTHERHOST || skb->pkt_type == PACKET_LOOPBACK) return 0;
      
      
     switch(dats)
      {
          case RegDevice: ///< Регистрация устройства
          printk( KERN_ERR "RegDev \n");
          if(FSM_RegisterEthernetDevice((struct FSM_DeviceRegistr *)skb->data,dev,eth->h_source)!=0) return 1;
          if(FSM_DeviceRegister(*((struct FSM_DeviceRegistr *)skb->data))!=0) return 1;
          ((struct FSM_DeviceRegistr *)skb->data)->opcode=AnsRegDevice;
          FSM_Send_Ethernet_Package(skb->data,sizeof(struct FSM_DeviceRegistr),FSM_FindEthernetDevice(((struct FSM_DeviceRegistr *)skb->data)->IDDevice));
          break;
          case AnsRegDevice: ///< Подтверждение регистрации
          break;
          case DelLisr: ///< Удаление устройства из списка
          FSM_DeRegister(*((struct FSM_DeviceDelete *)skb->data));
          ((struct FSM_DeviceDelete *)skb->data)->opcode=AnsDelList;
          FSM_Send_Ethernet_Package(skb->data,sizeof(struct FSM_DeviceDelete),FSM_FindEthernetDevice(((struct FSM_DeviceDelete *)skb->data)->IDDevice));
          FSM_DeleteEthernetDevice(((struct FSM_DeviceDelete *)skb->data)->IDDevice);
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
          dftv=FSM_FindDevice(((struct FSM_SendCmdTS *)skb->data)->IDDevice);
           if(dftv==0) 
            {
                printk( KERN_INFO "Eror \n"); 
                 return 5;
            }
           //printk( KERN_INFO "FSM Dev %u\n",((struct FSM_SendCmdTS *)skb->data)->IDDevice); 
           dftv->dt->Proc((char*)skb->data,sizeof(struct FSM_SendCmdTS),dt);
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
                    
                       
                    
   
  
  


  /*fsdev.destmac[0]=0xa0;
   fsdev.destmac[1]=0xa1;
   fsdev.destmac[2]=0xa2;
   fsdev.destmac[3]=0xa3;
   fsdev.destmac[4]=0xa4;
   fsdev.destmac[5]=0xa5;*/
   
   printk( KERN_ERR "packet received with length: %u\n", skb->len );
   
   
   //FSM_Send_Ethernet_Package(odev,dts,3,fsdev);
   return skb->len; 
}; 


static struct packet_type FSMClientProtocol_proto = { 
   .type =	cpu_to_be16( FSM_PROTO_ID ),  // may be: __constant_htons( TEST_PROTO_ID ), 
   .func = FSMClientProtocol_pack_rcv, 
}; 




 
static int __init FSMClientProtocol_init(void)
{
    struct FSM_DeviceRegistr regp;
   dev_add_pack( &FSMClientProtocol_proto ); 
   dft.type=(unsigned char)Network;
   dft.VidDevice=(unsigned char)Ethernet;
   dft.PodVidDevice=(unsigned char)WireEthernet;
   dft.KodDevice=(unsigned char)StandartEthernet;
   dft.Proc= FSM_EthernetSendPckt;
   FSM_DeviceClassRegister(dft);
   
   regp.IDDevice=FSM_EthernetID;
   regp.VidDevice=dft.VidDevice;
   regp.PodVidDevice= dft.PodVidDevice;
   regp.KodDevice=dft.KodDevice;
   regp.type=dft.type;
   regp.opcode=RegDevice;
   regp.CRC=0;
   FSM_DeviceRegister(regp);
   dt=FSM_FindDevice(FSM_EthernetID);
   if(dt==0) return 1;
   memset(fsdev,0,sizeof(fsdev));
   printk( KERN_INFO "FSMClientProtocol module loaded\n" ); 
   return 0;  
}

static void __exit FSMClientProtocol_exit(void)
{  
    struct FSM_DeviceDelete delp;
    dev_remove_pack( &FSMClientProtocol_proto ); 
    delp.IDDevice=FSM_EthernetID;
    delp.opcode=DelLisr;
    delp.CRC=0;
    FSM_DeRegister(delp);
    FSM_ClassDeRegister(dft);
   printk( KERN_INFO "FSMClientProtocol module unloaded\n" );  
}

module_init(FSMClientProtocol_init);
module_exit(FSMClientProtocol_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Protocol Module");
MODULE_LICENSE("GPL");