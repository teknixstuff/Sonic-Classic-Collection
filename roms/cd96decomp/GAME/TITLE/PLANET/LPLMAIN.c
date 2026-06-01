#include "../../EQU.h"
#include "../../SPM_EQU.h"
#include "LPL_TYPES.h"
#include "SPM_EQU.h"
#include "LPLMAIN.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../boxreader.h"
#include "../../../services.h"
#include "../../COL.h"
#include "ACTM.h"
#include "ASCIISET.h"
#include "KAITEN.h"
#include "PLS.h"

static void ram_clear(void);
static void cgdata_unlze(void);
static void kaiten_req(void);
static void m2copy(void);
static void cgchange_chk(void);
static void lp_makeup(void);
static int init_dsp(void);
static void end_proc(void);
static void prg_init(void);
static void patchg_init(void);
static void prgend_chk(void);
static void cgdata_change(void);
static void SubCpuMain(void);
static void cgmwrt_a(void);
static void cgmwrt_b(void);
static void cd_call(void);

static char* ScrAMapFileName[3] =
{
  "TITLE/PLANET/MAP/LP.MAP",
  "TITLE/PLANET/MAP/LPG.MAP",
  "TITLE/PLANET/MAP/LPB.MAP"
};
static int InitMode;
static int MakeupMode;
static char ScrBMapFileName[26] = "TITLE/PLANET/MAP/LPBS.MAP";
static unsigned int bGameInit = 1;
extern PALETTEENTRY init_col[];
static short ScrBMap[704];
extern short* funka_map_tbl[];
extern short funka_timetbl[];
extern PALETTEENTRY ascii_col[];
extern PALETTEENTRY sprite_col1[];
extern PALETTEENTRY** lp_coltbl[];
extern short lpl_lpbs_timer[];
extern PALETTEENTRY* sprite_color[];
static short DATable[39] =
{
   3, 36,  4,  5,  6, 37,  7,  8,  9, 38,
  10, 11, 12, 39, 13, 14, 15, 40, 16, 17,
  18, 41, 19, 20, 21, 42, 22, 23, 25, 33,
  31, 28, 24, 30, 29, 26, 32, 34, 35
};
static unsigned int hSmAdr;
static unsigned int hWordRAM;






















































































































void lplgame_init(void) {
  int x, y;
  short s;
  short* pSmap;
  PALETTEENTRY *lpSrc, *lpDst;
  int i;
  unsigned int ProcEnd;
  FILE* hf;

  MakeupMode = 0;
  InitMode = 0;
  bGameInit = 1;

  void* aMap_data = NULL;
  int aMap_size = box_read(&aMap_data, ScrAMapFileName[0]);
  if (aMap_size < 1) {
	  fprintf(stderr, "Could not read %s, error %i.\n", ScrAMapFileName[0], aMap_size);
    abort();
  }
  else
  {
    void* aMap_data_start = aMap_data;
    pSmap = (short*)sm_adr0;
    for (y = 0; y < 7; ++y)
    {
      for (x = 0; x < 8; ++x)
      {
        if (aMap_size - (aMap_data - aMap_data_start) < 2)
        {
          free(aMap_data_start);
          return;
        }
        memcpy(&s, aMap_data, sizeof(s));
        aMap_data += sizeof(s);
        *pSmap++ = s;
      }
      while (x < 10) *pSmap++ = 0, ++x;
    }
    free(aMap_data_start);
  }

  memset(ScrBMap, 0, sizeof(ScrBMap));
  void* bMap_data = NULL;
  int bMap_size = box_read(&aMap_data, ScrBMapFileName);
  if (bMap_size < 1) {
	  fprintf(stderr, "Could not read %s, error %i.\n", ScrBMapFileName, aMap_size);
    abort();
  }
  else {
    memcpy(ScrBMap, bMap_data, bMap_size < sizeof(ScrBMap) ? bMap_size : sizeof(ScrBMap));
    free(bMap_data);
  }





  ProcEnd = 0;
  do
  {
    switch (InitMode)
    {



      case 0:
        lplWorkRamClear();

        comdata_m0 = 0;
        comdata_m1 = 0;
        comdata_m2 = 0;
        comdata_m3 = 0;
        comdata_m4 = 0;
        comdata_m5 = 0;
        comdata_m6 = 0;
        comdata_m7 = 0;
        swdata1.w = 32768;
        main_lpcnt = 1;




        comdata_s0 = 0;
        comdata_s1 = 0;
        comdata_s2 = 0;
        comdata_s3 = 0;
        comdata_s4 = 0;
        comdata_s5 = 0;
        comdata_s6 = 0;
        comdata_s7 = 0;
        comflag_s &= 3;
        ram_clear();
        cgdata_unlze();




        patchg_init();

        cgmwrt_a();
        cgmwrt_b();

        flash_flg = 1;
      case 1:
      case 2:
      case 3:
      case 4:
        if (init_dsp() == 0) break;
        comflag_m = 0;
        ProcEnd = 1;

        break;

      case 5:
        prg_init();
        lpSrc = init_col;
        lpDst = colorwk2;
        for (i = 0; i < 64; ++i) *lpDst++ = *lpSrc++;
        fadein();

      default:
        ProcEnd = 1;
    }

    v_int();
  } while (ProcEnd == 0);
  CDPlay(33);
  bGameInit = 0;

}






int lplgame(void) {
  int RetMode;

  RetMode = 0;
  switch (ProcMode)
  {
    case 0:
      if (main_lpcnt < 0)
      {
        main_lpcnt = 1;
        intmode = 0;
      }
      kaiten_req();
      sprascii();
      lplaction();
      SubCpuMain();
      ++ProcMode;
      break;

    case 1:
      ++intmode;
      sprascii();
      lplaction();
      ++ProcMode;
      break;

    case 2:
      set_asciicg();
      m2copy();
      cgchange_chk();
      if (comflag_s & 32)
      {
        MakeupMode = 0;
        lp_makeup();
      }
      else
      {
        ++ProcMode;
      }
      ++ProcMode;
      break;

    case 3:
      lp_makeup();
      if (!(comflag_m & 32))
      {
        comflag_s &= 223;
        comflag_s |= 16;
      }
      if (MakeupMode < 0) ++ProcMode;
      break;

    case 4:
      if (comflag_s & 64)
      {
        prgend_chk();
        ++ProcMode;
      }
      else
      {
        --main_lpcnt;
        ++intmode;
        ProcMode = 0;
      }
      break;

    case 5:
      comflag_m = 0;
      comflag_s = 0;
      RetMode = -1;
      break;
  }

  v_int();
  return RetMode;
}




static void ram_clear(void) {}



static void cgdata_unlze(void) {}



static void kaiten_req(void) {}



static void m2copy(void) {}

static void cgchange_chk(void) {
  short fPatnoWk, *pMaptbl, *pWkadr, wk, funka_off;
  int i, j;

  switch (lplanet_no)
  {
    case 0:
    case 1:
      funka_off = 620;
      break;

    case 2:
      funka_off = 720;
      break;

    default:
      return;
  }
  if (funka_pctimer == 0)
  {
    if (funka_patno >= 12) funka_patno = 0;
    fPatnoWk = funka_patno;
    funka_pctimer = funka_timetbl[fPatnoWk];
    ++funka_patno;
    pMaptbl = funka_map_tbl[fPatnoWk];
    pWkadr = (short*)sm_adr0 + 6;
    for (i = 0; i < 2; ++i)
    {
      for (j = 0; j < 2; ++j)
      {
        if ((wk = *pMaptbl++) != 0) wk += funka_off;
        *pWkadr++ = wk;
        SetStampGrid(-1, j + 6, i, wk, 0);
      }
      pWkadr += 126;
    }
  }

}

static void lp_makeup(void) {
  switch (MakeupMode)
  {
    case 0:
      flashout();
      ++MakeupMode;
      break;

    case 1:
      memset(lplactwk, 0, 960);
      prg_init();
      comflag_m &= 223;
      kaiten_req();
      m2copy();
      SubCpuMain();
      if (comflag_s & 64)
      {
        MakeupMode = -1;
      }
      else
        ++MakeupMode;
      break;

    case 2:
      intmode = 0;
      kaiten_req();
      m2copy();
      SubCpuMain();
      if (comflag_s & 64)
      {
        MakeupMode = -1;
      }
      else
        ++MakeupMode;
      break;

    case 3:
      intmode = 1;
      if (comflag_s & 64)
      {
        MakeupMode = -1;
      }
      else
        ++MakeupMode;
      break;

    case 4:
      intmode = 2;
      kaiten_req();
      m2copy();
      SubCpuMain();
      if (comflag_s & 64)
      {
        MakeupMode = -1;
      }
      else
        ++MakeupMode;
      break;

    case 5:
      intmode = 3;
      if (comflag_s & 64)
      {
        MakeupMode = -1;
      }
      else
        ++MakeupMode;
      break;

    case 6:
      music_selflg &= 254;
      actset_flg = 0;
      flashin();
      ++MakeupMode;
      break;

    case 7:
      main_lpcnt = 0;
      intmode = -1;
      MakeupMode = -1;
      break;

    default:
      MakeupMode = -1;
  }


}

static int init_dsp(void) {
  switch (InitMode)
  {
    case 0:
      kaiten_req();
      m2copy();
      SubCpuMain();
      cgchange_chk();
      ++InitMode;
      break;

    case 1:
      intmode = 1;
      if (comflag_s & 64) end_proc();
      ++InitMode;
      break;

    case 2:
      kaiten_req();
      m2copy();
      SubCpuMain();
      cgchange_chk();
    case 3:
      ++intmode;
      ++InitMode;
      break;

    case 4:
      if (comflag_s & 64) end_proc();
      else ++InitMode;
  }

  return 0;
}

static void end_proc(void) {
  flash_flg = 1;
  fadeout();
}

static void prg_init(void) {
  PALETTEENTRY *lpPlCol, *lpBkgCol, *lpDst;
  int i;

  lpPlCol = *lp_coltbl[lplanet_no * 2];
  lpBkgCol = *lp_coltbl[lplanet_no * 2 + 1];
  lpDst = colorwk2;
  for (i = 0; i < 16; ++i) *lpDst++ = *lpBkgCol++;
  for (i = 0; i < 16; ++i) *lpDst++ = *lpPlCol++;
  lpPlCol = sprite_col1;
  for (i = 0; i < 16; ++i) *lpDst++ = *lpPlCol++;
  lpPlCol = ascii_col;
  for (i = 0; i < 16; ++i) *lpDst++ = *lpPlCol++;
  patchg_init();
}

static void patchg_init(void) {
  short *pMapwk, *pMapadr, funka_off;
  int i, wk;

  colorno = 0;
  coltimer = lpl_lpbs_timer[0];
  funka_patno = 0;


  funka_pctimer = 0;
  pMapwk = funka_map_tbl[0];
  pMapadr = (short*)sm_adr0 + 6;
  switch (lplanet_no)
  {
    case 0:
    case 1:
      funka_off = 620;
      break;

    case 2:
      funka_off = 720;
      break;

    default:
      funka_off = 0;
  }
  for (i = 0; i < 2; ++i)
  {
    wk = funka_off + *pMapwk++;
    *pMapadr++ = wk;
    SetStampGrid(-1, 6, i, wk, 0);
    wk = funka_off + *pMapwk++;
    *pMapadr++ = wk;
    SetStampGrid(-1, 7, i, wk, 0);
    pMapadr += 127;
  }
  spr_coltimer = 5;
  spr_colno = 0;
}

static void prgend_chk(void) {
  flash_flg = 1;
  fadeout();


}

static void cgdata_change(void) {
  unsigned short *pA0, *pA1, *pA2, *pSmap, s, offs;
  int i, j, x, y;
  FILE* hf;

  if (comdata_m5 != 3)
  {
    unsigned char* aMap_data = NULL;
    int aMap_size = box_read((void**)&aMap_data, ScrAMapFileName[comdata_m5]);
    if (aMap_size < 1) {
  	  fprintf(stderr, "Could not read %s, error %i.\n", ScrAMapFileName[comdata_m5], aMap_size);
      abort();
    }

    switch (comdata_m5)
    {
      case 0:
        offs = 0;
        break;

      case 1:
        offs = 200;
        break;

      case 2:
        offs = 416;
        break;

      default:
        offs = 0;
        break;
    }
    unsigned char* aMap_data_start = aMap_data;
    pSmap = (short*)sm_adr0;
    for (y = 0; y < 7; ++y)
    {
      for (x = 0; x < 8; ++x)
      {
        if (aMap_size - (aMap_data - aMap_data_start) < 2)
        {
          free(aMap_data_start);
          return;
        }
        memcpy(&s, aMap_data, sizeof(s));
        aMap_data += sizeof(s);
        if (s != 0) s += offs;
        *pSmap++ = s;
      }
      while (x < 10) *pSmap++ = 0, ++x;
    }
    free(aMap_data_start);

    switch (lplanet_no)
    {
      case 0:
      case 1:
        offs = 620;
        break;

      case 2:
        offs = 720;
        break;

      default:
        offs = 0;
    }
    pA0 = (unsigned short*)funka_map_tbl[0];
    pA2 = sm_adr0 + 6;
    for (i = 1; i >= 0; --i)
    {
      pA1 = pA2;
      for (j = 1; j >= 0; --j)
      {
        s = *pA0++;
        if (s != 0) s += offs;
        *pA1++ = s;
      }
      pA2 += 128;
    }
    pSmap = sm_adr0;
    for (y = 0; y < 7; ++y)
    {
      for (x = 0; x < 10; ++x)
      {
        SetStampGrid(-1, x, y, *pSmap, 0);
        ++pSmap;
      }
    }
  }

}

static void SubCpuMain(void) {
  if (bGameInit == 0) lplplayer();

  if (comflag_s & 16)
  {
    cd_call();
    cgdata_change();
    comflag_s &= 239;
  }
  kaiten0();
  comflag_s &= 223;
  if (comflag_m & 32) comflag_s |= 32;
  else comflag_s &= 223;

}

void v_int(void) {
  PALETTEENTRY *lpPlanet, *lpBkg, *lpDst, *lpSpr;
  int i;

  switch (intmode)
  {
    case 0:



    case 1:



    case 2:



    case 3:



    default:
      if (flash_flg == 0)
      {
        if (--coltimer == 0)
        {
          if (colorno >= 31) colorno = 0;
          coltimer = lpl_lpbs_timer[colorno];
          lpPlanet = lp_coltbl[lplanet_no * 2][colorno];
          lpBkg = lp_coltbl[lplanet_no * 2 + 1][colorno];
          ++colorno;
          lpDst = lpcolorwk;
          for (i = 0; i < 16; ++i) *lpDst++ = *lpBkg++;
          for (i = 0; i < 16; ++i) *lpDst++ = *lpPlanet++;
        }
        if (--spr_coltimer <= 0)
        {
          lpSpr = sprite_color[spr_colno / 2];
          lpDst = lpcolorwk + 32;
          for (i = 0; i < 16; ++i) *lpDst++ = *lpSpr++;
          if (spr_colno == 0) spr_colno = 2;
          else spr_colno = 0;
          spr_coltimer = 5;
        }
      }
  }
  if (funka_pctimer > 0) --funka_pctimer;
  if (gmtime0 != 0) --gmtime0;
  ++gmtime1;
}

static void cgmwrt_a(void) {
  int x, y;

  for (y = 0; y < 3; ++y)
  {
    for (x = 0; x < 40; ++x)
    {
      SetGrid(0, x, y, 32818, 0);
    }
  }
  for (y += 22; y < 28; ++y)
  {
    for (x = 0; x < 40; ++x)
    {
      SetGrid(0, x, y, 32818, 0);
    }
  }

}

static void cgmwrt_b(void) {
  short* pA1;
  int x, y, i;

  for (y = 0; y < 3; ++y)
  {
    for (x = 0; x < 40; ++x)
    {
      SetGrid(1, x, y, 49, 0);
    }
  }
  pA1 = ScrBMap;
  for ( ; y < 25; ++y)
  {
    for (x = 0; x < 32; ++x)
    {
      SetGrid(0, x, y, *pA1, 0);
      ++pA1;
    }
    pA1 -= 11;
    for (i = 1; i <= 8; ++i)
    {
      SetGrid(0, x, y, pA1[i], 0);
      ++x;
    }
    pA1 += 11;
  }
  for ( ; y < 28; ++y)
  {
    for (x = 0; x < 40; ++x)
    {
      SetGrid(1, x, y, 49, 0);
    }
  }

}











































static void cd_call(void) {
  CDPlay(DATable[comdata_m4]);
}
