#ifndef FSM_Client_H
#define FSM_Client_H
typedef void (*DeviceClientProcess)(char*,short, struct fsm_client_struct*);
struct fsm_client_struct
{
    char reg;
    unsigned short id;
  
    DeviceClientProcess Handler;
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

#endif