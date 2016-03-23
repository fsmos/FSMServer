/*!
\file
\brief Драйвер E1
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"

struct FSM_DeviceFunctionTree dft;

void FSM_E1Recive(char* data,short len, struct FSM_DeviceTree* fsmdt)
{
    printk( KERN_INFO "RPack\n" ); 
}

static int __init FSME1Protocol_init(void)
{
   dft.type=(unsigned char)AudioDevice;
   dft.VidDevice=(unsigned char)CommunicationDevice;
   dft.PodVidDevice=(unsigned char)CCK;
   dft.KodDevice=(unsigned char)MN524;
   dft.Proc=FSM_E1Recive;
   FSM_DeviceClassRegister(dft);
   printk( KERN_INFO "FSME1Protocol module loaded\n" ); 
   return 0;  
}

static void __exit FSME1Protocol_exit(void)
{
    FSM_ClassDeRegister(dft);
   printk( KERN_INFO "FSME1Protocol module unloaded\n" );  
}

module_init(FSME1Protocol_init);
module_exit(FSME1Protocol_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM E1 Protocol Module");
MODULE_LICENSE("GPL");