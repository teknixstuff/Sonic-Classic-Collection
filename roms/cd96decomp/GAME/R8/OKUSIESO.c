#include "../EQU.h"
#include "OKUSIESO.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../RIDECHK.h"

static void okusieso_init(sprite_status* pActwk);
static void okusieso_move(sprite_status* pActwk);
static void ball_move(sprite_status* pActwk);
static void dai_move(sprite_status* pActwk);

static sprite_pattern z81_spr_sieso_00 = { 2, { { -40, -56, 0, 414 }, { -32, -24, 0, 423 } } };
static sprite_pattern z82_spr_sieso_00 = { 2, { { -40, -56, 0, 411 }, { -32, -24, 0, 420 } } };
static sprite_pattern z81_spr_sieso_01 = { 2, { { -24, -24, 0, 424 }, { -40, -40, 0, 415 } } };
static sprite_pattern z82_spr_sieso_01 = { 2, { { -24, -24, 0, 421 }, { -40, -40, 0, 412 } } };
static sprite_pattern z81_spr_sieso_02 = { 1, { { -24, -24, 0, 416 } } };
static sprite_pattern z82_spr_sieso_02 = { 1, { { -24, -24, 0, 413 } } };
static sprite_pattern z81_spr_sieso_03 = { 1, { { -40, -32, 0, 417 } } };
static sprite_pattern z82_spr_sieso_03 = { 1, { { -40, -32, 0, 414 } } };
static sprite_pattern z81_spr_sieso_04 = { 1, { { -40, -40, 0, 418 } } };
static sprite_pattern z82_spr_sieso_04 = { 1, { { -40, -40, 0, 415 } } };
static sprite_pattern z81_spr_ball_00 = { 1, { { -16, -16, 0, 419 } } };
static sprite_pattern z82_spr_ball_00 = { 1, { { -16, -16, 0, 416 } } };
static sprite_pattern z81_spr_ball_01 = { 1, { { -24, -24, 0, 420 } } };
static sprite_pattern z82_spr_ball_01 = { 1, { { -24, -24, 0, 417 } } };
static sprite_pattern z81_spr_ball_02 = { 1, { { -32, -32, 0, 421 } } };
static sprite_pattern z82_spr_ball_02 = { 1, { { -32, -32, 0, 418 } } };
static sprite_pattern z81_spr_dai_00 = { 1, { { -40, -12, 0, 422 } } };
static sprite_pattern z82_spr_dai_00 = { 1, { { -40, -12, 0, 419 } } };
sprite_pattern* z81okusiesopat[9] =
{
  &z81_spr_sieso_00,
  &z81_spr_sieso_01,
  &z81_spr_sieso_02,
  &z81_spr_sieso_03,
  &z81_spr_sieso_04,
  &z81_spr_ball_00,
  &z81_spr_ball_01,
  &z81_spr_ball_02,
  &z81_spr_dai_00
};
sprite_pattern* z82okusiesopat[9] =
{
  &z82_spr_sieso_00,
  &z82_spr_sieso_01,
  &z82_spr_sieso_02,
  &z82_spr_sieso_03,
  &z82_spr_sieso_04,
  &z82_spr_ball_00,
  &z82_spr_ball_01,
  &z82_spr_ball_02,
  &z82_spr_dai_00
};
sprite_pattern** okusiesopats[2] =
{
  z81okusiesopat,
  z82okusiesopat
};




























































































void okusieso(sprite_status* pActwk) {
  short wD0, wD1;
  static void(*okusieso_tbl[2])(sprite_status*) =
  {
    &okusieso_init,
    &okusieso_move
  };

  okusieso_tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  wD0 = pActwk->xposi.w.h & -128;
  wD1 = scra_h_posit.w.h - 128 & -128;
  if ((unsigned short)(wD0 - wD1) > 640)
    frameout(pActwk);
}



static void okusieso_init(sprite_status* pActwk) {
  sprite_status* subActwk;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->patbase = okusiesopats[stageno_i.b.l];
  pActwk->sproffset = 928;
  pActwk->sprpri = 5;
  pActwk->patno = 0;
  pActwk->sprhsize = 40;
  pActwk->sprvsize = 56;
  pActwk->actfree[6] = 1;
  pActwk->actfree[20] = 0;


  if (actwkchk2(pActwk, &subActwk) == 0)
  {
    subActwk->r_no0 = 2;
    subActwk->actflg |= 4;
    subActwk->patbase = pActwk->patbase;
    subActwk->sproffset = 17312;
    subActwk->sprpri = 6;
    subActwk->patno = 5;
    subActwk->sprhsize = 16;
    subActwk->sprvsize = 16;
    subActwk->yspeed.w = 0;
    subActwk->actfree[20] = 0;
    subActwk->actno = pActwk->actno;
    subActwk->actfree[20] |= 1;
    subActwk->xposi.l = pActwk->xposi.l;
    subActwk->yposi.l = pActwk->yposi.l;
    ((short*)subActwk)[29] = pActwk->yposi.w.h;
    ((short*)subActwk)[27] = (unsigned short)(unsigned char)(pActwk - actwk);
  }
  else
    return;

  if (actwkchk2(pActwk, &subActwk) == 0)
  {
    subActwk->r_no0 = 2;
    subActwk->actflg |= 4;
    subActwk->patbase = okusiesopats[stageno_i.b.l];
    subActwk->sproffset = 928;
    subActwk->sprpri = 3;
    subActwk->patno = 8;
    subActwk->sprhsize = 40;
    subActwk->sprvsize = 12;
    subActwk->yspeed.w = 0;
    subActwk->actfree[20] = 0;
    subActwk->actno = pActwk->actno;
    subActwk->actfree[20] |= 2;
    subActwk->xposi.l = pActwk->xposi.l;
    subActwk->yposi.l = pActwk->yposi.l;
    ((short*)subActwk)[29] = pActwk->yposi.w.h;
    subActwk->yposi.w.h = (unsigned short)subActwk->yposi.w.h + 65492;
    ((short*)subActwk)[27] = (unsigned short)(unsigned char)(pActwk - actwk);
  }
}



static void okusieso_move(sprite_status* pActwk) {
  short wD1;
  unsigned char patno_tbl[4] =
  {
    3, 2, 1, 2
  };

  if (pActwk->actfree[20] & 8) return;

  if (pActwk->actfree[20] & 1)
  {
    ball_move(pActwk);
    return;
  }
  if (pActwk->actfree[20] & 2)
  {
    dai_move(pActwk);
    return;
  }
  if (!(pActwk->actfree[20] & 16)) return;



  if (time_stop) return;

  pActwk->yspeed.w = 0;
  if (!(pActwk->actfree[20] & 64))
  {
    --((char*)pActwk)[52];
    if (((char*)pActwk)[52] < 0)
    {
      ((char*)pActwk)[53] = 5;
      pActwk->actfree[20] |= 64;
      ++pActwk->patno;
    }
    return;
  }

  if (!(pActwk->actfree[20] & 32))
  {
    --((char*)pActwk)[53];
    if (((char*)pActwk)[53] >= 0) return;

    ++pActwk->patno;
    ((char*)pActwk)[53] = 5;
    if (pActwk->patno < 4) return;

    pActwk->actfree[20] |= 32;
    ((char*)pActwk)[52] = 0;
    ((char*)pActwk)[53] = 10;


    return;
  }


  if (pActwk->actfree[20] & 4)
  {

    if (pActwk->patno != 4)
    {
      ++pActwk->patno;
      ((char*)pActwk)[53] = 10;
    }
    return;
  }
  --((char*)pActwk)[53];
  if (((char*)pActwk)[53] < 0)
  {
    ++((char*)pActwk)[52];
    wD1 = ((char*)pActwk)[52];
    if (wD1 == 4)
    {
      ((char*)pActwk)[52] = 0;
      wD1 = 0;
    }

    pActwk->patno = patno_tbl[wD1];
    ((char*)pActwk)[53] = 10;
  }
}








static void ball_move(sprite_status* pActwk) {
  short subact;
  short wD1;
  int lD0;

  if (time_stop) goto label1;

  subact = ((short*)pActwk)[27];
  if (!(actwk[subact].actfree[20] & 16)) goto label1;

  if (!(pActwk->actfree[20] & 64))
  {
    pActwk->yspeed.w = -12288;
    pActwk->actfree[20] |= 64;
    goto label1;
  }

  pActwk->yspeed.w += 256;
  if (pActwk->yspeed.w >= 0)
  {
    wD1 = pActwk->yposi.w.h - ((short*)pActwk)[29];
    if ((unsigned short)wD1 <= 8)
    {
      pActwk->yposi.w.h = ((short*)pActwk)[29] + 4;
      subact = ((short*)pActwk)[27];
      actwk[subact].actfree[20] |= 8;
      pActwk->actfree[20] |= 8;
      actwk[subact].patno = 4;
      pActwk->yspeed.w = 0;
      goto label1;
    }
  }

  if (pActwk->yspeed.w == 0)
  {
    ++pActwk->patno;
    pActwk->colino = 164;
    pActwk->sprpri = 4;
    goto label1;
  }

  if (pActwk->yspeed.w == 57344)
    ++pActwk->patno;

label1:
  lD0 = pActwk->yspeed.w;
  lD0 <<= 6;
  pActwk->yposi.l += lD0;

}




static void dai_move(sprite_status* pActwk) {
  short subact;
  short wD1;
  unsigned char speed_tbl[5] =
  {
    0, 8, 16, 8, 0
  };
  short ofs_tbl[5] =
  {
    -44, -28, -12, 12, 28
  };

  if (time_stop) return;

  subact = ((short*)pActwk)[27];
  if (!(actwk[subact].actfree[20] & 16))
  {
    if (ride_on_chk(pActwk, &actwk[0]))
    {

      subact = ((short*)pActwk)[27];
      actwk[subact].actfree[20] |= 16;
    }
  }
  else
  {

    subact = ((short*)pActwk)[27];
    actwk[subact].actfree[20] |= 16;
  }

  subact = ((short*)pActwk)[27];
  wD1 = actwk[subact].patno;
  pActwk->yposi.w.h = ((short*)pActwk)[29] + ofs_tbl[wD1];

  subact = ((short*)pActwk)[27];
  wD1 = actwk[subact].patno;
  wD1 = speed_tbl[wD1];
  wD1 = (unsigned short)wD1 << 8;
  pActwk->yspeed.w = wD1;

  actwk[subact].actfree[20] &= 251;
  if (ride_on_chk(pActwk, &actwk[0]))
    actwk[subact].actfree[20] |= 4;
}
