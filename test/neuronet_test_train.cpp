//
// Created by zealot on 29.12.2022.
//


#include "neural_network/Network.h"

int main(int argc, const char *argv[]) {
    MNISTReader reader("", "");
    Network network({28 * 28, 30, 10}, reader);
    network.init();
    unsigned char *img = new unsigned char[28 * 28];
    unsigned char label;
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<char> distribution(0, 255);
    for (int i = 0; i < 28 * 28; i++) {
        img[i] = distribution(generator);
    }
    network.train(img, &label, 28 * 28, 1);
    return 0;
}