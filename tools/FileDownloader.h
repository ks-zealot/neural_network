//
// Created by zealot on 06.12.2022.
//
#include <string>
#include "curl/curl.h"
#include <string>
#include <ncurses.h>
#include <fstream>
#include <filesystem>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds


#ifndef NEURONET_FILEDOWNLOADER_H
#define NEURONET_FILEDOWNLOADER_H

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;
class FileDownloader {
public:
    FileDownloader(std::string url, std::string file_name) : url(url), file_name(file_name) {
    };

private:
    CURL *curl;
    std::string  url;
    std::string file_name;
public:
    void setup();
    void shutdown();
    void download();

    FILE *fp = 0;
};


#endif //NEURONET_FILEDOWNLOADER_H
