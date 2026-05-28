#include "savedata.h"
#include <string.h>
#include "constants.h"
#include "graphics/screen.h"
#include "graphics/sprites.h"
#include "graphics/sprites2.h"
#include "input/input.h"
#include "sequence.h"
#include "services.h"
#include "score.h"
#include "GAME/EQU.h"
#include "GAME/TITLE/COMMON/SCORE_DATA_TYPES.h"
#define SPRITE_MENU_ITEM_BASE 4
#define SPRITE_FILE_SELECT_BG 9
#define SPRITE_UNSELECTED_FILE_MARKER_BASE 10
#define SPRITE_SELECTED_FILE_MARKER 16
#define SPRITE_MESSAGE_BASE 17
#define SPRITE_DATAFILE_0_PLAYER_BASE 44
#define SPRITE_DATAFILE_0_ROUND_BASE 56
#define SPRITE_DATAFILE_0_DATE_BASE 63
#define SPRITE_DATAFILE_0_TIME_BASE 74
#define SPRITE_PLAYER_EDIT_CURSOR 308
#define SPRITE_SONIC_CURSOR 309
static void load_savedata(void);
static void unload_savedata(void);
static void draw_savedata(void);
static int SVD_main(void);
static void SVD_start(void);
static void SVD_update_menu(unsigned short menu_kind, unsigned short menu_kind_old);
static void SVD_delete_fileselect(void);
static void SVD_update_fileselect(unsigned short newnumber);
static void SVD_update_selectsonicmark(unsigned short newnumber);
static void SVD_update_fileview(unsigned short filenumber);
static void SVD_update_message(char* msg);
static void SVD_defaultmessage(void);
static unsigned int SVD_chk_savefile(void);
static void SVD_menu(void);
static int SVD_end(void);
static int SVD_check_auto_end(void);
static int SVD_edit(void);
static void SVD_display_savedata(int index);
static void SVD_display_all(void);
static void SVD_read_datafile(void);
static void SVD_write_datafile(void);
static unsigned int SVD_fileselect(int* p_filenumber);
static void SVD_menu_select(void);
static void SVD_menu_copy(void);
static void SVD_menu_rename(void);
static void SVD_menu_delete(void);
static void SVD_menu_exit(void);
static void SVD_move_cursor(int x);
static void SVD_display_cursor(void);
static void SVD_hide_cursor(void);
static void SVD_hide_soniccursor(void);
static void SVD_display_soniccursor(int x, int y);
static void SVD_move_soniccursor(int x, int y);
static void SVD_run_soniccursor(int x, int y);
static void SVD_update_soniccursor(void);
static unsigned short get_char_sprite_index_kind_0(char code);
static unsigned short get_char_sprite_index_kind_1(char code);
static unsigned short get_char_sprite_index_kind_2(char code);
static unsigned short get_char_sprite_index_kind_3(char code);
static int isqrt(int xx);

extern int g_quit;
extern score_data g_current_score_data;

sprite_info SVD_sprites[209] = {
  {  16,  48,   1, 0 }, /* SELECT */
  {  16,  48,   2, 0 }, /* SELECT (selected) */
  {  16,  72,   3, 0 }, /* COPY */
  {  16,  72,   4, 0 }, /* COPY (selected) */
  {  16,  96,   5, 0 }, /* RENAME */
  {  16,  96,   6, 0 }, /* RENAME (selected) */
  {  16, 120,   7, 0 }, /* DELETE */
  {  16, 120,   8, 0 }, /* DELETE (selected) */
  {  16, 144,   9, 0 }, /* EXIT */
  {  16, 144,  10, 0 }, /* EXIT (selected) */
  {  96,  32,  11, 0 }, /* selected file marker */
  {   0,   0,  12, 0 }, /* 0 */
  {   0,   0,  13, 0 }, /* 1 */
  {   0,   0,  14, 0 }, /* 2 */
  {   0,   0,  15, 0 }, /* 3 */
  {   0,   0,  16, 0 }, /* 4 */
  {   0,   0,  17, 0 }, /* 5 */
  {   0,   0,  18, 0 }, /* 6 */
  {   0,   0,  19, 0 }, /* 7 */
  {   0,   0,  20, 0 }, /* 8 */
  {   0,   0,  21, 0 }, /* 9 */
  {   0,   0,  22, 0 }, /* A */
  {   0,   0,  23, 0 }, /* B */
  {   0,   0,  24, 0 }, /* C */
  {   0,   0,  25, 0 }, /* D */
  {   0,   0,  26, 0 }, /* E */
  {   0,   0,  27, 0 }, /* F */
  {   0,   0,  28, 0 }, /* G */
  {   0,   0,  29, 0 }, /* H */
  {   0,   0,  30, 0 }, /* I */
  {   0,   0,  31, 0 }, /* J */
  {   0,   0,  32, 0 }, /* K */
  {   0,   0,  33, 0 }, /* L */
  {   0,   0,  34, 0 }, /* M */
  {   0,   0,  35, 0 }, /* N */
  {   0,   0,  36, 0 }, /* O */
  {   0,   0,  37, 0 }, /* P */
  {   0,   0,  38, 0 }, /* Q */
  {   0,   0,  39, 0 }, /* R */
  {   0,   0,  40, 0 }, /* S */
  {   0,   0,  41, 0 }, /* T */
  {   0,   0,  42, 0 }, /* U */
  {   0,   0,  43, 0 }, /* V */
  {   0,   0,  44, 0 }, /* W */
  {   0,   0,  45, 0 }, /* X */
  {   0,   0,  46, 0 }, /* Y */
  {   0,   0,  47, 0 }, /* Z */
  {   0,   0,  48, 0 }, /* 0 */
  {   0,   0,  49, 0 }, /* 1 */
  {   0,   0,  50, 0 }, /* 2 */
  {   0,   0,  51, 0 }, /* 3 */
  {   0,   0,  52, 0 }, /* 4 */
  {   0,   0,  53, 0 }, /* 5 */
  {   0,   0,  54, 0 }, /* 6 */
  {   0,   0,  55, 0 }, /* 7 */
  {   0,   0,  56, 0 }, /* 8 */
  {   0,   0,  57, 0 }, /* 9 */
  {   0,   0,  58, 0 }, /* A */
  {   0,   0,  59, 0 }, /* B */
  {   0,   0,  60, 0 }, /* C */
  {   0,   0,  61, 0 }, /* D */
  {   0,   0,  62, 0 }, /* E */
  {   0,   0,  63, 0 }, /* F */
  {   0,   0,  64, 0 }, /* G */
  {   0,   0,  65, 0 }, /* H */
  {   0,   0,  66, 0 }, /* I */
  {   0,   0,  67, 0 }, /* J */
  {   0,   0,  68, 0 }, /* K */
  {   0,   0,  69, 0 }, /* L */
  {   0,   0,  70, 0 }, /* M */
  {   0,   0,  71, 0 }, /* N */
  {   0,   0,  72, 0 }, /* O */
  {   0,   0,  73, 0 }, /* P */
  {   0,   0,  74, 0 }, /* Q */
  {   0,   0,  75, 0 }, /* R */
  {   0,   0,  76, 0 }, /* S */
  {   0,   0,  77, 0 }, /* T */
  {   0,   0,  78, 0 }, /* U */
  {   0,   0,  79, 0 }, /* V */
  {   0,   0,  80, 0 }, /* W */
  {   0,   0,  81, 0 }, /* X */
  {   0,   0,  82, 0 }, /* Y */
  {   0,   0,  83, 0 }, /* Z */
  {   0,   0,  84, 0 }, /* 0 */
  {   0,   0,  85, 0 }, /* 1 */
  {   0,   0,  86, 0 }, /* 2 */
  {   0,   0,  87, 0 }, /* 3 */
  {   0,   0,  88, 0 }, /* 4 */
  {   0,   0,  89, 0 }, /* 5 */
  {   0,   0,  90, 0 }, /* 6 */
  {   0,   0,  91, 0 }, /* 7 */
  {   0,   0,  92, 0 }, /* 8 */
  {   0,   0,  93, 0 }, /* 9 */
  {   0,   0,  94, 0 }, /* A */
  {   0,   0,  95, 0 }, /* B */
  {   0,   0,  96, 0 }, /* C */
  {   0,   0,  97, 0 }, /* D */
  {   0,   0,  98, 0 }, /* E */
  {   0,   0,  99, 0 }, /* F */
  {   0,   0, 100, 0 }, /* G */
  {   0,   0, 101, 0 }, /* H */
  {   0,   0, 102, 0 }, /* I */
  {   0,   0, 103, 0 }, /* J */
  {   0,   0, 104, 0 }, /* K */
  {   0,   0, 105, 0 }, /* L */
  {   0,   0, 106, 0 }, /* M */
  {   0,   0, 107, 0 }, /* N */
  {   0,   0, 108, 0 }, /* O */
  {   0,   0, 109, 0 }, /* P */
  {   0,   0, 110, 0 }, /* Q */
  {   0,   0, 111, 0 }, /* R */
  {   0,   0, 112, 0 }, /* S */
  {   0,   0, 113, 0 }, /* T */
  {   0,   0, 114, 0 }, /* U */
  {   0,   0, 115, 0 }, /* V */
  {   0,   0, 116, 0 }, /* W */
  {   0,   0, 117, 0 }, /* X */
  {   0,   0, 118, 0 }, /* Y */
  {   0,   0, 119, 0 }, /* Z */
  {   0,   0, 120, 0 }, /* 0 */
  {   0,   0, 121, 0 }, /* 1 */
  {   0,   0, 122, 0 }, /* 2 */
  {   0,   0, 123, 0 }, /* 3 */
  {   0,   0, 124, 0 }, /* 4 */
  {   0,   0, 125, 0 }, /* 5 */
  {   0,   0, 126, 0 }, /* 6 */
  {   0,   0, 127, 0 }, /* 7 */
  {   0,   0, 128, 0 }, /* 8 */
  {   0,   0, 129, 0 }, /* 9 */
  {   0,   0, 130, 0 }, /* A */
  {   0,   0, 131, 0 }, /* B */
  {   0,   0, 132, 0 }, /* C */
  {   0,   0, 133, 0 }, /* D */
  {   0,   0, 134, 0 }, /* E */
  {   0,   0, 135, 0 }, /* F */
  {   0,   0, 136, 0 }, /* G */
  {   0,   0, 137, 0 }, /* H */
  {   0,   0, 138, 0 }, /* I */
  {   0,   0, 139, 0 }, /* J */
  {   0,   0, 140, 0 }, /* K */
  {   0,   0, 141, 0 }, /* L */
  {   0,   0, 142, 0 }, /* M */
  {   0,   0, 143, 0 }, /* N */
  {   0,   0, 144, 0 }, /* O */
  {   0,   0, 145, 0 }, /* P */
  {   0,   0, 146, 0 }, /* Q */
  {   0,   0, 147, 0 }, /* R */
  {   0,   0, 148, 0 }, /* S */
  {   0,   0, 149, 0 }, /* T */
  {   0,   0, 150, 0 }, /* U */
  {   0,   0, 151, 0 }, /* V */
  {   0,   0, 152, 0 }, /* W */
  {   0,   0, 153, 0 }, /* X */
  {   0,   0, 154, 0 }, /* Y */
  {   0,   0, 155, 0 }, /* Z */
  {   0,   0, 156, 0 }, /* ? */
  {   0,   0, 157, 0 }, /* ? */
  {   0,   0, 158, 0 }, /* ? */
  {   0,   0, 159, 0 }, /* ? */
  {   0,   0, 160, 0 }, /* / */
  {   0,   0, 161, 0 }, /* / */
  {   0,   0, 162, 0 }, /* / */
  {   0,   0, 163, 0 }, /* / */
  {   0,   0, 164, 0 }, /* . */
  {   0,   0, 165, 0 }, /* . */
  {   0,   0, 166, 0 }, /* . */
  {   0,   0, 167, 0 }, /* . */
  {   0,   0, 168, 0 }, /* - */
  {   0,   0, 169, 0 }, /* - */
  {   0,   0, 170, 0 }, /* - */
  {   0,   0, 171, 0 }, /* - */
  {   0,   0, 172, 0 }, /* , */
  {   0,   0, 173, 0 }, /* , */
  {   0,   0, 174, 0 }, /* , */
  {   0,   0, 175, 0 }, /* , */
  {   0,   0, 176, 0 }, /* ) */
  {   0,   0, 177, 0 }, /* ) */
  {   0,   0, 178, 0 }, /* ) */
  {   0,   0, 179, 0 }, /* ) */
  {   0,   0, 180, 0 }, /* ( */
  {   0,   0, 181, 0 }, /* ( */
  {   0,   0, 182, 0 }, /* ( */
  {   0,   0, 183, 0 }, /* ( */
  {   0,   0, 184, 0 }, /* : */
  {   0,   0, 185, 0 }, /* : */
  {   0,   0, 186, 0 }, /* : */
  {   0,   0, 187, 0 }, /* : */
  {   0,   0, 188, 0 }, /* : */
  {   0,   0, 189, 0 }, /* : */
  {   0,   0, 190, 0 }, /* : */
  {   0,   0, 191, 0 }, /* : */
  {   0,   0, 192, 0 }, /* file cursor */
  { 128,  32, 193, 0 }, /* file select background */
  {  96,  32, 194, 0 }, /* unselected file marker */
  {  96,  64, 195, 0 }, /* unselected file marker */
  {  96,  96, 196, 0 }, /* unselected file marker */
  {  96, 128, 197, 0 }, /* unselected file marker */
  {  96, 160, 198, 0 }, /* unselected file marker */
  {  96, 192, 199, 0 }, /* unselected file marker */
  {   0, 112, 200, 0 }, /* background (lower left) */
  { 160, 112, 201, 0 }, /* background (lower right) */
  {   0,   0, 202, 0 }, /* background (top left) */
  { 160,   0, 203, 0 }, /* background (top right) */
  {   0,   0, 204, 0 }, /* Sonic stopped */
  {   0,   0, 205, 0 }, /* Sonic stopped */
  {   0,   0, 206, 0 }, /* Sonic stopped */
  {   0,   0, 207, 0 }, /* Sonic running */
  {   0,   0, 208, 0 }, /* Sonic running */
  {   0,   0, 209, 0 } /* Sonic running */
};
static PALETTEENTRY tblPal1[16] = {
  { 240, 240, 240, 1 }, { 224, 224, 224, 1 }, { 224, 160,   0, 1 }, { 192,   0,   0, 1 },
  { 160, 192, 224, 1 }, { 160, 160, 224, 1 }, { 160,  96,   0, 1 }, { 128, 128, 224, 1 },
  { 128, 128, 192, 1 }, {  96,  96, 224, 1 }, {  96,  96, 160, 1 }, {  96,  32,   0, 1 },
  {  96,   0,   0, 1 }, {  64,  64, 224, 1 }, {  64,  64, 128, 1 }, {  32,   0,   0, 1 }
};
static PALETTEENTRY tblPal2[16] = {
  {  96,  96, 160, 1 }, { 160, 160, 224, 1 }, {  64,  64, 128, 1 }, {   0,   0, 128, 1 },
  {   0, 224,   0, 1 }, { 224, 224, 224, 1 }, {  96,  96, 160, 1 }, { 128, 128, 192, 1 },
  { 160, 192, 224, 1 }, { 128,  96, 192, 1 }, {   0,  96,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static PALETTEENTRY tblPal3[16] = {
  {   0,   0,   0, 1 }, {  32,  32,  32, 1 }, {  64,  64,  64, 1 }, { 128, 128, 128, 1 },
  {   0,   0,   0, 1 }, { 192, 192, 192, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 },
  { 160, 160, 160, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static PALETTEENTRY tblPal4[16] = {
  {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, { 224, 160, 128, 1 }, { 160,  96,  64, 1 },
  { 128, 128, 224, 1 }, { 128, 128, 128, 1 }, { 128,   0,   0, 1 }, {  96,  96, 224, 1 },
  {   0,   0,   0, 1 }, {  64,  64, 224, 1 }, {  64,  64,  64, 1 }, {  32,  32, 192, 1 },
  {   0, 224,   0, 1 }, {  64,   0,   0, 1 }, { 160, 160, 160, 1 }, { 224,   0,   0, 1 }
};
typedef struct {
  char code;
  int yello816;
  int white88;
  int yello88;
  int whitex16;
}
mark_info;
mark_info markTable[10] = {
  {  '?', 155, 156, 157, 158 },
  {  '/', 159, 160, 161, 162 },
  {  '.', 163, 164, 165, 166 },
  {  '-', 167, 168, 169, 170 },
  {  ',', 171, 172, 173, 174 },
  {  ')', 175, 176, 177, 178 },
  {  '(', 179, 180, 181, 182 },
  { '\'', 183, 184, 185, 186 },
  {  '"', 187, 188, 189, 190 }
};
static unsigned int g_defaultmsg_flag;
static unsigned short g_menu_kind;
static int g_filenumber;
static unsigned int g_editmode;
static char g_editbuf[12];
static score_data g_savedata[6];
static unsigned int g_menu_chosen;
static unsigned int g_file_chosen;
static int g_select_filenumber;
static int g_src_filenumber;
static unsigned int g_destfile_chosen;
static int cursor_posi_x;
static int soniccursor_index;
static int soniccursor_mode;
static int soniccursor_posi_x;
static int soniccursor_posi_y;
static int soniccursor_posi_target_x;
static int soniccursor_posi_target_y;
static int_union soniccursor_posi_old_x;
static int_union soniccursor_posi_old_y;
static int soniccursor_posi_inc_x_fraction;
static int soniccursor_posi_inc_y_fraction;
static int soniccursor_timercount_start;
static int SONICMOVEM_MAG = 4;


void savedata(void) {
  load_savedata();
  clear_palette();
  clear_sprites2();
  g_defaultmsg_flag = 0;
  g_menu_kind = 0;
  g_filenumber = 0;
  g_editmode = 0;
  g_menu_chosen = 0;
  g_file_chosen = 0;
  g_select_filenumber = 0;
  g_src_filenumber = 0;
  g_destfile_chosen = 0;
  cursor_posi_x = 0;
  soniccursor_index = 0;
  soniccursor_mode = 0;
  soniccursor_posi_x = 0;
  soniccursor_posi_y = 0;
  soniccursor_posi_target_x = 0;
  soniccursor_posi_target_y = 0;
  soniccursor_posi_old_x.l = 0;
  soniccursor_posi_old_y.l = 0;
  soniccursor_posi_inc_x_fraction = 0;
  soniccursor_posi_inc_y_fraction = 0;
  soniccursor_timercount_start = 0;
  memcpy(&lpcolorwk[0], tblPal1, sizeof(tblPal1));
  memcpy(&lpcolorwk[16], tblPal2, sizeof(tblPal2));
  memcpy(&lpcolorwk[32], tblPal3, sizeof(tblPal3));
  memcpy(&lpcolorwk[48], tblPal4, sizeof(tblPal4));
  init_sequence();
  start_timer();

  while (g_quit == 0) {
    int next;

    poll_controller();
    next = SVD_main();
    if (next != 0) break;
    draw_savedata();
  }

  unload_savedata();
}


static void load_savedata(void) {
  int palette_offsets[209] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 16, 32, 64, 64, 64, 64, 64, 64, 16, 16, 16, 16, 64, 64, 64, 64, 64, 64 };
  load_menu_sprite_bitmaps("TITLE/BMP/SAVEDATS.CM_", palette_offsets);
}


static void unload_savedata(void) {
  unload_sprite_bitmaps();
}


static void draw_savedata(void) {
  int i;

  clear_screen();
  lock_screen();
  if (get_sequencenum() > 1) {
    blit_sprites2(get_screen_pixels(), get_sprites2(), get_scanline_padding());
  }
  unlock_screen();
  blit_screen();
}


static int SVD_main(void) {
  int ret = 0;

  switch (get_sequencenum()) {
    case 1:
      SVD_start();
      break;
    case 2:
      SVD_menu();
      break;
    case 3:
      if (wait2() != 0 && g_defaultmsg_flag != 0) {
        SVD_defaultmessage();
        g_defaultmsg_flag = 0;
      }
      break;
    case 999:
      ret = SVD_end();
      break;
  }

  update_sequence_timer();

  SVD_update_soniccursor();
  if (ret == 0) {
    ret = SVD_check_auto_end();
  }
  return ret;
}


static void SVD_start(void) {
  int n;

  clear_sprites2();
  for (n = 0; n < 4; ++n) {
    set_sprite2_info(n, SVD_sprites[199 + n]);
  }
  SVD_read_datafile();
  SVD_display_all();
  g_menu_kind = 1;
  set_sequencenum(2);
  SVD_display_soniccursor(SVD_sprites[0].x + 48, SVD_sprites[0].y - 8);
}


static void SVD_update_menu(unsigned short menu_kind, unsigned short menu_kind_old) {
  if (menu_kind == menu_kind_old) return;

  set_sprite2_info(SPRITE_MENU_ITEM_BASE + menu_kind_old - 1, SVD_sprites[(menu_kind_old - 1) * 2]);
  set_sprite2_info(SPRITE_MENU_ITEM_BASE + menu_kind - 1, SVD_sprites[(menu_kind - 1) * 2 + 1]);
}


static void SVD_delete_fileselect(void) {
  set_sprite2(SPRITE_FILE_SELECT_BG, -1, -1, 0, 0);
}


static void SVD_update_fileselect(unsigned short newnumber) {
  set_sprite2(SPRITE_FILE_SELECT_BG, SVD_sprites[192].x, SVD_sprites[192].y + newnumber * 32, SVD_sprites[192].index, 0);
}


static void SVD_update_selectsonicmark(unsigned short newnumber) {
  if (g_savedata[newnumber].saved == 0) {
    set_sprite2(SPRITE_SELECTED_FILE_MARKER, -1, -1, 0, 0);
  }
  else {
    set_sprite2(SPRITE_SELECTED_FILE_MARKER, SVD_sprites[10].x, SVD_sprites[10].y + newnumber * 32, SVD_sprites[10].index, 0);
  }
}


static void SVD_update_fileview(unsigned short filenumber) {
  SVD_display_savedata(filenumber);
}


static void SVD_update_message(char* msg) {
  set_string_sprites2(msg, 27, SPRITE_MESSAGE_BASE, 96, 10, 8, &get_char_sprite_index_kind_2);
}


static void SVD_defaultmessage(void) {
  SVD_update_message("SONIC CD DATA-FILES");
}


static unsigned int SVD_chk_savefile(void) {
  int i;

  for (i = 0; i < 6; ++i) {
    if (g_savedata[i].saved != 0) {
      return 1;
    }
  }

  return 0;
}


static void SVD_menu(void) {
  unsigned short menu_kind_old;

  if (g_menu_chosen == 0) {
    if (swdata1.w & 0x300) {
      menu_kind_old = g_menu_kind;
      if (swdata1.w & 0x200) {
        g_menu_kind = g_menu_kind + 1 < 5 ? g_menu_kind + 1 : 5;
      }
      else if (swdata1.w & 0x100) {
        g_menu_kind = g_menu_kind - 1 > 1 ? g_menu_kind - 1 : 1;
      }
      if (g_menu_kind == menu_kind_old) return;
      WaveRequest(9);
      SVD_update_menu(g_menu_kind, menu_kind_old);
      SVD_run_soniccursor(SVD_sprites[(g_menu_kind - 1) * 2].x + 48, SVD_sprites[(g_menu_kind - 1) * 2].y - 8);
      key_wait(6);
    }
    else if (swdata1.w & 0x4000) {
      if (SVD_chk_savefile() == 0) {
        if (g_menu_kind != 5) {
          WaveRequest(30);
          key_wait(6);
          return;
        }
      }
      g_menu_chosen = 1;
      g_file_chosen = 0;
      g_destfile_chosen = 0;
      g_filenumber = g_select_filenumber;
      if (g_menu_kind != 5) {
        int x = SVD_sprites[193 + g_filenumber].x - 16;
        int y = SVD_sprites[193 + g_filenumber].y;

        WaveRequest(26);

        switch (g_menu_kind) {
          case 1:
            SVD_update_message("SELECT FILE TO USE IN GAME.");
            break;
          case 2:
            SVD_update_message("SELECT FILE TO COPY FROM.");
            break;
          case 3:
            SVD_update_message("SELECT FILE TO RENAME.");
            break;
          case 4:
            SVD_update_message("SELECT FILE TO DELETE.");
            break;
        }

        SVD_update_fileselect(g_select_filenumber);
        SVD_run_soniccursor(x, y);
        wait_key_off(0);
      }
    }
  }
  else {
    switch (g_menu_kind) {
      case 1:
        SVD_menu_select();
        break;
      case 2:
        SVD_menu_copy();
        break;
      case 3:
        SVD_menu_rename();
        break;
      case 4:
        SVD_menu_delete();
        break;
      case 5:
        SVD_menu_exit();
        break;
    }
  }
}


static int SVD_end(void) {
  int ret = 0;

  if (get_timercount() == 0) {
    SVD_write_datafile();
    ret = 9;
  }

  return ret;
}


static int SVD_check_auto_end(void) {
  static int inputkeytime;
  int ret = 0;

  if (swdata1.w || swdata2.w) {
    inputkeytime = get_timercount();
  }
  if (get_timercount() - inputkeytime > 36000) {
    ret = 4;
  }
  return ret;
}


static int SVD_edit(void) {
  int ret = 0;
  int posi;

  g_editmode = 1;
  if (swdata1.w & 0xC00) {
    WaveRequest(54);
    posi = cursor_posi_x;
    if (swdata1.w & 0x400) {
      posi = posi - 1 > 0 ? posi - 1 : 0;
    }
    else if (swdata1.w & 0x800) {
      posi = posi + 1 < 9 ? posi + 1 : 9;
    }
    SVD_display_cursor();
    SVD_move_cursor(posi);
    wait(2);
  }
  else if (swdata1.w & 0x300) {
    WaveRequest(54);
    posi = cursor_posi_x;
    if (swdata1.w & 0x200) {
      switch (g_editbuf[posi]) {
        case 32: g_editbuf[posi] = 90; break;
        case 45: g_editbuf[posi] = 32; break;
        case 48: g_editbuf[posi] = 45; break;
        case 65: g_editbuf[posi] = 57; break;
        default: --g_editbuf[posi]; break;
      }
    }
    else if (swdata1.w & 0x100) {
      switch (g_editbuf[posi]) {
        case 32: g_editbuf[posi] = 45; break;
        case 45: g_editbuf[posi] = 48; break;
        case 57: g_editbuf[posi] = 65; break;
        case 90: g_editbuf[posi] = 32; break;
        default: ++g_editbuf[posi]; break;
      }
    }
    set_sprite2(SPRITE_DATAFILE_0_PLAYER_BASE + g_filenumber * 44 + posi, 128 + posi * 8, 32 + g_filenumber * 32, get_char_sprite_index_kind_0(g_editbuf[posi]), 0);
    wait(2);
  }
  else if (swdata1.w & 0x5000) {
    g_editmode = 0;
    wait_key_off(0);
    if (swdata1.w & 0x4000) {
      ret = 1;
    }
    else if (swdata1.w & 0x1000) {
      ret = -1;
    }
  }

  return ret;
}


static void SVD_display_savedata(int index) {
  char str[256];
  int round;

  if (g_savedata[index].saved != 0) {
    set_string_sprites2(g_savedata[index].player, 12, SPRITE_DATAFILE_0_PLAYER_BASE + index * 44, 128, 32 + index * 32, 8, &get_char_sprite_index_kind_0);
    sprintf(str, "%4u/%2u/%2u", g_savedata[index].year, g_savedata[index].month, g_savedata[index].date);
    set_string_sprites2(str, 11, SPRITE_DATAFILE_0_DATE_BASE + index * 44, 212, 36 + index * 32, 8, &get_char_sprite_index_kind_0);
    round = g_savedata[index].roundNo + 1;
    if (round > 7) {
      round = 7;
    }
    sprintf(str, "ROUND-%1d", round);
    set_string_sprites2(str, 7, SPRITE_DATAFILE_0_ROUND_BASE + index * 44, 144, 42 + index * 32, 8, &get_char_sprite_index_kind_2);
    sprintf(str, "%02u\"%02u\"%02u", g_savedata[index].hour, g_savedata[index].min, g_savedata[index].sec);
    set_string_sprites2(str, 14, SPRITE_DATAFILE_0_TIME_BASE + index * 44, 228, 46 + index * 32, 8, &get_char_sprite_index_kind_0);
    set_sprite2_info(SPRITE_UNSELECTED_FILE_MARKER_BASE + index, SVD_sprites[193 + index]);
  }
  else {
    set_string_sprites2("NO DATA-FILE", 44, SPRITE_DATAFILE_0_PLAYER_BASE + index * 44, 160, 40 + index * 32, 8, &get_char_sprite_index_kind_0);
    set_sprite2(SPRITE_UNSELECTED_FILE_MARKER_BASE + index, -1, -1, 0, 0);
  }
}


static void SVD_display_all(void) {
  int i;

  SVD_defaultmessage();
  set_sprite2_info(SPRITE_MENU_ITEM_BASE, SVD_sprites[1]);
  set_sprite2_info(SPRITE_MENU_ITEM_BASE + 1, SVD_sprites[2]);
  set_sprite2_info(SPRITE_MENU_ITEM_BASE + 2, SVD_sprites[4]);
  set_sprite2_info(SPRITE_MENU_ITEM_BASE + 3, SVD_sprites[6]);
  set_sprite2_info(SPRITE_MENU_ITEM_BASE + 4, SVD_sprites[8]);

  for (i = 0; i < 6; ++i) {
    SVD_display_savedata(i);
  }

  SVD_update_selectsonicmark(g_select_filenumber);
}


static void SVD_read_datafile(void) {
  int n;
  FILE* h_file = open_score_data(0);
  int index = read_score_index(h_file);

  if (index < 0 || index > 5) return;
  g_select_filenumber = index;
  close_score_data(h_file);

  for (n = 0; n < 6; ++n) {
    ReadScore(n, (char*)&g_savedata[n], 0);
  }
}


static void SVD_write_datafile(void) {
  int n;
  FILE* h_file = open_score_data(1);

  write_score_index(g_select_filenumber, h_file);
  close_score_data(h_file);

  for (n = 0; n < 6; ++n) {
    write_score_data(n, &g_savedata[n], 0);
  }

  memcpy(&g_current_score_data, &g_savedata[g_select_filenumber], sizeof(g_savedata[g_select_filenumber]));
}


static unsigned int SVD_fileselect(int* p_filenumber) {
  int old_number;

  if (swdata1.w & 0x300) {
    old_number = *p_filenumber;
    if (swdata1.w & 0x200) {
      *p_filenumber = *p_filenumber + 1 < 5 ? *p_filenumber + 1 : 5;
    }
    else if (swdata1.w & 0x100) {
      *p_filenumber = *p_filenumber - 1 > 0 ? *p_filenumber - 1 : 0;
    }
    if (old_number != *p_filenumber) {
      WaveRequest(9);
      SVD_update_fileselect(*p_filenumber);
      SVD_run_soniccursor(SVD_sprites[193 + *p_filenumber].x - 16, SVD_sprites[193 + *p_filenumber].y);
      key_wait(6);
    }
  }
  else if (swdata1.w & 0x4000) {
    return 1;
  }
  else if (swdata1.w & 0x1000) {
    WaveRequest(25);
    g_menu_chosen = 0;
    SVD_delete_fileselect();
    SVD_defaultmessage();
    SVD_run_soniccursor(SVD_sprites[(g_menu_kind - 1) * 2].x + 48, SVD_sprites[(g_menu_kind - 1) * 2].y - 8);
  }
  return 0;
}


static void SVD_menu_select(void) {
  static unsigned int yesnodialog_on;

  if (g_file_chosen == 0) {
    g_file_chosen = SVD_fileselect(&g_filenumber);
    yesnodialog_on = 0;
    if (g_file_chosen == 0) return;
    if (g_savedata[g_filenumber].saved != 0) {
      SVD_update_message("CONTINUE WITH THIS FILE?");
      yesnodialog_on = 1;
      wait_key_off(0);
      WaveRequest(26);
      return;
    }
    g_file_chosen = 0;
    wait_key_off(0);
    WaveRequest(30);
  }
  else if (yesnodialog_on != 0) {
    if (swdata1.w & 0x4000) {
      WaveRequest(5);
      g_select_filenumber = g_filenumber;
      g_menu_chosen = g_file_chosen = 0;
      SVD_defaultmessage();
      SVD_update_selectsonicmark(g_select_filenumber);
      SVD_delete_fileselect();
      SVD_run_soniccursor(SVD_sprites[0].x - 48, SVD_sprites[0].y - 8);
      wait_key_off(0);
    }
    else if (swdata1.w & 0x1000) {
      WaveRequest(25);
      g_file_chosen = 0;
      SVD_update_message("SELECT FILE TO USE IN GAME.");
      wait_key_off(0);
    }
  }
}


static void SVD_menu_copy(void) {
  static unsigned int yesnodialog_on;

  if (g_file_chosen == 0) {
    g_file_chosen = SVD_fileselect(&g_filenumber);
    g_destfile_chosen = 0;
    yesnodialog_on = 0;
    if (g_file_chosen == 0) return;
    if (g_savedata[g_filenumber].saved != 0) {
      WaveRequest(26);
      SVD_update_message("SELECT FILE TO COPY TO.");
      g_src_filenumber = g_filenumber;
    }
    else {
      WaveRequest(30);
      g_file_chosen = 0;
    }
    wait_key_off(0);
  }
  else if (g_destfile_chosen == 0) {
    g_destfile_chosen = SVD_fileselect(&g_filenumber);
    if (g_destfile_chosen == 0) return;
    if (g_filenumber == g_src_filenumber) {
      WaveRequest(30);
      g_destfile_chosen = 0;
    }
    else {
      WaveRequest(26);
      if (g_savedata[g_filenumber].saved != 0) {
        SVD_update_message("OK TO OVERWRITE FILE?");
      }
      else {
        SVD_update_message("OK TO COPY?");
      }
      yesnodialog_on = 1;
      wait_key_off(0);
    }
  }
  else if (yesnodialog_on != 0) {
    if (swdata1.w & 0x4000) {
      WaveRequest(5);
      memcpy(&g_savedata[g_filenumber], &g_savedata[g_src_filenumber], sizeof(g_savedata[g_src_filenumber]));
      g_menu_chosen = 0;
      SVD_update_fileview(g_filenumber);
      SVD_update_message("COPY COMPLETED.");
      SVD_delete_fileselect();
      SVD_run_soniccursor(SVD_sprites[2].x - 48, SVD_sprites[2].y - 8);
      wait_key_off(60);
      g_defaultmsg_flag = 1;
    }
    else if (swdata1.w & 0x1000) {
      WaveRequest(25);
      g_file_chosen = 0;
      SVD_update_message("SELECT FILE TO COPY FROM.");
      wait_key_off(0);
    }
  }
}


static void SVD_menu_rename(void) {
  int ret;
  static unsigned int editmode;
  static unsigned int cursor_on;

  if (g_file_chosen == 0) {
    g_file_chosen = SVD_fileselect(&g_filenumber);
    editmode = 0;
    if (g_file_chosen == 0) return;
    if (g_savedata[g_filenumber].saved != 0) {
      WaveRequest(26);
      editmode = 1;
      memcpy(g_editbuf, g_savedata[g_filenumber].player, sizeof(((score_data*)0)->player));
      SVD_display_cursor();
      SVD_move_cursor(0);
    }
    else {
      WaveRequest(30);
      g_file_chosen = 0;
    }
    wait_key_off(0);
  }
  else if (editmode != 0) {
    if (get_timercount() % 10 == 0) {
      cursor_on = cursor_on == 0;
      if (cursor_on != 0) {
        SVD_display_cursor();
      }
      else {
        SVD_hide_cursor();
      }
    }
    ret = SVD_edit();
    if (ret == 1 || ret == -1) {
      WaveRequest(5);
      memcpy(g_savedata[g_filenumber].player, g_editbuf, sizeof(((score_data*)0)->player));
      g_menu_chosen = g_file_chosen = editmode = 0;
      SVD_defaultmessage();
      SVD_delete_fileselect();
      SVD_hide_cursor();
      SVD_run_soniccursor(SVD_sprites[4].x + 48, SVD_sprites[4].y - 8);
    }
  }
}


static void SVD_menu_delete(void) {
  int i;
  static unsigned int yesnodialog_on;

  if (g_file_chosen == 0) {
    g_file_chosen = SVD_fileselect(&g_filenumber);
    yesnodialog_on = 0;
    if (g_file_chosen == 0) return;
    if (g_savedata[g_filenumber].saved != 0) {
      WaveRequest(26);
      SVD_update_message("OK TO DELETE?");
      yesnodialog_on = 1;
    }
    else {
      WaveRequest(30);
      g_file_chosen = 0;
    }
    wait_key_off(0);
  }
  else if (yesnodialog_on != 0) {
    if (swdata1.w & 0x4000) {
      WaveRequest(5);
      memset(&g_savedata[g_filenumber], 0, sizeof(g_savedata[g_filenumber]));
      g_menu_chosen = 0;
      if (g_select_filenumber == g_filenumber) {
        for (i = 0; i < 6; ++i) {
          if (g_savedata[i].saved != 0) break;
        }
        if (i == 6) {
          g_select_filenumber = 0;
        }
        else {
          g_select_filenumber = i;
        }
        SVD_update_selectsonicmark(g_select_filenumber);
      }
      SVD_update_fileview(g_filenumber);
      SVD_update_message("FILE DELETED.");
      SVD_delete_fileselect();
      SVD_run_soniccursor(SVD_sprites[6].x + 48, SVD_sprites[6].y - 8);
      wait_key_off(60);
      g_defaultmsg_flag = 1;
    }
    else if (swdata1.w & 0x1000) {
      WaveRequest(25);
      g_file_chosen = 0;
      SVD_update_message("SELECT FILE TO DELETE.");
      wait_key_off(0);
    }
  }
}


static void SVD_menu_exit(void) {
  set_sequencenum(999);
}


static void SVD_move_cursor(int x) {
  POINT point;

  cursor_posi_x = x;
  set_sprite2(SPRITE_PLAYER_EDIT_CURSOR, 128 + 8 * x, 32 + g_filenumber * 32, SVD_sprites[191].index, 0);
}


static void SVD_display_cursor(void) {
  SVD_move_cursor(cursor_posi_x);
}


static void SVD_hide_cursor(void) {
  set_sprite2(SPRITE_PLAYER_EDIT_CURSOR, -1, -1, 0, 0);
}


static void SVD_hide_soniccursor(void) {
  set_sprite2(SPRITE_SONIC_CURSOR, -1, -1, 0, -1);
}


static void SVD_display_soniccursor(int x, int y) {
  soniccursor_index = 203;
  soniccursor_posi_x = x;
  soniccursor_posi_y = y;
  set_sprite2(SPRITE_SONIC_CURSOR, x, y, SVD_sprites[soniccursor_index].index, (g_menu_chosen == 0 ? HFLIP : NOFLIP));
  soniccursor_mode = 1;
  soniccursor_timercount_start = get_timercount();
}


static void SVD_move_soniccursor(int x, int y) {
  SVD_hide_soniccursor();

  switch (soniccursor_index) {
    case 203:
    case 204:
    case 205:
      soniccursor_index = 206;
      break;
    case 208:
      soniccursor_index = 206;
      break;
    default:
      ++soniccursor_index;
      break;
  }

  soniccursor_posi_x = x;
  soniccursor_posi_y = y;
  set_sprite2(SPRITE_SONIC_CURSOR, x, y, SVD_sprites[soniccursor_index].index, (soniccursor_posi_inc_x_fraction < 0 || g_menu_chosen == 0 ? HFLIP : NOFLIP));
}


static void SVD_run_soniccursor(int x, int y) {
  int_union sx, sy;

  soniccursor_posi_target_x = x;
  soniccursor_posi_target_y = y;
  sx.w.h = soniccursor_posi_target_x - soniccursor_posi_x, sx.w.l = 0;
  sy.w.h = soniccursor_posi_target_y - soniccursor_posi_y, sy.w.l = 0;
  if (sx.w.h == 0) {
    soniccursor_posi_inc_x_fraction = 0;
  }
  else {
    soniccursor_posi_inc_x_fraction = SONICMOVEM_MAG * (sx.l / isqrt((sx.w.h * sx.w.h + sy.w.h * sy.w.h) * 65536));
  }
  if (sy.w.h == 0) {
    soniccursor_posi_inc_y_fraction = 0;
  }
  else {
    soniccursor_posi_inc_y_fraction = SONICMOVEM_MAG * (sy.l / isqrt((sx.w.h * sx.w.h + sy.w.h * sy.w.h) * 65536));
  }
  soniccursor_posi_old_x.w.h = soniccursor_posi_x;
  soniccursor_posi_old_y.w.h = soniccursor_posi_y;
  soniccursor_mode = 2;
}


static void SVD_update_soniccursor(void) {
  if (soniccursor_mode == 1) {
    if (get_timercount() % 20 != 0) return;
    if (get_timercount() - soniccursor_timercount_start <= 60) return;
    SVD_hide_soniccursor();

    switch (soniccursor_index) {
      case 203: soniccursor_index = 204; break;
      case 204: soniccursor_index = 205; break;
      case 205: soniccursor_index = 204; break;
      default: soniccursor_index = 203; break;
    }

    set_sprite2(SPRITE_SONIC_CURSOR, soniccursor_posi_x, soniccursor_posi_y, SVD_sprites[soniccursor_index].index, -1);
  }
  else if (soniccursor_mode == 2) {
    soniccursor_posi_old_x.l += soniccursor_posi_inc_x_fraction * 256;
    soniccursor_posi_old_y.l += soniccursor_posi_inc_y_fraction * 256;
    soniccursor_posi_x = soniccursor_posi_old_x.w.h;
    soniccursor_posi_y = soniccursor_posi_old_y.w.h;

    if ((soniccursor_posi_inc_x_fraction >= 0 && soniccursor_posi_x >= soniccursor_posi_target_x)
        || soniccursor_posi_inc_x_fraction < 0 && soniccursor_posi_x <= soniccursor_posi_target_x) {
      soniccursor_posi_x = soniccursor_posi_target_x;
    }
    if ((soniccursor_posi_inc_y_fraction >= 0 && soniccursor_posi_y >= soniccursor_posi_target_y)
        || soniccursor_posi_inc_y_fraction < 0 && soniccursor_posi_y <= soniccursor_posi_target_y) {
      soniccursor_posi_y = soniccursor_posi_target_y;
    }
    if (soniccursor_posi_x == soniccursor_posi_target_x && soniccursor_posi_y == soniccursor_posi_target_y) {
      SVD_hide_soniccursor();
      SVD_display_soniccursor(soniccursor_posi_x, soniccursor_posi_y);
    }
    else {
      SVD_move_soniccursor(soniccursor_posi_x, soniccursor_posi_y);
    }
  }
}


static int get_markfont_index(char code, int kind) {
  int n = 0;

  while (markTable[n].code) {
    if (code == markTable[n].code) {
      switch (kind) {
        case 0:
          return markTable[n].white88;
        case 1:
          return markTable[n].yello88;
        case 2:
          return markTable[n].yello816;
        case 3:
          return markTable[n].whitex16;
        default:
          return -1;
      }
    }
    ++n;
  }
  return -1;
}


static unsigned short get_char_sprite_index_kind_0(char code) {
  unsigned short index;

  if (code >= '0' && code <= '9') {
    index = code - 37;
  }
  else if (code >= 'A' && code <= 'Z') {
    index = code - 44;
  }
  else {
    index = get_markfont_index(code, 0);
    if (index == -1) {
      return 0;
    }
  }

  return index + 1;
}


static unsigned short get_char_sprite_index_kind_1(char code) {
  unsigned short index;

  if (code >= '0' && code <= '9') {
    index = code - 1;
  }
  else if (code >= 'A' && code <= 'Z') {
    index = code - 8;
  }
  else {
    index = get_markfont_index(code, 1);
    if (index == -1) {
      return 0;
    }
  }

  return index + 1;
}


static unsigned short get_char_sprite_index_kind_2(char code) {
  unsigned short index;

  if (code >= '0' && code <= '9') {
    index = code + 35;
  }
  else if (code >= 'A' && code <= 'Z') {
    index = code + 28;
  }
  else
  {
    index = get_markfont_index(code, 2);
    if (index == -1) {
      return 0;
    }
  }

  return index + 1;
}


static unsigned short get_char_sprite_index_kind_3(char code) {
  unsigned short index;

  if (code >= '0' && code <= '9') {
    index = code + 71;
  }
  else if (code >= 'A' && code <= 'Z') {
    index = code + 64;
  }
  else {
    index = get_markfont_index(code, 3);
    if (index == -1) {
      return 0;
    }
  }

  return index + 1;
}


static int isqrt(int xx) {
  int s, t;

  if (xx == 0) return 0;
  s = 1, t = xx;
  while (s < t) s <<= 1, t >>= 1;

  do {
    t = s;
    s = (s + xx / s) >> 1;
  }
  while (s < t);

  return t;
}
