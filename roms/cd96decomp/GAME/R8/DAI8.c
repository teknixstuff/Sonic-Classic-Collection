#include "../EQU.h"
#include "DAI8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../PLAYSUB.h"
#include "../RIDECHK.h"

static void act_init(sprite_status* actionwk);
static void act_init_sub(sprite_status* actionwk, sprite_status* a6);
static void act_wait(sprite_status* actionwk);

static char p00[47] =
{
  0, 5, 5, 5, 5, 5, 4, 4, 4, 5,
  5, 5, 5, 5, 4, 4, 4, 3, 3, 3,
  3, 3, 2, 2, 2, 3, 3, 3, 3, 3,
  2, 2, 2, 1, 1, 1, 1, 1, 7, 7,
  7, 1, 1, 1, 1, 1, 0
};
static char p01[152] =
{
  0, 1, 1, 1, 1, 1, 7, 7, 7, 1,
  1, 1, 1, 1, 2, 2, 2, 3, 3, 3,
  3, 3, 2, 2, 2, 3, 3, 3, 3, 3,
  4, 4, 4, 5, 5, 5, 5, 5, 4, 4,
  4, 5, 5, 5, 5, 5, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 5, 5, 5, 5,
  5, 4, 4, 4, 5, 5, 5, 5, 5, 4,
  4, 4, 3, 3, 3, 3, 3, 2, 2, 2,
  3, 3, 3, 3, 3, 2, 2, 2, 1, 1,
  1, 1, 1, 7, 7, 7, 1, 1, 1, 1,
  1, 0
};
static char* pchg[2] =
{
  p00,
  p01
};
static sprite_pattern z81pat00 = { 1, { { -16, -16, 0, 475 } } };
static sprite_pattern z82pat00 = { 1, { { -16, -16, 0, 437 } } };
static sprite_pattern z83pat00 = { 1, { { -16, -16, 0, 433 } } };
static sprite_pattern z81pat01 = { 1, { { -16, -16, 0, 476 } } };
static sprite_pattern z82pat01 = { 1, { { -16, -16, 0, 438 } } };
static sprite_pattern z83pat01 = { 1, { { -16, -16, 0, 434 } } };
static sprite_pattern z81pat02 = { 1, { { -8, -16, 0, 477 } } };
static sprite_pattern z82pat02 = { 1, { { -8, -16, 0, 439 } } };
static sprite_pattern z83pat02 = { 1, { { -8, -16, 0, 435 } } };
static sprite_pattern z81pat03 = { 1, { { -8, -16, 0, 478 } } };
static sprite_pattern z82pat03 = { 1, { { -8, -16, 0, 440 } } };
static sprite_pattern z83pat03 = { 1, { { -8, -16, 0, 436 } } };
static sprite_pattern z81pat04 = { 1, { { -4, -16, 0, 479 } } };
static sprite_pattern z82pat04 = { 1, { { -4, -16, 0, 441 } } };
static sprite_pattern z83pat04 = { 1, { { -4, -16, 0, 437 } } };
static sprite_pattern z81pat05 = { 1, { { -4, -16, 0, 480 } } };
static sprite_pattern z82pat05 = { 1, { { -4, -16, 0, 442 } } };
static sprite_pattern z83pat05 = { 1, { { -4, -16, 0, 438 } } };
static sprite_pattern patnull = { 1, { { 0, 0, 0, 0 } } };
sprite_pattern* z81_pat_dai8[8] =
{
  &z81pat00,
  &z81pat01,
  &z81pat02,
  &z81pat03,
  &z81pat04,
  &z81pat05,
  &patnull,
  &z81pat00
};
sprite_pattern* z82_pat_dai8[8] =
{
  &z82pat00,
  &z82pat01,
  &z82pat02,
  &z82pat03,
  &z82pat04,
  &z82pat05,
  &patnull,
  &z82pat00
};
sprite_pattern* z83_pat_dai8[8] =
{
  &z83pat00,
  &z83pat01,
  &z83pat02,
  &z83pat03,
  &z83pat04,
  &z83pat05,
  &patnull,
  &z83pat00
};
sprite_pattern** pats_dai8[3] =
{
  z81_pat_dai8,
  z82_pat_dai8,
  z83_pat_dai8
};


void dai8(sprite_status* actionwk) {
  short ano;

  if (actionwk->userflag.b.h < 0)
  {
    ano = ((short*)actionwk)[24];
    if (actwk[ano].actno != 44)
    {
      frameout(actionwk);
      return;
    }
    if (((short*)actionwk)[25] != ((short*)&actwk[ano])[25])
    {

      frameout(actionwk);
      return;
    }
    if (((short*)actionwk)[26] != ((short*)&actwk[ano])[26])
    {

      frameout(actionwk);
      return;
    }
  }

  switch (actionwk->r_no0)
  {
    case 0:
      act_init(actionwk);
      break;
    case 2:
      act_wait(actionwk);
      break;
    case 4:
      act_appear(actionwk);
      break;
    case 6:
      act_on(actionwk);
      break;
    case 8:
      act_off(actionwk);
      break;
  }
  actionsub(actionwk);
  if (actionwk->userflag.b.h >= 0)
  {
    frameout_s00(actionwk, ((short*)actionwk)[25]);
  }
}

static void act_init(sprite_status* actionwk) {
  short tbl00[2] = { 60, 0 };
  short tbl01[5] = { 60, 1, 60, 32, 0 };
  short tbl02[8] = { 90, 2, 180, 32, 16, 270, 64, 32 };
  sprite_status* a1;
  short *a5tbl, i, d6;

  switch (actionwk->userflag.b.h)
  {
    case 0:
      a5tbl = tbl00;
      break;
    case 1:
      a5tbl = tbl01;
      break;
    case 2:
      a5tbl = tbl02;
      break;
  }
  ((short*)actionwk)[23] = *a5tbl++;
  act_init_sub(actionwk, actionwk);

  d6 = *a5tbl++;
  for (i = 0; i < d6; ++i)
  {
    if (actwkchk(&a1) != 0)
    {
      frameout(actionwk);
      break;
    }
    a1->actno = actionwk->actno;
    ((short*)a1)[24] = (unsigned short)(actionwk - actwk);
    a1->userflag.b.h = -1;
    ((short*)a1)[23] = *a5tbl++;
    a1->xposi.w.h = actionwk->xposi.w.h + *a5tbl++;
    a1->yposi.w.h = actionwk->yposi.w.h + *a5tbl++;
    act_init_sub(actionwk, a1);
  }
}

static void act_init_sub(sprite_status* actionwk, sprite_status* a6) {
  a6->actflg |= 4;
  a6->sprpri = 3;
  a6->sprhs = 16;
  a6->sprhsize = 16;
  a6->sprvsize = 16;
  a6->sproffset = 920;
  a6->patbase = pats_dai8[stageno_i.b.l];
  a6->patno = 6;
  a6->r_no0 = 2;
  ((short*)a6)[25] = actionwk->xposi.w.h;
  ((short*)a6)[26] = actionwk->yposi.w.h;
}

static void act_wait(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] != 0) return;
  actionwk->r_no0 += 2;
}

void act_appear(sprite_status* actionwk) {
  patchg(actionwk, (unsigned char**)pchg);
  if (actionwk->patno == 0)
  {
    ((short*)actionwk)[23] = 120;
    actionwk->r_no0 += 2;
  }

}

void act_on(sprite_status* actionwk) {
  if (ridechk(actionwk, &actwk[0]) != 0) actionwk->actfree[21] = 255;
  else actionwk->actfree[21] = 0;

  if (--((short*)actionwk)[23] != 0) return;
  actionwk->mstno.w = 511;
  actionwk->r_no0 += 2;
  if (actionwk->actfree[21] != 0)
  {
    ride_on_clr(actionwk, &actwk[0]);
  }
}

void act_off(sprite_status* actionwk) {
  patchg(actionwk, (unsigned char**)pchg);

  if (actionwk->patno == 0)
  {
    ((short*)actionwk)[23] = 120;
    actionwk->r_no0 -= 2;
  }

}
