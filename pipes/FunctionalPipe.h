#pragma once

#include <functional>

#include "pipes/Pipe.h"

class FunctionalPipe : public Pipe {
 public:
  virtual void write(void* bytes);
  virtual void writeInner(void* bytes) = 0;
  virtual void prepare(void* arg, ...) = 0;
  std::function<void*(void* in)> func;

  FunctionalPipe(std::function<void*(void* in)> f) : func(f){};

  FunctionalPipe(std::function<void*(void* in)> f, Destination* next)
      : func(f), Pipe(next){};
};
