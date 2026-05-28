#include "thanks.h"
#include "audio.h"
#include "constants.h"
#include "graphics/screen.h"
#include "graphics/sprites.h"
#include "graphics/tiles.h"
#include "input/input.h"
#include "GAME/EQU.h"
#include "GAME/TITLE/THANKS/GAME.h"
static void load_thanks(void);
static void unload_thanks(void);
static void draw_thanks(void);

extern int g_quit;
extern bmp_info SprBmp[700];


void thanks(void) {
  load_thanks();
  clear_palette();
  thanksgame_init();
  start_timer();

  while (g_quit == 0) {
    int next;

    poll_controller();
    next = thanksgame();
    if (next != 0) break;
    draw_thanks();
  }

  unload_thanks();
}


static void load_thanks(void) {
  load_sprite_bitmaps("TITLE/THANKS/CG/SCMPTH.CM_", (unsigned char(*)[3])SprBmp);
  load_tile_bitmaps("TITLE/THANKS/CG/SCR_A.CM_", 0);
}


static void unload_thanks(void) {
  pause_bgm();
  unload_sprite_bitmaps();
  unload_tile_bitmaps();
}


static void draw_thanks(void) {
  unsigned short hscroll_empty[SCREEN_HEIGHT_PX] = { 0 };
  int i;

  blit_plane(get_screen_pixels(), PLANE_B, get_scanline_padding(), hscroll_empty, vscroll.w.l, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_plane(get_screen_pixels(), PLANE_A_LO, get_scanline_padding(), hscroll_empty, vscroll.w.h, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_sprites_lo(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
  blit_plane(get_screen_pixels(), PLANE_A_HI, get_scanline_padding(), hscroll_empty, vscroll.w.h, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_sprites_hi(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
  blit_screen();
}
