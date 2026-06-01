#include "../../EQU.h"
#include "../COMMON/SCORE_DATA_TYPES.h"
#include "THANKS_TYPES.h"
#include "GAME.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../boxreader.h"
#include "../../../services.h"
#include "../../IO.h"
#include "BM_M.h"
#include "ETC_M.h"
#include "IO.h"
#include "SPM.h"

static void v_int(void);

static PALETTEENTRY endingcol[64] = {
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0, 224, 1 },
  {  96,  96, 224, 1 }, { 128, 128, 224, 1 }, { 224, 224, 224, 1 }, { 160, 160, 160, 1 },
  { 128, 128, 128, 1 }, {  64,  64,  64, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, { 224, 224,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }
};
static unsigned short gEndingMesTimer;
extern bmp_info SprBmp[700];
score_data* lpScorData;
extern short end_timer;
extern short heart_tm;
extern short posetimer;
extern short colorno2;
extern short coltimer2;
extern short colorno;
extern short coltimer;
extern unsigned short thanks_lpbs_timer[32];
extern unsigned char quit_flg;
extern PALETTEENTRY* asc_coltbl[2];
extern PALETTEENTRY* lpbs_good[32];
extern short animal_timer;
extern unsigned char animal_flg;
extern sprite_status_thanks thanksactwk[66];
extern unsigned short* asc_maptbl[];


































































void thanksgame_init(void) {
  thanksWorkRamClear();

  swdata1.w = -4096;

  cgmwrt_a();
  cgmwrt_b();


  EndingMesColor();

  coltimer = thanks_lpbs_timer[0];
  colorno = 0;

  coltimer2 = 20;
  colorno2 = 1;

  posetimer = 1536;
  heart_tm = 1;

  end_timer = 10800;
}






int thanksgame(void) {


  if (EndingMes() != 0) return 0;
  if (gKeepWork.EndingMesType & 2) {
    return -1;
  }

  mainloop();

  v_int();

  if (quit_flg) return -1;
  return 0;
}



void cgmwrt_a(void) {
  int x, y, TileNo;
  short aMap[2048], *pMap;
  FILE* hf;

  memset(aMap, 0, sizeof(aMap));
  unsigned char* file_data = NULL;
  int file_size = box_read((void**)&file_data, "TITLE/THANKS/MAP/VA_MAP.BIN");
  if (file_size < 1) {
	  fprintf(stderr, "Could not read TITLE/THANKS/MAP/VA_MAP.BIN, error %i.\n", file_size);
    abort();
  }
  else {
    memcpy(aMap, file_data, file_size > sizeof(aMap) ? sizeof(aMap) : file_size);
    free(file_data);
  }
  for (y = 0; y < 28; ++y) {

    pMap = &aMap[y * 64];
    for (x = 0; x < 40; ++x) {

      TileNo = *pMap++;
      if (TileNo & 1023) TileNo += 174;
      if ((TileNo & 1023) >= 461) TileNo = 0;

      SetGrid(0, x, y, TileNo, 0);
    }
  }
}

void cgmwrt_b(void) {
  int x, y, TileNo;
  short bMap[2048], *pMap;
  FILE* hf;

  memset(bMap, 0, sizeof(bMap));
  unsigned char* file_data = NULL;
  int file_size = box_read((void**)&file_data, "TITLE/THANKS/MAP/VB_MAP.BIN");
  if (file_size < 1) {
	  fprintf(stderr, "Could not read TITLE/THANKS/MAP/VB_MAP.BIN, error %i.\n", file_size);
    abort();
  }
  else {
    memcpy(bMap, file_data, file_size > sizeof(bMap) ? sizeof(bMap) : file_size);
    free(file_data);
  }
  for (y = 0; y < 28; ++y) {

    pMap = &bMap[y * 64];
    for (x = 0; x < 40; ++x) {

      TileNo = *pMap++;
      if (TileNo & 1023) TileNo -= 154;
      if ((TileNo & 1023) >= 329) TileNo = 0;
      SetGrid(1, x, y, TileNo, 0);
    }
  }
}





static void v_int(void) {
  PALETTEENTRY *lpDst, *lpSpr;
  int_union ld0;
  short i;
  short d0;

  if (animal_flg == 2) {

    if (--animal_timer <= 0) {

      animal_flg = 0;
    }
  }
  if (--posetimer <= 0) {

    if (thanksactwk[0].ACT_NO) {

      animal_flg = 1;
    }
    animal_timer = 900;
    ld0.l = random2();
    ld0.l &= 32767;
    ld0.w.l = (int)ld0.w.l % 4096;
    ld0.w.l += 8192;
    posetimer = ld0.w.l;
  }


  --coltimer;
  if (coltimer <= 0) {

    if (colorno >= 31) {

      colorno = 0;
    }
    d0 = colorno;
    coltimer = thanks_lpbs_timer[d0];
    ++colorno;

    lpSpr = lpbs_good[d0];
    lpDst = lpcolorwk + 16;
    for (i = 0; i < 16; ++i) {

      *lpDst++ = *lpSpr++;
    }
  }

  --coltimer2;
  if (coltimer2 <= 0) {

    if (colorno2 >= 2) {

      colorno2 = 0;
    }
    coltimer2 = 20;
    d0 = colorno2;
    ++colorno2;

    lpSpr = asc_coltbl[d0];
    lpDst = lpcolorwk + 40;
    for (i = 0; i < 8; ++i) {

      *lpDst++ = *lpSpr++;
    }
  }


  if (--end_timer <= 0) {

    quit_flg = 1;
  }

}








void PutAscii(unsigned short c, unsigned short XPos, unsigned short YPos) {
  int vcellno, i;
  unsigned short* pMap;

  pMap = asc_maptbl[c];
  if (c == 27) {
    vcellno = 4;
  }
  else vcellno = 3;


  for (i = 0; i < vcellno; ++i) {
    SetGrid(0, XPos, YPos + i, *pMap++ + 32767 + 330, 0);
    SetGrid(0, XPos + 1, YPos + i, *pMap++ + 32767 + 330, 0);
  }
}


void EndingMesColor(void) {
  PALETTEENTRY *lpPeSrc, *lpPeDest;
  int i;

  lpPeSrc = endingcol;
  lpPeDest = lpcolorwk;
  for (i = 0; i < 64; ++i) {
    *lpPeDest++ = *lpPeSrc++;
  }
}

int EndingMes(void) {
  int i;

  ++gEndingMesTimer;
  if (gEndingMesTimer > 360) {
    gEndingMesTimer = 360;
    return 0;
  }









  if (gKeepWork.EndingMesType & 1) {
    switch (gEndingMesTimer) {

      case 1:
        EAsprset(224, 288, 76, 0, 0);
        break;

      case 180:
        EAsprset(208, 228, 77, 0, 0);
        break;
      case 360:
        if ((unsigned char)swdata1.b.l & 240) {
          vdpinit();
        }
        else {
          --gEndingMesTimer;
        }
        break;
    }
  }
  else if (gKeepWork.EndingMesType & 2) {
    switch (gEndingMesTimer) {

      case 1:
        EAsprset(252, 288, 75, 0, 0);
        break;

      case 180:
        EAsprset(208, 228, 77, 0, 0);
        break;
      case 360:
        if ((unsigned char)swdata1.b.l & 240) {


          for (i = 0; i < 64; ++i) {
            lpcolorwk[i].peRed = 0;
            lpcolorwk[i].peGreen = 0;
            lpcolorwk[i].peBlue = 0;
          }
        }
        else {
          --gEndingMesTimer;
        }
    }
  }

  return 1;
}
