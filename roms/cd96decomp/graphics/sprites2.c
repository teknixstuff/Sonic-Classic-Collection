#include "sprites2.h"
#include <stdio.h>
#include <string.h>
#include "spriteinfo.h"

static sprite_info sprites[512] = { 0 };


sprite_info* get_sprites2(void) {
  return sprites;
}


void set_sprite2(int rank, short x, short y, unsigned short index, short reverse) {
  if (x >= 0) {
    sprites[rank].x = x;
  }
  if (y >= 0) {
    sprites[rank].y = y;
  }
  sprites[rank].index = index;
  if (reverse >= 0) {
    sprites[rank].reverse = reverse;
  }
}


void set_sprite2_info(int rank, sprite_info info) {
  set_sprite2(rank, info.x, info.y, info.index, info.reverse);
}


void set_string_sprites2(char* p_string, int length, int rank, short x, short y, int char_width, unsigned short(*get_char_sprite_index)(char)) {
  int i = 0;

  while (*p_string != 0) {
    sprites[rank].x = x;
    sprites[rank].y = y;
    sprites[rank].index = get_char_sprite_index(*p_string);
    sprites[rank].reverse = 0;
    ++p_string;
    ++rank;
    x += char_width;
    ++i;
  }

  for ( ; i < length; ++i, ++rank) {
    sprites[rank].index = 0;
  }
}


void set_number_sprites2(unsigned char number, int rank, short x, short y, int digit_width, unsigned short(*get_char_sprite_index)(char)) {
  char buf[3];

  sprintf(buf, "%02d", number);
  set_string_sprites2(buf, 2, rank, x, y, digit_width, get_char_sprite_index);
}


void clear_sprites2(void) {
  memset(sprites, 0, sizeof(sprites));
}
