#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSMAudio/FSM_AudioStream.h"

struct FSM_AudioStream FSMASDB[FSM_AudioStreamDeviceTreeSize];


static int __init FSM_AudioStream_init(void)
{
   memset(FSMASDB,0,sizeof(FSMASDB));
   printk( KERN_INFO "FSM Audio Stream Module loaded\n" ); 
   return 0;  
}

static void __exit FSM_AudioStream_exit(void)
{
   printk( KERN_INFO "FSM Audio Stream Module unloaded\n" );  
}

module_init(FSM_AudioStream_init);
module_exit(FSM_AudioStream_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Audio Stream Module");
MODULE_LICENSE("GPL");