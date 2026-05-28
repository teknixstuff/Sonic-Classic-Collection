#include "options.h"
#include <string.h>
#include "graphics/screen.h"
#include "graphics/sprites.h"
#include "graphics/sprites2.h"
#include "input/input.h"
#include "sequence.h"
#include "audio.h"
#include "GAME/EQU.h"
static void load_options(void);
static void unload_options(void);
static void draw_options(void);
static int OPT_main(void);
static void OPT_update_menu(void);
static void OPT_start(void);
static void OPT_menu(void);
static int OPT_end(int newret);
static unsigned short get_char_sprite_index_color_0(char code);
static unsigned short get_char_sprite_index_color_1(char code);
static void update_soundtrack(int color);
static void update_soundtrack_choice(void);
static void update_skip_time_warp(int color);
static void update_skip_time_warp_choice(void);

extern int g_quit;

static unsigned short menukind;
int g_use_original_soundtrack = 1;
int g_skip_time_warp = 0;
static sprite_info OPT_sprites[16] = {
  {   0, 168,  84, 0 }, /* background */
  {  80, 168,  85, 0 }, /* background */
  { 160, 168,  86, 0 }, /* background */
  { 240, 168,  87, 0 }, /* background */
  {   0, 112,  88, 0 }, /* background */
  {  80, 112,  89, 0 }, /* background */
  { 160, 112,  90, 0 }, /* background */
  { 240, 112,  91, 0 }, /* background */
  {   0,  56,  92, 0 }, /* background */
  {  80,  56,  93, 0 }, /* background */
  { 160,  56,  94, 0 }, /* background */
  { 240,  56,  95, 0 }, /* background */
  {   0,   0,  96, 0 }, /* background */
  {  80,   0,  97, 0 }, /* background */
  { 160,   0,  98, 0 }, /* background */
  { 240,   0,  99, 0 }  /* background */
};
static PALETTEENTRY tblPal1[16] = {
  {   0,   0,   0, 1 }, {  32,  32,  32, 1 }, {  64,  64,  64, 1 }, { 128, 128, 128, 1 },
  {   0,   0,   0, 1 }, { 192, 192, 192, 1 }, { 224, 224, 224, 1 }, {   0,   0, 224, 1 },
  { 160, 160, 160, 1 }, {   0,   0, 224, 1 }, {   0,   0, 224, 1 }, {   0,   0, 224, 1 },
  {   0,   0, 224, 1 }, {   0,   0, 224, 1 }, {   0,   0, 224, 1 }, {   0,   0, 224, 1 }
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


void options(void) {
  load_options();
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
    next = OPT_main();
    if (next != 0) break;
    draw_options();
  }

  unload_options();
}


static void load_options(void) {
  int palette_offsets[100] = { 16, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 32, 48, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 16 };
  load_menu_sprite_bitmaps("TITLE/BMP/SNDTESTS.CM_", palette_offsets);
}


static void unload_options(void) {
  unload_sprite_bitmaps();
}


static void draw_options(void) {
  int i;

  clear_screen();
  lock_screen();
  if (get_sequencenum() > 1) {
    blit_sprites2(get_screen_pixels(), get_sprites2(), get_scanline_padding());
  }
  unlock_screen();
  blit_screen();
}


static int OPT_main(void) {
  int ret = 0;

  switch (get_sequencenum()) {
    case 1:
      OPT_start();
      break;
    case 2:
      OPT_menu();
      break;
    case 3:
      wait2();
      break;
    case 999:
      ret = OPT_end(9);
      break;
  }

  update_sequence_timer();

  return ret;
}


static void OPT_update_menu(void) {
  if (menukind == 1) {
    update_soundtrack(1);
  }
  else {
    update_soundtrack(2);
  }
  if (menukind == 2) {
    update_skip_time_warp(1);
  }
  else {
    update_skip_time_warp(2);
  }
}


static void OPT_start(void) {
  int n;

  for (n = 0; n < 16; ++n) {
    set_sprite2_info(n, OPT_sprites[n]);
  }
  menukind = 1;
  OPT_update_menu();
  update_soundtrack_choice();
  update_skip_time_warp_choice();
  set_sequencenum(2);
}


static void OPT_menu(void) {
  unsigned short menukind_old;

  if (swdata1.w & 0x200) {
    menukind_old = menukind;
    menukind = menukind + 1 < 2 ? menukind + 1 : 2;
    if (menukind == menukind_old) return;
    OPT_update_menu();
    key_wait(6);
  }
  else if (swdata1.w & 0x100) {
    menukind_old = menukind;
    menukind = menukind - 1 > 1 ? menukind - 1 : 1;
    if (menukind == menukind_old) return;
    OPT_update_menu();
    key_wait(6);
  }
  else if (swdata1.w & 0xC00) {
    if (menukind == 1) {
      g_use_original_soundtrack = !g_use_original_soundtrack;
      update_soundtrack_choice();
    }
    else if (menukind == 2) {
      g_skip_time_warp = !g_skip_time_warp;
      update_skip_time_warp_choice();
    }
    key_wait(6);
  }
  else if (swdata1.w & 0x8000) {
    set_sequencenum(999);
  }
}


static int OPT_end(int newret) {
  int ret = 0;

  if (get_timercount() == 0) {
    ret = newret;
  }

  return ret;
}


static unsigned short get_char_sprite_index_color_0(char code) {
  int index;

  if (code == ' ') {
    return 0;
  }
  else if (code == '.') {
    index = 81;
  }
  else if (code < 'A') {
    index = code - 39;
  }
  else {
    index = code - 46;
  }

  return index + 1;
}


static unsigned short get_char_sprite_index_color_1(char code) {
  unsigned short index;

  if (code == ' ') {
    return 0;
  }
  else if (code == '.') {
    index = 82;
  }
  else if (code < 'A') {
    index = code - 3;
  }
  else {
    index = code - 10;
  }

  return index + 1;
}


static void update_soundtrack(int color) {
  unsigned short(*func)(char) = &get_char_sprite_index_color_0;

  if (color == 1) {
    func = &get_char_sprite_index_color_1;
  }
  set_string_sprites2("SOUNDTRACK", 12, 25, 44, 80, 8, func);
}


static void update_soundtrack_choice(void) {
  char choices[2][13] = {
    "AMERICAN",
    "ORIGINAL"
  };

  set_string_sprites2(choices[g_use_original_soundtrack], 8, 37, 200, 80, 8, &get_char_sprite_index_color_0);
}


static void update_skip_time_warp(int color) {
  unsigned short(*func)(char) = &get_char_sprite_index_color_0;

  if (color == 1) {
    func = &get_char_sprite_index_color_1;
  }
  set_string_sprites2("SKIP TIME WARP", 14, 45, 44, 112, 8, func);
}


static void update_skip_time_warp_choice(void) {
  char choices[2][4] = {
    "NO ",
    "YES"
  };

  set_string_sprites2(choices[g_skip_time_warp], 3, 59, 200, 112, 8, &get_char_sprite_index_color_0);
}
