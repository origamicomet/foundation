// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_DICTIONARY_H_
#define _FOUNDATION_DICTIONARY_H_

// A O(log n) structure for key to value mappings.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>
#include <foundation/allocator.h>
#include <foundation/pair.h>
#include <foundation/array.h>

namespace foundation {
  template <typename _Key, typename _Value>
  class FOUNDATION_EXPORT Dictionary {
    friend class Iterator;

    public:
      typedef Pair<_Key, _Value> Entry;

    public:
      class Iterator {
        friend class Dictionary<_Key, _Value>;

        private:
          Iterator( const Dictionary<_Key, _Value>& dict, size_t index )
            : _dict(const_cast<Dictionary<_Key, _Value>&>(dict)), _index(index)
          {}

          Iterator( Dictionary<_Key, _Value>& dict, size_t index )
            : _dict(dict), _index(index)
          {}

        public:
          Iterator( const Iterator& iter )
            : _dict(iter._dict), _index(iter._index)
          {}

        public:
          FOUNDATION_INLINE bool operator== ( const Iterator& iter )
          { return ((_dict == iter._dict) && (_index == iter._index)); }

          FOUNDATION_INLINE bool operator!= ( const Iterator& iter )
          { return ((_dict != iter._dict) || (_index != iter._index)); }

          FOUNDATION_INLINE Iterator operator++ ()
          { return Iterator(_dict, min(_index + 1, _dict._entries.size() - 1)); }

          FOUNDATION_INLINE Iterator operator++ ( int )
          { Iterator iter(*this); ++(*this); return iter; }

          FOUNDATION_INLINE Iterator operator-- ()
          { return Iterator(_dict, max(1, _index) - 1); }

          FOUNDATION_INLINE Iterator operator-- ( int )
          { Iterator iter(*this); --(*this); return iter; }

        public:
          FOUNDATION_INLINE Entry& to_ref()
          { return _dict._entries[_index]; }

          FOUNDATION_INLINE const Entry& to_ref() const
          { return _dict._entries[_index]; }
        
          FOUNDATION_INLINE bool is_valid() const
          { return ((_index > 0) && (_index <= _dict._entries.size())); }

        private:
          Dictionary<_Key, _Value>& _dict;
          size_t _index;
      };

    public:
      Dictionary( Allocator& allocator = Allocator::heap() )
        : _entries(allocator)
      {
      }

      Dictionary( const Dictionary<_Key, _Value>& dict )
        : _entries(dict._entries)
      {
      }

      Dictionary<_Key, _Value>& operator= ( const Dictionary<_Key, _Value>& dict )
      {
        if (&dict == this)
          return *this;
        _entries = dict._entries;
      }

      ~Dictionary()
      {
      }

    public:
      Iterator find( const _Key& key ) const
      {
        Entry* entry = search(key, _entries.to_ptr(), _entries.size());

        if (!entry)
          return end();

        const size_t index =
          (((uintptr_t)entry) - ((uintptr_t)_entries.to_ptr())) / sizeof(Entry);

        return Iterator(*this, index);
      }

      void insert( const _Key& key, const _Value& value )
      {
        assert(!find(key).is_valid());
        _entries.push_back(Entry(key, value));
        sort(_entries.to_ptr(), _entries.size());
      }

      void remove( const Iterator& iter )
      {
        assert(iter.is_valid());

        copy_safe(
          (void*)_entries[iter._index],
          (const void*)&_entries[_entries.size() - 1],
          sizeof(Entry)
        );

        _entries.pop_back();
        sort(_entries.to_ptr(), _entries.size());
      }

    public:
      FOUNDATION_INLINE Iterator begin() const
      { return Iterator(*this, (size_t)0); }

      FOUNDATION_INLINE Iterator end() const
      { return Iterator(*this, max(_entries.size() + 1, (size_t)1) - 1); }

    public:
      FOUNDATION_INLINE Allocator& allocator() const
      { return _entries.allocator(); }

    private:
      Array<Entry> _entries;
  };
} // foundation

#endif // _FOUNDATION_DICTIONARY_H_