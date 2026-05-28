#include "../EQU.h"
#include "BRANKO1.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DUMMY.h"
#include "../ETC.h"
#include "../RIDECHK.h"

static void branko1_init(sprite_status* pActwk);
static void branko1_move(sprite_status* pActwk);
static void branko1_posiset(sprite_status* pActwk);
static void branko1_ridechk(sprite_status* pActwk);

static sprite_pattern z12apat0 = { 1, { { -8, -8, 0, 524 } } };
static sprite_pattern z12cpat0 = { 1, { { -8, -8, 0, 515 } } };
static sprite_pattern z12apat1 = { 1, { { -8, -8, 0, 525 } } };
static sprite_pattern z12cpat1 = { 1, { { -8, -8, 0, 516 } } };
static sprite_pattern z12apat2 = { 1, { { -8, -8, 0, 526 } } };
static sprite_pattern z12cpat2 = { 1, { { -8, -8, 0, 517 } } };
sprite_pattern* z12abranko1pat[3] = {
  &z12apat0,
  &z12apat1,
  &z12apat2
};
sprite_pattern* z12cbranko1pat[3] = {
  &z12cpat0,
  &z12cpat1,
  &z12cpat2
};
sprite_pattern** branko1pats[3] = {
  z12abranko1pat, z12abranko1pat, z12cbranko1pat
};
static void(*branko1_move_tbl[2])(sprite_status*) = {
  &branko1_init,
  &branko1_move
};
static brankodata branko1_initbl[8] = {
  { -16384,  8,  512, -512 },
  { -16384,  2,  256, -256 },
  { -16384, -2, -512,  256 },
  { -24576,  3,  384, -384 },
  { -32768, -2, -256,  256 },
  { -32768,  2,  256, -256 },
  { -32768, -1, -256,    0 },
  { -32768,  1,  256,    0 }
};
























































void branko1(sprite_status* pActwk) {
  branko1_move_tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[29]);
}
























static void branko1_init(sprite_status* pActwk) {
  int i;
  unsigned char knum;
  sprite_status* pNewact;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->patbase = branko1pats[time_flag_i & 0x7F];

  pa_set(0, 0);

  pActwk->sprhsize = 24;
  pActwk->sprvsize = 8;

  if (pActwk->actfree[18] == 0) {
    ((unsigned short*)pActwk)[29] = pActwk->xposi.w.h;
    ((unsigned short*)pActwk)[27] = pActwk->yposi.w.h;
    pActwk->actfree[5] = knum = (unsigned char)(pActwk->userflag.b.h & 15);

    for ( ; knum > 0; --knum) {
      if (actwkchk(&pNewact) == 0) {

        pNewact->actno = 41;
        ((unsigned short*)pNewact)[29] = ((unsigned short*)pActwk)[29];

        ((unsigned short*)pNewact)[27] = ((unsigned short*)pActwk)[27];

        pNewact->userflag.b.h = pActwk->userflag.b.h;
        pNewact->actfree[5] = pActwk->actfree[5];
        pNewact->actfree[18] = knum;

        if (pActwk->actfree[5] == knum) {

          pNewact->patno = 1;
        }
        else {
          pNewact->patno = 2;
        }
      }
    }
  }


  i = (unsigned char)(pActwk->userflag.b.h & 112) >> 4;
  ((short*)pActwk)[31] = branko1_initbl[i].angle;
  ((short*)pActwk)[33] = branko1_initbl[i].accel;
  ((short*)pActwk)[28] = branko1_initbl[i].area1;
  ((short*)pActwk)[30] = branko1_initbl[i].area2;

  branko1_move(pActwk);
}





static void branko1_move(sprite_status* pActwk) {
  int xwk, ywk;

  xwk = pActwk->xposi.l;
  ywk = pActwk->yposi.l;
  branko1_posiset(pActwk);
  if (pActwk->actfree[5] == pActwk->actfree[18]) {
    pActwk->xspeed.w = (pActwk->xposi.l - xwk) >> 8;
    pActwk->yspeed.w = (pActwk->yposi.l - ywk) >> 8;
    branko1_ridechk(pActwk);
  }
}













static void branko1_posiset(sprite_status* pActwk) {
  short spdwk, sinwk, coswk;
  unsigned int lSinwk, lCoswk;
  ushort_union direc;

  if (pActwk->actfree[19] == 0) {
    spdwk = ((short*)pActwk)[26] + ((short*)pActwk)[33];

    ((short*)pActwk)[26] = spdwk;
    ((short*)pActwk)[31] += spdwk;
    if (((short*)pActwk)[28] == spdwk) {
      pActwk->actfree[19] = 255;
    }
  }
  else {
    spdwk = ((short*)pActwk)[26] - ((short*)pActwk)[33];

    ((short*)pActwk)[26] = spdwk;
    ((short*)pActwk)[31] += spdwk;
    if (((short*)pActwk)[30] == spdwk) {
      pActwk->actfree[19] = 0;
    }
  }



  direc.w = ((unsigned short*)pActwk)[31];
  sinset(direc.b.h, &sinwk, &coswk);
  spdwk = (short)((char*)pActwk)[64] << 4;
  lSinwk = sinwk * spdwk;
  lCoswk = coswk * spdwk;
  sinwk = (short)((int)lSinwk >> 4) >> 4;
  coswk = (short)((int)lCoswk >> 4) >> 4;
  pActwk->yposi.w.h = coswk + ((short*)pActwk)[27];
  pActwk->xposi.w.h = sinwk + ((short*)pActwk)[29];
}










static void branko1_ridechk(sprite_status* pActwk) {
  sprite_status* pPlayerwk;
  int i;

  for (i = 0, pPlayerwk = &actwk[0]; i < 2; ++i) {  ;
    pActwk->sprvsize = 8;


    if (ridechk(pActwk, pPlayerwk) == 0) {
      pActwk->sprvsize = 12;

      if (ridechk(pActwk, pPlayerwk) == 0) goto label1;
    }




    pActwk->sprvsize = 8;
    if (pActwk->yposi.w.h >= pPlayerwk->yposi.w.h) {



      pPlayerwk->yposi.w.h = pActwk->yposi.w.h - (short)((char*)pActwk)[23] - (short)((char*)pPlayerwk)[23] + 2;
    }





label1:
    pActwk->sprvsize = 8;
    pPlayerwk = &actwk[1];
  }
}
