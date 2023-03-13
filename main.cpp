#include <ncurses.h>
#include <cstddef>
#include <iostream>
#include "threadpool/ThreadPool.h"
#include "tools/FileDownloader.h"
#include "tools/ArchiveDecompressor.h"
#include "dataset_readers/MNISTReader.h"
#include "narray/narray.h"
#include "global.h"

void print_splash() {
    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    unsigned pos = 20;
    mvaddwstr(pos, 56,
              splash1);
    pos++;
    mvaddwstr(pos, 56,
              splash2);
    pos++;
    mvaddwstr(pos, 56,
              splash3);
    pos++;
    mvaddwstr(pos, 56,
              splash4);
    pos++;
    mvaddwstr(pos, 56,
              splash5);
    pos++;
    mvaddwstr(pos, 56,
              splash6);
    pos++;
    mvaddwstr(pos, 56,
              splash7);
    pos++;
    mvaddwstr(pos, 56,
              splash8);
    pos++;
    mvaddwstr(pos, 56,
              splash9);
    pos++;
    mvaddwstr(pos, 56,
              splash10);
    pos++;
    mvaddwstr(pos, 56,
              splash11);
    pos++;
    mvaddwstr(pos, 56,
              splash12);


    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));
}

void show_prepare_screen() {
    move(28, 56);
    printw("Open dataset...");
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void show_read_screen() {
    move(30, 56);
    printw("Read files...");
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void show_train_screen() {
    move(32, 56);
    printw("Train...");
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(int argc, const char *argv[]) {
//    setlocale(LC_CTYPE, "en_US.UTF-8");
//    setlocale(LC_ALL, "");
//    initscr();
//
//    start_color();
//    init_pair(1, COLOR_GREEN, COLOR_BLACK);
//    init_pair(2, COLOR_WHITE, COLOR_WHITE);
//    print_splash();
//    clear();
//    refresh();
//    attron(COLOR_PAIR(1));
    MNISTReader reader("train-images-idx3-ubyte", "train-labels-idx1-ubyte");
//    clear();
//    refresh();
//    std::thread t1(show_prepare_screen);
    reader.prepare();
//    t1.join();
//    std::thread t2(show_read_screen);
    reader.read();
//    t2.join();
//    show_train_screen();
//    clear();
//    refresh();
//    attroff(COLOR_PAIR(1));
//    init_pair(1, COLOR_BLACK, COLOR_WHITE);
//    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    reader.train();
    reader.close();
//    endwin();
    return 0;
}
