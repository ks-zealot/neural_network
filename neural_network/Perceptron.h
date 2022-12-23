//
// Created by zealot on 09.12.2022.
//

#ifndef NEURONET_PERCEPTRON_H
#define NEURONET_PERCEPTRON_H


#include "dataset_readers/DatasetImage.h"
#include "math/math.h"

class Perceptron {
public:
    Perceptron(char * weights) : weights(weights) {}

public:
    void init(unsigned int size, unsigned int label_size);

    void shutdown();

    bool evaluate(DatasetImage *image);

private:
    char * weights;
    char *weights_to_label;
    char *biases;
    int label_size = 10;//todo
    int image_size = 28 * 28;//todo
private:
    std::vector<char> feed_forward(char *image);//

//     Return a tuple ``(nabla_b, nabla_w)`` representing the
//    gradient for the cost function C_x.  ``nabla_b`` and
//    ``nabla_w`` are layer-by-layer lists of numpy arrays, similar
//            to ``self.biases`` and ``self.weights``."""
    std::tuple<std::vector<char>, std::vector<char>> backprop(DatasetImage *image);
};


#endif //NEURONET_PERCEPTRON_H
