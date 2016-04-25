#ifndef FSM_STATUSSTRUCT
#define FSM_STATUSSTRUCT
#define srow_cnt 8
#define scolumn_cnt 12
#define status_cnt srow_cnt*scolumn_cnt
struct fsm_status_element
{
int row;
int column;
char state[32];
char fsmdevcode[32];
short devid;
};
struct fsm_device_config
{
    int row;
    int column;
    unsigned short IDDevice;
    unsigned short Len;
    char config[1000];
};
struct fsm_devices_config
{
    struct fsm_device_config setel[srow_cnt][scolumn_cnt];
};
struct fsm_statusstruct
{
struct fsm_status_element statel[srow_cnt][scolumn_cnt];
};

enum FSMST_VidDevice
{
    FSMDeviceConfig=1, ///<  Модуль Конфигурации
    FSMDeviceStatistic=2, ///<  Модуль Конфигурации
};
/*!
\brief ПодВид устроства
*/
enum FSMST_PodVidDevice
{
   ComputerStatistic=1 ///< ComputerStatistic
};
/*!
\brief Род устроства
*/
enum FSMST_RodDevice
{
    PCx86=1,///< PCx86
};
enum FSMST_Cmd /*0*****125*/
{
    GetStatistic=1,
    AnsGetStatistic=2
};
enum FSMS_Cmd /*0*****125*/
{
    GetSet=1,
    AnsGetSet=2
};
#endif // FSM_STATUSSTRUCT
