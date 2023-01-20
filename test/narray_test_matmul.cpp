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
    narray<float> a = narray<float>({30, 784}, random_filler<float>::GetInstance());
    narray<float> b = narray<float>({784, 1},
                                       random_filler<float>::GetInstance());//todo если поменять местами цифры то вылетает сегфолт
    float *res = std::allocator<float>().allocate(1 * 30);
//    obj2 = obj2.transpose();
    time_profiling::set_label("matmul");

//    mmult(obj1.at({0, 0}), 30, 784, obj2.at({0, 0}), 784, 1, res);// 0.000207698
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
//     cblas_saxpy();
//    cblas_sgemm(CblasRowMajor,// 0.096858185
//                obj1.is_transposed() ? CblasTrans : CblasNoTrans,
//                obj2.is_transposed() ? CblasTrans : CblasNoTrans,
//                obj1.get_sizes().front(),
//                obj2.get_sizes().back(),
//                obj1.get_sizes().back(),
//                1.0,
//                obj1.at({0, 0}),
//                obj1.get_sizes().front(),
//                obj2.at({0, 0}),
//                obj1.get_sizes().back(),
//                0.0,
//                res,
//                obj1.get_sizes().front());
    dot_product<narray<float>, float>(a, b); // 0.933408
    time_profiling::measure("matmul");
    std::allocator<float>().deallocate(res, 1 * 30);
    return 0;
}