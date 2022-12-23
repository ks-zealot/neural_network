#pragma once

#include "destinations/destination.h"
#include "mempool/data/Image.h"
enum ImageState {
  START,
  AWAIT_NUMBER_OF_IMAGES,
  AWAIT_NUMBER_OF_ROWS,
  AWAIT_NUMBER_OF_COLUMNS,
  IMAGE_PROCESSING
};
ImageState& operator++(ImageState& state);
ImageState operator++(ImageState& state, int);

class ImageDestination : public Destination {
 private:
  ImageState state = START;
  unsigned int Magic;
  unsigned int NumberOfImages;
  unsigned int NumberOfRows;
  unsigned int NumberOfColumns;
  unsigned char bytesNeed = 4;
  void combineNumber(unsigned int& Number, unsigned char& c);
  Image* currentImage;

 public:
  virtual void eat(void* v);
};
