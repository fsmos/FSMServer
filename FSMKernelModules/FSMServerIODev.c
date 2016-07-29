/*!
\file
\brief Модуль командного управления
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/

#define SUCCESS 0 

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/netdevice.h>

#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_SendCmdUserspace fsmdat;

static dev_t first; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

static int device_open( struct inode *inode, struct file *file )
{
   // printk( KERN_INFO "FSM SIOCTLOpen\n" ); 
 return SUCCESS;
}

static int device_release( struct inode *inode, struct file *file )
{
    //printk( KERN_INFO "FSM SIOCTLClose\n" ); 
 return SUCCESS;
}

long device_ioctl(struct file *f, 
                      unsigned int cmd, unsigned long arg ) 
{ 
   struct FSM_DeviceTree* dftv; 
  
   switch( cmd ) 
   { 
      case  FSMIOCTL_SendData: 
         if(copy_from_user( &fsmdat,(void*)arg , sizeof(struct FSM_SendCmdUserspace))) return -EFAULT; 
         dftv=FSM_FindDevice(fsmdat.IDDevice);
         if(dftv!=0)
         {
         dftv->dt->Proc((char*)&fsmdat,sizeof(struct FSM_SendCmdUserspace),dftv,0); 
         if(dftv->debug) 
             printk( KERN_INFO "FSM SIOCTL, \n" ); 
         }
         fsmdat.opcode=PacketToUserSpace;
         if(copy_to_user((void*)arg, &fsmdat,sizeof(struct FSM_SendCmdUserspace))) return -EFAULT; 
        
         break; 
      default: 
         return -ENOTTY; 
   } 
   return 0; 
} 

static struct file_operations fops =
 {
  .open = device_open,
  .release = device_release,
  .unlocked_ioctl = device_ioctl
 };
 
static int __init FSM_SIOCTLModule_init(void)
{
    if (alloc_chrdev_region(&first, 0, 1, "fsmr") < 0) return -1;
    if ((cl = class_create(THIS_MODULE, "fsm")) == NULL)
    {
    unregister_chrdev_region(first, 1);
    return -1;
    }
    if (device_create(cl, NULL, first, NULL, "fsmio") == NULL)
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
   printk( KERN_INFO "FSM SIOCTL module loaded\n" ); 
   return 0;  
}


static void __exit FSM_SIOCTLModule_exit(void)
{  
     cdev_del(&c_dev);
  device_destroy(cl, first);
  class_destroy(cl);
  unregister_chrdev_region(first, 1);
  
   printk( KERN_INFO "FSM SIOCTL module unloaded\n" );  
}
module_init(FSM_SIOCTLModule_init);
module_exit(FSM_SIOCTLModule_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM SIOCTL Module");
MODULE_LICENSE("GPL");