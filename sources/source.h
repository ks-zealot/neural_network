#pragma once

#include <list>

#include "../destinations/destination.h"
#include "pipes/Pipe.h"

class Source {
 public:
  virtual void retrieve() = 0;

  Source(std::list<Destination*> Destinations, std::list<Pipe*> Pipes);

 protected:
  Pipe* pipe = 0;
};
