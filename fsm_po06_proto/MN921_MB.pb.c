/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.4.0-dev at Tue Jun 19 19:11:19 2018. */

#include "MN921_MB.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t json2proto_json2proto_MN921_MB_fields[8] = {
    PB_FIELD(  1, STRING  , SINGULAR, STATIC  , FIRST, json2proto_json2proto_MN921_MB, self_sip_description, self_sip_description, 0),
    PB_FIELD(  2, INT32   , SINGULAR, STATIC  , OTHER, json2proto_json2proto_MN921_MB, type_channel, self_sip_description, 0),
    PB_FIELD(  3, MESSAGE , SINGULAR, STATIC  , OTHER, json2proto_json2proto_MN921_MB, MB, type_channel, &json2proto_json2proto_MN921_MB_MB_fields),
    PB_FIELD(  4, INT32   , SINGULAR, STATIC  , OTHER, json2proto_json2proto_MN921_MB, self_port, MB, 0),
    PB_FIELD(  5, INT32   , SINGULAR, STATIC  , OTHER, json2proto_json2proto_MN921_MB, audio_port, self_port, 0),
    PB_FIELD(  6, MESSAGE , REPEATED, STATIC  , OTHER, json2proto_json2proto_MN921_MB, SubscriberForCall, audio_port, &json2proto_json2proto_MN921_MB_SubscriberForCall_fields),
    PB_FIELD(  7, INT32   , SINGULAR, STATIC  , OTHER, json2proto_json2proto_MN921_MB, channel, SubscriberForCall, 0),
    PB_LAST_FIELD
};

const pb_field_t json2proto_json2proto_MN921_MB_MB_fields[2] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, json2proto_json2proto_MN921_MB_MB, ToneOutputCallPulse, ToneOutputCallPulse, 0),
    PB_LAST_FIELD
};

const pb_field_t json2proto_json2proto_MN921_MB_SubscriberForCall_fields[3] = {
    PB_FIELD(  1, STRING  , SINGULAR, STATIC  , FIRST, json2proto_json2proto_MN921_MB_SubscriberForCall, abonent, abonent, 0),
    PB_FIELD(  2, INT32   , SINGULAR, STATIC  , OTHER, json2proto_json2proto_MN921_MB_SubscriberForCall, id, abonent, 0),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(json2proto_json2proto_MN921_MB, MB) < 65536 && pb_membersize(json2proto_json2proto_MN921_MB, SubscriberForCall[0]) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_json2proto_json2proto_MN921_MB_json2proto_json2proto_MN921_MB_MB_json2proto_json2proto_MN921_MB_SubscriberForCall)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(json2proto_json2proto_MN921_MB, MB) < 256 && pb_membersize(json2proto_json2proto_MN921_MB, SubscriberForCall[0]) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_json2proto_json2proto_MN921_MB_json2proto_json2proto_MN921_MB_MB_json2proto_json2proto_MN921_MB_SubscriberForCall)
#endif


/* @@protoc_insertion_point(eof) */
