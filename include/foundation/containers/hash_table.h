// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_CONTAINERS_HASH_TABLE_H_
#define _FOUNDATION_CONTAINERS_HASH_TABLE_H_

// Provides a generic flexibly sized hash table.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>
#include <foundation/pair.h>
#include <foundation/hash.h>
#include <foundation/digest.h>

namespace foundation {
  template <typename _Hash, typename _Value>
  class FOUNDATION_EXPORT HashTable {
    typedef Pair<_Hash, _Value> Pair;

    public:
      explicit HashTable(
        Allocator& allocator,
        size_t size = 0
      ) : _ht(allocator, size)
      { _ht.resize(size); }

      HashTable(
        const HashTable<_Value, _Hash>& hash_table
      ) : _ht(hash_table._ht)
      {}

      HashTable<_Value, _Hash>& operator= (
        const HashTable<_Value, _Hash>& hash_table )
      {
        _ht = hash_table._ht;
        return *this;
      }

    public:
      bool insert(
        const _Hash hash,
        const _Value& value )
      {
        if ((load() >= 70) || (_ht.size() == 0))
          grow();
        const size_t idx = hash % _ht.size();
        for (size_t probe = 0; probe < _ht.size(); ++probe) {
          const size_t idx_ = (idx + probe) % _ht.size();
          if (_ht[idx_].key == hash)
            return end();
          if (_ht[idx_].key == _Hash("")) {
            ++_load;
            _ht[idx_].key = key;
            _ht[idx_].value = value;
            return true; }}
        return false;
      }

      bool find(
        const _Hash hash,
        const _Value& value ) const
      {
        const size_t idx = probe(hash);
        if (idx == ~((size_t)0))
          return false;
        _ht[idx] = value;
        return true;
      }

      void remove(
        const _Hash hash )
      {
        const size_t idx = probe(hash);
        if (idx == ~((size_t)0))
          return;
        _ht[_idx].key = Hash("");
        _ht[_idx].value.~_Value();
        --_load;
      }

    private:
      FOUNDATION_INLINE size_t load() const
      { return ((_ht.size() * 100) / (_load ? _load : 1)); }

      size_t probe(
        const _Hash hash ) const
      {
        const size_t idx = hash % _ht.size();
        for (size_t probe = 0; probe < _ht.size(); ++probe) {
          const size_t idx_ = (idx + probe) % _ht.size();
          if (_ht[idx_].key == hash)
            return idx_; }
        return ~((size_t)0);
      }

    private:
      size_t _load;
      Array<Pair> _ht;
  };
} // foundation

#endif // _FOUNDATION_CONTAINERS_HASH_TABLE_H_
