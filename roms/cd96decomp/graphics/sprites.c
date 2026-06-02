#include "sprites.h"
#include <stdlib.h>
#include <string.h>
#include "../cmp.h"
#include "../cmpheader.h"
#include "../cmpspritemeta.h"
#include "../constants.h"
#include "../szdd.h"
#include "rawbitmap.h"
#include "spriteinfo.h"
static void blit_sprites(unsigned char* p_pixelbuffer, int scanline_padding, unsigned int hi_prio, unsigned char waterflag, short hintposi);
static void blit_sprite(unsigned char* p_pixelbuffer, raw_bitmap bitmap, int scanline_padding, int x, int y, int h_dir, int v_dir, unsigned char waterflag, short hintposi);
static void blit_sprite_line(unsigned char* p_pixelbuffer, unsigned char* p_pixels, unsigned int pixel_cnt, int h_dir);
static void blit_sprite_line_water(unsigned char* p_pixelbuffer, unsigned char* p_pixels, unsigned int pixel_cnt, int h_dir);

static raw_bitmap g_sprite_bitmaps[SPRITE_BITMAPS_MAX] = { 0 };
static sprite_info g_sprites[SPRITES_MAX] = { 0 };
static int g_sprite_bitmap_cnt = 0;
static int g_sprite_cnt = 0;


void load_sprite_bitmaps(char* p_filename, unsigned char (*p_sprbmp)[3]) {
  unsigned char* p_bytes_start = szdd_decompress(p_filename);
  unsigned char* p_bytes = p_bytes_start;
  cmp_header header;
  cmp_sprite_meta* p_meta;
  int i;

  p_bytes = read_cmp_header(p_bytes, &header);
  p_bytes = read_cmp_sprite_meta(p_bytes, &p_meta, header.cnt);
  extract_sprites(g_sprite_bitmaps, p_bytes, header.cnt, p_meta);
  g_sprite_bitmap_cnt = header.cnt;

  for (i = 0; i < header.cnt; ++i) {
    p_sprbmp[i][0] = p_meta[i].width;
    p_sprbmp[i][1] = p_meta[i].height;
  }

  free(p_meta);
  free(p_bytes_start);
}


void load_opening_sprite_bitmaps(char* p_filename) {
  int palette_offsets[34] = { 16, 16, 32, 32, 48, 48, 48, 48, 64, 64, 64, 64, 64, 64, 64, 16, 16, 32, 16, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };
  unsigned char* p_bytes_start = szdd_decompress(p_filename);
  unsigned char* p_bytes = p_bytes_start;
  cmp_header header;
  cmp_sprite_meta* p_meta;
  int i;

  p_bytes = read_cmp_header(p_bytes, &header);
  p_bytes = read_cmp_sprite_meta(p_bytes, &p_meta, header.cnt);

  /* Patch incorrect metadata. */
  p_meta[31].width = 16;
  p_meta[31].height = 8;

  for (i = 0; i < header.cnt; ++i) {
    /* Patch incorrect metadata. */
    p_meta[i].width = (p_meta[i].width + 7) / 8 * 8;
    p_meta[i].palette_offset = palette_offsets[i];
  }

  extract_opening_sprites(&g_sprite_bitmaps[1], p_bytes, header.cnt, p_meta);
  g_sprite_bitmap_cnt = header.cnt + 1;

  free(p_meta);
  free(p_bytes_start);
}


void load_menu_sprite_bitmaps(char* p_filename, int* p_palette_offsets) {
  unsigned char* p_bytes_start = szdd_decompress(p_filename);
  unsigned char* p_bytes = p_bytes_start;
  cmp_header header;
  cmp_sprite_meta* p_meta;
  int i;

  p_bytes = read_cmp_header(p_bytes, &header);
  p_bytes = read_cmp_sprite_meta(p_bytes, &p_meta, header.cnt);

  for (i = 0; i < header.cnt; ++i) {
    /* Patch incorrect metadata. */
    p_meta[i].palette_offset = p_palette_offsets[i];
  }

  extract_sprites(&g_sprite_bitmaps[1], p_bytes, header.cnt, p_meta);
  g_sprite_bitmap_cnt = header.cnt + 1;

  free(p_meta);
  free(p_bytes_start);
}


void load_extra_sprite_bitmap(char* p_filename, int palette_offset, int has_transparency) {
  raw_bitmap bitmap = load_raw_bitmap(p_filename, palette_offset, has_transparency);

  g_sprite_bitmaps[g_sprite_bitmap_cnt++] = bitmap;
}


void unload_sprite_bitmaps(void) {
  int i;

  for (i = 0; i < g_sprite_bitmap_cnt; ++i) {
    free(g_sprite_bitmaps[i].p_data);
  }

  memset(g_sprite_bitmaps, 0, sizeof(g_sprite_bitmaps));
}


void set_sprite(short x, short y, unsigned short index, unsigned short linkdata, unsigned short reverse) {
  if (index == 0) {
    g_sprites[linkdata].index = 0;
  }
  else {
    g_sprites[linkdata].x = x - 128;
    g_sprites[linkdata].y = y - 128;
    g_sprites[linkdata].index = index;
    g_sprites[linkdata].reverse = reverse;
  }

  g_sprite_cnt = linkdata;
}


void blit_sprites_lo(unsigned char* p_pixelbuffer, int scanline_padding, unsigned char waterflag, short hintposi) {
  blit_sprites(p_pixelbuffer, scanline_padding, 0, waterflag, hintposi);
}


void blit_sprites_hi(unsigned char* p_pixelbuffer, int scanline_padding, unsigned char waterflag, short hintposi) {
  blit_sprites(p_pixelbuffer, scanline_padding, 1, waterflag, hintposi);
}


static void blit_sprites(unsigned char* p_pixelbuffer, int scanline_padding, unsigned int hi_prio, unsigned char waterflag, short hintposi) {
  int i;

  for (i = g_sprite_cnt - 1; i >= 0; --i) {
    sprite_info info = g_sprites[i];

    if (info.index != 0 && !!(g_sprites[i].reverse & PRIORITY_MASK) == hi_prio) {
      raw_bitmap bitmap = g_sprite_bitmaps[info.index];

      switch (g_sprites[i].reverse & FLIP_MASK) {
        case NOFLIP: blit_sprite(p_pixelbuffer, bitmap, scanline_padding, info.x, info.y, 1, 1, waterflag, hintposi); break;
        case HFLIP: blit_sprite(p_pixelbuffer, bitmap, scanline_padding, info.x, info.y, -1, 1, waterflag, hintposi); break;
        case VFLIP: blit_sprite(p_pixelbuffer, bitmap, scanline_padding, info.x, info.y, 1, -1, waterflag, hintposi); break;
        case HVFLIP: blit_sprite(p_pixelbuffer, bitmap, scanline_padding, info.x, info.y, -1, -1, waterflag, hintposi); break;
      }
    }
  }
}


void blit_sprites2(unsigned char* p_pixelbuffer, sprite_info* p_list, int scanline_padding) {
  int i;

  for (i = 0; i < 512; ++i) {
    raw_bitmap bitmap = g_sprite_bitmaps[p_list[i].index];

    switch (p_list[i].reverse) {
      case NOFLIP: blit_sprite(p_pixelbuffer, bitmap, scanline_padding, p_list[i].x, p_list[i].y, 1, 1, 0, SCREEN_HEIGHT_PX - 1); break;
      case HFLIP: blit_sprite(p_pixelbuffer, bitmap, scanline_padding, p_list[i].x, p_list[i].y, -1, 1, 0, SCREEN_HEIGHT_PX - 1); break;
      case VFLIP: blit_sprite(p_pixelbuffer, bitmap, scanline_padding, p_list[i].x, p_list[i].y, 1, -1, 0, SCREEN_HEIGHT_PX - 1); break;
      case HVFLIP: blit_sprite(p_pixelbuffer, bitmap, scanline_padding, p_list[i].x, p_list[i].y, -1, -1, 0, SCREEN_HEIGHT_PX - 1); break;
    }
  }
}


static void blit_sprite(unsigned char* p_pixelbuffer, raw_bitmap bitmap, int scanline_padding, int x, int y, int h_dir, int v_dir, unsigned char waterflag, short hintposi) {
  x += TILE_LENGTH * 5; // center widescreen
  int x_end = x + bitmap.width;
  int y_end = y + bitmap.height;
  int x_skip = 0;
  int y_skip = 0;

  if (x >= SCREEN_WIDTH_PX) return;
  if (x_end <= 0) return;
  if (y >= SCREEN_HEIGHT_PX) return;
  if (y_end <= 0) return;

  if (x < 0) {
    x_skip = -x * h_dir;
    x = 0;
  }
  if (x_end > SCREEN_WIDTH_PX) {
    x_end = SCREEN_WIDTH_PX;
  }
  if (y < 0) {
    y_skip = -y * v_dir;
    y = 0;
  }
  if (y_end > SCREEN_HEIGHT_PX) {
    y_end = SCREEN_HEIGHT_PX;
  }

  p_pixelbuffer += y * (SCREEN_WIDTH_PX + scanline_padding);
  if (h_dir == -1) {
    // Move to the last pixel of the line.
    bitmap.p_data += bitmap.width - 1;
  }
  if (v_dir == -1) {
    // Move to the last line.
    bitmap.p_data += bitmap.width * (bitmap.height - 1);
  }
  bitmap.p_data += y_skip * bitmap.width;

  if (waterflag == 0) {
    int y_start_water = y_end > hintposi + 1 ? hintposi + 1 : y_end;

    while (y < y_start_water) {
      blit_sprite_line(p_pixelbuffer + x, bitmap.p_data + x_skip, x_end - x, h_dir);
      p_pixelbuffer += SCREEN_WIDTH_PX + scanline_padding;
      bitmap.p_data += bitmap.width * v_dir;
      ++y;
    }
  }

  while (y < y_end) {
    blit_sprite_line_water(p_pixelbuffer + x, bitmap.p_data + x_skip, x_end - x, h_dir);
    p_pixelbuffer += SCREEN_WIDTH_PX + scanline_padding;
    bitmap.p_data += bitmap.width * v_dir;
    ++y;
  }
}


static void blit_sprite_line(unsigned char* p_pixelbuffer, unsigned char* p_pixels, unsigned int pixel_cnt, int h_dir) {
  int i;

  for (i = 0; i < pixel_cnt; ++i) {
    if (*p_pixels != SPRITE_TRANSPARENT_COLOR) {
      *p_pixelbuffer = *p_pixels;
    }
    ++p_pixelbuffer;
    p_pixels += h_dir;
  }
}


static void blit_sprite_line_water(unsigned char* p_pixelbuffer, unsigned char* p_pixels, unsigned int pixel_cnt, int h_dir) {
  int i;

  for (i = 0; i < pixel_cnt; ++i) {
    if (*p_pixels != SPRITE_TRANSPARENT_COLOR) {
      *p_pixelbuffer = *p_pixels + WATER_PALETTE_OFFSET;
    }
    ++p_pixelbuffer;
    p_pixels += h_dir;
  }
}
