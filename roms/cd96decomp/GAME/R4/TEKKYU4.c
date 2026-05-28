#include "../EQU.h"
#include "TEKKYU4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"

static void act_init_sub(sprite_status* pActwk, sprite_status* pNewactwk);

sprite_pattern z41c_tekkyu4_pat0 = { 1, { { -16, -16, 0, 449 } } };
sprite_pattern z41d_tekkyu4_pat0 = { 1, { { -16, -16, 0, 435 } } };
sprite_pattern z42a_tekkyu4_pat0 = { 1, { { -16, -16, 0, 469 } } };
sprite_pattern z42c_tekkyu4_pat0 = { 1, { { -16, -16, 0, 474 } } };
sprite_pattern* z41c_pat_tekkyu4[1] = { &z41c_tekkyu4_pat0 };
sprite_pattern* z41d_pat_tekkyu4[1] = { &z41d_tekkyu4_pat0 };
sprite_pattern* z42a_pat_tekkyu4[1] = { &z42a_tekkyu4_pat0 };
sprite_pattern* z42c_pat_tekkyu4[1] = { &z42c_tekkyu4_pat0 };
sprite_pattern** pats_tekkyu4[2][4] = {
  { z41c_pat_tekkyu4, z41c_pat_tekkyu4, z41d_pat_tekkyu4, z41c_pat_tekkyu4 },
  { z42c_pat_tekkyu4, z42a_pat_tekkyu4, z42c_pat_tekkyu4, z42c_pat_tekkyu4 }
};





















































void tekkyu4(sprite_status* pActwk) {
  sprite_status* pMainactwk;

  void(*tekkyu4_acttbl[2])(sprite_status*) = {
    &tekkyu4init,
    &tekkyu4move
  };


  if (((short*)pActwk)[33]) {
    pMainactwk = &actwk[((short*)pActwk)[33]];
    if (pMainactwk->actno != 56) {
      frameout(pActwk);
      return;
    }

  }
  tekkyu4_acttbl[pActwk->r_no0 / 2](pActwk);







}








void tekkyu4init(sprite_status* pActwk) {
  sprite_status *pNewactwk1, *pNewactwk2, *pNewactwk3;
  short wD0;

  ((short*)pActwk)[28] = pActwk->xposi.w.h;

  if (actwkchk(&pNewactwk3) != 0) {
    frameout(pActwk);
    return;
  }

  pNewactwk3->actno = pActwk->actno;
  pNewactwk3->r_no0 = 2;
  ((short*)pNewactwk3)[33] = pActwk - actwk;

  if (actwkchk(&pNewactwk2) != 0) {
    frameout(pActwk);
    return;
  }

  pNewactwk2->actno = pActwk->actno;
  pNewactwk2->r_no0 = 2;
  ((short*)pNewactwk2)[33] = pActwk - actwk;

  if (actwkchk(&pNewactwk1) != 0) {
    frameout(pActwk);
    return;
  }

  pNewactwk1->actno = pActwk->actno;
  pNewactwk1->r_no0 = 2;
  ((short*)pNewactwk1)[33] = pActwk - actwk;

  wD0 = -2048;

  if (pActwk->userflag.b.h & 128) wD0 *= -1;

  ((short*)pNewactwk1)[25] = (int)wD0;
  ((short*)pNewactwk2)[25] = wD0 * 2;
  ((short*)pNewactwk3)[25] = wD0 * 3;

  ((short*)pActwk)[26] = 256;
  if (pActwk->userflag.b.h & 128) ((short*)pActwk)[26] *= -1;

  if ((wD0 = pActwk->userflag.b.h) & 128) wD0 *= -1;

  ((short*)pActwk)[27] = wD0 & 127;

  pActwk->sprpri = 1;
  pNewactwk1->sprpri = 2;
  pNewactwk2->sprpri = 3;
  pNewactwk3->sprpri = 4;

  act_init_sub(pActwk, pActwk);
  act_init_sub(pActwk, pNewactwk1);
  act_init_sub(pActwk, pNewactwk2);
  act_init_sub(pActwk, pNewactwk3);
}


static void act_init_sub(sprite_status* pActwk, sprite_status* pNewactwk) {
  pNewactwk->actflg |= 4;
  pNewactwk->colino = 169;
  pNewactwk->sprhs = 16;
  pNewactwk->sprhsize = 16;
  pNewactwk->sprvsize = 16;
  pNewactwk->sproffset = 880;
  pNewactwk->patbase = pats_tekkyu4[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  pNewactwk->r_no0 = 2;
  ((short*)pNewactwk)[23] = pActwk->xposi.w.h;
  ((short*)pNewactwk)[24] = pActwk->yposi.w.h;
  ((short*)pNewactwk)[26] = ((short*)pActwk)[26];
  ((short*)pNewactwk)[27] = ((short*)pActwk)[27];
}








void tekkyu4move(sprite_status* pActwk) {
  unsigned short wD0, wD1;

  ((unsigned short*)pActwk)[25] += ((unsigned short*)pActwk)[26];


  sinset(((short*)pActwk)[25] >> 8, (short*)&wD0, (short*)&wD1);





  wD0 = (short)wD0 >> ((unsigned short*)pActwk)[27];
  wD1 = (short)wD1 >> ((unsigned short*)pActwk)[27];




  pActwk->xposi.w.h = ((short*)pActwk)[23] + (short)wD1;
  pActwk->yposi.w.h = ((short*)pActwk)[24] + (short)wD0;

  actionsub(pActwk);

  if (!((short*)pActwk)[33]) frameout_s(pActwk);

}
