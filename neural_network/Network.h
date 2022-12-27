//
// Created by zealot on 08.12.2022.
//

#ifndef NEURONET_NETWORK_H
#define NEURONET_NETWORK_H


#include <vector>
#include <random>
#include "dataset_readers/MNISTReader.h"
#include "narray/narray.h"
template<class Iterator, typename  T> class view {
    Iterator b, e;
public:
    view(Iterator b, Iterator e): b(b), e(e) {}

    T &operator[](std::size_t i) { return *(b[i]); }
    T const &operator[](std::size_t i) const { return *(b[i]); }
    Iterator begin() const { return b; }
    Iterator end() const { return e; }
    std::size_t size() const { return e - b; }
};

class Network {
public:
    Network(const std::vector<int> sizes, MNISTReader &mnist_reader) : sizes(sizes), mnist_reader(mnist_reader) {}

private:
    const std::vector<int> sizes;
    int num_layer;
    std::vector<narray<float>> biases;
    std::vector<narray<float>> weights;
    MNISTReader &mnist_reader;
public:
    void init();

    void print();

private:
    narray<float> &feed_forward(narray<float> &a);


    std::tuple<std::vector<narray<float>>, std::vector<narray<float>>>
    back_propagation(narray<float> &x, narray<float> &y);

    void update_mini_butch(view<std::vector<std::tuple<narray<float>, narray<float>>>::iterator, std::tuple<narray<float>,
            narray<float>>> mini_batch, float eta); //todo объявить тип

    void SGD (std::vector<std::tuple<narray<float>, narray<float>>> training_data, int epochs, int mini_butch_size, float eta);
};


#endif //NEURONET_NETWORK_H
