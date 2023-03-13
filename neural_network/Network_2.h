//
// Created by zealot on 10.03.2023.
//

#ifndef NEURONET_NETWORK_2_H
#define NEURONET_NETWORK_2_H


#include <vector>
#include "Layer.h"

class Network_2 {
public:
    Network_2(const std::vector<layer> &layers,unsigned mini_batch_size) : layers(layers), mini_batch_size(mini_batch_size) {};

    void init();
private:
    std::vector<layer> layers;
    unsigned mini_batch_size;
};


#endif //NEURONET_NETWORK_2_H
