// This file is part of Butane. See README.md and LICENSE.md for details.
// Copyright (c) 2012 Michael Williams <devbug@bitbyte.ca>

#include <foundation/sjson.h>

namespace foundation {
namespace sjson {
  Value::Value(
    const Type type,
    const Hash key,
    const uint32_t len
  ) : _type(type)
    , _key(key)
    , _len(len)
  {}

  Nil::Nil(
    const Hash key
  ) : Value(Value::T_NIL, key, sizeof(Nil))
  {}

  uint32_t Nil::parse(
    const Hash key,
    void* blob,
    uint32_t blob_len,
    uint32_t blob_offset,
    const char* sjson,
    const jsmntok_t* token )
  {
    (void)sjson;
    (void)token;

    if ((blob_offset + sizeof(Nil)) > blob_len)
      return 0;

    return (new ((void*)((uintptr_t)blob + blob_offset)) Nil(key))->_len;
  }

  Boolean::Boolean(
    const Hash key,
    const bool value
  ) : Value(Value::T_BOOLEAN, key, sizeof(Boolean))
    , _value(value)
  {}

  uint32_t Boolean::parse(
    const Hash key,
    void* blob,
    uint32_t blob_len,
    uint32_t blob_offset,
    const char* sjson,
    const jsmntok_t* token )
  {
    if ((blob_offset + sizeof(Boolean)) > blob_len)
      return 0;

    switch (sjson[token->start]) {
      case 't': case 'T':
        return (new ((void*)((uintptr_t)blob + blob_offset)) Boolean(key, true))->_len;
      case 'f': case 'F':
        return (new ((void*)((uintptr_t)blob + blob_offset)) Boolean(key, true))->_len;
    }

    return 0;
  }

  Number::Number(
    const Hash key,
    double value
  ) : Value(Value::T_NUMBER, key, sizeof(Number))
    , _value(value)
  {}

  uint32_t Number::parse(
    const Hash key,
    void* blob,
    uint32_t blob_len,
    uint32_t blob_offset,
    const char* sjson,
    const jsmntok_t* token )
  {
    if ((blob_offset + sizeof(Number)) > blob_len)
      return 0;

    const size_t len = token->end - token->start;
    char* buf = (char*)alloca(len + 1);
    copy((void*)&buf[0], (const void*)&sjson[token->start], len);
    buf[len - 1] = '\0';
    return (new ((void*)((uintptr_t)blob + blob_offset)) Number(key, strtod(&buf[0], nullptr)))->_len;
  }

  String::String(
    const Hash key,
    const char* value
  ) : Value(Value::T_STRING, key, sizeof(String) - 1 + (value ? strlen(value) : 0))
  {
    copy((void*)&_raw[0], (const void*)value, value ? strlen(value) : 0);
  }

  uint32_t String::parse(
    const Hash key,
    void* blob,
    uint32_t blob_len,
    uint32_t blob_offset,
    const char* sjson,
    const jsmntok_t* token )
  {
    const uint32_t len = token->end - token->start + 1;
    if ((blob_offset + (sizeof(String) - 1 + len)) > blob_len)
      return 0;

    String* str = new ((void*)((uintptr_t)blob + blob_offset)) String(key, nullptr);
    str->_len += len;
    copy((void*)&str->_raw[0], (const void*)&sjson[token->start], len - 1);
    str->_raw[len - 1] = '\0';
    return str->_len;
  }

  namespace Token {
    static uint32_t parse(
      const Hash key,
      void* blob,
      uint32_t blob_len,
      uint32_t blob_offset,
      const char* sjson,
      const jsmntok_t* token,
      const jsmntok_t* value )
    {
      switch (value->type) {
        case JSMN_OBJECT: {
          return Object::parse(
            key, blob, blob_len, blob_offset, sjson, value);
        } break;

        case JSMN_ARRAY: {
          return Array::parse(
            key, blob, blob_len, blob_offset, sjson, value);
        } break;

        case JSMN_STRING: {
          return String::parse(
            key, blob, blob_len, blob_offset, sjson, value);
        } break;

        case JSMN_PRIMITIVE: {
          switch (sjson[token->start]) {
            case 'n': case 'N': {
              return Nil::parse(
                key, blob, blob_len, blob_offset, sjson, value);
            } break;

            case 't': case 'T': case 'f': case 'F': {
              return Boolean::parse(
                key, blob, blob_len, blob_offset, sjson, value);
            } break;

            case '-': case '.':
            case '0': case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9': {
              return Number::parse(
                key, blob, blob_len, blob_offset, sjson, value);
            } break;
          }
        } break;
      }

      return 0;
    }
  } // Token

  Array::Array(
    const Hash key,
    uint32_t num_values
  ) : Value(Value::T_ARRAY, key, sizeof(Array))
    , _num_values(num_values)
  {}

  uint32_t Array::parse(
    const Hash key,
    void* blob,
    uint32_t blob_len,
    uint32_t blob_offset,
    const char* sjson,
    const jsmntok_t* token )
  {
    if ((blob_offset + sizeof(Array)) > blob_len)
      return 0;

    Array* array = new ((void*)((uintptr_t)blob + blob_offset)) Array(key, token->size);

    for (int t = 0; t < token->size; ++t) {
      const uint32_t len = (Token::parse(
        "", blob, blob_len, blob_offset + array->_len, sjson, token, &token[t + 1]) > 0);
      if (len == 0)
        return 0;
      array->_len += len;
    }

    return array->_len;
  }

  const Value* Array::at(
    uint32_t idx ) const
  {
    if (idx >= _num_values)
      return nullptr;

    uintptr_t iter = ((uintptr_t)this) + sizeof(Array);
    const uintptr_t end = iter + _len;

    while (iter < end) {
      if (--idx != 0) {
        iter += ((Value*)iter)->_len;
        continue; }
      return ((Value*)iter); }

    return nullptr;
  }

  Object::Object(
    const Hash key
  ) : Value(Value::T_OBJECT, key, sizeof(Object))
  {}

  const Value* Object::find(
    const char* path ) const
  {
    Value* value = (Value*)this;
    const char* iter = path;

    while (iter) {
      const char* seperator = prev(foundation::find(iter, "."));
      seperator = seperator ? seperator : (path + strlen(path));
      
      if (!value->is_object())
        return nullptr;
      
      const Hash key((const void*)iter, seperator - iter);
      uintptr_t iter_ = ((uintptr_t)value + sizeof(Object));
      const uintptr_t end = iter_ + value->_len;
      while (iter_ < end) {
        if (((Value*)iter_)->_key != key) {
          iter_ += ((Value*)iter_)->_len;
          continue; }
        value = ((Value*)iter_);
        if (!*seperator)
          return value;
        break; }

      iter = next(next(seperator));
    }

    return nullptr;
  }

  uint32_t Object::parse(
    const Hash key,
    void* blob,
    uint32_t blob_len,
    uint32_t blob_offset,
    const char* sjson,
    const jsmntok_t* token )
  {
    if ((blob_offset + sizeof(Object)) > blob_len)
      return 0;

    Object* obj = new ((void*)((uintptr_t)blob + blob_offset)) Object(key);

    for (int t = 0; t < (token->size - 1); t += 2) {
      const jsmntok_t* key = &token[t + 1];
      const jsmntok_t* value = &token[t + 2];

      if (key->type != JSMN_PRIMITIVE)
        return 0;

      const uint32_t len = Token::parse(
        Hash((void*)&sjson[key->start], key->end - key->start),
        blob, blob_len, blob_offset + obj->_len, sjson, token, value);
      
      if (len == 0)
        return 0;

      obj->_len += len;
    }

    return obj->_len;
  }

  Object* parse(
    Allocator& allocator,
    const char* sjson,
    void* blob,
    const uint32_t blob_len )
  {
    if ((sjson == nullptr) || (blob == nullptr) || (blob_len == 0))
      return nullptr;

    size_t num_tokens = 1;
    jsmntok_t* tokens = nullptr;

    while (true) {
      jsmn_parser jp;
      jsmn_init(&jp);

      tokens = (jsmntok_t*)allocator.realloc(
        (void*)tokens, num_tokens * sizeof(jsmntok_t),
        alignment_of<jsmntok_t>::value);

      switch (jsmn_parse(&jp, sjson, tokens, num_tokens)) {
        case JSMN_SUCCESS: {
          const bool succesful = (Object::parse("", blob, blob_len, 0, sjson, &tokens[0]) > 0);
          allocator.free((void*)tokens);
          return succesful ? (Object*)blob : nullptr;
        } break;

        case JSMN_ERROR_NOMEM: {
          num_tokens *= 2;
        } break;

        default: {
          allocator.free((void*)tokens);
          return nullptr;
        } break;
      }
    }

    __builtin_unreachable();
    return nullptr;
  }
} // sjson
} // foundation
