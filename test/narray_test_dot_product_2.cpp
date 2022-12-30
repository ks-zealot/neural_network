#include <cassert>
#include "narray/narray.h"
#include "math/math.h"

//
// Created by zealot on 30.12.2022.
//
int main(int argc, const char *argv[]) {

    const narray<int> obj1 = narray<int>(3);
    const  narray<int> obj2 = narray<int>(4);
    narray<int> dp = dot_product<narray<int>, int>(obj1, obj2);
    assert(dp == 12);
    return 0;
}
