#include "../EQU.h"
#include "UDBLK6.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../RIDECHK.h"

static sprite_pattern udblk6pat0 = { 1, { { -48, -80, 0, 481 } } };
static sprite_pattern z6budblk6pat0 = { 1, { { -48, -80, 0, 475 } } };
static sprite_pattern z63udblk6pat0 = { 1, { { -48, -80, 0, 448 } } };
sprite_pattern* udblk6pat[1] = { &udblk6pat0 };
sprite_pattern* z6budblk6pat[1] = { &udblk6pat0 };
sprite_pattern* z63udblk6pat[1] = { &udblk6pat0 };
sprite_pattern** udblk6pats[3][3] =
{
  { z6budblk6pat, udblk6pat,udblk6pat },
  { z6budblk6pat, udblk6pat,udblk6pat },
  { 0, 0, z63udblk6pat }
};




















void udblk6(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      udblk6_init(actionwk);
    case 2:
      udblk6_chk1(actionwk);
      break;
    case 4:
      udblk6_mov1(actionwk);
      break;
    case 6:
      udblk6_chk2(actionwk);
      break;
    case 8:
      udblk6_mov2(actionwk);
      break;
  }
  actionsub(actionwk);
  frameout_s(actionwk);
}

void udblk6_ridechk(sprite_status* actionwk) {
  ride_on_chk(actionwk, &actwk[0]);
}


void udblk6_init(sprite_status* actionwk) {
  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 3;
  actionwk->sproffset = 17640;
  actionwk->patbase = udblk6pats[stageno_i.b.l][time_flag_i & 0x7F];
  actionwk->sprvsize = 80;
  actionwk->sprhsize = 48;
  ((short*)actionwk)[27] = actionwk->yposi.w.h;
}


void udblk6_chk1(sprite_status* actionwk) {
  short d0;

  d0 = actionwk->yposi.w.h - actwk[0].yposi.w.h;
  if (d0 < 0)
  {
    d0 = -d0;
  }

  if (d0 < 192)
  {
    d0 = actionwk->xposi.w.h - actwk[0].xposi.w.h;
    if (d0 >= 0)
    {
      if (d0 < 136)
      {
        actionwk->actfree[18] = 0;
        ((short*)actionwk)[31] = 0;
        actionwk->r_no0 += 2;
      }
    }
  }

  udblk6_ridechk(actionwk);
}


void udblk6_mov1(sprite_status* actionwk) {
  actionwk->actfree[18] = 0;
  movecnt(actionwk);
  if (actionwk->actfree[17] == 2)
    actionwk->r_no0 += 2;

  udblk6_ridechk(actionwk);
}


void udblk6_chk2(sprite_status* actionwk) {
  short d0;

  d0 = actionwk->yposi.w.h - actwk[0].yposi.w.h;
  if (d0 < 0)
  {
    d0 = -d0;
  }

  if (d0 < 192)
  {
    d0 = actwk[0].xposi.w.h - actionwk->xposi.w.h;
    if (d0 >= 0)
    {
      if (d0 >= 136)
      {
        ((short*)actionwk)[31] = 0;
        actionwk->r_no0 += 2;
      }
    }
  }

  udblk6_ridechk(actionwk);
}


void udblk6_mov2(sprite_status* actionwk) {
  actionwk->actfree[18] = 1;
  movecnt(actionwk);
  if (actionwk->actfree[17] == 2)
    actionwk->r_no0 = 2;

  udblk6_ridechk(actionwk);
}


void movecnt(sprite_status* actionwk) {

  short mvtbl1[6] =
  {
    64,  8,    0,
    64, -8,  512
  };


  short mvtbl2[6] =
  {
    64, -8,    0,
    64,  8, -512
  };
  short* a2;
  short d0;



  a2 = mvtbl1;
  if (actionwk->actfree[18] != 0) a2 = mvtbl2;

  if (actionwk->actfree[16] == 0)
  {
    d0 = actionwk->actfree[17] * 3;
    actionwk->actfree[16] = (char)a2[d0];
    ((short*)actionwk)[33] = a2[d0 + 1];
    ((short*)actionwk)[26] = a2[d0 + 2];
  }
  else
  {

    actionwk->yposi.l += actionwk->yspeed.w << 8;
    actionwk->yspeed.w += ((short*)actionwk)[33];

    if (--actionwk->actfree[16] == 0)
      ++actionwk->actfree[17];
  }
}
