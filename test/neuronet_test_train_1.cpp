//
// Created by zealot on 29.12.2022.
//


#include <ncurses.h>
#include <thread>
#include "neural_network/Network.h"
#include "utils.h"

int main(int argc, const char *argv[]) {
    initscr();
    setlocale(LC_CTYPE, "en_US.UTF-8");
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
//    float f = 0.6f;
//    print_weight(1, 1, &f);
//    std::this_thread::sleep_for(std::chrono::seconds (100));
    MNISTReader reader("", "");
    Network network({28 * 28, 30, 10}, reader);
    network.init();
    unsigned char *img = new unsigned char[28 * 28 * 600];
    unsigned char *labels = new unsigned char[600];;
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<char> distribution(0, 255);
    std::uniform_int_distribution<char> distribution1(0, 9);
    for (int i = 0; i < 28 * 28 * 600; i++) {
        img[i] = distribution(generator);
    }
    for (int i = 0; i < 600; i++) {
        labels[i] = distribution1(generator);
    }
    network.train(img, labels, 28 * 28, 400, 200, 1, 10);
    delete [] img;
    delete[] labels;
    endwin();
    return 0;
}