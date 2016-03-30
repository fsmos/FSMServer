/*!
\file
\brief FSM Аудиопотоки
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#ifndef FCM_AUDIO_STREAM_H
#define	FCM_AUDIO_STREAM_H
typedef void (*FSM_StreamProcessUser)(char*,short,void*);
typedef void (*FSM_StreamProcessProcess)(char*,short);
typedef void (*FSM_StreamProcessSend)(unsigned short,char*,short);


struct FSM_AudioStream
{
    char reg;
    unsigned short iddev;
    FSM_StreamProcessUser ToUser;
    FSM_StreamProcessProcess ToProcess;
    void* TransportDevice;
    char TransportDeviceType;
};

int FSM_AudioStreamRegistr(struct FSM_AudioStream fsmas);
void  FSM_AudioStreamUnRegistr(int id);
void FSM_AudioStreamToUser(int id,char* Data,short len);
void FSM_AudioStreamToProcess(int id,char* Data,short len);


#endif