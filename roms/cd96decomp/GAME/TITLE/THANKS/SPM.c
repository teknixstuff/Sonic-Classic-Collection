#include "../../EQU.h"
#include "../../SPM_EQU.h"
#include "THANKS_TYPES.h"
#include <string.h>
#include "../../../services.h"

short end_timer;
short heart_tm;
short animal_timer;
unsigned char animal_flg;
unsigned char poseno;
short posetimer;
short coltimer2;
short colorno2;
short wkarea3;
short wkarea2;
short wkarea1;
short prg_mode;
unsigned char quit_flg;
sprite_status_thanks** priptr[4];
sprite_status_thanks* pribuf3[64];
sprite_status_thanks* pribuf2[64];
sprite_status_thanks* pribuf1[64];
sprite_status_thanks* pribuf0[64];
sprite_status_thanks thanksactwk[66];


void thanksWorkRamClear(void) {
  gFadeFlag = 0;
  DLLRetMode = 0;
  ProcMode = 0;

  memset(thanksactwk, 0, sizeof(thanksactwk));






  memset(pribuf0, 0, sizeof(pribuf0));
  memset(pribuf1, 0, sizeof(pribuf1));
  memset(pribuf2, 0, sizeof(pribuf2));
  memset(pribuf3, 0, sizeof(pribuf3));


  priptr[0] = 0;
  priptr[1] = 0;
  priptr[2] = 0;
  priptr[3] = 0;

  quit_flg = 0;
  push_flg = 0;
  int_flg = 0;
  colorflg = 0;
  colorno = 0;
  coltimer = 0;

  linkdata = 0;
  intmode = 0;
  gmtime0 = 0;
  gmtime1 = 0;
  sr_save = 0;
  ranum = 0;
  overint = 0;

  startcolor = 0;
  colorcnt = 0;

  prg_mode = 0;

  wkarea1 = 0;
  wkarea2 = 0;
  wkarea3 = 0;

  memset(actset_tm, 0, sizeof(actset_tm));

  colorno2 = 0;
  coltimer2 = 0;

  posetimer = 0;
  poseno = 0;
  animal_flg = 0;
  animal_timer = 0;
  heart_tm = 0;

  end_timer = 0;


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
