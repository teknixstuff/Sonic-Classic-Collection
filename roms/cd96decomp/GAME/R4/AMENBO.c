#include "../EQU.h"
#include "AMENBO.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void act_init(sprite_status* pActwk);
static void act_accel(sprite_status* pActwk);
static void act_decel(sprite_status* pActwk);
static void act_stop(sprite_status* pActwk);
static void act_stop1(sprite_status* pActwk);
static void act_move0(sprite_status* pActwk);
static void act_tama(sprite_status* pActwk);
static int act_check(sprite_status* pActwk);

static unsigned char pchg_b0[4] = { 20, 0, 1, 255 };
static unsigned char pchg_e0[4] = { 10, 0, 1, 255 };
static unsigned char pchg_e1[4] = { 5, 2, 3, 255 };
static unsigned char* pchg_b[1] = { pchg_b0 };
static unsigned char* pchg_e[2] =
{
  pchg_e0,
  pchg_e1
};
static sprite_pattern z41a_spr_amenbo_b_00 = { 1, { { -20, -12, 0, 479 } } };
static sprite_pattern z41b_spr_amenbo_b_00 = { 1, { { -20, -12, 0, 440 } } };
static sprite_pattern z41c_spr_amenbo_b_00 = { 1, { { -20, -12, 0, 457 } } };
static sprite_pattern z41d_spr_amenbo_b_00 = { 1, { { -20, -12, 0, 447 } } };
static sprite_pattern z42a_spr_amenbo_b_00 = { 1, { { -20, -12, 0, 485 } } };
static sprite_pattern z42b_spr_amenbo_b_00 = { 1, { { -20, -12, 0, 438 } } };
static sprite_pattern z42c_spr_amenbo_b_00 = { 1, { { -20, -12, 0, 442 } } };
static sprite_pattern z41a_spr_amenbo_b_01 = { 1, { { -20, -12, 0, 480 } } };
static sprite_pattern z41b_spr_amenbo_b_01 = { 1, { { -20, -12, 0, 441 } } };
static sprite_pattern z41c_spr_amenbo_b_01 = { 1, { { -20, -12, 0, 458 } } };
static sprite_pattern z41d_spr_amenbo_b_01 = { 1, { { -20, -12, 0, 448 } } };
static sprite_pattern z42a_spr_amenbo_b_01 = { 1, { { -20, -12, 0, 486 } } };
static sprite_pattern z42b_spr_amenbo_b_01 = { 1, { { -20, -12, 0, 439 } } };
static sprite_pattern z42c_spr_amenbo_b_01 = { 1, { { -20, -12, 0, 443 } } };
static sprite_pattern z41a_spr_amenbo_e_00 = { 1, { { -20, -12, 0, 481 } } };
static sprite_pattern z41b_spr_amenbo_e_00 = { 1, { { -20, -12, 0, 442 } } };
static sprite_pattern z41c_spr_amenbo_e_00 = { 1, { { -20, -12, 0, 459 } } };
static sprite_pattern z41d_spr_amenbo_e_00 = { 1, { { -20, -12, 0, 449 } } };
static sprite_pattern z42a_spr_amenbo_e_00 = { 1, { { -20, -12, 0, 487 } } };
static sprite_pattern z42b_spr_amenbo_e_00 = { 1, { { -20, -12, 0, 440 } } };
static sprite_pattern z42c_spr_amenbo_e_00 = { 1, { { -20, -12, 0, 444 } } };
static sprite_pattern z41a_spr_amenbo_e_01 = { 1, { { -20, -12, 0, 482 } } };
static sprite_pattern z41b_spr_amenbo_e_01 = { 1, { { -20, -12, 0, 443 } } };
static sprite_pattern z41c_spr_amenbo_e_01 = { 1, { { -20, -12, 0, 460 } } };
static sprite_pattern z41d_spr_amenbo_e_01 = { 1, { { -20, -12, 0, 450 } } };
static sprite_pattern z42a_spr_amenbo_e_01 = { 1, { { -20, -12, 0, 488 } } };
static sprite_pattern z42b_spr_amenbo_e_01 = { 1, { { -20, -12, 0, 441 } } };
static sprite_pattern z42c_spr_amenbo_e_01 = { 1, { { -20, -12, 0, 445 } } };
static sprite_pattern z41a_spr_amenbo_e_02 = { 1, { { -4, -4, 0, 483 } } };
static sprite_pattern z41b_spr_amenbo_e_02 = { 1, { { -4, -4, 0, 444 } } };
static sprite_pattern z41c_spr_amenbo_e_02 = { 1, { { -4, -4, 0, 461 } } };
static sprite_pattern z41d_spr_amenbo_e_02 = { 1, { { -4, -4, 0, 451 } } };
static sprite_pattern z42a_spr_amenbo_e_02 = { 1, { { -4, -4, 0, 489 } } };
static sprite_pattern z42b_spr_amenbo_e_02 = { 1, { { -4, -4, 0, 442 } } };
static sprite_pattern z42c_spr_amenbo_e_02 = { 1, { { -4, -4, 0, 446 } } };
static sprite_pattern z41a_spr_amenbo_e_03 = { 1, { { -4, -4, 0, 484 } } };
static sprite_pattern z41b_spr_amenbo_e_03 = { 1, { { -4, -4, 0, 445 } } };
static sprite_pattern z41c_spr_amenbo_e_03 = { 1, { { -4, -4, 0, 462 } } };
static sprite_pattern z41d_spr_amenbo_e_03 = { 1, { { -4, -4, 0, 452 } } };
static sprite_pattern z42a_spr_amenbo_e_03 = { 1, { { -4, -4, 0, 490 } } };
static sprite_pattern z42b_spr_amenbo_e_03 = { 1, { { -4, -4, 0, 443 } } };
static sprite_pattern z42c_spr_amenbo_e_03 = { 1, { { -4, -4, 0, 447 } } };
sprite_pattern* z41a_pat_amenbo_b[2] =
{
  &z41a_spr_amenbo_b_00,
  &z41a_spr_amenbo_b_01
};
sprite_pattern* z41b_pat_amenbo_b[2] =
{
  &z41b_spr_amenbo_b_00,
  &z41b_spr_amenbo_b_01
};
sprite_pattern* z41c_pat_amenbo_b[2] =
{
  &z41c_spr_amenbo_b_00,
  &z41c_spr_amenbo_b_01
};
sprite_pattern* z41d_pat_amenbo_b[2] =
{
  &z41d_spr_amenbo_b_00,
  &z41d_spr_amenbo_b_01
};
sprite_pattern* z42a_pat_amenbo_b[2] =
{
  &z42a_spr_amenbo_b_00,
  &z42a_spr_amenbo_b_01
};
sprite_pattern* z42b_pat_amenbo_b[2] =
{
  &z42b_spr_amenbo_b_00,
  &z42b_spr_amenbo_b_01
};
sprite_pattern* z42c_pat_amenbo_b[2] =
{
  &z42c_spr_amenbo_b_00,
  &z42c_spr_amenbo_b_01
};
sprite_pattern** pats_amenbo_b[2][4] =
{
  { z41b_pat_amenbo_b, z41a_pat_amenbo_b, z41d_pat_amenbo_b, z41c_pat_amenbo_b },
  { z42b_pat_amenbo_b, z42a_pat_amenbo_b, z42c_pat_amenbo_b, z42c_pat_amenbo_b }
};
sprite_pattern* z41a_pat_amenbo_e[4] =
{
  &z41a_spr_amenbo_e_00,
  &z41a_spr_amenbo_e_01,
  &z41a_spr_amenbo_e_02,
  &z41a_spr_amenbo_e_03
};
sprite_pattern* z41b_pat_amenbo_e[4] =
{
  &z41b_spr_amenbo_e_00,
  &z41b_spr_amenbo_e_01,
  &z41b_spr_amenbo_e_02,
  &z41b_spr_amenbo_e_03
};
sprite_pattern* z41c_pat_amenbo_e[4] =
{
  &z41c_spr_amenbo_e_00,
  &z41c_spr_amenbo_e_01,
  &z41c_spr_amenbo_e_02,
  &z41c_spr_amenbo_e_03
};
sprite_pattern* z41d_pat_amenbo_e[4] =
{
  &z41d_spr_amenbo_e_00,
  &z41d_spr_amenbo_e_01,
  &z41d_spr_amenbo_e_02,
  &z41d_spr_amenbo_e_03
};
sprite_pattern* z42a_pat_amenbo_e[4] =
{
  &z42a_spr_amenbo_e_00,
  &z42a_spr_amenbo_e_01,
  &z42a_spr_amenbo_e_02,
  &z42a_spr_amenbo_e_03
};
sprite_pattern* z42b_pat_amenbo_e[4] =
{
  &z42b_spr_amenbo_e_00,
  &z42b_spr_amenbo_e_01,
  &z42b_spr_amenbo_e_02,
  &z42b_spr_amenbo_e_03
};
sprite_pattern* z42c_pat_amenbo_e[4] =
{
  &z42c_spr_amenbo_e_00,
  &z42c_spr_amenbo_e_01,
  &z42c_spr_amenbo_e_02,
  &z42c_spr_amenbo_e_03
};
sprite_pattern** pats_amenbo_e[2][4] =
{
  { z41b_pat_amenbo_e, z41a_pat_amenbo_e, z41d_pat_amenbo_e, z41c_pat_amenbo_e },
  { z42b_pat_amenbo_e, z42a_pat_amenbo_e, z42c_pat_amenbo_e, z42c_pat_amenbo_e }
};














void amenbo(sprite_status* pActwk) {
  static void(*act_tbl[5])(sprite_status*) =
  {
    &act_init,
    &act_accel,
    &act_decel,
    &act_stop,
    &act_stop1
  };

  if (pActwk->userflag.b.h < 0)
  {

    pActwk->xposi.l += ((int*)pActwk)[12];
    if (((int*)pActwk)[15] == 0)
      patchg(pActwk, pchg_b);
    else
      patchg(pActwk, pchg_e);
    actionsub(pActwk);
    frameout_s(pActwk);
    return;
  }
  if (enemy_suicide(pActwk)) return;
  act_tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s(pActwk);
}



static void act_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sproffset = 9136;
  pActwk->sprhs = 20;
  pActwk->sprhsize = 20;
  pActwk->sprvsize = 12;
  pActwk->colino = 49;
  ((short*)pActwk)[32] = 120;
  ((short*)pActwk)[33] = pActwk->xposi.w.h;
  if (!pActwk->userflag.b.h)
  {
    pActwk->patbase = pats_amenbo_e[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
    ((int*)pActwk)[15] = 1;
    ((int*)pActwk)[13] = -1536;
    ((int*)pActwk)[14] = 256;
  }
  else
  {
    pActwk->patbase = pats_amenbo_b[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
    ((int*)pActwk)[15] = 0;
    ((int*)pActwk)[13] = -512;
    ((int*)pActwk)[14] = 192;
  }
  act_accel(pActwk);
}



static void act_accel(sprite_status* pActwk) {
  int lD5, lD6;

  lD6 = ((int*)pActwk)[12] + ((int*)pActwk)[13];
  if (!pActwk->userflag.b.h)
    lD5 = -98304;
  else
    lD5 = -49152;

  if (lD6 <= lD5)
  {
    lD6 = lD5;

    pActwk->r_no0 += 2;
    ((int*)pActwk)[13] *= -1;
  }
  else
  {

    lD5 = -lD5;
    if (lD6 < lD5) goto label1;

    lD6 = lD5;

    pActwk->r_no0 += 2;
    ((int*)pActwk)[13] *= -1;
  }

label1:
  ((int*)pActwk)[12] = lD6;
  if (!pActwk->userflag.b.h)
    act_tama(pActwk);

  if (((int*)pActwk)[15] == 0)
    patchg(pActwk, pchg_b);
  else
    patchg(pActwk, pchg_e);
  act_move0(pActwk);
}



static void act_decel(sprite_status* pActwk) {
  int lD6;
  unsigned char temp0, temp1;

  lD6 = ((int*)pActwk)[12] + ((int*)pActwk)[14];
  temp0 = temp1 = 0;
  if (((int*)pActwk)[12] < 0)
    temp0 = 255;
  if (lD6 < 0)
    temp1 = 255;
  if (temp0 ^ temp1)
  {
    pActwk->r_no0 += 2;
    ((int*)pActwk)[14] *= -1;
    lD6 = 0;
    if (!pActwk->userflag.b.h)
      ((short*)pActwk)[23] = 60;
    else
      ((short*)pActwk)[23] = 60;
  }

  ((int*)pActwk)[12] = lD6;
  if (!pActwk->userflag.b.h)
    act_tama(pActwk);

  act_move0(pActwk);
}



static void act_stop(sprite_status* pActwk) {
  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] <= 0)
  {
    pActwk->r_no0 += 2;
    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;
    if (!pActwk->userflag.b.h)
      ((short*)pActwk)[23] = 60;
    else
      ((short*)pActwk)[23] = 60;
  }

  if (!pActwk->userflag.b.h)
    act_tama(pActwk);

  act_move0(pActwk);
}



static void act_stop1(sprite_status* pActwk) {
  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] <= 0)
    pActwk->r_no0 = 2;

  act_move0(pActwk);
}



static void act_move0(sprite_status* pActwk) {
  pActwk->xposi.l += ((int*)pActwk)[12];
  pActwk->yposi.w.h = waterposi - 8;
}



static void act_tama(sprite_status* pActwk) {
  sprite_status* subActwk;

  --((short*)pActwk)[32];
  if (((short*)pActwk)[32] <= 0)
  {
    ((short*)pActwk)[32] = 120;
    if (act_check(pActwk) != 0)
    {

      if (actwkchk(&subActwk) == 0)
      {
        subActwk->actno = pActwk->actno;
        subActwk->userflag.b.h = -1;
        ((short*)subActwk)[44] = (unsigned char)(pActwk - actwk);
        subActwk->xposi.w.h = pActwk->xposi.w.h;
        subActwk->yposi.w.h = pActwk->yposi.w.h;
        subActwk->actflg = pActwk->actflg;
        subActwk->sprpri = pActwk->sprpri + 1;
        subActwk->sproffset = pActwk->sproffset;
        subActwk->sprhs = 4;
        subActwk->sprhsize = 4;
        subActwk->sprvsize = 4;
        subActwk->colino = 178;
        subActwk->patbase = pActwk->patbase;
        ((int*)subActwk)[15] = ((int*)pActwk)[15];
        subActwk->mstno.b.h = 1;
        if (!(subActwk->actflg & 1))
          ((int*)subActwk)[12] = -0x20000;
        else
          ((int*)subActwk)[12] = 0x20000;
        if ((char)pActwk->actflg < 0)
          soundset(160);
      }
    }
  }
}



static int act_check(sprite_status* pActwk) {
  short tmp;
  unsigned char bD0;
  unsigned char bD1;
  int ret;


  ret = 0;

  tmp = actwk[0].yposi.w.h - pActwk->yposi.w.h + 96;
  if ((unsigned short)tmp < 192)
  {
    tmp -= 192;
    bD0 = bD1 = 0;
    tmp = actwk[0].xposi.w.h - pActwk->xposi.w.h;
    if (tmp < 0)
      bD1 = 255;
    tmp += 96;
    if ((unsigned short)tmp < 192)
    {
      if (!(pActwk->actflg & 1))
        bD0 = 255;
      if (!(bD1 ^ bD0))
        ret = -1;
    }
  }
  return ret;
}
