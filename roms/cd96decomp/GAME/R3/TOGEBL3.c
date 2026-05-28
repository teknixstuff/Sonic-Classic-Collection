#include "../EQU.h"
#include "TOGEBL3.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"

static void togeball_main(sprite_status* actionwk);
static void act_init(sprite_status* actionwk);
static void act_move(sprite_status* actionwk);
static void togeball_opt(sprite_status* actionwk);
static void act_init2(sprite_status* actionwk);
static void act_move2(sprite_status* actionwk);

static sprite_pattern z31a_spat_chg0 = { 1, { { -8, -8, 0, 556 } } };
static sprite_pattern z31b_spat_chg0 = { 1, { { -8, -8, 0, 550 } } };
static sprite_pattern z3c_spat_chg0 = { 1, { { -8, -8, 0, 503 } } };
static sprite_pattern z32a_spat_chg0 = { 1, { { -8, -8, 0, 550 } } };
static sprite_pattern z32b_spat_chg0 = { 1, { { -8, -8, 0, 503 } } };
static sprite_pattern z33_spat_chg0 = { 1, { { -8, -8, 0, 554 } } };
static sprite_pattern z31a_spat_chg1 = { 1, { { -8, -8, 0, 557 } } };
static sprite_pattern z31b_spat_chg1 = { 1, { { -8, -8, 0, 551 } } };
static sprite_pattern z3c_spat_chg1 = { 1, { { -8, -8, 0, 504 } } };
static sprite_pattern z32a_spat_chg1 = { 1, { { -8, -8, 0, 551 } } };
static sprite_pattern z32b_spat_chg1 = { 1, { { -8, -8, 0, 504 } } };
static sprite_pattern z33_spat_chg1 = { 1, { { -8, -8, 0, 555 } } };
sprite_pattern* z31a_pat_chg[1] = { &z31a_spat_chg0 };
sprite_pattern* z31b_pat_chg[1] = { &z31b_spat_chg0 };
sprite_pattern* z3c_pat_chg[1] = { &z3c_spat_chg0 };
sprite_pattern* z32a_pat_chg[1] = { &z32a_spat_chg0 };
sprite_pattern* z32b_pat_chg[1] = { &z32b_spat_chg0 };
sprite_pattern* z33_pat_chg[1] = { &z33_spat_chg0 };
static sprite_pattern** pats_chg[3][3] = {
  { z31b_pat_chg, z31a_pat_chg, z3c_pat_chg },
  { z32b_pat_chg, z32a_pat_chg, z3c_pat_chg },
  { 0, 0, z33_pat_chg }
};
sprite_pattern* z31a_togeball_pat[1] = { &z31a_spat_chg1 };
sprite_pattern* z31b_togeball_pat[1] = { &z31b_spat_chg1 };
sprite_pattern* z3c_togeball_pat[1] = { &z3c_spat_chg1 };
sprite_pattern* z32a_togeball_pat[1] = { &z32a_spat_chg1 };
sprite_pattern* z32b_togeball_pat[1] = { &z32b_spat_chg1 };
sprite_pattern* z33_togeball_pat[1] = { &z33_spat_chg1 };
sprite_pattern** togeball_pats[3][3] = {
  { z31b_togeball_pat, z31a_togeball_pat, z3c_togeball_pat },
  { z32b_togeball_pat, z32a_togeball_pat, z3c_togeball_pat },
  { 0, 0, z33_togeball_pat }
};


void togeball3(sprite_status* actionwk) {
  if (actionwk->userflag.b.h >= 0)
    togeball_main(actionwk);
  else
    togeball_opt(actionwk);
}

static void togeball_main(sprite_status* actionwk) {
  switch (actionwk->r_no0) {

    case 0:
      act_init(actionwk);
      break;
    case 2:
      act_move(actionwk);
      break;
  }
  actionsub(actionwk);
  frameout_s(actionwk);
}

static void act_init(sprite_status* actionwk) {
  sprite_status* a1;

  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 1;
  actionwk->sprhsize = 8;
  actionwk->sprvsize = 8;
  actionwk->patbase = pats_chg[stageno_i.b.l][time_flag_i & 0x7F];
  actionwk->sproffset = 957;
  ((short*)actionwk)[24] = 256;
  if (actionwk->userflag.b.h != 0)
    ((short*)actionwk)[24] = -((short*)actionwk)[24];


  if (actwkchk2(actionwk, &a1) != 0) {

    frameout(actionwk);
    return;
  }
  ((unsigned short*)a1)[33] = actionwk - actwk;
  ((unsigned short*)actionwk)[25] = a1 - actwk;
  a1->actno = actionwk->actno;
  a1->userflag.b.h = -1;
  a1->sprhsize = 8;
  a1->sprvsize = 8;

  if (actwkchk2(actionwk, &a1) != 0) {

    frameout(actionwk);
    return;
  }
  ((unsigned short*)a1)[33] = actionwk - actwk;
  ((unsigned short*)actionwk)[26] = a1 - actwk;
  a1->actno = actionwk->actno;
  a1->userflag.b.h = -1;
  a1->sprhsize = 8;
  a1->sprvsize = 8;

  if ((time_flag_i & 0x7F) != 0) {
    if (actwkchk2(actionwk, &a1) != 0) {

      frameout(actionwk);
      return;
    }
    ((unsigned short*)a1)[33] = actionwk - actwk;
    ((unsigned short*)actionwk)[27] = a1 - actwk;
    a1->actno = actionwk->actno;
    a1->userflag.b.h = -1;
    a1->sprhsize = 8;
    a1->sprvsize = 8;

    if ((time_flag_i & 0x7F) == 2) {
      if (actwkchk2(actionwk, &a1) != 0) {

        frameout(actionwk);
        return;
      }
      ((unsigned short*)a1)[33] = actionwk - actwk;
      ((unsigned short*)actionwk)[28] = a1 - actwk;
      a1->actno = actionwk->actno;
      a1->userflag.b.h = -1;
      a1->sprhsize = 8;
      a1->sprvsize = 8;
    }
  }
}

static void act_move(sprite_status* actionwk) {
  short d0;
  unsigned short sin, cos;
  int d0l, d1l, d2l, d3l, d4l, d5l;
  sprite_status* a1;

  d0 = ((short*)actionwk)[24];
  ((short*)actionwk)[23] += d0;
  d0 = ((short*)actionwk)[23];
  d0 >>= 8;

  sinset(d0, (short*)&sin, (short*)&cos);
  d0l = d1l = 0;
  d0l = sin << 16;
  d1l = cos << 16;
  d0l >>= 2;
  d1l >>= 2;
  d4l = d0l;
  d5l = d1l;
  d0l >>= 1;
  d1l >>= 1;
  d2l = d0l;
  d3l = d1l;
  d0l >>= 1;
  d1l >>= 1;
  a1 = &actwk[((unsigned short*)actionwk)[25]];
  *(int*)&a1->actfree[4] = actionwk->yposi.l + d0l;
  *(int*)&a1->actfree[0] = actionwk->xposi.l + d1l;
  a1 = &actwk[((unsigned short*)actionwk)[26]];
  *(int*)&a1->actfree[4] = actionwk->yposi.l + d2l;
  *(int*)&a1->actfree[0] = actionwk->xposi.l + d3l;
  if ((time_flag_i & 0x7F) != 0) {
    a1 = &actwk[((unsigned short*)actionwk)[27]];
    *(int*)&a1->actfree[4] = actionwk->yposi.l + d0l + d2l;
    *(int*)&a1->actfree[0] = actionwk->xposi.l + d1l + d3l;
    if ((time_flag_i & 0x7F) == 2) {
      a1 = &actwk[((unsigned short*)actionwk)[28]];
      *(int*)&a1->actfree[4] = actionwk->yposi.l + d4l;
      *(int*)&a1->actfree[0] = actionwk->xposi.l + d5l;
    }
  }
}

static void togeball_opt(sprite_status* actionwk) {
  sprite_status* a1;

  switch (actionwk->r_no0) {

    case 0:
      act_init2(actionwk);
    case 2:
      act_move2(actionwk);
      break;
  }
  a1 = &actwk[((unsigned short*)actionwk)[33]];
  if (a1->actno != 44) {

    frameout(actionwk);
    return;
  }
  actionsub(actionwk);
}

static void act_init2(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 1;
  actionwk->patbase = togeball_pats[stageno_i.b.l][time_flag_i & 0x7F];
  actionwk->sproffset = 957;
  actionwk->colino = 139;
}

static void act_move2(sprite_status* actionwk) {
  actionwk->xposi.w.h = ((short*)actionwk)[24];
  actionwk->yposi.w.h = ((short*)actionwk)[26];
}
