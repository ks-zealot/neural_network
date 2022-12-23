#pragma once

#include "pipes/FunctionalPipe.h"
#include <zlib.h>

class GzPipe : public FunctionalPipe {
 public:
  virtual void writeInner(void* b);
  virtual void prepare(void* arg, ...);
  GzPipe()
      : FunctionalPipe([this](void* bytes) { return this->deflate(bytes); }){};

 private:
  void* deflate(void* bytes);
  z_stream strm;
  int ret;
};
