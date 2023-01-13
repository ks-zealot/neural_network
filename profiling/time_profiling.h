//
// Created by zealot on 13.01.2023.
//

#ifndef NEURONET_TIME_PROFILING_H
#define NEURONET_TIME_PROFILING_H


#include <string>
#include <chrono>
#include <map>
#include "logging/log.h"

class time_profiling {

public:
    static void set_label(std::string label){
//        if (time_map.contains("calculate_nabla_w") || label == "calculate_nabla_w") {
            time_map[label] = std::chrono::system_clock::now();
//        }
    }


    static void measure(std::string label){
//        if (time_map.contains("calculate_nabla_w") || label == "calculate_nabla_w") {
            std::chrono::duration<double> diff = std::chrono::system_clock::now() - time_map[label];
            time_map.erase(label);
            info("time for label {} : {} ", label, diff.count());
//        }
    }

private:
    static std::map<std::string, std::chrono::time_point<std::chrono::system_clock> > time_map;
};


#endif //NEURONET_TIME_PROFILING_H
