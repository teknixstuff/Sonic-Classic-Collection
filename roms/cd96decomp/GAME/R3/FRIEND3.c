#include "../EQU.h"
#include "FRIEND3.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../ETC.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void t_init(sprite_status* actionwk);
static void t_move(sprite_status* actionwk);
static void t_movie(sprite_status* actionwk);
static void t_roll(sprite_status* actionwk, short d2, short d3);
static void p_init(sprite_status* actionwk);
static void p_move(sprite_status* actionwk);
static void p_end(sprite_status* actionwk);
static void p_rev(sprite_status* actionwk);
static void p_movie(sprite_status* actionwk);
static void set_sproffset(sprite_status* actionwk);

static sprite_pattern patnull = { 1, { { 0, 0, 0, 0 } } };
static sprite_pattern pat00 = { 1, { { -8, -8, 0, 491 } } };
static sprite_pattern z31apat00 = { 1, { { -8, -8, 0, 538 } } };
static sprite_pattern z33pat00 = { 1, { { -8, -8, 0, 542 } } };
static sprite_pattern pat01 = { 1, { { -8, -8, 0, 492 } } };
static sprite_pattern z31apat01 = { 1, { { -8, -8, 0, 539 } } };
static sprite_pattern z33pat01 = { 1, { { -8, -8, 0, 543 } } };
static sprite_pattern pat02 = { 1, { { -8, -12, 0, 493 } } };
static sprite_pattern z31apat02 = { 1, { { -8, -12, 0, 540 } } };
static sprite_pattern z33pat02 = { 1, { { -8, -12, 0, 544 } } };
static sprite_pattern pat03 = { 1, { { -8, -12, 0, 494 } } };
static sprite_pattern z31apat03 = { 1, { { -8, -12, 0, 541 } } };
static sprite_pattern z33pat03 = { 1, { { -8, -12, 0, 545 } } };
static sprite_pattern pat04 = { 1, { { -8, -12, 0, 495 } } };
static sprite_pattern z31apat04 = { 1, { { -8, -12, 0, 542 } } };
static sprite_pattern z33pat04 = { 1, { { -8, -12, 0, 546 } } };
static sprite_pattern pat05 = { 1, { { -8, -4, 0, 496 } } };
static sprite_pattern z31apat05 = { 1, { { -8, -4, 0, 543 } } };
static sprite_pattern z33pat05 = { 1, { { -8, -4, 0, 547 } } };
static sprite_pattern* pat_friend0[3] =
{
  &pat00,
  &pat01,
  &patnull
};
static sprite_pattern* z31a_pat_friend0[3] =
{
  &z31apat00,
  &z31apat01,
  &patnull
};
static sprite_pattern* z33_pat_friend0[3] =
{
  &z33pat00,
  &z33pat01,
  &patnull
};
static sprite_pattern** pats_friend0[3][3] =
{
  { z31a_pat_friend0, z31a_pat_friend0, pat_friend0 },
  { pat_friend0, z31a_pat_friend0, pat_friend0 },
  { 0, 0, z33_pat_friend0 }
};
static sprite_pattern* pat_friend1[5] =
{
  &pat02,
  &pat03,
  &patnull,
  &pat04,
  &pat05
};
static sprite_pattern* z31a_pat_friend1[5] =
{
  &z31apat02,
  &z31apat03,
  &patnull,
  &z31apat04,
  &z31apat05
};
static sprite_pattern* z33_pat_friend1[5] =
{
  &z33pat02,
  &z33pat03,
  &patnull,
  &z33pat04,
  &z33pat05
};
static sprite_pattern** pats_friend1[3][3] =
{
  { z31a_pat_friend1, z31a_pat_friend1, pat_friend1 },
  { pat_friend1, z31a_pat_friend1, pat_friend1 },
  { 0, 0, z33_pat_friend1 }
};
static char p00[4] = { 3, 0, 1, -1 };
static char p01[30] =
{
  0, 0, 0, 2, 0, 0, 2, 1, 1, 2,
  2, 1, 1, 2, 2, 0, 0, 2, 0, 0,
  2, 1, 1, 2, 2, 1, 1, 2, 2, -1
};
static char p10[58] =
{
  0, 3, 3, 2, 3, 3, 2, 3, 3, 2,
  3, 3, 2, 3, 3, 2, 2, 3, 3, 2,
  2, 3, 3, 2, 2, 3, 3, 2, 2, 4,
  4, 2, 4, 4, 2, 4, 4, 2, 4, 4,
  2, 4, 4, 2, 2, 4, 4, 2, 2, 4,
  4, 2, 2, 4, 4, 2, 2, -1
};
static char* pchg0[2] = { p00, p01 };
static char* pchg1[1] = { p10 };
static unsigned short tbl0sproffset[11] = { 1943, 986, 986, 0, 1943, 986, 986, 0, 0, 0, 986 };





void friend3(sprite_status* actionwk) {

  if (friend_suicide(actionwk) == -1) return;


  if (actionwk->userflag.b.h & 127)
    pocky(actionwk);
  else
    inco(actionwk);
}

void inco(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      t_init(actionwk);
      break;
    case 2:
      t_move(actionwk);
      break;
    case 4:
      t_movie(actionwk);
      break;
  }
}

static void t_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg = 4;

  actionwk->sprvsize = 8;
  actionwk->sprhs = 8;
  actionwk->sprpri = 1;
  actionwk->sprhsize = 8;
  actionwk->patbase = pats_friend0[stageno_i.b.l][time_flag_i & 0x7F];
  ((short*)actionwk)[23] = actionwk->xposi.w.h;
  ((short*)actionwk)[24] = actionwk->yposi.w.h;
  actionwk->actflg ^= 1, actionwk->cddat ^= 1;
  set_sproffset(actionwk);

  if (actionwk->userflag.b.h < 0)
  {
    actionwk->r_no0 += 2;
    actionwk->mstno.b.h = 1;
    actionwk->sprpri = 3;
  }
  else
  {
    actionwk->sprpri = 1;
    actionwk->sproffset |= 32768;
    actionwk->actfree[4] = 1;
    actionwk->actfree[5] = 1;
  }
}

static void t_move(sprite_status* actionwk) {
  char d0, d1;

  t_roll(actionwk, 1, 1);
  d1 = d0 = (char)actionwk->actfree[4] + (char)actionwk->actfree[5];
  d1 += 126;
  if (d1 >= 0)
  {
    d0 = actionwk->actfree[4];
    actionwk->actfree[5] = -actionwk->actfree[5];
    actionwk->actflg ^= 1, actionwk->cddat ^= 1;
  }

  actionwk->actfree[4] = d0;
  patchg(actionwk, (unsigned char**)pchg0);
  actionsub(actionwk);
  frameout_s00(actionwk, ((short*)actionwk)[23]);
}

static void t_movie(sprite_status* actionwk) {
  sprite_status* a1;

  a1 = &actwk[((unsigned short*)actionwk)[33]];
  if (a1->actno != 56 || a1->actfree[21])
  {
    frameout(actionwk);
    return;
  }
  t_roll(actionwk, 3, 4);
  actionwk->actfree[4] += 4;
  if (!(actionwk->actfree[4] & 127)) actionwk->actflg ^= 1, actionwk->cddat ^= 1;

  patchg(actionwk, (unsigned char**)pchg0);
  actionsub(actionwk);
}

static void t_roll(sprite_status* actionwk, short d2, short d3) {
  short sin, cos;

  sinset(actionwk->actfree[4], &sin, &cos);
  cos >>= d2;
  sin >>= d3;
  actionwk->xposi.w.h = cos + ((short*)actionwk)[23];
  actionwk->yposi.w.h = sin + ((short*)actionwk)[24];
}

void pocky(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      p_init(actionwk);
      break;
    case 2:
      p_move(actionwk);
      break;
    case 4:
      p_move(actionwk);
      break;
    case 6:
      p_rev(actionwk);
      break;
    case 8:
      p_movie(actionwk);
      break;
  }
}

static void p_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprvsize = 12;
  actionwk->sprhs = 8;
  actionwk->sprpri = 4;
  actionwk->sprhsize = 8;
  actionwk->patbase = pats_friend1[stageno_i.b.l][time_flag_i & 0x7F];

  set_sproffset(actionwk);
  if (actionwk->userflag.b.h < 0)
  {
    actionwk->r_no0 = 8;
    actionwk->actflg ^= 1, actionwk->cddat ^= 1;
  }
  else
  {
    ((int*)actionwk)[12] = 65536;
    ((int*)actionwk)[13] = -0x40000;
  }
}

static void p_move(sprite_status* actionwk) {
  short d1;

  actionwk->xposi.l += ((int*)actionwk)[12];
  actionwk->yposi.l += ((int*)actionwk)[13];

  ((int*)actionwk)[13] += 8192;
  if (((int*)actionwk)[13] < 0)
    actionwk->patno = 0;
  else
    actionwk->patno = 1;
  d1 = emycol_d(actionwk);
  if (d1 < 0)
  {
    actionwk->r_no0 += 2;
    actionwk->yposi.w.h += d1;
    ((int*)actionwk)[13] = -0x40000;
  }
  p_end(actionwk);
}

static void p_end(sprite_status* actionwk) {
  actionsub(actionwk);
  frameout_s(actionwk);
}

static void p_rev(sprite_status* actionwk) {
  actionwk->r_no0 = 2;
  ((int*)actionwk)[12] = -((int*)actionwk)[12];

  actionwk->actflg ^= 1, actionwk->cddat ^= 1;
  p_end(actionwk);
}

static void p_movie(sprite_status* actionwk) {
  sprite_status* a1;

  a1 = &actwk[((unsigned short*)actionwk)[33]];
  if (a1->actno != 56 || a1->actfree[21])
  {
    frameout(actionwk);
    return;
  }
  patchg(actionwk, (unsigned char**)pchg1);
  actionsub(actionwk);
}

static void set_sproffset(sprite_status* actionwk) {
  unsigned short* a1;
  unsigned short d0;

  a1 = tbl0sproffset;
  d0 = (stageno.w + 1 << 2) + (unsigned short)time_flag;
  actionwk->sproffset = a1[d0];
}
