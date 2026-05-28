#include "../EQU.h"
#include "KANABUN.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static sprite_pattern pat_e00 = {
  1,
  { { -16, -16, 128, 415 } }
};
static sprite_pattern pat_e01 = {
  1,
  { { -16, -16, 128, 416 } }
};
static sprite_pattern pat_e02 = {
  1,
  { { -12, -12, 128, 417 } }
};
static sprite_pattern pat_e03 = {
  1,
  { { -12, -12, 128, 418 } }
};
static sprite_pattern pat_e04 = {
  1,
  { { -12, -12, 0, 419 } }
};
static sprite_pattern pat_e05 = {
  1,
  { { -12, -12, 0, 420 } }
};
static sprite_pattern pat_e06 = {
  1,
  { { -12, -12, 0, 421 } }
};
static sprite_pattern pat_e07 = {
  1,
  { { -12, -12, 0, 422 } }
};
sprite_pattern* pat_kanabun_e[8] = {
  &pat_e00,
  &pat_e01,
  &pat_e02,
  &pat_e03,
  &pat_e04,
  &pat_e05,
  &pat_e06,
  &pat_e07
};
static sprite_pattern pat_b00 = {
  1,
  { { -16, -16, 128, 407 } }
};
static sprite_pattern pat_b01 = {
  1,
  { { -16, -16, 128, 408 } }
};
static sprite_pattern pat_b02 = {
  1,
  { { -12, -12, 128, 409 } }
};
static sprite_pattern pat_b03 = {
  1,
  { { -12, -12, 128, 410 } }
};
static sprite_pattern pat_b04 = {
  1,
  { { -12, -12, 0, 411 } }
};
static sprite_pattern pat_b05 = {
  1,
  { { -12, -12, 0, 412 } }
};
static sprite_pattern pat_b06 = {
  1,
  { { -12, -12, 0, 413 } }
};
static sprite_pattern pat_b07 = {
  1,
  { { -12, -12, 0, 414 } }
};
sprite_pattern* pat_kanabun_b[8] = {
  &pat_b00,
  &pat_b01,
  &pat_b02,
  &pat_b03,
  &pat_b04,
  &pat_b05,
  &pat_b06,
  &pat_b07
};
static unsigned char pchg_e00[66] = {
  1, 6, 7, 6, 7, 6, 7, 6, 7, 4,
  5, 4, 5, 4, 5, 4, 5, 2, 3, 2,
  3, 2, 3, 2, 3, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  1, 2, 3, 2, 3, 2, 3, 2, 3, 4,
  5, 4, 5, 4, 5, 4, 5, 6, 7, 6,
  7, 6, 7, 6, 7, 255
};
static unsigned char* pchg_e[1] = { pchg_e00 };
static unsigned char pchg_b00[66] = {
  3, 6, 7, 6, 7, 6, 7, 6, 7, 4,
  5, 4, 5, 4, 5, 4, 5, 2, 3, 2,
  3, 2, 3, 2, 3, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
  1, 2, 3, 2, 3, 2, 3, 2, 3, 4,
  5, 4, 5, 4, 5, 4, 5, 6, 7, 6,
  7, 6, 7, 6, 7, 255
};
static unsigned char* pchg_b[1] = { pchg_b00 };
static char tbl0[4] = { 47, 48, 48, 0 };
















































































void kanabun(sprite_status* pActwk) {
  int_union poswk;
  int spdwk;
  short sinwk, coswk;

  if (enemy_suicide(pActwk)) return;



  if (!pActwk->r_no0) {

    pActwk->r_no0 += 2;
    pActwk->actflg |= 4;
    pActwk->sprpri = 3;
    pActwk->sproffset = 9193;
    pActwk->sprhs = 16;
    pActwk->sprhsize = 16;
    pActwk->sprvsize = 16;
    ((short*)pActwk)[31] = pActwk->xposi.w.h;
    ((short*)pActwk)[26] = pActwk->yposi.w.h;
    ((short*)pActwk)[25] = -32768;

    if (!pActwk->userflag.b.h) {
      pActwk->patbase = pat_kanabun_e;
      *(unsigned char***)&pActwk->actfree[12] = pchg_e;
      ((short*)pActwk)[28] = -512;
      ((int*)pActwk)[16] = -16384;
    } else {
      pActwk->patbase = pat_kanabun_b;
      *(unsigned char***)&pActwk->actfree[12] = pchg_b;
      ((short*)pActwk)[28] = -256;
      ((int*)pActwk)[16] = -16384;
    }
  }


  poswk.l = spdwk = pActwk->xposi.l + ((int*)pActwk)[16];
  poswk.l = (unsigned int)poswk.l >> 16 & 65535 | poswk.l << 16 & -65536;

  if ((poswk.w.l -= ((short*)pActwk)[31]) < 0) {
    poswk.w.l *= -1;
  }


  if (poswk.w.l > 64) {
    ((int*)pActwk)[16] *= -1;
    spdwk += ((int*)pActwk)[16];
    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;
    ((short*)pActwk)[27] = 0;
    pActwk->mstno.w = 255;
  }


  pActwk->xposi.l = spdwk;
  poswk.w.l = ((short*)pActwk)[27] + ((short*)pActwk)[28];

  ((short*)pActwk)[27] = poswk.w.l;
  poswk.w.l = (unsigned short)poswk.w.l >> 8;
  sinset(poswk.w.l, &sinwk, &coswk);
  poswk.w.l = sinwk;
  poswk.l = (unsigned int)poswk.l >> 16 & 65535 | poswk.l << 16 & -65536;
  poswk.l >>= 2;
  poswk.l += *(int*)&pActwk->actfree[4];
  pActwk->yposi.l = poswk.l;

  patchg(pActwk, *(unsigned char***)&pActwk->actfree[12]);
  pActwk->colino = tbl0[pActwk->patno >> 1];
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[31]);
}
