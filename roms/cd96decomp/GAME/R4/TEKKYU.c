#include "../EQU.h"
#include "TEKKYU.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"

static void tekkyu_main(sprite_status* pActwk);
static void act_init(sprite_status* pActwk);
static void act_move(sprite_status* pActwk);
static void tekkyu_opt(sprite_status* pActwk);
static void opt_act_init(sprite_status* pActwk);
static void opt_act_move(sprite_status* pActwk);

static sprite_pattern z4a_tekkyu_pat00 = { 1, { { -8, -8, 0, 467 } } };
static sprite_pattern z42c_tekkyu_pat00 = { 1, { { -8, -8, 0, 472 } } };
static sprite_pattern z43_tekkyu_pat00 = { 1, { { -8, -8, 0, 493 } } };
sprite_pattern* z4a_pat_tekkyu[1] = { &z4a_tekkyu_pat00 };
sprite_pattern* z42c_pat_tekkyu[1] = { &z42c_tekkyu_pat00 };
sprite_pattern* z43_pat_tekkyu[1] = { &z43_tekkyu_pat00 };
sprite_pattern** pat_tyuusin[3][3] = {
  { z4a_pat_tekkyu, z4a_pat_tekkyu, z4a_pat_tekkyu },
  { z4a_pat_tekkyu, z4a_pat_tekkyu, z42c_pat_tekkyu },
  { 0, 0, z43_pat_tekkyu }
};
static void(*act_tbl[2])(sprite_status*) = {
  &act_init,
  &act_move
};
static sprite_pattern z4a_kusari_pat00 = { 1, { { -8, -8, 0, 468 } } };
static sprite_pattern z42c_kusari_pat00 = { 1, { { -8, -8, 0, 473 } } };
static sprite_pattern z43_kusari_pat00 = { 1, { { -8, -8, 0, 494 } } };
sprite_pattern* z4a_pat_kusari[1] = { &z4a_kusari_pat00 };
sprite_pattern* z42c_pat_kusari[1] = { &z42c_kusari_pat00 };
sprite_pattern* z43_pat_kusari[1] = { &z43_kusari_pat00 };
sprite_pattern** pats_kusari[3][3] = {
  { z4a_pat_kusari, z4a_pat_kusari, z4a_pat_kusari },
  { z4a_pat_kusari, z4a_pat_kusari, z42c_pat_kusari },
  { 0, 0, z43_pat_kusari }
};
static sprite_pattern z4a_tekkyu1_pat00 = { 1, { { -16, -16, 0, 469 } } };
static sprite_pattern z42c_tekkyu1_pat00 = { 1, { { -16, -16, 0, 474 } } };
static sprite_pattern z43_tekkyu1_pat00 = { 1, { { -16, -16, 0, 495 } } };
sprite_pattern* z4a_pat_tekkyu1[1] = { &z4a_tekkyu1_pat00 };
sprite_pattern* z42c_pat_tekkyu1[1] = { &z42c_tekkyu1_pat00 };
sprite_pattern* z43_pat_tekkyu1[1] = { &z43_tekkyu1_pat00 };
sprite_pattern** pats_tekkyu1[3][3] = {
  { z4a_pat_tekkyu1, z4a_pat_tekkyu1, z4a_pat_tekkyu1 },
  { z4a_pat_tekkyu1, z4a_pat_tekkyu1, z42c_pat_tekkyu1 },
  { 0, 0, z43_pat_tekkyu1 }
};
static void(*opt_act_tbl[2])(sprite_status*) = {
  &opt_act_init,
  &opt_act_move
};

















































void tekkyu(sprite_status* pActwk) {
  if (pActwk->userflag.b.h & 128) {
    tekkyu_opt(pActwk);
  } else {
    tekkyu_main(pActwk);
  }
}





static void tekkyu_main(sprite_status* pActwk) {
  act_tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s(pActwk);
}





static void act_init(sprite_status* pActwk) {
  sprite_status* pNewact;
  short* pActidx;
  int i;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sprhsize = 8;
  pActwk->sprvsize = 8;
  pActwk->patbase = pat_tyuusin[stageno_i.b.l][time_flag_i & 0x7F];
  pActwk->sproffset = 872;

  if (pActwk->userflag.b.h == 0) {
    ((short*)pActwk)[24] = 256;
  } else {
    ((short*)pActwk)[24] = -256;
  }

  pActidx = &((short*)pActwk)[25];
  for (i = 0; i < 6; ++i) {
    if (actwkchk(&pNewact) != 0) {
      frameout(pActwk);
      return;
    }

    *pActidx++ = pNewact - actwk;
    pNewact->actno = pActwk->actno;
    pNewact->userflag.b.h = -1;
    pNewact->sprhsize = 8;
    pNewact->sprvsize = 8;
    ((short*)pNewact)[33] = pActwk - actwk;
  }

  pNewact->userflag.b.h = -2;
  act_move(pActwk);
}





static void act_move(sprite_status* pActwk) {
  int_union ldSin, ldCos;
  int sinsv1, sinsv2, cossv1, cossv2;
  sprite_status* pSubact;

  ((short*)pActwk)[23] += ((short*)pActwk)[24];

  sinset(pActwk->actfree[1], &ldSin.w.h, &ldCos.w.h);
  ldSin.w.l = ldCos.w.l = 0;

  ldSin.l >>= 2;
  ldCos.l >>= 2;
  sinsv1 = ldSin.l;
  cossv1 = ldCos.l;

  ldSin.l >>= 1;
  ldCos.l >>= 1;
  sinsv2 = ldSin.l;
  cossv2 = ldCos.l;

  ldSin.l >>= 1;
  ldCos.l >>= 1;

  pSubact = &actwk[((short*)pActwk)[25]];
  *(int*)&pSubact->actfree[4] = pActwk->yposi.l + ldSin.l;
  *(int*)&pSubact->actfree[0] = pActwk->xposi.l + ldCos.l;

  pSubact = &actwk[((short*)pActwk)[26]];
  *(int*)&pSubact->actfree[4] = pActwk->yposi.l + sinsv2;
  *(int*)&pSubact->actfree[0] = pActwk->xposi.l + cossv2;

  pSubact = &actwk[((short*)pActwk)[27]];
  *(int*)&pSubact->actfree[4] = pActwk->yposi.l + ldSin.l + sinsv2;
  *(int*)&pSubact->actfree[0] = pActwk->xposi.l + ldCos.l + cossv2;

  pSubact = &actwk[((short*)pActwk)[28]];
  *(int*)&pSubact->actfree[4] = pActwk->yposi.l + sinsv1;
  *(int*)&pSubact->actfree[0] = pActwk->xposi.l + cossv1;

  pSubact = &actwk[((short*)pActwk)[29]];
  *(int*)&pSubact->actfree[4] = pActwk->yposi.l + ldSin.l + sinsv1;
  *(int*)&pSubact->actfree[0] = pActwk->xposi.l + ldCos.l + cossv1;

  pSubact = &actwk[((short*)pActwk)[30]];
  *(int*)&pSubact->actfree[4] = pActwk->yposi.l + sinsv2 + sinsv1;
  *(int*)&pSubact->actfree[0] = pActwk->xposi.l + cossv2 + cossv1;
}



































static void tekkyu_opt(sprite_status* pActwk) {
  opt_act_tbl[pActwk->r_no0 / 2](pActwk);
  if (actwk[((short*)pActwk)[33]].actno != 54) {

    frameout(pActwk);
  } else {
    actionsub(pActwk);
  }
}





static void opt_act_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;

  if (pActwk->userflag.b.h == -1) {
    pActwk->sprpri = 3;
    pActwk->patbase = pats_kusari[stageno_i.b.l][time_flag_i & 0x7F];
    pActwk->sproffset = 872;
  }
  else {
    pActwk->sprpri = 2;
    pActwk->patbase = pats_tekkyu1[stageno_i.b.l][time_flag_i & 0x7F];
    pActwk->sproffset = 880;
    pActwk->colino = 169;
  }

  opt_act_move(pActwk);
}





static void opt_act_move(sprite_status* pActwk) {
  pActwk->xposi.w.h = ((short*)pActwk)[24];
  pActwk->yposi.w.h = ((short*)pActwk)[26];
}
