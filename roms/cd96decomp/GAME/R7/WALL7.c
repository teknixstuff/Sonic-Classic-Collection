#include "../EQU.h"
#include "WALL7.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../RIDECHK.h"

static sprite_pattern wall7_pat0 = { 1, { { -16, -16, 0, 428 } } };
static sprite_pattern z73_wall7_pat0 = { 1, { { -16, -16, 0, 411 } } };
static sprite_pattern wall7_pat1 = { 1, { { -32, -16, 0, 429 } } };
static sprite_pattern z73_wall7_pat1 = { 1, { { -32, -16, 0, 412 } } };
static sprite_pattern wall7_pat2 = { 1, { { -48, -16, 0, 430 } } };
static sprite_pattern z73_wall7_pat2 = { 1, { { -48, -16, 0, 413 } } };
static sprite_pattern wall7_pat3 = { 1, { { -64, -16, 0, 431 } } };
static sprite_pattern z73_wall7_pat3 = { 1, { { -64, -16, 0, 414 } } };
static sprite_pattern wall7_pat4 = { 1, { { -16, -32, 0, 432 } } };
static sprite_pattern z73_wall7_pat4 = { 1, { { -16, -32, 0, 415 } } };
static sprite_pattern wall7_pat5 = { 1, { { -16, -48, 0, 433 } } };
static sprite_pattern z73_wall7_pat5 = { 1, { { -16, -48, 0, 416 } } };
sprite_pattern* pat_wall7[6] = {
  &wall7_pat0,
  &wall7_pat1,
  &wall7_pat2,
  &wall7_pat3,
  &wall7_pat4,
  &wall7_pat5
};
sprite_pattern* z73_pat_wall7[6] = {
  &z73_wall7_pat0,
  &z73_wall7_pat1,
  &z73_wall7_pat2,
  &z73_wall7_pat3,
  &z73_wall7_pat4,
  &z73_wall7_pat5
};
sprite_pattern** pats_wall7[3] = {
  pat_wall7,
  pat_wall7,
  z73_pat_wall7
};




























void wall7(sprite_status* pActwk) {
  unsigned char wall7_tbl0[12] = {
    12, 17,
    28, 17,
    44, 17,
    60, 17,
    12, 33,
    12, 49
  };

  if (!pActwk->r_no0) {

    pActwk->r_no0 += 2;
    pActwk->actflg |= 4;
    pActwk->sprpri = 3;
    pActwk->sproffset = 17270;
    pActwk->patbase = pats_wall7[stageno_i.b.l];
    pActwk->patno = pActwk->userflag.b.h;

    pActwk->sprhs = wall7_tbl0[pActwk->userflag.b.h * 2];
    pActwk->sprhsize = wall7_tbl0[pActwk->userflag.b.h * 2];
    pActwk->sprvsize = wall7_tbl0[pActwk->userflag.b.h * 2 + 1];
  }

  hitchk(pActwk, &actwk[0]);
  actionsub(pActwk);
  frameout_s(pActwk);
}
