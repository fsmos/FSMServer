#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include <linux/fs.h> 
//#include <asm/uaccess.h>   // Needed by segment descriptors

unsigned char FSM_CheckUUID(unsigned char* uuid,unsigned char type,unsigned char id)
{
char ruuid[36];
struct file *f; 
int numb;
char filename[100];
int i;

// preempt_disable();
printk( KERN_INFO "UUID Config Open" ); 
sprintf(filename,"/fsm/config/uuid/neobi%u_%u",type,id);
f = filp_open( filename, O_RDONLY, 0 ); 
if( IS_ERR( f ) ) { 
        printk( KERN_INFO "Firmware not found" ); 
        return -1;
} 
numb = kernel_read( f, ruuid, 36,0); 
filp_close( f, NULL ); 
if(!(numb)) return -2;
   
for(i=0;i<36;i++)
{
    if(ruuid[i] != uuid[i])
    {
        return 0;
    }
}
return 1;
}

EXPORT_SYMBOL(FSM_CheckUUID);

static int __init FSMCCKConfigDevice_init(void)
{
    printk(KERN_INFO "FSM CCK Config Device loaded\n");
    return 0;
}
static void __exit FSMCCKConfigDevice_exit(void)
{
    printk(KERN_INFO "FSM CCK Config Device module unloaded\n");
}

module_init(FSMCCKConfigDevice_init);
module_exit(FSMCCKConfigDevice_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM CCK Config Device Module");
MODULE_LICENSE("GPL");