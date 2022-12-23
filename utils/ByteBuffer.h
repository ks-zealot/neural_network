#pragma once

struct ByteBuffer {
  char* bytes;
  int size;
  ByteBuffer(char* bytes, int size) : bytes(bytes), size(size) {}
};
