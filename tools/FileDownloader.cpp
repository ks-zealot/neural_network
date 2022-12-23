//
// Created by zealot on 06.12.2022.
//

#include "FileDownloader.h"

#include "logging/log.h"

std::size_t write_data(void *ptr, std::size_t size, std::size_t nmemb,
                       FileDownloader *source) {
    std::size_t written = fwrite(ptr, size, nmemb, source->fp);
    if (written != nmemb) {
        throw new std::runtime_error("incomplete write");
    }
    return written;
}

static std::size_t progress_function(void *clientp, curl_off_t dltotal,
                                     curl_off_t dlnow, curl_off_t ultotal,
                                     curl_off_t ulnow) {



    if (dltotal == 0.) {
//        static  Clock::time_point now = Clock::now();
//        static int i = 0;
//        milliseconds ms = std::chrono::duration_cast<milliseconds>(Clock::now() - now);
//        if (ms.count() > 100) {
//            now =  Clock::now();
//            i++;
//        }
//        const wchar_t* star = L"\x2593";
//        mvaddwstr(2, i, star);
//        if (i == 100) {
//            i = 0;
//            clear();
//            move(0,0);
//        }
//        refresh();


        return 0;
    }
    mvaddch(2, dlnow * 100 / dltotal, '#');
    refresh();
    return 0;
}

void FileDownloader::setup() {

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_function);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, this);
}

void FileDownloader::shutdown() {
    if (fp) {
        fclose(fp);
    }
    curl_easy_cleanup(curl);

}

void FileDownloader::download() {
    setlocale(LC_ALL, "");
    initscr();
    if (std::filesystem::exists(file_name)) {
        printw("File already exists");
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    } else {
        fp = fopen(file_name.c_str(), "wb");
        printw("Downloading file...");
        CURLcode code = curl_easy_perform(curl);
//       info("Error {} ",  curl_easy_strerror(code));
    }
    erase();
    refresh();
    endwin();
}
