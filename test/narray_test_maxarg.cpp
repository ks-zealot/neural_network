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
    narray<float> a = narray<float>({10, 1}, random_filler<float>::GetInstance());
    time_profiling::set_label("maxsum1");
    max_arg(a);
    time_profiling::measure("maxsum1");
    time_profiling::set_label("maxsum2");
    cblas_isamax(1000, a.get_mem(), 0);
    time_profiling::measure("maxsum2");
    return 0;
}