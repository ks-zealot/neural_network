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
#include "profiling/time_profiling.h"

void print_matrix(narray<float> &array) {
    for (int i = 0; i < 28; i++) {//todo хардкод
        for (int j = 0; j < 28; j++) {
            float t = *(array.at({0, j + (i * 28) }));
            std::cout << " " << t;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
};

//[784, 30, 10]
void Network::init() {
    num_layer = sizes.size();
    biases.push_back(narray<float>(std::vector({sizes[1], 1}), random_filler<float>::GetInstance()));
    biases.push_back(narray<float>(std::vector({sizes[2], 1}), random_filler<float>::GetInstance()));
    weights.push_back(narray<float>(std::vector({sizes[1], sizes[0]}), random_filler<float>::GetInstance()));
    weights.push_back(narray<float>(std::vector({sizes[2], sizes[1]}), random_filler<float>::GetInstance()));


}


void Network::print(narray<float> &t) {
    print_weight(28, 28, t.at({0, 0}));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

narray<float> &Network::feed_forward(narray<float> &a) {
    for (auto &&[b, w]: _zip(biases, weights)) {
        a = sigmoid<float, narray<float>>(dot_product<narray<float>, float>(w, a) + b);
    }
    return a;
}

training_data_tuple Network::back_propagation(narray<float> &x, narray<float> &y) {
    std::vector<narray<float>> nabla_b;
    for (narray<float> &b: biases) {
        nabla_b.push_back(narray<float>(b.get_sizes()));//todo не нужно, просто заранее задать размер вектора
    }
    std::vector<narray<float>> nabla_w;
    for (narray<float> &w: weights) {
        nabla_w.push_back(narray<float>(w.get_sizes()));
    }
    narray<float> activation = x;//copy
    std::vector<narray<float>> activations;
    activations.push_back(activation);
    std::vector<narray<float>> zs;
//    time_profiling::set_label("calculate_activations");
    for (auto &&[b, w]: _zip(biases, weights)) {
//        z = np.dot(w, activation)+b
        narray<float> z = dot_product<narray<float>, float>(w, activation) + b;

        zs.push_back(z);
        activation = sigmoid<float, narray<float>>(z);
//        print_matrix(z);
//        std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
        activations.push_back(activation);
    }
//    time_profiling::measure("calculate_activations");
//    delta = self.cost_derivative(activations[-1], y) * \
//            sigmoid_prime(zs[-1])
//    narray<float> sp = sigmoid_prime<float, narray<float>>(zs[zs.size() - 1]);
//    narray<float> cd = cost_derivative<narray<float>>(activations[activations.size() - 1], y);
//    time_profiling::set_label("calculate_delta");
    narray<float> delta = cost_derivative<narray<float>>(activations[activations.size() - 1], y) *
                          sigmoid_prime<float, narray<float>>(zs[zs.size() - 1]);
//    time_profiling::measure("calculate_delta");
//    print_matrix(zs[zs.size() - 1]);
//    std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
//    print_matrix(activations[activations.size() - 1]);
//
//    std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
//    print_matrix(delta);
//    time_profiling::set_label("calculate_nabla");
    nabla_b[nabla_b.size() - 1] = delta;
    nabla_w[nabla_w.size() - 1] = dot_product<narray<float>, float>(delta,
                                                                    activations[activations.size() - 2].transpose());
//    time_profiling::measure("calculate_nabla");
//    time_profiling::set_label("calculate_bp");
    for (int l = 2; l < num_layer; l++) {
        narray<float> z = zs[zs.size() - l];
//        time_profiling::set_label("calculate_sigmoid_prime");
        narray<float> sp = sigmoid_prime<float, narray<float>>(z);
//        time_profiling::measure("calculate_sigmoid_prime");
//        time_profiling::set_label("calculate_delta");
        delta = dot_product<narray<float>, float>(weights[weights.size() - l + 1].transpose(), delta) * sp;
//        time_profiling::measure("calculate_delta");
        nabla_b[nabla_b.size() - l] = delta;
//        time_profiling::set_label("calculate_nabla_w");
        nabla_w[nabla_w.size() - l] = dot_product<narray<float>, float>(delta, activations[activations.size() - l -
                                                                                           1].transpose());
//        time_profiling::measure("calculate_nabla_w");
    }
//    time_profiling::measure("calculate_bp");
//    print_matrix(nabla_w[0]);
//    std::cout << std::endl;
//    print_matrix(nabla_w[1]);
    return training_data_tuple(nabla_b, nabla_w);
}

void Network::update_mini_batch(mini_batch_view mini_batch, float eta) {
    std::vector<narray<float>> nabla_b;
    for (narray<float> &b: biases) {
        nabla_b.push_back(narray<float>(b.get_sizes()));
    }
    std::vector<narray<float>> nabla_w;
    for (narray<float> &w: weights) {
        nabla_w.push_back(narray<float>(w.get_sizes()));
    }
    for (std::tuple<narray<float>, narray<float>> &tpl: mini_batch) {
//        info("+++++++++++++++++++++++++++++++++++++");
        narray<float> &x = std::get<0>(tpl);
        narray<float> &y = std::get<1>(tpl);
//        time_profiling::set_label("back_propagation");
        training_data_tuple back_prp_res = back_propagation(x, y);
//        time_profiling::measure("back_propagation");
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
//        info("+++++++++++++++++++++++++++++++++++++");
    }
}

void
Network::SGD(training_data_container &training_data, training_data_container &test_data, int epochs,
             int mini_batch_size) {
    for (int epoch = 0; epoch < epochs; epoch++) {
        time_profiling::set_label("epoch");
        std::random_shuffle(training_data.begin(), training_data.end());
//        counting_mem_allocator::put_label("update_mini_batch");
        for (int k = 0; k < training_data.size() / mini_batch_size; k += mini_batch_size) {
            mini_batch_view mini_batch = mini_batch_view(training_data.begin() + (k * mini_batch_size),
                                                         training_data.begin() + ((k + 1) * mini_batch_size));
//            narray<float> t = weights[0][0];
//            print_matrix(t);
//            std::cout << " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

            update_mini_batch(mini_batch, eta);

//            t -= weights[0][0];
//            print_matrix(weights[0]);
//            print(t);
        }
//        counting_mem_allocator::remove_label("update_mini_batch");
        time_profiling::measure("epoch");

//        counting_mem_allocator::put_label("evaluate");
        unsigned count = 0;
        mini_batch_view mini_batch = mini_batch_view(test_data.begin() ,
                                                     test_data.end() );
        time_profiling::set_label("validation");
        for (std::tuple<narray<float>, narray<float>> &tdc: mini_batch) {
            narray<float>& a =std::get<0>(tdc);
            narray<float>& b =std::get<0>(tdc);
            if (evaluate(a) == max_arg(b)) {
                count++;
            }

        }
        if (test_data.size() > 0) {
            info("Epoch {}: {} / {}", epoch, epochs, (float) count / (float) test_data.size() * 100.f);
        } else {
            info("{} epoch from {} epochs", epoch, epochs);
        }
//        counting_mem_allocator::remove_label("evaluate");
        time_profiling::measure("validation");
    }
}

void
Network::train(unsigned char *images, unsigned char *labels, unsigned image_size, unsigned int size,
               unsigned int validation_size, unsigned epochs,
               unsigned mini_batch_size) {
    training_data_container container = training_data_container(size);
    training_data_container test_data = training_data_container(validation_size);
    std::vector<float> prepared_img = std::vector<float>(image_size);
    std::vector<unsigned char> img = std::vector<unsigned char>(image_size);
    std::vector<float> vectorized = std::vector<float>(10);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < image_size; j++) {
            img[j] = (*(images + j + (image_size * i)));
        }//todo заменить на инсерт с вьюшкой
        char_to_float_conversion(img, prepared_img);
        vectorized[*(labels + i)] = 1.f;
        narray<float> _img = narray<float>(prepared_img);
        _img.add_dim();
        narray<float> _label = narray<float>(vectorized);
        _label.add_dim();
        container[i] = std::make_tuple(_img, _label);
        vectorized[*(labels + i)] = 0.f;
    }
    for (int i = 0; i < validation_size; i++) {
        for (int j = 0; j < image_size; j++) {
            img[j] = (*(images + j + (image_size * i)));
        }
        //todo заменить на инсерт с вьюшкой
        char_to_float_conversion(img, prepared_img);
        vectorized[*(labels + i)] = 1.f;
        narray<float> _img = narray<float>(prepared_img);
        _img.add_dim();
        narray<float> _label = narray<float>(vectorized);
        _label.add_dim();
        test_data[i] = std::make_tuple(_img, _label);
        vectorized[*(labels + i)] = 0.f;
    }
    SGD(container, test_data, epochs, mini_batch_size);

}

int Network::evaluate(narray<float>& image) {
    narray<float> copy = image;
    return max_arg<narray<float>>(feed_forward(copy));
}

