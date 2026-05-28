#include "EQU.h"
#include "BLOCK.h"
#include "ACTION.h"
#include "DUMMY.h"
#include "PLAYSUB.h"
#include "RIDECHK.h"

void(*block_tbl[7])(sprite_status*) = {
  &block_init,
  &block_move,
  &block_move2,
  &block_move3,
  &block_move4,
  &block_move5,
  &block_move6
};
unsigned char blockchg0[3] = { 2, 5, 255 };
unsigned char blockchg1[10] = { 2, 1, 5, 2, 5, 3, 5, 4, 5, 252 };
unsigned char blockchg2[10] = { 2, 1, 0, 2, 0, 3, 0, 4, 0, 252 };
unsigned char* blockchg[3] = {
  blockchg0,
  blockchg1,
  blockchg2
};
sprite_pattern block0 = { 0, { { -12, -12, 0, 294 } } };
sprite_pattern z3block0 = { 0, { { -12, -12, 0, 404 } } };
sprite_pattern z33block0 = { 0, { { -12, -12, 0, 408 } } };
sprite_pattern z6block0 = { 0, { { -12, -12, 0, 403 } } };
sprite_pattern block1 = { 0, { { -12, -12, 0, 294 } } };
sprite_pattern z3block1 = { 0, { { -12, -12, 0, 404 } } };
sprite_pattern z33block1 = { 0, { { -12, -12, 0, 408 } } };
sprite_pattern z6block1 = { 0, { { -12, -12, 0, 403 } } };
sprite_pattern block2 = { 1, { { -12, -12, 0, 295 } } };
sprite_pattern z3block2 = { 1, { { -12, -12, 0, 405 } } };
sprite_pattern z33block2 = { 1, { { -12, -12, 0, 409 } } };
sprite_pattern z6block2 = { 1, { { -12, -12, 0, 404 } } };
sprite_pattern block3 = { 1, { { -12, -12, 0, 296 } } };
sprite_pattern z3block3 = { 1, { { -12, -12, 0, 406 } } };
sprite_pattern z33block3 = { 1, { { -12, -12, 0, 410 } } };
sprite_pattern z6block3 = { 1, { { -12, -12, 0, 405 } } };
sprite_pattern block4 = { 1, { { -12, -12, 0, 297 } } };
sprite_pattern z3block4 = { 1, { { -12, -12, 0, 407 } } };
sprite_pattern z33block4 = { 1, { { -12, -12, 0, 411 } } };
sprite_pattern z6block4 = { 1, { { -12, -12, 0, 406 } } };
sprite_pattern block5 = { 1, { { -12, -12, 0, 298 } } };
sprite_pattern z3block5 = { 1, { { -12, -12, 0, 408 } } };
sprite_pattern z33block5 = { 1, { { -12, -12, 0, 412 } } };
sprite_pattern z6block5 = { 1, { { -12, -12, 0, 407 } } };
sprite_pattern* blockpat[6] = {
  &block0,
  &block1,
  &block2,
  &block3,
  &block4,
  &block5
};
sprite_pattern* z3blockpat[6] = {
  &z3block0,
  &z3block1,
  &z3block2,
  &z3block3,
  &z3block4,
  &z3block5
};
sprite_pattern* z33blockpat[6] = {
  &z33block0,
  &z33block1,
  &z33block2,
  &z33block3,
  &z33block4,
  &z33block5
};
sprite_pattern* z6blockpat[6] = {
  &z6block0,
  &z6block1,
  &z6block2,
  &z6block3,
  &z6block4,
  &z6block5
};
sprite_pattern** blockpats[7][3][3] = {
  {
    { blockpat, blockpat, blockpat },
    { blockpat, blockpat, blockpat },
    { 0, 0, blockpat }
  },
  {
    { z3blockpat, z3blockpat, z3blockpat },
    { z3blockpat, z3blockpat, z3blockpat },
    { 0, 0, z33blockpat }
  },
  {
    { blockpat, blockpat, blockpat },
    { blockpat, blockpat, blockpat },
    { 0, 0, blockpat }
  },
  {
    { blockpat, blockpat, blockpat },
    { blockpat, blockpat, blockpat },
    { 0, 0, blockpat }
  },
  {
    { z6blockpat, z6blockpat, z6blockpat },
    { z6blockpat, z6blockpat, z6blockpat },
    { 0, 0, z6blockpat }
  },
  {
    { blockpat, blockpat, blockpat },
    { blockpat, blockpat, blockpat },
    { 0, 0, blockpat }
  },
  {
    { blockpat, blockpat, blockpat },
    { blockpat, blockpat, blockpat },
    { 0, 0, blockpat }
  }
};


void block(sprite_status* pActwk) {
  short iD0, iD1;

  block_tbl[pActwk->r_no0 / 2](pActwk);
  iD0 = pActwk->xposi.w.h & 65408;
  iD1 = scra_h_posit.w.h - 128;
  iD1 &= -128;
  iD0 -= iD1;
  if ((unsigned short)iD0 > 640)
    frameout(pActwk);
}











void block_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->patbase = blockpats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];

  pa_set(pActwk, 5);

  pActwk->sprpri = 1;
  pActwk->sprhsize = 12;
  pActwk->sprvsize = 12;
  pActwk->patno = 5;
  block_move(pActwk);
}











void block_move(sprite_status* pActwk) {
  block_ride(pActwk);
  if (time_flag != 0)
    if (time_flag == 2)
    {
      if (pActwk->cddat & 8) goto label1;
    }
    else
    {

      pActwk->patno = 0;
      if (pActwk->cddat & 8)
      {
        pActwk->r_no0 = 6;
        pActwk->mstno.b.h = 1;
      }
    }

  actionsub(pActwk);
  return;
label1:
  pActwk->r_no0 += 2;
  block_move2(pActwk);
}











void block_move2(sprite_status* pActwk) {
  short iD0;

  block_ride(pActwk);
  pActwk->yposi.w.h += 2;
  iD0 = scra_v_posit.w.h;
  iD0 += 224;
  if (iD0 < pActwk->yposi.w.h)
  {
    frameout(pActwk);
  } else
  {
    actionsub(pActwk);
  }
}











void block_move3(sprite_status* pActwk) {
  block_ride(pActwk);
  if (!(pActwk->cddat & 8))
  {
    pActwk->r_no0 = 2;
    return;
  }

  patchg(pActwk, blockchg);
  actionsub(pActwk);
}











void block_move4(sprite_status* pActwk) {
  pActwk->mstno.b.h = 0;
  block_ride(pActwk);
  if (!(pActwk->cddat & 8))
  {
    pActwk->r_no0 += 2;
    pActwk->mstno.b.h = 2;
    return;
  }

  patchg(pActwk, blockchg);
  actionsub(pActwk);
}











void block_move5(sprite_status* pActwk) {
  block_ride(pActwk);
  patchg(pActwk, blockchg);
  actionsub(pActwk);
}











void block_move6(sprite_status* pActwk) {
  pActwk->r_no0 = 2;
}











void block_ride(sprite_status* pActwk) {
  ride_on_chk_b(pActwk, actwk);
  ride_on_chk_b(pActwk, actwk);
}












void ride_on_chk_b(sprite_status* pActwk, sprite_status* pPlaywk) {
  ridechk(pActwk, pPlaywk);
}
