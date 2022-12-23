//
// Created by zealot on 08.12.2022.
//

#ifndef NEURONET_NETWORK_H
#define NEURONET_NETWORK_H


#include <vector>
#include <random>
#include "dataset_readers/MNISTReader.h"

template<class T>
using vector_2d = typename std::vector<std::vector<T>>;

class Network {
public:
    Network(const std::vector<int> sizes, MNISTReader *mnist_reader) : sizes(sizes), mnist_reader(mnist_reader) {}

private:
    const std::vector<int> sizes;
    int num_layer;
    vector_2d<float> biases;
    vector_2d<float> weights;
    MNISTReader *mnist_reader;
public:
    void init();

    void print();

private:
    void init_biases(std::default_random_engine &generator, std::normal_distribution<float> &distribution);

    void init_weights(std::default_random_engine &generator, std::normal_distribution<float> &distribution,
                      int x,
                      int y);

    void print(std::vector<std::vector<float>> &v);

    std::vector<float> feed_forward(std::vector<float> a);

    void SGD(std::vector<std::tuple<int, int>> training_data, int epochs, int mini_butch_size, float eta);

    void update_mini_batch(std::vector<std::tuple<int, int>> vector1, float eta);

    std::tuple<vector_2d<float>, vector_2d<float>> backprop(DatasetImage *image, int label);
};


#endif //NEURONET_NETWORK_H
