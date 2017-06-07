#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct FSM_SendCmdUserspace fsmdat;

int main()
{
    int listener;
    struct sockaddr_in si_me, si_other;
    unsigned short* bufrd;
    char buf[1512];
    int recv_len;
    int slen = sizeof(si_other);
    printf("PRG");
    listener = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(listener < 0)
    {
        printf("socket");
        exit(1);
    }
    
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(7777);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&si_me, sizeof(si_me)) < 0)
    {
        printf("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);
        
        if ((recv_len = recvfrom(listener, buf, 1512, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            printf("recvfrom()");
        }
        
         printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));         
         bufrd = (unsigned short*)buf;
         unsigned short iduss = *bufrd ;
         bufrd++;
         unsigned short cnt = *bufrd ;
         bufrd++;
         unsigned short type = *bufrd ;
         bufrd++;
         if(type == 0xAAAA)
         {
             fsmdat.opcode=PacketToDevice;
             fsmdat.IDDevice=FSM_CCKControlID;
             fsmdat.cmd=FSM_CCKGetInfo;
             FSM_SendCtlCmd(&fsmdat);
             if (sendto(listener, fsmdat.Data, (sizeof(struct CCKDeviceInfo)*FSM_CCKTreeSize), 0, (struct sockaddr*) &si_other, slen) == -1)
             {
               printf("sendto()");
             }
             continue;
         }
         fsmdat.IDDevice=iduss;
         if(type == 0x00AA)  fsmdat.cmd=FSMMN825R168100KB_Packet;
         if(type == 0xAA00)  fsmdat.cmd=FSMMN825R168100KB_PacketUDP;
         fsmdat.countparam = cnt;
         memcpy(fsmdat.Data,bufrd,cnt);
         FSM_SendCtlCmd(&fsmdat);
         if (sendto(listener, fsmdat.Data, fsmdat.countparam, 0, (struct sockaddr*) &si_other, slen) == -1)
         {
            printf("sendto()");
         }
    }
    close(listener);
    return 0;
}

