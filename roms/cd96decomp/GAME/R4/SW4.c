#include "../EQU.h"
#include "SW4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

static void act_init(sprite_status* pActwk);
static void act_move(sprite_status* pActwk);
static short hosei(sprite_status* pActwk, sprite_status* pActwk2);

static sprite_pattern z4apat00 = { 1, { { -16, -8, 0, 438 } } };
static sprite_pattern z41bpat00 = { 1, { { -16, -8, 0, 492 } } };
static sprite_pattern z41cpat00 = { 1, { { -16, -8, 0, 476 } } };
static sprite_pattern z42bpat00 = { 1, { { -16, -8, 0, 489 } } };
static sprite_pattern z42cpat00 = { 1, { { -16, -8, 0, 486 } } };
static sprite_pattern z43pat00 = { 1, { { -16, -8, 0, 472 } } };
static sprite_pattern z4apat01 = { 1, { { -16, -4, 0, 439 } } };
static sprite_pattern z41bpat01 = { 1, { { -16, -4, 0, 493 } } };
static sprite_pattern z41cpat01 = { 1, { { -16, -4, 0, 477 } } };
static sprite_pattern z42bpat01 = { 1, { { -16, -4, 0, 490 } } };
static sprite_pattern z42cpat01 = { 1, { { -16, -4, 0, 487 } } };
static sprite_pattern z43pat01 = { 1, { { -16, -4, 0, 473 } } };
sprite_pattern* z4a_pat_sw[2] =
{
  &z4apat00,
  &z4apat01
};
sprite_pattern* z41b_pat_sw[2] =
{
  &z41bpat00,
  &z41bpat01
};
sprite_pattern* z41c_pat_sw[2] =
{
  &z41cpat00,
  &z41cpat01
};
sprite_pattern* z42b_pat_sw[2] =
{
  &z42bpat00,
  &z42bpat01
};
sprite_pattern* z42c_pat_sw[2] =
{
  &z42cpat00,
  &z42cpat01
};
sprite_pattern* z43_pat_sw[2] =
{
  &z43pat00,
  &z43pat01
};
static sprite_pattern** pats_sw[3][3] =
{
  { z41b_pat_sw, z4a_pat_sw, z41c_pat_sw },
  { z42b_pat_sw, z4a_pat_sw, z42c_pat_sw },
  { 0, 0, z43_pat_sw }
};


void sw4(sprite_status* pActwk) {
  if (pActwk->r_no0) act_move(pActwk);
  else act_init(pActwk);
}




static void act_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sprhsize = 16;
  pActwk->sproffset = 1290;
  pActwk->patbase = pats_sw[stageno_i.b.l][time_flag_i & 0x7F];
  pActwk->sprvsize = 10;

  ((short*)pActwk)[32] = (unsigned short)pActwk->userflag.b.h;

  pActwk->actfree[20] = 0;
  pActwk->actfree[21] = 0;

  act_move(pActwk);
}




static void act_move(sprite_status* pActwk) {
  sprite_status* pActwk_a1;
  sprite_status* pPlayerwk;
  unsigned char* a4;
  short d0, d1, d3, d4;
  short z;

  d0 = ((short*)pActwk)[28];
  if (d0)
  {
    pActwk_a1 = &actwk[d0];
    d1 = pActwk->xposi.w.h;
    d0 = ((char*)pActwk)[60];
    d0 += pActwk_a1->xposi.w.h;
    pActwk->xposi.w.h = d0;
    d0 -= d1;
    d0 <<= 8;
    pActwk->xspeed.w = d0;
    d0 = ((char*)pActwk)[61];
    d0 += pActwk_a1->yposi.w.h;
    pActwk->yposi.w.h = d0;
  }
  pActwk->actfree[20] = pActwk->actfree[21];
  d3 = pActwk->xposi.w.h;
  d4 = pActwk->yposi.w.h;
  pPlayerwk = &actwk[0];
  if (hitchk(pActwk, pPlayerwk))
  {
    z = hosei(pActwk, pPlayerwk);
  }
  else
  {
    z = 1;
  }
  a4 = &switchflag[((short*)pActwk)[32]];
  if (z == 0) pActwk->actfree[21] = 255;
  else pActwk->actfree[21] = 0;
  if (z)
  {
    *a4 &= 127;
  }
  else
  {
    hosei(pActwk, pPlayerwk);
    *a4 |= 128;
    *a4 |= 64;
  }

  if (pActwk->actfree[20] == 0 && pActwk->actfree[21] == 255)
  {
    if (pActwk->actflg & 128)
    {
      soundset(191);
    }
    *a4 ^= 32;
    pPlayerwk->yposi.w.h += 8;
    if (((short*)pActwk)[28])
    {
      ((char*)pActwk)[61] += 4;
    }
    else
    {
      pActwk->yposi.w.h += 4;
    }
    pActwk->patno = 1;
    pActwk->sprvsize -= 4;
  }

  if (pActwk->actfree[20] == 255 && pActwk->actfree[21] == 0)
  {
    pPlayerwk->yposi.w.h -= 8;
    if (((short*)pActwk)[28])
    {
      ((char*)pActwk)[61] -= 4;
    }
    else
    {
      pActwk->yposi.w.h -= 4;
    }
    pActwk->patno = 0;
    pActwk->sprvsize += 4;
  }
  actionsub(pActwk);
  d0 = ((short*)pActwk)[28];
  if (d0 == 0)
  {
    frameout_s(pActwk);
    return;
  }
  pActwk_a1 = &actwk[d0];
  d0 = ((short*)pActwk_a1)[29];
  d0 &= -128;
  d1 = scra_h_posit.w.h;
  d1 -= 128;
  d1 &= -128;
  d0 -= d1;
  if ((unsigned short)d0 > 640) frameout_s0(pActwk);
}




static short hosei(sprite_status* pActwk, sprite_status* pActwk2) {
  short d0, d1;
  short z;

  d0 = pActwk->yposi.w.h;
  d1 = pActwk->sprvsize;
  d0 -= d1;
  d1 = pActwk2->sprvsize;
  d0 -= d1;
  ++d0;
  pActwk2->yposi.w.h = d0;
  if (d0) z = 0;
  else z = 1;
  return z;
}
