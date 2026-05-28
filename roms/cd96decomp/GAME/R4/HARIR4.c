#include "../EQU.h"
#include "HARIR4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../COLI.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

sprite_pattern z4a_harir4_pat0 = { 1, { { -16, -16, 0, 443 } } };
sprite_pattern z41b_harir4_pat0 = { 1, { { -16, -16, 0, 431 } } };
sprite_pattern z41d_harir4_pat0 = { 1, { { -16, -16, 0, 466 } } };
sprite_pattern z42b_harir4_pat0 = { 1, { { -16, -16, 0, 429 } } };
sprite_pattern z4a_harir4_pat1 = { 1, { { -16, -16, 0, 444 } } };
sprite_pattern z41b_harir4_pat1 = { 1, { { -16, -16, 0, 432 } } };
sprite_pattern z41d_harir4_pat1 = { 1, { { -16, -16, 0, 467 } } };
sprite_pattern z42b_harir4_pat1 = { 1, { { -16, -16, 0, 430 } } };
sprite_pattern* z4aharir4pat[2] = {
  &z4a_harir4_pat0,
  &z4a_harir4_pat1
};
sprite_pattern* z41bharir4pat[2] = {
  &z41b_harir4_pat0,
  &z41b_harir4_pat1
};
sprite_pattern* z41dharir4pat[2] = {
  &z41d_harir4_pat0,
  &z41d_harir4_pat1
};
sprite_pattern* z42bharir4pat[2] = {
  &z42b_harir4_pat0,
  &z42b_harir4_pat1
};
sprite_pattern** harir4pats[2][4] = {
  { z41bharir4pat, z4aharir4pat, z41dharir4pat, z41bharir4pat },
  { z42bharir4pat, z4aharir4pat, z42bharir4pat, z42bharir4pat }
};







































void harir4(sprite_status* pActwk) {
  sprite_status* pRideactwk;

  void(*harir4_acttbl[2])(sprite_status*) = {
    &harir4_init,
    &harir4_move
  };

  harir4_acttbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);


  if (((short*)pActwk)[28]) {
    pRideactwk = &actwk[((short*)pActwk)[28]];
    if (!pRideactwk->actno) {
      frameout(pActwk);
      return;
    }

    pActwk->xposi.w.h = pRideactwk->xposi.w.h + (short)pActwk->actfree[14];
    pActwk->yposi.w.h = pRideactwk->yposi.w.h + (short)pActwk->actfree[15];
  }

  frameout_s00(pActwk, ((short*)pActwk)[29]);
}








void harir4_ridechk(sprite_status* pActwk) {
  if (pActwk->patno) {
    hitchk(pActwk, &actwk[0]);
    return;
  }


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








void harir4_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 928;
  pActwk->sprpri = 4;
  pActwk->patbase = harir4pats[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  if (!((short*)pActwk)[29]) {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
  }
  ((short*)pActwk)[27] = pActwk->yposi.w.h;
  pActwk->sprhsize = 18;
  pActwk->sprvsize = 12;
  if (pActwk->userflag.b.h) {
    pActwk->patno = 1;
    pActwk->colino = 131;
  }

  harir4_move(pActwk);
}








void harir4_move(sprite_status* pActwk) {
  if (pActwk->userflag.b.h != 1) {
    harir4_sub(pActwk);
    pActwk->yposi.w.h = pActwk->actfree[17] + ((short*)pActwk)[27];
  }

  harir4_ridechk(pActwk);
}








void harir4_sub(sprite_status* pActwk) {
  if (pActwk->actfree[16]) {
    if (--pActwk->actfree[16]) return;
    if (pActwk->actflg & 128) soundset(183);
  }

  if (pActwk->actfree[18]) {


    if (pActwk->actfree[17] < 8) {
      pActwk->actfree[17] = 0;
      pActwk->actfree[18] = 0;
      pActwk->actfree[16] = 60;
    }
    else pActwk->actfree[17] -= 8;
  }
  else {
    if ((char)(pActwk->actfree[17] += 8) >= 32) {
      pActwk->actfree[17] = 32;
      pActwk->actfree[18] = 1;
      pActwk->actfree[16] = 60;
    }
  }
}
