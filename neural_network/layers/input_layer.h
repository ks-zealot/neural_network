//
// Created by zealot on 13.03.2023.
//

#ifndef NEURONET_INPUT_LAYER_H
#define NEURONET_INPUT_LAYER_H


#include "layer.h"

class input_layer : public layer {
public:
    input_layer(unsigned size) : layer(size, "linear") {}
};


#endif //NEURONET_INPUT_LAYER_H
