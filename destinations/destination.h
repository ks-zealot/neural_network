#pragma once

class Pipe;
class Destination {
 public:
  Pipe* pipe;
  virtual void eat(void* data) = 0;
  virtual ~Destination() {}
};
