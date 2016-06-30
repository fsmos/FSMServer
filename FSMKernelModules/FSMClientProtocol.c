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
#include <linux/netfilter.h>





struct sock *nl_sk = NULL; 
struct FSM_DeviceFunctionTree dft;
struct FSM_DeviceTree* dt;
struct fsm_ethernet_dev fsdev[FSM_EthernetDeviceTreeSize];
struct FSM_SendCmd fsmsc;
struct fsm_ethernet_dev fsdev2;
FSM_StreamProcessSend FSM_AudioStreamCallback;

#ifdef  DEBUG_CALL_STACK 
uint64_t debug_this2;
extern uint64_t debug_global;
#define DEBUG_CALL_STACK_SetStack debug_this2=(debug_this2<<8) 
#define DEBUG_CALL_STACK_THIS 2
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

 unsigned int FSM_Send_Ethernet_Package(void * data, int len, struct fsm_ethernet_dev *fsmdev)
{

  struct net_device *dev;
  struct sk_buff *skb;
  int hlen ;
  int tlen;

  #ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_sendethpack_init);
  #endif
 
  if(fsmdev==0) return 1;
  dev =fsmdev->dev;
  tlen = dev->needed_tailroom;
  hlen = LL_RESERVED_SPACE(dev);
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
EXPORT_SYMBOL(FSM_Send_Ethernet_Package);

unsigned int FSM_Send_Ethernet_Package2(void * data, int len, int id)
{

 return FSM_Send_Ethernet_Package(data,len,&fsdev[id]);
}
EXPORT_SYMBOL(FSM_Send_Ethernet_Package2);

int FSM_RegisterEthernetDevice(struct FSM_DeviceRegistr *fsmrg, struct net_device *dev, char* mac)
{
    int i=0;
    
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_regeth_init);
#endif
  
  
    for(i=0;i<FSM_EthernetDeviceTreeSize;i++)
    {
        if((fsmrg->IDDevice==fsdev[i].id)&&(fsdev[i].reg==1)) fsdev[i].reg=0;
    }
    for(i=0;i<FSM_EthernetDeviceTreeSize;i++)
    {
        if(fsdev[i].reg==0) 
        {
            fsdev[i].dev=dev;
            fsdev[i].id=fsmrg->IDDevice;
            fsdev[i].reg=1;
           fsdev[i].numdev=i;
            memcpy(fsdev[i].destmac,mac,6);
            printk( KERN_INFO "FSM Ethernet Device Registred %u \n",fsmrg->IDDevice); 
            return 0;
        }
    }
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_regeth_exit);
#endif

    return 2;
}
struct fsm_ethernet_dev*  FSM_FindEthernetDevice(unsigned short id)
{
    int i;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_findeth_init);
#endif

    for(i=0;i<FSM_EthernetDeviceTreeSize;i++)
    {
        if((id==fsdev[i].id)&&(fsdev[i].reg==1)) return &fsdev[i];
    }
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_findeth_exit);
#endif

    return 0;
    

}
EXPORT_SYMBOL(FSM_FindEthernetDevice);

int  FSM_DeleteEthernetDevice(unsigned short id)
{

    int i;

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_deleth_init);
#endif

    for(i=0;i<FSM_EthernetDeviceTreeSize;i++)
    {
        if((id==fsdev[i].id)&&(fsdev[i].reg==1)) 
        {
                fsdev[i].reg=0;
                 printk( KERN_INFO "FSM Ethernet Device UnRegistred %u \n",id); 
                return 0;
        }
    }
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_deleth_exit);
#endif
   
    return 1;
}
void FSM_EthernetSendPckt(char* data,short len, struct FSM_DeviceTree* fsmdt)
{
    struct fsm_ethernet_dev* fsmsd;
    struct fsm_ethernet_dev fsdev2;
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_esp_init);
#endif
    fsmsd=0;
    if(fsmdt!=0) fsmsd=FSM_FindEthernetDevice(fsmdt->IDDevice);
    else fsmsd=0;
    
    if(fsmsd==0) 
        {
        fsdev2.numdev=1;
        memset(fsdev2.destmac,0xFF,6);
        fsdev2.dev = first_net_device( &init_net ); 
        while (fsdev2.dev)
        {
        FSM_Send_Ethernet_Package(data,len,&fsdev2);
        fsdev2.dev = next_net_device( fsdev2.dev );
        }
        //printk(KERN_INFO "FSM Ethernet Not Registred. Use Broacast \n"); 
        return;
        }
      //  printk( KERN_INFO "FSM Send %u \n",len); 

      FSM_Send_Ethernet_Package(data,len,fsmsd);

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(get_esp_exit);
#endif
}

void FSM_RegisterAudioStreamCallback(FSM_StreamProcessSend FSM_ASC)
{
    FSM_AudioStreamCallback=FSM_ASC;
}
EXPORT_SYMBOL(FSM_RegisterAudioStreamCallback);

FSM_ADSendEthPack FSM_GetAudioStreamCallback(void)
{
    return FSM_Send_Ethernet_Package2;
}
EXPORT_SYMBOL(FSM_GetAudioStreamCallback);


int FSMClientProtocol_pack_rcv( struct sk_buff *skb, struct net_device *dev, 
                   struct packet_type *pt, struct net_device *odev ) { 
     struct FSM_DeviceTree* dftv;

     char dats= ((char*)skb->data)[0];
     struct ethhdr *eth=eth_hdr(skb);
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(get_prcv_init);
#endif

     if (skb->pkt_type == PACKET_OTHERHOST || skb->pkt_type == PACKET_LOOPBACK) goto clear;
      
       //printk( KERN_ERR "RegDev %u\n",dats);
     switch(dats)
      {
          case RegDevice: ///< Регистрация устройства
    
          if(FSM_RegisterEthernetDevice((struct FSM_DeviceRegistr *)skb->data,dev,eth->h_source)==0) 
          {
          if(FSM_DeviceRegister(*((struct FSM_DeviceRegistr *)skb->data))!=0) goto clear; 
          }
           dftv=FSM_FindDevice(((struct FSM_DeviceRegistr *)skb->data)->IDDevice);
           if(dftv==0) 
            {
                printk( KERN_INFO "Eror \n"); 
                 goto clear; 
            }
           //printk( KERN_INFO "FSM Dev %u\n",((struct FSM_SendCmdTS *)skb->data)->IDDevice); 
           dftv->dt->Proc((char*)skb->data,sizeof(struct FSM_DeviceRegistr),dftv);
          ((struct FSM_DeviceRegistr *)skb->data)->opcode=AnsRegDevice;
          FSM_Send_Ethernet_Package(skb->data,sizeof(struct FSM_DeviceRegistr),FSM_FindEthernetDevice(((struct FSM_DeviceRegistr *)skb->data)->IDDevice));
        
          
          break;
          case AnsRegDevice: ///< Подтверждение регистрации
          break;
          case DelLisr: ///< Удаление устройства из списка
          dftv=FSM_FindDevice(((struct FSM_DeviceDelete *)skb->data)->IDDevice);
           if(dftv==0) 
            {
                printk( KERN_INFO "Eror \n"); 
                 goto clear; 
            }
           //printk( KERN_INFO "FSM Dev %u\n",((struct FSM_SendCmdTS *)skb->data)->IDDevice); 
           dftv->dt->Proc((char*)skb->data,sizeof(struct FSM_DeviceDelete),dftv);
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
          goto clear; 
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
                fsmsc.cmd=FSMNotRegistred;
                fsmsc.CRC=0;
                fsmsc.countparam=0;
                fsmsc.IDDevice=((struct FSM_SendCmdTS *)skb->data)->IDDevice;
                fsmsc.opcode=SendCmdToDevice;
                 memset(fsdev2.destmac,0xFF,6);
                 fsdev2.id=((struct FSM_SendCmdTS *)skb->data)->IDDevice;
                 fsdev2.numdev=1;
                 fsdev2.dev = dev; 
                FSM_Send_Ethernet_Package(&fsmsc,sizeof(struct FSM_SendCmd)-sizeof(fsmsc.Data),&fsdev2);

                  goto clear; 
            }
           //printk( KERN_INFO "FSM Dev %u\n",((struct FSM_SendCmdTS *)skb->data)->IDDevice); 
           dftv->dt->Proc((char*)skb->data,skb->len,dt);
           ((struct FSM_SendCmdTS *)skb->data)->opcode=AnsRqToDevice;
          FSM_Send_Ethernet_Package(skb->data,FSMH_Header_Size_AnsAnsCmd,FSM_FindEthernetDevice(((struct FSM_SendCmdTS *)skb->data)->IDDevice));
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
          //printk( KERN_INFO "FSM ID %u\n",((struct FSM_SendAudioData*)skb->data)->IDDevice); 
          if((FSM_AudioStreamCallback!=0)&&(((struct FSM_SendAudioData*)skb->data)->IDDevice<FSM_AudioStreamDeviceTreeSize) )FSM_AudioStreamCallback(((struct FSM_SendAudioData*)skb->data)->IDDevice,skb->data,skb->len);
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
      }                 
                    
                       
                    
   
  
  


  /*fsdev.destmac[0]=0xa0;
   fsdev.destmac[1]=0xa1;
   fsdev.destmac[2]=0xa2;
   fsdev.destmac[3]=0xa3;
   fsdev.destmac[4]=0xa4;
   fsdev.destmac[5]=0xa5;*/
   
   //printk( KERN_ERR "packet received with length: %u\n", skb->len );
   
   
   //FSM_Send_Ethernet_Package(odev,dts,3,fsdev);
   #ifdef  DEBUG_CALL_STACK 
   DEBUG_CALL_STACK_SetStack|(get_prcv_exit);
   #endif
   
clear:
   kfree_skb(skb);  
   return skb->len; 
}; 


static struct packet_type FSMClientProtocol_proto = { 
   .type =	cpu_to_be16( FSM_PROTO_ID ),  // may be: __constant_htons( TEST_PROTO_ID ), 
   .func = FSMClientProtocol_pack_rcv, 
}; 




 
static int __init FSMClientProtocol_init(void)
{
    struct FSM_DeviceRegistr regp;
    
#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(init_on);
#endif
   dev_add_pack( &FSMClientProtocol_proto ); 
   dft.type=(unsigned char)Network;
   dft.VidDevice=(unsigned char)Ethernet;
   dft.PodVidDevice=(unsigned char)WireEthernet;
   dft.KodDevice=(unsigned char)StandartEthernet;
   dft.Proc= FSM_EthernetSendPckt;
   dft.config_len=0;
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
   FSM_Statstic_SetStatus(dt,"ok");
   if(dt==0) return 1;
   memset(fsdev,0,sizeof(fsdev));
   FSM_SendEventToAllDev(FSM_EthernetStarted);
   printk( KERN_INFO "FSMClientProtocol module loaded\n" ); 

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(init_off);
#endif

   return 0;  
}

static void __exit FSMClientProtocol_exit(void)
{  
    struct FSM_DeviceDelete delp;

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack|(exit_on);
#endif

    dev_remove_pack( &FSMClientProtocol_proto ); 
    delp.IDDevice=FSM_EthernetID;
    delp.opcode=DelLisr;
    delp.CRC=0;
    FSM_DeRegister(delp);
    FSM_ClassDeRegister(dft);
   printk( KERN_INFO "FSMClientProtocol module unloaded\n" ); 

#ifdef  DEBUG_CALL_STACK 
    DEBUG_CALL_STACK_SetStack|(exit_off);
#endif 
}

module_init(FSMClientProtocol_init);
module_exit(FSMClientProtocol_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Protocol Module");
MODULE_LICENSE("GPL");