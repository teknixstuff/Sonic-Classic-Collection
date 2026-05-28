#ifndef PLANELAYOUT_H
#define PLANELAYOUT_H

typedef struct plane_layout {
  unsigned char plane;
  unsigned char start_x;
  unsigned char start_y;
  unsigned char width;
  unsigned char height;
  short index_base;
  char clear;
  char* p_filename;
}
plane_layout;

#endif
