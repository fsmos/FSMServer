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
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

FSM_ADSendEthPack FSM_sendpkt;

#ifdef DEBUG_CALL_STACK
uint64_t debug_this4;
extern uint64_t debug_global;
#define DEBUG_CALL_STACK_SetStack debug_this4 = (debug_this4 << 8)
#define DEBUG_CALL_STACK_THIS 4
#define DEBUG_CALL_STACK_GLOBSET debug_global = (debug_global << 8) | (DEBUG_CALL_STACK_THIS);

typedef enum debug_function {
    init_on = 0x00,
    init_off = 0x01,
    exit_on = 0x02,
    exit_off = 0x03,
    get_asr_init = 0x04,
    get_asr_exit = 0x05,
    get_astu_init = 0x06,
    get_astu_exit = 0x07,
    get_astp_init = 0x08,
    get_astp_exit = 0x09,

} debug_fun;
#endif

struct FSM_AudioStream FSMASDB[FSM_AudioStreamDeviceTreeSize];
/*
 *unsigned int FSM_AudioStrean_Send_Ethernet_Package(void * data, int len, struct fsm_ethernet_dev *fsmdev)
{
    return FSM_Send_Ethernet_Package2(data,len,fsmdev);
}
 */
int FSM_AudioStreamRegistr(struct FSM_AudioStream fsmas)
{
    int i;

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (get_asr_init);
#endif

    for(i = 0; i < FSM_AudioStreamDeviceTreeSize; i++) {
        if(FSMASDB[i].reg == 0) {
            FSMASDB[i].reg = 1;
            FSMASDB[i].iddev = fsmas.iddev;
            FSMASDB[i].ToProcess = fsmas.ToProcess;

            FSMASDB[i].TransportDevice = fsmas.TransportDevice;
            FSMASDB[i].TransportDeviceType = fsmas.TransportDeviceType;
            FSMASDB[i].Data = fsmas.Data;
            FSMASDB[i].IDConnection = 0xffff;
            FSM_sendpkt = FSM_GetAudioStreamCallback();
            switch(fsmas.TransportDeviceType) {
            case FSM_EthernetID2:
                FSMASDB[i].ToUser = (FSM_StreamProcessUser)FSM_sendpkt;
                break;
            case FSM_FifoID:
                FSMASDB[i].ToUser = fsmas.ToUser;
                break;
            }
            printk(KERN_INFO "Registred Stream %u", i);

            return i;
        }
    }

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (get_asr_exit);
#endif
    return -1;
}
EXPORT_SYMBOL(FSM_AudioStreamRegistr);

void FSM_AudioStreamUnRegistr(int id)
{
    FSMASDB[id].reg = 0;
}
EXPORT_SYMBOL(FSM_AudioStreamUnRegistr);

unsigned short FSM_AudioStreamGETIDConnect(int id)
{
    return FSMASDB[id].IDConnection;
}
EXPORT_SYMBOL(FSM_AudioStreamGETIDConnect);

void FSM_AudioStreamSetIDConnect(int id, unsigned short idcon, char type)
{
    FSMASDB[id].IDConnection = idcon;
    FSMASDB[id].typcon = type;
}
EXPORT_SYMBOL(FSM_AudioStreamSetIDConnect);

char FSM_AudioStreamGETTypeConnect(int id)
{
    return FSMASDB[id].typcon;
}
EXPORT_SYMBOL(FSM_AudioStreamGETTypeConnect);

void FSM_AudioStreamToUser(int id, char* Data, short len)
{
#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (get_astu_init);
#endif

    if(id == -1)
        return;
    if(((char*)&FSMASDB[id])[0] == 0) {
        // printk( KERN_INFO "NotStreamID TUn" );
        return;
    }
    if((((char*)&FSMASDB[id])[0] != 0) && (FSMASDB[id].ToUser != 0))
        FSMASDB[id].ToUser(Data, len, FSMASDB[id].TransportDevice);

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (get_astu_exit);
#endif
}
EXPORT_SYMBOL(FSM_AudioStreamToUser);
void FSM_AudioStreamSetToProcess(int id, FSM_StreamProcessProcess fsmtu)
{
    FSMASDB[id].ToProcess = fsmtu;
}
EXPORT_SYMBOL(FSM_AudioStreamSetToProcess);

void FSM_AudioStreamToProcess(int id, char* Data, short len)
{
#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (get_astp_init);
#endif

    if(id == -1)
        return;
    if(((char*)&FSMASDB[id])[0] == 0) {
        // printk( KERN_INFO "NotStreamID TP\n" );
        return;
    }
    if(FSMASDB[id].ToProcess == 0)
        return;
    FSMASDB[id].ToProcess(Data, len);

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (get_astp_exit);
#endif
}
EXPORT_SYMBOL(FSM_AudioStreamToProcess);

int FSM_AudioStreamGetEthernetDevice(int id)
{
    return FSMASDB[id].TransportDevice;
}
EXPORT_SYMBOL(FSM_AudioStreamGetEthernetDevice);

void FSM_AudioStreamSetEthernetDevice(int id, struct fsm_ethernet_dev* edev)
{
    FSMASDB[id].TransportDevice = edev->numdev;
    FSMASDB[id].TransportDeviceType = FSM_EthernetID2;
}
EXPORT_SYMBOL(FSM_AudioStreamSetEthernetDevice);

void FSM_AudioStreamSetFIFODevice(int id, int edev)
{
    FSMASDB[id].TransportDevice = edev;
    FSMASDB[id].TransportDeviceType = FSM_FifoID;
}
EXPORT_SYMBOL(FSM_AudioStreamSetFIFODevice);

int FSM_AudioStreamGetFIFODevice(int id)
{
    return FSMASDB[id].TransportDevice;
}
EXPORT_SYMBOL(FSM_AudioStreamGetFIFODevice);

void* FSM_AudioStreamData(int id)
{
    return FSMASDB[id].Data;
}
EXPORT_SYMBOL(FSM_AudioStreamData);

static int __init FSM_AudioStream_init(void)
{

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (init_on);
#endif

    FSM_RegisterAudioStreamCallback((FSM_StreamProcessSend)FSM_AudioStreamToProcess);
    memset(FSMASDB, 0, sizeof(FSMASDB));
    printk(KERN_INFO "FSM Audio Stream Module loaded\n");

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (init_off);
#endif

    return 0;
}

static void __exit FSM_AudioStream_exit(void)
{

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (exit_on);
#endif

    printk(KERN_INFO "FSM Audio Stream Module unloaded\n");

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (exit_off);
#endif
}

module_init(FSM_AudioStream_init);
module_exit(FSM_AudioStream_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Audio Stream Module");
MODULE_LICENSE("GPL");