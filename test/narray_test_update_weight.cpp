//
// Created by zealot on 25.01.2023.
//


#include "narray/narray.h"

int main(int argc, const char *argv[]) {
    std::vector<double> v = {1., 2., 3., 4.};
    std::vector<double> v1 = {-1., -2., -3., -4.};
    narray<double> obj = narray<double>(v);
    narray<double> obj1 = narray<double>(v1);
    narray<double> obj2 = obj * 0.3;
    narray<double> obj3 = obj1 - obj * 0.3;
    return 0;
}