//
// Created by zealot on 09.12.2022.
//

#include <random>
#include "Perceptron.h"

void Perceptron::init(unsigned int size, unsigned int label_size) {
    std::random_device r;
    std::default_random_engine generator(r());
    std::normal_distribution<float> distribution(0, 255);
//    for (int i = 0; i < size; i++) {
//        weights[i] = (char) distribution(generator);
//    }
//    weights_to_label = new char[label_size];
//    biases = new char[label_size];
//    for (int i = 0; i < label_size; i++) {
//        weights_to_label[i] = distribution(generator);
//        biases[i] = distribution(generator);
//    }
}

bool Perceptron::evaluate(DatasetImage *image) {
    return image->label == max_arg(feed_forward(image->image));
}

void Perceptron::shutdown() {
    delete[] weights_to_label;
    delete[] biases;

}

// возващаем вектор вероятностей. где вероятность выше тот лейбл верен
std::vector<char> Perceptron::feed_forward(char *image) {//todo
    std::vector<char> res;
    std::vector<char> w(weights, weights + image_size);
    std::vector<char> a(image, image + image_size);
    int dot_product = inner_product(w.begin(), w.end(), a.begin(), 0);
    for (int i = 0; i < label_size; i++) {
        res.push_back(sigmoid(dot_product + biases[i]));
    }
    return res;
}


//функция возвращает дельту весов и дельту искажений
//def backprop(self, x, y):#x input y label
//"""Return a tuple ``(nabla_b, nabla_w)`` representing the
//gradient for the cost function C_x.  ``nabla_b`` and
//``nabla_w`` are layer-by-layer lists of numpy arrays, similar
//        to ``self.biases`` and ``self.weights``."""
//nabla_b = [10] # вектор длиной 10 идентичен весам()
//nabla_w = [768]# вектор длиной 768 идентичен весам
//# feedforward
//z = np.dot(w, x)+b # то же самое что фидфорвард, но без сигмоиды
//activation = sigmoid(z) # а с сигмоидой
//activations.append(activation)
//# backward pass
//delta = self.cost_derivative(activation, y) * \
        //            sigmoid_prime(z) # считаем дельиу
//nabla_b  = delta # набла б это дельта
//        nabla_w = np.dot(delta, activations.transpose()) # НАБЛА в это скалярное произведение дельты на транспонированную матрицу активаций
// в целом это матрица размерностью 28 х 28 с числоами от 0 до 1
// return (nabla_b, nabla_w)

//y это не число, а вектор!
std::tuple<std::vector<char>, std::vector<char>> Perceptron::backprop(DatasetImage *_image) {
    char *nabla_w = new char[image_size];
    char *nabla_b = new char[label_size];
    char *image = _image->image;
    std::vector<char> z = feed_forward(image);
    std::vector<char> cs =  cost_derivative(z , _image->label);
    std::vector<char> delta = mul(cs, sigmoid_prime(z));
    nabla_b = delta.data();
//    nabla_w = dot_product(delta, z)
    return std::tuple<std::vector<char>, std::vector<char>>();
}


