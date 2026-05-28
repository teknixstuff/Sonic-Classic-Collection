#include "../EQU.h"
#include "SEMI.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void act_init(sprite_status* actionwk);
static void act_wait(sprite_status* actionwk);
static short act_check(sprite_status* actionwk, sprite_status* pw);
static void bomb(sprite_status* actionwk);

static char pchg0[6] = { 3, 1, 2, 3, 2, -1 };
char pchg_bomb0[4] = { 1, 0, 1, -1 };
static char* pchg[1] = { pchg0 };
char* pchg_bomb[1] = { pchg_bomb0 };
static sprite_pattern pat00 = { 1, { { -16, -16, 0, 471 } } };
static sprite_pattern z6bpat00 = { 1, { { -16, -16, 0, 465 } } };
static sprite_pattern pat01 = { 1, { { -16, -16, 0, 472 } } };
static sprite_pattern z6bpat01 = { 1, { { -16, -16, 0, 466 } } };
static sprite_pattern pat02 = { 1, { { -20, -16, 0, 473 } } };
static sprite_pattern z6bpat02 = { 1, { { -20, -16, 0, 467 } } };
static sprite_pattern pat03 = { 1, { { -16, -16, 0, 474 } } };
static sprite_pattern z6bpat03 = { 1, { { -16, -16, 0, 468 } } };
static sprite_pattern pat04 = { 1, { { -16, -16, 0, 475 } } };
static sprite_pattern z6bpat04 = { 1, { { -16, -16, 0, 469 } } };
static sprite_pattern pat05 = { 1, { { -16, -16, 0, 476 } } };
static sprite_pattern z6bpat05 = { 1, { { -16, -16, 0, 470 } } };
static sprite_pattern pat06 = { 1, { { -20, -16, 0, 477 } } };
static sprite_pattern z6bpat06 = { 1, { { -20, -16, 0, 471 } } };
static sprite_pattern pat07 = { 1, { { -16, -16, 0, 478 } } };
static sprite_pattern z6bpat07 = { 1, { { -16, -16, 0, 472 } } };
static sprite_pattern pat08 = { 1, { { -8, -8, 0, 479 } } };
static sprite_pattern z6bpat08 = { 1, { { -8, -8, 0, 473 } } };
static sprite_pattern pat09 = { 1, { { -8, -8, 0, 480 } } };
static sprite_pattern z6bpat09 = { 1, { { -8, -8, 0, 474 } } };
sprite_pattern* pat_semi_e[4] =
{
  &pat00,
  &pat01,
  &pat02,
  &pat03
};
sprite_pattern* z6b_pat_semi_e[4] =
{
  &z6bpat00,
  &z6bpat01,
  &z6bpat02,
  &z6bpat03
};
sprite_pattern** pats_semi_e[3] =
{
  z6b_pat_semi_e,
  pat_semi_e,
  pat_semi_e
};
sprite_pattern* pat_semi_b[4] =
{
  &pat04,
  &pat05,
  &pat06,
  &pat07
};
sprite_pattern* z6b_pat_semi_b[4] =
{
  &z6bpat04,
  &z6bpat05,
  &z6bpat06,
  &z6bpat07
};
sprite_pattern** pats_semi_b[3] =
{
  z6b_pat_semi_b,
  pat_semi_b,
  pat_semi_b
};
static sprite_pattern* pat_bomb[2] =
{
  &pat08,
  &pat09
};
static sprite_pattern* z6b_pat_bomb[2] =
{
  &z6bpat08,
  &z6bpat09
};
static sprite_pattern** pats_bomb[3] =
{
  z6b_pat_bomb,
  pat_bomb,
  pat_bomb
};


void semi(sprite_status* actionwk) {
  if (actionwk->userflag.b.l < 0)
  {
    bomb(actionwk);
    return;
  }
  if (enemy_suicide(actionwk) == -1) return;
  switch (actionwk->r_no0) {

    case 0:
      act_init(actionwk);
    case 2:
      act_wait(actionwk);
      break;
    case 4:
      act_wait1(actionwk);
      break;
    case 6:
      act_movea(actionwk);
    case 8:
      act_movea1(actionwk);
      break;
    case 10:
      act_moveb(actionwk);
    case 12:
      act_moveb1(actionwk);
      break;
  }
  actionsub(actionwk);
  frameout_s(actionwk);
}

static void act_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 1;
  actionwk->sprvsize = 16;

  actionwk->sprhs = 19;
  actionwk->sprhsize = 19;
  actionwk->sproffset = 42152;
  actionwk->colino = 54;


  actionwk->actfree[8] = actionwk->userflag.b.l;
  if (actionwk->userflag.b.h != 0)
    actionwk->patbase = pats_semi_b[time_flag_i & 0x7F];
  else
    actionwk->patbase = pats_semi_e[time_flag_i & 0x7F];
}

static void act_wait(sprite_status* actionwk) {
  if (--((short*)actionwk)[27] > 0) return;
  actionwk->r_no0 += 2;
}

void act_wait1(sprite_status* actionwk) {
  if (!act_check(actionwk, &actwk[0])) return;
  actionwk->r_no0 += 2;
}

static short act_check(sprite_status* actionwk, sprite_status* pw) {
  short d0w;

  d0w = pw->yposi.w.h;
  d0w -= actionwk->yposi.w.h;
  if (d0w < -96 || d0w > 96) return 0;
  ((short*)actionwk)[28] = pw->xposi.w.h - actionwk->xposi.w.h;

  d0w = pw->xposi.w.h;
  d0w -= actionwk->xposi.w.h;
  if (d0w >= -120 && d0w <= 120) return 1;
  return 0;

}

void act_movea(sprite_status* actionwk) {
  int d0, d1;
  short d2;

  actionwk->r_no0 += 2;
  d0 = 65536;
  d1 = -32768;
  d2 = 96;
  if (actionwk->userflag.b.h != 0)
  {
    d0 = 49152;
    d1 = 24576;
    d2 = 42;
  }

  if (((short*)actionwk)[28] >= 0)
  {
    d0 = -d0;
  }
  *(int*)&actionwk->actfree[0] = d0;
  *(int*)&actionwk->actfree[4] = d1;
  ((short*)actionwk)[27] = d2;
}

void act_movea1(sprite_status* actionwk) {
  if (--((short*)actionwk)[27] <= 0) actionwk->r_no0 += 2;

  actionwk->xposi.l += *(int*)&actionwk->actfree[0];
  actionwk->yposi.l += *(int*)&actionwk->actfree[4];
  patchg(actionwk, (unsigned char**)pchg);
}

void act_moveb(sprite_status* actionwk) {
  int d0;

  actionwk->r_no0 += 2;
  ((short*)actionwk)[27] = 0;
  d0 = 65536;
  if (actionwk->userflag.b.h != 0)
    d0 = 49152;

  if (((short*)actionwk)[28] >= 0)
  {
    d0 = -d0;
  }
  *(int*)&actionwk->actfree[0] = d0;
}

void act_moveb1(sprite_status* actionwk) {
  sprite_status* a1;

  if (actionwk->userflag.b.h == 0)
  {
    ((short*)actionwk)[27] &= 63;
    if (((short*)actionwk)[27] == 0)
    {
      if (act_check(actionwk, &actwk[0]) != 0)
      {
        if (actwkchk(&a1) == 0)
        {
          a1->actno = actionwk->actno;
          a1->xposi.l = actionwk->xposi.l;
          a1->yposi.l = actionwk->yposi.l;
          a1->yposi.w.h += 10;
          a1->userflag.b.l = -1;
          a1->actflg = actionwk->actflg;
          a1->sprpri = actionwk->sprpri;
          ++a1->sprpri;
        }
      }
    }
    ++((short*)actionwk)[27];
  }

  actionwk->xposi.l += *(int*)&actionwk->actfree[0];
  patchg(actionwk, (unsigned char**)pchg);
}





static void bomb(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      bomb_init(actionwk);
    case 2:
      bomb_fall(actionwk);
      break;
    case 4:
      bomb_wait(actionwk);
      break;
    case 6:
      bomb_blink(actionwk);
      break;
    case 8:
      bomb_die(actionwk);
      break;
  }
  actionsub(actionwk);
  frameout_s(actionwk);
}

void bomb_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->colino = 183;

  actionwk->sprvsize = 6;
  actionwk->sprhs = 6;
  actionwk->sprhsize = 6;
  actionwk->sproffset = 33992;
  actionwk->patbase = pats_bomb[time_flag_i & 0x7F];
  *(int*)&actionwk->actfree[4] = 32768;
}

void bomb_fall(sprite_status* actionwk) {
  short d1;

  actionwk->yposi.l += *(int*)&actionwk->actfree[4];
  *(int*)&actionwk->actfree[4] += 16384;
  d1 = emycol_d(actionwk);
  if (d1 < 0)
  {
    actionwk->r_no0 += 2;
    actionwk->yposi.w.h += d1;
    ((short*)actionwk)[27] = 120;
  }
}

void bomb_wait(sprite_status* actionwk) {
  short t;

  --((short*)actionwk)[27];
  t = ((short*)actionwk)[27];
  if (t < 0)
  {
    actionwk->r_no0 += 2;
    ((short*)actionwk)[27] = 120;
  }
}

void bomb_blink(sprite_status* actionwk) {
  short t;

  --((short*)actionwk)[27];
  t = ((short*)actionwk)[27];
  if (t < 0)
  {
    actionwk->r_no0 += 2;
  }

  patchg(actionwk, (unsigned char**)pchg_bomb);
}

void bomb_die(sprite_status* actionwk) {
  actionwk->actno = 24;
  actionwk->r_no0 = 0;
  actionwk->r_no1 = 1;
  if ((char)actionwk->actflg < 0)
    soundset(158);
}
