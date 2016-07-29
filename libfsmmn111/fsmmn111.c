#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct FSM_SendCmdUserspace fsmdat;

float FSM_ADC_IntToVoltage(unsigned int Value, float Uref, int Ucontr, float Usred ){
	return (Value*Uref*Ucontr)/(4096 * Usred);
};
void FSM_CCK_MN111_Reqest_Voltage(enum FSMMN111Command fsmcmd,unsigned short IDDevice)
{
   fsmdat.IDDevice=IDDevice;
   fsmdat.cmd=fsmcmd;
   FSM_SendCtlCmd(&fsmdat);
}
float FSM_CCK_MN111_Read_Voltage(enum FSMMN111Command fsmcmd,unsigned short IDDevice)
{
   unsigned short value;
   fsmdat.IDDevice=IDDevice;
   fsmdat.cmd=fsmcmd;
   FSM_SendCtlCmd(&fsmdat);
   value=((unsigned short*)fsmdat.Data)[0];
   switch(fsmcmd)
   {
    case FSM_Read_MN111_Power_5V:
    return FSM_ADC_IntToVoltage(value,3.3,5,1.64);
    break;
    case FSM_Read_MN111_Power_n5V:
    return FSM_ADC_IntToVoltage(value,3.3,-5,0.996);
    break;
    case FSM_Read_MN111_Power_n60V:
    return FSM_ADC_IntToVoltage(value,3.3,-60,-1.08);
    break;
    case FSM_Read_MN111_Power_90V:
    return FSM_ADC_IntToVoltage(value,3.3,-90,-1.465);
    break;
    case FSM_Read_MN111_Power_220V:
    return 0.3725f*value;
    break;
    default:
    return 0;
    break;
   }
   /*
    switch(fsmcmd)
   {
    case FSM_Read_MN111_Power_5V:
    return value*0.002441406f;
    break;
    case FSM_Read_MN111_Power_n5V:
    return -1*value*0.004882813f;
    break;
    case FSM_Read_MN111_Power_n60V:
    return -1*value*0.05859375f;
    break;
    case FSM_Read_MN111_Power_90V:
    return value*0.043945312f;
    break;
    case FSM_Read_MN111_Power_220V:
    return 0.3725*value;
    break;
    default:
    return 0;
    break;
   }
   */
   
}