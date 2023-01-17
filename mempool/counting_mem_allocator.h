//
// Created by zealot on 09.01.2023.
//

#ifndef NEURONET_COUNTING_MEM_ALLOCATOR_H
#define NEURONET_COUNTING_MEM_ALLOCATOR_H

#include <memory>
#include <cstdio>
#include <map>
#include <iostream>

class counting_mem_data {
public:
    unsigned long mem_allocated = 0l;
    unsigned long mem_deallocated = 0l;
    unsigned long mem_call_allocate = 0l;
    unsigned long mem_call_deallocate = 0l;
};

class counting_mem_allocator {
public:

    template<typename T>
    static T *allocate( std::allocator<T> &allocator, size_t size) {
        data.mem_allocated += size;
        data.mem_call_allocate++;
        if (current_label != "") {
            counting_mem_data local_data = data_map[current_label];
            local_data.mem_allocated += size;
            local_data.mem_call_allocate++;
            data_map[current_label] = local_data;
        }
        return allocator.allocate(size);
    }

    template<typename T>
    static void deallocate(std::allocator<T> &allocator, T *mem, size_t size) {
        data.mem_deallocated += size;
        data.mem_call_deallocate++;
        if (current_label != "") {
            counting_mem_data local_data = data_map[current_label];
            local_data.mem_deallocated += size;
            local_data.mem_call_deallocate++;
            data_map[current_label] = local_data;
        }
        allocator.deallocate(mem, size);
    }

    static void print_profiling() {
        for (const std::tuple<std::string, counting_mem_data> &tpl: data_map) {
            std::cout << " Data for label " << std::get<0>(tpl) << std::endl;
            std::cout << " +++++++++++++++++++++++++++++++++++++ " << std::endl;
            counting_mem_data local_data = std::get<1>(tpl);
            std::cout << " mem_allocated " << local_data.mem_allocated << std::endl;
            std::cout << " mem_call_allocate " << local_data.mem_call_allocate << std::endl;
            std::cout << " mem_deallocated " << local_data.mem_deallocated << std::endl;
            std::cout << " mem_call_deallocate " << local_data.mem_call_deallocate << std::endl;
        }
    }

    static void put_label(std::string label) {
        current_label = label;
        counting_mem_data local_data;
        data_map[label] = local_data;
    }

    static void remove_label(std::string label) {
        current_label = "";
    }

    static counting_mem_data data;


private:
    static std::map<std::string, counting_mem_data> data_map;
    static std::string current_label;
};

#endif //NEURONET_COUNTING_MEM_ALLOCATOR_H
