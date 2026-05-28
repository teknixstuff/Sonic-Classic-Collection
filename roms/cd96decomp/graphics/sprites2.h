#ifndef SPRITES2_H
#define SPRITES2_H

#include "spriteinfo.h"

sprite_info* get_sprites2(void);
void set_sprite2(int rank, short x, short y, unsigned short index, short reverse);
void set_sprite2_info(int rank, sprite_info info);
void set_string_sprites2(char* p_string, int length, int rank, short x, short y, int char_width, unsigned short(*get_char_sprite_index)(char));
void set_number_sprites2(unsigned char number, int rank, short x, short y, int digit_width, unsigned short(*get_char_sprite_index)(char));
void clear_sprites2(void);

#endif
