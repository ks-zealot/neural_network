//
// Created by zealot on 28.12.2022.
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

int main(int argc, const char *argv[])  {
  const  narray<int> & obj = narray<int>({2, 2}, random_filler<int>::GetInstance());
//    print_matrix<int>(obj);
//    std::cout << std::endl;
    narray<int> obj1 = narray<int>(obj);
    print_matrix<int>(obj1);
    return 0;
}