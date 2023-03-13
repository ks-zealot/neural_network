//
// Created by zealot on 08.12.2022.
//

#ifndef NEURONET_NETWORK_H
#define NEURONET_NETWORK_H


#include <vector>
#include <random>
#include "dataset_readers/MNISTReader.h"
#include "narray/narray.h"
#include "neural_network/layers/layer.h"


template<class Iterator, typename T>
class view {
    Iterator b, e;
public:
    view(Iterator b, Iterator e) : b(b), e(e) {}

    T &operator[](std::size_t i) { return *(b[i]); }

    T const &operator[](std::size_t i) const { return *(b[i]); }

    Iterator begin() const { return b; }

    Iterator end() const { return e; }

    std::size_t size() const { return e - b; }
};

using mini_batch_view = view<std::vector<std::tuple<narray<double>, narray<double>>>::iterator, std::tuple<narray<double>,
        narray<double>>>;

using training_data_container = std::vector<std::tuple<narray<double>, narray<double>>>;

using vector_tuple = std::tuple<std::vector<narray<double>>, std::vector<narray<double>>>;

class Network {
public:
//    Network(const std::vector<int> sizes, MNISTReader &mnist_reader, double eta = 3.f) : sizes(sizes),
//                                                                                         mnist_reader(mnist_reader),
//                                                                                         eta(eta) {}

    Network(const std::vector<layer> layers, MNISTReader &mnist_reader, double eta = 3.f) : input_layer(layers[0]),
                                                                                            layers(layers),
                                                                                            mnist_reader(mnist_reader),
                                                                                            eta(eta) {

    }

private:
    const std::vector<int> sizes;
    const std::vector<layer> layers;
    const layer input_layer;
    int num_layer;
    std::vector<narray<double>> biases;
    std::vector<narray<double>> weights;
    std::vector<narray<double> (*)(const narray<double> &)> activation_functions;
    MNISTReader &mnist_reader;
public:
    void init();

    void print(narray<double> &t);

    void train(unsigned char *images, unsigned char *labels, unsigned image_size, unsigned size,
               unsigned int validation_size, unsigned epochs, unsigned mini_batch_size);

    //    def evaluate(self, test_data):
//    """Return the number of test inputs for which the neural
//    network outputs the correct result. Note that the neural
//    network's output is assumed to be the index of whichever
//    neuron in the final layer has the highest activation."""
//    test_results = [(np.argmax(self.feedforward(x)), y)
//    for (x, y) in test_data]
//    return sum(int(x == y) for (x, y) in test_results)
    int evaluate(narray<double> &container);

private:
    narray<double> &feed_forward(narray<double> &a);

    vector_tuple back_propagation(narray<double> &x, narray<double> &y);

    void update_mini_batch(mini_batch_view mini_batch, double eta);

    void
    SGD(training_data_container &training_data, training_data_container &test_data, int epochs, int mini_batch_size);


    float eta = 3.f;
};


#endif //NEURONET_NETWORK_H
