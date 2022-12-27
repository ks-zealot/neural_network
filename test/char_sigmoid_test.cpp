//
// Created by zealot on 27.12.2022.
//


#include <vector>
#include <iostream>
#include "math/math.h"

int main(int argc, const char *argv[]) {
    std::vector<unsigned char> c = {0, 50, 100, 255};
    std::vector<float> res;
    char_to_float_conversion(c, res);
    std::cout << res.size() << std::endl;
}