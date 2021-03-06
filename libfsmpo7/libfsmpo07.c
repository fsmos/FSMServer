#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct FSM_SendCmdUserspace fsmdat;

void FSM_CCK_PO07_SendCMD(enum FSMPO07Command fsmcmd,unsigned short IDDevice)
{
   fsmdat.IDDevice=IDDevice;
   fsmdat.cmd=fsmcmd;
   FSM_SendCtlCmd(&fsmdat);
}

void FSM_CCK_PO07_SendCMD_Set(enum FSMPO07Command fsmcmd,unsigned short IDDevice)
{
   fsmdat.IDDevice=IDDevice;
   fsmdat.cmd=fsmcmd;
   fsmdat.Data[0]=1;
   FSM_SendCtlCmd(&fsmdat);
}
void FSM_CCK_PO07_SendCMD_ReSet(enum FSMPO07Command fsmcmd,unsigned short IDDevice)
{
   fsmdat.IDDevice=IDDevice;
   fsmdat.cmd=fsmcmd;
   fsmdat.Data[0]=0;
   FSM_SendCtlCmd(&fsmdat);
}