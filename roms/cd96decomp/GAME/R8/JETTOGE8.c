#include "../EQU.h"
#include "JETTOGE8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../PLAYSUB.h"

static void a_init(sprite_status* actionwk);
static void a_move(sprite_status* actionwk);

static char p00[4] = { 1, 0, 1, -1 };
static char* pchg[1] = { p00 };
static sprite_pattern z82pat00 = { 1, { { -16, -76, 0, 475 } } };
static sprite_pattern z83pat00 = { 1, { { -16, -76, 0, 505 } } };
static sprite_pattern z82pat01 = { 1, { { -16, -76, 0, 476 } } };
static sprite_pattern z83pat01 = { 1, { { -16, -76, 0, 506 } } };
sprite_pattern* z82_pat_jettoge[2] =
{
  &z82pat00,
  &z82pat01
};
sprite_pattern* z83_pat_jettoge[2] =
{
  &z83pat00,
  &z83pat01
};
sprite_pattern** pats_jettoge[3] =
{
  0,
  z82_pat_jettoge,
  z83_pat_jettoge
};


void jettoge(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      a_init(actionwk);
    case 2:
      a_move(actionwk);
      break;
  }
}

static void a_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->patbase = pats_jettoge[stageno_i.b.l];
  actionwk->sproffset = 33856;
  ((short*)actionwk)[26] = actionwk->xposi.w.h;
  actionwk->actfree[9] = 177;
  ((int*)actionwk)[12] = 20480;
  actionwk->sprvsize = 76;
  actionwk->sprpri = 1;
  actionwk->sprhsize = 16;
}

static void a_move(sprite_status* actionwk) {
  short t;

  actionwk->xposi.l += ((int*)actionwk)[12];
  if (prio_flag == 0)
    actionwk->colino = actionwk->actfree[9];
  else
    actionwk->colino = 0;
  t = ((short*)actionwk)[23]--;
  if (t <= 0)
  {
    ((short*)actionwk)[23] = 409;
    ((int*)actionwk)[12] = -((int*)actionwk)[12];

    actionwk->actflg ^= 1;
    actionwk->cddat ^= 1;
  }
  patchg(actionwk, (unsigned char**)pchg);
  actionsub(actionwk);
  frameout_s00(actionwk, ((short*)actionwk)[26]);

}
