#include "../EQU.h"
#include "MOVIE3.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../RIDECHK.h"
#include "../SCR.h"

static void die(sprite_status* moviewk);
static void m_init(sprite_status* moviewk);
static void m_wait(sprite_status* moviewk);
static void m_die(sprite_status* moviewk);
static void m_baku(sprite_status* moviewk);
static void m1wait(sprite_status* moviewk);
static void sub(sprite_status* moviewk);
static void s_init(sprite_status* moviewk);
static void s_move(sprite_status* moviewk);

static unsigned char pchg00[6] = { 0, 2, 1, 3, 1, 255 };
static unsigned char pchg01[58] = { 0, 4, 4, 1, 4, 4, 1, 4, 4, 1, 4, 4, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 4, 4, 1, 1, 5, 5, 1, 5, 5, 1, 5, 5, 1, 5, 5, 1, 5, 5, 1, 1, 5, 5, 1, 1, 5, 5, 1, 1, 5, 5, 1, 1, 255 };
static unsigned char* pchg[2] = {
  pchg00,
  pchg01
};
static sprite_pattern mov00 = { 1, { { -12, -12, 0, 316 } } };
static sprite_pattern z33mov00 = { 1, { { -12, -12, 0, 320 } } };
static sprite_pattern pat00 = { 1, { { -16, -20, 0, 0 } } };
static sprite_pattern mov01 = { 1, { { -8, -4, 0, 317 } } };
static sprite_pattern z33mov01 = { 1, { { -8, -4, 0, 321 } } };
static sprite_pattern mov02 = { 1, { { -8, -4, 0, 318 } } };
static sprite_pattern z33mov02 = { 1, { { -8, -4, 0, 322 } } };
static sprite_pattern mov03 = { 1, { { -20, -24, 0, 319 } } };
static sprite_pattern z33mov03 = { 1, { { -20, -24, 0, 323 } } };
static sprite_pattern mov04 = { 1, { { -20, -24, 0, 320 } } };
static sprite_pattern z33mov04 = { 1, { { -20, -24, 0, 324 } } };
sprite_pattern* pat_movie3[6] = {
  &mov00,
  &pat00,
  &mov01,
  &mov02,
  &mov03,
  &mov04
};
sprite_pattern* z33_pat_movie3[6] = {
  &z33mov00,
  &pat00,
  &z33mov01,
  &z33mov02,
  &z33mov03,
  &z33mov04
};
sprite_pattern** pats_movie3[3][3] = {
  { pat_movie3, pat_movie3, pat_movie3 },
  { pat_movie3, pat_movie3, pat_movie3 },
  { 0, 0, z33_pat_movie3 }
};
static char tbl0[37] = {
    1,   0,   0,
    5, -18, -10,
   10, -10,  10,
   15,   0, -18,
   20, -10,  18,
   22,   8,  23,
   25,  13, -10,
   28,  -3, -25,
   30,  10,  20,
   32, -10,   2,
   35,  13, -10,
   40, -10,  10,
   -1
};


void movie3(sprite_status* moviewk) {
  void(*act_tbl[5])(sprite_status*) = { &m_init, &m_wait, &m_die, &m_baku, &m1wait };

  if (moviewk->userflag.b.h != 0) { sub(moviewk); return; }

  act_tbl[moviewk->r_no0 / 2](moviewk);
  actionsub(moviewk);
  if (moviewk->r_no0 > 2) return;
  frameout_s(moviewk);
  if (moviewk->actno == 0) divdevset(4);
}



static void die(sprite_status* moviewk) {
  frameout(moviewk);
}


static void m_init(sprite_status* moviewk) {
  sprite_status* new_actwk;

  if (projector_flag != 0) { die(moviewk); return; }
  divdevset(5);

  moviewk->r_no0 += 2;
  moviewk->actflg |= 4;
  moviewk->sprpri = 4;
  moviewk->sprhs = moviewk->sprhsize = moviewk->sprvsize = 12;
  moviewk->colino = 251;

  moviewk->patbase = pats_movie3[stageno_i.b.l][time_flag_i & 0x7F];
  ((char**)moviewk)[12] = tbl0;

  if (actwkchk(&new_actwk) != 0) { die(moviewk); return; }
  new_actwk->actno = moviewk->actno;
  new_actwk->xposi.w.h = moviewk->xposi.w.h - 21;
  new_actwk->yposi.w.h = moviewk->yposi.w.h - 7;
  new_actwk->userflag.b.h = -1;
  ((unsigned short*)new_actwk)[33] = moviewk - actwk;

  if (actwkchk(&new_actwk) != 0) { die(moviewk); return; }
  new_actwk->actno = moviewk->actno;
  new_actwk->xposi.w.h = moviewk->xposi.w.h - 88;
  new_actwk->yposi.w.h = moviewk->yposi.w.h - 4;
  new_actwk->userflag.b.h = 1;
  ((unsigned short*)new_actwk)[33] = moviewk - actwk;

  if (actwkchk(&new_actwk) != 0) { die(moviewk); return; }
  new_actwk->actno = 57;
  new_actwk->xposi.w.h = moviewk->xposi.w.h - 88;
  new_actwk->yposi.w.h = moviewk->yposi.w.h - 24;
  new_actwk->userflag.b.h = -128;
  ((unsigned short*)new_actwk)[33] = moviewk- actwk;

  if (actwkchk(&new_actwk) != 0) { die(moviewk); return; }
  new_actwk->actno = 57;
  new_actwk->xposi.w.h = moviewk->xposi.w.h - 98;
  new_actwk->yposi.w.h = (int)moviewk->yposi.w.h;
  new_actwk->userflag.b.h = -127;
  ((unsigned short*)new_actwk)[33] = moviewk - actwk;
}



static void m_wait(sprite_status* moviewk) {
  if (moviewk->colicnt != 0) {
    moviewk->colino = moviewk->colicnt = 0;
    moviewk->r_no0 += 2;
  }
  hitchk(moviewk, &actwk[0]);
}



static void m_die(sprite_status* moviewk) {
  moviewk->r_no0 += 2;
  moviewk->patno = 1;
  moviewk->actfree[21] = 255;
  divdevset(4);

  if (hitchk(moviewk, &actwk[0]) != 0) ride_on_clr(moviewk, &actwk[0]);
  m_baku(moviewk);
}



static void m_baku(sprite_status* moviewk) {
  char *data_tbl, time_limit, x_add, y_add;
  sprite_status* new_actwk;

  data_tbl = ((char**)moviewk)[12];
  if ((time_limit = data_tbl[0]) < 0) {
    moviewk->r_no0 += 2;
    ((short*)moviewk)[23] = 60;
    return;
  }

  if (++moviewk->actfree[0] != time_limit) return;

  x_add = data_tbl[1], y_add = data_tbl[2];
  ((char**)moviewk)[12] = data_tbl + 3;

  if (actwkchk(&new_actwk) != 0) return;
  new_actwk->actno = 24;
  new_actwk->r_no1 = 1;
  new_actwk->xposi.w.h = moviewk->xposi.w.h + (short)x_add;
  new_actwk->yposi.w.h = moviewk->yposi.w.h + (short)y_add;
  soundset(158);
}



static void m1wait(sprite_status* moviewk) {
  if (--((short*)moviewk)[23] == 0) {
    projector_flag = 255;
    die(moviewk);
  }
}



static void sub(sprite_status* moviewk) {
  sprite_status* parent;

  parent = &actwk[((unsigned short*)moviewk)[33]];
  if (parent->actno != 56) { die(moviewk); return; }
  if (parent->actfree[21] != 0) { die(moviewk); return; }

  if (moviewk->r_no0 == 0) { s_init(moviewk); return; }
  s_move(moviewk);
}



static void s_init(sprite_status* moviewk) {
  moviewk->r_no0 += 2;
  moviewk->actflg |= 4;
  moviewk->sprpri = 4;

  moviewk->patbase = pats_movie3[stageno_i.b.l][time_flag_i & 0x7F];
  if (moviewk->userflag.b.h < 0) {
    moviewk->sprhs = moviewk->sprhsize = 8;
    moviewk->sprvsize = 4;
    moviewk->mstno.b.h = 0;
  } else {
    moviewk->sprhs = moviewk->sprhsize = 20;
    moviewk->sprvsize = 24;
    moviewk->mstno.b.h = 1;
  }
}



static void s_move(sprite_status* moviewk) {
  patchg(moviewk, pchg);
  actionsub(moviewk);
}
