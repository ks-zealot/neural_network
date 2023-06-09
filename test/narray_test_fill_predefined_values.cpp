#include <iostream>
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
    std::vector<std::vector<float>> v1 = {{-0.513067, 0.544265,   0.683725},
                                          {0.0883649, -0.0245399, 0.661257}};
    std::vector<std::vector<float>> v2 = {{-0.74331, -1.00973},
                                          {0.73697,  2.04419},
                                          {0.064087, 1.15236}};
    narray<float> obj1 = narray<float>(v1);
    print_matrix<float>(obj1);
    std::cout << std::endl;
    narray<float> obj2 = narray<float>(v2);
    print_matrix<float>(obj2);
    std::cout << std::endl;

    narray<float> obj3 = narray<float>(v2);
    obj3.transpose();
    print_matrix<float>(obj3);
    std::cout << std::endl;
    narray<float> dot_product = obj1.dot_product(obj2);
    print_matrix<float>(dot_product);
    return 0;
}
