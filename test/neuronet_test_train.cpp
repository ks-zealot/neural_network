//
// Created by zealot on 29.12.2022.
//


#include <cassert>
#include "neural_network/Network.h"


void foo1();
int main(int argc, const char *argv[]) {
    assert (counting_mem_allocator::data.mem_allocated == 0);
    assert (counting_mem_allocator::data.mem_deallocated == 0);
    assert (counting_mem_allocator::data.mem_call_allocate == 0);
    assert (counting_mem_allocator::data.mem_call_deallocate == 0);
    foo1();
    counting_mem_allocator::print_profiling();
    assert (counting_mem_allocator::data.mem_allocated == counting_mem_allocator::data.mem_deallocated);
    assert (counting_mem_allocator::data.mem_call_allocate == counting_mem_allocator::data.mem_call_deallocate);
    return 0;
}

void foo1() {
    MNISTReader reader("", "");
    Network network({28 * 28, 30, 10}, reader);
    network.init();
    unsigned char *img = new unsigned char[28 * 28];
    unsigned char label;
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<char> distribution(0, 255);
    for (int i = 0; i < 28 * 28; i++) {
        img[i] = distribution(generator);
    }
    network.train(img, &label, 28 * 28, 1, 0, 1, 1);
    delete [] img;
}
