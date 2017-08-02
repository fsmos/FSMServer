#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kthread.h>

#include <linux/errno.h>
#include <linux/types.h>

#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/in.h>

#include <linux/delay.h>

#include "FSM/FSMDevice/FSM_DeviceProcess.h"


#define DEFAULT_PORT 2325
#define CONNECT_PORT 23
#define MODULE_NAME "FSM TCPServer"
#define INADDR_SEND INADDR_LOOPBACK



static int __init FSM_TCPServer_init(void)
{    
    printk(KERN_INFO "FSM TCPServer loaded\n");
    return 0;
}
static void __exit FSM_TCPServer_exit(void)
{
    
    printk(KERN_INFO "FSM TCPServer unloaded\n");
}

module_init(FSM_TCPServer_init);
module_exit(FSM_TCPServer_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM TCP Server Module");
MODULE_LICENSE("GPL");