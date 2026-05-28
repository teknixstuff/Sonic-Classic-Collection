#include "../EQU.h"
#include "POCKET.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SCORE.h"

static void a_init(sprite_status* actionwk);
static void b_init(sprite_status* actionwk);

static sprite_pattern pat_pocket1 = { 1, { { 0, 0, 0, 0 } } };
static sprite_pattern pat_pocket2 = { 1, { { -24, -8, 0, 505 } } };
static sprite_pattern z31a_pat_pocket2 = { 1, { { -24, -8, 0, 558 } } };
static sprite_pattern z31b_pat_pocket2 = { 1, { { -24, -8, 0, 552 } } };
static sprite_pattern z33_pat_pocket2 = { 1, { { -24, -8, 0, 556 } } };
static sprite_pattern pat_pocket3 = { 1, { { -16, -24, 0, 506 } } };
static sprite_pattern z31a_pat_pocket3 = { 1, { { -16, -24, 0, 559 } } };
static sprite_pattern z31b_pat_pocket3 = { 1, { { -16, -24, 0, 553 } } };
static sprite_pattern z33_pat_pocket3 = { 1, { { -16, -24, 0, 557 } } };
static sprite_pattern pat_pocket4 = { 1, { { -8, -16, 0, 507 } } };
static sprite_pattern z31a_pat_pocket4 = { 1, { { -8, -16, 0, 560 } } };
static sprite_pattern z31b_pat_pocket4 = { 1, { { -8, -16, 0, 554 } } };
static sprite_pattern z33_pat_pocket4 = { 1, { { -8, -16, 0, 558 } } };
static sprite_pattern pat_pocket5 = { 1, { { -24, -8, 0, 508 } } };
static sprite_pattern z31a_pat_pocket5 = { 1, { { -24, -8, 0, 561 } } };
static sprite_pattern z31b_pat_pocket5 = { 1, { { -24, -8, 0, 555 } } };
static sprite_pattern z33_pat_pocket5 = { 1, { { -24, -8, 0, 559 } } };
sprite_pattern* pat[4] =
{
  &pat_pocket1,
  &pat_pocket2,
  &pat_pocket3,
  &pat_pocket4
};
sprite_pattern* z31apat[4] =
{
  &pat_pocket1,
  &z31a_pat_pocket2,
  &z31a_pat_pocket3,
  &z31a_pat_pocket4
};
sprite_pattern* z31bpat[4] =
{
  &pat_pocket1,
  &z31b_pat_pocket2,
  &z31b_pat_pocket3,
  &z31b_pat_pocket4
};
sprite_pattern* z33pat[4] =
{
  &pat_pocket1,
  &z33_pat_pocket2,
  &z33_pat_pocket3,
  &z33_pat_pocket4
};
sprite_pattern** pats[3][3] =
{
  { z31bpat, z31apat, pat },
  { pat, z31bpat, pat },
  { 0, 0, z33pat }
};
sprite_pattern* pat_pocket[2] =
{
  &pat_pocket5,
  &pat_pocket1
};
sprite_pattern* z31a_pat_pocket[2] =
{
  &z31a_pat_pocket5,
  &pat_pocket1
};
sprite_pattern* z31b_pat_pocket[2] =
{
  &z31b_pat_pocket5,
  &pat_pocket1
};
sprite_pattern* z33_pat_pocket[2] =
{
  &z33_pat_pocket5,
  &pat_pocket1
};
sprite_pattern** pats_pocket[3][3] =
{
  { z31b_pat_pocket, z31a_pat_pocket, pat_pocket },
  { pat_pocket, z31b_pat_pocket, pat_pocket },
  { 0, 0, z33_pat_pocket }
};
static char pchg0[4] = { 3, 0, 1, -1 };
static char* pchg[1] = { pchg0 };
void(*pocket_move_tbl[11])(sprite_status*) =
{
  &a_init,
  &a_move0,
  &a_move00,
  &a_move1,
  &a_move2,
  &a_move3,
  &a_move4,
  &a_move5,
  &a_move6,
  &a_move7,
  &a_move8
};


void pocket(sprite_status* actionwk) {
  if (actionwk->userflag.b.h < 0)
    pocket0(actionwk);
  else
    pocket1(actionwk);
}















void pocket0(sprite_status* actionwk) {
  pocket_move_tbl[actionwk->r_no0 / 2](actionwk);
  actionsub(actionwk);
  frameout_s(actionwk);
}

static void a_init(sprite_status* actionwk) {
  if (time_flag == 2 && generate_flag != 0)
  {
    frameout(actionwk);
    return;
  }

  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 0;
  actionwk->sproffset = 943;
  actionwk->patbase = pats[stageno_i.b.l][time_flag_i & 0x7F];

  ((short*)actionwk)[26] = 7;
  a_move0(actionwk);
}

void a_move0(sprite_status* actionwk) {
  sprite_status* a6;

  if (editmode.w) return;
  a6 = &actwk[0];
  a_check(actionwk, a6);
  if (actionwk->actfree[20] != 0) to_a_move1(actionwk);
}

void a_check(sprite_status* actionwk, sprite_status* a6) {
  short d0;

  if (a6->yspeed.w < 0) return;
  if (a6->r_no0 == 4 || a6->r_no0 == 6) return;
  d0 = a6->yposi.w.h - actionwk->yposi.w.h;
  d0 += 24;
  if (d0 < 0 || d0 >= 16) return;
  d0 = a6->xposi.w.h - actionwk->xposi.w.h;
  d0 += 24;
  if (d0 < 0 || d0 >= 48) return;

  actionwk->actfree[20] = 255;
  a6->actfree[2] |= 1;
  a6->cddat |= 4;
  a6->sprvsize = 14;
  a6->sprhs = 7;
  a6->mstno.b.h = 2;
  a6->xspeed.w = 0;
  a6->yspeed.w = -2048;
  a6->xposi.w.h = actionwk->xposi.w.h;
  a6->yposi.w.h = actionwk->yposi.w.h - 16;
}

void to_a_move1(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 8;
  actionwk->patno = 1;
  soundset(215);
  a_move00(actionwk);
}

void a_move00(sprite_status* actionwk) {
  sprite_status* a1;

  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  actionwk->patno = 2;
  ((short*)actionwk)[23] = 6;
  if (actwkchk(&a1) != 0)
  {
    frameout(actionwk);
    return;
  }
  ((unsigned short*)actionwk)[24] = a1 - actwk;
  ((unsigned short*)a1)[25] = actionwk - actwk;
  a1->actno = actionwk->actno;

  a1->xposi.w.h = actionwk->xposi.w.h;
  a1->yposi.w.h = actionwk->yposi.w.h;
  actwk[0].actfree[2] |= 64;
}

void a_move1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 2;
  actionwk->patno = 3;

}

void a_move2(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 30;
  actionwk->patno = 0;
}

void a_move3(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 30;
  if (((unsigned short*)actionwk)[26] == 0) return;
  --((unsigned short*)actionwk)[26];
  scoreup(10);
  tensuu0(actionwk, 0);
}

void a_move4(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 30;
  if (((unsigned short*)actionwk)[26] == 0) return;
  --((unsigned short*)actionwk)[26];
  scoreup(10);
  tensuu0(actionwk, 0);
}

void a_move5(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 4;
  actionwk->patno = 3;
}

void a_move6(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 6;
  actionwk->patno = 2;
}

void a_move7(sprite_status* actionwk) {
  sprite_status* a1;

  if (--((short*)actionwk)[23] >= 0) return;
  soundset(159);
  actionwk->r_no0 += 2;
  actionwk->patno = 0;

  ((short*)actionwk)[23] = 120;
  a1 = &actwk[((unsigned short*)actionwk)[24]];
  a1->r_no0 = 4;
  if (actionwk->actfree[20] == 0) return;
  actionwk->actfree[20] = 0;
  actwk[0].actfree[2] &= 254;
  actwk[0].actfree[2] &= 191;
}

void a_move8(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 = 2;
  actionwk->actfree[20] = 0;
}

void pocket1(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      b_init(actionwk);
      break;
    case 2:
      b_move(actionwk);
      break;
    case 4:
      b_die(actionwk);
      break;
  }
}

static void b_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 0;
  actionwk->sprhsize = 24;
  actionwk->sprvsize = 8;
  actionwk->sproffset = 17327;
  actionwk->patbase = pats_pocket[stageno_i.b.l][time_flag_i & 0x7F];
  b_move(actionwk);
}

void b_move(sprite_status* actionwk) {
  sprite_status* a1;

  a1 = &actwk[((unsigned short*)actionwk)[25]];
  if (a1->actno != 47)
  {
    frameout(actionwk);
    return;
  }
  patchg(actionwk, (unsigned char**)pchg);
  actionsub(actionwk);
}

void b_die(sprite_status* actionwk) {
  frameout(actionwk);
}
