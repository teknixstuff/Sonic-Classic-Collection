#include "../EQU.h"
#include "FRIEND4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void m_init(sprite_status* pActwk);
static void m0move(sprite_status* pActwk);
static void m1move(sprite_status* pActwk);

static unsigned char pchg0[30] = {
  0, 0, 0, 2, 0, 0, 2, 1, 1, 2,
  1, 1, 2, 0, 0, 2, 2, 0, 0, 2,
  2, 1, 1, 2, 2, 1, 1, 2, 2, 255
};
static unsigned char pchg1[4] = { 19, 0, 1, 255 };
static unsigned char* pchg[2] = {
  pchg0,
  pchg1
};

static sprite_pattern z41a_spr_friend4_00 = { 1, { { -8, -12, 0, 494 } } };
static sprite_pattern z41b_spr_friend4_00 = { 1, { { -8, -12, 0, 455 } } };
static sprite_pattern z41c_spr_friend4_00 = { 1, { { -8, -12, 0, 472 } } };
static sprite_pattern z41d_spr_friend4_00 = { 1, { { -8, -12, 0, 462 } } };
static sprite_pattern z42a_spr_friend4_00 = { 1, { { -8, -12, 0, 500 } } };
static sprite_pattern z42b_spr_friend4_00 = { 1, { { -8, -12, 0, 453 } } };
static sprite_pattern z42c_spr_friend4_00 = { 1, { { -8, -12, 0, 457 } } };
static sprite_pattern z43c_spr_friend4_00 = { 1, { { -8, -12, 0, 435 } } };
static sprite_pattern z41a_spr_friend4_01 = { 1, { { -8, -12, 0, 495 } } };
static sprite_pattern z41b_spr_friend4_01 = { 1, { { -8, -12, 0, 456 } } };
static sprite_pattern z41c_spr_friend4_01 = { 1, { { -8, -12, 0, 473 } } };
static sprite_pattern z41d_spr_friend4_01 = { 1, { { -8, -12, 0, 463 } } };
static sprite_pattern z42a_spr_friend4_01 = { 1, { { -8, -12, 0, 501 } } };
static sprite_pattern z42b_spr_friend4_01 = { 1, { { -8, -12, 0, 454 } } };
static sprite_pattern z42c_spr_friend4_01 = { 1, { { -8, -12, 0, 458 } } };
static sprite_pattern z43c_spr_friend4_01 = { 1, { { -8, -12, 0, 436 } } };
static sprite_pattern z41a_spr_friend4_10 = { 1, { { -8, -12, 0, 496 } } };
static sprite_pattern z41b_spr_friend4_10 = { 1, { { -8, -12, 0, 457 } } };
static sprite_pattern z41c_spr_friend4_10 = { 1, { { -8, -12, 0, 474 } } };
static sprite_pattern z41d_spr_friend4_10 = { 1, { { -8, -12, 0, 464 } } };
static sprite_pattern z42a_spr_friend4_10 = { 1, { { -8, -12, 0, 502 } } };
static sprite_pattern z42b_spr_friend4_10 = { 1, { { -8, -12, 0, 455 } } };
static sprite_pattern z42c_spr_friend4_10 = { 1, { { -8, -12, 0, 459 } } };
static sprite_pattern z43c_spr_friend4_10 = { 1, { { -8, -12, 0, 437 } } };
static sprite_pattern z41a_spr_friend4_11 = { 1, { { -8, -12, 0, 497 } } };
static sprite_pattern z41b_spr_friend4_11 = { 1, { { -8, -12, 0, 458 } } };
static sprite_pattern z41c_spr_friend4_11 = { 1, { { -8, -12, 0, 475 } } };
static sprite_pattern z41d_spr_friend4_11 = { 1, { { -8, -12, 0, 465 } } };
static sprite_pattern z42a_spr_friend4_11 = { 1, { { -8, -12, 0, 503 } } };
static sprite_pattern z42b_spr_friend4_11 = { 1, { { -8, -12, 0, 456 } } };
static sprite_pattern z42c_spr_friend4_11 = { 1, { { -8, -12, 0, 460 } } };
static sprite_pattern z43c_spr_friend4_11 = { 1, { { -8, -12, 0, 438 } } };
static sprite_pattern z41a_spr_friend4_99 = { 0, { { -8, -12, 0, 497 } } };
static sprite_pattern z41b_spr_friend4_99 = { 0, { { -8, -12, 0, 458 } } };
static sprite_pattern z41c_spr_friend4_99 = { 0, { { -8, -12, 0, 475 } } };
static sprite_pattern z41d_spr_friend4_99 = { 0, { { -8, -12, 0, 465 } } };
static sprite_pattern z42a_spr_friend4_99 = { 0, { { -8, -12, 0, 503 } } };
static sprite_pattern z42b_spr_friend4_99 = { 0, { { -8, -12, 0, 456 } } };
static sprite_pattern z42c_spr_friend4_99 = { 0, { { -8, -12, 0, 460 } } };
static sprite_pattern z43c_spr_friend4_99 = { 0, { { -8, -12, 0, 438 } } };
sprite_pattern* z41a_pat_friend0[3] = {
  &z41a_spr_friend4_00,
  &z41a_spr_friend4_01,
  &z41a_spr_friend4_99
};
sprite_pattern* z41b_pat_friend0[3] = {
  &z41b_spr_friend4_00,
  &z41b_spr_friend4_01,
  &z41b_spr_friend4_99
};
sprite_pattern* z41c_pat_friend0[3] = {
  &z41c_spr_friend4_00,
  &z41c_spr_friend4_01,
  &z41c_spr_friend4_99
};
sprite_pattern* z41d_pat_friend0[3] = {
  &z41d_spr_friend4_00,
  &z41d_spr_friend4_01,
  &z41d_spr_friend4_99
};
sprite_pattern* z42a_pat_friend0[3] = {
  &z42a_spr_friend4_00,
  &z42a_spr_friend4_01,
  &z42a_spr_friend4_99
};
sprite_pattern* z42b_pat_friend0[3] = {
  &z42b_spr_friend4_00,
  &z42b_spr_friend4_01,
  &z42b_spr_friend4_99
};
sprite_pattern* z42c_pat_friend0[3] = {
  &z42c_spr_friend4_00,
  &z42c_spr_friend4_01,
  &z42c_spr_friend4_99
};
sprite_pattern* z43c_pat_friend0[3] = {
  &z43c_spr_friend4_00,
  &z43c_spr_friend4_01,
  &z43c_spr_friend4_99
};
static sprite_pattern** pats_friend0[3][4] = {
  { z41b_pat_friend0, z41a_pat_friend0, z41d_pat_friend0, z41c_pat_friend0 },
  { z42b_pat_friend0, z42a_pat_friend0, z42c_pat_friend0, z42c_pat_friend0 },
  { 0, 0, z43c_pat_friend0, z43c_pat_friend0 }
};
sprite_pattern* z41a_pat_friend1[3] = {
  &z41a_spr_friend4_10,
  &z41a_spr_friend4_11,
  &z41a_spr_friend4_99
};
sprite_pattern* z41b_pat_friend1[3] = {
  &z41b_spr_friend4_10,
  &z41b_spr_friend4_11,
  &z41b_spr_friend4_99
};
sprite_pattern* z41c_pat_friend1[3] = {
  &z41c_spr_friend4_10,
  &z41c_spr_friend4_11,
  &z41c_spr_friend4_99
};
sprite_pattern* z41d_pat_friend1[3] = {
  &z41d_spr_friend4_10,
  &z41d_spr_friend4_11,
  &z41d_spr_friend4_99
};
sprite_pattern* z42a_pat_friend1[3] = {
  &z42a_spr_friend4_10,
  &z42a_spr_friend4_11,
  &z42a_spr_friend4_99
};
sprite_pattern* z42b_pat_friend1[3] = {
  &z42b_spr_friend4_10,
  &z42b_spr_friend4_11,
  &z42b_spr_friend4_99
};
sprite_pattern* z42c_pat_friend1[3] = {
  &z42c_spr_friend4_10,
  &z42c_spr_friend4_11,
  &z42c_spr_friend4_99
};
sprite_pattern* z43c_pat_friend1[3] = {
  &z43c_spr_friend4_10,
  &z43c_spr_friend4_11,
  &z43c_spr_friend4_99
};
static sprite_pattern** pats_friend1[3][4] = {
  { z41b_pat_friend1, z41a_pat_friend1, z41d_pat_friend1, z41c_pat_friend1 },
  { z42b_pat_friend1, z42a_pat_friend1, z42c_pat_friend1, z42c_pat_friend1 },
  { 0, 0, z43c_pat_friend1, z43c_pat_friend1 }
};
static unsigned short tbl0sproffset[11] = {
  1104, 1104, 1104, 0,
  1104, 1104, 1104, 0,
     0,    0, 1104
};


void friend4(sprite_status* pActwk) {
  if (!friend_suicide(pActwk)) {
    if ((char)pActwk->r_no0 < 0) {
      m0move(pActwk); return;
    }

    if (pActwk->r_no0 != 0) {
      m1move(pActwk); return;
    }
    m_init(pActwk);
  }
}



static void m_init(sprite_status* pActwk) {
  short_union temp;

  pActwk->actflg |= 4;
  pActwk->sprpri = 5;
  pActwk->sprhs = 8;
  pActwk->sprhsize = 8;
  pActwk->sprvsize = 12;

  temp.w = 0;
  temp.b.l = stageno.b.l;
  temp.w <<= 2;
  temp.b.l = temp.b.l + (char)time_flag;
  temp.w <<= 1;
  pActwk->sproffset = tbl0sproffset[temp.w];
  if (pActwk->userflag.b.h & 1) {
    pActwk->sproffset += 8192;
  }

  pActwk->patbase = pats_friend0[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  if (pActwk->userflag.b.h & 1)
    pActwk->patbase = pats_friend1[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  ((short*)pActwk)[25] = pActwk->yposi.w.h;
  if (pActwk->userflag.b.h < 0) {

    pActwk->r_no0 -= 2;
    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;
    ((short*)pActwk)[30] = pActwk->xposi.w.h;
    ((int*)pActwk)[14] = 512;
    if (pActwk->userflag.b.h & 1) {

      pActwk->actflg ^= 1;
      pActwk->cddat ^= 1;
      ((int*)pActwk)[14] *= -1;
      ((int*)pActwk)[13] = 12288;
    }
  }
  else {


    pActwk->r_no0 += 2;
    pActwk->mstno.b.h = 1;
    *(int*)&pActwk->actfree[0] = 65536;
    ((int*)pActwk)[14] = 256;
  }
}



static void m0move(sprite_status* pActwk) {
  sprite_status* tempact;
  unsigned short sin, cos;
  int sinl, cosl;

  tempact = &actwk[((short*)pActwk)[33]];
  if (tempact->actno != 82) {

    frameout(pActwk);
    return;
  }
  if (((char*)tempact)[67]) {

    frameout(pActwk);
    return;
  }

  sinset(((char*)pActwk)[53], (short*)&sin, (short*)&cos);
  cosl = 0, sinl = 0;
  cosl = cos;
  sinl = sin;
  cosl = (unsigned int)cosl >> 16 & 65535 | cosl << 16 & -65536;
  sinl = (unsigned int)sinl >> 16 & 65535 | sinl << 16 & -65536;
  cosl >>= 3;
  sinl >>= 4;
  cosl = cosl + 32768;
  sinl = sinl + 32768;
  cosl = (unsigned int)cosl >> 16 & 65535 | cosl << 16 & -65536;
  sinl = (unsigned int)sinl >> 16 & 65535 | sinl << 16 & -65536;
  pActwk->xposi.w.h = ((short*)pActwk)[30] + (short)(cosl & 65535);
  pActwk->yposi.w.h = ((short*)pActwk)[25] + (short)(sinl & 65535);

  ((int*)pActwk)[13] += ((int*)pActwk)[14];
  if (!(((int*)pActwk)[13] & 32767)) {

    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;
    if (pActwk->sprpri != 5) {


      pActwk->sprpri = 5;
    }
    else {


      pActwk->sprpri = 3;
    }
  }

  patchg(pActwk, pchg);
  actionsub(pActwk);
}



static void m1move(sprite_status* pActwk) {
  unsigned short sin, cos;
  int sinl;

  pActwk->xposi.l += *(int*)&pActwk->actfree[0];

  sinset(((char*)pActwk)[53], (short*)&sin, (short*)&cos);
  sinl = 0;
  sinl = sin;
  sinl = (unsigned int)sinl >> 16 & 65535 | sinl << 16 & -65536;
  sinl >>= 3;
  sinl = sinl + 32768;
  sinl = (unsigned int)sinl >> 16 & 65535 | sinl << 16 & -65536;
  pActwk->yposi.w.h = ((short*)pActwk)[25] + (short)(sinl & 65535);

  ((int*)pActwk)[13] += ((int*)pActwk)[14];
  if (((int*)pActwk)[13] < 0) {


    ((int*)pActwk)[14] *= -1;
    *(int*)&pActwk->actfree[0] *= -1;
    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;
  }
  else {

    if (((int*)pActwk)[13] >= 65536) {


      ((int*)pActwk)[14] *= -1;
      *(int*)&pActwk->actfree[0] *= -1;
      pActwk->actflg ^= 1;
      pActwk->cddat ^= 1;
    }
  }

  patchg(pActwk, pchg);
  actionsub(pActwk);
  frameout_s(pActwk);
}
