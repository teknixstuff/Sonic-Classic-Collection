#include "../TYPES.h"

static sprite_pattern pata00 = {
  1,
  { { -40, -48, 0, 481 } }
};
sprite_pattern* patbase_kuzure_a[1] = { &pata00 };
static unsigned char tbla00[22] = {
  4, 3, 255, 255, 0, 0, 0, 1, 2, 3,
  3, 4, 0, 5, 5, 5, 5, 6, 6, 6,
  6, 6
};
unsigned char* tbl_kuzure_a[1] = { tbla00 };
static sprite_pattern patc00 = {
  1,
  { { -8, -8, 0, 482 } }
};
static sprite_pattern patc01 = {
  1,
  { { -8, -8, 0, 483 } }
};
static sprite_pattern patc02 = {
  1,
  { { -8, -8, 0, 484 } }
};
static sprite_pattern patc03 = {
  1,
  { { -8, -8, 0, 485 } }
};
static sprite_pattern patc04 = {
  1,
  { { -8, -8, 0, 486 } }
};
static sprite_pattern patc05 = {
  1,
  { { -8, -8, 0, 487 } }
};
static sprite_pattern patc06 = {
  1,
  { { -8, -24, 0, 488 } }
};
sprite_pattern* patbase_kuzure_c[7] = {
  &patc00,
  &patc01,
  &patc02,
  &patc03,
  &patc04,
  &patc05,
  &patc06
};
static sprite_pattern patb00 = {
  1,
  { { -48, -32, 0, 489 } }
};
static sprite_pattern patb01 = {
  1,
  { { -32, -48, 0, 490 } }
};
sprite_pattern* patbase_kuzure_b[2] = {
  &patb00,
  &patb00
};
static unsigned char tblb00[8] = { 5, 1, 0, 0, 0, 0, 0, 0 };
unsigned char* tbl_kuzure_b[2] = {
  tblb00,
  tblb00
};
static sprite_pattern patd00 = {
  1,
  { { -8, -32, 0, 491 } }
};
sprite_pattern* patbase_kuzure_d[1] = { &patd00 };
