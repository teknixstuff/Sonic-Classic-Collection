#include "../EQU.h"
#include "COMMON.h"
#include "SPS_EQU.h"

static unsigned short stage_table_damage[8] = { 364, 428, 492, 460, 432, 364, 420, 364 };
static unsigned short stage_table_hane[8] = { 352, 416, 480, 448, 420, 352, 408, 352 };






























void Special_block_chg(unsigned short* hane1, unsigned short* hane2, unsigned short* dmg1, unsigned short* dmg2) {

  if ((unsigned short)++hane_cnt > 2) hane_cnt = 0;
  *hane1 = stage_table_hane[stagenm] / 4 - 1;
  *hane2 = hane_cnt + stage_table_hane[stagenm] / 4 - 1;

  ++chg_timer;
  if (!(chg_timer & 1)) {

    if ((unsigned short)++damage_cnt > 4 - 1) damage_cnt = 0;
  }

  *dmg1 = stage_table_damage[stagenm] / 4 - 1;
  *dmg2 = damage_cnt + stage_table_damage[stagenm] / 4 - 1;


}
