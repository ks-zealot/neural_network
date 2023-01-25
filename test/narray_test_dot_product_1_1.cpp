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
//[[ 0.33569195 -0.22602878]
//[ 0.44642273  0.94106807]]
int main(int argc, const char *argv[]) {
    std::vector<std::vector<double>> v1 = {{-0.513067, 0.544265,   0.683725},
                                          {0.0883649, -0.0245399, 0.661257}};
    std::vector<std::vector<double>> v2 = {{-0.74331, -1.00973,  0.73697},
                                           {  2.04419, 0.064087, 1.15236}};
    narray<double> a = narray<double>(v1);
    narray<double> b = narray<double>(v2);
    narray<double> dp = dot_product<narray<double>, double>(a, b.transpose());
    std::allocator<double> _allocator;
    double *new_mem = dp.get_mem();
    assert(new_mem[0] == 0.33569194657000007);
    assert(new_mem[1] == -0.22602877867499993);
    assert(new_mem[2] == 0.44642273069799998);
    assert(new_mem[3] == 0.94106807287970007);
    return 0;
}
