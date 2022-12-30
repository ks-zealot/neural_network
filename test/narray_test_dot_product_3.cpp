#include <cassert>
#include "narray/narray.h"
#include "math/math.h"

//
// Created by zealot on 30.12.2022.
//
int main(int argc, const char *argv[]) {
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {3, 4};
    const narray<int> obj1 = narray<int>(v1, new standart_policy<int>(), std::allocator<int>());
    const narray<int> obj2 = narray<int>(v2, new standart_policy<int>(), std::allocator<int>());
    narray<int> dp = dot_product<narray<int>, int>(obj1, obj2);
    assert(dp == 11);
    return 0;
}
