#include <stdio.h>
#include <stdlib.h>
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/fcmprotocol.h"
struct FSM_SendCmdUserspace fsmdat;
int main(int argc, char **argv)
{
    int i;
    if(argc<3)
    {
        printf("Input Eror\n");
        return 0;
    }
    fsmdat.IDDevice=strtol(argv[1],0,16);
    printf("ID Dev %u\n",fsmdat.IDDevice);
    fsmdat.cmd=strtol(argv[2],0,16);
    fsmdat.countparam=argc-3;
    printf("Cmd %u\n",fsmdat.cmd);
    for(i=0;i<argc-3;i++)
    {
        fsmdat.Data[i]=strtol(argv[i+3],0,16);
        printf("Data Input %u: 0x%02x \n",i,fsmdat.Data[i]);
    }
    printf("\n \n");
    FSM_SendCtlCmd(&fsmdat);
    for(i=0;i<fsmdat.countparam;i++)
    {
        printf("Data Output %u: 0x%02x \n",i,fsmdat.Data[i]);
    }
	return 0;
}
