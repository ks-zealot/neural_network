#pragma once
#include <iostream>

#include "destination.h"
#include "utils/ByteBuffer.h"
#include "utils/Void.h"

class DummyDestination : public Destination {
  void eat(void* b);
  ~DummyDestination() {
    std::cout << "I am dummy and i go to die" << std::endl;
  };
};
