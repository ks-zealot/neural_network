//
// Created by zealot on 13.12.2022.
//


#include <iostream>
#include "narray.h"

template<typename T>
narray<T>::narray() {
    this->mem_policy = new standart_policy<T>();
    allocator = std::allocator<T>();
}

template<typename T>
narray<T>::narray(narray<T> &&rhs) noexcept {
    sizes = rhs.sizes;
    mem_size = rhs.mem_size;
    allocator = rhs.allocator;
    mem = rhs.mem;
    mem_policy = rhs.mem_policy;
    stride_info = rhs.stride_info;
//    memcpy(mem, rhs.mem, sizeof(T) * rhs.mem_size);
}

template<typename T>
narray<T>::narray(narray<T> &out) {
    out = *this;
//    out.mem = out.allocator.allocate(out.mem_size);
//    out.mem = mem;
}


template<typename T>
narray<T>::narray(std::vector<int> sizes, T *mem, memory_policy<T> *policy, std::allocator<T> alloc) {
    this->mem_policy = policy;
    this->allocator = alloc;
    this->sizes = sizes;
    this->mem = mem;
    mem_size = 1;
    std::for_each(sizes.begin(), sizes.end(),
                  [this](int i) mutable {
                      mem_size *= i;
                  });
    std::vector<int> stride_info = sizes;
    std::reverse(stride_info.begin(), stride_info.end());
    for (int i = 0; i < stride_info.size(); i++) {
        stride_info[i] = pow(sizes[i], i);
    }
    this->stride_info = stride_info;
}

template<typename T>
narray<T>::narray(std::vector<int> sizes, std::vector<int> stride_info, T *mem, memory_policy<T> *policy,
                  std::allocator<T> alloc) {
    this->stride_info = stride_info;
    this->mem_policy = policy;
    this->allocator = alloc;
    this->sizes = sizes;
    this->mem = mem;
    mem_size = 1;
    std::for_each(sizes.begin(), sizes.end(),
                  [this](int i) mutable {
                      mem_size *= i;
                  });
}
// 3 x 2



template<typename T>
narray<T>::narray(std::vector<int> sizes, filler<T> &filler) {
    this->mem_policy = new standart_policy<T>();
    this->sizes = sizes;
    mem_size = 1;
    std::for_each(sizes.begin(), sizes.end(),
                  [this](int i) mutable {
                      mem_size *= i;
                  });
    std::vector<int> stride_info = sizes;
    std::reverse(stride_info.begin(), stride_info.end());
    for (int i = 0; i < stride_info.size(); i++) {
        stride_info[i] = pow(sizes[i], i);
    }
    this->stride_info = stride_info;
    mem = allocator.allocate(mem_size);
    filler.fill(mem, mem_size);
}


template<typename T>
narray<T>::~narray() {
    mem_policy->free(allocator, mem, mem_size);
    delete mem_policy;
}

//     (4, 5)          (5, 4)         (5, 5)
//    |1|2|3|4|5|     |1|2|3|4|    |1|2|3|4|5|
//    |1|2|3|4|5|     |1|2|3|4|    |1|2|3|4|5|
//    |1|2|3|4|5|   ⋅ |1|2|3|4| =  |1|2|3|4|5|
//    |1|2|3|4|5|     |1|2|3|4|    |1|2|3|4|5|
//                    |1|2|3|4|    |1|2|3|4|5|

//берем i-тую строчку и j-тый столбец, перемножаем и суммируем
//
template<typename T>
narray<T> narray<T>::dot_product(narray<T> other) {
    narray<T> transposed = other;

    if (sizes.size() > 2 || other.sizes.size() > 2) {
        throw new std::runtime_error("Dot product implement only for narray dim < 2");
    }
    if (sizes.front() != other.sizes.back()) {
        throw new std::runtime_error("narrays is not conform");
    }
    std::vector<int> new_sizes;
    new_sizes.push_back(sizes.front());
    new_sizes.push_back(other.sizes.back());
    std::allocator<T> _allocator;
    int new_mem_size = 1;
    std::for_each(new_sizes.begin(), new_sizes.end(),
                  [&new_mem_size](int i) mutable {
                      new_mem_size *= i;
                  });
    T *new_mem = _allocator.allocate(new_mem_size);
    narray res = narray<T>(new_sizes, new_mem, new standart_policy<T>(), _allocator);
    transposed.transpose();
    narray<T> ref = *this;
    int n = new_sizes.front();
    for (int i = 0; i < new_sizes.front(); i++) {
        for (int j = 0; j < new_sizes.back(); j++) {
            narray<T> row1 = ref[i];
            narray<T> row2 = transposed[j];
            for (auto &&[x, y]: _zip(row1, row2)) {
                res[i][j] += x * y;
            }
        }
    }
    return res;

}

template<typename T>
narray<T> &narray<T>::transpose(int axis1, int axis2) {
    std::iter_swap(sizes.begin() + axis1, sizes.begin() + axis2);
    std::iter_swap(stride_info.begin() + axis1, stride_info.begin() + axis2);
    return *this;
}

//| 0,0 | 0,1 | 0,2 |    | 0 | 1 |
//| 1,0 | 1,1 | 1,2 |   | 2 | 3 |
//| 2,0 | 2,1 | 2,2 |   | 2 | 3 |

//любое число в степени 0 дает 1
//любое число в степени 1 дает это число
template<typename T>
T *narray<T>::at(std::vector<int> coord) const {
    int pos = 0;
    std::reverse(coord.begin(), coord.end());
    for (int i = 0; i < coord.size(); i++) {
        pos += coord[i] * stride_info[i];
    }
    return mem + pos;
}


template
class narray<int>;

template
class narray<float>;