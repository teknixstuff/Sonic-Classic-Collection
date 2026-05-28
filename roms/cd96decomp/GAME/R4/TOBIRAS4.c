#include "../EQU.h"
#include "TOBIRAS4.h"
#include <string.h>
#include "../../services.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../RIDECHK.h"

static void act_init(sprite_status* pActwk);
static void act_sense(sprite_status* pActwk);
static void act_down(sprite_status* pActwk);
static void act_disp(sprite_status* pActwk);

static sprite_pattern z42apat00 = { 1, { { -64, -64, 0, 516 } } };
static sprite_pattern z42cpat00 = { 1, { { -64, -64, 0, 509 } } };
static sprite_pattern z42apat01 = { 1, { { -16, -64, 0, 517 } } };
static sprite_pattern z42cpat01 = { 1, { { -16, -64, 0, 510 } } };
static sprite_pattern z42apat02 = { 1, { { -16, -64, 0, 518 } } };
static sprite_pattern z42cpat02 = { 1, { { -16, -64, 0, 511 } } };
sprite_pattern* z42a_pat_tobiras4[3] =
{
  &z42apat00,
  &z42apat01,
  &z42apat02
};
sprite_pattern* z42c_pat_tobiras4[3] =
{
  &z42cpat00,
  &z42cpat01,
  &z42cpat02
};
sprite_pattern** pat_tobiras4s[3] =
{
  z42a_pat_tobiras4,
  z42a_pat_tobiras4,
  z42c_pat_tobiras4
};



















void tobiras4(sprite_status* pActwk) {
  void(*tbl[3])(sprite_status*) =
  {
    &act_init,
    &act_sense,
    &act_down
  };

  tbl[pActwk->r_no0 / 2](pActwk);
}




static void act_init(sprite_status* pActwk) {
  unsigned char* p;

  p = &switchflag[pActwk->userflag.b.h];
  if (*p)
  {
    frameout(pActwk);
    return;
  }
  ((unsigned char**)pActwk)[13] = p;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17514;
  pActwk->patbase = pat_tobiras4s[time_flag_i & 0x7F];
  pActwk->sprvsize = 64;
  pActwk->sprhsize = 64;
  pActwk->sprpri = 3;
  pActwk->sprhs = 64;
}




static void act_sense(sprite_status* pActwk) {
  sprite_status* pNewActwk;
  unsigned char* p;
  short d5, d6;

  p = ((unsigned char**)pActwk)[13];
  if (*p == 0)
  {
    hitchk(pActwk, &actwk[0]);
    actionsub(pActwk);
    frameout_s(pActwk);
    return;
  }

  pActwk->r_no0 += 2;
  pActwk->sprhs = 16;
  pActwk->sprhsize = 16;
  ((short*)pActwk)[23] = 128;
  ((int*)pActwk)[12] = -65536;
  ++pActwk->patno;
  pActwk->xposi.w.h -= 48;

  d6 = 2;
  d5 = pActwk->xposi.w.h;
  do
  {
    if (actwkchk2(pActwk, &pNewActwk) != 0)
    {
      frameout(pActwk);
      return;
    }
    memcpy(pNewActwk, pActwk, sizeof(*pActwk));
    d5 += 32;
    pNewActwk->xposi.w.h = d5;
    if (!(d6 & 1))
    {
      ((int*)pNewActwk)[12] *= -1;
      ++pNewActwk->patno;
    }
  } while (--d6 >= 0);

  act_disp(pActwk);
}




static void act_down(sprite_status* pActwk) {
  if (((short*)pActwk)[23] < 0)
  {
    frameout(pActwk);
    return;
  }
  --((short*)pActwk)[23];
  pActwk->yposi.l -= ((int*)pActwk)[12];
  act_disp(pActwk);
}




static void act_disp(sprite_status* pActwk) {
  hitchk(pActwk, &actwk[0]);
  actionsub(pActwk);
}
