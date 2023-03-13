//
// Created by zealot on 10.03.2023.
//

#ifndef NEURONET_LAYER_H
#define NEURONET_LAYER_H


#include "narray/narray.h"

class layer {
public:
    layer(unsigned size, narray<double> (*activation_function)(narray<double> &)) : size(size), activation_function(
            activation_function){};

    virtual void init(unsigned n_out);
    virtual void set_input(narray<double> input, narray<double> dropout , unsigned mini_butch_size);

    unsigned size;
protected:
    narray<double> biases;
    narray<double> dropout;
    narray<double> input;
    narray<double> output;
    narray<double> weights;

    narray<double> (*activation_function)(narray<double> &);
};


#endif //NEURONET_LAYER_H
