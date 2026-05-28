#include "../EQU.h"
#include "FRIEND6.h"
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

static sprite_pattern patnull =
{
  1,
  { { 0, 0, 0, 0 } }
};
static sprite_pattern pat00 =
{
  1,
  { { -12, -8, 0, 435 } }
};
static sprite_pattern pat01 =
{
  1,
  { { -12, -8, 0, 436 } }
};
static sprite_pattern pat02 =
{
  1,
  { { -8, -12, 0, 437 } }
};
static sprite_pattern pat03 =
{
  1,
  { { -8, -12, 0, 438 } }
};
static sprite_pattern pat04 =
{
  1,
  { { -12, -8, 0, 439 } }
};
static sprite_pattern pat05 =
{
  1,
  { { -12, -8, 0, 440 } }
};
sprite_pattern* z6_pat_friend0[3] =
{
  &pat00,
  &pat01,
  &patnull
};
sprite_pattern* z6_pat_friend1[5] =
{
  &pat02,
  &pat03,
  &patnull,
  &pat04,
  &pat05
};
static char p00[4] = { 19, 0, 1, -1 };
static unsigned char p01[30] =
{
  0, 0, 0, 2, 0, 0, 2, 1, 1, 2,
  2, 1, 1, 2, 2, 0, 0, 2, 0, 0,
  2, 1, 1, 2, 2, 1, 1, 2, 2, 255
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
static char* pchg0[2] =
{
  p00,
  (char*)p01
};
static char* pchg1[1] = { p10 };
static unsigned short tbl0sproffset[11] =
{
  1943, 986, 986, 0,
  1943, 986, 986, 0,
     0,   0, 986
};






























void friend6(sprite_status* actionwk) {

  if (friend_suicide(actionwk) == -1) return;


  if (actionwk->userflag.b.h & 127)
    pecky(actionwk);
  else
    tsubame(actionwk);
}

void tsubame(sprite_status* actionwk) {
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
  actionwk->patbase = z6_pat_friend0;
  ((short*)actionwk)[23] = actionwk->xposi.w.h;
  ((short*)actionwk)[24] = (actionwk->yposi).w.h;
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
  if (a1->actno != 47 || a1->actfree[21])
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

void pecky(sprite_status* actionwk) {
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
  actionwk->sprvsize = 8;
  actionwk->sprhs = 8;
  actionwk->sprpri = 4;
  actionwk->sprhsize = 8;
  actionwk->patbase = z6_pat_friend1;

  set_sproffset(actionwk);
  if (actionwk->userflag.b.h < 0)
  {
    actionwk->r_no0 = 8;

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
  if (a1->actno != 47 || a1->actfree[21])
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
  d0 = ((stageno.w + 1) << 2) + (unsigned short)time_flag;
  actionwk->sproffset = a1[d0];
}
