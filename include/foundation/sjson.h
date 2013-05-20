// This file is part of Butane. See README.md and LICENSE.md for details.
// Copyright (c) 2012 Michael Williams <devbug@bitbyte.ca>

#ifndef _FOUNDATION_SJSON_H_
#define _FOUNDATION_SJSON_H_

// Provides utilities to parse and generate Simplified JSON.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/allocator.h>
#include <foundation/hash.h>
#include <foundation/digest.h>
#include <foundation/string.h>

#include <jsmn.h>

namespace foundation {
namespace sjson {
  typedef ImmutableHash<uint32_t, murmur_hash> Hash;

  class Value {
    protected:
      enum Type {
        T_NIL     = 0,
        T_BOOLEAN = 1,
        T_NUMBER  = 2,
        T_STRING  = 3,
        T_ARRAY   = 4,
        T_OBJECT  = 5
      };

    protected:
      Value(
        const Type type,
        const Hash key,
        const uint32_t len );

    public:
      FOUNDATION_INLINE bool is_nil() const
      { return (_type == T_NIL); }

      FOUNDATION_INLINE bool is_boolean() const
      { return (_type == T_BOOLEAN); }
      
      FOUNDATION_INLINE bool is_number() const
      { return (_type == T_NUMBER); }
      
      FOUNDATION_INLINE bool is_string() const
      { return (_type == T_STRING); }
      
      FOUNDATION_INLINE bool is_array() const
      { return (_type == T_ARRAY); }

      FOUNDATION_INLINE bool is_object() const
      { return (_type == T_OBJECT); }

    public: /* private */
      Type _type;
      Hash _key;
      uint32_t _len;
  };

  class Nil final
    : public Value
  {
    private:
      Nil(
        const Hash key );

    public: /* private */
      static uint32_t parse(
        const Hash key,
        void* blob,
        uint32_t blob_len,
        uint32_t blob_offset,
        const char* sjson,
        const jsmntok_t* token );
  };

  class Boolean final
    : public Value
  {
    private:
      Boolean(
        const Hash key,
        const bool value );

    public: /* private */
      static uint32_t parse(
        const Hash key,
        void* blob,
        uint32_t blob_len,
        uint32_t blob_offset,
        const char* sjson,
        const jsmntok_t* token );

    public:
      FOUNDATION_INLINE operator bool() const
      { return _value; }

    private:
      bool _value;
  };

  class Number final
    : public Value
  {
    private:
      Number(
        const Hash key,
        double value );

    public: /* private */
      static uint32_t parse(
        const Hash key,
        void* blob,
        uint32_t blob_len,
        uint32_t blob_offset,
        const char* sjson,
        const jsmntok_t* token );

    public:
      FOUNDATION_INLINE operator double() const
      { return _value; }

    private:
      double _value;
  };

  class String final
    : public Value
  {
    private:
      String(
        const Hash key,
        const char* value );

    public: /* private */
      static uint32_t parse(
        const Hash key,
        void* blob,
        uint32_t blob_len,
        uint32_t blob_offset,
        const char* sjson,
        const jsmntok_t* token );

    public:
      FOUNDATION_INLINE const char* raw() const
      { return &_raw[0]; }

    private:
      char _raw[1];
  };

  class Array final
    : public Value
  {
    private:
      Array(
        const Hash key,
        uint32_t num_values );

    public: /* private */
      static uint32_t parse(
        const Hash key,
        void* blob,
        uint32_t blob_len,
        uint32_t blob_offset,
        const char* sjson,
        const jsmntok_t* token );

    public:
      FOUNDATION_INLINE const Value* operator[] (
        const uint32_t idx )
      { return at(idx); }

    public:
      FOUNDATION_INLINE uint32_t size() const
      { return _num_values; }

      const Value* at(
        uint32_t idx ) const;

    private:
      uint32_t _num_values;
  };

  class Object final
    : public Value
  {
    private:
      Object(
        const Hash key );

    public: /* private */
      static uint32_t parse(
        const Hash key,
        void* blob,
        uint32_t blob_len,
        uint32_t blob_offset,
        const char* sjson,
        const jsmntok_t* token );

    public:
      const Value* find(
        const char* path ) const;
  };

  extern FOUNDATION_EXPORT Object* parse(
    Allocator& allocator,
    const char* sjson,
    void* blob,
    const uint32_t blob_len );
} // sjson
} // foundation

#endif // _FOUNDATION_SJSON_H_
