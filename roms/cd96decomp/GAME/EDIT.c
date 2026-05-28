#include "EQU.h"
#include "EDIT.h"
#include "ACTION.h"
#include "ACTSET.h"
#include "FCOL.h"

extern sprite_pattern** sncpats[6];
extern edit_data z11a_edit_tbl;
extern edit_data z11b_edit_tbl;
extern edit_data z11c_edit_tbl;
extern edit_data z11d_edit_tbl;
extern edit_data z12a_edit_tbl;
extern edit_data z12b_edit_tbl;
extern edit_data z12c_edit_tbl;
extern edit_data z12d_edit_tbl;
extern edit_data z13c_edit_tbl;
extern edit_data z31a_edit_tbl;
extern edit_data z31b_edit_tbl;
extern edit_data z31c_edit_tbl;
extern edit_data z31d_edit_tbl;
extern edit_data z32a_edit_tbl;
extern edit_data z32b_edit_tbl;
extern edit_data z32c_edit_tbl;
extern edit_data z32d_edit_tbl;
extern edit_data z33c_edit_tbl;
extern edit_data z41a_edit_tbl;
extern edit_data z41b_edit_tbl;
extern edit_data z41c_edit_tbl;
extern edit_data z42a_edit_tbl;
extern edit_data z42b_edit_tbl;
extern edit_data z42c_edit_tbl;
extern edit_data z43c_edit_tbl;
extern edit_data z5_edit_tbl;
extern edit_data z53_edit_tbl;
extern edit_data z61a_edit_tbl;
extern edit_data z61b_edit_tbl;
extern edit_data z61c_edit_tbl;
extern edit_data z62a_edit_tbl;
extern edit_data z62b_edit_tbl;
extern edit_data z62c_edit_tbl;
extern edit_data z62d_edit_tbl;
extern edit_data z63c_edit_tbl;
extern edit_data z7_edit_tbl;
extern edit_data z73_edit_tbl;
extern edit_data z81_edit_tbl;
extern edit_data z82_edit_tbl;
extern edit_data z83_edit_tbl;


void edit(sprite_status* pActwk) {
  edit_data* pEdit_tbl;
  sprite_status* pActwk2;
  int edit_spd = 0x80000;
  int speed;
  short xposi;
  short yposi;
  short sprvs;
  short index;
  char en;
  static edit_data* edit_tbls[7][3][4] =
  {
    {
      { &z11b_edit_tbl, &z11a_edit_tbl, &z11d_edit_tbl, &z11c_edit_tbl },
      { &z12b_edit_tbl, &z12a_edit_tbl, &z12d_edit_tbl, &z12c_edit_tbl },
      { 0, 0, &z13c_edit_tbl, &z13c_edit_tbl}
    },
    {
      { &z31b_edit_tbl, &z31a_edit_tbl, &z31d_edit_tbl, &z31c_edit_tbl },
      { &z32b_edit_tbl, &z32a_edit_tbl, &z32d_edit_tbl, &z32c_edit_tbl },
      { 0, 0, &z33c_edit_tbl, &z33c_edit_tbl }
    },
    {
      { &z41b_edit_tbl, &z41a_edit_tbl, &z41c_edit_tbl, &z41c_edit_tbl },
      { &z42b_edit_tbl, &z42a_edit_tbl, &z42c_edit_tbl, &z42c_edit_tbl },
      { 0, 0, &z43c_edit_tbl, &z43c_edit_tbl }
    },
    {
      { &z5_edit_tbl, &z5_edit_tbl, &z5_edit_tbl, &z5_edit_tbl },
      { &z5_edit_tbl, &z5_edit_tbl, &z5_edit_tbl, &z5_edit_tbl },
      { 0, 0, &z53_edit_tbl, &z53_edit_tbl }
    },
    {
      { &z61b_edit_tbl, &z61a_edit_tbl, &z61c_edit_tbl, &z61c_edit_tbl },
      { &z62b_edit_tbl, &z62a_edit_tbl, &z62d_edit_tbl, &z62c_edit_tbl },
      { 0, 0, &z63c_edit_tbl, &z63c_edit_tbl }
    },
    {
      { &z7_edit_tbl, &z7_edit_tbl, &z7_edit_tbl, &z7_edit_tbl },
      { &z7_edit_tbl, &z7_edit_tbl, &z7_edit_tbl, &z7_edit_tbl },
      { 0, 0, &z73_edit_tbl, &z73_edit_tbl }
    },
    {
      { &z81_edit_tbl, &z81_edit_tbl, &z81_edit_tbl, &z81_edit_tbl },
      { &z82_edit_tbl, &z82_edit_tbl, &z82_edit_tbl, &z82_edit_tbl },
      { 0, 0, &z83_edit_tbl, &z83_edit_tbl }
    }
  };

  if (editmode.b.h == 0) return;

  if (swdata1.b.h & 15)
  {
    edit_spd += 8192;
    if (edit_spd > 0x80000) edit_spd = 0x80000;
  }
  else
  {
    edit_spd = 16384;
  }
  speed = edit_spd;
  if (swdata1.b.h & 1) pActwk->yposi.l -= speed;
  if (swdata1.b.h & 2) pActwk->yposi.l += speed;
  if (swdata1.b.h & 4) pActwk->xposi.l -= speed;
  if (swdata1.b.h & 8) pActwk->xposi.l += speed;
  yposi = pActwk->yposi.w.h;
  sprvs = pActwk->sprvsize;
  yposi += sprvs;
  xposi = pActwk->xposi.w.h;
  blkno = scramapad(pActwk, xposi, yposi);

  pEdit_tbl = edit_tbls[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];

  if (swdata1.b.l & 16)
  {
    editmode.b.h = 0;
    pActwk->patbase = sncpats[stageno_i.b.h];
    pActwk->sproffset = 1920;
    pActwk->sprpri = 2;
    pActwk->patno = 0;
    pActwk->actflg = 4;
    actionsub(pActwk);
    return;
  }

  if (swdata1.b.l & 64)
  {
    en = editno.b.h + 1;
    if (en >= pEdit_tbl->num) en = 0;
    editno.b.h = en;
  }








  index = editno.b.h;

  pActwk->patbase = pEdit_tbl->dat[index].patbase;
  pActwk->sproffset = pEdit_tbl->dat[index].offset;
  pActwk->sprpri = pEdit_tbl->dat[index].sprpri;
  pActwk->patno = pEdit_tbl->dat[index].patno;
  edit_user = pEdit_tbl->dat[index].userflag_l;
  pActwk->actflg = pEdit_tbl->dat[index].rludrv | 4;
  pActwk->mstno.b.h = 0;

  if (swdata1.b.l & 32)
  {
    if (actwkchk(&pActwk2) == 0)
    {
      index = editno.b.h;
      pActwk2->actno = pEdit_tbl->dat[index].actno;
      pActwk2->userflag.b.h = pEdit_tbl->dat[index].userflag_h;
      pActwk2->userflag.b.l = pEdit_tbl->dat[index].userflag_l;
      pActwk2->patno = pEdit_tbl->dat[index].patno;
      pActwk2->xposi.w.h = pActwk->xposi.w.h;
      pActwk2->yposi.w.h = pActwk->yposi.w.h;
      pActwk2->actflg = pActwk->actflg & 3;
      pActwk2->cddat = pActwk->actflg & 3;
    }
  }
  actionsub(pActwk);
}
