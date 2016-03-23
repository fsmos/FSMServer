#ifndef FSMEthernetHeader
#define FSMEthernetHeader

#define FSM_PROTO_ID 0x1996
#define FSM_PROTO_ID_R 0x9619

struct fsm_ethernet_dev
{
    char destmac[6];
};
#endif