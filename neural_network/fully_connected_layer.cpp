//
// Created by zealot on 10.03.2023.
//

#include "fully_connected_layer.h"
#include "math/math.h"

void fully_connected_layer::init(unsigned int n_out) {
    scale_filler<double> filler = scale_filler<double>(n_out);
    random_filler<double> r = random_filler<double>::GetInstance();
    weights = narray<double>(std::vector<int>(size, n_out), filler);
    biases = narray<double>(std::vector<int>(n_out), r);
}

void fully_connected_layer::set_input(narray<double> input, narray<double> dropout, unsigned int mini_butch_size) {
//    self.inpt = inpt.reshape((mini_batch_size, self.n_in))
//  input это матрица размером минибатчсайз х размер картинки. условно это информация о всех картинках в батче
    input = narray<double>(std::vector<int>(mini_butch_size, size));
//    self.output = self.activation_fn(
//            (1-self.p_dropout)*T.dot(self.inpt, self.w) + self.b)
    narray<double> tmp = (1. - p_dropout) * dot_product<narray<double>, double>(input, weights) + biases;
    output = activation_function(tmp);
//    self.y_out = T.argmax(self.output, axis=1)
    y_out = max_arg(output);
}
