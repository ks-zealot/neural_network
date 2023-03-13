//
// Created by zealot on 13.03.2023.
//

#include "layer.h"


narray<double> layer::activate(narray<double> &&input) const {
    return activation_function(input);
}

narray<double> layer::derivative(narray<double> &&input) const {
    return derivative_functions(input);
}



narray<double> layer::activate(narray<double> &input) const {
    return activation_function(input);
}

narray<double> layer::derivative(narray<double> &input) const {
    return derivative_functions(input);
}
