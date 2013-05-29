// This file is part of Butane. See README.md and LICENSE.md for details.
// Copyright (c) 2012 Michael Williams <devbug@bitbyte.ca>

#include <foundation/sjson.h>

namespace foundation {
namespace sjson {
  const Hash Value::Unnamed("");

  Value* Value::parse(
    Value* const parent,
    const Parser& parser,
    Parser::State& state )
  {
    Value* value;
    switch (parser._tokens[state.token].type) {
      case JSMN_PRIMITIVE:
        switch (parser._sjson[parser._tokens[state.token].start]) {
          case 'n': case 'N':
            if (!(value = Nil::parse(parent, parser, state)))
              return nullptr;
            break;

          case 't': case 'f': case 'T': case 'F':
            if (!(value = Boolean::parse(parent, parser, state)))
              return nullptr;
            break;

          case '-': case '.':
          case '0': case '1': case '2': case '4': case '5':
          case '6': case '7': case '8': case '9':
            if (!(value = Number::parse(parent, parser, state)))
              return nullptr;
            break;

          default:
            return nullptr; }
        break;

      case JSMN_OBJECT:
        if (!(value = Object::parse(parent, parser, state)))
          return nullptr;
        break;

      case JSMN_ARRAY:
        if (!(value = Array::parse(parent, parser, state)))
          return nullptr;
        break;

      case JSMN_STRING:
        if (!(value = String::parse(parent, parser, state)))
          return nullptr;
        break;

      default:
        return nullptr;
    }

    if (parent)
      parent->_len += value->_len;
    return value;
  }

  Value* Nil::parse(
    Value* const parent,
    const Parser& parser,
    Parser::State& state )
  {
    const jsmntok_t& token = parser._tokens[state.token++];

    if ((state.blob_offset + sizeof(Nil)) > parser._blob_len)
      return false;

    Nil* nil =
      new ((void*)((uintptr_t)parser._blob + state.blob_offset)) Nil();
    state.blob_offset += sizeof(Nil);

    return nil;
  }

  bool Boolean::_from_initial_character(
    const char ch )
  {
    switch (ch) {
      case 't': case 'T':
        return true; }
    return false;
  }

  Value* Boolean::parse(
    Value* const parent,
    const Parser& parser,
    Parser::State& state )
  {
    const jsmntok_t& token = parser._tokens[state.token++];

    if ((state.blob_offset + sizeof(Boolean)) > parser._blob_len)
      return false;

    Boolean* boolean =
      new ((void*)((uintptr_t)parser._blob + state.blob_offset)) Boolean();
    boolean->_value = _from_initial_character(parser._sjson[token.start]);
    state.blob_offset += sizeof(Boolean);

    return boolean;
  }

  Value* Number::parse(
    Value* const parent,
    const Parser& parser,
    Parser::State& state )
  {
    const jsmntok_t& token = parser._tokens[state.token++];
    const uint32_t len = token.end - token.start;

    if ((state.blob_offset + sizeof(Number)) > parser._blob_len)
      return false;

    char* str = (char*)alloca(len + 1);
    copy((void*)&str[0], (const void*)&parser._sjson[token.start], len);
    str[len] = '\0';

    Number* num =
      new ((void*)((uintptr_t)parser._blob + state.blob_offset)) Number();
    num->_value = strtod(&str[0], nullptr);
    state.blob_offset += sizeof(Number);

    return num;
  }

  Value* String::parse(
    Value* const parent,
    const Parser& parser,
    Parser::State& state )
  {
    const jsmntok_t& token = parser._tokens[state.token++];
    const uint32_t len = token.end - token.start;

    if ((state.blob_offset + sizeof(String) + len) > parser._blob_len)
      return false;

    String* str =
      new ((void*)((uintptr_t)parser._blob + state.blob_offset)) String();
    str->_len += len;
    copy((void*)&str->_raw[0], (const void*)&parser._sjson[token.start], len);
    str->_raw[len] = '\0';
    state.blob_offset += sizeof(String) + len;

    return str;
  }

  Value* Array::parse(
    Value* const parent,
    const Parser& parser,
    Parser::State& state )
  {
    const jsmntok_t& root = parser._tokens[state.token++];

    if ((state.blob_offset + sizeof(Array)) > parser._blob_len)
      return false;

    Array* array =
      new ((void*)((uintptr_t)parser._blob + state.blob_offset)) Array();
    array->_size = root.size;
    state.blob_offset += sizeof(Array);

    for (int element = 0; element < root.size; ++element) {
      if (!Value::parse(array, parser, state))
        return false; }

    return array;
  }

  const Value* Array::at(
    uint32_t index ) const
  {
    if (index >= _size)
      return nullptr;

    uintptr_t iter = ((uintptr_t)this) + sizeof(Array);
    const uintptr_t end = ((uintptr_t)this) + _len;

    for (; index > 0; --index) {
      if ((iter + sizeof(Value*)) >= end)
        return nullptr;
      iter += ((Value*)iter)->_len;
    }

    return ((Value*)iter);
  }

  Value* Object::parse(
    Value* const parent,
    const Parser& parser,
    Parser::State& state )
  {
    const jsmntok_t& root = parser._tokens[state.token++];

    if ((state.blob_offset + sizeof(Object)) > parser._blob_len)
      return false;

    Object* obj =
      new ((void*)((uintptr_t)parser._blob + state.blob_offset)) Object();
    state.blob_offset += obj->_len;

    for (int child = 0; child < root.size; child += 2) {
      const jsmntok_t& key = parser._tokens[state.token++];
      if (key.type != JSMN_PRIMITIVE)
        return false;
      Value* value = Value::parse(obj, parser, state);
      if (!value)
        return false;
      value->_key = Hash((const void*)&parser._sjson[key.start], key.end - key.start);
    }

    return obj;
  }

  const Value* Object::find(
    const char* const path ) const
  {
    if (!path)
      return nullptr;

    const Value* value = this;
    const char* iter = path;
    const char* const end = path + strlen(path);

    while (iter) {
      const char* seperator = foundation::find(iter, ".");
      seperator = seperator ? seperator : end;

      if (!value->is_object())
        return nullptr;

      const Hash key((const void*)iter, seperator - iter);
      uintptr_t iter_ = ((uintptr_t)value + sizeof(Object));
      const uintptr_t end_ = ((uintptr_t)value + value->_len);
      while (iter_ < end_) {
        if (((Value*)iter_)->_key != key) {
          iter_ += ((Value*)iter_)->_len;
          continue; }
        value = ((Value*)iter_);
        if (!*seperator)
          return value;
        break;
      }

      iter = next(seperator);
    }

    return nullptr;
  }
} // sjson
} // foundation

namespace foundation {
namespace sjson {
  Parser::Parser(
    Allocator& allocator,
    void* blob,
    uint32_t blob_len
  ) : _tokens(allocator, (size_t)0)
    , _blob(blob)
    , _blob_len(blob_len)
    , _sjson(nullptr)
  {
    assert(blob != nullptr);
    assert(blob_len > 0);
  }

  Parser::~Parser()
  {
  }

  bool Parser::parse(
    const char* sjson,
    size_t sjson_len )
  {
    _sjson = sjson;

    if (!_sjson) {
      if (sizeof(Object) > _blob_len)
        return false;
      new (_blob) Object();
      return true; }

    _tokens.resize(1);
    while (_tokens.size() < 0xFFFFFFFFu) {
      jsmn_parser jp;
      jsmn_init(&jp);

      State state;
      state.token = 0;
      state.blob_offset = 0;

      switch (jsmn_parse(&jp, sjson, sjson_len, &_tokens[0], _tokens.size())) {
        case JSMN_ERROR_NOMEM:
          _tokens.resize(_tokens.size() * 2);
          break;

        case JSMN_SUCCESS:
          if (Value::parse(nullptr, *this, state)) {
            _tokens.resize(0);
            return true; }

        default:
          goto unsuccessful;
      }
    }

  unsuccessful:
    _tokens.resize(0);
    return false;
  }
} // sjson
} // foundation
