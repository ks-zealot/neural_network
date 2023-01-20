//
// Created by zealot on 09.01.2023.
//

#ifndef NEURONET_COUNTING_MEM_ALLOCATOR_H
#define NEURONET_COUNTING_MEM_ALLOCATOR_H

#include <memory>
#include <cstdio>
#include <unordered_map>
#include <iostream>

class counting_mem_data {
public:
    unsigned long mem_allocated = 0l;
    unsigned long mem_deallocated = 0l;
    unsigned long mem_call_allocate = 0l;
    unsigned long mem_call_deallocate = 0l;
};

template<class T>
class counting_mem_allocator {
private:
    static T *__allocate(std::size_t size) {
        ptr_map[size]++;
        int ptr = ptr_map[size];
        if (ptr > stat_map[size]) {
            free_mem();
            throw std::runtime_error("out of memory");
        }
        T *t = mem_map[size];
        return t + (ptr * size);
    }

    static void __deallocate(size_t size) {
        ptr_map[size]--;
    }

public:

    static void create_mempool(std::size_t size, int count) {
        std::allocator<T> allocator;
        stat_map[size] = count;
        ptr_map[size] = 0;
        T *t = allocator.allocate(size * count);
        std::fill_n(t, count, 0);
        mem_map[size] = allocator.allocate(size * count);
    }

    static T *allocate(std::allocator<T> &allocator, size_t size) {
        data.mem_allocated += size;
        data.mem_call_allocate++;
        if (current_label != "") {
            counting_mem_data local_data = data_map[current_label];
            local_data.mem_allocated += size;
            local_data.mem_call_allocate++;
            data_map[current_label] = local_data;
        }
        if (mem_map.empty()) {
            return allocator.allocate(size);
        } else {
            return __allocate(size);
        }
    }

    static void deallocate(std::allocator<T> &allocator, T *mem, size_t size) {
        data.mem_deallocated += size;
        data.mem_call_deallocate++;
        if (current_label != "") {
            counting_mem_data local_data = data_map[current_label];
            local_data.mem_deallocated += size;
            local_data.mem_call_deallocate++;
            data_map[current_label] = local_data;
        }
        if (mem_map.empty()) {
            allocator.deallocate(mem, size);
        } else {
            __deallocate(size);
        }
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
        std::cout << " +++++++++++++++++++++++++++++++++++++ " << std::endl;
        std::cout << " mem_allocated " << data.mem_allocated << std::endl;
        std::cout << " mem_call_allocate " << data.mem_call_allocate << std::endl;
        std::cout << " mem_deallocated " << data.mem_deallocated << std::endl;
        std::cout << " mem_call_deallocate " << data.mem_call_deallocate << std::endl;
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

    ~counting_mem_allocator() {
        free_mem();
    }

    static void free_mem() {
        std::allocator<T> allocator;
        for (const std::tuple<std::size_t, T *> &tpl: mem_map) {
            std::size_t size = std::get<0>(tpl);
            int count = stat_map[size];
            allocator.deallocate(std::get<1>(tpl), size * count);
        }
    }

private:
    static std::unordered_map<std::string, counting_mem_data> data_map;
    static std::unordered_map<std::size_t, T *> mem_map;
    static std::unordered_map<std::size_t, int> stat_map;
    static std::unordered_map<std::size_t, int> ptr_map;
    static std::string current_label;
};

#endif //NEURONET_COUNTING_MEM_ALLOCATOR_H
