/*!
\file
\brief Модуль клиент статистики
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/

#define SUCCESS 0 

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
#include <linux/timer.h>
#include <net/sock.h>
#include <linux/etherdevice.h> 
#include <linux/unistd.h>
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
static dev_t first; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class
static dev_t firstset; // Global variable for the first device number
static struct cdev c_devset; // Global variable for the character device structure
static struct class *clset; // Global variable for the device class
char is_device_open,is_device_openset;
char *dthw="Hello World";
struct fsm_statusstruct fsm_ss;
struct fsm_devices_config fsm_ds;
struct FSM_DeviceRegistr regp;
struct FSM_DeviceRegistr regset;
struct FSMSSetconfigParam fsmspar;
unsigned short setservid;
struct  FSM_SendCmdTS regpcmdts;
/*
static ssize_t fsmset_show(struct class *class, struct class_attribute *attr,char *buf)
{
  // strcpy( buf, buf_msg );
  // printk( "read %d\n", strlen( buf ) );
   return 1;
}
static ssize_t fsmset_store(struct class *class, struct class_attribute *attr,const char *buf, size_t count)
{
   //printk( "write %d\n" , count );
   //strncpy( buf_msg, buf, count );
   //buf_msg[ count ] = '\0';
   return count;
}
struct class_attribute class_attr_fsmset=
{				
	.attr = {
         .name = __stringify(fsmsetc),				
		 .mode = (S_IWUSR | S_IRUGO)
           },		
	.show	= fsmset_show,						\
	.store	= fsmset_store,						\
};

static struct class *fsmset_class;
 * */
//CLASS_ATTR(fsmsetc,0666,&fsmset_show,&fsmset_store);


 unsigned int FSM_Send_Ethernet_Package(void * data, int len, struct fsm_ethernet_dev *fsmdev)
{
  //if(fsdev.dev==0) fsdev.dev = find_mergeable_anon_vma(); 
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
     struct FSM_DeviceDelete delp; 
     struct FSM_SendCmd* fscts= (struct FSM_SendCmd*)skb->data;  
     struct FSM_AnsDeviceRegistr* fscar= (struct FSM_AnsDeviceRegistr*)skb->data;  
     if (skb->pkt_type == PACKET_OTHERHOST || skb->pkt_type == PACKET_LOOPBACK) return 0;
     //printk( KERN_ERR "RegDev %u\n",dats);
    
     switch(dats)
      {
          case RegDevice: ///< Регистрация устройства
          break;
          case AnsRegDevice:
          fsdev.reg=1;
          memcpy(fsdev.destmac,eth->h_source,6);
          fsdev.dev=dev; 
           printk( KERN_INFO "Device Registred\n" ); 
          if(fscar->IDDevice==FSM_StatisicID)
          { 
          FSM_Send_Ethernet_Package(&regset,sizeof(struct FSM_DeviceRegistr),&fsdev);
          printk( KERN_INFO "Device Reg2\n" ); 
          }
          
          break;
          case AnsDelList: ///< Подтверждение удаления устройства из списка
          break;
          case AnsPing:///< Пинг
          break;
          case SendCmdToDevice:///< Отправка команды устройству
          if(fscts->IDDevice==FSM_StatisicID)
          {
          switch(fscts->cmd)
          {
            case AnsGetStatistic:
            //printk( KERN_INFO "FSM Cmd %u\n",fscts->cmd); 
            memcpy(&fsm_ss.statel[((struct fsm_status_element*)fscts->Data)->row][((struct fsm_status_element*)fscts->Data)->column],fscts->Data,sizeof(struct fsm_status_element));
            break;
            case FSMNotRegistred:
            FSM_Send_Ethernet_Package(&regp,sizeof(struct FSM_DeviceRegistr),&fsdev);
            break;
          }
          }
          if(fscts->IDDevice==FSM_SettingID)
          {
          switch(fscts->cmd)
          {
            case AnsGetSet:
           // printk( KERN_INFO "FSM Cmd %u\n",fscts->cmd); 
            memcpy(&fsm_ds.setel[((struct fsm_device_config*)fscts->Data)->row][((struct fsm_device_config*)fscts->Data)->column],fscts->Data,sizeof(struct fsm_device_config));
            break;
            
            case FSMNotRegistred:
            printk( KERN_INFO "Device FSR\n" ); 
            FSM_Send_Ethernet_Package(&regset,sizeof(struct FSM_DeviceRegistr),&fsdev);
            break;
            
            case SetSettingClient:
             printk( KERN_INFO "FSM_Setting_Applay\n" ); 
             delp.CRC=0;
             delp.opcode=DelLisr;
             delp.IDDevice=FSM_SettingID;
             setservid=((struct fsm_ClientSetting_Setting*)fscts->Data)->id;
             FSM_Send_Ethernet_Package(&delp,sizeof(struct FSM_DeviceDelete),&fsdev);
             regset.IDDevice=(unsigned short)FSM_SettingID;
             FSM_Send_Ethernet_Package(&regset,sizeof(struct FSM_DeviceRegistr),&fsdev);
            break;
          }
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
                    
                       
                
   
   //printk( KERN_ERR "packet received with length: %u\n", skb->len );
   
   
   //FSM_Send_Ethernet_Package(odev,dts,3,fsdev);
   return skb->len; 
}; 


static struct packet_type FSMClientProtocol_proto = { 
   .type =	cpu_to_be16( FSM_PROTO_ID ),  // may be: __constant_htons( TEST_PROTO_ID ), 
   .func = FSMClientProtocol_pack_rcv, 
}; 

static int device_open( struct inode *inode, struct file *file )
{
 if ( is_device_open )
  return -EBUSY;

 is_device_open++;

 return SUCCESS;
}

static int device_release( struct inode *inode, struct file *file )
{
 is_device_open--;
 return SUCCESS;
}


static int device_write( struct file *filp, const char *buff, size_t len, loff_t * off )
{
  
memset(&fsm_ss,0,sizeof(fsm_ss));
regpcmdts.opcode=SendCmdToServer;
regpcmdts.countparam=1;
regpcmdts.CRC=0;
regpcmdts.IDDevice=FSM_StatisicID;  
regpcmdts.cmd=GetStatistic;
FSM_Send_Ethernet_Package(&regpcmdts,sizeof(struct FSM_SendCmdTS),&fsdev);
regpcmdts.cmd=GetSet;
regpcmdts.IDDevice=FSM_SettingID;  
FSM_Send_Ethernet_Package(&regpcmdts,sizeof(struct FSM_SendCmdTS),&fsdev);
 //printk( "SendReqest" );
 return len;

}

static ssize_t device_read( struct file *filp, /* include/linux/fs.h */
       char *buffer, /* buffer */
       size_t length, /* buffer length */
       loff_t * offset )
{
  if( *offset != 0 ) {
      return 0;
   }
    
  memcpy(buffer,&fsm_ss,sizeof(fsm_ss));
  *offset =sizeof(fsm_ss);
 return sizeof(fsm_ss);
}

static int deviceset_open( struct inode *inode, struct file *file )
{
 if ( is_device_openset )
  return -EBUSY;
  printk(KERN_INFO "%s",file->f_path.dentry->d_name.name);
 is_device_openset++;

 return SUCCESS;
}

static int deviceset_release( struct inode *inode, struct file *file )
{
 is_device_openset--;
 return SUCCESS;
}


static int deviceset_write( struct file *filp, const char *buff, size_t len, loff_t * off )
{
    int i;
    int j;
struct FSMSSetconfig* scp=(struct FSMSSetconfig*)buff;

    fsmspar.cmd=scp->cmd;
    fsmspar.IDDevice=scp->IDDevice;
    for(i=0;i<srow_cnt;i++)
    {
        for(j=0;j<scolumn_cnt;j++)
           {
            if(fsm_ds.setel[i][j].IDDevice==fsmspar.IDDevice)
            {
            fsmspar.config=&fsm_ds.setel[i][j];
            //printk( KERN_INFO "FSM Send %u %s\n",fsmstate->statel[i][j].devid,fsmstate->statel[i][j].fsmdevcode);
            }
            }
    }
    if(fsmspar.cmd==SetFSMSetting)
    {
        regpcmdts.opcode=SendCmdToServer;
        regpcmdts.countparam=1;
        regpcmdts.CRC=0;
       regpcmdts.cmd=SetSetting;
       regpcmdts.IDDevice=FSM_SettingID;
       scp->config.row=fsmspar.config->row;
       scp->config.column=fsmspar.config->column;
       memcpy(&regpcmdts.Data,&scp->config,sizeof(struct fsm_device_config));
       FSM_Send_Ethernet_Package(&regpcmdts,sizeof(struct FSM_SendCmdTS),&fsdev); 
       printk( KERN_INFO "Set %i",fsmspar.IDDevice );
    }
    if(fsmspar.cmd==GetFSMSetting)
    {
         
    }
 return len;
}

static ssize_t deviceset_read( struct file *filp, /* include/linux/fs.h */
       char *buffer, /* buffer */
       size_t length, /* buffer length */
       loff_t * offset )
{
  if( *offset != 0 ) {
      return 0;
   }

   
   
  memcpy(buffer,fsmspar.config,sizeof(struct fsm_device_config));
  *offset =sizeof(struct fsm_device_config);
 return sizeof(struct fsm_device_config);
}

static struct file_operations fops =
 {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release
 };
 
static struct file_operations fopsset =
 {
  .read = deviceset_read,
  .write = deviceset_write,
  .open = deviceset_open,
  .release = deviceset_release
 };


 
static int __init FSM_ClientModule_init(void)
{
    struct fsm_ethernet_dev fsdev2;
    setservid=22;
    memset(&fsdev,0,sizeof(fsdev));

    dev_add_pack( &FSMClientProtocol_proto );
   regp.IDDevice=(unsigned short)FSM_StatisicID;
   regp.VidDevice=(unsigned char)FSMDeviceStatistic;
   regp.PodVidDevice=(unsigned char)ComputerStatistic;
   regp.KodDevice=(unsigned char)PCx86;
   regp.type=(unsigned char)StatisticandConfig;
   regp.opcode=RegDevice;
   regp.CRC=0;
   
   regset.IDDevice=(unsigned short)FSM_SettingID;
   regset.VidDevice=(unsigned char)FSMDeviceConfig;
   regset.PodVidDevice=(unsigned char)ComputerStatistic;
   regset.KodDevice=(unsigned char)PCx86;
   regset.type=(unsigned char)StatisticandConfig;
   regset.opcode=RegDevice;
   regset.CRC=0;
   
   fsdev.dev=0;
   fsdev.id=FSM_StatisicID;
   fsdev.numdev=1;
   memset(fsdev2.destmac,0xFF,6);
   fsdev2.id=FSM_StatisicID;
   fsdev2.numdev=1;
   fsdev2.dev = first_net_device( &init_net ); 
   
   while (fsdev2.dev)
   {
   FSM_Send_Ethernet_Package(&regp,sizeof(struct FSM_DeviceRegistr),&fsdev2);
   fsdev2.dev = next_net_device( fsdev2.dev );
   }
   
    if (alloc_chrdev_region(&first, 0, 1, "fsmr") < 0) return -1;
    if ((cl = class_create(THIS_MODULE, "fsm")) == NULL)
    {
    unregister_chrdev_region(first, 1);
    return -1;
    }
    if (device_create(cl, NULL, first, NULL, "fsmstatistic") == NULL)
    {
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    return -1;
    }
    cdev_init(&c_dev, &fops);
    if (cdev_add(&c_dev, first, 1) == -1)
    {
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    return -1;
    }
    
    if (alloc_chrdev_region(&firstset, 0, 1, "fsms") < 0) return -1;
    if ((clset = class_create(THIS_MODULE, "fsmsetc")) == NULL)
    {
    unregister_chrdev_region(firstset, 1);
    return -1;
    }
    if (device_create(clset, NULL, firstset, NULL, "fsmset") == NULL)
    {
    class_destroy(clset);
    unregister_chrdev_region(firstset, 1);
    return -1;
    }
    cdev_init(&c_devset, &fopsset);
    if (cdev_add(&c_devset, firstset, 1) == -1)
    {
    device_destroy(clset, firstset);
    class_destroy(clset);
    unregister_chrdev_region(firstset, 1);
    return -1;
    }
   //FSM_DeviceRegister(regp);
   //fsmset_class = class_create( THIS_MODULE, "fsmset" );
   fsmspar.config=&fsm_ds.setel[0][0];
   printk( KERN_INFO "FSMClientProtocol module loaded\n" ); 
   return 0;  
}


static void __exit FSM_ClientModule_exit(void)
{  
    struct FSM_DeviceDelete delp;
    delp.CRC=0;
    delp.IDDevice=FSM_StatisicID;
    delp.opcode=DelLisr;
    FSM_Send_Ethernet_Package(&delp,sizeof(struct FSM_DeviceDelete),&fsdev);
    delp.IDDevice=FSM_SettingID;
    FSM_Send_Ethernet_Package(&delp,sizeof(struct FSM_DeviceDelete),&fsdev);
    dev_remove_pack( &FSMClientProtocol_proto ); 
     cdev_del(&c_dev);
  device_destroy(cl, first);
  class_destroy(cl);
  unregister_chrdev_region(first, 1);
  
   cdev_del(&c_devset);
  device_destroy(clset, firstset);
  class_destroy(clset);
  unregister_chrdev_region(firstset, 1);
  // class_destroy( fsmset_class );
   printk( KERN_INFO "FSM Client module unloaded\n" );  
}
module_init(FSM_ClientModule_init);
module_exit(FSM_ClientModule_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Client Module");
MODULE_LICENSE("GPL");