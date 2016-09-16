#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct FSM_SendCmdUserspace fsmdat;

void FSM_Get_Setting_List_Count(unsigned short IDDevice,struct FSM_SetTreeGetListCount* SetMass)
{
   fsmdat.opcode=PacketToDevice;
   fsmdat.IDDevice=FSM_TreeSettingID;
   fsmdat.cmd=FSM_DevTreeSetGetCount;
   ((unsigned short*)fsmdat.Data)[0]=IDDevice;
   FSM_SendCtlCmd(&fsmdat);
   
   memcpy(SetMass,fsmdat.Data,sizeof(struct FSM_SetTreeGetListCount));
}
void FSM_Get_Setting_List_Item(struct FSM_SetTreeGetList* ReadMass,struct FSM_SetTreeElementFS* SetItem)
{
   fsmdat.opcode=PacketToDevice;
   fsmdat.IDDevice=FSM_TreeSettingID;
   fsmdat.cmd=FSM_DevTreeSetGet;
   memcpy(fsmdat.Data,ReadMass,sizeof(struct FSM_SetTreeGetList));
   FSM_SendCtlCmd(&fsmdat);
   memcpy(SetItem,fsmdat.Data,sizeof(struct FSM_SetTreeElementFS));
}

void FSM_Get_Item_Rq(struct FSM_SetTreeReadElement* in)
{
   fsmdat.opcode=PacketToDevice;
   fsmdat.IDDevice=FSM_TreeSettingID;
   fsmdat.cmd=FSM_DevTreeSetReadReqest;
   memcpy(fsmdat.Data,in,sizeof(struct FSM_SetTreeReadElement));
   FSM_SendCtlCmd(&fsmdat);
}

int FSM_Get_Item_Read(unsigned short IDDevice,char* Data)
{
   fsmdat.opcode=PacketToDevice;
   fsmdat.IDDevice=FSM_TreeSettingID;
   fsmdat.cmd=FSM_DevTreeSetReadReqest;
   ((unsigned short*)fsmdat.Data)[0]=IDDevice;
   FSM_SendCtlCmd(&fsmdat);
   memcpy(Data,fsmdat.Data,fsmdat.countparam);
   return fsmdat.countparam;
}
void FSM_Set_Item(struct FSM_SetTreeWriteElement* in)
{
   fsmdat.opcode=PacketToDevice;
   fsmdat.IDDevice=FSM_TreeSettingID;
   fsmdat.cmd=FSM_DevTreeSetReadReqest;
   memcpy(fsmdat.Data,in,sizeof(struct FSM_SetTreeWriteElement));
   FSM_SendCtlCmd(&fsmdat);
}