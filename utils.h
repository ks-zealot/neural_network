#pragma once

#include <ncurses.h>
#include <type_traits>
#include <array>
#include <cstring>
#ifndef NEURONET_UTILS_H
#define NEURONET_UTILS_H
//const unsigned int BLOCK_SIZE = 2;
void print_image(unsigned int Width, unsigned int Height, unsigned char *data);

void print_weight(unsigned int Width, unsigned int Height, char *weight);

void print_pixel(unsigned int pos, unsigned int x, unsigned int y);


template<typename T>
void SwapEnd(T &var) {
    static_assert(std::is_standard_layout<T>::value && std::is_trivial<T>::value, "Type must be POD type for safety");
    std::array<char, sizeof(T)> varArray;
    std::memcpy(varArray.data(), &var, sizeof(T));
    for (int i = 0; i < static_cast<int>(sizeof(var) / 2); i++)
        std::swap(varArray[sizeof(var) - 1 - i], varArray[i]);
    std::memcpy(&var, varArray.data(), sizeof(T));
}

#endif //NEURONET_UTILS_H