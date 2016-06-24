#ifndef FSM_Client_H
#define FSM_Client_H
typedef void (*DeviceClientProcess)(char*,short, struct fsm_client_struct*);
typedef void (*EventClientProcess)(char*,short, struct fsm_event_struct*);
typedef void (*IOClientProcess)(char*,short, struct fsm_ioctl_struct*);
struct fsm_client_struct
{
    char reg;
    unsigned short id;
  
    DeviceClientProcess Handler;
};
struct fsm_event_struct
{
    char reg;
    unsigned int id;
    
    EventClientProcess Handler;
};

struct fsm_ioctl_struct
{
    char reg;
    unsigned int id;
    
    IOClientProcess Handler;
};
struct fsm_server_connection
{
    unsigned short id;  
    char destmac[6];
    char coonect;
    struct net_device *dev;
};
unsigned int FSM_Send_Ethernet(void * data, int len, struct fsm_server_connection *fsmdev);
int FSM_RegisterServer(unsigned short id,unsigned char type,unsigned char VidDevice, unsigned char PodVidDevice,unsigned char KodDevice);
int FSM_RegisterDevice(unsigned short id,unsigned char type,unsigned char VidDevice, unsigned char PodVidDevice,unsigned char KodDevice, DeviceClientProcess Handler);
struct fsm_client_struct*  FSM_FindHandlerDevice(unsigned short id);
int  FSM_DeleteDevice(unsigned short id);
void FSM_DeregisterServer(void);
unsigned int FSM_Send_Ethernet_TS(void * data, int len);
int FSM_SendSignalToPipe(char* pipe, int signal);
void FSM_DeleteEvent(unsigned int id);
struct fsm_event_struct* FSM_FindEvent(unsigned int id);
struct fsm_event_struct* FSM_RegisterEvent(unsigned int id,EventClientProcess Handler);
struct fsm_ioctl_struct* FSM_RegisterIOCtl(unsigned int id,IOClientProcess Handler);
struct fsm_ioctl_struct* FSM_FindIOCtl(unsigned int id);
void FSM_DeleteIOCtl(unsigned int id);

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
#endif