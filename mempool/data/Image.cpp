#include "mempool/data/Image.h"

#include "mempool/DynamicMempool.h"

pool<Image> Image::mainPool = pool<Image>(256);
PoolAllocator Image::ImagePoolAllocator = PoolAllocator(65536);
