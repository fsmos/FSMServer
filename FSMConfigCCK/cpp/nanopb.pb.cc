// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: nanopb.proto

#include "nanopb.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace protobuf_nanopb_2eproto {
extern PROTOBUF_INTERNAL_EXPORT_protobuf_nanopb_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_NanoPBOptions;
}  // namespace protobuf_nanopb_2eproto
class NanoPBOptionsDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<NanoPBOptions>
      _instance;
} _NanoPBOptions_default_instance_;
namespace protobuf_nanopb_2eproto {
static void InitDefaultsNanoPBOptions() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_NanoPBOptions_default_instance_;
    new (ptr) ::NanoPBOptions();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::NanoPBOptions::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_NanoPBOptions =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsNanoPBOptions}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_NanoPBOptions.base);
}

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[2];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, max_size_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, max_length_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, max_count_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, int_size_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, type_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, long_names_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, packed_struct_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, packed_enum_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, skip_message_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, no_unions_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, msgid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, anonymous_oneof_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, proto3_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, enum_to_string_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, fixed_length_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::NanoPBOptions, fixed_count_),
  0,
  13,
  1,
  3,
  2,
  15,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  14,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 21, sizeof(::NanoPBOptions)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::_NanoPBOptions_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "nanopb.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\014nanopb.proto\032 google/protobuf/descript"
      "or.proto\"\277\003\n\rNanoPBOptions\022\020\n\010max_size\030\001"
      " \001(\005\022\022\n\nmax_length\030\016 \001(\005\022\021\n\tmax_count\030\002 "
      "\001(\005\022&\n\010int_size\030\007 \001(\0162\010.IntSize:\nIS_DEFA"
      "ULT\022$\n\004type\030\003 \001(\0162\n.FieldType:\nFT_DEFAUL"
      "T\022\030\n\nlong_names\030\004 \001(\010:\004true\022\034\n\rpacked_st"
      "ruct\030\005 \001(\010:\005false\022\032\n\013packed_enum\030\n \001(\010:\005"
      "false\022\033\n\014skip_message\030\006 \001(\010:\005false\022\030\n\tno"
      "_unions\030\010 \001(\010:\005false\022\r\n\005msgid\030\t \001(\r\022\036\n\017a"
      "nonymous_oneof\030\013 \001(\010:\005false\022\025\n\006proto3\030\014 "
      "\001(\010:\005false\022\035\n\016enum_to_string\030\r \001(\010:\005fals"
      "e\022\033\n\014fixed_length\030\017 \001(\010:\005false\022\032\n\013fixed_"
      "count\030\020 \001(\010:\005false*i\n\tFieldType\022\016\n\nFT_DE"
      "FAULT\020\000\022\017\n\013FT_CALLBACK\020\001\022\016\n\nFT_POINTER\020\004"
      "\022\r\n\tFT_STATIC\020\002\022\r\n\tFT_IGNORE\020\003\022\r\n\tFT_INL"
      "INE\020\005*D\n\007IntSize\022\016\n\nIS_DEFAULT\020\000\022\010\n\004IS_8"
      "\020\010\022\t\n\005IS_16\020\020\022\t\n\005IS_32\020 \022\t\n\005IS_64\020@:E\n\016n"
      "anopb_fileopt\022\034.google.protobuf.FileOpti"
      "ons\030\362\007 \001(\0132\016.NanoPBOptions:G\n\rnanopb_msg"
      "opt\022\037.google.protobuf.MessageOptions\030\362\007 "
      "\001(\0132\016.NanoPBOptions:E\n\016nanopb_enumopt\022\034."
      "google.protobuf.EnumOptions\030\362\007 \001(\0132\016.Nan"
      "oPBOptions:>\n\006nanopb\022\035.google.protobuf.F"
      "ieldOptions\030\362\007 \001(\0132\016.NanoPBOptionsB\032\n\030fi"
      ".kapsi.koti.jpa.nanopb"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 982);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "nanopb.proto", &protobuf_RegisterTypes);
  ::protobuf_google_2fprotobuf_2fdescriptor_2eproto::AddDescriptors();
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_nanopb_2eproto
const ::google::protobuf::EnumDescriptor* FieldType_descriptor() {
  protobuf_nanopb_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_nanopb_2eproto::file_level_enum_descriptors[0];
}
bool FieldType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* IntSize_descriptor() {
  protobuf_nanopb_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_nanopb_2eproto::file_level_enum_descriptors[1];
}
bool IntSize_IsValid(int value) {
  switch (value) {
    case 0:
    case 8:
    case 16:
    case 32:
    case 64:
      return true;
    default:
      return false;
  }
}


// ===================================================================

void NanoPBOptions::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int NanoPBOptions::kMaxSizeFieldNumber;
const int NanoPBOptions::kMaxLengthFieldNumber;
const int NanoPBOptions::kMaxCountFieldNumber;
const int NanoPBOptions::kIntSizeFieldNumber;
const int NanoPBOptions::kTypeFieldNumber;
const int NanoPBOptions::kLongNamesFieldNumber;
const int NanoPBOptions::kPackedStructFieldNumber;
const int NanoPBOptions::kPackedEnumFieldNumber;
const int NanoPBOptions::kSkipMessageFieldNumber;
const int NanoPBOptions::kNoUnionsFieldNumber;
const int NanoPBOptions::kMsgidFieldNumber;
const int NanoPBOptions::kAnonymousOneofFieldNumber;
const int NanoPBOptions::kProto3FieldNumber;
const int NanoPBOptions::kEnumToStringFieldNumber;
const int NanoPBOptions::kFixedLengthFieldNumber;
const int NanoPBOptions::kFixedCountFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

NanoPBOptions::NanoPBOptions()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_nanopb_2eproto::scc_info_NanoPBOptions.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:NanoPBOptions)
}
NanoPBOptions::NanoPBOptions(const NanoPBOptions& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&max_size_, &from.max_size_,
    static_cast<size_t>(reinterpret_cast<char*>(&long_names_) -
    reinterpret_cast<char*>(&max_size_)) + sizeof(long_names_));
  // @@protoc_insertion_point(copy_constructor:NanoPBOptions)
}

void NanoPBOptions::SharedCtor() {
  ::memset(&max_size_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&fixed_count_) -
      reinterpret_cast<char*>(&max_size_)) + sizeof(fixed_count_));
  long_names_ = true;
}

NanoPBOptions::~NanoPBOptions() {
  // @@protoc_insertion_point(destructor:NanoPBOptions)
  SharedDtor();
}

void NanoPBOptions::SharedDtor() {
}

void NanoPBOptions::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* NanoPBOptions::descriptor() {
  ::protobuf_nanopb_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_nanopb_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const NanoPBOptions& NanoPBOptions::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_nanopb_2eproto::scc_info_NanoPBOptions.base);
  return *internal_default_instance();
}


void NanoPBOptions::Clear() {
// @@protoc_insertion_point(message_clear_start:NanoPBOptions)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 255u) {
    ::memset(&max_size_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&no_unions_) -
        reinterpret_cast<char*>(&max_size_)) + sizeof(no_unions_));
  }
  if (cached_has_bits & 65280u) {
    ::memset(&msgid_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&fixed_count_) -
        reinterpret_cast<char*>(&msgid_)) + sizeof(fixed_count_));
    long_names_ = true;
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool NanoPBOptions::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:NanoPBOptions)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(16383u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 max_size = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          set_has_max_size();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &max_size_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int32 max_count = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
          set_has_max_count();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &max_count_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional .FieldType type = 3 [default = FT_DEFAULT];
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::FieldType_IsValid(value)) {
            set_type(static_cast< ::FieldType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                3, static_cast< ::google::protobuf::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool long_names = 4 [default = true];
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {
          set_has_long_names();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &long_names_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool packed_struct = 5 [default = false];
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(40u /* 40 & 0xFF */)) {
          set_has_packed_struct();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &packed_struct_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool skip_message = 6 [default = false];
      case 6: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(48u /* 48 & 0xFF */)) {
          set_has_skip_message();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &skip_message_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional .IntSize int_size = 7 [default = IS_DEFAULT];
      case 7: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(56u /* 56 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::IntSize_IsValid(value)) {
            set_int_size(static_cast< ::IntSize >(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                7, static_cast< ::google::protobuf::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool no_unions = 8 [default = false];
      case 8: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(64u /* 64 & 0xFF */)) {
          set_has_no_unions();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &no_unions_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 msgid = 9;
      case 9: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(72u /* 72 & 0xFF */)) {
          set_has_msgid();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &msgid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool packed_enum = 10 [default = false];
      case 10: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(80u /* 80 & 0xFF */)) {
          set_has_packed_enum();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &packed_enum_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool anonymous_oneof = 11 [default = false];
      case 11: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(88u /* 88 & 0xFF */)) {
          set_has_anonymous_oneof();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &anonymous_oneof_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool proto3 = 12 [default = false];
      case 12: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(96u /* 96 & 0xFF */)) {
          set_has_proto3();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &proto3_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool enum_to_string = 13 [default = false];
      case 13: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(104u /* 104 & 0xFF */)) {
          set_has_enum_to_string();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &enum_to_string_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int32 max_length = 14;
      case 14: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(112u /* 112 & 0xFF */)) {
          set_has_max_length();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &max_length_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool fixed_length = 15 [default = false];
      case 15: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(120u /* 120 & 0xFF */)) {
          set_has_fixed_length();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &fixed_length_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool fixed_count = 16 [default = false];
      case 16: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(128u /* 128 & 0xFF */)) {
          set_has_fixed_count();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &fixed_count_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:NanoPBOptions)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:NanoPBOptions)
  return false;
#undef DO_
}

void NanoPBOptions::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:NanoPBOptions)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 max_size = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->max_size(), output);
  }

  // optional int32 max_count = 2;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->max_count(), output);
  }

  // optional .FieldType type = 3 [default = FT_DEFAULT];
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->type(), output);
  }

  // optional bool long_names = 4 [default = true];
  if (cached_has_bits & 0x00008000u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->long_names(), output);
  }

  // optional bool packed_struct = 5 [default = false];
  if (cached_has_bits & 0x00000010u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->packed_struct(), output);
  }

  // optional bool skip_message = 6 [default = false];
  if (cached_has_bits & 0x00000040u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(6, this->skip_message(), output);
  }

  // optional .IntSize int_size = 7 [default = IS_DEFAULT];
  if (cached_has_bits & 0x00000008u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      7, this->int_size(), output);
  }

  // optional bool no_unions = 8 [default = false];
  if (cached_has_bits & 0x00000080u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(8, this->no_unions(), output);
  }

  // optional uint32 msgid = 9;
  if (cached_has_bits & 0x00000100u) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->msgid(), output);
  }

  // optional bool packed_enum = 10 [default = false];
  if (cached_has_bits & 0x00000020u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(10, this->packed_enum(), output);
  }

  // optional bool anonymous_oneof = 11 [default = false];
  if (cached_has_bits & 0x00000200u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(11, this->anonymous_oneof(), output);
  }

  // optional bool proto3 = 12 [default = false];
  if (cached_has_bits & 0x00000400u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(12, this->proto3(), output);
  }

  // optional bool enum_to_string = 13 [default = false];
  if (cached_has_bits & 0x00000800u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(13, this->enum_to_string(), output);
  }

  // optional int32 max_length = 14;
  if (cached_has_bits & 0x00002000u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(14, this->max_length(), output);
  }

  // optional bool fixed_length = 15 [default = false];
  if (cached_has_bits & 0x00001000u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(15, this->fixed_length(), output);
  }

  // optional bool fixed_count = 16 [default = false];
  if (cached_has_bits & 0x00004000u) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(16, this->fixed_count(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:NanoPBOptions)
}

::google::protobuf::uint8* NanoPBOptions::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:NanoPBOptions)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 max_size = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->max_size(), target);
  }

  // optional int32 max_count = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->max_count(), target);
  }

  // optional .FieldType type = 3 [default = FT_DEFAULT];
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      3, this->type(), target);
  }

  // optional bool long_names = 4 [default = true];
  if (cached_has_bits & 0x00008000u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->long_names(), target);
  }

  // optional bool packed_struct = 5 [default = false];
  if (cached_has_bits & 0x00000010u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->packed_struct(), target);
  }

  // optional bool skip_message = 6 [default = false];
  if (cached_has_bits & 0x00000040u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(6, this->skip_message(), target);
  }

  // optional .IntSize int_size = 7 [default = IS_DEFAULT];
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      7, this->int_size(), target);
  }

  // optional bool no_unions = 8 [default = false];
  if (cached_has_bits & 0x00000080u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(8, this->no_unions(), target);
  }

  // optional uint32 msgid = 9;
  if (cached_has_bits & 0x00000100u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(9, this->msgid(), target);
  }

  // optional bool packed_enum = 10 [default = false];
  if (cached_has_bits & 0x00000020u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(10, this->packed_enum(), target);
  }

  // optional bool anonymous_oneof = 11 [default = false];
  if (cached_has_bits & 0x00000200u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(11, this->anonymous_oneof(), target);
  }

  // optional bool proto3 = 12 [default = false];
  if (cached_has_bits & 0x00000400u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(12, this->proto3(), target);
  }

  // optional bool enum_to_string = 13 [default = false];
  if (cached_has_bits & 0x00000800u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(13, this->enum_to_string(), target);
  }

  // optional int32 max_length = 14;
  if (cached_has_bits & 0x00002000u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(14, this->max_length(), target);
  }

  // optional bool fixed_length = 15 [default = false];
  if (cached_has_bits & 0x00001000u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(15, this->fixed_length(), target);
  }

  // optional bool fixed_count = 16 [default = false];
  if (cached_has_bits & 0x00004000u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(16, this->fixed_count(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:NanoPBOptions)
  return target;
}

size_t NanoPBOptions::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:NanoPBOptions)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (_has_bits_[0 / 32] & 255u) {
    // optional int32 max_size = 1;
    if (has_max_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->max_size());
    }

    // optional int32 max_count = 2;
    if (has_max_count()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->max_count());
    }

    // optional .FieldType type = 3 [default = FT_DEFAULT];
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }

    // optional .IntSize int_size = 7 [default = IS_DEFAULT];
    if (has_int_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->int_size());
    }

    // optional bool packed_struct = 5 [default = false];
    if (has_packed_struct()) {
      total_size += 1 + 1;
    }

    // optional bool packed_enum = 10 [default = false];
    if (has_packed_enum()) {
      total_size += 1 + 1;
    }

    // optional bool skip_message = 6 [default = false];
    if (has_skip_message()) {
      total_size += 1 + 1;
    }

    // optional bool no_unions = 8 [default = false];
    if (has_no_unions()) {
      total_size += 1 + 1;
    }

  }
  if (_has_bits_[8 / 32] & 65280u) {
    // optional uint32 msgid = 9;
    if (has_msgid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->msgid());
    }

    // optional bool anonymous_oneof = 11 [default = false];
    if (has_anonymous_oneof()) {
      total_size += 1 + 1;
    }

    // optional bool proto3 = 12 [default = false];
    if (has_proto3()) {
      total_size += 1 + 1;
    }

    // optional bool enum_to_string = 13 [default = false];
    if (has_enum_to_string()) {
      total_size += 1 + 1;
    }

    // optional bool fixed_length = 15 [default = false];
    if (has_fixed_length()) {
      total_size += 1 + 1;
    }

    // optional int32 max_length = 14;
    if (has_max_length()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->max_length());
    }

    // optional bool fixed_count = 16 [default = false];
    if (has_fixed_count()) {
      total_size += 2 + 1;
    }

    // optional bool long_names = 4 [default = true];
    if (has_long_names()) {
      total_size += 1 + 1;
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void NanoPBOptions::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:NanoPBOptions)
  GOOGLE_DCHECK_NE(&from, this);
  const NanoPBOptions* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const NanoPBOptions>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:NanoPBOptions)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:NanoPBOptions)
    MergeFrom(*source);
  }
}

void NanoPBOptions::MergeFrom(const NanoPBOptions& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:NanoPBOptions)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 255u) {
    if (cached_has_bits & 0x00000001u) {
      max_size_ = from.max_size_;
    }
    if (cached_has_bits & 0x00000002u) {
      max_count_ = from.max_count_;
    }
    if (cached_has_bits & 0x00000004u) {
      type_ = from.type_;
    }
    if (cached_has_bits & 0x00000008u) {
      int_size_ = from.int_size_;
    }
    if (cached_has_bits & 0x00000010u) {
      packed_struct_ = from.packed_struct_;
    }
    if (cached_has_bits & 0x00000020u) {
      packed_enum_ = from.packed_enum_;
    }
    if (cached_has_bits & 0x00000040u) {
      skip_message_ = from.skip_message_;
    }
    if (cached_has_bits & 0x00000080u) {
      no_unions_ = from.no_unions_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  if (cached_has_bits & 65280u) {
    if (cached_has_bits & 0x00000100u) {
      msgid_ = from.msgid_;
    }
    if (cached_has_bits & 0x00000200u) {
      anonymous_oneof_ = from.anonymous_oneof_;
    }
    if (cached_has_bits & 0x00000400u) {
      proto3_ = from.proto3_;
    }
    if (cached_has_bits & 0x00000800u) {
      enum_to_string_ = from.enum_to_string_;
    }
    if (cached_has_bits & 0x00001000u) {
      fixed_length_ = from.fixed_length_;
    }
    if (cached_has_bits & 0x00002000u) {
      max_length_ = from.max_length_;
    }
    if (cached_has_bits & 0x00004000u) {
      fixed_count_ = from.fixed_count_;
    }
    if (cached_has_bits & 0x00008000u) {
      long_names_ = from.long_names_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void NanoPBOptions::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:NanoPBOptions)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void NanoPBOptions::CopyFrom(const NanoPBOptions& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:NanoPBOptions)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NanoPBOptions::IsInitialized() const {
  return true;
}

void NanoPBOptions::Swap(NanoPBOptions* other) {
  if (other == this) return;
  InternalSwap(other);
}
void NanoPBOptions::InternalSwap(NanoPBOptions* other) {
  using std::swap;
  swap(max_size_, other->max_size_);
  swap(max_count_, other->max_count_);
  swap(type_, other->type_);
  swap(int_size_, other->int_size_);
  swap(packed_struct_, other->packed_struct_);
  swap(packed_enum_, other->packed_enum_);
  swap(skip_message_, other->skip_message_);
  swap(no_unions_, other->no_unions_);
  swap(msgid_, other->msgid_);
  swap(anonymous_oneof_, other->anonymous_oneof_);
  swap(proto3_, other->proto3_);
  swap(enum_to_string_, other->enum_to_string_);
  swap(fixed_length_, other->fixed_length_);
  swap(max_length_, other->max_length_);
  swap(fixed_count_, other->fixed_count_);
  swap(long_names_, other->long_names_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata NanoPBOptions::GetMetadata() const {
  protobuf_nanopb_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_nanopb_2eproto::file_level_metadata[kIndexInFileMessages];
}

::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FileOptions,
    ::google::protobuf::internal::MessageTypeTraits< ::NanoPBOptions >, 11, false >
  nanopb_fileopt(kNanopbFileoptFieldNumber, *::NanoPBOptions::internal_default_instance());
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::MessageOptions,
    ::google::protobuf::internal::MessageTypeTraits< ::NanoPBOptions >, 11, false >
  nanopb_msgopt(kNanopbMsgoptFieldNumber, *::NanoPBOptions::internal_default_instance());
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumOptions,
    ::google::protobuf::internal::MessageTypeTraits< ::NanoPBOptions >, 11, false >
  nanopb_enumopt(kNanopbEnumoptFieldNumber, *::NanoPBOptions::internal_default_instance());
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::MessageTypeTraits< ::NanoPBOptions >, 11, false >
  nanopb(kNanopbFieldNumber, *::NanoPBOptions::internal_default_instance());

// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::NanoPBOptions* Arena::CreateMaybeMessage< ::NanoPBOptions >(Arena* arena) {
  return Arena::CreateInternal< ::NanoPBOptions >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)