#include "../EQU.h"
#include "WALL1.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../RIDECHK.h"

static void act_init(sprite_status* pActwk);
static void act_move(sprite_status* pActwk);

static sprite_pattern z4apat00 = { 1, { { -16, -16, 0, 450 } } };
static sprite_pattern z41bpat00 = { 1, { { -16, -16, 0, 470 } } };
static sprite_pattern z41cpat00 = { 1, { { -16, -16, 0, 434 } } };
static sprite_pattern z41dpat00 = { 1, { { -16, -16, 0, 469 } } };
static sprite_pattern z42bpat00 = { 1, { { -16, -16, 0, 466 } } };
static sprite_pattern z42cpat00 = { 1, { { -16, -16, 0, 465 } } };
static sprite_pattern z43pat00 = { 1, { { -16, -16, 0, 481 } } };
static sprite_pattern z4apat01 = { 1, { { -16, -16, 0, 451 } } };
static sprite_pattern z41bpat01 = { 1, { { -16, -16, 0, 471 } } };
static sprite_pattern z41cpat01 = { 1, { { -16, -16, 0, 435 } } };
static sprite_pattern z41dpat01 = { 1, { { -16, -16, 0, 470 } } };
static sprite_pattern z42bpat01 = { 1, { { -16, -16, 0, 467 } } };
static sprite_pattern z42cpat01 = { 1, { { -16, -16, 0, 466 } } };
static sprite_pattern z43pat01 = { 1, { { -16, -16, 0, 482 } } };
static sprite_pattern z4apat02 = { 1, { { -32, -16, 0, 452 } } };
static sprite_pattern z41bpat02 = { 1, { { -32, -16, 0, 472 } } };
static sprite_pattern z41cpat02 = { 1, { { -32, -16, 0, 436 } } };
static sprite_pattern z41dpat02 = { 1, { { -32, -16, 0, 471 } } };
static sprite_pattern z42bpat02 = { 1, { { -32, -16, 0, 468 } } };
static sprite_pattern z42cpat02 = { 1, { { -32, -16, 0, 467 } } };
static sprite_pattern z43pat02 = { 1, { { -32, -16, 0, 483 } } };
static sprite_pattern z4apat03 = { 1, { { -16, -32, 0, 453 } } };
static sprite_pattern z41bpat03 = { 1, { { -16, -32, 0, 473 } } };
static sprite_pattern z41cpat03 = { 1, { { -16, -32, 0, 437 } } };
static sprite_pattern z41dpat03 = { 1, { { -16, -32, 0, 472 } } };
static sprite_pattern z42bpat03 = { 1, { { -16, -32, 0, 469 } } };
static sprite_pattern z42cpat03 = { 1, { { -16, -32, 0, 468 } } };
static sprite_pattern z43pat03 = { 1, { { -16, -32, 0, 484 } } };
static sprite_pattern z4apat04 = { 1, { { -32, -32, 0, 454 } } };
static sprite_pattern z41bpat04 = { 1, { { -32, -32, 0, 474 } } };
static sprite_pattern z41cpat04 = { 1, { { -32, -32, 0, 438 } } };
static sprite_pattern z41dpat04 = { 1, { { -32, -32, 0, 473 } } };
static sprite_pattern z42bpat04 = { 1, { { -32, -32, 0, 470 } } };
static sprite_pattern z42cpat04 = { 1, { { -32, -32, 0, 469 } } };
static sprite_pattern z43pat04 = { 1, { { -32, -32, 0, 485 } } };
static sprite_pattern z4apat05 = { 1, { { -64, -16, 0, 455 } } };
static sprite_pattern z41bpat05 = { 1, { { -64, -16, 0, 475 } } };
static sprite_pattern z41cpat05 = { 1, { { -64, -16, 0, 439 } } };
static sprite_pattern z41dpat05 = { 1, { { -64, -16, 0, 474 } } };
static sprite_pattern z42bpat05 = { 1, { { -64, -16, 0, 471 } } };
static sprite_pattern z42cpat05 = { 1, { { -64, -16, 0, 470 } } };
static sprite_pattern z43pat05 = { 1, { { -64, -16, 0, 486 } } };
static sprite_pattern z4apat06 = { 1, { { -16, -64, 0, 456 } } };
static sprite_pattern z41bpat06 = { 1, { { -16, -64, 0, 476 } } };
static sprite_pattern z41cpat06 = { 1, { { -16, -64, 0, 440 } } };
static sprite_pattern z41dpat06 = { 1, { { -16, -64, 0, 475 } } };
static sprite_pattern z42bpat06 = { 1, { { -16, -64, 0, 472 } } };
static sprite_pattern z42cpat06 = { 1, { { -16, -64, 0, 471 } } };
static sprite_pattern z43pat06 = { 1, { { -16, -64, 0, 487 } } };
sprite_pattern* z4a_pat_wall1[7] = {
  &z4apat00,
  &z4apat01,
  &z4apat02,
  &z4apat03,
  &z4apat04,
  &z4apat05,
  &z4apat06
};
sprite_pattern* z41b_pat_wall1[7] = {
  &z41bpat00,
  &z41bpat01,
  &z41bpat02,
  &z41bpat03,
  &z41bpat04,
  &z41bpat05,
  &z41bpat06
};
sprite_pattern* z41c_pat_wall1[7] = {
  &z41cpat00,
  &z41cpat01,
  &z41cpat02,
  &z41cpat03,
  &z41cpat04,
  &z41cpat05,
  &z41cpat06
};
sprite_pattern* z41d_pat_wall1[7] = {
  &z41dpat00,
  &z41dpat01,
  &z41dpat02,
  &z41dpat03,
  &z41dpat04,
  &z41dpat05,
  &z41dpat06
};
sprite_pattern* z42b_pat_wall1[7] = {
  &z42bpat00,
  &z42bpat01,
  &z42bpat02,
  &z42bpat03,
  &z42bpat04,
  &z42bpat05,
  &z42bpat06
};
sprite_pattern* z42c_pat_wall1[7] = {
  &z42cpat00,
  &z42cpat01,
  &z42cpat02,
  &z42cpat03,
  &z42cpat04,
  &z42cpat05,
  &z42cpat06
};
sprite_pattern* z43_pat_wall1[7] = {
  &z43pat00,
  &z43pat01,
  &z43pat02,
  &z43pat03,
  &z43pat04,
  &z43pat05,
  &z43pat06
};
sprite_pattern** pats_wall1[3][4] = {
  { z41b_pat_wall1, z4a_pat_wall1, z41d_pat_wall1, z41c_pat_wall1 },
  { z42b_pat_wall1, z4a_pat_wall1, z42c_pat_wall1, z42c_pat_wall1 },
  { 0, 0, z43_pat_wall1, z43_pat_wall1 }
};
static unsigned char tbl0[14] = {
  16, 16,
  16, 16,
  32, 16,
  16, 32,
  32, 32,
  64, 16,
  16, 64
};


void wall1(sprite_status* pActwk) {
  if (pActwk->r_no0) {
    act_move(pActwk);
  } else {
    act_init(pActwk);
  }
}





static void act_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 1;
  pActwk->sproffset = 17514;
  pActwk->patbase = pats_wall1[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  pActwk->patno = pActwk->userflag.b.h;
  pActwk->sprhs = pActwk->sprhsize = tbl0[pActwk->userflag.b.h * 2];
  pActwk->sprvsize = tbl0[pActwk->userflag.b.h * 2 + 1];

  act_move(pActwk);
}





static void act_move(sprite_status* pActwk) {
  hitchk(pActwk, &actwk[0]);
  actionsub(pActwk);
  frameout_s(pActwk);
}
