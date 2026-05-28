#include "littleplanet.h"
#include "audio.h"
#include "constants.h"
#include "graphics/screen.h"
#include "graphics/sprites.h"
#include "graphics/tiles.h"
#include "input/input.h"
#include "GAME/EQU.h"
#include "GAME/COL.h"
#include "GAME/TITLE/COMMON/SMORPHDATA.h"
#include "GAME/TITLE/PLANET/LPLMAIN.h"
static void load_little_planet(void);
static void unload_little_planet(void);
static void draw_little_planet(void);
static void init_planet(void);
static void update_planet(void);

extern int g_quit;
extern bmp_info SprBmp[700];
extern unsigned char flash_flg;

static smorph_data g_planet[176] = { 0 };


void little_planet(void) {
  load_little_planet();
  clear_palette();
  lplgame_init();

  set_stamp_map(sm_adr0, SCREEN_WIDTH_PX / STAMP_LENGTH, PLANE_HEIGHT_PX / STAMP_LENGTH);
  init_planet();
  set_smorph_data(g_planet);
  start_timer();

  while (g_quit == 0) {
    if (gFadeFlag != 0) {
      int ret = FadeProc();

      v_int();
      if (ret != 0) {
        gFadeFlag = 0;
        flash_flg = 0;
      }
    }
    else {
      int next;

      poll_controller();
      next = lplgame();
      if (next != 0) break;
    }
    draw_little_planet();
  }

  unload_little_planet();
}


static void load_little_planet(void) {
  load_sprite_bitmaps("TITLE/PLANET/CG/SCMPLP.CM_", (unsigned char(*)[3])SprBmp);
  load_tile_bitmaps("TITLE/PLANET/CG/LPBS.CM_", 0);
  load_stamp_bitmaps("TITLE/PLANET/CG/PLANET.CM_");
}


static void unload_little_planet(void) {
  pause_bgm();
  unload_sprite_bitmaps();
  unload_tile_bitmaps();
}


static void draw_little_planet(void) {
  unsigned short hscroll_empty[SCREEN_HEIGHT_PX] = { 0 };

  clear_screen();
  lock_screen();
  update_planet();
  blit_plane(get_screen_pixels(), PLANE_B, get_scanline_padding(), hscroll_empty, 0, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_plane(get_screen_pixels(), PLANE_A_LO, get_scanline_padding(), hscroll_empty, 0, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_smorphed_plane(get_screen_pixels(), get_scanline_padding(), 24, 176, STAMP_MAP_WIDTH, STAMP_LENGTH, 0);
  blit_sprites_lo(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
  blit_plane(get_screen_pixels(), PLANE_A_HI, get_scanline_padding(), hscroll_empty, 0, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_sprites_hi(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
  unlock_screen();
  blit_screen();
}


static void init_planet(void) {
  int i;

  for (i = 0; i < 176; ++i) {
    g_planet[i].StartX = 0;
    g_planet[i].StartY = i * 0x10000;
    g_planet[i].DeltaX = 0x10000;
    g_planet[i].DeltaY = 0;
  }
}


static void update_planet(void) {
  short* p_tvadr = (short*)tv_adr;
  int i;

  for (i = 0; i < 176; ++i) {
    g_planet[i].StartX = *p_tvadr++ * 0x2000;
    g_planet[i].StartY = *p_tvadr++ * 0x2000;
    g_planet[i].DeltaX = *p_tvadr++ * 32;
    g_planet[i].DeltaY = *p_tvadr++ * 32;
  }
}
