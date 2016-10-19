#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct CCKDeviceInfo CCKDev[FSM_CCKTreeSize];
const char* fsm_dev_types[]=
{
    "n",
    "MN921",
    "MN825",
    "PO07",
    "PO08",
    "PO06",
    "MN524",
    "MN111"
};
const char* fsm_firmware_state[]=
{
    "Ok",
    "Error",
    "Error",
};
int main(int argc, char **argv)
{
    int i;
    FSM_CCK_Get_Data(CCKDev);
    for(i=0;i<FSM_CCKTreeSize;i++)
    {
      printf("CCK %u Type %s IP %u.%u.%u.%u Position %u CRC32:0x%08x Memory: %u DTS %u Ch %u Ver %u.%u.%u FW St:%s Build: %u \n",CCKDev[i].id,fsm_dev_types[CCKDev[i].type], CCKDev[i].ip[0], CCKDev[i].ip[1], CCKDev[i].ip[2], CCKDev[i].ip[3], CCKDev[i].Position,CCKDev[i].crc32,CCKDev[i].ramstate,CCKDev[i].dstlen,CCKDev[i].channel,CCKDev[i].ver1,CCKDev[i].ver2,CCKDev[i].ver3,fsm_firmware_state[CCKDev[i].crcerror],CCKDev[i].id_build);  
    }
	
	return 0;
}
