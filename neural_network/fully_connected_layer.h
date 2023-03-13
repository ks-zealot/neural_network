//
// Created by zealot on 10.03.2023.
//

#ifndef NEURONET_FULLY_CONNECTED_LAYER_H
#define NEURONET_FULLY_CONNECTED_LAYER_H


#include "Layer.h"

class fully_connected_layer : public layer {
public:
    void init(unsigned int n_out) override;

    void set_input(narray<double> input, narray<double> dropout, unsigned int mini_butch_size) override;

private:
    double p_dropout = 0.;
    double y_out = 0;
};


#endif //NEURONET_FULLY_CONNECTED_LAYER_H
