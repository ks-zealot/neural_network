//
// Created by zealot on 13.03.2023.
//

#ifndef NEURONET_LAYER_H
#define NEURONET_LAYER_H
#include "neural_network/activations/activations_holder.h"

#include "narray/narray.h"



class layer {
public:
    layer(int size, std::string& activation) : activation_function(
            activations_map[activation]), derivative_functions(prime_activations_map[activation]), size(size) {};

    narray<double> activate(narray<double> &&input) const;
    narray<double> derivative(narray<double> &&input) const;
    narray<double> activate(narray<double> &input) const;
    narray<double> derivative(narray<double> &input) const;
    int size;
protected :
    narray<double> (*activation_function)(const narray<double> &);
    narray<double> (*derivative_functions)(const narray<double> &);

};


#endif //NEURONET_LAYER_H
