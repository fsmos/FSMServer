#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct FSM_SendCmdUserspace fsmdat;

void FSM_CTL_flash_Start(unsigned short IDDevice)
{
   fsmdat.opcode=PacketToDevice;
   fsmdat.IDDevice=FSM_FlashID;
   fsmdat.cmd=FSM_Flash_CTL_Flash;
   ((unsigned short*)fsmdat.Data)[0]=IDDevice;
   FSM_SendCtlCmd(&fsmdat);
}