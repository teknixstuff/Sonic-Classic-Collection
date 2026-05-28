#include "../EQU.h"
#include "IWA5ROLL.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../RIDECHK.h"

static void iwa5roll_init(sprite_status* pActwk);
static void iwa5roll_move(sprite_status* pActwk);

static sprite_pattern pat_iwa5roll_00 = {
  1,
  { { -8, -8, 0, 429 } }
};
sprite_pattern* pat_iwa5roll[1] = { &pat_iwa5roll_00 };






















































void iwa5roll(sprite_status* pActwk) {
  if (pActwk->r_no0) iwa5roll_move(pActwk);
  else iwa5roll_init(pActwk);
}








static void iwa5roll_init(sprite_status* pActwk) {
  sprite_status* pNewactwk;
  short wD1, wD3, wD4, wD5, wD6;
  short wA5;
  short iwa5roll_tbl[6] = {
    128, 1,
    192, 1,
    256, 1
  };

  wD1 = iwa5roll_tbl[time_flag * 2];
  wA5 = iwa5roll_tbl[time_flag * 2 + 1];
  if (pActwk->userflag.b.h) wD1 *= -1;

  ((short*)pActwk)[29] = wD1;

  wD6 = 3;
  wD5 = 0;
  wD4 = 0;
  wD3 = 0;
  pNewactwk = pActwk;
  goto label1;


  do {
    wD5 = 0; 
    wD3 = wD4;

    do {
      if (actwkchk(&pNewactwk) != 0) break;


label1:
      ((short*)pNewactwk)[23] = pActwk - actwk;
      pNewactwk->actflg |= 4;
      pNewactwk->r_no0 = 2;
      pNewactwk->sprpri = 3;
      pNewactwk->sprhs = 8;
      pNewactwk->sprhsize = 8;
      pNewactwk->sprvsize = 8;
      pNewactwk->sproffset = 17152;
      pNewactwk->patbase = pat_iwa5roll;
      pNewactwk->actno = pActwk->actno;
      pNewactwk->xposi.w.h = pActwk->xposi.w.h;
      pNewactwk->yposi.w.h = pActwk->yposi.w.h;
      ((int*)pNewactwk)[12] = pActwk->xposi.l;
      ((int*)pNewactwk)[13] = pActwk->yposi.l;
      ((short*)pNewactwk)[29] = ((short*)pActwk)[29];

      ((short*)pNewactwk)[28] = wD3;
      wD3 += 2048;
    } while (++wD5 <= wA5);
    wD4 += 16384;
  } while (--wD6 >= 0);


  ((short*)pActwk)[23] = 0;
}








static void iwa5roll_move(sprite_status* pActwk) {
  unsigned char bD0;
  short Sp;
  unsigned short Sin, Cos;
  int_union lD0, lD1;
  int_union lD4, lD5;
  int lD3;

  if (((short*)pActwk)[23]) {
    if (actwk[((short*)pActwk)[23]].actno != 39) {
      frameout(pActwk);
      return;
    }
  }

  ((short*)pActwk)[28] += ((short*)pActwk)[29];
  lD1.l = 0;
  lD0.l = 0;
  sinset(pActwk->actfree[11], (short*)&Sin, (short*)&Cos);
  lD1.w.h = Cos;
  lD0.w.h = Sin;
  lD5.l = lD1.l / 4 + lD1.l / 8;
  lD4.l = lD0.l / 4 + lD0.l / 8;
  lD5.l += ((int*)pActwk)[12];
  lD4.l += ((int*)pActwk)[13];
  lD3 = pActwk->xposi.l;
  pActwk->xposi.l = lD5.l;
  pActwk->yposi.l = lD4.l;
  lD5.l = lD5.l - lD3 >> 8;
  pActwk->xspeed.w = lD5.w.l;

  Sp = pActwk->xspeed.w;
  pActwk->xspeed.w = 0;
  pActwk->sprvsize = 10;
  if (hitchk(pActwk, &actwk[0])) bD0 = 255;
  else bD0 = 0;
  pActwk->xspeed.w = Sp;
  pActwk->sprvsize = 8;
  if (bD0) hitchk(pActwk, &actwk[0]);

  actionsub(pActwk);

  if (!((short*)pActwk)[23]) {
    frameout_s00(pActwk, ((short*)pActwk)[25]);
  }
}
