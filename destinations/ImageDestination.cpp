#include "destinations/ImageDestination.h"

#include <curl/curl.h>

#include <cstring>
#include <iterator>

#include "mempool/data/Chunk.h"
#include "pipes/Pipe.h"
#include "utils.h"
ImageState& operator++(ImageState& state) {
  state = static_cast<ImageState>(state + 1);
  return state;
};

ImageState operator++(ImageState& state, int) {
  ImageState rVal = state;
  ++state;
  return rVal;
};

void ImageDestination::combineNumber(unsigned int& Number, unsigned char& c) {
  Number = Number | (c << (8 * (4 - bytesNeed)));
  bytesNeed--;
  state++;
  if (bytesNeed == 0) {
    if (state == IMAGE_PROCESSING) {
      bytesNeed = NumberOfRows * NumberOfColumns;

    } else {
      bytesNeed = 4;
    }
  }
}

void ImageDestination::eat(void* eat) {
  Chunk* chunk = static_cast<Chunk*>(eat);
  unsigned char localData[1024];
  std::copy(std::begin(chunk->data), std::end(chunk->data), localData);
  int readed = 0;
  if (state != IMAGE_PROCESSING) {
    for (int i = 0; i < chunk->size; i++) {
      switch (state) {
        case START:
          combineNumber(Magic, localData[i]);
          if (Magic != 0x00000803) {
            throw -1;
          }

          break;
        case AWAIT_NUMBER_OF_IMAGES:
          combineNumber(NumberOfImages, localData[i]);
          break;
        case AWAIT_NUMBER_OF_ROWS:
          combineNumber(NumberOfRows, localData[i]);
        case AWAIT_NUMBER_OF_COLUMNS:
          combineNumber(NumberOfColumns, localData[i]);
        default:
          break;
      }
    }
  }
  if (currentImage == nullptr) {
    currentImage = new Image(NumberOfColumns, NumberOfRows);
  }
  int SizeToCopy = chunk->size;
  if (SizeToCopy > NumberOfColumns * NumberOfRows) {
    SizeToCopy = NumberOfColumns * NumberOfImages;
  }
  memcpy(currentImage->data + (NumberOfColumns * NumberOfRows - bytesNeed),
         chunk->data + readed, SizeToCopy);
  bytesNeed -= SizeToCopy;
  if (bytesNeed == 0) {
    bytesNeed = NumberOfColumns * NumberOfRows;
    printImage(NumberOfRows, NumberOfColumns, currentImage->data);
//    pipe->write(currentImage);
    currentImage = nullptr;
  }

  delete chunk;
}
