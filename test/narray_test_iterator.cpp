//
// Created by zealot on 16.12.2022.
//

#include <iostream>
#include "narray/narray.h"


int main(int argc, const char *argv[]) {
    narray<float> obj = narray<float>({3, 3}, random_filler<float>::GetInstance());
    narray<float>::iterator itr = obj.begin();
    int idx = 0;
    while (itr != obj.end()) {
            std::cout << *itr << " ";
            ++itr;
            idx++;
            if (idx == 3) {
                std::cout << std::endl;
                idx = 0;
            }
    }
    return 0;
}