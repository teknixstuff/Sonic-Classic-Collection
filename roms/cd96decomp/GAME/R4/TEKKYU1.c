#include "../EQU.h"
#include "TEKKYU1.h"
#include "../ACTION.h"
#include "../ACTSET.h"

static sprite_pattern z42apat0 = { 1, { { -16, -16, 0, 532 } } };
static sprite_pattern z42cpat0 = { 1, { { -16, -16, 0, 505 } } };
static sprite_pattern* z42a_pat_tekkyu1[1] = { &z42apat0 };
static sprite_pattern* z42c_pat_tekkyu1[1] = { &z42cpat0 };
static sprite_pattern** pats_tekkyu1[3] = {
  z42a_pat_tekkyu1,
  z42a_pat_tekkyu1,
  z42c_pat_tekkyu1
};

























void tekkyu1(sprite_status* pActwk) {
  if (pActwk->r_no0 == 0) {

    pActwk->r_no0 += 2;
    pActwk->actflg |= 4;
    pActwk->sprpri = 3;
    pActwk->colino = 169;
    pActwk->sprhs = 16;
    pActwk->sprhsize = 16;
    pActwk->sprvsize = 16;
    pActwk->sproffset = 880;
    pActwk->patbase = pats_tekkyu1[time_flag_i & 0x7F];
  }
  actionsub(pActwk);
  frameout_s(pActwk);
}
