/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.0-dev at Mon Aug 20 13:35:56 2018. */

#ifndef PB_FSM_FSM_CCKCONFIG_PO_PB_H_INCLUDED
#define PB_FSM_FSM_CCKCONFIG_PO_PB_H_INCLUDED
#include <pb.h>

#include "fsm_cckconfig_clientinfo.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _fsm_P0_Group_subel {
    pb_size_t abonent_count;
    uint32_t abonent[10];
/* @@protoc_insertion_point(struct:fsm_P0_Group_subel) */
} fsm_P0_Group_subel;

typedef struct _fsm_PO_Subscriber {
    uint32_t sip_number;
    uint32_t flags;
/* @@protoc_insertion_point(struct:fsm_PO_Subscriber) */
} fsm_PO_Subscriber;

typedef struct _fsm_P0_Group_el {
    pb_size_t grp_count;
    fsm_P0_Group_subel grp[4];
/* @@protoc_insertion_point(struct:fsm_P0_Group_el) */
} fsm_P0_Group_el;

typedef struct _fsm_PO_Channel {
    uint32_t self_sip_port;
    uint32_t self_rtp_port;
    uint32_t self_sip_number;
    uint32_t volume;
    pb_size_t SubscriberForCall_count;
    fsm_PO_Subscriber SubscriberForCall[12];
/* @@protoc_insertion_point(struct:fsm_PO_Channel) */
} fsm_PO_Channel;

typedef struct _fsm_P0_Group {
    fsm_P0_Group_el cnfg;
    fsm_P0_Group_el csvg;
/* @@protoc_insertion_point(struct:fsm_P0_Group) */
} fsm_P0_Group;

typedef PB_BYTES_ARRAY_T(6) fsm_P0_mac_t;
typedef struct _fsm_P0 {
    fsm_ClientInfo client;
    fsm_P0_Group grp;
    fsm_P0_mac_t mac;
    pb_size_t channel_count;
    fsm_PO_Channel channel[2];
/* @@protoc_insertion_point(struct:fsm_P0) */
} fsm_P0;

/* Default values for struct fields */

/* Initializer values for message structs */
#define fsm_P0_Group_subel_init_default          {0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define fsm_P0_Group_el_init_default             {0, {fsm_P0_Group_subel_init_default, fsm_P0_Group_subel_init_default, fsm_P0_Group_subel_init_default, fsm_P0_Group_subel_init_default}}
#define fsm_P0_Group_init_default                {fsm_P0_Group_el_init_default, fsm_P0_Group_el_init_default}
#define fsm_PO_Subscriber_init_default           {0, 0}
#define fsm_PO_Channel_init_default              {0, 0, 0, 0, 0, {fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default, fsm_PO_Subscriber_init_default}}
#define fsm_P0_init_default                      {fsm_ClientInfo_init_default, fsm_P0_Group_init_default, {0, {0}}, 0, {fsm_PO_Channel_init_default, fsm_PO_Channel_init_default}}
#define fsm_P0_Group_subel_init_zero             {0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define fsm_P0_Group_el_init_zero                {0, {fsm_P0_Group_subel_init_zero, fsm_P0_Group_subel_init_zero, fsm_P0_Group_subel_init_zero, fsm_P0_Group_subel_init_zero}}
#define fsm_P0_Group_init_zero                   {fsm_P0_Group_el_init_zero, fsm_P0_Group_el_init_zero}
#define fsm_PO_Subscriber_init_zero              {0, 0}
#define fsm_PO_Channel_init_zero                 {0, 0, 0, 0, 0, {fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero, fsm_PO_Subscriber_init_zero}}
#define fsm_P0_init_zero                         {fsm_ClientInfo_init_zero, fsm_P0_Group_init_zero, {0, {0}}, 0, {fsm_PO_Channel_init_zero, fsm_PO_Channel_init_zero}}

/* Field tags (for use in manual encoding/decoding) */
#define fsm_P0_Group_subel_abonent_tag           1
#define fsm_PO_Subscriber_sip_number_tag         1
#define fsm_PO_Subscriber_flags_tag              2
#define fsm_P0_Group_el_grp_tag                  1
#define fsm_PO_Channel_self_sip_port_tag         1
#define fsm_PO_Channel_self_rtp_port_tag         2
#define fsm_PO_Channel_self_sip_number_tag       3
#define fsm_PO_Channel_volume_tag                4
#define fsm_PO_Channel_SubscriberForCall_tag     5
#define fsm_P0_Group_cnfg_tag                    1
#define fsm_P0_Group_csvg_tag                    2
#define fsm_P0_client_tag                        1
#define fsm_P0_grp_tag                           2
#define fsm_P0_mac_tag                           3
#define fsm_P0_channel_tag                       4

/* Struct field encoding specification for nanopb */
extern const pb_field_t fsm_P0_Group_subel_fields[2];
extern const pb_field_t fsm_P0_Group_el_fields[2];
extern const pb_field_t fsm_P0_Group_fields[3];
extern const pb_field_t fsm_PO_Subscriber_fields[3];
extern const pb_field_t fsm_PO_Channel_fields[6];
extern const pb_field_t fsm_P0_fields[5];

/* Maximum encoded size of messages (where known) */
#define fsm_P0_Group_subel_size                  60
#define fsm_P0_Group_el_size                     248
#define fsm_P0_Group_size                        502
#define fsm_PO_Subscriber_size                   12
#define fsm_PO_Channel_size                      192
#define fsm_P0_size                              960

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define FSM_CCKCONFIG_PO_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
