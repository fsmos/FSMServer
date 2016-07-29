#if !defined(_GNU_SOURCE)
	#define _GNU_SOURCE
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <execinfo.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/fcmprotocol.h"
struct FSM_SendCmdUserspace fsmdat;
int init_th=0;
struct SendSignalStruct 
{
 char pipe[20];   
 int id;
};
// лимит для установки максимально кол-во открытых дискрипторов
#define FSM_Event_id 1

enum FSM_SSTP 
{
    FSM_SSTP_SetPid =0x00,
    FSM_SSTP_GetEvent=0x01
};

int WorkProc()
{
	sigset_t         sigset;
	int              signo;
	int              status;
    struct SendSignalStruct* sss;
    char *argv[] = {"fsmsstd",0, 0, NULL };
    char id[20];


	// пользовательский сигнал который мы будем использовать для обновления конфига
	sigaddset(&sigset, SIGUSR1);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
    fsmdat.IDDevice=FSM_Event_id;
    fsmdat.cmd=FSM_SSTP_SetPid;
    fsmdat.countparam=1;
    ((pid_t*)fsmdat.Data)[0]=getpid();
    FSM_SendCtlCmd(&fsmdat);
    init_th=1;

    // цикл ожижания сообщений
    for (;;)
    {
			// ждем указанных сообщений
			sigwait(&sigset, &signo);

			// если то сообщение обновления конфига
			if (signo == SIGUSR1)
			{
                    fsmdat.IDDevice=FSM_Event_id;
                    fsmdat.cmd=FSM_SSTP_GetEvent;
                    fsmdat.countparam=1;
                    sss=((struct SendSignalStruct*)fsmdat.Data);
                    FSM_SendCtlCmd(&fsmdat);
                    argv[1]=sss->pipe;
                    sprintf(id,"%u",sss->id);
                    argv[2]=id;
                    execv("/bin/fsmsstd",argv);
			}
    }
	// вернем код не требующим перезапуска
	return 0;
}

int main(int argc, char** argv)
{
	int status;
	int pid;

	// создаем потомка
	pid = fork();

	if (pid == -1) // если не удалось запустить потомка
	{
		// выведем на экран ошибку и её описание
		printf("Start Daemon Error: %s\n", strerror(errno));

		return -1;
	}
	else if (!pid) // если это потомок
	{
		// данный код уже выполняется в процессе потомка
		// разрешаем выставлять все биты прав на создаваемые файлы,
		// иначе у нас могут быть проблемы с правами доступа
		umask(0);

        printf("Demon Thread Run \n");
		// создаём новый сеанс, чтобы не зависеть от родителя
		setsid();

		// закрываем дискрипторы ввода/вывода/ошибок, так как нам они больше не понадобятся
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);

		status = WorkProc();

		return status;
	}
	else // если это родитель
	{
        printf("Demon Run \n");
		// завершим процес, т.к. основную свою задачу (запуск демона) мы выполнили
		return 0;
	}
}

