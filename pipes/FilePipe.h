#pragma once
#include <cstdio>
#include <fstream>
#include <functional>

#include "pipes/Pipe.h"
class FilePipe : public Pipe {
 public:
  FILE* fp = 0;
const  char* file;
  virtual void writeInner(void* b);
  virtual void prepare(void*  arg, ...);
  void close();
  FilePipe( const char* file) : file(file), Pipe(){};
  ~FilePipe() { fclose(fp); };
};
