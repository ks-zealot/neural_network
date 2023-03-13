//
// Created by zealot on 08.12.2022.
//

#include <chrono>
#include <thread>
#include <valarray>

#include "Network.h"
#include "utils/vector_util.h"
#include "math/math.h"
#include "utils.h"
#include "logging/log.h"

void print_matrix(narray<double> &array, short size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double t = *(array.at({0, j + (i * size)}));
            std::cout << " " << t;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
};

//[784, 30, 10]
void Network::init() {
    num_layer = sizes.size();
    biases.push_back(narray<double>(std::vector({sizes[1], 1}), random_filler<double>::GetInstance()));
    biases.push_back(narray<double>(std::vector({sizes[2], 1}), random_filler<double>::GetInstance()));
    weights.push_back(narray<double>(std::vector({sizes[1], sizes[0]}), random_filler<double>::GetInstance()));
    weights.push_back(narray<double>(std::vector({sizes[2], sizes[1]}), random_filler<double>::GetInstance()));
    activation_functions.push_back(reLU<double, narray<double>>);
    activation_functions.push_back(sigmoid<double, narray<double>>);
}


void Network::print(narray<double> &t) {
    print_weight(28, 28, t.get_mem());
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

narray<double> &Network::feed_forward(narray<double> &a) {
    for (auto &&[b, w, af]: _zip(biases, weights, activation_functions)) {
        a = af(dot_product<narray<double>, double>(w, a) + b);
    }
    return a;
}

vector_tuple Network::back_propagation(narray<double> &x, narray<double> &y) {
//    print_image(28, 28, x.get_mem(), max_arg(y));
//    std::cin.get();
    std::vector<narray<double>> nabla_b;
    for (narray<double> &b: biases) {
        nabla_b.push_back(narray<double>(b.get_sizes()));
    }
    std::vector<narray<double>> nabla_w;
    for (narray<double> &w: weights) {
        nabla_w.push_back(narray<double>(w.get_sizes()));
    }
    narray<double> activation = x;
    std::vector<narray<double>> activations;
    activations.push_back(activation);
    std::vector<narray<double>> zs;
    for (auto &&[b, w, a]: _zip(biases, weights, activation_functions)) {
//        z = np.dot(w, activation)+b
        narray<double> z = dot_product<narray<double>, double>(w, activation) + b;
        zs.push_back(z);
//        activation = sigmoid<double, narray<double>>(z);
        activation = a(z);
        activations.push_back(activation);
    }

    narray<double> delta = cost_derivative<narray<double>>(activations[activations.size() - 1], y) *
                           sigmoid_prime<double, narray<double>>(zs[zs.size() - 1]);
    nabla_b[nabla_b.size() - 1] = delta;
    nabla_w[nabla_w.size() - 1] = dot_product<narray<double>, double>(delta,
                                                                      activations[activations.size() - 2].transpose());
    for (int l = 2; l < num_layer; l++) {
        narray<double> z = zs[zs.size() - l];
        narray<double> sp = reLU_prime<double, narray<double>>(z);
        delta = dot_product<narray<double>, double>(weights[weights.size() - l + 1].transpose(), delta) * sp;
        nabla_b[nabla_b.size() - l] = delta;
        nabla_w[nabla_w.size() - l] = dot_product<narray<double>, double>(delta, activations[activations.size() - l -
                                                                                             1].transpose());
    }
    return vector_tuple(nabla_b, nabla_w);
}

void Network::update_mini_batch(mini_batch_view mini_batch, double eta) {
    std::vector<narray<double>> nabla_b;
    for (narray<double> &b: biases) {
        nabla_b.push_back(narray<double>(b.get_sizes()));
    }
    std::vector<narray<double>> nabla_w;
    for (narray<double> &w: weights) {
        nabla_w.push_back(narray<double>(w.get_sizes()));
    }
    for (std::tuple<narray<double>, narray<double>> &tpl: mini_batch) {
        narray<double> &x = std::get<0>(tpl);
        narray<double> &y = std::get<1>(tpl);
        vector_tuple back_prp_res = back_propagation(x, y);
        std::vector<narray<double>> &delta_nabla_b = std::get<0>(back_prp_res);
        std::vector<narray<double>> &delta_nabla_w = std::get<1>(back_prp_res);
        int idx = 0;
        for (auto &&[nb, dnb]: _zip(nabla_b, delta_nabla_b)) {
            nabla_b[idx] = nb + dnb;
            idx++;
        }
        idx = 0;
        for (auto &&[nw, dnw]: _zip(nabla_w, delta_nabla_w)) {
            nabla_w[idx] = nw + dnw;
            idx++;
        }
    }
    int idx = 0;
    for (auto &&[w, nw]: _zip(weights, nabla_w)) {
        weights[idx] = w - nw * (eta / mini_batch.size());
        idx++;
    }
    idx = 0;
    for (auto &&[b, nb]: _zip(biases, nabla_b)) {
        biases[idx] = b - nb * (eta / mini_batch.size());
        idx++;
    }
}

void
Network::SGD(training_data_container &training_data, training_data_container &test_data, int epochs,
             int mini_batch_size) {
    for (int epoch = 0; epoch < epochs; epoch++) {
        std::random_shuffle(training_data.begin(), training_data.end());
        for (int k = 0; k < training_data.size(); k += mini_batch_size) {
            mini_batch_view mini_batch = mini_batch_view(training_data.begin() + k,
                                                         training_data.begin() + k + mini_batch_size);

            update_mini_batch(mini_batch, eta);
            if (k % 500 == 0) {
                print(weights[0]);
            }
        }

        unsigned count = 0;
        int idx = 0;
        for (std::tuple<narray<double>, narray<double>> &tdc: test_data) {
            idx++;
            narray<double> &a = std::get<0>(tdc);
            narray<double> &b = std::get<1>(tdc);
            int a1 = evaluate(a);
            int a2 = max_arg(b);
//            print_image(28, 28, a.get_mem(), a2, a1);
//            std::cin.get();
            if (a1 == a2) {
                count++;
            }
        }
        if (test_data.size() > 0) {
            info("Epoch {}: {} / {} % accuracy", epoch, epochs, (double) count / (double) test_data.size() * 100.f);
        } else {
            info("{} epoch from {} epochs", epoch, epochs);
        }
    }
}

void
Network::train(unsigned char *images, unsigned char *labels, unsigned image_size, unsigned int size,
               unsigned int validation_size, unsigned epochs,
               unsigned mini_batch_size) {
    training_data_container container = training_data_container(size);
    training_data_container test_data = training_data_container(validation_size);
    std::vector<double> prepared_img = std::vector<double>(image_size);
    std::vector<unsigned char> img = std::vector<unsigned char>(image_size);
    std::vector<double> vectorized = std::vector<double>(10);

    for (int i = 0; i < size; i++) {
//        std::vector<unsigned char> slice =
//                std::vector<unsigned char>(images + i * image_size,
//                                           images + image_size + i * size);
        for (int j = 0; j < image_size; j++) {
            img[j] = (*(images + j + (image_size * i)));
        }
        char_to_double_conversion(img, prepared_img);
        vectorized[*(labels + i)] = 1.f;
        narray<double> _img = narray<double>(prepared_img);
        _img.add_dim();
        narray<double> _label = narray<double>(vectorized);
        _label.add_dim();
        container[i] = std::make_tuple(_img, _label);
        vectorized[*(labels + i)] = 0.f;
    }
    for (int i = 0; i < validation_size; i++) {
//        std::vector<unsigned char> slice =
//                std::vector<unsigned char>(images + i * image_size,
//                                           images + image_size + i * size);
        for (int j = 0; j < image_size; j++) {
            img[j] = (*(images + j + (image_size * i) + (image_size * size)));
        }
        char_to_double_conversion(img, prepared_img);
        vectorized[*(labels + i + size)] = 1.f;
        narray<double> _img = narray<double>(prepared_img);
        _img.add_dim();
        narray<double> _label = narray<double>(vectorized);
        _label.add_dim();
        test_data[i] = std::make_tuple(_img, _label);
        vectorized[*(labels + i + size)] = 0.f;
    }
    SGD(container, test_data, epochs, mini_batch_size);
}

int Network::evaluate(narray<double> &image) {
    narray<double> copy = image;
    return max_arg<narray<double>>(feed_forward(copy));
}

