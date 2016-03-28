/*!
\file
\brief FSM Аудиопотоки
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#ifndef FCM_AUDIO_STREAM_H
#define	FCM_AUDIO_STREAM_H
typedef void (*FSM_StreamProcess)(char*,short);
struct FSM_AudioStream
{
    short iddev;
    FSM_StreamProcess ToUser;
    FSM_StreamProcess ToProcess;
    void* TransportDevice;
    char TransportDeviceType;
};


#endif