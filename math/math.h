//
// Created by zealot on 08.12.2022.
//
#include <algorithm>
#include <random>
#include <cmath>
#include <vector>
#include <numeric>

#ifndef NEURONET_MATH_H
#define NEURONET_MATH_H

template<typename T>
T sigmoid(T z) {
    return 1.f / (1.f + exp(-z));
}

template<typename T>
T sigmoid_prime(T z) {
    return sigmoid(z) * (1 - sigmoid(z));
}


template<typename T, typename Container>
Container sigmoid(const Container &z) {
    Container c = z;
    std::transform(z.begin(), z.end(),
                   c.begin(),
                   [](T t) { return sigmoid(t); });
    return c;
}

template<typename T, typename Container>
Container sigmoid_prime(const Container &z) {
    Container c = z;
    std::transform(z.begin(), z.end(),
                   c.begin(),
                   [](T t) { return sigmoid_prime(t); });
    return c;
}

void char_to_float_conversion(const std::vector<unsigned char> &z, std::vector<float> &res) {
    std::transform(z.begin(), z.end(), res.begin(), [](unsigned char t) { return ((float) t / 255.f); });
}

std::vector<float> vectorize(unsigned char z, int max) {
    std::vector<float> res(max);
    res[z] = 1.0f;
    return res;
}

template<typename Iterator1, typename Iterator2, typename T>
void vectorize(Iterator1 &__input1, Iterator2 &__input2, int max) {
    std::for_each(__input1.begin(), __input1.end(),
                  [&__input2, &max](T t) { __input2.push_back(vectorize(t, max)); });
}


template<typename T>
std::vector<T> cost_derivative(std::vector<T> output_activations, std::vector<T> y) {
    std::vector<T> res;
    res.reserve(output_activations.size());
    std::transform(output_activations.begin(), output_activations.end(), y.begin(), res.begin(), std::minus<int>());
    return res;
}


template<typename T, typename T1>
std::vector<T> plus(std::vector<T> vector, T1 val) {
    std::transform(vector.begin(), vector.end(), vector.begin(), bind2nd(std::plus<T1>(), val));
    return vector;
}

template<typename T>
std::vector<T> mul(std::vector<T> vector1, std::vector<T> vector2) {
    std::vector<T> res;
    res.reserve(vector1.size());
    for (int i = 0; i < vector1.size(); i++) {
        res[i] = vector1[i] * vector2[i];
    }
    return res;
}


template<typename Container>
int max_arg(const Container &c) {
    if (c.begin() == c.end())
        throw std::invalid_argument("empty container is not allowed.");
    return (int) (std::distance(c.begin(), std::max_element(c.begin(), c.end())));
}

template<typename n_array>
n_array cost_derivative(n_array& activations, n_array& sgm_prime) {
    n_array res = activations - sgm_prime;
    return res;
}


//dot(a, b, out=None)
//
//Dot product of two arrays. Specifically,
//
//- If both `a` and `b` are 1-D arrays, it is inner product of vectors
//(without complex conjugation).
//
//- If both `a` and `b` are 2-D arrays, it is matrix multiplication,
//but using :func:`matmul` or ``a @ b`` is preferred.
//
//- If either `a` or `b` is 0-D (scalar), it is equivalent to :func:`multiply`
//and using ``numpy.multiply(a, b)`` or ``a * b`` is preferred.
//
//- If `a` is an N-D array and `b` is a 1-D array, it is a sum product over
//        the last axis of `a` and `b`.
//
//- If `a` is an N-D array and `b` is an M-D array (where ``M>=2``), it is a
//        sum product over the last axis of `a` and the second-to-last axis of `b`::
//
//dot(a, b)[i,j,k,m] = sum(a[i,j,:] * b[k,:,m])
//сум продукт это умножение каждого элемента двух векторов и сложение результатот

template<typename Container, typename T>
Container dot_product(const Container &a, const Container &b) {
    if (a.get_sizes().empty() && b.get_sizes().empty()) {
        Container res = a;
        res *= b;
        return res;
    }
    if (a.get_sizes().size() == 1 && b.get_sizes().size() == 1) {

        std::allocator<T> _allocator;
        T *new_mem = counting_mem_allocator::allocate<T>(_allocator,  1);
        *new_mem = T(0);
        Container res = Container(std::vector<int>(), new_mem);
        for (auto &&[x, y]: _zip(a, b)) {
            res += x * y;
        }
        return res;
    }
    if (a.get_sizes().size() == 2 && b.get_sizes().size() == 2) {
        std::vector<int> new_sizes;
        new_sizes.push_back(a.get_sizes().front());
        new_sizes.push_back(b.get_sizes().back());
        std::allocator<T> _allocator;
        int new_mem_size = 1;
        std::for_each(new_sizes.begin(), new_sizes.end(),
                      [&new_mem_size](int i) mutable {
                          new_mem_size *= i;
                      });
        T *new_mem = counting_mem_allocator::allocate<T>(_allocator,  new_mem_size);
        Container res = Container(new_sizes, new_mem);
        for (int i = 0; i < new_sizes.front(); i++) {
            for (int j = 0; j < new_sizes.back(); j++) {
                Container row1 = a[i];
                Container row2 = b[j];
                for (auto &&[x, y]: _zip(row1, row2)) {
                    res[i][j] += x * y;
                }
            }
        }
        return res;
    }
    if (a.get_sizes().size() == 2 && b.get_sizes().size() == 1) {
        std::vector<int> new_sizes = {a.get_sizes().back()};
        std::allocator<T> _allocator;
        int new_mem_size = 1;
        std::for_each(new_sizes.begin(), new_sizes.end(),
                      [&new_mem_size](int i) mutable {
                          new_mem_size *= i;
                      });
        T *new_mem =  counting_mem_allocator::allocate<T>(_allocator,  new_mem_size);
        Container res = Container(new_sizes, new_mem);
        std::insert_iterator<Container> insert_it(res, res.begin());
        for (int i = 0; i < new_sizes.front(); i++) {
            insert_it = dot_product<Container, T>(a[i], b);
        }

        return res;
    }
    throw new std::runtime_error("non supported for now");
}

#endif //NEURONET_MATH_H
