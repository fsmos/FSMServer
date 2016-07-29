#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct CCKDeviceInfo CCKDev[FSM_CCKTreeSize];
int main(int argc, char **argv)
{
    int i;
    FSM_CCK_Get_Data(CCKDev);
    for(int i=0;i<FSM_CCKTreeSize;i++)
    {
      printf("CCK %u Type %u IP %u.%u.%u.%u Position %u \n",CCKDev[i].id,CCKDev[i].type, CCKDev[i].ip[0], CCKDev[i].ip[1], CCKDev[i].ip[2], CCKDev[i].ip[3], CCKDev[i].Position);  
    }
	
	return 0;
}
