//
// Created by zealot on 13.01.2023.
//


#include "narray/narray.h"
#include "math/math.h"
#include "profiling/time_profiling.h"
#include <cblas.h>


//30, 784
// 84, 1
int main(int argc, const char *argv[]) {
    std::vector<double> v ={0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0.};
    narray<double> a = narray<double>(v);
    int max = max_arg<narray<double>>(a);
    assert(max == 2);

    std::vector<double> v1 ={0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0.};
    narray<double> a1 = narray<double>(v1);
    int max1 = max_arg<narray<double>>(a1);
    assert(max1 == 7);
    return 0;
}