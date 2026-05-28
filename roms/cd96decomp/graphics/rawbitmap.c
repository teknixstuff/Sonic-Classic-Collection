#include "rawbitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "../constants.h"

raw_bitmap load_raw_bitmap(char* p_filename, int palette_offset, int has_transparency) {
  raw_bitmap bitmap;
  unsigned char* p_source;
  unsigned char* p_destination;
  int padding;
  int y, x;
  SDL_Surface* p_surface = SDL_LoadBMP(p_filename);

  if (p_surface == 0) {
    fprintf(stderr, "SDL_LoadBMP failed with %s. Error: %s\n", p_filename, SDL_GetError());
    abort();
  }
  bitmap.p_data = malloc(p_surface->w * p_surface->h);
  if (bitmap.p_data == 0) {
    fprintf(stderr, "Could not allocate memory for bitmap data.");
    abort();
  }
  bitmap.width = p_surface->w;
  bitmap.height = p_surface->h;
  p_source = p_surface->pixels;
  p_destination = bitmap.p_data;
  padding = p_surface->pitch - p_surface->w;
  SDL_LockSurface(p_surface);

  for (y = 0; y < p_surface->h; ++y) {
    for (x = 0; x < p_surface->w; ++x) {
      if (*p_source == 0) {
        if (has_transparency != 0) {
          *p_destination = SPRITE_TRANSPARENT_COLOR;
        }
        else {
          *p_destination = 0;
        }
      }
      else {
        *p_destination = *p_source + palette_offset;
      }
      ++p_destination;
      ++p_source;
    }
    p_source += padding;
  }

  SDL_UnlockSurface(p_surface);
  SDL_FreeSurface(p_surface);

  return bitmap;
}
