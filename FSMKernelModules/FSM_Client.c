/*!
\file
\brief Модуль взаимодествия с Ethernet
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include "FSM/FSMAudio/FSM_AudioStream.h"
#include <FSM/FSMEthernet/FSMEthernetHeader.h> 
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSM_Client/FSM_client.h"
#include <linux/netfilter.h>
struct fsm_client_struct fsmlcs[FSM_ClientTreeSize];
struct fsm_server_connection fsmcon;
struct fsm_event_struct fsmes[FSM_EventTreeSize];

#ifdef  DEBUG_CALL_STACK 
uint64_t debug_this1;
extern uint64_t debug_global;
#define DEBUG_CALL_STACK_SetStack debug_this1=(debug_this2<<8) 
#define DEBUG_CALL_STACK_THIS 1
#define DEBUG_CALL_STACK_GLOBSET debug_global =(debug_global<<8)|(DEBUG_CALL_STACK_THIS);

typedef enum debug_function
{
    init_on=0x00,
    init_off=0x01,
    exit_on=0x02,
    exit_off=0x03,
    get_sendethpack_init=0x04,
    get_sendethpack_exit=0x05,
    get_regeth_init=0x06,
    get_regeth_exit=0x07,
    get_findeth_init=0x08,
    get_findeth_exit=0x09,
    get_deleth_init=0x10,
    get_deleth_exit=0x11,
    get_esp_init=0x12,
    get_esp_exit=0x13,
    get_prcv_init=0x14,
    get_prcv_exit=0x15,
    get_sendethpack_exit_eror=0x16,
    get_regdev_init=0x17,
    get_regdev_exit=0x18
    
}debug_fun ;
#endif 

static int packet_direct_xmit(struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	netdev_features_t features;
	struct netdev_queue *txq;
	int ret = NETDEV_TX_BUSY;

	if (unlikely(!netif_running(dev) ||
		     !netif_carrier_ok(dev)))
		goto drop;

	features = netif_skb_features(skb);
	if (skb_needs_linearize(skb, features) &&
	    __skb_linearize(skb))
		goto drop;

	txq = skb_get_tx_queue(dev, skb);

	local_bh_disable();

	HARD_TX_LOCK(dev, txq, smp_processor_id());
	if (!netif_xmit_frozen_or_drv_stopped(txq))
		ret = netdev_start_xmit(skb, dev, txq, false);
	HARD_TX_UNLOCK(dev, txq);

	local_bh_enable();

	if (!dev_xmit_complete(ret))
		kfree_skb(skb);

	return ret;
drop:
	atomic_long_inc(&dev->tx_dropped);
	kfree_skb(skb);
	return NET_XMIT_DROP;
}

unsigned int FSM_Send_Ethernet(void * data, int len, struct fsm_server_connection *fsmdev)
{

  struct net_device *dev = fsmdev->dev;
  struct sk_buff *skb;
  int hlen = LL_RESERVED_SPACE(dev);
  int tlen = dev->needed_tailroom;

  #ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_sendethpack_init);
  #endif
 
  if(fsmdev==0) return 1;
  //skb = alloc_skb(len + hlen + tlen, GFP_ATOMIC);
  skb = dev_alloc_skb(len + hlen + tlen);
  if(skb==NULL)
  {
       printk( KERN_INFO "SKB Eror\n"); 
       goto out;
  }
  skb_reserve(skb, hlen);
  skb->dev = dev;
  //skb->protocol = fsmdev.eth.h_proto;
  skb_reset_network_header(skb);
  memcpy(skb_put(skb, len),data,len);
  if(dev_hard_header(skb, dev, __constant_htons(FSM_PROTO_ID_R), fsmdev->destmac, dev->dev_addr, skb->len)<0) goto out;
  packet_direct_xmit(skb);
  //надо чистить буфер
 
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_sendethpack_exit);
#endif
  return 0;

 out:
 
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_sendethpack_exit_eror);
#endif

	kfree_skb(skb);
	return 0;
}
EXPORT_SYMBOL(FSM_Send_Ethernet);
unsigned int FSM_Send_Ethernet_TS(void * data, int len)
{
    FSM_Send_Ethernet(data,len,&fsmcon);
}
EXPORT_SYMBOL(FSM_Send_Ethernet_TS);

int FSM_RegisterServer(unsigned short id,unsigned char type,unsigned char VidDevice, unsigned char PodVidDevice,unsigned char KodDevice)
{
    struct FSM_DeviceRegistr regp;
    struct fsm_server_connection fsmdev;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_regeth_init);
#endif
    
   memset(&fsmdev,0,sizeof(fsmdev));
   regp.IDDevice=id;
   regp.VidDevice=VidDevice;
   regp.PodVidDevice=PodVidDevice;
   regp.KodDevice=KodDevice;
   regp.type=type;
   regp.opcode=RegDevice;
   regp.CRC=0;
   memset(fsmdev.destmac,0xFF,6);
   fsmcon.id=id;
   fsmdev.dev=first_net_device( &init_net ); 
   
   while (fsmdev.dev)
   {
   FSM_Send_Ethernet(&regp,sizeof(regp),&fsmdev);
   fsmdev.dev = next_net_device( fsmdev.dev );
   }
   
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_regeth_exit);
#endif

    return 2;
}
EXPORT_SYMBOL(FSM_RegisterServer);

struct fsm_event_struct* FSM_RegisterEvent(unsigned int id,EventClientProcess Handler)
{
    int i;
    for(i=0;i<FSM_EventTreeSize;i++)
    {
    if(fsmes[i].reg==0)
    {
    fsmes[i].reg=1;
    fsmes[i].id=id;
    fsmes[i].Handler=Handler;
    return &fsmes[i];
    }
    }
    return 0;
}
EXPORT_SYMBOL(FSM_RegisterEvent);

struct fsm_event_struct* FSM_FindEvent(unsigned int id)
{
    int i;
    for(i=0;i<FSM_EventTreeSize;i++)
    {
    if((fsmes[i].reg==1)&&(fsmes[i].id==id))
    {
    return &fsmes[i];
    }
    }
    return 0;
}
EXPORT_SYMBOL(FSM_FindEvent);

void FSM_DeleteEvent(unsigned int id)
{
    struct fsm_event_struct* evnt=FSM_FindEvent(id);
    if(evnt!=0) evnt->reg=0;
}
EXPORT_SYMBOL(FSM_DeleteEvent);

int FSM_RegisterDevice(unsigned short id,unsigned char type,unsigned char VidDevice, unsigned char PodVidDevice,unsigned char KodDevice, DeviceClientProcess Handler)
{
    int i;
    struct FSM_DeviceRegistr regp;
    int time=9000000;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_regdev_init);
#endif
    while(time)
    {
        time--;
        if(fsmcon.coonect==1) break;
        
    }
    if(fsmcon.coonect==0) return -1;
    
    for(i=0;i<FSM_ClientTreeSize;i++)
    {
    if(fsmlcs[i].reg==0)
    {
    fsmlcs[i].Handler=Handler;
    fsmlcs[i].reg=1;
    fsmlcs[i].id=id;
    break;
    }
    }



   regp.IDDevice=id;
   regp.VidDevice=VidDevice;
   regp.PodVidDevice=PodVidDevice;
   regp.KodDevice=KodDevice;
   regp.type=type;
   regp.opcode=RegDevice;
   regp.CRC=0;
   FSM_Send_Ethernet(&regp,sizeof(regp),&fsmcon);
   
   
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_regdev_exit);
#endif

    return 0;
}
EXPORT_SYMBOL(FSM_RegisterDevice);

struct fsm_client_struct*  FSM_FindHandlerDevice(unsigned short id)
{
    int i;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_findeth_init);
#endif
    
   if(fsmcon.coonect==1) 
   {
    for(i=0;i<FSM_ClientTreeSize;i++)
    {
    if((fsmlcs[i].reg==1)&&(fsmlcs[i].id==id))
    {
    return &fsmlcs[i];
    }
    }
   }
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_findeth_exit);
#endif

    return 0;
    

}
EXPORT_SYMBOL(FSM_FindHandlerDevice);

int  FSM_DeleteDevice(unsigned short id)
{
struct FSM_DeviceDelete delp;
struct fsm_client_struct* strdev;
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_deleth_init);
#endif
    
   if(fsmcon.coonect==1) 
   {
    delp.IDDevice=id;
    delp.opcode=DelLisr;
    delp.CRC=0;
    FSM_Send_Ethernet(&delp,sizeof(delp),&fsmcon);
    strdev=FSM_FindHandlerDevice(id);
    if(strdev==0) return -1;
    strdev->reg=0;
   }

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_deleth_exit);
#endif
   
    return 1;
}

EXPORT_SYMBOL(FSM_DeleteDevice);

void FSM_DeregisterServer(void)
{
struct FSM_DeviceDelete delp;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_esp_init);
#endif

  if(fsmcon.coonect==1) 
  {
    delp.IDDevice=fsmcon.id;
    delp.opcode=DelLisr;
    delp.CRC=0;
    fsmcon.coonect=0;
    FSM_Send_Ethernet(&delp,sizeof(delp),&fsmcon);
  }

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_esp_exit);
#endif

}
EXPORT_SYMBOL(FSM_DeregisterServer);



int FSMClient_pack_rcv( struct sk_buff *skb, struct net_device *dev, 
                   struct packet_type *pt, struct net_device *odev )
{ 
     char dats= ((char*)skb->data)[0];
     struct ethhdr *eth=eth_hdr(skb);
     struct fsm_client_struct* clstr;
      struct fsm_event_struct* evstr;
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_prcv_init);
#endif

     if (skb->pkt_type == PACKET_OTHERHOST || skb->pkt_type == PACKET_LOOPBACK) goto clear;
     
     switch(dats)
      {
          case RegDevice: ///< Регистрация устройства
         
          break;
          case AnsRegDevice: ///< Подтверждение регистрации 
          if(fsmcon.id==((struct FSM_AnsDeviceRegistr*)(skb->data))->IDDevice)
          {
          memcpy(fsmcon.destmac,eth->h_source,6);
          fsmcon.dev=dev; 
          fsmcon.coonect=1;
          }
          else
          {
             clstr= FSM_FindHandlerDevice(((struct FSM_AnsDeviceRegistr*)(skb->data))->IDDevice);
             if(clstr==0) goto clear;
             clstr->Handler(skb->data,sizeof(struct FSM_AnsDeviceRegistr),clstr);
          }
          break;
          case DelLisr: ///< Удаление устройства из списка
          break;
          case AnsDelList: ///< Подтверждение удаления устройства из списка
          if(fsmcon.id==((struct FSM_AnsDeviceDelete*)(skb->data))->IDDevice)
          {
          fsmcon.coonect=0;
          }
          else
          {
             clstr= FSM_FindHandlerDevice(((struct FSM_AnsDeviceDelete*)(skb->data))->IDDevice);
             if(clstr==0) goto clear;
             clstr->Handler(skb->data,sizeof(struct FSM_AnsDeviceDelete),clstr);
          }
          break;
          case AnsPing:///< Пинг
          break;
          case SendCmdToDevice:///< Отправка команды устройству
          if(fsmcon.id==((struct FSM_SendCmd*)(skb->data))->IDDevice)
          {
          }
          else
          {
             clstr= FSM_FindHandlerDevice(((struct FSM_SendCmd*)(skb->data))->IDDevice);
             if(clstr==0) goto clear;
             clstr->Handler(skb->data,sizeof(struct FSM_SendCmd),clstr);
          }
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
         goto clear;        
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
          case PacketFromUserSpace: 
          if(fsmcon.id==((struct FSM_SendCmdUserspace*)(skb->data))->IDDevice)
          {
          }
          else
          {
             clstr= FSM_FindHandlerDevice(((struct FSM_SendCmdUserspace*)(skb->data))->IDDevice);
             if(clstr==0) goto clear;
             clstr->Handler(skb->data,sizeof(struct FSM_SendCmdUserspace),clstr);
          }
          break;
          case SysEvent:
          evstr = FSM_FindEvent(((struct FSM_EventSignal*)(skb->data))->ID);
          if(evstr==0) goto clear;
          evstr->Handler(skb->data,sizeof(struct FSM_SendCmdUserspace),evstr);
          break;
      }                 
                    
                       
                    
   
  
  

   #ifdef  DEBUG_CALL_STACK 
   DEBUG_CALL_STACK_SetStack|(get_prcv_exit);
   #endif
   
clear:
   kfree_skb(skb);  
   return skb->len; 
}; 


static struct packet_type FSMClient_proto = { 
   .type =	cpu_to_be16( FSM_PROTO_ID ),  // may be: __constant_htons( TEST_PROTO_ID ), 
   .func = FSMClient_pack_rcv, 
}; 




 
static int __init FSMClient_init(void)
{

   memset(&fsmcon,0,sizeof(fsmcon));
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(init_on);
#endif

   dev_add_pack( &FSMClient_proto ); 
   printk( KERN_INFO "FSMClient module loaded\n" ); 

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(init_off);
#endif

   return 0;  
}

static void __exit FSMClient_exit(void)
{  
    

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(exit_on);
#endif

    dev_remove_pack( &FSMClient_proto ); 
   printk( KERN_INFO "FSMClient module unloaded\n" ); 

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(exit_off);
#endif 
}

module_init(FSMClient_init);
module_exit(FSMClient_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Protocol Module");
MODULE_LICENSE("GPL");