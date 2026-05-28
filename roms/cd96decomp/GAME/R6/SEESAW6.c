#include "../EQU.h"
#include "SEESAW6.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../PLAYSUB.h"
#include "../RIDECHK.h"

static void m_init(sprite_status* pActwk);
static void m_move(sprite_status* pActwk);
static void slave(sprite_status* pActwk);

void(*seesaw6_tbl[3])(sprite_status*) = {
  &m_init,
  &m_move,
  &m_up
};
unsigned char seesaw_pat_00[4] = { 2, 0, 1, 255 };
unsigned char seesaw_pat_01[5] = { 2, 1, 2, 3, 255 };
unsigned char seesaw_pat_02[4] = { 2, 2, 3, 255 };
unsigned char seesaw_pat_03[4] = { 2, 4, 5, 255 };
unsigned char seesaw_pat_04[6] = { 2, 4, 5, 6, 7, 255 };
unsigned char seesaw_pat_05[4] = { 2, 6, 7, 255 };
unsigned char* seesaw_pchg[6] =
{
  seesaw_pat_00,
  seesaw_pat_01,
  seesaw_pat_02,
  seesaw_pat_03,
  seesaw_pat_04,
  seesaw_pat_05
};
sprite_pattern seesawPat00 = { 1, { { -24, -24, 0, 487 } } };
sprite_pattern z6bseesawPat00 = { 1, { { -24, -24, 0, 481 } } };
sprite_pattern z63seesawPat00 = { 1, { { -24, -24, 0, 450 } } };
sprite_pattern seesawPat01 = { 1, { { -24, -24, 0, 488 } } };
sprite_pattern z6bseesawPat01 = { 1, { { -24, -24, 0, 482 } } };
sprite_pattern z63seesawPat01 = { 1, { { -24, -24, 0, 451 } } };
sprite_pattern seesawPat02 = { 1, { { -24, -24, 0, 489 } } };
sprite_pattern z6bseesawPat02 = { 1, { { -24, -24, 0, 483 } } };
sprite_pattern z63seesawPat02 = { 1, { { -24, -24, 0, 452 } } };
sprite_pattern seesawPat03 = { 1, { { -24, -24, 0, 490 } } };
sprite_pattern z6bseesawPat03 = { 1, { { -24, -24, 0, 484 } } };
sprite_pattern z63seesawPat03 = { 1, { { -24, -24, 0, 453 } } };
sprite_pattern seesawPat04 = { 1, { { -24, -24, 0, 491 } } };
sprite_pattern z6bseesawPat04 = { 1, { { -24, -24, 0, 485 } } };
sprite_pattern z63seesawPat04 = { 1, { { -24, -24, 0, 454 } } };
sprite_pattern seesawPat05 = { 1, { { -24, -24, 0, 492 } } };
sprite_pattern z6bseesawPat05 = { 1, { { -24, -24, 0, 486 } } };
sprite_pattern z63seesawPat05 = { 1, { { -24, -24, 0, 455 } } };
sprite_pattern seesawPat06 = { 1, { { -24, -24, 0, 493 } } };
sprite_pattern z6bseesawPat06 = { 1, { { -24, -24, 0, 487 } } };
sprite_pattern z63seesawPat06 = { 1, { { -24, -24, 0, 456 } } };
sprite_pattern seesawPat07 = { 1, { { -24, -24, 0, 494 } } };
sprite_pattern z6bseesawPat07 = { 1, { { -24, -24, 0, 488 } } };
sprite_pattern z63seesawPat07 = { 1, { { -24, -24, 0, 457 } } };
sprite_pattern seesawPat08 = { 1, { { -24, -8, 0, 495 } } };
sprite_pattern z6bseesawPat08 = { 1, { { -24, -8, 0, 489 } } };
sprite_pattern z63seesawPat08 = { 1, { { -24, -8, 0, 458 } } };
sprite_pattern seesawPat09 = { 1, { { -16, -7, 0, 496 } } };
sprite_pattern z6bseesawPat09 = { 1, { { -16, -7, 0, 490 } } };
sprite_pattern z63seesawPat09 = { 1, { { -16, -7, 0, 459 } } };
sprite_pattern* pat_seesaw6[10] =
{
  &seesawPat00,
  &seesawPat01,
  &seesawPat02,
  &seesawPat03,
  &seesawPat04,
  &seesawPat05,
  &seesawPat06,
  &seesawPat07,
  &seesawPat08,
  &seesawPat09
};
sprite_pattern* z6b_pat_seesaw6[10] =
{
  &z6bseesawPat00,
  &z6bseesawPat01,
  &z6bseesawPat02,
  &z6bseesawPat03,
  &z6bseesawPat04,
  &z6bseesawPat05,
  &z6bseesawPat06,
  &z6bseesawPat07,
  &z6bseesawPat08,
  &z6bseesawPat09
};
sprite_pattern* z63_pat_seesaw6[10] =
{
  &z63seesawPat00,
  &z63seesawPat01,
  &z63seesawPat02,
  &z63seesawPat03,
  &z63seesawPat04,
  &z63seesawPat05,
  &z63seesawPat06,
  &z63seesawPat07,
  &z63seesawPat08,
  &z63seesawPat09
};
sprite_pattern** pats_seesaw6[3][3] =
{
  { z6b_pat_seesaw6, pat_seesaw6, pat_seesaw6 },
  { z6b_pat_seesaw6, pat_seesaw6, pat_seesaw6 },
  { 0, 0, z63_pat_seesaw6 }
};


void seesaw6(sprite_status* pActwk) {
  if (pActwk->userflag.b.h != 0)
  {
    slave(pActwk);
  }
  else
  {

    seesaw6_tbl[pActwk->r_no0 / 2](pActwk);
    actionsub(pActwk);
    frameout_s(pActwk);
  }
}











static void m_init(sprite_status* pActwk) {
  sprite_status* pActfree;

  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sprhs = 24;
  pActwk->sprhsize = 24;
  pActwk->sprvsize = 24;
  pActwk->sproffset = 952;
  pActwk->patbase = pats_seesaw6[stageno_i.b.l][time_flag_i & 0x7F];

  if (actwkchk(&pActfree) != 0)
  {
    frameout(pActwk);
    return;
  }
  m_ini_s(pActwk, pActfree);

  ((unsigned short*)pActwk)[23] = pActfree - actwk;
  pActfree->xposi.w.h -= 40;
  pActfree->yposi.w.h -= 24;
  if (actwkchk(&pActfree) != 0)
  {
    frameout(pActwk);
    return;
  }
  m_ini_s(pActwk, pActfree);

  ((unsigned short*)pActwk)[24] = pActfree - actwk;
  pActfree->xposi.w.h += 40;
  pActfree->yposi.w.h += 24;
  pActfree->actflg |= 1;
  pActfree->cddat |= 1;
}











void m_ini_s(sprite_status* pActwk, sprite_status* pActfree) {
  pActfree->actno = pActwk->actno;
  pActfree->actflg = pActwk->actflg;
  pActfree->sprpri = pActwk->sprpri;
  pActfree->sproffset = pActwk->sproffset;
  pActfree->patbase = pActwk->patbase;
  pActfree->xposi.w.h = pActwk->xposi.w.h;
  pActfree->yposi.w.h = pActwk->yposi.w.h;
  pActfree->userflag.b.h = -1;
  pActfree->sprhs = 16;
  pActfree->sprhsize = 16;
  pActfree->sprvsize = 8;
  pActfree->patno = 9;

  ((unsigned short*)pActfree)[23] = pActwk - actwk;
  ((short*)pActwk)[25] = 120;
}











static void m_move(sprite_status* pActwk) {
  unsigned short wActwkNo;

  if (pActwk->yspeed.w == 0)
    m_stay(pActwk);
  else
    m_fall(pActwk);

  wActwkNo = ((unsigned short*)pActwk)[24];
  ridechk(&actwk[wActwkNo], &actwk[0]);
  actionsub(&actwk[wActwkNo]);

  wActwkNo = ((unsigned short*)pActwk)[23];
  if (ridechk(&actwk[wActwkNo], &actwk[0]) != 0)
    actwk[wActwkNo].actfree[21] = 255;
  else
    actwk[wActwkNo].actfree[21] = 0;
  actionsub(&actwk[wActwkNo]);

  if (actwk[wActwkNo].actfree[21] == 0)
  {
    patchg(pActwk, seesaw_pchg);
  }
  else
  {
    pActwk->r_no0 = 4;
    ((short*)pActwk)[25] = 3;
    pActwk->patno = 8;
  }
}















void m_stay(sprite_status* pActwk) {
  short iwk;

  iwk = ((short*)pActwk)[25];
  if (((short*)pActwk)[25] >= 0)
  {

    --((short*)pActwk)[25];
    if (((short*)pActwk)[25] < 0)
    {
      pActwk->yspeed.w = 256;
    }
    else
    {
      if (((short*)pActwk)[25] != 60) return;
    }

    ++pActwk->mstno.b.h;
  }
}











void m_fall(sprite_status* pActwk) {
  sprite_status* pActSu;
  sprite_status* pActSd;
  unsigned short wYspd;
  short iD0, iD1;

  pActSu = &actwk[((unsigned short*)pActwk)[23]];
  pActSd = &actwk[((unsigned short*)pActwk)[24]];

  wYspd = pActwk->yspeed.b.h;
  pActwk->yposi.w.h += wYspd;
  pActSu->yposi.w.h += wYspd;
  pActSd->yposi.w.h += wYspd;


  iD0 = pActSd->sprhsize;
  if (pActSd->xposi.w.h >= pActwk->xposi.w.h)
    iD0 = -iD0;

  iD0 += pActwk->xposi.w.h;
  iD1 = emycol_d2(pActSd, iD0);
  if (iD1 > 0) return;



  pActwk->yposi.w.h += iD1;
  pActSu->yposi.w.h += iD1;
  pActSd->yposi.w.h += iD1;
  pActwk->yspeed.w = 0;
}











void m_up(sprite_status* pActwk) {
  sprite_status *pActSd, *pActSu;
  unsigned short wwk_u, wwk_d;
  pActSd = &actwk[((unsigned short*)pActwk)[24]];
  pActSd->yposi.w.h -= 24;
  pActwk->yposi.w.h -= 12;
  --((short*)pActwk)[25];
  if (((short*)pActwk)[25] < 0)
  {


    pActwk->r_no0 = 2;
    pActwk->yspeed.w = 0;
    ((short*)pActwk)[25] = 120;
    wwk_d = ((unsigned short*)pActwk)[24];
    wwk_u = ((unsigned short*)pActwk)[23];
    ((unsigned short*)pActwk)[24] = wwk_u;
    ((unsigned short*)pActwk)[23] = wwk_d;
    if (pActwk->mstno.b.h > 2) pActwk->mstno.b.h = 0;
    else pActwk->mstno.b.h = 3;
    pActwk->mstno.b.l = -1;
  }

  actionsub(pActSd);
  pActSu = &actwk[((unsigned short*)pActwk)[23]];
  actionsub(pActSu);
}











static void slave(sprite_status* pActwk) {
  sprite_status* pActwk2;

  pActwk2 = &actwk[((unsigned short*)pActwk)[23]];
  if (pActwk2->actno != 44)
    frameout(pActwk);
}
