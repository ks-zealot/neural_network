#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/system.h>
#include <ncurses.h>
#include <stdio.h>

#include <cstddef>
#include <iostream>

#include "destinations/DummyDestination.h"
#include "destinations/ImageDestination.h"
#include "global.h"
#include "mempool/data/gzChunk.h"
#include "pipes/GzPipe.h"
#include "sources/mnist/MNISTsource.h"
#include "logging/log.h"
#include "threadpool/ThreadPool.h"
#include "tools/FileDownloader.h"
#include "tools/ArchiveDecompressor.h"
#include "dataset_readers/DatasetImage.h"
#include "dataset_readers/MNISTReader.h"
#include "narray/narray.h"
#include "neural_network/Network.h"
#include "utils.h"
// struct progress {
//    char *pr;
//    size_t size;
//};
//
//
// std::size_t write_data(void *ptr, std::size_t size, std::size_t nmemb, FILE
// *stream) {
//    std::size_t written = fwrite(ptr, size, nmemb, stream);
//    return written;
//}
//
// static std::size_t progress_function(void *clientp,
//                                     curl_off_t dltotal,
//                                     curl_off_t dlnow,
//                                     curl_off_t ultotal,
//                                     curl_off_t ulnow) {
////  mvaddch(0,dlnow/dltotal * 100,'#');
//    if (dltotal == 0.) {
//        return 0;
//    }
////  std::cout << "progress " << dltotal << " " << dlnow << " " << ultotal << "
///" << ulnow << std::endl; /  std::cout <<  dlnow * 100 / dltotal  <<
///std::endl;
//    mvaddch(1,dlnow * 100 / dltotal, '#' );
//    refresh();
//    return 0;
//}
//



int main(int argc, const char *argv[]) {
//    info("start neuronet app");


//    FileDownloader downloader1("https://ossci-datasets.s3.amazonaws.com/mnist/train-images-idx3-ubyte.gz",
//                               "train-images-idx3-ubyte.gz");
//    FileDownloader downloader2("https://ossci-datasets.s3.amazonaws.com/mnist/train-labels-idx1-ubyte.gz",
//                               "train-labels-idx1-ubyte.gz");
//    ArchiveDecompressor decompressor1("train-images-idx3-ubyte.gz");
//    ArchiveDecompressor decompressor2("train-labels-idx1-ubyte.gz");
//    downloader1.setup();
//    downloader1.download();
//    downloader2.setup();
//    downloader2.download();
//    decompressor1.extract();
//    decompressor2.extract();
//    downloader1.shutdown();
//    downloader2.shutdown();
//
    MNISTReader reader("train-images-idx3-ubyte", "train-labels-idx1-ubyte");
//    reader.prepare();
//    reader.read();
//    reader.train();
//    reader.close();

 initscr();
//    start_color();
//    init_pair(1, COLOR_GREEN, COLOR_GREEN);
//    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    print_pixel(2, 0, 0);
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(100));
endwin();
//  threadPool.Start();
//
// MNISTsource MNISTsource(
//   "http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz", "mnist.gz",
// {new ImageDestination()}, {new GzPipe()});
// MNISTsource.retrieve();
//threadPool.Stop();
//  info("return");
    return 0;
    //    initscr();
    //    resizeterm(2, 100);
    //    char* version =  curl_version();
    //    std::cout << version << std::endl;
    //    CURL *curl;
    //    FILE *fp;
    //    CURLcode res;
    //    const  char *url =
    //    "http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz";
    ////  const char* url =
    ///"https://dumps.wikimedia.org/other/pagecounts-raw/2016/2016-08/pagecounts-20160801-000000.gz";
    //    char outfilename[FILENAME_MAX] = "mnist.gz";
    //    curl = curl_easy_init();
    //    if (curl) {
    //        printw("Downloading file...");
    //        refresh();
    //        fp = fopen(outfilename,"wb");
    //        curl_easy_setopt(curl, CURLOPT_URL, url);
    //        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    //        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    //        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_function);
    //        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
    //        struct progress data;
    //
    //        /* pass struct to callback  */
    //        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &data);
    //// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    //        res = curl_easy_perform(curl);
    //
    //        /* always cleanup */
    //        curl_easy_cleanup(curl);
    //        fclose(fp);
    //        refresh();
    //    }
    //    endwin();
    //    return 0;
}
