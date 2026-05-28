#include "../EQU.h"
#include "SASORI.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void body_init(sprite_status* pActwk);
static void init_sub(sprite_status* pActwk0, sprite_status* pActwk1);
static void body_fall(sprite_status* pActwk);
static void body_move(sprite_status* pActwk);
static void body_waita(sprite_status* pActwk);
static void body_waita1(sprite_status* pActwk);
static void body_waitb(sprite_status* pActwk);
static void body_waitb1(sprite_status* pActwk);
static void body_waitc(sprite_status* pActwk);
static void body_waitc1(sprite_status* pActwk);
static void body_waitd(sprite_status* pActwk);
static void body_waitd1(sprite_status* pActwk);

static sprite_pattern pat00 =
{
  3,
  {
    { -21, -3, 0, 493 },
    { -24, -16, 0, 494 },
    { -32, -4, 0, 495 }
  }
};
static sprite_pattern pat01 =
{
  3,
  {
    { -25, -3, 0, 496 },
    { -24, -16, 0, 497 },
    { -28, -4, 0, 498 }
  }
};
static sprite_pattern pat02 =
{
  3,
  {
    { -23, -3, 0, 499 },
    { -24, -16, 0, 500 },
    { -31, -4, 0, 501 }
  }
};
static sprite_pattern pat03 =
{
  3,
  {
    { -24, -3, 0, 502 },
    { -24, -16, 0, 503 },
    { -30, -4, 0, 504 }
  }
};
static sprite_pattern pat04 =
{
  1,
  { { -12, -8, 0, 505 } }
};
static sprite_pattern pat05 =
{
  1,
  { { -8, -8, 0, 506 } }
};
static sprite_pattern pat06 =
{
  1,
  { { -8, -8, 0, 507 } }
};
static sprite_pattern pat07 =
{
  1,
  { { -8, -8, 0, 508 } }
};
sprite_pattern* pat_sasori_e[2] =
{
  &pat00,
  &pat01
};
sprite_pattern* pat_sasori_b[2] =
{
  &pat02,
  &pat03
};
sprite_pattern* pat_tail[2] =
{
  &pat04,
  &pat05
};
static sprite_pattern* pat_tama[2] =
{
  &pat06,
  &pat07
};
static unsigned char pchg00[4] = { 29, 0, 1, 255 };
static unsigned char* pchg[1] = { pchg00 };
static unsigned char pchg_tama00[4] = { 1, 0, 1, 255 };
static unsigned char* pchg_tama[1] = { pchg_tama00 };




































































void sasori(sprite_status* pActwk) {
  sprite_status* pMainwk;

  void(*tbl[11])(sprite_status*) =
  {
    &body_init,
    &body_fall,
    &body_move,
    &body_waita,
    &body_waita1,
    &body_waitb,
    &body_waitb1,
    &body_waitc,
    &body_waitc1,
    &body_waitd,
    &body_waitd1
  };

  if (pActwk->userflag.b.l == 0)
  {
    if (enemy_suicide(pActwk)) return;
    tbl[pActwk->r_no0 / 2](pActwk);
    patchg(pActwk, pchg);
    actionsub(pActwk);
    frameout_s00(pActwk, ((short*)pActwk)[23]);
  }
  else
  {
    pMainwk = &actwk[((short*)pActwk)[23]];
    if (pMainwk->actno != 33)
    {
      frameout(pActwk);
      return;
    }
    if (!(pActwk->userflag.b.l & 128))
    {
      actionsub(pActwk);
      return;
    }

    pActwk->xposi.l += ((int*)pActwk)[12];
    patchg(pActwk, pchg_tama);
    actionsub(pActwk);
    frameout_s(pActwk);
  }

}




static void body_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->sprpri = 3;
  pActwk->sprhs = 24;
  pActwk->sprhsize = 24;
  pActwk->sprvsize = 12;
  pActwk->colino = 49;
  ((short*)pActwk)[23] = pActwk->xposi.w.h;
  pActwk->patbase = pat_sasori_e;
  ((int*)pActwk)[12] = -65536;
  ((short*)pActwk)[27] = 3;
  if (pActwk->userflag.b.h)
  {
    pActwk->patbase = pat_sasori_b;
    ((int*)pActwk)[12] = -32768;
    ((short*)pActwk)[27] = 7;
  }

  pActwk->actflg |= 4;
  pActwk->sproffset = 9142;
}




static void init_sub(sprite_status* pActwk0, sprite_status* pActwk1) {
  pActwk1->actno = pActwk0->actno;
  pActwk1->xposi.w.h = pActwk0->xposi.w.h;
  pActwk1->yposi.w.h = pActwk0->yposi.w.h;
  pActwk1->sprpri = pActwk0->sprpri; 
  ((short*)pActwk1)[23] = (unsigned short)(pActwk0 - actwk);

  pActwk1->actflg |= 4;
  pActwk1->sproffset = 9142;
}




static void body_fall(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  short d1;

  ++pActwk->yposi.w.h;
  d1 = emycol_d(pActwk);
  if (d1 < 0)
  {
    pActwk->yposi.w.h += d1;
    pActwk->r_no0 += 2;
    if (actwkchk2(pActwk, &pNewActwk) != 0)
    {
      frameout(pActwk);
      return;
    }
    ((short*)pActwk)[26] = (unsigned short)(pNewActwk - actwk);
    pNewActwk->userflag.b.l = 1;
    pNewActwk->sprhs = 24;
    pNewActwk->sprhsize = 24;
    pNewActwk->sprvsize = 16;
    pNewActwk->patbase = pat_tail;
    pNewActwk->patno = pActwk->userflag.b.h;
    init_sub(pActwk, pNewActwk);
    --pNewActwk->sprpri;
  }
}




static void body_move(sprite_status* pActwk) {
  sprite_status* pTailwk;
  sprite_status* pPlayerwk;
  short d0, d1;
  short carry_flag;
  unsigned char bd0, bd1;

  pActwk->xposi.l += ((int*)pActwk)[12];
  d0 = pActwk->xposi.w.h;
  d0 -= ((short*)pActwk)[23];
  if (d0 < 0)
  {
    d0 *= -1;
  }
  if (d0 >= 80) goto label1;
  d1 = emycol_d(pActwk);
  d0 = d1;
  d0 += 7;
  if ((unsigned short)d0 >= 14) goto label1;
  d0 -= 14;
  pActwk->yposi.w.h += d1;
  pTailwk = &actwk[((short*)pActwk)[26]];
  pTailwk->xposi.w.h = pActwk->xposi.w.h;
  pTailwk->yposi.w.h = pActwk->yposi.w.h;
  pTailwk->xposi.w.h += ((short*)pActwk)[27];
  pTailwk->yposi.w.h -= 16;
  pPlayerwk = &actwk[0];

  d0 = pPlayerwk->yposi.w.h;
  d0 -= pActwk->yposi.w.h;
  d0 += 40;
  if ((unsigned short)d0 >= 80)
  {
    carry_flag = 0;
    d0 -= 80;
  }
  else
  {
    carry_flag = 1;
    d0 = pPlayerwk->xposi.w.h;
    d0 -= pActwk->xposi.w.h;
    d1 = d0;
    d1 += 80;
    if ((unsigned short)d1 >= 160)
    {
      carry_flag = 0;
    }
    else
    {
      carry_flag = 1;
    }
  }

  if (carry_flag)
  {
    pActwk->r_no0 += 2;
    if (d0 < 0) bd0 = 255;
    else bd0 = 0;
    if ((long int)((int*)pActwk)[12] < 0) bd1 = 255;
    else bd1 = 0;
    bd0 ^= bd1;
    if (bd0) goto label1;
  }
  return;
label1:
  pActwk->xposi.l -= ((int*)pActwk)[12];
  ((int*)pActwk)[12] *= -1;
  ((short*)pActwk)[27] *= -1;
  pTailwk = &actwk[((short*)pActwk)[26]];
  pActwk->actflg ^= 1;
  pTailwk->actflg ^= 1;
  pActwk->cddat ^= 1;
  pTailwk->cddat ^= 1;
}




static void body_waita(sprite_status* pActwk) {
  sprite_status* pTailwk;

  pActwk->r_no0 += 2;
  ((short*)pActwk)[28] = 30;
  pTailwk = &actwk[((short*)pActwk)[26]];
  pTailwk->xposi.w.h = pActwk->xposi.w.h;
  pTailwk->yposi.w.h = pActwk->yposi.w.h;
  pTailwk->xposi.w.h += ((short*)pActwk)[27];
  pTailwk->yposi.w.h -= 16;

  body_waita1(pActwk);
}




static void body_waita1(sprite_status* pActwk) {
  sprite_status* pTailwk;
  short d0;

  --((short*)pActwk)[28];
  if (((short*)pActwk)[28] == 0)
  {
    pActwk->r_no0 += 2;
    pTailwk = &actwk[((short*)pActwk)[26]];
    pTailwk->yposi.w.h -= 5;
    d0 = 5;
    if ((long int)((int*)pActwk)[12] >= 0)
    {
      d0 *= -1;
    }
    pTailwk->xposi.w.h += d0;
  }
}




static void body_waitb(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  ((short*)pActwk)[28] = 10;

  body_waitb1(pActwk);
}




static void body_waitb1(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  int d1;
  short d0;

  --((short*)pActwk)[28];
  if (((short*)pActwk)[28] == 0)
  {
    pActwk->r_no0 += 2;
    if (pActwk->userflag.b.h == 0)
    {
      if (actwkchk(&pNewActwk) == 0)
      {
        pNewActwk->userflag.b.l = -1;
        pNewActwk->sprhs = 16;
        pNewActwk->sprhsize = 16;
        pNewActwk->sprvsize = 16;
        pNewActwk->colino = 178;
        pNewActwk->patbase = pat_tama;
        init_sub(pActwk, pNewActwk);
        pNewActwk->yposi.w.h -= 24;
        d0 = -4;
        d1 = -196608;
        if ((long int)((int*)pActwk)[12] >= 0)
        {
          d0 *= -1;
          d1 *= -1;
        }
        pNewActwk->xposi.w.h += d0;
        ((int*)pNewActwk)[12] = d1;
        if (pActwk->actflg & 128)
        {
          soundset(160);
        }
      }
    }
  }
}




static void body_waitc(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  ((short*)pActwk)[28] = 30;

  body_waitc1(pActwk);
}




static void body_waitc1(sprite_status* pActwk) {
  sprite_status* pTailwk;
  short d0;

  --((short*)pActwk)[28];
  if (((short*)pActwk)[28] == 0)
  {
    pActwk->r_no0 += 2;
    pTailwk = &actwk[((short*)pActwk)[26]];
    pTailwk->yposi.w.h += 5;
    d0 = 5;
    if ((long int)((int*)pActwk)[12] >= 0)
    {
      d0 *= -1;
    }
    pTailwk->xposi.w.h -= d0;
  }
}




static void body_waitd(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  ((short*)pActwk)[28] = 30;

  body_waitd1(pActwk);
}




static void body_waitd1(sprite_status* pActwk) {
  --((short*)pActwk)[28];
  if (((short*)pActwk)[28] == 0)
  {
    pActwk->r_no0 = 4;
  }
}
