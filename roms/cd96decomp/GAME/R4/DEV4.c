#include "../EQU.h"
#include "DEV4.h"
#include "../../services.h"
#include "../DEV.h"

static int fire0cg[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
static int fire1cg[16] = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
static int fire2cg[16] = { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47 };
static int fire3cg[16] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63 };
static int fire4cg[16] = { 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79 };
static int fire5cg[16] = { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95 };
static int fire6cg[16] = { 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111 };
static int fire7cg[16] = { 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127 };
static tile_changes tbl_fir0 = { 24, 0, { { 60, 0 }, {  8, 1 }, {  8, 2 }, {  8, 3 }, {  8, 4 }, {  8, 5 }, {  6, 6 }, {  6, 7 }, { 60, 0 }, {  8, 1 }, {  8, 2 }, {  8, 3 }, {  8, 4 }, {  8, 5 }, {  6, 6 }, {  6, 7 }, { 60, 0 }, {  8, 0 }, {  8, 0 }, {  8, 0 }, {  8, 0 }, {  8, 0 }, {  6, 0 }, {  6, 0 } }, { fire0cg, fire1cg, fire2cg, fire3cg, fire4cg, fire5cg, fire6cg, fire7cg }, 558 };
static tile_changes tbl_fir1 = { 24, 0, { { 60, 0 }, {  8, 1 }, {  8, 2 }, {  8, 3 }, {  8, 4 }, {  8, 5 }, {  6, 6 }, {  6, 7 }, { 60, 0 }, {  8, 0 }, {  8, 0 }, {  8, 0 }, {  8, 0 }, {  8, 0 }, {  6, 0 }, {  6, 0 }, { 60, 0 }, {  8, 1 }, {  8, 2 }, {  8, 3 }, {  8, 4 }, {  8, 5 }, {  6, 6 }, {  6, 7 } }, { fire0cg, fire1cg, fire2cg, fire3cg, fire4cg, fire5cg, fire6cg, fire7cg }, 574 };
static tile_changes tbl_fir2 = { 24, 0, { { 60, 0 }, {  8, 0 }, {  8, 0 }, {  8, 0 }, {  8, 0 }, {  8, 0 }, {  6, 0 }, {  6, 0 }, { 60, 0 }, {  8, 1 }, {  8, 2 }, {  8, 3 }, {  8, 4 }, {  8, 5 }, {  6, 6 }, {  6, 7 }, { 60, 0 }, {  8, 1 }, {  8, 2 }, {  8, 3 }, {  8, 4 }, {  8, 5 }, {  6, 6 }, {  6, 7 } }, { fire0cg, fire1cg, fire2cg, fire3cg, fire4cg, fire5cg, fire6cg, fire7cg }, 590 };


void z41a_cg_change(void) {
  unsigned char *pcgchgtim, *pcgchgcnt;
  int i, playsubdma[16], top;

  if (pauseflag.b.h) return;

  if (scra_h_posit.w.h >= 640 || scra_v_posit.w.h >= 352)
    return;

  pcgchgtim = cgchgtim;
  pcgchgcnt = cgchgcnt;

  if (cg_chg1(&tbl_fir0, 15, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 16; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(&tbl_fir1, 15, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 16; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(&tbl_fir2, 15, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 16; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }
}
