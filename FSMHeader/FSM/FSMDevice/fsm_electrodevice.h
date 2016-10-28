#ifndef FSM_ELECTRODEVICE
#define FSM_ELECTRODEVICE

struct FSM_CPC_Device
{
    char reg;
    unsigned short iddev;
};
/*!
\brief Вид устроства
*/
enum FSMELS_VidDevice {
    C220V_12VEl = 1, ///< 220в электрощиток
    CPC = 2 ///< Контроль питания
};
/*!
\brief ПодВид устроства
*/
enum FSMELS_PodVidDevice {
    C220V_12VEl_rev1 = 1, ///< 220в электрощиток
    CPC_12_24_5V
};
/*!
\brief Род устроства
*/
enum FSMELS_RodDevice {
    C220V_12VEl_rev1v1 = 1, ///< 220в электрощиток
    CPC_STM32F103=2
};

enum FSMCPCCommand {
    SetSettingCPC = 1
};
#endif // FSM_ELECTRODEVICE