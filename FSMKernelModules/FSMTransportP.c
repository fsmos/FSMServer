#include <linux/module.h> 
#include <linux/init.h> 
#include <net/protocol.h> 

int fsm_t_pack_rcv( struct sk_buff *skb ) { 
   printk( KERN_INFO "Packet received with length: %u\n", skb->len ); 
   return skb->len; 
}; 

static struct net_protocol fsm_t_protocol = { 
   .handler = fsm_t_pack_rcv, 
   .err_handler = 0, 
   .no_policy = 0, 
}; 

#define FSM_T_PROTO 96
static int __init fsm_tp_init( void ) { 
   int ret; 
   if( ( ret = inet_add_protocol( &fsm_t_protocol, FSM_T_PROTO ) ) < 0 ) { 
      printk( KERN_INFO "proto init: can't add protocol\n"); 
      return ret; 
   }; 
   printk( KERN_INFO "FSM module loaded\n" ); 
   return 0; 
} 

static void __exit fsm_tp_exit( void ) { 
   inet_del_protocol( &fsm_t_protocol, FSM_T_PROTO ); 
   printk( KERN_INFO "FSM  module unloaded\n" ); 
} 


module_init(fsm_tp_init);
module_exit(fsm_tp_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Transport Protocol Module");
MODULE_LICENSE("GPL");