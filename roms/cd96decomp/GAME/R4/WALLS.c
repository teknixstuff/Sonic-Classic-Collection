#include "../EQU.h"
#include "WALLS.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../RIDECHK.h"

static void main_init(sprite_status* pActwk);
static void main_move(sprite_status* pActwk);
static void opt_check(sprite_status* pActwk);

static sprite_pattern z4apat00 = { 1, { { -16, -16, 0, 446 } } };
static sprite_pattern z41bpat00 = { 1, { { -16, -16, 0, 466 } } };
static sprite_pattern z42bpat00 = { 1, { { -16, -16, 0, 462 } } };
static sprite_pattern z42cpat00 = { 1, { { -16, -16, 0, 461 } } };
static sprite_pattern z43pat00 = { 1, { { -16, -16, 0, 477 } } };
static sprite_pattern z4apat01 = { 1, { { -32, -16, 0, 447 } } };
static sprite_pattern z41bpat01 = { 1, { { -32, -16, 0, 467 } } };
static sprite_pattern z42bpat01 = { 1, { { -32, -16, 0, 463 } } };
static sprite_pattern z42cpat01 = { 1, { { -32, -16, 0, 462 } } };
static sprite_pattern z43pat01 = { 1, { { -32, -16, 0, 478 } } };
static sprite_pattern z4apat02 = { 1, { { -48, -16, 0, 448 } } };
static sprite_pattern z41bpat02 = { 1, { { -48, -16, 0, 468 } } };
static sprite_pattern z42bpat02 = { 1, { { -48, -16, 0, 464 } } };
static sprite_pattern z42cpat02 = { 1, { { -48, -16, 0, 463 } } };
static sprite_pattern z43pat02 = { 1, { { -48, -16, 0, 479 } } };
static sprite_pattern z4apat03 = { 1, { { -64, -16, 0, 449 } } };
static sprite_pattern z41bpat03 = { 1, { { -64, -16, 0, 469 } } };
static sprite_pattern z42bpat03 = { 1, { { -64, -16, 0, 465 } } };
static sprite_pattern z42cpat03 = { 1, { { -64, -16, 0, 464 } } };
static sprite_pattern z43pat03 = { 1, { { -64, -16, 0, 480 } } };
static sprite_pattern pat04;
sprite_pattern* z4a_pat_walls[5] = {
  &z4apat00,
  &z4apat01,
  &z4apat02,
  &z4apat03,
  &pat04
};
sprite_pattern* z41b_pat_walls[5] = {
  &z41bpat00,
  &z41bpat01,
  &z41bpat02,
  &z41bpat03,
  &pat04
};
sprite_pattern* z42b_pat_walls[5] = {
  &z42bpat00,
  &z42bpat01,
  &z42bpat02,
  &z42bpat03,
  &pat04
};
sprite_pattern* z42c_pat_walls[5] = {
  &z42cpat00,
  &z42cpat01,
  &z42cpat02,
  &z42cpat03,
  &pat04
};
sprite_pattern* z43_pat_walls[5] = {
  &z43pat00,
  &z43pat01,
  &z43pat02,
  &z43pat03,
  &pat04
};
sprite_pattern** pats_walls[3][3] = {
  { z41b_pat_walls, z4a_pat_walls, z41b_pat_walls },
  { z42b_pat_walls, z4a_pat_walls, z42c_pat_walls },
  { 0, 0, z43_pat_walls }
};
static unsigned char patno_tbl[9][8] = {
  { 2, 1, 1, 2, 2, 1, 1, 2 },
  { 0, 3, 1, 2, 2, 1, 3, 0 },
  { 3, 0, 0, 3, 3, 0, 0, 3 },
  { 1, 2, 0, 0, 0, 0, 2, 1 },
  { 2, 1, 1, 2, 1, 2, 2, 1 },
  { 0, 3, 2, 0, 2, 0, 0, 3 },
  { 3, 0, 0, 0, 0, 0, 0, 3 },
  { 2, 1, 1, 2, 3, 0, 0, 3 },
  { 1, 2, 1, 1, 1, 1, 2, 1 }
};
static int data_tbl[8] = {
  60, 0,  48, 131072,
  60, 0, 192, -32768
};

















































































void walls(sprite_status* pActwk) {
  if (pActwk->userflag.b.h & 128) {

    opt_check(pActwk);
    return;
  } else if (!pActwk->r_no0) {
    main_init(pActwk);
  }

  main_move(pActwk);

}





static void main_init(sprite_status* pActwk) {
  unsigned char *pOptwk, *pPatno, patnowk;
  int i, j;
  sprite_status* pNewact;

  pActwk->r_no0 += 2;
  ((short*)pActwk)[26] = pActwk->xposi.w.h;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sprhs = 16;
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 16;
  pActwk->sproffset = 17514;
  pActwk->patbase = pats_walls[stageno_i.b.h][time_flag_i & 0x7F];
  pActwk->patno = 4;
  ((short*)pActwk)[27] = pActwk - actwk;
  ((short*)pActwk)[23] = 192;
  ((int*)pActwk)[12] = -32768;

  pOptwk = &pActwk->actfree[14];
  pPatno = patno_tbl[pActwk->userflag.b.h + 1];

  for (i = 3; i >= 0; --i) {

    for (j = 1; j >= 0; --j) {

      if (actwkchk2(pActwk, &pNewact) != 0) {
        frameout(pActwk);
        return;
      }


      *pOptwk++ = pNewact - actwk;
      pNewact->userflag.b.h = (j - 2) & 255;
      pNewact->yposi.w.h = pActwk->yposi.w.h - 48 + (short)(i * 32);

      pNewact->patno = patnowk = *--pPatno;
      pNewact->sprhsize = pNewact->sprhs = (patnowk + 1) * 16;
      if (j != 0) {
        pNewact->xposi.w.h = pActwk->xposi.w.h + 64 - (short)(patnowk * 16);

      } else {
        pNewact->xposi.w.h = pActwk->xposi.w.h - 64 + (short)(patnowk * 16);
      }

      ((short*)pNewact)[27] = pActwk - actwk;
      pNewact->actno = pActwk->actno;
      pNewact->actflg = pActwk->actflg;
      pNewact->sprpri = pActwk->sprpri;
      pNewact->sprvsize = pActwk->sprvsize;
      pNewact->sproffset = pActwk->sproffset;
      pNewact->patbase = pActwk->patbase;
    }
  }

  main_move(pActwk);
}





static void main_move(sprite_status* pActwk) {
  unsigned char* pOptwk;
  int i;
  int spdwk;
  sprite_status* pChildact;

  pOptwk = &pActwk->actfree[14];
  spdwk = ((int*)pActwk)[12];

  for (i = 3; i >= 0; --i) {

    pChildact = &actwk[*pOptwk++];
    pChildact->xposi.l -= spdwk;
    pChildact->xspeed.w = -(spdwk >> 8);

    pChildact = &actwk[*pOptwk++];
    pChildact->xposi.l += spdwk;
    pChildact->xspeed.w = spdwk >> 8;
  }

  if (--((short*)pActwk)[23] == 0) {
    ((short*)pActwk)[23] = data_tbl[((short*)pActwk)[28] / 4];

    ((int*)pActwk)[12] = data_tbl[((short*)pActwk)[28] / 4 + 1];

    ((short*)pActwk)[28] += 8;
    ((short*)pActwk)[28] &= 31;
  }


  frameout_s00(pActwk, ((short*)pActwk)[26]);
}





static void opt_check(sprite_status* pActwk) {
  if (actwk[((short*)pActwk)[27]].actno != 51) {
    frameout(pActwk);
  } else {
    hitchk(pActwk, &actwk[0]);
    actionsub(pActwk);
  }
}
