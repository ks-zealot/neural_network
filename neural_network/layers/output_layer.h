//
// Created by zealot on 13.03.2023.
//

#ifndef NEURONET_OUTPUT_LAYER_H
#define NEURONET_OUTPUT_LAYER_H


#include "layer.h"

class output_layer : public layer {
public:
    output_layer(unsigned size, const std::string&  activation = "sigmoid") : layer(size, activation) {}

};


#endif //NEURONET_OUTPUT_LAYER_H
