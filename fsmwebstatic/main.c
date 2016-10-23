#include <stdio.h>
#include <stdlib.h>
#include "libwebsockets.h"
#include "FSM/FSM_Client/FSM_client.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
struct fsm_statusstruct fsmsst;
char FSM_Statistic[1500];

void GenStringInfo()
{
    char Buf[400];
    int i,j;
    strcpy(FSM_Statistic,"{\n \"fsm_server_name\":\"fsm_statistic\",\n");
    strcat(FSM_Statistic,"\"device\":[\n");
    for(i=0;i<srow_cnt;i++)
    {
        strcat(FSM_Statistic,"[\n");
        for(j=0;j<scolumn_cnt;j++)
        {
        strcat(FSM_Statistic,"{\n");
        sprintf(Buf,"\"ID\":\"%u\",\n",fsmsst.statel[i][j].devid);
        strcat(FSM_Statistic,Buf);
        strcat(FSM_Statistic,"},\n");
        }
        strcat(FSM_Statistic,"],\n");
    }
    strcat(FSM_Statistic,"]\n");
    strcat(FSM_Statistic,"}");
}

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason,void *user, void *in, size_t len)
{
switch (reason) {
    case LWS_CALLBACK_ESTABLISHED: // just log message that someone is 
        printf("connection established\n");
    break;
    case LWS_CALLBACK_RECEIVE: 
    GenStringInfo();
    lws_write(wsi, (unsigned char*)FSM_Statistic,strlen(FSM_Statistic), LWS_WRITE_HTTP);
    //lws_return_http_status( wsi,201,0);
    lws_http_transaction_completed(wsi);
    break;
}
return 0;
}


int callback_dumb_increment(struct lws *wsi, enum lws_callback_reasons reason,void *user, void *in, size_t len)
{
unsigned char buf[2000];

switch (reason) {
    case LWS_CALLBACK_ESTABLISHED: // just log message that someone is 
        printf("connection established\n");
    break;
    case LWS_CALLBACK_RECEIVE: 
        printf("received data: %s, replying: %.*s\n", (char *) in, (int) len, buf + LWS_SEND_BUFFER_PRE_PADDING);
        lws_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], len, LWS_WRITE_TEXT);
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
    callback_dumb_increment,   // callback
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
    
    memset(&info, 0, sizeof info);
    info.port = 9000;
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
