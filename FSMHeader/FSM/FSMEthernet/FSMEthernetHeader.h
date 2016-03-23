#ifndef FSMEthernetHeader
#define FSMEthernetHeader

#define FSM_PROTO_ID 0x1996
#define FSM_PROTO_ID_R 0x9619

enum FSMNetwork_VidDevice
{
    Ethernet=1 ///< Ethernet
};
/*!
\brief ПодВид устроства
*/
enum FSMNetwork_PodVidDevice
{
   WireEthernet=1 ///< WireEthernet
};
/*!
\brief Род устроства
*/
enum FSMNetwork_RodDevice
{
    StandartEthernet=1///< StandartEthernet
};

struct fsm_ethernet_dev
{
    char destmac[6];
};
#endif