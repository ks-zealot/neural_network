#pragma once
#include "logging/log.h"
#include <memory>
template <typename T>
struct pool {
  std::mutex m;
  union pool_item {
   public:
    using StorageType = char[sizeof(T)];
    pool_item* next = 0 ;
    StorageType Datum;
    pool_item* getNext() const { return next; }

    void setNext(pool_item* n) { next = n; }

    T* getStorage() { return reinterpret_cast<T*>(Datum); }

    static pool_item* storageToItem(T* t) {
      return reinterpret_cast<pool_item*>(t);
    }
  };
  struct pool_arena {
   public:
    std::unique_ptr<pool_item[]> storage;
    std::unique_ptr<pool_arena> next;

    pool_arena(size_t size) : storage(new pool_item[size]) {
      for (size_t i = 1; i < size; i++) {
        storage[i - 1].setNext(&storage[i]);
      }
      storage[size - 1].setNext(nullptr);
    }

    pool_item* getStorage() const { return storage.get(); }

    void setNext(std::unique_ptr<pool_arena>&& n) { next.reset(n.release()); }
  };

 public:
  size_t arena_size;
  std::unique_ptr<pool_arena> arena;
  pool_item* free_list = 0;
  pool(size_t arena_size)
      : arena_size(arena_size),
        arena(new pool_arena(arena_size)),
        free_list(arena->getStorage()){};
  // Allocates an object in the current arena.
  template <typename... Args>
  T* alloc(Args&&... args) {
    info("alloc data ");
    if (free_list == nullptr) {
      m.lock();
 if (free_list == nullptr) {
      info("free list is null, create new");
      // If the current arena is full, const_reverse_iteratore a new one.
      std::unique_ptr<pool_arena> new_arena(new pool_arena(arena_size));
      // Link the new arena to the current one.
      new_arena->setNext(std::move(arena));
      // Make the new arena the current one.
      arena.reset(new_arena.release());
      // Update the free_list with the storage of the just created arena.
      free_list = arena->getStorage();
      m.unlock();
    }
    }
info("get storage and return memory");
    // Get the first free item.
    pool_item* current_item = free_list;
    // Update the free list to the next free item.
    free_list = current_item->getNext();

    // Get the storage for T.
    T* result = current_item->getStorage();
    // Construct the object in the obtained storage.
    ::new (result) T(std::forward<Args>(args)...);
    return result;
  }

  void free(T* t) {
    info ("free data");
    // Destroy the object.
    t->T::~T();

    // Convert this pointer to T to its enclosing pointer of an item of the
    // arena.
    pool_item* current_item = pool_item::storageToItem(t);

    // Add the item at the beginning of the free list.
    current_item->setNext(free_list);
    free_list = current_item;
  }
};
