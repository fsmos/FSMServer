#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct FSM_SendCmdUserspace fsmdat;

void FSM_CCK_Get_Data(struct CCKDeviceInfo* CCKMass)
{
   fsmdat.opcode=PacketToDevice;
   fsmdat.IDDevice=FSM_CCKControlID;
   fsmdat.cmd=FSM_CCKGetInfo;
   FSM_SendCtlCmd(&fsmdat);
   memcpy(CCKMass,fsmdat.Data,sizeof(struct CCKDeviceInfo)*FSM_CCKTreeSize);
}