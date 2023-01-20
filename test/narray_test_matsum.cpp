//
// Created by zealot on 13.01.2023.
//


#include "narray/narray.h"
#include "math/math.h"
#include "profiling/time_profiling.h"
#include <cblas.h>

void matsum(float *a, float *b, int d1) {
    for (int i = 0; i < d1; i++) {
        a[i] + b[i];
    }
}

void matsum1(float *a, float *b, int d1) {
    cblas_saxpby(d1, 1.0, a, 0, 1.0, b, 0);
}

//30, 784
// 84, 1
int main(int argc, const char *argv[]) {
    narray<float> a = narray<float>({1000000, 1}, random_filler<float>::GetInstance());
    narray<float> b = narray<float>({1000000, 1},
                                    random_filler<float>::GetInstance());
    time_profiling::set_label("matsum1");
    matsum(a.get_mem(), b.get_mem(), 1000000);
    time_profiling::measure("matsum1");
    time_profiling::set_label("matsum2");
    matsum1(a.get_mem(), b.get_mem(), 1000000);
    time_profiling::measure("matsum2");
    return 0;
}