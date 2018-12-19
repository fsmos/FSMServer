/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.0-dev at Tue Jun 19 19:11:19 2018. */

#ifndef PB_JSON2PROTO_MN921_ATS_PB_H_INCLUDED
#define PB_JSON2PROTO_MN921_ATS_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _json2proto_json2proto_MN921_ATS_ATS {
    int32_t Type;
    int32_t AtsR2Priority;
    int32_t AtsR2SNRDtmf;
    pb_callback_t SelfNumber;
    pb_callback_t TargetNumber;
    int32_t AtsR2SNRLin;
/* @@protoc_insertion_point(struct:json2proto_json2proto_MN921_ATS_ATS) */
} json2proto_json2proto_MN921_ATS_ATS;

typedef struct _json2proto_json2proto_MN921_ATS_SubscriberForCall {
    char abonent[5];
    int32_t id;
/* @@protoc_insertion_point(struct:json2proto_json2proto_MN921_ATS_SubscriberForCall) */
} json2proto_json2proto_MN921_ATS_SubscriberForCall;

typedef struct _json2proto_json2proto_MN921_ATS {
    json2proto_json2proto_MN921_ATS_ATS ATS;
    char self_sip_description[5];
    int32_t type_channel;
    int32_t self_port;
    pb_size_t SubscriberForCall_count;
    json2proto_json2proto_MN921_ATS_SubscriberForCall SubscriberForCall[4];
    int32_t audio_port;
    int32_t channel;
/* @@protoc_insertion_point(struct:json2proto_json2proto_MN921_ATS) */
} json2proto_json2proto_MN921_ATS;

/* Default values for struct fields */

/* Initializer values for message structs */
#define json2proto_json2proto_MN921_ATS_init_default {json2proto_json2proto_MN921_ATS_ATS_init_default, "", 0, 0, 0, {json2proto_json2proto_MN921_ATS_SubscriberForCall_init_default, json2proto_json2proto_MN921_ATS_SubscriberForCall_init_default, json2proto_json2proto_MN921_ATS_SubscriberForCall_init_default, json2proto_json2proto_MN921_ATS_SubscriberForCall_init_default}, 0, 0}
#define json2proto_json2proto_MN921_ATS_ATS_init_default {0, 0, 0, {{NULL}, NULL}, {{NULL}, NULL}, 0}
#define json2proto_json2proto_MN921_ATS_SubscriberForCall_init_default {"", 0}
#define json2proto_json2proto_MN921_ATS_init_zero {json2proto_json2proto_MN921_ATS_ATS_init_zero, "", 0, 0, 0, {json2proto_json2proto_MN921_ATS_SubscriberForCall_init_zero, json2proto_json2proto_MN921_ATS_SubscriberForCall_init_zero, json2proto_json2proto_MN921_ATS_SubscriberForCall_init_zero, json2proto_json2proto_MN921_ATS_SubscriberForCall_init_zero}, 0, 0}
#define json2proto_json2proto_MN921_ATS_ATS_init_zero {0, 0, 0, {{NULL}, NULL}, {{NULL}, NULL}, 0}
#define json2proto_json2proto_MN921_ATS_SubscriberForCall_init_zero {"", 0}

/* Field tags (for use in manual encoding/decoding) */
#define json2proto_json2proto_MN921_ATS_ATS_Type_tag 1
#define json2proto_json2proto_MN921_ATS_ATS_AtsR2Priority_tag 2
#define json2proto_json2proto_MN921_ATS_ATS_AtsR2SNRDtmf_tag 3
#define json2proto_json2proto_MN921_ATS_ATS_SelfNumber_tag 4
#define json2proto_json2proto_MN921_ATS_ATS_TargetNumber_tag 5
#define json2proto_json2proto_MN921_ATS_ATS_AtsR2SNRLin_tag 6
#define json2proto_json2proto_MN921_ATS_SubscriberForCall_abonent_tag 1
#define json2proto_json2proto_MN921_ATS_SubscriberForCall_id_tag 2
#define json2proto_json2proto_MN921_ATS_ATS_tag  1
#define json2proto_json2proto_MN921_ATS_self_sip_description_tag 2
#define json2proto_json2proto_MN921_ATS_type_channel_tag 3
#define json2proto_json2proto_MN921_ATS_self_port_tag 4
#define json2proto_json2proto_MN921_ATS_SubscriberForCall_tag 5
#define json2proto_json2proto_MN921_ATS_audio_port_tag 6
#define json2proto_json2proto_MN921_ATS_channel_tag 7

/* Struct field encoding specification for nanopb */
extern const pb_field_t json2proto_json2proto_MN921_ATS_fields[8];
extern const pb_field_t json2proto_json2proto_MN921_ATS_ATS_fields[7];
extern const pb_field_t json2proto_json2proto_MN921_ATS_SubscriberForCall_fields[3];

/* Maximum encoded size of messages (where known) */
#define json2proto_json2proto_MN921_ATS_size     (137 + json2proto_json2proto_MN921_ATS_ATS_size)
/* json2proto_json2proto_MN921_ATS_ATS_size depends on runtime parameters */
#define json2proto_json2proto_MN921_ATS_SubscriberForCall_size 18

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define MN921_ATS_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
