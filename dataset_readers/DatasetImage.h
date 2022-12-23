//
// Created by zealot on 07.12.2022.
//

#ifndef NEURONET_DATASETIMAGE_H
#define NEURONET_DATASETIMAGE_H


class DatasetImage {
public:

    DatasetImage(char *image, int label) : image(image), label(label) {};


private:
    char *image;
    char label;

    friend class MNISTReader;

    friend class Network;

    friend class Perceptron;
};


#endif //NEURONET_DATASETIMAGE_H
