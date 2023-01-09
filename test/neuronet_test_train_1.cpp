//
// Created by zealot on 29.12.2022.
//


#include "neural_network/Network.h"

int main(int argc, const char *argv[]) {
    MNISTReader reader("", "");
    Network network({28 * 28, 30, 10}, reader);
    network.init();
    unsigned char *img = new unsigned char[28 * 28 * 60000];
    unsigned char *labels = new unsigned char[60000];;
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<char> distribution(0, 255);
    std::uniform_int_distribution<char> distribution1(0, 9);
    for (int i = 0; i < 28 * 28 * 60000; i++) {
        img[i] = distribution(generator);
    }
    for (int i = 0; i < 60000; i++) {
        labels[i] = distribution1(generator);
    }
    network.train(img, labels, 28 * 28, 60000, 30, 10);
    delete [] img;
    delete[] labels;
    return 0;
}