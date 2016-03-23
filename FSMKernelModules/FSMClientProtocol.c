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



struct sock *nl_sk = NULL; 

struct fsm_ethernet_dev fsdev;

static unsigned int FSM_Send_Ethernet_Package(struct net_device *dev,void * data, int len, struct fsm_ethernet_dev fsmdev)
{
  struct sk_buff *skb;
  int hlen = LL_RESERVED_SPACE(dev);
  int tlen = dev->needed_tailroom;
  skb = alloc_skb(len + hlen + tlen, GFP_ATOMIC);
  skb_reserve(skb, hlen);
  skb->dev = dev;
  //skb->protocol = fsmdev.eth.h_proto;
  skb_reset_network_header(skb);
  memcpy(skb_put(skb, len),data,len);
  if(dev_hard_header(skb, dev, __constant_htons(FSM_PROTO_ID_R), fsmdev.destmac, dev->dev_addr, skb->len)<0) goto out;
  if(dev_queue_xmit(skb)<0) goto out;
  return 0;

 out:
	kfree_skb(skb);
	return 0;
}


int FSMClientProtocol_pack_rcv( struct sk_buff *skb, struct net_device *dev, 
                   struct packet_type *pt, struct net_device *odev ) { 
   char dts[3];
   
   if (skb->pkt_type == PACKET_OTHERHOST || skb->pkt_type == PACKET_LOOPBACK) return 0;
   printk( KERN_INFO "pck type: %u\n", skb->pkt_type  );
   fsdev.destmac[0]=0xa0;
   fsdev.destmac[1]=0xa1;
   fsdev.destmac[2]=0xa2;
   fsdev.destmac[3]=0xa3;
   fsdev.destmac[4]=0xa4;
   fsdev.destmac[5]=0xa5;
   
   printk( KERN_INFO "packet received with length: %u\n", skb->len );
   dts[0]=0xd1;
   dts[1]=0xd2;
   dts[2]=0xd3;
   
   
   FSM_Send_Ethernet_Package(odev,dts,3,fsdev);
   return skb->len; 
}; 


static struct packet_type FSMClientProtocol_proto = { 
   .type =	cpu_to_be16( FSM_PROTO_ID ),  // may be: __constant_htons( TEST_PROTO_ID ), 
   .func = FSMClientProtocol_pack_rcv, 
}; 




 
static int __init FSMClientProtocol_init(void)
{
   dev_add_pack( &FSMClientProtocol_proto ); 
   printk( KERN_INFO "module loaded\n" ); 
   return 0;  
}

static void __exit FSMClientProtocol_exit(void)
{
    dev_remove_pack( &FSMClientProtocol_proto ); 
   printk( KERN_INFO "module unloaded\n" ); 
      printk(KERN_INFO "exiting hello module\n");  
}

module_init(FSMClientProtocol_init);
module_exit(FSMClientProtocol_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Protocol Module");
MODULE_LICENSE("GPL");