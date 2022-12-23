//
// Created by zealot on 07.12.2022.
//
#include <string>
#include <fstream>
#include "DatasetImage.h"
#include <vector>

#ifndef NEURONET_MNISTREADER_H
#define NEURONET_MNISTREADER_H


class MNISTReader {
public:
    MNISTReader(std::string dataset_file_name, std::string labels_file_name) : dataset_file_name(dataset_file_name)
    , labels_file_name(labels_file_name) {};
private:
    std::string dataset_file_name;
    std::string labels_file_name;
    std::ifstream fp_dataset;
    std::ifstream lbl_dataset;
    int dataset_magic_number;
    int label_magic_number;
    int number_of_images;
    int number_of_labels;
    int number_of_rows;
    int number_of_cols;

    char *mem;
    std::vector<DatasetImage *> images;
    char* labels;
    void alloc_mem();
public:
    void read();
    void prepare();
    void close();

    void extractDataset();

    void extractLabels();

    void showImages();

    void train();
};


#endif //NEURONET_MNISTREADER_H
