// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#ifndef _FOUNDATION_NETWORK_PROTOCOL_H_
#define _FOUNDATION_NETWORK_PROTOCOL_H_

// Provides a abstract method of describing and handling TCP/IP protocols.

#include <foundation/detect.h>
#include <foundation/compat.h>
#include <foundation/config.h>
#include <foundation/assert.h>
#include <foundation/hash.h>
#include <foundation/digest/murmur_hash.h>
#include <foundation/containers/hash_table.h>
#include <foundation/system/network.h>
#include <foundation/network/packet.h>

namespace foundation {
  namespace Network {
    class FOUNDATION_EXPORT Protocol final {
      public:
        typedef Hash<uint32_t, murmur_hash> Type;

        typedef void (*Constructor)(
          void* closure,
          Packet& packet,
          va_list ap );

        typedef void (*Handler)(
          void* closure,
          Packet& packet );

      public:
        class Connection;
        friend class Connection;

        class Connection final {
          __foundation_trait(Connection, non_copyable);

          private:
            friend class Protocol;

          private:
            Connection(
              const Protocol& protocol,
              Socket remote );

            ~Connection();

          private:
            static Connection* create(
              const Protocol& protocol,
              Socket socket );

          public:
            void disconnect();

            bool send(
              const Protocol::Type type,
              void* closure, ... );

            bool update(
              void* closure );

          private:
            const Protocol& _protocol;
            Socket _remote;
        };

      public:
        Protocol(
          const char* name,
          const uint32_t version );

        Protocol(
          const Protocol& proto );

        ~Protocol();

        Protocol& operator= (
          const Protocol& proto );

      public:
        Connection* connect(
          const Network::Address& address,
          const uint32_t timeout = 10000 ) const;

      public:
        Protocol& local_to_remote(
          const Type type,
          Constructor constructor );

        Protocol& remote_to_local(
          const Type type,
          Handler handler );

      private:
        const char* _name;
        uint32_t _version;
        HashTable<Type, Constructor> _local_to_remote;
        HashTable<Type, Handler> _remote_to_local;
    };
  } // Network
} // foundation

#endif // _FOUNDATION_NETWORK_PROTOCOL_H_
