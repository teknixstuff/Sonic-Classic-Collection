#include "../EQU.h"
#include "BIGBOM8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../PLAYSUB.h"

static sprite_pattern pat000 =
{
  3,
  {
    { -4, -44, 0, 482 },
    { -28, 3, 0, 483 },
    { -20, -20, 0, 484 }
  }
};
static sprite_pattern pat001 =
{
  3,
  {
    { -4, -46, 0, 485 },
    { -20, 3, 0, 486 },
    { -20, -22, 0, 487 }
  }
};
static sprite_pattern pat002 =
{
  3,
  {
    { -4, -44, 0, 488 },
    { -20, 3, 0, 489 },
    { -20, -20, 0, 490 }
  }
};
static sprite_pattern pat003 =
{
  3,
  {
    { -4, -46, 0, 491 },
    { -12, 3, 0, 492 },
    { -20, -22, 0, 493 }
  }
};
static sprite_pattern pat004 =
{
  2,
  {
    { -28, 3, 0, 494 },
    { -20, -20, 0, 495 }
  }
};
sprite_pattern* pat_bigbom[5] =
{
  &pat000,
  &pat001,
  &pat002,
  &pat003,
  &pat004
};
static sprite_pattern pat100 =
{
  1,
  { { -4, -12, 0, 496 } }
};
static sprite_pattern pat101 =
{
  1,
  { { -4, -12, 0, 497 } }
};
sprite_pattern* pat1[2] =
{
  &pat100,
  &pat101
};
static sprite_pattern pat200 =
{
  1,
  { { -16, -8, 0, 498 } }
};
static sprite_pattern pat201 =
{
  1,
  { { -16, -16, 0, 499 } }
};
static sprite_pattern pat202 =
{
  1,
  { { -16, -16, 0, 500 } }
};
static sprite_pattern pat203 =
{
  1,
  { { -24, -24, 0, 501 } }
};
static sprite_pattern pat204 =
{
  1,
  { { -24, -24, 0, 502 } }
};
sprite_pattern* pat2[5] =
{
  &pat200,
  &pat201,
  &pat202,
  &pat203,
  &pat204
};
static sprite_pattern pat300 =
{
  1,
  { { -8, -8, 0, 503 } }
};
static sprite_pattern pat301 =
{
  1,
  { { -8, -8, 0, 504 } }
};
sprite_pattern* pat3[2] =
{
  &pat300,
  &pat301
};





































































void bigbom(sprite_status* pActwk) {
  void(*tbl[5])(sprite_status*) =
  {
    &bigbom0,
    &bigbom1,
    &bigbom2,
    &bigbom3,
    &bigbom4
  };

  tbl[pActwk->userflag.b.h / 2](pActwk);
}









































void bigbom0(sprite_status* pActwk) {
  void(*tbl[7])(sprite_status*) =
  {
    &m_move0,
    &m_move1,
    &m_move2,
    &m_move3,
    &m_move4,
    &m_move5,
    &m_move6
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  if (pActwk->userflag.b.l != 2)
  {
    frameout_s00(pActwk, ((short*)pActwk)[24]);
  }
}




void m_move0(sprite_status* pActwk) {
  sprite_status* pNewActwk;

  ((short*)pActwk)[24] = pActwk->xposi.w.h;

  if (actwkchk(&pNewActwk) != 0)
  {
    frameout_s0(pActwk);
  }
  else
  {
    pNewActwk->actno = pActwk->actno;
    pNewActwk->userflag.b.h = 2;
    pNewActwk->userflag.b.l = pActwk->userflag.b.l;
    pNewActwk->xposi.w.h = pActwk->xposi.w.h;
    pNewActwk->yposi.w.h = pActwk->yposi.w.h;
    ((short*)pNewActwk)[33] = (unsigned short)(pActwk - actwk);

    ((short*)pActwk)[32] = (unsigned short)(pNewActwk - actwk);
    pActwk->r_no0 += 2;

    m_move1(pActwk);
  }
}




void m_move1(sprite_status* pActwk) {

}




void m_move2(sprite_status* pActwk) {
  ((short*)pActwk)[23] = 30;
  pActwk->r_no0 += 2;

  m_move3(pActwk);
}




void m_move3(sprite_status* pActwk) {
  sprite_status* pObj1wk;
  sprite_status* pNewActwk;

  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] == 0)
  {

    pObj1wk = &actwk[((short*)pActwk)[32]];
    pObj1wk->r_no0 += 2;

    if (actwkchk(&pNewActwk) != 0)
    {
      frameout(pActwk);
    }
    else
    {
      pNewActwk->actno = pActwk->actno;
      pNewActwk->userflag.b.h = 4;

      ((short*)pNewActwk)[33] = (unsigned short)(pActwk - actwk);
      pNewActwk->xposi.w.h = pActwk->xposi.w.h;
      pNewActwk->yposi.w.h = pActwk->yposi.w.h - 31;
      pObj1wk = &actwk[((short*)pActwk)[32]];
      if (pObj1wk->actflg & 1)
      {
        pNewActwk->actflg ^= 1;
        pNewActwk->cddat ^= 1;
      }
      pActwk->r_no0 += 2;
    }
  }
}




void m_move4(sprite_status* pActwk) {

}




void m_move5(sprite_status* pActwk) {
  ((short*)pActwk)[23] = 0;
  pActwk->r_no0 += 2;

  m_move6(pActwk);
}




void m_move6(sprite_status* pActwk) {
  sprite_status* pObj1wk;
  sprite_status* pNewActwk;
  sprite_status* pAct1;

  ++((short*)pActwk)[23];

  if (((short*)pActwk)[23] == 32)
  {
    pObj1wk = &actwk[((short*)pActwk)[32]];
    pObj1wk->r_no0 += 2;
  }

  if (((short*)pActwk)[23] == 30)
  {
    if (actwkchk(&pNewActwk) != 0)
    {
      frameout(pActwk);
      return;
    }


    pNewActwk->actno = pActwk->actno;
    pNewActwk->userflag.b.h = 6;
    pNewActwk->xposi.w.h = pActwk->xposi.w.h;
    pNewActwk->yposi.w.h = pActwk->yposi.w.h;
  }


  if (((short*)pActwk)[23] == 31)
  {
    make_fire(pActwk, &pAct1);
    *(int*)&pAct1->actfree[0] = -65536;
    *(int*)&pAct1->actfree[4] = -270336;
    make_fire(pActwk, &pAct1);
    *(int*)&pAct1->actfree[0] = -0x20000;
    *(int*)&pAct1->actfree[4] = -335872;
    make_fire(pActwk, &pAct1);
    *(int*)&pAct1->actfree[0] = -196608;
    *(int*)&pAct1->actfree[4] = -401408;
    make_fire(pActwk, &pAct1);
    *(int*)&pAct1->actfree[0] = 65536;
    *(int*)&pAct1->actfree[4] = -270336;
    make_fire(pActwk, &pAct1);
    *(int*)&pAct1->actfree[0] = 0x20000;
    *(int*)&pAct1->actfree[4] = -335872;
    make_fire(pActwk, &pAct1);
    *(int*)&pAct1->actfree[0] = 196608;
    *(int*)&pAct1->actfree[4] = -401408;
    make_fire(pActwk, &pAct1);
    *(int*)&pAct1->actfree[0] = 0;
    *(int*)&pAct1->actfree[4] = -204800;
  }

  if (((short*)pActwk)[23] == 40)
  {
    frameout(pActwk);
  }
}


void make_fire(sprite_status* pActwk, sprite_status** pNewActwk) {
  if (actwkchk(pNewActwk) != 0)
  {
    frameout_s0(pActwk);
  }
  else
  {
    (*pNewActwk)->actno = pActwk->actno;
    (*pNewActwk)->userflag.b.h = 8;
    (*pNewActwk)->userflag.b.l = pActwk->userflag.b.l;
    (*pNewActwk)->xposi.w.h = pActwk->xposi.w.h;
    (*pNewActwk)->yposi.w.h = pActwk->yposi.w.h;
    *(int*)&(*pNewActwk)->actfree[8] = 0;
    *(int*)&(*pNewActwk)->actfree[12] = 8192;
  }
}


























void bigbom1(sprite_status* pActwk) {
  sprite_status* pMainwk;

  void(*tbl[13])(sprite_status*) =
  {
    &s0_init,
    &s0_fall,
    &s0_wait,
    &s0_move_const0,
    &s0_move_const,
    &s0_prio_const,
    &s0_move0,
    &s0_move,
    &s0_stop,
    &s0_stop0,
    &s0_move1,
    &s0_stop1,
    &s0_die
  };



  tbl[pActwk->r_no0 / 2](pActwk);
  pMainwk = &actwk[((short*)pActwk)[33]];
  if (pMainwk->actno == 35)
  {
    pMainwk->xposi.w.h = pActwk->xposi.w.h;
    pMainwk->yposi.w.h = pActwk->yposi.w.h;
    actionsub(pActwk);
  }
  else
  {
    frameout(pActwk);
  }
}




void s0_init(sprite_status* pActwk) {
  pActwk->actflg |= 4;
  pActwk->sprpri = 1;
  pActwk->sproffset = 33600;
  pActwk->patbase = pat_bigbom;
  pActwk->sprhsize = 20;
  pActwk->sprvsize = 26;
  pActwk->actfree[19] = 166;
  pActwk->r_no0 += 2;

  s0_fall(pActwk);
}




void s0_fall(sprite_status* pActwk) {
  short d1;

  pActwk->yposi.l += 65536;
  d1 = emycol_d(pActwk);
  if (d1 < 0)
  {
    pActwk->yposi.w.h += d1;
    if (pActwk->userflag.b.l != 2)
    {
      pActwk->r_no0 = 12;
      pActwk->colino = 166;
    }
    else
    {
      pActwk->r_no0 += 2;
      pActwk->actflg ^= 1;
      pActwk->cddat ^= 1;
    }
  }
}




void s0_wait(sprite_status* pActwk) {
  sprite_status* pPlayerwk;
  short d0;

  pPlayerwk = &actwk[0];
  if (s0_check(pActwk, pPlayerwk))
  {
    d0 = pPlayerwk->xposi.w.h;
    d0 -= pActwk->xposi.w.h;
    if (d0 >= 0)
    {
      pActwk->r_no0 += 2;
      s0_move_const0(pActwk);
    }
  }
}




void s0_move_const0(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  ((int*)pActwk)[12] = 163840;
  ((short*)pActwk)[23] = 230;
  ((short*)pActwk)[26] = 18;
  pActwk->patno = 3;

  s0_move_const(pActwk);
}




void s0_move_const(sprite_status* pActwk) {
  unsigned char bd0;
  short tbl[4] = { 25, 15, 25, 18 };




  bd0 = 0;
  if (prio_flag == 0)
  {
    bd0 = pActwk->actfree[19];
  }
  pActwk->colino = bd0;

  pActwk->xposi.l += ((int*)pActwk)[12];

  --((short*)pActwk)[26];
  if (((short*)pActwk)[26] < 0)
  {
    ++pActwk->patno;
    pActwk->patno &= 3;
    ((short*)pActwk)[26] = tbl[pActwk->patno];
  }
  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] < 0)
  {
    pActwk->r_no0 += 2;
  }
}




void s0_prio_const(sprite_status* pActwk) {
  unsigned char bd0;

  bd0 = 0;
  if (prio_flag == 0)
  {
    bd0 = pActwk->actfree[19];
  }
  pActwk->colino = bd0;

  if (prio_flag == 0)
  {
    if (s0_check(pActwk, &actwk[0]))
    {
      pActwk->r_no0 = 16;
    }
  }
}




void s0_move0(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  ((int*)pActwk)[12] = -40960;
  ((short*)pActwk)[23] = 0;
  ((short*)pActwk)[26] = 0;
  pActwk->patno = 3;

  s0_move(pActwk);
}




void s0_move(sprite_status* pActwk) {
  short d0, d1;
  short tbl[4] = { 25, 15, 25, 18 };




  pActwk->xposi.l += ((int*)pActwk)[12];

  d1 = emycol_d(pActwk);
  pActwk->yposi.w.h += d1;

  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] < 0)
  {
    ((int*)pActwk)[12] *= -1;
    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;
    d0 = 204;
    if (pActwk->userflag.b.l)
    {
      d0 = 25;
    }
    ((short*)pActwk)[23] = d0;
  }
  --((short*)pActwk)[26];
  if (((short*)pActwk)[26] < 0)
  {
    ++pActwk->patno;
    pActwk->patno &= 3;
    ((short*)pActwk)[26] = tbl[pActwk->patno];
  }
  if (pActwk->patno == 0)
  {
    if (s0_check(pActwk, &actwk[0]))
    {
      to_s0_stop(pActwk);
    }
  }
}




short s0_check(sprite_status* pActwk, sprite_status* pPlayerwk) {
  short d0;
  short carry;

  d0 = pPlayerwk->yposi.w.h;
  d0 -= pActwk->yposi.w.h;
  d0 += 160;
  if ((unsigned short)d0 < 240)
  {
    d0 = pPlayerwk->xposi.w.h;
    d0 -= pActwk->xposi.w.h;
    d0 += 96;
    if ((unsigned short)d0 < 192) carry = 1;
    else carry = 0;
  }
  else
  {
    carry = 0;
  }
  return carry;
}




void to_s0_stop(sprite_status* pActwk) {
  pActwk->r_no0 += 2;

  s0_stop(pActwk);
}




void s0_stop(sprite_status* pActwk) {
  sprite_status* pMainwk;

  pActwk->r_no0 += 2;
  pMainwk = &actwk[((short*)pActwk)[33]];
  pMainwk->r_no0 += 2;

  s0_stop0(pActwk);
}




void s0_stop0(sprite_status* pActwk) {
  unsigned char bd0;

  if (pActwk->userflag.b.l == 2)
  {
    bd0 = 0;
    if (prio_flag == 0)
    {
      bd0 = pActwk->actfree[19];
    }
    pActwk->colino = bd0;
  }
}




void s0_move1(sprite_status* pActwk) {
  pActwk->patno = 4;
  pActwk->r_no0 += 2;

  s0_stop1(pActwk);
}




void s0_stop1(sprite_status* pActwk) {
  s0_stop0(pActwk);
}




void s0_die(sprite_status* pActwk) {
  frameout(pActwk);
}

















void bigbom2(sprite_status* pActwk) {
  void(*tbl[4])(sprite_status*) =
  {
    &s1_init,
    &s1_wait,
    &s1_move,
    &s1_die
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
}




void s1_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 2;

  pActwk->sproffset = 832;
  pActwk->patbase = pat1;
  pActwk->sprhsize = 4;
  pActwk->sprvsize = 12;
  ((short*)pActwk)[23] = 60;

  s1_wait(pActwk);
}




void s1_wait(sprite_status* pActwk) {
  static unsigned char pat00[4] = { 2, 0, 1, 255 };
  static unsigned char* pchg1[1] = { pat00 };








  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] == 0)
  {
    ((short*)pActwk)[23] = 76;
    pActwk->r_no0 += 2;
  }
  patchg(pActwk, pchg1);
}




void s1_move(sprite_status* pActwk) {
  static unsigned char pat00[4] = { 2, 0, 1, 255 };
  static unsigned char* pchg1[1] = { pat00 };








  pActwk->yposi.l += 20480;
  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] < 0)
  {
    pActwk->r_no0 += 2;
  }
  patchg(pActwk, pchg1);
}




void s1_die(sprite_status* pActwk) {
  sprite_status* pMainwk;

  pMainwk = &actwk[((short*)pActwk)[33]];
  if (pMainwk->actno == 35)
  {
    pMainwk->r_no0 += 2;
  }
  frameout(pActwk);
}











void bigbom3(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &s2_init,
    &s2_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
}




void s2_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 1;
  pActwk->sproffset = 34432;
  pActwk->patbase = pat2;
  ((short*)pActwk)[23] = 40;

  s2_move(pActwk);
}




void s2_move(sprite_status* pActwk) {
  static unsigned char pat00[7] = { 3, 0, 1, 2, 3, 4, 255 };
  static unsigned char* pchg2[1] = { pat00 };








  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] == 0)
  {
    frameout(pActwk);
  }
  else
  {
    patchg(pActwk, pchg2);
  }
}

















void bigbom4(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &s3_init,
    &s3_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
}




void s3_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 1;
  pActwk->sprhsize = 8;
  pActwk->sprvsize = 8;
  pActwk->sproffset = 33600;
  pActwk->patbase = pat3;
  pActwk->colino = 167;
  pActwk->actfree[19] = 167;

  s3_move(pActwk);
}




void s3_move(sprite_status* pActwk) {
  sprite_status* pPlayerwk;
  short d0;
  unsigned char bd0;
  static unsigned char pat00[4] = { 1, 0, 1, 255 };
  static unsigned char* pchg3[1] = { pat00 };








  if (pActwk->userflag.b.l == 2)
  {
    bd0 = 0;
    if (prio_flag == 0)
    {
      bd0 = pActwk->actfree[19];
    }
    pActwk->colino = bd0;
  }

  pActwk->xposi.l += *(int*)&pActwk->actfree[0];
  pActwk->yposi.l += *(int*)&pActwk->actfree[4];
  *(int*)&pActwk->actfree[0] += *(int*)&pActwk->actfree[8];
  *(int*)&pActwk->actfree[4] += *(int*)&pActwk->actfree[12];

  pPlayerwk = &actwk[0];
  d0 = pActwk->yposi.w.h;
  d0 -= pPlayerwk->yposi.w.h;
  if (d0 >= 224)
  {
    frameout(pActwk);
  }
  else
  {
    patchg(pActwk, pchg3);
  }
}
