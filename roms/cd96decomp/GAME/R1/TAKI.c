#include "../EQU.h"
#include "TAKI.h"
#include "../ACTION.h"
#include "../PLAYSUB.h"

static void taki_init(sprite_status* pActwk);
static void taki_move(sprite_status* pActwk);

extern void block_wrt(unsigned short BlockNo, unsigned short xOffs, unsigned short yOffs);

static char shibukichg0[4] = { 4, 0, 1, -1 };
unsigned char* shibukichg = { (unsigned char*)shibukichg0 };
static sprite_pattern shibuki0 = { 1, { { -96, -16, 0, 448 } } };
static sprite_pattern z11ashibuki0 = { 1, { { -96, -16, 0, 465 } } };
static sprite_pattern shibuki1 = { 1, { { -96, -16, 0, 449 } } };
static sprite_pattern z11ashibuki1 = { 1, { { -96, -16, 0, 466 } } };
sprite_pattern* shibukipat[2] = {
  &shibuki0,
  &shibuki1
};
sprite_pattern* z11ashibukipat[2] = {
  &z11ashibuki0,
  &z11ashibuki1
};
sprite_pattern** shibukipats[3][3] = {
  { shibukipat, z11ashibukipat, shibukipat },
  { shibukipat, shibukipat, shibukipat },
  { 0, 0, shibukipat }
};
static void(*taki_move_tbl[2])(sprite_status*) = {
  &taki_init,
  &taki_move
};



































































void taki(sprite_status* pActwk) {
  taki_move_tbl[pActwk->r_no0 / 2](pActwk);
  patchg(pActwk, &shibukichg);
  actionsub(pActwk);
}





static void taki_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->patbase = shibukipats[stageno_i.b.l][time_flag_i & 0x7F];
  pActwk->actflg = 4;
  pActwk->sprpri = 1;
  pActwk->sprhsize = 16;
  pActwk->sproffset = 954;
  pActwk->yposi.w.h &= -16;

  ((short*)pActwk)[23] = pActwk->yposi.w.h + 384;

}





static void taki_move(sprite_status* pActwk) {
  unsigned short blkno;
  short i, xoffs;

  if (pActwk->yposi.w.h + 4 >= ((short*)pActwk)[23]) {

    frameout(pActwk);
    return;
  }

  pActwk->yposi.w.h += 4;
  blkno = 8194;
  xoffs = pActwk->xposi.w.h - 96;

  if (pActwk->yposi.w.h & 15) return;



  for (i = 0; i < 12; ++i, xoffs += 16) {
    block_wrt(blkno, xoffs, pActwk->yposi.w.h);
  }
}













void jisin_set(sprite_status* pActwk) {
  pActwk = pActwk;

}













void jisin(sprite_status* pActwk) {
  pActwk = pActwk;

}
