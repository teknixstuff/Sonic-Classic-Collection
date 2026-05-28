#include "../EQU.h"
#include "DEV6.h"
#include "../../services.h"
#include "../DEV.h"

static int nullcg[8];
static int sp1cg[4] = { 0, 1, 2, 3 };
static int alt_sp1cg[4] = { 1, 2, 3, 4 };
static int sp2cg[4] = { 4, 5, 6, 7 };
static int alt_sp2cg[4] = { 5, 6, 7, 8 };
static int t1cg[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
static int alt_t1cg[8] = { 9, 10, 11, 12, 13, 14, 15, 16 };
static int t2cg[8] = { 16, 17, 18, 19, 20, 21, 22, 23 };
static int alt_t2cg[8] = { 17, 18, 19, 20, 21, 22, 23, 24 };
static int t3cg[8] = { 24, 25, 26, 27, 28, 29, 30, 31 };
static int alt_t3cg[8] = { 25, 26, 27, 28, 29, 30, 31, 32 };
static int r01cg[4] = { 32, 33, 34, 35 };
static int alt_r01cg[4] = { 33, 34, 35, 36 };
static int r02cg[4] = { 36, 37, 38, 39 };
static int alt_r02cg[4] = { 37, 38, 39, 40 };
static int r03cg[4] = { 40, 41, 42, 43 };
static int alt_r03cg[4] = { 41, 42, 43, 44 };
static int r04cg[4] = { 44, 45, 46, 47 };
static int alt_r04cg[4] = { 45, 46, 47, 48 };
static tile_changes z6a_tbl_thund = { 3, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 } }, { t1cg, t2cg, t3cg }, 321 };
static tile_changes z6c_tbl_thund = { 3, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 } }, { alt_t1cg, alt_t2cg, alt_t3cg }, 347 };
static tile_changes z61b_tbl_thund = { 3, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 } }, { t1cg, t2cg, t3cg }, 374 };
static tile_changes z61d_tbl_thund = { 3, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 } }, { t1cg, t2cg, t3cg }, 380 };
static tile_changes z62b_tbl_thund = { 3, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 } }, { t1cg, t2cg, t3cg }, 333 };
static tile_changes z62d_tbl_thund = { 3, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 } }, { t1cg, t2cg, t3cg }, 446 };
static tile_changes z63d_tbl_thund = { 3, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 } }, { alt_t1cg, alt_t2cg, alt_t3cg }, 380 };
static tile_changes* tbls_thund[3][4] = {
  { &z61b_tbl_thund, &z6a_tbl_thund, &z61d_tbl_thund, &z6c_tbl_thund },
  { &z62b_tbl_thund, &z6a_tbl_thund, &z62d_tbl_thund, &z6c_tbl_thund },
  { 0, 0, &z63d_tbl_thund, &z6c_tbl_thund }
};
static tile_changes z6_tbl_null = { 3, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 } }, { nullcg, nullcg, nullcg }, 347 };
static tile_changes z63d_tbl_null = { 3, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 } }, { nullcg, nullcg, nullcg }, 380 };
static tile_changes* tbls_null[3][4] = {
  { 0, 0, 0, &z6_tbl_null },
  { 0, 0, 0, &z6_tbl_null },
  { 0, 0, &z63d_tbl_null, &z6_tbl_null }
};
static tile_changes z6a_tbl_sp = { 2, 0, { { 2, 0 }, { 2, 1 } }, { sp1cg, sp2cg }, 317 };
static tile_changes z6c_tbl_sp = { 2, 0, { { 2, 0 }, { 2, 1 } }, { alt_sp1cg, alt_sp2cg }, 343 };
static tile_changes z61b_tbl_sp = { 2, 0, { { 2, 0 }, { 2, 1 } }, { sp1cg, sp2cg }, 370 };
static tile_changes z61d_tbl_sp = { 2, 0, { { 2, 0 }, { 2, 1 } }, { sp1cg, sp2cg }, 376 };
static tile_changes z62b_tbl_sp = { 2, 0, { { 2, 0 }, { 2, 1 } }, { sp1cg, sp2cg }, 329 };
static tile_changes z62d_tbl_sp = { 2, 0, { { 2, 0 }, { 2, 1 } }, { sp1cg, sp2cg }, 442 };
static tile_changes z63d_tbl_sp = { 2, 0, { { 2, 0 }, { 2, 1 } }, { alt_sp1cg, alt_sp2cg }, 376 };
static tile_changes* tbls_sp[3][4] = {
  { &z61b_tbl_sp, &z6a_tbl_sp, &z61d_tbl_sp, &z6c_tbl_sp },
  { &z62b_tbl_sp, &z6a_tbl_sp, &z62d_tbl_sp, &z6c_tbl_sp },
  { 0, 0, &z63d_tbl_sp, &z6c_tbl_sp }
};
static tile_changes z6a_tbl_light = { 4, 0, { { 4, 0 }, { 9, 1 }, { 4, 2 }, { 15, 3 } }, { r01cg, r02cg, r03cg, r04cg }, 313 };
static tile_changes z61b_tbl_light = { 4, 0, { { 4, 0 }, { 9, 1 }, { 4, 2 }, { 15, 3 } }, { r01cg, r02cg, r03cg, r04cg }, 366 };
static tile_changes z61d_tbl_light = { 4, 0, { { 4, 0 }, { 9, 1 }, { 4, 2 }, { 15, 3 } }, { r01cg, r02cg, r03cg, r04cg }, 372 };
static tile_changes z62b_tbl_light = { 4, 0, { { 4, 0 }, { 9, 1 }, { 4, 2 }, { 15, 3 } }, { r01cg, r02cg, r03cg, r04cg }, 325 };
static tile_changes z62d_tbl_light = { 4, 0, { { 4, 0 }, { 9, 1 }, { 4, 2 }, { 15, 3 } }, { r01cg, r02cg, r03cg, r04cg }, 438 };
static tile_changes z63d_tbl_light = { 4, 0, { { 4, 0 }, { 9, 1 }, { 4, 2 }, { 15, 3 } }, { alt_r01cg, alt_r02cg, alt_r03cg, alt_r04cg }, 372 };
static tile_changes* tbls_light[3][4] = {
  { &z61b_tbl_light, &z6a_tbl_light, &z61d_tbl_light, 0 },
  { &z62b_tbl_light, &z6a_tbl_light, &z62d_tbl_light, 0 },
  { 0, 0, &z63d_tbl_light, 0 }
};


void z6_cg_change(void) {
  unsigned char *pcgchgtim, *pcgchgcnt;
  int i, playsubdma[16], top;

  pcgchgtim = cgchgtim;
  pcgchgcnt = cgchgcnt;

  if (cg_chg1(tbls_thund[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 8; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(tbls_sp[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 3, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 4; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(tbls_light[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 3, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 4; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }
}


void z6c_cg_change(void) {
  unsigned char *pcgchgtim, *pcgchgcnt;
  int i, playsubdma[16], top;

  pcgchgtim = cgchgtim;
  pcgchgcnt = cgchgcnt;

  if (cg_chg1(tbls_sp[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 3, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 4; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  --cgchgtim[2];
  if ((char)cgchgtim[2] < 0) {
    cgchgtim[2] ^= 1;
    if (cgchgtim[2] == 0) cgchgtim[2] = 90;
    else cgchgtim[2] = 30;
  }

  if (cgchgtim[2] != 0) {
    if (cg_chg1(tbls_thund[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
      for (i = 0; i < 8; ++i, ++top) {
        ChangeTileBmp(top, playsubdma[i]);
      }
    }
    return;
  }

  if (cg_chg1(tbls_null[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 8; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }
}


void z63_cg_change(void) {
  unsigned char *pcgchgtim, *pcgchgcnt;
  int i, playsubdma[16], top;

  pcgchgtim = cgchgtim;
  pcgchgcnt = cgchgcnt;

  if (bossflag & 64) {
    bossflag |= 128;
    if (cg_chg1(tbls_null[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
      for (i = 0; i < 8; ++i, ++top) {
        ChangeTileBmp(top, playsubdma[i]);
      }
    }
    goto label1;
  }

  if (!(bossflag & 128)) {
    if (cg_chg1(tbls_thund[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
      for (i = 0; i < 8; ++i, ++top) {
        ChangeTileBmp(top, playsubdma[i]);
      }
    }
    goto label1;
  }

  if (cg_chg1(tbls_null[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 8; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

label1:
  bossflag &= 191;

  if (cg_chg1(tbls_sp[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 3, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 4; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (generate_flag == 0 && cg_chg1(tbls_light[2][2], 3, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 4; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }
}
