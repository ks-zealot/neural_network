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
    rhs.mem = nullptr;
    rhs.mem_policy = new subnarray_policy<T>();
//    memcpy(mem, rhs.mem, sizeof(T) * rhs.mem_size);
}

template<typename T>
narray<T>::narray(const narray<T> &out) {
    sizes = out.sizes;
    mem_size = out.mem_size;
    stride_info = out.stride_info;
    std::allocator<T> alloc;
    mem = alloc.allocate(out.mem_size);
    mem_policy = new standart_policy<T>();
    allocator = alloc;
    memcpy(mem, out.mem, sizeof(T) * out.mem_size);
//    out.mem = out.allocator.allocate(out.mem_size);
//    out.mem = mem;
}


template<typename T>
narray<T>::narray(T t, memory_policy<T> *policy ,
                  std::allocator<T> alloc) {
    this->mem_policy = policy;
    this->allocator = alloc;
    std::vector<int> stride_info;
    stride_info.push_back(1);
    mem_size = 1;
    mem = alloc.allocate(1);
    *mem = t;
    this->stride_info = stride_info;
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
    int idx = 0;
    std::for_each(coord.rbegin(), coord.rend(), [&pos, &idx, this](int i) mutable {
        pos += i * stride_info[idx];
        idx++;
    });

    return mem + pos;
}


template<typename T>
typename narray<T>::iterator narray<T>::insert(narray::iterator position, narray::value_type const &val) {
    int idx = std::distance(begin(), position);
    *(mem + idx) = *val;
    return position;
}


template
class narray<int>;

template
class narray<float>;