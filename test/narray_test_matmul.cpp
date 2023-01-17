//
// Created by zealot on 13.01.2023.
//


#include "narray/narray.h"
#include "math/math.h"
#include "profiling/time_profiling.h"

int main(int argc, const char *argv[]) {
    narray<float> obj1 = narray<float>({1000, 1000}, random_filler<float>::GetInstance());
    narray<float> obj2 = narray<float>({1000, 1000},
                                       random_filler<float>::GetInstance());//todo если поменять местами цифры то вылетает сегфолт
    obj2.transpose();
    float *res = std::allocator<float>().allocate(1000 * 1000);
    time_profiling::set_label("matmul");
//    mmult(obj1.at({0, 0}), 30, 1, obj2.at({0, 0}), 1, 784, res);//0.000339867
    dot_product<narray<float>, float>(obj1, obj2); // 0.933408
    time_profiling::measure("matmul");
    std::allocator<float>().deallocate(res, 1000 * 1000);
    return 0;
}