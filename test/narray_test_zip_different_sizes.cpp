#include "narray/narray.h"

//
// Created by zealot on 09.01.2023.
//
int main(int argc, const char *argv[]) {
    std::vector<float> v1 = {-0.513067, 0.544265, 0.683725};
    narray<float> obj1 = narray<float>(v1);
    std::vector<float> v2 = {-0.513067, 0.544265, 0.683725, 0.544265};
    narray<float> obj2 = narray<float>(v2);
    auto t = _zip(obj1, obj2);
    t.begin();
    return 0;
}
