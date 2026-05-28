#include "opening.h"
#include <stdio.h>
#include "audio.h"
#include "besttimes.h"
#include "constants.h"
#include "gamemode.h"
#include "options.h"
#include "graphics/screen.h"
#include "graphics/sprites.h"
#include "graphics/tiles.h"
#include "input/input.h"
#include "savedata.h"
#include "score.h"
#include "soundtest.h"
#include "stage.h"
#include "stagetest.h"
#include "GAME/EQU.h"
#include "GAME/TITLE/OPENING/OPNDO.h"
static void load_opening(void);
static void unload_opening(void);
static gamemode run_opening(void);
static void draw_opening(void);

int g_quit = 0;


void opening(void) {
  while (g_quit == 0) {
    gamemode next;

    ta_flag = 0;
    gKeepWork.TimeWarp = 1;
    gKeepWork.SpecialTime = 0;
    play_start = 0;

    load_opening();
    clear_palette();
    OPN_Init();
    next = run_opening();
    unload_opening();

    switch (next) {
      case GAMEMODE_NEW_GAME:
        if (new_score_data() != 0) {
          start_new_game();
        }
        break;
      case GAMEMODE_CONTINUE:
        read_score_data(read_score_index(0), 0, 0);
        continue_game();
        break;
      case GAMEMODE_SAVED_GAMES:
        savedata();
        break;
      case GAMEMODE_SOUND_TEST:
        sound_test();
        break;
      case GAMEMODE_STAGE_SELECT:
        stage_test();
        break;
      case GAMEMODE_BEST_TIMES:
        best_times();
        break;
      case GAMEMODE_OPTIONS:
        options();
        break;
      case GAMEMODE_EXIT:
        g_quit = 1;
        break;
    }
  }
}


static void load_opening(void) {
  int tile_palette_info[2][2] = {
    { 1, 32 },
    { 832, 16 }
  };

  load_opening_sprite_bitmaps("TITLE/BMP/OPENINGS.CM_");
  load_extra_sprite_bitmap("TITLE/OPENING/1996SEGA.BMP", 0, 1);
  load_extra_sprite_bitmap("TITLE/OPENING/EXIT.BMP", 32, 1);
  load_extra_sprite_bitmap("TITLE/OPENING/OPTIONS.BMP", 32, 1);
  load_tile_bitmaps("TITLE/BMP/OPENINGT.CM_", tile_palette_info);
}


static void unload_opening(void) {
  pause_bgm();
  unload_sprite_bitmaps();
  unload_tile_bitmaps();
}


static gamemode run_opening(void) {
  start_timer();

  while (g_quit == 0) {
    gamemode next;

    poll_controller();
    next = OPN_Main();
    if (next != GAMEMODE_NONE) {
      return next;
    }
    draw_opening();
  }

  return GAMEMODE_NONE;
}


static void draw_opening(void) {
  unsigned short hscroll_a[SCREEN_HEIGHT_PX] = { 0 };
  unsigned short hscroll_b[SCREEN_HEIGHT_PX] = { 0 };
  int i;

  for (i = 0; i < SCREEN_HEIGHT_PX; ++i) {
    hscroll_b[i] = hscrollbuff[i].w.l;
  }

  clear_screen();
  lock_screen();
  blit_plane(get_screen_pixels(), PLANE_B, get_scanline_padding(), hscroll_b, 0, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_plane(get_screen_pixels(), PLANE_A_LO, get_scanline_padding(), hscroll_a, 0, 0, SCREEN_HEIGHT_PX - 1, 0);
  blit_sprites_lo(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
  blit_smorphed_plane(get_screen_pixels(), get_scanline_padding(), 0, 128, PLANE_WIDTH_TILES, TILE_LENGTH, 1);
  blit_sprites_hi(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
  unlock_screen();
  blit_screen();
}
