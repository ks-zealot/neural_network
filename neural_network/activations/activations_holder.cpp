//
// Created by zealot on 13.03.2023.
//

#include "activations_holder.h"
 std::map<std::string, narray<double> (*)(const narray<double> &)> activations_map = {
{"linear",  linear<double, narray<double>>},
{"sigmoid", sigmoid<double, narray<double>>},
{"reLU",    reLU<double, narray<double>>}};

 std::map<std::string, narray<double> (*)(const narray<double> &)> prime_activations_map = {
{"linear",  linear<double, narray<double>>},
{"sigmoid", sigmoid_prime<double, narray<double>>},
{"reLU",    reLU_prime<double, narray<double>>}};