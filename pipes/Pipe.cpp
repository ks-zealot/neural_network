#include "pipes/Pipe.h"

#include "global.h"
#include "logging/log.h"
void Pipe::write(void* bytes) {
  info("Pipe write async data");
  std::function f = [&bytes, this]() { this->writeInner(bytes); };
threadPool.queueJob(f);
}
