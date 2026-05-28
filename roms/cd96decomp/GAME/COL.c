#include "EQU.h"
#include "COL.h"
#include "R1/COL1.h"
#include "R3/COL3.h"
#include "R4/COL4.h"
#include "R5/COL5.h"
#include "R6/COL6.h"
#include "R7/COL7.h"
#include "R8/COL8.h"

extern palette_part zone1colortbla[6];
extern palette_part zone1colortblb[6];
extern palette_part zone1colortblc[6];
extern palette_part zone1colortbld[6];
extern palette_part zone3colortbla[6];
extern palette_part zone3colortblb[5];
extern palette_part zone3colortblc[8];
extern palette_part zone3colortbld[7];
extern palette_part zone4colortbla[5];
extern palette_part zone4colortblb[5];
extern palette_part zone4colortblc[6];
extern palette_part zone4colortbld[6];
extern palette_part zone5colortbla[6];
extern palette_part zone5colortblb[6];
extern palette_part zone5colortblc[7];
extern palette_part zone5colortbld[7];
extern palette_part zone6colortbla[6];
extern palette_part zone6colortblb[6];
extern palette_part zone6colortblc[7];
extern palette_part zone6colortbld[7];
extern palette_part zone7colortbla[6];
extern palette_part zone7colortblb[6];
extern palette_part zone7colortblc[7];
extern palette_part zone7colortbld[7];
extern palette_part zone8colortbla[6];
extern palette_part zone8colortblb[6];
extern palette_part zone8colortblc[12];
extern palette_part zone8colortbld[12];

static void colchg0(void);
static int fadein0_new(void);
static void fadein1(void);
static int fadeout_new(void);
static void fadeout1(void);
static void fadeout2(PALETTEENTRY* lpPeDest);
static int flashin_new(void);
static void flashin1(void);
static void flashin2(PALETTEENTRY* lpPeDest, PALETTEENTRY* lpPeSrc);
static int flashout_new(void);
static void flashout1(void);
static void flashout2(PALETTEENTRY* lpPeDest);
static int clwout_new(void);
static void woutcolor(unsigned short wD1);
static int clwin_new(void);
static void wincolor(unsigned char byD0, unsigned short wD1);
static void colorset00(int ColorNo, int WorkOffs);

PALETTEENTRY advacolor[64] = {
  {   0,  32, 160, 1 }, {   0,   0,  96, 1 }, {   0,   0, 192, 1 }, {  64,  64, 224, 1 },
  {  96,  96, 224, 1 }, { 128, 128, 224, 1 }, { 224, 224, 224, 1 }, { 224, 160,   0, 1 },
  { 160,  96,   0, 1 }, {  96,  32,   0, 1 }, { 224, 224,   0, 1 }, { 160, 160, 224, 1 },
  { 192,   0,   0, 1 }, {  96,   0,   0, 1 }, {  32,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0, 192, 1 }, {  32,  32, 224, 1 }, {  64,  64, 224, 1 },
  {  96,  96, 224, 1 }, { 128, 128, 224, 1 }, { 224, 224, 224, 1 }, { 160, 160, 160, 1 },
  { 128, 128, 128, 1 }, {  96,  96,  96, 1 }, {  64,  64,  64, 1 }, { 128,  64,  32, 1 },
  { 224, 160, 128, 1 }, { 192, 128,  96, 1 }, {   0,   0,   0, 1 }, { 224,   0,   0, 1 },
  {   0,   0, 128, 1 }, {  32,   0,   0, 1 }, { 224, 224, 224, 1 }, {  96,  32,   0, 1 },
  { 128,  64,   0, 1 }, { 192,  96,   0, 1 }, { 224, 128,   0, 1 }, { 224, 192,   0, 1 },
  {  32,  64, 192, 1 }, {  96, 128, 224, 1 }, { 160, 192, 224, 1 }, { 192, 224, 224, 1 },
  {   0,  64,   0, 1 }, {   0,  96,   0, 1 }, {  64, 160,   0, 1 }, { 128, 224,   0, 1 },
  {  32, 128, 192, 1 }, {  32,   0, 160, 1 }, {  32,  64, 192, 1 }, {  96, 128, 224, 1 },
  { 160, 192, 224, 1 }, { 192, 224, 224, 1 }, { 224, 224, 224, 1 }, { 192, 160, 224, 1 },
  { 160, 128, 224, 1 }, { 128,  96, 224, 1 }, { 128, 224,   0, 1 }, {  64, 160,   0, 1 },
  {  32,   0,   0, 1 }, {  96,  32,   0, 1 }, { 192,  96,   0, 1 }, { 224, 192,   0, 1 }
};
PALETTEENTRY advacolor2[64] = {
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {  32,   0,   0, 1 }, {  32,   0,   0, 1 },
  {  64,  32,  32, 1 }, {  64,  32,  32, 1 }, {  96,  64,  64, 1 }, {  96,  64,  64, 1 },
  {  64,  32,  32, 1 }, {  64,  32,  32, 1 }, {  96,  64,  64, 1 }, { 128,  96,  96, 1 },
  {  64,  32,  32, 1 }, {  32,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {  32,   0,   0, 1 }, {  64,  32,  32, 1 },
  {  64,  32,  32, 1 }, {  96,  64,  64, 1 }, { 128,  96,  96, 1 }, {  64,  32,  32, 1 },
  {  96,  64,  64, 1 }, {  64,  32,  32, 1 }, {  32,   0,   0, 1 }, {  64,  32,  32, 1 },
  {  96,  64,  64, 1 }, {  64,  32,  32, 1 }, {   0,   0,   0, 1 }, {  64,  32,  32, 1 },
  {   0,   0,   0, 1 }, { 224, 224,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, { 224, 224,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, { 192, 224, 224, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, { 192, 224, 224, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static unsigned short code_tbl[3] = { 1, 5, 9 };
static PALETTEENTRY colorsave[64];
static unsigned char clfflg;
static unsigned char byMskwk;
static unsigned short wColwk;
int FadeCount;


void clchgctr(void) {
  static void(*colchgtbls[7][4])(void) = {
    { &colchg11b, &colchg11a, &colchg11d, &colchg11c },
    { &colchg0, &colchg3a, &colchg3d, &colchg3c },
    { &colchg4b, &colchg4a, &colchg4d, &colchg4c },
    { &colchg5b, &colchg5a, &colchg5d, &colchg5c },
    { &colchg6b, &colchg6a, &colchg6d, &colchg6c },
    { &colchg0, &colchg7a, &colchg7d, &colchg0 },
    { &colchg8b, &colchg8a, &colchg8d, &colchg8c }
  };

  colchgtbls[stageno_i.b.h][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)]();
}


static void colchg0(void) {}


void clchg_sub0(unsigned char* pChgTime, unsigned char* pChgCnt, unsigned char* pCntTbl, PALETTEENTRY* pColTbl) {
  PALETTEENTRY* lpPe;

  --*pChgTime;
  if ((char)*pChgTime < 0) {
    lpPe = &lpcolorwk[*pCntTbl++];
    ++*pChgCnt;
    if (*pChgCnt >= *pCntTbl++) {
      *pChgCnt = 0;
    }

    pCntTbl = &pCntTbl[*pChgCnt * 2];
    *pChgTime = pCntTbl[0];
    *lpPe = pColTbl[pCntTbl[1]];
  }
}


void fadein(void) {
  startcolor = 0;
  colorcnt = 63;
  fadein0();
}


void fadein0(void) {
  PALETTEENTRY* lpPe;
  int i;

  lpPe = &lpcolorwk[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    lpPe->peRed = 0;
    lpPe->peGreen = 0;
    lpPe->peBlue = 0;
    lpPe->peFlags = 1;
    ++lpPe;
  }
  FadeCount = 0;
  gFadeFlag = 1;
}


static int fadein0_new(void) {
  int_flg = 18;

  fadein1();


  if (++FadeCount > 21) {
    FadeCount = 0;
    return 1;
  }
  return 0;
}


static void fadein1(void) {
  PALETTEENTRY *lpPe, *lpPe2;
  int i;

  lpPe = &lpcolorwk[startcolor / 2];
  lpPe2 = &colorwk2[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    fadein2(lpPe, lpPe2);
    ++lpPe;
    ++lpPe2;
  }
  if (stageno.b.h == 1) return;

  lpPe = &lpcolorwk3[startcolor / 2];
  lpPe2 = &colorwk4[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    fadein2(lpPe, lpPe2);
    ++lpPe;
    ++lpPe2;
  }
}


void fadein2(PALETTEENTRY* lpPeDest, PALETTEENTRY* lpPeSrc) {
  if (lpPeSrc->peBlue != lpPeDest->peBlue
      || lpPeSrc->peGreen != lpPeDest->peGreen
      || lpPeSrc->peRed != lpPeDest->peRed) {
    if (lpPeSrc->peBlue > lpPeDest->peBlue) {
      lpPeDest->peBlue += 32;
    }
    else if (lpPeSrc->peGreen > lpPeDest->peGreen) {
      lpPeDest->peGreen += 32;
    }
    else if (lpPeSrc->peRed > lpPeDest->peRed) {
      lpPeDest->peRed += 32;
    }
  }
}


void fadeout(void) {
  startcolor = 0;
  colorcnt = 63;

  FadeCount = 0;
  gFadeFlag = 2;
}


static int fadeout_new(void) {
  int_flg = 18;

  fadeout1();


  if (++FadeCount > 21) {
    FadeCount = 0;
    return 1;
  }
  return 0;
}


static void fadeout1(void) {
  PALETTEENTRY* lpPe;
  int i;

  lpPe = &lpcolorwk[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    fadeout2(lpPe);
    ++lpPe;
  }
  lpPe = &lpcolorwk3[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    fadeout2(lpPe);
    ++lpPe;
  }
}


static void fadeout2(PALETTEENTRY* lpPeDest) {
  if (lpPeDest->peRed) {
    lpPeDest->peRed -= 32;
  }
  else if (lpPeDest->peGreen) {
    lpPeDest->peGreen -= 32;
  }
  else if (lpPeDest->peBlue) {
    lpPeDest->peBlue -= 32;
  }
}


void flashin(void) {
  PALETTEENTRY* lpPe;
  int i;

  startcolor = 0;
  colorcnt = 63;

  lpPe = &lpcolorwk[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    lpPe->peRed = 224;
    lpPe->peGreen = 224;
    lpPe->peBlue = 224;
    lpPe->peFlags = 1;
    ++lpPe;
  }
  FadeCount = 0;
  gFadeFlag = 3;
}


static int flashin_new(void) {
  int_flg = 18;

  flashin1();


  if (++FadeCount > 21) {
    FadeCount = 0;
    return 1;
  }
  return 0;
}


static void flashin1(void) {
  PALETTEENTRY *lpPe, *lpPe2;
  int i;

  lpPe = &lpcolorwk[startcolor / 2];
  lpPe2 = &colorwk2[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    flashin2(lpPe, lpPe2);
    ++lpPe;
    ++lpPe2;
  }
  if (stageno.b.h == 1) return;

  lpPe = &lpcolorwk3[startcolor / 2];
  lpPe2 = &colorwk4[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    flashin2(lpPe, lpPe2);
    ++lpPe;
    ++lpPe2;
  }
}


static void flashin2(PALETTEENTRY* lpPeDest, PALETTEENTRY* lpPeSrc) {
  if (lpPeSrc->peBlue != lpPeDest->peBlue
      || lpPeSrc->peGreen != lpPeDest->peGreen
      || lpPeSrc->peRed != lpPeDest->peRed) {
    if (lpPeSrc->peBlue < lpPeDest->peBlue) {
      lpPeDest->peBlue -= 32;
    }
    else if (lpPeSrc->peGreen < lpPeDest->peGreen) {
      lpPeDest->peGreen -= 32;
    }
    else if (lpPeSrc->peRed < lpPeDest->peRed) {
      lpPeDest->peRed -= 32;
    }
  }
}


void flashout(void) {
  startcolor = 0;
  colorcnt = 63;

  FadeCount = 0;
  gFadeFlag = 4;
}


static int flashout_new(void) {
  int_flg = 18;

  flashout1();


  if (++FadeCount > 21) {
    FadeCount = 0;
    return 1;
  }
  return 0;
}


static void flashout1(void) {
  PALETTEENTRY* lpPe;
  int i;

  lpPe = &lpcolorwk[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    flashout2(lpPe);
    ++lpPe;
  }
  lpPe = &lpcolorwk3[startcolor / 2];

  for (i = 0; colorcnt >= i; ++i) {
    flashout2(lpPe);
    ++lpPe;
  }
}


static void flashout2(PALETTEENTRY* lpPeDest) {
  if (lpPeDest->peRed != 224) {
    lpPeDest->peRed += 32;
  }
  else if (lpPeDest->peGreen != 224) {
    lpPeDest->peGreen += 32;
  }
  else if (lpPeDest->peBlue != 224) {
    lpPeDest->peBlue += 32;
  }
}


void clwout(void) {
  clfflg = 1;
  gFadeFlag = 6;
  FadeCount = 8;
  wColwk = 0;
}


static int clwout_new(void) {
  if (wColwk >= 3) {
    gFadeFlag = 0;
  }
  else if (--FadeCount >= 0) {
    woutcolor(code_tbl[wColwk]);
  }
  else {
    FadeCount = 8;
    ++wColwk;
  }
  return 0;
}


static void woutcolor(unsigned short wD1) {
  short i;
  PALETTEENTRY* lpColwk;

  lpColwk = lpcolorwk;
  for (i = 0; i < 64; ++i, ++lpColwk) {
    switch (wD1) {
      case 1:
        if (lpColwk->peRed < 224) {
          lpColwk->peRed += 32;
        }
        break;
      case 5:
        if (lpColwk->peGreen < 224) {
          lpColwk->peGreen += 32;
        }
        break;
      case 9:
        if (lpColwk->peBlue < 224) {
          lpColwk->peBlue += 32;
        }
        break;
    }
  }
}


void clwin_init(void) {
  short i;
  PALETTEENTRY* lpColwk;
  PALETTEENTRY* lpSavewk;
  PALETTEENTRY tmp = { 224, 224, 224, 1 };

  lpColwk = lpcolorwk;
  lpSavewk = colorsave;
  for (i = 0; i < 64; ++i) {
    *lpSavewk++ = *lpColwk;
    *lpColwk++ = tmp;
  }
}


void clwin(void) {
  gFadeFlag = 5;
  FadeCount = 8;
  wColwk = 0;
  byMskwk = 224;
}


static int clwin_new(void) {
  if (wColwk >= 3) {
    gFadeFlag = 0;
  }
  else if (--FadeCount >= 0) {
    wincolor(byMskwk, code_tbl[wColwk]);
    byMskwk -= 32;
  }
  else {
    FadeCount = 8;
    byMskwk = 224;
    ++wColwk;
  }
  return 0;
}


static void wincolor(unsigned char byD0, unsigned short wD1) {
  short i;
  unsigned char byColwk;
  PALETTEENTRY *lpColwk, *lpSavewk;

  lpColwk = lpcolorwk;
  lpSavewk = colorsave;
  for (i = 0; i < 64; ++i) {
    switch (wD1) {
      case 1:
        byColwk = lpSavewk->peRed;
        if (byColwk < byD0) byColwk = byD0;
        lpColwk->peRed = byColwk;
        break;
      case 5:
        byColwk = lpSavewk->peGreen;
        if (byColwk < byD0) byColwk = byD0;
        lpColwk->peGreen = byColwk;
        break;
      case 9:
        byColwk = lpSavewk->peBlue;
        if (byColwk < byD0) byColwk = byD0;
        lpColwk->peBlue = byColwk;
        break;
    }
    ++lpSavewk;
    ++lpColwk;
  }
}


void colorset(int ColorNo) {
  colorset00(ColorNo, 1);
}


void colorset2(int ColorNo) {
  colorset00(ColorNo, 0);
}


void colorset3(int ColorNo) {
  colorset00(ColorNo, 2);
}


static void colorset00(int ColorNo, int WorkOffs) {
  PALETTEENTRY *lppe;
  PALETTEENTRY *lpPeSrc, *lpPeDest;
  int i, n;
  palette_part* colortbls[7][4] = {
    { zone1colortblb, zone1colortbla, zone1colortbld, zone1colortblc },
    { zone3colortblb, zone3colortbla, zone3colortbld, zone3colortblc },
    { zone4colortblb, zone4colortbla, zone4colortbld, zone4colortblc },
    { zone5colortblb, zone5colortbla, zone5colortbld, zone5colortblc },
    { zone6colortblb, zone6colortbla, zone6colortbld, zone6colortblc },
    { zone7colortblb, zone7colortbla, zone7colortbld, zone7colortblc },
    { zone8colortblb, zone8colortbla, zone8colortbld, zone8colortblc }
  };
  palette_part* colortbl = colortbls[stageno_i.b.h][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];

  switch (WorkOffs + colortbl[ColorNo].offset / 64) {
    case 0:
      lppe = lpcolorwk; break;
    case 1:
      lppe = colorwk2; break;
    case 2:
      lppe = lpcolorwk3; break;
    default:
      lppe = colorwk4; break;
  }

  lpPeSrc = colortbl[ColorNo].PeSrc;
  lpPeDest = &lppe[colortbl[ColorNo].offset];
  n = colortbl[ColorNo].cnt;
  for (i = 0; i < n; ++i) {
    *lpPeDest++ = *lpPeSrc++;
  }
}


int FadeProc(void) {
  switch (gFadeFlag) {
    case 1:
      return fadein0_new();
    case 2:
      return fadeout_new();
    case 3:
      return flashin_new();
    case 4:
      return flashout_new();
    case 5:
      return clwin_new();
    case 6:
      return clwout_new();
  }
  return 1;
}
