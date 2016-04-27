/*!
\file
\brief Процессс работы с устроствами
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/fcm_audiodeviceclass.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
#include "FSM/FSMSetting/FSM_settings.h"
#include "FSM/FSMDevice/fsm_statusstruct.h"
/*!
\brief Список классов устройств
 */
struct FSM_DeviceFunctionTree fsm_dft[FSM_DeviceFunctionTreeSize];
/*!
\brief Список  устройств
 */
struct FSM_DeviceTree fsm_dt[FSM_DeviceTreeSize];
struct fsm_statusstruct fsm_str;
struct fsm_devices_config fsm_set;

static int __init FSMDeviceProcess_init(void)
{
    memset(fsm_dft,0,sizeof(fsm_dft));
    memset(fsm_dt,0,sizeof(fsm_dt));
    printk( KERN_INFO "FSMDeviceProcess module loaded\n" ); 
    return 0;
}
static void __exit FSMDeviceProcess_exit(void)
{
    memset(fsm_dft,0,sizeof(fsm_dft));
    memset(fsm_dt,0,sizeof(fsm_dt));
    printk( KERN_INFO "FSMDeviceProcess module unloaded\n" ); 
}
/*!
\brief Получение статистики
\return Структуру статистики
*/
struct fsm_statusstruct *FSM_GetStatistic(void)
{
   int i,j;
   int m=0;
   memset(&fsm_str,0,sizeof(fsm_str));
   for(i=0;i<srow_cnt;i++)
   {
   for(j=0;j<scolumn_cnt;j++)
   {
       if((fsm_dt[m].IDDevice!=0)&&(fsm_dt[m].registr==1))
       {
       fsm_str.statel[i][j].devid=fsm_dt[m].IDDevice;
       strcpy(fsm_str.statel[i][j].state,fsm_dt[m].state);
       sprintf(fsm_str.statel[i][j].fsmdevcode,"t%uv%upv%uk%u",fsm_dt[m].dt->type,fsm_dt[m].dt->VidDevice,fsm_dt[m].dt->PodVidDevice,fsm_dt[m].dt->KodDevice);
       fsm_str.statel[i][j].row=i;
       fsm_str.statel[i][j].column=j;
       }
       m++;
       

   } 
 }
   return &fsm_str;
}
EXPORT_SYMBOL(FSM_GetStatistic);

struct fsm_devices_config *FSM_GetSetting(void)
{
   int i,j;
   int m=0;
   memset(&fsm_set,0,sizeof(fsm_set));
   for(i=0;i<srow_cnt;i++)
   {
   for(j=0;j<scolumn_cnt;j++)
   {
       if((fsm_dt[m].IDDevice!=0)&&(fsm_dt[m].registr==1))
       {
       fsm_set.setel[i][j].IDDevice=fsm_dt[m].IDDevice;
       fsm_set.setel[i][j].Len=fsm_dt[m].dt->config_len;
       memcpy(fsm_set.setel[i][j].config,fsm_dt[m].config,fsm_set.setel[i][j].Len);
       fsm_set.setel[i][j].row=i;
       fsm_set.setel[i][j].column=j;
       m++;
       }
       

   } 
 }
   return &fsm_set;
}
EXPORT_SYMBOL(FSM_GetSetting);

void FSM_Setting_Set(struct FSM_DeviceTree* fdt,void* set)
{
  fdt->config=set;
}
EXPORT_SYMBOL(FSM_Setting_Set);

void FSM_Setting_Applay(struct FSM_DeviceTree* fdt,void* set)
{
  if(fdt==0) return;
  memcpy(fdt->config,set,fdt->dt->config_len);
 // printk( KERN_INFO "FSMAP %i\n", fdt->dt->aplayp); 
  if(fdt->dt->aplayp!=0) fdt->dt->aplayp(fdt);
}
EXPORT_SYMBOL(FSM_Setting_Applay);

void FSM_Statstic_SetStatus(struct FSM_DeviceTree* fdt,char* status)
{
  strcpy(fdt->state,status);
}
EXPORT_SYMBOL(FSM_Statstic_SetStatus);
/*!
\brief Регистрация класса устройств
\param[in] dft Пакет класса устроства
\return Код ошибки
*/
unsigned char FSM_DeviceClassRegister(struct FSM_DeviceFunctionTree dft)
{
    int i;
    if(FSM_FindDeviceClass2(dft)!=0) return 2;
    for(i=0;i<FSM_DeviceFunctionTreeSize;i++)
    {
        if(fsm_dft[i].registr==0)
        {
            fsm_dft[i].registr=1;
            fsm_dft[i].type=dft.type;
            fsm_dft[i].VidDevice=dft.VidDevice;
            fsm_dft[i].PodVidDevice=dft.PodVidDevice;
            fsm_dft[i].KodDevice=dft.KodDevice;
            fsm_dft[i].Proc=dft.Proc;
            fsm_dft[i].config_len=dft.config_len;
            fsm_dft[i].aplayp=dft.aplayp;
             printk( KERN_INFO "DeviceClassRegistred: Type:%u; Vid:%u; PodVid:%u; KodDevice: %u \n", dft.type,dft.VidDevice,dft.PodVidDevice,dft.KodDevice ); 
            return 0;
        }
    }
    
    return 1;
}
EXPORT_SYMBOL(FSM_DeviceClassRegister);
/*!
\brief Регистрация устройства
\param[in] dt Пакет регистрации
\return Код ошибки
*/
unsigned char FSM_DeviceRegister(struct FSM_DeviceRegistr dt)
{
    int i;
    struct FSM_DeviceFunctionTree* classf;
    if(FSM_FindDevice(dt.IDDevice)!=0) return 2;
    for(i=0;i<FSM_DeviceTreeSize;i++)
    {
        if(fsm_dt[i].registr==0)
        {
            classf=FSM_FindDeviceClass(dt);
            if(classf!=0)
            {
            fsm_dt[i].registr=1;
            fsm_dt[i].IDDevice=dt.IDDevice;
            fsm_dt[i].dt=classf;
            printk( KERN_INFO "DeviceRegistred: ID: %u Type:%u; Vid:%u; PodVid:%u; KodDevice: %u \n", dt.IDDevice,dt.type,dt.VidDevice,dt.PodVidDevice,dt.KodDevice );

            return 0;

            }
        }
    }
    return 1;
}
EXPORT_SYMBOL(FSM_DeviceRegister);
/*!
\brief Поиск класса устроства
\param[in] dt Пакет регистрации
\return Код ошибки
*/
struct FSM_DeviceFunctionTree* FSM_FindDeviceClass(struct FSM_DeviceRegistr dt)
{
    int i;
    for(i=0;i<FSM_DeviceFunctionTreeSize;i++)
    {
        if((fsm_dft[i].KodDevice==dt.KodDevice)&&(fsm_dft[i].VidDevice==dt.VidDevice)&&(fsm_dft[i].PodVidDevice==dt.PodVidDevice)&&(fsm_dft[i].type==dt.type)&&(fsm_dft[i].registr==1))
        {
            return &fsm_dft[i];
        }
    } 
    return 0;
}
EXPORT_SYMBOL(FSM_FindDeviceClass);
/*!
\brief Поиск класса устроства
\param[in] dft Пакет класса устроства
\return Ссылку на класс устроства
*/
struct FSM_DeviceFunctionTree* FSM_FindDeviceClass2(struct FSM_DeviceFunctionTree dft)
{
    int i;
    for(i=0;i<FSM_DeviceFunctionTreeSize;i++)
    {
        if((fsm_dft[i].KodDevice==dft.KodDevice)&&(fsm_dft[i].VidDevice==dft.VidDevice)&&(fsm_dft[i].PodVidDevice==dft.PodVidDevice)&&(fsm_dft[i].type==dft.type)&&(fsm_dft[i].registr==1))
        {
            return &fsm_dft[i];
        }
    } 
    return 0;
}
EXPORT_SYMBOL(FSM_FindDeviceClass2);
/*!
\brief Поиск устроства
\param[in] id ID
\return Ссылку на класс устроства
*/
struct FSM_DeviceTree* FSM_FindDevice(unsigned short id)
{
    int i;
    for(i=0;i<FSM_DeviceTreeSize;i++)
    {
        //if(fsm_dt[i].IDDevice!=0) printk( KERN_INFO "DeviceNotFindScan: ID: %u - %u \n", fsm_dt[i].IDDevice,fsm_dt[i].registr);
        if((fsm_dt[i].IDDevice==id)&&(fsm_dt[i].registr==1))
        {
            
            return &fsm_dt[i];
        }
    } 
    printk( KERN_INFO "DeviceNotFind: ID: %u \n", id);
    return 0;
}
EXPORT_SYMBOL(FSM_FindDevice);
/*!
\brief Удаление из списка устроства
\param[in] fdd Пакет удаления устройства
\return Ссылку на устроство
*/
void FSM_DeRegister(struct FSM_DeviceDelete fdd)
{
    struct FSM_DeviceTree* dt= FSM_FindDevice(fdd.IDDevice);
    if(dt!=0) dt->registr=0; 
    printk( KERN_INFO "DeviceDeRegistred: ID: %u \n", fdd.IDDevice);
    
}
EXPORT_SYMBOL(FSM_DeRegister);
/*!
\brief Удаление из списка классов устроства
\param[in] dft Пакет класса устроства
*/
void FSM_ClassDeRegister(struct FSM_DeviceFunctionTree dfti)
{
    struct FSM_DeviceFunctionTree* dft =FSM_FindDeviceClass2(dfti);
    if(dft!=0) dft->registr=0; 
    printk( KERN_INFO "DeviceClassDeregistred: Type:%u; Vid:%u; PodVid:%u; KodDevice: %u \n", dfti.type,dfti.VidDevice,dfti.PodVidDevice,dfti.KodDevice );
}
EXPORT_SYMBOL(FSM_ClassDeRegister);

module_init(FSMDeviceProcess_init);
module_exit(FSMDeviceProcess_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM Device Manager Module");
MODULE_LICENSE("GPL");