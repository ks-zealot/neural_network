//
// Created by zealot on 13.01.2023.
//


#include "narray/narray.h"
#include "math/math.h"
#include "profiling/time_profiling.h"

int main(int argc, const char *argv[]) {
    narray<float> obj1 = narray<float>({30, 1}, random_filler<float>::GetInstance());
    narray<float> obj2 = narray<float>({784, 1},
                                       random_filler<float>::GetInstance());//todo если поменять местами цифры то вылетает сегфолт
    obj2.transpose();
    float *res = std::allocator<float>().allocate(30 * 784);
    time_profiling::set_label("matmul");
    mmult(obj1.at({0, 0}), 30, 1, obj2.at({0, 0}), 1, 784, res);//0.000287565
//    dot_product<narray<float>, float>(obj1, obj2); // 0.000933408
    time_profiling::measure("matmul");
    std::allocator<float>().deallocate(res, 1000 * 1000);
    return 0;
}