/*!
\file
\brief Модуль управления аудиопотоками
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
#include "FSM/FSMAudio/FSM_AudioStream.h"
#include "FSM/FSMEthernet/FSMEthernetHeader.h"

FSM_ADSendEthPack FSM_sendpkt;

struct FSM_AudioStream FSMASDB[FSM_AudioStreamDeviceTreeSize];
 unsigned int FSM_AudioStrean_Send_Ethernet_Package(void * data, int len, struct fsm_ethernet_dev *fsmdev)
 {
     FSM_Send_Ethernet_Package2(data,len,fsmdev);
 }
int FSM_AudioStreamRegistr(struct FSM_AudioStream fsmas)
{
    int i;
    for(i=0;i<FSM_AudioStreamDeviceTreeSize;i++)
    {
        if(FSMASDB[i].reg==0)
        {
            FSMASDB[i].reg=1;
            FSMASDB[i].iddev=fsmas.iddev;
            FSMASDB[i].ToProcess=fsmas.ToProcess;
           
            FSMASDB[i].TransportDevice=fsmas.TransportDevice;
            FSMASDB[i].TransportDeviceType=fsmas.TransportDeviceType;
            FSMASDB[i].Data=fsmas.Data;
            FSMASDB[i].IDConnection=0xffff;
            FSM_sendpkt=FSM_GetAudioStreamCallback();
            switch(fsmas.TransportDeviceType)
            {
            case FSM_EthernetID: 
            FSMASDB[i].ToUser=FSM_sendpkt;
            break;
            }
            printk( KERN_INFO "Registred Stream %u",i ); 

            return i;
        }
    }
    return -1;
}
EXPORT_SYMBOL(FSM_AudioStreamRegistr);


void  FSM_AudioStreamUnRegistr(int id)
{
    FSMASDB[id].reg=0;
}
EXPORT_SYMBOL(FSM_AudioStreamUnRegistr);

unsigned short FSM_AudioStreamGETIDConnect(int id)
{
    return FSMASDB[id].IDConnection;
}
EXPORT_SYMBOL(FSM_AudioStreamGETIDConnect);

void FSM_AudioStreamSetIDConnect(int id,unsigned short idcon,char type)
{
    FSMASDB[id].IDConnection=idcon;
    FSMASDB[id].typcon=type;
}
EXPORT_SYMBOL(FSM_AudioStreamSetIDConnect);

char FSM_AudioStreamGETTypeConnect(int id)
{
    return FSMASDB[id].typcon;
}
EXPORT_SYMBOL(FSM_AudioStreamGETTypeConnect);

void FSM_AudioStreamToUser(int id,char* Data,short len)
{
    if(id==-1) return;
    if(((char*)&FSMASDB[id])[0]==0)
    { 
    // printk( KERN_INFO "NotStreamID TUn" ); 
    return;
    }
    if((((char*)&FSMASDB[id])[0]!=0)&&(FSMASDB[id].ToUser!=0)) FSMASDB[id].ToUser(Data,len, FSMASDB[id].TransportDevice);
}

EXPORT_SYMBOL(FSM_AudioStreamToUser);
void FSM_AudioStreamToProcess(int id,char* Data,short len)
{
    if(id==-1) return;
    if(((char*)&FSMASDB[id])[0]==0) 
        {
               //printk( KERN_INFO "NotStreamID TP\n" ); 
            return;
        }
      FSMASDB[id].ToProcess(Data,len);
}
EXPORT_SYMBOL(FSM_AudioStreamToProcess);

struct fsm_ethernet_dev* FSM_AudioStreamGetEthernetDevice(int id)
{
    return (struct fsm_ethernet_dev* )FSMASDB[id].TransportDevice;
}
EXPORT_SYMBOL(FSM_AudioStreamGetEthernetDevice);

void FSM_AudioStreamSetEthernetDevice(int id,struct fsm_ethernet_dev* edev)
{
FSMASDB[id].TransportDevice=edev;
FSMASDB[id].TransportDeviceType=FSM_EthernetID;
}
EXPORT_SYMBOL(FSM_AudioStreamSetEthernetDevice);
void* FSM_AudioStreamData(int id)
{
    return FSMASDB[id].Data;
}
EXPORT_SYMBOL(FSM_AudioStreamData);

static int __init FSM_AudioStream_init(void)
{
    FSM_RegisterAudioStreamCallback(FSM_AudioStreamToProcess);
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