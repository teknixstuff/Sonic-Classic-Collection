#include "EQU.h"
#include "DAI_K.h"
#include "ACTION.h"
#include "ACTSET.h"
#include "ETC.h"
#include "LOADER2.h"
#include "PLAYSUB.h"
#include "RIDECHK.h"

static void dai_k_init(sprite_status* pActwk);
static void dai_k_move(sprite_status* pActwk);
static void k_move(sprite_status* pActwk, sprite_status* pSonicwk);
static void jumpchk_d(sprite_status* pActwk, sprite_status* pSonicwk);

static sprite_pattern k_daipat0 = { 1, { { -16, -8, 0, 478 } } };
static sprite_pattern z11a_k_daipat0 = { 1, { { -16, -8, 0, 495 } } };
static sprite_pattern k_daipat1 = { 1, { { -16, -8, 0, 479 } } };
static sprite_pattern z11a_k_daipat1 = { 1, { { -16, -8, 0, 496 } } };
static sprite_pattern k_daipat2 = { 1, { { -16, -8, 0, 480 } } };
static sprite_pattern z11a_k_daipat2 = { 1, { { -16, -8, 0, 497 } } };
sprite_pattern* k_daipat[3] = {
  &k_daipat0,
  &k_daipat1,
  &k_daipat2
};
sprite_pattern* z11a_k_daipat[3] = {
  &z11a_k_daipat0,
  &z11a_k_daipat1,
  &z11a_k_daipat2
};
sprite_pattern** k_daipats[3][3] = {
  { k_daipat, z11a_k_daipat, k_daipat },
  { k_daipat, k_daipat, k_daipat },
  { 0, 0, k_daipat }
};
static char k_daichg0[5] = { 1, 0, 1, 2, -1 };
static char* k_daichg = k_daichg0;
static void(*dai_k_move_tbl[2])(sprite_status*) = {
  &dai_k_init,
  &dai_k_move
};





















































































void dai_k(sprite_status* pActwk) {
  dai_k_move_tbl[pActwk->r_no0 / 2](pActwk);

  if (!time_stop) {
    patchg(pActwk, (unsigned char**)&k_daichg);
  }

  actionsub(pActwk);
  frameout_s(pActwk);
}






static void dai_k_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg = 4;
  pActwk->sprpri = 4;
  pActwk->patbase = k_daipats[stageno_i.b.l][time_flag_i & 0x7F];




  pActwk->sprhsize = 16;
  pActwk->sprvsize = 8;
  dai_k_move(pActwk);
}





static void dai_k_move(sprite_status* pActwk) {
  short lenwk, sinwk, coswk;
  static unsigned char pattbl[16] = { 0, 0, 0, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5 };

  if (!(pActwk->actflg & 128)) return;



  if (!ride_on_chk(pActwk, actwk)) return;



  if (!(actwk[0].actfree[2] & 1)) {
    actwk[0].actfree[2] |= 1;
    actwk[0].mstno.b.h = 45;
    lenwk = actwk[0].xposi.w.h - pActwk->xposi.w.h;

    if (lenwk >= 0) {
      actwk[0].actfree[1] = 0;
    } else {
      actwk[0].actfree[1] = 128;
      lenwk = -lenwk;
    }

    actwk[0].actfree[15] = lenwk;
  }


  if (actwk[0].r_no0 >= 6) return;




  actwk[0].actfree[1] += 8;
  sinset(actwk[0].actfree[1], &sinwk, &coswk);
  actwk[0].xposi.w.h = pActwk->xposi.w.h + ((unsigned int)(actwk[0].actfree[15] * coswk) >> 8);



  actwk[0].patcnt = pattbl[actwk[0].actfree[1] >> 4];

  if (!(actwk[0].actfree[1] & 63)) {
    ++actwk[0].actfree[15];
  }

  swdata = swdata1;
  k_move(pActwk, &actwk[0]);
  jumpchk_d(pActwk, &actwk[0]);
}













static void k_move(sprite_status* pActwk, sprite_status* pSonicwk) {
  if (pSonicwk->xposi.w.h >= pActwk->xposi.w.h) {


    if (swdata.b.h & 8) {
      ++pSonicwk->actfree[15];
    } else if (swdata.b.h & 4) {
      if (pSonicwk->actfree[15]) {
        --pSonicwk->actfree[15];
      }
    }
  }
  else {

    if (swdata.b.h & 4) {
      ++pSonicwk->actfree[15];
    } else if (swdata.b.h & 8) {
      if (pSonicwk->actfree[15]) {
        --pSonicwk->actfree[15];
      }
    }
  }
}













static void jumpchk_d(sprite_status* pActwk, sprite_status* pSonicwk) {
  short jumpwk, sinwk, coswk;

  if (!(swdata.b.l & 112)) return;




  pSonicwk->actfree[2] = 0;
  if (pActwk->cddat & 64) {
    jumpwk = 896;
  } else {
    jumpwk = 1664;
  }

  sinset(pSonicwk->direc.b.h - 64, &sinwk, &coswk);
  pSonicwk->xspeed.w += (coswk * jumpwk) >> 8;
  pSonicwk->yspeed.w += (sinwk * jumpwk) >> 8;

  pSonicwk->cddat |= 2;
  pSonicwk->cddat &= 223;
  pSonicwk->actfree[18] = 1;
  pSonicwk->actfree[14] = 0;

  soundset(160);






























  if (pSonicwk->cddat & 4) {
    if (chibi_flag) {
      pSonicwk->sprvsize = 10;
      pSonicwk->sprhs = 5;
    } else {
      pSonicwk->sprvsize = 19;
      pSonicwk->sprhs = 9;
    }

    pSonicwk->cddat |= 16;
  } else {
    if (chibi_flag) {
      pSonicwk->sprvsize = 10;
      pSonicwk->sprhs = 5;
    } else {
      pSonicwk->sprvsize = 14;
      pSonicwk->sprhs = 7;
    }

    pSonicwk->cddat |= 4;
    pSonicwk->mstno.b.h = 2;
  }


}
