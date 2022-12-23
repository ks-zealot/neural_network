#include <iostream>
#include "narray/narray.h"

//
// Created by zealot on 14.12.2022.
//
template<typename T>
void print_matrix(narray<T> &array) {
    for (int i = 0; i < (*array.get_sizes().begin()); i++) {
        for (int j = 0; j < (*array.get_sizes().begin()); j++) {
            T t = *(array.at({i, j}));
            std::cout << " " << t;
        }
        std::cout << std::endl;
    }
};

int main(int argc, const char *argv[])  {
    narray<float> obj = narray<float>({2, 2}, random_filler<float>::GetInstance());
    print_matrix<float>(obj);
    return 0;
}