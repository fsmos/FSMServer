#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

int main(int argc, char **argv)
{
    if(argc>2)
    {
       unsigned short id=atoi(argv[1]);
       if(strcmp(argv[2], "onaudio")==0)
       {
         FSM_CCK_PO07_SendCMD_Set(FSMPo07AudioRun,id);
       }
       else if(strcmp(argv[2], "offaudio")==0)
       {
        FSM_CCK_PO07_SendCMD_ReSet(FSMPo07AudioRun,id);
       }
       else if(strcmp(argv[2], "reset")==0)
       {
        FSM_CCK_PO07_SendCMD(FSMPo07Reset,id);
       }
       else if(strcmp(argv[2], "reregister")==0)
       { 
        FSM_CCK_PO07_SendCMD(FSMPo07Reregister,id);
       }
    }
	return 0;
}
