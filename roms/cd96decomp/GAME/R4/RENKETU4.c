#include "../EQU.h"
#include "RENKETU4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../RIDECHK.h"

sprite_pattern z41c_renketu4_pat0 = { 1, { { -32, -8, 0, 445 } } };
sprite_pattern z41d_renketu4_pat0 = { 1, { { -32, -8, 0, 431 } } };
sprite_pattern z42c_renketu4_pat0 = { 1, { { -32, -8, 0, 512 } } };
sprite_pattern z43c_renketu4_pat0 = { 1, { { -32, -8, 0, 496 } } };
sprite_pattern z41c_renketu4_pat1 = { 1, { { -8, -8, 0, 446 } } };
sprite_pattern z41d_renketu4_pat1 = { 1, { { -8, -8, 0, 432 } } };
sprite_pattern z42c_renketu4_pat1 = { 1, { { -8, -8, 0, 513 } } };
sprite_pattern z43c_renketu4_pat1 = { 1, { { -8, -8, 0, 497 } } };
sprite_pattern* z41crenketu4pat[2] = {
  &z41c_renketu4_pat0,
  &z41c_renketu4_pat1
};
sprite_pattern* z41drenketu4pat[2] = {
  &z41d_renketu4_pat0,
  &z41d_renketu4_pat1
};
sprite_pattern* z42crenketu4pat[2] = {
  &z42c_renketu4_pat0,
  &z42c_renketu4_pat1
};
sprite_pattern* z43crenketu4pat[2] = {
  &z43c_renketu4_pat0,
  &z43c_renketu4_pat1
};
sprite_pattern** renketu4pats[3][2] = {
  { z41drenketu4pat, z41crenketu4pat },
  { z42crenketu4pat, z42crenketu4pat },
  { z43crenketu4pat, z43crenketu4pat }
};










































void renketu4(sprite_status* pActwk) {
  unsigned short xwk1;
  unsigned short xwk2;
  void(*renketu4_acttbl[2])(sprite_status*) = {
    &renketu4_init,
    &renketu4_move
  };

  renketu4_acttbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);

  xwk1 = ((unsigned short*)pActwk)[29] & 65408;
  xwk2 = (unsigned short)scra_h_posit.w.h - 128 & 65408;
  if ((unsigned short)(xwk1 - xwk2) > 640) {
    frameout(pActwk);
  }
}








void renketu4_ridechk(sprite_status* pActwk) {
  if (ridechk(pActwk, &actwk[0])) {

    actwk[0].yposi.w.h = pActwk->yposi.w.h - (short)pActwk->sprvsize - (short)actwk[0].sprvsize + 2;
  }

}








void renketu4_init(sprite_status* pActwk) {
  char renketu4_tbl[18] = {
     32, 0,
      0, 0,
    -32, 0,
     24, 1,
     16, 1,
      8, 1,
     -8, 1,
    -16, 1,
    -24, 1
  };
  sprite_status* pNewactwk;
  unsigned char i;


  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;

  if (stageno.b.l == 2)
    pActwk->sproffset = 17408;
  else
    pActwk->sproffset = 17216;

  pActwk->patbase = renketu4pats[stageno_i.b.l][generate_flag];
  pActwk->sprhsize = 32;
  pActwk->sprvsize = 8;

  if (!pActwk->actfree[18]) {
    ((short*)pActwk)[29] = pActwk->xposi.w.h;
    ((short*)pActwk)[27] = pActwk->yposi.w.h;

    for (i = 1; i <= 8; ++i) {
      if (actwkchk(&pNewactwk) == 0) {
        pNewactwk->actno = 62;
        pNewactwk->userflag.b.h = pActwk->userflag.b.h;
        pNewactwk->actfree[18] = i;
        ((short*)pNewactwk)[29] = ((short*)pActwk)[29];
        ((short*)pNewactwk)[27] = ((short*)pActwk)[27];
      }
    }
  }

  pActwk->actfree[21] = renketu4_tbl[pActwk->actfree[18] * 2];
  pActwk->patno = renketu4_tbl[pActwk->actfree[18] * 2 + 1];

  pActwk->sprpri = 1;
  if (pActwk->patno) {
    pActwk->sprpri = 3;
    pActwk->sproffset -= 16384;
  }

  if (pActwk->userflag.b.h & 16)
    ((short*)pActwk)[26] = -256;
  else
    ((short*)pActwk)[26] = 256;

  renketu4_move(pActwk);
}








void renketu4_move(sprite_status* pActwk) {
  unsigned short wD0, wD1;
  int_union lD0, lD1, lD4, lD5;
  short wk;

  swchk(pActwk);

  ((short*)pActwk)[33] += ((short*)pActwk)[26];

  sinset(pActwk->actfree[21], (short*)&wD0, (short*)&wD1);

  lD0.l = (short)wD0 * 6 >> 4;
  lD1.l = (short)wD1 * 6 >> 4;
  wk = lD0.w.h;
  lD0.w.h = lD0.w.l;
  lD0.w.l = wk;
  wk = lD1.w.h;
  lD1.w.h = lD1.w.l;
  lD1.w.l = wk;

  lD4.w.l = lD5.w.l = 0;
  lD4.w.h = ((short*)pActwk)[27];
  lD5.w.h = ((short*)pActwk)[29];
  lD0.l += lD4.l;
  lD1.l += lD5.l;

  pActwk->yspeed.w = (lD0.l - pActwk->yposi.l) << 8 >> 16;
  pActwk->xspeed.w = (lD1.l - pActwk->xposi.l) << 8 >> 16;
  pActwk->yposi.l = lD0.l;
  pActwk->xposi.l = lD1.l;

  if (!pActwk->patno) renketu4_ridechk(pActwk);

}








void swchk(sprite_status* pActwk) {
  if (!(pActwk->userflag.b.h & 128)) {
    if (switchflag[pActwk->userflag.b.h & 15] & 128) {
      if (pActwk->actfree[19]) return;
      ((short*)pActwk)[26] *= -1;
      pActwk->actfree[19] = 1;
      return;
    }
    pActwk->actfree[19] = 0;
  }

}
