#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

//#define MAX_VALUE_5V (2271)
//#define MIN_VALUE_5V 1861

#define MAX_VALUE_5V (2476)
#define MIN_VALUE_5V (1657)

//#define MAX_VALUE_N5V (1141)
//#define MIN_VALUE_N5V (930)

#define MAX_VALUE_N5V (1241)
#define MIN_VALUE_N5V (826)

//#define MAX_VALUE_N60V (1530)
//#define MIN_VALUE_N60V (1026)

#define MAX_VALUE_N60V (1782)
#define MIN_VALUE_N60V (774)


//#define MAX_VALUE_90V 3351
//#define MIN_VALUE_90V 744

#define MAX_VALUE_90V (4654)
#define MIN_VALUE_90V (558)

#define MAX_VALUE_220V 64
#define MIN_VALUE_220V 51


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

char FSM_CCK_MN111_Read_Voltage_State(enum FSMMN111Command fsmcmd,unsigned short IDDevice)
{
   unsigned short value;
   fsmdat.IDDevice=IDDevice;
   fsmdat.cmd=fsmcmd;
   FSM_SendCtlCmd(&fsmdat);
   value=((unsigned short*)fsmdat.Data)[0];
   switch(fsmcmd)
   {
    case FSM_Read_MN111_Power_5V:
    if((MAX_VALUE_5V>value)&&(MIN_VALUE_5V<value)) return 0;
    else return 1;
    break;
    case FSM_Read_MN111_Power_n5V:
    if((MAX_VALUE_N5V>value)&&(MIN_VALUE_N5V<value)) return 0;
    else return 1;
    break;
    case FSM_Read_MN111_Power_n60V:
    if((MAX_VALUE_N60V>value)&&(MIN_VALUE_N60V<value)) return 0;
    else return 1;
    break;
    case FSM_Read_MN111_Power_90V:
    if((MAX_VALUE_90V>value)&&(MIN_VALUE_90V<value)) return 0;
    else return 1;
    break;
    case FSM_Read_MN111_Power_220V:
    if((MAX_VALUE_220V>value)&&(MIN_VALUE_220V<value)) return 0;
    else return 1;
    break;
    default:
    return 0;
    break;
   }
}