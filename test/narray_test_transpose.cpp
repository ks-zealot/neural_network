//
// Created by zealot on 15.12.2022.
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
    print_matrix<float>(obj);
    std::cout << std::endl;
    narray<float> transposed = obj.transpose();
    print_matrix<float>(transposed);
    return 0;
}