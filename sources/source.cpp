#include "sources/source.h"

#include <list>
#include "logging/log.h"

#include "destinations/destination.h"

Source::Source(std::list<Destination*> Destinations, std::list<Pipe*> pipes) {
  std::list<Destination*>::iterator dIt = Destinations.begin();
  std::list<Pipe*>::iterator pIt = pipes.begin();
  bool bFlip = false;
  while (pIt != pipes.end()) {
    if (!bFlip) {
      Pipe* p = *pIt;
      ++pIt;
      info("append destination to pipe");
      Destination* d = *dIt;
      p->next = d;
      if (pipe == nullptr) {
info("set root pipe");
        pipe = p;
        int i = 1;
        p->prepare(&i);
      }

    } else {
     info ("append pipe to destination");
      Destination* d = *dIt;
      ++dIt;
      Pipe* p = *pIt;
      d->pipe = p;
      int i = 1;
      p->prepare(&i);
    }
    bFlip = !bFlip;
  }
}
