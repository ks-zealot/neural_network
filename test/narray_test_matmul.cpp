//
// Created by zealot on 13.01.2023.
//


#include "narray/narray.h"
#include "math/math.h"
#include "profiling/time_profiling.h"
#include <cblas.h>


int main(int argc, const char *argv[]) {
    narray<float> obj1 = narray<float>({1000, 1000}, random_filler<float>::GetInstance());
    narray<float> obj2 = narray<float>({1000, 1000},
                                       random_filler<float>::GetInstance());//todo если поменять местами цифры то вылетает сегфолт
    float *res = std::allocator<float>().allocate(1000 * 1000);
    time_profiling::set_label("matmul");
//    mmult(obj1.at({0, 0}), 1000, 1000, obj2.at({0, 0}), 1000,1000, res);//9.314379909
    /**
     * CblasColMajor - констата
     * CblasNoTrans - мы уже транспонировали матрицу
     *  следующие три числа размероность матриц
     *  константа, равна 1
     *  ссылка на первый массив
     *  длина первого измерения первого массива
     *  ссыла на второй массив
     *  длина первого измерения второго массива
     *  константа, ноль
     *  ссылка на результирующий массив
     *  длина первого измерения третьего массива
     */
    cblas_sgemm(CblasColMajor,// 0.186824252
                CblasNoTrans,
                CblasNoTrans,
                obj1.get_sizes().front(),
                obj2.get_sizes().back(),
                obj1.get_sizes().back(),
                1.0,
                obj1.at({0, 0}),
                obj1.get_sizes().front(),
                obj2.at({0, 0}),
                obj1.get_sizes().back(),
                0.0,
                res,
                obj1.get_sizes().front());
//    dot_product<narray<float>, float>(obj1, obj2); // 0.933408
    time_profiling::measure("matmul");
    std::allocator<float>().deallocate(res, 1000 * 1000);
    return 0;
}