#include "../EQU.h"
#include "FRIEND1.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../ETC.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void t_roll(int cos_shift, int sin_shift, sprite_status* pActwk);
static void rev_h(sprite_status* pActwk);
static void set_sproffset(sprite_status* pActwk);
static void t_init(sprite_status* pActwk);
static void t_move(sprite_status* pActwk);
static void t_movie(sprite_status* pActwk);
static void p_init(sprite_status* pActwk);
static void p_move(sprite_status* pActwk);
static void p_movie(sprite_status* pActwk);

static unsigned char pchg00[4] = { 29, 0, 1, 255 };
static unsigned char pchg01[30] =
{
  0,
  0, 0, 2,
  0, 0, 2,
  1, 1, 2, 2,
  1, 1, 2, 2,
  0, 0, 2,
  0, 0, 2,
  1, 1, 2, 2,
  1, 1, 2, 2,
  255
};
static unsigned char pchg10[58] =
{
  0,
  3, 3, 2, 3,
  3, 2, 3, 3,
  2, 3, 3, 2,
  3, 3, 2, 2,
  3, 3, 2, 2,
  3, 3, 2, 2,
  3, 3, 2, 2,
  5, 5, 2, 5,
  5, 2, 5, 5,
  2, 5, 5, 2,
  5, 5, 2, 2,
  5, 5, 2, 2,
  5, 5, 2, 2,
  5, 5, 2, 2,
  255
};
static unsigned char* pchg0[2] = { pchg00, pchg01 };
static unsigned char* pchg1[1] = { pchg10 };
static sprite_pattern z11a_spr_flicky1 = { 1, { { -8, -8, 0, 536 } } };
static sprite_pattern z11b_spr_flicky1 = { 1, { { -8, -8, 0, 521 } } };
static sprite_pattern z11c_spr_flicky1 = { 1, { { -8, -8, 0, 502 } } };
static sprite_pattern z12a_spr_flicky1 = { 1, { { -8, -8, 0, 512 } } };
static sprite_pattern z12c_spr_flicky1 = { 1, { { -8, -8, 0, 503 } } };
static sprite_pattern z13_spr_flicky1 = { 1, { { -8, -8, 0, 491 } } };
static sprite_pattern z11a_spr_flicky2 = { 1, { { -8, -8, 0, 537 } } };
static sprite_pattern z11b_spr_flicky2 = { 1, { { -8, -8, 0, 522 } } };
static sprite_pattern z11c_spr_flicky2 = { 1, { { -8, -8, 0, 503 } } };
static sprite_pattern z12a_spr_flicky2 = { 1, { { -8, -8, 0, 513 } } };
static sprite_pattern z12c_spr_flicky2 = { 1, { { -8, -8, 0, 504 } } };
static sprite_pattern z13_spr_flicky2 = { 1, { { -8, -8, 0, 492 } } };
static sprite_pattern z11a_spr_ricky1 = { 1, { { -12, -8, 0, 538 } } };
static sprite_pattern z11b_spr_ricky1 = { 1, { { -12, -8, 0, 523 } } };
static sprite_pattern z11c_spr_ricky1 = { 1, { { -12, -8, 0, 504 } } };
static sprite_pattern z12a_spr_ricky1 = { 1, { { -12, -8, 0, 514 } } };
static sprite_pattern z12c_spr_ricky1 = { 1, { { -12, -8, 0, 505 } } };
static sprite_pattern z13_spr_ricky1 = { 1, { { -12, -8, 0, 493 } } };
static sprite_pattern z11a_spr_ricky2 = { 1, { { -12, -8, 0, 539 } } };
static sprite_pattern z11b_spr_ricky2 = { 1, { { -12, -8, 0, 524 } } };
static sprite_pattern z11c_spr_ricky2 = { 1, { { -12, -8, 0, 505 } } };
static sprite_pattern z12a_spr_ricky2 = { 1, { { -12, -8, 0, 515 } } };
static sprite_pattern z12c_spr_ricky2 = { 1, { { -12, -8, 0, 506 } } };
static sprite_pattern z13_spr_ricky2 = { 1, { { -12, -8, 0, 494 } } };
static sprite_pattern z11a_spr_ricky3 = { 1, { { -12, -8, 0, 540 } } };
static sprite_pattern z11b_spr_ricky3 = { 1, { { -12, -8, 0, 525 } } };
static sprite_pattern z11c_spr_ricky3 = { 1, { { -12, -8, 0, 506 } } };
static sprite_pattern z12a_spr_ricky3 = { 1, { { -12, -8, 0, 516 } } };
static sprite_pattern z12c_spr_ricky3 = { 1, { { -12, -8, 0, 507 } } };
static sprite_pattern z13_spr_ricky3 = { 1, { { -12, -8, 0, 495 } } };
static sprite_pattern z11a_spr_ricky4 = { 1, { { -12, -8, 0, 541 } } };
static sprite_pattern z11b_spr_ricky4 = { 1, { { -12, -8, 0, 526 } } };
static sprite_pattern z11c_spr_ricky4 = { 1, { { -12, -8, 0, 507 } } };
static sprite_pattern z12a_spr_ricky4 = { 1, { { -12, -8, 0, 517 } } };
static sprite_pattern z12c_spr_ricky4 = { 1, { { -12, -8, 0, 508 } } };
static sprite_pattern z13_spr_ricky4 = { 1, { { -12, -8, 0, 496 } } };
static sprite_pattern z11a_spr_friend0 = { 0, { { -12, -8, 0, 541 } } };
static sprite_pattern z11b_spr_friend0 = { 0, { { -12, -8, 0, 526 } } };
static sprite_pattern z11c_spr_friend0 = { 0, { { -12, -8, 0, 507 } } };
static sprite_pattern z12a_spr_friend0 = { 0, { { -12, -8, 0, 517 } } };
static sprite_pattern z12c_spr_friend0 = { 0, { { -12, -8, 0, 508 } } };
static sprite_pattern z13_spr_friend0 = { 0, { { -12, -8, 0, 496 } } };
static sprite_pattern z11a_spr_ricky5 = { 1, { { -12, -8, 0, 542 } } };
static sprite_pattern z11b_spr_ricky5 = { 1, { { -12, -8, 0, 527 } } };
static sprite_pattern z11c_spr_ricky5 = { 1, { { -12, -8, 0, 508 } } };
static sprite_pattern z12a_spr_ricky5 = { 1, { { -12, -8, 0, 518 } } };
static sprite_pattern z12c_spr_ricky5 = { 1, { { -12, -8, 0, 509 } } };
static sprite_pattern z13_spr_ricky5 = { 1, { { -12, -8, 0, 497 } } };
sprite_pattern* z11a_pat_friend0[3] =
{
  &z11a_spr_flicky1,
  &z11a_spr_flicky2,
  &z11a_spr_friend0
};
sprite_pattern* z11b_pat_friend0[3] =
{
  &z11b_spr_flicky1,
  &z11b_spr_flicky2,
  &z11b_spr_friend0
};
sprite_pattern* z11c_pat_friend0[3] =
{
  &z11c_spr_flicky1,
  &z11c_spr_flicky2,
  &z11c_spr_friend0
};
sprite_pattern* z12a_pat_friend0[3] =
{
  &z12a_spr_flicky1,
  &z12a_spr_flicky2,
  &z12a_spr_friend0
};
sprite_pattern* z12c_pat_friend0[3] =
{
  &z12c_spr_flicky1,
  &z12c_spr_flicky2,
  &z12c_spr_friend0
};
sprite_pattern* z13_pat_friend0[3] =
{
  &z13_spr_flicky1,
  &z13_spr_flicky2,
  &z13_spr_friend0
};
static sprite_pattern** pats_friend0[3][3] =
{
  { z11b_pat_friend0, z11a_pat_friend0, z11c_pat_friend0 },
  { z12a_pat_friend0, z12a_pat_friend0, z12c_pat_friend0 },
  { 0, 0, z13_pat_friend0 }
};
sprite_pattern* z11a_pat_friend1[6] =
{
  &z11a_spr_ricky1,
  &z11a_spr_ricky2,
  &z11a_spr_friend0,
  &z11a_spr_ricky3,
  &z11a_spr_ricky4,
  &z11a_spr_ricky5
};
sprite_pattern* z11b_pat_friend1[6] =
{
  &z11b_spr_ricky1,
  &z11b_spr_ricky2,
  &z11b_spr_friend0,
  &z11b_spr_ricky3,
  &z11b_spr_ricky4,
  &z11b_spr_ricky5
};
sprite_pattern* z11c_pat_friend1[6] =
{
  &z11c_spr_ricky1,
  &z11c_spr_ricky2,
  &z11c_spr_friend0,
  &z11c_spr_ricky3,
  &z11c_spr_ricky4,
  &z11c_spr_ricky5
};
sprite_pattern* z12a_pat_friend1[6] =
{
  &z12a_spr_ricky1,
  &z12a_spr_ricky2,
  &z12a_spr_friend0,
  &z12a_spr_ricky3,
  &z12a_spr_ricky4,
  &z12a_spr_ricky5
};
sprite_pattern* z12c_pat_friend1[6] =
{
  &z12c_spr_ricky1,
  &z12c_spr_ricky2,
  &z12c_spr_friend0,
  &z12c_spr_ricky3,
  &z12c_spr_ricky4,
  &z12c_spr_ricky5
};
sprite_pattern* z13_pat_friend1[6] =
{
  &z13_spr_ricky1,
  &z13_spr_ricky2,
  &z13_spr_friend0,
  &z13_spr_ricky3,
  &z13_spr_ricky4,
  &z13_spr_ricky5
};
static sprite_pattern** pats_friend1[3][3] =
{
  { z11b_pat_friend1, z11a_pat_friend1, z11c_pat_friend1 },
  { z12a_pat_friend1, z12a_pat_friend1, z12c_pat_friend1 },
  { 0, 0, z13_pat_friend1 }
};
static unsigned short tbl0sproffset[11] =
{
  1271,  904, 1123,    0,
  1271,  911, 1121,    0,
     0,    0,  975
};









static void t_roll(int cos_shift, int sin_shift, sprite_status* pActwk) {
  unsigned short sin, cos;

  sinset(pActwk->actfree[4], (short*)&sin, (short*)&cos);
  cos = (short)cos >> cos_shift;
  sin = (short)sin >> sin_shift;
  cos += ((unsigned short*)pActwk)[23];
  sin += ((unsigned short*)pActwk)[24];
  pActwk->xposi.w.h = cos;
  pActwk->yposi.w.h = sin;
}


static void rev_h(sprite_status* pActwk) {
  pActwk->actflg ^= 1;
  pActwk->cddat ^= 1;
}


static void set_sproffset(sprite_status* pActwk) {
  int temp;

  temp = stageno.b.l;
  temp *= 4;
  temp += time_flag;
  temp &= 255;
  pActwk->sproffset = tbl0sproffset[temp];
}



void friend1(sprite_status* pActwk) {
  void(*tbl_f[3])(sprite_status*) =
  {
    &t_init,
    &t_move,
    &t_movie
  };
  void(*tbl_r[3])(sprite_status*) =
  {
    &p_init,
    &p_move,
    &p_movie
  };

  if (friend_suicide(pActwk)) return;
  if ((pActwk->userflag.b.h & 127) == 0)
    tbl_f[pActwk->r_no0 / 2](pActwk);
  else
    tbl_r[pActwk->r_no0 / 2](pActwk);
}




static void t_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg = 4;
  pActwk->sprvsize = 8;
  pActwk->sprhs = 8;
  pActwk->sprpri = 4;
  pActwk->sprhsize = 8;
  pActwk->patbase = pats_friend0[stageno_i.b.l][time_flag_i & 0x7F];
  ((short*)pActwk)[23] = pActwk->xposi.w.h;
  ((short*)pActwk)[24] = pActwk->yposi.w.h;
  rev_h(pActwk);
  set_sproffset(pActwk);

  if (pActwk->userflag.b.h >= 0)
  {
    pActwk->sprpri = 4;
    pActwk->sproffset |= 32768;
    pActwk->actfree[4] = 1;
    pActwk->actfree[5] = 1;
  }
  else
  {
    pActwk->r_no0 += 2;
    pActwk->mstno.b.h = 1;
    pActwk->sprpri = 3;
  }
}



static void t_move(sprite_status* pActwk) {
  unsigned char temp;

  t_roll(1, 1, pActwk);
  temp = pActwk->actfree[4] + pActwk->actfree[5];
  if ((unsigned char)(temp - 1) < 127) goto label1;
  temp = pActwk->actfree[4];
  ((char*)pActwk)[51] *= -1;
  rev_h(pActwk);
label1:
  pActwk->actfree[4] = temp;
  patchg(pActwk, pchg0);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[23]);
}



static void t_movie(sprite_status* pActwk) {
  sprite_status* tempact;

  tempact = &actwk[((short*)pActwk)[33]];
  if (tempact->actno != 46)
  {
    frameout(pActwk);
    return;
  }
  if (((char*)tempact)[67])
  {
    frameout(pActwk);
    return;
  }

  t_roll(3, 4, pActwk);

  pActwk->actfree[4] += 4;
  if ((pActwk->actfree[4] & 127) == 0)
    rev_h(pActwk);
  else
  {
    patchg(pActwk, pchg0);
    actionsub(pActwk);
  }
}




static void p_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg = 4;
  pActwk->sprvsize = 8;
  pActwk->sprhs = 8;
  pActwk->sprpri = 4;
  pActwk->sprhsize = 8;
  pActwk->patbase = pats_friend1[stageno_i.b.l][time_flag_i & 0x7F];
  ((short*)pActwk)[23] = pActwk->xposi.w.h;
  set_sproffset(pActwk);

  if (pActwk->userflag.b.h >= 0)
  {
    ((int*)pActwk)[12] = 65536;
    ((int*)pActwk)[13] = -0x40000;
  }
  else
  {
    pActwk->r_no0 = 4;
    rev_h(pActwk);
  }
}



static void p_move(sprite_status* pActwk) {
  short temp;

  pActwk->xposi.l += ((int*)pActwk)[12];
  pActwk->yposi.l += ((int*)pActwk)[13];

  if ((((int*)pActwk)[13] += 8192) < 0)
    pActwk->patno = 0;
  else
    pActwk->patno = 1;

  if ((temp = emycol_d(pActwk)) <= 0)
  {
    pActwk->yposi.w.h += temp;
    ((int*)pActwk)[13] = -0x40000;
    ((int*)pActwk)[12] *= -1;
    rev_h(pActwk);
  }
  actionsub(pActwk);
  frameout_s(pActwk);
}



static void p_movie(sprite_status* pActwk) {
  sprite_status* tempact;

  tempact = &actwk[((short*)pActwk)[33]];
  if (tempact->actno != 46)
  {
    frameout(pActwk);
    return;
  }
  if (((char*)tempact)[67])
  {
    frameout(pActwk);
    return;
  }
  patchg(pActwk, pchg1);
  actionsub(pActwk);
}
