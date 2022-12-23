//
// Created by zealot on 08.12.2022.
//
#include <algorithm>
#include <random>
#include <logging/log.h>
#include <cmath>
#include <vector>
#include<numeric>

#ifndef NEURONET_MATH_H
#define NEURONET_MATH_H

#endif //NEURONET_MATH_H

template<typename T>
T sigmoid(T z) {
    return 1.f / (1.f + exp(-z));
}

template<typename T>
std::vector<T> sigmoid(std::vector<T> z) {
    for (int i = 0; i < z.size(); i++) {
        z[i] = sigmoid(z[i]);
    }
    return z;
}

template<typename T>
std::vector<T> sigmoid_prime(std::vector<T> z) {
    std::transform(z.begin(), z.end(), z.begin(), [](T t) {
        return sigmoid(t) * (1 - sigmoid(t));
    });
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
int max_arg(Container const c)  {
    if (std::begin(c) == std::end(c))
        throw std::invalid_argument("empty container is not allowed.");
    return (int) (std::distance(c.begin(), std::max_element(c.begin(), c.end())));
}

template<typename T>
std::vector<T> cost_derivative(std::vector<T>  activations, T y) {
    std::transform(activations.begin(), activations.end(), activations.begin(), [&y] (T t) { return t - y;});
    return activations;
}

template<typename T>
using matrix = std::vector<std::vector<T>>;

template<typename T>
matrix<T> multiple(matrix<T> A, matrix<T> B)
{
    matrix<T> C;
    for (int i = 0; i < A.size(); ){
        for (int j = 0; j < B.size(); ){
            for (int k = 0; k < A.size();k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
    return C;
}
//https://stackoverflow.com/questions/16737298/what-is-the-fastest-way-to-transpose-a-matrix-in-c
template<typename T>
matrix<T> transpose() {

}