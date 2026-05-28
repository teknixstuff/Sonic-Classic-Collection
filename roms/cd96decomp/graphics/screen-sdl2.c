#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "../constants.h"
#include "../GAME/EQU.h"
static void wait_for_next_frame(void);

SDL_Surface* gp_screen = 0;
static SDL_Surface* gp_screen_rgba = 0;
static SDL_Window* gp_window = 0;
static SDL_Renderer* gp_renderer = 0;
static SDL_Texture* gp_texture = 0;
static int vsync = 0;
static int frame_multiplier = 1;
PALETTEENTRY g_palette[256] = { 0 };
static unsigned long next_frame_ticks = 0;
static unsigned long frame_durations[FRAME_DURATIONS] = { 17, 17, 16 };
static int frame_duration_index = 0;


void init_screen(void) {
  SDL_DisplayMode mode;
  int refresh_rate;

  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed. Error: %s\n", SDL_GetError());
    abort();
  }
  SDL_GetDesktopDisplayMode(0, &mode);
  refresh_rate = mode.refresh_rate;
  if (refresh_rate != 0) {
    /* Round up if refresh rate is 59 or something. */
    if ((refresh_rate + 1) % FRAMES_PER_SECOND == 0) {
      ++refresh_rate;
    }
    if (refresh_rate % FRAMES_PER_SECOND == 0) {
      vsync = 1;
      frame_multiplier = refresh_rate / FRAMES_PER_SECOND;
    }
  }
  SDL_CreateWindowAndRenderer(1200, 672, 0, &gp_window, &gp_renderer);
  if (gp_window == 0 || gp_renderer == 0) {
    fprintf(stderr, "SDL_CreateWindowAndRenderer failed. Error: %s\n", SDL_GetError());
    abort();
  }
  SDL_RenderSetLogicalSize(gp_renderer, SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX);
  SDL_RenderSetIntegerScale(gp_renderer, SDL_TRUE);
  SDL_RenderSetVSync(gp_renderer, vsync);
  gp_screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX, SCREEN_BPP, 0, 0, 0, 0);
  if (gp_screen == 0) {
    fprintf(stderr, "SDL_CreateRGBSurface failed. Error: %s\n", SDL_GetError());
    abort();
  }
  gp_screen_rgba = SDL_CreateRGBSurface(0, gp_screen->w, gp_screen->h, 32, 0, 0, 0, 0);
  if (gp_screen_rgba == 0) {
    fprintf(stderr, "SDL_CreateRGBSurface failed. Error: %s\n", SDL_GetError());
    abort();
  }
  gp_texture = SDL_CreateTexture(gp_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, gp_screen_rgba->w, gp_screen_rgba->h);
  if (gp_texture == 0) {
    fprintf(stderr, "SDL_CreateTexture failed. Error: %s\n", SDL_GetError());
    abort();
  }
  lpcolorwk = &g_palette[16];
  lpcolorwk3 = &g_palette[80];
}


void term_screen(void) {
  SDL_DestroyTexture(gp_texture);
  SDL_FreeSurface(gp_screen_rgba);
  SDL_FreeSurface(gp_screen);
  SDL_DestroyRenderer(gp_renderer);
  SDL_DestroyWindow(gp_window);
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
  void* texture_pixels;
  int texture_pitch;
  int i;

  SDL_SetPaletteColors(gp_screen->format->palette, (SDL_Color*)g_palette, 0, 256);
  SDL_BlitSurface(gp_screen, 0, gp_screen_rgba, 0);
  SDL_LockTexture(gp_texture, 0, &texture_pixels, &texture_pitch);
  SDL_ConvertPixels(gp_screen_rgba->w, gp_screen_rgba->h, gp_screen_rgba->format->format, gp_screen_rgba->pixels, gp_screen_rgba->pitch, SDL_PIXELFORMAT_RGBA8888, texture_pixels, texture_pitch);
  SDL_UnlockTexture(gp_texture);
  wait_for_next_frame();

  for (i = 0; i < frame_multiplier; ++i) {
    SDL_RenderClear(gp_renderer);
    SDL_RenderCopy(gp_renderer, gp_texture, 0, 0);
    SDL_RenderPresent(gp_renderer);
  }
}


void start_timer(void) {
  if (vsync != 0) return;

  next_frame_ticks = SDL_GetTicks();
  frame_duration_index = 0;
}


static void wait_for_next_frame(void) {
  unsigned long ticks;

  if (vsync != 0) return;

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
