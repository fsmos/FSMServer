#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H 

///Максимальное количество ячеек в стойке
#define MAX_BOARD_NUMBER	8
///Максимальная длина имени SIP-аккаунта
#define MAX_SIP_NAME	5
///Максимальная длина номера вызываемого абонента
#define MAX_SIZE_SUBSCIBER_FOR_CALL	16
///Кол-во циркулярных групп
#define CIRCULAR_NUMBER	4
///Кол-во конференц-групп
#define CONFERENCE_NUMBER	4
///Макс. кол-во участников в конференции
#define MAX_SUBSCRIBER_CONFERENCE	10
///Макс. кол-во участников в конференции
#define MAX_SUBSCRIBER_CIRCULAR	10

#define MAGIC_WORD	"ASALIA"
/*! Список типов ячеек в изделии
* BOARD_NONE - отсутствии ячейки\n
* BOARD_MN825 - ячейка типа МN825(2 абонента р/с Р-168)\n
* BOARD_MN921 - ячейка типа МN921(2 универсальных абонента МБ/АТС/ТЧ)\n
*/
typedef enum{BOARD_NONE, BOARD_MN825, BOARD_MN921}TYPE_BOARD;
typedef enum{TYPEPO_PO06, TYPEPO_PO07, TYPEPO_PO08, TYPEPO_VPO}TYPE_PO;

/*! Список типов абонентов в изделии
* CHANNEL_MB - абонент типа стыка с телефонным аппаратом МБ\n
* CHANNEL_CB - абонент типа стыка с телефонным аппаратом ЦБ\n
* CHANNEL_ATS - абонент типа стыка с линией АТС\n
* CHANNEL_R168 - абонент типа стыка с радиостанцией Р-168\n
* CHANNEL_TCH - абонент типа стыка с линией ТЧ\n
*/
typedef enum{CHANNEL_MB, CHANNEL_CB, CHANNEL_ATS, CHANNEL_R168, CHANNEL_TCH}TYPE_CHANNEL;

typedef enum{TWO_WIRE, FOUR_WIRE_FL, FOUR_WIRE_TCH}TYPE_LINE_TCH;

/** 
  * @brief Структура описывающая настройки стыка с аппаратом МБ
  */
typedef struct{
	unsigned int ToneOutputCallPulse;///время исходящего вызова в тиках (1сек = 8000 тиков)
}CMB;

/** 
  * @brief Структура описывающая настройки стыка с аппаратом ЦБ
  */
typedef struct{
	unsigned int ToneOutputCallPulse;///время исходящего вызова в тиках (1сек = 8000 тиков)	
}CCB;

/** 
  * @brief Структура описывающая настройки стыка с линией АТС
  */
typedef struct{
	unsigned int TypeATS;///тип АТС, 0 - импульсная, 1 - тоновая, 2 - Р2
	char SelfNumber[16];///свой телефонный номер (параметр для атс типа Р2 - необходим для идентификации вызова)
	char SelfNumberLength;///длина своего телефонного номера
	char TargetNumber[16];///телефонный номер на который дается вызов 
	char TargetNumberLength;///длина телефонного номера на который дается вызов 
	char Priority;///приоритет (параметр для атс типа Р2)
	unsigned char SNRLin;///отношение сигнал/шум для линейных сигналов
	unsigned char SNRDtmf;///отношение сигнал/шум для сигналов DTMF
}CATS;

/** 
  * @brief Структура описывающая настройки стыка с линией ТЧ
  */
typedef struct{
	TYPE_LINE_TCH type_line;/*!< \b 0 - 2-х проводная линия ТЧ
								\b 1 - 4-х проводная линия ФЛ \n
								\b 2- 4-х проводная линия ТЧ
							*/
	unsigned int ToneOutputCallPulse;///время исходящего вызова в тиках (1сек = 8000 тиков)
	unsigned int MinToneCallPulse;/// Минимальное время тонального вызова, которое будет воспринято как вызов, в тиках(8000=1с) 
	unsigned int MaxToneCallPulse;/// Максимальное время тонального вызова, которое будет воспринято как вызов, в тиках(8000=1с) 
	unsigned int OutputCallFreq;///частота вызывного сигнала
}CTCH;

/** 
  * @brief Структура описывающая настройки стыка со станцией Р-168
  */
typedef struct{
	unsigned int TimeCall;///Время исходящего вызова в Р168. мсек
}CR168;

/** 
  * @brief Структура описывающая настройки канала ячейки типа МН825
  */
typedef struct{
	///Имя SIP-аккаунта канала ячейки
	char self_sip_description[MAX_SIP_NAME];
	///Номер звукового порта для канала ячейки
	unsigned int audio_port;
	// Номер sip-порта для канала
	unsigned int self_port;
	///Номер вызываемого абонента для канала ячейки
	char SubscriberForCall[4][MAX_SIP_NAME];
	///Поднастройки стыка связи с радиостанцией типа Р-168 для каналов ячейки
	CR168 R168;
}CMN825ChannelConfig;

/** 
  * @brief Структура описывающая поднастройки ячейки типа МН925
  */
typedef struct{
	///UDP порт для приема кодограмм управления/конфигурирования Р-168 для канала ячейки
	unsigned int rcv_port_control_r168;
	///Поднастройки стыка для каналов ячейки
	CMN825ChannelConfig ChannelConfig[2];
}CMN825;

/** 
  * @brief Структура описывающая настройки канала ячейки типа МН921
  */
typedef struct{
	///Имя SIP-аккаунта канала ячейки
	char self_sip_description[MAX_SIP_NAME];
	///Номер вызываемого абонента для канала ячейки
	char SubscriberForCall[4][MAX_SIP_NAME];
	///Номер звукового порта для канала ячейки
	unsigned int audio_port;
	// Номер sip-порта для канала
	unsigned int self_port;
	///Описание типа канала
	TYPE_CHANNEL type_channel;
	///Описание настроек канала
	union CHANNEL{
		CMB		MB;
		CCB		CB;
		CATS	ATS;
		CTCH	TCH;
	}Channel_settings;
}CMN921ChannelConfig;

/** 
  * @brief Структура описывающая поднастройки ячейки типа МС927
  */
typedef struct{
	///Поднастройки стыка для канала ячейки
	CMN921ChannelConfig ChannelConfig[2];
}CMN921;

/** 
  * @brief Структура описывающая общие настройки ячейки изделия
  */
typedef struct{
	unsigned int position;
	unsigned int server_ip;
	unsigned int server_sip_port;
	unsigned int self_ip;
	unsigned int self_mask;			//++++++
	unsigned int self_gateway;
	char name_sip_domen[MAX_SIP_NAME];//+++++++
	TYPE_BOARD type_board;
	union TypeBoard{
		CMN825 MN825;
		CMN921 MN921;
	}BoardSettings;
}CBoardConfiguration;

/** 
  * @brief Структура описывающая IP-настройки связи с сервером
*/
typedef struct{
	unsigned int server_ip;
	unsigned int self_ip;
	unsigned int subnet_mask;
	unsigned int gateway;
	unsigned int server_sip_port;
	unsigned char mac[6];
} CServerInfo;

/** 
  * @brief Структура описывающая SIP-настройки связи с сервером
*/
typedef struct{
	unsigned int self_port;
	char SipName[MAX_SIP_NAME];
	unsigned int RTP_port;
} CSIPInfo;

/** 
  * @brief Структура описывающая SIP-настройки вирт. ПО связи с сервером
*/
typedef struct{
	unsigned int server_listen_port;
	char SipName[MAX_SIP_NAME];
	char DisplayName[MAX_SIP_NAME];
} CSIPInfoVPO;

/** 
  * @brief Структура описывающая Аудио-настройки связи виртуального ПО
*/
typedef struct{
	char alsa_dev_name[64];
	unsigned int MinPort;
	unsigned int MaxPort;
} CMediaInfo;

/** 
  * @brief Структура описывающая предопределенные циркулярные связи ПО
*/
typedef struct{
	char dynamic_sip_name[MAX_SIP_NAME];
	char SipNameGroupList[CIRCULAR_NUMBER][MAX_SUBSCRIBER_CIRCULAR][MAX_SIP_NAME];
} CCircularInfo;

/** 
  * @brief Структура описывающая предопределенные конференц-связи ПО
*/
typedef struct{
	char dynamic_sip_name[MAX_SIP_NAME];
	char SipNameGroupList[CONFERENCE_NUMBER][MAX_SUBSCRIBER_CONFERENCE][MAX_SIP_NAME];
} CConferenceInfo;

/** 
  * @brief Структура описывающая настройки связи со стыком управления РС-ей Р-168
*/
typedef struct{
	unsigned int ip_addr[4];
	unsigned int port[4];
} CConfigR168;

/** 
  * @brief Структура описывающая одного абонента связи в ПО-06, ПО-07, ПО-08
*/
typedef struct{
	char sip_name[MAX_SIP_NAME];
	unsigned char exclusive;
	unsigned char autoconnection;
} CSubscriberInfo;

/** 
  * @brief Структура описывающая одного абонента виртуального ПО
*/
typedef struct{
	CSubscriberInfo SubscriberInfo;
	char display_name[9];
} CSubscriberVPOInfo;

/** 
  * @brief Структура описывающая одну линию связи ПО
*/
typedef struct{
	CSIPInfo sip_info;
	CSubscriberInfo SubscriberInfo[12];
	unsigned int Volume;
} CLineInfo;

/** 
  * @brief Структура описывающая параметры ПО-06
*/
typedef struct{
	CServerInfo server_info;
	CLineInfo LineInfo[2];
	CConfigR168 ConfigR168;
	CCircularInfo CircularInfo;
	CConferenceInfo ConferenceInfo;
	char sip_name_ats[MAX_SIP_NAME];
} CPO06_Config __attribute__((aligned(4)));

/** 
  * @brief Структура описывающая параметры ПО-07
*/
typedef struct{
	CServerInfo server_info;
	CLineInfo LineInfo[2];
	CCircularInfo CircularInfo;
	CConferenceInfo ConferenceInfo;
	char sip_name_ats[MAX_SIP_NAME];
} CPO07_Config;

/** 
  * @brief Структура описывающая параметры ПО-08
*/
typedef struct{
	CServerInfo server_info;
	CSIPInfo sip_info;
	CSubscriberInfo SubscriberInfo[9];
	CConfigR168 ConfigR168;
	CCircularInfo CircularInfo;
	CConferenceInfo ConferenceInfo;
	char sip_name_ats[MAX_SIP_NAME];
	unsigned int Volume;
} CPO08_Config;

/** 
  * @brief Структура описывающая параметры глобального хоткея на вызов тангенты
*/
typedef struct{
	char Key[4];
	unsigned char Modif;
}CXK_TANG;

/** 
  * @brief Структура описывающая параметры вирутального ПО
*/
typedef struct{
	CServerInfo server_info;
	CSIPInfoVPO SIPInfoVPO;
	CConfigR168 ConfigR168;
	CMediaInfo MediaInfo;
	CCircularInfo CircularInfo;
	CConferenceInfo ConferenceInfo;
	unsigned int PortExchangeRLK;
	char sip_name_ats[MAX_SIP_NAME];
	CSubscriberVPOInfo SubscriberVPOInfo[16];
	CXK_TANG XK_TANG;
} CVPO_Config;

#endif
