#include "../EQU.h"
#include "FRIEND7.h"
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
static void p_rev(sprite_status* pActwk);
static void p_movie(sprite_status* pActwk);

unsigned char pchg00[4] = { 3, 0, 1, 255 };
unsigned char pchg01[30] =
{
  0, 0, 0, 2, 0, 0, 2, 1, 1, 2,
  2, 1, 1, 2, 2, 0, 0, 2, 0, 0,
  2, 1, 1, 2, 2, 1, 1, 2, 2, 255
};
unsigned char pchg10[58] =
{
  0, 3, 3, 2, 3, 3, 2, 3, 3, 2,
  3, 3, 2, 3, 3, 2, 2, 3, 3, 2,
  2, 3, 3, 2, 2, 3, 3, 2, 2, 4,
  4, 2, 4, 4, 2, 4, 4, 2, 4, 4,
  2, 4, 4, 2, 2, 4, 4, 2, 2, 4,
  4, 2, 2, 4, 4, 2, 2, 255
};
unsigned char* pchg0[2] =
{
  pchg00,
  pchg01
};
unsigned char* pchg1[1] = { pchg10 };
sprite_pattern spr_flicky1 = { 1, { { -8, -8, 0, 462 } } };
sprite_pattern z73_spr_flicky1 = { 1, { { -8, -8, 0, 441 } } };
sprite_pattern spr_flicky2 = { 1, { { -8, -8, 0, 463 } } };
sprite_pattern z73_spr_flicky2 = { 1, { { -8, -8, 0, 442 } } };
sprite_pattern spr_ricky1 = { 1, { { -8, -12, 0, 464 } } };
sprite_pattern z73_spr_ricky1 = { 1, { { -8, -12, 0, 443 } } };
sprite_pattern spr_ricky2 = { 1, { { -8, -12, 0, 465 } } };
sprite_pattern z73_spr_ricky2 = { 1, { { -8, -12, 0, 444 } } };
sprite_pattern spr_ricky3 = { 1, { { -8, -12, 0, 466 } } };
sprite_pattern z73_spr_ricky3 = { 1, { { -8, -12, 0, 445 } } };
sprite_pattern spr_ricky4 = { 1, { { -8, -4, 0, 467 } } };
sprite_pattern z73_spr_ricky4 = { 1, { { -8, -4, 0, 446 } } };
sprite_pattern spr_friend0 = { 0, { { -8, -4, 0, 468 } } };
sprite_pattern z73_spr_friend0 = { 0, { { -8, -4, 0, 446 } } };
sprite_pattern* z7_pat_friend0[3] =
{
  &spr_flicky1,
  &spr_flicky2,
  &spr_friend0
};
sprite_pattern* z73_pat_friend0[3] =
{
  &z73_spr_flicky1,
  &z73_spr_flicky2,
  &z73_spr_friend0
};
sprite_pattern** pats_friend0[3] =
{
  z7_pat_friend0,
  z7_pat_friend0,
  z73_pat_friend0
};
sprite_pattern* z7_pat_friend1[5] =
{
  &spr_ricky1,
  &spr_ricky2,
  &spr_friend0,
  &spr_ricky3,
  &spr_ricky4
};
sprite_pattern* z73_pat_friend1[5] =
{
  &z73_spr_ricky1,
  &z73_spr_ricky2,
  &z73_spr_friend0,
  &z73_spr_ricky3,
  &z73_spr_ricky4
};
sprite_pattern** pats_friend1[3] =
{
  z7_pat_friend1,
  z7_pat_friend1,
  z73_pat_friend1
};
unsigned short tbl0sproffset[11] =
{
  918, 918, 918, 0,
  918, 918, 918, 0,
    0,   0, 918
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



void friend7(sprite_status* pActwk) {
  void(*tbl_f[3])(sprite_status*) =
  {
    &t_init,
    &t_move,
    &t_movie
  };
  void(*tbl_r[5])(sprite_status*) =
  {
    &p_init,
    &p_move,
    &p_move,
    &p_rev,
    &p_movie
  };

  if (friend_suicide(pActwk)) return;
  if (!(pActwk->userflag.b.h & 127))
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
  pActwk->patbase = pats_friend0[stageno_i.b.l];
  ((short*)pActwk)[23] = pActwk->xposi.w.h;
  ((short*)pActwk)[24] = pActwk->yposi.w.h;
  rev_h(pActwk);
  set_sproffset(pActwk);

  if (pActwk->userflag.b.h >= 0)
  {


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
  if (tempact->actno != 39)
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
  if (!(pActwk->actfree[4] & 127))
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
  pActwk->sprvsize = 12;
  pActwk->sprhs = 8;
  pActwk->sprpri = 4;
  pActwk->sprhsize = 8;
  pActwk->patbase = pats_friend1[stageno_i.b.l];

  set_sproffset(pActwk);

  if (pActwk->userflag.b.h >= 0)
  {
    ((int*)pActwk)[12] = 65536;
    ((int*)pActwk)[13] = -0x40000;
  }
  else
  {
    pActwk->r_no0 = 8;
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
    pActwk->r_no0 += 2;
    pActwk->yposi.w.h += temp;
    ((int*)pActwk)[13] = -0x40000;
  }
  actionsub(pActwk);
  frameout_s(pActwk);
}



static void p_rev(sprite_status* pActwk) {
  pActwk->r_no0 = 2;
  ((int*)pActwk)[12] *= -1;
  rev_h(pActwk);

  actionsub(pActwk);
  frameout_s(pActwk);
}


static void p_movie(sprite_status* pActwk) {
  sprite_status* tempact;

  tempact = &actwk[((short*)pActwk)[33]];
  if (tempact->actno != 39)
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
