#include "../EQU.h"
#include "RBLK4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../FCOL.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

static void rblk4_init(sprite_status* pActwk);
static void rblk4_wait(sprite_status* pActwk);
static void rblk4_move(sprite_status* pActwk);
static void rblk4_push(sprite_status* pActwk);
static void rblk4_ract_init(sprite_status* pActwk);
static void rblk4_ract_move(sprite_status* pActwk);

static sprite_pattern z41bpat00 = { 2, { { -8, -8, 0, 506 }, { -48, -48, 0, 507 } } };
static sprite_pattern z42bpat00 = { 2, { { -8, -8, 0, 494 }, { -48, -48, 0, 495 } } };
static sprite_pattern z41bpat01 = { 2, { { -8, -8, 0, 508 }, { -48, -16, 0, 509 } } };
static sprite_pattern z42bpat01 = { 2, { { -8, -8, 0, 496 }, { -48, -16, 0, 497 } } };
static sprite_pattern z41bpat02 = { 2, { { -8, -8, 0, 510 }, { -16, -16, 0, 511 } } };
static sprite_pattern z42bpat02 = { 2, { { -8, -8, 0, 498 }, { -16, -16, 0, 499 } } };
static sprite_pattern z41bpat03 = { 2, { { -8, -8, 0, 512 }, { -16, -48, 0, 513 } } };
static sprite_pattern z42bpat03 = { 2, { { -8, -8, 0, 500 }, { -16, -48, 0, 501 } } };
static sprite_pattern z41bpat04 = { 2, { { -8, -8, 0, 514 }, { -48, -48, 0, 515 } } };
static sprite_pattern z42bpat04 = { 2, { { -8, -8, 0, 502 }, { -48, -48, 0, 503 } } };
static sprite_pattern z41bpat05 = { 2, { { -8, -8, 0, 516 }, { -48, -24, 0, 517 } } };
static sprite_pattern z42bpat05 = { 2, { { -8, -8, 0, 504 }, { -48, -24, 0, 505 } } };
static sprite_pattern z41bpat06 = { 2, { { -8, -8, 0, 518 }, { -24, -48, 0, 519 } } };
static sprite_pattern z42bpat06 = { 2, { { -8, -8, 0, 506 }, { -24, -48, 0, 507 } } };
static sprite_pattern z41bpat07 = { 2, { { -8, -8, 0, 520 }, { -48, -48, 0, 521 } } };
static sprite_pattern z42bpat07 = { 2, { { -8, -8, 0, 508 }, { -48, -48, 0, 509 } } };
static sprite_pattern z41bpat08 = { 1, { { -32, -32, 0, 522 } } };
static sprite_pattern z42bpat08 = { 1, { { -32, -32, 0, 510 } } };
sprite_pattern* z41brblk4pat[9] =
{
  &z41bpat00,
  &z41bpat01,
  &z41bpat02,
  &z41bpat03,
  &z41bpat04,
  &z41bpat05,
  &z41bpat06,
  &z41bpat07,
  &z41bpat08
};
sprite_pattern* z42brblk4pat[9] =
{
  &z42bpat00,
  &z42bpat01,
  &z42bpat02,
  &z42bpat03,
  &z42bpat04,
  &z42bpat05,
  &z42bpat06,
  &z42bpat07,
  &z42bpat08
};
sprite_pattern** rblk4pats[2] =
{
  z41brblk4pat,
  z42brblk4pat
};























































































void rblk4(sprite_status* pActwk) {
  void(*tbl[4])(sprite_status*) =
  {
    &rblk4_init,
    &rblk4_wait,
    &rblk4_move,
    &rblk4_push
  };

  if (pActwk->actfree[18] == 255)
  {
    rblk4_ract(pActwk);
  }
  else
  {
    tbl[pActwk->r_no0 / 2](pActwk);
    actionsub(pActwk);
    frameout_s(pActwk);
  }
}




static void rblk4_init(sprite_status* pActwk) {
  sprite_status* pNewActwk;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->patbase = rblk4pats[stageno_i.b.l];
  pActwk->sproffset = 17152;
  pActwk->sprvsize = 64;
  pActwk->sprhsize = 64;

  pActwk->patno = pActwk->userflag.b.h & 3;
  pActwk->actfree[19] = pActwk->patno;

  if (actwkchk(&pNewActwk) != 0)
  {
    frameout_s0(pActwk);
    return;
  }
  pNewActwk->actno = 61;
  ((short*)pNewActwk)[29] = pActwk->xposi.w.h;
  ((short*)pNewActwk)[28] = (unsigned short)(pActwk - actwk);
  pNewActwk->actfree[18] = 255;
  pNewActwk->actfree[19] = 0;
  ((short*)pActwk)[26] = (unsigned short)(pNewActwk - actwk);

  if (actwkchk(&pNewActwk) != 0)
  {
    frameout_s0(pActwk);
    return;
  }
  pNewActwk->actno = 61;
  ((short*)pNewActwk)[29] = pActwk->xposi.w.h;
  ((short*)pNewActwk)[28] = (unsigned short)(pActwk - actwk);
  pNewActwk->actfree[18] = 255;
  pNewActwk->actfree[19] = 1;
  ((short*)pActwk)[28] = (unsigned short)(pNewActwk - actwk);
}




static void rblk4_wait(sprite_status* pActwk) {
  sprite_status* pActwk_y;
  sprite_status* pPlayerwk;
  char* a4;
  short d0;
  short d1;
  unsigned char d3;

  pActwk_y = &actwk[((short*)pActwk)[26]];
  if (!(pActwk_y->actfree[20] & 128)) return;

  pPlayerwk = &actwk[0];
  if (pActwk->actfree[19] < 2)
  {
    d0 = pActwk->xposi.w.h;
    d1 = pPlayerwk->xposi.w.h + (short)(pPlayerwk->sprhsize + 2);
  }
  else
  {
    d1 = pActwk->xposi.w.h;
    d0 = pPlayerwk->xposi.w.h + (short)-((char)pPlayerwk->sprhsize + 2);
  }
  if (d0 < d1) return;
  d0 -= d1;


  a4 = dirstk;
  *a4 = 0;
  scdchk(pActwk, pActwk->yposi.w.h + d0, pActwk->xposi.w.h, 16, 0, 13, a4);

  d3 = dirstk[0];
  if (d3 & 1) d3 = 0;

  if (d1 >= 0)
  {
    if (d1 >= 16)
    {
      pActwk->r_no0 += 2;
      pActwk->actfree[16] = 16;
      pActwk->actfree[17] = 0;
      return;
    }
  }
  pPlayerwk = &actwk[((short*)pActwk)[28]];
  if (pPlayerwk->actfree[20])
  {
    pActwk->r_no0 = 6;
    pActwk->actfree[16] = 16;
    pActwk->actfree[17] = 0;
  }
}




static void rblk4_move(sprite_status* pActwk) {
  unsigned char d0;
  unsigned char rkpchg0[16] =
  {
    0, 4, 1, 255,
    1, 5, 2, 255,
    2, 5, 1, 255,
    3, 6, 2, 255
  };

  d0 = pActwk->actfree[19];
  d0 *= 4;
  d0 = d0 + pActwk->actfree[17];
  d0 = rkpchg0[d0];
  if (d0 & 128)
  {
    pActwk->actfree[19] = pActwk->patno;
    pActwk->r_no0 -= 2;
    return;
  }
  pActwk->patno = d0;
  --pActwk->actfree[16];
  if (pActwk->actfree[16]) return;



  soundset(191);
  pActwk->actfree[16] = 4;
  ++pActwk->actfree[17];
}




static void rblk4_push(sprite_status* pActwk) {
  sprite_status* pPlayerwk;
  short sd0, sd1;
  unsigned char d0;
  unsigned char pspchg0[16] =
  {
    0, 7, 3, 255,
    1, 4, 2, 255,
    2, 4, 1, 255,
    3, 7, 0, 255
  };

  d0 = pActwk->actfree[19];
  d0 *= 4;
  d0 = d0 + pActwk->actfree[17];
  d0 = pspchg0[d0];
  if (d0 & 128)
  {
    pActwk->actfree[19] = pActwk->patno;
    pActwk->r_no0 = 2;
    return;
  }
  pActwk->patno = d0;

  pPlayerwk = &actwk[0];
  sd0 = pActwk->yposi.w.h;
  sd1 = pActwk->sprvsize;
  sd0 -= sd1;
  sd1 = pPlayerwk->sprvsize;
  sd0 -= sd1;
  pPlayerwk->yposi.w.h = sd0;

  --pActwk->actfree[16];
  if (pActwk->actfree[16]) return;




  pActwk->actfree[16] = 8;
  ++pActwk->actfree[17];
  if (pActwk->actfree[17] == 1)
  {
    pPlayerwk->xposi.w.h = pActwk->xposi.w.h;
    return;
  }
  if (pActwk->actfree[17] == 2)
  {
    sd0 = 16;
    if (pActwk->actfree[19] & 2)
    {
      sd0 *= -1;
    }
    sd0 += pActwk->xposi.w.h;
    pPlayerwk->xposi.w.h = sd0;
  }
}




void rblk4_ract(sprite_status* pActwk) {
  void(*tbl[2])(sprite_status*) =
  {
    &rblk4_ract_init,
    &rblk4_ract_move
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}




static void rblk4_ract_init(sprite_status* pActwk) {
  unsigned char d0, d1;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->patbase = rblk4pats[stageno_i.b.l];
  pActwk->sproffset = 17152;
  pActwk->patno = 8;

  d0 = 32;
  d1 = 16;
  if (pActwk->actfree[19])
  {
    d0 = 16;
    d1 = 16;
  }
  pActwk->sprhsize = d0;
  pActwk->sprvsize = d1;

  rblk4_ract_move(pActwk);
}




static void rblk4_ract_move(sprite_status* pActwk) {
  sprite_status* pRideact;
  char* a2;
  unsigned char d0;
  char xyofset_tbl1[8] =
  {
    -16, 0,
    -16, 0,
     16, 0,
     16, 0
  };
  char xyofset_tbl2[8] =
  {
    0, -32,
    0,  32,
    0,  32,
    0, -32
  };

  pRideact = &actwk[((short*)pActwk)[28]];
  d0 = pRideact->patno;
  if (d0 >= 4)
  {
    ride_on_clr(pActwk, &actwk[0]);
    return;
  }
  d0 = d0 + d0;
  a2 = &xyofset_tbl1[d0];
  if (pActwk->actfree[19])
  {
    a2 = &xyofset_tbl2[d0];
  }
  pActwk->xposi.w.h = pRideact->xposi.w.h + (short)*a2++;
  pActwk->yposi.w.h = pRideact->yposi.w.h + (short)*a2++;

  hitchk(pActwk, &actwk[0]);
  if (pActwk->actfree[19] == 0)
  {
    if (pActwk->cddat & 8) pActwk->actfree[20] = 255;
    else pActwk->actfree[20] = 0;
  }
  else
  {
    if (!(pActwk->cddat & 32))
    {
      pActwk->actfree[20] = 0;
      pActwk->actfree[21] = 0;
      return;
    }
    if (pActwk->actfree[21] == 0)
    {
      pActwk->actfree[20] = 255;
      pActwk->actfree[21] = 255;
      pActwk->cddat &= 223;
    }
  }
}
