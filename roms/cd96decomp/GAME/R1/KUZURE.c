#include "../EQU.h"
#include "KUZURE.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

extern unsigned char* tbl_kuzure_b[];
extern unsigned char* z11a_tbl_kuzure_b[];
extern unsigned char* z11b_tbl_kuzure_b[];
extern sprite_pattern* patbase_kuzure_b[];
extern sprite_pattern* z11a_patbase_kuzure_b[];
extern sprite_pattern* z11b_patbase_kuzure_b[];
extern unsigned char* tbl_kuzure_a[];
extern unsigned char* z11a_tbl_kuzure_a[];
extern unsigned char* z11b_tbl_kuzure_a[];
extern sprite_pattern* patbase_kuzure_a[];
extern sprite_pattern* z11a_patbase_kuzure_a[];
extern sprite_pattern* z11b_patbase_kuzure_a[];
extern sprite_pattern* patbase_kuzure_c[];
extern sprite_pattern* z11a_patbase_kuzure_c[];
extern sprite_pattern* z11b_patbase_kuzure_c[];
extern sprite_pattern* patbase_kuzure_d[];
extern sprite_pattern* z11a_patbase_kuzure_d[];
extern sprite_pattern* z11b_patbase_kuzure_d[];

unsigned char** tbls_kuzureb[3][3] =
{
  { z11b_tbl_kuzure_b, z11a_tbl_kuzure_b, tbl_kuzure_b },
  { tbl_kuzure_b, tbl_kuzure_b, tbl_kuzure_b },
  { 0, 0, tbl_kuzure_b }
};
sprite_pattern** patbases_kuzure_b[3][3] =
{
  { z11b_patbase_kuzure_b, z11a_patbase_kuzure_b, patbase_kuzure_b },
  { patbase_kuzure_b, patbase_kuzure_b, patbase_kuzure_b },
  { 0, 0, patbase_kuzure_b }
};
unsigned char** tbls_kuzurea[3][3] =
{
  { z11b_tbl_kuzure_a, z11a_tbl_kuzure_a, tbl_kuzure_a },
  { tbl_kuzure_a, tbl_kuzure_a, tbl_kuzure_a },
  { 0, 0, tbl_kuzure_a }
};
sprite_pattern** patbases_kuzure_a[3][3] =
{
  { z11b_patbase_kuzure_a, z11a_patbase_kuzure_a, patbase_kuzure_a },
  { patbase_kuzure_a, patbase_kuzure_a, patbase_kuzure_a },
  { 0, 0, patbase_kuzure_a }
};
sprite_pattern** patbases_kuzure_c[3][3] =
{
  { z11b_patbase_kuzure_c, z11a_patbase_kuzure_c, patbase_kuzure_c },
  { patbase_kuzure_c, patbase_kuzure_c, patbase_kuzure_c },
  { 0, 0, patbase_kuzure_c }
};
sprite_pattern** patbases_kuzure_d[3][3] =
{
  { z11b_patbase_kuzure_d, z11a_patbase_kuzure_d, patbase_kuzure_d },
  { patbase_kuzure_d, patbase_kuzure_d, patbase_kuzure_d },
  { 0, 0, patbase_kuzure_d }
};














void kuzureru_tikei(sprite_status* pActwk) {
  void(*act_tbl[4])(sprite_status*) =
  {
    &acta_init,
    &acta_check,
    &actb_wait,
    &actb_down
  };

  act_tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  if (pActwk->r_no0 < 4) frameout_s(pActwk);
}






void acta_init(sprite_status* pActwk) {
  sprite_pattern** pPB_kuzure;
  ushort_union id_no;
  unsigned char** pTbltbl;
  unsigned char* pTbl;
  char userflag;
  char block_x;
  char block_y;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sproffset = 17598;

  pPB_kuzure = patbases_kuzure_a[stageno_i.b.l][time_flag_i & 0x7F];
  pTbltbl = tbls_kuzurea[stageno_i.b.l][time_flag_i & 0x7F];
  userflag = pActwk->userflag.b.h;
  if (userflag < 0)
  {
    pTbltbl = tbls_kuzureb[stageno_i.b.l][time_flag_i & 0x7F];
    pPB_kuzure = patbases_kuzure_b[stageno_i.b.l][time_flag_i & 0x7F];
  }
  pActwk->patbase = pPB_kuzure;
  if (userflag & 16)
  {
    pActwk->actflg |= 1;
    pActwk->cddat |= 1;
  }
  id_no.b.h = 0;
  id_no.b.l = (unsigned char)userflag & 15;
  pActwk->patno = id_no.b.l;
  pTbl = pTbltbl[id_no.w];

  block_x = pTbl++[0];
  block_x = (block_x + 1) << 3;
  pActwk->sprhs = block_x;
  pActwk->sprhsize = block_x;

  block_y = pTbl++[0];
  if (block_y < 0) block_y = -block_y;
  block_y = ((block_y + 1) << 3) + 2;
  pActwk->sprvsize = block_y;


}






void acta_check(sprite_status* pActwk) {
  sprite_status* pPlayerwk;

  pPlayerwk = &actwk[0];
  if (ridechk(pActwk, pPlayerwk))
  {
    ride_on_clr(pActwk, pPlayerwk);
    soundset(163);
    pActwk->r_no0 += 2;
    if (pActwk->userflag.b.h < 0) actb_init_b(pActwk);
    else actb_init_a(pActwk);
  }
}






void actb_wait(sprite_status* pActwk) {
  sprite_status* pPlayerwk;

  --((short*)pActwk)[23];
  if (((short*)pActwk)[23] == 0)
  {
    pActwk->r_no0 += 2;
  }
  if (pActwk->actfree[20])
  {
    pPlayerwk = &actwk[0];
    if (ridechk(pActwk, pPlayerwk))
    {
      if (((short*)pActwk)[23] == 0)
      {
        ride_on_clr(pActwk, pPlayerwk);
      }
    }
  }
}






void actb_down(sprite_status* pActwk) {
  sprite_status* pPlayerwk;
  short yposi;

  pActwk->yposi.l += ((int*)pActwk)[12];
  ((int*)pActwk)[12] += 16384;

  yposi = pActwk->yposi.w.h;
  pPlayerwk = &actwk[0];
  yposi -= pPlayerwk->yposi.w.h;
  if (yposi > 512) frameout(pActwk);
}







void actb_init_a(sprite_status* pActwk) {
  sprite_status* pActwk_w;
  sprite_status* pPlayerwk;
  unsigned char** pTbltbl;
  unsigned char* pTbla;
  char patno;
  char userflag;
  short time_x;
  short time_y;
  short posi_x;
  short posi_y;
  short posi_x_start;
  short posi_x_step;
  short reverse_flag;
  short count0x;
  short_union count_x;
  short_union count_y;
  short_union tmp;


  userflag = pActwk->userflag.b.h;
  if (userflag & 16) reverse_flag = 1;
  else reverse_flag = 0;
  pTbltbl = tbls_kuzurea[stageno_i.b.l][time_flag_i & 0x7F];
  pTbla = pTbltbl[userflag & 15];
  tmp.w = 0;
  tmp.b.l = pTbla++[0];
  count0x = tmp.w;
  tmp.w *= 8;
  time_x = -16;
  if (reverse_flag == 0)
  {
    tmp.w *= -1;
    time_x *= -1;
  }
  tmp.w += pActwk->xposi.w.h;
  posi_x_start = tmp.w;
  posi_x_step = time_x;
  count_y.w = 0;
  count_y.b.l = pTbla++[0];
  posi_y = count_y.w;
  posi_y *= 8;
  posi_y += pActwk->yposi.w.h;
  time_y = 9;
  pActwk->actfree[21] = pActwk->actno;
  do
  {
    count_x.w = count0x;
    posi_x = posi_x_start;
    time_x = time_y;
    do
    {
      if (actwkchk(&pActwk_w) != 0)
      {
        pPlayerwk = &actwk[0];
        if (ridechk(pActwk, pPlayerwk)) ride_on_clr(pActwk, pPlayerwk);
        frameout(pActwk);
        return;
      }
      patno = pTbla++[0];
      if (patno >= 0)
      {
        pActwk_w->patno = patno;
        pActwk_w->actflg |= 4;
        pActwk_w->sprpri = 3;
        pActwk_w->sproffset = 17598;
        pActwk_w->patbase = patbases_kuzure_c[stageno_i.b.l][(time_flag_i & 0x7F) + generate_flag];
        ((int*)pActwk_w)[12] = 0x20000;
        pActwk_w->actno = pActwk->actfree[21];
        pActwk_w->r_no0 = pActwk->r_no0;
        if (reverse_flag)
        {
          pActwk_w->actflg |= 1;
          pActwk_w->cddat |= 1;
        }
        if (count_y.w == 0)
        {
          pActwk_w->actfree[20] = 255;
          pActwk_w->sprhs = 8;
          pActwk_w->sprhsize = 8;
          pActwk_w->sprvsize = 9;
        }
        pActwk_w->yposi.w.h = posi_y;
        pActwk_w->xposi.w.h = posi_x;
        ((short*)pActwk_w)[23] = time_x;
      }
      posi_x += posi_x_step;
      time_x += 12;
    } while (--count_x.w >= 0);

    posi_y -= 16;
    time_y += 5;
  } while (--count_y.w >= 0);

  frameout(pActwk);
}







void actb_init_b(sprite_status* pActwk) {
  sprite_status* pActwk_w;
  sprite_status* pPlayerwk;
  unsigned char** pTbltbl;
  unsigned char* pTblb;
  char userflag;
  unsigned char sprvsize;
  short time_w;
  short d3;
  short d4;
  short_union d5;
  short d6;
  short xspeed;

  userflag = pActwk->userflag.b.h;
  pTbltbl = tbls_kuzureb[stageno_i.b.l][time_flag_i & 0x7F];
  pTblb = pTbltbl[userflag & 31];
  d5.b.l = pTblb++[0];
  sprvsize = pTblb++[0];
  ++sprvsize;
  sprvsize = sprvsize * 8;
  sprvsize += 2;
  d5.w &= 255;
  d4 = d5.w;
  d4 <<= 3;
  d4 *= -1;
  d3 = 16;
  d6 = 1;
  if ((userflag & 64) == 0)
  {
    userflag <<= 2;
    if (userflag < 0)
    {
      pTblb += d5.w;
      d4 *= -1;
      d3 *= -1;
      d6 *= -1;
    }
  }
  else
  {
    pPlayerwk = &actwk[0];
    xspeed = pPlayerwk->xspeed.w;
    if (userflag & 32) xspeed *= -1;
    if (xspeed < 0)
    {
      pTblb += d5.w;
      d4 *= -1;
      d3 *= -1;
      d6 *= -1;
    }
  }
  d4 += pActwk->xposi.w.h;

  time_w = 9;
  pActwk->actfree[21] = pActwk->actno;
  do
  {
    if (actwkchk(&pActwk_w) != 0)
    {
      pPlayerwk = &actwk[0];
      if (ridechk(pActwk, pPlayerwk)) ride_on_clr(pActwk, pPlayerwk);
      frameout(pActwk);
      return;
    }
    pActwk_w->sprpri = 3;
    pActwk_w->sproffset = 17598;
    pActwk_w->actflg |= 4;
    pActwk_w->patbase = patbases_kuzure_d[stageno_i.b.l][time_flag_i & 0x7F];
    ((int*)pActwk_w)[12] = 0x20000;
    pActwk_w->actno = pActwk->actfree[21];
    pActwk_w->r_no0 = pActwk->r_no0;
    pActwk_w->yposi.w.h = pActwk->yposi.w.h;
    pActwk_w->actfree[20] = 255;
    pActwk_w->sprhs = 8;
    pActwk_w->sprhsize = 8;
    pActwk_w->sprvsize = sprvsize;

    pActwk_w->patno = pTblb[0];
    pTblb += d6;
    pActwk_w->xposi.w.h = d4;
    d4 += d3;
    ((short*)pActwk_w)[23] = time_w;
    time_w += 12;
  } while (--d5.w >= 0);

  frameout(pActwk);
}
