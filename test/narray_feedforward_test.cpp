//
// Created by zealot on 24.01.2023.
//



#include <vector>
#include "narray/narray.h"
#include "math/math.h"

int main() {

    std::vector<double> v1 = {-0.513067, 0.544265, 0.683725,
                              0.0883649, -0.0245399, 0.661257};
    std::vector<std::vector<double>> v2 = {{-0.123067, 0.444265, 0.65625,
                                                   0.5883649, -0.02565399, 0.4441257},
                                           {-0.123067, 0.444265, 0.65625,
                                                   0.5883649, -0.02565399, 0.4441257},
                                           {-0.123067, 0.444265, 0.65625,
                                                   0.5883649, -0.02565399, 0.4441257},
                                           {-0.123067, 0.444265, 0.65625,
                                                   0.5883649, -0.02565399, 0.4441257},
                                           {-0.123067, 0.444265, 0.65625,
                                                   0.5883649, -0.02565399, 0.4441257},
                                           {-0.123067, 0.444265, 0.65625,
                                                   0.5883649, -0.02565399, 0.4441257},
    };
    std::vector<double> v3 = {-0.123067, 0.544265, 0.65625,
                              0.0883649, 0.02565399, 0.661257};
    narray<double> a = narray<double>(v1);
    narray<double> w = narray<double>(v2);
    narray<double> b = narray<double>(v3);
    a.add_dim();
    b.add_dim();
    narray<double> dp = dot_product<narray<double>, double>(w, a);
    for (double d: dp) {//[[1.09993562]      [1.09993562]        [1.09993562]        [1.09993562]        [1.09993562]        [1.09993562]]
        std::cout << d << " ";
    }
    std::cout << std::endl;
    narray<double> s =sigmoid<double, narray<double>>(dp + b);
    for (double d: s) {//[[0.72648644]        [0.83810571]        [0.85273129]        [0.76643698]        [0.75502406]        [0.85335896]]
        std::cout << d << " ";
    }

    std::cout << std::endl;
    narray<double> t = sigmoid<double, narray<double>>(dot_product<narray<double>, double>(w, a) + b);
    for (double d: t) {//[[0.62718104]        [1.29451304]        [1.40649804]        [0.83861294]        [0.77590203]        [1.41150504]]
        std::cout << d << " ";
    }
    return 0;
}