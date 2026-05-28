#include "../EQU.h"
#include "SCREW.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../PLAYSUB.h"

static unsigned char pchg_00[7] = { 1, 0, 1, 2, 3, 4, 255 };
static unsigned char* pchg[1] = { pchg_00 };

static sprite_pattern z4a_screw0_pat00 = { 1, { { -16, -8, 0, 457 } } };
static sprite_pattern z41b_screw0_pat00 = { 1, { { -16, -8, 0, 477 } } };
static sprite_pattern z42b_screw0_pat00 = { 1, { { -16, -8, 0, 528 } } };
static sprite_pattern z43_screw0_pat00 = { 1, { { -16, -8, 0, 488 } } };
static sprite_pattern z4a_screw0_pat01 = { 1, { { -12, -8, 0, 458 } } };
static sprite_pattern z41b_screw0_pat01 = { 1, { { -12, -8, 0, 478 } } };
static sprite_pattern z42b_screw0_pat01 = { 1, { { -12, -8, 0, 529 } } };
static sprite_pattern z43_screw0_pat01 = { 1, { { -12, -8, 0, 489 } } };
static sprite_pattern z4a_screw0_pat02 = { 1, { { -8, -8, 0, 459 } } };
static sprite_pattern z41b_screw0_pat02 = { 1, { { -8, -8, 0, 479 } } };
static sprite_pattern z42b_screw0_pat02 = { 1, { { -8, -8, 0, 530 } } };
static sprite_pattern z43_screw0_pat02 = { 1, { { -8, -8, 0, 490 } } };
static sprite_pattern z4a_screw0_pat03 = { 1, { { -12, -8, 0, 460 } } };
static sprite_pattern z41b_screw0_pat03 = { 1, { { -12, -8, 0, 480 } } };
static sprite_pattern z42b_screw0_pat03 = { 1, { { -12, -8, 0, 531 } } };
static sprite_pattern z43_screw0_pat03 = { 1, { { -12, -8, 0, 491 } } };
static sprite_pattern z4a_screw0_pat04 = { 1, { { -16, -8, 0, 461 } } };
static sprite_pattern z41b_screw0_pat04 = { 1, { { -16, -8, 0, 481 } } };
static sprite_pattern z42b_screw0_pat04 = { 1, { { -16, -8, 0, 532 } } };
static sprite_pattern z43_screw0_pat04 = { 1, { { -16, -8, 0, 492 } } };
sprite_pattern* z4a_pat_screw0a[5] = {
  &z4a_screw0_pat00,
  &z4a_screw0_pat01,
  &z4a_screw0_pat02,
  &z4a_screw0_pat03,
  &z4a_screw0_pat04
};
sprite_pattern* z41b_pat_screw0a[5] = {
  &z41b_screw0_pat00,
  &z41b_screw0_pat01,
  &z41b_screw0_pat02,
  &z41b_screw0_pat03,
  &z41b_screw0_pat04
};
sprite_pattern* z42b_pat_screw0a[5] = {
  &z42b_screw0_pat00,
  &z42b_screw0_pat01,
  &z42b_screw0_pat02,
  &z42b_screw0_pat03,
  &z42b_screw0_pat04
};
sprite_pattern* z43_pat_screw0a[5] = {
  &z43_screw0_pat00,
  &z43_screw0_pat01,
  &z43_screw0_pat02,
  &z43_screw0_pat03,
  &z43_screw0_pat04
};
static sprite_pattern z4a_screw1_pat00 = { 1, { { -8, -16, 0, 462 } } };
static sprite_pattern z41b_screw1_pat00 = { 1, { { -8, -16, 0, 482 } } };
static sprite_pattern z42b_screw1_pat00 = { 1, { { -8, -16, 0, 533 } } };
static sprite_pattern z43_screw1_pat00 = { 1, { { -8, -16, 0, 493 } } };
static sprite_pattern z4a_screw1_pat01 = { 1, { { -8, -12, 0, 463 } } };
static sprite_pattern z41b_screw1_pat01 = { 1, { { -8, -12, 0, 483 } } };
static sprite_pattern z42b_screw1_pat01 = { 1, { { -8, -12, 0, 534 } } };
static sprite_pattern z43_screw1_pat01 = { 1, { { -8, -12, 0, 494 } } };
static sprite_pattern z4a_screw1_pat02 = { 1, { { -8, -8, 0, 464 } } };
static sprite_pattern z41b_screw1_pat02 = { 1, { { -8, -8, 0, 484 } } };
static sprite_pattern z42b_screw1_pat02 = { 1, { { -8, -8, 0, 535 } } };
static sprite_pattern z43_screw1_pat02 = { 1, { { -8, -8, 0, 495 } } };
static sprite_pattern z4a_screw1_pat03 = { 1, { { -8, -12, 0, 465 } } };
static sprite_pattern z41b_screw1_pat03 = { 1, { { -8, -12, 0, 485 } } };
static sprite_pattern z42b_screw1_pat03 = { 1, { { -8, -12, 0, 536 } } };
static sprite_pattern z43_screw1_pat03 = { 1, { { -8, -12, 0, 496 } } };
static sprite_pattern z4a_screw1_pat04 = { 1, { { -8, -16, 0, 466 } } };
static sprite_pattern z41b_screw1_pat04 = { 1, { { -8, -16, 0, 486 } } };
static sprite_pattern z42b_screw1_pat04 = { 1, { { -8, -16, 0, 537 } } };
static sprite_pattern z43_screw1_pat04 = { 1, { { -8, -16, 0, 497 } } };
sprite_pattern* z4a_pat_screw1a[5] = {
  &z4a_screw1_pat00,
  &z4a_screw1_pat01,
  &z4a_screw1_pat02,
  &z4a_screw1_pat03,
  &z4a_screw1_pat04
};
sprite_pattern* z41b_pat_screw1a[5] = {
  &z41b_screw1_pat00,
  &z41b_screw1_pat01,
  &z41b_screw1_pat02,
  &z41b_screw1_pat03,
  &z41b_screw1_pat04
};
sprite_pattern* z42b_pat_screw1a[5] = {
  &z42b_screw1_pat00,
  &z42b_screw1_pat01,
  &z42b_screw1_pat02,
  &z42b_screw1_pat03,
  &z42b_screw1_pat04
};
sprite_pattern* z43_pat_screw1a[5] = {
  &z43_screw1_pat00,
  &z43_screw1_pat01,
  &z43_screw1_pat02,
  &z43_screw1_pat03,
  &z43_screw1_pat04
};
sprite_pattern z41c_pat_screw00 = { 1, { { -16, -8, 0, 441 } } };
sprite_pattern z41d_pat_screw00 = { 1, { { -16, -8, 0, 442 } } };
sprite_pattern z42c_pat_screw00 = { 1, { { -16, -8, 0, 432 } } };
sprite_pattern z41c_pat_screw01 = { 1, { { -16, -8, 0, 442 } } };
sprite_pattern z41d_pat_screw01 = { 1, { { -16, -8, 0, 443 } } };
sprite_pattern z42c_pat_screw01 = { 1, { { -16, -8, 0, 433 } } };
sprite_pattern z41c_pat_screw02 = { 1, { { -8, -16, 0, 443 } } };
sprite_pattern z41d_pat_screw02 = { 1, { { -8, -16, 0, 444 } } };
sprite_pattern z42c_pat_screw02 = { 1, { { -8, -16, 0, 434 } } };
sprite_pattern z41c_pat_screw03 = { 1, { { -8, -16, 0, 444 } } };
sprite_pattern z41d_pat_screw03 = { 1, { { -8, -16, 0, 445 } } };
sprite_pattern z42c_pat_screw03 = { 1, { { -8, -16, 0, 435 } } };
sprite_pattern* z41c_pat_screw0c[2] = {
  &z41c_pat_screw00,
  &z41c_pat_screw01
};
sprite_pattern* z41d_pat_screw0c[2] = {
  &z41d_pat_screw00,
  &z41d_pat_screw01
};
sprite_pattern* z42c_pat_screw0c[2] = {
  &z42c_pat_screw00,
  &z42c_pat_screw01
};
sprite_pattern* z41c_pat_screw1c[2] = {
  &z41c_pat_screw02,
  &z41c_pat_screw03
};
sprite_pattern* z41d_pat_screw1c[2] = {
  &z41d_pat_screw02,
  &z41d_pat_screw03
};
sprite_pattern* z42c_pat_screw1c[2] = {
  &z42c_pat_screw02,
  &z42c_pat_screw03
};
sprite_pattern** pats_screw0[3][4] = {
  { z41b_pat_screw0a, z4a_pat_screw0a, z41d_pat_screw0c, z41c_pat_screw0c },
  { z42b_pat_screw0a, z4a_pat_screw0a, z42c_pat_screw0c, z42c_pat_screw0c },
  { 0, 0, z43_pat_screw0a, z43_pat_screw0a }
};
sprite_pattern** pats_screw1[3][4] = {
  { z41b_pat_screw1a, z4a_pat_screw1a, z41d_pat_screw1c, z41c_pat_screw1c },
  { z42b_pat_screw1a, z4a_pat_screw1a, z42c_pat_screw1c, z42c_pat_screw1c },
  { 0, 0, z43_pat_screw1a, z43_pat_screw1a }
};


void screw(sprite_status* pActwk) {
  sprite_status* pCallactwk;

  if (stageno_i.b.l != 2 && (time_flag_i & 0x7F) == 2) {
    pCallactwk = &actwk[((short*)pActwk)[23]];
  }

  if (!pActwk->r_no0) {
    if (stageno_i.b.l != 2 && (time_flag_i & 0x7F) == 2) {
      pActwk->actfree[2] = pCallactwk->actno;
    }
    pActwk->r_no0 += 2;
    pActwk->actflg |= 4;
    pActwk->sprpri = 3;
    pActwk->sproffset = 17280;

    if (pActwk->userflag.b.h & 128) {
      if (stageno_i.b.l != 2 && (time_flag_i & 0x7F) == 2) {
        ++pActwk->patno;
      }
      else {
        pActwk->actfree[21] = 255;
      }
    }

    if (!(pActwk->userflag.b.h & 2)) {
      pActwk->patbase = pats_screw0[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
      pActwk->sprhsize = 16;
      pActwk->sprvsize = 8;
    } else {
      pActwk->patbase = pats_screw1[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
      pActwk->sprhsize = 8;
      pActwk->sprvsize = 16;
    }

    if (pActwk->userflag.b.h & 1) {
      pActwk->actflg |= 3;
      pActwk->cddat |= 3;
    }
  }

  if (stageno_i.b.l == 2 || (time_flag_i & 0x7F) != 2 || pActwk->actfree[2] == pCallactwk->actno) {
    if (!(pActwk->userflag.b.l & 128) && !pActwk->actfree[20] && switchflag[pActwk->userflag.b.l]) {
      if (stageno_i.b.l != 2 && (time_flag_i & 0x7F) == 2) {
        pActwk->actfree[20] = 255;
        pActwk->patno ^= 1;
      }
      else {
        pActwk->actfree[20] = 1;
        pActwk->actfree[21] = ~pActwk->actfree[21];
      }
    }
    if (stageno_i.b.l != 2 && (time_flag_i & 0x7F) == 2) {
      actionsub(pActwk);
      return;
    }
  }

  if (stageno_i.b.l != 2 && (time_flag_i & 0x7F) != 2) {
    if (!pActwk->actfree[21]) {
      pActwk->patno = 0;
    }
    else {
      patchg(pActwk, pchg);
    }
  }
  actionsub(pActwk);
  if (stageno_i.b.l != 2 && (time_flag_i & 0x7F) == 2) {
    frameout(pActwk);
  }
  else {
    frameout_s(pActwk);
  }
}
