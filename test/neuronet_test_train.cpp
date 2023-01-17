//
// Created by zealot on 29.12.2022.
//


#include <cassert>
#include "neural_network/Network.h"


void foo1();

void foo2();


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
    unsigned char *img = new unsigned char[28 * 28 * 60000];
    unsigned char *labels = new unsigned char[60000];;
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<char> distribution(0, 255);
    std::uniform_int_distribution<char> distribution1(0, 9);
    for (int i = 0; i < 28 * 28 * 60000; i++) {
        img[i] = distribution(generator);
    }
    for (int i = 0; i < 60000; i++) {
        labels[i] = distribution1(generator);
    }
//    counting_mem_allocator::put_label("train");
    network.train(img, labels, 28 * 28, 40000, 20000, 1, 10);
//    counting_mem_allocator::remove_label("train");
    delete[] img;
    delete[] labels;
}

void foo2() {
//    std::vector<narray<float>> container = std::vector<narray<float>>(3);
//    {
//        for (int i = 0; i < 3; i++) {
//            narray<float> _img = narray<float>({3, 3});
//            container[i] = _img;
//        }
//    }
    narray<float> __a  = narray<float>({3, 3});
    narray<float> __b    = narray<float>({3, 3});
    narray<float> __tmp = _GLIBCXX_MOVE(__a);
    __a = _GLIBCXX_MOVE(__b);
//    __b = _GLIBCXX_MOVE(__tmp);
std::cout << std::endl;
//    std::random_shuffle(container.begin(), container.end());
}
