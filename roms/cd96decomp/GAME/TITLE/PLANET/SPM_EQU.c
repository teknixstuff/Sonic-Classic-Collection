#include "../../EQU.h"
#include "../../SPM_EQU.h"
#include "LPL_TYPES.h"
#include <string.h>
#include "../../../services.h"

unsigned char cgchg_end;
unsigned char cgchg_timer;
unsigned char flash_flg;
short lplanet_no;
short flash_timer;
unsigned char actset_wk;
unsigned char actset_flg;
short spr_colno;
short spr_coltimer;
short main_lpcnt;
short funka_patno;
short funka_pctimer;
sprite_status_lpl lplactwk[18];
int_union* lphscrollbuff;
unsigned char music_selflg;
unsigned char m2save[22528];


void lplWorkRamClear(void) {
  gFadeFlag = 0;
  DLLRetMode = 0;
  ProcMode = 0;

  memset(lplactwk, 0, sizeof(lplactwk));

  coltimer = 0;
  colorno = 0;
  funka_pctimer = 0;
  funka_patno = 0;
  main_lpcnt = 0;
  spr_coltimer = 0;
  spr_colno = 0;



  memset(actset_tm, 0, sizeof(actset_tm));
  actset_flg = 0;
  actset_wk = 0;
  push_flg = 0;
  int_flg = 0;
  colorflg = 0;

  intmode = 0;
  gmtime0 = 0;
  gmtime1 = 0;
  sr_save = 0;

  ranum = 0;
  overint = 0;

  flash_timer = 0;
  lplanet_no = 0;
  startcolor = 0;
  colorcnt = 0;
  flash_flg = 0;
  cgchg_timer = 0;
  cgchg_end = 0;


  comflag_m = 0;
  comflag_s = 0;

  comdata_m0 = 0;
  comdata_m1 = 0;
  comdata_m2 = 0;
  comdata_m3 = 0;
  comdata_m4 = 0;
  comdata_m5 = 0;
  comdata_m6 = 0;
  comdata_m7 = 0;
  swdata1.w = 0;
  swdata2.w = 0;
  comdata_s0 = 0;
  comdata_s1 = 0;
  comdata_s2 = 0;
  comdata_s3 = 0;
  comdata_s4 = 0;
  comdata_s5 = 0;
  comdata_s6 = 0;
  comdata_s7 = 0;
}
