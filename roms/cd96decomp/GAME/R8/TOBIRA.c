#include "../EQU.h"
#include "TOBIRA.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../PLAYSUB.h"
#include "../RIDECHK.h"

static void slave(sprite_status* actionwk, short ano);

static char pchg00[4] = { 2, 0, 1, -1 };
static char* pchg[1] = { pchg00 };
static sprite_pattern z81pat00 = { 1, { { -8, -16, 0, 464 } } };
static sprite_pattern z82pat00 = { 1, { { -8, -16, 0, 432 } } };
static sprite_pattern z83pat00 = { 1, { { -8, -16, 0, 500 } } };
static sprite_pattern z81pat01 = { 1, { { -8, -16, 0, 465 } } };
static sprite_pattern z82pat01 = { 1, { { -8, -16, 0, 433 } } };
static sprite_pattern z83pat01 = { 1, { { -8, -16, 0, 501 } } };
static sprite_pattern z81pat02 = { 1, { { -8, -16, 0, 466 } } };
static sprite_pattern z82pat02 = { 1, { { -8, -16, 0, 434 } } };
static sprite_pattern z83pat02 = { 1, { { -8, -16, 0, 502 } } };
static sprite_pattern z81pat03 = { 1, { { -16, -16, 0, 467 } } };
static sprite_pattern z82pat03 = { 1, { { -16, -16, 0, 435 } } };
static sprite_pattern z83pat03 = { 1, { { -16, -16, 0, 503 } } };
static sprite_pattern z81pat04 = { 1, { { -16, -16, 0, 468 } } };
static sprite_pattern z82pat04 = { 1, { { -16, -16, 0, 436 } } };
static sprite_pattern z83pat04 = { 1, { { -16, -16, 0, 504 } } };
sprite_pattern* z81_pat_tobira0[2] =
{
  &z81pat00,
  &z81pat00
};
sprite_pattern* z82_pat_tobira0[2] =
{
  &z82pat00,
  &z82pat00
};
sprite_pattern* z83_pat_tobira0[2] =
{
  &z83pat00,
  &z83pat00
};
sprite_pattern** pats_tobira0[3] =
{
  z81_pat_tobira0,
  z82_pat_tobira0,
  z83_pat_tobira0
};
sprite_pattern* z81_pat_tobira1[2] =
{
  &z81pat01,
  &z81pat02
};
sprite_pattern* z82_pat_tobira1[2] =
{
  &z82pat01,
  &z82pat02
};
sprite_pattern* z83_pat_tobira1[2] =
{
  &z83pat01,
  &z83pat02
};
sprite_pattern** pats_tobira1[3] =
{
  z81_pat_tobira1,
  z82_pat_tobira1,
  z83_pat_tobira1
};
sprite_pattern* z81_pat_tobira2[2] =
{
  &z81pat03,
  &z81pat04
};
sprite_pattern* z82_pat_tobira2[2] =
{
  &z82pat03,
  &z82pat04
};
sprite_pattern* z83_pat_tobira2[2] =
{
  &z83pat03,
  &z83pat04
};
sprite_pattern** pats_tobira2[3] =
{
  z81_pat_tobira2,
  z82_pat_tobira2,
  z83_pat_tobira2
};


void tobira(sprite_status* actionwk) {
  short a;
  a = ((short*)actionwk)[23];
  if (a != 0)
  {
    slave(actionwk, ((short*)actionwk)[23]);
    return;
  }
  master(actionwk);
}

void master(sprite_status* actionwk) {
  switch (actionwk->r_no0)
  {
    case 0:
      m_init(actionwk);
      break;
    case 2:
      m_closed(actionwk);
      break;
    case 4:
      m_open(actionwk);
      break;
    case 6:
      m_opend(actionwk);
      break;
    case 8:
      m_close(actionwk);
      break;
  }
}

void m_init(sprite_status* actionwk) {
  short d0, d1;
  sprite_status* a1;

  actionwk->r_no0 += 2;
  ((short*)actionwk)[25] = actionwk->yposi.w.h - 16;


  if (actionwk->userflag.b.h == 0) actionwk->patbase = pats_tobira0[stageno_i.b.l];
  if (actionwk->userflag.b.h == 1) actionwk->patbase = pats_tobira1[stageno_i.b.l];
  if (actionwk->userflag.b.h == 2) actionwk->patbase = pats_tobira2[stageno_i.b.l];
  if (actwkchk2(actionwk, &a1) != 0)
  {
    frameout(actionwk);
    return;
  }
  a1->actno = actionwk->actno;
  a1->xposi.w.h = actionwk->xposi.w.h;
  a1->patbase = actionwk->patbase;
  ((unsigned short*)a1)[23] = actionwk - actwk;
  ((unsigned short*)actionwk)[24] = a1 - actwk;
  d0 = d1 = 0;
  ini_com(actionwk, a1, &d0, &d1);
  a1->yposi.w.h -= d0;
  ((short*)a1)[26] -= d0;
  ((short*)a1)[27] -= d1;
  a1 = actionwk;
  ini_com(actionwk, a1, &d0, &d1);
  a1->yposi.w.h += d0;
  ((short*)a1)[26] += d0;
  ((short*)a1)[27] += d1;
}

void ini_com(sprite_status* actionwk, sprite_status* a1, short* d0, short* d1) {
  a1->actflg |= 4;
  a1->sprpri = 3;
  a1->sproffset = 1150;
  a1->sprhsize = 8;
  a1->sprvsize = 16;
  a1->yposi.w.h = ((short*)actionwk)[25];
  ((short*)a1)[26] = ((short*)actionwk)[25];
  ((short*)a1)[27] = ((short*)actionwk)[25];
  *d0 = 16;
  *d1 = 49;
}

void m_closed(sprite_status* actionwk) {
  short d0, d4, d5;

  ms_hitchk(actionwk);
  if (actionwk->actfree[21] != 0)
  {
    actionwk->actfree[21] = 0;
  }
  else
  {
    d0 = actionwk->userflag.b.h;
    if (d0 == 0) goto label1;
    d4 = 8;
    d5 = 64;
    if (d0 != 1)
    {
      d4 = -72;
      d5 = 64;
    }
    if (m_area(actionwk, d4, d5) == 0) goto label1;
  }

  actionwk->r_no0 += 2;
label1:
  ms_end(actionwk);
}

void ms_end(sprite_status* actionwk) {
  short ano;

  patchg(actionwk, (unsigned char**)pchg);
  ano = ((unsigned short*)actionwk)[24];
  actwk[ano].patno = actionwk->patno;

  actionsub(&actwk[ano]);
  actionsub(actionwk);
  frameout_s(actionwk);
}

void m_open(sprite_status* actionwk) {
  short ano;

  ms_hitchk(actionwk);

  ano = ((unsigned short*)actionwk)[24];
  actionwk->yposi.w.h += 2;
  actwk[ano].yposi.w.h -= 2;
  if (((short*)actionwk)[27] <= actionwk->yposi.w.h)
  {
    actionwk->r_no0 += 2;
    actionwk->yposi.w.h = ((short*)actionwk)[27];
    actwk[ano].yposi.w.h = ((short*)&actwk[ano])[27];
  }

  ms_end(actionwk);
}

void m_opend(sprite_status* actionwk) {
  short d0, d4, d5;

  ms_hitchk(actionwk);

  d0 = actionwk->userflag.b.h;
  if (d0 != 0)
  {
    d4 = -40;
    d5 = 112;
    if (d0 != 1)
    {
      d4 = -72;
      d5 = 112;
    }
    if (m_area(actionwk, d4, d5) == 0) actionwk->r_no0 += 2;
  }

  ms_end(actionwk);
}

void m_close(sprite_status* actionwk) {
  short ano;

  ms_hitchk(actionwk);

  ano = ((unsigned short*)actionwk)[24];
  actionwk->yposi.w.h -= 2;
  actwk[ano].yposi.w.h += 2;

  if (((short*)actionwk)[26] >= actionwk->yposi.w.h)
  {
    actionwk->r_no0 = 2;
    actionwk->yposi.w.h = ((short*)actionwk)[26];
    actwk[ano].yposi.w.h = ((short*)&actwk[ano])[26];
  }
  ms_end(actionwk);
}

short ms_hitchk(sprite_status* actionwk) {
  short ano;

  ano = ((unsigned short*)actionwk)[24];
  hitchk(&actwk[ano], &actwk[0]);
  hitchk(actionwk, &actwk[0]);
}


short m_area(sprite_status* actionwk, short d4, short d5) {
  short d0;

  d0 = actwk[0].xposi.w.h - actionwk->xposi.w.h - d4;
  if ((unsigned short)d5 <= (unsigned short)d0) return 0;
  d0 = actwk[0].yposi.w.h - ((short*)actionwk)[25] + 48;

  if ((unsigned short)d0 >= 96) return 0;
  return 1;
}

static void slave(sprite_status* actionwk, short ano) {
  if (actwk[ano].actno != 41)
  {
    frameout(actionwk);
  }
}
