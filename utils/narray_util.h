//
// Created by zealot on 13.12.2022.
//

#include <vector>
#include <string>
#include <sstream>
#include "zipper.h"

#ifndef NEURONET_NARRAY_UTIL_H
#define NEURONET_NARRAY_UTIL_H

void throw_matrix_noneq_error(std::vector<int> sizes, std::vector<int> other_sizes);

template<typename Iterator>
void advance_all(Iterator &iterator) {
    ++iterator;
}

template<typename Iterator, typename ... Iterators>
void advance_all(Iterator &iterator, Iterators &... iterators) {
    ++iterator;
    advance_all(iterators...);
}


//template<  typename Iterator, typename ... Iterators, typename... Outputs>
//auto zip(Iterator begin,
//              Iterator end,
//              Iterators ... iterators) {
//    std::vector<std::tuple<Outputs...>> v;
//    for (; begin != end; ++begin, advance_all(iterators...)) {
//        v.push_back(std::make_tuple(*begin, *(iterators)...));;
//    }
////could also make this a tuple
//
//    return v.begin();
//}

template<typename T, typename Iterator>
std::vector<std::tuple<T, T>> zip(Iterator begin,
                                  Iterator end,
                                  Iterator second) {
    std::vector<std::tuple<T, T>> v;
    for (; begin != end; ++begin, advance_all(second)) {
        v.push_back(std::make_tuple(*begin, *(second)));;
    }
//could also make this a tuple

    return v;
}

template<typename... T>
std::tuple<T...> &create_tuple(T... t) {
    return std::make_tuple<T...>(t...);
}



template <typename ... T>
auto _zip(T && ... t) {
    return zipper<T ...>{std::forward<T>(t)...};
}
#endif