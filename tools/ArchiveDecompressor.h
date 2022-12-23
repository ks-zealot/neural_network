//
// Created by zealot on 06.12.2022.
//
#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <stdexcept>
#include <zlib.h>
#ifndef NEURONET_ARCHIVEDECOMPRESSOR_H
#define NEURONET_ARCHIVEDECOMPRESSOR_H


class ArchiveDecompressor {
public:
    ArchiveDecompressor(std::string  file_name) : file_name (file_name){
        dest_file_name = file_name.substr(0, file_name.find_last_of('.'));
    }
private:
    std::string file_name;
    std::string dest_file_name;

public:
    void extract();
};


#endif //NEURONET_ARCHIVEDECOMPRESSOR_H
