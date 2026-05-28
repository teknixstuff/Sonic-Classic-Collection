#include "../EQU.h"
#include "WARP.h"
#include <string.h>
#include "../../services.h"
#include "../ACTION.h"
#include "../COL.h"
#include "../IO.h"
#include "../LOADER2.h"

static unsigned short clchg_cnt[2] = {
  65535, 0
};
static PALETTEENTRY colortbl[32] = {
  {   0,   0,   0, 1 }, {   0, 224,   0, 1 }, {  32,  32, 192, 1 }, {  64,  64, 224, 1 },
  {  96,  96, 224, 1 }, { 128, 128, 224, 1 }, { 224, 224, 224, 1 }, { 160, 160, 160, 1 },
  { 128, 128, 128, 1 }, {  64,  64,  64, 1 }, { 224, 160, 128, 1 }, { 160,  96,  64, 1 },
  { 224,   0,   0, 1 }, { 128,   0,   0, 1 }, {  64,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0, 224,   0, 1 }, {  32, 224,  32, 1 }, {  64, 224,  64, 1 },
  {  96, 224,  96, 1 }, { 128, 224, 128, 1 }, { 160, 224, 160, 1 }, { 192, 224, 192, 1 },
  { 224, 224, 224, 1 }, { 192, 224, 192, 1 }, { 160, 224, 160, 1 }, { 128, 224, 128, 1 },
  {  96, 224,  96, 1 }, {  64, 224,  64, 1 }, {  32, 224,  32, 1 }, {   0,   0,   0, 1 }
};
static PALETTEENTRY clchg_tbl[28] = {
  {   0, 224,   0 ,1 }, {  32, 224,  32, 1 }, {  64, 224,  64, 1 }, {  96, 224,  96, 1 },
  { 128, 224, 128, 1 }, { 160, 224, 160, 1 }, { 192, 224, 192, 1 }, { 224, 224, 224, 1 },
  { 192, 224, 192, 1 }, { 160, 224, 160, 1 }, { 128, 224, 128, 1 }, {  96, 224,  96, 1 },
  {  64, 224,  64, 1 }, {  32, 224,  32, 1 }, {   0, 224,   0, 1 }, {  32, 224,  32, 1 },
  {  64, 224,  64, 1 }, {  96, 224,  96, 1 }, { 128, 224, 128, 1 }, { 160, 224, 160, 1 },
  { 192, 224, 192, 1 }, { 224, 224, 224, 1 }, { 192, 224, 192, 1 }, { 160, 224, 160, 1 },
  { 128, 224, 128, 1 }, {  96, 224,  96, 1 }, {  64, 224,  64, 1 }, {  32, 224,  32, 1 }
};
void(*warp_act_tbl[2])(sprite_status*) = { &sonic_act, &atom };
extern bmp_info SprBmp[700];
static unsigned short gmtime0;
static unsigned short setcnt;
static unsigned short gmtime1;


void warp_init() {
  int i;

  memset(actwk, 0, sizeof(actwk));

  scra_h_posit.l = 0;
  scra_v_posit.l = 0;
  scrb_h_posit.l = 0;
  scrb_v_posit.l = 0;
  scrc_h_posit.l = 0;
  scrc_v_posit.l = 0;
  scrz_h_posit.l = 0;
  scrz_v_posit.l = 0;

  for (i = 0; i < 32; ++i) {
    lpcolorwk[i] = colortbl[i];
  }
  soundset(216);
  clwin_init();
  gmtime0 = 420;
  clwin();

}



sprite_status* atomwk_search() {
  int i;


  for (i = 4; i < 32; ++i) {
    if (!actwk[i].actno) return &actwk[i];
  }
  return &actwk[4];
}



int warp() {
  sprite_status* pActwk;
  unsigned short wD0;

  if (!gmtime0)
    return 1;

  clchg();
  wD0 = gmtime1 & 3;
  if (!wD0) {
    wD0 = setcnt++;
    setcnt &= 3;
    actwk[wD0].actno = 1;
  }

  wD0 = gmtime1 & 3;
  if (!wD0) {
    pActwk = atomwk_search();
    pActwk->actno = 2;
  }

  action();
  patset();

  --gmtime0;
  ++gmtime1;
  vscroll.w.h -= 4;

  if (!gmtime0 || swdata.b.l & 128) {
    gmtime0 = 0;
    clwout();
  }
  return 0;
}


static sprite_pattern snc0 = {
  1, { { -16, -24, 0, 0 } }
};
static sprite_pattern snc1 = {
  1, { { -16, -24, 0, 1 } }
};
static sprite_pattern snc2 = {
  1, { { -16, -24, 0, 2 } }
};
static sprite_pattern snc3 = {
  1, { { -16, -24, 0, 3 } }
};
static sprite_pattern snc4 = {
  1, { { -16, -24, 0, 4 } }
};
static sprite_pattern* ptsonic[5] = {
  &snc0,
  &snc1,
  &snc2,
  &snc3,
  &snc4
};

void sonic0(sprite_status* pActwk) {
  pActwk->sproffset = 32768;
  pActwk->patbase = ptsonic;
  pActwk->xposi.w.h = 288;
  pActwk->yposi.w.h = 416;
  ++pActwk->r_no0;
}

void sonic1(sprite_status* pActwk) {
  pActwk->yposi.w.h -= 8;
  if (pActwk->yposi.w.h == 248) {
    ++pActwk->r_no0;
    pActwk->actfree[8] = 240;
  }

}

void sonic2(sprite_status* pActwk) {
  --pActwk->actfree[8];
  if (pActwk->actfree[8] == 0) {
    ++pActwk->r_no0;
  }

}

void sonic3(sprite_status* pActwk) {
  pActwk->yposi.w.h -= 8;
  if (pActwk->yposi.w.h == 96) {
    ++pActwk->r_no0;
  }

}

void sonic_act(sprite_status* pActwk) {
  if (gmtime1 & 1) {
    ++pActwk->patno;
    if (pActwk->patno > 4) pActwk->patno = 0;
  }
  pActwk->patno = actwk[0].patno;


  switch (pActwk->r_no0) {
    case 0:
      sonic0(pActwk);
      break;
    case 1:
      sonic1(pActwk);
      break;
    case 2:
      sonic2(pActwk);
      break;
    case 3:
      sonic3(pActwk);
  }





  actionsub(pActwk);

}

static sprite_pattern atm0 = {
  1, { { -16, -16, 0, 5 } }
};
static sprite_pattern atm1 = {
  1, { { -16, -16, 0, 6 } }
};
static sprite_pattern atm2 = {
  1, { { -24, -24, 0, 7 } }
};
static sprite_pattern atm3 = {
  1, { { -16, -16, 0, 8 } }
};
static sprite_pattern atm4 = {
  1, { { -16, -24, 0, 9 } }
};
static sprite_pattern* spr_atom[5] = {
  &atm0,
  &atm1,
  &atm2,
  &atm3,
  &atm4
};

void atom1(sprite_status* pActwk) {
  int lD0;

  lD0 = *(int*)&pActwk->actfree[0];
  pActwk->xposi.l += lD0;

  lD0 = *(int*)&pActwk->actfree[4];
  pActwk->yposi.l += lD0;

  --pActwk->actfree[8];
  if (pActwk->actfree[8]) {
    actionsub(pActwk);
  }
  else {
    frameout(pActwk);
  }

}


void atom0(sprite_status* pActwk) {
  int_union lD0, lD1;
  pActwk->sproffset = 32768;
  pActwk->patbase = spr_atom;
  ++pActwk->r_no0;


  lD0.l = lD1.l = random();
  lD0.l &= 262143;
  *(int*)&pActwk->actfree[4] = lD0.l;
  lD1.w.l &= 31;
  pActwk->xposi.w.h = actwk[0].xposi.w.h - 16 + lD1.w.l;
  pActwk->yposi.w.h = actwk[0].yposi.w.h - 24;
  pActwk->actfree[8] = 45;
  atom1(pActwk);
}


void atom(sprite_status* pActwk) {
  if (gmtime1 & 1) {
    ++pActwk->patno;
    if (pActwk->patno > 4) pActwk->patno = 0;
  }
  switch (pActwk->r_no0) {
    case 0:
      atom0(pActwk);
      break;
    case 1:
      atom1(pActwk);
  }



}



void clchg() {
  unsigned short wD0;
  int i;

  ++clchg_cnt[0];
  if ((clchg_cnt[0] & 1) == 0) {


    wD0 = clchg_cnt[1];
    ++clchg_cnt[1];
    if (clchg_cnt[1] >= 14) {
      clchg_cnt[1] = 0;
    }
    for (i = 17; i < 31; ++i) {
      lpcolorwk[i] = clchg_tbl[wD0++];
    }
  }
}
