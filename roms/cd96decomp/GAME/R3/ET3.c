#include "../EQU.h"
#include "ET3.h"
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

static sprite_pattern z3tpat00 = { 1, { { -40, 16, 0, 509 } } };
static sprite_pattern z31atpat00 = { 1, { { -40, 16, 0, 562 } } };
static sprite_pattern z31btpat00 = { 1, { { -40, 16, 0, 556 } } };
static sprite_pattern z33tpat00 = { 1, { { -40, 16, 0, 560 } } };
static sprite_pattern z3tpat01 = { 1, { { -40, 16, 0, 510 } } };
static sprite_pattern z31atpat01 = { 1, { { -40, 16, 0, 563 } } };
static sprite_pattern z31btpat01 = { 1, { { -40, 16, 0, 557 } } };
static sprite_pattern z33tpat01 = { 1, { { -40, 16, 0, 561 } } };
static sprite_pattern z3tpat07 = { 1, { { 0, 0, 0, 0 } } };
static sprite_pattern z3tpat02 = { 1, { { -24, -32, 0, 516 } } };
static sprite_pattern z31atpat02 = { 1, { { -24, -32, 0, 569 } } };
static sprite_pattern z31btpat02 = { 1, { { -24, -32, 0, 563 } } };
static sprite_pattern z33tpat02 = { 1, { { -24, -32, 0, 567 } } };
static sprite_pattern z3tpat03 = { 3, { { -22, -8, 0, 518 }, { -24, -32, 0, 516 }, { -40, -32, 0, 517 } } };
static sprite_pattern z31atpat03 = { 3, { { -22, -8, 0, 571 }, { -24, -32, 0, 569 }, { -40, -32, 0, 570 } } };
static sprite_pattern z31btpat03 = { 3, { { -22, -8, 0, 565 }, { -24, -32, 0, 563 }, { -40, -32, 0, 564 } } };
static sprite_pattern z33tpat03 = { 3, { { -22, -8, 0, 569 }, { -24, -32, 0, 567 }, { -40, -32, 0, 568 } } };
static sprite_pattern z3tpat04 = { 4, { { -22, -8, 0, 519 }, { -24, -32, 0, 522 }, { -24, -32, 0, 516 }, { -40, -32, 0, 517 } } };
static sprite_pattern z31atpat04 = { 4, { { -22, -8, 0, 572 }, { -24, -32, 0, 575 }, { -24, -32, 0, 569 }, { -40, -32, 0, 570 } } };
static sprite_pattern z31btpat04 = { 4, { { -22, -8, 0, 566 }, { -24, -32, 0, 569 }, { -24, -32, 0, 563 }, { -40, -32, 0, 564 } } };
static sprite_pattern z33tpat04 = { 4, { { -22, -8, 0, 570 }, { -24, -32, 0, 573 }, { -24, -32, 0, 567 }, { -40, -32, 0, 568 } } };
static sprite_pattern z3tpat05 = { 4, { { -22, -8, 0, 520 }, { -24, -32, 0, 523 }, { -24, -32, 0, 516 }, { -40, -32, 0, 517 } } };
static sprite_pattern z31atpat05 = { 4, { { -22, -8, 0, 573 }, { -24, -32, 0, 576 }, { -24, -32, 0, 569 }, { -40, -32, 0, 570 } } };
static sprite_pattern z31btpat05 = { 4, { { -22, -8, 0, 567 }, { -24, -32, 0, 570 }, { -24, -32, 0, 563 }, { -40, -32, 0, 564 } } };
static sprite_pattern z33tpat05 = { 4, { { -22, -8, 0, 571 }, { -24, -32, 0, 574 }, { -24, -32, 0, 567 }, { -40, -32, 0, 568 } } };
static sprite_pattern z3tpat06 = { 4, { { -22, -8, 0, 521 }, { -24, -32, 0, 524 }, { -24, -32, 0, 516 }, { -40, -32, 0, 517 } } };
static sprite_pattern z31atpat06 = { 4, { { -22, -8, 0, 574 }, { -24, -32, 0, 577 }, { -24, -32, 0, 569 }, { -40, -32, 0, 570 } } };
static sprite_pattern z31btpat06 = { 4, { { -22, -8, 0, 568 }, { -24, -32, 0, 571 }, { -24, -32, 0, 563 }, { -40, -32, 0, 564 } } };
static sprite_pattern z33tpat06 = { 4, { { -22, -8, 0, 572 }, { -24, -32, 0, 575 }, { -24, -32, 0, 567 }, { -40, -32, 0, 568 } } };
sprite_pattern* z3_pat_et[8] =
{
  &z3tpat00,
  &z3tpat01,
  &z3tpat02,
  &z3tpat03,
  &z3tpat04,
  &z3tpat05,
  &z3tpat06,
  &z3tpat07
};
sprite_pattern* z31a_pat_et[8] =
{
  &z31atpat00,
  &z31atpat01,
  &z31atpat02,
  &z31atpat03,
  &z31atpat04,
  &z31atpat05,
  &z31atpat06,
  &z3tpat07
};
sprite_pattern* z31b_pat_et[8] =
{
  &z31btpat00,
  &z31btpat01,
  &z31btpat02,
  &z31btpat03,
  &z31btpat04,
  &z31btpat05,
  &z31btpat06,
  &z3tpat07
};
sprite_pattern* z33_pat_et[8] =
{
  &z33tpat00,
  &z33tpat01,
  &z33tpat02,
  &z33tpat03,
  &z33tpat04,
  &z33tpat05,
  &z33tpat06,
  &z3tpat07
};
sprite_pattern** z3_pats_et[3][3] =
{
  { z31b_pat_et, z31a_pat_et, z3_pat_et },
  { z3_pat_et, z31b_pat_et, z3_pat_et },
  { 0, 0, z33_pat_et }
};
static unsigned short tbl0sproffset[11] = { 1087, 1033, 0, 0, 1108, 1024, 0, 0, 0, 0, 0 };
static char tbl0[64] =
{
    1,   0,
    0,   2,
  -40, -20,
    3,  28,
   10,   4,
   18, -18,
    5, -18,
  -10,   6,
    8,  -8,
    8, -18,
   14,  10,
  -10,  10,
   12,  30,
  -10,  15,
    0, -18,
   18,  20,
  -10,  20,
  -10,  18,
   22,   8,
   23,  25,
   13, -10,
   26,  23,
  -22,  28,
   -3, -25,
   30,  10,
   20,  32,
  -10,   2,
   34,  30,
   -8,  35,
   13, -10,
   40, -10,
   10,  -1
};
static char pchg0[6] = { 3, 3, 4, 5, 6, -1 };
static char* pchg[1] = { pchg0 };












void et3(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
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
  if (actionwk->r_no0 <= 2)
    frameout_s(actionwk);

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
  d0 = (stageno.w + 1 << 2) + (unsigned short)time_flag;
  actionwk->sproffset = a1[d0];





  actionwk->patbase = z3_pats_et[stageno_i.b.l][time_flag_i & 0x7F];

  ((short*)actionwk)[24] = 0;
  ((short*)actionwk)[26] = actionwk->yposi.w.h;
  ((short*)actionwk)[23] = 4;
  ((short*)actionwk)[27] = 1;

  d0 = 0;
  if (generate_flag == 0) d0 += 2;
  if (time_flag == 0) ++d0;
  actionwk->patno = d0;
  if (generate_flag == 0 && time_flag == 0)
  {
    actionwk->colino = 250;
    actionwk->yposi.w.h -= 16;
  }
}

static void m_wait(sprite_status* actionwk) {
  int d0;
  sprite_status* a1;

  if (generate_flag != 0 || time_flag != 0) return;
  a_hover(actionwk);

  if (actionwk->colicnt == 0) goto label1;
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
label1:
  hitchk(actionwk, &actwk[0]);
  patchg(actionwk, (unsigned char**)pchg);
}

static void m_die(sprite_status* actionwk) {
  sprite_status* a1;
  char d0;
  short d5, d6, a6;

  a6 = ((short*)actionwk)[24];
  d0 = tbl0[a6++];
  if (d0 < 0)
  {
    actionwk->r_no0 += 2;
    ((char*)actionwk)[46] = 8;
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
  if (d0 == 0)
  {
    d0 = ((unsigned short*)actionwk)[27];
    actionwk->yposi.w.h += d0;
  }
  d0 = ((unsigned short*)actionwk)[23];
  d0 &= 31;
  if (d0 == 0) ((short*)actionwk)[27] = -((short*)actionwk)[27];
}
