#include "../EQU.h"
#include "DEV8.h"
#include "../../services.h"
#include "../DEV.h"

map_init_data z8mapinittbl = { 0, 0, 0, 3, 2, 0, 0, 5, 5, 129 };
map_init_data z82cmapinittbl = { 0, 0, 0, 3, 2, 0, 0, 6, 6, 129 };
map_init_data z82dmapinittbl = { 0, 0, 0, 3, 2, 0, 0, 10, 10, 129 };
static int pis1cg[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
static int pis2cg[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
static int pis3cg[8] = { 16, 17, 18, 19, 20, 21, 22, 23 };
static int com1cg[8] = { 24, 25, 26, 27, 28, 29, 30, 31 };
static int com2cg[8] = { 32, 33, 34, 35, 36, 37, 38, 39 };
static int com3cg[8] = { 40, 41, 42, 43, 44, 45, 46, 47 };
static int com4cg[8] = { 48, 49, 50, 51, 52, 53, 54, 55 };
static int mot1cg[16] = { 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71 };
static int mot2cg[16] = { 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 };
static int mot3cg[16] = { 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103 };
static int mot4cg[16] = { 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119 };
static int spo1cg[4] = { 120, 121, 122, 123 };
static int spo2cg[4] = { 124, 125, 126, 127 };
static int spo3cg[4] = { 128, 129, 130, 131 };
static int spo4cg[4] = { 132, 133, 134, 135 };
static int spo5cg[4] = { 136, 137, 138, 139 };
static int spo6cg[4] = { 140, 141, 142, 143 };
static int spo7cg[4] = { 144, 145, 146, 147 };
static int bal1cg[16] = { 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163 };
static int bal2cg[16] = { 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179 };
static int bal3cg[16] = { 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195 };
static int bal4cg[16] = { 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211 };
static int z82apan1cg[4] = { 148, 149, 150, 151 };
static int z82apan2cg[4] = { 152, 153, 154, 155 };
static int z82apan3cg[4] = { 156, 157, 158, 159 };
static int z82apan4cg[4] = { 160, 161, 162, 163 };
static int z82apan5cg[4] = { 164, 165, 166, 167 };
static int z82apan6cg[4] = { 168, 169, 170, 171 };
static int z82bpan1cg[4] = { 0, 1, 2, 3 };
static int z82bpan2cg[4] = { 4, 5, 6, 7 };
static int z82bpan3cg[4] = { 8, 9, 10, 11 };
static int z82bpan4cg[4] = { 12, 13, 14, 15 };
static int z82bpan5cg[4] = { 16, 17, 18, 19 };
static int z82bpan6cg[4] = { 20, 21, 22, 23 };
static int z82cpan1cg[4] = { 120, 121, 122, 123 };
static int z82cpan2cg[4] = { 124, 125, 126, 127 };
static int z82cpan3cg[4] = { 128, 129, 130, 131 };
static int z82cpan4cg[4] = { 132, 133, 134, 135 };
static int z82cpan5cg[4] = { 136, 137, 138, 139 };
static int z82cpan6cg[4] = { 140, 141, 142, 143 };
static tile_changes z81a_tbl_pis = { 4, 0, { { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 } }, { pis1cg, pis2cg, pis3cg, pis2cg }, 333 };
static tile_changes z81c_tbl_pis = { 4, 0, { { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 } }, { pis1cg, pis2cg, pis3cg, pis2cg }, 360 };
static tile_changes z81d_tbl_pis = { 4, 0, { { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 } }, { pis1cg, pis2cg, pis3cg, pis2cg }, 349 };
static tile_changes z82a_tbl_pis = { 4, 0, { { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 } }, { pis1cg, pis2cg, pis3cg, pis2cg }, 435 };
static tile_changes z82c_tbl_pis = { 4, 0, { { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 } }, { pis1cg, pis2cg, pis3cg, pis2cg }, 422 };
static tile_changes z82d_tbl_pis = { 4, 0, { { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 } }, { pis1cg, pis2cg, pis3cg, pis2cg }, 438 };
static tile_changes z83c_tbl_pis = { 4, 0, { { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 } }, { pis1cg, pis2cg, pis3cg, pis2cg }, 287 };
static tile_changes z83d_tbl_pis = { 4, 0, { { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 } }, { pis1cg, pis2cg, pis3cg, pis2cg }, 302 };
static tile_changes* tbls_pis[3][4] = {
  { 0, &z81a_tbl_pis, &z81d_tbl_pis, &z81c_tbl_pis },
  { 0, &z82a_tbl_pis, &z82d_tbl_pis, &z82c_tbl_pis },
  { 0, 0, &z83d_tbl_pis, &z83c_tbl_pis }
};
static tile_changes z81a_tbl_com = { 4, 0, { { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } }, { com1cg, com2cg, com3cg, com4cg }, 341 };
static tile_changes z81c_tbl_com = { 4, 0, { { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } }, { com1cg, com2cg, com3cg, com4cg }, 368 };
static tile_changes z81d_tbl_com = { 4, 0, { { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } }, { com1cg, com2cg, com3cg, com4cg }, 357 };
static tile_changes z82a_tbl_com = { 4, 0, { { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } }, { com1cg, com2cg, com3cg, com4cg }, 443 };
static tile_changes z82c_tbl_com = { 4, 0, { { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } }, { com1cg, com2cg, com3cg, com4cg }, 430 };
static tile_changes z82d_tbl_com = { 4, 0, { { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } }, { com1cg, com2cg, com3cg, com4cg }, 446 };
static tile_changes z83c_tbl_com = { 4, 0, { { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } }, { com1cg, com2cg, com3cg, com4cg }, 295 };
static tile_changes z83d_tbl_com = { 4, 0, { { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 } }, { com1cg, com2cg, com3cg, com4cg }, 310 };
static tile_changes* tbls_com[3][4] = {
  { 0, &z81a_tbl_com, &z81d_tbl_com, &z81c_tbl_com },
  { 0, &z82a_tbl_com, &z82d_tbl_com, &z82c_tbl_com },
  { 0, 0, &z83d_tbl_com, &z83c_tbl_com }
};
static tile_changes z81a_tbl_mot = { 4, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } }, { mot1cg, mot2cg, mot3cg, mot4cg }, 349 };
static tile_changes z81c_tbl_mot = { 4, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } }, { mot1cg, mot2cg, mot3cg, mot4cg }, 376 };
static tile_changes z81d_tbl_mot = { 4, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } }, { mot1cg, mot2cg, mot3cg, mot4cg }, 365 };
static tile_changes z82a_tbl_mot = { 4, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } }, { mot1cg, mot2cg, mot3cg, mot4cg }, 451 };
static tile_changes z82c_tbl_mot = { 4, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } }, { mot1cg, mot2cg, mot3cg, mot4cg }, 438 };
static tile_changes z82d_tbl_mot = { 4, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } }, { mot1cg, mot2cg, mot3cg, mot4cg }, 454 };
static tile_changes z83c_tbl_mot = { 4, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } }, { mot1cg, mot2cg, mot3cg, mot4cg }, 303 };
static tile_changes z83d_tbl_mot = { 4, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 } }, { mot1cg, mot2cg, mot3cg, mot4cg }, 318 };
static tile_changes* tbls_mot[3][4] = {
  { 0, &z81a_tbl_mot, &z81d_tbl_mot, &z81c_tbl_mot },
  { 0, &z82a_tbl_mot, &z82d_tbl_mot, &z82c_tbl_mot },
  { 0, 0, &z83d_tbl_mot, &z83c_tbl_mot }
};
static tile_changes z81a_tbl_spo = { 7, 0, { { 7, 0 }, { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 7, 6 } }, { spo1cg, spo2cg, spo3cg, spo4cg, spo5cg, spo6cg, spo7cg }, 365 };
static tile_changes z81d_tbl_spo = { 7, 0, { { 7, 0 }, { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 7, 6 } }, { spo1cg, spo2cg, spo3cg, spo4cg, spo5cg, spo6cg, spo7cg }, 381 };
static tile_changes z82a_tbl_spo = { 7, 0, { { 7, 0 }, { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 7, 6 } }, { spo1cg, spo2cg, spo3cg, spo4cg, spo5cg, spo6cg, spo7cg }, 467 };
static tile_changes z82d_tbl_spo = { 7, 0, { { 7, 0 }, { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 7, 6 } }, { spo1cg, spo2cg, spo3cg, spo4cg, spo5cg, spo6cg, spo7cg }, 470 };
static tile_changes z83d_tbl_spo = { 7, 0, { { 7, 0 }, { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 7, 6 } }, { spo1cg, spo2cg, spo3cg, spo4cg, spo5cg, spo6cg, spo7cg }, 338 };
static tile_changes* tbls_spo[3][4] = {
  { 0, &z81a_tbl_spo, &z81d_tbl_spo, 0 },
  { 0, &z82a_tbl_spo, &z82d_tbl_spo, 0 },
  { 0, 0, &z83d_tbl_spo, 0 }
};
static tile_changes tbl_bal = { 16, 0, { { 3, 0 }, { 3, 1 }, { 12, 2 }, { 3, 3 }, { 3, 0 }, { 3, 1 }, { 12, 2 }, { 3, 3 }, { 3, 0 }, { 3, 1 }, { 12, 2 }, { 3, 3 }, { 50, 0 }, { 3, 1 }, { 12, 2 }, { 3, 3 } }, { bal1cg, bal2cg, bal3cg, bal4cg }, 529 };
static tile_changes z82a_tbl_pan = { 6, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 } }, { z82apan1cg, z82apan2cg, z82apan3cg, z82apan4cg, z82apan5cg, z82apan6cg }, 471 };
static tile_changes z82b_tbl_pan = { 6, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 } }, { z82bpan1cg, z82bpan2cg, z82bpan3cg, z82bpan4cg, z82bpan5cg, z82bpan6cg }, 444 };
static tile_changes z82c_tbl_pan = { 6, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 } }, { z82cpan1cg, z82cpan2cg, z82cpan3cg, z82cpan4cg, z82cpan5cg, z82cpan6cg }, 458 };
static tile_changes z82d_tbl_pan = { 6, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 } }, { z82apan1cg, z82apan2cg, z82apan3cg, z82apan4cg, z82apan5cg, z82apan6cg }, 474 };
static tile_changes z83c_tbl_pan = { 6, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 } }, { z82cpan1cg, z82cpan2cg, z82cpan3cg, z82cpan4cg, z82cpan5cg, z82cpan6cg }, 319 };
static tile_changes z83d_tbl_pan = { 6, 0, { { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 4, 5 } }, { z82apan1cg, z82apan2cg, z82apan3cg, z82apan4cg, z82apan5cg, z82apan6cg }, 334 };
static tile_changes* tbls_pan[3][4] = {
  { 0, 0, 0, 0 },
  { &z82b_tbl_pan, &z82b_tbl_pan, &z82d_tbl_pan, &z82c_tbl_pan },
  { 0, 0, &z83d_tbl_pan, &z83c_tbl_pan }
};


void z8_cg_change(void) {
  unsigned char *pcgchgtim, *pcgchgcnt;
  int i, playsubdma[16], top;

  pcgchgtim = cgchgtim;
  pcgchgcnt = cgchgcnt;

  if (cg_chg1(tbls_pis[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 8; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(tbls_com[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 7, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 8; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(tbls_mot[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 15, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 16; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (stageno_i.b.l == 0 && (time_flag_i & 0x7F) == 1 && cg_chg1(&tbl_bal, 15, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 16; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (cg_chg1(tbls_spo[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 3, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
    for (i = 0; i < 4; ++i, ++top) {
      ChangeTileBmp(top, playsubdma[i]);
    }
  }

  if (stageno_i.b.l == 1
      ||
      stageno_i.b.l == 2 && (
        (generate_flag != 0 && (shut_flag == 0 || *pcgchgcnt != 0))
        ||
        (generate_flag == 0 && (shut_flag == 0 || cgchgcnt[0] != 0))
      )) {
    if (cg_chg1(tbls_pan[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], 3, &pcgchgtim, &pcgchgcnt, playsubdma, &top) != 0) {
      for (i = 0; i < 4; ++i, ++top) {
        ChangeTileBmp(top, playsubdma[i]);
      }
    }
  }
}
