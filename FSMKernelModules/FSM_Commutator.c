/*!
\file
\brief Модуль коммутатор
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_P2P_abonent FSM_P2P_fsmabon[FSM_P2P_abonent_count];
struct FSM_opov_abonent FSM_opov_fsmabon[FSM_opov_abonent_count];

unsigned short FSM_P2P_Connect(unsigned short id1, unsigned short id2)
{
    int i = 0;

    for(i = 0; i < FSM_P2P_abonent_count; i++) {
        if(FSM_P2P_fsmabon[i].reg == 0) {
            FSM_P2P_fsmabon[i].reg = 1;
            FSM_P2P_fsmabon[i].idstream1 = id1;
            FSM_P2P_fsmabon[i].idstream2 = id2;
            FSM_P2P_fsmabon[i].idcon = i;
            FSM_AudioStreamSetIDConnect(id1, i, p2p);
            FSM_AudioStreamSetToProcess(id1, FSM_Commutator_Process);
            FSM_AudioStreamSetIDConnect(id2, i, p2p);
            FSM_AudioStreamSetToProcess(id2, FSM_Commutator_Process);
            return i;
        }
    }

    return 0xffff;
}
EXPORT_SYMBOL(FSM_P2P_Connect);

unsigned short FSM_Opov_Connect(unsigned short idorg, unsigned short* id,unsigned short count)
{
    int i = 0;
    int j=0;

    for(i = 0; i < FSM_opov_abonent_count; i++) {
        if(FSM_opov_fsmabon[i].reg == 0) {
            FSM_opov_fsmabon[i].reg = 1;
            FSM_opov_fsmabon[i].idorg = idorg;
            FSM_opov_fsmabon[i].idcon = i;
            FSM_opov_fsmabon[i].count = count;
            for(j=0;j<count;j++) FSM_opov_fsmabon[i].idstreams[j]=id[j];
            FSM_AudioStreamSetIDConnect(idorg, i, opov);
            FSM_AudioStreamSetToProcess(idorg, FSM_Commutator_Process);
            return i;
        }
    }

    return 0xffff;
}
EXPORT_SYMBOL(FSM_Opov_Connect);
void FSM_Opov_Add(unsigned short idopov, unsigned short id)
{

    FSM_opov_fsmabon[idopov].idstreams[FSM_opov_fsmabon[idopov].count]=id;
    FSM_opov_fsmabon[idopov].count++;
}
EXPORT_SYMBOL(FSM_Opov_Add);

void FSM_P2P_Disconnect(unsigned short idcon)
{
    FSM_P2P_fsmabon[idcon].reg = 0;
}
EXPORT_SYMBOL(FSM_P2P_Disconnect);

void FSM_opov_Disconnect(unsigned short idcon)
{
    FSM_opov_fsmabon[idcon].reg = 0;
}
EXPORT_SYMBOL(FSM_opov_Disconnect);

void FSM_Commutator_Process(char* data, short len)
{
    struct FSM_SendAudioData* FSMAPk = (struct FSM_SendAudioData*)data;
    unsigned short idcon;
    int i;
    
    idcon = FSM_AudioStreamGETIDConnect(FSMAPk->IDDevice);
    if(idcon == 0xffff)
        return;
        
    switch(FSM_AudioStreamGETTypeConnect(FSMAPk->IDDevice)) {
    case p2p:
        if(FSMAPk->IDDevice == FSM_P2P_fsmabon[idcon].idstream1) {
            FSMAPk->IDDevice = FSM_P2P_fsmabon[idcon].idstream2;
            FSM_AudioStreamToUser(
                FSM_P2P_fsmabon[idcon].idstream2, data, sizeof(struct FSM_SendAudioData) - sizeof(FSMAPk->Data) + FSMAPk->len);
        } else {
            FSMAPk->IDDevice = FSM_P2P_fsmabon[idcon].idstream1;
            FSM_AudioStreamToUser(FSM_P2P_fsmabon[idcon].idstream1,
                                  (char*)FSMAPk,
                                  sizeof(struct FSM_SendAudioData) - sizeof(FSMAPk->Data) + FSMAPk->len);
        }
        break;
     case opov:
           
           for(i=0;i<FSM_opov_fsmabon[idcon].count;i++)
               {
                   FSMAPk->IDDevice = FSM_opov_fsmabon[idcon].idstreams[i];
                   FSM_AudioStreamToUser(FSM_opov_fsmabon[idcon].idstreams[i], data, sizeof(struct FSM_SendAudioData) - sizeof(FSMAPk->Data) + FSMAPk->len);
               }
        break;
    }
    // fsmabon[idcon].idcon
}
EXPORT_SYMBOL(FSM_Commutator_Process);

static int __init FSM_Commutator_init(void)
{
    printk(KERN_INFO "FSM Commutator Module loaded\n");
    return 0;
}

static void __exit FSM_Commutator_exit(void)
{
    printk(KERN_INFO "FSM Commutator Module unloaded\n");
}

module_init(FSM_Commutator_init);
module_exit(FSM_Commutator_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Commutator Module");
MODULE_LICENSE("GPL");