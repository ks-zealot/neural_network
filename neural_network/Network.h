//
// Created by zealot on 08.12.2022.
//

#ifndef NEURONET_NETWORK_H
#define NEURONET_NETWORK_H


#include <vector>
#include <random>
#include "dataset_readers/MNISTReader.h"
#include "narray/narray.h"


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

using mini_batch_view = view<std::vector<std::tuple<narray<float>, narray<float>>>::iterator, std::tuple<narray<float>,
        narray<float>>>;

using training_data_container = std::vector<std::tuple<narray<float>, narray<float>>>;

using training_data_tuple = std::tuple<std::vector<narray<float>>, std::vector<narray<float>>>;//todo переименовать

class Network {
public:
    Network(const std::vector<int> sizes, MNISTReader &mnist_reader, float eta = 3.f) : sizes(sizes), mnist_reader(mnist_reader), eta(eta) {}
private:
    const std::vector<int> sizes;
    int num_layer;
    std::vector<narray<float>> biases;
    std::vector<narray<float>> weights;
    MNISTReader &mnist_reader;
public:
    void init();

    void print(narray<float>& t);

    void train(unsigned char * images,unsigned char * labels, unsigned image_size, unsigned size,  unsigned int validation_size, unsigned epochs, unsigned mini_batch_size);
    //    def evaluate(self, test_data):
//    """Return the number of test inputs for which the neural
//    network outputs the correct result. Note that the neural
//    network's output is assumed to be the index of whichever
//    neuron in the final layer has the highest activation."""
//    test_results = [(np.argmax(self.feedforward(x)), y)
//    for (x, y) in test_data]
//    return sum(int(x == y) for (x, y) in test_results)
    int evaluate(   narray<float> & container);

private:
    narray<float> &feed_forward(narray<float>& a);

    training_data_tuple back_propagation(narray<float> &x, narray<float> &y);

    void update_mini_butch(mini_batch_view mini_batch, float eta);

    void SGD(training_data_container& training_data,  training_data_container &test_data,  int epochs, int mini_batch_size);


    float eta = 3.f;
};


#endif //NEURONET_NETWORK_H
