#include "../EQU.h"
#include "MOVIE1.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../RIDECHK.h"
#include "../SCR.h"

static void die(sprite_status* pActwk);
static void mm_init(sprite_status* pActwk);
static void mm_wait(sprite_status* pActwk);
static void mm_die(sprite_status* pActwk);
static void m_baku(sprite_status* pActwk);
static void mm1wait(sprite_status* pActwk);
static void sub(sprite_status* pActwk);
static void s_init(sprite_status* pActwk);
static void s_move(sprite_status* pActwk);

unsigned char movie1_pchg00[6] = { 0, 2, 1, 3, 1, 255 };
unsigned char movie1_pchg01[58] =
{
  0,
  4, 4, 1, 4,
  4, 1, 4, 4,
  1, 4, 4, 1,
  4, 4, 1, 1,
  4, 4, 1, 1,
  4, 4, 1, 1,
  4, 4, 1, 1,
  5, 5, 1, 5,
  5, 1, 5, 5,
  1, 5, 5, 1,
  5, 5, 1, 1,
  5, 5, 1, 1,
  5, 5, 1, 1,
  5, 5, 1, 1,
  255
};
unsigned char* movie1_pchg[2] =
{
  movie1_pchg00,
  movie1_pchg01
};
sprite_pattern z11a_spr_movie1 = { 1, { { -12, -12, 0, 543 } } };
sprite_pattern z11b_spr_movie1 = { 1, { { -12, -12, 0, 528 } } };
sprite_pattern z11c_spr_movie1 = { 1, { { -12, -12, 0, 509 } } };
sprite_pattern z12a_spr_movie1 = { 1, { { -12, -12, 0, 519 } } };
sprite_pattern z12c_spr_movie1 = { 1, { { -12, -12, 0, 510 } } };
sprite_pattern z11a_spr_movie2 = { 1, { { -8, -4, 0, 544 } } };
sprite_pattern z11b_spr_movie2 = { 1, { { -8, -4, 0, 529 } } };
sprite_pattern z11c_spr_movie2 = { 1, { { -8, -4, 0, 510 } } };
sprite_pattern z12a_spr_movie2 = { 1, { { -8, -4, 0, 520 } } };
sprite_pattern z12c_spr_movie2 = { 1, { { -8, -4, 0, 511 } } };
sprite_pattern z11a_spr_movie3 = { 1, { { -8, -4, 0, 545 } } };
sprite_pattern z11b_spr_movie3 = { 1, { { -8, -4, 0, 530 } } };
sprite_pattern z11c_spr_movie3 = { 1, { { -8, -4, 0, 511 } } };
sprite_pattern z12a_spr_movie3 = { 1, { { -8, -4, 0, 521 } } };
sprite_pattern z12c_spr_movie3 = { 1, { { -8, -4, 0, 512 } } };
sprite_pattern z11a_spr_movie4 = { 1, { { -20, -24, 0, 546 } } };
sprite_pattern z11b_spr_movie4 = { 1, { { -20, -24, 0, 531 } } };
sprite_pattern z11c_spr_movie4 = { 1, { { -20, -24, 0, 512 } } };
sprite_pattern z12a_spr_movie4 = { 1, { { -20, -24, 0, 522 } } };
sprite_pattern z12c_spr_movie4 = { 1, { { -20, -24, 0, 513 } } };
sprite_pattern z11a_spr_movie5 = { 1, { { -20, -24, 0, 547 } } };
sprite_pattern z11b_spr_movie5 = { 1, { { -20, -24, 0, 532 } } };
sprite_pattern z11c_spr_movie5 = { 1, { { -20, -24, 0, 513 } } };
sprite_pattern z12a_spr_movie5 = { 1, { { -20, -24, 0, 523 } } };
sprite_pattern z12c_spr_movie5 = { 1, { { -20, -24, 0, 514 } } };
sprite_pattern z11a_spr_movie0 = { 0, { { -20, -24, 0, 547 } } };
sprite_pattern z11b_spr_movie0 = { 0, { { -20, -24, 0, 532 } } };
sprite_pattern z11c_spr_movie0 = { 0, { { -20, -24, 0, 513 } } };
sprite_pattern z12a_spr_movie0 = { 0, { { -20, -24, 0, 523 } } };
sprite_pattern z12c_spr_movie0 = { 0, { { -20, -24, 0, 514 } } };
sprite_pattern* z11a_pat_movie1[6] =
{
  &z11a_spr_movie1,
  &z11a_spr_movie0,
  &z11a_spr_movie2,
  &z11a_spr_movie3,
  &z11a_spr_movie4,
  &z11a_spr_movie5
};
sprite_pattern* z11b_pat_movie1[6] =
{
  &z11b_spr_movie1,
  &z11b_spr_movie0,
  &z11b_spr_movie2,
  &z11b_spr_movie3,
  &z11b_spr_movie4,
  &z11b_spr_movie5
};
sprite_pattern* z11c_pat_movie1[6] =
{
  &z11c_spr_movie1,
  &z11c_spr_movie0,
  &z11c_spr_movie2,
  &z11c_spr_movie3,
  &z11c_spr_movie4,
  &z11c_spr_movie5
};
sprite_pattern* z12a_pat_movie1[6] =
{
  &z12a_spr_movie1,
  &z12a_spr_movie0,
  &z12a_spr_movie2,
  &z12a_spr_movie3,
  &z12a_spr_movie4,
  &z12a_spr_movie5
};
sprite_pattern* z12c_pat_movie1[6] =
{
  &z12c_spr_movie1,
  &z12c_spr_movie0,
  &z12c_spr_movie2,
  &z12c_spr_movie3,
  &z12c_spr_movie4,
  &z12c_spr_movie5
};
sprite_pattern** pats_movie1[2][3] =
{
  { z11b_pat_movie1, z11a_pat_movie1, z11c_pat_movie1 },
  { z12a_pat_movie1, z12a_pat_movie1, z12c_pat_movie1 }
};
static char tbl0[37] =
{
    1,   0,   0,   5,
  -18, -10,  10, -10,
   10,  15,   0, -18,
   20, -10,  18,  22,
    8,  23,  25,  13,
  -10,  28,  -3, -25,
   30,  10,  20,  32,
  -10,   2,  35,  13,
  -10,  40, -10,  10,
  -1
};














void movie1(sprite_status* pActwk) {
  void(*tbl_m[5])(sprite_status*) =
  {
    &mm_init,
    &mm_wait,
    &mm_die,
    &m_baku,
    &mm1wait
  };

  if (pActwk->userflag.b.h)
    sub(pActwk);
  else
  {
    tbl_m[pActwk->r_no0 / 2](pActwk);
    actionsub(pActwk);
    if (pActwk->r_no0 <= 2)
    {
      if (frameout_s(pActwk) != 0) return;
      divdevset(4);
    }
  }
}




static void die(sprite_status* pActwk) {
  frameout(pActwk);
}




static void mm_init(sprite_status* pActwk) {
  sprite_status* subactwk;

  if (projector_flag)
  {
    die(pActwk);
    return;
  }
  divdevset(5);

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 4;
  pActwk->sprhs = 12;
  pActwk->sprhsize = 12;
  pActwk->sprvsize = 12;
  pActwk->colino = 251;

  if (stageno.b.l) pActwk->sproffset = 9135;
  else pActwk->sproffset = 1027;

  pActwk->patbase = pats_movie1[stageno_i.b.l][time_flag_i & 0x7F];
  ((char**)pActwk)[12] = tbl0;

  if (actwkchk(&subactwk) != 0)
  {
    die(pActwk);
    return;
  }
  subactwk->actno = pActwk->actno;
  subactwk->xposi.w.h = pActwk->xposi.w.h - 21;
  subactwk->yposi.w.h = pActwk->yposi.w.h - 7;
  subactwk->userflag.b.h = -1;
  ((short*)subactwk)[33] = (unsigned short)(unsigned char)(pActwk - actwk);

  if (actwkchk(&subactwk) != 0)
  {
    die(pActwk);
    return;
  }
  subactwk->actno = pActwk->actno;
  subactwk->xposi.w.h = pActwk->xposi.w.h - 88;
  subactwk->yposi.w.h = pActwk->yposi.w.h - 4;
  subactwk->userflag.b.h = 1;
  ((short*)subactwk)[33] = (unsigned short)(unsigned char)(pActwk - actwk);

  if (actwkchk(&subactwk) != 0)
  {
    die(pActwk);
    return;
  }
  subactwk->actno = 36;
  subactwk->xposi.w.h = pActwk->xposi.w.h - 88;
  subactwk->yposi.w.h = pActwk->yposi.w.h - 24;
  subactwk->userflag.b.h = -128;
  ((short*)subactwk)[33] = (unsigned short)(unsigned char)(pActwk - actwk);

  if (actwkchk(&subactwk) != 0)
  {
    die(pActwk);
    return;
  }
  subactwk->actno = 36;
  subactwk->xposi.w.h = pActwk->xposi.w.h - 100;
  subactwk->yposi.w.h = pActwk->yposi.w.h + 4;
  subactwk->userflag.b.h = -127;
  ((short*)subactwk)[33] = (unsigned short)(unsigned char)(pActwk - actwk);
}



static void mm_wait(sprite_status* pActwk) {
  if (pActwk->colicnt)
  {
    pActwk->colino = 0;
    pActwk->colicnt = 0;
    pActwk->r_no0 += 2;
  }
  hitchk(pActwk, &actwk[0]);
}



static void mm_die(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->patno = 1;
  pActwk->actfree[21] = 255;
  divdevset(4);
  if (hitchk(pActwk, &actwk[0])) ride_on_clr(pActwk, &actwk[0]);
}



static void m_baku(sprite_status* pActwk) {
  char* temp;
  unsigned char timeb;
  char xx, yy;
  sprite_status* subactwk;

  temp = ((char**)pActwk)[12];
  if (*temp >= 0)
  {
    ((unsigned short*)pActwk)[23] += 256;
    timeb = ((unsigned short*)pActwk)[23] >> 8;
    if (timeb != *temp) return;

    ++temp;
    xx = *temp;
    ++temp;
    yy = *temp;
    ++temp;
    ((char**)pActwk)[12] = temp;
    if (actwkchk(&subactwk) != 0) return;

    subactwk->actno = 24;
    subactwk->r_no1 = 1;
    subactwk->xposi.w.h = pActwk->xposi.w.h;
    subactwk->yposi.w.h = pActwk->yposi.w.h;
    subactwk->xposi.w.h += (unsigned short)xx;
    subactwk->yposi.w.h += (unsigned short)yy;
    soundset(158);


    return;
  }

  pActwk->r_no0 += 2;
  ((short*)pActwk)[23] = 60;

}



static void mm1wait(sprite_status* pActwk) {
  --((unsigned short*)pActwk)[23];
  if (!((unsigned short*)pActwk)[23])
  {
    projector_flag = 255;
    die(pActwk);
  }
}



static void sub(sprite_status* pActwk) {
  short subact;

  subact = ((short*)pActwk)[33];
  if (actwk[subact].actno != 46)
  {
    die(pActwk);
    return;
  }
  if (actwk[subact].actfree[21])
  {
    die(pActwk);
    return;
  }
  if (pActwk->r_no0)
  {
    s_move(pActwk);
    return;
  }
  s_init(pActwk);
}



static void s_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 4;

  if (!stageno.b.l)
    pActwk->sproffset = 1027;
  else
    pActwk->sproffset = 9135;

  pActwk->patbase = pats_movie1[stageno_i.b.l][time_flag_i & 0x7F];
  if (pActwk->userflag.b.h < 0)
  {

    pActwk->sprhs = 8;
    pActwk->sprhsize = 8;
    pActwk->sprvsize = 4;
    pActwk->mstno.b.h = 0;
  }
  else
  {

    pActwk->sprhs = 20;
    pActwk->sprhsize = 20;
    pActwk->sprvsize = 24;
    pActwk->mstno.b.h = 1;
  }
  s_move(pActwk);
}



static void s_move(sprite_status* pActwk) {

  patchg(pActwk, movie1_pchg);
  actionsub(pActwk);
}
