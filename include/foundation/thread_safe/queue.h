// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_THREAD_SAFE_QUEUE_H_
#define _FOUNDATION_THREAD_SAFE_QUEUE_H_

// A thread safe fized-size queue.

#include <foundation/config.h>
#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/assert.h>
#include <foundation/allocator.h>
#include <foundation/mutex.h>

namespace foundation {
namespace thread_safe {
  template <typename T>
  class Queue {
    FOUNDATION_NON_COPYABLE(Queue);

    public:
      Queue( Allocator& allocator, size_t size )
        : _allocator(allocator)
        , _size(size)
        , _buffer((T*)_allocator.alloc(sizeof(T) * size))
        , _queue(0)
        , _dequeue(0)
      {
      }

      ~Queue()
      {
        _allocator.free((void*)_buffer);
      }

    public:
      void enqueue( const T& item )
      {
        ScopedMutexLock(_mutex);
        if ((_queue - _dequeue) == size)
          fail("Unable to enqueue, backing ring-buffer is full!\n");
        _buffer[(_queue++) % _size] = item;
      }

      T next()
      {
        while (true) {
          ScopedMutexLock(_mutex);
          if ((_queue - _dequeue) == 0)
            break;
          return _buffer[(_dequeue++) % _size];
        }
      }

    public:
      FOUNDATION_INLINE Allocator& allocator() const
      { return _allocator; }
      
      FOUNDATION_INLINE size_t size() const
      { return _size; }

    private:
      Allocator& _allocator;
      size_t _size;
      T* _buffer;
      size_t _queue, _dequeue;
      Mutex _mutex;
  };
} // thread_safe
} // foundation

#endif // _FOUNDATION_THREAD_SAFE_QUEUE_H_