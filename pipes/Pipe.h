#pragma once

#include <functional>

#include "destinations/destination.h"
class Pipe {
  virtual void writeInner(void* bytes) = 0;

 public:
  Destination* next;
  virtual void write(void* bytes);
  virtual void prepare(void* arg, ...) = 0;
  Pipe(){};
  Pipe(Destination* next) : next(next){};
};
