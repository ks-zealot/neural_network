//
// Created by zealot on 10.03.2023.
//

#include "Network_2.h"

void Network_2::init() {
    for (int i = 0; i < layers.size() - 1; i++) {
        layers[i].init(layers[i + 1].size);
    }

}
