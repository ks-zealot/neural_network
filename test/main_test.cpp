#include <iostream>
#include "../narray/narray.h"

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
    narray<int> obj = narray<int>({2, 2}, random_filler<int>::GetInstance());
    print_matrix<int>(obj);
    return 0;
}