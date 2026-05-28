#ifndef TILES_H
#define TILES_H

#include "planelayout.h"

void load_tile_bitmaps(char* p_filename, int (*p_alt_palette_info)[2]);
void load_tile_change_bitmaps(char* p_filename);
void load_stamp_bitmaps(char* p_filename);
void unload_tile_bitmaps(void);
void set_plane_tile(int base, int x, int y, int block, int frip);
void set_special_plane_tile(int x, int y, int block);
void change_tile_bitmap(int tile_id, int bmp_id);
void load_plane_layout(plane_layout layout);
void set_stamp_map(unsigned short* p_data, int width, int height);
void set_stamp_map_stamp(int x, int y, int block);
void set_stamp_bitmap(unsigned short location, unsigned short new_index);
void set_smorph_data(void* p_data);
void blit_plane(unsigned char* p_pixelbuffer, int plane_id, int scanline_padding, unsigned short* p_hscroll, unsigned short vscroll, unsigned char waterflag, short hintposi, unsigned int start_y);
void blit_smorphed_plane(unsigned char* p_pixelbuffer, int scanline_padding, int start_y, int height, int source_width, int tile_length, int use_plane_a);

#endif
