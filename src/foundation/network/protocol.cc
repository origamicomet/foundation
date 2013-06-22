// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/network/protocol.h>

#include <foundation/allocators/proxy.h>
#include <foundation/thread_safe/static.h>

namespace foundation {
  namespace Network {
    static Allocator& __allocator_initializer() {
      static ProxyAllocator allocator("protocols", Allocators::heap());
      return allocator;
    }

    static const thread_safe::Static< Allocator >
      __ts_allocator(&__allocator_initializer);

    static Allocator& allocator() {
      return __ts_allocator();
    }

    Protocol::Connection::Connection(
      const Protocol& protocol,
      Socket remote
    ) : _protocol(protocol)
      , _remote(remote)
    {
    }

    Protocol::Connection::~Connection()
    {
      _remote.disconnect();
    }

    Protocol::Connection* Protocol::Connection::create(
      const Protocol& protocol,
      Socket socket )
    {
      socket.set_sending_timeout(10);
      socket.set_receiving_timeout(10);
      return make_new(Connection, allocator())(protocol, socket);
    }

    void Protocol::Connection::disconnect()
    {
      make_delete(Connection, allocator(), this);
    }

    bool Protocol::Connection::send(
      const Protocol::Type type,
      void* closure, ... )
    {
      Protocol::Constructor ctor;
      if (!_protocol._local_to_remote.find(type, ctor))
        return false;

      va_list ap;
      va_start(ap, closure);

      Packet packet(allocator());
      packet.write(Packet::Field("__type"), (uint32_t)type);
      ctor(closure, packet, ap);
      va_end(ap);

      const uint32_t len = (uint32_t)packet.length();
      if (!_remote.send_all((const void*)&len, sizeof(uint32_t)))
        return false;
      if (!_remote.send_all(packet.raw(), packet.length()))
        return false;

      return true;
    }

    bool Protocol::Connection::update(
      void* closure )
    {
      Protocol::Type type;

      int r;
      if ((r = _remote.receive((void*)&type, sizeof(Protocol::Type)) < sizeof(Protocol::Type))) {
        const int err = Network::get_last_error();
        if ((err == EWOULDBLOCK) || (err == EAGAIN))
          return true; /* No remote-to-local to process. */
        return false; /* Disconnect, or other error. */
      }

      uint32_t len;
      if ((!_remote.receive_all((void*)&len, sizeof(uint32_t))) || (len == 0))
        return false; /* Disconnect, or other error. */

      Packet packet(allocator(), len);
      if (!_remote.receive_all((void*)packet.raw(), len))
        return false; /* Disconnect, or other error. */

      Protocol::Handler handler;
      if (!_protocol._remote_to_local.find(type, handler))
        return true; /* Skip. */

      handler(closure, packet);
      return true;
    }

    Protocol::Protocol(
      const char* name,
      const uint32_t version
    ) : _name(name)
      , _version(version)
      , _local_to_remote(allocator(), 8)
      , _remote_to_local(allocator(), 8)
    {
    }

    Protocol::Protocol(
      const Protocol& proto
    ) : _name(proto._name)
      , _version(proto._version)
      , _local_to_remote(proto._local_to_remote)
      , _remote_to_local(proto._remote_to_local)
    {
    }

    Protocol::~Protocol()
    {}

    Protocol& Protocol::operator= (
      const Protocol& proto )
    {
      if (&proto == this)
        return *this;
      _name = proto._name;
      _version = proto._version;
      _local_to_remote = proto._local_to_remote;
      _remote_to_local = proto._remote_to_local;
      return *this;
    }

    Protocol::Connection* Protocol::connect(
      const Network::Address& address,
      const uint32_t timeout ) const
    {
      Socket remote;
      if (!remote.connect(address, (timeout > 0) ? timeout : -1))
        return nullptr;
      return Connection::create(*this, remote);
    }

    Protocol& Protocol::local_to_remote(
      const Type type,
      Constructor constructor )
    {
      assert(constructor != nullptr);
      _local_to_remote.insert(type, constructor);
      return *this;
    }

    Protocol& Protocol::remote_to_local(
      const Type type,
      Handler handler )
    {
      assert(handler != nullptr);
      _remote_to_local.insert(type, handler);
      return *this;
    }
  } // Network
} // foundation
