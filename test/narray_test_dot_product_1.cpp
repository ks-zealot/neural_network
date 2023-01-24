//
// Created by zealot on 28.12.2022.
//


#include <iostream>
#include "narray/narray.h"
#include "math/math.h"


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
//0.826293 2.41854 -0.0413897 0.622617
int main(int argc, const char *argv[]) {
    std::vector<std::vector<float>> v1 = {{-0.513067, 0.544265,   0.683725},
                                          {0.0883649, -0.0245399, 0.661257}};
    std::vector<std::vector<float>> v2 = {{-0.74331, -1.00973},
                                          {0.73697,  2.04419},
                                          {0.064087, 1.15236}};
//    std::vector<std::vector<float>> v2 = {{-0.74331, -1.00973,  0.73697},
//                                          {2.04419,   0.064087, 1.15236}};
    narray<float> a = narray<float>(v1);
    narray<float> b = narray<float>(v2);
    narray<float> dp = dot_product<narray<float>, float>(a, b);
    std::allocator<float> _allocator;
    float *new_mem = dp.get_mem();
//    cblas_sgemm(CblasRowMajor, CblasNoTrans,CblasNoTrans,A_R, B_C,A_C,1.0, A,A_C, B, B_C,0.0, C,   B_C  );
    assert(new_mem[0] == 0.826292634f);
    assert(new_mem[1] = 2.41853738f);
    assert(new_mem[2] = -0.0413897f);
    assert(new_mem[3] = 0.622617185f);
    return 0;
}
