#pragma once

#include "threadpool/ThreadPool.h"
#include <spdlog/logger.h>

extern ThreadPool threadPool;
extern std::shared_ptr<spdlog::logger> file_log;
extern const wchar_t *blocks[];

