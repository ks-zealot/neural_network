//
// Created by zealot on 09.01.2023.
//

#include "counting_mem_allocator.h"

counting_mem_data counting_mem_allocator::data;
std::string counting_mem_allocator::current_label = "";
std::map<std::string, counting_mem_data> counting_mem_allocator::data_map;