//
// Created by zealot on 14.03.2023.
//

#ifndef NEURONET_ACTIVATIONS_H
#define NEURONET_ACTIVATIONS_H
template<typename T>
T sigmoid(T z) {
    return 1.f / (1.f + exp(-z));
}

template<typename T>
T sigmoid_prime(T z) {
    return sigmoid(z) * (1 - sigmoid(z));
}

template<typename T>
T reLU(T z) {
    return std::max<T>(0, z);
}

template<typename T>
T reLU_prime(T z) {
    if (z <= T(0)) {
        return T(0);
    } else {
        return T(1);
    }
}

template<typename T>
T tanh(T z) {
    return (exp(z) - exp(z)) / (exp(z) + exp(z));
}

template<typename T, typename Container>
Container tanh(const Container &z) {
    Container c = z;
    std::transform(z.begin(), z.end(),
                   c.begin(),
                   [](T t) { return tanh(t); });
    return c;
}



template<typename T, typename Container>
Container softmax(const Container &z) {
    Container c = z;
    T sum = std::reduce(z.begin(), z.end(), T(0), [](T t) { return exp(t); });
    std::transform(z.begin(), z.end(),
                   c.begin(),
                   [&sum](T t) { return exp(t) / sum; });
    return c;
}

template<typename T, typename Container>
Container reLU(const Container &z) {
    Container c = z;
    std::transform(z.begin(), z.end(),
                   c.begin(),
                   [](T t) { return reLU(t); });
    return c;
}

template<typename T, typename Container>
Container linear(const Container &z) {
    Container c = z;
    return c;
}

template<typename T, typename Container>
Container reLU_prime(const Container &z) {
    Container c = z;
    std::transform(z.begin(), z.end(),
                   c.begin(),
                   [](T t) { return reLU_prime(t); });
    return c;
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
#endif //NEURONET_ACTIVATIONS_H
