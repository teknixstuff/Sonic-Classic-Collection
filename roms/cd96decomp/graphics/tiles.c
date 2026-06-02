#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cmp.h"
#include "../cmpheader.h"
#include "../cmptilemeta.h"
#include "../constants.h"
#include "../szdd.h"
#include "../boxreader.h"
#include "bitmapmanipulation.h"
#include "planelayout.h"
#include "screen.h"
#include "../GAME/TITLE/COMMON/SMORPHDATA.h"
static int load_tile_bitmaps_internal(unsigned char** pp_bitmap_data, unsigned char** pp_bitmaps, char* p_filename, int (*p_alt_palette_info)[2], int version_cnt);
static void add_flip_tile_bitmaps(unsigned char* p_data, unsigned char** pp_bitmaps, int tile_cnt, int tile_length);
static void add_rotate_tile_bitmaps(unsigned char* p_data, unsigned char** pp_bitmaps, int tile_cnt, int tile_length);
static void blit_plane_internal(unsigned char* p_pixelbuffer, unsigned short(*p_plane)[PLANE_WIDTH_TILES], int scanline_padding, unsigned short* p_hscroll, unsigned short vscroll, unsigned char waterflag, short hintposi, unsigned int start_y);
static unsigned char* blit_scanline(unsigned char* p_pixelbuffer, unsigned short* p_plane_row, unsigned short hscroll, unsigned short tile_row);
static unsigned char* blit_scanline_water(unsigned char* p_pixelbuffer, unsigned short* p_plane_row, unsigned short hscroll, unsigned short tile_row);
static unsigned char* blit_tile_line(unsigned char* p_pixelbuffer, unsigned char* p_pixels, unsigned int pixel_cnt);
static unsigned char* blit_tile_line_water(unsigned char* p_pixelbuffer, unsigned char* p_pixels, unsigned int pixel_cnt);

static unsigned char* gp_tile_bitmap_data = 0;
static unsigned char* g_tile_bitmaps[TILE_BITMAPS_MAX] = { 0 };
static unsigned char* gp_tile_change_bitmap_data = 0;
static unsigned char* g_tile_change_bitmaps[TILE_CHANGE_BITMAPS_MAX] = { 0 };
static unsigned char* gp_stamp_bitmap_data = 0;
static unsigned char* g_stamp_bitmaps[STAMP_BITMAPS_MAX] = { 0 };
static unsigned short g_planes[PLANES_MAX][PLANE_HEIGHT_TILES][PLANE_WIDTH_TILES] = { 0 };
static unsigned short g_stamp_map[STAMP_MAP_HEIGHT][STAMP_MAP_WIDTH] = { 0 };
static smorph_data* gp_smorph_data = 0;
static int g_stamp_bitmap_cnt = 0;


void load_tile_bitmaps(char* p_filename, int (*p_alt_palette_info)[2]) {
  int cnt = load_tile_bitmaps_internal(&gp_tile_bitmap_data, g_tile_bitmaps, p_filename, p_alt_palette_info, TILE_VERSIONS);

  add_flip_tile_bitmaps(gp_tile_bitmap_data, g_tile_bitmaps, cnt, TILE_LENGTH);
}


void load_tile_change_bitmaps(char* p_filename) {
  int cnt = load_tile_bitmaps_internal(&gp_tile_change_bitmap_data, g_tile_change_bitmaps, p_filename, 0, TILE_VERSIONS);

  add_flip_tile_bitmaps(gp_tile_change_bitmap_data, g_tile_change_bitmaps, cnt, TILE_LENGTH);
}


void load_stamp_bitmaps(char* p_filename) {
  /* Keep the first stamp's entries empty to serve as transparent. */
  g_stamp_bitmap_cnt = load_tile_bitmaps_internal(&gp_stamp_bitmap_data, &g_stamp_bitmaps[STAMP_VERSIONS], p_filename, 0, STAMP_VERSIONS);

  add_rotate_tile_bitmaps(gp_stamp_bitmap_data, &g_stamp_bitmaps[STAMP_VERSIONS], g_stamp_bitmap_cnt, STAMP_LENGTH);
  add_flip_tile_bitmaps(gp_stamp_bitmap_data, &g_stamp_bitmaps[STAMP_VERSIONS], g_stamp_bitmap_cnt * 2, STAMP_LENGTH);
}


static int load_tile_bitmaps_internal(unsigned char** pp_bitmap_data, unsigned char** pp_bitmaps, char* p_filename, int (*p_alt_palette_info)[2], int version_cnt) {
  unsigned char* p_bytes_start = szdd_decompress(p_filename);
  unsigned char* p_bytes = p_bytes_start;
  cmp_header header;
  cmp_tile_meta meta;
  unsigned long bitmap_data_size = 0;
  int palette_info[PALETTE_LINES_MAX][2] = {
    { 0, 16 },
    { 0, 32 },
    { 0, 48 },
    { 0, 64 }
  };
  int (*p_palette_info)[2] = palette_info;

  p_bytes = read_cmp_header(p_bytes, &header);
  p_bytes = read_cmp_tile_meta(p_bytes, &meta, header.cnt);
  palette_info[0][0] = meta.palette_line_cnt[0];
  palette_info[1][0] = meta.palette_line_cnt[1];
  palette_info[2][0] = meta.palette_line_cnt[2];
  palette_info[3][0] = meta.palette_line_cnt[3];
  bitmap_data_size = header.cnt * meta.p_dimensions[0][0] * meta.p_dimensions[0][1];
  *pp_bitmap_data = malloc(bitmap_data_size * version_cnt);
  if (*pp_bitmap_data == 0) {
    fprintf(stderr, "Could not allocate memory for tile bitmap data.\n");
    abort();
  }
  if (p_alt_palette_info != 0) {
    p_palette_info = p_alt_palette_info;
  }
  extract_tiles(*pp_bitmap_data, pp_bitmaps, p_bytes, header.cnt, meta, p_palette_info);
  free(meta.p_dimensions);
  free(p_bytes_start);

  return header.cnt;
}


static void add_flip_tile_bitmaps(unsigned char* p_data, unsigned char** pp_bitmaps, int tile_cnt, int tile_length) {
  int tile_size = tile_length * tile_length;
  int old_index;

  for (old_index = tile_cnt - 1; old_index >= 0; --old_index) {
    int new_index = old_index * 4;
    unsigned char* p_source = &p_data[old_index * tile_size];
    unsigned char* p_destination = &p_data[new_index * tile_size];

    memcpy(p_destination, p_source, tile_size);
    pp_bitmaps[new_index] = p_destination;
    p_source = p_destination;

    p_destination = &p_data[(new_index + HFLIP) * tile_size];
    hflip_bitmap(p_destination, p_source, tile_length, tile_length);
    pp_bitmaps[new_index + HFLIP] = p_destination;

    p_destination = &p_data[(new_index + VFLIP) * tile_size];
    vflip_bitmap(p_destination, p_source, tile_length, tile_length);
    pp_bitmaps[new_index + VFLIP] = p_destination;

    p_destination = &p_data[(new_index + HVFLIP) * tile_size];
    hvflip_bitmap(p_destination, p_source, tile_length, tile_length);
    pp_bitmaps[new_index + HVFLIP] = p_destination;
  }
}


static void add_rotate_tile_bitmaps(unsigned char* p_data, unsigned char** pp_bitmaps, int tile_cnt, int tile_length) {
  int tile_size = tile_length * tile_length;
  int old_index;

  for (old_index = tile_cnt - 1; old_index >= 0; --old_index) {
    int new_index = old_index * 2;
    unsigned char* p_source = &p_data[old_index * tile_size];
    unsigned char* p_destination = &p_data[new_index * tile_size];

    memcpy(p_destination, p_source, tile_size);
    pp_bitmaps[new_index] = p_destination;
    p_source = p_destination;

    p_destination = &p_data[(new_index + 1) * tile_size];
    rot90r_bitmap(p_destination, p_source, tile_length, tile_length);
    pp_bitmaps[new_index + 1] = p_destination;
  }
}


void unload_tile_bitmaps(void) {
  if (gp_tile_bitmap_data != 0) {
    free(gp_tile_bitmap_data);
    gp_tile_bitmap_data = 0;
  }
  if (gp_tile_change_bitmap_data != 0) {
    free(gp_tile_change_bitmap_data);
    gp_tile_change_bitmap_data = 0;
  }
  if (gp_stamp_bitmap_data != 0) {
    free(gp_stamp_bitmap_data);
    gp_stamp_bitmap_data = 0;
  }
  memset(g_tile_bitmaps, 0, sizeof(g_tile_bitmaps));
  memset(g_tile_change_bitmaps, 0, sizeof(g_tile_change_bitmaps));
  memset(g_stamp_bitmaps, 0, sizeof(g_stamp_bitmaps));
  memset(g_planes, 0, sizeof(g_planes));
  memset(g_stamp_map, 0, sizeof(g_stamp_map));
}


void set_plane_tile(int base, int x, int y, int block, int frip) {
  unsigned short index = (unsigned int)block & 0x7FF;
  unsigned short flip = (((unsigned int)frip ^ (unsigned int)block) >> 11) & FLIP_MASK;

  if (index == 0) {
    if (base != 0) {
      g_planes[PLANE_B][y][x] = 0;
    }
    else {
      g_planes[PLANE_A_HI][y][x] = 0;
      g_planes[PLANE_A_LO][y][x] = 0;
    }
  }
  else {
    index = index * 4 + flip;
    if (base != 0) {
      g_planes[PLANE_B][y][x] = index;
    }
    else if (block & PRIORITY_MASK) {
      g_planes[PLANE_A_HI][y][x] = index;
      g_planes[PLANE_A_LO][y][x] = 0;
    }
    else {
      g_planes[PLANE_A_HI][y][x] = 0;
      g_planes[PLANE_A_LO][y][x] = index;
    }
  }
}


void set_special_plane_tile(int x, int y, int block) {
  unsigned short index = (unsigned int)block & 0x7FF;

  g_planes[PLANE_A_HI][y][x] = index * 4;
}


void change_tile_bitmap(int tile_id, int bmp_id) {
  unsigned long tile_index = tile_id * 4;
  unsigned long tile_change_index = bmp_id * 4;

  g_tile_bitmaps[tile_index] = g_tile_change_bitmaps[tile_change_index];
  g_tile_bitmaps[tile_index + HFLIP] = g_tile_change_bitmaps[tile_change_index + HFLIP];
  g_tile_bitmaps[tile_index + VFLIP] = g_tile_change_bitmaps[tile_change_index + VFLIP];
  g_tile_bitmaps[tile_index + HVFLIP] = g_tile_change_bitmaps[tile_change_index + HVFLIP];
}


void load_plane_layout(plane_layout layout) {
  unsigned short* p_buffer = 0;
  int y, x;
  int file_size = box_read((void**)&p_buffer, layout.p_filename);
  if (file_size < 1) {
	fprintf(stderr, "Could not read %s, error %i.\n", layout.p_filename, file_size);
    abort();
  }

  for (y = 0; y < layout.height; ++y) {
    unsigned int tile_y = layout.start_y + y;

    for (x = 0; x < layout.width; ++x) {
      unsigned int tile_x = layout.start_x + x;
      unsigned short block = p_buffer[y * layout.width + x];
      unsigned short index = block & 0x7FF;
      unsigned short flip = block >> 11 & FLIP_MASK;

      if (index != 0) {
        index += layout.index_base;
        index = index * 4 + flip;
      }
      else if (layout.clear) {
        index = 0;
      }
      else {
        index = layout.index_base * 4;
      }
      g_planes[layout.plane][tile_y][tile_x] = index;
    }
  }

  free(p_buffer);
}


void set_stamp_map(unsigned short* p_data, int width, int height) {
  int y, x;

  for (y = 0; y < height; ++y) {
    for (x = 0; x < width; ++x) {
      set_stamp_map_stamp(x, y, *p_data);
      ++p_data;
    }
  }
}

void set_stamp_map_stamp(int x, int y, int block) {
  int index = (block & 0x7FF) / 4;
  int flip_rot = block >> 13 & ROTATE_MASK;

  if (index > g_stamp_bitmap_cnt) {
    index = 0;
  }
  if (index != 0) {
    index *= STAMP_VERSIONS;

    switch (flip_rot) {
      case 4: index += 1; break;
      case 6: index += 2; break;
      case 2: index += 3; break;
      case 3: index += 4; break;
      case 5: index += 6; break;
      case 7: index += 5; break;
      case 1: index += 7; break;
    }
  }
  g_stamp_map[y][x] = index;
}


void set_stamp_bitmap(unsigned short location, unsigned short new_index) {
  g_stamp_bitmaps[location] = g_stamp_bitmaps[new_index];
}


void set_smorph_data(void* p_data) {
  gp_smorph_data = p_data;
}


void blit_plane(unsigned char* p_pixelbuffer, int plane_id, int scanline_padding, unsigned short* p_hscroll, unsigned short vscroll, unsigned char waterflag, short hintposi, unsigned int start_y) {
  blit_plane_internal(p_pixelbuffer, g_planes[plane_id], scanline_padding, p_hscroll, vscroll, waterflag, hintposi, start_y);
}


static void blit_plane_internal(unsigned char* p_pixelbuffer, unsigned short(*p_plane)[PLANE_WIDTH_TILES], int scanline_padding, unsigned short* p_hscroll, unsigned short vscroll, unsigned char waterflag, short hintposi, unsigned int start_y) {
  unsigned int screen_y = start_y;

  p_pixelbuffer += start_y * (SCREEN_WIDTH_PX + scanline_padding);
  p_hscroll += start_y;

  if (waterflag == 0) {
    for ( ; screen_y < hintposi + 1; ++screen_y) {
      unsigned short plane_y = vscroll / TILE_LENGTH % PLANE_HEIGHT_TILES;
      unsigned short* p_plane_row = p_plane[plane_y];
      unsigned short tile_row = vscroll % TILE_LENGTH;

      p_pixelbuffer = blit_scanline(p_pixelbuffer, p_plane_row, *p_hscroll, tile_row);
      p_pixelbuffer += scanline_padding;
      ++p_hscroll;
      ++vscroll;
    }
  }
  for ( ; screen_y < SCREEN_HEIGHT_PX; ++screen_y) {
    unsigned short plane_y = vscroll / TILE_LENGTH % PLANE_HEIGHT_TILES;
    unsigned short* p_plane_row = p_plane[plane_y];
    unsigned short tile_row = vscroll % TILE_LENGTH;

    p_pixelbuffer = blit_scanline_water(p_pixelbuffer, p_plane_row, *p_hscroll, tile_row);
    p_pixelbuffer += scanline_padding;
    ++p_hscroll;
    ++vscroll;
  }
}


static unsigned char* blit_scanline(unsigned char* p_pixelbuffer, unsigned short* p_plane_row, unsigned short hscroll, unsigned short tile_row) {
  hscroll -= TILE_LENGTH * 5; // center widescreen
  unsigned short plane_x = hscroll / TILE_LENGTH % PLANE_WIDTH_TILES;
  unsigned short tile = p_plane_row[plane_x];
  unsigned char* p_pixels = &g_tile_bitmaps[tile][tile_row * TILE_LENGTH];
  unsigned short left_overhang = hscroll % TILE_LENGTH;
  int i;

  if (left_overhang == 0) {
    if (tile != 0) {
      p_pixelbuffer = blit_tile_line(p_pixelbuffer, p_pixels, TILE_LENGTH);
    }
    else {
      p_pixelbuffer += TILE_LENGTH;
    }
  }
  else {
    if (tile != 0) {
      p_pixels += left_overhang;
      p_pixelbuffer = blit_tile_line(p_pixelbuffer, p_pixels, TILE_LENGTH - left_overhang);
    }
    else {
      p_pixelbuffer += TILE_LENGTH - left_overhang;
    }
  }

  for (i = 0; i < SCREEN_WIDTH_TILES - 1; ++i) {
    ++plane_x;
    plane_x %= PLANE_WIDTH_TILES;
    tile = p_plane_row[plane_x];
    if (tile != 0) {
      p_pixels = &g_tile_bitmaps[tile][tile_row * TILE_LENGTH];
      p_pixelbuffer = blit_tile_line(p_pixelbuffer, p_pixels, TILE_LENGTH);
    }
    else {
      p_pixelbuffer += TILE_LENGTH;
    }
  }

  if (left_overhang != 0) {
    ++plane_x;
    plane_x %= PLANE_WIDTH_TILES;
    tile = p_plane_row[plane_x];
    if (tile != 0) {
      p_pixels = &g_tile_bitmaps[tile][tile_row * TILE_LENGTH];
      p_pixelbuffer = blit_tile_line(p_pixelbuffer, p_pixels, left_overhang);
    }
    else {
      p_pixelbuffer += left_overhang;
    }
  }

  return p_pixelbuffer;
}


static unsigned char* blit_scanline_water(unsigned char* p_pixelbuffer, unsigned short* p_plane_row, unsigned short hscroll, unsigned short tile_row) {
  hscroll -= TILE_LENGTH * 5; // center widescreen
  unsigned short plane_x = hscroll / TILE_LENGTH % PLANE_WIDTH_TILES;
  unsigned short tile = p_plane_row[plane_x];
  unsigned char* p_pixels = &g_tile_bitmaps[tile][tile_row * TILE_LENGTH];
  unsigned short left_overhang = hscroll % TILE_LENGTH;
  int i;

  if (left_overhang == 0) {
    if (tile != 0) {
      p_pixelbuffer = blit_tile_line_water(p_pixelbuffer, p_pixels, TILE_LENGTH);
    }
    else {
      p_pixelbuffer += TILE_LENGTH;
    }
  }
  else {
    if (tile != 0) {
      p_pixels += left_overhang;
      p_pixelbuffer = blit_tile_line_water(p_pixelbuffer, p_pixels, TILE_LENGTH - left_overhang);
    }
    else {
      p_pixelbuffer += TILE_LENGTH - left_overhang;
    }
  }

  for (i = 0; i < SCREEN_WIDTH_TILES - 1; ++i) {
    ++plane_x;
    plane_x %= PLANE_WIDTH_TILES;
    tile = p_plane_row[plane_x];
    if (tile != 0) {
      p_pixels = &g_tile_bitmaps[tile][tile_row * TILE_LENGTH];
      p_pixelbuffer = blit_tile_line_water(p_pixelbuffer, p_pixels, TILE_LENGTH);
    }
    else {
      p_pixelbuffer += TILE_LENGTH;
    }
  }

  if (left_overhang != 0) {
    ++plane_x;
    plane_x %= PLANE_WIDTH_TILES;
    tile = p_plane_row[plane_x];
    if (tile != 0) {
      p_pixels = &g_tile_bitmaps[tile][tile_row * TILE_LENGTH];
      p_pixelbuffer = blit_tile_line_water(p_pixelbuffer, p_pixels, left_overhang);
    }
    else {
      p_pixelbuffer += left_overhang;
    }
  }

  return p_pixelbuffer;
}


static unsigned char* blit_tile_line(unsigned char* p_pixelbuffer, unsigned char* p_pixels, unsigned int pixel_cnt) {
  int i;

  for (i = 0; i < pixel_cnt; ++i) {
    if (*p_pixels != 0) {
      *p_pixelbuffer = *p_pixels;
    }
    ++p_pixelbuffer;
    ++p_pixels;
  }

  return p_pixelbuffer;
}


static unsigned char* blit_tile_line_water(unsigned char* p_pixelbuffer, unsigned char* p_pixels, unsigned int pixel_cnt) {
  int i;

  for (i = 0; i < pixel_cnt; ++i) {
    if (*p_pixels != 0) {
      *p_pixelbuffer = *p_pixels + WATER_PALETTE_OFFSET;
    }
    ++p_pixelbuffer;
    ++p_pixels;
  }

  return p_pixelbuffer;
}


void blit_smorphed_plane(unsigned char* p_pixelbuffer, int scanline_padding, int start_y, int height, int source_width, int tile_length, int use_plane_a) {
  unsigned short* p_source_plane = &g_stamp_map[0][0];
  unsigned char** pp_source_bitmaps = g_stamp_bitmaps;
  int screen_y, screen_x;

  if (gp_smorph_data == 0) return;

  if (use_plane_a != 0) {
    p_source_plane = &g_planes[PLANE_A_HI][0][0];
    pp_source_bitmaps = g_tile_bitmaps;
  }
  p_pixelbuffer += start_y * (SCREEN_WIDTH_PX + scanline_padding);

  for (screen_y = 0; screen_y < height; ++screen_y) {
    int fp_source_x = gp_smorph_data[screen_y].StartX;
    int fp_source_y = gp_smorph_data[screen_y].StartY;

    for (screen_x = 0; screen_x < SCREEN_WIDTH_PX; ++screen_x) {
      int source_x = fp_source_x / 0x10000;
      int source_y = fp_source_y / 0x10000;
      unsigned char pixel = 0;
      if (source_x >= 0 && source_x < 0x1000 && source_y >= 0 && source_y < 0x1000) {
        unsigned int tile_x = source_x / tile_length;
        unsigned int tile_y = source_y / tile_length;
        unsigned short tile = p_source_plane[tile_y * source_width + tile_x];
        if (tile != 0) {
          unsigned int row_offset = source_y % tile_length * tile_length;
          unsigned int column_offset = source_x % tile_length;

          pixel = pp_source_bitmaps[tile][row_offset + column_offset];
        }
      }
      if (pixel != 0) {
        *p_pixelbuffer = pixel;
      }
      ++p_pixelbuffer;
      fp_source_x += gp_smorph_data[screen_y].DeltaX;
      fp_source_y += gp_smorph_data[screen_y].DeltaY;
    }

    p_pixelbuffer += scanline_padding;
  }
}
