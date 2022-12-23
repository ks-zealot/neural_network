//
// Created by zealot on 20.12.2022.
//
#include <iostream>
#include <cassert>
#include "narray/narray.h"

//
// Created by zealot on 16.12.2022.
//
// Created by zealot on 16.12.2022.
//
template<typename T>
void print_matrix(narray<T> &array) {
    for (int i = 0; i < array.get_sizes().front(); i++) {
        for (int j = 0; j < array.get_sizes().back(); j++) {
            T t = *(array.at({i, j}));
            std::cout << " " << t;
        }
        std::cout << std::endl;
    }
};
//-0.513067 0.544265 0.683725
//0.0883649 -0.0245399 0.661257
//
//-0.74331 -1.00973
//0.73697 2.04419
//0.064087 1.15236
//
//0.826293 2.41854
//-0.0413897 0.622618

int main(int argc, const char *argv[]) {
    std::vector<int> a = std::vector<int>{1, 2, 3, 4, 5, 6};
    std::vector<int> b = std::vector<int>{1, 2, 3, 4, 5, 6, 7};
    std::vector<int> c = std::vector<int>{0, 0, 0, 0, 0};
    std::vector<int> const & d = b;

    for (auto && [x, y, z] : _zip(a, d, c)) {
        z = x + y;
    }

    auto expected = std::vector<int>{2, 4, 6, 8, 10};
    assert(c == expected);
    return 0;
}
