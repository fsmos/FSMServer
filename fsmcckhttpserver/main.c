/*
* \file: http_server.cpp
* \description: Simple HTTP server
*
*/
#include <errno.h>
#include <event.h>
#include <evhttp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
    "В норме",
    "Повреждена",
};
const short  SERVER_BACKLOG    = 128;

void on_request(struct evhttp_request *, void *);

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

int main(int argc, char **argv)
{
int flags;

daemonize();

int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
       // printf("Error str error:%u ", strerror(errno) );
        return 1;
    }      


struct sockaddr_in  sa;
int on = 1;

sa.sin_family      = AF_INET;
sa.sin_port        = htons(10000);
sa.sin_addr.s_addr = INADDR_ANY;

   /* if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) 
    {
       printf("Error setsockopt():%u ", strerror(errno) );
       return 1;
    }
     * */

// Bind server socket to ip:port
    if (bind(server_sock, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
    printf("Error bind(): %u " ,strerror(errno));
    return 1;
    }
// Make server to listen
    if (listen(server_sock, SERVER_BACKLOG) == -1) {
    printf("Error listen(): %u" ,strerror(errno));
    return 1;
    }
    if ((flags = fcntl(server_sock, F_GETFL, 0)) < 0  
        || fcntl(server_sock, F_SETFL, flags | O_NONBLOCK) < 0)  
    {  
        printf("fcntl error !\n");  
        return -1;  
    }  
// Init events
struct event_base * serv_base   = (struct event_base *)event_init();
struct evhttp     * http_server = evhttp_new(serv_base);

// Ignore SIGPIPE
signal(SIGPIPE, SIG_IGN);

    if (evhttp_accept_socket(http_server, server_sock) == -1) {
   printf("Error evhttp_accept_socket():  %u" ,strerror(errno));
    return 1;
    }
    
// Set HTTP request callback                               
evhttp_set_gencb(http_server, on_request, NULL);
//printf("Run\n");
// Dispatch events
event_base_dispatch(serv_base);

return 0;
}

void on_request(struct evhttp_request * req, void * arg)
{
int i;
char statefw[100];
struct evhttp_uri *decoded = NULL;
// Create responce buffer
struct evbuffer *evb = evbuffer_new();
//printf("Event\n");
if (!evb) { return; }

if(strcmp(req->uri,"/")==0)
{
// Add heading text
evbuffer_add_printf(evb, "<!DOCTYPE html> \n <html>\n<head>\n<meta charset=\"utf-8\">\n<title>%s Page</title>\n</head>\n<body>\n", "FSM CCK Server");
// Add buffer

evbuffer_add_printf(evb, "<h1> %s </h1> \n", "FSM CCK Server");
evbuffer_add_printf(evb, "<table border=\"1\">\n<tr>\n<td>ID</td>\n<td>Тип</td>\n<td>IP</td>\n<td>Позиция</td>\n<td>CRC32</td>\n<td>Состояние памяти</td>\n<td>Размер дерева настроек</td>\n<td>Канал</td>\n<td>Версия</td>\n<td>Hg Версия</td>\n<td>Прошивка</td>\n<td>Управление</td>\n</tr>\n");

FSM_CCK_Get_Data(CCKDev);

for(i=0;i<FSM_CCKTreeSize;i++)
{
    //CCKDev[i].crcerror=1;
    if(CCKDev[i].crcerror==0) sprintf(statefw,"В норме");
    else if(CCKDev[i].crcerror==1) sprintf(statefw,"<a href=\"flash?%u\">Востановить прошивку</a>",CCKDev[i].id); 
    else if(CCKDev[i].crcerror==2) sprintf(statefw,"Повреждена"); 
    evbuffer_add_printf(evb,"<tr>\n<td>%u </td>\n<td>%s</td>\n<td>%u.%u.%u.%u </td>\n<td> %u</td>\n<td>0x%08x</td>\n<td>%u</td>\n<td>%u</td>\n<td>%u</td>\n<td>%u.%u.%u</td><td>%u</td>\n<td>%s</td>\n<td></td></tr>",CCKDev[i].id,fsm_dev_types[CCKDev[i].type], CCKDev[i].ip[0], CCKDev[i].ip[1], CCKDev[i].ip[2], CCKDev[i].ip[3], CCKDev[i].Position,CCKDev[i].crc32,CCKDev[i].ramstate,CCKDev[i].dstlen,CCKDev[i].channel,CCKDev[i].ver1,CCKDev[i].ver2,CCKDev[i].ver3,CCKDev[i].id_build,statefw);  
}




evbuffer_add_printf(evb,"</table>\n");
//evbuffer_add_printf(evb, "Your request is <B>%s</B> from <B>%s</B>.<BR/>Your user agent is '%s'\n", 
//req->uri, req->remote_host, evhttp_find_header(req->input_headers, "User-Agent"));
// Add footer
evbuffer_add_printf(evb, "</body>\n</html>");
}
else
{
    decoded = evhttp_uri_parse(req->uri);
    if(strcmp(evhttp_uri_get_path(decoded),"/flash")==0)
    {
        evbuffer_add_printf(evb, "<h1> Прошивка запущена ID: %u </h1><a href=\"/\">Назад</a>",atoi(evhttp_uri_get_query(decoded)));
        FSM_CTL_flash_Start(atoi(evhttp_uri_get_query(decoded)));
    }
    
}
// Set HTTP headers
evhttp_add_header(req->output_headers, "Server", "FSM CCK Server");
evhttp_add_header(req->output_headers, "Connection", "close");
evhttp_add_header(req->output_headers, "Content-Type", "text/html; charset=utf-8");

// Send reply
evhttp_send_reply(req, HTTP_OK, "OK", evb);

// Free memory
evbuffer_free(evb);
}
