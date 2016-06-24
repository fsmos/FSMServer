#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h> 
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSM_Client/FSM_client.h"
#include "FSM/FSMDevice/fsm_statusstruct.h"
#include "FSM/FSMSetting/FSM_settings.h"
            
pid_t FSM_SSTP_PID=0;
struct siginfo info;
struct task_struct *task;
struct SendSignalStruct signstr;
void  FSM_EventIOCtl(char* Data,short len , struct fsm_ioctl_struct* ioctl)
{
    struct FSM_SendCmdUserspace* fsm_scus=(struct FSM_SendCmdUserspace*)Data;
    switch(fsm_scus->cmd)
    {
        case FSM_SSTP_SetPid:
        info.si_signo = SIGUSR1;
        info.si_errno = 0;
        info.si_code = SI_USER;
        FSM_SSTP_PID=((pid_t*)fsm_scus->Data)[0] ; 
        printk( KERN_INFO "FSM Set Setting %u, ",FSM_SSTP_PID ); 
        //task = pid_task(find_pid_ns(FSM_SSTP_PID, &init_pid_ns), PIDTYPE_PID);
        //task = pid_task(find_vpid(FSM_SSTP_PID),PIDTYPE_PID);
        task = pid_task(find_vpid(FSM_SSTP_PID),PIDTYPE_PID);
        break;
        case FSM_SSTP_GetEvent:
        memcpy(fsm_scus->Data,&signstr,sizeof(struct SendSignalStruct));
        printk( KERN_INFO "GEvent" ); 
        break;
    }
}
int FSM_SendSignalToPipe_thread(void * Data)
{
    char id[10];
    struct SendSignalStruct* datas= (struct SendSignalStruct*)Data;
    char *argv[] = {"fsmsstd",datas->pipe, datas->id, NULL };
    char *envp[] = { NULL };
    
    
    sprintf(id,"%u",datas->id);
    call_usermodehelper("/bin/fsmsstd",argv,envp,UMH_WAIT_EXEC );
    return 0;
}

int FSM_SendSignalToPipe(char* pipe, int signal)
{
   
    signstr.id=signal;
    strcpy(signstr.pipe,pipe);
    if(FSM_SSTP_PID) send_sig_info(SIGUSR1, &info, task);
    //send_sig_info( SIGUSR1, FSM_SSTP_PID, 0 ); 
    //pid = kthread_run(FSM_SendSignalToPipe_thread, &signstr, "FSM_SendSignalToPipe" ); /* запускаем новый поток */
    //FSM_SendSignalToPipe_thread(&signstr);
    return 0; 
}
EXPORT_SYMBOL(FSM_SendSignalToPipe);


static int __init FSMSendSigTP_init(void)
{
   FSM_RegisterIOCtl(FSM_EventIOCtlId,FSM_EventIOCtl);
   FSM_SendSignalToPipe("fsmstat",2);
   printk( KERN_INFO "FSM Send Signal To Pipe loaded\n" ); 

   return 0;  
}
static void __exit FSMSendSigTP_exit(void)
{  
   FSM_DeleteIOCtl(FSM_EventIOCtlId);
   printk( KERN_INFO "FSM Send Signal To Pipe unloaded\n" );
}

MODULE_LICENSE("GPL");
module_init(FSMSendSigTP_init);
module_exit(FSMSendSigTP_exit);