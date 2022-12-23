#include <iostream>

#include "DummyDestination.h"
#include "utils/ByteBuffer.h"
void DummyDestination::eat(void* c) { std::cout << "Im dummy" << std::endl; }
