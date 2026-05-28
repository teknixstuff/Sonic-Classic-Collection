#include "../EQU.h"
#include "KUZURE5.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

static void main_ini(sprite_status* pActwk);
static void main_check(sprite_status* pActwk);
static void main_wait(sprite_status* pActwk);
static void main_break(sprite_status* pActwk);
static void parts_ini(sprite_status* pActwk);
static void parts_wait(sprite_status* pActwk);
static void parts_fall(sprite_status* pActwk);

static sprite_pattern pat_00 = { 1, { { -8, -16, 0, 477 } } };
static sprite_pattern z53_pat_00 = { 1, { { -8, -16, 0, 403 } } };
static sprite_pattern pat_01 = { 1, { { -16, -16, 0, 478 } } };
static sprite_pattern z53_pat_01 = { 1, { { -16, -16, 0, 404 } } };
static sprite_pattern pat_02 = { 1, { { -24, -16, 0, 479 } } };
static sprite_pattern z53_pat_02 = { 1, { { -24, -16, 0, 405 } } };
static sprite_pattern pat_03 = { 1, { { -32, -16, 0, 480 } } };
static sprite_pattern z53_pat_03 = { 1, { { -32, -16, 0, 406 } } };
static sprite_pattern pat_04 = { 1, { { -40, -16, 0, 481 } } };
static sprite_pattern z53_pat_04 = { 1, { { -40, -16, 0, 407 } } };
static sprite_pattern pat_05 = { 1, { { -48, -16, 0, 482 } } };
static sprite_pattern z53_pat_05 = { 1, { { -48, -16, 0, 408 } } };
static sprite_pattern pat_06 = { 1, { { -56, -16, 0, 483 } } };
static sprite_pattern z53_pat_06 = { 1, { { -56, -16, 0, 409 } } };
static sprite_pattern pat_07 = { 1, { { -64, -16, 0, 484 } } };
static sprite_pattern z53_pat_07 = { 1, { { -64, -16, 0, 410 } } };
static sprite_pattern pat_08 = { 1, { { -8, -8, 0, 485 } } };
static sprite_pattern z53_pat_08 = { 1, { { -8, -8, 0, 411 } } };
static sprite_pattern pat_09 = { 1, { { -8, -8, 0, 486 } } };
static sprite_pattern z53_pat_09 = { 1, { { -8, -8, 0, 412 } } };
sprite_pattern* z5_pat_kuzure_a[10] = {
  &pat_00,
  &pat_01,
  &pat_02,
  &pat_03,
  &pat_04,
  &pat_05,
  &pat_06,
  &pat_07,
  &pat_08,
  &pat_09
};
sprite_pattern* z53_pat_kuzure_a[10] = {
  &z53_pat_00,
  &z53_pat_01,
  &z53_pat_02,
  &z53_pat_03,
  &z53_pat_04,
  &z53_pat_05,
  &z53_pat_06,
  &z53_pat_07,
  &z53_pat_08,
  &z53_pat_09
};
static sprite_pattern** pats_kuzure_a[3] = {
  z5_pat_kuzure_a,
  z5_pat_kuzure_a,
  z53_pat_kuzure_a
};
static void(*kuzure5_act_tbl[4])(sprite_status*) = {
  &main_ini,
  &main_check,
  &main_wait,
  &main_break
};
static void(*parts_act_tbl[3])(sprite_status*) = {
  &parts_ini,
  &parts_wait,
  &parts_fall
};






































































void kuzure5(sprite_status* pActwk) {
  if (pActwk->userflag.b.l)
  {
    parts_act_tbl[pActwk->r_no0 / 2](pActwk);
  }
  else {
    kuzure5_act_tbl[pActwk->r_no0 / 2](pActwk);
  }
}





static void main_ini(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg = 4;
  pActwk->patbase = pats_kuzure_a[stageno_i.b.l];
  pActwk->sprpri = 3;
  pActwk->sprvsize = 17;

  if (stageno.b.l != 2) {
    pActwk->sproffset = 17232;
  } else {
    pActwk->sproffset = 17312;
  }

  pActwk->patno = pActwk->userflag.b.h - 1;
  pActwk->sprhs = pActwk->sprhsize = pActwk->userflag.b.h * 8;
  main_check(pActwk);
}





static void main_check(sprite_status* pActwk) {
  if (ridechk(pActwk, &actwk[0])) {
    pActwk->r_no0 += 2;
    pActwk->cdsts = 0;
    ((short*)pActwk)[23] = 8;

    if (actwk[0].xspeed.w >= 0) {
      ((short*)pActwk)[24] = 8;
    }
    else ((short*)pActwk)[24] = -8;


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
    pNewact->patno = 8;

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
      pNewact->patno = 9;
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









static void parts_ini(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
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
