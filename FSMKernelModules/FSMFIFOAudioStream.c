
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSMAudio/FSM_AudioStream.h"
#include "FSM/FSMEthernet/FSMEthernetHeader.h"

struct FSM_FIFOAS fsmfifoas[FSM_FIFOAudioStreamDeviceTreeSize];
struct FSM_SendAudioData sad;
 
void FSM_FIFOAudioStreamTobuffer(char* Data,short len,int id)
{
    int i=0; 
    struct FSM_SendAudioData * FSMAPk =(struct FSM_SendAudioData *) Data;
struct FSM_FIFOAS* devfifo=&fsmfifoas[FSM_AudioStreamGetFIFODevice(FSMAPk->IDDevice)];
     for(i=0;i<FSMAPk->len;i++)
     {
         if(devfifo->in_count<1024)
         {
         devfifo->inBuffer[devfifo->in_writeptr]=FSMAPk->Data[i];
         devfifo->in_writeptr++;
         if(devfifo->in_writeptr>=1024) devfifo->in_writeptr=0;
         devfifo->in_count++;
         }
     }
}
EXPORT_SYMBOL(FSM_FIFOAudioStreamTobuffer);
int FSM_FIFOAudioStreamRegistr(struct FSM_AudioStream fsmas,unsigned short* idfifo)
{
    int fsmstream,i;
    fsmas.ToUser=FSM_FIFOAudioStreamTobuffer;
    fsmas.TransportDeviceType=FSM_FifoID;
    fsmstream =FSM_AudioStreamRegistr(fsmas);
    if(fsmstream!=-1)
    {
       for(i=0;i<FSM_FIFOAudioStreamDeviceTreeSize;i++)
       {
           if(fsmfifoas[i].reg==0)
           {
               fsmfifoas[i].reg=1;
               fsmfifoas[i].streamid=fsmstream;
               FSM_AudioStreamSetFIFODevice(fsmstream,i);
               *idfifo=i;
               return fsmstream;
           }
       }
    }
    return -1;

}
EXPORT_SYMBOL(FSM_FIFOAudioStreamRegistr);
void FSM_FIFOAudioStreamWrite(char* Data,short len,unsigned short idfifo)
{
    int i=0;
    if(idfifo>=FSM_FIFOAudioStreamDeviceTreeSize) return;
 for(i=0;i<len;i++)
   {
        fsmfifoas[idfifo].outBuffer[fsmfifoas[idfifo].out_count]=Data[i];
       fsmfifoas[idfifo].out_count++;
      if(fsmfifoas[idfifo].out_count>=160)
       {
            sad.IDDevice=fsmfifoas[idfifo].streamid;
            sad.len=160;
            memcpy(sad.Data,fsmfifoas[idfifo].outBuffer,sad.len);
            FSM_AudioStreamToProcess(fsmfifoas[idfifo].streamid,(char*)&sad,sizeof(struct FSM_SendAudioData)-sizeof(sad.Data)+sad.len);
            fsmfifoas[idfifo].out_count-=160;
       }
   }
  
    
   
}
EXPORT_SYMBOL(FSM_FIFOAudioStreamWrite);
int FSM_FIFOAudioStreamRead(char* Data,unsigned short count,unsigned short idfifo)
{
    int i;
    for(i=0;i<count;i++)
    {
        if(fsmfifoas[idfifo].in_count>0)
        {
            Data[i]=fsmfifoas[idfifo].inBuffer[fsmfifoas[idfifo].in_readptr];
            fsmfifoas[idfifo].in_readptr++;
            if(fsmfifoas[idfifo].in_readptr>=1024) fsmfifoas[idfifo].in_readptr=0;
            fsmfifoas[idfifo].in_count--;
            
        }
        else
        {
             Data[i]=0xff;
        }
    }
    return count;
}
EXPORT_SYMBOL(FSM_FIFOAudioStreamRead);
unsigned short FSM_FIFOAudioStreamGetAS(unsigned short idfifo)
{
    return fsmfifoas[idfifo].streamid;
}
EXPORT_SYMBOL(FSM_FIFOAudioStreamGetAS);

static int __init FSM_FIFOAudioStream_init(void)
{
   memset(fsmfifoas,0,sizeof(fsmfifoas));
   sad.opcode=SendAudio;
   printk( KERN_INFO "FSM FIFO Audio Stream Module loaded\n" ); 
   return 0;  
}

static void __exit FSM_FIFOAudioStream_exit(void)
{
   printk( KERN_INFO "FSM FIFO Audio Stream Module unloaded\n" );  
}

module_init(FSM_FIFOAudioStream_init);
module_exit(FSM_FIFOAudioStream_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM FIFO Audio Stream Module");
MODULE_LICENSE("GPL");