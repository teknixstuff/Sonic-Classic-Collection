#ifndef CMPBMP_H
#define CMPBMP_H

#include <stdio.h>
#include "cmpheader.h"
#include "cmpspritemeta.h"
#include "cmptilemeta.h"
#include "graphics/rawbitmap.h"

unsigned char* read_cmp_header(unsigned char* p_bytes, cmp_header* header);
void read_cmp_header_file(FILE* fp, cmp_header* header);
unsigned char* read_cmp_sprite_meta(unsigned char* p_bytes, cmp_sprite_meta** pp_meta, unsigned long sprite_cnt);
unsigned char* read_cmp_tile_meta(unsigned char* p_bytes, cmp_tile_meta* p_meta, unsigned long tile_cnt);
void extract_sprites(raw_bitmap* p_bitmap, unsigned char* p_input, unsigned long cnt, cmp_sprite_meta* p_meta);
void extract_opening_sprites(raw_bitmap* p_bitmap, unsigned char* p_input, unsigned long cnt, cmp_sprite_meta* p_meta);
void extract_tiles(unsigned char* p_output, unsigned char** pp_output, unsigned char* p_input, unsigned long cnt, cmp_tile_meta meta, int (*p_palette_info)[2]);

#endif
