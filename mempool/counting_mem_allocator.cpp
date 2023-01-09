//
// Created by zealot on 09.01.2023.
//

#include "counting_mem_allocator.h"

unsigned long counting_mem_allocator::mem_allocated = 0l;
unsigned long counting_mem_allocator::mem_deallocated = 0l;
unsigned long counting_mem_allocator::mem_call_allocate = 0l;
unsigned long counting_mem_allocator::mem_call_deallocate = 0l;