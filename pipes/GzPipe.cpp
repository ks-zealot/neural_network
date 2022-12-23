#include "pipes/GzPipe.h"

#include <zconf.h>
#include <zlib.h>

#include <iterator>
#include "logging/log.h"
#include "mempool/data/Chunk.h"
#include "mempool/data/gzChunk.h"

void GzPipe::writeInner(void* bytes) {
  info("GzPipe write chunk");
  next->eat(func(bytes));
}

void GzPipe::prepare(void* arg, ...) {
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;
  ret = inflateInit2(&strm, MAX_WBITS + 16);
  if (ret != Z_OK) throw -1;

}

void* GzPipe::deflate(void* bytes) {
  gzChunk* inChunk = static_cast<gzChunk*>(bytes);
  info("receive chunk with {} bytes ", inChunk->size);
  unsigned char out[1024];
  strm.avail_in = inChunk->size;
  if (strm.avail_in == 0) {
    return new Chunk();
  }
  strm.next_in = inChunk->data;
  strm.avail_out = 1024;
  strm.next_out = out;
  ret = inflate(&strm, Z_NO_FLUSH);
  info (" RET {}", ret);
  if (ret != Z_OK) {
    info ("MSG {}", strm.msg);
  }
  switch (ret) {
    case Z_NEED_DICT:
      info("NEED DICK");
      ret = Z_DATA_ERROR; /* and fall through */
    case Z_DATA_ERROR:
    case Z_MEM_ERROR:
      info("THROW 1");
      (void)inflateEnd(&strm);
      throw 1;
  }
  Chunk* chunk = new Chunk();
  std::copy(std::begin(out), std::end(out), std::begin(chunk->data));
  chunk->size = strm.avail_out;
  if (ret == Z_STREAM_END) {
  (void)inflateEnd(&strm);
  }
  delete inChunk;
  return chunk;
}
