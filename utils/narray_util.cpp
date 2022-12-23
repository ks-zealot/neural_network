//
// Created by zealot on 14.12.2022.
//
#include <tuple>
#include "narray_util.h"

void throw_matrix_noneq_error(std::vector<int> sizes, std::vector<int> other_sizes) {
    std::string exp_message("Impossible to sum narray with different dimensions: ");
    std::stringstream ss;
    ss << exp_message;
    for (auto it = sizes.begin(); it != sizes.end(); it++) {
        if (it != sizes.begin()) {
            ss << ", ";
        }
        ss << *it;
    }
    ss << " and ";
    for (auto it = other_sizes.begin(); it != other_sizes.end(); it++) {
        if (it != sizes.begin()) {
            ss << ", ";
        }
        ss << *it;
    }
    throw new std::runtime_error(ss.str());
}

//template< typename Iterator, typename ... Iterators, class ... Outputs>
//auto &zip(Iterator begin,
//                     Iterator end,
//                     Iterators ... iterators) {
//    std::vector<std::tuple<Outputs...>> v;
//    for (; begin != end; ++begin, advance_all(iterators...)) {
//        v.push_back(std::make_tuple(*begin, *(iterators)...));;
//    }
////could also make this a tuple
//
//    return v.begin();
//}