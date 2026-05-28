#include "soundtest.h"
#include <string.h>
#include "audio.h"
#include "graphics/screen.h"
#include "graphics/spriteinfo.h"
#include "graphics/sprites.h"
#include "graphics/sprites2.h"
#include "input/input.h"
#include "sequence.h"
#include "services.h"
#include "specialstage.h"
#include "GAME/EQU.h"
#include "GAME/GAME.h"
#include "GAME/SPECIAL/COMMON.h"
static void load_sound_test(void);
static void unload_sound_test(void);
static void draw_sound_test(void);
static int SND_main(void);
static void SND_update_menu(void);
static void SND_start(void);
static void SND_menu(void);
static int SND_end(int newret);
static int mc_sonic_create(short cgno);
static void SND_kakusi(void);
static void SND_special_mes(void);
static unsigned short get_char_sprite_index_color_0(char code);
static unsigned short get_char_sprite_index_color_1(char code);
static void update_pcm(int color);
static void update_pcm_no(unsigned char number);
static void update_da(int color);
static void update_da_no(unsigned char number);

extern int g_quit;

static sprite_info SND_sprites[100] = {
  { 120,  40,   1, 0 }, /* S */
  { 128,  40,   2, 0 }, /* O */
  { 136,  40,   3, 0 }, /* U */
  { 144,  40,   4, 0 }, /* N */
  { 152,  40,   5, 0 }, /* D */
  { 168,  40,   6, 0 }, /* T */
  { 176,  40,   7, 0 }, /* E */
  { 184,  40,   8, 0 }, /* S */
  { 192,  40,   9, 0 }, /* T */
  {   0,   0,  10, 0 }, /* 0 */
  {   0,   0,  11, 0 }, /* 1 */
  {   0,   0,  12, 0 }, /* 2 */
  {   0,   0,  13, 0 }, /* 3 */
  {   0,   0,  14, 0 }, /* 4 */
  {   0,   0,  15, 0 }, /* 5 */
  {   0,   0,  16, 0 }, /* 6 */
  {   0,   0,  17, 0 }, /* 7 */
  {   0,   0,  18, 0 }, /* 8 */
  {   0,   0,  19, 0 }, /* 9 */
  {   0,   0,  20, 0 }, /* A */
  {   0,   0,  21, 0 }, /* B */
  {   0,   0,  22, 0 }, /* C */
  {   0,   0,  23, 0 }, /* D */
  {   0,   0,  24, 0 }, /* E */
  {   0,   0,  25, 0 }, /* F */
  {   0,   0,  26, 0 }, /* G */
  {   0,   0,  27, 0 }, /* H */
  {   0,   0,  28, 0 }, /* I */
  {   0,   0,  29, 0 }, /* J */
  {   0,   0,  30, 0 }, /* K */
  {   0,   0,  31, 0 }, /* L */
  {   0,   0,  32, 0 }, /* M */
  {   0,   0,  33, 0 }, /* N */
  {   0,   0,  34, 0 }, /* O */
  {   0,   0,  35, 0 }, /* P */
  {   0,   0,  36, 0 }, /* Q */
  {   0,   0,  37, 0 }, /* R */
  {   0,   0,  38, 0 }, /* S */
  {   0,   0,  39, 0 }, /* T */
  {   0,   0,  40, 0 }, /* U */
  {   0,   0,  41, 0 }, /* V */
  {   0,   0,  42, 0 }, /* W */
  {   0,   0,  43, 0 }, /* X */
  {   0,   0,  44, 0 }, /* Y */
  {   0,   0,  45, 0 }, /* Z */
  {   0,   0,  46, 0 }, /* 0 */
  {   0,   0,  47, 0 }, /* 1 */
  {   0,   0,  48, 0 }, /* 2 */
  {   0,   0,  49, 0 }, /* 3 */
  {   0,   0,  50, 0 }, /* 4 */
  {   0,   0,  51, 0 }, /* 5 */
  {   0,   0,  52, 0 }, /* 6 */
  {   0,   0,  53, 0 }, /* 7 */
  {   0,   0,  54, 0 }, /* 8 */
  {   0,   0,  55, 0 }, /* 9 */
  {   0,   0,  56, 0 }, /* A */
  {   0,   0,  57, 0 }, /* B */
  {   0,   0,  58, 0 }, /* C */
  {   0,   0,  59, 0 }, /* D */
  {   0,   0,  60, 0 }, /* E */
  {   0,   0,  61, 0 }, /* F */
  {   0,   0,  62, 0 }, /* G */
  {   0,   0,  63, 0 }, /* H */
  {   0,   0,  64, 0 }, /* I */
  {   0,   0,  65, 0 }, /* J */
  {   0,   0,  66, 0 }, /* K */
  {   0,   0,  67, 0 }, /* L */
  {   0,   0,  68, 0 }, /* M */
  {   0,   0,  69, 0 }, /* N */
  {   0,   0,  70, 0 }, /* O */
  {   0,   0,  71, 0 }, /* P */
  {   0,   0,  72, 0 }, /* Q */
  {   0,   0,  73, 0 }, /* R */
  {   0,   0,  74, 0 }, /* S */
  {   0,   0,  75, 0 }, /* T */
  {   0,   0,  76, 0 }, /* U */
  {   0,   0,  77, 0 }, /* V */
  {   0,   0,  78, 0 }, /* W */
  {   0,   0,  79, 0 }, /* X */
  {   0,   0,  80, 0 }, /* Y */
  {   0,   0,  81, 0 }, /* Z */
  {   0,   0,  82, 0 }, /* & */
  {   0,   0,  83, 0 }, /* & */
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
  { 240,   0,  99, 0 }, /* background */
  {   0,   0, 100, 0 }  /* WELCOME TO SECRET SPECIAL STAGE */
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
static PALETTEENTRY MIYAKEcolor[16] = {
  { 240, 240, 240, 1 }, {   0,   0,   0, 1 }, {   0,   0,  64, 1 }, {   0,   0, 128, 1 },
  {   0,   0, 192, 1 }, {  32,   0, 224, 1 }, {  32,  32, 224, 1 }, {  64, 192, 224, 1 },
  {   0,  64, 224, 1 }, {   0,  32, 224, 1 }, {   0,  32, 192, 1 }, {   0,  32, 160, 1 },
  {   0,  32, 128, 1 }, {   0,  32,  96, 1 }, {   0,  32,  64, 1 }, {   0,  32,  32, 1 }
};
static PALETTEENTRY NISIMURAcolor[16] = {
  {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, {  96,  96,  96, 1 }, { 160, 160, 160, 1 },
  {  32,  32,  32, 1 }, { 240, 240, 240, 1 }, { 240, 240, 240, 1 }, { 240, 240, 240, 1 },
  { 240, 240, 240, 1 }, {  96,  64, 160, 1 }, { 240, 240, 240, 1 }, {   0,   0, 128, 1 },
  {   0,   0,  32, 1 }, {  64,  32, 128, 1 }, { 240, 240, 240, 1 }, { 240, 240, 240, 1 }
};
static PALETTEENTRY SANPEIcolor[16] = {
  {   0,   0,   0, 1 }, {  32,  32, 128, 1 }, {  64,  64, 192, 1 }, {  64,  64, 224, 1 },
  { 240, 240, 240, 1 }, { 224, 224, 192, 1 }, { 224, 224, 224, 1 }, { 160, 160, 160, 1 },
  { 128, 128, 128, 1 }, {  64,  64,  64, 1 }, { 224, 160, 128, 1 }, { 160,  96,  64, 1 },
  { 224,   0,   0, 1 }, { 128,   0,   0, 1 }, {  64,   0,   0, 1 }, { 224, 192, 160, 1 }
};
static PALETTEENTRY YAMAGU1color[16] = {
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, {   0,  32,   0, 1 },
  {  32,  64,   0, 1 }, {  96, 128,  32, 1 }, {  32,  32,  32, 1 }, {  64,  64,  64, 1 },
  {  96,  96, 128, 1 }, { 128, 128, 160, 1 }, { 160, 160, 160, 1 }, { 192, 192, 192, 1 },
  { 224, 224, 128, 1 }, {  64, 128, 224, 1 }, { 128, 128,  96, 1 }, {   0,  32, 208, 1 }
};
static PALETTEENTRY YAMAGU2color[16] = {
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {  64,  64, 128, 1 }, {  96,  96, 160, 1 },
  { 128, 160, 224, 1 }, { 160, 192, 224, 1 }, { 224, 224, 224, 1 }, { 224, 160,   0, 1 },
  { 224, 128,   0, 1 }, { 192,  96,   0, 1 }, { 224, 192, 128, 1 }, { 192, 224, 224, 1 },
  { 160,  64,   0, 1 }, {  96,   0,   0, 1 }, { 192,  32,   0, 1 }, {   0,  32, 192, 1 }
};
static PALETTEENTRY HOSHINOcolor[16] = {
  {   0,   0,   0, 1 }, {   0,  96,   0, 1 }, {  32,  32, 192, 1 }, {  64,  64, 224, 1 },
  {  96,  96, 224, 1 }, { 128, 128, 224, 1 }, { 224, 224, 224, 1 }, { 160, 160, 160, 1 },
  { 128, 128, 128, 1 }, {  64,  64,  64, 1 }, { 224, 160, 128, 1 }, { 160,  96,  64, 1 },
  { 224,   0,   0, 1 }, { 128,   0,   0, 1 }, {  64,   0,   0, 1 }, { 224, 224,   0, 1 }
};
static unsigned char tblPCM[80] = {
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
  10, 11, 11, 12, 13, 14, 15, 16, 17, 18,
  19, 20, 20, 21, 22, 22, 23, 23, 24, 25,
  26, 27, 28, 29, 30, 31, 43, 44, 45, 46,
  47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
  57, 58, 58, 59, 60, 61, 62, 63, 64, 65,
  67, 68, 69, 70, 71, 71, 72, 73, 74, 32,
  33, 34, 35, 36, 37, 38, 39, 40, 41, 42
};
static unsigned char tblDA[34] = {
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
  10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
  20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
  30, 31, 32, 33
};
static int kakusi;
static unsigned short menukind;
static unsigned short pcm_number_index;
static unsigned short da_number_index;


void sound_test(void) {
  load_sound_test();
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
    next = SND_main();
    if (next != 0) {
      if (next == 18) {
        unload_sound_test();
        stagenm = 7;
        special_stage();
      }
      else if (next == 19) {
        SetDebugFlag(1);
      }
      break;
    }
    draw_sound_test();
  }

  unload_sound_test();
}


static void load_sound_test(void) {
  int palette_offsets[100] = { 16, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 32, 48, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 16 };
  load_menu_sprite_bitmaps("TITLE/BMP/SNDTESTS.CM_", palette_offsets);
  load_extra_sprite_bitmap("HOSHINO3.BMP", 0, 0);
  load_extra_sprite_bitmap("NISIMUR3.BMP", 0, 0);
  load_extra_sprite_bitmap("MIYAKE3.BMP", 0, 0);
  load_extra_sprite_bitmap("SANPEI3.BMP", 0, 0);
  load_extra_sprite_bitmap("YAMA_L3.BMP", 0, 0);
  load_extra_sprite_bitmap("YAMA_R3.BMP", 0, 0);
}


static void unload_sound_test(void) {
  pause_bgm();
  unload_sprite_bitmaps();
}


static void draw_sound_test(void) {
  int i;

  clear_screen();
  lock_screen();
  if (get_sequencenum() > 1) {
    blit_sprites2(get_screen_pixels(), get_sprites2(), get_scanline_padding());
  }
  unlock_screen();
  blit_screen();
}


static int SND_main(void) {
  int ret = 0;

  switch (get_sequencenum()) {
    case 1:
      SND_start();
      break;
    case 2:
      SND_menu();
      break;
    case 3:
      wait2();
      break;
    case 4:
      SND_kakusi();
      break;
    case 999:
      ret = SND_end(9);
      break;
    case 5:
      SND_special_mes();
      break;
    case 6:
      ret = SND_end(18);
      break;
    case 7:
      ret = SND_end(19);
      break;
  }

  update_sequence_timer();

  return ret;
}


static void SND_update_menu(void) {
  if (menukind == 1) {
    update_pcm(2);
  }
  else {
    update_pcm(1);
  }
  if (menukind == 2) {
    update_da(2);
  }
  else {
    update_da(1);
  }
}


static void SND_start(void) {
  int n;

  clear_sprites2();
  for (n = 0; n < 16; ++n) {
    set_sprite2_info(n, SND_sprites[83 + n]);
  }
  for (n = 0; n < 9; ++n) {
    set_sprite2_info(16 + n, SND_sprites[n]);
  }
  menukind = 1;
  SND_update_menu();
  update_pcm_no(tblPCM[0]);
  update_da_no(tblDA[0]);
  pcm_number_index = da_number_index = 0;
  set_sequencenum(2);
}


static void SND_menu(void) {
  unsigned short menukind_old;

  if (swdata1.w & 0x800) {
    menukind_old = menukind;
    menukind = menukind + 1 < 2 ? menukind + 1 : 2;
    if (menukind == menukind_old) return;
    SND_update_menu();
    key_wait(6);
  }
  else if (swdata1.w & 0x400) {
    menukind_old = menukind;
    menukind = menukind - 1 > 1 ? menukind - 1 : 1;
    if (menukind == menukind_old) return;
    SND_update_menu();
    key_wait(6);
  }
  else if (swdata1.w & 0x100) {
    if (menukind == 1) {
      if (pcm_number_index == 0) {
        pcm_number_index = 79;
      }
      else {
        --pcm_number_index;
      }
      update_pcm_no(pcm_number_index);
    }
    else {
      if (da_number_index == 0) {
        da_number_index = 33;
      }
      else {
        --da_number_index;
      }
      update_da_no(tblDA[da_number_index]);
    }
    key_wait(6);
  }
  else if (swdata1.w & 0x200) {
    if (menukind == 1) {
      if (pcm_number_index == 79) {
        pcm_number_index = 0;
      }
      else {
        ++pcm_number_index;
      }
      update_pcm_no(pcm_number_index);
    }
    else {
      if (da_number_index == 33) {
        da_number_index = 0;
      }
      else {
        ++da_number_index;
      }
      update_da_no(tblDA[da_number_index]);
    }
    key_wait(6);
  }
  else if (swdata1.w & 0x4000) {
    if (pcm_number_index == 3 && da_number_index == 1) {
      clear_sprites2();
      mc_sonic_create(0);
      kakusi = 1;
      CDPause(2);
      CDPlay(21);
      set_sequencenum(4);
      return;
    }
    if (pcm_number_index == 12 && da_number_index == 25) {
      clear_sprites2();
      mc_sonic_create(1);
      kakusi = 1;
      CDPause(2);
      CDPlay(24);
      set_sequencenum(4);
      return;
    }
    if (pcm_number_index == 4 && da_number_index == 21) {
      clear_sprites2();
      mc_sonic_create(2);
      kakusi = 1;
      CDPause(2);
      CDPlay(25);
      set_sequencenum(4);
      return;
    }
    if (pcm_number_index == 11 && da_number_index == 9) {
      clear_sprites2();
      mc_sonic_create(3);
      kakusi = 1;
      CDPause(2);
      CDPlay(4);
      set_sequencenum(4);
      return;
    }
    if (pcm_number_index == 7 && da_number_index == 7) {
      CDPause(2);
      set_sprite2(39, 36, 160, 100, 0);
      set_sequencenum(5);
      return;
    }
    if (pcm_number_index == 12 && da_number_index == 11) {
      CDPause(2);
      CDPlay(33);
      clear_sprites2();
      mc_sonic_create(4);
      kakusi = 2;
      set_sequencenum(4);
      return;
    }

    if (menukind == 1) {
      WaveRequest(tblPCM[pcm_number_index]);
    }
    else {
      CDPause(2);
      CDPlay(tblDA[da_number_index]);
    }
    wait_key_off(0);
  }
  else if (swdata1.w & 0x1000) {
    CDPause(2);
    set_sequencenum(999);
  }
}


static int SND_end(int newret) {
  int ret = 0;

  if (get_timercount() == 0) {
    ret = newret;
  }

  return ret;
}


static int mc_sonic_create(short cgno) {
  switch (cgno) {
    case 0:
      memcpy(&lpcolorwk[0], HOSHINOcolor, sizeof(HOSHINOcolor));
      break;
    case 1:
      memcpy(&lpcolorwk[0], NISIMURAcolor, sizeof(NISIMURAcolor));
      break;
    case 2:
      memcpy(&lpcolorwk[0], MIYAKEcolor, sizeof(MIYAKEcolor));
      break;
    case 3:
      memcpy(&lpcolorwk[0], SANPEIcolor, sizeof(SANPEIcolor));
      break;
    case 4:
      memcpy(&lpcolorwk[0], YAMAGU1color, sizeof(YAMAGU1color));
      memcpy(&lpcolorwk[16], YAMAGU2color, sizeof(YAMAGU2color));
      break;
  }

  switch (cgno) {
    case 0:
    case 1:
    case 2:
    case 3:
      set_sprite2(0, 0, 0, 101 + cgno, 0);
      break;
    case 4:
      set_sprite2(0, 0, 0, 101 + cgno, 0);
      set_sprite2(1, 160, 0, 101 + cgno + 1, 0);
      break;
  }

  return 0;
}


static void SND_kakusi(void) {
  if (!(swdata1.w & 0x4000)) {
    kakusi |= 4;
  }
  if (kakusi & 4 && (swdata1.w & 0x4000 || swdata1.w & 0x1000)) {
    if ((kakusi & 3) == 2) {
      set_sequencenum(7);
    }
    if ((kakusi & 3) == 1) {
      set_sequencenum(999);
    }
  }
}


static void SND_special_mes(void) {
  if (!(swdata1.w & 0x4000)) {
    kakusi |= 4;
  }
  if (kakusi & 4 && (swdata1.w & 0x4000 || swdata1.w & 0x1000)) {
    set_sprite2(39, -1, -1, 0, 0);
    kakusi = 0;
    set_sequencenum(6);
  }
}


static unsigned short get_char_sprite_index_color_0(char code) {
  int index;

  if (code == '.') {
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

  if (code == '.') {
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


static void update_pcm(int color) {
  unsigned short(*func)(char) = &get_char_sprite_index_color_0;

  if (color == 1) {
    func = &get_char_sprite_index_color_1;
  }
  set_string_sprites2("PCMNO.", 6, 25, 44, 80, 8, func);
}


static void update_pcm_no(unsigned char number) {
  set_number_sprites2(number, 31, 44 + 7 * 8, 80, 8, &get_char_sprite_index_color_1);
}


static void update_da(int color) {
  unsigned short(*func)(char) = &get_char_sprite_index_color_0;

  if (color == 1) {
    func = &get_char_sprite_index_color_1;
  }
  set_string_sprites2("DANO.", 5, 33, 208, 80, 8, func);
}


static void update_da_no(unsigned char number) {
  set_number_sprites2(number, 38, 208 + 6 * 8, 80, 8, &get_char_sprite_index_color_1);
}
