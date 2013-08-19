// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_THREAD_SAFE_STATIC_H_
#define _FOUNDATION_THREAD_SAFE_STATIC_H_

// A thread safe on-demand static initializer.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/system/concurrency.h>

namespace foundation {
namespace thread_safe {
  template <typename T>
  class FOUNDATION_EXPORT Static final {
    __foundation_trait(Static, non_copyable);

    public:
      typedef T* (*Initializer)( void );

    private:
      typedef T* (*Getter)(
        const Static<T>* s );

    public:
      Static(
        Initializer initializer
      ) : _initializer(initializer)
        , _getter(&Static<T>::__initialize)
        , _value(nullptr)
      {}

      ~Static()
      {}

    public:
      FOUNDATION_INLINE T& operator() () const
      { return *_getter(this); }

      FOUNDATION_INLINE operator T&() const
      { return *_getter(this); }

    private:
      static T* __initialize( const Static<T>* s ) {
        if (!__sync_bool_compare_and_swap((volatile void**)&s->_getter, (void*)&Static<T>::__initialize, (void*)&Static<T>::__initializing))
          return s->_getter(s);
        __sync_val_compare_and_swap((volatile void**)&s->_value, (void*)nullptr, (void*)s->_initializer());
        return s->_value;
      }

      static T* __initializing( const Static<T>* s ) {
        while (__sync_bool_compare_and_swap((volatile void**)&s->_value, (void*)nullptr, (void*)nullptr));
        __sync_val_compare_and_swap((volatile void**)&s->_getter, (void*)&Static<T>::__initializing, (void*)&Static<T>::__get);
        return s->_value;
      }

      static T* __get( const Static<T>* s ) {
        return s->_value;
      }

    private:
      Initializer _initializer;
      Getter _getter;
      mutable T* _value;
  };
} // thread_safe
} // foundation

#endif // _FOUNDATION_THREAD_SAFE_STATIC_H_
