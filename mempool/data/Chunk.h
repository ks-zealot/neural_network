#pragma once
#include "mempool/Mempool.h"

struct Chunk {
 public:
  static pool<Chunk> p;
  unsigned char data[1024] = {0};
  int size;

  void* operator new(size_t size) { return p.alloc(); }

  void operator delete(void* t) { p.free(static_cast<Chunk*>(t)); }
};
