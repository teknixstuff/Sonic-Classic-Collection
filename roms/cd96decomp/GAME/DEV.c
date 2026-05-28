#include "EQU.h"
#include "DEV.h"
#include "R3/DEV3.h"
#include "R4/DEV4.h"
#include "R6/DEV6.h"
#include "R8/DEV8.h"

extern map_init_data z1amapinittbl;
extern map_init_data z3cmapinittbl;
extern map_init_data z32amapinittbl;
extern map_init_data z53cmapinittbl;
extern map_init_data z8mapinittbl;
extern map_init_data z82cmapinittbl;
extern map_init_data z82dmapinittbl;

static void no_cg_change(void);

map_init_data mapinittbl = { 0, 0, 0, 3, 2, 0, 0, 4, 4, 129 };
map_init_data* mapinittbls[7][3][4] = {
  {
    { &z1amapinittbl, &z1amapinittbl, &mapinittbl, &mapinittbl },
    { &z1amapinittbl, &z1amapinittbl, &mapinittbl, &mapinittbl },
    { 0, 0, &mapinittbl, &mapinittbl }
  },
  {
    { &mapinittbl, &mapinittbl, &mapinittbl, &z3cmapinittbl },
    { &mapinittbl, &z32amapinittbl, &mapinittbl, &z3cmapinittbl },
    { 0, 0, &mapinittbl, &mapinittbl }
  },
  {
    { &mapinittbl, &mapinittbl, &mapinittbl, &mapinittbl },
    { &mapinittbl, &mapinittbl, &mapinittbl, &mapinittbl },
    { 0, 0, &mapinittbl, &mapinittbl }
  },
  {
    { &mapinittbl, &mapinittbl, &mapinittbl, &mapinittbl },
    { &mapinittbl, &mapinittbl, &mapinittbl, &mapinittbl },
    { 0, 0, &mapinittbl, &z53cmapinittbl }
  },
  {
    { &mapinittbl, &mapinittbl, &mapinittbl, &mapinittbl },
    { &mapinittbl, &mapinittbl, &mapinittbl, &mapinittbl },
    { 0, 0, &mapinittbl, &mapinittbl }
  },
  {
    { &mapinittbl, &mapinittbl, &mapinittbl, &mapinittbl },
    { &mapinittbl, &mapinittbl, &mapinittbl, &mapinittbl },
    { 0, 0, &mapinittbl, &mapinittbl }
  },
  {
    { &mapinittbl, &mapinittbl, &mapinittbl, &mapinittbl },
    { &z8mapinittbl, &z8mapinittbl, &z82dmapinittbl, &z82cmapinittbl },
    { 0, 0, &z8mapinittbl, &z8mapinittbl }
  }
};


void cg_change(void) {
  static void(*cg_changes[7][3][4])(void) = {
    {
      { &no_cg_change, &no_cg_change, &no_cg_change, &no_cg_change },
      { &no_cg_change, &no_cg_change, &no_cg_change, &no_cg_change },
      { 0, 0, &no_cg_change, &no_cg_change }
    },
    {
      { &no_cg_change, &no_cg_change, &no_cg_change, &no_cg_change },
      { &no_cg_change, &z32a_cg_change, &z32d_cg_change, &z32c_cg_change },
      { 0, 0, &no_cg_change, &no_cg_change }
    },
    {
      { &no_cg_change, &z41a_cg_change, &no_cg_change, &no_cg_change },
      { &no_cg_change, &no_cg_change, &no_cg_change, &no_cg_change },
      { 0, 0, &no_cg_change, &no_cg_change }
    },
    {
      { &no_cg_change, &no_cg_change, &no_cg_change, &no_cg_change },
      { &no_cg_change, &no_cg_change, &no_cg_change, &no_cg_change },
      { 0, 0, &no_cg_change, &no_cg_change }
    },
    {
      { &z6_cg_change, &z6_cg_change, &z6_cg_change, &z6c_cg_change },
      { &z6_cg_change, &z6_cg_change, &z6_cg_change, &z6c_cg_change },
      { 0, 0, &z63_cg_change, &z63_cg_change }
    },
    {
      { &no_cg_change, &no_cg_change, &no_cg_change, &no_cg_change },
      { &no_cg_change, &no_cg_change, &no_cg_change, &no_cg_change },
      { 0, 0, &no_cg_change, &no_cg_change }
    },
    {
      { &no_cg_change, &z8_cg_change, &z8_cg_change, &z8_cg_change },
      { &z8_cg_change, &z8_cg_change, &z8_cg_change, &z8_cg_change },
      { 0, 0, &z8_cg_change, &z8_cg_change }
    }
  };

  cg_changes[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)]();
}


static void no_cg_change(void) {}


unsigned int cg_chg1(tile_changes* pTbl, int iNum, unsigned char** ppChgTim, unsigned char** ppChgCnt, int* BmpNo, int* TileStart) {
  int tblidx, *pNoTbl;
  char Timwk;

  if (pTbl == 0) {
    return 0;
  }

  Timwk = --**ppChgTim;
  if (Timwk >= 0) {
    ++*ppChgTim;
    ++*ppChgCnt;
    return 0;
  }

  tblidx = **ppChgCnt;
  if (++tblidx >= pTbl->chgcnt)
    tblidx = 0;

  **ppChgCnt = tblidx;
  **ppChgTim = pTbl->dattbl[tblidx].tim;

  tblidx = (short)pTbl->dattbl[tblidx].no;
  pNoTbl = pTbl->TileNoTbl[tblidx];

  for ( ; iNum >= 0; --iNum) {
    *BmpNo++ = *pNoTbl++;
  }

  ++*ppChgTim;
  ++*ppChgCnt;
  *TileStart = pTbl->TileStart;
  return 1;
}
