#include "../EQU.h"
#include "YAGO.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void act_disp(sprite_status* pActwk);
static void yago_e(sprite_status* pActwk);
static void act_init(sprite_status* pActwk);
static void act_fall(sprite_status* pActwk);
static void act_lr(sprite_status* pActwk);
static void act_rev(sprite_status* pActwk);
static void act_rev1(sprite_status* pActwk);
static void act_jet(sprite_status* pActwk);
static void act_jet1(sprite_status* pActwk);
static void act_jet2(sprite_status* pActwk);
static void act_fall1(sprite_status* pActwk);
static void yago_b(sprite_status* pActwk);
static void act_init_(sprite_status* pActwk);
static void act_fall_(sprite_status* pActwk);
static void act_jet1_(sprite_status* pActwk);
static void act_jet2_(sprite_status* pActwk);

static unsigned char pat_chg0[4] = { 9, 0, 1, 255 };
static unsigned char* pat_chg[1] = { pat_chg0 };
static sprite_pattern z41a_spr_yago_e_00 = { 1, { { -24, -12, 0, 492 } } };
static sprite_pattern z41b_spr_yago_e_00 = { 1, { { -24, -12, 0, 453 } } };
static sprite_pattern z41c_spr_yago_e_00 = { 1, { { -24, -12, 0, 470 } } };
static sprite_pattern z41d_spr_yago_e_00 = { 1, { { -24, -12, 0, 460 } } };
static sprite_pattern z42a_spr_yago_e_00 = { 1, { { -24, -12, 0, 498 } } };
static sprite_pattern z42b_spr_yago_e_00 = { 1, { { -24, -12, 0, 451 } } };
static sprite_pattern z42c_spr_yago_e_00 = { 1, { { -24, -12, 0, 455 } } };
static sprite_pattern z41a_spr_yago_e_01 = { 1, { { -24, -12, 0, 493 } } };
static sprite_pattern z41b_spr_yago_e_01 = { 1, { { -24, -12, 0, 454 } } };
static sprite_pattern z41c_spr_yago_e_01 = { 1, { { -24, -12, 0, 471 } } };
static sprite_pattern z41d_spr_yago_e_01 = { 1, { { -24, -12, 0, 461 } } };
static sprite_pattern z42a_spr_yago_e_01 = { 1, { { -24, -12, 0, 499 } } };
static sprite_pattern z42b_spr_yago_e_01 = { 1, { { -24, -12, 0, 452 } } };
static sprite_pattern z42c_spr_yago_e_01 = { 1, { { -24, -12, 0, 456 } } };
static sprite_pattern z41a_spr_yago_b_00 = { 1, { { -24, -12, 0, 490 } } };
static sprite_pattern z41b_spr_yago_b_00 = { 1, { { -24, -12, 0, 451 } } };
static sprite_pattern z41c_spr_yago_b_00 = { 1, { { -24, -12, 0, 468 } } };
static sprite_pattern z41d_spr_yago_b_00 = { 1, { { -24, -12, 0, 458 } } };
static sprite_pattern z42a_spr_yago_b_00 = { 1, { { -24, -12, 0, 496 } } };
static sprite_pattern z42b_spr_yago_b_00 = { 1, { { -24, -12, 0, 449 } } };
static sprite_pattern z42c_spr_yago_b_00 = { 1, { { -24, -12, 0, 453 } } };
static sprite_pattern z41a_spr_yago_b_01 = { 1, { { -24, -12, 0, 491 } } };
static sprite_pattern z41b_spr_yago_b_01 = { 1, { { -24, -12, 0, 452 } } };
static sprite_pattern z41c_spr_yago_b_01 = { 1, { { -24, -12, 0, 469 } } };
static sprite_pattern z41d_spr_yago_b_01 = { 1, { { -24, -12, 0, 459 } } };
static sprite_pattern z42a_spr_yago_b_01 = { 1, { { -24, -12, 0, 497 } } };
static sprite_pattern z42b_spr_yago_b_01 = { 1, { { -24, -12, 0, 450 } } };
static sprite_pattern z42c_spr_yago_b_01 = { 1, { { -24, -12, 0, 454 } } };
sprite_pattern* z41a_pat_yago_e[2] =
{
  &z41a_spr_yago_e_00,
  &z41a_spr_yago_e_01
};
sprite_pattern* z41b_pat_yago_e[2] =
{
  &z41b_spr_yago_e_00,
  &z41b_spr_yago_e_01
};
sprite_pattern* z41c_pat_yago_e[2] =
{
  &z41c_spr_yago_e_00,
  &z41c_spr_yago_e_01
};
sprite_pattern* z41d_pat_yago_e[2] =
{
  &z41d_spr_yago_e_00,
  &z41d_spr_yago_e_01
};
sprite_pattern* z42a_pat_yago_e[2] =
{
  &z42a_spr_yago_e_00,
  &z42a_spr_yago_e_01
};
sprite_pattern* z42b_pat_yago_e[2] =
{
  &z42b_spr_yago_e_00,
  &z42b_spr_yago_e_01
};
sprite_pattern* z42c_pat_yago_e[2] =
{
  &z42c_spr_yago_e_00,
  &z42c_spr_yago_e_01
};
sprite_pattern** pats_yago_e[2][4] =
{
  { z41b_pat_yago_e, z41a_pat_yago_e, z41d_pat_yago_e, z41c_pat_yago_e },
  { z42b_pat_yago_e, z42a_pat_yago_e, z42c_pat_yago_e, z42c_pat_yago_e }
};
sprite_pattern* z41a_pat_yago_b[2] =
{
  &z41a_spr_yago_b_00,
  &z41a_spr_yago_b_01
};
sprite_pattern* z41b_pat_yago_b[2] =
{
  &z41b_spr_yago_b_00,
  &z41b_spr_yago_b_01
};
sprite_pattern* z41c_pat_yago_b[2] =
{
  &z41c_spr_yago_b_00,
  &z41c_spr_yago_b_01
};
sprite_pattern* z41d_pat_yago_b[2] =
{
  &z41d_spr_yago_b_00,
  &z41d_spr_yago_b_01
};
sprite_pattern* z42a_pat_yago_b[2] =
{
  &z42a_spr_yago_b_00,
  &z42a_spr_yago_b_01
};
sprite_pattern* z42b_pat_yago_b[2] =
{
  &z42b_spr_yago_b_00,
  &z42b_spr_yago_b_01
};
sprite_pattern* z42c_pat_yago_b[2] =
{
  &z42c_spr_yago_b_00,
  &z42c_spr_yago_b_01
};
sprite_pattern** pats_yago_b[2][4] =
{
  { z41b_pat_yago_b, z41a_pat_yago_b, z41d_pat_yago_b, z41c_pat_yago_b },
  { z42b_pat_yago_b, z42a_pat_yago_b, z42c_pat_yago_b, z42c_pat_yago_b }
};
















void yago(sprite_status* pActwk) {
  if (!pActwk->userflag.b.h)
    yago_e(pActwk);
  else
    yago_b(pActwk);
}



static void act_disp(sprite_status* pActwk) {
  patchg(pActwk, pat_chg);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[33]);
}



static void yago_e(sprite_status* pActwk) {
  static void(*act_tbl[9])(sprite_status*) =
  {
    &act_init,
    &act_fall,
    &act_lr,
    &act_rev,
    &act_rev1,
    &act_jet,
    &act_jet1,
    &act_jet2,
    &act_fall1
  };

  if (!enemy_suicide(pActwk))
    act_tbl[pActwk->r_no0 / 2](pActwk);
}



static void act_init(sprite_status* pActwk) {
  ((short*)pActwk)[33] = pActwk->xposi.w.h;
  pActwk->r_no0 += 2;
  pActwk->actflg = 4;
  pActwk->colino = 47;
  pActwk->sprpri = 1;
  pActwk->sprhsize = 24;
  pActwk->sprvsize = 12;

  pActwk->sproffset = 9200;
  pActwk->patbase = pats_yago_e[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  act_fall(pActwk);
}



static void act_fall(sprite_status* pActwk) {
  pActwk->yposi.l += 65536;
  if (emycol_d(pActwk) - 5 >= 0)
  {
    act_disp(pActwk);
  }
  else
  {

    pActwk->r_no0 += 2;
    *(int*)&pActwk->actfree[0] = 5242880;
    *(int*)&pActwk->actfree[4] = -16384;
    act_disp(pActwk);
  }
}



static void act_lr(sprite_status* pActwk) {
  short temp;

  *(int*)&pActwk->actfree[0] += -16384;
  if ((long int)*(int*)&pActwk->actfree[0] >= 0)
  {
    pActwk->xposi.l += *(int*)&pActwk->actfree[4];
    pActwk->yposi.w.h += emycol_d(pActwk) - 5;
    if (pActwk->actflg & 1)
      temp = emycol_r(pActwk, pActwk->sprhs);
    else
      temp = emycol_l(pActwk, -(char)pActwk->sprhs);
    if (temp - 5 >= 0)
    {
      temp = pActwk->xposi.w.h - actwk[0].xposi.w.h;
      if (pActwk->actflg & 1)
        temp *= -1;

      if ((unsigned short)temp > 80)
      {
        temp -= 16;
        temp -= 64;
        act_disp(pActwk);
        return;
      }


      temp -= 16;
      temp -= 64;

      pActwk->r_no0 += 6;
      ((short*)pActwk)[27] = 7;
      act_disp(pActwk);
      return;
    }
  }


  pActwk->r_no0 += 2;
  ((short*)pActwk)[27] = 31;
  act_disp(pActwk);
}



static void act_rev(sprite_status* pActwk) {
  --((short*)pActwk)[27];
  if (((short*)pActwk)[27])
  {
    act_disp(pActwk);
    return;
  }

  pActwk->r_no0 += 2;
  ((short*)pActwk)[27] = 31;
  *(int*)&pActwk->actfree[0] = 5242880;
  *(int*)&pActwk->actfree[4] *= -1;
  pActwk->actflg ^= 1;
  pActwk->cddat ^= 1;
  act_disp(pActwk);
}



static void act_rev1(sprite_status* pActwk) {
  --((short*)pActwk)[27];
  if (((short*)pActwk)[27])
  {
    act_disp(pActwk);
    return;
  }

  pActwk->r_no0 -= 4;
  act_disp(pActwk);
}



static void act_jet(sprite_status* pActwk) {
  --((short*)pActwk)[27];
  if (((short*)pActwk)[27])
  {
    act_disp(pActwk);
    return;
  }

  pActwk->r_no0 += 2;
  ((short*)pActwk)[27] = 31;
  act_disp(pActwk);
}



static void act_jet1(sprite_status* pActwk) {
  pActwk->yposi.l += 8192;
  --((short*)pActwk)[27];
  if (((short*)pActwk)[27])
  {
    act_disp(pActwk);
    return;
  }

  pActwk->r_no0 += 2;
  ((int*)pActwk)[15] = -294912;
  if (pActwk->actflg & 1)
    ((int*)pActwk)[15] *= -1;

  ((int*)pActwk)[14] = -98304;
  act_disp(pActwk);
}



static void act_jet2(sprite_status* pActwk) {
  short temp;

  pActwk->xposi.l += ((int*)pActwk)[15];
  if (pActwk->actflg & 1)
    temp = emycol_r(pActwk, pActwk->sprhs);
  else
    temp = emycol_l(pActwk, -(char)pActwk->sprhs);
  if (temp - 5 >= 0)
  {
    pActwk->yposi.l += ((int*)pActwk)[14];
    if (((int*)pActwk)[14] < 0)
      ((int*)pActwk)[14] += 8192;

    frameout_s(pActwk);
    act_disp(pActwk);
    return;
  }

  pActwk->r_no0 = 6;

  ((short*)pActwk)[27] = 31;
  act_disp(pActwk);
}



static void act_fall1(sprite_status* pActwk) {
  short temp;

  pActwk->yposi.l += 65536;
  if ((temp = emycol_d(pActwk) - 5) >= 0)
  {
    act_disp(pActwk);
    return;
  }

  pActwk->r_no0 = 6;
  pActwk->yposi.w.h += temp;
  ((short*)pActwk)[27] = 31;
  act_disp(pActwk);
}



static void yago_b(sprite_status* pActwk) {
  static void(*act_tbl[9])(sprite_status*) =
  {
    &act_init_,
    &act_fall_,
    &act_lr,
    &act_rev,
    &act_rev1,
    &act_jet,
    &act_jet1_,
    &act_jet2_,
    &act_fall1
  };

  if (!enemy_suicide(pActwk))
    act_tbl[pActwk->r_no0 / 2](pActwk);
}



static void act_init_(sprite_status* pActwk) {
  ((short*)pActwk)[33] = pActwk->xposi.w.h;
  pActwk->r_no0 += 2;
  pActwk->actflg = 4;
  pActwk->colino = 47;
  pActwk->sprpri = 1;
  pActwk->sprhsize = 24;
  pActwk->sprvsize = 12;

  pActwk->sproffset = 9200;
  pActwk->patbase = pats_yago_b[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  act_fall_(pActwk);
}



static void act_fall_(sprite_status* pActwk) {
  short temp;

  pActwk->yposi.l += 65536;
  if ((temp = emycol_d(pActwk)) - 5 >= 0)
  {
    act_disp(pActwk);
  }
  else
  {

    pActwk->r_no0 += 2;
    pActwk->yposi.w.h += temp - 5;
    *(int*)&pActwk->actfree[0] = 5242880;
    *(int*)&pActwk->actfree[4] = -16384;
    act_disp(pActwk);
  }
}



static void act_jet1_(sprite_status* pActwk) {
  pActwk->yposi.l += 10240;
  --((short*)pActwk)[27];
  if (((short*)pActwk)[27])
  {
    act_disp(pActwk);
    return;
  }

  pActwk->r_no0 += 2;
  ((int*)pActwk)[15] = -65536;
  if (pActwk->actflg & 1)
    ((int*)pActwk)[15] *= -1;

  ((int*)pActwk)[14] = -98304;
  act_disp(pActwk);
}



static void act_jet2_(sprite_status* pActwk) {
  short temp;

  pActwk->xposi.l += ((int*)pActwk)[15];
  if (pActwk->actflg & 1)
    temp = emycol_r(pActwk, pActwk->sprhs);
  else
    temp = emycol_l(pActwk, -(char)pActwk->sprhs);
  if (temp >= 0)
  {
    pActwk->yposi.l += ((int*)pActwk)[14];
    ((int*)pActwk)[14] += 4096;
    if (((int*)pActwk)[14] < 0)
    {
      act_disp(pActwk);
      return;
    }
    if (emycol_d(pActwk) - 5 < 0)
    {

      pActwk->r_no0 = 4;
      act_disp(pActwk);
      return;
    }
    act_disp(pActwk);
    return;
  }

  pActwk->r_no0 += 2;

  ((short*)pActwk)[27] = 31;
  act_disp(pActwk);
}
