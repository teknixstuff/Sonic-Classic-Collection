#include "../EQU.h"
#include "DAI_RD5.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../ETC.h"
#include "../RIDECHK.h"

static void dair5_init(sprite_status* pActwk);
static void dair5_move(sprite_status* pActwk);
static void type01(sprite_status* pActwk);
static void type02(sprite_status* pActwk);
static void type03(sprite_status* pActwk);
static void type04(sprite_status* pActwk);
static void type05(sprite_status* pActwk);
static void type06(sprite_status* pActwk);
static void type06_00(sprite_status* pActwk);
static void type06_01(sprite_status* pActwk);
static void type06_02(sprite_status* pActwk);
static void dodai_sub(sprite_status* pActwk, unsigned char d4);
static void dai5sub(sprite_status* pActwk);
static void banesetsub(sprite_status* pActwk, char d2);
static void belttask(sprite_status* pActwk);

static sprite_pattern z5pat00 = { 1, { { -16, -16, 0, 468 } } };
static sprite_pattern z53pat00 = { 1, { { -16, -16, 0, 413 } } };
static sprite_pattern z5pat01 = { 2, { { -16, -16, 0, 469 }, { -16, -16, 0, 470 } } };
static sprite_pattern z53pat01 = { 2, { { -16, -16, 0, 414 }, { -16, -16, 0, 415 } } };
static sprite_pattern z5pat02 = { 1, { { -32, -16, 0, 471 } } };
static sprite_pattern z53pat02 = { 1, { { -32, -16, 0, 416 } } };
static sprite_pattern z5pat03 = { 2, { { -32, -16, 0, 472 }, { -32, -16, 0, 473 } } };
static sprite_pattern z53pat03 = { 2, { { -32, -16, 0, 417 }, { -32, -16, 0, 418 } } };
static sprite_pattern z5pat04 = { 1, { { -48, -16, 0, 474 } } };
static sprite_pattern z53pat04 = { 1, { { -48, -16, 0, 419 } } };
static sprite_pattern z5pat05 = { 2, { { -48, -16, 0, 475 }, { -48, -16, 0, 476 } } };
static sprite_pattern z53pat05 = { 2, { { -48, -16, 0, 420 }, { -48, -16, 0, 421 } } };
sprite_pattern* z5dair5pat[6] =
{
  &z5pat00,
  &z5pat01,
  &z5pat02,
  &z5pat03,
  &z5pat04,
  &z5pat05
};
sprite_pattern* z53dair5pat[6] =
{
  &z53pat00,
  &z53pat01,
  &z53pat02,
  &z53pat03,
  &z53pat04,
  &z53pat05
};
sprite_pattern** dair5pats[3] =
{
  z5dair5pat,
  z5dair5pat,
  z53dair5pat
};



























































void dair5(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &dair5_init,
    &dair5_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}




static void dair5_init(sprite_status* pActwk) {
  unsigned char* a2;
  short d0;
  unsigned char bd0;
  unsigned char bd1;
  unsigned char ini_tbl[50] =
  {
    0, 16,
    1, 16,
    0, 16,
    0, 16,
    1, 16,
    0, 16,
    0, 16,
    2, 32,
    2, 32,
    3, 32,
    2, 32,
    3, 32,
    2, 32,
    3, 32,
    2, 32,
    2, 32,
    2, 32,
    4, 48,
    5, 48,
    4, 48,
    4, 48,
    5, 48,
    4, 48,
    4, 48,
    4, 48
  };



  unsigned char belt_flag[50] =
  {
      0,   1,   0,   0,   1,   0,   0,   0,   0,   1,
      0,   1,   0,   1,   0,   0,   0,   0,   1,   0,
      0,   1,   0,   0,   0,   0, 192, 192, 192, 192,
      0,   0,   0,  64,  64, 192, 192, 192, 192, 192,
      0,   0,   0,   0, 192, 192, 192, 192,   0,   0
  };



  unsigned char bane_flag[25] =
  {
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 3, 0, 0
  };

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;

  d0 = 17156;
  if (stageno.b.l == 2)
  {
    d0 = 17272;
  }
  pActwk->sproffset = d0;

  pActwk->patbase = dair5pats[stageno_i.b.l];
  ((short*)pActwk)[29] = pActwk->xposi.w.h;
  ((short*)pActwk)[27] = pActwk->yposi.w.h;
  pActwk->sprvsize = 16;
  bd0 = 0;
  bd1 = 0;

  bd0 = pActwk->userflag.b.h;
  bd0 &= 31;
  bd1 = bd0;
  bd1 = bd1 + bd1;
  a2 = &ini_tbl[bd1];
  pActwk->patno = *a2++;
  pActwk->sprhsize = *a2++;

  a2 = &belt_flag[bd0];
  pActwk->actfree[21] = *a2;

  a2 = &bane_flag[bd0];
  bd1 = *a2;
  switch (bd1) {


    case 0:
      break;


    case 1:
      banesetsub(pActwk, 0);
      break;


    case 2:
      banesetsub(pActwk, -16);
      banesetsub(pActwk, 16);
      break;


    case 3:
      banesetsub(pActwk, -32);
      banesetsub(pActwk, 0);
      banesetsub(pActwk, 32);
      break;
  }





  dair5_move(pActwk);
}




static void dair5_move(sprite_status* pActwk) {
  void(*tbl[25])(sprite_status*) =
  {
    &type01,
    &type02,
    &type02,
    &type03,
    &type03,
    &type06,
    &type05,
    &type01,
    &type04,
    &type04,
    &type03,
    &type03,
    &type02,
    &type02,
    &type02,
    &type06,
    &type05,
    &type01,
    &type01,
    &type03,
    &type02,
    &type02,
    &type02,
    &type06,
    &type05,
  };



  tbl[pActwk->userflag.b.h & 31](pActwk);
  dai5sub(pActwk);
  belttask(pActwk);
  ridechk(pActwk, &actwk[0]);
}





static void type01(sprite_status* pActwk) {
  pActwk->actfree[21] |= 128;
}




static void type02(sprite_status* pActwk) {
  short d0;

  pActwk->actfree[21] |= 128;
  ((short*)pActwk)[26] = 4;
  dodai_sub(pActwk, 48);

  d0 = ((short*)pActwk)[25];
  if (pActwk->userflag.b.h & 128)
  {
    d0 *= -1;
  }
  pActwk->xspeed.w = d0;
  pActwk->xposi.l += d0 << 8;
}




static void type03(sprite_status* pActwk) {
  int ld0;
  short d0;

  ((short*)pActwk)[26] = 4;
  dodai_sub(pActwk, 48);
  d0 = ((short*)pActwk)[25];
  if (pActwk->userflag.b.h & 128)
  {
    d0 *= -1;
  }
  ld0 = d0;
  ld0 <<= 8;
  pActwk->yposi.l += ld0;
}




static void type04(sprite_status* pActwk) {
  short d0;

  pActwk->actfree[21] |= 128;
  ((short*)pActwk)[26] = 4;
  dodai_sub(pActwk, 32);

  d0 = ((short*)pActwk)[25];
  if (pActwk->userflag.b.h & 128)
  {
    d0 *= -1;
  }
  pActwk->xspeed.w = d0;
  pActwk->xposi.l += d0 << 8;
}




static void type05(sprite_status* pActwk) {
  int ld0;
  short d0;

  if (pActwk->actfree[19] == 0)
  {
    pActwk->actfree[21] |= 128;
    if (pActwk->cddat & 8)
    {
      pActwk->actfree[17] = 30;
      pActwk->actfree[19] = 1;
    }
  }
  else
  {
    if (pActwk->actfree[17])
    {
      --pActwk->actfree[17];
      if (pActwk->actfree[17]) return;
      pActwk->actfree[21] &= 127;
    }
    pActwk->sprvsize = 16;
    if (pActwk->yspeed.w >= 512)
    {
      pActwk->sprvsize = 18;
      if (pActwk->yspeed.w >= 768)
      {
        pActwk->sprvsize = 20;
      }
    }
    d0 = pActwk->yspeed.w;
    if (d0 < 1024)
    {
      pActwk->yspeed.w += 32;
    }
    ld0 = pActwk->yspeed.w;
    ld0 <<= 8;
    pActwk->yposi.l += ld0;
    d0 = scra_v_posit.w.h;
    d0 += 224;
    if (d0 < pActwk->yposi.w.h)
    {
      ride_on_clr(pActwk, &actwk[0]);
      frameout(pActwk);
    }
  }
}




static void type06(sprite_status* pActwk) {
  void(*tbl[3])(sprite_status*) =
  {
    &type06_00,
    &type06_01,
    &type06_02
  };

  tbl[pActwk->actfree[19] / 2](pActwk);
}


static void type06_00(sprite_status* pActwk) {
  pActwk->actfree[21] |= 128;
  if (pActwk->cddat & 8)
  {
    pActwk->actfree[19] += 2;
    pActwk->actfree[17] = 30;
    type06_01(pActwk);
  }
}


static void type06_01(sprite_status* pActwk) {
  int stk;
  short d0, d1;

  if (pActwk->actfree[17])
  {
    --pActwk->actfree[17];
    if (pActwk->actfree[17]) return;
    pActwk->actfree[21] &= 127;
    pActwk->sprvsize = 14;
  }
  d0 = pActwk->yspeed.w;
  d0 -= 8;
  if (d0 < -768)
  {
    d0 = -768;
  }
  pActwk->yspeed.w = d0;
  speedset2(pActwk);
  stk = pActwk->yposi.l;
  pActwk->yposi.w.h -= 48;
  d1 = emycol_u(pActwk);
  pActwk->yposi.l = stk;
  if (d1 < 0)
  {
    pActwk->sprvsize = 16;
    pActwk->yspeed.w = 0;
    ((short*)pActwk)[27] = pActwk->yposi.w.h;
    pActwk->actfree[21] |= 128;
    pActwk->actfree[19] += 2;
  }
}


static void type06_02(sprite_status* pActwk) {

}




static void dodai_sub(sprite_status* pActwk, unsigned char d4) {
  short d0, d2;

  d2 = ((short*)pActwk)[26];
  if (pActwk->actfree[18] == 0)
  {
    d0 = ((short*)pActwk)[25];
    d0 += d2;
    ((short*)pActwk)[25] = d0;
    ((short*)pActwk)[24] += d0;
    if (d4 <= pActwk->actfree[3])
    {
      pActwk->actfree[18] = 255;
    }
  }
  else
  {
    d0 = ((short*)pActwk)[25];
    d0 -= d2;
    ((short*)pActwk)[25] = d0;
    ((short*)pActwk)[24] += d0;
    if (d4 > pActwk->actfree[3])
    {
      pActwk->actfree[18] = 0;
    }
  }
}




static void dai5sub(sprite_status* pActwk) {
  int_union ld0;
  short d0, d1;

  if (pActwk->actfree[21] & 128)
  {
    if (!(pActwk->cddat & 8))
    {
      if (pActwk->actfree[20] == 0) return;



      ((char*)pActwk)[66] -= 8;
    }
    else
    {
      if (pActwk->actfree[20] == 64) return;



      ((char*)pActwk)[66] += 8;
    }
    sinset(pActwk->actfree[20], &d0, &d1);
    d1 = 1024;
    ld0.l = d0 * d1;
    d0 = ld0.w.h;
    d0 += ((short*)pActwk)[27];
    pActwk->yposi.w.h = d0;
  }
}




static void banesetsub(sprite_status* pActwk, char d2) {
  sprite_status* pNewActwk;


  if (actwkchk2(pActwk, &pNewActwk) == 0)
  {
    pNewActwk->actno = 10;
    pNewActwk->yposi.w.h = pActwk->yposi.w.h;
    pNewActwk->xposi.w.h = pActwk->xposi.w.h;
    ((char*)pNewActwk)[60] = d2;
    ((char*)pNewActwk)[61] = -24;
    ((short*)pNewActwk)[28] = (unsigned short)(pActwk - actwk);
    pNewActwk->userflag.b.h = 2;
  }
}




static void belttask(sprite_status* pActwk) {
  sprite_status* pPlayerwk;
  int ld0;
  short d0;
  unsigned char bd1;

  if (!(pActwk->actfree[21] & 1)) return;
  if (!(pActwk->cddat & 8)) return;

  pPlayerwk = &actwk[0];

  if (pPlayerwk->actno == 0) return;

  if (!(pPlayerwk->cddat & 8)) return;
  d0 = (unsigned short)pPlayerwk->actfree[19];

  if (d0 != (short)(unsigned short)(pActwk - actwk)) return;

  bd1 = time_flag;
  ld0 = 32768;
  if (bd1)
  {
    ld0 = 65536;
    --bd1;
    if (bd1)
    {
      ld0 = 0x20000;
    }
  }
  if (colrevflag)
  {
    ld0 = -ld0;
  }
  pPlayerwk->xposi.l += ld0;
}
