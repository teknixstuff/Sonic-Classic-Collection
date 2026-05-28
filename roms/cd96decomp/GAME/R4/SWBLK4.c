#include "../EQU.h"
#include "SWBLK4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../RIDECHK.h"

static void switchr4_init(sprite_status* pActwk);
static void switchr4_move(sprite_status* pActwk);
static unsigned int switchr4_colichk(sprite_status* pActwk, sprite_status* pPlayerwk);
static void swblkr4_init(sprite_status* pActwk);
static void swblkr4_move(sprite_status* pActwk);

static sprite_pattern z4a_switchr4_pat0 = { 1, { { -16, -12, 0, 438 } } };
static sprite_pattern z43_switchr4_pat0 = { 1, { { -16, -12, 0, 472 } } };
static sprite_pattern z4a_switchr4_pat1 = { 1, { { -16, -4, 0, 439 } } };
static sprite_pattern z43_switchr4_pat1 = { 1, { { -16, -4, 0, 473 } } };
sprite_pattern* z4aswitchr4pat[2] = {
  &z4a_switchr4_pat0,
  &z4a_switchr4_pat1
};
sprite_pattern* z43switchr4pat[2] = {
  &z43_switchr4_pat0,
  &z43_switchr4_pat1
};
sprite_pattern** switchr4pats[3] = {
  z4aswitchr4pat,
  z4aswitchr4pat,
  z43switchr4pat
};
static void(*switchr4_jmp_tbl[2])(sprite_status*) = {
  &switchr4_init,
  &switchr4_move
};
static sprite_pattern z4a_swblkr4_pat0 = { 1, { { -32, -64, 0, 440 } } };
static sprite_pattern z43_swblkr4_pat0 = { 1, { { -32, -64, 0, 474 } } };
static sprite_pattern z4a_swblkr4_pat1 = { 1, { { -16, -64, 0, 441 } } };
static sprite_pattern z43_swblkr4_pat1 = { 1, { { -16, -64, 0, 475 } } };
static sprite_pattern z4a_swblkr4_pat2 = { 1, { { -16, -32, 0, 442 } } };
static sprite_pattern z43_swblkr4_pat2 = { 1, { { -16, -32, 0, 476 } } };
sprite_pattern* z4aswblkr4pat[3] = {
  &z4a_swblkr4_pat0,
  &z4a_swblkr4_pat1,
  &z4a_swblkr4_pat2
};
sprite_pattern* z43swblkr4pat[3] = {
  &z43_swblkr4_pat0,
  &z43_swblkr4_pat1,
  &z43_swblkr4_pat2
};
sprite_pattern** swblkr4pats[3] = {
  z4aswblkr4pat,
  z4aswblkr4pat,
  z43swblkr4pat
};
static void(*swblkr4_jmp_tbl[2])(sprite_status*) = {
  &swblkr4_init,
  &swblkr4_move
};

















































void switchr4(sprite_status* pActwk) {
  sprite_status* pRideact;
  short actidx;

  switchr4_jmp_tbl[pActwk->r_no0 / 2](pActwk);
  ride_on_chk(pActwk, &actwk[0]);
  if ((actidx = ((short*)pActwk)[28]) != 0) {
    pRideact = &actwk[actidx];
    pActwk->xposi.w.h = (short)(char)pActwk->actfree[14]
                      + pRideact->xposi.w.h;
    pActwk->yposi.w.h = (short)(char)pActwk->actfree[15]
                      + pRideact->yposi.w.h;
  }


  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}






static void switchr4_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 1290;
  pActwk->sprpri = 3;
  pActwk->patbase = switchr4pats[stageno_i.b.l];

  if (!((short*)pActwk)[29]) {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
  }


  pActwk->sprhsize = 14;
  pActwk->sprvsize = 5;

  switchr4_move(pActwk);
}





static void switchr4_move(sprite_status* pActwk) {
  if (switchr4_colichk(pActwk, &actwk[0]) != 0) {

    pActwk->userflag.b.h |= 1;
  } else {
    pActwk->userflag.b.h &= -2;
  }


  if (pActwk->userflag.b.h) {
    pActwk->patno = 1;
  } else {
    pActwk->patno = 0;
  }
}

















static unsigned int switchr4_colichk(sprite_status* pActwk, sprite_status* pPlayerwk) {
  short szwk;
  short poswk;

  szwk = (short)(char)pActwk->sprhsize + 8;
  poswk = szwk + (pPlayerwk->xposi.w.h - pActwk->xposi.w.h);
  if (poswk < 0 || poswk >= szwk * 2) {
    return 0;
  }


  poswk = (short)(char)pPlayerwk->sprvsize + pPlayerwk->yposi.w.h;
  szwk = pActwk->yposi.w.h - 16 - poswk;
  if (szwk > 0 || szwk < -16) {
    return 0;
  }

  return 1;
}








































void swblkr4(sprite_status* pActwk) {
  short actidx, xwk, hwk;
  sprite_status* pRideact;

  swblkr4_jmp_tbl[pActwk->r_no0 / 2](pActwk);
  ride_on_chk(pActwk, &actwk[0]);

  if (pActwk->actfree[18]) {
    if ((actidx = ((short*)pActwk)[28]) != 0) {
      pRideact = &actwk[actidx];
      if (pRideact->actno != 48) {

        frameout(pActwk);
        return;
      }

      pActwk->xposi.w.h = pRideact->xposi.w.h - 32;
      pActwk->yposi.w.h = pRideact->yposi.w.h + 32;
    }
  }


  actionsub(pActwk);

  xwk = ((short*)pActwk)[29] & -128;
  hwk = scra_h_posit.w.h - 128 & -128;
  if ((unsigned short)(xwk - hwk) > 640) {
    frameout(pActwk);
  }
}





static void swblkr4_init(sprite_status* pActwk) {
  sprite_status* pNewact;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->sprpri = 3;
  pActwk->patbase = swblkr4pats[stageno_i.b.l];

  if (!pActwk->actfree[18]) {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    ((short*)pActwk)[27] = pActwk->yposi.w.h;
    pActwk->xposi.w.h += 16;
    pActwk->sprhsize = 16;
    pActwk->sprvsize = 64;
    pActwk->patno = 1;

    if (actwkchk2(pActwk, &pNewact) != 0) {
      frameout(pActwk);
      return;
    }



    pNewact->actno = pActwk->actno;
    ((short*)pNewact)[29] = ((short*)pActwk)[29];

    ((short*)pNewact)[27] = ((short*)pActwk)[27];

    pNewact->sprhsize = 16;
    pNewact->sprvsize = 32;
    pNewact->actfree[18] = 1;
    pNewact->yposi.w.h = pActwk->yposi.w.h + 32;
    pNewact->xposi.w.h = pActwk->xposi.w.h - 32;
    ((short*)pNewact)[28] = pActwk - actwk;
    ((short*)pActwk)[28] = pNewact - actwk;
    pNewact->patno = 2;

    if (actwkchk2(pActwk, &pNewact) != 0) {
      frameout(pActwk);
      return;
    }



    pNewact->actno = 49;
    ((short*)pNewact)[28] = pActwk - actwk;
    ((short*)pActwk)[26] = pNewact - actwk;
    pNewact->actfree[15] = 188;
    ((short*)pNewact)[29] = ((short*)pActwk)[29];

    ((short*)pNewact)[27] = ((short*)pActwk)[27];
  }



  swblkr4_move(pActwk);
}





static void swblkr4_move(sprite_status* pActwk) {
  int ysv;
  sprite_status* pRideact;

  if (pActwk->actfree[18]) return;




  ysv = pActwk->yposi.l;

  if (pActwk->yspeed.w < 0) {

    pActwk->yposi.w.h -= 64;
    if (emycol_u(pActwk) < 0) {
      pActwk->yspeed.w = 0;
    }
  }
  else if (emycol_d(pActwk) < 0) {
    pActwk->yspeed.w = 0;
  }



  pActwk->yposi.l = ysv;
  pActwk->yposi.l += pActwk->yspeed.w << 8;
  pRideact = &actwk[((short*)pActwk)[28]];





  if (pRideact->actno == 48) {
    pRideact->yspeed.w = pActwk->yspeed.w;
  }


  pRideact = &actwk[((short*)pActwk)[26]];





  if (pRideact->actno != 49) return;



  if (pRideact->userflag.b.h & 3) {


    if ((pActwk->yspeed.w -= 8) < -256) {
      pActwk->yspeed.w = -256;
    }
  }
  else {
    if ((pActwk->yspeed.w += 8) > 256) {
      pActwk->yspeed.w = 256;
    }
  }
}
