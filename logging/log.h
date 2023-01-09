#pragma once
#include "global.h"
#include <spdlog/spdlog.h>

template<typename ... Args>
void info(const char * fmt, Args... args) {
    if (fmt == NULL) {
        return;
    }
 file_log->info(fmt, std::forward<Args>(args)...);
 spdlog::info(fmt,std::forward<Args>(args)... );
}
template<typename ... Args>
void error(const char * fmt, Args... args) {
if (fmt == NULL) {
    return;
}
    file_log->error(fmt, std::forward<Args>(args)...);
    spdlog::info(fmt,std::forward<Args>(args)... );
}