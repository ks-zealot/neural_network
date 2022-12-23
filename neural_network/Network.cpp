//
// Created by zealot on 08.12.2022.
//

#include <random>
#include <iostream>
#include "Network.h"
#include "utils/vector_util.h"
#include "math/math.h"

void Network::init() {
    num_layer = sizes.size();
    std::random_device r;
    std::default_random_engine generator(r());
    std::normal_distribution<float> distribution(.0, 1.0);
    init_biases(generator, distribution);
    std::vector<int> v1 = remove_first(sizes);
    std::vector<int> v2 = remove_last(sizes);
    std::vector<std::vector<int>> zipped = zip(v1, v2);
    for (std::vector<std::vector<int>>::iterator it = zipped.begin(); it < zipped.end(); it++) {
        std::vector<int> v = *it;
        init_weights(generator, distribution, v[0], v[1]);
    }
}


void Network::init_weights(std::default_random_engine &generator, std::normal_distribution<float> &distribution,
                           int x, int y) {
    for (int x_ = 0; x_ < x; x_++) {
        std::vector<float> layer;
        for (int y_ = 0; y_ < y; y_++) {
            layer.push_back(distribution(generator));
        }
        weights.push_back(layer);
    }
    std::reverse(weights.begin(), weights.end());
}

void Network::init_biases(std::default_random_engine &generator, std::normal_distribution<float> &distribution) {
    for (int idx = 1; idx < sizes.size(); idx++) {
        std::vector<float> layer;
        for (int i = 0; i < sizes[idx]; i++) {
            layer.push_back(distribution(generator));
        }
        biases.push_back(layer);
    }
}

void Network::print() {
    std::cout << "biases" << std::endl;
    print(biases);
    std::cout << "weights" << std::endl;
    print(weights);

}

void Network::print(std::vector<std::vector<float>> &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            std::cout << v[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<float> Network::feed_forward(std::vector<float> a) {
    vector_2d<float>::iterator bIt = biases.begin();
    vector_2d<float>::iterator wIt = weights.begin();
    for (; bIt < biases.end(); bIt++) {
        std::vector<float> b = *bIt;
        std::vector<float> w = *wIt;
        wIt++;
        int dot_product = inner_product(w.begin(), w.end(), a.begin(), 0);
        a = sigmoid(plus(b, dot_product));
    }
    return a;
}


void Network::SGD(std::vector<std::tuple<int, int>> training_data, int epochs, int mini_butch_size, float eta) {
    int n = training_data.size();
    std::random_device r;
    std::default_random_engine generator(r());
    for (int j = 0; j < epochs; j++) {
        std::shuffle(training_data.begin(), training_data.end(), generator);
        for (std::vector<std::tuple<int, int>> batch: split_vector(training_data, mini_butch_size)) {
            update_mini_batch(batch, eta);
        }
        info("Epoch {} complete", j);
    }
}

void Network::update_mini_batch(std::vector<std::tuple<int, int>> batch, float eta) {
    vector_2d<float> nabla_b = init_zero_vector(biases);
    vector_2d<float> nabla_w = init_zero_vector(weights);
    for (std::tuple<int, int> xy: batch) {

    }
}
//Boost.Iterator's zip_iterator

//ToDo array to vector
//std::vector<int> v(x, x + sizeof x / sizeof x[0]);
std::tuple<vector_2d<float>, vector_2d<float>> Network::backprop(DatasetImage *image, int label) {
    vector_2d<float> nabla_b = init_zero_vector(biases);
    vector_2d<float> nabla_w = init_zero_vector(weights);
    char* activation = image->image;
    std::vector<char*> activations;
    activations.push_back(activation);
    vector_2d<float> zs;
    for(unsigned i = 0; i < biases.size(); ++i) {
        std::vector<float> b = biases[i];
        std::vector<float> w = weights[i];
        int dot_product = inner_product(w.begin(), w.end(), activation, 0);
        std::vector<float> z = plus(b, dot_product);
        zs.push_back(z);
    }
}
