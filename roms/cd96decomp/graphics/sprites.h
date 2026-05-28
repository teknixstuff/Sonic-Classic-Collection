#ifndef SPRITES_H
#define SPRITES_H

#include "spriteinfo.h"

void load_sprite_bitmaps(char* p_filename, unsigned char(*p_sprbmp)[3]);
void load_opening_sprite_bitmaps(char* p_filename);
void load_menu_sprite_bitmaps(char* p_filename, int* p_palette_offsets);
void load_extra_sprite_bitmap(char* p_filename, int palette_offset, int has_transparency);
void unload_sprite_bitmaps(void);
void set_sprite(short x, short y, unsigned short index, unsigned short linkdata, unsigned short reverse);
void blit_sprites_lo(unsigned char* p_pixelbuffer, int scanline_padding, unsigned char waterflag, short hintposi);
void blit_sprites_hi(unsigned char* p_pixelbuffer, int scanline_padding, unsigned char waterflag, short hintposi);
void blit_sprites2(unsigned char* p_pixelbuffer, sprite_info* p_list, int scanline_padding);

#endif
