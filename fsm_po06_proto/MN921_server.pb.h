/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.0-dev at Mon May 21 13:33:25 2018. */

#ifndef PB_JSON2PROTO_MN921_SERVER_PB_H_INCLUDED
#define PB_JSON2PROTO_MN921_SERVER_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _json2proto_json2proto_MN921_server {
    int32_t server_sip_port;
    int32_t gateway;
    int32_t server_ip;
    int32_t self_ip;
    uint32_t subnet_mask;
/* @@protoc_insertion_point(struct:json2proto_json2proto_MN921_server) */
} json2proto_json2proto_MN921_server;

/* Default values for struct fields */

/* Initializer values for message structs */
#define json2proto_json2proto_MN921_server_init_default {0, 0, 0, 0, 0}
#define json2proto_json2proto_MN921_server_init_zero {0, 0, 0, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define json2proto_json2proto_MN921_server_server_sip_port_tag 1
#define json2proto_json2proto_MN921_server_gateway_tag 2
#define json2proto_json2proto_MN921_server_server_ip_tag 3
#define json2proto_json2proto_MN921_server_self_ip_tag 4
#define json2proto_json2proto_MN921_server_subnet_mask_tag 5

/* Struct field encoding specification for nanopb */
extern const pb_field_t json2proto_json2proto_MN921_server_fields[6];

/* Maximum encoded size of messages (where known) */
#define json2proto_json2proto_MN921_server_size  50

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define MN921_SERVER_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif