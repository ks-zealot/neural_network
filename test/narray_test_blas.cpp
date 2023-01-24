//
// Created by zealot on 28.12.2022.
//


#include <iostream>
#include "narray/narray.h"
#include "math/math.h"




int main(int argc, const char *argv[]) {
    std::vector<narray<float>> biases;
    std::vector<narray<float>> weights;
    biases.push_back(narray<float>(std::vector({30, 1}), random_filler<float>::GetInstance()));
    biases.push_back(narray<float>(std::vector({10, 1}), random_filler<float>::GetInstance()));
    weights.push_back(narray<float>(std::vector({30, 784}), random_filler<float>::GetInstance()));
    weights.push_back(narray<float>(std::vector({10, 30}), random_filler<float>::GetInstance()));
    narray<float> activation = narray<float>({784, 1});
    for (auto &&[b, w]: _zip(biases, weights)) {
        narray<float> z = dot_product<narray<float>, float>(w, activation) + b;
        activation = sigmoid<float, narray<float>>(z);
    }
    return 0;
}
