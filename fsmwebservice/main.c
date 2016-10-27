#include <stdio.h>
#include <stdlib.h>
#include "libwebsockets.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMDevice/FSMSysCtl.h"

static void daemonize(void)
{
	pid_t pid, sid;

	/* already a daemon */
	if ( getppid() == 1 ) return;

	/* Fork off the parent process */
	pid = fork();
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}
	/* If we got a good PID, then we can exit the parent process. */
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	/* At this point we are executing as the child process */

	/* Change the file mode mask */
	umask(0);

	/* Create a new SID for the child process */
	sid = setsid();
	if (sid < 0) {
		exit(EXIT_FAILURE);
	}

	/* Change the current working directory.  This prevents the current
	directory from being locked; hence not being able to remove it. */
	if ((chdir("/")) < 0) {
		exit(EXIT_FAILURE);
	}

	/* Redirect standard files to /dev/null */
	// freopen( "/dev/null", "r", stdin);
	// freopen( "/dev/null", "w", stdout);
	// freopen( "/dev/null", "w", stderr);
}

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason,void *user, void *in, size_t len)
{
return 0;
}


int callback_fsm(struct lws *wsi, enum lws_callback_reasons reason,void *user, void *in, size_t len)
{
struct FSM_SendCmdUserspace buf;

switch (reason) {
    case LWS_CALLBACK_ESTABLISHED: // just log message that someone is 
        printf("connection established\n");
    break;
    case LWS_CALLBACK_RECEIVE: 
        //printf("received data: %s, replying: %.*s\n", (char *) in, (int) len, buf + LWS_SEND_BUFFER_PRE_PADDING);
        memcpy((char*)&buf,in,len);
        printf("%u\n",buf.opcode);
        printf("%u\n",buf.IDDevice);
        FSM_SendCtlCmd(&buf);
        lws_write(wsi, (unsigned char*)&buf, sizeof(struct FSM_SendCmdUserspace), LWS_WRITE_BINARY);
    break;
    default:
    break;
}
 
return 0;
}
 
static struct lws_protocols protocols[] = 
{
{
    "http-only",   // name
    callback_http, // callback
    0              // per_session_data_size
},
{
    "fsm", // protocol name - very important!
    callback_fsm,   // callback
    0    ,// we don't use any per session data
    2000                         
},
{
    NULL,
    NULL,
    0   /* End of list */
}
};
 
int main(void) 
{
    struct lws_context *context;
    struct lws_context_creation_info info;
    
V    daemonize();
    
    memset(&info, 0, sizeof info);
    info.port = 1996;
    info.gid = -1;
    info.uid = -1;
    info.protocols = protocols;
 
    context = lws_create_context(&info);
 
    if (context == NULL) {
    fprintf(stderr, "libwebsocket init failed\n");
    return -1;
    }
 
    printf("starting server...\n");
     //GenStringInfo();
     //printf("%s",FSM_Statistic);
    while (1) {
        lws_service(context, 50);
    }
 
    lws_context_destroy(context);
 
    return 0;
}
