#include "bitmapmanipulation.h"


void hflip_bitmap(unsigned char* p_output, unsigned char* p_input, int width, int height) {
  int y, x;

  /* Move to the last pixel of the first line. */
  p_input += width - 1;

  for (y = 0; y < height; ++y) {
    for (x = 0; x < width; ++x) {
      *p_output++ = *p_input--;
    }

    /* We're now at the last pixel of the previous line. */
    /* Move to the last pixel of the next line. */
    p_input += width * 2;
  }
}


void vflip_bitmap(unsigned char* p_output, unsigned char* p_input, int width, int height) {
  int y, x;

  /* Move to the first pixel of the last line. */
  p_input += width * (height - 1);

  for (y = 0; y < height; ++y) {
    for (x = 0; x < width; ++x) {
      *p_output++ = *p_input++;
    }

    /* We're now at the first pixel of the next line. */
    /* Move to the first pixel of the previous line. */
    p_input -= width * 2;
  }
}


void hvflip_bitmap(unsigned char* p_output, unsigned char* p_input, int width, int height) {
  int y, x;

  /* Move to the last pixel of the last line. */
  p_input += width * height - 1;

  for (y = 0; y < height; ++y) {
    for (x = 0; x < height; ++x) {
      *p_output++ = *p_input--;
    }
  }
}


void rot90r_bitmap(unsigned char* p_output, unsigned char* p_input, int width, int height) {
  int y, x;

  for (y = 0; y < height; ++y) {
    /* Move to a pixel on the last line. */
    unsigned char* p_source = &p_input[width * (height - 1) + y];

    for (x = 0; x < width; ++x) {
      *p_output++ = *p_source;
      p_source -= height;
    }
  }
}
