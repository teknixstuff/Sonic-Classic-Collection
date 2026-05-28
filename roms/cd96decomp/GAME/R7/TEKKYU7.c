#include "../EQU.h"
#include "TEKKYU7.h"
#include "../ACTION.h"
#include "../ACTSET.h"

static void tekkyu7_init(sprite_status* pActwk);
static void tekkyu7_move(sprite_status* pActwk);
static void tekkyu7_stop(sprite_status* pActwk);

static sprite_pattern tekkyu7_pat0 = { 1, { { -16, -16, 0, 427 } } };
static sprite_pattern z73_tekkyu7_pat0 = { 1, { { -16, -16, 0, 410 } } };
sprite_pattern* pat_tekkyu7[1] = { &tekkyu7_pat0 };
sprite_pattern* z73_pat_tekkyu7[1] = { &z73_tekkyu7_pat0 };
sprite_pattern** pats_tekkyu7[3] = {
  pat_tekkyu7,
  pat_tekkyu7,
  z73_pat_tekkyu7
};




















































void tekkyu7(sprite_status* pActwk) {
  void(*tekkyu7_acttbl[3])(sprite_status*) = {
    &tekkyu7_init,
    &tekkyu7_move,
    &tekkyu7_stop
  };

  tekkyu7_acttbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[23]);
}








void tekkyu7_init(sprite_status* pActwk) {
  short tekkyu7_tbl0[24] = {
    1024,    0, 24, 12,
       0, 1024, 16,  8,
     512,    0, 48, 24,
       0,  512, 32, 16,
     256,    0, 96, 48,
       0,  256, 64, 32
  };

  short tekkyu7_tbl1[3] = {
    60,
    40,
    20
  };

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->colino = 181;
  pActwk->sprhs = 16;
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 16;
  pActwk->sproffset = 902;
  pActwk->patbase = pats_tekkyu7[stageno_i.b.l];
  ((short*)pActwk)[23] = pActwk->xposi.w.h;
  ((short*)pActwk)[25] = tekkyu7_tbl1[time_flag];

  *(int*)&pActwk->actfree[8] = tekkyu7_tbl0[time_flag * 8 + pActwk->userflag.b.h * 4] << 8;
  *(int*)&pActwk->actfree[12] = tekkyu7_tbl0[time_flag * 8 + pActwk->userflag.b.h * 4 + 1] << 8;
  ((short*)pActwk)[24] = tekkyu7_tbl0[time_flag * 8 + pActwk->userflag.b.h * 4 + 2];
  ((short*)pActwk)[26] = tekkyu7_tbl0[time_flag * 8 + pActwk->userflag.b.h * 4 + 3];

  tekkyu7_move(pActwk);
}








void tekkyu7_move(sprite_status* pActwk) {
  pActwk->xposi.l += *(int*)&pActwk->actfree[8];
  pActwk->yposi.l += *(int*)&pActwk->actfree[12];
  if (!(--((short*)pActwk)[26])) {
    pActwk->r_no0 += 2;
    ((short*)pActwk)[26] = ((short*)pActwk)[25];
    *(int*)&pActwk->actfree[8] *= -1;
    *(int*)&pActwk->actfree[12] *= -1;
  }
}








void tekkyu7_stop(sprite_status* pActwk) {
  if (!(--((short*)pActwk)[26])) {
    pActwk->r_no0 -= 2;
    ((short*)pActwk)[26] = ((short*)pActwk)[24];
  }
}
