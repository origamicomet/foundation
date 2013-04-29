// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_ARRAY_H_
#define _FOUNDATION_ARRAY_H_

// A resizable array.

#include <foundation/config.h>
#include <foundation/detect.h>
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
          Iterator( Array<T>& array, size_t index )
            : _array(array)
            , _index(index)
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
          { return ((&_array == &iter._array) && (_index == iter._index)); }

          FOUNDATION_INLINE bool operator!= ( const Iterator& iter )
          { return ((&_array != &iter._array) || (_index != iter._index)); }

          FOUNDATION_INLINE Iterator operator++ ()
          { _index = min(_index + 1, _array.size()); return *this; }

          FOUNDATION_INLINE Iterator operator++ ( int )
          { Iterator iter(*this); ++(*this); return iter; }

          FOUNDATION_INLINE Iterator operator-- ()
          { _index = max(1, _index) - 1; return *this; }

          FOUNDATION_INLINE Iterator operator-- ( int )
          { Iterator iter(*this); --(*this); return iter; }

        public:
          FOUNDATION_INLINE T& to_ref()
          { return _array.to_ptr()[_index]; }

          FOUNDATION_INLINE const T& to_ref() const
          { return _array.to_ptr()[_index]; }
        
          FOUNDATION_INLINE bool is_valid() const
          { return ((_index >= 0) && (_index < _array.size())); }

        private:
          Array<T>& _array;
          size_t _index;
      };

    public:
      explicit Array( Allocator& allocator = Allocator::heap(), size_t reserve = 0 )
        : _allocator(allocator)
        , _size(0)
        , _reserved(reserve)
        , _ptr((T*)allocator.alloc(reserve * sizeof(T), max(alignof(T), (size_t)4)))
      {}

      ~Array()
      {
        _allocator.free((void*)_ptr);
        _ptr = nullptr;
      }

    private:
      // You never go full Boost-tard.
      template <typename T, bool _IsTriviallyCopyable>
      class copier {
        public:
          static void copy( Array<T>* self, const Array<T>& array ) {
            for (size_t idx = 0; idx < array._size; ++idx)
              { new ((void*)(&self->_ptr[idx])) T(array._ptr[idx]); }
          }
      };

      template <typename T>
      class copier<T, true> {
        public:
          static void copy( Array<T>* self, const Array<T>& array ) {
            foundation::copy((void*)self->_ptr, (const void*)array._ptr, array._size * sizeof(T));
          }
      };

      friend class copier<T, false>;
      friend class copier<T, true>;

    public:
      FOUNDATION_INLINE Array( const Array<T>& array )
        : _allocator(array._allocator)
        , _size(array._size)
        , _reserved(array._reserved)
        , _ptr((T*)array._allocator.alloc(array._reserved * sizeof(T), max(alignof(T), (size_t)4)))
      {
        copier<T, is_trivially_copyable<T>::value>::copy(this, array);
      }

      FOUNDATION_INLINE Array<T>& operator= ( const Array<T>& array )
      {
        if (self == &array)
          return *self;
        self->_size = array._size;
        self->_reserved = array._reserved;
        self->_ptr = (T*)array._allocator.realloc((void*)self->_ptr, array._reserved * sizeof(T), max(alignof(T), (size_t)4));
        copier<T, is_trivially_copyable<T>::value>::copy(this, array);
        return *self;
      }

    public:
      FOUNDATION_INLINE void operator+= ( const T& item )
      { push_back(item); }

      FOUNDATION_INLINE T& operator[] ( size_t index )
      {
        assert(index < reserved());
        if (index >= size())
          _size = index + 1;
        return _ptr[index];
      }

      FOUNDATION_INLINE const T& operator[] ( size_t index ) const
      {
        assert(index < size());
        return _ptr[index];
      }

    public:
      FOUNDATION_INLINE void push_back( const T& item )
      {
        if (_size == _reserved)
          grow();
        new ((void*)(&_ptr[_size++])) T(item);
      }

      FOUNDATION_INLINE void pop_back()
      {
        _size--;
      }

    public:
      FOUNDATION_INLINE Iterator begin() const
      { return Iterator((Array<T>&)*this, (size_t)0); }

      FOUNDATION_INLINE Iterator end() const
      { return Iterator((Array<T>&)*this, _size); }

      FOUNDATION_INLINE Iterator front() const
      { return Iterator((Array<T>&)*this, 0); }

      FOUNDATION_INLINE Iterator back() const
      { return Iterator((Array<T>&)*this, max(_size, (size_t)1) - 1); }

    public:
      FOUNDATION_INLINE Allocator& allocator() const
      { return _allocator; }
      
      FOUNDATION_INLINE size_t size() const
      { return _size; }

      void resize( size_t size )
      {
        _size = _reserved = size;
        _ptr = (T*)_allocator.realloc(
          (void*)_ptr, size * sizeof(T), max(alignof(T), (size_t)4)
        );
      }

      FOUNDATION_INLINE size_t reserved() const
      { return _reserved; }

      void reserve( size_t extra )
      {
        _reserved += extra;
        _ptr = (T*)_allocator.realloc(
          (void*)_ptr, _reserved * sizeof(T), max(alignof(T), (size_t)4)
        );
      }

      FOUNDATION_EXPORT T* to_ptr()
      { return _ptr; }

      FOUNDATION_INLINE const T* to_ptr() const
      { return _ptr; }

    private:
      void grow()
      {
        _reserved = round_to_prime(_reserved);
        _ptr = (T*)_allocator.realloc(
          (void*)_ptr, _reserved * sizeof(T), max(alignof(T), (size_t)4)
        );
      }

    private:
      Allocator& _allocator;
      size_t _size, _reserved;
      T* _ptr;
  };
} // foundation

#endif // _FOUNDATION_ARRAY_H_