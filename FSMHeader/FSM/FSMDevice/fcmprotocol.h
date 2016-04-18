/*!
\file
\brief Протокол FSM
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#ifndef FCMPROTOCOL
#define FCMPROTOCOL

/*!
\brief Коды операци
*/
enum FSM_CodeOperation
{
  RegDevice=1, ///< Регистрация устройства
  AnsRegDevice=2, ///< Подтверждение регистрации
  DelLisr=3, ///< Удаление устройства из списка
  AnsDelList=4,///< Подтверждение удаления устройства из списка
  AnsPing=5, ///< Пинг
  SendCmdToDevice=6,///< Отправка команды устройству
  AnsSendCmdToDevice=7, ///< Подтверждение приёма команды устройством
  RqToDevice=8, ///< Ответ на команду устройством
  AnsRqToDevice=9,///< Подтверждение приёма команды сервером
  SendCmdToServer=10,///< Отправка команды серверу
  SendTxtMassage=11,///< Отправка текстового сообщения
  AnsSendTxtMassage=12, ///< Подтверждение приёма текстового сообщения
  SendTxtEncMassage=13, ///< Отправка зашифрованного текстового сообщения
  AnsSendTxtEncMassage=14, ///< Подтверждение приёма зашифрованного текстового сообщения
  SendAudio=15,///< Передача аудио данных
  SendVideo=16,///< Передача видео данных
  SendBinData=17,///< Передача бинарных данных
  AnsSendBinData=18,///< Подтверждение приёма бинарных данных
  SendSMS=19,///< Отправить СМС
  SendAnsSMS=20,///< Подтверждение СМС
  SendSMStoDev=21,///< Передача СМС устройству
  SendAnsSMStoDev=22,///< Подтверждение СМС устройством
  SendEncSMS=23, ///< Отправить зашифрованного СМС
  SendAnsEncSMS=24, ///<Подтверждение зашифрованного СМС
  SendEncSMStoDev=25,///< Отправить зашифрованного СМС устройству
  SendAnsEncSMStoDev=26,///< Подтверждение зашифрованного СМС  устройства
  SendEmail=27,///< Отправка email
  AnsEmail=28,///<Подтверждение email
  SendEmailtoDevice=29,///<Передача email устройству
  AnsSendEmailtoDevice=30,///<Подтверждение email устройством
  SendEncEmail=31,///<Отправить зашифрованного email
  AnsEncEmail=32,///<Подтверждение зашифрованного email
  SendEncEmailtoDev=33,///< Отправить зашифрованного email устройству
  AnsEncEmailtoDev=34,///< Подтверждение зашифрованного email   устройства
  SocSend=35,///< Отправка сообщение в социальную сеть
  AnsSocSend=36,///< Подтверждение сообщения в социальную сеть
  SocSendtoDev=37,///< Передача сообщения в социальную сеть устройству
  AnsSocSendtoDev=38,///< Подтверждение   сообщения в социальную сеть устройством
  SocEncSend=39,///< Отправить зашифрованного сообщения в социальную сеть
  AnsSocEncSend=40,///< Подтверждение зашифрованного сообщения в социальную сеть
  SocEncSendtoDev=41,///<	Отправить зашифрованного сообщения в социальную сеть устройству
  AnsSocEncSendtoDev=42,///<	Подтверждение зашифрованного сообщения в социальную сеть   устройства
  Alern=43,///<Тревога
  Warning=44,///<Предупреждение
  Trouble=45,///<Сбой
  Beep=46 ///<Звуковой сигнал

};
/*!
\brief Тип устройства
*/
enum FSM_TypeDevice
{
    AvtoElSheet=1, ///<Автоматически Электрощиток
    MindTepl=2, ///<Умная Теплица
    SmartPhone=3, ///< Смартфон
    AudioDevice=4, ///< Устройство аудио связи
    Network=5, ///< Сеть
    StatisticandConfig=6 ///< Модуль статистики и конфигурации
};
/*!
\brief Регистрация устроства
*/
struct FSM_DeviceRegistr
{
   unsigned char opcode; ///< Код операции
   unsigned char type;///< Тип устройства
   unsigned char VidDevice;///< Вид устройства
   unsigned  char PodVidDevice;///< Подвид устройства
   unsigned char KodDevice;///<Код устройства
   unsigned short IDDevice;///< Ид устройства
   unsigned char CRC;///< CRC
};
/*!
\brief Подтверждение регистрации
*/
struct FSM_AnsDeviceRegistr
{
   unsigned char opcode;///< Код операции
   unsigned char type;///< Тип устройства
   unsigned char VidDevice;///< Вид устройства
   unsigned char PodVidDevice;///< Подвид устройства
   unsigned char KodDevice;///<Код устройства
   unsigned short IDDevice;///< Ид устройства
   unsigned char CRC;///< CRC
};
/*!
\brief Удаление устройства из списка
*/
struct FSM_DeviceDelete
{
   unsigned char opcode;///< Код операции
   unsigned  short IDDevice;///< Ид устройства
   unsigned char CRC;///< CRC
};
/*!
\brief Подтверждение удаления устройства из списка
*/
struct FSM_AnsDeviceDelete
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char CRC;///< CRC
};
/*!
\brief Пинг
*/
struct FSM_Ping
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char CRC;///< CRC
};
/*!
\brief Отправка команды устройству
*/
struct FSM_SendCmd
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char cmd;///< Команда
   unsigned char countparam;///< Количество параметров
   unsigned char CRC;///< CRC
   unsigned char Data[250] __attribute__((aligned(4)));///< Параметры
};
/*!
\brief  Подтверждение приёма команды устройством
*/
struct FSM_AnsSendCmd
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char cmd;///< Команда
   unsigned char CRC;///< CRC
};
/*!
\brief Ответ на команду устройством
*/
struct FSM_AnsCmd
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char cmd;///< Команда
   unsigned char countparam;///< Количество параметров
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Параметры
};
/*!
\brief  Подтверждение приёма команды сервером
*/
struct FSM_AnsAnsCmd
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char cmd;///< Команда
   unsigned char CRC;///< CRC
};

/*!
\brief Отправка команды серверу
*/
struct FSM_SendCmdTS
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char cmd;///< Команда
   unsigned char countparam;///< Количество параметров
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Параметры
};
/*!
\brief Отправка текстового сообщения
*/
struct FSM_SendMessage
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение приёма текстового сообщения
*/
struct FSM_AnsSendMessage
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
};
/*!
\brief Отправка зашифрованного текстового сообщения
*/
struct FSM_SendEncMessage
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char alg;///< Алгоритм
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение приёма зашифрованного текстового сообщения
*/
struct FSM_AnsSendEncMessage
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char alg;///< Алгоритм
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
};
/*!
\brief Передача аудио данных
*/
struct FSM_SendAudioData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char codec;///< Кодек
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Аудио
};
/*!
\brief Передача видео данных
*/
struct FSM_SendVideoData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char codec;///< Кодек
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Видео
};
/*!
\brief Передача бинарных данных
*/
struct FSM_SendBinData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Данные
};
/*!
\brief Подтверждение приёма бинарных данных
*/
struct FSM_AnsSendBinData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
};
/*!
\brief Отправить СМС
*/
struct FSM_SendSmsData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lennumber;///< Длина номера телефона
   unsigned char number[15];///< Номера телефона
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение СМС
*/
struct FSM_ansSendSmsData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lennumber;///< Длина номера телефона
   unsigned char number[15];///< Номера телефона
   unsigned char CRC;///< CRC
};
/*!
\brief Передача СМС устройству
*/
struct FSM_SendSmsDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lennumber;///< Длина номера телефона
   unsigned char number[15];///< Номера телефона
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение СМС устройством
*/
struct FSM_ansSendSmsDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lennumber;///< Длина номера телефона
   unsigned char number[15];///< Номера телефона
   unsigned char CRC;///< CRC
};
/*!
\brief Отправить зашифрованного СМС
*/
struct FSM_SendEncSmsData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lennumber;///< Длина номера телефона
   unsigned char number[15];///< Номера телефона
   unsigned char alg;///<Алгоритм
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение зашифрованного СМС
*/
struct FSM_ansSendEncSmsData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lennumber;///< Длина номера телефона
   unsigned char number[15];///< Номера телефона
   unsigned char CRC;///< CRC
};
/*!
\brief Отправить зашифрованного СМС устройству
*/
struct FSM_SendEncSmsDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lennumber;///< Длина номера телефона
   unsigned char number[15];///< Номера телефона
   unsigned char alg;///<Алгоритм
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение зашифрованного СМС  устройства
*/
struct FSM_ansSendEncSmsDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lennumber;///< Длина номера телефона
   unsigned char number[15];///< Номера телефона
   unsigned char CRC;///< CRC
};
/*!
\brief Отправка email
*/
struct FSM_SendEmailData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenemail;///< Длина email
   unsigned char email[25];///< email
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение email
*/
struct FSM_AnsSendEmailData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenemail;///< Длина email
   unsigned char email[25];///< email
   unsigned char CRC;///< CRC
};
/*!
\brief Передача email устройству
*/
struct FSM_SendEmailDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenemail;///< Длина email
   unsigned char email[25];///< email
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение email устройством
*/
struct FSM_AnsSendEmailDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenemail;///< Длина email
   unsigned char email[25];///< email
   unsigned char CRC;///< CRC
};
/*!
\brief Отправить зашифрованного email
*/
struct FSM_SendEncEmailData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenemail;///< Длина email
   unsigned char email[25];///< email
   unsigned char alg;///<Алгоритм
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение зашифрованного email
*/
struct FSM_AnsSendEncEmailData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenemail;///< Длина email
   unsigned char email[25];///< email
   unsigned char CRC;///< CRC
};
/*!
\brief Отправить зашифрованного email устройству
*/
struct FSM_SendEncEmailDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenemail;///< Длина email
   unsigned char email[25];///< email
   unsigned char alg;///<Алгоритм
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение зашифрованного email   устройства
*/
struct FSM_AnsSendEncEmailDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenemail;///< Длина email
   unsigned char email[25];///< email
   unsigned char CRC;///< CRC
};
/*!
\brief Отправка сообщение в социальную сеть
*/
struct FSM_SendSocData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenlogin;///< Длина login
   unsigned char login[25];///< login
   unsigned char sctype;///<Тип социально сети
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение сообщения в социальную сеть
*/
struct FSM_AnsSendSocData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenlogin;///< Длина login
   unsigned char login[25];///< login
   unsigned char CRC;///< CRC
};
/*!
\brief Передача   сообщения в социальную сеть устройству
*/
struct FSM_SendSocDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenlogin;///< Длина login
   unsigned char login[25];///< login
   unsigned char sctype;///<Тип социально сети
   unsigned short len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение  сообщения в социальную сеть устройством
*/
struct FSM_AnsSendSocDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenlogin;///< Длина login
   unsigned char login[25];///< login
   unsigned char CRC;///< CRC
};
/*!
\brief Отправить зашифрованного сообщения в социальную сеть
*/
struct FSM_SendEncSocData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenlogin;///< Длина login
   unsigned char login[25];///< login
   unsigned char sctype;///<Тип социально сети
   unsigned char alg;///<Алгоритм
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение зашифрованного сообщения в социальную сеть
*/
struct FSM_AnsSendEncSocData
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenlogin;///< Длина login
   unsigned char login[25];///< login
   unsigned char CRC;///< CRC
};
/*!
\brief Отправить зашифрованного сообщения в социальную сеть устройству
*/
struct FSM_SendEncSocDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenlogin;///< Длина login
   unsigned char login[25];///< login
   unsigned char sctype;///<Тип социально сети
   unsigned char alg;///<Алгоритм
   unsigned char len;///< Длина
   unsigned char CRC;///< CRC
   unsigned char Data[250];///< Текст
};
/*!
\brief Подтверждение зашифрованного сообщения в социальную сеть   устройства
*/
struct FSM_AnsSendEncSocDatatoDev
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned char lenlogin;///< Длина login
   unsigned char login[25];///< login
   unsigned char CRC;///< CRC
};
/*!
\brief Тревога
*/
struct FSM_AlernSignal
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned short ID;///< Ид Тревоги
   unsigned char CRC;///< CRC
};
/*!
\brief Предупреждение
*/
struct FSM_WarningSignal
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned short ID;///< Ид Предупреждения
   unsigned char CRC;///< CRC
};
/*!
\brief Сбой
*/
struct FSM_TroubleSignal
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned short ID;///< Ид Предупреждения
   unsigned char CRC;///< CRC
};
/*!
\brief Звуковой сигнал
*/
struct FSM_BeepSignal
{
   unsigned char opcode;///< Код операции
   unsigned short IDDevice;///< Ид устройства
   unsigned short ID;///< Ид Звукового сигнала
   unsigned char CRC;///< CRC
};

#endif // FCMPROTOCOL

