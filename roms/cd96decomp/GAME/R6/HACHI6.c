#include "../EQU.h"
#include "HACHI6.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void act_init(sprite_status* actionwk);
static void act_move(sprite_status* actionwk);
static void act_move1(sprite_status* actionwk);
static short act_check(sprite_status* actionwk, sprite_status* pw);
static void tama(sprite_status* actionwk);

static sprite_pattern pat00 = { 1, { { -24, -19, 0, 447 } } };
static sprite_pattern z6bpat00 = { 1, { { -24, -19, 0, 441 } } };
static sprite_pattern pat01 = { 1, { { -24, -15, 0, 448 } } };
static sprite_pattern z6bpat01 = { 1, { { -24, -15, 0, 442 } } };
static sprite_pattern pat02 = { 1, { { -16, -23, 0, 449 } } };
static sprite_pattern z6bpat02 = { 1, { { -16, -23, 0, 443 } } };
static sprite_pattern pat03 = { 1, { { -16, -19, 0, 450 } } };
static sprite_pattern z6bpat03 = { 1, { { -16, -19, 0, 444 } } };
static sprite_pattern pat04 = { 1, { { -24, -19, 0, 451 } } };
static sprite_pattern z6bpat04 = { 1, { { -24, -19, 0, 445 } } };
static sprite_pattern pat05 = { 1, { { -24, -15, 0, 452 } } };
static sprite_pattern z6bpat05 = { 1, { { -24, -15, 0, 446 } } };
static sprite_pattern pat06 = { 1, { { -8, -8, 0, 453 } } };
static sprite_pattern z6bpat06 = { 1, { { -8, -8, 0, 447 } } };
static sprite_pattern pat07 = { 1, { { -8, -8, 0, 454 } } };
static sprite_pattern z6bpat07 = { 1, { { -8, -8, 0, 448 } } };
static sprite_pattern pat08 = { 1, { { -8, -8, 0, 455 } } };
static sprite_pattern z6bpat08 = { 1, { { -8, -8, 0, 449 } } };
static sprite_pattern pat09 = { 1, { { -8, -8, 0, 456 } } };
static sprite_pattern z6bpat09 = { 1, { { -8, -8, 0, 450 } } };
sprite_pattern* pat_hachi6_e[4] =
{
  &pat00,
  &pat01,
  &pat02,
  &pat03
};
sprite_pattern* z6b_pat_hachi6_e[4] =
{
  &z6bpat00,
  &z6bpat01,
  &z6bpat02,
  &z6bpat03
};
sprite_pattern** pats_hachi6_e[3] =
{
  z6b_pat_hachi6_e,
  pat_hachi6_e,
  pat_hachi6_e
};
sprite_pattern* pat_hachi6_b[2] =
{
  &pat04,
  &pat05
};
sprite_pattern* z6b_pat_hachi6_b[2] =
{
  &z6bpat04,
  &z6bpat05
};
sprite_pattern** pats_hachi6_b[3] =
{
  z6b_pat_hachi6_b,
  pat_hachi6_b,
  pat_hachi6_b
};
static sprite_pattern* pat_tama[4] =
{
  &pat06,
  &pat07,
  &pat08,
  &pat09
};
static sprite_pattern* z6b_pat_tama[4] =
{
  &z6bpat06,
  &z6bpat07,
  &z6bpat08,
  &z6bpat09
};
static sprite_pattern** pats_tama[3] =
{
  z6b_pat_tama,
  pat_tama,
  pat_tama
};
static char pchg00[4] = { 1, 0, 1, -1 };
static char pchg01[4] = { 1, 2, 3, -1 };
static char* pchg[2] =
{
  pchg00,
  pchg01
};
char pchg_tama0[4] = { 1, 2, 3, -1 };
char* pchg_tama[1] = { pchg_tama0 };




void hachi6(sprite_status* actionwk) {
  void(*act_tbl[10])(sprite_status*) =
  {
    act_init,
    act_move,
    act_move1,
    act_rev,
    act_rev1,
    act_rev2,
    act_shot,
    act_shot1,
    act_shot2,
    act_shot3
  };

  if (actionwk->userflag.b.h < 0)
  {
    tama(actionwk);
    return;
  }
  if (enemy_suicide(actionwk) == -1) return;
  act_tbl[actionwk->r_no0 / 2](actionwk);
  patchg(actionwk, (unsigned char**)pchg);
  actionsub(actionwk);
  frameout_s(actionwk);
}

static void act_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 1;
  actionwk->sprhs = 24;
  actionwk->sprhsize = 24;
  actionwk->sprvsize = 12;
  actionwk->sproffset = 42071;
  actionwk->colino = 49;
  ((short*)actionwk)[26] = -8;

  if (actionwk->userflag.b.h == 0)
  {
    actionwk->patbase = pats_hachi6_e[time_flag_i & 0x7F];
    ((int*)actionwk)[12] = -65536;
  }
  else
  {
    actionwk->patbase = pats_hachi6_b[time_flag_i & 0x7F];
    ((int*)actionwk)[12] = -32768;
  }

  act_move(actionwk);
}

static void act_move(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  if (actionwk->userflag.b.h == 0)
    ((short*)actionwk)[23] = 512;
  else
    ((short*)actionwk)[23] = 1024;
}

static void act_move1(sprite_status* actionwk) {
  actionwk->xposi.l += ((int*)actionwk)[12];
  if (actionwk->userflag.b.h == 0)
  {
    if (((short*)actionwk)[27] != 0)
    {
      --((short*)actionwk)[27];
    }
    else
    {

      if (act_check(actionwk, &actwk[0]))
      {
        actionwk->r_no0 = 12;
        return;
      }
    }
  }

  if (--((short*)actionwk)[23] == 0)
    actionwk->r_no0 = 6;

}

static short act_check(sprite_status* actionwk, sprite_status* pw) {
  char d1;
  char d2;
  short d0w;

  d0w = pw->yposi.w.h;
  d0w -= actionwk->yposi.w.h;
  if (d0w < -96 || d0w > 96) return 0;
  if ((short)(pw->xposi.w.h - actionwk->xposi.w.h) >= 0) d1 = -1;
  else d1 = 0;


  d0w = pw->xposi.w.h;
  d0w -= actionwk->xposi.w.h;
  if (d0w < -120 || d0w > 120) return 0;
  if (actionwk->actflg & 1) d2 = -1;
  else d2 = 0;
  d2 ^= d1;
  if (d2 != 0)
  {
    ((int*)actionwk)[12] = -((int*)actionwk)[12];
    ((short*)actionwk)[26] = -((short*)actionwk)[26];
    actionwk->actflg ^= 1;
    actionwk->cddat ^= 1;
  }
  return -1;
}

void act_rev(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 30;
}

void act_rev1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 30;
  ((int*)actionwk)[12] = -((int*)actionwk)[12];
  ((short*)actionwk)[26] = -((short*)actionwk)[26];
  actionwk->actflg ^= 1;
  actionwk->cddat ^= 1;
}

void act_rev2(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 = 2;
}

void act_shot(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 30;
  act_shot1(actionwk);
}

void act_shot1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 30;
  actionwk->mstno.b.h = 1;
  actionwk->colino = 50;

  actionwk->sprvsize = 16;
  actionwk->sprhs = 16;
  actionwk->sprhsize = 16;
  actionwk->xposi.w.h += ((short*)actionwk)[26];
  actionwk->yposi.w.h += 4;
}

void act_shot2(sprite_status* actionwk) {
  sprite_status* a1;

  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 30;
  if (actwkchk(&a1) != 0) return;
  a1->actno = actionwk->actno;
  a1->userflag.b.h = -1;
  a1->actflg = actionwk->actflg;
  a1->sproffset = actionwk->sproffset;
  a1->patbase = pats_tama[time_flag_i & 0x7F];
  a1->sprpri = 1;

  a1->sprvsize = 16;
  a1->sprhs = 16;
  a1->sprhsize = 16;
  a1->colino = 179;
  a1->yposi.w.h = actionwk->yposi.w.h + 23;
  ((int*)a1)[13] = 0x20000;

  a1->xposi.w.h = actionwk->xposi.w.h;
  if (actionwk->actflg & 1)
  {
    a1->xposi.w.h += 7;
    ((int*)a1)[12] = 0x20000;
  }
  else
  {
    a1->xposi.w.h -= 7;
    ((int*)a1)[12] = -0x20000;
  }
  if ((char)actionwk->actflg < 0) soundset(160);
}

void act_shot3(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] >= 0) return;
  actionwk->r_no0 = 2;
  ((short*)actionwk)[27] = 60;
  actionwk->mstno.b.h = 0;
  actionwk->colino = 49;

  actionwk->sprvsize = 12;
  actionwk->sprhs = 24;
  actionwk->sprhsize = 24;
  actionwk->yposi.w.h -= 4;
}




static void tama(sprite_status* actionwk) {
  switch (actionwk->r_no0) {

    case 0:
      tam_move(actionwk);
    case 2:
      tam_move1(actionwk);
      break;
    case 4:
      tam_move2(actionwk);
      break;
    case 6:
      tam_move3(actionwk);
      break;
  }
  actionsub(actionwk);
  frameout_s(actionwk);
}

void tam_move(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  ((short*)actionwk)[23] = 3;
}

void tam_move1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] > 0) return;
  actionwk->r_no0 += 2;
  actionwk->patno = 1;
  ((short*)actionwk)[23] = 10;
}

void tam_move2(sprite_status* actionwk) {
  actionwk->xposi.l += ((int*)actionwk)[12];
  actionwk->yposi.l += ((int*)actionwk)[13];
  if (--((short*)actionwk)[23] > 0) return;
  actionwk->r_no0 += 2;
}

void tam_move3(sprite_status* actionwk) {
  if ((char)actionwk->actflg >= 0)
  {
    frameout(actionwk);
    return;
  }
  actionwk->xposi.l += ((int*)actionwk)[12];
  actionwk->yposi.l += ((int*)actionwk)[13];
  patchg(actionwk, (unsigned char**)pchg_tama);
}
