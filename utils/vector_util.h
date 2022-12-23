//
// Created by zealot on 08.12.2022.
//
#include <vector>

#ifndef NEURONET_VECTOR_UTIL_H
#define NEURONET_VECTOR_UTIL_H

#endif //NEURONET_VECTOR_UTIL_H

template<typename T>
std::vector<T> remove_first(std::vector<T> in) {
    in.erase(in.begin());
    return in;
}

template<typename T>
std::vector<T> remove_last(std::vector<T> in) {
    in.erase(in.end() - 1);
    return in;
}

template<typename T>
std::vector<std::vector<T>> zip(std::vector<T> in, std::vector<T> in1) {
    std::vector<std::vector<T>> res;
    res.reserve(in.size() + in1.size());
    res.push_back(in);
    res.push_back(in1);
    return res;
}

template<typename T>
std::vector<std::vector<T>> init_zero_vector(std::vector<std::vector<T>>& in) {
    std::vector<std::vector<T>> res = in;
    std::for_each(res.begin(), res.end(),
                  [](std::vector<T> &vec) {
                      std::for_each(vec.begin(), vec.end(),
                                    [](T &n) { n = 0.; });
                  }
    );
    return res;
}


template<typename Vector>
auto split_vector(const Vector &v, unsigned number_lines) {
    using Iterator = typename Vector::const_iterator;
    std::vector<Vector> rtn;
    Iterator it = v.cbegin();
    const Iterator end = v.cend();

    while (it != end) {
        Vector v;
        std::back_insert_iterator<Vector> inserter(v);
        const auto num_to_copy = std::min(static_cast<unsigned>(
                                                  std::distance(it, end)), number_lines);
        std::copy(it, it + num_to_copy, inserter);
        rtn.push_back(std::move(v));
        std::advance(it, num_to_copy);
    }

    return rtn;
}
