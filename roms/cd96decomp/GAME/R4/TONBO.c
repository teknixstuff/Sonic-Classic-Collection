#include "../EQU.h"
#include "TONBO.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void act_init(sprite_status* pActwk);
static void act_lr(sprite_status* pActwk);

static unsigned char pchg0[4] = { 2, 0, 1, 255 };
static unsigned char pchg1[4] = { 4, 0, 2, 255 };
static unsigned char* pchg[2] =
{
  pchg0,
  pchg1
};
static sprite_pattern z41a_spr_tonbo_e_00 = { 1, { { -29, -17, 0, 476 } } };
static sprite_pattern z41b_spr_tonbo_e_00 = { 1, { { -29, -17, 0, 437 } } };
static sprite_pattern z41c_spr_tonbo_e_00 = { 1, { { -29, -17, 0, 454 } } };
static sprite_pattern z41d_spr_tonbo_e_00 = { 1, { { -29, -17, 0, 439 } } };
static sprite_pattern z42a_spr_tonbo_e_00 = { 1, { { -29, -17, 0, 482 } } };
static sprite_pattern z42b_spr_tonbo_e_00 = { 1, { { -29, -17, 0, 435 } } };
static sprite_pattern z43_spr_tonbo_e_00 = { 1, { { -29, -17, 0, 432 } } };
static sprite_pattern z41a_spr_tonbo_e_01 = { 1, { { -29, -13, 0, 477 } } };
static sprite_pattern z41b_spr_tonbo_e_01 = { 1, { { -29, -13, 0, 438 } } };
static sprite_pattern z41c_spr_tonbo_e_01 = { 1, { { -29, -13, 0, 455 } } };
static sprite_pattern z41d_spr_tonbo_e_01 = { 1, { { -29, -13, 0, 440 } } };
static sprite_pattern z42a_spr_tonbo_e_01 = { 1, { { -29, -13, 0, 483 } } };
static sprite_pattern z42b_spr_tonbo_e_01 = { 1, { { -29, -13, 0, 436 } } };
static sprite_pattern z43_spr_tonbo_e_01 = { 1, { { -29, -13, 0, 433 } } };
static sprite_pattern z41a_spr_tonbo_e_02 = { 1, { { -29, -17, 0, 478 } } };
static sprite_pattern z41b_spr_tonbo_e_02 = { 1, { { -29, -17, 0, 439 } } };
static sprite_pattern z41c_spr_tonbo_e_02 = { 1, { { -29, -17, 0, 456 } } };
static sprite_pattern z41d_spr_tonbo_e_02 = { 1, { { -29, -17, 0, 441 } } };
static sprite_pattern z42a_spr_tonbo_e_02 = { 1, { { -29, -17, 0, 484 } } };
static sprite_pattern z42b_spr_tonbo_e_02 = { 1, { { -29, -17, 0, 437 } } };
static sprite_pattern z43_spr_tonbo_e_02 = { 1, { { -29, -17, 0, 434 } } };
static sprite_pattern z41a_spr_tonbo_b_00 = { 1, { { -29, -17, 0, 473 } } };
static sprite_pattern z41b_spr_tonbo_b_00 = { 1, { { -29, -17, 0, 434 } } };
static sprite_pattern z41c_spr_tonbo_b_00 = { 1, { { -29, -17, 0, 451 } } };
static sprite_pattern z41d_spr_tonbo_b_00 = { 1, { { -29, -17, 0, 436 } } };
static sprite_pattern z42a_spr_tonbo_b_00 = { 1, { { -29, -17, 0, 479 } } };
static sprite_pattern z42b_spr_tonbo_b_00 = { 1, { { -29, -17, 0, 432 } } };
static sprite_pattern z43_spr_tonbo_b_00 = { 1, { { -29, -17, 0, 429 } } };
static sprite_pattern z41a_spr_tonbo_b_01 = { 1, { { -29, -13, 0, 474 } } };
static sprite_pattern z41b_spr_tonbo_b_01 = { 1, { { -29, -13, 0, 435 } } };
static sprite_pattern z41c_spr_tonbo_b_01 = { 1, { { -29, -13, 0, 452 } } };
static sprite_pattern z41d_spr_tonbo_b_01 = { 1, { { -29, -13, 0, 437 } } };
static sprite_pattern z42a_spr_tonbo_b_01 = { 1, { { -29, -13, 0, 480 } } };
static sprite_pattern z42b_spr_tonbo_b_01 = { 1, { { -29, -13, 0, 433 } } };
static sprite_pattern z43_spr_tonbo_b_01 = { 1, { { -29, -13, 0, 430 } } };
static sprite_pattern z41a_spr_tonbo_b_02 = { 1, { { -29, -17, 0, 475 } } };
static sprite_pattern z41b_spr_tonbo_b_02 = { 1, { { -29, -17, 0, 436 } } };
static sprite_pattern z41c_spr_tonbo_b_02 = { 1, { { -29, -17, 0, 453 } } };
static sprite_pattern z41d_spr_tonbo_b_02 = { 1, { { -29, -17, 0, 438 } } };
static sprite_pattern z42a_spr_tonbo_b_02 = { 1, { { -29, -17, 0, 481 } } };
static sprite_pattern z42b_spr_tonbo_b_02 = { 1, { { -29, -17, 0, 434 } } };
static sprite_pattern z43_spr_tonbo_b_02 = { 1, { { -29, -17, 0, 431 } } };
sprite_pattern* z41a_pat_tonbo_e[3] =
{
  &z41a_spr_tonbo_e_00,
  &z41a_spr_tonbo_e_01,
  &z41a_spr_tonbo_e_02
};
sprite_pattern* z41b_pat_tonbo_e[3] =
{
  &z41b_spr_tonbo_e_00,
  &z41b_spr_tonbo_e_01,
  &z41b_spr_tonbo_e_02
};
sprite_pattern* z41c_pat_tonbo_e[3] =
{
  &z41c_spr_tonbo_e_00,
  &z41c_spr_tonbo_e_01,
  &z41c_spr_tonbo_e_02
};
sprite_pattern* z41d_pat_tonbo_e[3] =
{
  &z41d_spr_tonbo_e_00,
  &z41d_spr_tonbo_e_01,
  &z41d_spr_tonbo_e_02
};
sprite_pattern* z42a_pat_tonbo_e[3] =
{
  &z42a_spr_tonbo_e_00,
  &z42a_spr_tonbo_e_01,
  &z42a_spr_tonbo_e_02
};
sprite_pattern* z42b_pat_tonbo_e[3] =
{
  &z42b_spr_tonbo_e_00,
  &z42b_spr_tonbo_e_01,
  &z42b_spr_tonbo_e_02
};
sprite_pattern* z43_pat_tonbo_e[3] =
{
  &z43_spr_tonbo_e_00,
  &z43_spr_tonbo_e_01,
  &z43_spr_tonbo_e_02
};
sprite_pattern** pats_tonbo_e[3][4] =
{
  { z41b_pat_tonbo_e, z41a_pat_tonbo_e, z41d_pat_tonbo_e, z41c_pat_tonbo_e },
  { z42b_pat_tonbo_e, z42a_pat_tonbo_e, z41d_pat_tonbo_e, z41d_pat_tonbo_e },
  { 0, 0, z43_pat_tonbo_e, z43_pat_tonbo_e }
};
sprite_pattern* z41a_pat_tonbo_b[3] =
{
  &z41a_spr_tonbo_b_00,
  &z41a_spr_tonbo_b_01,
  &z41a_spr_tonbo_b_02
};
sprite_pattern* z41b_pat_tonbo_b[3] =
{
  &z41b_spr_tonbo_b_00,
  &z41b_spr_tonbo_b_01,
  &z41b_spr_tonbo_b_02
};
sprite_pattern* z41c_pat_tonbo_b[3] =
{
  &z41c_spr_tonbo_b_00,
  &z41c_spr_tonbo_b_01,
  &z41c_spr_tonbo_b_02
};
sprite_pattern* z41d_pat_tonbo_b[3] =
{
  &z41d_spr_tonbo_b_00,
  &z41d_spr_tonbo_b_01,
  &z41d_spr_tonbo_b_02
};
sprite_pattern* z42a_pat_tonbo_b[3] =
{
  &z42a_spr_tonbo_b_00,
  &z42a_spr_tonbo_b_01,
  &z42a_spr_tonbo_b_02
};
sprite_pattern* z42b_pat_tonbo_b[3] =
{
  &z42b_spr_tonbo_b_00,
  &z42b_spr_tonbo_b_01,
  &z42b_spr_tonbo_b_02
};
sprite_pattern* z43_pat_tonbo_b[3] =
{
  &z43_spr_tonbo_b_00,
  &z43_spr_tonbo_b_01,
  &z43_spr_tonbo_b_02
};
sprite_pattern** pats_tonbo_b[3][4] =
{
  { z41b_pat_tonbo_b, z41a_pat_tonbo_b, z41d_pat_tonbo_b, z41c_pat_tonbo_b },
  { z42b_pat_tonbo_b, z42a_pat_tonbo_b, z41d_pat_tonbo_b, z41d_pat_tonbo_b },
  { 0, 0, z43_pat_tonbo_b, z43_pat_tonbo_b }
};


void tonbo(sprite_status* pActwk) {
  short temp;
  static void(*act_tbl[2])(sprite_status*) =
  {
    &act_init,
    &act_lr
  };

  if (enemy_suicide(pActwk)) return;
  act_tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  temp = ((short*)pActwk)[33];
  frameout_s00(pActwk, temp);
}



static void act_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg = 4;
  pActwk->colino = 44;
  pActwk->sprpri = 1;
  pActwk->sprhs = 28;
  pActwk->sprhsize = 28;
  pActwk->sprvsize = 16;
  pActwk->sproffset = 9238;
  ((short*)pActwk)[33] = pActwk->xposi.w.h;
  *(int*)&pActwk->actfree[0] = pActwk->yposi.l;

  if (!pActwk->userflag.b.h)
  {
    pActwk->patbase = pats_tonbo_e[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
    ((int*)pActwk)[13] = -65536;
    ((short*)pActwk)[28] = 4;
    ((short*)pActwk)[30] = 256;
  }
  else
  {
    pActwk->patbase = pats_tonbo_b[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
    ((int*)pActwk)[13] = -32768;
    ((short*)pActwk)[28] = 1;
    ((short*)pActwk)[30] = 512;
  }
  ((short*)pActwk)[29] = ((short*)pActwk)[30];
  ((short*)pActwk)[29] >>= 1;
}



static void act_lr(sprite_status* pActwk) {
  short sin;
  short cos;
  int_union sinl;


  pActwk->xposi.l += ((int*)pActwk)[13];
  sinset(pActwk->actfree[4], &sin, &cos);
  sinl.l = 0;
  sinl.w.h = sin;



  sinl.l >>= 4;
  pActwk->yposi.l = *(int*)&pActwk->actfree[0] + sinl.l;

  ((short*)pActwk)[25] += ((short*)pActwk)[28];

  --((short*)pActwk)[29];
  if (!((short*)pActwk)[29])
  {
    ((short*)pActwk)[29] = ((short*)pActwk)[30];
    ((int*)pActwk)[13] *= -1;
    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;
  }

  patchg(pActwk, pchg);
}
