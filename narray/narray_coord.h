//
// Created by zealot on 26.12.2022.
//

#ifndef NEURONET_NARRAY_COORD_H
#define NEURONET_NARRAY_COORD_H


#include <utility>
#include <vector>

class narray_coord {
public:

    narray_coord(std::vector<int> _size_vector) : coord(_size_vector), size_vector(_size_vector) {
        std::fill(coord.begin(), coord.end(), 0);
    }


    friend narray_coord &operator++(narray_coord &rhs) {
        rhs.plus_coord(1);
        return rhs;
    }

    narray_coord &operator+=(const int &rhs) {
        this->plus_coord(rhs);
        return *this;
    }

public:
    void plus_coord(int val);


    inline std::vector<int> get_coord() {
        return coord;
    }

private:
    std::vector<int> coord;
    std::vector<int> size_vector;
};


#endif //NEURONET_NARRAY_COORD_H
