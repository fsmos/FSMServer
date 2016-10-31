#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct FSM_Filter_str FSM_ft;
unsigned int FSM_InRange(struct FSM_Range range,unsigned short value)
{
    if((value>=range.StartAddress)&&(value<=range.StopAddress)) return 0;
    return 0;
}
unsigned int FSM_Filter(struct FSM_DeviceRegistr dt) 
{
 unsigned int res;
 if(FSM_ft.FSM_ID_Filter) if(FSM_InRange(FSM_ft.FSM_ID,dt.IDDevice)) res |= 1;
 if(FSM_ft.FSM_Type_Filter) if(FSM_InRange(FSM_ft.FSM_Type,dt.type)) res |= 2;
 if(FSM_ft.FSM_Vid_Filter) if(FSM_InRange(FSM_ft.FSM_Vid,dt.VidDevice)) res |= 4;
 if(FSM_ft.FSM_PodVid_Filter) if(FSM_InRange(FSM_ft.FSM_PodVid,dt.PodVidDevice)) res |= 8;
 if(FSM_ft.FSM_Kod_Filter) if(FSM_InRange(FSM_ft.FSM_Kod,dt.KodDevice)) res |= 16;
 return 0;
}
EXPORT_SYMBOL(FSM_Filter);

void FSM_FilterLoad(void)
{
    struct file *f; 
    int numb;
    printk( KERN_INFO "Read Filter" ); 
    memset(&FSM_ft,0,sizeof(struct FSM_Filter_str));
    f = filp_open( "/fsm/programm/filter.fsmprg", O_RDONLY, 0 ); 
    if( IS_ERR( f ) ) { 
        printk( KERN_INFO "Filter not found" ); 
        return;
    } 
    numb = kernel_read( f, 0, (char*)&FSM_ft, sizeof(struct FSM_Filter_str) ); 
    filp_close( f, NULL ); 
    if(!(numb)) return;   
}

static int __init FSM_Filter_init(void)
{
    FSM_FilterLoad();   
    printk(KERN_INFO "FSM Filter loaded\n");
    return 0;
}
static void __exit FSM_Filter_exit(void)
{
   printk(KERN_INFO "FSM Filter module unloaded\n");
}
module_init(FSM_Filter_init);
module_exit(FSM_Filter_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Filter Module");
MODULE_LICENSE("GPL");