//
// Created by zealot on 23.12.2022.
//
#include <iostream>
#include "math/math.h"
#include "narray/narray.h"

//
// Created by zealot on 16.12.2022.
//
// Created by zealot on 16.12.2022.
//
template<typename T>
void print_matrix(narray<T> &array) {
    for (int i = 0; i < array.get_sizes().front(); i++) {
        for (int j = 0; j < array.get_sizes().back(); j++) {
            T t = *(array.at({i, j}));
            std::cout << " " << t;
        }
        std::cout << std::endl;
    }
};

int main(int argc, const char *argv[]) {

    narray<float> obj1 = narray<float>({2, 2}, random_filler<float>::GetInstance());
    print_matrix<float>(obj1);
    sigmoid<float, narray<float>>(obj1);
    print_matrix<float>(obj1);
    return 0;
}
//template <class T> class col_iterator;
//
//template<class T, int N>
//class Collection
//{
//    T data[N] = { 0 };
//public:
//    col_iterator<T> begin()
//    {
//        return col_iterator<T>(data);
//    }
//    col_iterator<T> end()
//    {
//        return col_iterator<T>(data + N);
//    }
//};
//
//template <class T>
//class col_iterator
//{
//public:
//    T* data;
//    using iterator_category = std::forward_iterator_tag;
//    using value_type = T;
//    using difference_type = size_t;
//    using pointer = T*;
//    using reference = T&;
//
//    col_iterator(){}
//    col_iterator(pointer _data) : data(_data) {}
//
//    reference operator*() { return *data; }
//    bool operator!=(const col_iterator& other)
//    {
//        return data != other.data;
//    }
//    col_iterator<T>& operator++()
//    {
//        data += 1;
//        return *this;
//    }
//    col_iterator<T> operator++(int)
//    {
//        return col_iterator<T>(data + 1);
//    }
//};
//
//int main(void)
//{
//    Collection<int,10> test;
//
//    std::fill(test.begin(), test.end(), 2);
//
//    std::transform(test.begin(), test.end(), test.begin(), [](int i)
//    {
//        return i * i;
//    });
//
//    for(auto t : test)
//        std::cout << t << std::endl;
//}