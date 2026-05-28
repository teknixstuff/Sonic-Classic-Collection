#include "../EQU.h"
#include "MINOMUSI.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void body(sprite_status* actionwk);
static short act_check(sprite_status* actionwk, sprite_status* pw);

static sprite_pattern nullpat = { 1, { { 0, 0, 0, 0 } } };
static sprite_pattern ito01 = { 1, { { -4, -12, 0, 457 } } };
static sprite_pattern z6bito01 = { 1, { { -4, -12, 0, 451 } } };
static sprite_pattern ito02 = { 1, { { -4, -16, 0, 458 } } };
static sprite_pattern z6bito02 = { 1, { { -4, -16, 0, 452 } } };
static sprite_pattern ito03 = { 1, { { -4, -20, 0, 459 } } };
static sprite_pattern z6bito03 = { 1, { { -4, -20, 0, 453 } } };
static sprite_pattern ito04 = { 1, { { -4, -24, 0, 460 } } };
static sprite_pattern z6bito04 = { 1, { { -4, -24, 0, 454 } } };
static sprite_pattern ito05 = { 1, { { -4, -28, 0, 461 } } };
static sprite_pattern z6bito05 = { 1, { { -4, -28, 0, 455 } } };
static sprite_pattern ito06 = { 1, { { -4, -32, 0, 462 } } };
static sprite_pattern z6bito06 = { 1, { { -4, -32, 0, 456 } } };
static sprite_pattern ito07 = { 1, { { -4, -36, 0, 463 } } };
static sprite_pattern z6bito07 = { 1, { { -4, -36, 0, 457 } } };
static sprite_pattern ito08 = { 1, { { -4, -40, 0, 464 } } };
static sprite_pattern z6bito08 = { 1, { { -4, -40, 0, 458 } } };
static sprite_pattern mino1 = { 1, { { -8, -16, 0, 465 } } };
static sprite_pattern z6bmino1 = { 1, { { -8, -16, 0, 459 } } };
static sprite_pattern mino2 = { 1, { { -12, -16, 0, 466 } } };
static sprite_pattern z6bmino2 = { 1, { { -12, -16, 0, 460 } } };
static sprite_pattern mino3 = { 1, { { -16, -16, 0, 467 } } };
static sprite_pattern z6bmino3 = { 1, { { -16, -16, 0, 461 } } };
static sprite_pattern mino4 = { 1, { { -8, -16, 0, 468 } } };
static sprite_pattern z6bmino4 = { 1, { { -8, -16, 0, 462 } } };
static sprite_pattern mino5 = { 1, { { -8, -16, 0, 469 } } };
static sprite_pattern z6bmino5 = { 1, { { -8, -16, 0, 463 } } };
sprite_pattern* pat_minomusi_e[12] =
{
  &nullpat,
  &ito01,
  &ito02,
  &ito03,
  &ito04,
  &ito05,
  &ito06,
  &ito07,
  &ito08,
  &mino1,
  &mino2,
  &mino3
};
sprite_pattern* z6b_pat_minomusi_e[12] =
{
  &nullpat,
  &z6bito01,
  &z6bito02,
  &z6bito03,
  &z6bito04,
  &z6bito05,
  &z6bito06,
  &z6bito07,
  &z6bito08,
  &z6bmino1,
  &z6bmino2,
  &z6bmino3
};
sprite_pattern** pats_minomusi_e[3] =
{
  z6b_pat_minomusi_e,
  pat_minomusi_e,
  pat_minomusi_e
};
sprite_pattern* pat_minomusi_b[11] = {
  &nullpat,
  &ito01,
  &ito02,
  &ito03,
  &ito04,
  &ito05,
  &ito06,
  &ito07,
  &ito08,
  &mino4,
  &mino5
};
sprite_pattern* z6b_pat_minomusi_b[11] = {
  &nullpat,
  &z6bito01,
  &z6bito02,
  &z6bito03,
  &z6bito04,
  &z6bito05,
  &z6bito06,
  &z6bito07,
  &z6bito08,
  &z6bmino4,
  &z6bmino5
};
sprite_pattern** pats_minomusi_b[3] =
{
  z6b_pat_minomusi_b,
  pat_minomusi_b,
  pat_minomusi_b
};
static char pchg0[36] = { 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, -1 };
static char pchg1[4] = { 9, 9, 10, -1 };
static char* pchg[2] = { pchg0, pchg1 };


void minomusi(sprite_status* actionwk) {
  if (actionwk->userflag.b.l == 0) { body(actionwk); return; }
  if (actionwk->userflag.b.l < 0) { ito(actionwk); return; }
  hari(actionwk);
}

static void body(sprite_status* actionwk) {
  void(*body_tbl[9])(sprite_status*) =
  {
    &body_init,
    &body_wait,
    &body_wait1,
    &body_down,
    &body_down1,
    &body_up,
    &body_up1,
    &body_stay,
    &body_stay1
  };
  if (enemy_suicide(actionwk) == -1) return;
  body_tbl[actionwk->r_no0 / 2](actionwk);
  actionsub(actionwk);
  frameout_s(actionwk);
}





void body_init(sprite_status* actionwk) {
  sprite_status* a1;

  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 3;

  actionwk->sprvsize = 16;
  actionwk->sprhs = 16;
  actionwk->sprhsize = 16;
  actionwk->sproffset = 9352;
  actionwk->colino = 52;
  actionwk->yposi.w.h += 8;
  ((short*)actionwk)[28] = actionwk->yposi.w.h;
  ((short*)actionwk)[29] = actionwk->yposi.w.h + 95;
  if (actionwk->userflag.b.h == 0)
    actionwk->patbase = pats_minomusi_e[time_flag_i & 0x7F];
  else
    actionwk->patbase = pats_minomusi_b[time_flag_i & 0x7F];
  if (actwkchk2(actionwk, &a1) != 0)
  {
    frameout(actionwk);
    return;
  }

  a1->actno = actionwk->actno;
  a1->userflag.b.l = -1;
  a1->xposi.w.h = actionwk->xposi.w.h;
  a1->yposi.w.h = actionwk->yposi.w.h;
  a1->actflg = actionwk->actflg;
  a1->sprpri = actionwk->sprpri;
  ++a1->sprpri;
  a1->sproffset = actionwk->sproffset;
  a1->patbase = actionwk->patbase;

  a1->sprvsize = 32;
  a1->sprhs = 1;
  a1->sprhsize = 1;
  ((unsigned short*)a1)[30] = actionwk - actwk;
}

void body_wait(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->patno = 9;
  ((short*)actionwk)[23] = 121;
  body_wait1(actionwk);
}

void body_wait1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] != 0) return;
  if (act_check(actionwk, &actwk[0]))
    actionwk->r_no0 += 2;
  else
    actionwk->r_no0 -= 2;
}

static short act_check(sprite_status* actionwk, sprite_status* pw) {
  short d0w;

  d0w = pw->yposi.w.h;
  d0w -= actionwk->yposi.w.h;
  d0w -= 40;

  if (d0w < 0 || d0w > 120) return 0;
  d0w = pw->xposi.w.h;
  d0w -= actionwk->xposi.w.h;
  d0w += 168;

  if (d0w >= 0 && d0w < 336) return 1;
  return 0;
}

void body_down(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  ((int*)actionwk)[13] = 524288;
  body_down1(actionwk);
}

void body_down1(sprite_status* actionwk) {
  short d0;

  actionwk->yposi.l += ((int*)actionwk)[13];
  d0 = ((short*)actionwk)[29] - actionwk->yposi.w.h;
  if (d0 <= 0)
  {
    actionwk->yposi.w.h += d0;
    actionwk->r_no0 = 14;
  }
}

void body_up(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  if (actionwk->userflag.b.h != 0)
    ((int*)actionwk)[13] = 0x20000;
  else
    ((int*)actionwk)[13] = 458752;
  body_up1(actionwk);
}

void body_up1(sprite_status* actionwk) {
  short d0;

  actionwk->yposi.l -= ((int*)actionwk)[13];
  d0 = ((short*)actionwk)[28] - actionwk->yposi.w.h;
  if (d0 >= 0)
  {
    actionwk->yposi.w.h += d0;
    actionwk->r_no0 = 2;
  }
}

void body_stay(sprite_status* actionwk) {
  short d0, d1;

  actionwk->r_no0 += 2;
  if (actionwk->userflag.b.h == 0)
  {
    d0 = 230;
    d1 = 255;
  }
  else
  {
    d0 = 61;
    d1 = 511;
  }
  ((short*)actionwk)[23] = d0;
  actionwk->mstno.w = d1;
}

void body_stay1(sprite_status* actionwk) {
  sprite_status* a1;

  if (--((short*)actionwk)[23] == 0) actionwk->r_no0 = 10;

  patchg(actionwk, (unsigned char**)pchg);
  if (actionwk->userflag.b.h != 0) return;

  if (actionwk->patcnt != 15) return;
  if (actwkchk2(actionwk, &a1) != 0) return;

  a1->actno = actionwk->actno;
  a1->userflag.b.l = 1;
  a1->xposi.w.h = actionwk->xposi.w.h;
  a1->yposi.w.h = actionwk->yposi.w.h;
  a1->yposi.w.h += 4;
  a1->actflg = actionwk->actflg;
  a1->sprpri = actionwk->sprpri;
  a1->sproffset = actionwk->sproffset;
  a1->patbase = actionwk->patbase;

  a1->sprvsize = actionwk->sprvsize;
  a1->sprhs = actionwk->sprhs;
  a1->sprhsize = actionwk->sprhsize;
  ((unsigned short*)a1)[30] = actionwk - actwk;

  a1->colino = 181;
  if ((char)actionwk->actflg < 0)
    soundset(183);
}

void hari(sprite_status* actionwk) {
  sprite_status* a1;

  a1 = &actwk[((unsigned short*)actionwk)[30]];
  if (a1->patcnt == 1)
    frameout(actionwk);
  else
    actionsub(actionwk);
}



void ito(sprite_status* actionwk) {
  sprite_status* a1;
  short d0;

  a1 = &actwk[((unsigned short*)actionwk)[30]];
  if (a1->actno != 51)
  {
    frameout(actionwk);
    return;
  }

  d0 = (a1->yposi.w.h - ((short*)a1)[28] - 24) >> 3;
  if (d0 < 0) d0 = 0;

  actionwk->patno = d0;
  d0 <<= 2;
  d0 += ((short*)a1)[28] + 16;
  actionwk->yposi.w.h = d0;
  actionsub(actionwk);
}
