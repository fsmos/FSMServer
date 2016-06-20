#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSMSysCtl.h"
#define DEVPATH "/dev/fsmio"

void FSM_SendCtlCmd(struct FSM_SendCmdUserspace* fsmdat)
{
   int dfd;  
   fsmdat->opcode=PacketFromUserSpace;
   dfd = open(DEVPATH,O_RDWR);
   ioctl(dfd, FSMIOCTL_SendData, fsmdat );
   close(dfd);
}