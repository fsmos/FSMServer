#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include <FSM/FSMDevice/FSME1Cas.h>

struct FSME1CAS fsmcas[FSM_E1CasTreeSize];

#ifdef DEBUG_CALL_STACK
uint64_t debug_this8;
extern uint64_t debug_global;
#define DEBUG_CALL_STACK_SetStack debug_this8 = (debug_this8 << 8)
#define DEBUG_CALL_STACK_THIS 8
#define DEBUG_CALL_STACK_GLOBSET debug_global = (debug_global << 8) | (DEBUG_CALL_STACK_THIS);

typedef enum debug_function {
    init_on = 0x00,
    init_off = 0x01,
    exit_on = 0x02,
    exit_off = 0x03,
    get_cas_handl_init = 0x04,
    get_cas_handl_exit = 0x05,
    get_cas_reg_init = 0x04,
    get_cas_reg_exit = 0x05,

} debug_fun;
#endif
void FSMCASHandler(char* Data, short len)
{

// struct FSM_SendAudioData* indat=(struct FSM_SendAudioData*) Data;
// struct FSME1CAS* casdata =(struct FSME1CAS*)FSM_AudioStreamData(indat->IDDevice);

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (get_cas_handl_init);
#endif

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (get_cas_handl_exit);
#endif
}

int32_t FSMCASRegister(void)
{
    int i;
    struct FSM_AudioStream fsmas;

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (get_cas_reg_init);
#endif

    for(i = 0; i < FSM_E1CasTreeSize; i++) {
        if(fsmcas[i].reg == 0) {
            fsmcas[i].reg = 1;
            fsmas.ToProcess = FSMCASHandler;
            fsmas.TransportDevice = 0;
            fsmas.TransportDeviceType = FSM_FifoID;
            fsmas.Data = &fsmcas[i];
            fsmcas[i].idstream = FSM_AudioStreamRegistr(fsmas);
            return i;
        }
    }

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (get_cas_reg_exit);
#endif

    return -1;
}

void FSMCASUnRegister(uint16_t idcon)
{
    fsmcas[idcon].reg = 0;
}

uint16_t FSM_CAS_GetStream(uint16_t idcon)
{
    return fsmcas[idcon].idstream;
}

static int __init FSME1CAS1Protocol_init(void)
{

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (init_on);
#endif
    memset(&fsmcas, 0, sizeof(fsmcas));
    printk(KERN_INFO "FSME1CAS1 module loaded\n");

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (init_off);
#endif

    return 0;
}

static void __exit FSME1CAS1Protocol_exit(void)
{
#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_GLOBSET
    DEBUG_CALL_STACK_SetStack | (exit_on);
#endif

    printk(KERN_INFO "FSME1CAS1 module unloaded\n");

#ifdef DEBUG_CALL_STACK
    DEBUG_CALL_STACK_SetStack | (exit_off);
#endif
}

module_init(FSME1CAS1Protocol_init);
module_exit(FSME1CAS1Protocol_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM E1 Protocol Module");
MODULE_LICENSE("GPL");