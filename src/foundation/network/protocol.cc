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
      socket.set_non_blocking(true);
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
      uint32_t len;

      int r;
      if ((r = _remote.receive((void*)&len, sizeof(uint32_t)) < sizeof(uint32_t)) <= 0) {
        const int err = Network::get_last_error();
        if ((err == EWOULDBLOCK) || (err == EAGAIN))
          return true; /* No remote-to-local to process. */
        return false; /* Disconnect, or other error. */
      }

      Packet packet(allocator(), len);
      if (!_remote.receive_all((void*)packet.raw(), len))
        return false; /* Disconnect, or other error. */

      uint32_t type;
      if (!packet.read<uint32_t>("__type", type))
        return false; /* Malformed packet. */

      Protocol::Handler handler;
      if (!_protocol._remote_to_local.find(*((Type*)type), handler)) {
        if (_protocol._unhandled)
          _protocol._unhandled(closure, *((Type*)type));
        return true; /* Skip. */
      }

      handler(closure, packet);
      return true;
    }

    Protocol::Protocol(
      const char* name,
      const uint32_t version
    ) : _name(name)
      , _version(version)
      , _connect(nullptr)
      , _disconnect(nullptr)
      , _unhandled(nullptr)
      , _local_to_remote(allocator(), 8)
      , _remote_to_local(allocator(), 8)
    {
    }

    Protocol::Protocol(
      const Protocol& proto
    ) : _name(proto._name)
      , _version(proto._version)
      , _connect(proto._connect)
      , _disconnect(proto._disconnect)
      , _unhandled(proto._unhandled)
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
      _connect = proto._connect;
      _disconnect = proto._disconnect;
      _unhandled = proto._unhandled;
      _local_to_remote = proto._local_to_remote;
      _remote_to_local = proto._remote_to_local;
      return *this;
    }

    Protocol& Protocol::connected(
      OnConnected handler )
    {
      assert(handler != nullptr);
      _connect = handler;
      return *this;
    }

    Protocol& Protocol::disconnected(
      OnDisconnected handler )
    {
      assert(handler != nullptr);
      _disconnect = handler;
      return *this;
    }

    Protocol& Protocol::unhandled(
      Unhandled handler )
    {
      assert(handler != nullptr);
      _unhandled = handler;
      return *this;
    }

    Protocol& Protocol::local_to_remote(
      const Type type,
      Constructor constructor )
    {
      assert(type != nullptr);
      assert(constructor != nullptr);
      _local_to_remote.insert(type, constructor);
      return *this;
    }

    Protocol& Protocol::remote_to_local(
      const Type type,
      Handler handler )
    {
      assert(type != nullptr);
      assert(handler != nullptr);
      _remote_to_local.insert(type, handler);
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

    bool Protocol::host(
      void (*tick)( void ),
      const Network::Address& host,
      const int backlog ) const
    {
      Socket h;
      if (!h.bind(host))
        return false;
      if (!h.listen(backlog))
        return false;

      Array< Pair<Connection*, void*> > connections(allocator());
      SocketSet readable;

      while (true) {
        readable.zero();
        readable.set(h);

        for (auto iter = connections.begin(); iter != connections.end(); ++iter)
          readable.set((*iter).key->remote());

        if (!Network::select(&readable, nullptr, nullptr, 10))
          goto skip;

        if (readable.is_set(h)) {
          Socket remote;
          Network::Address addr;
          if (!h.accept(remote, addr))
            return false;
          Connection* conn = Connection::create(*this, remote);
          connections += Pair<Connection*, void*>(conn, _connect ? _connect(conn, addr) : nullptr);
        }

        for (auto iter = connections.begin(); iter != connections.end(); ++iter) {
          if (!readable.is_set(((*iter).key)->remote()))
            continue;
          if ((*iter).key->update((*iter).value))
            continue;
          if (_disconnect)
            _disconnect((*iter).value);
          connections.remove(iter);
        }

      skip:
        if (tick)
          tick();
      }

      return true;
    }
  } // Network
} // foundation
