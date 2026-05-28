#include "EQU.h"
#include "RING.h"
#include "ACTION.h"
#include "ACTSET.h"
#include "DIRCOL.h"
#include "ETC.h"
#include "LOADER2.h"
#include "PLAYSUB.h"

sprite_pattern ringsp0 = { 1, { { -8, -8, 0, 362 } } };
sprite_pattern z3ringsp0 = { 1, { { -8, -8, 0, 321 } } };
sprite_pattern z33ringsp0 = { 1, { { -8, -8, 0, 325 } } };
sprite_pattern z6ringsp0 = { 1, { { -8, -8, 0, 320 } } };
sprite_pattern z81ringsp0 = { 1, { { -8, -8, 0, 310 } } };
sprite_pattern z82ringsp0 = { 1, { { -8, -8, 0, 319 } } };
sprite_pattern z83ringsp0 = { 1, { { -8, -8, 0, 312 } } };
sprite_pattern ringsp1 = { 1, { { -8, -8, 0, 363 } } };
sprite_pattern z3ringsp1 = { 1, { { -8, -8, 0, 322 } } };
sprite_pattern z33ringsp1 = { 1, { { -8, -8, 0, 326 } } };
sprite_pattern z6ringsp1 = { 1, { { -8, -8, 0, 321 } } };
sprite_pattern z81ringsp1 = { 1, { { -8, -8, 0, 311 } } };
sprite_pattern z82ringsp1 = { 1, { { -8, -8, 0, 320 } } };
sprite_pattern z83ringsp1 = { 1, { { -8, -8, 0, 313 } } };
sprite_pattern ringsp2 = { 1, { { -4, -8, 0, 364 } } };
sprite_pattern z3ringsp2 = { 1, { { -4, -8, 0, 323 } } };
sprite_pattern z33ringsp2 = { 1, { { -4, -8, 0, 327 } } };
sprite_pattern z6ringsp2 = { 1, { { -4, -8, 0, 322 } } };
sprite_pattern z81ringsp2 = { 1, { { -4, -8, 0, 312 } } };
sprite_pattern z82ringsp2 = { 1, { { -4, -8, 0, 321 } } };
sprite_pattern z83ringsp2 = { 1, { { -4, -8, 0, 314 } } };
sprite_pattern ringsp3 = { 1, { { -8, -8, 0, 365 } } };
sprite_pattern z3ringsp3 = { 1, { { -8, -8, 0, 324 } } };
sprite_pattern z33ringsp3 = { 1, { { -8, -8, 0, 328 } } };
sprite_pattern z6ringsp3 = { 1, { { -8, -8, 0, 323 } } };
sprite_pattern z81ringsp3 = { 1, { { -8, -8, 0, 313 } } };
sprite_pattern z82ringsp3 = { 1, { { -8, -8, 0, 322 } } };
sprite_pattern z83ringsp3 = { 1, { { -8, -8, 0, 315 } } };
sprite_pattern ringsp4 = { 1, { { -8, -8, 0, 366 } } };
sprite_pattern z3ringsp4 = { 1, { { -8, -8, 0, 325 } } };
sprite_pattern z33ringsp4 = { 1, { { -8, -8, 0, 329 } } };
sprite_pattern z6ringsp4 = { 1, { { -8, -8, 0, 324 } } };
sprite_pattern z81ringsp4 = { 1, { { -8, -8, 0, 314 } } };
sprite_pattern z82ringsp4 = { 1, { { -8, -8, 0, 323 } } };
sprite_pattern z83ringsp4 = { 1, { { -8, -8, 0, 316 } } };
sprite_pattern ringsp5 = { 1, { { -8, -8, 0, 367 } } };
sprite_pattern z3ringsp5 = { 1, { { -8, -8, 0, 326 } } };
sprite_pattern z33ringsp5 = { 1, { { -8, -8, 0, 330 } } };
sprite_pattern z6ringsp5 = { 1, { { -8, -8, 0, 325 } } };
sprite_pattern z81ringsp5 = { 1, { { -8, -8, 0, 315 } } };
sprite_pattern z82ringsp5 = { 1, { { -8, -8, 0, 324 } } };
sprite_pattern z83ringsp5 = { 1, { { -8, -8, 0, 317 } } };
sprite_pattern ringsp6 = { 1, { { -8, -8, 0, 368 } } };
sprite_pattern z3ringsp6 = { 1, { { -8, -8, 0, 327 } } };
sprite_pattern z33ringsp6 = { 1, { { -8, -8, 0, 331 } } };
sprite_pattern z6ringsp6 = { 1, { { -8, -8, 0, 326 } } };
sprite_pattern z81ringsp6 = { 1, { { -8, -8, 0, 316 } } };
sprite_pattern z82ringsp6 = { 1, { { -8, -8, 0, 325 } } };
sprite_pattern z83ringsp6 = { 1, { { -8, -8, 0, 318 } } };
sprite_pattern ringsp7 = { 1, { { -8, -8, 0, 369 } } };
sprite_pattern z3ringsp7 = { 1, { { -8, -8, 0, 328 } } };
sprite_pattern z33ringsp7 = { 1, { { -8, -8, 0, 332 } } };
sprite_pattern z6ringsp7 = { 1, { { -8, -8, 0, 327 } } };
sprite_pattern z81ringsp7 = { 1, { { -8, -8, 0, 317 } } };
sprite_pattern z82ringsp7 = { 1, { { -8, -8, 0, 326 } } };
sprite_pattern z83ringsp7 = { 1, { { -8, -8, 0, 319 } } };
sprite_pattern ringsp8;
sprite_pattern* ringpat[9] = {
  &ringsp0,
  &ringsp1,
  &ringsp2,
  &ringsp3,
  &ringsp4,
  &ringsp5,
  &ringsp6,
  &ringsp7,
  &ringsp8
};
sprite_pattern* z3ringpat[9] = {
  &z3ringsp0,
  &z3ringsp1,
  &z3ringsp2,
  &z3ringsp3,
  &z3ringsp4,
  &z3ringsp5,
  &z3ringsp6,
  &z3ringsp7,
  &ringsp8
};
sprite_pattern* z33ringpat[9] = {
  &z33ringsp0,
  &z33ringsp1,
  &z33ringsp2,
  &z33ringsp3,
  &z33ringsp4,
  &z33ringsp5,
  &z33ringsp6,
  &z33ringsp7,
  &ringsp8
};
sprite_pattern* z6ringpat[9] = {
  &z6ringsp0,
  &z6ringsp1,
  &z6ringsp2,
  &z6ringsp3,
  &z6ringsp4,
  &z6ringsp5,
  &z6ringsp6,
  &z6ringsp7,
  &ringsp8
};
sprite_pattern* z81ringpat[9] = {
  &z81ringsp0,
  &z81ringsp1,
  &z81ringsp2,
  &z81ringsp3,
  &z81ringsp4,
  &z81ringsp5,
  &z81ringsp6,
  &z81ringsp7,
  &ringsp8
};
sprite_pattern* z82ringpat[9] = {
  &z82ringsp0,
  &z82ringsp1,
  &z82ringsp2,
  &z82ringsp3,
  &z82ringsp4,
  &z82ringsp5,
  &z82ringsp6,
  &z82ringsp7,
  &ringsp8
};
sprite_pattern* z83ringpat[9] = {
  &z83ringsp0,
  &z83ringsp1,
  &z83ringsp2,
  &z83ringsp3,
  &z83ringsp4,
  &z83ringsp5,
  &z83ringsp6,
  &z83ringsp7,
  &ringsp8
};
sprite_pattern** ringpats[7][3][3] = {
  {
    { ringpat, ringpat, ringpat },
    { ringpat, ringpat, ringpat },
    { 0, 0, ringpat }
  },
  {
    { z3ringpat, z3ringpat, z3ringpat },
    { z3ringpat, z3ringpat, z3ringpat },
    { 0, 0, z33ringpat }
  },
  {
    { ringpat, ringpat, ringpat },
    { ringpat, ringpat, ringpat },
    { 0, 0, ringpat }
  },
  {
    { ringpat, ringpat, ringpat },
    { ringpat, ringpat, ringpat },
    { 0, 0, ringpat }
  },
  {
    { z6ringpat, z6ringpat, z6ringpat },
    { z6ringpat, z6ringpat, z6ringpat },
    { 0, 0, z6ringpat }
  },
  {
    { ringpat, ringpat, ringpat },
    { ringpat, ringpat, ringpat },
    { 0, 0, ringpat }
  },
  {
    { z81ringpat, z81ringpat, z81ringpat },
    { z82ringpat, z82ringpat, z82ringpat },
    { 0, 0, z83ringpat }
  }
};
unsigned char ringchg0[6] = { 5, 4, 5, 6, 7, 252 };
unsigned char ringchg1[6] = { 7, 0, 1, 2, 3, 255 };
unsigned char ringchg2[6] = { 7, 0, 1, 2, 3, 255 };
unsigned char* ringchg[3] = {
  ringchg0,
  ringchg1,
  ringchg2
};


void ring(sprite_status* pActwk) {
  void(*ring_move_tbl[5])(sprite_status*) = {
    &ringinit,
    &ringmove,
    &ringget,
    &ringdie,
    &ringerase
  };

  ring_move_tbl[pActwk->r_no0 / 2](pActwk);
}





void ringinit(sprite_status* pActwk) {
  char ringtbl[32] = {
     16,   0,
     24,   0,
     32,   0,
      0,  16,
      0,  24,
      0,  32,
     16,  16,
     24,  24,
     32,  32,
    -16,  16,
    -24,  24,
    -32,  32,
     16,   8,
     24,  16,
    -16,   8,
    -24,  16
  };
  int fw_index;
  int i;
  char ring_counter;
  short d0, d1, d2, d3, d5, d6;
  char d4;
  sprite_status* new_actwk;

  d1 = time_flag & 127;
  if (time_flag & 128) {
    d1 += -time_item;
    if (d1 < 0) d1 = 0;
    else if (d1 >= 3) d1 = 2;
  }
  fw_index = d1 + pActwk->cdsts * 3;

  d4 = flagwork[fw_index];
  d1 = pActwk->userflag.b.h & 7;
  if (d1 == 7) d1 = 6;
  ring_counter = 1;
  d0 = ((unsigned char)pActwk->userflag.b.h >> 4) * 2;
  d5 = ringtbl[d0];
  d6 = ringtbl[d0 + 1];
  new_actwk = pActwk;
  d2 = pActwk->xposi.w.h;
  d3 = pActwk->yposi.w.h;

  d0 = time_flag & 127;
  if (time_flag & 128) {
    d0 += -time_item;
    if (d0 < 0) d0 = 0;
    else if (d0 >= 3) d0 = 2;
  }
  i = fw_index + 1;
  do {
    if (flagwork[--i] & (1 << (ring_counter - 1))) goto label3;
  } while (--d0 != -1);

  flagwork[fw_index] &= 127;
  goto label2;

label1:
  d0 = time_flag & 127;
  if (time_flag & 128) {
    d0 += -time_item;
    if (d0 < 0) d0 = 0;
    else if (d0 >= 3) d0 = 2;
  }
  i = fw_index + 1;
  do {
    if (flagwork[--i] & (1 << (ring_counter - 1))) goto label3;
  } while (--d0 != -1);

  flagwork[fw_index] &= 127;
  if (actwkchk2(pActwk, &new_actwk) == 0) {
label2:
    new_actwk->actno = 16;
    new_actwk->r_no0 = 2;
    new_actwk->xposi.w.h = d2;
    ((short*)new_actwk)[27] = pActwk->xposi.w.h;
    new_actwk->yposi.w.h = d3;
    new_actwk->patbase = ringpats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
    new_actwk->sproffset = 42926;
    new_actwk->sprpri = 2;
    if (stageno.b.h == 6) {
      new_actwk->sprpri = 0;
      new_actwk->userflag.b.l = pActwk->userflag.b.l;
      if (new_actwk->userflag.b.l) {
        new_actwk->sproffset &= 127;
        new_actwk->sprpri = 2;
      }
    }
    new_actwk->actflg = 4;
    new_actwk->colino = 71;
    new_actwk->sprhsize = 8;
    new_actwk->sprvsize = 8;
    new_actwk->cdsts = pActwk->cdsts;
    new_actwk->actfree[10] = ring_counter;
    new_actwk->mstno.b.h = 1;
label3:
    ++ring_counter;
    d2 += d5;
    d3 += d6;
    if (--d1 != -1) goto label1;
  }
  d0 = time_flag & 127;
  if (time_flag & 128) {
    d0 += -time_item;
    if (d0 < 0) d0 = 0;
    else if (d0 >= 3) d0 = 2;
  }
  i = fw_index + 1;
  do {
    if (flagwork[--i] & 1) {
      frameout(pActwk);
      return;
    }
  } while (--d0 != -1);

  ringmove(pActwk);
}





void ringmove(sprite_status* pActwk) {
  unsigned short d0;

  if (pActwk->actflg >= 0) {
    d0 = (((unsigned short*)pActwk)[27] & 65408) - (((uint_union*)&scra_h_posit)->w.h - 128 & 65408);
    if (d0 > 640) {
      ringerase(pActwk);
      return;
    }
  }

  pActwk->patcnt = (unsigned char)((systemtimer.b.b4 >> 3) & 3) + 1;
  pActwk->pattim = systemtimer.b.b4 & 7;
  patchg(pActwk, ringchg);
  actionsub(pActwk);
}





void ringget(sprite_status* pActwk) {
  short d0, d1;

  pActwk->r_no0 += 2;
  pActwk->colino = 0;
  pActwk->sprpri = 1;
  pActwk->mstno.b.h = 0;
  ringgetsub();

  d0 = pActwk->cdsts * 3;
  d1 = time_flag & 127;
  if (time_flag & 128) {
    d1 += -time_item;
    if (d1 < 0) d1 = 0;
    else if (d1 >= 3) d1 = 2;
  }

  flagwork[d0 + d1] |= 1 << (pActwk->actfree[10] - 1);
  ringdie(pActwk);
}





void ringgetsub(void) {
  ++plring;
  plring_f |= 1;
  if (plring >= 100) {
    if (plring_f2 & 2) {
      if (plring < 200) {
        soundset(149);
        return;
      }
      if (plring_f2 & 4) {
        soundset(149);
        return;
      }
      plring_f2 |= 4;
    }
    plring_f2 |= 2;
    ++pl_suu;
    ++pl_suu_f;
    sub_sync(122);
  }
  else {
    soundset(149);
  }

}





void ringdie(sprite_status* pActwk) {
  patchg(pActwk, ringchg);
  actionsub(pActwk);
}





void ringerase(sprite_status* pActwk) {
  frameout(pActwk);
}








void flyring(sprite_status* pActwk) {
  void(*flyring_move_tbl[5])(sprite_status*) = {
    &flyringinit,
    &flyringmove,
    &flyringget,
    &flyringdie,
    &flyringerase
  };

  flyring_move_tbl[pActwk->r_no0 / 2](pActwk);
}





void flyringinit(sprite_status* pActwk) {
  short d2, d3, d5;
  sprite_status* new_actwk;
  unsigned short d0, d1;
  short_union d4;

  new_actwk = pActwk;
  if ((d5 = plring) > 32) d5 = 32;
  --d5;
  d4.w = 648;
  goto label1;

  do {
    if (actwkchk(&new_actwk) != 0) break;
label1:
    new_actwk->actno = 17;
    new_actwk->r_no0 += 2;
    new_actwk->sprvsize = 8;
    new_actwk->sprhs = 8;
    new_actwk->xposi.w.h = pActwk->xposi.w.h;
    new_actwk->yposi.w.h = pActwk->yposi.w.h;
    new_actwk->patbase = ringpats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
    new_actwk->userflag.b.l = pActwk->userflag.b.l;
    new_actwk->sproffset = 42926;
    new_actwk->sprpri = 3;
    if (stageno.b.h == 6) {
      new_actwk->sprpri = 0;
      if (pActwk->userflag.b.l) {
        new_actwk->sprpri = 3;
        new_actwk->sproffset &= 127;
      }
    }
    new_actwk->actflg = 4;
    new_actwk->colino = 71;
    new_actwk->sprhsize = 8;
    new_actwk->sprvsize = 8;
    sys_pattim4 = 255;
    new_actwk->mstno.b.h = 2;

    if (d4.w >= 0) {
      sinset(d4.b.l, (short*)&d0, (short*)&d1);
      d2 = d0 << (d4.w >> 8);
      d3 = d1 << (d4.w >> 8);
      if ((d4.b.l += 16) > 0)
        if ((d4.w -= 128) < 0) d4.w = 648;
    }
    new_actwk->xspeed.w = d2;
    new_actwk->yspeed.w = d3;
    d2 *= -1;
    d4.w *= -1;
  } while (--d5 != -1);

  if (gKeepWork.User & 1) {


    plring /= 2;
  }
  else {
    plring = 0;
  }
  plring_f = 128;
  plring_f2 = 0;
  soundset(148);
  flyringmove(pActwk);
}





void flyringmove(sprite_status* pActwk) {
  short d1;



  speedset2(pActwk);
  if ((pActwk->yspeed.w += 24) >= 0) {
    if (!((systemtimer.b.b4 + ((unsigned int)(pActwk - actwk) / 68)) & 3)) {
      if ((d1 = emycol_d(pActwk)) < 0) {
        pActwk->yposi.w.h += d1;
        pActwk->yspeed.w -= pActwk->yspeed.w / 4;
        pActwk->yspeed.w *= -1;
      }
    }
  }
  if (sys_pattim4) {
    if (pActwk->yposi.w.h < scralim_down + 224) {
      patchg(pActwk, ringchg);
      actionsub(pActwk);
      return;
    }
  }
  flyringerase(pActwk);
}





void flyringget(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->colino = 0;
  pActwk->sprpri = 1;
  pActwk->mstno.b.h = 0;
  ringgetsub();
  flyringdie(pActwk);
}





void flyringdie(sprite_status* pActwk) {
  patchg(pActwk, ringchg);
  actionsub(pActwk);
}





void flyringerase(sprite_status* pActwk) {
  frameout(pActwk);
}
