#include "../EQU.h"
#include "GA3.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

extern sprite_pattern** ringpats[7][3][3];

static void m_init(sprite_status* actionwk);
static void m_wait(sprite_status* actionwk);
static void m_move(sprite_status* actionwk);
static void s_init(sprite_status* actionwk);

static sprite_pattern spat_b3 = { 1, { { -16, -10, 0, 482 } } };
static sprite_pattern z31a_spat_b3 = { 1, { { -16, -10, 0, 529 } } };
static sprite_pattern z33_spat_b3 = { 1, { { -16, -10, 0, 533 } } };
static sprite_pattern spat_b4 = { 1, { { -16, -8, 0, 483 } } };
static sprite_pattern z31a_spat_b4 = { 1, { { -16, -8, 0, 530 } } };
static sprite_pattern z33_spat_b4 = { 1, { { -16, -8, 0, 534 } } };
static sprite_pattern spat_b5 = { 1, { { -16, -10, 0, 484 } } };
static sprite_pattern z31a_spat_b5 = { 1, { { -16, -10, 0, 531 } } };
static sprite_pattern z33_spat_b5 = { 1, { { -16, -10, 0, 535 } } };
static sprite_pattern spat_e3 = { 1, { { -16, -12, 0, 485 } } };
static sprite_pattern z31a_spat_e3 = { 1, { { -16, -12, 0, 532 } } };
static sprite_pattern z33_spat_e3 = { 1, { { -16, -12, 0, 536 } } };
static sprite_pattern spat_e4 = { 1, { { -16, -8, 0, 486 } } };
static sprite_pattern z31a_spat_e4 = { 1, { { -16, -8, 0, 533 } } };
static sprite_pattern z33_spat_e4 = { 1, { { -16, -8, 0, 537 } } };
static sprite_pattern spat_e5 = { 1, { { -16, -8, 0, 487 } } };
static sprite_pattern z31a_spat_e5 = { 1, { { -16, -8, 0, 534 } } };
static sprite_pattern z33_spat_e5 = { 1, { { -16, -8, 0, 538 } } };
static sprite_pattern spat_0 = { 1, { { -12, -12, 0, 488 } } };
static sprite_pattern z31a_spat_0 = { 1, { { -12, -12, 0, 535 } } };
static sprite_pattern z33_spat_0 = { 1, { { -12, -12, 0, 539 } } };
static sprite_pattern spat_1 = { 1, { { -12, -12, 0, 489 } } };
static sprite_pattern z31a_spat_1 = { 1, { { -12, -12, 0, 536 } } };
static sprite_pattern z33_spat_1 = { 1, { { -12, -12, 0, 540 } } };
static sprite_pattern spat_2 = { 1, { { -12, -16, 0, 490 } } };
static sprite_pattern z31a_spat_2 = { 1, { { -12, -16, 0, 537 } } };
static sprite_pattern z33_spat_2 = { 1, { { -12, -16, 0, 541 } } };
sprite_pattern* pat_b_ga[6] = {
  &spat_0,
  &spat_1,
  &spat_2,
  &spat_b3,
  &spat_b4,
  &spat_b5
};
sprite_pattern* z31a_pat_b_ga[6] = {
  &z31a_spat_0,
  &z31a_spat_1,
  &z31a_spat_2,
  &z31a_spat_b3,
  &z31a_spat_b4,
  &z31a_spat_b5
};
sprite_pattern* z33_pat_b_ga[6] = {
  &z33_spat_0,
  &z33_spat_1,
  &z33_spat_2,
  &z33_spat_b3,
  &z33_spat_b4,
  &z33_spat_b5
};
sprite_pattern** pats_b_ga[3][3] = {
  { z31a_pat_b_ga, z31a_pat_b_ga, pat_b_ga },
  { pat_b_ga, z31a_pat_b_ga, pat_b_ga },
  { 0, 0, z33_pat_b_ga }
};
sprite_pattern* pat_e_ga[6] = {
  &spat_0,
  &spat_1,
  &spat_2,
  &spat_e3,
  &spat_e4,
  &spat_e5
};
sprite_pattern* z31a_pat_e_ga[6] = {
  &z31a_spat_0,
  &z31a_spat_1,
  &z31a_spat_2,
  &z31a_spat_e3,
  &z31a_spat_e4,
  &z31a_spat_e5
};
sprite_pattern* z33_pat_e_ga[6] = {
  &z33_spat_0,
  &z33_spat_1,
  &z33_spat_2,
  &z33_spat_e3,
  &z33_spat_e4,
  &z33_spat_e5
};
sprite_pattern** pats_e_ga[3][3] = {
  { z31a_pat_e_ga, z31a_pat_e_ga, pat_e_ga },
  { pat_e_ga, z31a_pat_e_ga, pat_e_ga },
  { 0, 0, z33_pat_e_ga }
};
static char pchg0[4] = { 29, 0, 1, 1 };
static char pchg1[3] = { 49, 2, 2 };
static char pchg2[6] = { 4, 3, 4, 5, 4, -1 };
static char* pchg[3] = {
  pchg0,
  pchg1,
  pchg2
};
static char ringchg0[6] = { 5, 4, 5, 6, 7, -1 };
static char* ringchg[1] = { ringchg0 };


void ga(sprite_status* actionwk) {
  if (actionwk->userflag.b.h - 1 < 0)
    eb_ga0(actionwk);
  else
    eb_ga1(actionwk);
}

void eb_ga0(sprite_status* actionwk) {


  if (enemy_suicide(actionwk) == -1) return;



  switch (actionwk->r_no0) {

    case 0:
      m_init(actionwk);
    case 2:
      m_wait(actionwk);
      break;
    case 4:
      m_appear0(actionwk);
      break;
    case 6:
      m_appear1(actionwk);
      break;
    case 8:
      m_move(actionwk);
      break;
  }
  actionsub(actionwk);
  frameout_s(actionwk);
}

static void m_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->patno = 0;
  actionwk->sprpri = 1;
  actionwk->sprhsize = 16;
  actionwk->sprvsize = 8;
  actionwk->sproffset = 42017;
  ((short*)actionwk)[23] = 61;
  if (actionwk->userflag.b.h & 128)
    actionwk->patbase = pats_b_ga[stageno_i.b.l][time_flag_i & 0x7F];
  else {

    actionwk->patbase = pats_e_ga[stageno_i.b.l][time_flag_i & 0x7F];
    actionwk->actfree[21] = 255;
  }
}

static void m_wait(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] == 0) {

    actionwk->r_no0 += 2;
    ((short*)actionwk)[23] = 61;
  }
}

void m_appear0(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] == 0) {

    actionwk->colino = 37;
    actionwk->r_no0 += 2;
    ++actionwk->mstno.b.h;
    ((short*)actionwk)[23] = 51;
  }
  m_disp(actionwk);
}

void m_disp(sprite_status* actionwk) {
  patchg(actionwk, (unsigned char**)pchg);
  actionsub(actionwk);
}

void m_appear1(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] == 0) {

    actionwk->colino = 38;
    actionwk->r_no0 += 2;
    ++actionwk->mstno.b.h;
    ((int*)actionwk)[13] = 32768;
    ((short*)actionwk)[23] = 32;
    ((int*)actionwk)[12] = -32768;
    if (actionwk->userflag.b.h < 0) {
      ((short*)actionwk)[23] = 48;
      ((int*)actionwk)[12] = -16384;
    }
    if (actionwk->xposi.w.h - actwk[0].xposi.w.h < 0) {

      ((int*)actionwk)[12] = -((int*)actionwk)[12];

      actionwk->actflg |= 1;
      actionwk->cddat |= 1;
    }
  }
  m_disp(actionwk);
}

static void m_move(sprite_status* actionwk) {
  sprite_status* a1;

  actionwk->xposi.l += ((int*)actionwk)[12];
  actionwk->yposi.l += ((int*)actionwk)[13];
  if (--((short*)actionwk)[23] == 0) {

    ((short*)actionwk)[23] = 65;
    if (actionwk->userflag.b.h < 0) {

      ((short*)actionwk)[23] = 97;
    }
    ((int*)actionwk)[13] = -((int*)actionwk)[13];

    if (actionwk->actfree[21] != 0) {

      if (actwkchk(&a1) == 0) {
        a1->actno = actionwk->actno;
        a1->xposi.l = actionwk->xposi.l;
        a1->yposi.l = actionwk->yposi.l;
        a1->userflag.b.h = 1;
      }
    }
  }
  m_disp(actionwk);
}






void eb_ga1(sprite_status* actionwk) {
  switch (actionwk->r_no0) {

    case 0:
      s_init(actionwk);
    case 2:
      s_fall(actionwk);
      break;
    case 4:
      s_die(actionwk);
      return;
  }
  actionsub(actionwk);
}

static void s_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 1;

  actionwk->sprhs = 6;
  actionwk->sprhsize = 6;
  actionwk->sprvsize = 6;
  actionwk->sproffset = 42926;
  actionwk->patbase = ringpats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  actionwk->sprhsize = 6;
  ((short*)actionwk)[23] = 180;
}

void s_fall(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] == 0) {

    s_die(actionwk);
    return;
  }










  actionwk->yposi.l += 65536;
  patchg(actionwk, (unsigned char**)ringchg);
}

void s_die(sprite_status* actionwk) {
  frameout(actionwk);
}
