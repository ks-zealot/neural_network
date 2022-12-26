//
// Created by zealot on 26.12.2022.
//

#include "narray_coord.h"

void narray_coord::plus_coord(int val) {
        int shift = val;
        int idx = coord.size() - 1;
        std::for_each(coord.rbegin(), coord.rend(),
                      [this, &idx, &shift](int i) mutable {
                          coord[idx] += shift;
                          shift = 0;
                          while (coord[idx] >= size_vector[idx]) {
                              shift++;
                              coord[idx] =0;
                          }
                          idx--;
                      });
    }


