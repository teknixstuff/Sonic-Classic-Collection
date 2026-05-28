#include "../EQU.h"
#include "ET1.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../RIDECHK.h"
#include "../SCORE.h"

static void m_init(sprite_status* actionwk);
static void m_wait(sprite_status* actionwk);
static void m_die(sprite_status* actionwk);
static void m1wait(sprite_status* actionwk);
static void a_hover(sprite_status* actionwk);

static sprite_pattern z11atpat00 = { 1, { { -40, 16, 0, 517 } } };
static sprite_pattern z11btpat00 = { 1, { { -40, 16, 0, 502 } } };
static sprite_pattern z11ctpat00 = { 1, { { -40, 16, 0, 492 } } };
static sprite_pattern z12tpat00 = { 1, { { -40, 16, 0, 493 } } };
static sprite_pattern z13tpat00 = { 1, { { -40, 16, 0, 481 } } };
static sprite_pattern z11atpat01 = { 1, { { -40, 16, 0, 518 } } };
static sprite_pattern z11btpat01 = { 1, { { -40, 16, 0, 503 } } };
static sprite_pattern z11ctpat01 = { 1, { { -40, 16, 0, 493 } } };
static sprite_pattern z12tpat01 = { 1, { { -40, 16, 0, 494 } } };
static sprite_pattern z13tpat01 = { 1, { { -40, 16, 0, 482 } } };
static sprite_pattern tpat07 = { 1, { { 0, 0, 0, 0 } } };
static sprite_pattern z11atpat02 = { 2, { { -24, -32, 0, 524 }, { -40, -32, 0, 525 } } };
static sprite_pattern z11btpat02 = { 2, { { -24, -32, 0, 509 }, { -40, -32, 0, 510 } } };
static sprite_pattern z11ctpat02 = { 2, { { -24, -32, 0, 499 }, { -40, -32, 0, 500 } } };
static sprite_pattern z12tpat02 = { 2, { { -24, -32, 0, 500 }, { -40, -32, 0, 501 } } };
static sprite_pattern z13tpat02 = { 2, { { -24, -32, 0, 488 }, { -40, -32, 0, 489 } } };
static sprite_pattern z11atpat03 = { 3, { { -22, -8, 0, 526 }, { -24, -32, 0, 524 }, { -40, -32, 0, 525 } } };
static sprite_pattern z11btpat03 = { 3, { { -22, -8, 0, 511 }, { -24, -32, 0, 509 }, { -40, -32, 0, 510 } } };
static sprite_pattern z11ctpat03 = { 3, { { -22, -8, 0, 501 }, { -24, -32, 0, 499 }, { -40, -32, 0, 500 } } };
static sprite_pattern z12tpat03 = { 3, { { -22, -8, 0, 502 }, { -24, -32, 0, 500 }, { -40, -32, 0, 501 } } };
static sprite_pattern z13tpat03 = { 3, { { -22, -8, 0, 490 }, { -24, -32, 0, 488 }, { -40, -32, 0, 489 } } };
static sprite_pattern z11atpat04 = { 4, { { -22, -8, 0, 527 }, { -24, -32, 0, 530 }, { -24, -32, 0, 524 }, { -40, -32, 0, 525 } } };
static sprite_pattern z11btpat04 = { 4, { { -22, -8, 0, 512 }, { -24, -32, 0, 515 }, { -24, -32, 0, 509 }, { -40, -32, 0, 510 } } };
static sprite_pattern z11ctpat04 = { 4, { { -22, -8, 0, 502 }, { -24, -32, 0, 505 }, { -24, -32, 0, 499 }, { -40, -32, 0, 500 } } };
static sprite_pattern z12tpat04 = { 4, { { -22, -8, 0, 503 }, { -24, -32, 0, 506 }, { -24, -32, 0, 500 }, { -40, -32, 0, 501 } } };
static sprite_pattern z13tpat04 = { 4, { { -22, -8, 0, 491 }, { -24, -32, 0, 494 }, { -24, -32, 0, 488 }, { -40, -32, 0, 489 } } };
static sprite_pattern z11atpat05 = { 4, { { -22, -8, 0, 528 }, { -24, -32, 0, 530 }, { -24, -32, 0, 524 }, { -40, -32, 0, 525 } } };
static sprite_pattern z11btpat05 = { 4, { { -22, -8, 0, 513 }, { -24, -32, 0, 515 }, { -24, -32, 0, 509 }, { -40, -32, 0, 510 } } };
static sprite_pattern z11ctpat05 = { 4, { { -22, -8, 0, 503 }, { -24, -32, 0, 505 }, { -24, -32, 0, 499 }, { -40, -32, 0, 500 } } };
static sprite_pattern z12tpat05 = { 4, { { -22, -8, 0, 504 }, { -24, -32, 0, 506 }, { -24, -32, 0, 500 }, { -40, -32, 0, 501 } } };
static sprite_pattern z13tpat05 = { 4, { { -22, -8, 0, 492 }, { -24, -32, 0, 494 }, { -24, -32, 0, 488 }, { -40, -32, 0, 489 } } };
static sprite_pattern z11atpat06 = { 4, { { -22, -8, 0, 529 }, { -24, -32, 0, 532 }, { -24, -32, 0, 524 }, { -40, -32, 0, 525 } } };
static sprite_pattern z11btpat06 = { 4, { { -22, -8, 0, 514 }, { -24, -32, 0, 517 }, { -24, -32, 0, 509 }, { -40, -32, 0, 510 } } };
static sprite_pattern z11ctpat06 = { 4, { { -22, -8, 0, 504 }, { -24, -32, 0, 507 }, { -24, -32, 0, 499 }, { -40, -32, 0, 500 } } };
static sprite_pattern z12tpat06 = { 4, { { -22, -8, 0, 505 }, { -24, -32, 0, 508 }, { -24, -32, 0, 500 }, { -40, -32, 0, 501 } } };
static sprite_pattern z13tpat06 = { 4, { { -22, -8, 0, 493 }, { -24, -32, 0, 496 }, { -24, -32, 0, 488 }, { -40, -32, 0, 489 } } };
sprite_pattern* z11a_pat_et[8] = {
  &z11atpat00,
  &z11atpat01,
  &z11atpat02,
  &z11atpat03,
  &z11atpat04,
  &z11atpat05,
  &z11atpat06,
  &tpat07
};
sprite_pattern* z11b_pat_et[8] = {
  &z11btpat00,
  &z11btpat01,
  &z11btpat02,
  &z11btpat03,
  &z11btpat04,
  &z11btpat05,
  &z11btpat06,
  &tpat07
};
sprite_pattern* z11c_pat_et[8] = {
  &z11ctpat00,
  &z11ctpat01,
  &z11ctpat02,
  &z11ctpat03,
  &z11ctpat04,
  &z11ctpat05,
  &z11ctpat06,
  &tpat07
};
sprite_pattern* z12_pat_et[8] = {
  &z12tpat00,
  &z12tpat01,
  &z12tpat02,
  &z12tpat03,
  &z12tpat04,
  &z12tpat05,
  &z12tpat06,
  &tpat07
};
sprite_pattern* z13_pat_et[8] = {
  &z13tpat00,
  &z13tpat01,
  &z13tpat02,
  &z13tpat03,
  &z13tpat04,
  &z13tpat05,
  &z13tpat06,
  &tpat07
};
sprite_pattern** z1_pats_et[3][3] = {
  { z11b_pat_et, z11a_pat_et, z11c_pat_et },
  { z12_pat_et, z12_pat_et, z12_pat_et },
  { 0, 0, z13_pat_et }
};
static unsigned short tbl0sproffset[11] = {
  1087, 1033,    0,    0,
  1108, 1024,    0,    0,
     0,    0,    0
};
static char tbl0[64] = {
    1,   0,   0,   2,
  -40, -20,   3,  28,
   10,   4,  18, -18,
    5, -18, -10,   6,
    8,  -8,   8, -18,
   14,  10, -10,  10,
   12,  30, -10,  15,
    0, -18,  18,  20,
  -10,  20, -10,  18,
   22,   8,  23,  25,
   13, -10,  26,  23,
  -22,  28,  -3, -25,
   30,  10,  20,  32,
  -10,   2,  34,  30,
   -8,  35,  13, -10,
   40, -10,  10,  -1
};
static char pchg0[6] = { 3, 3, 4, 5, 6, -1 };
static char* pchg[1] = { pchg0 };















void et1(sprite_status* actionwk) {
  switch (actionwk->r_no0) {

    case 0:
      m_init(actionwk);
    case 2:
      m_wait(actionwk);
      break;
    case 4:
      m_die(actionwk);
      break;
    case 6:
      m1wait(actionwk);
      break;
  }
  actionsub(actionwk);
  if (actionwk->r_no0 < 3) {
    frameout_s(actionwk);
  }
}


static void m_init(sprite_status* actionwk) {
  unsigned short* a1;
  unsigned short d0;

  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 4;
  actionwk->sprhs = 34;
  actionwk->sprhsize = 34;
  actionwk->sprvsize = 32;

  a1 = tbl0sproffset;
  d0 = (stageno.w + 1 << 2) + (time_flag & 65535);
  actionwk->sproffset = a1[d0];





  actionwk->patbase = z1_pats_et[stageno_i.b.l][time_flag_i & 0x7F];

  ((short*)actionwk)[24] = 0;
  ((short*)actionwk)[26] = actionwk->yposi.w.h;
  ((short*)actionwk)[23] = 4;
  ((short*)actionwk)[27] = 1;

  d0 = 0;
  if (generate_flag == 0) d0 += 2;
  if (time_flag == 0) ++d0;
  actionwk->patno = d0;
  if (generate_flag == 0 && time_flag == 0) {

    actionwk->colino = 250;
    actionwk->yposi.w.h -= 16;
  }
}

static void m_wait(sprite_status* actionwk) {
  int d0;
  sprite_status* a1;

  if (generate_flag != 0 || time_flag != 0) return;
  a_hover(actionwk);

  if (actionwk->colicnt != 0) {
    actionwk->colino = 0;
    ((short*)actionwk)[23] = 0;
    actionwk->patno = 7;
    actionwk->r_no0 += 2;
    generate_flag = 1;
    d0 = 150;
    scoreup(d0);
    a1 = &actwk[0];
    if (hitchk(actionwk, a1)) ride_on_clr(actionwk, a1);
    return;
  }
  hitchk(actionwk, &actwk[0]);
  patchg(actionwk, (unsigned char**)pchg);
}

static void m_die(sprite_status* actionwk) {
  sprite_status* a1;
  char d0;
  short d5, d6, a6;

  a6 = ((short*)actionwk)[24];
  d0 = tbl0[a6++];
  if (d0 < 0) {

    actionwk->r_no0 += 2;
    actionwk->actfree[0] = 8;
    return;
  }
  ++((char*)actionwk)[46];
  if (((char*)actionwk)[46] != d0) return;
  d5 = tbl0[a6++];
  d6 = tbl0[a6++];
  ((short*)actionwk)[24] = a6;
  if (actwkchk(&a1) != 0) return;
  a1->actno = 24;
  a1->r_no1 = 1;
  a1->xposi = actionwk->xposi;
  a1->yposi = actionwk->yposi;
  a1->xposi.w.h += d5;
  a1->yposi.w.h += d6;
  baku_init(a1);
  soundset(158);
}

static void m1wait(sprite_status* actionwk) {
  if (--actionwk->actfree[0]) return;
  actionwk->r_no0 -= 6;
  actionwk->yposi.w.h = ((short*)actionwk)[26];
  soundset(217);
}

static void a_hover(sprite_status* actionwk) {
  unsigned short d0;

  ++((unsigned short*)actionwk)[23];
  d0 = ((unsigned short*)actionwk)[23];
  d0 &= 7;
  if (d0 == 0) {

    d0 = ((unsigned short*)actionwk)[27];
    actionwk->yposi.w.h += d0;
  }
  d0 = ((unsigned short*)actionwk)[23];
  d0 &= 31;
  if (d0 == 0) ((short*)actionwk)[27] = -((short*)actionwk)[27];
}
