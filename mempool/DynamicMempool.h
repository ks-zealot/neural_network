#pragma once
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

/**
 * A chunk within a larger block.
 */
struct MemChunk {
  /**
   * When a chunk is free, the `next` contains the
   * address of the next chunk in a list.
   *
   * When it's allocated, this space is used by
   * the user.
   */
  MemChunk *next;
};

/**
 * The allocator class.
 *
 * Features:
 *
 *   - Parametrized by number of chunks per block
 *   - Keeps track of the allocation pointer
 *   - Bump-allocates chunks
 *   - Requests a new larger block when needed
 *
 */
class PoolAllocator {
 public:
  PoolAllocator(size_t chunksPerBlock) : mChunksPerBlock(chunksPerBlock) {}

  void *allocate(size_t size);
  void deallocate(void *ptr, size_t size);

 private:
  /**
   * Number of chunks per larger block.
   */
  size_t mChunksPerBlock;

  /**
   * Allocation pointer.
   */
  MemChunk *mAlloc = nullptr;

  /**
   * Allocates a larger block (pool) for chunks.
   */
  MemChunk *allocateBlock(size_t chunkSize);
};
