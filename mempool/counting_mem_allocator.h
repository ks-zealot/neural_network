//
// Created by zealot on 09.01.2023.
//

#ifndef NEURONET_COUNTING_MEM_ALLOCATOR_H
#define NEURONET_COUNTING_MEM_ALLOCATOR_H

#include <memory>
#include <cstdio>

class counting_mem_allocator {
public:

    template<typename T>
    static T *allocate(std::allocator<T>& allocator, size_t size) {
        mem_allocated += size;
        mem_call_allocate++;
        return allocator.allocate(size);
    }

    template<typename T>
    static void deallocate(std::allocator<T>& allocator, T *mem, size_t size) {
        mem_deallocated += size;
        mem_call_deallocate++;
        allocator.deallocate(mem, size);
    }

    static unsigned long mem_allocated;
    static unsigned long mem_deallocated;
    static unsigned long mem_call_allocate;
    static unsigned long mem_call_deallocate;
};

#endif //NEURONET_COUNTING_MEM_ALLOCATOR_H
