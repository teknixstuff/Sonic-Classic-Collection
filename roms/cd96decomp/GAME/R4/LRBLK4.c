#include "../EQU.h"
#include "LRBLK4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../RIDECHK.h"

typedef struct {
  unsigned char cnt;
  unsigned char dummy;
  short speed;
}
move_data;

static void lrblk4_foutchk(sprite_status* pActwk);
static void lrblk4_type1(sprite_status* pActwk);
static void type1_init(sprite_status* pActwk);
static void type1_move(sprite_status* pActwk);
static void lrblk4_type2(sprite_status* pActwk);
static void type2_init(sprite_status* pActwk);
static void type2_move(sprite_status* pActwk);
static void lrblk4_type3(sprite_status* pActwk);
static void type3_init(sprite_status* pActwk);
static void type3_move(sprite_status* pActwk);
static void lrblk4_type4(sprite_status* pActwk);
static void type4_init(sprite_status* pActwk);
static void type4_move(sprite_status* pActwk);
static void lrblk4_type5(sprite_status* pActwk);
static void type5_init(sprite_status* pActwk);
static void type5_move(sprite_status* pActwk);
static void type5_end(sprite_status* pActwk);
static void lrblk4_type6(sprite_status* pActwk);
static void type6_init(sprite_status* pActwk);
static void type6_move(sprite_status* pActwk);
static void lrblk4_type8(sprite_status* pActwk);
static void type8_init(sprite_status* pActwk);
static void type8_move(sprite_status* pActwk);

static sprite_pattern z41bpat10 = { 1, { { -64, -16, 0, 497 } } };
static sprite_pattern z41cpat10 = { 1, { { -64, -16, 0, 485 } } };
static sprite_pattern z42apat10 = { 1, { { -64, -16, 0, 504 } } };
static sprite_pattern z42bpat10 = { 1, { { -64, -16, 0, 519 } } };
static sprite_pattern z42cpat10 = { 1, { { -64, -16, 0, 491 } } };
static sprite_pattern z41bpat11 = { 1, { { -48, -16, 0, 498 } } };
static sprite_pattern z41cpat11 = { 1, { { -48, -16, 0, 486 } } };
static sprite_pattern z42apat11 = { 1, { { -48, -16, 0, 505 } } };
static sprite_pattern z42bpat11 = { 1, { { -48, -16, 0, 520 } } };
static sprite_pattern z42cpat11 = { 1, { { -48, -16, 0, 492 } } };
static sprite_pattern z41bpat20 = { 1, { { -32, -16, 0, 499 } } };
static sprite_pattern z41cpat20 = { 1, { { -32, -16, 0, 487 } } };
static sprite_pattern z42apat20 = { 1, { { -32, -16, 0, 506 } } };
static sprite_pattern z42bpat20 = { 1, { { -32, -16, 0, 521 } } };
static sprite_pattern z42cpat20 = { 1, { { -32, -16, 0, 493 } } };
static sprite_pattern z41bpat30 = { 1, { { -32, -32, 0, 500 } } };
static sprite_pattern z41cpat30 = { 1, { { -32, -32, 0, 488 } } };
static sprite_pattern z42apat30 = { 1, { { -32, -32, 0, 507 } } };
static sprite_pattern z42bpat30 = { 1, { { -32, -32, 0, 522 } } };
static sprite_pattern z42cpat30 = { 1, { { -32, -32, 0, 494 } } };
static sprite_pattern z41bpat50 = { 1, { { -32, -32, 0, 501 } } };
static sprite_pattern z41cpat50 = { 1, { { -32, -32, 0, 489 } } };
static sprite_pattern z42apat50 = { 1, { { -32, -32, 0, 508 } } };
static sprite_pattern z42bpat50 = { 1, { { -32, -32, 0, 523 } } };
static sprite_pattern z42cpat50 = { 1, { { -32, -32, 0, 495 } } };
static sprite_pattern z41bpat60 = { 1, { { -16, -16, 0, 502 } } };
static sprite_pattern z41cpat60 = { 1, { { -16, -16, 0, 490 } } };
static sprite_pattern z42apat60 = { 1, { { -16, -16, 0, 509 } } };
static sprite_pattern z42bpat60 = { 1, { { -16, -16, 0, 524 } } };
static sprite_pattern z42cpat60 = { 1, { { -16, -16, 0, 496 } } };
static sprite_pattern z41bpat61 = { 1, { { -32, -16, 0, 503 } } };
static sprite_pattern z41cpat61 = { 1, { { -32, -16, 0, 491 } } };
static sprite_pattern z42apat61 = { 1, { { -32, -16, 0, 510 } } };
static sprite_pattern z42bpat61 = { 1, { { -32, -16, 0, 525 } } };
static sprite_pattern z42cpat61 = { 1, { { -32, -16, 0, 497 } } };
static sprite_pattern z41bpat62 = { 1, { { -48, -16, 0, 504 } } };
static sprite_pattern z41cpat62 = { 1, { { -48, -16, 0, 492 } } };
static sprite_pattern z42apat62 = { 1, { { -48, -16, 0, 511 } } };
static sprite_pattern z42bpat62 = { 1, { { -48, -16, 0, 526 } } };
static sprite_pattern z42cpat62 = { 1, { { -48, -16, 0, 498 } } };
static sprite_pattern z41bpat63 = { 1, { { -64, -16, 0, 505 } } };
static sprite_pattern z41cpat63 = { 1, { { -64, -16, 0, 493 } } };
static sprite_pattern z42apat63 = { 1, { { -64, -16, 0, 512 } } };
static sprite_pattern z42bpat63 = { 1, { { -64, -16, 0, 527 } } };
static sprite_pattern z42cpat63 = { 1, { { -64, -16, 0, 499 } } };
sprite_pattern* z41blrblk4pat1[2] =
{
  &z41bpat10,
  &z41bpat11
};
sprite_pattern* z41clrblk4pat1[2] =
{
  &z41cpat10,
  &z41cpat11
};
sprite_pattern* z42alrblk4pat1[2] =
{
  &z42apat10,
  &z42apat11
};
sprite_pattern* z42blrblk4pat1[2] =
{
  &z42bpat10,
  &z42bpat11
};
sprite_pattern* z42clrblk4pat1[2] =
{
  &z42cpat10,
  &z42cpat11
};
sprite_pattern** lrblk4pat1s[2][3] =
{
  { z41blrblk4pat1, z41blrblk4pat1, z41clrblk4pat1 },
  { z42blrblk4pat1, z42alrblk4pat1, z42clrblk4pat1 }
};
sprite_pattern* z41blrblk4pat2[1] = { &z41bpat20 };
sprite_pattern* z41clrblk4pat2[1] = { &z41cpat20 };
sprite_pattern* z42alrblk4pat2[1] = { &z42apat20 };
sprite_pattern* z42blrblk4pat2[1] = { &z42bpat20 };
sprite_pattern* z42clrblk4pat2[1] = { &z42cpat20 };
sprite_pattern** lrblk4pat2s[2][3] =
{
  { z41blrblk4pat2, z41blrblk4pat2, z41clrblk4pat2 },
  { z42blrblk4pat2, z42alrblk4pat2, z42clrblk4pat2 }
};
sprite_pattern* z41blrblk4pat3[1] = { &z41bpat30 };
sprite_pattern* z41clrblk4pat3[1] = { &z41cpat30 };
sprite_pattern* z42alrblk4pat3[1] = { &z42apat30 };
sprite_pattern* z42blrblk4pat3[1] = { &z42bpat30 };
sprite_pattern* z42clrblk4pat3[1] = { &z42cpat30 };
sprite_pattern** lrblk4pat3s[2][3] =
{
  { z41blrblk4pat3, z41blrblk4pat3, z41clrblk4pat3 },
  { z42blrblk4pat3, z42alrblk4pat3, z42clrblk4pat3 }
};
sprite_pattern* z41blrblk4pat5[1] = { &z41bpat50 };
sprite_pattern* z41clrblk4pat5[1] = { &z41cpat50 };
sprite_pattern* z42alrblk4pat5[1] = { &z42apat50 };
sprite_pattern* z42blrblk4pat5[1] = { &z42bpat50 };
sprite_pattern* z42clrblk4pat5[1] = { &z42cpat50 };
sprite_pattern** lrblk4pat5s[2][3] =
{
  { z41blrblk4pat5, z41blrblk4pat5, z41clrblk4pat5 },
  { z42blrblk4pat5, z42alrblk4pat5, z42clrblk4pat5 }
};
sprite_pattern* z41blrblk4pat6[4] =
{
  &z41bpat60,
  &z41bpat61,
  &z41bpat62,
  &z41bpat63
};
sprite_pattern* z41clrblk4pat6[4] =
{
  &z41cpat60,
  &z41cpat61,
  &z41cpat62,
  &z41cpat63
};
sprite_pattern* z42alrblk4pat6[4] =
{
  &z42apat60,
  &z42apat61,
  &z42apat62,
  &z42apat63
};
sprite_pattern* z42blrblk4pat6[4] =
{
  &z42bpat60,
  &z42bpat61,
  &z42bpat62,
  &z42bpat63
};
sprite_pattern* z42clrblk4pat6[4] =
{
  &z42cpat60,
  &z42cpat61,
  &z42cpat62,
  &z42cpat63
};
sprite_pattern** lrblk4pat6s[2][3] =
{
  { z41blrblk4pat6, z41blrblk4pat6, z41clrblk4pat6 },
  { z42blrblk4pat6, z42alrblk4pat6, z42clrblk4pat6 }
};
sprite_pattern* z41blrblk4pat8[2] =
{
  &z41bpat10,
  &z41bpat11
};
sprite_pattern* z41clrblk4pat8[2] =
{
  &z41cpat10,
  &z41cpat11
};
sprite_pattern* z42alrblk4pat8[2] =
{
  &z42apat10,
  &z42apat11
};
sprite_pattern* z42blrblk4pat8[2] =
{
  &z42bpat10,
  &z42bpat11
};
sprite_pattern* z42clrblk4pat8[2] =
{
  &z42cpat10,
  &z42cpat11
};
sprite_pattern** lrblk4pat8s[2][3] =
{
  { z41blrblk4pat8, z41blrblk4pat8, z41clrblk4pat8 },
  { z42blrblk4pat8, z42alrblk4pat8, z42clrblk4pat8 }
};


void lrblk4(sprite_status* pActwk) {
  void(*tbl[9])(sprite_status*) =
  {
    &lrblk4_type1,
    &lrblk4_type1,
    &lrblk4_type2,
    &lrblk4_type3,
    &lrblk4_type4,
    &lrblk4_type5,
    &lrblk4_type6,
    &lrblk4_type1,
    &lrblk4_type8
  };









  tbl[pActwk->userflag.b.h](pActwk);
}




static void lrblk4_foutchk(sprite_status* pActwk) {
  short d0, d1;

  d0 = ((short*)pActwk)[29];
  d0 &= -128;
  d1 = scra_h_posit.w.h;
  d1 -= 128;
  d1 &= -128;
  d0 -= d1;
  if ((unsigned short)d0 > 640)
  {
    d0 = (unsigned short)pActwk->cdsts;
    if (d0)
    {
      d0 *= 3;
      d0 += (unsigned short)time_flag;
      flagwork[d0] &= 127;
    }
    frameout(pActwk);
  }
}




static void lrblk4_type1(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type1_init,
    &type1_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  lrblk4_foutchk(pActwk);
}




static void type1_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  short i;
  unsigned short d0;
  unsigned char d1;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = lrblk4pat1s[stageno_i.b.l][time_flag_i & 0x7F];
  ((short*)pActwk)[27] = pActwk->xposi.w.h;
  pActwk->sprhsize = 48;
  pActwk->sprvsize = 16;
  pActwk->patno = 1;

  if (pActwk->actfree[18])
  {
    type1_move(pActwk);
    return;
  }

  ((short*)pActwk)[29] = pActwk->xposi.w.h;
  if (pActwk->actfree[19] == 0)
  {
    d1 = 1;
    for (i = 0; i <= 4; ++i)
    {
      if (actwkchk(&pNewActwk) == 0)
      {
        pNewActwk->actno = 36;
        pNewActwk->userflag.b.h = 1;
        pNewActwk->actfree[19] = d1;
        pNewActwk->xposi.w.h = pActwk->xposi.w.h;

        pNewActwk->actfree[16] = (char)(d1 * 32) + 16;
        d0 = d1;
        d0 *= 96;
        d0 += pActwk->yposi.w.h;
        pNewActwk->yposi.w.h = d0;
      }

      ++d1;
    }
  }
  if (actwkchk(&pNewActwk) == 0)
  {
    pNewActwk->actno = 36;
    pNewActwk->userflag.b.h = 1;
    pNewActwk->actfree[18] = 1;

    ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
    pNewActwk->yposi.w.h = pActwk->yposi.w.h;
    pNewActwk->xposi.w.h = pActwk->xposi.w.h + 224;
    pNewActwk->actfree[16] = pActwk->actfree[16];
  }
  type1_move(pActwk);
}




static void type1_move(sprite_status* pActwk) {
  short d0, d1, stk;

  stk = pActwk->xposi.w.h;
  sinset(pActwk->actfree[16], &d0, &d1);
  d0 >>= 3;
  ++pActwk->actfree[16];
  d0 += ((short*)pActwk)[27];
  pActwk->xposi.w.h = d0;
  d1 = stk;
  d0 -= d1;
  d0 <<= 8;
  pActwk->xspeed.w = d0;
  hitchk(pActwk, &actwk[0]);
}




static void lrblk4_type2(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type2_init,
    &type2_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  lrblk4_foutchk(pActwk);
}




static void type2_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = lrblk4pat2s[stageno_i.b.l][time_flag_i & 0x7F];
  pActwk->sprhsize = 32;
  pActwk->sprvsize = 16;

  if (pActwk->actfree[18])
  {
    type2_move(pActwk);
    return;
  }

  ((short*)pActwk)[29] = pActwk->xposi.w.h;

  ((short*)pActwk)[27] = pActwk->xposi.w.h - 32;

  if (actwkchk(&pNewActwk) == 0)
  {
    pNewActwk->actno = 36;
    pNewActwk->userflag.b.h = 2;
    pNewActwk->actfree[18] = 1;

    ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
    pNewActwk->yposi.w.h = pActwk->yposi.w.h;
    pNewActwk->xposi.w.h = pActwk->xposi.w.h + 64;
    ((short*)pNewActwk)[27] = pNewActwk->xposi.w.h + 32;
    pNewActwk->actfree[16] = pActwk->actfree[16] - 128;
  }
  type2_move(pActwk);
}




static void type2_move(sprite_status* pActwk) {
  short d0, d1, stk;

  stk = pActwk->xposi.w.h;
  sinset(pActwk->actfree[16], &d0, &d1);
  d0 >>= 3;
  ++pActwk->actfree[16];
  d0 += ((short*)pActwk)[27];
  pActwk->xposi.w.h = d0;
  d1 = stk;
  d0 -= d1;
  d0 <<= 8;
  pActwk->xspeed.w = d0;
  hitchk(pActwk, &actwk[0]);
}




static void lrblk4_type3(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type3_init,
    &type3_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  lrblk4_foutchk(pActwk);
}




static void type3_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  short* a2;
  short i;
  unsigned char d0, d1;
  short tbl[18] =
  {
       0,    0, -128,
    -144,    0, -128,
     144,    0, -128,
       0,   64,  128,
    -144,   64,  128,
     144,   64,  128
  };

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = lrblk4pat3s[stageno_i.b.l][time_flag_i & 0x7F];
  pActwk->sprhsize = 32;
  pActwk->sprvsize = 32;

  if (pActwk->actfree[18] == 0)
  {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    d1 = 1;
    for (i = 0; i <= 4; ++i)
    {
      if (actwkchk(&pNewActwk) == 0)
      {
        pNewActwk->actno = 36;
        pNewActwk->userflag.b.h = 3;
        pNewActwk->actfree[18] = d1;
        ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
        pNewActwk->xposi.w.h = pActwk->xposi.w.h;
        pNewActwk->yposi.w.h = pActwk->yposi.w.h;
      }
      ++d1;
    }
  }
  d0 = pActwk->actfree[18] * 6;
  a2 = &tbl[d0 / 2];
  pActwk->xposi.w.h += *a2++;
  pActwk->yposi.w.h += *a2++;
  pActwk->xspeed.w = *a2++;
}




static void type3_move(sprite_status* pActwk) {
  sprite_status* pPlayerwk;
  int ld0;
  short d0;

  ld0 = pActwk->xspeed.w;
  ld0 <<= 8;
  pActwk->xposi.l += ld0;


  if (pActwk->xspeed.w < 0)
  {
    d0 = ((short*)pActwk)[29];
    if ((unsigned short)d0 >= (unsigned short)pActwk->xposi.w.h)
    {
      d0 -= pActwk->xposi.w.h;
      if ((unsigned short)d0 >= 224)
      {
        d0 = ((short*)pActwk)[29];
        d0 += 224;
        pActwk->xposi.w.h = d0;
      }
    }
  }
  else
  {
    d0 = pActwk->xposi.w.h;
    if ((unsigned short)d0 >= (unsigned short)((short*)pActwk)[29])
    {
      d0 -= ((short*)pActwk)[29];
      if ((unsigned short)d0 >= 224)
      {
        d0 = ((short*)pActwk)[29];
        d0 -= 224;
        pActwk->xposi.w.h = d0;
      }
    }
  }

  if (pActwk->actflg & 128)
  {
    pPlayerwk = &actwk[0];
    d0 = pPlayerwk->yposi.w.h;
    if ((unsigned short)d0 < (unsigned short)pActwk->yposi.w.h)
    {
      d0 -= pActwk->yposi.w.h;
      d0 *= -1;
    }
    else
    {
      d0 -= pActwk->yposi.w.h;
    }
    if ((unsigned short)d0 < 64)
    {
      hitchk(pActwk, pPlayerwk);
    }
  }
}




static void lrblk4_type4(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type4_init,
    &type4_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  lrblk4_foutchk(pActwk);
}




static void type4_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;

  pActwk->sprhsize = 64;
  pActwk->sprvsize = 64;
  if (pActwk->actfree[19])
  {
    pActwk->patbase = lrblk4pat8s[stageno_i.b.l][time_flag_i & 0x7F];
    pActwk->sprvsize = 16;
  }

  if (pActwk->actfree[18] == 0)
  {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    if (actwkchk(&pNewActwk) == 0)
    {
      pNewActwk->actno = 36;
      pNewActwk->userflag.b.h = 4;
      pNewActwk->actfree[18] = 1;
      pNewActwk->actfree[19] = pActwk->actfree[19];
      ((short*)pNewActwk)[29] = ((short*)pActwk)[29];

      pNewActwk->xposi.w.h = ((short*)pActwk)[29] + 128;
      pNewActwk->yposi.w.h = pActwk->yposi.w.h;

      pActwk->xposi.w.h = ((short*)pActwk)[29] - 128;
    }
  }
  pActwk->xspeed.w = -512;
}




static void type4_move(sprite_status* pActwk) {
  short d0;

  pActwk->xposi.l += pActwk->xspeed.w << 8;
  hitchk(pActwk, &actwk[0]);
  d0 = ((short*)pActwk)[29];
  if (d0 >= pActwk->xposi.w.h)
  {
    d0 -= pActwk->xposi.w.h;
    if (d0 == 256)
    {
      pActwk->xposi.w.h = ((short*)pActwk)[29] + 256;
    }
  }
}




static void lrblk4_type5(sprite_status* pActwk) {
  void(*tbl[3])(sprite_status*) =
  {
    &type5_init,
    &type5_move,
    &type5_end
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  lrblk4_foutchk(pActwk);
}




static void type5_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  unsigned char* a1;
  short i;
  unsigned short d0;
  unsigned char d1;
  unsigned char tbl[14] =
  {
      0,   0,
     64,   1,
    128,   2,
    192,   3,
    128,   4,
     64,   5,
      0,   0
  };

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = lrblk4pat5s[stageno_i.b.l][time_flag_i & 0x7F];
  ((short*)pActwk)[29] = pActwk->xposi.w.h;
  pActwk->sprhsize = 32;
  pActwk->sprvsize = 32;

  if (pActwk->actfree[18] == 0)
  {
    d1 = 1;
    for (i = 0; i <= 3; ++i)
    {
      if (actwkchk(&pNewActwk) == 0)
      {
        pNewActwk->actno = 36;
        pNewActwk->userflag.b.h = 5;
        pNewActwk->actfree[18] = d1;
        pNewActwk->xposi.w.h = pActwk->xposi.w.h;
        d0 = d1;
        d0 *= 64;
        pNewActwk->yposi.w.h = pActwk->yposi.w.h + (short)d0;
      }
      ++d1;
    }
  }
  a1 = &tbl[pActwk->actfree[18] * 2];
  pActwk->xposi.w.h += (unsigned short)*a1++;
  pActwk->actfree[17] = *a1++;
}




static void type5_move(sprite_status* pActwk) {
  move_data* a1;
  short d0;







  move_data type5_mvtbl[6] =
  {
    { 128, 0,  128 },
    { 128, 0,  128 },
    { 128, 0,  128 },
    { 128, 0, -128 },
    { 128, 0, -128 },
    { 128, 0, -128 }
  };







label1:
  if (pActwk->actfree[16] == 0)
  {
    a1 = &type5_mvtbl[pActwk->actfree[17]];
    pActwk->actfree[16] = a1->cnt;
    ((short*)pActwk)[26] = a1->speed;
  }
  else
  {
    d0 = ((short*)pActwk)[26];
    pActwk->xspeed.w = d0;
    pActwk->xposi.l += d0 << 8;
    --pActwk->actfree[16];
    if (pActwk->actfree[16] == 0)
    {
      ++pActwk->actfree[17];
      if (pActwk->actfree[17] != 6) goto label1;



      pActwk->actfree[17] = 0;
      goto label1;
    }
  }
  type5_end(pActwk);
}




static void type5_end(sprite_status* pActwk) {
  hitchk(pActwk, &actwk[0]);
}




static void lrblk4_type6(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type6_init,
    &type6_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  lrblk4_foutchk(pActwk);
}




static void type6_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  uint_union dw;
  short i;
  short d0;
  unsigned char bd0;
  unsigned char d1;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = lrblk4pat6s[stageno_i.b.l][time_flag_i & 0x7F];
  pActwk->sprvsize = 16;

  if (pActwk->actfree[18] == 0)
  {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    d1 = 1;
    for (i = 0; i <= 2; ++i)
    {
      if (actwkchk(&pNewActwk) == 0)
      {
        pNewActwk->actno = 36;
        pNewActwk->userflag.b.h = 6;
        pNewActwk->actfree[18] = d1;
        ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
        d0 = (char)d1 * 16;
        d0 *= -1;
        d0 += pActwk->xposi.w.h;
        pNewActwk->xposi.w.h = d0;
        dw.l = d1;
        dw.l <<= 5;
        d0 = dw.w.l;
        d0 += pActwk->yposi.w.h;
        pNewActwk->yposi.w.h = d0;
      }
      ++d1;
    }
  }
  bd0 = pActwk->actfree[18];
  pActwk->patno = bd0;
  ++bd0;
  pActwk->actfree[17] = bd0;
  bd0 = pActwk->actfree[18];
  d1 = 0;
  for (i = 0; i <= (short)(unsigned short)bd0; ++i)
  {
    d1 += 16;
  }
  pActwk->sprhsize = d1;
  d0 = pActwk->xposi.w.h;
  d0 += (unsigned short)d1;
  ((short*)pActwk)[27] = d0;
  pActwk->actfree[16] = 128;

  type6_move(pActwk);
}




static void type6_move(sprite_status* pActwk) {
  short d0, d1, d3, stk;
  unsigned char d2;

  stk = pActwk->xposi.w.h;
  sinset(pActwk->actfree[16], &d0, &d1);

  d3 = 0;
  d2 = pActwk->actfree[17];
  if (d2)
  {
    do
    {
      d3 += d0;
      --d2;
    } while (d2 != 0);
  }

  d3 >>= 4;
  d0 = d3;
  d0 += ((short*)pActwk)[27];
  pActwk->xposi.w.h = d0;

  d1 = stk;
  d0 -= d1;
  d0 <<= 8;
  pActwk->xspeed.w = d0;
  ++pActwk->actfree[16];
  hitchk(pActwk, &actwk[0]);
}




static void lrblk4_type8(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &type8_init,
    &type8_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  lrblk4_foutchk(pActwk);
}




static void type8_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  short d0;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = lrblk4pat8s[stageno_i.b.l][time_flag_i & 0x7F];
  pActwk->sprhsize = 64;
  pActwk->sprvsize = 16;

  if (pActwk->actfree[18] == 0)
  {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    if (actwkchk(&pNewActwk) == 0)
    {
      pNewActwk->actno = 36;
      pNewActwk->userflag.b.h = 4;
      pNewActwk->actfree[19] = 8;
      pNewActwk->xposi.w.h = pActwk->xposi.w.h;
      pNewActwk->yposi.w.h = pActwk->yposi.w.h - 96;
    }
    if (actwkchk(&pNewActwk) == 0)
    {
      pNewActwk->actno = 36;
      pNewActwk->userflag.b.h = 8;
      pNewActwk->actfree[18] = 1;
      ((short*)pNewActwk)[29] = ((short*)pActwk)[29];
      d0 = ((short*)pActwk)[29];
      d0 -= 128;
      pNewActwk->xposi.w.h = d0;
      pNewActwk->yposi.w.h = pActwk->yposi.w.h;
      d0 = ((short*)pActwk)[29];
      d0 += 128;
      pActwk->xposi.w.h = d0;
    }
  }
  pActwk->xspeed.w = 512;
}




static void type8_move(sprite_status* pActwk) {
  short d0;

  pActwk->xposi.l += pActwk->xspeed.w << 8;
  hitchk(pActwk, &actwk[0]);
  d0 = pActwk->xposi.w.h;
  if (d0 >= ((short*)pActwk)[29])
  {
    d0 -= ((short*)pActwk)[29];
    if (d0 == 256)
    {
      pActwk->xposi.w.h = ((short*)pActwk)[29] - 256;
    }
  }
}
