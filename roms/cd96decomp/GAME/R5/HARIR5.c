#include "../EQU.h"
#include "HARIR5.h"
#include "../ACTION.h"
#include "../RIDECHK.h"
#include "COLI5.h"

static void harir3_init(sprite_status* pActwk);
static void harir3_move(sprite_status* pActwk);
static void harir3_kind(sprite_status* pActwk);
static void harir3_ymv1(sprite_status* pActwk);
static void harir3_ymv2(sprite_status* pActwk);
static void harir3_xmv1(sprite_status* pActwk);
static void harir3_xmv2(sprite_status* pActwk);
static void harir3_sub(sprite_status* pActwk);

static sprite_pattern harir5_pat1 = {
  1,
  { { -16, -16, 0, 417 } }
};
static sprite_pattern harir5_pat2 = {
  1,
  { { -16, -16, 0, 418 } }
};
static sprite_pattern harir5_pat3 = {
  1,
  { { -16, -16, 0, 419 } }
};
static sprite_pattern harir5_pat4 = {
  1,
  { { -16, -16, 0, 420 } }
};
sprite_pattern* harir5pat[4] = {
  &harir5_pat1,
  &harir5_pat2,
  &harir5_pat3,
  &harir5_pat4
};
























































void harir5(sprite_status* pActwk) {
  sprite_status* pRideactwk;

  void(*harir3_acttbl[2])(sprite_status*) = {
    &harir3_init,
    &harir3_move
  };

  harir3_acttbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);

  if (((short*)pActwk)[28]) {
    pRideactwk = &actwk[((short*)pActwk)[28]];
    pActwk->xposi.w.h = pRideactwk->xposi.w.h + (short)(char)pActwk->actfree[14];
    pActwk->yposi.w.h = pRideactwk->yposi.w.h + (short)(char)pActwk->actfree[15];
  }

  if ((unsigned short)(
      (((unsigned short*)pActwk)[29] & 65408) - ((unsigned short)(scra_h_posit.w.h - 128) & 65408)
      ) > 640) {
    if (pActwk->cdsts) {
      flagwork[time_flag + pActwk->cdsts * 3] &= 127;
    }
    frameout(pActwk);
  }
}








static void harir3_init(sprite_status* pActwk) {
  unsigned char bD0;


  unsigned char harir3sztbl[12] = {
    18, 12,   0,
    18, 12, 131,
    10, 14, 130,
    10, 14, 130
  };

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 1099;
  pActwk->sprpri = 3;
  pActwk->patbase = harir5pat;

  ((short*)pActwk)[29] = pActwk->xposi.w.h;
  ((short*)pActwk)[27] = pActwk->yposi.w.h;

  bD0 = pActwk->userflag.b.h & 3;
  pActwk->patno = bD0;
  pActwk->sprhsize = harir3sztbl[bD0 * 3];
  pActwk->sprvsize = harir3sztbl[bD0 * 3 + 1];
  pActwk->colino = harir3sztbl[bD0 * 3 + 2];

  harir3_move(pActwk);
}








static void harir3_move(sprite_status* pActwk) {
  harir3_kind(pActwk);


  if (pActwk->patno) {
    hitchk(pActwk, &actwk[0]);
  }
  else {



    if (hitchk(pActwk, &actwk[0])) {
      if (pActwk->cddat & 8) {
        if (!plpower_a) {
          if (!plpower_m) {
            if (actwk[0].r_no0 < 4) {
              if (!((short*)&actwk[0])[26]) {
                actwk[0].yposi.l -= actwk[0].yspeed.w << 8;
                playdamageset(&actwk[0], pActwk);
              }
            }
          }
        }
      }
    }
  }

}








static void harir3_kind(sprite_status* pActwk) {
  void(*harir3_kndtbl[4])(sprite_status*) = {
    &harir3_ymv1,
    &harir3_ymv2,
    &harir3_xmv1,
    &harir3_xmv2
  };

  if (pActwk->userflag.b.h & 4)
    harir3_kndtbl[pActwk->userflag.b.h & 3](pActwk);
}








static void harir3_ymv1(sprite_status* pActwk) {
  harir3_sub(pActwk);
  pActwk->yposi.w.h = (short)(unsigned short)pActwk->actfree[17] + ((short*)pActwk)[27];
}








static void harir3_ymv2(sprite_status* pActwk) {
  harir3_sub(pActwk);
  pActwk->yposi.w.h = -(short)(unsigned short)pActwk->actfree[17] + ((short*)pActwk)[27];
}







static void harir3_xmv1(sprite_status* pActwk) {
  harir3_sub(pActwk);
  pActwk->xposi.w.h = -(short)(unsigned short)pActwk->actfree[17] + ((short*)pActwk)[29];
}







static void harir3_xmv2(sprite_status* pActwk) {
  harir3_sub(pActwk);
  pActwk->xposi.w.h = (short)(unsigned short)pActwk->actfree[17] + ((short*)pActwk)[29];
}








static void harir3_sub(sprite_status* pActwk) {
  if (pActwk->actfree[16]) {
    if (--pActwk->actfree[16]) return;
  }

  if (pActwk->actfree[18]) {
    if (pActwk->actfree[17] >= 8) {
      pActwk->actfree[17] -= 8;
      return;
    }
    pActwk->actfree[17] = 0;
    pActwk->actfree[18] = 0;
    pActwk->actfree[16] = 60;
  }
  else {


    pActwk->actfree[17] += 8;
    if (pActwk->actfree[17] >= 32) {
      pActwk->actfree[17] = 32;
      pActwk->actfree[18] = 1;
      pActwk->actfree[16] = 60;
    }
  }
}
