#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Python.h>
#include "libfsmgetccklist.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct CCKDeviceInfo CCKDev[FSM_CCKTreeSize];
char Packet[5000];
const char* fsm_dev_types[]=
{
    "n",
    "MN921",
    "MN825",
    "PO07",
    "PO08",
    "PO06",
    "MN524",
    "MN111",
    "MN401"
};
const char* fsm_firmware_state[]=
{
    "Ok",
    "Error",
    "Error",
};
PyObject * getccklist(PyObject * self)
{
    int i;
    FSM_CCK_Get_Data(CCKDev);
    strcpy(Packet,"{ \"devices\":[");
    for(i=0;i<FSM_CCKTreeSize;i++)
    {
      sprintf(Packet + strlen(Packet), "{\"CCK\":\"%u\",\"Type\":\"%s\",\"IP\":\"%u.%u.%u.%u\",\"Position\":\"%u\",\"CRC32\":\"0x%08x\",\"Mem\":\"%u\",\"DTS\":\"%u\",\"Ch\":\"%u\",\"Ver\":\"%u.%u.%u\",\"FW St\":\"%s\",\"Bd\":\"%u\" ,\"AS\":\"%u\"},",CCKDev[i].id,fsm_dev_types[CCKDev[i].type], CCKDev[i].ip[0], CCKDev[i].ip[1], CCKDev[i].ip[2], CCKDev[i].ip[3], CCKDev[i].Position,CCKDev[i].crc32,CCKDev[i].ramstate,CCKDev[i].dstlen,CCKDev[i].channel,CCKDev[i].ver1,CCKDev[i].ver2,CCKDev[i].ver3,fsm_firmware_state[CCKDev[i].crcerror],CCKDev[i].id_build,CCKDev[i].audiostreamid);  
    }
   sprintf(Packet + strlen(Packet), "{\"CCK\":\"%u\",\"Type\":\"%s\",\"IP\":\"%u.%u.%u.%u\",\"Position\":\"%u\",\"CRC32\":\"0x%08x\",\"Mem\":\"%u\",\"DTS\":\"%u\",\"Ch\":\"%u\",\"Ver\":\"%u.%u.%u\",\"FW St\":\"%s\",\"Bd\":\"%u\" ,\"AS\":\"%u\"}",0,"MN401", 0, 0, 0,0, 10,0,0,0,0,1,0,0,fsm_firmware_state[0],0,0);  
   strcat(Packet,"]}");
   return PyUnicode_FromFormat(Packet);
}
