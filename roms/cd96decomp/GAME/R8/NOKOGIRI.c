#include "../EQU.h"
#include "NOKOGIRI.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"

static void act_init(sprite_status* actionwk);
static void act_open(sprite_status* actionwk);
static void act_close(sprite_status* actionwk);

static char p00[4] = { 1, 0, 1, -1 };
static char p01[4] = { 1, 2, 3, -1 };
static char p02[4] = { 1, 4, 5, -1 };
static char p03[4] = { 1, 6, 7, -1 };
static char p04[4] = { 1, 8, 9, -1 };
static char p05[4] = { 1, 10, 11, -1 };
static char p06[4] = { 1, 12, 13, -1 };
static char p07[4] = { 1, 14, 15, -1 };
static char p08[4] = { 1, 16, 17, -1 };
static char* pchg[10] =
{
  p00,
  p01,
  p02,
  p03,
  p04,
  p05,
  p06,
  p07,
  p08,
  p08
};
static sprite_pattern z81pat00 = { 1, { { -32, -34, 0, 425 } } };
static sprite_pattern z83pat00 = { 1, { { -32, -34, 0, 404 } } };
static sprite_pattern z81pat01 = { 1, { { -32, -34, 0, 426 } } };
static sprite_pattern z83pat01 = { 1, { { -32, -34, 0, 405 } } };
static sprite_pattern z81pat02 = { 1, { { -43, -43, 0, 427 } } };
static sprite_pattern z83pat02 = { 1, { { -43, -43, 0, 406 } } };
static sprite_pattern z81pat03 = { 1, { { -43, -43, 0, 428 } } };
static sprite_pattern z83pat03 = { 1, { { -43, -43, 0, 407 } } };
static sprite_pattern z81pat04 = { 1, { { -52, -54, 0, 429 } } };
static sprite_pattern z83pat04 = { 1, { { -52, -54, 0, 408 } } };
static sprite_pattern z81pat05 = { 1, { { -52, -54, 0, 430 } } };
static sprite_pattern z83pat05 = { 1, { { -52, -54, 0, 409 } } };
static sprite_pattern z81pat06 = { 1, { { -63, -63, 0, 431 } } };
static sprite_pattern z83pat06 = { 1, { { -63, -63, 0, 410 } } };
static sprite_pattern z81pat07 = { 1, { { -63, -63, 0, 432 } } };
static sprite_pattern z83pat07 = { 1, { { -63, -63, 0, 411 } } };
static sprite_pattern z81pat08 = { 1, { { -72, -74, 0, 433 } } };
static sprite_pattern z83pat08 = { 1, { { -72, -74, 0, 412 } } };
static sprite_pattern z81pat09 = { 1, { { -72, -74, 0, 434 } } };
static sprite_pattern z83pat09 = { 1, { { -72, -74, 0, 413 } } };
static sprite_pattern z81pat10 = { 1, { { -83, -83, 0, 435 } } };
static sprite_pattern z83pat10 = { 1, { { -83, -83, 0, 414 } } };
static sprite_pattern z81pat11 = { 1, { { -83, -83, 0, 436 } } };
static sprite_pattern z83pat11 = { 1, { { -83, -83, 0, 415 } } };
static sprite_pattern z81pat12 = { 1, { { -92, -94, 0, 437 } } };
static sprite_pattern z83pat12 = { 1, { { -92, -94, 0, 416 } } };
static sprite_pattern z81pat13 = { 1, { { -92, -94, 0, 438 } } };
static sprite_pattern z83pat13 = { 1, { { -92, -94, 0, 417 } } };
static sprite_pattern z81pat14 = { 1, { { -103, -103, 0, 439 } } };
static sprite_pattern z83pat14 = { 1, { { -103, -103, 0, 418 } } };
static sprite_pattern z81pat15 = { 1, { { -103, -103, 0, 440 } } };
static sprite_pattern z83pat15 = { 1, { { -103, -103, 0, 419 } } };
static sprite_pattern z81pat16 = { 1, { { -112, -114, 0, 441 } } };
static sprite_pattern z83pat16 = { 1, { { -112, -114, 0, 420 } } };
static sprite_pattern z81pat17 = { 1, { { -112, -114, 0, 442 } } };
static sprite_pattern z83pat17 = { 1, { { -112, -114, 0, 421 } } };
sprite_pattern* z81_pat_nokogiri[20] =
{
  &z81pat00,
  &z81pat01,
  &z81pat02,
  &z81pat03,
  &z81pat04,
  &z81pat05,
  &z81pat06,
  &z81pat07,
  &z81pat08,
  &z81pat09,
  &z81pat10,
  &z81pat11,
  &z81pat12,
  &z81pat13,
  &z81pat14,
  &z81pat15,
  &z81pat16,
  &z81pat17
};
sprite_pattern* z83_pat_nokogiri[20] =
{
  &z83pat00,
  &z83pat01,
  &z83pat02,
  &z83pat03,
  &z83pat04,
  &z83pat05,
  &z83pat06,
  &z83pat07,
  &z83pat08,
  &z83pat09,
  &z83pat10,
  &z83pat11,
  &z83pat12,
  &z83pat13,
  &z83pat14,
  &z83pat15,
  &z83pat16,
  &z83pat17
};
sprite_pattern** pats_nokogiri[3] =
{
  z81_pat_nokogiri,
  0,
  z83_pat_nokogiri
};
static sprite_pattern z81_pat_bar0 = { 1, { { -41, -43, 0, 443 } } };
static sprite_pattern z83_pat_bar0 = { 1, { { -41, -43, 0, 422 } } };
sprite_pattern* z81_pat_bar[1] = { &z81_pat_bar0 };
sprite_pattern* z83_pat_bar[1] = { &z83_pat_bar0 };
sprite_pattern** pats_bar[3] =
{
  z81_pat_bar,
  0,
  z83_pat_bar
};


void nokogiri(sprite_status* actionwk) {
  if (actionwk->userflag.b.l != 0)
  {
    bar(actionwk);
    return;
  }
  switch (actionwk->r_no0)
  {
    case 0:
      act_init(actionwk);
    case 2:
      act_open(actionwk);
      break;
    case 4:
      act_opend(actionwk);
      break;
    case 6:
      act_close(actionwk);
      break;
    case 8:
      act_closed(actionwk);
      break;
  }
  patchg(actionwk, (unsigned char**)pchg);
  actionsub(actionwk);
  frameout_s00(actionwk, ((short*)actionwk)[29]);
}

static void act_init(sprite_status* actionwk) {
  sprite_status* a1;
  short d0, d1;

  ((short*)actionwk)[29] = actionwk->xposi.w.h;
  actionwk->actflg |= 4;
  actionwk->sprpri = 3;
  actionwk->sproffset = 17174;
  actionwk->patbase = pats_nokogiri[stageno_i.b.l];
  actionwk->colino = 169;
  actionwk->sprhsize = 80;
  actionwk->sprvsize = 80;

  ((int*)actionwk)[12] = 65536;
  ((int*)actionwk)[13] = 65536;

  if (actionwk->userflag.b.h & 1)
  {
    ((int*)actionwk)[12] = -((int*)actionwk)[12];

    actionwk->actflg |= 1;
    actionwk->cddat |= 1;
  }


  if (actionwk->userflag.b.h & 2)
  {
    ((int*)actionwk)[13] = -((int*)actionwk)[13];

    actionwk->actflg |= 2;
    actionwk->cddat |= 2;
  }

  ((short*)actionwk)[23] = 60;
  actionwk->r_no0 = 8;
  if (actionwk->userflag.b.h < 0)
  {
    actionwk->mstno.b.h = 9;
    actionwk->r_no0 = 4;
  }

  if (actwkchk2(actionwk, &a1) != 0)
  {
    frameout(actionwk);
    return;
  }
  ((unsigned short*)actionwk)[31] = a1 - actwk;
  ((unsigned short*)a1)[23] = actionwk - actwk;
  a1->actno = actionwk->actno;
  a1->actflg = actionwk->actflg;
  a1->sproffset = actionwk->sproffset;
  a1->userflag.b.h = actionwk->userflag.b.h;
  a1->userflag.b.l = -1;
  a1->sprpri = actionwk->sprpri - 1;
  a1->xposi.w.h = actionwk->xposi.w.h;
  a1->yposi.w.h = actionwk->yposi.w.h + 1;
  if (actionwk->userflag.b.h & 128)
  {
    d0 = 80;
    d1 = 79;
    if (actionwk->userflag.b.h & 1) d0 = -(d0 - 1);
    if (actionwk->userflag.b.h & 2) d1 = -(d1 - 1);
    a1->xposi.w.h -= d0;
    a1->yposi.w.h -= d1;
  }
  else
  {
    if (actionwk->userflag.b.h & 1)
    {
      --a1->yposi.w.h;
      ++a1->xposi.w.h;
    }
    if (actionwk->userflag.b.h & 2)
    {
      --a1->yposi.w.h;
      --a1->xposi.w.h;
    }
  }
}

static void act_open(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] == 0)
  {
    ++actionwk->mstno.b.h;
    ((short*)actionwk)[23] = 9;
    if (--((short*)actionwk)[28] == 0)
    {
      actionwk->r_no0 += 2;
      ((short*)actionwk)[23] = 60;
    }
  }

  actionwk->xposi.l += ((int*)actionwk)[12];
  actionwk->yposi.l += ((int*)actionwk)[13];
  _soundset(actionwk);
}

void act_opend(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] == 0)
  {
    actionwk->r_no0 += 2;
    ((short*)actionwk)[28] = 9;
    ((short*)actionwk)[23] = 1;
  }
  _soundset(actionwk);
}

static void act_close(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] == 0)
  {
    --actionwk->mstno.b.h;
    ((short*)actionwk)[23] = 9;
    if (--((short*)actionwk)[28] == 0)
    {
      actionwk->r_no0 += 2;
      ((short*)actionwk)[23] = 60;
    }
  }

  actionwk->xposi.l -= ((int*)actionwk)[12];
  actionwk->yposi.l -= ((int*)actionwk)[13];
  _soundset(actionwk);
}

void act_closed(sprite_status* actionwk) {
  if (--((short*)actionwk)[23] == 0)
  {
    actionwk->r_no0 -= 6;
    ((short*)actionwk)[28] = 9;
    ((short*)actionwk)[23] = 1;
  }
  _soundset(actionwk);
}

void _soundset(sprite_status* actionwk) {
  short d0;

  if ((char)actionwk->actflg >= 0) return;
  ++((short*)actionwk)[30];
  d0 = ((short*)actionwk)[30];
  d0 &= 31;
  if (d0 != 0) return;
  soundset(177);
}

void bar(sprite_status* actionwk) {
  short ano;

  ano = ((short*)actionwk)[23];
  if (actwk[ano].actno != 39)
  {
    frameout(actionwk);
    return;
  }
  if (actionwk->r_no0)
  {
    actionsub(actionwk);
    return;
  }

  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->patbase = pats_bar[stageno_i.b.l];
  actionwk->sprhsize = 32;
  actionwk->sprvsize = 32;
}
