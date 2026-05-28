#include "../EQU.h"
#include "TENTOU.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../FCOL.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static unsigned char bCarry;
void(*tentou_tbl[6])(sprite_status*) = {
  &ten_a_init,
  &ten_a_fall,
  &ten_a_wait,
  &ten_a_lr,
  &ten_a_up,
  &ten_a_gake
};
void(*tentou1_tbl[5])(sprite_status*) = {
  &ten_b_init,
  &ten_b_fall,
  &ten_b_wait,
  &ten_b_blink,
  &ten_b_die
};
unsigned char pchg0_0[5] = { 3, 0, 1, 2, 255 };
static unsigned char* pchg0[1] = { pchg0_0 };
sprite_pattern ten_b_tentou0 = { 1, { { -24, -24, 0, 474 } } };
sprite_pattern z31a_ten_b_tentou0 = { 1, { { -24, -24, 0, 521 } } };
sprite_pattern z33_ten_b_tentou0 = { 1, { { -24, -24, 0, 525 } } };
sprite_pattern ten_b_tentou1 = { 1, { { -24, -24, 0, 475 } } };
sprite_pattern z31a_ten_b_tentou1 = { 1, { { -24, -24, 0, 522 } } };
sprite_pattern z33_ten_b_tentou1 = { 1, { { -24, -24, 0, 526 } } };
sprite_pattern ten_b_tentou2 = { 1, { { -24, -24, 0, 476 } } };
sprite_pattern z31a_ten_b_tentou2 = { 1, { { -24, -24, 0, 523 } } };
sprite_pattern z33_ten_b_tentou2 = { 1, { { -24, -24, 0, 527 } } };
sprite_pattern* pat_ten_b_tentou[3] = {
  &ten_b_tentou0,
  &ten_b_tentou1,
  &ten_b_tentou2
};
sprite_pattern* z31a_pat_ten_b_tentou[3] = {
  &z31a_ten_b_tentou0,
  &z31a_ten_b_tentou1,
  &z31a_ten_b_tentou2
};
sprite_pattern* z33_pat_ten_b_tentou[3] = {
  &z33_ten_b_tentou0,
  &z33_ten_b_tentou1,
  &z33_ten_b_tentou2
};
sprite_pattern** pats_ten_b_tentou[3][3] = {
  { z31a_pat_ten_b_tentou, z31a_pat_ten_b_tentou, pat_ten_b_tentou },
  { pat_ten_b_tentou, z31a_pat_ten_b_tentou, pat_ten_b_tentou },
  { 0, 0, z33_pat_ten_b_tentou }
};
sprite_pattern e_tentou0 = { 1, { { -24, -24, 0, 477 } } };
sprite_pattern z31a_e_tentou0 = { 1, { { -24, -24, 0, 524 } } };
sprite_pattern z33_e_tentou0 = { 1, { { -24, -24, 0, 528 } } };
sprite_pattern e_tentou1 = { 1, { { -24, -24, 0, 478 } } };
sprite_pattern z31a_e_tentou1 = { 1, { { -24, -24, 0, 525 } } };
sprite_pattern z33_e_tentou1 = { 1, { { -24, -24, 0, 529 } } };
sprite_pattern e_tentou2 = { 1, { { -24, -24, 0, 479 } } };
sprite_pattern z31a_e_tentou2 = { 1, { { -24, -24, 0, 526 } } };
sprite_pattern z33_e_tentou2 = { 1, { { -24, -24, 0, 530 } } };
sprite_pattern* pat_e_tentou[3] = {
  &e_tentou0,
  &e_tentou1,
  &e_tentou2
};
sprite_pattern* z31a_pat_e_tentou[3] = {
  &z31a_e_tentou0,
  &z31a_e_tentou1,
  &z31a_e_tentou2
};
sprite_pattern* z33_pat_e_tentou[3] = {
  &z33_e_tentou0,
  &z33_e_tentou1,
  &z33_e_tentou2
};
sprite_pattern** pats_e_tentou[3][3] = {
  { z31a_pat_e_tentou, z31a_pat_e_tentou, pat_e_tentou },
  { pat_e_tentou, z31a_pat_e_tentou, pat_e_tentou },
  { 0, 0, z33_pat_e_tentou }
};
unsigned char pchg1_0[4] = { 1, 0, 1, 255 };
static unsigned char* pchg1[1] = { pchg1_0 };
sprite_pattern bomten_b_0 = { 1, { { -8, -8, 0, 480 } } };
sprite_pattern z31a_bomten_b_0 = { 1, { { -8, -8, 0, 527 } } };
sprite_pattern z33_bomten_b_0 = { 1, { { -8, -8, 0, 531 } } };
sprite_pattern bomten_b_1 = { 1, { { -8, -8, 0, 481 } } };
sprite_pattern z31a_bomten_b_1 = { 1, { { -8, -8, 0, 528 } } };
sprite_pattern z33_bomten_b_1 = { 1, { { -8, -8, 0, 532 } } };
sprite_pattern* tentou_bomten_b_pat[2] = {
  &bomten_b_0,
  &bomten_b_1
};
sprite_pattern* z31a_tentou_bomten_b_pat[2] = {
  &z31a_bomten_b_0,
  &z31a_bomten_b_1
};
sprite_pattern* z33_tentou_bomten_b_pat[2] = {
  &z33_bomten_b_0,
  &z33_bomten_b_1
};
sprite_pattern** tentou_bomten_b_pats[3][3] = {
  { z31a_tentou_bomten_b_pat, z31a_tentou_bomten_b_pat, tentou_bomten_b_pat },
  { tentou_bomten_b_pat, z31a_tentou_bomten_b_pat, tentou_bomten_b_pat },
  { 0, 0, z33_tentou_bomten_b_pat }
};


void tentou(sprite_status* pActwk) {
  if (pActwk->userflag.b.h - 1 >= 0)
  {
    tentou1(pActwk);
    return;
  }
  if (enemy_suicide(pActwk) == -1) return;

  tentou_tbl[pActwk->r_no0 / 2](pActwk);
  patchg(pActwk, pchg0);
  actionsub(pActwk);
  frameout_s(pActwk);
}











void ten_a_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 132;
  pActwk->sprpri = 1;
  pActwk->colino = 6;
  pActwk->sprhsize = 14;
  pActwk->sprvsize = 14;
  pActwk->sproffset = 42090;
  if (pActwk->userflag.w >= 0)
  {
    pActwk->patbase = pats_e_tentou[stageno_i.b.l][time_flag_i & 0x7F];
    pActwk->actfree[21] = 255;
  }
  else
    pActwk->patbase = pats_ten_b_tentou[stageno_i.b.l][time_flag_i & 0x7F];
  ten_a_fall(pActwk);
}











void ten_a_fall(sprite_status* pActwk) {
  short iD1;

  pActwk->yposi.l += 65536;
  iD1 = emycol_d(pActwk);
  iD1 -= 8;
  if (iD1 <= 0)
  {
    pActwk->yposi.w.h -= iD1;
    *(int*)&pActwk->actfree[8] = pActwk->yposi.l;
    *(int*)&pActwk->actfree[4] = 12288;
    ((short*)pActwk)[29] = 8;
    pActwk->r_no0 += 2;
    if ((long int)*(int*)&pActwk->actfree[0] != 0)
      pActwk->r_no0 += 2;
  }
}



int abs(int i) {
  if (i >= 0)
    return i;

  return -i;
}











void ten_a_wait(sprite_status* pActwk) {
  sprite_status* pPlaywk = &actwk[0];
  short iD0, iD1;

  ten_a_hover(pActwk);

  iD0 = pActwk->yposi.w.h - pPlaywk->yposi.w.h;
  iD0 = abs(iD0);
  if (iD0 <= 80)
  {





    iD0 = pActwk->xposi.w.h - pPlaywk->xposi.w.h;
    iD1 = iD0;
    iD0 = abs(iD0);
    if (iD0 <= 80)
    {





      pActwk->r_no0 += 2;
      *(int*)&pActwk->actfree[0] = 4294918144;
      if (iD1 >= 0)
      {
        pActwk->actflg ^= 1;
        pActwk->cddat ^= 1;
        *(int*)&pActwk->actfree[0] = -(long int)*(int*)&pActwk->actfree[0];
      }
    }
  }
}











void ten_a_lr(sprite_status* pActwk) {
  short iD1;
  sprite_status* pActfree;

  pActwk->xposi.l += *(int*)&pActwk->actfree[0];
  pActwk->yposi.l = *(int*)&pActwk->actfree[8];

  if (*(int*)&pActwk->actfree[0] >= 0)
    iD1 = emycol_r(pActwk, pActwk->sprhs);
  else
    iD1 = emycol_l(pActwk, pActwk->sprhs);

  if (iD1 >= 0)
  {
    iD1 = emycol_d(pActwk);
    if (iD1 < 16)
    {
      iD1 -= 8;
      pActwk->yposi.w.h += iD1;
      *(int*)&pActwk->actfree[8] = pActwk->yposi.l;
      ten_a_hover(pActwk);
      if (pActwk->actfree[21] != 0)
      {
        ((unsigned short*)pActwk)[29] &= 127;
        if (((unsigned short*)pActwk)[29] == 0)
        {
          if (actwkchk(&pActfree) == 0)
          {
            pActfree->actno = pActwk->actno;
            pActfree->xposi.l = pActwk->xposi.l;
            pActfree->yposi.l = pActwk->yposi.l;
            pActfree->yposi.w.h += 16;
            pActfree->userflag.b.h = 1;
          }
        }
      }
    }
    else
    {

      pActwk->r_no0 += 4;
      ten_a_hover(pActwk);
      *(int*)&pActwk->actfree[8] = pActwk->yposi.l;
    }
  }
  else
  {

    pActwk->r_no0 += 2;
  }
}











void ten_a_up(sprite_status* pActwk) {
  pActwk->yposi.l -= 32768;
}











void ten_a_gake(sprite_status* pActwk) {
  char cwk, cRwk;
  short iD1, iD3, iD4;

  pActwk->xposi.l += *(int*)&pActwk->actfree[0];
  iD3 = pActwk->xposi.w.h;
  iD4 = pActwk->sprhsize;
  iD3 -= iD4;
  if ((long int)*(int*)&pActwk->actfree[0] > 0)
    iD3 += iD4 + iD4;
  iD1 = emycol_d2(pActwk, iD3);
  if (iD1 >= 16)
  {

    cwk = 2;
    cwk = -cwk * 4;
    cRwk = pActwk->r_no0;
    cRwk = cRwk + cwk;
    pActwk->r_no0 = cRwk;
  }
}











void ten_a_hover(sprite_status* pActwk) {
  unsigned short wD0;

  ++((short*)pActwk)[29];
  pActwk->yposi.l += *(int*)&pActwk->actfree[4];
  wD0 = ((unsigned short*)pActwk)[29];
  wD0 &= 15;
  if (wD0 != 0) return;
  *(int*)&pActwk->actfree[4] = -(long int)*(int*)&pActwk->actfree[4];
}











void ten_a_range(sprite_status* pActwk) {
  short iD0;
  sprite_status* pPlaywk = &actwk[0];

  iD0 = pPlaywk->yposi.w.h;
  iD0 -= pActwk->yposi.w.h;
  iD0 += 256;
  bCarry = CCset(iD0, 512);
  iD0 -= 512;
  if (bCarry == 1)
  {
    iD0 = pPlaywk->yposi.w.h - pActwk->yposi.w.h;
    iD0 += 256;
    iD0 -= 512;
  }
}





























void tentou1(sprite_status* pActwk) {
  unsigned char byRwk;

  byRwk = pActwk->r_no0 / 2;
  tentou1_tbl[byRwk](pActwk);
  actionsub(pActwk);
}












void ten_b_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 2;
  pActwk->colino = 139;
  pActwk->sprhs = 6;
  pActwk->sprhsize = 6;
  pActwk->sprvsize = 6;
  pActwk->sproffset = 1173;
  pActwk->patbase = tentou_bomten_b_pats[stageno_i.b.l][time_flag_i & 0x7F];
  ten_b_fall(pActwk);
}











void ten_b_fall(sprite_status* pActwk) {
  short iD1;

  if (pActwk->colicnt != 0)
  {
    ten_b_die(pActwk);
    return;
  }
  pActwk->yposi.l += 65536;
  iD1 = emycol_d(pActwk);
  if (iD1 < 0)
  {
    pActwk->yposi.w.h += iD1;
    ((short*)pActwk)[23] = 120;
    pActwk->r_no0 += 2;
  }
}











void ten_b_wait(sprite_status* pActwk) {
  if (pActwk->colicnt != 0)
  {
    ten_b_die(pActwk);
    return;
  }
  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] == 0)
  {
    ((short*)pActwk)[23] = 120;
    pActwk->r_no0 += 2;
  }
}











void ten_b_blink(sprite_status* pActwk) {
  if (pActwk->colicnt != 0)
  {
    ten_b_die(pActwk);
    return;
  }
  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] == 0)
  {
    pActwk->r_no0 += 2;
  }
  patchg(pActwk, pchg1);
}











void ten_b_die(sprite_status* pActwk) {
  pActwk->actno = 24;
  pActwk->r_no0 = 0;
  pActwk->r_no1 = 1;
  if ((char)pActwk->actflg < 0)
    soundset(158);
}
