//
// Created by zealot on 29.12.2022.
//


#include <ncurses.h>
#include <thread>
#include "neural_network/Network.h"
#include "utils.h"
#include "profiling/time_profiling.h"

int main(int argc, const char *argv[]) {
    initscr();
    setlocale(LC_CTYPE, "en_US.UTF-8");
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    MNISTReader reader("train-images-idx3-ubyte", "train-labels-idx1-ubyte");
    reader.prepare();
    reader.read();
    reader.train();
    reader.close();

    endwin();
    return 0;
}