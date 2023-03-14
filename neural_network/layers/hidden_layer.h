//
// Created by zealot on 13.03.2023.
//

#ifndef NEURONET_HIDDEN_LAYER_H
#define NEURONET_HIDDEN_LAYER_H


#include "layer.h"

class hidden_layer  : public layer{
public:
    hidden_layer(unsigned size,const std::string & activation =  "sigmoid") : layer(size, activation) {}
};


#endif //NEURONET_HIDDEN_LAYER_H
