#include "../EQU.h"
#include "BATTA.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../SUICIDE.h"

void(*batta_tbl[4])(sprite_status*) =
{
  &batta_init,
  &batta_down,
  &batta_wait,
  &batta_up
};
sprite_pattern ep_batta0 = { 1, { { -16, -18, 0, 483 } } };
sprite_pattern z6b_ep_batta0 = { 1, { { -16, -18, 0, 477 } } };
sprite_pattern ep_batta1 = { 1, { { -16, -29, 0, 484 } } };
sprite_pattern z6b_ep_batta1 = { 1, { { -16, -29, 0, 478 } } };
sprite_pattern* pat_batta_e[2] =
{
  &ep_batta0,
  &ep_batta1
};
sprite_pattern* z6b_pat_batta_e[2] =
{
  &z6b_ep_batta0,
  &z6b_ep_batta1
};
sprite_pattern** pats_batta_e[3] =
{
  z6b_pat_batta_e,
  pat_batta_e,
  pat_batta_e
};
sprite_pattern bp_batta0 = { 1, { { -16, -18, 0, 485 } } };
sprite_pattern z6b_bp_batta0 = { 1, { { -16, -18, 0, 479 } } };
sprite_pattern bp_batta1 = { 1, { { -16, -29, 0, 486 } } };
sprite_pattern z6b_bp_batta1 = { 1, { { -16, -29, 0, 480 } } };
sprite_pattern* pat_batta_b[2] =
{
  &bp_batta0,
  &bp_batta1
};
sprite_pattern* z6b_pat_batta_b[2] =
{
  &z6b_bp_batta0,
  &z6b_bp_batta1
};
sprite_pattern** pats_batta_b[3] =
{
  z6b_pat_batta_b,
  pat_batta_b,
  pat_batta_b
};



































void batta(sprite_status* pActwk) {
  if (enemy_suicide(pActwk)) return;
  batta_tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s(pActwk);
}











void batta_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sproffset = 9272;
  pActwk->sprhs = 16;
  pActwk->sprhsize = 16;
  *(int*)&pActwk->actfree[4] = 458752;
  pActwk->actfree[12] = 255;
  ((short*)pActwk)[28] = -16;
  pActwk->patno = 1;

  batta_patexg(pActwk);
  if (pActwk->userflag.b.h == 0)
  {
    pActwk->patbase = pats_batta_e[time_flag_i & 0x7F];
    *(int*)&pActwk->actfree[0] = -40960;
    pActwk->actfree[8] = 7;
    pActwk->actfree[9] = 7;
  }
  else
  {
    pActwk->patbase = pats_batta_b[time_flag_i & 0x7F];
    *(int*)&pActwk->actfree[0] = -32768;
    pActwk->actfree[8] = 3;
    pActwk->actfree[9] = 3;
  }

  ++pActwk->actfree[8];
}



short emylr_jump(sprite_status* pActwk, unsigned char byD3) {
  if (pActwk->actfree[12] == 255)
    emycol_r(pActwk, byD3);
  else
    emycol_l(pActwk, byD3);
}










void batta_down(sprite_status* pActwk) {
  short iD1, iD3;

  pActwk->xposi.l += *(int*)&pActwk->actfree[0];
  pActwk->yposi.l += *(int*)&pActwk->actfree[4];

  iD1 = emycol_d(pActwk);
  ((short*)pActwk)[33] = iD1;
  iD3 = ((short*)pActwk)[28];
  iD1 = emylr_jump(pActwk, iD3);
  if (iD1 < 0)
  {
    if (((short*)pActwk)[33] >= 0)
    {
      batta_wall(pActwk);
      return;
    }
    if (iD1 <= ((short*)pActwk)[33])
      batta_wall(pActwk);
    else
      batta_floor(pActwk);
    return;
  }

  if (((short*)pActwk)[33] < 0)
  {
    batta_floor(pActwk);
    return;
  }
  *(int*)&pActwk->actfree[4] += 8192;
  if (*(int*)&pActwk->actfree[4] >= 458752)
    *(int*)&pActwk->actfree[4] = 458752;

}











void batta_floor(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->yposi.w.h += ((short*)pActwk)[33];
  if (pActwk->userflag.b.h == 0)
    ((short*)pActwk)[31] = 1;
  else
    ((short*)pActwk)[31] = 20;
}











void batta_wait(sprite_status* pActwk) {
  short iD6;

  if (pActwk->userflag.b.h != 0)
  {
    iD6 = 7;
    switch (((short*)pActwk)[31])
    {
      case 11:
      case 18:
        iD6 = -iD6;
      case 6:
      case 15:
        pActwk->yposi.w.h += iD6;
        batta_patexg(pActwk);
        break;
    }
  }



  --((short*)pActwk)[31];
  if (((short*)pActwk)[31] == 0)
  {
    pActwk->r_no0 += 2;
    pActwk->yposi.w.h -= 7;
    batta_patexg(pActwk);
    if (pActwk->userflag.b.h == 0)
      *(int*)&pActwk->actfree[4] = -393216;
    else
      *(int*)&pActwk->actfree[4] = -327680;
    --((char*)pActwk)[54];
    if (((char*)pActwk)[54] < 0)
      batta_wall(pActwk);
  }
}











void batta_up(sprite_status* pActwk) {
  short iD1, iD3;

  pActwk->xposi.l += *(int*)&pActwk->actfree[0];
  pActwk->yposi.l += *(int*)&pActwk->actfree[4];
  iD1 = emycol_u(pActwk);
  ((short*)pActwk)[33] = iD1;
  iD3 = ((short*)pActwk)[28];
  iD1 = emylr_jump(pActwk, iD3);
  if (iD1 < 0)
  {
    if (((short*)pActwk)[33] >= 0 || iD1 <= ((short*)pActwk)[33])
    {

      batta_wall(pActwk);
    }
    else
      batta_ceiling(pActwk);
    return;
  }

  if (((short*)pActwk)[33] < 0)
  {
    batta_ceiling(pActwk);
    return;
  }
  *(int*)&pActwk->actfree[4] += 8192;
  if (*(int*)&pActwk->actfree[4] >= 0)
    batta_fall(pActwk);
}











void batta_ceiling(sprite_status* pActwk) {
  pActwk->yposi.w.h -= ((short*)pActwk)[33];
  *(int*)&pActwk->actfree[4] = 0;
  batta_fall(pActwk);
}











void batta_fall(sprite_status* pActwk) {
  pActwk->r_no0 -= 4;
  pActwk->yposi.w.h -= 11;
  batta_patexg(pActwk);
}











void batta_wall(sprite_status* pActwk) {
  pActwk->actfree[8] = pActwk->actfree[9];
  pActwk->actflg ^= 1;
  pActwk->cddat ^= 1;
  *(int*)&pActwk->actfree[0] = -(long int)*(int*)&pActwk->actfree[0];
  ((short*)pActwk)[28] = -((short*)pActwk)[28];
  if (pActwk->actfree[12] == 255)
    pActwk->actfree[12] = 1;
  else
    pActwk->actfree[12] = 255;
}











void batta_patexg(sprite_status* pActwk) {
  if (pActwk->patno != 0)
  {
    pActwk->patno = 0;
    pActwk->sprvsize = 19;
    pActwk->colino = 47;
  }
  else
  {
    pActwk->patno = 1;
    pActwk->sprvsize = 28;
    pActwk->colino = 48;
  }
}
