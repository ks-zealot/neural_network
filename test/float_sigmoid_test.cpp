//
// Created by zealot on 27.12.2022.
//


#include <vector>
#include <iostream>
#include "narray/narray.h"
#include "math/math.h"

int main(int argc, const char *argv[]) {
    std::vector<float> c = {0., 2.5, 0.5, 0.01};
    for (float f: sigmoid<float, std::vector<float>>(c)) {
        std::cout << f << std::endl;
    }
    std::cout << std::endl;
    for (float f: sigmoid_prime<float, std::vector<float>>(c)) {
        std::cout << f << std::endl;
    }
    std::cout << std::endl;
    std::vector<float> f1 = {0.5, 2., 4};
    std::vector<float> f2 = {0.0, 0.0, 1};
    narray<float> a = narray<float>(f1);
    narray<float> x = narray<float>(f2);
    for (float f: cost_derivative<narray<float> >(a, x)) {
        std::cout << f << std::endl;
    }
}