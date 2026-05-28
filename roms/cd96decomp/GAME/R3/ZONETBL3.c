#include "../TYPES.h"

unsigned short z3_title_tbl[32] = {
   304,  552,  360,  346,
   256,  568,  376,  602,
   256,  576,  384,  602,
   256,  584,  392,  602,
   288,  560,  368,  858,
   320,  584,  392, 1114,
   256,  464,  272, 1882,
   256,  464,  272, 2138
};
static sprite_pattern z3titlepat0 = { 1, { { -16, -112, 0, 360 } } };
static sprite_pattern z33titlepat0 = { 1, { { -16, -112, 0, 364 } } };
static sprite_pattern z3titlepat1 = { 1, { { -24, -8, 0, 361 } } };
static sprite_pattern z33titlepat1 = { 1, { { -24, -8, 0, 365 } } };
static sprite_pattern z3titlepat2 = { 1, { { -4, -24, 0, 362 } } };
static sprite_pattern z33titlepat2 = { 1, { { -4, -24, 0, 366 } } };
static sprite_pattern z3titlepat3 = { 1, { { -80, -8, 0, 363 } } };
static sprite_pattern z33titlepat3 = { 1, { { -80, -8, 0, 367 } } };
static sprite_pattern z3titlepat4 = { 1, { { -24, -24, 0, 364 } } };
static sprite_pattern z33titlepat4 = { 1, { { -24, -24, 0, 368 } } };
static sprite_pattern z3titlepat5 = { 1, { { -24, -24, 0, 365 } } };
static sprite_pattern z33titlepat5 = { 1, { { -24, -24, 0, 369 } } };
static sprite_pattern z3titlepat6 = { 1, { { -24, -24, 0, 366 } } };
static sprite_pattern z33titlepat6 = { 1, { { -24, -24, 0, 370 } } };
static sprite_pattern z3titlepat7 = { 1, { { 0, -56, 0, 367 } } };
static sprite_pattern z33titlepat7 = { 1, { { 0, -56, 0, 371 } } };
static sprite_pattern z3titlepat8 = { 1, { { 0, 0, 0, 368 } } };
static sprite_pattern z33titlepat8 = { 1, { { 0, 0, 0, 372 } } };
sprite_pattern* z3_title_pat[9] = {
  &z3titlepat0,
  &z3titlepat1,
  &z3titlepat2,
  &z3titlepat3,
  &z3titlepat4,
  &z3titlepat5,
  &z3titlepat6,
  &z3titlepat7,
  &z3titlepat8
};
sprite_pattern* z33_title_pat[9] = {
  &z33titlepat0,
  &z33titlepat1,
  &z33titlepat2,
  &z33titlepat3,
  &z33titlepat4,
  &z33titlepat5,
  &z33titlepat6,
  &z33titlepat7,
  &z33titlepat8
};
