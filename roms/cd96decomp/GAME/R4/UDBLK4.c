#include "../EQU.h"
#include "UDBLK4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../RIDECHK.h"

typedef struct {
  unsigned char kakudo;
  char xofst;
}
kakudo_xofst;

typedef struct {
  char xofs;
  char yofs;
  short yspd;
}
xofs_yofs_yspd;

static void sin_move(sprite_status* pActwk, short d2, short d3);
static void udblk4_type1(sprite_status* pActwk);
static void type1_init(sprite_status* pActwk);
static void type1_move(sprite_status* pActwk);
static void udblk4_type2(sprite_status* pActwk);
static void udblk4_type3(sprite_status* pActwk);
static void type3_init(sprite_status* pActwk);
static void type3_move(sprite_status* pActwk);
static void udblk4_type4(sprite_status* pActwk);
static void type4_coset(sprite_status* pActwk, sprite_status* pNewActwk, unsigned char d0, short d1);
static void type4_init(sprite_status* pActwk);
static void type4_move(sprite_status* pActwk);
static void udblk4_type5(sprite_status* pActwk);
static void type5_coset(sprite_status* pActwk, sprite_status* pNewActwk, unsigned char d0, short d1, unsigned char d2, short d3);
static void type5_init(sprite_status* pActwk);
static void type5_move(sprite_status* pActwk);
static void udblk4_type6(sprite_status* pActwk);
static void type6_init(sprite_status* pActwk);
static void type6_move(sprite_status* pActwk);
static void udblk4_type7(sprite_status* pActwk);
static void type7_coset(sprite_status* pActwk, sprite_status* pNewActwk, unsigned char d0, short d1, unsigned char d2);
static void type7_init(sprite_status* pActwk);
static void type7_move(sprite_status* pActwk);
static void udblk4_type8(sprite_status* pActwk);
static void type8_init(sprite_status* pActwk);
static void type8_move(sprite_status* pActwk);
static void udblk4_type9(sprite_status* pActwk);
static void type9_init(sprite_status* pActwk);
static void type9_move(sprite_status* pActwk);
static void udblk4_typeA(sprite_status* pActwk);
static void typeA_init(sprite_status* pActwk);
static void typeA_move(sprite_status* pActwk);
static void udblk4_typeB(sprite_status* pActwk);
static void typeB_init(sprite_status* pActwk);
static void typeB_move(sprite_status* pActwk);

static sprite_pattern z41bpat00 = { 1, { { -16, -64, 0, 523 } } };
static sprite_pattern z41cpat00 = { 1, { { -16, -64, 0, 494 } } };
static sprite_pattern z41dpat00 = { 1, { { -16, -64, 0, 485 } } };
static sprite_pattern z42bpat00 = { 1, { { -16, -64, 0, 511 } } };
static sprite_pattern z42cpat00 = { 1, { { -16, -64, 0, 514 } } };
static sprite_pattern z41bpat01 = { 1, { { -32, -96, 0, 524 } } };
static sprite_pattern z41cpat01 = { 1, { { -32, -96, 0, 495 } } };
static sprite_pattern z41dpat01 = { 1, { { -32, -96, 0, 486 } } };
static sprite_pattern z42bpat01 = { 1, { { -32, -96, 0, 512 } } };
static sprite_pattern z42cpat01 = { 1, { { -32, -96, 0, 515 } } };
static sprite_pattern z41bpat02 = { 1, { { -16, -48, 0, 525 } } };
static sprite_pattern z41cpat02 = { 1, { { -16, -48, 0, 496 } } };
static sprite_pattern z41dpat02 = { 1, { { -16, -48, 0, 487 } } };
static sprite_pattern z42bpat02 = { 1, { { -16, -48, 0, 513 } } };
static sprite_pattern z42cpat02 = { 1, { { -16, -48, 0, 516 } } };
static sprite_pattern z41bpat03 = { 1, { { -16, -64, 0, 526 } } };
static sprite_pattern z41cpat03 = { 1, { { -16, -64, 0, 497 } } };
static sprite_pattern z41dpat03 = { 1, { { -16, -64, 0, 488 } } };
static sprite_pattern z42bpat03 = { 1, { { -16, -64, 0, 514 } } };
static sprite_pattern z42cpat03 = { 1, { { -16, -64, 0, 517 } } };
static sprite_pattern z41bpat04 = { 1, { { -16, -32, 0, 527 } } };
static sprite_pattern z41cpat04 = { 1, { { -16, -32, 0, 498 } } };
static sprite_pattern z41dpat04 = { 1, { { -16, -32, 0, 489 } } };
static sprite_pattern z42bpat04 = { 1, { { -16, -32, 0, 515 } } };
static sprite_pattern z42cpat04 = { 1, { { -16, -32, 0, 518 } } };
static sprite_pattern z41bpat05 = { 1, { { -16, -96, 0, 528 } } };
static sprite_pattern z41cpat05 = { 1, { { -16, -96, 0, 499 } } };
static sprite_pattern z41dpat05 = { 1, { { -16, -96, 0, 490 } } };
static sprite_pattern z42bpat05 = { 1, { { -16, -96, 0, 516 } } };
static sprite_pattern z42cpat05 = { 1, { { -16, -96, 0, 519 } } };
static sprite_pattern z41bpat06 = { 1, { { -32, -48, 0, 529 } } };
static sprite_pattern z41cpat06 = { 1, { { -32, -48, 0, 500 } } };
static sprite_pattern z41dpat06 = { 1, { { -32, -48, 0, 491 } } };
static sprite_pattern z42bpat06 = { 1, { { -32, -48, 0, 517 } } };
static sprite_pattern z42cpat06 = { 1, { { -32, -48, 0, 520 } } };
static sprite_pattern z41bpat07 = { 1, { { -16, -16, 0, 530 } } };
static sprite_pattern z41cpat07 = { 1, { { -16, -16, 0, 501 } } };
static sprite_pattern z41dpat07 = { 1, { { -16, -16, 0, 492 } } };
static sprite_pattern z42bpat07 = { 1, { { -16, -16, 0, 518 } } };
static sprite_pattern z42cpat07 = { 1, { { -16, -16, 0, 521 } } };
sprite_pattern* z41budblk4pat1[1] = { &z41bpat00 };
sprite_pattern* z41cudblk4pat1[1] = { &z41cpat00 };
sprite_pattern* z41dudblk4pat1[1] = { &z41dpat00 };
sprite_pattern* z42budblk4pat1[1] = { &z42bpat00 };
sprite_pattern* z42cudblk4pat1[1] = { &z42cpat00 };
sprite_pattern** udblk4pat1s[2][4] =
{
  { z41budblk4pat1, z41budblk4pat1, z41dudblk4pat1, z41cudblk4pat1 },
  { z42budblk4pat1, z42budblk4pat1, z42cudblk4pat1, z42cudblk4pat1 }
};
sprite_pattern* z41budblk4pat3[1] = { &z41bpat01 };
sprite_pattern* z41cudblk4pat3[1] = { &z41cpat01 };
sprite_pattern* z41dudblk4pat3[1] = { &z41dpat01 };
sprite_pattern* z42budblk4pat3[1] = { &z42bpat01 };
sprite_pattern* z42cudblk4pat3[1] = { &z42cpat01 };
sprite_pattern** udblk4pat3s[2][4] =
{
  { z41budblk4pat3, z41budblk4pat3, z41dudblk4pat3, z41cudblk4pat3 },
  { z42budblk4pat3, z42budblk4pat3, z42cudblk4pat3, z42cudblk4pat3 }
};
sprite_pattern* z41budblk4pat4[1] = { &z41bpat02 };
sprite_pattern* z41cudblk4pat4[1] = { &z41cpat02 };
sprite_pattern* z41dudblk4pat4[1] = { &z41dpat02 };
sprite_pattern* z42budblk4pat4[1] = { &z42bpat02 };
sprite_pattern* z42cudblk4pat4[1] = { &z42cpat02 };
sprite_pattern** udblk4pat4s[2][4] =
{
  { z41budblk4pat4, z41budblk4pat4, z41dudblk4pat4, z41cudblk4pat4 },
  { z42budblk4pat4, z42budblk4pat4, z42cudblk4pat4, z42cudblk4pat4 }
};
sprite_pattern* z41budblk4pat5[1] = { &z41bpat03 };
sprite_pattern* z41cudblk4pat5[1] = { &z41cpat03 };
sprite_pattern* z41dudblk4pat5[1] = { &z41dpat03 };
sprite_pattern* z42budblk4pat5[1] = { &z42bpat03 };
sprite_pattern* z42cudblk4pat5[1] = { &z42cpat03 };
sprite_pattern** udblk4pat5s[2][4] =
{
  { z41budblk4pat5, z41budblk4pat5, z41dudblk4pat5, z41cudblk4pat5 },
  { z42budblk4pat5, z42budblk4pat5, z42cudblk4pat5, z42cudblk4pat5 }
};
sprite_pattern* z41budblk4pat7[1] = { &z41bpat03 };
sprite_pattern* z41cudblk4pat7[1] = { &z41cpat03 };
sprite_pattern* z41dudblk4pat7[1] = { &z41dpat03 };
sprite_pattern* z42budblk4pat7[1] = { &z42bpat03 };
sprite_pattern* z42cudblk4pat7[1] = { &z42cpat03 };
sprite_pattern** udblk4pat7s[2][4] =
{
  { z41budblk4pat7, z41budblk4pat7, z41dudblk4pat7, z41cudblk4pat7 },
  { z42budblk4pat7, z42budblk4pat7, z42cudblk4pat7, z42cudblk4pat7 }
};
sprite_pattern* z41budblk4pat8[1] = { &z41bpat04 };
sprite_pattern* z41cudblk4pat8[1] = { &z41cpat04 };
sprite_pattern* z41dudblk4pat8[1] = { &z41dpat04 };
sprite_pattern* z42budblk4pat8[1] = { &z42bpat04 };
sprite_pattern* z42cudblk4pat8[1] = { &z42cpat04 };
sprite_pattern** udblk4pat8s[2][4] =
{
  { z41budblk4pat8, z41budblk4pat8, z41dudblk4pat8, z41cudblk4pat8 },
  { z42budblk4pat8, z42budblk4pat8, z42cudblk4pat8, z42cudblk4pat8 }
};
sprite_pattern* z41budblk4pat6[2] =
{
  &z41bpat05,
  &z41bpat06
};
sprite_pattern* z41cudblk4pat6[2] =
{
  &z41cpat05,
  &z41cpat06
};
sprite_pattern* z41dudblk4pat6[2] =
{
  &z41dpat05,
  &z41dpat06
};
sprite_pattern* z42budblk4pat6[2] =
{
  &z42bpat05,
  &z42bpat06
};
sprite_pattern* z42cudblk4pat6[2] =
{
  &z42cpat05,
  &z42cpat06
};
sprite_pattern** udblk4pat6s[2][4] =
{
  { z41budblk4pat6, z41budblk4pat6, z41dudblk4pat6, z41cudblk4pat6 },
  { z42budblk4pat6, z42budblk4pat6, z42cudblk4pat6, z42cudblk4pat6 }
};
sprite_pattern* z41budblk4pat9[2] =
{
  &z41bpat05,
  &z41bpat06
};
sprite_pattern* z41cudblk4pat9[2] =
{
  &z41cpat05,
  &z41cpat06
};
sprite_pattern* z41dudblk4pat9[2] =
{
  &z41dpat05,
  &z41dpat06
};
sprite_pattern* z42budblk4pat9[2] =
{
  &z42bpat05,
  &z42bpat06
};
sprite_pattern* z42cudblk4pat9[2] =
{
  &z42cpat05,
  &z42cpat06
};
sprite_pattern** udblk4pat9s[2][4] =
{
  { z41budblk4pat9, z41budblk4pat9, z41dudblk4pat9, z41cudblk4pat9 },
  { z42budblk4pat9, z42budblk4pat9, z42cudblk4pat9, z42cudblk4pat9 }
};
sprite_pattern* z41budblk4patA[1] = { &z41bpat07 };
sprite_pattern* z41cudblk4patA[1] = { &z41cpat07 };
sprite_pattern* z41dudblk4patA[1] = { &z41dpat07 };
sprite_pattern* z42budblk4patA[1] = { &z42bpat07 };
sprite_pattern* z42cudblk4patA[1] = { &z42cpat07 };
sprite_pattern** udblk4patAs[2][4] =
{
  { z41budblk4patA, z41budblk4patA, z41dudblk4patA, z41cudblk4patA },
  { z42budblk4patA, z42budblk4patA, z42cudblk4patA, z42cudblk4patA }
};


void udblk4(sprite_status* pActwk) {
  void(*tbl[12])(sprite_status*) =
  {
    &udblk4_type1,
    &udblk4_type1,
    &udblk4_type2,
    &udblk4_type3,
    &udblk4_type4,
    &udblk4_type5,
    &udblk4_type6,
    &udblk4_type7,
    &udblk4_type8,
    &udblk4_type9,
    &udblk4_typeA,
    &udblk4_typeB
  };

  tbl[pActwk->userflag.b.h](pActwk);
}




static void sin_move(sprite_status* pActwk, short d2, short d3) {
  int_union ld0;
  int stk;
  short d0, d1;

  if (pActwk->yspeed.w < 0)
  {
    ride_on_chk(pActwk, &actwk[0]);
  }
  stk = pActwk->yposi.l;
  sinset(pActwk->actfree[16], &d0, &d1);
  d1 = d0;
  d0 <<= d2;
  d1 <<= d3;
  d0 += d1;
  d0 >>= 8;

  ++pActwk->actfree[16];
  d0 += ((short*)pActwk)[27];
  pActwk->yposi.w.h = d0;
  ld0.w.h = d0;
  ld0.w.l = 0;
  ld0.l -= stk;
  ld0.l >>= 8;
  pActwk->yspeed.w = ld0.w.l;

  if (pActwk->yspeed.w >= 0)
  {
    ride_on_chk(pActwk, &actwk[0]);
  }
}




static void udblk4_type1(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type1_init,
    &type1_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}




static void type1_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  short i;
  unsigned char d0, d1;
  kakudo_xofst tbl[7] =
  {
    { 192,   0 },
    { 168, -32 },
    { 144, -64 },
    { 120, -96 },
    { 216,  32 },
    { 240,  64 },
    {   8,  96 }
  };

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = udblk4pat1s[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  ((short*)pActwk)[27] = pActwk->yposi.w.h + 64;
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 64;

  if (pActwk->actfree[18] == 0)
  {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    d1 = 1;
    for (i = 0; i <= 5; ++i)
    {
      if (actwkchk(&pNewActwk) == 0)
      {
        pNewActwk->actno = 35;
        pNewActwk->userflag.b.h = 1;
        pNewActwk->xposi.w.h = pActwk->xposi.w.h;
        pNewActwk->yposi.w.h = pActwk->yposi.w.h;
        ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
        pNewActwk->actfree[18] = d1;
      }
      ++d1;
    }
  }
  d0 = pActwk->actfree[18];
  pActwk->actfree[16] = tbl[d0].kakudo;
  pActwk->xposi.w.h += tbl[d0].xofst;
  type1_move(pActwk);
}




static void type1_move(sprite_status* pActwk) {
  sin_move(pActwk, 6, 0);
}




static void udblk4_type2(sprite_status* pActwk) {

}




static void udblk4_type3(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type3_init,
    &type3_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}




static void type3_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = udblk4pat3s[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  ((short*)pActwk)[29] = pActwk->xposi.w.h;
  ((short*)pActwk)[27] = pActwk->yposi.w.h - 80;
  pActwk->sprhsize = 32;
  pActwk->sprvsize = 96;
  pActwk->actfree[16] = 64;

  type3_move(pActwk);
}




static void type3_move(sprite_status* pActwk) {
  sin_move(pActwk, 6, 4);
}




static void udblk4_type4(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type4_init,
    &type4_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}




static void type4_coset(sprite_status* pActwk, sprite_status* pNewActwk, unsigned char d0, short d1) {
  pNewActwk->actno = 35;
  pNewActwk->userflag.b.h = 4;
  pNewActwk->actfree[18] = d0;
  pNewActwk->yposi.w.h = pActwk->yposi.w.h;
  pNewActwk->xposi.w.h = pActwk->xposi.w.h + d1;
  ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
}




static void type4_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = udblk4pat4s[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  ((short*)pActwk)[27] = pActwk->yposi.w.h + 48;
  pActwk->sprhsize = 18;
  pActwk->sprvsize = 48;
  pActwk->actfree[16] = 192;

  if (pActwk->actfree[18] == 0)
  {

    ((short*)pActwk)[29] = pActwk->xposi.w.h;
  }
  if (actwkchk(&pNewActwk) == 0)
  {

    pNewActwk->actno = 34;

    pNewActwk->xposi.w.h = pActwk->xposi.w.h;
    pNewActwk->yposi.w.h = pActwk->yposi.w.h;
    ((short*)pNewActwk)[29] = ((short*)pActwk)[29];

    ((short*)pNewActwk)[28] = (unsigned short)(pActwk - actwk);
    pNewActwk->actfree[15] = 64;
    pNewActwk->userflag.b.h = 1;
  }
  if (pActwk->actfree[18] == 0)
  {
    if (actwkchk(&pNewActwk) == 0)
    {
      type4_coset(pActwk, pNewActwk, 1, -80);
    }
    if (actwkchk(&pNewActwk) == 0)
    {
      type4_coset(pActwk, pNewActwk, 2, 80);
    }
  }

  type4_move(pActwk);
}




static void type4_move(sprite_status* pActwk) {
  short stk;
  short d0, d1;

  stk = pActwk->yposi.w.h;
  sinset(pActwk->actfree[16], &d0, &d1);
  d0 *= 3;
  d0 >>= 4;
  d0 += ((short*)pActwk)[27];
  pActwk->yposi.w.h = d0;
  ++pActwk->actfree[16];
  d1 = stk;
  d0 -= d1;
  d0 <<= 8;
  pActwk->yspeed.w = d0;
  d1 = ((short*)pActwk)[28];
  if (d1)
  {
    actwk[d1].yspeed.w = d0;
  }
  ride_on_chk(pActwk, &actwk[0]);
}




static void udblk4_type5(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type5_init,
    &type5_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}




static void type5_coset(sprite_status* pActwk, sprite_status* pNewActwk, unsigned char d0, short d1, unsigned char d2, short d3) {
  pNewActwk->actno = 35;
  pNewActwk->userflag.b.h = 5;
  pNewActwk->actfree[18] = d0;
  pNewActwk->actfree[16] = d2;

  pNewActwk->xposi.w.h = pActwk->xposi.w.h + d1;

  pNewActwk->yposi.w.h = pActwk->yposi.w.h + d3;
  ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
}




static void type5_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = udblk4pat5s[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  ((short*)pActwk)[27] = pActwk->yposi.w.h + 64;
  pActwk->sprhsize = 20;
  pActwk->sprvsize = 65;

  if (pActwk->actfree[18] == 0)
  {

    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    pActwk->actfree[16] = 0;
    if (actwkchk(&pNewActwk) == 0)
    {
      type5_coset(pActwk, pNewActwk, 1, 32, 240, -32);
    }
    if (actwkchk(&pNewActwk) == 0)
    {
      type5_coset(pActwk, pNewActwk, 1, 64, 224, -64);
    }
    if (actwkchk(&pNewActwk) == 0)
    {
      type5_coset(pActwk, pNewActwk, 1, 96, 208, -96);
    }
  }

  type5_move(pActwk);
}




static void type5_move(sprite_status* pActwk) {
  sin_move(pActwk, 6, 0);
}




static void udblk4_type6(sprite_status* pActwk) {
  if (pActwk->r_no0) type6_move(pActwk);
  else type6_init(pActwk);
}




static void type6_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  short i, d1;
  kakudo_xofst tbl[7] =
  {
    {   0,   0 },
    {  32, -32 },
    {  64, -64 },
    {  96, -96 },
    {  32,  32 },
    {  64,  64 },
    {  96,  96 }
  };

  pActwk->r_no0 += 2;
  ((short*)pActwk)[29] = pActwk->xposi.w.h;
  d1 = 0;
  for (i = 0; i <= 6; ++i)
  {
    if (actwkchk(&pNewActwk) == 0)
    {
      pNewActwk->actno = 35;
      pNewActwk->userflag.b.h = 9;
      pNewActwk->yposi.w.h = pActwk->yposi.w.h;
      ((short*)pNewActwk)[28] = (unsigned short)(pActwk - actwk);
      pNewActwk->actfree[19] = 255;
      pNewActwk->actfree[16] = tbl[d1].kakudo;
      pNewActwk->xposi.w.h = pActwk->xposi.w.h + (short)tbl[d1].xofst;
    }
    ++d1;
  }
  type6_move(pActwk);
}




static void type6_move(sprite_status* pActwk) {
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}




static void udblk4_type7(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type7_init,
    &type7_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}




static void type7_coset(sprite_status* pActwk, sprite_status* pNewActwk, unsigned char d0, short d1, unsigned char d2) {
  pNewActwk->actno = 35;
  pNewActwk->userflag.b.h = 7;
  pNewActwk->actfree[18] = d0;
  pNewActwk->actfree[16] = d2;
  pNewActwk->yposi.w.h = pActwk->yposi.w.h;

  pNewActwk->xposi.w.h = pActwk->xposi.w.h + d1;
  ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
}




static void type7_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = udblk4pat7s[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  ((short*)pActwk)[27] = pActwk->yposi.w.h + 64;
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 64;

  if (pActwk->actfree[18] == 0)
  {

    ((short*)pActwk)[29] = pActwk->xposi.w.h + 48;
    pActwk->actfree[16] = 192;
    if (actwkchk(&pNewActwk) == 0)
    {
      type7_coset(pActwk, pNewActwk, 1, 32, 224);
    }
    if (actwkchk(&pNewActwk) == 0)
    {
      type7_coset(pActwk, pNewActwk, 1, 64, 0);
    }
    if (actwkchk(&pNewActwk) == 0)
    {
      type7_coset(pActwk, pNewActwk, 1, 96, 32);
    }
  }

  type7_move(pActwk);
}




static void type7_move(sprite_status* pActwk) {
  sin_move(pActwk, 6, 0);
}




static void udblk4_type8(sprite_status* pActwk) {
  short d0;
  void(*tbl[2])(sprite_status*) =
  {
    &type8_init,
    &type8_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);

  d0 = ((short*)pActwk)[28];
  if (d0)
  {
    if (actwk[d0].actno != 35)
    {
      frameout_s0(pActwk);
    }
  }
  else
  {
    frameout_s00(pActwk, ((short*)pActwk)[29]);
  }
}




static void type8_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  short i;
  short d0;
  unsigned char d1;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = udblk4pat8s[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  ((short*)pActwk)[27] = pActwk->yposi.w.h - 32;
  pActwk->sprhsize = 32;
  pActwk->sprvsize = 48;
  if (pActwk->actfree[19] == 0)
  {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
  }

  if (pActwk->actfree[18] == 0)
  {
    if (actwkchk(&pNewActwk) == 0)
    {
      pNewActwk->actno = 35;
      pNewActwk->actfree[18] = 1;
      pNewActwk->userflag.b.h = 8;
      pNewActwk->xposi.w.h = pActwk->xposi.w.h;
      ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
      pNewActwk->yposi.w.h = pActwk->yposi.w.h + 160;
      pNewActwk->actfree[16] = pActwk->actfree[16];
      pNewActwk->actfree[19] = pActwk->actfree[19];
      if (pActwk->actfree[19] == 0)
      {
        d1 = 1;
        for (i = 0; i <= 1; ++i)
        {
          if (actwkchk(&pNewActwk) == 0)
          {
            pNewActwk->actno = 35;
            pNewActwk->userflag.b.h = 8;
            pNewActwk->actfree[19] = d1;
            pNewActwk->actfree[16] = 128;
            d0 = -64;
            if (d1 != 1) d0 *= -1;
            pNewActwk->xposi.w.h = pActwk->xposi.w.h + d0;
            pNewActwk->yposi.w.h = pActwk->yposi.w.h;
            ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
          }
          ++d1;
        }
      }
    }
  }

  type8_move(pActwk);
}




static void type8_move(sprite_status* pActwk) {
  short_union tmp;
  short stk;
  short d0, d1;

  stk = pActwk->yposi.w.h;
  sinset(pActwk->actfree[16], &d0, &d1);
  d0 = d0 * 2 >> 4;

  tmp.b.h = pActwk->actfree[16];
  tmp.b.l = pActwk->actfree[17];
  tmp.w += 128;
  pActwk->actfree[16] = tmp.b.h;
  pActwk->actfree[17] = tmp.b.l;

  pActwk->yposi.w.h = ((short*)pActwk)[27] + d0;
  d0 -= stk;
  d0 <<= 8;
  pActwk->yspeed.w = d0;
  ride_on_chk(pActwk, &actwk[0]);
}




static void udblk4_type9(sprite_status* pActwk) {
  short d0;
  void(*tbl[2])(sprite_status*) =
  {
    &type9_init,
    &type9_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);

  d0 = ((short*)pActwk)[28];
  if (d0)
  {
    if (actwk[d0].actno == 0)
    {
      frameout_s0(pActwk);
    }
  }
  else
  {
    frameout_s00(pActwk, ((short*)pActwk)[29]);
  }
}




static void type9_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  short d1;
  unsigned char d0;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = udblk4pat9s[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  ((short*)pActwk)[29] = pActwk->xposi.w.h;
  ((short*)pActwk)[27] = pActwk->yposi.w.h;
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 32;

  if (pActwk->actfree[18] == 0)
  {
    if (actwkchk(&pNewActwk) == 0)
    {
      pNewActwk->actno = 35;
      pNewActwk->actfree[18] = 1;
      pNewActwk->userflag.b.h = 9;
      pNewActwk->xposi.w.h = pActwk->xposi.w.h;
      d1 = 128;
      d0 = pActwk->actfree[16];
      if (pActwk->actfree[19] & 128)
      {
        d1 = 160;
        d0 -= 128;
      }
      pNewActwk->actfree[16] = d0;
      pNewActwk->yposi.w.h = pActwk->yposi.w.h + d1;
    }
  }
}




static void type9_move(sprite_status* pActwk) {
  sin_move(pActwk, 5, 0);
}




static void udblk4_typeA(sprite_status* pActwk) {
  short d0;
  void(*tbl[2])(sprite_status*) =
  {
    &typeA_init,
    &typeA_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);

  d0 = ((short*)pActwk)[28];
  if (d0)
  {
    if (actwk[d0].actno == 0)
    {
      frameout_s0(pActwk);
    }
  }
  else
  {
    frameout_s00(pActwk, ((short*)pActwk)[29]);
  }
}




static void typeA_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  short i;
  unsigned char d1;
  kakudo_xofst tbl[7] =
  {
    {   0,   0 },
    { 224, -32 },
    { 192, -64 },
    { 160, -96 },
    { 224,  32 },
    { 192,  64 },
    { 160,  96 }
  };

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = udblk4patAs[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  ((short*)pActwk)[27] = pActwk->yposi.w.h;
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 16;

  if (pActwk->actfree[18] == 0)
  {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    d1 = 1;
    for (i = 0; i <= 5; ++i)
    {
      if (actwkchk(&pNewActwk) == 0)
      {
        pNewActwk->actno = 35;
        pNewActwk->userflag.b.h = 10;
        pNewActwk->yposi.w.h = pActwk->yposi.w.h;
        ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
        pNewActwk->actfree[18] = d1;
        pNewActwk->actfree[16] = tbl[d1].kakudo;

        pNewActwk->xposi.w.h = pActwk->xposi.w.h + (short)tbl[d1].xofst;
      }
      ++d1;
    }
  }
  typeA_move(pActwk);
}




static void typeA_move(sprite_status* pActwk) {
  sin_move(pActwk, 5, 4);
}




static void udblk4_typeB(sprite_status* pActwk) {
  short d0;
  void(*tbl[2])(sprite_status*) =
  {
    &typeB_init,
    &typeB_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);

  d0 = ((short*)pActwk)[28];
  if (d0)
  {
    if (actwk[d0].actno == 0)
    {
      frameout_s0(pActwk);
    }
  }
  else
  {
    frameout_s00(pActwk, ((short*)pActwk)[29]);
  }
}




static void typeB_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  xofs_yofs_yspd* a1;
  short i;
  unsigned char d1;
  xofs_yofs_yspd tbl[6] =
  {
    {    0,    0,  128 },
    {    0, -128,  128 },
    {  -80,   32, -256 },
    {  -80,  -96, -256 },
    {   80,   32, -256 },
    {   80,  -96, -256 }
  };









  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = udblk4pat9s[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 32;
  pActwk->patno = 0;

  if (pActwk->actfree[18] == 0)
  {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    ((short*)pActwk)[27] = pActwk->yposi.w.h;
    d1 = 1;
    for (i = 0; i <= 4; ++i)
    {
      if (actwkchk(&pNewActwk) == 0)
      {
        pNewActwk->actno = 35;
        pNewActwk->userflag.b.h = 11;
        pNewActwk->actfree[18] = d1;
        ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
        ((short*)pNewActwk)[27] = ((short*)pActwk)[27];
      }
      ++d1;
    }
  }
  a1 = &tbl[pActwk->actfree[18]];
  pActwk->xposi.w.h = ((short*)pActwk)[29] + (short)a1->xofs;
  pActwk->yposi.w.h = ((short*)pActwk)[27] + (short)a1->yofs;
  pActwk->yspeed.w += a1->yspd;
}




static void typeB_move(sprite_status* pActwk) {
  short d0;

  pActwk->yposi.l = pActwk->yposi.l + (pActwk->yspeed.w << 8);


  if (pActwk->yspeed.w < 0)
  {
    d0 = ((short*)pActwk)[27];
    if (d0 < pActwk->yposi.w.h) return;
    d0 -= pActwk->yposi.w.h;
    if (d0 < 128) return;
    pActwk->yposi.w.h = ((short*)pActwk)[27] + 128;
  }
  else
  {
    d0 = pActwk->xposi.w.h;
    if (d0 < ((short*)pActwk)[27]) return;
    d0 -= ((short*)pActwk)[27];
    if (d0 < 128) return;
    pActwk->yposi.w.h = ((short*)pActwk)[27] - 128;
  }
}
