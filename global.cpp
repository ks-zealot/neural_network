#include "global.h"
#include <spdlog/sinks/rotating_file_sink.h>

#include "threadpool/ThreadPool.h"

//ThreadPool threadPool = ThreadPool();
auto max_size = 1048576 * 5;
auto max_files = 3;
std::shared_ptr<spdlog::logger> file_log = spdlog::rotating_logger_mt("some_logger_name", "logs/rotating.txt", max_size,max_files);
const wchar_t *       splash1 = L"/‾‾‾‾‾/      /‾‾‾‾‾‾‾‾‾/   /‾‾‾‾‾‾‾‾‾‾/   /‾‾/       /‾‾‾‾‾‾‾‾/ /‾‾‾‾‾‾‾‾‾‾/";
const wchar_t *       splash2 = L"‾‾‾/ /      / /‾‾‾‾‾‾‾‾   /  (‾‾‾‾)  /   /  /       / /‾‾‾‾/ /  ‾‾‾‾/ /‾‾‾‾";
const wchar_t *       splash3 = L"  / /      /  ‾‾‾‾‾‾‾/   /  /‾‾‾‾/  /   /  /       / /    / /      / /        ";
const wchar_t *       splash4 = L" / /＿＿  / /‾‾‾‾‾‾‾‾   /  /    /  /   /  /       / /    / /      / /         ";
const wchar_t *       splash5 = L"/＿＿＿/ /  ‾‾‾‾‾‾‾‾/  /＿/    /＿/   /   ‾‾‾‾/  / /＿＿/ /      / /          ";
const wchar_t *       splash6 = L"         ‾‾‾‾‾‾‾‾‾‾                   ‾‾‾‾‾‾‾‾   ‾‾‾‾‾‾‾‾‾       ‾‾          ";
const wchar_t *       splash7 = L"    /‾‾‾‾‾/  /‾‾‾‾‾‾‾‾/ /‾‾‾‾‾\\        /‾‾‾‾‾‾‾ \\                          ";
const wchar_t *       splash8 = L"   / /‾‾‾   / /    / / / /‾‾‾/ )      /  /‾‾‾‾‾) /                          ";
const wchar_t *       splash9 = L"  / /      / /    / / / /＿＿/ /     /  /＿＿＿/ /                           ";
const wchar_t *       splash10 =L" / /      / /    / / / /‾‾‾\\ \\      /   ＿＿＿＿ /                            ";
const wchar_t *       splash11 =L"/  ‾‾‾/  / /    / / / /     \\ \\    /  / ＿                                   ";
const wchar_t *       splash12 =L"‾‾‾‾‾‾   ‾‾‾‾‾‾‾‾‾  ‾‾        ‾‾   ‾‾  (＿)                                  ";
const wchar_t *blocks[] = {L"\0020", L"\x2591", L"\x2592", L"\x2593", L"\x2588"};

