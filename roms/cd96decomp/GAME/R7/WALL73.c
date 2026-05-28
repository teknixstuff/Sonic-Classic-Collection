#include "../EQU.h"
#include "WALL73.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../RIDECHK.h"

extern sprite_pattern** pats_wall7[3];

static short move_blk(sprite_status* pActwk);

static unsigned char wall7_tbl0[12] = {
  11, 16,
  32, 16,
  48, 16,
  64, 16,
  11, 32,
  11, 48
};















































void wall73(sprite_status* pActwk) {
  if (!pActwk->r_no0) {

    pActwk->r_no0 += 2;
    pActwk->actflg |= 4;
    pActwk->sprpri = 3;
    pActwk->sproffset = 17676;
    pActwk->patbase = pats_wall7[stageno_i.b.l];
    pActwk->patno = pActwk->userflag.b.h;

    pActwk->sprhs = wall7_tbl0[pActwk->userflag.b.h * 2];
    pActwk->sprhsize = wall7_tbl0[pActwk->userflag.b.h * 2];
    pActwk->sprvsize = wall7_tbl0[pActwk->userflag.b.h * 2 + 1];
  }

  if (pActwk->userflag.b.l) {
    if (move_blk(pActwk)) return;
  }
  if (hitchk(pActwk, &actwk[0]))
    actwk[0].colino = 0;
  actionsub(pActwk);
  frameout_s(pActwk);
}








static short move_blk(sprite_status* pActwk) {
  short wD0, wD1;
  char bD0;

  if (!(bossflag & 128))
    return 0;
  if (!((short*)pActwk)[23]) {

    wD0 = 32;
    wD1 = 512;
    if (pActwk->userflag.b.l & 128) {
      wD0 *= -1;
      wD1 *= -1;
    }

    pActwk->yspeed.w = wD1;
    ((short*)pActwk)[23] = pActwk->yposi.w.h + wD0;
  }

  pActwk->yposi.l += pActwk->yspeed.w << 8;

  if (((short*)pActwk)[23] != pActwk->yposi.w.h) {
    return 0;
  }
  ((short*)pActwk)[23] = 0;


  bD0 = (pActwk->userflag.b.l & 15) - 1;
  if (!bD0) {

    bossflag &= 127;
    if (pActwk->userflag.b.l & 64) {

      pActwk->userflag.b.l = 0;
      return 0;
    }


    frameout(pActwk);
    return -1;
  }



  pActwk->userflag.b.l &= -16;
  pActwk->userflag.b.l += bD0;
  if (pActwk->userflag.b.l & 32)
    return 0;
  if (pActwk->userflag.b.l & 16) {

    if (++pActwk->patno == 1) {
      pActwk->patno = 4;
    }
    pActwk->yposi.w.h -= 16;
  }
  else {

    if (--pActwk->patno == 3) {
      pActwk->patno = 0;
    }
    pActwk->yposi.w.h += 16;
  }

  pActwk->sprhs = wall7_tbl0[pActwk->patno * 2];
  pActwk->sprhsize = wall7_tbl0[pActwk->patno * 2];
  pActwk->sprvsize = wall7_tbl0[pActwk->patno * 2 + 1];

  return 0;

}
