#include "../EQU.h"
#include "COMMON.h"
#include "SPS_EQU.h"
#include "COLI_S.h"
#include <stdio.h>
#include "ACT_S.h"

static unsigned short sm_cnt;
unsigned char ctbl00[96] = { 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 4, 0, 4, 4, 4, 0, 0, 0, 0, 0, 4, 0, 4, 4, 4, 4, 4, 0, 0, 4, 0, 3, 3, 3, 3, 4, 0, 4, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 4, 4, 0, 0, 0, 4, 0, 4, 0, 0, 0, 4, 4, 4, 5, 7, 7, 8, 9, 9, 9, 2, 2, 2, 6, 6, 6, 6, 3 };
unsigned char ctbl10[112] = { 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 4, 0, 0, 3, 0, 3, 0, 3, 4, 0, 0, 3, 0, 0, 4, 4, 0, 4, 4, 0, 4, 0, 0, 0, 4, 0, 0, 4, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 3, 0, 3, 3, 3, 3, 5, 9, 9, 9, 9, 9, 8, 7, 7, 4, 0, 0, 3, 3, 3, 2, 2, 2, 6, 6, 6, 6, 0 };
unsigned char ctbl20[144] = { 3, 1, 1, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 4, 4, 0, 0, 0, 4, 0, 4, 0, 4, 0, 0, 0, 0, 0, 4, 0, 3, 4, 0, 0, 3, 0, 0, 0, 4, 4, 0, 0, 0, 4, 0, 0, 4, 4, 0, 0, 0, 3, 0, 0, 3, 0, 0, 4, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 5, 7, 7, 8, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 6, 6, 6, 6, 3, 3, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char ctbl30[128] = { 3, 1, 1, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 4, 4, 0, 4, 0, 4, 0, 0, 4, 4, 0, 0, 4, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 7, 7, 7, 8, 8, 7, 7, 9, 9, 2, 2, 2, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char ctbl40[112] = { 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 4, 4, 4, 0, 4, 0, 0, 0, 4, 0, 4, 4, 0, 4, 3, 0, 0, 0, 4, 4, 3, 3, 3, 3, 3, 3, 3, 5, 7, 7, 7, 7, 7, 8, 0, 0, 9, 9, 9, 2, 2, 2, 6, 6, 6, 6 };
unsigned char ctbl50[96] = { 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 4, 4, 0, 0, 0, 4, 0, 4, 0, 0, 4, 4, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 7, 7, 8, 7, 7, 3, 0, 9, 9, 9, 9, 2, 2, 2, 6, 6, 6, 6, 0 };
unsigned char ctbl60[112] = { 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 0, 0, 0, 0, 4, 4, 3, 3, 3, 3, 3, 0, 3, 0, 5, 7, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 6, 6, 6, 6, 0, 0, 0 };
unsigned char ctbl70[144] = { 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 4, 0, 4, 4, 4, 0, 0, 0, 0, 0, 4, 0, 4, 4, 4, 4, 4, 0, 0, 4, 0, 3, 3, 3, 3, 4, 0, 4, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 4, 4, 0, 0, 0, 4, 0, 4, 0, 0, 0, 4, 4, 4, 5, 7, 7, 8, 9, 9, 9, 2, 2, 2, 6, 6, 6, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char* colliadr_tbl[8] = {
  ctbl00,
  ctbl10,
  ctbl20,
  ctbl30,
  ctbl40,
  ctbl50,
  ctbl60,
  ctbl70
};













void ufovspl(sprite_status_sp* pActwk) {
  sprite_status_sp* pPlaywk;
  short iD0, iD1, iD2;

  pPlaywk = &specactwk[0];
  if (pPlaywk->actno == 0) return;
  if (pPlaywk->colliflg != 0) return;

  iD0 = pActwk->x_posi.w.h - 16;
  iD1 = iD0 + 32;
  iD2 = pPlaywk->x_posi.w.h - 16;
  if (iD2 > iD1) return;

  if (iD2 + 32 < iD0) return;


  iD0 = pActwk->y_posi.w.h - 12;
  iD1 = iD0 + 24;
  iD2 = pPlaywk->y_posi.w.h - 16;
  if (iD2 > iD1) return;

  if (iD2 + 32 < iD0) return;


  if ((unsigned short)pPlaywk->z_posi.w.h < 528) return;

  if ((unsigned short)pPlaywk->z_posi.w.h >= 624) return;

  pPlaywk->colliflg = pActwk->actno;
  pActwk->colliflg = pPlaywk->actno;
}















void plcolli(sprite_status_sp* pActwk) {
  short iD1, iD2;

  stpnmget(pActwk->x_posi.w.h, pActwk->y_posi.w.h, &iD1, &iD2);
  pActwk->scno_ce = colliadr[iD2];










  iD1 >>= 12;
  iD1 &= 15;
  pActwk->scno_sdir = iD1;

  stpnmget(pActwk->x_posi.w.h - 8, pActwk->y_posi.w.h - 8, &iD1, &iD2);



  pActwk->scno_ul = colliadr[iD2];

  stpnmget(pActwk->x_posi.w.h + 8, pActwk->y_posi.w.h - 8, &iD1, &iD2);



  pActwk->scno_ur = colliadr[iD2];

  stpnmget(pActwk->x_posi.w.h + 8, pActwk->y_posi.w.h + 8, &iD1, &iD2);



  pActwk->scno_dr = colliadr[iD2];

  stpnmget(pActwk->x_posi.w.h - 8, pActwk->y_posi.w.h + 8, &iD1, &iD2);



  pActwk->scno_dl = colliadr[iD2];
}













short blcolli(sprite_status_sp* pActwk) {
  short iD0, iD1, iD2;

  stpnmget(pActwk->x_posi.w.h, pActwk->y_posi.w.h, &iD1, &iD2);
  iD0 = colliadr[iD2];
  return iD0;
}
















void stpnmget(short iXposi, short iYposi, short* ipD1, short* ipD2) {
  ushort_union uwk1;
  ushort_union uwk2;
  char buf[80];
  unsigned short wD2 = iXposi >> 5;
  unsigned short wD3 = iYposi >> 5;

  wD2 += wD3 << 7;
  if (wD2 >= 16383) {


    sprintf(buf, "stpnmget Err wD2 = %x\n", wD2);
    printf(buf);
    wD2 = 16383;
  }
  uwk1.w = sm_adr0[wD2];
  uwk2.b.h = uwk1.b.l;
  uwk2.b.l = uwk1.b.h;
  *ipD2 = uwk1.w;

  *ipD1 = *ipD2;
  *ipD2 &= 2047;
  *ipD2 = *ipD2 >> 2;
}













void colli_init(void) {
  colliadr = colliadr_tbl[stagenm];
}
