// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_CONTAINERS_THREAD_SAFE_QUEUE_H_
#define _FOUNDATION_CONTAINERS_THREAD_SAFE_QUEUE_H_

// Provides a thread-safe fixed-sized Queue.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>
#include <foundation/allocator.h>
#include <foundation/system/concurrency.h>
#include <foundation/algorithms/optimized_copy.h>
#include <foundation/algorithms/optimized_destruct.h>

namespace foundation {
namespace thread_safe {
  template <typename T>
  class FOUNDATION_EXPORT Queue final
  {
    public:
      Queue(
        Allocator& allocator,
        size_t size
      ) : _allocator(allocator)
        , _ring_buffer((T*)_allocator.alloc(size * sizeof(T), alignment_of<T>::value))
        , _size(size)
        , _queue(0)
        , _dequeue(0)
      {}

      Queue(
        const Queue& queue
      ) : _allocator(queue._allocator)
        , _ring_buffer(nullptr)
        , _size(0)
        , _queue(0)
        , _dequeue(0)
      {
        queue._mutex.lock();
        _ring_buffer = (T*)_allocator.alloc(queue._size, alignof<T>::value);
        _size = queue._size;
        optimizied_copy(_ring_buffer, queue._ring_buffer, queue._size);
        queue._mutex.unlock();
      }

      Queue& operator= (
        const Queue& queue )
      {
        if (&queue == this)
          return *this;

        _mutex.lock();
        optimized_destruct<T>(_ring_buffer, _size);
        _allocator.free((void*)_ring_buffer);
        queue._mutex.lock();
        _ring_buffer = (T*)_allocator.alloc(len, alignof<T>::value);
        _size = queue._size;
        _queue = queue._queue;
        _dequeue = queue._dequeue;
        optimizied_copy(_ring_buffer, queue._ring_buffer, queue._size);
        queue._mutex.unlock();
        _mutex.unlock();
      }

      ~Queue()
      {
        _mutex.lock();
        optimized_destruct<T>(_ring_buffer, _size);
        _allocator.free((void*)_ring_buffer);
        _mutex.unlock();
      }

    public:
      void enqueue(
        const T& value )
      {
        _mutex.lock();
        // if (_queue < _dequeue)
        //   _dequeue = _dequeue % _size;
        if ((_dequeue - _queue) == 0)
          while (!_has_room.wait(_mutex));
        _ring_buffer[(_queue++) % _size] = value;
        _mutex.unlock();
        _has_element.signal();
      }

      void dequeue(
        T& value )
      {
        _mutex.lock();
        if ((_dequeue - _queue) == 0)
          while (!_has_element.wait(_mutex));
        value = _ring_buffer[(_dequeue++) % _size];
        _mutex.unlock();
        _has_room.signal();
      }

    public:
      FOUNDATION_INLINE Allocator& allocator() const
      { return _allocator; }

    private:
      Allocator& _allocator;
      Mutex _mutex;
      ConditionVariable _has_room;
      ConditionVariable _has_element;
      T* _ring_buffer;
      size_t _size;
      size_t _queue, _dequeue;
  };
} // thread_safe
} // foundation

#endif // _FOUNDATION_CONTAINERS_THREAD_SAFE_QUEUE_H_
