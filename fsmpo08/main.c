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
         FSM_CCK_PO08_SendCMD_Set(FSMPo08AudioRun,id);
       }
       else if(strcmp(argv[2], "offaudio")==0)
       {
        FSM_CCK_PO08_SendCMD_ReSet(FSMPo08AudioRun,id);
       }
       else if(strcmp(argv[2], "reset")==0)
       {
        FSM_CCK_PO08_SendCMD(FSMPo08Reset,id);
       }
       else if(strcmp(argv[2], "reregister")==0)
       { 
        FSM_CCK_PO08_SendCMD(FSMPo08Reregister,id);
       }
    }
	return 0;
}
