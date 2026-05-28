#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "../constants.h"
#include "../GAME/EQU.h"
static void wait_for_next_frame(void);

SDL_Surface* gp_screen = 0;
PALETTEENTRY g_palette[256] = { 0 };
static unsigned long next_frame_ticks = 0;
static unsigned long frame_durations[FRAME_DURATIONS] = { 17, 17, 16 };
static int frame_duration_index = 0;


void init_screen(void) {
#ifdef _WIN32
  SDL_putenv("SDL_VIDEODRIVER=directx");
#endif
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed. Error: %s\n", SDL_GetError());
    abort();
  }
  gp_screen = SDL_SetVideoMode(SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX, SCREEN_BPP, SDL_SWSURFACE);
  if (gp_screen == 0) {
    fprintf(stderr, "SDL_SetVideoMode failed. Error: %s\n", SDL_GetError());
    abort();
  }
  lpcolorwk = &g_palette[16];
  lpcolorwk3 = &g_palette[80];
}


void term_screen(void) {
  SDL_Quit();
}


void clear_screen(void) {
  SDL_FillRect(gp_screen, 0, BG_TRANSPARENT_COLOR);
}


void clear_palette(void) {
  memset(g_palette, 0, sizeof(g_palette));
}


void lock_screen(void) {
  SDL_LockSurface(gp_screen);
}


void unlock_screen(void) {
  SDL_UnlockSurface(gp_screen);
}


unsigned char* get_screen_pixels(void) {
  return gp_screen->pixels;
}


int get_scanline_padding(void) {
  return gp_screen->pitch - gp_screen->w;
}


void blit_screen(void) {
  SDL_SetColors(gp_screen, (SDL_Color*)g_palette, 0, 256);
  wait_for_next_frame();
  SDL_Flip(gp_screen);
}


void start_timer(void) {
  next_frame_ticks = SDL_GetTicks();
  frame_duration_index = 0;
}


static void wait_for_next_frame(void) {
  unsigned long ticks;

  ticks = SDL_GetTicks();
  next_frame_ticks += frame_durations[frame_duration_index++];
  if (frame_duration_index == FRAME_DURATIONS) {
    frame_duration_index = 0;
  }
  if (ticks < next_frame_ticks) {
    do {
      SDL_Delay(1);
      ticks = SDL_GetTicks();
    }
    while (ticks < next_frame_ticks);
  }
  else {
    next_frame_ticks = SDL_GetTicks();
  }
}
