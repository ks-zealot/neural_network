#include <vector>
#include "math/math.h"

//
// Created by zealot on 25.01.2023.
//
int main(int argc, const char *argv[]) {
    std::vector<unsigned char> c = {0, 50, 100, 125, 75, 11, 23, 44,66, 1, 255};
    std::vector<double> res(10);
    char_to_double_conversion(c, res);
    for (double d : res) {
        std::cout << d << std::endl;
    }

}