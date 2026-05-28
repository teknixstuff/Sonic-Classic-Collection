#include "specialstage.h"
#include <stdio.h>
#include "audio.h"
#include "constants.h"
#include "graphics/planelayout.h"
#include "graphics/screen.h"
#include "graphics/sprites.h"
#include "graphics/tiles.h"
#include "input/input.h"
#include "GAME/EQU.h"
#include "GAME/COL.h"
#include "GAME/SPECIAL/BACT.h"
#include "GAME/SPECIAL/COMMON.h"
#include "GAME/SPECIAL/GAME.h"
#include "GAME/TITLE/COMMON/SCORE_DATA_TYPES.h"
#include "GAME/TITLE/COMMON/SMORPHDATA.h"
static void load_special_stage(void);
static void unload_special_stage(void);
static void manage_special_stage(void);
static int run_special_stage(void);
static void draw_special_stage(void);
static void init_floor(void);
static void update_floor(void);
static void set_hscroll(unsigned short hscroll_plane[SCREEN_HEIGHT_PX], unsigned short value);

extern int g_quit;
extern bmp_info SprBmp[700];
extern score_data g_current_score_data;

static smorph_data g_floor[96] = { 0 };


void special_stage(void) {
  gKeepWork.SPEMode = 0;

  load_special_stage();
  clear_palette();
  specgame_init();
  manage_special_stage();
  unload_special_stage();
}


static void load_special_stage(void) {
  char path[256];

  load_sprite_bitmaps("SPECIAL/SCMPSPE.CM_", (unsigned char(*)[3])SprBmp);
  if (gKeepWork.SPEMode == 0) {
    plane_layout hud_layout = { 0, 0, 0, 40, 2, 0, 0, "SPECIAL/BMP/FIX/panel1.bin" };
    plane_layout bg_layouts_0[6] = {
      { 3,  0, 0, 32, 16, 203, 0, "SPECIAL/BMP/FIX/s1b0.bin" },
      { 3, 32, 0, 32, 16, 203, 0, "SPECIAL/BMP/FIX/s1b0.bin" },
      { 4,  0, 0, 32, 12,  35, 0, "SPECIAL/BMP/FIX/s1b1.bin" },
      { 4, 32, 0, 32, 12,  35, 0, "SPECIAL/BMP/FIX/s1b1.bin" },
      { 1,  0, 0, 64, 10,  40, 1, "SPECIAL/BMP/FIX/s1a0.bin" },
      { 2,  0, 0, 64,  4,  40, 1, "SPECIAL/BMP/FIX/s1a1.bin" }
    };
    plane_layout bg_layouts_1[6] = {
      { 1,  0, 0, 32, 16, 35, 0, "SPECIAL/BMP/FIX/mpb1_a0.bin" },
      { 1, 32, 0, 32, 16, 35, 0, "SPECIAL/BMP/FIX/mpb1_a1.bin" },
      { 2,  0, 0, 32, 16, 35, 1, "SPECIAL/BMP/FIX/mpb1_b0.bin" },
      { 2, 32, 0, 32, 16, 35, 1, "SPECIAL/BMP/FIX/mpb1_b1.bin" },
      { 3,  0, 0, 32, 12, 35, 0, "SPECIAL/BMP/FIX/mpb1_b2.bin" },
      { 3,  8, 0, 32, 12, 35, 0, "SPECIAL/BMP/FIX/mpb1_b2.bin" }
    };
    plane_layout bg_layouts_2[14] = {
      { 1,  0, 0, 32, 16, 34, 1, "SPECIAL/BMP/FIX/mpb2_a0.bin" },
      { 1, 32, 0, 32, 16, 34, 1, "SPECIAL/BMP/FIX/mpb2_a1.bin" },
      { 2,  0, 0, 32,  6, 34, 1, "SPECIAL/BMP/FIX/mpb2_b00.bin" },
      { 2, 32, 0, 32,  6, 34, 1, "SPECIAL/BMP/FIX/mpb2_b20.bin" },
      { 3,  0, 0, 32,  3, 34, 1, "SPECIAL/BMP/FIX/mpb2_b01.bin" },
      { 3, 32, 0, 32,  3, 34, 1, "SPECIAL/BMP/FIX/mpb2_b21.bin" },
      { 4,  0, 0, 32,  1, 34, 1, "SPECIAL/BMP/FIX/mpb2_b02.bin" },
      { 4, 32, 0, 32,  1, 34, 1, "SPECIAL/BMP/FIX/mpb2_b22.bin" },
      { 5,  0, 0, 32,  4, 34, 1, "SPECIAL/BMP/FIX/mpb2_b03.bin" },
      { 5, 32, 0, 32,  4, 34, 1, "SPECIAL/BMP/FIX/mpb2_b23.bin" },
      { 6,  0, 0, 32,  2, 34, 1, "SPECIAL/BMP/FIX/mpb2_b1.bin" },
      { 6, 32, 0, 32,  2, 34, 1, "SPECIAL/BMP/FIX/mpb2_b1.bin" },
      { 7,  0, 0, 32, 12, 41, 1, "SPECIAL/BMP/FIX/mpb2_b4.bin" },
      { 7,  8, 0, 32, 12, 41, 1, "SPECIAL/BMP/FIX/mpb2_b4.bin" }
    };
    plane_layout bg_layouts_3[6] = {
      { 1,  0, 0, 32,  5, 35, 1, "SPECIAL/BMP/FIX/mpb3_b1.bin" },
      { 1, 32, 0, 32,  5, 35, 1, "SPECIAL/BMP/FIX/mpb3_b3.bin" },
      { 2,  0, 0, 32, 16, 35, 1, "SPECIAL/BMP/FIX/mpb3_a0.bin" },
      { 2, 32, 0, 32, 16, 35, 1, "SPECIAL/BMP/FIX/mpb3_a1.bin" },
      { 3,  0, 0, 32, 11, 35, 1, "SPECIAL/BMP/FIX/mpb3_b0.bin" },
      { 3, 32, 0, 32, 11, 35, 1, "SPECIAL/BMP/FIX/mpb3_b2.bin" }
    };
    plane_layout bg_layouts_4[6] = {
      { 1,  0, 0, 32, 14, 172, 1, "SPECIAL/BMP/FIX/mpb4_a0.bin" },
      { 1, 32, 0, 32, 14, 172, 1, "SPECIAL/BMP/FIX/mpb4_a1.bin" },
      { 3,  0, 0, 32, 16, -97, 1, "SPECIAL/BMP/FIX/mpb4_b0.bin" },
      { 3, 32, 0, 32, 16, -97, 1, "SPECIAL/BMP/FIX/mpb4_b1.bin" },
      { 2,  0, 0, 32, 12,  35, 0, "SPECIAL/BMP/FIX/mpb4_b2.bin" },
      { 2,  8, 0, 32, 12,  35, 0, "SPECIAL/BMP/FIX/mpb4_b2.bin" }
    };
    plane_layout bg_layouts_5[6] = {
      { 1,  0, 0, 32, 14, 35, 1, "SPECIAL/BMP/FIX/sp6_a01.bin" },
      { 1, 32, 0, 32, 14, 35, 1, "SPECIAL/BMP/FIX/sp6_a02.bin" },
      { 3,  0, 0, 32, 16, 55, 1, "SPECIAL/BMP/FIX/sp6_b0.bin" },
      { 3, 32, 0, 32, 16, 55, 1, "SPECIAL/BMP/FIX/sp6_b0.bin" },
      { 2,  0, 0, 32, 12, 52, 0, "SPECIAL/BMP/FIX/sp6_000.bin" },
      { 2,  8, 0, 32, 12, 52, 0, "SPECIAL/BMP/FIX/sp6_000.bin" }
    };
    plane_layout bg_layouts_6[10] = {
      { 1,  0, 0, 32,  6,  35, 1, "SPECIAL/BMP/FIX/mpb6b2l.bin" },
      { 1, 32, 0, 32,  6,  35, 1, "SPECIAL/BMP/FIX/mpb6b2r.bin" },
      { 2,  0, 0, 32, 14,  35, 1, "SPECIAL/BMP/FIX/mpb6a1r.bin" },
      { 2, 32, 0, 32, 14,  35, 1, "SPECIAL/BMP/FIX/mpb6a1l.bin" },
      { 3,  0, 0, 32,  2,  35, 1, "SPECIAL/BMP/FIX/mpb6a2r.bin" },
      { 3, 32, 0, 32,  2,  35, 1, "SPECIAL/BMP/FIX/mpb6a2l.bin" },
      { 4,  0, 0, 32, 10,  35, 1, "SPECIAL/BMP/FIX/mpb6b1l.bin" },
      { 4, 32, 0, 32, 10,  35, 1, "SPECIAL/BMP/FIX/mpb6b1r.bin" },
      { 5,  0, 0, 32, 12, 471, 0, "SPECIAL/BMP/FIX/mpb6_b8.bin" },
      { 5,  8, 0, 32, 12, 471, 0, "SPECIAL/BMP/FIX/mpb6_b8.bin" }
    };
    plane_layout bg_layouts_7[3] = {
      { 1, 0, 0, 40, 16, 41, 0, "SPECIAL/BMP/FIX/egg.bin" },
      { 2, 0, 0, 32, 12, 35, 0, "SPECIAL/BMP/FIX/mpb7_b1.bin" },
      { 2, 8, 0, 32, 12, 35, 0, "SPECIAL/BMP/FIX/mpb7_b1.bin" }
    };
    plane_layout* bg_layouts[8] = {
      bg_layouts_0,
      bg_layouts_1,
      bg_layouts_2,
      bg_layouts_3,
      bg_layouts_4,
      bg_layouts_5,
      bg_layouts_6,
      bg_layouts_7
    };
    int bg_layout_cnts[8] = { 6, 6, 14, 6, 6, 6, 10, 3 };
    int i;

    sprintf(path, "SPECIAL/BMP/FIX/TCMPS%1d.CM_", stagenm + 1);
    load_tile_bitmaps(path, 0);
    load_plane_layout(hud_layout);

    for (i = 0; i < bg_layout_cnts[stagenm]; ++i) {
      load_plane_layout(bg_layouts[stagenm][i]);
    }

    sprintf(path, "SPECIAL/CG/SP%1dCG32.CM_", stagenm + 1);
    load_stamp_bitmaps(path);
  }
  else {
    plane_layout layout = { 1, 0, 0, 40, 28, 687, 1, "SPECIAL/BMP/FIX/clrback.bin" };

    load_tile_bitmaps("SPECIAL/BMP/FIX/SCLEAR.CM_", 0);
    load_plane_layout(layout);
  }
}


static void unload_special_stage(void) {
  pause_bgm();
  unload_sprite_bitmaps();
  unload_tile_bitmaps();
}


static void manage_special_stage(void) {
  while (g_quit == 0) {
    if (gKeepWork.SPEMode != 0 && stagenm == 7) return;

    switch (gKeepWork.SPEMode) {
      case 0:
        set_stamp_map(sm_adr0, STAMP_MAP_WIDTH, STAMP_MAP_HEIGHT);
        init_floor();
        set_smorph_data(g_floor);
        break;
      case 1:
        pause_bgm();
        set_smorph_data(0);
        unload_special_stage();
        load_special_stage();
        break;
      case 2:
        break;
      case 4:
      case 6:
        ++stagenm;
        stagenm %= 6;
        g_current_score_data.clrspflg_save = clrspflg_save;
        g_current_score_data.stagenm = stagenm;
        return;
    }

    run_special_stage();
  }
}


static int run_special_stage(void) {
  int mode = gKeepWork.SPEMode;
  int frame = FRAMES_PER_SECOND / SPECIAL_STAGE_FRAMES_PER_SECOND - 1;

  start_timer();

  while (g_quit == 0 && gKeepWork.SPEMode == mode) {
    if (++frame == FRAMES_PER_SECOND / SPECIAL_STAGE_FRAMES_PER_SECOND) {
      frame = 0;
      if (gFadeFlag != 0) {
        if (FadeProc() != 0) {
          gFadeFlag = 0;
        }
      }
      else {
        int next;

        poll_controller();
        next = specgame();
        if (next != 0) {
          return next;
        }
      }
    }
    draw_special_stage();
  }

  return 0;
}


static void draw_special_stage(void) {
  unsigned short hscroll_empty[SCREEN_HEIGHT_PX] = { 0 };
  int i;

  if (gKeepWork.SPEMode != 1) {
    clear_screen();
  }
  lock_screen();
  if (gKeepWork.SPEMode == 0) {
    unsigned short hscroll_plane[PLANES_MAX][SCREEN_HEIGHT_PX] = { 0 };
    unsigned char plane_y[8][8] = {
      {   8,  16,  96,   0, 128,   0,   0,   0 },
      {   8,   0,   0, 128,   0,   0,   0,   0 },
      {   8,   0,   0,  48,  72,  80, 112, 128 },
      {   8,  88,   0,   0,   0,   0,   0,   0 },
      {   8,  16, 128,   0,   0,   0,   0,   0 },
      {   8,  16, 128,   0,   0,   0,   0,   0 },
      {   8,  80,   0, 112,   0, 128,   0,   0 },
      {   8,   0, 128,   0,   0,   0,   0,   0 }
    };
    unsigned short hane1, hane2, dmg1, dmg2;
    unsigned short modifier = 0;

    switch (stagenm) {
      case 0:
        set_hscroll(hscroll_plane[2], -hscrollbuff[96].w.l);
      case 4:
      case 5:
        set_hscroll(hscroll_plane[1], -hscrollbuff[32].w.l);
        if (stagenm == 4) {
          modifier = 32;
        }

        for (i = 0; i < 128; ++i) {
          hscroll_plane[3][i] = -hscrollbuff[i].w.h + modifier & PLANE_WIDTH_PX - 1;
        }

        break;
      case 1:
        set_hscroll(hscroll_plane[1], -hscrollbuff[0].w.l);
        set_hscroll(hscroll_plane[2], -hscrollbuff[1].w.l);
        break;
      case 2:
        set_hscroll(hscroll_plane[1], -hscrollbuff[0].w.l);
        set_hscroll(hscroll_plane[3], -hscrollbuff[1].w.l);
        set_hscroll(hscroll_plane[4], -hscrollbuff[2].w.l);
        set_hscroll(hscroll_plane[5], -hscrollbuff[3].w.l);
        set_hscroll(hscroll_plane[6], -hscrollbuff[4].w.l);
        break;
      case 3:
        set_hscroll(hscroll_plane[1], -hscrollbuff[2].w.l);
        set_hscroll(hscroll_plane[2], -hscrollbuff[0].w.l);
        set_hscroll(hscroll_plane[3], -hscrollbuff[1].w.l);
        break;
      case 6:
        set_hscroll(hscroll_plane[1], -hscrollbuff[2].w.l);
        set_hscroll(hscroll_plane[2], -hscrollbuff[3].w.l);
        set_hscroll(hscroll_plane[3], -hscrollbuff[0].w.l);
        set_hscroll(hscroll_plane[4], -hscrollbuff[1].w.l);
        break;
    }

    Special_block_chg(&hane1, &hane2, &dmg1, &dmg2);
    hane1 *= STAMP_VERSIONS;
    hane2 *= STAMP_VERSIONS;
    dmg1 *= STAMP_VERSIONS;
    dmg2 *= STAMP_VERSIONS;

    for (i = 0; i < STAMP_VERSIONS; ++i) {
      set_stamp_bitmap(hane1++, hane2++);
      set_stamp_bitmap(dmg1++, dmg2++);
    }

    for (i = PLANES_MAX - 1; i >= 0; --i) {
      blit_plane(get_screen_pixels(), i, get_scanline_padding(), hscroll_plane[i], 0, 0, SCREEN_HEIGHT_PX - 1, plane_y[stagenm][i]);
      if (i == 2) {
        update_floor();
        blit_smorphed_plane(get_screen_pixels(), get_scanline_padding(), 128, 96, STAMP_MAP_WIDTH, STAMP_LENGTH, 0);
      }
      else if (i == 1) {
        blit_sprites_lo(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
      }
      else if (i == 0) {
        blit_sprites_hi(get_screen_pixels(), get_scanline_padding(), 0, SCREEN_HEIGHT_PX - 1);
      }
    }
  }
  else if (gKeepWork.SPEMode != 1) {
    blit_plane(get_screen_pixels(), PLANE_B, get_scanline_padding(), hscroll_empty, 0, 0, SCREEN_HEIGHT_PX - 1, 0);
    blit_plane(get_screen_pixels(), PLANE_A_LO, get_scanline_padding(), hscroll_empty, 0, 0, SCREEN_HEIGHT_PX - 1, 0);
    blit_plane(get_screen_pixels(), PLANE_A_HI, get_scanline_padding(), hscroll_empty, 0, 0, SCREEN_HEIGHT_PX - 1, 0);
  }
  unlock_screen();
  blit_screen();
}


static void init_floor(void) {
  int i;

  for (i = 0; i < 96; ++i) {
    g_floor[i].StartX = 0;
    g_floor[i].StartY = i * 0x10000;
    g_floor[i].DeltaX = 0x10000;
    g_floor[i].DeltaY = 0;
  }
}


static void update_floor(void) {
  short* p_tvadr = (short*)tv_adr;
  int i;

  for (i = 0; i < 96; ++i) {
    g_floor[i].StartX = *p_tvadr++ * 0x2000;
    g_floor[i].StartY = *p_tvadr++ * 0x2000;
    g_floor[i].DeltaX = *p_tvadr++ / 5 * 128;
    g_floor[i].DeltaY = *p_tvadr++ / 5 * 128;
  }
}


static void set_hscroll(unsigned short hscroll_plane[SCREEN_HEIGHT_PX], unsigned short value) {
  int i;

  for (i = 0; i < SCREEN_HEIGHT_PX; ++i) {
    hscroll_plane[i] = value & PLANE_WIDTH_PX - 1;
  }
}
