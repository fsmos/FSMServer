/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.0-dev at Tue Jun 19 19:11:19 2018. */

#ifndef PB_JSON2PROTO_MN921_MB_PB_H_INCLUDED
#define PB_JSON2PROTO_MN921_MB_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _json2proto_json2proto_MN921_MB_MB {
    int32_t ToneOutputCallPulse;
/* @@protoc_insertion_point(struct:json2proto_json2proto_MN921_MB_MB) */
} json2proto_json2proto_MN921_MB_MB;

typedef struct _json2proto_json2proto_MN921_MB_SubscriberForCall {
    char abonent[5];
    int32_t id;
/* @@protoc_insertion_point(struct:json2proto_json2proto_MN921_MB_SubscriberForCall) */
} json2proto_json2proto_MN921_MB_SubscriberForCall;

typedef struct _json2proto_json2proto_MN921_MB {
    char self_sip_description[5];
    int32_t type_channel;
    json2proto_json2proto_MN921_MB_MB MB;
    int32_t self_port;
    int32_t audio_port;
    pb_size_t SubscriberForCall_count;
    json2proto_json2proto_MN921_MB_SubscriberForCall SubscriberForCall[4];
    int32_t channel;
/* @@protoc_insertion_point(struct:json2proto_json2proto_MN921_MB) */
} json2proto_json2proto_MN921_MB;

/* Default values for struct fields */

/* Initializer values for message structs */
#define json2proto_json2proto_MN921_MB_init_default {"", 0, json2proto_json2proto_MN921_MB_MB_init_default, 0, 0, 0, {json2proto_json2proto_MN921_MB_SubscriberForCall_init_default, json2proto_json2proto_MN921_MB_SubscriberForCall_init_default, json2proto_json2proto_MN921_MB_SubscriberForCall_init_default, json2proto_json2proto_MN921_MB_SubscriberForCall_init_default}, 0}
#define json2proto_json2proto_MN921_MB_MB_init_default {0}
#define json2proto_json2proto_MN921_MB_SubscriberForCall_init_default {"", 0}
#define json2proto_json2proto_MN921_MB_init_zero {"", 0, json2proto_json2proto_MN921_MB_MB_init_zero, 0, 0, 0, {json2proto_json2proto_MN921_MB_SubscriberForCall_init_zero, json2proto_json2proto_MN921_MB_SubscriberForCall_init_zero, json2proto_json2proto_MN921_MB_SubscriberForCall_init_zero, json2proto_json2proto_MN921_MB_SubscriberForCall_init_zero}, 0}
#define json2proto_json2proto_MN921_MB_MB_init_zero {0}
#define json2proto_json2proto_MN921_MB_SubscriberForCall_init_zero {"", 0}

/* Field tags (for use in manual encoding/decoding) */
#define json2proto_json2proto_MN921_MB_MB_ToneOutputCallPulse_tag 1
#define json2proto_json2proto_MN921_MB_SubscriberForCall_abonent_tag 1
#define json2proto_json2proto_MN921_MB_SubscriberForCall_id_tag 2
#define json2proto_json2proto_MN921_MB_self_sip_description_tag 1
#define json2proto_json2proto_MN921_MB_type_channel_tag 2
#define json2proto_json2proto_MN921_MB_MB_tag    3
#define json2proto_json2proto_MN921_MB_self_port_tag 4
#define json2proto_json2proto_MN921_MB_audio_port_tag 5
#define json2proto_json2proto_MN921_MB_SubscriberForCall_tag 6
#define json2proto_json2proto_MN921_MB_channel_tag 7

/* Struct field encoding specification for nanopb */
extern const pb_field_t json2proto_json2proto_MN921_MB_fields[8];
extern const pb_field_t json2proto_json2proto_MN921_MB_MB_fields[2];
extern const pb_field_t json2proto_json2proto_MN921_MB_SubscriberForCall_fields[3];

/* Maximum encoded size of messages (where known) */
#define json2proto_json2proto_MN921_MB_size      144
#define json2proto_json2proto_MN921_MB_MB_size   11
#define json2proto_json2proto_MN921_MB_SubscriberForCall_size 18

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define MN921_MB_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
