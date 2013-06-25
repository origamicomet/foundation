# This file is part of Butane. See README.md and LICENSE.md for details.
# Copyright (c) 2012 Michael Williams <devbug@bitbyte.ca>

import math

def __bytes_to_long(bytes):
  assert len(bytes) == 4
  return sum((b << (k * 8)) for k, b in enumerate(bytes))

def murmur_hash(key, key_len, seed):
  m = 0x5bd1e995
  r = 24

  MASK = (2 ** 32) - 1
  h = seed ^ key_len

  key = key + ("\x00" * (key_len - len(key)))
  for l in range(0, (key_len/4)*4, 4):
    k = __bytes_to_long(key[l:l + 4])
    k = (k * m) & MASK
    k = (k ^ (k >> r))
    k = (k * m) & MASK
    h = (h * m) & MASK
    h = (h ^ k)

  l = (key_len - (key_len/4)*4)
  remaining = key[(key_len-l):]
  if l >= 3:
    h = (h ^ (remaining[2] << 16))
  if l >= 2:
    h = (h ^ (remaining[1] << 8))
  if l >= 1:
    h = (h ^ (remaining[0] << 0))
    h = (h * m) & MASK

  h = (h ^ (h >> 13))
  h = (h * m) & MASK
  h = (h ^ (h >> 15))

  return h

def __bytes_to_long_long(bytes):
  assert len(bytes) == 8
  return sum((b << (k * 8)) for k, b in enumerate(bytes))

def murmur_hash_64(key, key_len, seed):
  raise "Not implemented!"
