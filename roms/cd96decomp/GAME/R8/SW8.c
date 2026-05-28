#include "../EQU.h"
#include "SW8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

static void act_init(sprite_status* swwk);
static void act_move(sprite_status* swwk);

static sprite_pattern z81sw00 = { 2, { { -16, -8, 0, 306 }, { 0, -8, 8, 306 } } };
static sprite_pattern z82sw00 = { 2, { { -16, -8, 0, 315 }, { 0, -8, 8, 315 } } };
static sprite_pattern z83sw00 = { 2, { { -16, -8, 0, 308 }, { 0, -8, 8, 308 } } };
static sprite_pattern z81sw01 = { 2, { { -16, -4, 0, 307 }, { 0, -4, 8, 307 } } };
static sprite_pattern z82sw01 = { 2, { { -16, -4, 0, 316 }, { 0, -4, 8, 316 } } };
static sprite_pattern z83sw01 = { 2, { { -16, -4, 0, 309 }, { 0, -4, 8, 309 } } };
sprite_pattern* z81_pat_sw[2] = {
  &z81sw00,
  &z81sw01
};
sprite_pattern* z82_pat_sw[2] = {
  &z82sw00,
  &z82sw01
};
sprite_pattern* z83_pat_sw[2] = {
  &z83sw00,
  &z83sw01
};
static sprite_pattern** pats_sw[3] = {
  z81_pat_sw,
  z82_pat_sw,
  z83_pat_sw
};





void sw(sprite_status* swwk) {
  if (swwk->r_no0 == 0) act_init(swwk);
  else act_move(swwk);
}



static void act_init(sprite_status* swwk) {
  swwk->r_no0 += 2;
  swwk->actflg |= 4;
  swwk->sprpri = 1;
  swwk->sprhs = swwk->sprhsize = 16;

  swwk->patbase = pats_sw[stageno_i.b.l];
  swwk->sprvsize = 8;

  ((short*)swwk)[32] = swwk->userflag.b.h;
}




static void act_move(sprite_status* swwk) {
  short switch_adr;

  swwk->actfree[20] = swwk->actfree[21];
  switch_adr = ((short*)swwk)[32];
  if (hitchk(swwk, &actwk[0]) && actwk[0].yposi.w.h <= swwk->yposi.w.h) {
    swwk->actfree[21] = 255;
    switchflag[switch_adr] |= 192;
  } else {
    swwk->actfree[21] = 0;
    switchflag[switch_adr] &= 127;
  }


  if (swwk->actfree[20] == 0 && swwk->actfree[21] == 255) {

    if ((char)swwk->actflg < 0) soundset(191);

    switchflag[switch_adr] ^= 32;
    actwk[0].yposi.w.h += 8;
    swwk->yposi.w.h += 4;
    ++swwk->patno;
    swwk->sprvsize -= 4;
  }

  if (swwk->actfree[20] == 255 && swwk->actfree[21] == 0) {

    actwk[0].yposi.w.h -= 12;
    swwk->yposi.w.h -= 4;
    --swwk->patno;
    swwk->sprvsize += 4;
  }

  actionsub(swwk);
  frameout_s(swwk);
}
