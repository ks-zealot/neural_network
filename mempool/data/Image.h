#pragma once
#include "mempool/DynamicMempool.h"
#include "mempool/Mempool.h"
struct Image {
 private:
  static PoolAllocator ImagePoolAllocator;
  static pool<Image> mainPool;

  unsigned int Width;
  unsigned int Height;

 public:
  unsigned char* data;
  Image() {}
  Image(unsigned int Width, unsigned int Height)
      : Width(Width),
        Height(Height),
        data((unsigned char*)ImagePoolAllocator.allocate(Width * Height)) {}

  void* operator new(size_t size) { return mainPool.alloc(); }

  void operator delete(void* t) {
    Image* image = static_cast<Image*>(t);
    ImagePoolAllocator.deallocate(image->data, image->Width * image->Height);
    mainPool.free(static_cast<Image*>(t));
  }
};
