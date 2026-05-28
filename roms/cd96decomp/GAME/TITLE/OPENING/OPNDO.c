#include "../../EQU.h"
#include "../../../audio.h"
#include "OPNDO.h"
#include <string.h>
#include "../../../services.h"
#include "../COMMON/GRID.h"
#include "../COMMON/SCORE_DATA_TYPES.h"
#include "../COMMON/SMORPHDATA.h"
#include "../COMMON/SPRITEBMP.h"

#define SPRITE_START_GAME 7
#define SPRITE_MENU_OFFSET 8
#define SPRITE_LEFT_ARROW 17
#define SPRITE_RIGHT_ARROW 18
#define SPRITE_PLANET 35

typedef struct {
  unsigned short wrap;
  void* pSmorphArray;
}
smorph;

typedef struct {
  int time;
  POINT point;
}
time_point;

typedef struct {
  int time;
  unsigned short timingPatNo;
}
time_pat;

extern sprite_bmp OPN_infoSprtBmp[];
extern PALETTEENTRY OPN_tblPal1[16];
extern PALETTEENTRY OPN_tblPal1a[16];
extern PALETTEENTRY OPN_tblPal2[16];
extern PALETTEENTRY OPN_tblPal2a[16];
extern PALETTEENTRY OPN_tblPal3[16];
extern PALETTEENTRY OPN_tblPal4[16];
extern score_data g_current_score_data;
extern int g_use_original_soundtrack;

static void OESetSequenceNum(unsigned short num);
static void OEDraw(void);
static void OEUpdateHand(void);
static void OEUpdateMayu(void);
static void OEUpdatePlanet(void);
static void OEUpdateMizu(void);
static void OEUpdateKumo(void);
static void GetEnabeMenu(unsigned int* menuTable);
static int GetNextMenu(unsigned int* menuTable, int kind, unsigned int bNext);
static unsigned int ChkNewSlot(void);
static void OEUpdateMsg(void);
static void OETitleSta(void);
static void OETitle(void);
static void OEFadeOut(void);
static void OEFadeIn(void);
static void OEOpenSta(void);
static void OESegaLogo(void);
static void OEDark(void);
static void OESonic(void);
static int OEEnd(void);
static void OESprCreate(unsigned short timing);
static void ShowSprite(int index);

static int nTimerCunt;
static unsigned short nSequenceNum;
static unsigned int selectIndx;
static unsigned int bFirstTitle = 1;
static time_point ptPlnt[8] = {
  {  16, { 240, -33 } },
  {  32, { 240, -34 } },
  {  48, { 240, -35 } },
  {  84, { 240, -34 } },
  { 100, { 240, -33 } },
  { 116, { 240, -32 } },
  { 128, { 240, -32 } },
  {  -1, {   0,   0 } }
};
static time_pat timeHand[16] = {
  {  0, 11 },
  { 18, 10 },
  { 19,  9 },
  { 20,  8 },
  { 21,  8 },
  { 22,  9 },
  { 23, 10 },
  { 24, 11 },
  { 25, 11 },
  { 26, 10 },
  { 27,  9 },
  { 28,  8 },
  { 29,  8 },
  { 30,  9 },
  { 31, 10 },
  { 32, 11 }
};
static int timeMayu[2] = { 18, 20 };
static int posiLeftArrow[3] = { 90, 88, 86 };
static int posiRightArrow[3] = { 210, 212, 214 };
static unsigned int bDrawDisable;
static unsigned short nMenuKind;
static int nFadoSeqNum;
static int nFadoValu;
static int nFadoTime;
static unsigned int bFadePaletDisable[4];
static PALETTEENTRY workPalet[4][16];
static int shownSprites[35][3] = { 0 };
static unsigned char shownGrids[3] = { 0 };


static void OESetSequenceNum(unsigned short num) {
  nSequenceNum = num;
  nTimerCunt = -1;
}


void OPN_Init(void) {
  memcpy(&lpcolorwk[0], OPN_tblPal1, sizeof(OPN_tblPal1));
  memcpy(&lpcolorwk[16], OPN_tblPal2, sizeof(OPN_tblPal2));
  memcpy(&lpcolorwk[32], OPN_tblPal3, sizeof(OPN_tblPal3));
  memcpy(&lpcolorwk[48], OPN_tblPal4, sizeof(OPN_tblPal4));

  nSequenceNum = 1;
  nTimerCunt = 0;
  memset(shownSprites, 0, sizeof(shownSprites));
  memset(shownGrids, 0, sizeof(shownGrids));
  memset(hscrollbuff, 0, sizeof(hscrollbuff));
  SetSmorph(0);
}


int OPN_Main(void) {
  int ret = 0;

  switch (nSequenceNum) {
    case 1:
      OEOpenSta();
      break;

    case 2:
      OESegaLogo();
      break;

    case 3:
      OEDark();
      break;

    case 5:
      OESonic();
      break;

    case 6:
      OETitleSta();
      break;

    case 7:
      OETitle();
      break;

    case 8:
      OEFadeOut();
      break;

    case 9:
      OEFadeIn();
      break;

    case 999:
      ret = OEEnd();
      break;
  }
  if (nTimerCunt == 0x7FFFFFFF)
    nTimerCunt = 5184000;
  else
    ++nTimerCunt;

  OEDraw();

  return ret;
}


static void OEDraw(void) {
  int i, spriteNo;

  if (nSequenceNum > 1 && bDrawDisable == 0) {
    for (i = 0, spriteNo = 0; i < 35; ++i) {
      if (shownSprites[i][0] != 0) {
        EAsprset(shownSprites[i][1] + 128, shownSprites[i][2] + 128, OPN_infoSprtBmp[i].index, spriteNo++, OPN_infoSprtBmp[i].reverse);
      }
    }

    for ( ; i < 80; ++i) {
      EAsprset(0, 0, 0, spriteNo, 0);
    }

    for (i = 0; i < 3; ++i) {
      if (shownGrids[i] != 0) {
        OEGridCreate(i);
      }
    }
  }
}


static void OEUpdateHand(void) {
  static int num;

  if (nTimerCunt == 0) {
    num = 0;
  }
  if (nTimerCunt == timeHand[num].time && (unsigned int)num < 16) {
    if (num != 0)
      OESprCreate(timeHand[num].timingPatNo);
    ++num;
  }
  else if (num != 0)
    OESprCreate(timeHand[num - 1].timingPatNo);
  else {
    OESprCreate(timeHand[num].timingPatNo);
  }
}


static void OEUpdateMayu(void) {
  static int num;

  if (nTimerCunt == 0) {
    num = 0;
  }
  if (nTimerCunt == timeMayu[num] && (unsigned int)num < 2) {
    if (num % 2 == 0)
      OESprCreate(12);
    ++num;
  }
  else if (num % 2 == 0 && (unsigned int)num < 2) {
    OESprCreate(12);
  }
}


static void OEUpdatePlanet(void) {
  static int num;
  static int staTime;

  if (shownSprites[SPRITE_PLANET][0] != 0) {
    if (nTimerCunt == 0) {
      num = 0;
      staTime = 0;
    }

    shownSprites[SPRITE_PLANET][1] = ptPlnt[num].point.x;
    shownSprites[SPRITE_PLANET][2] = ptPlnt[num].point.y;
    if (ptPlnt[num].time == nTimerCunt - staTime) {
      if ((unsigned int)++num > 7) {
        num = 0;
      }
    }
    else if (ptPlnt[num].time == -1) {
      num = 0;
      staTime = nTimerCunt;

      shownSprites[SPRITE_PLANET][1] = ptPlnt[num].point.x;
      shownSprites[SPRITE_PLANET][2] = ptPlnt[num].point.y;
    }
  }
}


static void OEUpdateMizu(void) {
  int inc;
  int i;
  static int nHorizShearArray[64], fHorizShearArray[64];

  if (nTimerCunt == 0) {
    for (i = 0; i < 64; ++i) {
      fHorizShearArray[i] = 0;
      hscrollbuff[160 + i].l = 0;
    }
  }

  if (shownGrids[1] != 0) {
    if (nTimerCunt % 2 == 0) {
      for (i = 0; i < 64; ++i) {
        inc = i * 10 + 40;
        fHorizShearArray[i] += inc;
        if (fHorizShearArray[i] > 32000)
          fHorizShearArray[i] -= 32000;
        hscrollbuff[160 + i].l = -(fHorizShearArray[i] / 100);
      }
    }
  }
}


static void OEUpdateKumo(void) {
  int i;
  static unsigned short incY;
  static smorph_data RotateMorphValues[128];
  static unsigned char offsetY[92] = {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
     20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
     40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  52,  54,  56,  58,  60,  62,  64,  66,  68,
     70,  72,  74,  76,  78,  80,  84,  88,  92,  96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136,
    142, 148, 154, 160, 170, 180, 190, 200, 210, 220, 236, 255
  };
  static smorph RotateMorph;

  if (nTimerCunt == 0) {
    for (i = 0; i < 92; ++i) {
      RotateMorphValues[i].StartX = (i * -64000 / 92 + 32767 + 31233) * 65;
      RotateMorphValues[i].StartY = i * 65536;
      RotateMorphValues[i].DeltaX = (i * 400 / 92 + 400) * 65;
      RotateMorphValues[i].DeltaY = 0;
    }
    for (i = 92; i < 128; ++i) {
      RotateMorphValues[i].StartX = 65536;
      RotateMorphValues[i].StartY = 65536;
      RotateMorphValues[i].DeltaX = 0;
      RotateMorphValues[i].DeltaY = 0;
    }
    RotateMorph.wrap = 0;
    RotateMorph.pSmorphArray = RotateMorphValues;

    incY = 0;
  }
  for (i = 0; i < 92; ++i) {
    RotateMorphValues[i].StartY = (offsetY[i] + incY) % 128 * 65536;
  }
  SetSmorph(RotateMorphValues);
  if (++incY >= 128) incY = 0;
}


static void GetEnabeMenu(unsigned int* menuTable) {
  score_data dummyData;
  unsigned int bDataExist;

  if (ReadScore(selectIndx, (char*)&dummyData, 0) == 0) {
    bDataExist = 0;
  }
  else {
    bDataExist = 1;
    selectIndx = ReadIndx(0);
    ReadScore(selectIndx, (char*)&g_current_score_data, 0);
  }

  menuTable[0] = 1;
  menuTable[6] = 1;
  menuTable[7] = 1;

  if (bDataExist != 0)
    if (ChkNewSlot() == 0)
      menuTable[0] = 0;

  if (g_current_score_data.saved == 1)
    menuTable[1] = 1;
  else
    menuTable[1] = 0;

  if (bDataExist != 0)
    menuTable[3] = 1;
  else
    menuTable[3] = 0;

  if (g_current_score_data.roundNo != 0)
    menuTable[2] = 1;
  else
    menuTable[2] = 0;

  if (g_current_score_data.roundNo >= 7 && g_current_score_data.total < 134734)
    menuTable[4] = 1;
  else
    menuTable[4] = 0;

  if (g_current_score_data.roundNo >= 7 && g_current_score_data.total < 92767)
    menuTable[5] = 1;
  else
    menuTable[5] = 0;
}


static int GetNextMenu(unsigned int* menuTable, int kind, unsigned int bNext) {
  int indx;
  int n;

  if (kind == -1) {
    if (menuTable[1] != 0)
      return 1;
    else
      return 0;
  }

  indx = kind;

  if (bNext != 0) {
    for (n = 0; n < 8; ++n) {
      ++indx;
      if (indx > 7) indx = 0;
      if (menuTable[indx] != 0) return indx;
    }
  }
  else {
    for (n = 0; n < 8; ++n) {
      --indx;
      if (indx < 0) indx = 7;
      if (menuTable[indx] != 0) return indx;
    }
  }
}


static unsigned int ChkNewSlot(void) {
  int i;
  score_data dummyData;

  for (i = 0; i < 6; ++i) {
    if (ReadScore(i, (char*)&dummyData, 0) == 0) break;

    if (dummyData.saved == 0) break;
  }
  if (i == 6) {
    return 0;
  }
  return 1;
}


static void OEUpdateMsg(void) {
  POINT leftArrowPoint;
  POINT rightArrowPoint;
  unsigned int kPosi;
  unsigned int lPosi;
  unsigned int rPosi;
  static POINT point;
  static int kind;
  static int nSeqNo;
  static unsigned int RArrow, LArrow;
  static int nSeqNoNext;
  static int timeOld;
  static unsigned int menuEnable[7];
  static int arrowKind;
  static unsigned int bDelete;
  static int testCheckMode;

  rPosi = lPosi = kPosi = 0;

  if (nTimerCunt == 0) {
    kind = SPRITE_START_GAME;
    bDelete = 0;
    timeOld = 0;
    arrowKind = 0;
    RArrow = LArrow = 0;
    testCheckMode = 1;
    GetEnabeMenu(menuEnable);
    nSeqNo = 1;
  }
  
  if (get_remaining_bgm() < 72000) {
    nMenuKind = 8;
    nFadoTime = 21;
    nFadoValu = 32;
    nFadoSeqNum = 999;
    OESetSequenceNum(8);
  }

  if (nSeqNo == 1) {
    if (testCheckMode != 0) {
      if (swdata1.w & 24320) {
        switch (testCheckMode) {
          case 1:   if (swdata1.w & 512) ++testCheckMode;
                    else if (swdata1.w & 256) testCheckMode = 12;
                    else if (swdata1.w & 2048) testCheckMode = 20;
                    else testCheckMode = 0;
                    break;
          case 2:   if (swdata1.w & 512) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 3:   if (swdata1.w & 512) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 4:   if (swdata1.w & 1024) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 5:   if (swdata1.w & 2048) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 6:   if (swdata1.w & 16384) {
                      nMenuKind = 9;
                      nFadoTime = 21;
                      nFadoValu = 32;
                      nFadoSeqNum = 999;
                      OESetSequenceNum(8);
                    }
                    else testCheckMode = 0;
                    break;
          case 12:  if (swdata1.w & 512) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 13:  if (swdata1.w & 512) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 14:  if (swdata1.w & 1024) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 15:  if (swdata1.w & 2048) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 16:  if (swdata1.w & 16384) {
                      nMenuKind = 10;
                      nFadoTime = 21;
                      nFadoValu = 32;
                      nFadoSeqNum = 999;
                      OESetSequenceNum(8);
                    }
                    else testCheckMode = 0;
                    break;
          case 20:  if (swdata1.w & 2048) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 21:  if (swdata1.w & 256) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 22:  if (swdata1.w & 256) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 23:  if (swdata1.w & 512) ++testCheckMode;
                    else testCheckMode = 0;
                    break;
          case 24:  if (swdata1.w & 16384) {
                      nMenuKind = 11;
                      nFadoTime = 21;
                      nFadoValu = 32;
                      nFadoSeqNum = 999;
                      OESetSequenceNum(8);
                    }
                    else testCheckMode = 0;
                    break;
        }

        timeOld = nTimerCunt;
        nSeqNoNext = 1;
        nSeqNo = 7;
      }
    }
    if (nTimerCunt % 20 == 0) {
      bDelete = bDelete ? 0 : 1;
    }

    if (bDelete == 0) ShowSprite(kind);

    if (swdata1.w & 53248) {
      point = OPN_infoSprtBmp[kind].point;
      if (bDelete == 0)
        ShowSprite(kind);
      memcpy(&lpcolorwk[16], OPN_tblPal2a, sizeof(OPN_tblPal2a));
      nSeqNo = 2;
    }
  }
  else if (nSeqNo == 2) {
    RArrow = LArrow = 0;
    memcpy(&lpcolorwk[16], OPN_tblPal2a, sizeof(OPN_tblPal2a));
    point.x += 32;
    if (point.x >= 320) {
      if (kind == SPRITE_START_GAME) {
        kind = GetNextMenu(menuEnable, -1, 0) + SPRITE_MENU_OFFSET;
      }
      else
        kind = GetNextMenu(menuEnable, kind - SPRITE_MENU_OFFSET, 0) + SPRITE_MENU_OFFSET;
      point = OPN_infoSprtBmp[kind].point;
      point.x = -OPN_infoSprtBmp[kind].w;
      memcpy(&lpcolorwk[16], OPN_tblPal2a, sizeof(OPN_tblPal2a));
      nSeqNo = 3;
    }
    kPosi = 1;
  }
  else if (nSeqNo == 3) {
    memcpy(&lpcolorwk[16], OPN_tblPal2a, sizeof(OPN_tblPal2a));
    point.x += 32;
    if (point.x >= OPN_infoSprtBmp[kind].point.x) {
      if (GetNextMenu(menuEnable, kind - SPRITE_MENU_OFFSET, 0) + SPRITE_MENU_OFFSET < kind) LArrow = 1;
      if (GetNextMenu(menuEnable, kind - SPRITE_MENU_OFFSET, 1) + SPRITE_MENU_OFFSET > kind) RArrow = 1;
      point = OPN_infoSprtBmp[kind].point;
      memcpy(&lpcolorwk[16], OPN_tblPal2, sizeof(OPN_tblPal2));
      nSeqNo = 6;
      timeOld = nTimerCunt;
    }
    kPosi = 1;
  }
  else if (nSeqNo == 4) {
    RArrow = LArrow = 0;
    memcpy(&lpcolorwk[16], OPN_tblPal2a, sizeof(OPN_tblPal2a));
    point.x -= 32;
    if (point.x < -OPN_infoSprtBmp[kind].w) {
      kind = GetNextMenu(menuEnable, kind - SPRITE_MENU_OFFSET, 1) + SPRITE_MENU_OFFSET;
      point = OPN_infoSprtBmp[kind].point;
      point.x = 320;
      memcpy(&lpcolorwk[16], OPN_tblPal2a, sizeof(OPN_tblPal2a));
      nSeqNo = 5;
    }
    kPosi = 1;
  }
  else if (nSeqNo == 5) {
    memcpy(&lpcolorwk[16], OPN_tblPal2a, sizeof(OPN_tblPal2a));
    point.x -= 32;
    if (point.x < OPN_infoSprtBmp[kind].point.x) {
      if (GetNextMenu(menuEnable, kind - SPRITE_MENU_OFFSET, 0) + SPRITE_MENU_OFFSET < kind) LArrow = 1;
      if (GetNextMenu(menuEnable, kind - SPRITE_MENU_OFFSET, 1) + SPRITE_MENU_OFFSET > kind) RArrow = 1;
      point = OPN_infoSprtBmp[kind].point;
      memcpy(&lpcolorwk[16], OPN_tblPal2, sizeof(OPN_tblPal2));
      nSeqNo = 6;
      timeOld = nTimerCunt;
    }
    kPosi = 1;
  }
  else if (nSeqNo == 6) {
    if (LArrow != 0) {
      leftArrowPoint.x = posiLeftArrow[arrowKind];
      leftArrowPoint.y = OPN_infoSprtBmp[SPRITE_LEFT_ARROW].point.y;
      lPosi = 1;
    }
    if (RArrow != 0) {
      rightArrowPoint.x = posiRightArrow[arrowKind];
      rightArrowPoint.y = OPN_infoSprtBmp[SPRITE_RIGHT_ARROW].point.y;
      rPosi = 1;
    }
    if ((nTimerCunt - timeOld) % 32 == 0) {
      if (++arrowKind > 2) arrowKind = 0;
    }

    if (swdata1.w & 20480) {
      if (kind - SPRITE_MENU_OFFSET == 0) {
        if (ChkNewSlot() == 0) {
          WaveRequest(28);
          return;
        }
      }

      nFadoTime = 21;
      nFadoValu = 32;
      nFadoSeqNum = 999;
      OESetSequenceNum(8);
      nMenuKind = kind - SPRITE_MENU_OFFSET;
    }
    else if (swdata1.w & 1024 && GetNextMenu(menuEnable, kind - SPRITE_MENU_OFFSET, 0) + SPRITE_MENU_OFFSET < kind) {
      timeOld = nTimerCunt;
      nSeqNo = 7;
      nSeqNoNext = 2;
    }
    else if (swdata1.w & 2048 && GetNextMenu(menuEnable, kind - SPRITE_MENU_OFFSET, 1) + SPRITE_MENU_OFFSET > kind) {
      timeOld = nTimerCunt;
      nSeqNo = 7;
      nSeqNoNext = 4;
    }
  }
  else if (nSeqNo == 7) {
    if (nTimerCunt - timeOld > 6) {
      nSeqNo = nSeqNoNext;
    }
  }
  if (LArrow != 0) ShowSprite(SPRITE_LEFT_ARROW);
  if (RArrow != 0) ShowSprite(SPRITE_RIGHT_ARROW);
  if (nSeqNo != 1) ShowSprite(kind);

  if (kPosi != 0) {
    shownSprites[kind][1] = point.x;
    shownSprites[kind][2] = point.y;
  }
  if (lPosi != 0) {
    shownSprites[SPRITE_LEFT_ARROW][1] = leftArrowPoint.x;
    shownSprites[SPRITE_LEFT_ARROW][2] = leftArrowPoint.y;
  }
  if (rPosi != 0) {
    shownSprites[SPRITE_RIGHT_ARROW][1] = rightArrowPoint.x;
    shownSprites[SPRITE_RIGHT_ARROW][2] = rightArrowPoint.y;
  }
}


static void OETitleSta(void) {
  memset(shownSprites, 0, sizeof(shownSprites));
  if (nTimerCunt == 0) {
    shownGrids[1] = 1;
    bDrawDisable = 1;
    nFadoTime = 21;
    nFadoValu = 32;
    nFadoSeqNum = 7;
    bFadePaletDisable[3] = 1;
    OESetSequenceNum(9);
  }
  OESprCreate(7);
  OESprCreate(11);
}


static void OETitle(void) {
  memset(shownSprites, 0, sizeof(shownSprites));
  OESprCreate(7);
  if (nTimerCunt == 0) {
	workPalet[2][0].peBlue = 96;
	lpcolorwk[32].peBlue = 96;
    shownGrids[2] = 1;
  }
  OEUpdateHand();
  OEUpdateMayu();
  OEUpdatePlanet();
  OEUpdateMizu();
  OEUpdateKumo();
  OEUpdateMsg();
}


static void OEFadeOut(void) {
  int i, j;
  static int colorNum;

  if (nTimerCunt == 0) {
    memcpy(workPalet[0], OPN_tblPal1, sizeof(workPalet[0]));
    memcpy(workPalet[1], OPN_tblPal2, sizeof(workPalet[1]));
    memcpy(workPalet[2], OPN_tblPal3, sizeof(workPalet[2]));
    memcpy(workPalet[3], OPN_tblPal4, sizeof(workPalet[3]));
    colorNum = 0;
  }
  else if (nTimerCunt == nFadoTime) {
    bFadePaletDisable[0] = bFadePaletDisable[1] = bFadePaletDisable[2] = bFadePaletDisable[3] = 0;
    OESetSequenceNum(nFadoSeqNum);
  }
  else {
    for (i = 0; i < 4; ++i) {
      for (j = 0; j < 16; ++j) {
        if (workPalet[i][j].peRed > nFadoValu) workPalet[i][j].peRed -= nFadoValu;
        else workPalet[i][j].peRed = 0;
        if (workPalet[i][j].peRed == 0) {
          if (workPalet[i][j].peGreen > nFadoValu) workPalet[i][j].peGreen -= nFadoValu;
          else workPalet[i][j].peGreen = 0;
          if (workPalet[i][j].peGreen == 0) {
            if (workPalet[i][j].peBlue > nFadoValu) workPalet[i][j].peBlue -= nFadoValu;
            else workPalet[i][j].peBlue = 0;
          }
        }
      }
      if (bFadePaletDisable[i] == 0) memcpy(&lpcolorwk[i * 16], workPalet[i], sizeof(workPalet[i]));
    }
  }
}


static void OEFadeIn(void) {
  int n, j;
  PALETTEENTRY* lpPal;

  memset(shownSprites, 0, sizeof(shownSprites));
  if (nFadoSeqNum == 7) {
    OESprCreate(7);
    OESprCreate(11);
  }

  if (nTimerCunt == nFadoTime) {
    memcpy(&lpcolorwk[0], OPN_tblPal1, sizeof(OPN_tblPal1));
    memcpy(&lpcolorwk[16], OPN_tblPal2, sizeof(OPN_tblPal2));
    memcpy(&lpcolorwk[32], OPN_tblPal3, sizeof(OPN_tblPal3));
    memcpy(&lpcolorwk[48], OPN_tblPal4, sizeof(OPN_tblPal4));
    bFadePaletDisable[0] = bFadePaletDisable[1] = bFadePaletDisable[2] = bFadePaletDisable[3] = 0;
    OESetSequenceNum(nFadoSeqNum);
  }
  else {
    bDrawDisable = 0;
    if (nFadoValu * nTimerCunt < 256) {
      for (n = 0; n < 4; ++n) {
        switch (n) {
          case 0: lpPal = OPN_tblPal1; break;
          case 1: lpPal = OPN_tblPal2; break;
          case 2: lpPal = OPN_tblPal3; break;
          case 3: lpPal = OPN_tblPal4; break;
        }
        for (j = 0; j < 16; ++j) {
          workPalet[n][j].peRed = lpPal[j].peRed > 224 - nFadoValu * nTimerCunt ? lpPal[j].peRed : 224 - nFadoValu * nTimerCunt;
          workPalet[n][j].peGreen = lpPal[j].peGreen > 224 - nFadoValu * nTimerCunt ? lpPal[j].peGreen : 224 - nFadoValu * nTimerCunt;
          workPalet[n][j].peBlue = lpPal[j].peBlue > 224 - nFadoValu * nTimerCunt ? lpPal[j].peBlue : 224 - nFadoValu * nTimerCunt;
          workPalet[n][j].peFlags = lpPal[j].peFlags;
        }
        if (bFadePaletDisable[n] == 0) memcpy(&lpcolorwk[n * 16], workPalet[n], sizeof(workPalet[n]));
      }
    }
  }
}


static void OEOpenSta(void) {
  if (nTimerCunt == 0) {
	workPalet[2][0].peBlue = 0;
	lpcolorwk[32].peBlue = 0;
    shownGrids[0] = 1;
    if (bFirstTitle != 0) {
      OESetSequenceNum(2);
      bFirstTitle = 0;
    }
    else OESetSequenceNum(5);
  }
}


static void OESegaLogo(void) {
  memset(shownSprites, 0, sizeof(shownSprites));
  shownGrids[0] = 1;
  if (nTimerCunt == 0) {
    memcpy(&lpcolorwk[0], OPN_tblPal1a, sizeof(OPN_tblPal1a));
  }
  else if (nTimerCunt == 90) {
    OESetSequenceNum(3);
    memcpy(&lpcolorwk[0], OPN_tblPal1, sizeof(OPN_tblPal1));
  }
  else OESprCreate(1);
}


static void OEDark(void) {
  memset(shownSprites, 0, sizeof(shownSprites));
  if (nTimerCunt == 30) {
    OESetSequenceNum(5);
  }
}


static void OESonic(void) {
  memset(shownSprites, 0, sizeof(shownSprites));
  if (nTimerCunt == 0) {
    CDPlay(26);
  }
  else if (nTimerCunt < 30) {
    OESprCreate(2);
  }
  else if (nTimerCunt < 32) {
    OESprCreate(3);
  }
  else if (nTimerCunt < 35) {
    OESprCreate(4);
  }
  else if (nTimerCunt < 38) {
    OESprCreate(5);
  }
  else {
    OESetSequenceNum(6);
  }
}


static int OEEnd(void) {
  int ret = 0;

  if (nTimerCunt == 0) {
    CDPause(2);
    switch (nMenuKind) {
      case 0:
        ret = 1;
        break;
      case 1:
        ret = 2;
        break;
      case 2:
        ret = 3;
        break;
      case 3:
        ret = 4;
        break;
      case 4:
        ret = 5;
        break;
      case 5:
        ret = 6;
        break;
      case 7:
        ret = 21;
        break;
	  case 8:
        ret = 7;
        break;
      case 9:
        ret = 13;
        break;
      case 10:
        ret = 14;
        break;
      case 11:
        ret = 20;
        break;

      case 6:
        ret = 22;
        break;
    }
  }

  return ret;
}


static void OESprCreate(unsigned short timing) {
  int i;

  for (i = 0; i < 35; ++i) {
    if (timing == OPN_infoSprtBmp[i].timing) {
      ShowSprite(i);
    }
  }
}


static void ShowSprite(int index) {
  shownSprites[index][0] = 1;
  shownSprites[index][1] = OPN_infoSprtBmp[index].point.x;
  shownSprites[index][2] = OPN_infoSprtBmp[index].point.y;
}
