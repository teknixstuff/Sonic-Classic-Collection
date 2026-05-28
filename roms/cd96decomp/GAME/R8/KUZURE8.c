#include "../EQU.h"
#include "KUZURE8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

static sprite_pattern z81pat00 = { 1, { { -8, -16, 0, 444 } } };
static sprite_pattern z82pat00 = { 1, { { -8, -16, 0, 422 } } };
static sprite_pattern z83pat00 = { 1, { { -8, -16, 0, 423 } } };
static sprite_pattern z81pat01 = { 1, { { -16, -16, 0, 445 } } };
static sprite_pattern z82pat01 = { 1, { { -16, -16, 0, 423 } } };
static sprite_pattern z83pat01 = { 1, { { -16, -16, 0, 424 } } };
static sprite_pattern z81pat02 = { 1, { { -24, -16, 0, 446 } } };
static sprite_pattern z82pat02 = { 1, { { -24, -16, 0, 424 } } };
static sprite_pattern z83pat02 = { 1, { { -24, -16, 0, 425 } } };
static sprite_pattern z81pat03 = { 1, { { -32, -16, 0, 447 } } };
static sprite_pattern z82pat03 = { 1, { { -32, -16, 0, 425 } } };
static sprite_pattern z83pat03 = { 1, { { -32, -16, 0, 426 } } };
static sprite_pattern z81pat04 = { 1, { { -40, -16, 0, 448 } } };
static sprite_pattern z82pat04 = { 1, { { -40, -16, 0, 426 } } };
static sprite_pattern z83pat04 = { 1, { { -40, -16, 0, 427 } } };
static sprite_pattern z81pat05 = { 1, { { -48, -16, 0, 449 } } };
static sprite_pattern z82pat05 = { 1, { { -48, -16, 0, 427 } } };
static sprite_pattern z83pat05 = { 1, { { -48, -16, 0, 428 } } };
static sprite_pattern z81pat06 = { 1, { { -56, -16, 0, 450 } } };
static sprite_pattern z82pat06 = { 1, { { -56, -16, 0, 428 } } };
static sprite_pattern z83pat06 = { 1, { { -56, -16, 0, 429 } } };
static sprite_pattern z81pat07 = { 1, { { -64, -16, 0, 451 } } };
static sprite_pattern z82pat07 = { 1, { { -64, -16, 0, 429 } } };
static sprite_pattern z83pat07 = { 1, { { -64, -16, 0, 430 } } };
static sprite_pattern z81pat08 = { 1, { { -8, -8, 0, 452 } } };
static sprite_pattern z82pat08 = { 1, { { -8, -8, 0, 430 } } };
static sprite_pattern z83pat08 = { 1, { { -8, -8, 0, 431 } } };
static sprite_pattern z81pat09 = { 1, { { -8, -8, 0, 453 } } };
static sprite_pattern z82pat09 = { 1, { { -8, -8, 0, 431 } } };
static sprite_pattern z83pat09 = { 1, { { -8, -8, 0, 432 } } };
sprite_pattern* z81_pat_kuzure_a[10] =
{
  &z81pat00,
  &z81pat01,
  &z81pat02,
  &z81pat03,
  &z81pat04,
  &z81pat05,
  &z81pat06,
  &z81pat07,
  &z81pat08,
  &z81pat09
};
sprite_pattern* z82_pat_kuzure_a[10] =
{
  &z82pat00,
  &z82pat01,
  &z82pat02,
  &z82pat03,
  &z82pat04,
  &z82pat05,
  &z82pat06,
  &z82pat07,
  &z82pat08,
  &z82pat09
};
sprite_pattern* z83_pat_kuzure_a[10] =
{
  &z83pat00,
  &z83pat01,
  &z83pat02,
  &z83pat03,
  &z83pat04,
  &z83pat05,
  &z83pat06,
  &z83pat07,
  &z83pat08,
  &z83pat09
};
static sprite_pattern** pats_kuzure_a[3] =
{
  z81_pat_kuzure_a,
  z82_pat_kuzure_a,
  z83_pat_kuzure_a
};


void kuzure8(sprite_status* actionwk) {
  if (actionwk->userflag.b.l != 0)
  {
    parts(actionwk);
    return;
  }
  switch (actionwk->r_no0)
  {
    case 0:
      main_ini(actionwk);
      break;
    case 2:
      main_check(actionwk);
      break;
    case 4:
      main_wait(actionwk);
      break;
    case 6:
      main_break(actionwk);
      break;
    case 8:
      main_hitchk(actionwk);
      break;
  }
}

void main_ini(sprite_status* actionwk) {
  char d0, d1;

  actionwk->actflg |= 4;
  actionwk->patbase = pats_kuzure_a[stageno_i.b.l];
  actionwk->sprvsize = 17;
  if (stageno.b.l != 2)
    actionwk->sproffset = 17624;
  else
    actionwk->sproffset = 17274;
  d0 = actionwk->userflag.b.h;
  if (d0 < 0) d0 = -d0;

  d1 = d0;
  --d0;
  actionwk->patno = d0;
  d1 <<= 3;
  actionwk->sprhs = d1;
  actionwk->sprhsize = d1;
  d0 = 3;
  d1 = 2;
  if (actionwk->userflag.b.h < 0)
  {
    d0 = 1;
    d1 = 8;
  }
  actionwk->sprpri = d0;
  actionwk->r_no0 = d1;
}

void main_check(sprite_status* actionwk) {
  if (ridechk(actionwk, &actwk[0]) != 0)
  {
    actionwk->r_no0 += 2;
    actionwk->cdsts = 0;
    ((short*)actionwk)[23] = 8;
    if (actwk[0].xspeed.w < 0)
      ((short*)actionwk)[24] = -8;
    else
      ((short*)actionwk)[24] = 8;
    soundset(163);
  }
  actionsub(actionwk);
  frameout_s(actionwk);
}

void main_wait(sprite_status* actionwk) {
  short t;

  ridechk(actionwk, &actwk[0]);
  --((short*)actionwk)[23];
  t = ((short*)actionwk)[23];
  if (t < 0) actionwk->r_no0 += 2;
  actionsub(actionwk);
}





void main_break(sprite_status* actionwk) {
  short d1, d2, d3;
  char ride;
  sprite_status* a1;

  ride = 0;
  d1 = -1;
  d2 = 8;
  d3 = (actionwk->userflag.b.h - 1) << 3;
  if (((short*)actionwk)[24] >= 0) d3 = -d3;
  if (actwkchk(&a1) == 0)
  {
    a1->actno = actionwk->actno;
    a1->actflg = actionwk->actflg;
    a1->sproffset = actionwk->sproffset;
    a1->patbase = actionwk->patbase;
    a1->xposi.w.h = actionwk->xposi.w.h;
    a1->yposi.w.h = actionwk->yposi.w.h;

    a1->userflag.b.l = d1;
    a1->yposi.w.h -= d2;
    a1->xposi.w.h += d3;
    ((short*)a1)[23] = 4;
    a1->patno = 8;
    if (actwkchk(&a1) == 0)
    {
      a1->actno = actionwk->actno;
      a1->actflg = actionwk->actflg;
      a1->sproffset = actionwk->sproffset;
      a1->patbase = actionwk->patbase;
      a1->xposi.w.h = actionwk->xposi.w.h;
      a1->yposi.w.h = actionwk->yposi.w.h;

      a1->userflag.b.l = d1;
      a1->yposi.w.h += d2;
      a1->xposi.w.h += d3;
      ((short*)a1)[23] = 0;
      a1->patno = 9;
    }
  }


  if (ridechk(actionwk, &actwk[0])) ride_on_clr(actionwk, &actwk[0]);

  --actionwk->userflag.b.h;
  ride = actionwk->userflag.b.h;
  if (ride <= 0)
  {
    frameout(actionwk);
    return;
  }
  actionwk->r_no0 -= 2;
  --actionwk->patno;
  actionwk->sprhs -= 8;
  actionwk->sprhsize -= 8;
  ((short*)actionwk)[23] = 7;
  actionwk->xposi.w.h += ((short*)actionwk)[24];

  ridechk(actionwk, &actwk[0]);
  actionsub(actionwk);
}

void main_hitchk(sprite_status* actionwk) {
  hitchk(actionwk, &actwk[0]);
  actionsub(actionwk);
  frameout_s(actionwk);
}








void parts(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      parts_ini(actionwk);
      break;
    case 2:
      parts_wait(actionwk);
      break;
    case 4:
      parts_fall(actionwk);
      break;
  }
}

void parts_ini(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->sprpri = 3;
  actionwk->sprhs = 8;
  actionwk->sprhsize = 8;
  actionwk->sprvsize = 8;
  actionsub(actionwk);
}

void parts_wait(sprite_status* actionwk) {
  short t;

  t = ((short*)actionwk)[23]--;
  if (t <= 0) actionwk->r_no0 += 2;
  actionsub(actionwk);
}

void parts_fall(sprite_status* actionwk) {
  int d0;

  if ((char)actionwk->actflg >= 0)
  {
    frameout(actionwk);
    return;
  }
  d0 = ((int*)actionwk)[12] + 16384;
  if (d0 > 1441792) d0 = 1441792;

  ((int*)actionwk)[12] = d0;
  actionwk->yposi.l += d0;
  actionsub(actionwk);
}
