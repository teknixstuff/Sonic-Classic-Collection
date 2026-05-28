#include "../EQU.h"
#include "PROPERA8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../PLAYSUB.h"

static void a_move(sprite_status* actionwk);
static void b_init(sprite_status* actionwk);

static char p00[4] = { 10, 0, 1, -1 };
static char p01[8] = { 2, 0, 1, 2, 3, 4, 5, -1 };
static char* pchg[1] = { p00 };
static char* pchg1[1] = { p01 };
static sprite_pattern pat00 = { 1, { { -8, -40, 0, 454 } } };
static sprite_pattern pat01 = { 1, { { -8, -40, 0, 455 } } };
static sprite_pattern pat02 = { 1, { { -32, -4, 0, 456 } } };
static sprite_pattern pat03 = { 1, { { -24, -4, 0, 457 } } };
static sprite_pattern pat04 = { 1, { { -16, -4, 0, 458 } } };
static sprite_pattern pat05 = { 1, { { -4, -4, 0, 459 } } };
static sprite_pattern pat06 = { 1, { { -16, -4, 0, 460 } } };
static sprite_pattern pat07 = { 1, { { -24, -4, 0, 461 } } };
static sprite_pattern pat08 = { 1, { { -16, -4, 0, 462 } } };
static sprite_pattern pat09 = { 1, { { -12, -4, 0, 463 } } };
sprite_pattern* pat_propera[2] = {
  &pat00,
  &pat01
};
sprite_pattern* pat_propera1[8] =
{
  &pat02,
  &pat03,
  &pat04,
  &pat05,
  &pat06,
  &pat07,
  &pat08,
  &pat09
};
























void propera(sprite_status* actionwk) {
  if (actionwk->userflag.b.h == 0)
  {
    propera0(actionwk);
  }
  else
    propera1(actionwk);
}

void propera0(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      a_init(actionwk);
      break;
    case 2:
      a_fall(actionwk);
      break;
    case 4:
      a_move(actionwk);
      break;
  }
  patchg(actionwk, (unsigned char**)pchg);
  actionsub(actionwk);
  frameout_s00(actionwk, ((short*)actionwk)[26]);
}

void a_init(sprite_status* actionwk) {
  sprite_status *a1, *a2;

  ((short*)actionwk)[26] = actionwk->xposi.w.h;

  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 4;
  actionwk->sproffset = 874;
  ((short*)actionwk)[23] = 128;
  ((int*)actionwk)[12] = 65536;
  actionwk->patbase = pat_propera;
  actionwk->sprhs = 8;
  actionwk->sprhsize = 8;
  actionwk->sprvsize = 46;

  if (actwkchk2(actionwk, &a1) != 0)
  {
    frameout(actionwk);
    return;
  }

  a1->actno = actionwk->actno;
  ((unsigned short*)a1)[33] = actionwk - actwk;
  a1->userflag.b.h = 1;
  a2 = a1;
  if (actwkchk2(actionwk, &a1) != 0)
  {
    frameout(actionwk);
    return;
  }

  a1->actno = actionwk->actno;
  ((unsigned short*)a1)[33] = actionwk - actwk;
  a1->userflag.b.h = -1;
  ((short*)a1)[32] = -44;
  ((short*)a2)[32] = 20;
  a2->actflg |= 2;
  a2->cddat |= 2;

  a_init_sub(a1);
  a_init_sub(a2);
  ((unsigned short*)a2)[33] = actionwk - actwk;
}

void a_init_sub(sprite_status* actionwk) {
  actionwk->actflg |= 4;
  actionwk->sproffset = 874;
  actionwk->sprpri = 3;
  actionwk->patbase = pat_propera1;
  actionwk->sprhs = 32;
  actionwk->sprhsize = 32;
  actionwk->sprvsize = 28;
}

void a_fall(sprite_status* actionwk) {
  short d1;

  ++actionwk->yposi.w.h;
  d1 = emycol_d(actionwk);
  if (d1 < 0)
  {
    actionwk->yposi.w.h += d1;
    actionwk->r_no0 += 2;
  }
}

static void a_move(sprite_status* actionwk) {
  short d1;

  actionwk->xposi.l += ((int*)actionwk)[12];
  d1 = emycol_d(actionwk);
  actionwk->yposi.w.h += d1;
  if (--((short*)actionwk)[23] != 0) return;
  ((int*)actionwk)[12] = -((int*)actionwk)[12];

  ((short*)actionwk)[23] = 128;
}











void propera1(sprite_status* actionwk) {
  void(*tbl[9])(sprite_status*) =
  {
    &b_init,
    &b_close,
    &b_close1,
    &b_closed,
    &b_closed1,
    &b_open,
    &b_open1,
    &b_opend,
    &b_opend1
  };
  short ano;

  ano = ((short*)actionwk)[33];
  if (actwk[ano].actno != 40)
  {
    frameout(actionwk);
    return;
  }

  tbl[actionwk->r_no0 / 2](actionwk);
  actionwk->xposi.w.h = actwk[ano].xposi.w.h;
  actionwk->yposi.w.h = actwk[ano].yposi.w.h;
  actionwk->yposi.w.h += ((short*)actionwk)[32];
  actionsub(actionwk);
}

static void b_init(sprite_status* actionwk) {
  if (actionwk->userflag.b.h < 0)
  {
    actionwk->r_no0 = 10;
    b_open(actionwk);
  }
  else
  {
    actionwk->r_no0 = 2;
    b_close(actionwk);
  }
}

void b_close(sprite_status* actionwk) {
  actionwk->patno = 6;
  ((short*)actionwk)[23] = 5;
  actionwk->colino = 0;
  actionwk->r_no0 += 2;
  b_close1(actionwk);
}

void b_close1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] != 0) return;
  actionwk->r_no0 += 2;
  b_closed(actionwk);
}

void b_closed(sprite_status* actionwk) {
  actionwk->patno = 7;
  ((short*)actionwk)[23] = 73;
  actionwk->r_no0 += 2;
  b_closed1(actionwk);
}

void b_closed1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] != 0) return;
  actionwk->r_no0 += 2;
  b_open(actionwk);
}

void b_open(sprite_status* actionwk) {
  actionwk->patno = 6;
  ((short*)actionwk)[23] = 5;
  actionwk->r_no0 += 2;

}

void b_open1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] != 0) return;
  actionwk->r_no0 += 2;
  b_opend(actionwk);
}

void b_opend(sprite_status* actionwk) {
  actionwk->mstno.w = 255;
  ((short*)actionwk)[23] = 73;
  actionwk->colino = 168;
  actionwk->colicnt = 0;
  actionwk->r_no0 += 2;

}

void b_opend1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] != 0)
  {
    patchg(actionwk, (unsigned char**)pchg1);
    return;
  }
  actionwk->r_no0 -= 14;
  b_close(actionwk);
}
