// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_message_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_message_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3013000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3013000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_message_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_message_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_message_2eproto;
class Message;
class MessageDefaultTypeInternal;
extern MessageDefaultTypeInternal _Message_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::Message* Arena::CreateMaybeMessage<::Message>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class Message PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Message) */ {
 public:
  inline Message() : Message(nullptr) {}
  virtual ~Message();

  Message(const Message& from);
  Message(Message&& from) noexcept
    : Message() {
    *this = ::std::move(from);
  }

  inline Message& operator=(const Message& from) {
    CopyFrom(from);
    return *this;
  }
  inline Message& operator=(Message&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Message& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Message* internal_default_instance() {
    return reinterpret_cast<const Message*>(
               &_Message_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Message& a, Message& b) {
    a.Swap(&b);
  }
  inline void Swap(Message* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Message* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Message* New() const final {
    return CreateMaybeMessage<Message>(nullptr);
  }

  Message* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Message>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Message& from);
  void MergeFrom(const Message& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Message* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Message";
  }
  protected:
  explicit Message(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_message_2eproto);
    return ::descriptor_table_message_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
    kStatusFieldNumber = 2,
    kRoleFieldNumber = 3,
    kPosxFieldNumber = 4,
    kPosyFieldNumber = 5,
    kPoszFieldNumber = 6,
    kFacexFieldNumber = 7,
    kFaceyFieldNumber = 8,
    kTimestampFieldNumber = 10,
    kFacezFieldNumber = 9,
  };
  // int32 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::int32 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 status = 2;
  void clear_status();
  ::PROTOBUF_NAMESPACE_ID::int32 status() const;
  void set_status(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_status() const;
  void _internal_set_status(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 role = 3;
  void clear_role();
  ::PROTOBUF_NAMESPACE_ID::int32 role() const;
  void set_role(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_role() const;
  void _internal_set_role(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // float posx = 4;
  void clear_posx();
  float posx() const;
  void set_posx(float value);
  private:
  float _internal_posx() const;
  void _internal_set_posx(float value);
  public:

  // float posy = 5;
  void clear_posy();
  float posy() const;
  void set_posy(float value);
  private:
  float _internal_posy() const;
  void _internal_set_posy(float value);
  public:

  // float posz = 6;
  void clear_posz();
  float posz() const;
  void set_posz(float value);
  private:
  float _internal_posz() const;
  void _internal_set_posz(float value);
  public:

  // float facex = 7;
  void clear_facex();
  float facex() const;
  void set_facex(float value);
  private:
  float _internal_facex() const;
  void _internal_set_facex(float value);
  public:

  // float facey = 8;
  void clear_facey();
  float facey() const;
  void set_facey(float value);
  private:
  float _internal_facey() const;
  void _internal_set_facey(float value);
  public:

  // int64 timestamp = 10;
  void clear_timestamp();
  ::PROTOBUF_NAMESPACE_ID::int64 timestamp() const;
  void set_timestamp(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_timestamp() const;
  void _internal_set_timestamp(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // float facez = 9;
  void clear_facez();
  float facez() const;
  void set_facez(float value);
  private:
  float _internal_facez() const;
  void _internal_set_facez(float value);
  public:

  // @@protoc_insertion_point(class_scope:Message)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::int32 id_;
  ::PROTOBUF_NAMESPACE_ID::int32 status_;
  ::PROTOBUF_NAMESPACE_ID::int32 role_;
  float posx_;
  float posy_;
  float posz_;
  float facex_;
  float facey_;
  ::PROTOBUF_NAMESPACE_ID::int64 timestamp_;
  float facez_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_message_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Message

// int32 id = 1;
inline void Message::clear_id() {
  id_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Message::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Message::id() const {
  // @@protoc_insertion_point(field_get:Message.id)
  return _internal_id();
}
inline void Message::_internal_set_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  id_ = value;
}
inline void Message::set_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:Message.id)
}

// int32 status = 2;
inline void Message::clear_status() {
  status_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Message::_internal_status() const {
  return status_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Message::status() const {
  // @@protoc_insertion_point(field_get:Message.status)
  return _internal_status();
}
inline void Message::_internal_set_status(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  status_ = value;
}
inline void Message::set_status(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_status(value);
  // @@protoc_insertion_point(field_set:Message.status)
}

// int32 role = 3;
inline void Message::clear_role() {
  role_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Message::_internal_role() const {
  return role_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Message::role() const {
  // @@protoc_insertion_point(field_get:Message.role)
  return _internal_role();
}
inline void Message::_internal_set_role(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  role_ = value;
}
inline void Message::set_role(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_role(value);
  // @@protoc_insertion_point(field_set:Message.role)
}

// float posx = 4;
inline void Message::clear_posx() {
  posx_ = 0;
}
inline float Message::_internal_posx() const {
  return posx_;
}
inline float Message::posx() const {
  // @@protoc_insertion_point(field_get:Message.posx)
  return _internal_posx();
}
inline void Message::_internal_set_posx(float value) {
  
  posx_ = value;
}
inline void Message::set_posx(float value) {
  _internal_set_posx(value);
  // @@protoc_insertion_point(field_set:Message.posx)
}

// float posy = 5;
inline void Message::clear_posy() {
  posy_ = 0;
}
inline float Message::_internal_posy() const {
  return posy_;
}
inline float Message::posy() const {
  // @@protoc_insertion_point(field_get:Message.posy)
  return _internal_posy();
}
inline void Message::_internal_set_posy(float value) {
  
  posy_ = value;
}
inline void Message::set_posy(float value) {
  _internal_set_posy(value);
  // @@protoc_insertion_point(field_set:Message.posy)
}

// float posz = 6;
inline void Message::clear_posz() {
  posz_ = 0;
}
inline float Message::_internal_posz() const {
  return posz_;
}
inline float Message::posz() const {
  // @@protoc_insertion_point(field_get:Message.posz)
  return _internal_posz();
}
inline void Message::_internal_set_posz(float value) {
  
  posz_ = value;
}
inline void Message::set_posz(float value) {
  _internal_set_posz(value);
  // @@protoc_insertion_point(field_set:Message.posz)
}

// float facex = 7;
inline void Message::clear_facex() {
  facex_ = 0;
}
inline float Message::_internal_facex() const {
  return facex_;
}
inline float Message::facex() const {
  // @@protoc_insertion_point(field_get:Message.facex)
  return _internal_facex();
}
inline void Message::_internal_set_facex(float value) {
  
  facex_ = value;
}
inline void Message::set_facex(float value) {
  _internal_set_facex(value);
  // @@protoc_insertion_point(field_set:Message.facex)
}

// float facey = 8;
inline void Message::clear_facey() {
  facey_ = 0;
}
inline float Message::_internal_facey() const {
  return facey_;
}
inline float Message::facey() const {
  // @@protoc_insertion_point(field_get:Message.facey)
  return _internal_facey();
}
inline void Message::_internal_set_facey(float value) {
  
  facey_ = value;
}
inline void Message::set_facey(float value) {
  _internal_set_facey(value);
  // @@protoc_insertion_point(field_set:Message.facey)
}

// float facez = 9;
inline void Message::clear_facez() {
  facez_ = 0;
}
inline float Message::_internal_facez() const {
  return facez_;
}
inline float Message::facez() const {
  // @@protoc_insertion_point(field_get:Message.facez)
  return _internal_facez();
}
inline void Message::_internal_set_facez(float value) {
  
  facez_ = value;
}
inline void Message::set_facez(float value) {
  _internal_set_facez(value);
  // @@protoc_insertion_point(field_set:Message.facez)
}

// int64 timestamp = 10;
inline void Message::clear_timestamp() {
  timestamp_ = PROTOBUF_LONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Message::_internal_timestamp() const {
  return timestamp_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Message::timestamp() const {
  // @@protoc_insertion_point(field_get:Message.timestamp)
  return _internal_timestamp();
}
inline void Message::_internal_set_timestamp(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  timestamp_ = value;
}
inline void Message::set_timestamp(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_timestamp(value);
  // @@protoc_insertion_point(field_set:Message.timestamp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_message_2eproto
