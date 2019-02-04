// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: fsm_cckconfig_MN401.proto

#include "fsm_cckconfig_MN401.pb.h"

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

namespace protobuf_fsm_5fcckconfig_5fMN401_2eproto {
extern PROTOBUF_INTERNAL_EXPORT_protobuf_fsm_5fcckconfig_5fMN401_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_ServerInfo;
}  // namespace protobuf_fsm_5fcckconfig_5fMN401_2eproto
namespace fsm {
class ServerInfoDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<ServerInfo>
      _instance;
} _ServerInfo_default_instance_;
class MN401DefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<MN401>
      _instance;
} _MN401_default_instance_;
}  // namespace fsm
namespace protobuf_fsm_5fcckconfig_5fMN401_2eproto {
static void InitDefaultsServerInfo() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::fsm::_ServerInfo_default_instance_;
    new (ptr) ::fsm::ServerInfo();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::fsm::ServerInfo::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_ServerInfo =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsServerInfo}, {}};

static void InitDefaultsMN401() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::fsm::_MN401_default_instance_;
    new (ptr) ::fsm::MN401();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::fsm::MN401::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<1> scc_info_MN401 =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsMN401}, {
      &protobuf_fsm_5fcckconfig_5fMN401_2eproto::scc_info_ServerInfo.base,}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_ServerInfo.base);
  ::google::protobuf::internal::InitSCC(&scc_info_MN401.base);
}

::google::protobuf::Metadata file_level_metadata[2];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::fsm::ServerInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::fsm::ServerInfo, ip_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::fsm::ServerInfo, sip_port_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::fsm::MN401, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::fsm::MN401, client_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::fsm::MN401, devlist_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::fsm::ServerInfo)},
  { 7, -1, sizeof(::fsm::MN401)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::fsm::_ServerInfo_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::fsm::_MN401_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "fsm_cckconfig_MN401.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\031fsm_cckconfig_MN401.proto\022\003fsm\"*\n\nServ"
      "erInfo\022\n\n\002ip\030\001 \001(\005\022\020\n\010sip_port\030\002 \001(\005\"M\n\005"
      "MN401\022\037\n\006client\030\001 \001(\0132\017.fsm.ServerInfo\022#"
      "\n\007devlist\030\002 \003(\0162\022.fsm.CCKTypeDevice*\230\001\n\r"
      "CCKTypeDevice\022\013\n\007DT_None\020\000\022\014\n\010DT_MN921\020\001"
      "\022\014\n\010DT_MN825\020\002\022\013\n\007DT_PO07\020\003\022\013\n\007DT_PO08\020\004"
      "\022\013\n\007DT_PO06\020\005\022\014\n\010DT_MN524\020\006\022\014\n\010DT_MN111\020"
      "\007\022\r\n\tDT_VirtPO\020\010\022\014\n\010DT_MN401\020\tb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 318);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "fsm_cckconfig_MN401.proto", &protobuf_RegisterTypes);
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
}  // namespace protobuf_fsm_5fcckconfig_5fMN401_2eproto
namespace fsm {
const ::google::protobuf::EnumDescriptor* CCKTypeDevice_descriptor() {
  protobuf_fsm_5fcckconfig_5fMN401_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_fsm_5fcckconfig_5fMN401_2eproto::file_level_enum_descriptors[0];
}
bool CCKTypeDevice_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      return true;
    default:
      return false;
  }
}


// ===================================================================

void ServerInfo::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ServerInfo::kIpFieldNumber;
const int ServerInfo::kSipPortFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ServerInfo::ServerInfo()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_fsm_5fcckconfig_5fMN401_2eproto::scc_info_ServerInfo.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:fsm.ServerInfo)
}
ServerInfo::ServerInfo(const ServerInfo& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&ip_, &from.ip_,
    static_cast<size_t>(reinterpret_cast<char*>(&sip_port_) -
    reinterpret_cast<char*>(&ip_)) + sizeof(sip_port_));
  // @@protoc_insertion_point(copy_constructor:fsm.ServerInfo)
}

void ServerInfo::SharedCtor() {
  ::memset(&ip_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&sip_port_) -
      reinterpret_cast<char*>(&ip_)) + sizeof(sip_port_));
}

ServerInfo::~ServerInfo() {
  // @@protoc_insertion_point(destructor:fsm.ServerInfo)
  SharedDtor();
}

void ServerInfo::SharedDtor() {
}

void ServerInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* ServerInfo::descriptor() {
  ::protobuf_fsm_5fcckconfig_5fMN401_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_fsm_5fcckconfig_5fMN401_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const ServerInfo& ServerInfo::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_fsm_5fcckconfig_5fMN401_2eproto::scc_info_ServerInfo.base);
  return *internal_default_instance();
}


void ServerInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:fsm.ServerInfo)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&ip_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&sip_port_) -
      reinterpret_cast<char*>(&ip_)) + sizeof(sip_port_));
  _internal_metadata_.Clear();
}

bool ServerInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:fsm.ServerInfo)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 ip = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &ip_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 sip_port = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &sip_port_)));
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
  // @@protoc_insertion_point(parse_success:fsm.ServerInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:fsm.ServerInfo)
  return false;
#undef DO_
}

void ServerInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:fsm.ServerInfo)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 ip = 1;
  if (this->ip() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->ip(), output);
  }

  // int32 sip_port = 2;
  if (this->sip_port() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->sip_port(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:fsm.ServerInfo)
}

::google::protobuf::uint8* ServerInfo::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:fsm.ServerInfo)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 ip = 1;
  if (this->ip() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->ip(), target);
  }

  // int32 sip_port = 2;
  if (this->sip_port() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->sip_port(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:fsm.ServerInfo)
  return target;
}

size_t ServerInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:fsm.ServerInfo)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // int32 ip = 1;
  if (this->ip() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->ip());
  }

  // int32 sip_port = 2;
  if (this->sip_port() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->sip_port());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ServerInfo::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:fsm.ServerInfo)
  GOOGLE_DCHECK_NE(&from, this);
  const ServerInfo* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ServerInfo>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:fsm.ServerInfo)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:fsm.ServerInfo)
    MergeFrom(*source);
  }
}

void ServerInfo::MergeFrom(const ServerInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:fsm.ServerInfo)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.ip() != 0) {
    set_ip(from.ip());
  }
  if (from.sip_port() != 0) {
    set_sip_port(from.sip_port());
  }
}

void ServerInfo::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:fsm.ServerInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ServerInfo::CopyFrom(const ServerInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:fsm.ServerInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ServerInfo::IsInitialized() const {
  return true;
}

void ServerInfo::Swap(ServerInfo* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ServerInfo::InternalSwap(ServerInfo* other) {
  using std::swap;
  swap(ip_, other->ip_);
  swap(sip_port_, other->sip_port_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata ServerInfo::GetMetadata() const {
  protobuf_fsm_5fcckconfig_5fMN401_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_fsm_5fcckconfig_5fMN401_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void MN401::InitAsDefaultInstance() {
  ::fsm::_MN401_default_instance_._instance.get_mutable()->client_ = const_cast< ::fsm::ServerInfo*>(
      ::fsm::ServerInfo::internal_default_instance());
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int MN401::kClientFieldNumber;
const int MN401::kDevlistFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

MN401::MN401()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_fsm_5fcckconfig_5fMN401_2eproto::scc_info_MN401.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:fsm.MN401)
}
MN401::MN401(const MN401& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      devlist_(from.devlist_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_client()) {
    client_ = new ::fsm::ServerInfo(*from.client_);
  } else {
    client_ = NULL;
  }
  // @@protoc_insertion_point(copy_constructor:fsm.MN401)
}

void MN401::SharedCtor() {
  client_ = NULL;
}

MN401::~MN401() {
  // @@protoc_insertion_point(destructor:fsm.MN401)
  SharedDtor();
}

void MN401::SharedDtor() {
  if (this != internal_default_instance()) delete client_;
}

void MN401::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* MN401::descriptor() {
  ::protobuf_fsm_5fcckconfig_5fMN401_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_fsm_5fcckconfig_5fMN401_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const MN401& MN401::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_fsm_5fcckconfig_5fMN401_2eproto::scc_info_MN401.base);
  return *internal_default_instance();
}


void MN401::Clear() {
// @@protoc_insertion_point(message_clear_start:fsm.MN401)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  devlist_.Clear();
  if (GetArenaNoVirtual() == NULL && client_ != NULL) {
    delete client_;
  }
  client_ = NULL;
  _internal_metadata_.Clear();
}

bool MN401::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:fsm.MN401)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .fsm.ServerInfo client = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
               input, mutable_client()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .fsm.CCKTypeDevice devlist = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          ::google::protobuf::uint32 length;
          DO_(input->ReadVarint32(&length));
          ::google::protobuf::io::CodedInputStream::Limit limit = input->PushLimit(static_cast<int>(length));
          while (input->BytesUntilLimit() > 0) {
            int value;
            DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
            add_devlist(static_cast< ::fsm::CCKTypeDevice >(value));
          }
          input->PopLimit(limit);
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          add_devlist(static_cast< ::fsm::CCKTypeDevice >(value));
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
  // @@protoc_insertion_point(parse_success:fsm.MN401)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:fsm.MN401)
  return false;
#undef DO_
}

void MN401::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:fsm.MN401)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .fsm.ServerInfo client = 1;
  if (this->has_client()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->_internal_client(), output);
  }

  // repeated .fsm.CCKTypeDevice devlist = 2;
  if (this->devlist_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(
      2,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      output);
    output->WriteVarint32(
        static_cast< ::google::protobuf::uint32>(_devlist_cached_byte_size_));
  }
  for (int i = 0, n = this->devlist_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteEnumNoTag(
      this->devlist(i), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:fsm.MN401)
}

::google::protobuf::uint8* MN401::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:fsm.MN401)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .fsm.ServerInfo client = 1;
  if (this->has_client()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        1, this->_internal_client(), deterministic, target);
  }

  // repeated .fsm.CCKTypeDevice devlist = 2;
  if (this->devlist_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      2,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(      static_cast< ::google::protobuf::uint32>(
            _devlist_cached_byte_size_), target);
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumNoTagToArray(
      this->devlist_, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:fsm.MN401)
  return target;
}

size_t MN401::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:fsm.MN401)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated .fsm.CCKTypeDevice devlist = 2;
  {
    size_t data_size = 0;
    unsigned int count = static_cast<unsigned int>(this->devlist_size());for (unsigned int i = 0; i < count; i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::EnumSize(
        this->devlist(static_cast<int>(i)));
    }
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
            static_cast< ::google::protobuf::int32>(data_size));
    }
    int cached_size = ::google::protobuf::internal::ToCachedSize(data_size);
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _devlist_cached_byte_size_ = cached_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  // .fsm.ServerInfo client = 1;
  if (this->has_client()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSize(
        *client_);
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void MN401::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:fsm.MN401)
  GOOGLE_DCHECK_NE(&from, this);
  const MN401* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const MN401>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:fsm.MN401)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:fsm.MN401)
    MergeFrom(*source);
  }
}

void MN401::MergeFrom(const MN401& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:fsm.MN401)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  devlist_.MergeFrom(from.devlist_);
  if (from.has_client()) {
    mutable_client()->::fsm::ServerInfo::MergeFrom(from.client());
  }
}

void MN401::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:fsm.MN401)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MN401::CopyFrom(const MN401& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:fsm.MN401)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MN401::IsInitialized() const {
  return true;
}

void MN401::Swap(MN401* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MN401::InternalSwap(MN401* other) {
  using std::swap;
  devlist_.InternalSwap(&other->devlist_);
  swap(client_, other->client_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata MN401::GetMetadata() const {
  protobuf_fsm_5fcckconfig_5fMN401_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_fsm_5fcckconfig_5fMN401_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace fsm
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::fsm::ServerInfo* Arena::CreateMaybeMessage< ::fsm::ServerInfo >(Arena* arena) {
  return Arena::CreateInternal< ::fsm::ServerInfo >(arena);
}
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::fsm::MN401* Arena::CreateMaybeMessage< ::fsm::MN401 >(Arena* arena) {
  return Arena::CreateInternal< ::fsm::MN401 >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
