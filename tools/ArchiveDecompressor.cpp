//
// Created by zealot on 06.12.2022.
//

#include "ArchiveDecompressor.h"
#include "logging/log.h"
#include <filesystem>
void ArchiveDecompressor::extract() {
    if (std::filesystem::exists(dest_file_name)){
        return;
    }
    FILE* dest = fopen(dest_file_name.c_str(), "wb");
    gzFile inFileZ = gzopen(file_name.c_str(), "rb");
    if (inFileZ == NULL) {
        error("Error: Failed to gzopen {}", file_name);
        exit(0);
    }
    unsigned char unzipBuffer[8192];
    unsigned int unzippedBytes;
    std::vector<unsigned char> unzippedData;
    while (true) {
        unzippedBytes = gzread(inFileZ, unzipBuffer, 8192);
        if (unzippedBytes > 0) {
            fwrite(unzipBuffer, 1,unzippedBytes, dest);
        } else {
            break;
        }
    }
    fclose(dest);
    gzclose(inFileZ);
}
