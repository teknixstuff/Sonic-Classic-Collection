#include "boxreader.h"
#include "microtar.h"
mtar_t file_box;

void box_open() {
  mtar_open(&file_box, "cd.bin", "r");
}

void box_close() {
  mtar_close(&file_box);
}

int box_read(void** data, char* name) {
  mtar_header_t h;
  if (int error = mtar_find(&file_box, name, &h)) {
	  *data = NULL;
	  return error;
  }
  *data = calloc(1, h.size + 1);
  if (int error = mtar_read_data(&file_box, *data, h.size)) {
	  free(*data);
	  *data = NULL;
	  return error;
  }
  return h.size;
}