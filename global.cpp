#include "global.h"
#include <spdlog/sinks/rotating_file_sink.h>

#include "threadpool/ThreadPool.h"

//ThreadPool threadPool = ThreadPool();
auto max_size = 1048576 * 5;
auto max_files = 3;
std::shared_ptr<spdlog::logger> file_log = spdlog::rotating_logger_mt("some_logger_name", "logs/rotating.txt", max_size,
                                                                      max_files);
const wchar_t *blocks[] = {L"\0020", L"\x2591", L"\x2592", L"\x2593", L"\x2588"};
