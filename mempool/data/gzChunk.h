#pragma once
#include "mempool/Mempool.h"

struct gzChunk {
 public:
  static pool<gzChunk> p;

  int size;
  unsigned char data[1024] = {0};

  void* operator new(size_t size) { return p.alloc(); }

  void operator delete(void* t) { p.free(static_cast<gzChunk*>(t)); }
};
