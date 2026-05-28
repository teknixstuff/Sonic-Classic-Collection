#ifndef RAWBITMAP_H
#define RAWBITMAP_H

typedef struct raw_bitmap {
  unsigned char* p_data;
  unsigned short width;
  unsigned short height;
}
raw_bitmap;

raw_bitmap load_raw_bitmap(char* p_filename, int palette_offset, int has_transparency);

#endif
