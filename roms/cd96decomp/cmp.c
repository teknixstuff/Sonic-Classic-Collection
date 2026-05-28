#include "cmp.h"
#include <stdio.h>
#include <stdlib.h>
#include "cmpheader.h"
#include "cmpspritemeta.h"
#include "cmptilemeta.h"
#include "constants.h"
#include "graphics/rawbitmap.h"
#include "util.h"
static void read_bitmap(unsigned char* p_output, unsigned char** pp_input, unsigned short width, unsigned short height, unsigned int palette_offset, int has_transparency, int has_padding);
static void read_start_game_bitmap(unsigned char* p_output, unsigned char** pp_input, unsigned short width, unsigned short height, unsigned int palette_offset, int has_transparency, int has_padding);


unsigned char* read_cmp_header(unsigned char* p_bytes, cmp_header* header) {
  header->magic[0] = *p_bytes++;
  header->magic[1] = *p_bytes++;
  header->magic[2] = *p_bytes++;
  header->magic[3] = *p_bytes++;
  read_ulong_littleendian(&p_bytes, &header->end_pos);
  read_ulong_littleendian(&p_bytes, &header->cnt);
  read_ulong_littleendian(&p_bytes, &header->data_pos);

  return p_bytes;
}


void read_cmp_header_file(FILE* fp, cmp_header* header) {
  unsigned char bytes[FILE_CMPHEADER_SIZE];

  fread(bytes, 1, sizeof(bytes), fp);
  read_cmp_header(bytes, header);
}


unsigned char* read_cmp_sprite_meta(unsigned char* p_bytes, cmp_sprite_meta** pp_meta, unsigned long sprite_cnt) {
  int i;
  cmp_sprite_meta* p_meta = malloc(sprite_cnt * sizeof(cmp_sprite_meta));

  for (i = 0; i < sprite_cnt; ++i) {
    read_ushort_littleendian(&p_bytes, &p_meta[i].x);
    read_ushort_littleendian(&p_bytes, &p_meta[i].y);
    read_ushort_littleendian(&p_bytes, &p_meta[i].width);
    read_ushort_littleendian(&p_bytes, &p_meta[i].height);
    read_ushort_littleendian(&p_bytes, &p_meta[i].palette_offset);
    read_ushort_littleendian(&p_bytes, &p_meta[i].unknown);
  }

  *pp_meta = p_meta;

  return p_bytes;
}


unsigned char* read_cmp_tile_meta(unsigned char* p_bytes, cmp_tile_meta* p_meta, unsigned long tile_cnt) {
  int i;

  read_ushort_littleendian(&p_bytes, &p_meta->palette_line_cnt[0]);
  read_ushort_littleendian(&p_bytes, &p_meta->palette_line_cnt[1]);
  read_ushort_littleendian(&p_bytes, &p_meta->palette_line_cnt[2]);
  read_ushort_littleendian(&p_bytes, &p_meta->palette_line_cnt[3]);
  p_meta->p_dimensions = malloc(tile_cnt * sizeof(unsigned short) * 2);
  if (p_meta->p_dimensions == 0) {
    fprintf(stderr, "Could not allocate memory for dimensions of tile bitmaps.\n");
    abort();
  }

  for (i = 0; i < tile_cnt; ++i) {
    read_ushort_littleendian(&p_bytes, &p_meta->p_dimensions[i][0]);
    read_ushort_littleendian(&p_bytes, &p_meta->p_dimensions[i][1]);
  }

  return p_bytes;
}


void extract_sprites(raw_bitmap* p_bitmap, unsigned char* p_input, unsigned long cnt, cmp_sprite_meta* p_meta) {
  int i;

  for (i = 0; i < cnt; ++i) {
    int has_padding = 0;
    if (p_meta[i].width & 4) {
      has_padding = 1;
    }
    p_bitmap[i].p_data = malloc(p_meta[i].width * p_meta[i].height);
    if (p_bitmap[i].p_data == 0) {
      fprintf(stderr, "Could not allocate memory for sprite bitmap data.");
      abort();
    }
    p_bitmap[i].width = p_meta[i].width;
    p_bitmap[i].height = p_meta[i].height;
    read_bitmap(p_bitmap[i].p_data, &p_input, p_meta[i].width, p_meta[i].height, p_meta[i].palette_offset, 1, has_padding);
  }
}


void extract_opening_sprites(raw_bitmap* p_bitmap, unsigned char* p_input, unsigned long cnt, cmp_sprite_meta* p_meta) {
  int i;

  for (i = 0; i < cnt; ++i) {
    int has_padding = 0;

    if (p_meta[i].width & 4) {
      has_padding = 1;
    }
    p_bitmap[i].p_data = malloc(p_meta[i].width * p_meta[i].height);
    if (p_bitmap[i].p_data == 0) {
      fprintf(stderr, "Could not allocate memory for sprite bitmap data.");
      abort();
    }
    p_bitmap[i].width = p_meta[i].width;
    p_bitmap[i].height = p_meta[i].height;
    if (i == 24) {
      read_start_game_bitmap(p_bitmap[i].p_data, &p_input, p_meta[i].width, p_meta[i].height, p_meta[i].palette_offset, 1, has_padding);
    }
    else {
      read_bitmap(p_bitmap[i].p_data, &p_input, p_meta[i].width, p_meta[i].height, p_meta[i].palette_offset, 1, has_padding);
    }
  }
}


void extract_tiles(unsigned char* p_output, unsigned char** pp_output, unsigned char* p_input, unsigned long cnt, cmp_tile_meta meta, int (*p_palette_info)[2]) {
  int i;
  int remaining_tile_cnt = 0;
  int palette_line = 0;
  int palette_offset = 0;

  for (i = 0; i < cnt; ++i) {
    --remaining_tile_cnt;
    if (remaining_tile_cnt <= 0) {
      /* Compressed tile bitmap data is supposed to come in a maximum of
        four groups, one for each palette line. However, at least one file
        exceeds this maximum. This guard against that and has the remaining
        tiles use the last palette line. */
      if (palette_line > PALETTE_LINES_MAX - 1) {
        remaining_tile_cnt = cnt - i;
      }
      else {
        do {
          remaining_tile_cnt = p_palette_info[palette_line][0];
          palette_offset = p_palette_info[palette_line][1];
          ++palette_line;
        }
        while (remaining_tile_cnt == 0);
      }
    }

    pp_output[i] = p_output;
    read_bitmap(p_output, &p_input, meta.p_dimensions[i][0], meta.p_dimensions[i][1], palette_offset, 0, 0);
    p_output += meta.p_dimensions[i][0] * meta.p_dimensions[i][1];
  }
}


static void read_bitmap(unsigned char* p_output, unsigned char** pp_input, unsigned short width, unsigned short height, unsigned int palette_offset, int has_transparency, int has_padding) {
  unsigned int y, x;
  unsigned char* p_input = *pp_input;

  if (has_padding != 0) {
    width += 4;
  }

  for (y = 0; y < height; ++y) {
    for (x = 0; x < width; ++x) {
      if (has_padding == 0 || width - 4 > x) {
        if (x & 1) {
          *p_output = (*p_input & 0x0F) + palette_offset;
        }
        else {
          *p_output = ((*p_input & 0xF0) >> 4) + palette_offset;
        }
        if (*p_output == palette_offset) {
          if (has_transparency != 0) {
            *p_output = 0xFF;
          }
          else {
            *p_output = 0;
          }
        }
        ++p_output;
      }
      if (x & 1) {
        ++p_input;
      }
    }
  }

  *pp_input = p_input;
}


static void read_start_game_bitmap(unsigned char* p_output, unsigned char** pp_input, unsigned short width, unsigned short height, unsigned int palette_offset, int has_transparency, int has_padding) {
  unsigned int y, x;
  unsigned char* p_input = *pp_input;

  if (has_padding != 0) {
    width += 4;
  }

  for (y = 0; y < height; ++y) {
    for (x = 0; x < width; ++x) {
      if (has_padding == 0 || width - 4 > x) {
        if (x < width - 1) {
          if (x & 1) {
            *p_output = (*p_input & 0x0F) + palette_offset;
          }
          else {
            *p_output = ((*p_input & 0xF0) >> 4) + palette_offset;
          }
        }
        else {
          *p_output = palette_offset;
        }
        if (*p_output == palette_offset) {
          if (has_transparency != 0) {
            *p_output = 0xFF;
          }
          else {
            *p_output = 0;
          }
        }
        ++p_output;
      }
      if (x & 1) {
        ++p_input;
      }
    }
  }

  *pp_input = p_input;
}
