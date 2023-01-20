//
// Created by zealot on 13.01.2023.
//


#include "narray/narray.h"
#include "profiling/time_profiling.h"


//30, 784
// 84, 1
int main(int argc, const char *argv[]) {
//    counting_mem_allocator<float>::create_mempool(28 * 28, 100000);// images
//    counting_mem_allocator<float>::create_mempool(28 * 28 * 30, 100); // weight
//    counting_mem_allocator<float>::create_mempool(10 * 30, 100);// weight
//    counting_mem_allocator<float>::create_mempool(30, 100);// biases
//    counting_mem_allocator<float>::create_mempool(10, 100000 + 100);// biases + labels
//    counting_mem_allocator<float>::create_mempool(1, 100);//scalar
    time_profiling::set_label("mempool");
    for (int i =0; i < 60000; i++) {
        narray<float> a = narray<float>({28 * 28});
    }
    time_profiling::measure("mempool");
    return 0;
}