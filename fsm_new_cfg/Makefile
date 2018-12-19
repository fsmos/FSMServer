# Include the nanopb provided Makefile rules
include ../../extra/nanopb.mk

# Compiler flags to enable all warnings & debug info
CFLAGS = -Wall -Werror -g -O0
CFLAGS += -I$(NANOPB_DIR)

# C source code files that are required

CSRC += fsm_cckconfig_clientinfo.pb.c               # The compiled protocol definition
CSRC += fsm_cckconfig_MN.pb.c               # The compiled protocol definition
CSRC += fsm_cckconfig_PO.pb.c               # The compiled protocol definition
CSRC += $(NANOPB_DIR)/pb_encode.c  # The nanopb encoder
CSRC += $(NANOPB_DIR)/pb_decode.c  # The nanopb decoder
CSRC += $(NANOPB_DIR)/pb_common.c  # The nanopb common parts

# Build rule for the main program
CCKSV: $(CSRC)
	$(CC) $(CFLAGS) -osimple $(CSRC)

# Build rule for the protocol
fsm_cckconfig_clientinfo.pb.c: fsm_cckconfig_clientinfo.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=./nanopb fsm_cckconfig_clientinfo.proto

fsm_cckconfig_MN.pb.c: fsm_cckconfig_MN.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=./nanopb fsm_cckconfig_MN.proto

fsm_cckconfig_PO.pb.c: fsm_cckconfig_PO.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=./nanopb fsm_cckconfig_PO.proto


