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
struct FSMSSetconfig
{
    unsigned char cmd; 
    unsigned short IDDevice;
    struct fsm_device_config config;
};
enum FSMSSetconfigCmd
{
    SetFSMSetting=1,
    GetFSMSetting=2
};
struct FSMSSetconfigParam
{
    unsigned char cmd; 
    unsigned short IDDevice;
   struct fsm_device_config*  config;
};

struct fsm_devices_config
{
    struct fsm_device_config setel[srow_cnt][scolumn_cnt];
};
struct fsm_statusstruct
{
struct fsm_status_element statel[srow_cnt][scolumn_cnt];
};
struct fsm_ClientSetting_Setting
{
    unsigned short id;
    unsigned short size_row;
    unsigned short size_column;
};
struct fsm_ServerSetting_Setting
{
    unsigned short size_row;
    unsigned short size_column;
};
struct fsm_Setting_Setting
{
  struct fsm_ClientSetting_Setting fsmcs;
  struct fsm_ServerSetting_Setting fsmss;  
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
    AnsGetSet=2,
    SetSetting=3,
    AnsSetSetting=4,
    SetSettingClient=5,
    AnsSetSettingClient=6
};
#endif // FSM_STATUSSTRUCT
