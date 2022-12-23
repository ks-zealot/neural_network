#include "pipes/FilePipe.h"

#include <bits/types/FILE.h>

#include <cstdio>

#include "global.h"
#include "mempool/data/gzChunk.h"
#include "logging/log.h"

void FilePipe::writeInner(void* c) {
  if (fp == nullptr) {

    fp = fopen(file, "wb");
  }
    gzChunk* gzChunk = static_cast<struct gzChunk*>(c);
    info ("write {} data to {} file", gzChunk->size, file);

  fwrite(gzChunk->data, sizeof(char), gzChunk->size, fp);
  delete gzChunk;
}


void FilePipe::prepare(void* arg, ...) {

}

void FilePipe::close() {
  fclose(fp);
}
