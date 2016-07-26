#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct FSM_SendCmdUserspace fsmdat;

void FSM_GPIO_Ctl_Reset()
{
   fsmdat.IDDevice=FSM_GPIOID;
   fsmdat.cmd=FSM_Reset_Bit;
   FSM_SendCtlCmd(&fsmdat);
}

void FSM_GPIO_Ctl_Eror()
{
   fsmdat.IDDevice=FSM_GPIOID;
   fsmdat.cmd=FSM_Event_Bit;
   FSM_SendCtlCmd(&fsmdat);
}

void FSM_GPIO_Ctl_SetBit(enum FSM_GPIO_Bit_Enum Pin)
{
   fsmdat.IDDevice=FSM_GPIOID;
   fsmdat.cmd=FSM_ON_Bit;
   fsmdat.Data[0]=Pin;
   FSM_SendCtlCmd(&fsmdat);
}

void FSM_GPIO_Ctl_ReSetBit(enum FSM_GPIO_Bit_Enum Pin)
{
   fsmdat.IDDevice=FSM_GPIOID;
   fsmdat.cmd=FSM_OFF_Bit;
   fsmdat.Data[0]=Pin;
   FSM_SendCtlCmd(&fsmdat);
}

void FSM_GPIO_Ctl_Error_ON()
{
   fsmdat.IDDevice=FSM_GPIOID;
   fsmdat.cmd=FSM_Eror_ON_Bit;
   FSM_SendCtlCmd(&fsmdat);
}

void FSM_GPIO_Ctl_Error_OFF()
{
   fsmdat.IDDevice=FSM_GPIOID;
   fsmdat.cmd=FSM_Eror_OFF_Bit;
   FSM_SendCtlCmd(&fsmdat);
}