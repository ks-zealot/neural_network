#include <cassert>
#include <iostream>
#include "narray/narray.h"
#include "math/math.h"

//
// Created by zealot on 30.12.2022.
//
template<typename T>
void print_matrix(narray<T> &array) {
    for (int i = 0; i < array.get_sizes().front(); i++) {
            T t = *(array.at({i}));
            std::cout << " " << t;
    }
};


int main(int argc, const char *argv[]) {
    const narray<float> obj1 = narray<float>({30, 28 * 28} , random_filler<float>::GetInstance());
    const narray<float> obj2 = narray<float>({28 * 28}, random_filler<float>::GetInstance());
    narray<float> dp = dot_product<narray<float>, float>(obj1, obj2);
    print_matrix(dp);
    return 0;
}
