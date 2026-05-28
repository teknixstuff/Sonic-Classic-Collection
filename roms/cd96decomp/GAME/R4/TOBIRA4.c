#include "../EQU.h"
#include "TOBIRA4.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../RIDECHK.h"

static sprite_pattern z41apat0 = { 1, { { -8, -64, 0, 512 } } };
static sprite_pattern z42apat0 = { 1, { { -8, -64, 0, 513 } } };
static sprite_pattern z42cpat0 = { 1, { { -8, -64, 0, 506 } } };
static sprite_pattern z41apat1 = { 1, { { -8, -32, 0, 513 } } };
static sprite_pattern z42apat1 = { 1, { { -8, -32, 0, 514 } } };
static sprite_pattern z42cpat1 = { 1, { { -8, -32, 0, 507 } } };
static sprite_pattern z41apat2 = { 1, { { -64, -8, 0, 514 } } };
static sprite_pattern z42apat2 = { 1, { { -64, -8, 0, 515 } } };
static sprite_pattern z42cpat2 = { 1, { { -64, -8, 0, 508 } } };
sprite_pattern* z41atobira4pat[3] = {
  &z41apat0,
  &z41apat1,
  &z41apat2
};
sprite_pattern* z42atobira4pat[3] = {
  &z42apat0,
  &z42apat1,
  &z42apat2
};
sprite_pattern* z42ctobira4pat[3] = {
  &z42cpat0,
  &z42cpat1,
  &z42cpat2
};
sprite_pattern** tobira4pats[2][3] = {
  { z41atobira4pat, z41atobira4pat, z41atobira4pat },
  { z42atobira4pat, z42atobira4pat, z42ctobira4pat }
};




































void tobira4(sprite_status* pActwk) {
  void(*tbl[4])(sprite_status*) =
  {
    &tobira4_init,
    &tobira4_move,
    &tobira4_chek,
    &tobira4_clse
  };

  tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s(pActwk);
}




void tobira4_init(sprite_status* pActwk) {
  unsigned char d0, d1;
  unsigned char tbl[20] =
  {
    64,  8, 128, 2,
    64,  8, 128, 2,
     8, 32,  64, 1,
     8, 64, 128, 0,
     8, 64, 128, 0
  };

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sproffset = 17472;
  pActwk->sprpri = 2;
  pActwk->patbase = tobira4pats[stageno_i.b.l][time_flag_i & 0x7F];
  ((short*)pActwk)[29] = pActwk->xposi.w.h;
  ((short*)pActwk)[27] = pActwk->yposi.w.h;

  d1 = d0 = pActwk->userflag.b.h;
  d1 &= 15;
  pActwk->actfree[6] = d1;
  d0 >>= 4;
  d0 &= 15;
  pActwk->actfree[7] = d0;
  d0 <<= 2;
  pActwk->sprhsize = tbl[d0];
  pActwk->sprvsize = tbl[d0 + 1];
  pActwk->actfree[17] = tbl[d0 + 2];
  pActwk->patno = tbl[d0 + 3];
}




void tobira4_move(sprite_status* pActwk) {
  unsigned char d0;

  d0 = pActwk->actfree[6];
  if (!(switchflag[d0] & 128))
  {
    pActwk->actfree[18] = 255;
  }
  else
  {
    pActwk->actfree[18] = 0;
  }

  if (pActwk->actfree[7] != 4)
  {
    if (pActwk->actfree[16])
    {
      pActwk->actfree[18] = 0;
    }
  }
  ((short*)pActwk)[30] = actwk[0].xposi.w.h;
  ((short*)pActwk)[33] = actwk[0].yposi.w.h;
  tobira4_cnt(pActwk);
  hitchk(pActwk, &actwk[0]);

  if (pActwk->actfree[7] != 4)
  {
    if (pActwk->actfree[16] == pActwk->actfree[17])
    {
      pActwk->r_no0 += 2;
    }
  }
}




void cl_type1(sprite_status* pActwk) {
  sprite_status* pPlayerwk;
  short d0;

  pPlayerwk = &actwk[0];
  d0 = pActwk->yposi.w.h;
  if (d0 < ((short*)pActwk)[33])
  {
    d0 = pPlayerwk->sprvsize;
    d0 += pPlayerwk->yposi.w.h;
    if (d0 >= pActwk->yposi.w.h) return;
    d0 -= pActwk->yposi.w.h;
    d0 *= -1;
    if (d0 < 16) return;
  }
  else
  {
    d0 = -pPlayerwk->sprvsize;
    d0 += pPlayerwk->yposi.w.h;
    if (d0 < pPlayerwk->yposi.w.h) return;
    d0 -= pPlayerwk->yposi.w.h;
    if (d0 < 8) return;
  }
  pActwk->r_no0 += 2;
}




void cl_type2(sprite_status* pActwk) {
  sprite_status* pPlayerwk;
  short d0;

  pPlayerwk = &actwk[0];
  d0 = pActwk->xposi.w.h;
  if (d0 < ((short*)pActwk)[30])
  {
    d0 = pPlayerwk->sprhs;
    d0 += pPlayerwk->xposi.w.h;
    if (d0 >= pActwk->xposi.w.h) return;
    d0 -= pActwk->xposi.w.h;
    d0 *= -1;
    if (d0 < 8) return;
  }
  else
  {
    d0 = -pPlayerwk->sprhs;
    d0 += pPlayerwk->xposi.w.h;
    if (d0 < pActwk->xposi.w.h) return;
    d0 -= pActwk->xposi.w.h;
    if (d0 < 8) return;
  }
  pActwk->r_no0 += 2;
}




void tobira4_chek(sprite_status* pActwk) {
  void(*tbl[5])(sprite_status*) =
  {
    &cl_type1,
    &cl_type1,
    &cl_type2,
    &cl_type2,
    &cl_type2
  };

  tbl[pActwk->actfree[7]](pActwk);
  hitchk(pActwk, &actwk[0]);
}




void tobira4_clse(sprite_status* pActwk) {
  pActwk->actfree[18] = 255;
  tobira4_cnt(pActwk);
  if (pActwk->actfree[16] == 0)
  {
    pActwk->r_no0 = 2;
  }
  hitchk(pActwk, &actwk[0]);
}




void type1(sprite_status* pActwk) {
  short d0;

  tobira4_sub(pActwk);
  d0 = (unsigned short)pActwk->actfree[16];
  d0 *= -1;
  d0 += ((short*)pActwk)[29];
  pActwk->xposi.w.h = d0;
}




void type2(sprite_status* pActwk) {
  short d0;

  tobira4_sub(pActwk);
  d0 = (unsigned short)pActwk->actfree[16];
  d0 += ((short*)pActwk)[29];
  pActwk->xposi.w.h = d0;
}




void type3(sprite_status* pActwk) {
  short d0;

  tobira4_sub(pActwk);
  d0 = (unsigned short)pActwk->actfree[16];
  d0 *= -1;
  d0 += ((short*)pActwk)[27];
  pActwk->yposi.w.h = d0;
}




void type4(sprite_status* pActwk) {
  short d0;

  tobira4_sub(pActwk);
  d0 = (unsigned short)pActwk->actfree[16];
  d0 += ((short*)pActwk)[27];
  pActwk->yposi.w.h = d0;
}




void tobira4_cnt(sprite_status* pActwk) {
  void(*tbl[5])(sprite_status*) =
  {
    &type1,
    &type2,
    &type3,
    &type4,
    &type3
  };

  tbl[pActwk->actfree[7]](pActwk);
}




void tobira4_sub(sprite_status* pActwk) {
  if (pActwk->actfree[18])
  {
    if (pActwk->actfree[16] >= 8)
    {
      pActwk->actfree[16] -= 8;
      return;
    }
    pActwk->actfree[16] = 0;
  }
  else
  {
    pActwk->actfree[16] += 8;
    if (pActwk->actfree[16] < pActwk->actfree[17]) return;



    pActwk->actfree[16] = pActwk->actfree[17];
  }
}
