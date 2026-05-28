#include "EQU.h"
#include "ACT.h"
#include "ACTION.h"

extern void(*z11a_act_tbl[64])(sprite_status*);
extern void(*z11b_act_tbl[64])(sprite_status*);
extern void(*z12a_act_tbl[64])(sprite_status*);
extern void(*z13c_act_tbl[64])(sprite_status*);
extern void(*z31a_act_tbl[60])(sprite_status*);
extern void(*z31b_act_tbl[60])(sprite_status*);
extern void(*z32a_act_tbl[60])(sprite_status*);
extern void(*z33c_act_tbl[63])(sprite_status*);
extern void(*z41a_act_tbl[82])(sprite_status*);
extern void(*z41b_act_tbl[82])(sprite_status*);
extern void(*z41c_act_tbl[82])(sprite_status*);
extern void(*z42a_act_tbl[82])(sprite_status*);
extern void(*z42b_act_tbl[82])(sprite_status*);
extern void(*z42c_act_tbl[80])(sprite_status*);
extern void(*z43c_act_tbl[80])(sprite_status*);
extern void(*z51a_act_tbl[60])(sprite_status*);
extern void(*z53_act_tbl[60])(sprite_status*);
extern void(*z61a_act_tbl[60])(sprite_status*);
extern void(*z62a_act_tbl[60])(sprite_status*);
extern void(*z63_act_tbl[64])(sprite_status*);
extern void(*z71a_act_tbl[60])(sprite_status*);
extern void(*z73_act_tbl[60])(sprite_status*);
extern void(*z81a_act_tbl[67])(sprite_status*);
extern void(*z82a_act_tbl[67])(sprite_status*);
extern void(*z83_act_tbl[67])(sprite_status*);
extern void(*warp_act_tbl[2])(sprite_status*);

void(*(*act_tbls[8][3][3]))(sprite_status*) = {
  {
    { z11b_act_tbl, z11a_act_tbl, z11b_act_tbl },
    { z12a_act_tbl, z12a_act_tbl, z12a_act_tbl },
    { 0, 0, z13c_act_tbl }
  },
  {
    { z31b_act_tbl, z31a_act_tbl, z31b_act_tbl },
    { z32a_act_tbl, z32a_act_tbl, z32a_act_tbl },
    { 0, 0, z33c_act_tbl }
  },
  {
    { z41b_act_tbl, z41a_act_tbl, z41c_act_tbl },
    { z42b_act_tbl, z42a_act_tbl, z42c_act_tbl },
    { 0, 0, z43c_act_tbl }
  },
  {
    { z51a_act_tbl, z51a_act_tbl, z51a_act_tbl },
    { z51a_act_tbl, z51a_act_tbl, z51a_act_tbl },
    { 0, 0, z53_act_tbl }
  },
  {
    { z61a_act_tbl, z61a_act_tbl, z61a_act_tbl },
    { z62a_act_tbl, z62a_act_tbl, z62a_act_tbl },
    { 0, 0, z63_act_tbl }
  },
  {
    { z71a_act_tbl, z71a_act_tbl, z71a_act_tbl },
    { z71a_act_tbl, z71a_act_tbl, z71a_act_tbl },
    { 0, 0, z73_act_tbl }
  },
  {
    { z81a_act_tbl, z81a_act_tbl, z81a_act_tbl },
    { z82a_act_tbl, z82a_act_tbl, z82a_act_tbl },
    { 0, 0, z83_act_tbl }
  },
  {
    { warp_act_tbl, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 }
  }
};


void debugact(sprite_status* pActwk) {
  if (pActwk->xposi.w.h++ >= 300) {
    pActwk->xposi.w.h = 0;
  }
  if (pActwk->yposi.w.h++ >= 200) {
    pActwk->yposi.w.h = 0;
  }

  actionsub(pActwk);
}


void noact(sprite_status* pActwk) {
  frameout(pActwk);
}
