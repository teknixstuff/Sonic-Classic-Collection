#include "../EQU.h"
#include "HACHI8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../SUICIDE.h"

extern void patchg(sprite_status* patchgwk, unsigned char** pat_dat);

static void body(sprite_status* actionwk);
static void ball(sprite_status* actionwk);
static void ball_move(sprite_status* actionwk);

static char p00[4] = { 2, 0, 1, -1 };
static char* pchg[1] = { p00 };
static sprite_pattern body_pat0 =
{
  1,
  { { -19, -20, 0, 469 } }
};
static sprite_pattern body_pat1 =
{
  1,
  { { -19, -20, 0, 470 } }
};
static sprite_pattern kusari_00 =
{
  1,
  { { -8, -8, 0, 471 } }
};
static sprite_pattern ball_pat0 =
{
  1,
  { { -12, -12, 0, 472 } }
};
static sprite_pattern kusari_01 =
{
  1,
  { { -8, -8, 0, 473 } }
};
static sprite_pattern ball_pat1 =
{
  1,
  { { -12, -12, 0, 474 } }
};
sprite_pattern* pat_hachi8_e[4] =
{
  &body_pat0,
  &body_pat1,
  &kusari_00,
  &ball_pat0
};
sprite_pattern* pat_hachi8_b[4] =
{
  &body_pat0,
  &body_pat1,
  &kusari_01,
  &ball_pat1
};










void hachi8(sprite_status* actionwk) {
  if (actionwk->userflag.b.l == 0)
  {
    body(actionwk);
    return;
  }
  if (actionwk->userflag.b.l > 0)
  {
    kusari(actionwk);
    return;
  }
  ball(actionwk);
}

static void body(sprite_status* actionwk) {
  sprite_status* a1;

  if (enemy_suicide(actionwk) == -1) return;

  if (actionwk->r_no0 != 0)
  {
    body_move(actionwk);
    return;
  }

  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 3;
  actionwk->sprhs = 16;
  actionwk->sprhsize = 16;
  actionwk->sprvsize = 16;
  actionwk->colino = 46;
  actionwk->sproffset = 9301;
  ((short*)actionwk)[30] = actionwk->xposi.w.h;
  ((short*)actionwk)[31] = actionwk->yposi.w.h;
  ((short*)actionwk)[26] = 0;
  if (actionwk->userflag.b.h == 0)
  {
    actionwk->patbase = pat_hachi8_e;
    *(int*)&actionwk->actfree[0] = -65536;
    ((short*)actionwk)[25] = 128;
    ((short*)actionwk)[28] = 1024;
    ((short*)actionwk)[29] = 3;
  }
  else
  {
    actionwk->patbase = pat_hachi8_b;
    *(int*)&actionwk->actfree[0] = -32768;
    ((short*)actionwk)[25] = 256;
    ((short*)actionwk)[28] = 768;
    ((short*)actionwk)[29] = 4;
  }

  if (actwkchk2(actionwk, &a1) != 0)
  {
    frameout(actionwk);
    return;
  }
  a1->actno = actionwk->actno;
  ((unsigned short*)actionwk)[32] = a1 - actwk;
  ((unsigned short*)a1)[33] = actionwk - actwk;
  a1->actflg = actionwk->actflg;
  a1->sproffset = actionwk->sproffset;
  a1->patbase = actionwk->patbase;
  a1->userflag.b.h = actionwk->userflag.b.h;
  a1->userflag.b.l = -1;
  a1->xposi.w.h = actionwk->xposi.w.h;
  a1->yposi.w.h = actionwk->yposi.w.h;


  if (actionwk->userflag.b.h != 0)
  {
    body_move(actionwk);
    return;
  }
  if (actwkchk2(actionwk, &a1) != 0)
  {
    frameout(actionwk);
    return;
  }

  a1->actno = actionwk->actno;
  ((unsigned short*)actionwk)[33] = a1 - actwk;
  ((unsigned short*)a1)[33] = actionwk - actwk;
  a1->actflg = actionwk->actflg;
  a1->sproffset = actionwk->sproffset;
  a1->patbase = actionwk->patbase;
  a1->userflag.b.h = actionwk->userflag.b.h;
  a1->userflag.b.l = -2;
  a1->xposi.w.h = actionwk->xposi.w.h;
  a1->yposi.w.h = actionwk->yposi.w.h;
}

void body_move(sprite_status* actionwk) {
  unsigned short d0, sin, cos;
  int d0l;
  short t;

  actionwk->xposi.l += *(int*)&actionwk->actfree[0];
  --((short*)actionwk)[26];
  t = ((short*)actionwk)[26];
  if (t < 0)
  {
    ((int*)actionwk)[13] = ((short*)actionwk)[25];

    *(int*)&actionwk->actfree[0] = -*(int*)&actionwk->actfree[0];

    actionwk->actflg ^= 1;
    actionwk->cddat ^= 1;
  }

  actionwk->yposi.w.h = ((short*)actionwk)[31];
  actionwk->yposi.w.l = 0;
  ((short*)actionwk)[27] += ((short*)actionwk)[28];

  d0 = ((short*)actionwk)[27] >> 8;
  sinset(d0, (short*)&sin, (short*)&cos);
  d0l = sin << 16;
  d0l >>= ((short*)actionwk)[29];
  actionwk->yposi.l += d0l;
  patchg(actionwk, (unsigned char**)pchg);
  actionsub(actionwk);
  frameout_s00(actionwk, ((short*)actionwk)[30]);
}



















static void ball(sprite_status* actionwk) {
  sprite_status* a1;
  short i, d6;

  if (actionwk->r_no0 != 0)
  {
    ball_move(actionwk);
    return;
  }

  actionwk->r_no0 += 2;
  actionwk->sprhs = 12;
  actionwk->sprhsize = 12;
  actionwk->sprvsize = 12;
  actionwk->sprpri = 2;
  actionwk->patno = 3;
  actionwk->colino = 175;
  if (actionwk->userflag.b.l == -1)
  {
    ((short*)actionwk)[23] = 2048;
    ((short*)actionwk)[25] = 8;
    ((short*)actionwk)[26] = 9;
  }
  else
  {
    ((short*)actionwk)[23] = 4096;
    ((short*)actionwk)[25] = 8;
    ((short*)actionwk)[26] = 3;
  }

  d6 = ((short*)actionwk)[26];


  for (i = 0; i <= d6; ++i)
  {
    if (actwkchk2(actionwk, &a1) != 0)
    {

      frameout(actionwk);
      return;
    }

    a1->actno = actionwk->actno;
    actionwk->actfree[i + 8] = a1 - actwk;
    ((unsigned short*)a1)[33] = ((unsigned short*)actionwk)[33];

    a1->actflg = actionwk->actflg;
    a1->sproffset = actionwk->sproffset;
    a1->patbase = actionwk->patbase;
    a1->userflag.b.h = actionwk->userflag.b.h;
    a1->userflag.b.l = 1;
    a1->xposi.w.h = actionwk->xposi.w.h;
    a1->yposi.w.h = actionwk->yposi.w.h;
  }
  ball_move(actionwk);
}

static void ball_move(sprite_status* actionwk) {
  int_union d2, d3;
  short d0, d6, i, ano;
  unsigned short sin, cos;
  int d4, d5;

  ((short*)actionwk)[24] += ((short*)actionwk)[25];

  d6 = ((short*)actionwk)[23];
  ((short*)actionwk)[23] += ((short*)actionwk)[24];












  if ((((short*)actionwk)[25] >= 0
        && ((unsigned short*)actionwk)[24] < 16384
        && ((unsigned short*)actionwk)[23] >= 16384)
      ||
      (((short*)actionwk)[25] < 0
        && ((unsigned short*)actionwk)[24] >= 16384
        && ((unsigned short*)actionwk)[23] < 16384))
  {
    ((short*)actionwk)[25] = -((short*)actionwk)[25];
  }


  d6 = ((short*)actionwk)[26];
  ano = ((unsigned short*)actionwk)[33];
  d5 = actwk[ano].yposi.l + 786432;
  d4 = actwk[ano].xposi.l;
  d0 = ((short*)actionwk)[23] >> 8;
  sinset(d0, (short*)&sin, (short*)&cos);
  d3.l = sin;
  d2.l = cos;
  d3.l = (unsigned int)d3.l >> 16 & 65535 | d3.l << 16 & -65536;
  d2.l = (unsigned int)d2.l >> 16 & 65535 | d2.l << 16 & -65536;
  d3.w.l = 0;
  d2.w.l = 0;
  d3.l >>= 5;
  d2.l >>= 5;


  for (i = 0; i <= d6; ++i)
  {
    d5 += d3.l;
    d4 += d2.l;
    ano = actionwk->actfree[i + 8];
    actwk[ano].yposi.l = d5;
    actwk[ano].xposi.l = d4;
  }
  d5 += d3.l;
  d4 += d2.l;
  actionwk->yposi.l = d5;
  actionwk->xposi.l = d4;
  kusari_move(actionwk);
}

void kusari(sprite_status* actionwk) {
  if (actionwk->r_no0 != 0)
  {
    kusari_move(actionwk);
    return;
  }

  actionwk->r_no0 += 2;
  actionwk->sprhs = 8;
  actionwk->sprhsize = 8;
  actionwk->sprvsize = 8;
  actionwk->sprpri = 3;
  actionwk->patno = 2;
  kusari_move(actionwk);
}

void kusari_move(sprite_status* actionwk) {
  short ano;

  ano = ((unsigned short*)actionwk)[33];
  if (actwk[ano].actno != 46)
  {
    frameout(actionwk);
    return;
  }
  actionsub(actionwk);
}
