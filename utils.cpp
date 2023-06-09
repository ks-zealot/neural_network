#include <sstream>
#include "utils.h"
#include "global.h"


#define  BLOCK_SIZE 2


void print_image(unsigned int Width, unsigned int Height, unsigned char *data) {
    unsigned int x = 0;
    unsigned int y = 0;
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    for (unsigned int j = 0; j < Height; j++) {
        for (unsigned int i = 0; i < Width; i++) {
            unsigned int pos = data[i + (j * Width)] / 64;
            print_pixel(pos, x, y);
            x += BLOCK_SIZE * 2;
        }
        y += BLOCK_SIZE;
        x = 0;
    }

    refresh();
}

void print_image(unsigned int Width, unsigned int Height, double *data, int label) {
    unsigned int x = 0;
    unsigned int y = 0;
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    for (unsigned int j = 0; j < Height; j++) {
        for (unsigned int i = 0; i < Width; i++) {
            unsigned int pos = data[i + (j * Width)] * 5.0;
            print_pixel(pos, x, y);
            x += BLOCK_SIZE * 2;
        }
        y += BLOCK_SIZE;
        x = 0;
    }
    std::stringstream ss;
    ss << "This is ";
    ss << label;
    printw(ss.str().c_str());
    refresh();
}

void print_image(unsigned int Width, unsigned int Height, const double *data, int label, int evaluated) {
    clear();
    refresh();
    unsigned int x = 0;
    unsigned int y = 0;
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    for (unsigned int j = 0; j < Height; j++) {
        for (unsigned int i = 0; i < Width; i++) {
            unsigned int pos = data[i + (j * Width)] * 5.0;
            print_pixel(pos, x, y);
            x += BLOCK_SIZE * 2;
        }
        y += BLOCK_SIZE;
        x = 0;
    }
    std::stringstream ss;
    ss << "This is ";
    ss << label;
    if (label == evaluated) {
        ss << " and evualated ";
    } else {
        ss << " but evualated ";
    }

    ss << evaluated;
    printw(ss.str().c_str());
    refresh();
}

float sigmoid(float z) {//todo найти способ не дублировать функции
    return 1.f / (1.f + exp(-z));
}

void print_weight(unsigned int Width, unsigned int Height, float *weight) {
    unsigned int x = 0;
    unsigned int y = 0;
    for (unsigned int j = 0; j < Height; j++) {
        for (unsigned int i = 0; i < Width; i++) {
            unsigned int pos = fabs(sigmoid(weight[i + (j * Width)]) * 5.f);
            print_pixel(pos, x, y);
            x += BLOCK_SIZE * 2;
        }
        y += BLOCK_SIZE;
        x = 0;
    }

    refresh();
}

void print_weight(unsigned int Width, unsigned int Height, const double *weight) {
    clear();
    refresh();
    unsigned int x = 0;
    unsigned int y = 0;
    for (unsigned int j = 0; j < Height; j++) {
        for (unsigned int i = 0; i < Width; i++) {
            unsigned int pos = fabs(sigmoid(weight[i + (j * Width)]) * 5.f);
            print_pixel(pos, x, y);
            x += BLOCK_SIZE * 2;
        }
        y += BLOCK_SIZE;
        x = 0;
    }

    refresh();
}

void print_pixel(unsigned int pos, unsigned int x, unsigned int y) {
    const wchar_t *block = blocks[pos];
    unsigned int cp = (pos == 0) + 1;
    attron(COLOR_PAIR(cp));
    for (unsigned int k = 0; k < BLOCK_SIZE; k++) {
        for (unsigned int k1 = 0; k1 < BLOCK_SIZE * 2; k1++) {
            mvaddwstr(y + k, x + k1, block);
        }
    }
    attroff(COLOR_PAIR(cp));
}

