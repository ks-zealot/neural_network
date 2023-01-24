//
// Created by zealot on 24.01.2023.
//

#include <vector>
#include "narray/narray.h"

int main(int argc, const char *argv[]) {
    std::vector<float> v1 = {-0.513067, 0.544265, 0.683725,
                             0.0883649, -0.0245399, 0.661257};
    std::vector<float> v2 = {-0.123067, 0.444265, 0.65625,
                             0.5883649, -0.02565399, 0.4441257};
    narray<float> nw = narray<float>(v1);
    narray<float> w = narray<float>(v2);
    float eta = 3.0f;
    int size = 10;
    narray<float> res = w -  nw * (eta / size);
    for (float f: res) {
        std::cout << f << std::endl;
    }
    return 0;
}
