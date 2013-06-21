// The author(s) disclaim copyright to this source-code.
// Can be licensed under MIT (in case the public domain is not recognized).
// More information can be found in the LICENSE file.

#include <foundation/network/packet.h>

namespace foundation {
  namespace Network {
    Packet::Packet(
      Allocator& allocator,
      const size_t reserve
    ) : _read_offs(0)
      , _write_offs(0)
      , _raw(allocator, reserve)
    {
    }

    Packet::Packet(
      Allocator& allocator,
      const void* bytes,
      size_t num_of_bytes
    ) : _read_offs(0)
      , _write_offs(num_of_bytes)
      , _raw(allocator, num_of_bytes)
    {
      _raw.resize(num_of_bytes);
      copy((void*)_raw.raw(), bytes, num_of_bytes);
    }

    Packet::Packet(
      const Packet& p
    ) : _read_offs(p._read_offs)
      , _write_offs(p._write_offs)
      , _raw(p._raw)
    {
    }

    Packet::~Packet()
    {
    }

    Packet& Packet::operator= (
      const Packet& p )
    {
      if (&p == this)
        return *this;
      _read_offs = p._read_offs;
      _write_offs = p._write_offs;
      _raw = p._raw;
      return *this;
    }

    void Packet::write(
      const void* bytes,
      size_t num_of_bytes )
    {
      assert(bytes != nullptr);
      while ((_write_offs + num_of_bytes) > _raw.size())
        _raw.resize(max((size_t)1, _raw.size()) * 2);
      copy((void*)&_raw[_write_offs], bytes, num_of_bytes);
      _write_offs += num_of_bytes;
    }

    void Packet::write(
      const Field field,
      const void* bytes,
      size_t num_of_bytes )
    {
      assert(bytes != nullptr);
      write((const void*)&field, sizeof(Field));
      write(bytes, num_of_bytes);
    }

    template <typename T>
    void Packet::write(
      const Field field,
      const T& value )
    {
      write(field, (const void*)&value, sizeof(T));
    }

    template void Packet::write<bool>( const Field, const bool& );
    template void Packet::write<int8_t>( const Field, const int8_t& );
    template void Packet::write<uint8_t>( const Field, const uint8_t& );
    template void Packet::write<int16_t>( const Field, const int16_t& );
    template void Packet::write<uint16_t>( const Field, const uint16_t& );
    template void Packet::write<int32_t>( const Field, const int32_t& );
    template void Packet::write<uint32_t>( const Field, const uint32_t& );
    template void Packet::write<int64_t>( const Field, const int64_t& );
    template void Packet::write<uint64_t>( const Field, const uint64_t& );
    template void Packet::write<float>( const Field, const float& );
    template void Packet::write<double>( const Field, const double& );

    void Packet::write(
      const Field field,
      const char* value )
    {
      assert(value != nullptr);
      write((const void*)&field, sizeof(Field));
      const uint32_t len = strlen(value) + 1;
      write((const void*)&len, sizeof(uint32_t));
      write((const void*)value, strlen(value) + 1);
    }

    bool Packet::read(
      void* bytes,
      size_t num_of_bytes )
    {
      assert(bytes != nullptr);
      if ((_read_offs + num_of_bytes) > _write_offs)
        return false;
      copy(bytes, (const void*)&_raw[_read_offs], num_of_bytes);
      _read_offs += num_of_bytes;
      return true;
    }

    bool Packet::read(
      const Field field,
      void* bytes,
      size_t num_of_bytes )
    {
      assert(bytes != nullptr);
      Field field_;
      if (!read((void*)&field_, sizeof(Field)))
        return false;
      if (field_ != field)
        return false;
      return read(bytes, num_of_bytes);
    }

    template <typename T>
    bool Packet::read(
      const Field field,
      T& value )
    {
      return read(field, (void*)&value, sizeof(T));
    }

    template bool Packet::read<bool>( const Field, bool& );
    template bool Packet::read<int8_t>( const Field, int8_t& );
    template bool Packet::read<uint8_t>( const Field, uint8_t& );
    template bool Packet::read<int16_t>( const Field, int16_t& );
    template bool Packet::read<uint16_t>( const Field, uint16_t& );
    template bool Packet::read<int32_t>( const Field, int32_t& );
    template bool Packet::read<uint32_t>( const Field, uint32_t& );
    template bool Packet::read<int64_t>( const Field, int64_t& );
    template bool Packet::read<uint64_t>( const Field, uint64_t& );
    template bool Packet::read<float>( const Field, float& );
    template bool Packet::read<double>( const Field, double& );

    bool Packet::read(
      const Field field,
      const char*& value )
    {
      Field field_;
      if (!read((void*)&field_, sizeof(Field)))
        return false;
      if (field_ != field)
        return false;
      uint32_t len;
      if (!read((void*)&len, sizeof(uint32_t)))
        return false;
      if (len == 0)
        return false;
      value = (const char*)&_raw[_read_offs];
      _read_offs += len;
      return true;
    }
  } // Network
} // foundation
