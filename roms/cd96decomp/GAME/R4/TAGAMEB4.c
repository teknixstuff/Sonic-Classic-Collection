#include "../EQU.h"
#include "TAGAMEB4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void tagameb0(sprite_status* pActwk);
static void a_init(sprite_status* pActwk);
static void make_toge(sprite_status* pActwk);
static void a_init_sub(short subact, sprite_status* pActwk);
static void a_move(sprite_status* pActwk);
static int a_check(sprite_status* pActwk);
static void a_stop(sprite_status* pActwk);
static void a_stop1(sprite_status* pActwk);
static void a_dash(sprite_status* pActwk);
static void tagameb1(sprite_status* pActwk);
static void b_init(sprite_status* pActwk);
static void b_follow(sprite_status* pActwk);
static void b_move(sprite_status* pActwk);

static unsigned char pchg0[4] = { 30, 0, 1, 255 };
static unsigned char* pchg[1] = { pchg0 };
static sprite_pattern z41a_spr_tagame_b_00 = { 1, { { -20, -12, 0, 485 } } };
static sprite_pattern z41b_spr_tagame_b_00 = { 1, { { -20, -12, 0, 446 } } };
static sprite_pattern z41c_spr_tagame_b_00 = { 1, { { -20, -12, 0, 463 } } };
static sprite_pattern z41d_spr_tagame_b_00 = { 1, { { -20, -12, 0, 453 } } };
static sprite_pattern z42a_spr_tagame_b_00 = { 1, { { -20, -12, 0, 491 } } };
static sprite_pattern z42b_spr_tagame_b_00 = { 1, { { -20, -12, 0, 444 } } };
static sprite_pattern z42c_spr_tagame_b_00 = { 1, { { -20, -12, 0, 448 } } };
static sprite_pattern z41a_spr_tagame_b_01 = { 1, { { -20, -12, 0, 486 } } };
static sprite_pattern z41b_spr_tagame_b_01 = { 1, { { -20, -12, 0, 447 } } };
static sprite_pattern z41c_spr_tagame_b_01 = { 1, { { -20, -12, 0, 464 } } };
static sprite_pattern z41d_spr_tagame_b_01 = { 1, { { -20, -12, 0, 454 } } };
static sprite_pattern z42a_spr_tagame_b_01 = { 1, { { -20, -12, 0, 492 } } };
static sprite_pattern z42b_spr_tagame_b_01 = { 1, { { -20, -12, 0, 445 } } };
static sprite_pattern z42c_spr_tagame_b_01 = { 1, { { -20, -12, 0, 449 } } };
static sprite_pattern z41a_spr_tagame_e_00 = { 1, { { -20, -12, 0, 487 } } };
static sprite_pattern z41b_spr_tagame_e_00 = { 1, { { -20, -12, 0, 448 } } };
static sprite_pattern z41c_spr_tagame_e_00 = { 1, { { -20, -12, 0, 465 } } };
static sprite_pattern z41d_spr_tagame_e_00 = { 1, { { -20, -12, 0, 455 } } };
static sprite_pattern z42a_spr_tagame_e_00 = { 1, { { -20, -12, 0, 493 } } };
static sprite_pattern z42b_spr_tagame_e_00 = { 1, { { -20, -12, 0, 446 } } };
static sprite_pattern z42c_spr_tagame_e_00 = { 1, { { -20, -12, 0, 450 } } };
static sprite_pattern z41a_spr_tagame_e_01 = { 1, { { -20, -12, 0, 488 } } };
static sprite_pattern z41b_spr_tagame_e_01 = { 1, { { -20, -12, 0, 449 } } };
static sprite_pattern z41c_spr_tagame_e_01 = { 1, { { -20, -12, 0, 466 } } };
static sprite_pattern z41d_spr_tagame_e_01 = { 1, { { -20, -12, 0, 456 } } };
static sprite_pattern z42a_spr_tagame_e_01 = { 1, { { -20, -12, 0, 494 } } };
static sprite_pattern z42b_spr_tagame_e_01 = { 1, { { -20, -12, 0, 447 } } };
static sprite_pattern z42c_spr_tagame_e_01 = { 1, { { -20, -12, 0, 451 } } };
static sprite_pattern z41a_spr_tagame_99 = { 1, { { 0, 0, 0, 489 } } };
static sprite_pattern z41b_spr_tagame_99 = { 1, { { 0, 0, 0, 450 } } };
static sprite_pattern z41c_spr_tagame_99 = { 1, { { 0, 0, 0, 467 } } };
static sprite_pattern z41d_spr_tagame_99 = { 1, { { 0, 0, 0, 457 } } };
static sprite_pattern z42a_spr_tagame_99 = { 1, { { 0, 0, 0, 495 } } };
static sprite_pattern z42b_spr_tagame_99 = { 1, { { 0, 0, 0, 448 } } };
static sprite_pattern z42c_spr_tagame_99 = { 1, { { 0, 0, 0, 452 } } };
sprite_pattern* z41a_pat_tagameb_b[2] =
{
  &z41a_spr_tagame_b_00,
  &z41a_spr_tagame_b_01
};
sprite_pattern* z41b_pat_tagameb_b[2] =
{
  &z41b_spr_tagame_b_00,
  &z41b_spr_tagame_b_01
};
sprite_pattern* z41c_pat_tagameb_b[2] =
{
  &z41c_spr_tagame_b_00,
  &z41c_spr_tagame_b_01
};
sprite_pattern* z41d_pat_tagameb_b[2] =
{
  &z41d_spr_tagame_b_00,
  &z41d_spr_tagame_b_01
};
sprite_pattern* z42a_pat_tagameb_b[2] =
{
  &z42a_spr_tagame_b_00,
  &z42a_spr_tagame_b_01
};
sprite_pattern* z42b_pat_tagameb_b[2] =
{
  &z42b_spr_tagame_b_00,
  &z42b_spr_tagame_b_01
};
sprite_pattern* z42c_pat_tagameb_b[2] =
{
  &z42c_spr_tagame_b_00,
  &z42c_spr_tagame_b_01
};
sprite_pattern** pats_tagameb_b[2][4] =
{
  { z41b_pat_tagameb_b, z41a_pat_tagameb_b, z41d_pat_tagameb_b, z41c_pat_tagameb_b },
  { z42b_pat_tagameb_b, z42a_pat_tagameb_b, z42c_pat_tagameb_b, z42c_pat_tagameb_b }
};
sprite_pattern* z41a_pat_tagameb_e[2] =
{
  &z41a_spr_tagame_e_00,
  &z41a_spr_tagame_e_01
};
sprite_pattern* z41b_pat_tagameb_e[2] =
{
  &z41b_spr_tagame_e_00,
  &z41b_spr_tagame_e_01
};
sprite_pattern* z41c_pat_tagameb_e[2] =
{
  &z41c_spr_tagame_e_00,
  &z41c_spr_tagame_e_01
};
sprite_pattern* z41d_pat_tagameb_e[2] =
{
  &z41d_spr_tagame_e_00,
  &z41d_spr_tagame_e_01
};
sprite_pattern* z42a_pat_tagameb_e[2] =
{
  &z42a_spr_tagame_e_00,
  &z42a_spr_tagame_e_01
};
sprite_pattern* z42b_pat_tagameb_e[2] =
{
  &z42b_spr_tagame_e_00,
  &z42b_spr_tagame_e_01
};
sprite_pattern* z42c_pat_tagameb_e[2] =
{
  &z42c_spr_tagame_e_00,
  &z42c_spr_tagame_e_01
};
sprite_pattern** pats_tagameb_e[2][4] =
{
  { z41b_pat_tagameb_e, z41a_pat_tagameb_e, z41d_pat_tagameb_e, z41c_pat_tagameb_e },
  { z42b_pat_tagameb_e, z42a_pat_tagameb_e, z42c_pat_tagameb_e, z42c_pat_tagameb_e }
};
static sprite_pattern* z41apat[1] = { &z41a_spr_tagame_99 };
static sprite_pattern* z41bpat[1] = { &z41b_spr_tagame_99 };
static sprite_pattern* z41cpat[1] = { &z41c_spr_tagame_99 };
static sprite_pattern* z41dpat[1] = { &z41d_spr_tagame_99 };
static sprite_pattern* z42apat[1] = { &z42a_spr_tagame_99 };
static sprite_pattern* z42bpat[1] = { &z42b_spr_tagame_99 };
static sprite_pattern* z42cpat[1] = { &z42c_spr_tagame_99 };
static sprite_pattern** pats[2][4] =
{
  { z41bpat, z41apat, z41dpat, z41cpat },
  { z42bpat, z42apat, z42cpat, z42cpat }
};






















void tagameb(sprite_status* pActwk) {
  if (pActwk->userflag.b.h >= 0)
    tagameb0(pActwk);
  else
    tagameb1(pActwk);
}




static void tagameb0(sprite_status* pActwk) {
  static void(*tbl[5])(sprite_status*) =
  {
    &a_init,
    &a_move,
    &a_stop,
    &a_stop1,
    &a_dash
  };

  if (enemy_suicide(pActwk)) return;
  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s(pActwk);
}



static void a_init(sprite_status* pActwk) {
  ((short*)pActwk)[30] = pActwk->xposi.w.h;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sproffset = 9168;
  pActwk->sprhs = 20;
  pActwk->sprhsize = 20;
  pActwk->sprvsize = 8;
  pActwk->colino = 45;
  pActwk->r_no0 += 2;

  if (!pActwk->userflag.b.h)
  {
    pActwk->patbase = pats_tagameb_e[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
    ((int*)pActwk)[12] = -65536;
    ((short*)pActwk)[29] = 200;
  }
  else
  {
    pActwk->patbase = pats_tagameb_b[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
    ((int*)pActwk)[12] = -32768;
    ((short*)pActwk)[29] = 400;
    return;
  }
  make_toge(pActwk);
}


static void make_toge(sprite_status* pActwk) {
  sprite_status* subActwk;

  if (actwkchk(&subActwk) == 0)
  {
    subActwk->actno = pActwk->actno;
    subActwk->userflag.b.h = -1;
    subActwk->actfree[19] = pActwk->cdsts;
    ((short*)subActwk)[33] = (unsigned short)(unsigned char)(pActwk - actwk);
    ((short*)pActwk)[26] = (unsigned short)(unsigned char)(subActwk - actwk);
  }
  else
  {
    frameout(pActwk);
    return;
  }
  if (actwkchk(&subActwk) == 0)
  {
    subActwk->actno = pActwk->actno;
    subActwk->userflag.b.h = -1;
    subActwk->actfree[19] = pActwk->cdsts;
    ((short*)subActwk)[33] = (unsigned short)(unsigned char)(pActwk - actwk);
    ((short*)pActwk)[27] = (unsigned short)(unsigned char)(subActwk - actwk);
  }
  else
  {
    frameout(pActwk);
    return;
  }
  if (actwkchk(&subActwk) == 0)
  {
    subActwk->actno = pActwk->actno;
    subActwk->userflag.b.h = -1;
    subActwk->actfree[19] = pActwk->cdsts;
    ((short*)subActwk)[33] = (unsigned short)(unsigned char)(pActwk - actwk);
    ((short*)pActwk)[28] = (unsigned short)(unsigned char)(subActwk - actwk);
  }
  else
  {
    frameout(pActwk);
    return;
  }

  a_init_sub(((short*)pActwk)[26], pActwk);
  actwk[((short*)pActwk)[26]].xposi.w.h += 2;
  actwk[((short*)pActwk)[26]].yposi.w.h -= 10;
  a_init_sub(((short*)pActwk)[27], pActwk);
  actwk[((short*)pActwk)[27]].xposi.w.h -= 3;
  actwk[((short*)pActwk)[27]].yposi.w.h -= 10;
  a_init_sub(((short*)pActwk)[28], pActwk);
  actwk[((short*)pActwk)[28]].xposi.w.h -= 7;
  actwk[((short*)pActwk)[28]].yposi.w.h -= 9;
}


static void a_init_sub(short subact, sprite_status* pActwk) {
  actwk[subact].xposi.w.h = pActwk->xposi.w.h;
  actwk[subact].yposi.w.h = pActwk->yposi.w.h;
  actwk[subact].actflg |= 4;
  actwk[subact].sproffset = 9168;
  actwk[subact].sprpri = 3;
  actwk[subact].sprhs = 2;
  actwk[subact].sprhsize = 2;
  actwk[subact].sprvsize = 2;
}



static void a_move(sprite_status* pActwk) {
  if (!pActwk->userflag.b.h)
  {
    if (a_check(pActwk) != 0)
    {

      pActwk->r_no0 += 2;
      ((short*)pActwk)[23] = 60;
      return;
    }
  }

  pActwk->xposi.l += ((int*)pActwk)[12];

  if (!pActwk->userflag.b.h)
  {
    actwk[((short*)pActwk)[26]].xposi.l += ((int*)pActwk)[12];
    actwk[((short*)pActwk)[27]].xposi.l += ((int*)pActwk)[12];
    actwk[((short*)pActwk)[28]].xposi.l += ((int*)pActwk)[12];
  }

  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] < 0)
  {
    ((short*)pActwk)[23] = ((short*)pActwk)[29];
    ((int*)pActwk)[12] *= -1;
    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;

    if (!pActwk->userflag.b.h)
    {
      actwk[((short*)pActwk)[26]].xposi.w.h = pActwk->xposi.w.h;
      actwk[((short*)pActwk)[27]].xposi.w.h = pActwk->xposi.w.h;
      actwk[((short*)pActwk)[28]].xposi.w.h = pActwk->xposi.w.h;
      if (!(pActwk->actflg & 1))
      {
        actwk[((short*)pActwk)[26]].xposi.w.h -= 2;
        actwk[((short*)pActwk)[27]].xposi.w.h += 3;
        actwk[((short*)pActwk)[28]].xposi.w.h += 7;
      }
      else
      {
        actwk[((short*)pActwk)[26]].xposi.w.h -= 1;
        actwk[((short*)pActwk)[27]].xposi.w.h -= 6;
        actwk[((short*)pActwk)[28]].xposi.w.h -= 10;
      }
    }
  }

  patchg(pActwk, pchg);
}


static int a_check(sprite_status* pActwk) {
  short wD0;
  int ret;



  ret = 0;

  wD0 = actwk[0].yposi.w.h - pActwk->yposi.w.h;
  if (wD0 < 0)
  {
    wD0 = actwk[0].xposi.w.h - pActwk->xposi.w.h;
    if (!(pActwk->actflg & 1))
      wD0 *= -1;
    wD0 += 80;
    if (wD0 >= 0)
      ret = -1;
  }
  return ret;
}



static void a_stop(sprite_status* pActwk) {
  short subact;

  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] < 0)
  {
    if ((char)pActwk->actflg < 0)
      soundset(179);


    ((short*)pActwk)[23] = 60;
    pActwk->r_no0 += 2;

    if (!pActwk->userflag.b.h)
    {
      subact = ((short*)pActwk)[26];
      *(int*)&actwk[subact].actfree[0] = -0x20000;
      *(int*)&actwk[subact].actfree[4] = -196608;
      *(int*)&actwk[subact].actfree[8] = 0;
      *(int*)&actwk[subact].actfree[12] = 8192;
      actwk[subact].r_no0 += 2;
      subact = ((short*)pActwk)[27];
      *(int*)&actwk[subact].actfree[0] = 65536;
      *(int*)&actwk[subact].actfree[4] = -196608;
      *(int*)&actwk[subact].actfree[8] = 0;
      *(int*)&actwk[subact].actfree[12] = 8192;
      actwk[subact].r_no0 += 2;
      subact = ((short*)pActwk)[28];
      *(int*)&actwk[subact].actfree[0] = 0x20000;
      *(int*)&actwk[subact].actfree[4] = -196608;
      *(int*)&actwk[subact].actfree[8] = 0;
      *(int*)&actwk[subact].actfree[12] = 8192;
      actwk[subact].r_no0 += 2;
    }
  }
}



static void a_stop1(sprite_status* pActwk) {
  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] < 0)
  {
    pActwk->r_no0 += 2;

    if (!pActwk->userflag.b.h)
      ((int*)pActwk)[12] = 0x40000;
    else
      ((int*)pActwk)[12] = 98304;

    if (!(pActwk->actflg & 1))
      ((int*)pActwk)[12] *= -1;
  }

}



static void a_dash(sprite_status* pActwk) {
  pActwk->xposi.l += ((int*)pActwk)[12];
}















static void tagameb1(sprite_status* pActwk) {
  short subact;
  static void(*tbl[3])(sprite_status*) =
  {
    &b_init,
    &b_follow,
    &b_move
  };

  subact = ((short*)pActwk)[33];
  if (actwk[subact].actno != 45)
  {
    frameout(pActwk);
    return;
  }
  if (pActwk->actfree[19] != actwk[subact].cdsts)
  {
    frameout(pActwk);
    return;
  }
  tbl[pActwk->r_no0 / 2](pActwk);
}



static void b_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->patbase = pats[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  b_follow(pActwk);
}



static void b_follow(sprite_status* pActwk) {
  actionsub(pActwk);
}



static void b_move(sprite_status* pActwk) {
  pActwk->xposi.l += *(int*)&pActwk->actfree[0];
  pActwk->yposi.l += *(int*)&pActwk->actfree[4];
  *(int*)&pActwk->actfree[0] += *(int*)&pActwk->actfree[8];
  *(int*)&pActwk->actfree[4] += *(int*)&pActwk->actfree[12];

  if (pActwk->yposi.w.h - actwk[0].yposi.w.h > 224)
  {
    frameout(pActwk);
    return;
  }
  actionsub(pActwk);
}
