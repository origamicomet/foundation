// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ARRAY_H_
#define _FOUNDATION_ARRAY_H_

// A resizable array.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/assert.h>
#include <foundation/algorithm.h>
#include <foundation/allocator.h>

namespace foundation {
  template <typename T>
  class FOUNDATION_EXPORT Array {
    public:
      class Iterator {
        friend class Array<T>;

        private:
          Iterator( const Array<T>& array, size_t index )
            : _array(const_cast<Array<T>&>(array))
            , _index(index + 1)
          {}

          Iterator( Array<T>& array, size_t index )
            : _array(array)
            , _index(index + 1)
          {}

        public:
          Iterator( const Iterator& iter )
            : _array(iter._array)
            , _index(iter._index)
          {}

          Iterator& operator= ( const Iterator& iter )
          {
            _array = iter._array;
            _index = iter._index;

            return *this;
          }

        public:
          FOUNDATION_INLINE bool operator== ( const Iterator& iter )
          { return ((_array == iter._array) && (_index == iter._index)); }

          FOUNDATION_INLINE bool operator!= ( const Iterator& iter )
          { return ((_array != iter._array) || (_index != iter._index)); }

          FOUNDATION_INLINE Iterator operator++ ()
          { return Iterator(_array, max(_index + 1, _array.size())); }

          FOUNDATION_INLINE Iterator operator++ ( int )
          { Iterator iter(*this); ++(*this); return iter; }

          FOUNDATION_INLINE Iterator operator-- ()
          { return Iterator(_array, max(1, _index) - 1); }

          FOUNDATION_INLINE Iterator operator-- ( int )
          { Iterator iter(*this); --(*this); return iter; }

        public:
          FOUNDATION_INLINE T& to_ref()
          { return _array.to_ptr()[_index - 1]; }

          FOUNDATION_INLINE const T& to_ref() const
          { return _array.to_ptr()[_index - 1]; }
        
          FOUNDATION_INLINE bool is_valid() const
          { return ((_index > 0) && (_index <= _array.size())); }

        private:
          Array& _array;
          size_t _index;
      };

    public:
      explicit Array( Allocator& allocator, size_t reserve = 0 )
        : _allocator(allocator)
        , _size(0)
        , _reserved(reserve)
        , _ptr((T*)allocator.alloc(reserve * sizeof(T), alignof(T)))
      {}

      ~Array()
      {
        _allocator.free((void*)_ptr);
        _ptr = nullptr;
      }

    public:
      Array( const Array& array )
        : _allocator(array._allocator)
        , _size(array._size)
        , _reserved(array._reserved)
        , _ptr((T*)array._allocator.alloc(array._reserved * sizeof(T), alignof(T)))
      {
        copy((void*)_ptr, (const void*)array._ptr, array._reserved * sizeof(T));
      }

      Array& operator= ( const Array& array )
      {
        if (this == &array)
          return *this;

        _size = array._size;
        _reserved = array._reserved;
        _ptr = (T*)_allocator.realloc((void*)_ptr, array._reserved * sizeof(T), alignof(T));
        copy((void*)_ptr, (const void*)array._ptr, array._reserved * sizeof(T));

        return *this;
      }

    public:
      FOUNDATION_INLINE bool operator== ( const Array<T>& array )
      { return (this == &array); }

      FOUNDATION_INLINE bool operator!= ( const Array<T>& array )
      { return (this != &array); }

      FOUNDATION_INLINE void operator+= ( const T& item )
      { push_back(item); }

      FOUNDATION_INLINE T& operator[] ( size_t index )
      {
        assert(index < array._size());
        return _ptr[index];
      }

      FOUNDATION_INLINE const T& operator[] ( size_t index ) const
      {
        assert(index < array._size());
        return _ptr[index];
      }

    public:
      FOUNDATION_INLINE size_t size() const
      { return _size; }

      FOUNDATION_INLINE size_t reserved() const
      { return _reserved; }

      FOUNDATION_EXPORT T* to_ptr()
      { return _ptr; }

      FOUNDATION_INLINE const T* to_ptr() const
      { return _ptr; }

    public:
      FOUNDATION_INLINE Iterator begin() const
      { const Array<T>& self = *this; return Iterator(self, (size_t)0); }

      FOUNDATION_INLINE Iterator end() const
      { const Array<T>& self = *this; return Iterator(self, max(_size, (size_t)1) - 1); }

      FOUNDATION_INLINE Iterator front() const
      { const Array<T>& self = *this; return Iterator(self, 0); }

      FOUNDATION_INLINE Iterator back() const
      { const Array<T>& self = *this; return Iterator(self, _size); }

      FOUNDATION_INLINE void push_back( const T& item )
      {
        if (_size == _reserved)
          grow();

        copy_safe((void*)&_ptr[_size++], (const void*)&item, sizeof(T));
      }

      FOUNDATION_INLINE void pop_back()
      {
        _size--;
      }

    private:
      void grow()
      {
        _ptr = (T*)_allocator.realloc(
          (void*)_ptr,
          alignof(T),
          round_to_prime(_reserved) * sizeof(T)
        );
      }

    private:
      Allocator& _allocator;
      size_t _size, _reserved;
      T* _ptr;
  };
} // foundation

#endif // _FOUNDATION_ARRAY_H_