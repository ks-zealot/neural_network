//
// Created by zealot on 07.12.2022.
//

#include <cassert>
#include <cstdlib>
#include <cstring>

#include "MNISTReader.h"
#include "utils.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

void MNISTReader::read() {
    extractDataset();
    extractLabels();
    showImages();


    //initscr();
    // printw("Display random image...");

    // print_image(number_of_rows, number_of_cols, (unsigned char *) images[1]->image);
//    std::cin.get();
//    endwin();

    //   std::this_thread::sleep_for (std::chrono::seconds(25));
    // endwin();
}

void MNISTReader::extractLabels() {
    lbl_dataset.read(reinterpret_cast<char *>(&label_magic_number), sizeof(int));
    SwapEnd(label_magic_number);
    assert(label_magic_number == 0x00000801);
    lbl_dataset.read(reinterpret_cast<char *>(&number_of_labels), sizeof(int));
    SwapEnd(number_of_labels);
    labels = new char[number_of_labels];
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
    alloc_mem();

    int image_size = number_of_cols * number_of_rows;
    char *image = new char[image_size];

    for (int i = 0; i < number_of_images; i++) {
        fp_dataset.read(image, image_size);
        memcpy(mem + (i * image_size), image, image_size);
        images.push_back(new DatasetImage((char *) mem + (i * image_size), 0));
    }
    delete[] image;

}

void MNISTReader::prepare() {
    fp_dataset = std::ifstream(dataset_file_name.c_str(), std::ios::in | std::ios::binary);
    lbl_dataset = std::ifstream(labels_file_name.c_str(), std::ios::in | std::ios::binary);
    if (!fp_dataset.is_open() || !lbl_dataset.is_open()) {
        throw new std::runtime_error("could not open dataset");
    }
}

void MNISTReader::close() {
    free(mem);
    delete[] labels;
    fp_dataset.close();
    lbl_dataset.close();
}

void MNISTReader::alloc_mem() {
    mem = (char *) malloc(number_of_images * number_of_rows * number_of_cols * sizeof(char));
}

void MNISTReader::showImages() {
    initscr();
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(0, number_of_images);
    for (int i = 0; i < 60; i++) {
        int dice_roll = distribution(generator);
        print_image(number_of_cols, number_of_rows, (unsigned char *) images[dice_roll]->image);
        mvaddstr(number_of_rows + 2, 0, std::string("This is ").append(std::to_string(labels[dice_roll])).c_str());
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    endwin();
}

void MNISTReader::train() {

}

