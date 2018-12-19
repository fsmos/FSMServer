# Include the nanopb provided Makefile rules
include ../../extra/nanopb.mk

# Compiler flags to enable all warnings & debug info
CFLAGS = -Wall -Werror -g -O0
CFLAGS += -I$(NANOPB_DIR)

# C source code files that are required
CSRC += MN921_server.pb.c                # The compiled protocol definition
CSRC += MN921_ATS.pb.c                # The compiled protocol definition
CSRC += MN921_TCH.pb.c                # The compiled protocol definition
CSRC += MN921_MB.pb.c                # The compiled protocol definition
CSRC += MN921_CB.pb.c                # The compiled protocol definition
CSRC += $(NANOPB_DIR)/pb_encode.c  # The nanopb encoder
CSRC += $(NANOPB_DIR)/pb_decode.c  # The nanopb decoder
CSRC += $(NANOPB_DIR)/pb_common.c  # The nanopb common parts

# Build rule for the main program
MN921_ATS: $(CSRC)
	$(CC) $(CFLAGS) -osimple $(CSRC)

# Build rule for the protocol
MN921_server.pb.c: MN921_server.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. MN921_server.proto

MN921_ATS.pb.c: MN921_ATS.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. MN921_ATS.proto

MN921_TCH.pb.c: MN921_TCH.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. MN921_TCH.proto

MN921_MB.pb.c: MN921_MB.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. MN921_MB.proto

MN921_CB.pb.c: MN921_CB.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. MN921_CB.proto