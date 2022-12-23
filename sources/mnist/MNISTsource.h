#pragma once
#include <curl/curl.h>

#include <cstddef>
#include <iostream>

#include "pipes/FilePipe.h"
#include "sources/source.h"

class MNISTsource : public Source {
 private:
  const char* url;
  const char* targetFile;
  FilePipe filePipe;
  CURL* curl;

 public:
  std::size_t write(void* mem, std::size_t size, std::size_t nmem);
  void retrieve();
  MNISTsource(const char* url, const char* file,
              std::list<Destination*> destinations, std::list<Pipe*> pipes)
      : url(url),
        targetFile(file),
        filePipe(targetFile),
        Source(destinations, pipes) {}
};
