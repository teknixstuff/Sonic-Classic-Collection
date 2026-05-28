#include "../EQU.h"
#include "FRIEND8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../ETC.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void t_init(sprite_status* actionwk);
static void t_move(sprite_status* actionwk);
static void t_roll(sprite_status* actionwk, short d2, short d3);
static void p_init(sprite_status* actionwk);
static void p_move(sprite_status* actionwk);
static void set_sproffset(sprite_status* actionwk);

static sprite_pattern z81pat00 = { 1, { { -8, -8, 0, 497 } } };
static sprite_pattern z82pat00 = { 1, { { -8, -8, 0, 459 } } };
static sprite_pattern z83pat00 = { 1, { { -8, -8, 0, 439 } } };
static sprite_pattern z81pat01 = { 1, { { -8, -8, 0, 498 } } };
static sprite_pattern z82pat01 = { 1, { { -8, -8, 0, 460 } } };
static sprite_pattern z83pat01 = { 1, { { -8, -8, 0, 440 } } };
static sprite_pattern z81pat02 = { 1, { { -12, -8, 0, 499 } } };
static sprite_pattern z82pat02 = { 1, { { -12, -8, 0, 461 } } };
static sprite_pattern z83pat02 = { 1, { { -12, -8, 0, 441 } } };
static sprite_pattern z81pat03 = { 1, { { -12, -8, 0, 500 } } };
static sprite_pattern z82pat03 = { 1, { { -12, -8, 0, 462 } } };
static sprite_pattern z83pat03 = { 1, { { -12, -8, 0, 442 } } };
sprite_pattern* z81_pat_friend0[2] =
{
  &z81pat00,
  &z81pat01
};
sprite_pattern* z82_pat_friend0[2] =
{
  &z82pat00,
  &z82pat01
};
sprite_pattern* z83_pat_friend0[2] =
{
  &z83pat00,
  &z83pat01
};
sprite_pattern** z8_pats_friend0[3] =
{
  z81_pat_friend0,
  z82_pat_friend0,
  z83_pat_friend0
};
sprite_pattern* z81_pat_friend1[2] =
{
  &z81pat02,
  &z81pat03
};
sprite_pattern* z82_pat_friend1[2] =
{
  &z82pat02,
  &z82pat03
};
sprite_pattern* z83_pat_friend1[2] =
{
  &z83pat02,
  &z83pat03
};
sprite_pattern** z8_pats_friend1[3] =
{
  z81_pat_friend1,
  z82_pat_friend1,
  z83_pat_friend1
};
static char p00[4] = { 3, 0, 1, -1 };
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
static unsigned short tbl0sproffset[11] =
{
  1943, 986, 986, 0,
  1943, 986, 986, 0,
     0,   0, 986
};

















void friend8(sprite_status* actionwk) {

  if (friend_suicide(actionwk) == -1) return;


  if (actionwk->userflag.b.h & 127)
    sheep(actionwk);
  else
    hato(actionwk);
}

void hato(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      t_init(actionwk);
      break;
    case 2:
      t_move(actionwk);
      break;
  }
}

static void t_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg = 4;

  actionwk->sprvsize = 8;
  actionwk->sprhs = 8;
  actionwk->sprpri = 4;
  actionwk->sprhsize = 8;
  actionwk->patbase = z8_pats_friend0[stageno_i.b.l];
  ((short*)actionwk)[23] = actionwk->xposi.w.h;
  ((short*)actionwk)[24] = actionwk->yposi.w.h;
  actionwk->actflg ^= 1, actionwk->cddat ^= 1;
  set_sproffset(actionwk);


  actionwk->actfree[4] = 1;
  actionwk->actfree[5] = 1;
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

static void t_roll(sprite_status* actionwk, short d2, short d3) {
  short sin, cos;

  sinset(actionwk->actfree[4], &sin, &cos);
  cos >>= d2;
  sin >>= d3;
  actionwk->xposi.w.h = cos + ((short*)actionwk)[23];
  actionwk->yposi.w.h = sin + ((short*)actionwk)[24];
}

void sheep(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      p_init(actionwk);
      break;
    case 2:
      p_move(actionwk);
      break;
  }
}

static void p_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprvsize = 7;
  actionwk->sprhs = 8;
  actionwk->sprpri = 4;
  actionwk->sprhsize = 8;
  actionwk->patbase = z8_pats_friend1[stageno_i.b.l];

  set_sproffset(actionwk);

  ((int*)actionwk)[12] = 65536;
  ((int*)actionwk)[13] = -0x40000;
}

static void p_move(sprite_status* actionwk) {
  short d1;
  int spd;

  actionwk->xposi.l += ((int*)actionwk)[12];
  actionwk->yposi.l += ((int*)actionwk)[13];

  ((int*)actionwk)[13] += 8192;
  spd = ((int*)actionwk)[13];
  if (spd < 0)
    actionwk->patno = 0;
  else
    actionwk->patno = 1;
  d1 = emycol_d(actionwk);
  if (d1 < 0)
  {

    actionwk->yposi.w.h += d1;
    ((int*)actionwk)[13] = -0x40000;
    ((int*)actionwk)[12] = -((int*)actionwk)[12];

    actionwk->actflg ^= 1, actionwk->cddat ^= 1;
  }
  p_end(actionwk);
}

void p_end(sprite_status* actionwk) {
  actionsub(actionwk);
  frameout_s(actionwk);
}

static void set_sproffset(sprite_status* actionwk) {
  unsigned short* a1;
  unsigned short d0;

  a1 = tbl0sproffset;
  d0 = ((stageno.w + 1) << 2) + (unsigned short)time_flag;
  actionwk->sproffset = a1[d0];
}
