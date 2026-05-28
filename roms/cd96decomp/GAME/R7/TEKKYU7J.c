#include "../EQU.h"
#include "TEKKYU7J.h"
#include "../ACTION.h"
#include "../ACTSET.h"

extern sprite_pattern** pats_tekkyu7[3];

static void tekkyu7(sprite_status* pActwk);
static void tekkyu7_init(sprite_status* pActwk);
static void tekkyu7_move(sprite_status* pActwk);
static void tekkyu7_stop(sprite_status* pActwk);
static void tekkyu7_jump(sprite_status* pActwk);

static sprite_pattern tekkyu7j_pat0 = { 1, { { -16, -16, 0, 423 } } };
static sprite_pattern z73_tekkyu7j_pat0 = { 1, { { -16, -16, 0, 406 } } };
static sprite_pattern tekkyu7j_pat1 = { 1, { { -16, 0, 0, 424 } } };
static sprite_pattern z73_tekkyu7j_pat1 = { 1, { { -16, 0, 0, 407 } } };
static sprite_pattern tekkyu7j_pat2 = { 1, { { -16, -16, 0, 425 } } };
static sprite_pattern z73_tekkyu7j_pat2 = { 1, { { -16, -16, 0, 408 } } };
static sprite_pattern tekkyu7j_pat3 = { 1, { { 0, -16, 0, 426 } } };
static sprite_pattern z73_tekkyu7j_pat3 = { 1, { { 0, -16, 0, 409 } } };
sprite_pattern* pat_tekkyu7j[4] = {
  &tekkyu7j_pat0,
  &tekkyu7j_pat1,
  &tekkyu7j_pat2,
  &tekkyu7j_pat3
};
sprite_pattern* z73_pat_tekkyu7j[4] = {
  &z73_tekkyu7j_pat0,
  &z73_tekkyu7j_pat1,
  &z73_tekkyu7j_pat2,
  &z73_tekkyu7j_pat3
};
sprite_pattern** pats_tekkyu7j[3] = {
  pat_tekkyu7j,
  pat_tekkyu7j,
  z73_pat_tekkyu7j
};



















































void tekkyu7j(sprite_status* pActwk) {
  sprite_status* pNewactwk;

  if (pActwk->userflag.b.l) {
    tekkyu7(pActwk);
  }
  else {

    if (!pActwk->r_no0) {

      pActwk->r_no0 += 2;
      pActwk->actflg |= 4;
      pActwk->sprpri = 1;
      pActwk->sproffset = 910;
      pActwk->patbase = pats_tekkyu7j[stageno_i.b.l];
      pActwk->patno = pActwk->userflag.b.h;
      ((short*)pActwk)[23] = 150;
      pActwk->sprhs = 16;
      pActwk->sprhsize = 16;
      pActwk->sprvsize = 16;
    }

    if (!(--((short*)pActwk)[23])) {
      ((short*)pActwk)[23] = 150;
      if (actwkchk(&pNewactwk) == 0) {
        pNewactwk->actno = pActwk->actno;
        pNewactwk->userflag.b.h = pActwk->userflag.b.h;
        pNewactwk->userflag.b.l = -1;
        pNewactwk->xposi.w.h = pActwk->xposi.w.h;
        pNewactwk->yposi.w.h = pActwk->yposi.w.h;
      }
    }
    actionsub(pActwk);
    frameout_s(pActwk);
  }
}








static void tekkyu7(sprite_status* pActwk) {
  void(*tekkyu7_acttbl[4])(sprite_status*) = {
    &tekkyu7_init,
    &tekkyu7_move,
    &tekkyu7_stop,
    &tekkyu7_jump
  };

  tekkyu7_acttbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
}








void tekkyu7_init(sprite_status* pActwk) {
  short wD0;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 4;
  pActwk->colino = 181;
  pActwk->sprhs = 16;
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 16;
  pActwk->sproffset = 902;
  pActwk->patbase = pats_tekkyu7[stageno_i.b.l];
  ((short*)pActwk)[25] = 32;

  ((int*)pActwk)[13] = 32768;
  pActwk->actfree[21] = 0;
  if (!(pActwk->userflag.b.h & 1)) {
    pActwk->actfree[21] = 255;
    ((int*)pActwk)[13] *= -1;
  }
  pActwk->actfree[0] = 0;
  wD0 = pActwk->xposi.w.h;
  if (pActwk->userflag.b.h < 2) {
    pActwk->actfree[0] = 1;
    wD0 = pActwk->yposi.w.h;
  }
  ((short*)pActwk)[24] = wD0;

  tekkyu7_move(pActwk);
}








void tekkyu7_move(sprite_status* pActwk) {
  if (pActwk->actfree[0])
    pActwk->yposi.l += ((int*)pActwk)[13];
  else
    pActwk->xposi.l += ((int*)pActwk)[13];
  if (!(--((short*)pActwk)[25])) {
    pActwk->r_no0 += 2;
    ((short*)pActwk)[25] = 30;
  }
}








void tekkyu7_stop(sprite_status* pActwk) {
  if (!(--((short*)pActwk)[25])) {
    pActwk->r_no0 += 2;
    ((int*)pActwk)[13] = 393216;
    ((int*)pActwk)[14] = -16384;
    if (!(pActwk->userflag.b.h & 1)) {
      ((int*)pActwk)[13] *= -1;
      ((int*)pActwk)[14] *= -1;
    }
  }
}








void tekkyu7_jump(sprite_status* pActwk) {
  short wD0;
  unsigned char bD0;

  ((int*)pActwk)[13] += ((int*)pActwk)[14];
  if (pActwk->actfree[0]) {
    pActwk->yposi.l += ((int*)pActwk)[13];
    wD0 = pActwk->yposi.w.h;
  }
  else {
    pActwk->xposi.l += ((int*)pActwk)[13];
    wD0 = pActwk->xposi.w.h;
  }
  bD0 = 0;
  if (wD0 < ((short*)pActwk)[24])
    bD0 = 255;
  if (pActwk->actfree[21] != bD0)
    frameout(pActwk);
}
