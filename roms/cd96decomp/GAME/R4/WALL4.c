#include "../EQU.h"
#include "WALL4.h"
#include "../ACTION.h"
#include "../RIDECHK.h"

sprite_pattern z42a_wall4_pat0 = { 1, { { -64, -64, 0, 470 } } };
sprite_pattern z43_wall4_pat0 = { 1, { { -64, -64, 0, 492 } } };
sprite_pattern* z42a_pat_wall4[1] = { &z42a_wall4_pat0 };
sprite_pattern* z43_pat_wall4[1] = { &z43_wall4_pat0 };
sprite_pattern** pats_wall4[3] = {
  z42a_pat_wall4,
  z42a_pat_wall4,
  z43_pat_wall4
};

































































void wall4(sprite_status* pActwk) {
  void(*wall4_acttbl[4])(sprite_status*) = {
    &wall4_init,
    &wall4_sense,
    &wall4_wait,
    &wall4_down
  };

  wall4_acttbl[pActwk->r_no0 / 2](pActwk);
  hitchk(pActwk, &actwk[0]);
  actionsub(pActwk);
  frameout_s_(pActwk);
}








void wall4_init(sprite_status* pActwk) {
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;

  pActwk->sprhs = 64;
  pActwk->sprhsize = 64;
  pActwk->sprvsize = 64;
  pActwk->sproffset = 17514;
  pActwk->patbase = pats_wall4[stageno_i.b.l];

  ((unsigned short*)pActwk)[24] = time_flag + pActwk->cdsts * 3;

  if (!(flagwork[((unsigned short*)pActwk)[24]] & 1)) {

    if (pActwk->userflag.b.h) ((short*)pActwk)[23] = 32;
    else ((short*)pActwk)[23] = 16;



    pActwk->r_no0 = (pActwk->userflag.b.h + 1) * 2;
  }
  else {

    if (pActwk->userflag.b.h) pActwk->yposi.w.h += 128;
    else pActwk->yposi.w.h += 64;
    pActwk->r_no0 += 4;
  }
}








void wall4_sense(sprite_status* pActwk) {
  if ((unsigned short)(actwk[0].yposi.w.h - pActwk->yposi.w.h) < 128) {
    if ((unsigned short)(actwk[0].xposi.w.h - pActwk->xposi.w.h - 160) < 32) {
      pActwk->actfree[21] = 255;
      pActwk->r_no0 += 2;
    }
  }
}








void wall4_wait(sprite_status* pActwk) {
  if (pActwk->actfree[21]) {

    flagwork[((unsigned short*)pActwk)[24]] |= 1;
    pActwk->r_no0 += 2;
  }
}








void wall4_down(sprite_status* pActwk) {
  pActwk->yposi.l += 0x40000;
  if (!(--((short*)pActwk)[23])) {
    pActwk->actfree[21] = 0;
    pActwk->r_no0 -= 2;
  }
}








void frameout_s_(sprite_status* pActwk) {
  if (pActwk->userflag.b.h != 1) {
    if ((pActwk->xposi.w.h & 65408) - (scra_h_posit.w.h - 128 & 65408) > 640) {
      flagwork[((unsigned short*)pActwk)[24]] &= 127;
      frameout(pActwk);
    }
  }
}
