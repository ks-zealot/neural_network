#include "MNISTsource.h"

#include <cstdint>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>

#include <cstddef>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include "logging/log.h"

#include "mempool/data/gzChunk.h"
#include "pipes/FilePipe.h"

std::size_t write_data(void* ptr, std::size_t size, std::size_t nmemb,
                       MNISTsource* source) {
  std::size_t written = source->write(ptr, size, nmemb);
  return written;
}

static std::size_t progress_function(void* clientp, curl_off_t dltotal,
                                     curl_off_t dlnow, curl_off_t ultotal,
                                     curl_off_t ulnow) {
  if (dltotal == 0.) {
    return 0;
  }
  mvaddch(1, dlnow * 100 / dltotal, '#');
  refresh();
  return 0;
}

std::size_t MNISTsource::write(void* mem, std::size_t size, std::size_t nmem) {
//  info("allocate data and write to destination");
//  gzChunk* gzChunk1 = new struct gzChunk();
//  gzChunk1->size = nmem;
//  memcpy(&gzChunk1->data, mem, nmem);

  //pipe->write(gzChunk1);
  info("allocate data and write to file");
  gzChunk* gzChunk = new struct gzChunk();
  gzChunk->size = nmem;
  memcpy(&gzChunk->data, mem, nmem);
  filePipe.write(gzChunk);
  return nmem;
}

void MNISTsource::retrieve() {
  if (std::filesystem::exists(this->targetFile)) {
info( "file exist, no need to download");
    std::ifstream file(this->targetFile, std::ios::binary);
    std::uintmax_t filesize = std::filesystem::file_size(this->targetFile);
    info("file size {}", filesize);
    char buffer[1024];
    while (!file.eof()) {
      file.read(buffer, 1024);
      gzChunk* gzChunk = new struct gzChunk();
      std::copy(std::begin(buffer), std::end(buffer),
                std::begin(gzChunk->data));
      gzChunk->size = 1024;
      pipe->write(gzChunk);
    }
    info("file readed");
  } else {
    initscr();
    printw("Downloading file...");
    refresh();
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_function);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, this);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    refresh();
    endwin();
  //  info("close file pipe");
//    filePipe.close();

  }
}
