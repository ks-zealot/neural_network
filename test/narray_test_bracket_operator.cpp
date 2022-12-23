//
// Created by zealot on 16.12.2022.
//
#include <iostream>
#include "narray/narray.h"
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


int main(int argc, const char *argv[]) {
    narray<float> obj = narray<float>({3, 3}, random_filler<float>::GetInstance());
     narray<float> row = obj[0];
    print_matrix<float>(obj);
    std::cout << std::endl;
    narray<float>::iterator itr = row.begin();
    while (itr != row.end()) {
        std::cout << *itr << " ";
        ++itr;
    }
    std::vector<std::vector<float>> v1 = {{-0.513067, 0.544265,   0.683725},
                                          {0.0883649, -0.0245399, 0.661257}};
    narray<float> obj1 = narray<float>(v1);
    narray<float> row1 = obj1[1];
    return 0;
}