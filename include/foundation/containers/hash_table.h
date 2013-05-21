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
#include <foundation/containers/array.h>

namespace foundation {
  template <typename T, typename _Value>
  class FOUNDATION_EXPORT HashTable {
    typedef Pair<T, _Value> Pair;

    public:
      explicit HashTable(
        Allocator& allocator,
        size_t size = 0
      ) : _ht(allocator, size)
      { _ht.resize(size); }

      HashTable(
        const HashTable<_Value, T>& hash_table
      ) : _ht(hash_table._ht)
      {}

      HashTable<_Value, T>& operator= (
        const HashTable<_Value, T>& hash_table )
      {
        _ht = hash_table._ht;
        return *this;
      }

    public:
      bool insert(
        const T hash,
        const _Value& value )
      {
        if ((load() >= 70) || (_ht.size() == 0))
          grow();
        return insert(_ht, hash, value);
      }

      bool find(
        const T hash,
        _Value& value ) const
      {
        return find(_ht, hash, value);
      }

      void remove(
        const T hash )
      {
        remove(_ht, hash);
      }

    private:
      bool insert(
        Array<Pair>& ht,
        const T hash,
        const _Value& value )
      {
        const size_t idx = hash % ht.size();
        for (size_t probe = 0; probe < ht.size(); ++probe) {
          const size_t idx_ = (idx + probe) % ht.size();
          if (ht[idx_].key == hash)
            return false;
          if (ht[idx_].key == ((T)0)) {
            ++_load;
            ht[idx_].key = hash;
            ht[idx_].value = value;
            return true; }}
        return false;
      }

      bool find(
        const Array<Pair>& ht,
        const T hash,
        _Value& value ) const
      {
        const size_t idx = probe(ht, hash);
        if (idx == ~((size_t)0))
          return false;
        value = ht[idx].value;
        return true;
      }

      void remove(
        Array<Pair>& ht,
        const T hash )
      {
        const size_t idx = probe(ht, hash);
        if (idx == ~((size_t)0))
          return;
        ht[idx].key = ((T)0);
        ht[idx].value.~_Value();
        --_load;
      }

    private:
      FOUNDATION_INLINE size_t load() const
      { return (_load / (min(_ht.size(), (size_t)1) * 100)); }

      size_t probe(
        const Array<Pair>& ht,
        const T hash ) const
      {
        const size_t idx = hash % ht.size();
        for (size_t probe = 0; probe < ht.size(); ++probe) {
          const size_t idx_ = (idx + probe) % ht.size();
          if (ht[idx_].key == hash)
            return idx_; }
        return ~((size_t)0);
      }

      void grow()
      {
        Array<Pair> ht(_ht.allocator(), min(_ht.size(), (size_t)1) * 2);
        ht.resize(ht.size());

        static const T empty;
        for (auto iter = _ht.begin(); iter != _ht.end(); ++iter) {
          if ((*iter).key != empty)
            insert(ht, (*iter).key, (*iter).value); }

        _ht = ht;
      }

    private:
      size_t _load;
      Array<Pair> _ht;
  };
} // foundation

#endif // _FOUNDATION_CONTAINERS_HASH_TABLE_H_
