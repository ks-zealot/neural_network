//
// Created by zealot on 09.01.2023.
//

#include "counting_mem_allocator.h"

template<typename T> counting_mem_data counting_mem_allocator<T>::data;
template<typename T> std::string counting_mem_allocator<T>::current_label = "";
template<typename T> std::unordered_map<std::string, counting_mem_data> counting_mem_allocator<T>::data_map;
template<typename T> std::unordered_map<std::size_t, T *> counting_mem_allocator<T>::mem_map;
template<typename T> std::unordered_map<std::size_t, int> counting_mem_allocator<T>::stat_map;
template<typename T> std::unordered_map<std::size_t, int> counting_mem_allocator<T>::ptr_map;

template class counting_mem_allocator<int>;
template class counting_mem_allocator<float>;
template class counting_mem_allocator<double>;