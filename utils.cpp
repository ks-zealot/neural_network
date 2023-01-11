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
            x += 4;
        }
        y += 2;
        x = 0;
    }

    refresh();
}

float sigmoid(float z) {//todo найти способ не дублировать функции
    return 1.f / (1.f + exp(-z));
}

void print_weight(unsigned int Width, unsigned int Height, float *weight) {
    unsigned int x = 0;
    unsigned int y = 0;
    float t = weight[10];
//    start_color();
//    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
//    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    for (unsigned int j = 0; j < Height; j++) {
        for (unsigned int i = 0; i < Width; i++) {
            float f = fabs(sigmoid(weight[i + (j * Width)]));
            unsigned int pos = fabs(sigmoid(weight[i + (j * Width)]) * 5.f);
            print_pixel(pos, x, y);
            x += 4;
        }
        y += 2;
        x = 0;
    }

    refresh();
}



void print_pixel(unsigned int pos, unsigned int x, unsigned int y) {
    const wchar_t *block = blocks[pos];
    const wchar_t *block1 = blocks[1];
    const wchar_t *block2 = blocks[2];
    const wchar_t *block3 = blocks[3];
    const wchar_t *block4 = blocks[4];
    const wchar_t *block5 = blocks[5];
    unsigned int cp = (pos == 0) + 1;
    attron(COLOR_PAIR(cp));
    for (unsigned int k = 0; k < BLOCK_SIZE; k++) {
        for (unsigned int k1 = 0; k1 < BLOCK_SIZE * 2; k1++) {
            mvaddwstr(y + k, x + k1, block);
        }
    }
    attroff(COLOR_PAIR(cp));
}

