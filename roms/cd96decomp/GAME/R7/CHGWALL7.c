#include "../EQU.h"
#include "CHGWALL7.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../RIDECHK.h"

sprite_pattern pat00;
sprite_pattern pat01 = { 1, { { -32, -16, 0, 403 } } };
sprite_pattern z73pat01 = { 1, { { -32, -16, 0, 452 } } };
sprite_pattern* pat_chgwall7[2] = {
  &pat00,
  &pat01
};
sprite_pattern* z73_pat_chgwall7[2] = {
  &pat00,
  &z73pat01
};
sprite_pattern** pats_chgwall7[3] = {
  pat_chgwall7,
  pat_chgwall7,
  z73_pat_chgwall7
};











































void chgwall7(sprite_status* pActwk) {
  if (!pActwk->r_no0) {

    pActwk->r_no0 += 2;
    pActwk->actflg |= 4;
    pActwk->sprhs = pActwk->sprhsize = 32;
    pActwk->sprvsize = 17;
    pActwk->patbase = pats_chgwall7[stageno_i.b.l];
  }



  pActwk->patno = 0;
  if (prio_flag) {

    if (hitchk(pActwk, &actwk[0])) {
      pActwk->actfree[0] = 1;
    }
  }
  else {
    if (pActwk->actfree[0]) {
      pActwk->actfree[0] = 0;
      ride_on_clr(pActwk, &actwk[0]);
    }
  }


  actionsub(pActwk);
  frameout_s(pActwk);
}
