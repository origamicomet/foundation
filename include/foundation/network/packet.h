// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_NETWORK_PACKET_H_
#define _FOUNDATION_NETWORK_PACKET_H_

// Provides methods to read and write primitives from a variable length packet.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>
#include <foundation/hash.h>
#include <foundation/digest/murmur_hash.h>
#include <foundation/system/network.h>

namespace foundation {
  namespace Network {
    class FOUNDATION_EXPORT Packet final {
      public:
        typedef Hash<uint32_t, murmur_hash> Field;

      public:
        Packet(
          Allocator& allocator,
          const size_t reserve = 0 );

        Packet(
          Allocator& allocator,
          const void* bytes,
          size_t num_of_bytes );

        Packet(
          const Packet& p );

        ~Packet();

        Packet& operator= (
          const Packet& p );

      private:
        void write(
          const void* bytes,
          size_t num_of_bytes );

      public:
        void write(
          const Field field,
          const void* bytes,
          size_t num_of_bytes );

        template <typename T>
        void write(
          const Field field,
          const T& value );

        void write(
          const Field field,
          const char* value );

      private:
        bool read(
          void* bytes,
          size_t num_of_bytes );

      public:
        bool read(
          const Field field,
          void* bytes,
          size_t num_of_bytes );

        template <typename T>
        bool read(
          const Field field,
          T& value );

        bool read(
          const Field field,
          const char*& value );

      public:
        FOUNDATION_INLINE const void* raw() const
        { return _raw.raw(); }

        FOUNDATION_INLINE size_t length() const
        { return _write_offs; }

      private:
        size_t _read_offs;
        size_t _write_offs;
        Array<uint8_t> _raw;
    };
  } // Network
} // foundation

#endif // _FOUNDATION_NETWORK_PACKET_H_
