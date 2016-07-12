#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_DeviceFunctionTree dft;

void FSM_ControlDeviceRecive(char* data,short len,  struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
    
}
static int __init FSMControlDevice_init(void)
{
   dft.aplayp=0;
   dft.type=(unsigned char)ControlMachine;
   dft.VidDevice=(unsigned char)Computer;
   dft.PodVidDevice=(unsigned char)PC;
   dft.KodDevice=(unsigned char)ARM;
   dft.Proc=FSM_ControlDeviceRecive;
   dft.config_len=0;
   FSM_DeviceClassRegister(dft);
   printk( KERN_INFO "FSM ControlDevice loaded\n" ); 
   FSM_SendEventToAllDev(FSM_ControlDeviceRun);
   return 0;  
}
static void __exit FSMControlDevice_exit(void)
{  
   FSM_ClassDeRegister(dft);
   printk( KERN_INFO "FSM ControlDevice module unloaded\n" );
}

module_init(FSMControlDevice_init);
module_exit(FSMControlDevice_exit);