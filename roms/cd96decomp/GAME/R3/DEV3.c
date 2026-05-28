#include "../EQU.h"
#include "DEV3.h"
#include "../../services.h"
#include "../DEV.h"

map_init_data z3cmapinittbl = { 0, 0, 0, 3, 2, 0, 0, 7, 7, 129 };
map_init_data z32amapinittbl = { 0, 0, 0, 3, 2, 0, 0, 5, 5, 129 };
static int drum_re0cg[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static int drum_re1cg[6] = { 10, 11, 12, 13, 14, 15 };
static int drum_no0cg[10] = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
static int drum_no1cg[6] = { 26, 27, 28, 29, 30, 31 };
static int drumgb_re0cg[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
static int drumgb_re1cg[8] = { 10, 11, 12, 13, 14, 15, 16, 17 };
static int drumgb_no0cg[10] = { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 };
static int drumgb_no1cg[8] = { 28, 29, 30, 31, 32, 33, 34, 35 };
static tile_changes tbl_drum00 = { 2, 0, { { 10, 0 }, { 10, 1 } }, { drum_no0cg, drum_re0cg }, 436 };
static tile_changes tbl_drum01 = { 2, 0, { { 10, 0 }, { 10, 1 } }, { drum_no1cg, drum_re1cg }, 462 };
static tile_changes tbl_drumg00 = { 2, 0, { { 10, 0 }, { 10, 1 } }, { drumgb_no0cg, drumgb_re0cg }, 438 };
static tile_changes tbl_drumg01 = { 2, 0, { { 10, 0 }, { 10, 1 } }, { drumgb_no1cg, drumgb_re1cg }, 464 };
static tile_changes tbl_drumb00 = { 2, 0, { { 10, 0 }, { 10, 1 } }, { drumgb_no0cg, drumgb_re0cg }, 417 };
static tile_changes tbl_drumb01 = { 2, 0, { { 10, 0 }, { 10, 1 } }, { drumgb_no1cg, drumgb_re1cg }, 443 };


void z32a_cg_change(void) {
  unsigned char *pcgchgtim, *pcgchgcnt;
  int i, playsubdma[16], top;

  pcgchgtim = cgchgtim;
  pcgchgcnt = cgchgcnt;

  if (cg_chg1(&tbl_drum00, 9, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 10; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(&tbl_drum01, 5, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 6; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }
}


void z32c_cg_change(void) {
  unsigned char *pcgchgtim, *pcgchgcnt;
  int i, playsubdma[16], top;

  pcgchgtim = cgchgtim;
  pcgchgcnt = cgchgcnt;

  if (cg_chg1(&tbl_drumg00, 9, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 10; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(&tbl_drumg01, 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 8; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }
}


void z32d_cg_change(void) {
  unsigned char *pcgchgtim, *pcgchgcnt;
  int i, playsubdma[16], top;

  pcgchgtim = cgchgtim;
  pcgchgcnt = cgchgcnt;

  if (cg_chg1(&tbl_drumb00, 9, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 10; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(&tbl_drumb01, 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 8; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }
}
