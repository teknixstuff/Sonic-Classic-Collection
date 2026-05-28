#include "besttimes.h"
#include <string.h>
#include "graphics/screen.h"
#include "graphics/spriteinfo.h"
#include "graphics/sprites.h"
#include "graphics/sprites2.h"
#include "input/input.h"
#include "sequence.h"
#include "services.h"
#include "GAME/EQU.h"
static void load_best_times(void);
static void unload_best_times(void);
static void draw_best_times(void);
static int BEST_main(void);
static void BEST_update_menu(void);
static int BEST_menumax_check(int index);
static void BEST_start(void);
static void BEST_menu(void);
static int BEST_end(void);
static unsigned short get_char_sprite_index_color_0(char code);
static unsigned short get_char_sprite_index_color_1(char code);

extern int g_quit;

static sprite_info BEST_sprites[100] = {
  {   0,   0,   1, 0 }, /* 0 */
  {   0,   0,   2, 0 }, /* 1 */
  {   0,   0,   3, 0 }, /* 2 */
  {   0,   0,   4, 0 }, /* 3 */
  {   0,   0,   5, 0 }, /* 4 */
  {   0,   0,   6, 0 }, /* 5 */
  {   0,   0,   7, 0 }, /* 6 */
  {   0,   0,   8, 0 }, /* 7 */
  {   0,   0,   9, 0 }, /* 8 */
  {   0,   0,  10, 0 }, /* 9 */
  {   0,   0,  11, 0 }, /* A */
  {   0,   0,  12, 0 }, /* B */
  {   0,   0,  13, 0 }, /* C */
  {   0,   0,  14, 0 }, /* D */
  {   0,   0,  15, 0 }, /* E */
  {   0,   0,  16, 0 }, /* F */
  {   0,   0,  17, 0 }, /* G */
  {   0,   0,  18, 0 }, /* H */
  {   0,   0,  19, 0 }, /* I */
  {   0,   0,  20, 0 }, /* J */
  {   0,   0,  21, 0 }, /* K */
  {   0,   0,  22, 0 }, /* L */
  {   0,   0,  23, 0 }, /* M */
  {   0,   0,  24, 0 }, /* N */
  {   0,   0,  25, 0 }, /* O */
  {   0,   0,  26, 0 }, /* P */
  {   0,   0,  27, 0 }, /* Q */
  {   0,   0,  28, 0 }, /* R */
  {   0,   0,  29, 0 }, /* S */
  {   0,   0,  30, 0 }, /* T */
  {   0,   0,  31, 0 }, /* U */
  {   0,   0,  32, 0 }, /* V */
  {   0,   0,  33, 0 }, /* W */
  {   0,   0,  34, 0 }, /* X */
  {   0,   0,  35, 0 }, /* Y */
  {   0,   0,  36, 0 }, /* Z */
  {   0,   0,  37, 0 }, /* 0 */
  {   0,   0,  38, 0 }, /* 1 */
  {   0,   0,  39, 0 }, /* 2 */
  {   0,   0,  40, 0 }, /* 3 */
  {   0,   0,  41, 0 }, /* 4 */
  {   0,   0,  42, 0 }, /* 5 */
  {   0,   0,  43, 0 }, /* 6 */
  {   0,   0,  44, 0 }, /* 7 */
  {   0,   0,  45, 0 }, /* 8 */
  {   0,   0,  46, 0 }, /* 9 */
  {   0,   0,  47, 0 }, /* A */
  {   0,   0,  48, 0 }, /* B */
  {   0,   0,  49, 0 }, /* C */
  {   0,   0,  50, 0 }, /* D */
  {   0,   0,  51, 0 }, /* E */
  {   0,   0,  52, 0 }, /* F */
  {   0,   0,  53, 0 }, /* G */
  {   0,   0,  54, 0 }, /* H */
  {   0,   0,  55, 0 }, /* I */
  {   0,   0,  56, 0 }, /* J */
  {   0,   0,  57, 0 }, /* K */
  {   0,   0,  58, 0 }, /* L */
  {   0,   0,  59, 0 }, /* M */
  {   0,   0,  60, 0 }, /* N */
  {   0,   0,  61, 0 }, /* O */
  {   0,   0,  62, 0 }, /* P */
  {   0,   0,  63, 0 }, /* Q */
  {   0,   0,  64, 0 }, /* R */
  {   0,   0,  65, 0 }, /* S */
  {   0,   0,  66, 0 }, /* T */
  {   0,   0,  67, 0 }, /* U */
  {   0,   0,  68, 0 }, /* V */
  {   0,   0,  69, 0 }, /* W */
  {   0,   0,  70, 0 }, /* X */
  {   0,   0,  71, 0 }, /* Y */
  {   0,   0,  72, 0 }, /* Z */
  {   0,   0,  73, 0 }, /* - */
  {   0, 168,  74, 0 }, /* background */
  {  80, 168,  75, 0 }, /* background */
  { 160, 168,  76, 0 }, /* background */
  { 240, 168,  77, 0 }, /* background */
  {   0, 112,  78, 0 }, /* background */
  {  80, 112,  79, 0 }, /* background */
  { 160, 112,  80, 0 }, /* background */
  { 240, 112,  81, 0 }, /* background */
  {   0,  56,  82, 0 }, /* background */
  {  80,  56,  83, 0 }, /* background */
  { 160,  56,  84, 0 }, /* background */
  { 240,  56,  85, 0 }, /* background */
  {   0,   0,  86, 0 }, /* background */
  {  80,   0,  87, 0 }, /* background */
  { 160,   0,  88, 0 }, /* background */
  { 240,   0,  89, 0 }, /* background */
  {   0,   0,  90, 0 }, /* space */
  {   0,   0,  91, 0 }, /* ' */
  {   0,   0,  92, 0 }, /* " */
  {   0, 168,  93, 0 }, /* top background overlay */
  {  80, 168,  94, 0 }, /* top background overlay */
  { 160, 168,  95, 0 }, /* top background overlay */
  { 240, 168,  96, 0 }, /* top background overlay */
  {   0,   0,  97, 0 }, /* bottom background overlay */
  {  80,   0,  98, 0 }, /* bottom background overlay */
  { 160,   0,  99, 0 }, /* bottom background overlay */
  { 240,   0, 100, 0 } /* bottom background overlay */
};
static PALETTEENTRY tblPal1[16] = {
  {   0,   0,   0, 1 }, {  64,  64, 128, 1 },
  { 160, 160, 224, 1 }, { 160, 160, 224, 1 },
  {   0,   0,   0, 1 }, { 160, 160, 224, 1 },
  { 160, 160, 224, 1 }, {   0, 160, 224, 1 },
  { 160, 160, 224, 1 }, {   0,   0, 224, 1 },
  { 160, 160, 224, 1 }, { 160, 160, 224, 1 },
  { 160, 160, 224, 1 }, { 160, 160, 224, 1 },
  { 160, 160, 224, 1 }, { 160, 160, 224, 1 }
};
static PALETTEENTRY tblPal2[16] = {
  {   0,   0,   0, 1 }, {  32,  32,  32, 1 },
  {  64,  64,  64, 1 }, { 128, 128, 128, 1 },
  {   0,   0,   0, 1 }, { 192, 192, 192, 1 },
  { 224, 224, 224, 1 }, { 224, 128,   0, 1 },
  { 160, 160, 160, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static PALETTEENTRY tblPal3[16] = {
  {   0,   0,   0, 1 }, {  32,  32,  32, 1 },
  {  64,  64,  64, 1 }, { 128, 128, 128, 1 },
  {  64,  64, 128, 1 }, { 192, 192, 192, 1 },
  { 224, 224, 224, 1 }, { 160, 160, 224, 1 },
  { 160, 160, 160, 1 }, { 128, 128, 192, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  { 192, 224, 224, 1 }, { 160, 224, 224, 1 },
  { 128, 224, 224, 1 }, {  64, 224, 224, 1 }
};
static PALETTEENTRY tblPal4[16] = {
  {   0,   0,   0, 1 }, { 160, 224, 224, 1 },
  { 224, 224, 224, 1 }, { 128, 224, 224, 1 },
  { 192, 224, 224, 1 }, {  64, 224, 224, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static char menuTbl[32][27] = {
  { "                          " },
  { "SONIC CD TEAM BEST OF TIME" },
  { " STAGE 1-1  00,24.10  CXX " },
  { " STAGE 1-2  00,21.55  TOT" },
  { " STAGE 1-3  00,21.08  ANN" },
  { " STAGE 2-1  00,49.60  TOT" },
  { " STAGE 2-2  00,47.50  TOT" },
  { " STAGE 2-3  00,14.85  SPE" },
  { " STAGE 3-1  00,41.20  SPE" },
  { " STAGE 3-2  00,54.75  SPE" },
  { " STAGE 3-3  01,01.33  KAZ" },
  { " STAGE 4-1  00,28.85  ANN" },
  { " STAGE 4-2  00,36.25  DOS" },
  { " STAGE 4-3  00,59.60  DOS" },
  { " STAGE 5-1  00,50.10  TAC" },
  { " STAGE 5-2  00,48.83  AXE" },
  { " STAGE 5-3  01,10.50  DOS" },
  { " STAGE 6-1  00,33.65  CXX" },
  { " STAGE 6-2  00,27.96  TAK" },
  { " STAGE 6-3  01,09.75  SPE" },
  { " STAGE 7-1  00,32.78  ANN" },
  { " STAGE 7-2  02,08.41  UNT" },
  { " STAGE 7-3  01,30.75  TNO" },
  { " SPECIAL 1  00,17.00  CXX" },
  { " SPECIAL 2  00,14.85  TOT" },
  { " SPECIAL 3  00,16.00  CXX" },
  { " SPECIAL 4  00,20.65  KAZ" },
  { " SPECIAL 5  00,22.35  KAZ" },
  { " SPECIAL 6  00,16.95  CXX" },
  { " SPECIAL 7  00,19.20  KAZ" },
  { "                         " },
  { "  " }
};
static int menu_index;
static int scroll_count;
static int menu_y[11] = { 7, 31, 55, 79, 103, 127, 151, 175, 199, 0, 0 };
static int MENUITEMMAX = 32;


void best_times(void) {
  load_best_times();
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
    next = BEST_main();
    if (next != 0) break;
    draw_best_times();
  }

  unload_best_times();
}


static void load_best_times(void) {
  int palette_offsets[100] = { 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 48, 48, 48, 64, 64, 64, 64, 64, 64, 64, 64 };
  load_menu_sprite_bitmaps("TITLE/BMP/BESTTIME.CM_", palette_offsets);
}


static void unload_best_times(void) {
  unload_sprite_bitmaps();
}


static void draw_best_times(void) {
  clear_screen();
  lock_screen();
  if (get_sequencenum() > 1) {
    blit_sprites2(get_screen_pixels(), get_sprites2(), get_scanline_padding());
  }
  unlock_screen();
  blit_screen();
}


static int BEST_main(void) {
  int ret = 0;

  switch (get_sequencenum()) {
    case 1:
      BEST_start();
      break;
    case 2:
      BEST_menu();
      break;
    case 3:
      wait2();
      break;
    case 998:
      ret = BEST_end();
      break;
  }

  update_sequence_timer();

  return ret;
}


static void BEST_update_menu(void) {
  int i;

  for (i = 0; i < 9; ++i) {
    unsigned short(*func)(char) = &get_char_sprite_index_color_1;
    int index = BEST_menumax_check(menu_index + i);

    if (index == 1) {
      func = &get_char_sprite_index_color_0;
    }
    set_string_sprites2(menuTbl[index], 26, 16 + i * 26, 56, scroll_count * 8 + menu_y[i], 8, func);
  }
}


static int BEST_menumax_check(int index) {
  if (index >= MENUITEMMAX) {
    return index - MENUITEMMAX;
  }
  return index;
}


static void BEST_start(void) {
  int n;

  CDPlay(29);
  for (n = 0; n < 16; ++n) {
    set_sprite2_info(n, BEST_sprites[73 + n]);
  }
  for (n = 0; n < 8; ++n) {
    set_sprite2_info(250 + n, BEST_sprites[92 + n]);
  }

  menu_index = 0;
  scroll_count = 0;
  BEST_update_menu();
  set_sequencenum(2);
}


static void BEST_menu(void) {
  if (swdata1.w & 0x100) {
    if (menu_index > 0 || (menu_index == 0 && scroll_count < 0)) {
      ++scroll_count;
      if (scroll_count == 3) {
        scroll_count = 0;
        if (menu_index != 0) {
          --menu_index;
        }
      }
      BEST_update_menu();
      key_wait(0);
    }
  }
  else {
    if (swdata1.w & 0x200) {
      if (menu_index <= MENUITEMMAX - 11
          || (menu_index == MENUITEMMAX - 10 && scroll_count >= -1)) {
        --scroll_count;
        if (scroll_count == -3) {
          scroll_count = 0;
          if (menu_index != MENUITEMMAX - 1) {
            ++menu_index;
          }
        }
        BEST_update_menu();
        key_wait(0);
      }
    }
  }
  if (swdata1.w & 0x1000) {
    set_sequencenum(998);
  }
}


static int BEST_end(void) {
  int ret = 0;

  if (get_timercount() == 0) {
    ret = 9;
    CDPause(2);
  }

  return ret;
}


static unsigned short get_char_sprite_index_color_0(char code) {
  int index;

  if (code == ' ') {
    index = 89;
  }
  else if (code == ',') {
    index = 90;
  }
  else if (code == '.') {
    index = 91;
  }
  else if (code == '-') {
    index = 72;
  }
  else if (code < 'A') {
    index = code - 48;
  }
  else {
    index = code - 55;
  }

  return index + 1;
}


static unsigned short get_char_sprite_index_color_1(char code) {
  int index;

  if (code == ' ') {
    index = 89;
  }
  else if (code == ',') {
    index = 90;
  }
  else if (code == '.') {
    index = 91;
  }
  else if (code == '-') {
    index = 72;
  }
  else if (code < 'A') {
    index = code - 12;
  }
  else {
    index = code - 19;
  }

  return index + 1;
}
