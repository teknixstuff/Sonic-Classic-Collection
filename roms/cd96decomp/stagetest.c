#include "stagetest.h"
#include <string.h>
#include "graphics/screen.h"
#include "graphics/spriteinfo.h"
#include "graphics/sprites.h"
#include "graphics/sprites2.h"
#include "input/input.h"
#include "sequence.h"
#include "stage.h"
#include "stageid.h"
#include "GAME/EQU.h"
static void load_stage_test(void);
static void unload_stage_test(void);
static void draw_stage_test(void);
static int STG_main(void);
static void STG_update_menu(void);
static void STG_start(void);
static void STG_menu(void);
static int STG_end(int newret);
static unsigned short get_char_sprite_index(char code);

extern int g_quit;

static sprite_info STG_sprites[64] = {
  { 120,  40,  1, 0 }, /* S */
  { 128,  40,  2, 0 }, /* T */
  { 136,  40,  3, 0 }, /* A */
  { 144,  40,  4, 0 }, /* G */
  { 152,  40,  5, 0 }, /* E */
  { 168,  40,  6, 0 }, /* S */
  { 176,  40,  7, 0 }, /* E */
  { 184,  40,  8, 0 }, /* L */
  { 192,  40,  9, 0 }, /* E */
  { 200,  40, 10, 0 }, /* C */
  { 208,  40, 11, 0 }, /* T */
  {   0,   0, 12, 0 }, /* 0 */
  {   0,   0, 13, 0 }, /* 1 */
  {   0,   0, 14, 0 }, /* 2 */
  {   0,   0, 15, 0 }, /* 3 */
  {   0,   0, 16, 0 }, /* 4 */
  {   0,   0, 17, 0 }, /* 5 */
  {   0,   0, 18, 0 }, /* 6 */
  {   0,   0, 19, 0 }, /* 7 */
  {   0,   0, 20, 0 }, /* 8 */
  {   0,   0, 21, 0 }, /* 9 */
  {   0,   0, 22, 0 }, /* A */
  {   0,   0, 23, 0 }, /* B */
  {   0,   0, 24, 0 }, /* C */
  {   0,   0, 25, 0 }, /* D */
  {   0,   0, 26, 0 }, /* E */
  {   0,   0, 27, 0 }, /* F */
  {   0,   0, 28, 0 }, /* G */
  {   0,   0, 29, 0 }, /* H */
  {   0,   0, 30, 0 }, /* I */
  {   0,   0, 31, 0 }, /* J */
  {   0,   0, 32, 0 }, /* K */
  {   0,   0, 33, 0 }, /* L */
  {   0,   0, 34, 0 }, /* M */
  {   0,   0, 35, 0 }, /* N */
  {   0,   0, 36, 0 }, /* O */
  {   0,   0, 37, 0 }, /* P */
  {   0,   0, 38, 0 }, /* Q */
  {   0,   0, 39, 0 }, /* R */
  {   0,   0, 40, 0 }, /* S */
  {   0,   0, 41, 0 }, /* T */
  {   0,   0, 42, 0 }, /* U */
  {   0,   0, 43, 0 }, /* V */
  {   0,   0, 44, 0 }, /* W */
  {   0,   0, 45, 0 }, /* X */
  {   0,   0, 46, 0 }, /* Y */
  {   0,   0, 47, 0 }, /* Z */
  {   0,   0, 48, 0 }, /* - */
  {   0, 168, 49, 0 }, /* background */
  {  80, 168, 50, 0 }, /* background */
  { 160, 168, 51, 0 }, /* background */
  { 240, 168, 52, 0 }, /* background */
  {   0, 112, 53, 0 }, /* background */
  {  80, 112, 54, 0 }, /* background */
  { 160, 112, 55, 0 }, /* background */
  { 240, 112, 56, 0 }, /* background */
  {   0,  56, 57, 0 }, /* background */
  {  80,  56, 58, 0 }, /* background */
  { 160,  56, 59, 0 }, /* background */
  { 240,  56, 60, 0 }, /* background */
  {   0,   0, 61, 0 }, /* background */
  {  80,   0, 62, 0 }, /* background */
  { 160,   0, 63, 0 }, /* background */
  { 240,   0, 64, 0 }  /* background */
};
static PALETTEENTRY tblPal1[16] = {
  {   0,   0,   0, 1 }, {  32,  32,  32, 1 }, {  64,  64,  64, 1 }, { 128, 128, 128, 1 },
  {   0,   0,   0, 1 }, { 192, 192, 192, 1 }, { 224, 224, 224, 1 }, {   0,   0, 224, 1 },
  { 160, 160, 160, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static PALETTEENTRY tblPal2[16] = {
  {   0,   0,   0, 1 }, {  32,  32,  32, 1 }, {  64,  64,  64, 1 }, { 128, 128, 128, 1 },
  {   0,   0,   0, 1 }, { 192, 192, 192, 1 }, { 224, 224, 224, 1 }, { 224, 128,   0, 1 },
  { 160, 160, 160, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static PALETTEENTRY tblPal3[16] = {
  {   0,   0,   0, 1 }, {  32,  32,  32, 1 }, {  64,  64,  64, 1 }, { 128, 128, 128, 1 },
  {   0,   0,   0, 1 }, { 192, 192, 192, 1 }, { 224, 224, 224, 1 }, { 224, 160, 192, 1 },
  { 160, 160, 160, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static PALETTEENTRY tblPal4[16] = {
  {   0,   0,   0, 1 }, { 160, 224, 224, 1 }, { 224, 224, 224, 1 }, { 128, 224, 224, 1 },
  { 192, 224, 224, 1 }, {  64, 224, 224, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static char menuTbl[70][6] = {
  { "1-1-A" }, { "1-1-B" }, { "1-1-C" }, { "1-1-D" },
  { "1-2-A" }, { "1-2-B" }, { "1-2-C" }, { "1-2-D" },
  { "1-3-C" }, { "1-3-D" },
  { "3-1-A" }, { "3-1-B" }, { "3-1-C" }, { "3-1-D" },
  { "3-2-A" }, { "3-2-B" }, { "3-2-C" }, { "3-2-D" },
  { "3-3-C" }, { "3-3-D" },
  { "4-1-A" }, { "4-1-B" }, { "4-1-C" }, { "4-1-D" },
  { "4-2-A" }, { "4-2-B" }, { "4-2-C" }, { "4-2-D" },
  { "4-3-C" }, { "4-3-D" },
  { "5-1-A" }, { "5-1-B" }, { "5-1-C" }, { "5-1-D" },
  { "5-2-A" }, { "5-2-B" }, { "5-2-C" }, { "5-2-D" },
  { "5-3-C" }, { "5-3-D" },
  { "6-1-A" }, { "6-1-B" }, { "6-1-C" }, { "6-1-D" },
  { "6-2-A" }, { "6-2-B" }, { "6-2-C" }, { "6-2-D" },
  { "6-3-C" }, { "6-3-D" },
  { "7-1-A" }, { "7-1-B" }, { "7-1-C" }, { "7-1-D" },
  { "7-2-A" }, { "7-2-B" }, { "7-2-C" }, { "7-2-D" },
  { "7-3-C" }, { "7-3-D" },
  { "8-1-A" }, { "8-1-B" }, { "8-1-C" }, { "8-1-D" },
  { "8-2-A" }, { "8-2-B" }, { "8-2-C" }, { "8-2-D" },
  { "8-3-C" }, { "8-3-D" }
};
static int menu_index;
static int MENUITEMMAX = 70;


void stage_test(void) {
  load_stage_test();
  clear_palette();
  memcpy(&lpcolorwk[0], tblPal1, sizeof(tblPal1));
  memcpy(&lpcolorwk[16], tblPal2, sizeof(tblPal2));
  memcpy(&lpcolorwk[32], tblPal3, sizeof(tblPal3));
  memcpy(&lpcolorwk[48], tblPal4, sizeof(tblPal4));
  init_sequence();
  start_timer();

  while (g_quit == 0) {
    int next;

    poll_controller();
    next = STG_main();
    if (next != 0) {
      if (next != 999) {
        unload_stage_test();
        start_stage((stage_id)(next - 1));
      }
      break;
    }
    draw_stage_test();
  }

  unload_stage_test();
}


static void load_stage_test(void) {
  int palette_offsets[64] = { 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64 };
  load_menu_sprite_bitmaps("TITLE/BMP/STAGES.CM_", palette_offsets);
}


static void unload_stage_test(void) {
  unload_sprite_bitmaps();
}


static void draw_stage_test(void) {
  int i;

  clear_screen();
  lock_screen();
  if (get_sequencenum() > 1) {
    blit_sprites2(get_screen_pixels(), get_sprites2(), get_scanline_padding());
  }
  unlock_screen();
  blit_screen();
}


static int STG_main(void) {
  int ret = 0;

  switch (get_sequencenum()) {
    case 1:
      STG_start();
      break;
    case 2:
      STG_menu();
      break;
    case 3:
      wait2();
      break;
    case 999:
      ret = STG_end(menu_index + 1);
      break;
    case 998:
      ret = STG_end(999);
      break;
  }

  update_sequence_timer();

  return ret;
}


static void STG_update_menu(void) {
  set_string_sprites2(menuTbl[menu_index], 5, 27, 120, 80, 8, &get_char_sprite_index);
}


static void STG_start(void) {
  int n;

  clear_sprites2();
  for (n = 0; n < 16; ++n) {
    set_sprite2_info(n, STG_sprites[48 + n]);
  }
  for (n = 0; n < 11; ++n) {
    set_sprite2_info(16 + n, STG_sprites[n]);
  }
  menu_index = 0;
  STG_update_menu();
  set_sequencenum(2);
}


static void STG_menu(void) {
  if (swdata1.w & 0x100) {
    if (menu_index == 0) {
      menu_index = MENUITEMMAX - 1;
    }
    else {
      --menu_index;
    }
    STG_update_menu();
    key_wait(6);
  }
  else if (swdata1.w & 0x200) {
    if (menu_index == MENUITEMMAX - 1) {
      menu_index = 0;
    }
    else {
      ++menu_index;
    }
    STG_update_menu();
    key_wait(6);
  }
  else if (swdata1.w & 0x4000) {
    set_sequencenum(999);
  }
  if (swdata1.w & 0x1000) {
    set_sequencenum(998);
  }
}


static int STG_end(int newret) {
  int ret = 0;

  if (get_timercount() == 0) {
    ret = newret;
  }

  return ret;
}


static unsigned short get_char_sprite_index(char code) {
  unsigned short index;

  if (code == '-') {
    index = 47;
}
  else if (code < 'A') {
    index = code - 37;
  }
  else {
    index = code - 44;
  }

  return index + 1;
}
