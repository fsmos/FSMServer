/*!
\file
\brief Процессс работы с устроствами
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/

#ifndef FSM_DEVICEPROCESS_H
#define	FSM_DEVICEPROCESS_H


/*!
\brief Информации о  устройстве
*/
struct FSM_DeviceTree
{
   unsigned char registr; ///< Состояние регистрации
   unsigned short IDDevice;///< Ид устройства
   struct FSM_DeviceFunctionTree* dt;///< Информации о виде устройства
   char state[32];
   void * config;
   void * data;
};
/*!
\brief Прототип функции обратной связи
*/
typedef void (*ApplayProcess)(struct FSM_DeviceTree*);

typedef void (*DeviceProcess)(char*,short, struct FSM_DeviceTree*);
/*!
\brief Информации о виде устройства
*/
struct FSM_DeviceFunctionTree
{
   unsigned char registr;///< Состояние регистрации
   unsigned char type;///< Тип устройства
   unsigned char VidDevice;///< Вид устройства
   unsigned char PodVidDevice;///< Подвид устройства
   unsigned char KodDevice;///<Код устройства
   DeviceProcess Proc;///< Обратная связь
    ApplayProcess aplayp;
   unsigned short config_len; 
};
/*!
\brief Регистрация устройства
\param[in] dt Пакет регистрации
\return Код ошибки
*/
unsigned char FSM_DeviceRegister(struct FSM_DeviceRegistr dt);
/*!
\brief Регистрация класса устройств
\param[in] dft Пакет класса устроства
\return Код ошибки
*/
unsigned char FSM_DeviceClassRegister(struct FSM_DeviceFunctionTree dft);
/*!
\brief Поиск класса устроства
\param[in] dt Пакет регистрации
\return Код ошибки
*/
struct FSM_DeviceFunctionTree* FSM_FindDeviceClass(struct FSM_DeviceRegistr dt);
/*!
\brief Поиск класса устроства
\param[in] dft Пакет класса устроства
\return Ссылку на класс устроства
*/
struct FSM_DeviceFunctionTree* FSM_FindDeviceClass2(struct FSM_DeviceFunctionTree dft);
/*!
\brief Поиск устроства
\param[in] id ID
\return Ссылку на класс устроства
*/
struct FSM_DeviceTree* FSM_FindDevice(unsigned short id);
/*!
\brief Удаление из списка устроства
\param[in] fdd Пакет удаления устройства
\return Ссылку на устроство
*/
void FSM_DeRegister(struct FSM_DeviceDelete fdd);
/*!
\brief Удаление из списка классов устроства
\param[in] dft Пакет класса устроства
*/
void FSM_ClassDeRegister(struct FSM_DeviceFunctionTree dft);

/*!
\brief Получение статистики
\return Статистику
*/
struct fsm_statusstruct *FSM_GetStatistic(void);

/*!
\brief Установка статуса
 \param[in] fdt Устроство
 \param[in] status Состояние
*/
void FSM_Statstic_SetStatus(struct FSM_DeviceTree* fdt,char* status);


/*!
\brief Получение настроек
\return Настройки
*/
struct fsm_devices_config *FSM_GetSetting(void);

/*!
\brief Установка структуры настроек
 \param[in] fdt Устроство
 \param[in] set Настроки
*/
void FSM_Setting_Set(struct FSM_DeviceTree* fdt,void* set);

/*!
\brief Применить настройки
 \param[in] fdt Устроство
 \param[in] set Настроки
*/
void FSM_Setting_Applay(struct FSM_DeviceTree* fdt,void* set);

/*!
\brief Регистрация устройства
\param[in] dt Пакет регистрации
\return Код ошибки
*/
typedef unsigned char(*FSM_FDeviceRegister)(struct FSM_DeviceRegistr);
/*!
\brief Регистрация класса устройств
\param[in] dft Пакет класса устроства
\return Код ошибки
*/
typedef unsigned char(*FSM_FDeviceClassRegister)(struct FSM_DeviceFunctionTree);
/*!
\brief Поиск класса устроства
\param[in] dt Пакет регистрации
\return Код ошибки
*/
typedef struct FSM_DeviceFunctionTree*(*FSM_FFindDeviceClass)(struct FSM_DeviceRegistr);
/*!
\brief Поиск класса устроства
\param[in] dft Пакет класса устроства
\return Ссылку на класс устроства
*/
typedef struct FSM_DeviceFunctionTree*(*FSM_FFindDeviceClass2)(struct FSM_DeviceFunctionTree dft);
/*!
\brief Поиск устроства
\param[in] id ID
\return Ссылку на класс устроства
*/
typedef struct FSM_DeviceTree* (*FSM_FFindDevice)(unsigned short id);
/*!
\brief Удаление из списка устроства
\param[in] fdd Пакет удаления устройства
\return Ссылку на устроство
*/
typedef void (*FSM_FDeRegister)(struct FSM_DeviceDelete fdd);
/*!
\brief Удаление из списка классов устроства
\param[in] dft Пакет класса устроства
*/
typedef void (*FSM_FClassDeRegister)(struct FSM_DeviceFunctionTree dft);

enum FSM_UK /*125 *** 254*/
{
   FSMNotRegistred=125,
};

#endif	/* FSM_DEVICEPROCESS_H */

