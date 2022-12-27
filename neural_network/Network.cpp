//
// Created by zealot on 08.12.2022.
//

#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <valarray>

#include "Network.h"
#include "utils/vector_util.h"
#include "math/math.h"
#include "utils.h"

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
        sigmoid<float, narray<float>>(weights[0]);
    }
    endwin();
}

narray<float> &Network::feed_forward(narray<float> &a) {

    for (narray<float> w: weights) {
        narray<float> v = w.dot_product(a) + biases[0];
        sigmoid<float, narray<float>>(v);
        a = v;
    }
    return a;
}

std::tuple<std::vector<narray<float>>, std::vector<narray<float>>>
Network::back_propagation(narray<float> &x, narray<float> &y) {
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
    activations.push_back(std::move(activation));
    std::vector<narray<float>> zs;
    for (auto &&[b, w]: _zip(biases, weights)) {
//        z = np.dot(w, activation)+b
        narray<float> dp = w.dot_product(activation);
        narray<float> z = dp + b;
        zs.push_back(std::move(z));
        sigmoid<float, narray<float>>(z);
        activation = z;
        activations.push_back(std::move(activation));// тут проследить, чтобы каждый раз была копия
    }
//    delta = self.cost_derivative(activations[-1], y) * \
//            sigmoid_prime(zs[-1])
    narray<float> prime = zs[zs.size() - 1];
    sigmoid_prime<float, narray<float>>(prime);
    narray<float> delta = cost_derivative(activations[activations.size() - 1], y) * prime;
    nabla_b[nabla_b.size() - 1] = delta;
    nabla_w[nabla_w.size() - 1] = delta.dot_product(activations[activations.size() - 2].transpose());
    for (int l = 2; l != num_layer; l++) {
        narray<float> z = zs[zs.size() - l];
        narray<float> sp = zs[zs.size() - l];
        sigmoid_prime<float, narray<float>>(sp);
        delta = weights[weights.size() - l].transpose().dot_product(delta) * sp;
        nabla_b[-l] = delta;
        nabla_w[-l] = delta.dot_product(activations[-l - 1].transpose());
    }
    return std::tuple<std::vector<narray<float>>, std::vector<narray<float>>>(nabla_b, nabla_w);//todo объявить тип
}

void Network::update_mini_butch(
        view<std::vector<std::tuple<narray<float>, narray<float>>>::iterator, std::tuple<narray<float>,
                narray<float>>> mini_batch, float eta) {
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
        std::tuple<std::vector<narray<float>>, std::vector<narray<float>>> back_prp_res = back_propagation(x, y);
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
Network::SGD(std::vector<std::tuple<narray<float>, narray<float>>> training_data, int epochs, int mini_butch_size,
             float eta) {
    for (int epoch = 0; epoch < epochs; epoch++) {
        std::random_shuffle(training_data.begin(), training_data.end());
        for (int k = 0; k < training_data.size() - mini_butch_size; k + mini_butch_size) {
            view < std::vector<std::tuple<narray < float>, narray < float>>>::iterator, std::tuple<narray < float>,
                    narray < float>>> mini_butch = view < std::vector<std::tuple<narray < float>,
                    narray < float>>>::iterator, std::tuple<narray < float>,
                    narray < float>>>(training_data.begin() + k,
                    training_data.begin() + k + mini_butch_size); //todo объявить тип
            update_mini_butch(mini_butch, eta);

            //todo обрабатывать тест дата
        }
    }
}
