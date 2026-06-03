#include "timewarp.h"
#include <stdio.h>
#include "constants.h"
#include "graphics/screen.h"
#include "graphics/sprites.h"
#include "graphics/tiles.h"
#include "input/input.h"
#include "GAME/EQU.h"
#include "GAME/COL.h"
#include "GAME/WARP/WARP.h"
#include <SDL2/SDL.h>
static void load_time_warp(void);
static void unload_time_warp(void);
static void draw_time_warp(void);

extern int g_quit;
extern bmp_info SprBmp[700];
extern SDL_Surface* gp_screen;

void time_warp(void) {
  load_time_warp();
  clear_palette();
  warp_init();
  stageno_i.w = 0x700;
  time_flag_i = 0;
  start_timer();

  while (g_quit == 0) {
    if (gFadeFlag != 0) {
      if (FadeProc() != 0) {
        gFadeFlag = 0;
      }
    }
    else {
      poll_controller();
      if (warp() != 0) break;
    }
    draw_time_warp();
  }

  unload_time_warp();
}


static void load_time_warp(void) {
  plane_layout layouts[2] = {
    { 1, 0, 0, 40, 28, 0, 1, "WARP/cgwarp.bin" },
    { 1, 0, 28, 40, 4, 0, 1, "WARP/cgwarp.bin" }
  };

  load_sprite_bitmaps("WARP/SCMPWARP.CM_", (unsigned char(*)[3])SprBmp);
  load_tile_bitmaps("WARP/TCMPWARP.CM_", 0);
  load_plane_layout(layouts[0]);
  load_plane_layout(layouts[1]);
}


static void unload_time_warp(void) {
  unload_sprite_bitmaps();
  unload_tile_bitmaps();
}


static void draw_time_warp(void) {
  unsigned short hscroll_empty[SCREEN_HEIGHT_PX] = { 0 };
  int i;

  clear_screen();
  lock_screen();
  blit_plane(get_screen_pixels(), PLANE_B, get_scanline_padding(), hscroll_empty, vscroll.w.l, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_plane(get_screen_pixels(), PLANE_A_LO, get_scanline_padding(), hscroll_empty, vscroll.w.h, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_sprites_lo(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
  blit_plane(get_screen_pixels(), PLANE_A_HI, get_scanline_padding(), hscroll_empty, vscroll.w.h, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_sprites_hi(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
  unlock_screen();
  
  SDL_Rect srcRect, destRect;
  srcRect.x = 40;
  srcRect.y = 0;
  srcRect.w = 40;
  srcRect.h = SCREEN_HEIGHT_PX;
  destRect.x = 360;
  destRect.y = 0;    
  SDL_BlitSurface(gp_screen, &srcRect, gp_screen, &destRect);
      
  destRect.x = 400; 
  SDL_BlitSurface(gp_screen, &srcRect, gp_screen, &destRect);

  srcRect.x = 320;
  srcRect.w = 40;
  destRect.x = 0;
  SDL_BlitSurface(gp_screen, &srcRect, gp_screen, &destRect);
  
  blit_screen();
}
