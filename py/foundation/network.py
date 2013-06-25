# This file is part of Butane. See README.md and LICENSE.md for details.
# Copyright (c) 2012 Michael Williams <devbug@bitbyte.ca>

import struct
import socket
import select
from cStringIO import StringIO
from Queue import Queue
from .digest import (murmur_hash, murmur_hash_64)

class FieldMismatch(Exception):
  pass

class Packet:
  def __init__(self, raw=""):
    self._buffer = StringIO(raw)

  def __write_field(self, field):
    f = bytearray(field)
    self._buffer.write(struct.pack('<L', murmur_hash(f, len(f) + 1, 0)))

  def write_bool(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<_Bool', v))

  def write_int8(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<b', v))

  def write_uint8(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<B', v))

  def write_int16(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<h', v))

  def write_uint16(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<H', v))

  def write_int32(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<l', v))

  def write_uint32(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<L', v))

  def write_int64(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<q', v))

  def write_uint64(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<Q', v))

  def write_float(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<f', v))

  def write_double(self, field, v):
    self.__write_field(field)
    self._buffer.write(struct.pack('<d', v))

  def write_str(self, field, v):
    self.__write_field(field)
    self._buffer.write(len(v) + 1)
    self._buffer.write(v)
    self._buffer.write(struct.pack('<b', '\x00'))

  def __read_field(self, field):
    f = struct.unpack('<L', self._buffer.read(4))[0]
    if f != murmur_hash(bytearray(field), len(field) + 1, 0):
      raise FieldMismatch

  def read_bool(self, field):
    self.__read_field(field)
    return struct.unpack('<_Bool', self._buffer.read(1))[0]

  def read_int8(self, field):
    self.__read_field(field)
    return struct.unpack('<b', self._buffer.read(1))[0]

  def read_uint8(self, field):
    self.__read_field(field)
    return struct.unpack('<B', self._buffer.read(1))[0]

  def read_int16(self, field):
    self.__read_field(field)
    return struct.unpack('<h', self._buffer.read(2))[0]

  def read_uint16(self, field):
    self.__read_field(field)
    return struct.unpack('<H', self._buffer.read(2))[0]

  def read_int32(self, field):
    self.__read_field(field)
    return struct.unpack('<l', self._buffer.read(4))[0]

  def read_uint32(self, field):
    self.__read_field(field)
    return struct.unpack('<L', self._buffer.read(4))[0]

  def read_int64(self, field):
    self.__read_field(field)
    return struct.unpack('<q', self._buffer.read(8))[0]

  def read_uint64(self, field):
    self.__read_field(field)
    return struct.unpack('<Q', self._buffer.read(8))[0]

  def read_float(self, field):
    self.__read_field(field)
    return struct.unpack('<f', self._buffer.read(4))[0]

  def read_double(self, field):
    self.__read_field(field)
    return struct.unpack('<d', self._buffer.read(8))[0]

  def read_str(self, field):
    self.__read_field(field)
    len = struct.unpack('<L', self._buffer.read(4))[0]
    return self._buffer.read(len)[:(len-1)]

  @property
  def raw(self):
    return self._buffer.getvalue()

  @property
  def length(self):
    return self._buffer.tell()

class Protocol:
  def __init__(self, name, version):
    self.name = name
    self.version = version
    self._connect = None
    self._disconnect = None
    self._unhandled = None
    self._local_to_remote = {}
    self._remote_to_local = {}

  def connect(self, handler):
    self._connect = handler
    return self

  def disconnect(self, handler):
    self._disconnect = handler
    return self

  def unhandled(self, handler):
    self._unhandled = handler
    return self

  def local_to_remote(self, type, constructor):
    self._local_to_remote[type] = constructor
    return self

  def remote_to_local(self, type, handler):
    h = murmur_hash(bytearray(type), len(type) + 1, 0)
    self._remote_to_local[h] = handler
    return self

  def host(self, host, port, backlog=1):
    h = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    h.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    h.bind((host, port))
    h.listen(backlog)

    sockets = [h]
    remotes = {}
    while True:
      readable, writeable, errored = select.select(sockets, [], sockets)
      for s in readable:
        if s is h:
          remote, addr = h.accept()
          conn = Connection.create(self, remote)
          sockets.append(remote)
          remotes[remote] = (conn, self._connect(conn))
        else:
          if not remotes[s][0].update(remotes[s][1]):
            self._disconnect(remotes[s][0], remotes[s][1])
            remotes[s][0].disconnect()
            del remotes[s]
            sockets.remove(s)

class Connection:
  def __init__(self, protocol, remote):
    self._protocol = protocol
    self._remote = remote

  @staticmethod
  def create(protocol, socket):
    socket.setblocking(1)
    return Connection(protocol, socket)

  def disconnect(self):
    if self._remote is not None:
      self._remote.shutdown(socket.SHUT_RDWR)
      del self._remote

  def send(self, type, closure, *args):
    try:
      ctor = self._protocol._local_to_remote[type]
      assert ctor is not None
      packet = Packet()
      packet.write_uint32("__type", murmur_hash(bytearray(type), len(type) + 1, 0))
      ctor(closure, packet, *args)
      self._remote.send(struct.pack('<L', packet.length))
      self._remote.send(packet.raw, packet.length)
    except:
      return False

    return True

  def update(self, closure):
    try:
      len = struct.unpack('<L', self._remote.recv(4))[0]
    except socket.timeout:
      return True
    except:
      return False

    try:
      packet = Packet(self._remote.recv(len))
      type = packet.read_uint32("__type")
    except:
      return False

    try:
      self._protocol._remote_to_local[type](closure, packet)
    except:
      try:
        self._protocol._unhandled(closure, type)
      except:
        pass
      return True

    return True

  @property
  def address(self):
    return self._remote.getpeername()
