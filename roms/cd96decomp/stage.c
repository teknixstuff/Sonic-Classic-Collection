#include "stage.h"
#include <stdio.h>
#include "audio.h"
#include "constants.h"
#include "gameflagtype.h"
#include "graphics/screen.h"
#include "graphics/sprites.h"
#include "graphics/tiles.h"
#include "input/input.h"
#include "score.h"
#include "specialstage.h"
#include "stageid.h"
#include "thanks.h"
#include "timewarp.h"
#include "GAME/EQU.h"
#include "GAME/SPECIAL/COMMON.h"
#include "GAME/TITLE/COMMON/SCORE_DATA_TYPES.h"
#include "GAME/COL.h"
#include "GAME/GAME.h"
static void set_stage(stage_id id, int use_stageno);
static void load_stage(void);
static void unload_stage(void);
static void manage_stage(int test);
static gameflag_type run_stage(void);
static void draw_stage(void);
static void read_stage_string(char* str);

extern int g_quit;
extern bmp_info SprBmp[700];
extern score_data g_current_score_data;
extern int g_skip_time_warp;

static int g_good_future = 0;


void start_new_game(void) {
  play_start = 0;
  plflag = 0;
  clrspflg_save = 0;
  stagenm = 0;
  emie3end = 0;

  set_stage(R11A, 0);
  load_stage();
  clear_palette();
  game_init();
  manage_stage(0);
}


void continue_game(void) {
  stage_id id = R11A;

  play_start = 0;
  plflag = 0;
  clrspflg_save = g_current_score_data.clrspflg_save;
  stagenm = g_current_score_data.stagenm;
  emie3end = 0;

  if (g_current_score_data.roundNo < 7) {
    id = g_current_score_data.roundNo * 10;
  }
  else {
    id = R81A;
  }
  set_stage(id, 0);
  load_stage();
  clear_palette();
  game_init();
  manage_stage(0);
}


void start_stage(stage_id id) {
  plflag = 0;
  clrspflg_save = 0;
  stagenm = 0;

  set_stage(id, 0);
  load_stage();
  clear_palette();
  game_init();
  manage_stage(1);
}


static void set_stage(stage_id id, int use_stageno) {
  if (use_stageno == 0) {
    unsigned char round = id / 10;
    unsigned char level = id % 10;
    unsigned char zone = level / 4;

    stageno.b.h = round;
    stageno.b.l = zone;
    if (level >= 8) {
      time_flag = 2;
    }
    else if (level % 4 >= 2) {
      time_flag = 2;
    }
    else if (level % 4 == 1) {
      time_flag = 0;
    }
    else {
      time_flag = 1;
    }
    generate_flag = 0;
    gf_flag = 0;
    if (level == 8 || level % 4 == 2) {
      generate_flag = 1;
    }
    else if (level == 9 || level % 4 == 3) {
      generate_flag = 0;
    }
  }
  else {
    unsigned char zone = stageno.b.l;

    if (time_flag & 0x80) {
      time_flag &= 0x7F;
    }
    else if (zone == 0) {
      generate_flag = 0;
      gf_flag = 0;
      projector_flag = 0;
    }
  }
  stageno_i.w = stageno.w;
  time_flag_i = time_flag;
}


static void load_stage(void) {
  char stage_str[4];
  char path[256];
  unsigned char stage_tile_changes[7][3][3] = {
    { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
    { { 0, 0, 0 }, { 0, 1, 1 }, { 0, 0, 0 } },
    { { 0, 1, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
    { { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 1 } },
    { { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 1 } },
    { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
    { { 0, 1, 1 }, { 1, 1, 1 }, { 0, 0, 1 } }
  };

  read_stage_string(stage_str);
  sprintf(path, "R%c/%3s/SCMP%3s.CM_", stage_str[0], stage_str, stage_str);
  load_sprite_bitmaps(path, (unsigned char(*)[3])SprBmp);
  sprintf(path, "R%c/%3s/TCMP%3s.CM_", stage_str[0], stage_str, stage_str);
  load_tile_bitmaps(path, 0);
  if (stage_tile_changes[stageno.b.h][stageno.b.l][time_flag & 0x7F] != 0) {
    sprintf(path, "R%c/%3s/TCHG%3s.CM_", stage_str[0], stage_str, stage_str);
    load_tile_change_bitmaps(path);
  }
}


static void unload_stage(void) {
  pause_bgm();
  unload_sprite_bitmaps();
  unload_tile_bitmaps();
}


static void manage_stage(int test) {
  while (g_quit == 0) {
    gameflag_type next = run_stage();

    if (test != 0) break;

    switch (next) {
      case GAMEFLAG_RESTART:
        if (pl_suu == 0) goto gameover;
        game_init();
        break;
      case GAMEFLAG_NEXT_STAGE:
        plflag = 0;
        projector_flag = 0;
        pause_bgm();
        unload_stage();
        if (special_flag != 0) {
          special_stage();
        }
        if (g_quit == 0) {
          set_stage(0, 1);
          if (stageno.b.l == 0) {
            if (g_good_future != 0) {
              g_current_score_data.clrgood |= 1 << stageno.b.h - 1;
            }
            g_current_score_data.roundNo = stageno.b.h;
            set_score_date(0);
          }
          if (stageno.w == 0x0700) {
            if (clrspflg_save == 0x7F || g_current_score_data.clrgood == 0x7F) {
              gKeepWork.EndingMesType = 1;
            }
            else {
              gKeepWork.EndingMesType = 2;
            }
            read_score_data(read_score_index(0), 0, 0);
            g_current_score_data.roundNo = 7;
            write_score_data(read_score_index(0), 0, 0);
            thanks();
            goto gameover;
          }
          g_good_future = stageno.b.l == 2 && generate_flag != 0;
          write_score_data(read_score_index(0), 0, 0);
          load_stage();
          clear_palette();
          game_init();
        }
        break;
      case GAMEFLAG_NEXT_TIME:
        plflag = 2;
        time_flag |= 0x80;
        pause_bgm();
        unload_stage();
        if (g_skip_time_warp == 0) {
          time_warp();
        }
        if (g_quit == 0) {
          set_stage(0, 1);
          load_stage();
          clear_palette();
          game_init();
        }
        break;
    }
  }

gameover:
  unload_stage();
}


static gameflag_type run_stage(void) {
  start_timer();

  while (g_quit == 0) {
    if (gFadeFlag != 0) {
      if (FadeProc() != 0) {
        gFadeFlag = 0;
      }
    }
    else {
      gameflag_type next;

      poll_controller();
      next = game();
      if (next != GAMEFLAG_NONE) {
        return next;
      }
    }

    draw_stage();
  }

  return GAMEFLAG_NONE;
}


static void draw_stage(void) {
  unsigned short hscroll_a[SCREEN_HEIGHT_PX] = { 0 };
  unsigned short hscroll_b[SCREEN_HEIGHT_PX] = { 0 };
  short stage_hintposi = stageno.b.h == 2 ? hintposi.w : SCREEN_HEIGHT_PX - 1;
  int i;

  for (i = 0; i < SCREEN_HEIGHT_PX; ++i) {
    hscroll_a[i] = scra_h_posiw.w.h;
    hscroll_a[i] &= PLANE_WIDTH_PX - 1;
    hscroll_b[i] = -hscrollbuff[i].w.l;
    hscroll_b[i] &= PLANE_WIDTH_PX - 1;
  }

  clear_screen();
  lock_screen();
  blit_plane(get_screen_pixels(), PLANE_B, get_scanline_padding(), hscroll_b, vscroll.w.l, waterflag, stage_hintposi, 0);
  blit_plane(get_screen_pixels(), PLANE_A_LO, get_scanline_padding(), hscroll_a, vscroll.w.h, waterflag, stage_hintposi, 0);
  blit_sprites_lo(get_screen_pixels(), get_scanline_padding(), waterflag, stage_hintposi);
  blit_plane(get_screen_pixels(), PLANE_A_HI, get_scanline_padding(), hscroll_a, vscroll.w.h, waterflag, stage_hintposi, 0);
  blit_sprites_hi(get_screen_pixels(), get_scanline_padding(), waterflag, stage_hintposi);
  unlock_screen();
  blit_screen();
}


static void read_stage_string(char* str) {
  unsigned char round = stageno.b.h + 1;
  unsigned char zone = stageno.b.l + 1;

  if (round > 1) {
    ++round;
  }
  *str++ = '0' + round;
  *str++ = '0' + zone;

  switch (time_flag & 0x7F) {
    case 0:
      *str++ = 'B';
      break;
    case 1:
      *str++ = 'A';
      break;
    case 2:
      if (generate_flag != 0) {
        *str++ = 'C';
      }
      else {
        *str++ = 'D';
      }
      break;
  }
  *str++ = 0;
}
