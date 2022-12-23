#include "pipes/FunctionalPipe.h"

#include <functional>

#include "global.h"

void FunctionalPipe::write(void* bytes) {
  std::function f = [bytes, this]() { this->writeInner(this->func(bytes)); };
  threadPool.queueJob(f);
}
