#include <QtNetwork>
#include <QCoreApplication>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
extern "C" {
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/fcmprotocol.h"
}
struct FSM_SendCmdUserspace fsmdat;
struct SendSignalStruct* sss;
int init_th=0;

struct SendSignalStruct
{
 char pipe[20];
 int id;
};
enum FSM_SSTP
{
    FSM_SSTP_SetPid =0x00,
    FSM_SSTP_GetEvent=0x01
};
struct sigaction sa;
// лимит для установки максимально кол-во открытых дискрипторов
#define FSM_Event_id 1

void daemonize()
{
    if(QCoreApplication::arguments().contains("--no-daemon"))
        return;

    switch (fork())
    {
        case 0:  break;
        case -1: exit(-1);
        default: exit(0);
    }
}

void send_handler(int i)
{
    fsmdat.IDDevice=FSM_Event_id;
     fsmdat.cmd=FSM_SSTP_GetEvent;
     fsmdat.countparam=1;
     sss=((struct SendSignalStruct*)fsmdat.Data);
     FSM_SendCtlCmd(&fsmdat);
     qDebug("Run");
     qDebug(sss->pipe);
     QLocalSocket* sock = new QLocalSocket();
     sock->connectToServer(sss->pipe);
     int data[1];
     data[0]=sss->id;
     sock->write((char*)data,sizeof(int));
     sock->close();

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    daemonize();
     sa.sa_handler = send_handler;

    if (sigemptyset(&sa.sa_mask))
    {
             return 0;
    }

    sigaction(SIGUSR1, &sa, 0);

        fsmdat.IDDevice=FSM_Event_id;
        fsmdat.cmd=FSM_SSTP_SetPid;
        fsmdat.countparam=1;
        ((pid_t*)fsmdat.Data)[0]=getpid();
        FSM_SendCtlCmd(&fsmdat);

    return a.exec();
}

