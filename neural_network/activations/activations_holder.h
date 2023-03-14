//
// Created by zealot on 13.03.2023.
//

#ifndef NEURONET_ACTIVATIONS_HOLDER_H
#define NEURONET_ACTIVATIONS_HOLDER_H


#include <string>
#include <map>
#include "narray/narray.h"
//

extern std::map<std::string, narray<double> (*)(const narray<double> &)> activations_map;
extern std::map<std::string, narray<double> (*)(const narray<double> &)> prime_activations_map;


#endif //NEURONET_ACTIVATIONS_HOLDER_H
