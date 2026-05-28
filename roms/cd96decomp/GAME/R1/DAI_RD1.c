#include "../EQU.h"
#include "DAI_RD1.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../DUMMY.h"
#include "../ETC.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

static void dodai_init(sprite_status* pActwk);
static void dodai_move(sprite_status* pActwk);
static void dodai_ud(sprite_status* pActwk);
static void dodai_lr(sprite_status* pActwk);
static unsigned char dodai_ride1(sprite_status* pActwk, int xpos);
static unsigned char dodai_ride2(sprite_status* pActwk);
static void dodai_nA(sprite_status* pActwk);
static void dodai_nB(sprite_status* pActwk);
static unsigned char dodai_fix(sprite_status* pActwk);
static void dodai_fal(sprite_status* pActwk);
static void dodai_up(sprite_status* pActwk);
static void dodai_upx(sprite_status* pActwk);
static void dodai_rm(sprite_status* pActwk);
static void dodai_lm(sprite_status* pActwk);
static short dodai_sub(sprite_status* pActwk);
static void dai_fout(sprite_status* pActwk);
static void vfuta_init(sprite_status* pActwk);
static void vfuta_move1(sprite_status* pActwk);
static void vfuta_move2(sprite_status* pActwk);

static sprite_pattern dai11a_pat1 = { 1, { { -16, -16, 0, 533 } } };
static sprite_pattern dai11b_pat1 = { 1, { { -16, -16, 0, 518 } } };
static sprite_pattern dai11c_pat1 = { 1, { { -16, -16, 0, 499 } } };
static sprite_pattern dai12a_pat1 = { 1, { { -16, -16, 0, 509 } } };
static sprite_pattern dai12c_pat1 = { 1, { { -16, -16, 0, 500 } } };
static sprite_pattern dai13c_pat1 = { 1, { { -16, -16, 0, 488 } } };
static sprite_pattern dai11a_pat2 = { 1, { { -32, -16, 0, 534 } } };
static sprite_pattern dai11b_pat2 = { 1, { { -32, -16, 0, 519 } } };
static sprite_pattern dai11c_pat2 = { 1, { { -32, -16, 0, 500 } } };
static sprite_pattern dai12a_pat2 = { 1, { { -32, -16, 0, 510 } } };
static sprite_pattern dai12c_pat2 = { 1, { { -32, -16, 0, 501 } } };
static sprite_pattern dai13c_pat2 = { 1, { { -32, -16, 0, 489 } } };
static sprite_pattern dai11a_pat3 = { 1, { { -48, -16, 0, 535 } } };
static sprite_pattern dai11b_pat3 = { 1, { { -48, -16, 0, 520 } } };
static sprite_pattern dai11c_pat3 = { 1, { { -48, -16, 0, 501 } } };
static sprite_pattern dai12a_pat3 = { 1, { { -48, -16, 0, 511 } } };
static sprite_pattern dai12c_pat3 = { 1, { { -48, -16, 0, 502 } } };
static sprite_pattern dai13c_pat3 = { 1, { { -48, -16, 0, 490 } } };
sprite_pattern* dai11a_pattbl[3] = {
  &dai11a_pat1,
  &dai11a_pat2,
  &dai11a_pat3
};
sprite_pattern* dai11b_pattbl[3] = {
  &dai11b_pat1,
  &dai11b_pat2,
  &dai11b_pat3
};
sprite_pattern* dai11c_pattbl[3] = {
  &dai11c_pat1,
  &dai11c_pat2,
  &dai11c_pat3
};
sprite_pattern* dai12a_pattbl[3] = {
  &dai12a_pat1,
  &dai12a_pat2,
  &dai12a_pat3
};
sprite_pattern* dai12c_pattbl[3] = {
  &dai12c_pat1,
  &dai12c_pat2,
  &dai12c_pat3
};
sprite_pattern* dai13c_pattbl[3] = {
  &dai13c_pat1,
  &dai13c_pat2,
  &dai13c_pat3
};
sprite_pattern** dai1_pattbls[3][3] = {
  { dai11b_pattbl, dai11a_pattbl, dai11c_pattbl },
  { dai12a_pattbl, dai12a_pattbl, dai12c_pattbl },
  { 0, 0, dai13c_pattbl }
};
static void(*dodai_acttbl[2])(sprite_status*) = {
  &dodai_init,
  &dodai_move
};
static void(*dodai_mtype[10])(sprite_status*) = {
  &dodai_ud,
  &dodai_lr,
  &dodai_nA,
  &dodai_nB,
  (void(*)(sprite_status*))&dodai_fix,
  &dodai_fal,
  &dodai_up,
  &dodai_upx,
  &dodai_rm,
  &dodai_lm
};
static sprite_pattern z11a_vfuta_pat0 = { 1, { { -4, -24, 0, 548 } } };
static sprite_pattern z11b_vfuta_pat0 = { 1, { { -4, -24, 0, 533 } } };
static sprite_pattern z11c_vfuta_pat0 = { 1, { { -4, -24, 0, 514 } } };
static sprite_pattern z12a_vfuta_pat0 = { 1, { { -4, -24, 0, 527 } } };
static sprite_pattern z12c_vfuta_pat0 = { 1, { { -4, -24, 0, 518 } } };
static sprite_pattern z13_vfuta_pat0 = { 1, { { -4, -24, 0, 524 } } };
static sprite_pattern z11a_vfuta_pat1 = { 1, { { -4, -24, 0, 549 } } };
static sprite_pattern z11b_vfuta_pat1 = { 1, { { -4, -24, 0, 534 } } };
static sprite_pattern z11c_vfuta_pat1 = { 1, { { -4, -24, 0, 515 } } };
static sprite_pattern z12a_vfuta_pat1 = { 1, { { -4, -24, 0, 528 } } };
static sprite_pattern z12c_vfuta_pat1 = { 1, { { -4, -24, 0, 519 } } };
static sprite_pattern z13_vfuta_pat1 = { 1, { { -4, -24, 0, 525 } } };
sprite_pattern* z11a_vfutapat[2] = {
  &z11a_vfuta_pat0,
  &z11a_vfuta_pat1
};
sprite_pattern* z11b_vfutapat[2] = {
  &z11b_vfuta_pat0,
  &z11b_vfuta_pat1
};
sprite_pattern* z11c_vfutapat[2] = {
  &z11c_vfuta_pat0,
  &z11c_vfuta_pat1
};
sprite_pattern* z12a_vfutapat[2] = {
  &z12a_vfuta_pat0,
  &z12a_vfuta_pat1
};
sprite_pattern* z12c_vfutapat[2] = {
  &z12c_vfuta_pat0,
  &z12c_vfuta_pat1
};
sprite_pattern* z13_vfutapat[2] = {
  &z13_vfuta_pat0,
  &z13_vfuta_pat1
};
sprite_pattern** vfutapats[3][3] = {
  { z11b_vfutapat, z11a_vfutapat, z11c_vfutapat },
  { z12a_vfutapat, z12a_vfutapat, z12c_vfutapat },
  { 0, 0, z13_vfutapat }
};
static void(*vfuta_tbl[3])(sprite_status*) = {
  &vfuta_init,
  &vfuta_move1,
  &vfuta_move2
};



void dodai(sprite_status* pActwk) {
  dodai_acttbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
}





static void dodai_init(sprite_status* pActwk) {
  char wk;
  sprite_status* pNewact;
  static unsigned char dai_mcnttbl[4] = { 0, 3, 4, 6 };
  static unsigned char dai_hstbl[3] = { 16, 32, 48 };




  pActwk->actflg |= 4;
  pActwk->sproffset = 17598;
  pActwk->sprpri = 2;


  ((short*)pActwk)[30] = pActwk->xposi.w.h;
  ((short*)pActwk)[31] = pActwk->yposi.w.h;
  ((short*)pActwk)[29] = pActwk->yposi.w.h;

  pActwk->patbase = dai1_pattbls[stageno_i.b.l][time_flag_i & 0x7F];
  wk = pActwk->userflag.b.h & 3;
  pActwk->patno = wk;


  pActwk->sprhsize = dai_hstbl[wk];
  pActwk->sprvsize = 8;

  wk = (pActwk->userflag.b.h >> 2) & 3;
  pActwk->actfree[3] = dai_mcnttbl[wk];


  pActwk->r_no0 += 2;
  if ((wk = pActwk->userflag.b.l) != 0) {

    if (actwkchk(&pNewact) != 0) {

      dai_fout(pActwk);
    }
    else {
      pNewact->actno = 10;
      pNewact->xposi.w.h = pActwk->xposi.w.h;
      pNewact->yposi.w.h = pActwk->yposi.w.h - 16;
      ((char*)(pNewact))[61] = -16;



      ((unsigned short*)pNewact)[28] = pActwk - actwk;


      pNewact->userflag.b.h = pActwk->userflag.b.l & 2;
      wk = (unsigned char)pActwk->userflag.b.l & 248;
      pNewact->actfree[14] = wk;
      pNewact->xposi.w.h += (unsigned short)wk;
    }
  }
}





















static void dodai_move(sprite_status* pActwk) {
  unsigned char mtype;
  unsigned short xlen;

  if (time_stop) {
    ridechk(pActwk, &actwk[0]);
    return;
  }



  mtype = (pActwk->userflag.b.h >> 4) & 15;
  dodai_mtype[mtype](pActwk);

  xlen = ((unsigned short*)pActwk)[30] & 65408;
  xlen -= (scra_h_posit.w.h - 128) & -128;
  if (xlen > 640) {
    ride_on_clr(pActwk, &actwk[0]);
    dai_fout(pActwk);
  }
}



static void dodai_ud(sprite_status* pActwk) {
  ++pActwk->actfree[0];
  pActwk->yposi.w.h = ((short*)pActwk)[31] + dodai_sub(pActwk);

  ridechk(pActwk, &actwk[0]);
}



static void dodai_lr(sprite_status* pActwk) {
  int xsav;

  xsav = pActwk->xposi.l;
  pActwk->xposi.w.h = ((short*)pActwk)[30] + dodai_sub(pActwk);

  ++pActwk->actfree[0];

  pActwk->yposi.w.h = ((char)(((unsigned char*)pActwk)[48]) >> 1) + ((short*)pActwk)[31];



  dodai_ride1(pActwk, xsav);
}


static unsigned char dodai_ride1(sprite_status* pActwk, int xpos) {
  pActwk->xspeed.w = (pActwk->xposi.l - xpos) >> 8;
  return dodai_ride2(pActwk);
}


static unsigned char dodai_ride2(sprite_status* pActwk) {
  if (!ridechk(pActwk, &actwk[0])) {

    if (pActwk->actfree[2]) {
      --pActwk->actfree[2];
    }
    return 0;
  }

  if (pActwk->actfree[2] < 8) {
    ++pActwk->actfree[2];
  }

  return 1;
}



static void dodai_nA(sprite_status* pActwk) {
  int xsav;

  xsav = pActwk->xposi.l;
  ++pActwk->actfree[0];
  pActwk->yposi.w.h = ((short*)pActwk)[31] + dodai_sub(pActwk);

  pActwk->xposi.w.h = ((short*)pActwk)[30] + dodai_sub(pActwk);

  dodai_ride1(pActwk, xsav);
}



static void dodai_nB(sprite_status* pActwk) {
  int xsav;

  xsav = pActwk->xposi.l;
  ++pActwk->actfree[0];
  pActwk->yposi.w.h = ((short*)pActwk)[31] + dodai_sub(pActwk);

  pActwk->xposi.w.h = ((short*)pActwk)[30] - dodai_sub(pActwk);

  dodai_ride1(pActwk, xsav);
}



static unsigned char dodai_fix(sprite_status* pActwk) {
  pActwk->yposi.w.h = ((char)pActwk->actfree[2] >> 1) + ((short*)pActwk)[31];

  return dodai_ride2(pActwk);
}



static void dodai_fal(sprite_status* pActwk) {
  if (!pActwk->actfree[1]) {
    if (!dodai_fix(pActwk)) return;




    pActwk->actfree[4] = 30;
    pActwk->actfree[1] += 2;
  }


  if (pActwk->actfree[4]) {
    --pActwk->actfree[4];
    dodai_fix(pActwk);
    return;
  }


  ridechk(pActwk, &actwk[0]);
  pActwk->yposi.l += pActwk->yspeed.w << 8;

  if (pActwk->yspeed.w < 1024) {
    pActwk->yspeed.w += 64;
  }



  if ((scra_v_posit.w.h + 256) < pActwk->yposi.w.h) {

    ride_on_clr(pActwk, &actwk[0]);
    frameout(pActwk);
  }
}



static void dodai_up(sprite_status* pActwk) {
  switch (pActwk->actfree[1]) {
    case 0:
      if (!dodai_fix(pActwk)) break;



      pActwk->actfree[1] += 2;
    case 2:
      if (pActwk->actfree[0] < 64) {
        pActwk->yposi.w.h = ((short*)pActwk)[31] - dodai_sub(pActwk);

        pActwk->actfree[0] += 2;
        ridechk(pActwk, &actwk[0]);
        break;
      }

      ((short*)pActwk)[31] = pActwk->yposi.w.h;
      pActwk->actfree[1] += 2;
    case 4:
      dodai_fix(pActwk);
      break;
  }

}



static void dodai_upx(sprite_status* pActwk) {
  short coli;

  switch (pActwk->actfree[1]) {
    case 0:
      if (!dodai_fix(pActwk)) break;



      pActwk->actfree[1] += 2;
      pActwk->actfree[4] = 60;
    case 2:
      if (pActwk->actfree[4]) {
        --pActwk->actfree[4];
        dodai_fix(pActwk);
        break;
      }

      speedset2(pActwk);
      pActwk->yspeed.w -= 8;

      if ((coli = emycol_u(pActwk)) >= 0) {
        dodai_ride2(pActwk);
        break;
      }

      pActwk->yposi.w.h -= coli;
      ((short*)pActwk)[31] = pActwk->yposi.w.h;
      pActwk->actfree[1] += 2;
    case 4:
      dodai_fix(pActwk);
      break;
  }

}



static void dodai_rm(sprite_status* pActwk) {
  int xsav;

  switch (pActwk->actfree[1]) {
    case 0:
      if (!dodai_fix(pActwk)) break;



      pActwk->actfree[1] += 2;
      pActwk->actfree[4] = 60;
    case 2:
      if (pActwk->actfree[4]) {
        --pActwk->actfree[4];
        dodai_fix(pActwk);
        break;
      }

      if (pActwk->actfree[0] < 64) {
        xsav = pActwk->xposi.l;
        pActwk->xposi.w.h = ((short*)pActwk)[30] + dodai_sub(pActwk);

        ++pActwk->actfree[0];
        pActwk->yposi.w.h = ((char)pActwk->actfree[2] >> 1) + ((short*)pActwk)[31];

        dodai_ride1(pActwk, xsav);
        break;
      }

      ((short*)pActwk)[30] = pActwk->xposi.w.h;
      pActwk->actfree[1] += 2;
    case 4:
      dodai_fix(pActwk);
      break;
  }

}



static void dodai_lm(sprite_status* pActwk) {
  int xsav;

  switch (pActwk->actfree[1]) {
    case 0:
      if (!dodai_fix(pActwk)) break;



      pActwk->actfree[1] += 2;
      pActwk->actfree[4] = 60;
    case 2:
      if (pActwk->actfree[4]) {
        --pActwk->actfree[4];
        dodai_fix(pActwk);
        break;
      }

      if (pActwk->actfree[0] < 64) {
        xsav = pActwk->xposi.l;
        pActwk->xposi.w.h = ((short*)pActwk)[30] - dodai_sub(pActwk);

        ++pActwk->actfree[0];
        pActwk->yposi.w.h = ((char)pActwk->actfree[2] >> 1) + ((short*)pActwk)[31];

        dodai_ride1(pActwk, xsav);
        break;
      }

      ((short*)pActwk)[30] = pActwk->xposi.w.h;
      pActwk->actfree[1] += 2;
    case 4:
      dodai_fix(pActwk);
      break;
  }

}














static short dodai_sub(sprite_status* pActwk) {
  short sinwk, coswk;

  sinset((unsigned char)(char)pActwk->actfree[0], &sinwk, &coswk);
  return (sinwk * (short)((char*)pActwk)[49]) >> 4;
}











static void dai_fout(sprite_status* pActwk) {
  short s;

  if (pActwk->cdsts) {
    s = time_flag + pActwk->cdsts * 3;
    flagwork[s] &= 127;
  }

  frameout(pActwk);
}































































void vfuta(sprite_status* pActwk) {
  vfuta_tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s(pActwk);
}





static void vfuta_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->patbase = vfutapats[stageno_i.b.l][time_flag_i & 0x7F];
  pActwk->sprpri = 1;
  pActwk->actflg |= 4;
  pActwk->sprhsize = 4;
  pActwk->sprvsize = 24;

  pa_set(0, 0);
  vfuta_move1(pActwk);
}





static void vfuta_move1(sprite_status* pActwk) {
  short wk;

  if ((wk = pActwk->yposi.w.h - actwk[0].yposi.w.h) < 0) {;
    wk = -wk;
  }

  if (wk < 32) {
    wk = pActwk->xposi.w.h - actwk[0].xposi.w.h;

    if (0 <= wk && wk < 49) {
      pActwk->actfree[16] = pActwk->actfree[17] = 0;
      pActwk->r_no0 = 4;

      if (pActwk->actflg & 128) {
        soundset(164);
        pActwk->patno = 1;
      }
    }
  }

  ride_on_chk(pActwk, &actwk[0]);
}





static void vfuta_move2(sprite_status* pActwk) {
  short wk;

  wk = pActwk->actfree[16];
  wk += 8;
  pActwk->actfree[16] += 8;

  if (wk > 255) {
    pActwk->r_no0 -= 2;
    pActwk->patno = 0;
  }
}
