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
#include <foundation/containers/array.h>

#include <jsmn.h>

namespace foundation {
namespace sjson {
  typedef ImmutableHash<uint32_t, murmur_hash> Hash;

  class Value;
  class Nil;
  class Boolean;
  class Number;
  class String;
  class Array;
  class Object;

  class Parser {
    __foundation_trait(Parser, non_copyable);

    private:
      friend class Value;
      friend class Nil;
      friend class Boolean;
      friend class Number;
      friend class String;
      friend class Array;
      friend class Object;

    private:
      struct State {
        int token;
        uint32_t blob_offset;
      };

    public:
      Parser(
        Allocator& allocator,
        void* blob,
        uint32_t blob_len );

      ~Parser();

    public:
      bool parse(
        const char* sjson );

    private:
      foundation::Array<jsmntok_t> _tokens;
      void* const _blob;
      uint32_t _blob_len;
      const char* _sjson;
  };

  class Value {
    __foundation_trait(Value, non_copyable);

    protected:
      friend class Parser;
      friend class Nil;
      friend class Boolean;
      friend class Number;
      friend class String;
      friend class Array;
      friend class Object;

    protected:
      static const Hash Unnamed;

    protected:
      enum Type {
        T_NIL          = 0,
        T_BOOLEAN      = 1,
        T_NUMBER       = 2,
        T_STRING       = 3,
        T_ARRAY        = 4,
        T_OBJECT       = 5,
        T_FORCE_UINT32 = 0xFFFFFFFFu
      };

    protected:
      Value(
        const Type type,
        uint32_t len
      ) : _type(type)
        , _key(Value::Unnamed)
        , _len(len)
      {}

      ~Value()
      {}

    protected:
      static Value* parse(
        Value* const parent,
        const Parser& parser,
        Parser::State& state );

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

    protected:
      const Type _type;
      Hash _key;
      uint32_t _len;
  };

  class Nil final
    : public Value
  {
    __foundation_trait(Nil, non_copyable);

    private:
      friend class Value;

    private:
      Nil()
        : Value(Value::T_NIL, sizeof(Nil))
      {}

    private:
      static Value* parse(
        Value* const parent,
        const Parser& parser,
        Parser::State& state );
  };

  class Boolean final
    : public Value
  {
    __foundation_trait(Boolean, non_copyable);

    private:
      friend class Value;

    private:
      Boolean()
        : Value(Value::T_BOOLEAN, sizeof(Boolean))
      {}

    private:
      static bool Boolean::_from_initial_character(
        const char ch );

      static Value* parse(
        Value* const parent,
        const Parser& parser,
        Parser::State& state );

    public:
      FOUNDATION_INLINE bool value() const
      { return _value; }

    private:
      bool _value;
  };

  class Number final
    : public Value
  {
    __foundation_trait(Number, non_copyable);

    private:
      friend class Value;

    private:
      Number()
        : Value(Value::T_NUMBER, sizeof(Number))
      {}

    private:
      static Value* parse(
        Value* const parent,
        const Parser& parser,
        Parser::State& state );

    public:
      FOUNDATION_INLINE double value() const
      { return _value; }

    private:
      double _value;
  };

  class String final
    : public Value
  {
    __foundation_trait(String, non_copyable);

    private:
      friend class Value;

    private:
      String()
        : Value(Value::T_STRING, sizeof(String))
      {}

    private:
      static Value* parse(
        Value* const parent,
        const Parser& parser,
        Parser::State& state );

    public:
      FOUNDATION_INLINE const char* raw() const
      { return &_raw[0]; }

    private:
      char _raw[1];
  };

  class Array final
    : public Value
  {
    __foundation_trait(Array, non_copyable);

    private:
      friend class Value;

    private:
      Array()
        : Value(Value::T_ARRAY, sizeof(Array))
      {}

    private:
      static Value* parse(
        Value* const parent,
        const Parser& parser,
        Parser::State& state );

    public:
      const Value* at(
        uint32_t index ) const;

    public:
      FOUNDATION_INLINE uint32_t size() const
      { return _size; }

    private:
      uint32_t _size;
  };

  class Object final
    : public Value
  {
    __foundation_trait(Object, non_copyable);

    private:
      friend class Value;

    private:
      Object()
        : Value(Value::T_OBJECT, sizeof(Object))
      {}

    private:
      static Value* parse(
        Value* const parent,
        const Parser& parser,
        Parser::State& state );

    public:
      const Value* find(
        const char* const path ) const;
  };
} // sjson
} // foundation

#endif // _FOUNDATION_SJSON_H_
