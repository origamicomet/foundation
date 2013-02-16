// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_INTRUSIVE_LIST_H_
#define _FOUNDATION_INTRUSIVE_LIST_H_

// A circular intrusive list.

#include <foundation/config.h>
#include <foundation/compat.h>
#include <foundation/assert.h>

namespace foundation {
  class FOUNDATION_EXPORT IntrusiveList {
    FOUNDATION_NON_COPYABLE(IntrusiveList);

    public:
      struct Node {
        Node* next;
        Node* prev;

        FOUNDATION_INLINE Node()
        { next = prev = nullptr; }

        FOUNDATION_INLINE void remove()
        { next->prev = prev; prev->next = next; }

        template <typename T, size_t _NodeOffset>
        FOUNDATION_INLINE T* to_ptr()
        { return ((T*)(((uintptr_t)this) - _NodeOffset)); }

        template <typename T, size_t _NodeOffset>
        FOUNDATION_INLINE const T* to_ptr() const
        { return ((const T*)(((uintptr_t)this) - _NodeOffset)); }

        template <typename T, size_t _NodeOffset>
        FOUNDATION_INLINE T& to_ref()
        { return *to_ptr(); }

        template <typename T, size_t _NodeOffset>
        FOUNDATION_INLINE const T& to_ref() const
        { return *to_ptr(); }
      };

    public:
      class Iterator {
        friend class IntrusiveList;

        private:
          FOUNDATION_INLINE Iterator( const IntrusiveList& list, Node* node )
            : _list(const_cast<IntrusiveList&>(list))
            , _node(node)
          {}

          FOUNDATION_INLINE Iterator( IntrusiveList& list, Node* node )
            : _list(list)
            , _node(node)
          {}

        public:
          FOUNDATION_INLINE Iterator( const Iterator& iter )
            : _list(iter._list)
            , _node(iter._node)
          {}

          FOUNDATION_INLINE Iterator& operator= ( const Iterator& iter )
          {
            _list = iter._list;
            _node = iter._node;
            return *this;
          }

        public:
          FOUNDATION_INLINE bool operator== ( const Iterator& iter )
          { return ((_list == iter._list) && (_node == iter._node)); }

          FOUNDATION_INLINE bool operator!= ( const Iterator& iter )
          { return ((_list != iter._list) || (_node != iter._node)); }

          FOUNDATION_INLINE Iterator operator++ ()
          { return Iterator(_list, _node->next); }

          FOUNDATION_INLINE Iterator operator++ ( int )
          { Iterator iter(*this); ++(*this); return iter; }

          FOUNDATION_INLINE Iterator operator-- ()
          { return Iterator(_list, _node->prev); }

          FOUNDATION_INLINE Iterator operator-- ( int )
          { Iterator iter(*this); --(*this); return iter; }

        public:
          FOUNDATION_INLINE void remove()
          { _node->remove(); }

          template <typename T, size_t _NodeOffset>
          FOUNDATION_INLINE T* to_ptr()
          { return _node->to_ptr<T, _NodeOffset>(); }

          template <typename T, size_t _NodeOffset>
          FOUNDATION_INLINE const T* to_ptr() const
          { return _node->to_ptr<T, _NodeOffset>(); }

          template <typename T, size_t _NodeOffset>
          FOUNDATION_INLINE T& to_ref()
          { return _node->to_ref<T, _NodeOffset>(); }

          template <typename T, size_t _NodeOffset>
          FOUNDATION_INLINE const T& to_ref() const
          { return _node->to_ref<T, _NodeOffset>(); }
        
          FOUNDATION_INLINE bool is_valid() const
          { return (_node != &_list._head); }

        private:
          IntrusiveList& _list;
          Node* _node;
      };

    public:
      FOUNDATION_INLINE IntrusiveList()
      {
        _head.next = &_head;
        _head.prev = &_head;
      }
      
    public:
      FOUNDATION_INLINE Iterator front() const
      { const IntrusiveList& self = *this; return Iterator(self, _head.next); }

      FOUNDATION_INLINE Iterator back() const
      { const IntrusiveList& self = *this; return Iterator(self, _head.prev); }

      FOUNDATION_INLINE void push_front( Node* node )
      {
        assert(node != nullptr);
        node->next = _head.next;
        node->prev = &_head;
        _head.next->prev = node;
        _head.next = node;
      }

      FOUNDATION_INLINE void pop_front()
      {
        _head.next->next->prev = &_head;
        _head.next = _head.next->next;
      }

      FOUNDATION_INLINE void push_back( Node* node )
      {
        assert(node != nullptr);
        node->prev = _head.prev;
        node->next = &_head;
        _head.prev->next = node;
        _head.prev = node;
      }

      FOUNDATION_INLINE void pop_back()
      {
        _head.prev->prev->next = &_head;
        _head.prev = _head.prev->prev;
      }

    private:
      FOUNDATION_INLINE bool operator== ( const IntrusiveList& list )
      { return (this == &list); }

      FOUNDATION_INLINE bool operator!= ( const IntrusiveList& list )
      { return (this != &list); }

    private:
      Node _head;
  };
} // foundation

#endif // _FOUNDATION_INTRUSIVE_LIST_H_