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

//[784, 30, 10]
void Network::init() {
    num_layer = sizes.size();
    biases.emplace_back(std::vector({sizes[1]}), random_filler<float>::GetInstance());
    biases.emplace_back(std::vector({sizes[2]}), random_filler<float>::GetInstance());
    weights.emplace_back(std::vector({sizes[0], sizes[1]}), random_filler<float>::GetInstance());
    weights.emplace_back(std::vector({sizes[1], sizes[2]}), random_filler<float>::GetInstance());
}


void Network::print() {
    for (narray<float> &n: weights) {
        sigmoid<float, narray<float>>(n);
    }
    initscr();
    while (true) {
        print_weight(28, 28, weights[0].at({0, 0}));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        weights[0] += narray<float>({28 * 28, 30}, random_filler<float>::GetInstance());
        weights[0] = sigmoid<float, narray<float>>(weights[0]);
    }
    endwin();
}

narray<float> &Network::feed_forward(narray<float> &a) {

    for (narray<float> w: weights) {
        narray<float> v = dot_product<narray<float>, float>(w, a) + biases[0];
        a = sigmoid<float, narray<float>>(v);
    }
    return a;
}

training_data_tuple Network::back_propagation(narray<float> &x, narray<float> &y) {
    std::vector<narray<float>> nabla_b;
    for (narray<float> &b: biases) {
        nabla_b.push_back(narray<float>(b.get_sizes()));
    }
    std::vector<narray<float>> nabla_w;
    for (narray<float> &w: weights) {
        nabla_w.push_back(narray<float>(w.get_sizes()));
    }
    narray<float> activation = x;//copy
    std::vector<narray<float>> activations;
    activations.push_back(activation);
    std::vector<narray<float>> zs;
    for (auto &&[b, w]: _zip(biases, weights)) {
//        z = np.dot(w, activation)+b
        narray<float> z = dot_product<narray<float>, float>(w, activation) + b;
        zs.push_back(z);
        activation = sigmoid<float, narray<float>>(z);
        activations.push_back(activation);// тут проследить, чтобы каждый раз была копия
    }
//    delta = self.cost_derivative(activations[-1], y) * \
//            sigmoid_prime(zs[-1])
    narray<float> delta = cost_derivative(activations[activations.size() - 1], y) *
                          sigmoid_prime<float, narray<float>>(zs[zs.size() - 1]);
    nabla_b.insert(nabla_b.cbegin() + (nabla_b.size() - 1), delta);
    nabla_w.insert(nabla_w.cbegin() + (nabla_w.size() - 1),
                   dot_product<narray<float>, float>(delta, activations[activations.size() - 2]));
    //по ходу тут транспонирование е нужно
    for (int l = 2; l != num_layer; l++) {
        narray<float> z = zs[zs.size() - l + 1];
        delta = dot_product<narray<float>, float>(weights[weights.size() - l + 1], delta) *
                sigmoid_prime<float, narray<float>>(zs[zs.size() - l + 1]);
        nabla_b.insert(nabla_b.cbegin() + (nabla_b.size() - l + 1), delta);
        narray<float> a = activations[activations.size() - l + 1];
        nabla_w.insert(nabla_w.cbegin() + (nabla_w.size() - l + 1),
                       dot_product<narray<float>, float>(delta, activations[activations.size() - l + 1]));
    }
    return training_data_tuple(nabla_b, nabla_w);
}

void Network::update_mini_butch(mini_batch_view mini_batch, float eta) {
    std::vector<narray<float>> nabla_b;
    for (narray<float> &b: biases) {
        nabla_b.push_back(narray<float>(b.get_sizes()));
    }
    std::vector<narray<float>> nabla_w;
    for (narray<float> &w: weights) {
        nabla_w.push_back(narray<float>(w.get_sizes()));
    }
    for (std::tuple<narray<float>, narray<float>> &tpl: mini_batch) {
        narray<float> &x = std::get<0>(tpl);
        narray<float> &y = std::get<1>(tpl);
        training_data_tuple back_prp_res = back_propagation(x, y);
        std::vector<narray<float>> &delta_nabla_b = std::get<0>(back_prp_res);
        std::vector<narray<float>> &delta_nabla_w = std::get<1>(back_prp_res);
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

        idx = 0;
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
}

void
Network::SGD(training_data_container &training_data, int epochs, int mini_batch_size) {
    for (int epoch = 0; epoch < epochs; epoch++) {
        std::random_shuffle(training_data.begin(), training_data.end());
        for (int k = 0; k < training_data.size() / mini_batch_size; k += mini_batch_size) {
            mini_batch_view mini_butch = mini_batch_view(training_data.begin() + (k * mini_batch_size),
                                                         training_data.begin() + ((k + 1) * mini_batch_size));
            update_mini_butch(mini_butch, eta);

            //todo обрабатывать тест дата
        }
        info("{} epoch from {} epochs", epoch, epochs);
    }
}

void
Network::train(unsigned char *images, unsigned char *labels, unsigned image_size, unsigned int size, unsigned epochs,
               unsigned mini_batch_size) {
    training_data_container container = training_data_container(size);
    std::vector<float> prepared_img = std::vector<float>(image_size);
    std::vector<unsigned char> img = std::vector<unsigned char>(image_size);
    std::vector<float> vectorized = std::vector<float>(10);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < image_size; j++) {
            img[j] = (*(images + j + (image_size * i)));
        }//todo заменить на инсерт с вьюшкой
        char_to_float_conversion(img, prepared_img);
        vectorized[*(labels + i)] = 1.f;
        container[i] = std::make_tuple(narray<float>(prepared_img), narray<float>(vectorized));
        vectorized[*(labels + i)] = 0.f;
//        img.clear();
//        prepared_img.clear();
    }
    SGD(container, epochs, mini_batch_size);
}

int Network::evaluate(narray<float> &image) {
    return max_arg<narray<float>>(feed_forward(image));
}

