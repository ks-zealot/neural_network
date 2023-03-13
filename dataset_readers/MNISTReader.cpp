//
// Created by zealot on 07.12.2022.
//

#include <cassert>
#include <cstdlib>
#include <cstring>

#include "MNISTReader.h"
#include "utils.h"
#include "neural_network/Network.h"
#include "neural_network/layers/hidden_layer.h"
#include "neural_network/layers/input_layer.h"
#include "neural_network/layers/output_layer.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

void MNISTReader::read() {
    extractDataset();
    extractLabels();
}

void MNISTReader::extractLabels() {
    lbl_dataset.read(reinterpret_cast<char *>(&label_magic_number), sizeof(int));
    SwapEnd(label_magic_number);
    assert(label_magic_number == 0x00000801);
    lbl_dataset.read(reinterpret_cast<char *>(&number_of_labels), sizeof(int));
    SwapEnd(number_of_labels);
    labels = new   char[number_of_labels];
    lbl_dataset.read(labels, number_of_labels);
}


void MNISTReader::extractDataset() {
    fp_dataset.read(reinterpret_cast<char *>(&dataset_magic_number), sizeof(int));
    SwapEnd(dataset_magic_number);
    assert(dataset_magic_number == 0x00000803);
    fp_dataset.read(reinterpret_cast<char *>(&number_of_images), sizeof(int));
    fp_dataset.read(reinterpret_cast<char *>(&number_of_rows), sizeof(int));
    fp_dataset.read(reinterpret_cast<char *>(&number_of_cols), sizeof(int));
    SwapEnd(number_of_images);
    SwapEnd(number_of_rows);
    SwapEnd(number_of_cols);
    images = new char[number_of_images * number_of_rows * number_of_cols];
    fp_dataset.read(images, number_of_images * number_of_rows * number_of_cols);
}

void MNISTReader::prepare() {
    fp_dataset = std::ifstream(dataset_file_name.c_str(), std::ios::in | std::ios::binary);
    lbl_dataset = std::ifstream(labels_file_name.c_str(), std::ios::in | std::ios::binary);
    if (!fp_dataset.is_open() || !lbl_dataset.is_open()) {
        throw new std::runtime_error("could not open dataset");
    }
}

void MNISTReader::close() {
    delete[] labels;
    delete[] images;
    fp_dataset.close();
    lbl_dataset.close();
}




void MNISTReader::train() {
//    Network network({number_of_rows * number_of_cols, 30, 10}, *this, 0.5);
    Network network({input_layer(number_of_rows * number_of_cols), hidden_layer(30, "reLU"), output_layer(10)}, *this, 0.5);
    network.init();
    network.train((unsigned char*)images,(unsigned char*) labels, number_of_rows * number_of_cols,
                  number_of_images - 10000, 10000, 30, 10);
}

