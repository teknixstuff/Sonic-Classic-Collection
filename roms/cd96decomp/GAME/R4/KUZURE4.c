#include "../EQU.h"
#include "KUZURE4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

static void main_ini(sprite_status* pActwk);
static void main_check(sprite_status* pActwk);
static void main_wait(sprite_status* pActwk);
static void main_break(sprite_status* pActwk);
static void parts(sprite_status* pActwk);
static void parts_ini(sprite_status* pActwk);
static void parts_wait(sprite_status* pActwk);
static void parts_fall(sprite_status* pActwk);

static sprite_pattern z41a_pat_kuzure_00 = { 1, { { -8, -16, 0, 515 } } };
static sprite_pattern z42a_pat_kuzure_00 = { 1, { { -8, -16, 0, 519 } } };
static sprite_pattern z42b_pat_kuzure_00 = { 1, { { -8, -16, 0, 480 } } };
static sprite_pattern z42c_pat_kuzure_00 = { 1, { { -8, -16, 0, 475 } } };
static sprite_pattern z41a_pat_kuzure_01 = { 1, { { -16, -16, 0, 516 } } };
static sprite_pattern z42a_pat_kuzure_01 = { 1, { { -16, -16, 0, 520 } } };
static sprite_pattern z42b_pat_kuzure_01 = { 1, { { -16, -16, 0, 481 } } };
static sprite_pattern z42c_pat_kuzure_01 = { 1, { { -16, -16, 0, 476 } } };
static sprite_pattern z41a_pat_kuzure_02 = { 1, { { -24, -16, 0, 517 } } };
static sprite_pattern z42a_pat_kuzure_02 = { 1, { { -24, -16, 0, 521 } } };
static sprite_pattern z42b_pat_kuzure_02 = { 1, { { -24, -16, 0, 482 } } };
static sprite_pattern z42c_pat_kuzure_02 = { 1, { { -24, -16, 0, 477 } } };
static sprite_pattern z41a_pat_kuzure_03 = { 1, { { -32, -16, 0, 518 } } };
static sprite_pattern z42a_pat_kuzure_03 = { 1, { { -32, -16, 0, 522 } } };
static sprite_pattern z42b_pat_kuzure_03 = { 1, { { -32, -16, 0, 483 } } };
static sprite_pattern z42c_pat_kuzure_03 = { 1, { { -32, -16, 0, 478 } } };
static sprite_pattern z41a_pat_kuzure_04 = { 1, { { -40, -16, 0, 519 } } };
static sprite_pattern z42a_pat_kuzure_04 = { 1, { { -40, -16, 0, 523 } } };
static sprite_pattern z42b_pat_kuzure_04 = { 1, { { -40, -16, 0, 484 } } };
static sprite_pattern z42c_pat_kuzure_04 = { 1, { { -40, -16, 0, 479 } } };
static sprite_pattern z41a_pat_kuzure_05 = { 1, { { -48, -16, 0, 520 } } };
static sprite_pattern z42a_pat_kuzure_05 = { 1, { { -48, -16, 0, 524 } } };
static sprite_pattern z42b_pat_kuzure_05 = { 1, { { -48, -16, 0, 485 } } };
static sprite_pattern z42c_pat_kuzure_05 = { 1, { { -48, -16, 0, 480 } } };
static sprite_pattern z41a_pat_kuzure_06 = { 1, { { -56, -16, 0, 521 } } };
static sprite_pattern z42a_pat_kuzure_06 = { 1, { { -56, -16, 0, 525 } } };
static sprite_pattern z42b_pat_kuzure_06 = { 1, { { -56, -16, 0, 486 } } };
static sprite_pattern z42c_pat_kuzure_06 = { 1, { { -56, -16, 0, 481 } } };
static sprite_pattern z41a_pat_kuzure_07 = { 1, { { -64, -16, 0, 522 } } };
static sprite_pattern z42a_pat_kuzure_07 = { 1, { { -64, -16, 0, 526 } } };
static sprite_pattern z42b_pat_kuzure_07 = { 1, { { -64, -16, 0, 487 } } };
static sprite_pattern z42c_pat_kuzure_07 = { 1, { { -64, -16, 0, 482 } } };
static sprite_pattern z41a_pat_kuzure_08 = { 1, { { -8, -8, 0, 523 } } };
static sprite_pattern z42a_pat_kuzure_08 = { 1, { { -8, -8, 0, 527 } } };
static sprite_pattern z42b_pat_kuzure_08 = { 1, { { -8, -8, 0, 488 } } };
static sprite_pattern z42c_pat_kuzure_08 = { 1, { { -8, -8, 0, 483 } } };
sprite_pattern* z41a_pat_kuzure_a[9] = {
  &z41a_pat_kuzure_00,
  &z41a_pat_kuzure_01,
  &z41a_pat_kuzure_02,
  &z41a_pat_kuzure_03,
  &z41a_pat_kuzure_04,
  &z41a_pat_kuzure_05,
  &z41a_pat_kuzure_06,
  &z41a_pat_kuzure_07,
  &z41a_pat_kuzure_08
};
sprite_pattern* z42a_pat_kuzure_a[9] = {
  &z42a_pat_kuzure_00,
  &z42a_pat_kuzure_01,
  &z42a_pat_kuzure_02,
  &z42a_pat_kuzure_03,
  &z42a_pat_kuzure_04,
  &z42a_pat_kuzure_05,
  &z42a_pat_kuzure_06,
  &z42a_pat_kuzure_07,
  &z42a_pat_kuzure_08
};
sprite_pattern* z42b_pat_kuzure_a[9] = {
  &z42b_pat_kuzure_00,
  &z42b_pat_kuzure_01,
  &z42b_pat_kuzure_02,
  &z42b_pat_kuzure_03,
  &z42b_pat_kuzure_04,
  &z42b_pat_kuzure_05,
  &z42b_pat_kuzure_06,
  &z42b_pat_kuzure_07,
  &z42b_pat_kuzure_08
};
sprite_pattern* z42c_pat_kuzure_a[9] = {
  &z42c_pat_kuzure_00,
  &z42c_pat_kuzure_01,
  &z42c_pat_kuzure_02,
  &z42c_pat_kuzure_03,
  &z42c_pat_kuzure_04,
  &z42c_pat_kuzure_05,
  &z42c_pat_kuzure_06,
  &z42c_pat_kuzure_07,
  &z42c_pat_kuzure_08
};
static sprite_pattern** pats_kuzure_a[2][3] = {
  { z41a_pat_kuzure_a, z41a_pat_kuzure_a, z41a_pat_kuzure_a },
  { z42b_pat_kuzure_a, z42a_pat_kuzure_a, z42c_pat_kuzure_a }
};
static void(*kuzure4_act_tbl[4])(sprite_status*) = {
  &main_ini,
  &main_check,
  &main_wait,
  &main_break
};
static void(*parts_act_tbl[3])(sprite_status*) = {
  &parts_ini,
  &parts_wait,
  parts_fall
};





























void kuzure4(sprite_status* pActwk) {
  if (pActwk->userflag.b.l) {
    parts(pActwk);
  } else {
    kuzure4_act_tbl[pActwk->r_no0 / 2](pActwk);
  }
}





static void main_ini(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg = 4;
  pActwk->sproffset = 17252;
  pActwk->patbase = pats_kuzure_a[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  pActwk->sprpri = 3;
  pActwk->sprvsize = 17;

  pActwk->patno = pActwk->userflag.b.h - 1;
  pActwk->sprhs = pActwk->sprhsize = pActwk->userflag.b.h * 8;
  main_check(pActwk);
}





static void main_check(sprite_status* pActwk) {
  if (ridechk(pActwk, &actwk[0])) {
    pActwk->r_no0 += 2;
    pActwk->cdsts = 0;
    ((short*)pActwk)[23] = 8;

    if (actwk[0].xspeed.w < 0) {
      ((short*)pActwk)[24] = -8;
    } else {
      ((short*)pActwk)[24] = 8;
    }

    soundset(163);
  }


  actionsub(pActwk);
  frameout_s(pActwk);
}





static void main_wait(sprite_status* pActwk) {
  ridechk(pActwk, &actwk[0]);

  if (--((short*)pActwk)[23] < 0) {
    pActwk->r_no0 += 2;
  }

  actionsub(pActwk);
}





static void main_break(sprite_status* pActwk) {
  unsigned char flagwk;
  short xwk;
  short ywk;
  sprite_status* pNewact;



  flagwk = 255;
  ywk = 8;
  xwk = ((short)pActwk->userflag.b.h - 1) * 8;

  if (((short*)pActwk)[24] >= 0) {
    xwk *= -1;
  }


  if (actwkchk(&pNewact) == 0) {


    pNewact->actno = pActwk->actno;
    pNewact->actflg = pActwk->actflg;
    pNewact->sproffset = pActwk->sproffset;
    pNewact->patbase = pActwk->patbase;
    pNewact->xposi.l = pActwk->xposi.l;
    pNewact->yposi.l = pActwk->yposi.l;


    pNewact->userflag.b.l = flagwk;
    pNewact->yposi.w.h -= ywk;
    pNewact->xposi.w.h += xwk;
    ((short*)pNewact)[23] = 4;

    if (actwkchk(&pNewact) == 0) {


      pNewact->actno = pActwk->actno;
      pNewact->actflg = pActwk->actflg;
      pNewact->sproffset = pActwk->sproffset;
      pNewact->patbase = pActwk->patbase;
      pNewact->xposi.l = pActwk->xposi.l;
      pNewact->yposi.l = pActwk->yposi.l;


      pNewact->userflag.b.l = flagwk;
      pNewact->yposi.w.h += ywk;
      pNewact->xposi.w.h += xwk;
    }
  }


  if (ridechk(pActwk, &actwk[0])) {
    ride_on_clr(pActwk, &actwk[0]);
  }


  if (--pActwk->userflag.b.h <= 0) {
    frameout(pActwk);
  } else {
    pActwk->r_no0 -= 2;
    --pActwk->patno;
    pActwk->sprhs -= 8;
    pActwk->sprhsize -= 8;
    ((short*)pActwk)[23] = 7;
    pActwk->xposi.w.h += ((short*)pActwk)[24];
    ridechk(pActwk, &actwk[0]);
    actionsub(pActwk);
  }
}
























static void parts(sprite_status* pActwk) {
  parts_act_tbl[pActwk->r_no0 / 2](pActwk);
}





static void parts_ini(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->patno = 8;
  pActwk->sprpri = 3;
  pActwk->sprhs = pActwk->sprhsize = 8;
  pActwk->sprvsize = 8;
  actionsub(pActwk);
}





static void parts_wait(sprite_status* pActwk) {
  if (--((short*)pActwk)[23] < 0) {
    pActwk->r_no0 += 2;
  }


  actionsub(pActwk);
}





static void parts_fall(sprite_status* pActwk) {
  int spdwk;

  if (!(pActwk->actflg & 128)) {
    frameout(pActwk);
  } else {
    spdwk = (long int)((int*)pActwk)[12] + 16384;
    if ((long int)spdwk > 1441792) {
      spdwk = 1441792;
    }
    ((int*)pActwk)[12] = spdwk;
    pActwk->yposi.l += spdwk;
    actionsub(pActwk);
  }
}
