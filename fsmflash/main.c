#include <stdio.h>
#include <stdlib.h>
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
int main(int argc, char **argv)
{
    unsigned short id=atoi(argv[1]);
    FSM_CTL_flash_Start(id);
	return 0;
}
