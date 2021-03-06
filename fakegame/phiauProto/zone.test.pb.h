// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: zone.test.proto

#ifndef PROTOBUF_zone_2etest_2eproto__INCLUDED
#define PROTOBUF_zone_2etest_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3001000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace zone {
namespace test {
class Request;
class RequestDefaultTypeInternal;
extern RequestDefaultTypeInternal _Request_default_instance_;
}  // namespace test
}  // namespace zone

namespace zone {
namespace test {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_zone_2etest_2eproto();
void protobuf_InitDefaults_zone_2etest_2eproto();

// ===================================================================

class Request : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:zone.test.Request) */ {
 public:
  Request();
  virtual ~Request();

  Request(const Request& from);

  inline Request& operator=(const Request& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Request& default_instance();

  static inline const Request* internal_default_instance() {
    return reinterpret_cast<const Request*>(
               &_Request_default_instance_);
  }

  void Swap(Request* other);

  // implements Message ----------------------------------------------

  inline Request* New() const PROTOBUF_FINAL { return New(NULL); }

  Request* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Request& from);
  void MergeFrom(const Request& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Request* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 code = 1;
  void clear_code();
  static const int kCodeFieldNumber = 1;
  ::google::protobuf::int32 code() const;
  void set_code(::google::protobuf::int32 value);

  // int32 count = 2;
  void clear_count();
  static const int kCountFieldNumber = 2;
  ::google::protobuf::int32 count() const;
  void set_count(::google::protobuf::int32 value);

  // int64 time = 3;
  void clear_time();
  static const int kTimeFieldNumber = 3;
  ::google::protobuf::int64 time() const;
  void set_time(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:zone.test.Request)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 code_;
  ::google::protobuf::int32 count_;
  ::google::protobuf::int64 time_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_zone_2etest_2eproto_impl();
  friend void  protobuf_AddDesc_zone_2etest_2eproto_impl();
  friend const ::google::protobuf::uint32* protobuf_Offsets_zone_2etest_2eproto();
  friend void protobuf_ShutdownFile_zone_2etest_2eproto();

};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Request

// int32 code = 1;
inline void Request::clear_code() {
  code_ = 0;
}
inline ::google::protobuf::int32 Request::code() const {
  // @@protoc_insertion_point(field_get:zone.test.Request.code)
  return code_;
}
inline void Request::set_code(::google::protobuf::int32 value) {
  
  code_ = value;
  // @@protoc_insertion_point(field_set:zone.test.Request.code)
}

// int32 count = 2;
inline void Request::clear_count() {
  count_ = 0;
}
inline ::google::protobuf::int32 Request::count() const {
  // @@protoc_insertion_point(field_get:zone.test.Request.count)
  return count_;
}
inline void Request::set_count(::google::protobuf::int32 value) {
  
  count_ = value;
  // @@protoc_insertion_point(field_set:zone.test.Request.count)
}

// int64 time = 3;
inline void Request::clear_time() {
  time_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 Request::time() const {
  // @@protoc_insertion_point(field_get:zone.test.Request.time)
  return time_;
}
inline void Request::set_time(::google::protobuf::int64 value) {
  
  time_ = value;
  // @@protoc_insertion_point(field_set:zone.test.Request.time)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace test
}  // namespace zone

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_zone_2etest_2eproto__INCLUDED
