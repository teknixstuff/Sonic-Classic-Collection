#include "../EQU.h"
#include "HARID4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../RIDECHK.h"

static void act_init(sprite_status* pActwk);
static void act_wait(sprite_status* pActwk);
static void act_slide(sprite_status* pActwk);
static void act_slide1(sprite_status* pActwk);
static void act_down(sprite_status* pActwk);
static void act_down1(sprite_status* pActwk);
static void act_stop(sprite_status* pActwk);

static sprite_pattern z41apat00 = { 2, { { -16, -64, 0, 445 }, { -16, 32, 0, 444 } } };
static sprite_pattern z41cpat00 = { 2, { { -16, -64, 0, 433 }, { -16, 32, 0, 432 } } };
static sprite_pattern z41dpat00 = { 2, { { -16, -64, 0, 468 }, { -16, 32, 0, 467 } } };
static sprite_pattern pat01;
sprite_pattern* z41a_pat_harid4[2] = {
  &z41apat00,
  &pat01
};
sprite_pattern* z41c_pat_harid4[2] = {
  &z41cpat00,
  &pat01
};
sprite_pattern* z41d_pat_harid4[2] = {
  &z41dpat00,
  &pat01
};
sprite_pattern** pats_harid4[4] = {
  z41a_pat_harid4,
  z41a_pat_harid4,
  z41d_pat_harid4,
  z41c_pat_harid4
};
static void(*hari4_act_tbl[7])(sprite_status*) = {
  &act_init,
  &act_wait,
  &act_slide,
  &act_slide1,
  &act_down,
  &act_down1,
  &act_stop
};








































































void harid4(sprite_status* pActwk) {
  if (pActwk->userflag.b.h & 128) {

    if (actwk[((short*)pActwk)[33]].actno != 50) {
      frameout(pActwk);
    }

    actionsub(pActwk);
  }
  else {
    if (pActwk->r_no0 == 0 || pActwk->actflg & 128) {

      hari4_act_tbl[pActwk->r_no0 / 2](pActwk);
      hitchk(pActwk, &actwk[0]);
    }


    actionsub(pActwk);
    frameout_s(pActwk);
  }
}





static void act_init(sprite_status* pActwk) {
  int xacwk;
  sprite_status* pNewact;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sprhs = 16;
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 64;
  pActwk->sproffset = 928;
  pActwk->patbase = pats_harid4[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];

  if (waterposi_m >= pActwk->yposi.w.h) {
    xacwk = 12288;
  } else {
    xacwk = 4096;
  }
  ((int*)pActwk)[14] = xacwk;

  if (actwkchk2(pActwk, &pNewact) == 0) {
    pNewact->actno = pActwk->actno;
    pNewact->userflag.b.h = -1;
    pNewact->xposi.w.h = pActwk->xposi.w.h;
    pNewact->yposi.w.h = pActwk->yposi.w.h + 48;
    ((short*)pNewact)[33] = pActwk - actwk;
    ((short*)pActwk)[32] = pNewact - actwk;
    pNewact->colino = 176;
    pNewact->actflg = pActwk->actflg;
    pNewact->sprpri = pActwk->sprpri;
    pNewact->sprhs = 16;
    pNewact->sprhsize = 16;
    pNewact->sprvsize = 16;
    pNewact->sproffset = 928;
    pNewact->patbase = pats_harid4[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
    pNewact->patno = 1;
  }


}





static void act_wait(sprite_status* pActwk) {
  short wk;

  wk = actwk[0].yposi.w.h - pActwk->yposi.w.h;
  wk -= 64;
  if ((unsigned short)wk >= 128) return;



  wk = actwk[0].xposi.w.h - pActwk->xposi.w.h;
  wk += 16;
  if ((unsigned short)wk >= 32) return;




  pActwk->r_no0 += 2;
  pActwk->yspeed.w = 256;
  ((short*)pActwk)[27] = 20;
}





static void act_slide(sprite_status* pActwk) {
  int spdwk;

  spdwk = *(int*)&pActwk->actfree[0];
  pActwk->yposi.l += spdwk;
  actwk[((short*)pActwk)[32]].yposi.l += spdwk;
  *(int*)&pActwk->actfree[0] += 8192;

  if (--((short*)pActwk)[27] < 0) {
    pActwk->r_no0 += 2;
    *(int*)&pActwk->actfree[0] = 0;
    ((short*)pActwk)[27] = 30;
  }
}





static void act_slide1(sprite_status* pActwk) {
  if (--((short*)pActwk)[27] < 0) {
    pActwk->r_no0 += 2;
  }
}





static void act_down(sprite_status* pActwk) {
  int spdwk;
  short ret;

  spdwk = *(int*)&pActwk->actfree[0];
  pActwk->yposi.l += spdwk;
  actwk[((short*)pActwk)[32]].yposi.l += spdwk;
  *(int*)&pActwk->actfree[0] += ((int*)pActwk)[14];

  if ((ret = emycol_d(pActwk)) < 0) {
    pActwk->r_no0 += 2;
    pActwk->yposi.w.h += ret;
    pActwk->yspeed.w = 0;
    *(int*)&pActwk->actfree[4] = 0x200000;

    frameout(&actwk[((short*)pActwk)[32]]);
  }
}





static void act_down1(sprite_status* pActwk) {
  int spdwk;

  spdwk = *(int*)&pActwk->actfree[0];
  pActwk->yposi.l += spdwk;

  if ((*(int*)&pActwk->actfree[4] -= spdwk) < 0) {
    pActwk->r_no0 += 2;
  }
}





static void act_stop(sprite_status* pActwk) {

  pActwk = pActwk;
}
