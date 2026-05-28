#include "../EQU.h"
#include "KAMA.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../FCOL.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static unsigned char bCarry;
static unsigned char jmp_flg;
void(*kama_tbl[7])(sprite_status*) = { &kama_init, &kama_fall, &kama_wait, &kama_atck, &kama_pati, &kama_move, &kama_reve };
void(*wpkama_tbl[3])(sprite_status*) = { &wpkama_init, &wpkama_wait, &wpkama_move };
unsigned char kama_pchg0[6] = { 7, 0, 1, 2, 3, 255 };
unsigned char kama_pchg1[4] = { 7, 5, 6, 255 };
unsigned char kama_pchg2[4] = { 7, 0, 4, 255 };
unsigned char kama_pchg3[4] = { 7, 7, 4, 255 };
unsigned char kama_pchg4[3] = { 7, 0, 255 };
unsigned char* kama_pchg[5] = { kama_pchg0, kama_pchg1, kama_pchg2, kama_pchg3, kama_pchg4 };
sprite_pattern kama_patA = { 3, { { -18, -20, 0, 424 }, { -12, -4, 0, 425 }, { -2, 4, 0, 426 } } };
sprite_pattern z31a_kama_patA = { 3, { { -18, -20, 0, 471 }, { -12, -4, 0, 472 }, { -2, 4, 0, 473 } } };
sprite_pattern z33_kama_patA = { 3, { { -18, -20, 0, 475 }, { -12, -4, 0, 476 }, { -2, 4, 0, 477 } } };
sprite_pattern kama_patB = { 3, { { -18, -19, 0, 427 }, { -12, -3, 0, 428 }, { -2, 4, 0, 429 } } };
sprite_pattern z31a_kama_patB = { 3, { { -18, -19, 0, 474 }, { -12, -3, 0, 475 }, { -2, 4, 0, 476 } } };
sprite_pattern z33_kama_patB = { 3, { { -18, -19, 0, 478 }, { -12, -3, 0, 479 }, { -2, 4, 0, 480 } } };
sprite_pattern kama_patC = { 3, { { -18, -20, 0, 430 }, { -12, -4, 0, 431 }, { -2, 4, 0, 432 } } };
sprite_pattern z31a_kama_patC = { 3, { { -18, -20, 0, 477 }, { -12, -4, 0, 478 }, { -2, 4, 0, 479 } } };
sprite_pattern z33_kama_patC = { 3, { { -18, -20, 0, 481 }, { -12, -4, 0, 482 }, { -2, 4, 0, 483 } } };
sprite_pattern kama_patD = { 3, { { -18, -19, 0, 433 }, { -12, -3, 0, 434 }, { -2, 4, 0, 435 } } };
sprite_pattern z31a_kama_patD = { 3, { { -18, -19, 0, 480 }, { -12, -3, 0, 481 }, { -2, 4, 0, 482 } } };
sprite_pattern z33_kama_patD = { 3, { { -18, -19, 0, 484 }, { -12, -3, 0, 485 }, { -2, 4, 0, 486 } } };
sprite_pattern kama_patE = { 3, { { -18, -19, 0, 436 }, { -12, -3, 0, 437 }, { -2, 4, 0, 438 } } };
sprite_pattern z31a_kama_patE = { 3, { { -18, -19, 0, 483 }, { -12, -3, 0, 484 }, { -2, 4, 0, 485 } } };
sprite_pattern z33_kama_patE = { 3, { { -18, -19, 0, 487 }, { -12, -3, 0, 488 }, { -2, 4, 0, 489 } } };
sprite_pattern kama_patF = { 4, { { -18, -19, 0, 439 }, { -24, -12, 0, 440 }, { -12, -4, 0, 441 }, { -2, 4, 0, 442 } } };
sprite_pattern z31a_kama_patF = { 4, { { -18, -19, 0, 486 }, { -24, -12, 0, 487 }, { -12, -4, 0, 488 }, { -2, 4, 0, 489 } } };
sprite_pattern z33_kama_patF = { 4, { { -18, -19, 0, 490 }, { -24, -12, 0, 491 }, { -12, -4, 0, 492 }, { -2, 4, 0, 493 } } };
sprite_pattern kama_patG = { 3, { { -18, -19, 0, 443 }, { -24, -11, 0, 444 }, { -12, -3, 0, 445 }, { -2, 4, 0, 446 } } };
sprite_pattern z31a_kama_patG = { 3, { { -18, -19, 0, 490 }, { -24, -11, 0, 491 }, { -12, -3, 0, 492 }, { -2, 4, 0, 493 } } };
sprite_pattern z33_kama_patG = { 3, { { -18, -19, 0, 494 }, { -24, -11, 0, 495 }, { -12, -3, 0, 496 }, { -2, 4, 0, 497 } } };
sprite_pattern kama_patH = { 3, { { -18, -20, 0, 447 }, { -12, -4, 0, 448 }, { -2, 4, 0, 449 } } };
sprite_pattern z31a_kama_patH = { 3, { { -18, -20, 0, 494 }, { -12, -4, 0, 495 }, { -2, 4, 0, 496 } } };
sprite_pattern z33_kama_patH = { 3, { { -18, -20, 0, 498 }, { -12, -4, 0, 499 }, { -2, 4, 0, 500 } } };
sprite_pattern* kamapat[8] =
{
  &kama_patA,
  &kama_patB,
  &kama_patC,
  &kama_patD,
  &kama_patE,
  &kama_patF,
  &kama_patG,
  &kama_patH
};
sprite_pattern* z31akamapat[8] =
{
  &z31a_kama_patA,
  &z31a_kama_patB,
  &z31a_kama_patC,
  &z31a_kama_patD,
  &z31a_kama_patE,
  &z31a_kama_patF,
  &z31a_kama_patG,
  &z31a_kama_patH
};
sprite_pattern* z33kamapat[8] =
{
  &z33_kama_patA,
  &z33_kama_patB,
  &z33_kama_patC,
  &z33_kama_patD,
  &z33_kama_patE,
  &z33_kama_patF,
  &z33_kama_patG,
  &z33_kama_patH
};
sprite_pattern** kamapats[3][3] =
{
  { z31akamapat, z31akamapat, kamapat },
  { kamapat, z31akamapat, kamapat },
  { 0, 0, z33kamapat }
};
sprite_pattern bkama_patA = { 3, { { -18, -20, 0, 450 }, { -12, -4, 0, 451 }, { -2, 4, 0, 452 } } };
sprite_pattern z31a_bkama_patA = { 3, { { -18, -20, 0, 497 }, { -12, -4, 0, 498 }, { -2, 4, 0, 499 } } };
sprite_pattern z33_bkama_patA = { 3, { { -18, -20, 0, 501 }, { -12, -4, 0, 502 }, { -2, 4, 0, 503 } } };
sprite_pattern bkama_patB = { 3, { { -18, -19, 0, 453 }, { -12, -3, 0, 454 }, { -2, 4, 0, 455 } } };
sprite_pattern z31a_bkama_patB = { 3, { { -18, -19, 0, 500 }, { -12, -3, 0, 501 }, { -2, 4, 0, 502 } } };
sprite_pattern z33_bkama_patB = { 3, { { -18, -19, 0, 504 }, { -12, -3, 0, 505 }, { -2, 4, 0, 506 } } };
sprite_pattern bkama_patC = { 3, { { -18, -20, 0, 456 }, { -12, -4, 0, 457 }, { -2, 4, 0, 458 } } };
sprite_pattern z31a_bkama_patC = { 3, { { -18, -20, 0, 503 }, { -12, -4, 0, 504 }, { -2, 4, 0, 505 } } };
sprite_pattern z33_bkama_patC = { 3, { { -18, -20, 0, 507 }, { -12, -4, 0, 508 }, { -2, 4, 0, 509 } } };
sprite_pattern bkama_patD = { 3, { { -18, -19, 0, 459 }, { -12, -3, 0, 460 }, { -2, 4, 0, 461 } } };
sprite_pattern z31a_bkama_patD = { 3, { { -18, -19, 0, 506 }, { -12, -3, 0, 507 }, { -2, 4, 0, 508 } } };
sprite_pattern z33_bkama_patD = { 3, { { -18, -19, 0, 510 }, { -12, -3, 0, 511 }, { -2, 4, 0, 512 } } };
sprite_pattern bkama_patE = { 3, { { -18, -19, 0, 462 }, { -12, -3, 0, 463 }, { -2, 4, 0, 464 } } };
sprite_pattern z31a_bkama_patE = { 3, { { -18, -19, 0, 509 }, { -12, -3, 0, 510 }, { -2, 4, 0, 511 } } };
sprite_pattern z33_bkama_patE = { 3, { { -18, -19, 0, 513 }, { -12, -3, 0, 514 }, { -2, 4, 0, 515 } } };
sprite_pattern bkama_patF = { 3, { { -18, -20, 0, 465 }, { -12, -4, 0, 466 }, { -2, 4, 0, 467 } } };
sprite_pattern z31a_bkama_patF = { 3, { { -18, -20, 0, 512 }, { -12, -4, 0, 513 }, { -2, 4, 0, 514 } } };
sprite_pattern z33_bkama_patF = { 3, { { -18, -20, 0, 516 }, { -12, -4, 0, 517 }, { -2, 4, 0, 518 } } };
sprite_pattern bkama_patG = { 3, { { -18, -19, 0, 468 }, { -12, -3, 0, 469 }, { -2, 4, 0, 470 } } };
sprite_pattern z31a_bkama_patG = { 3, { { -18, -19, 0, 515 }, { -12, -3, 0, 516 }, { -2, 4, 0, 517 } } };
sprite_pattern z33_bkama_patG = { 3, { { -18, -19, 0, 519 }, { -12, -3, 0, 520 }, { -2, 4, 0, 521 } } };
sprite_pattern bkama_patH = { 3, { { -18, -20, 0, 471 }, { -12, -4, 0, 472 }, { -2, 4, 0, 473 } } };
sprite_pattern z31a_bkama_patH = { 3, { { -18, -20, 0, 518 }, { -12, -4, 0, 519 }, { -2, 4, 0, 520 } } };
sprite_pattern z33_bkama_patH = { 3, { { -18, -20, 0, 522 }, { -12, -4, 0, 523 }, { -2, 4, 0, 524 } } };
sprite_pattern* bkamapat[8] =
{
  &bkama_patA,
  &bkama_patB,
  &bkama_patC,
  &bkama_patD,
  &bkama_patE,
  &bkama_patF,
  &bkama_patG,
  &bkama_patH
};
sprite_pattern* z31abkamapat[8] =
{
  &z31a_bkama_patA,
  &z31a_bkama_patB,
  &z31a_bkama_patC,
  &z31a_bkama_patD,
  &z31a_bkama_patE,
  &z31a_bkama_patF,
  &z31a_bkama_patG,
  &z31a_bkama_patH
};
sprite_pattern* z33bkamapat[8] =
{
  &z33_bkama_patA,
  &z33_bkama_patB,
  &z33_bkama_patC,
  &z33_bkama_patD,
  &z33_bkama_patE,
  &z33_bkama_patF,
  &z33_bkama_patG,
  &z33_bkama_patH
};
sprite_pattern** bkamapats[3][3] =
{
  { z31abkamapat, z31abkamapat, bkamapat },
  { bkamapat, z31abkamapat, bkamapat },
  { 0, 0, z33bkamapat }
};
unsigned char wpkama_pchg0[8] = { 3, 0, 1, 2, 3, 4, 5, 255 };
unsigned char wpkama_pchg1[8] = { 0, 0, 1, 2, 3, 4, 5, 255 };
unsigned char* wpkama_pchg[2] = { wpkama_pchg0, wpkama_pchg1 };
sprite_pattern bu0 = { 1, { { -8, -8, 0, 418 } } };
sprite_pattern z31abu0 = { 1, { { -8, -8, 0, 465 } } };
sprite_pattern z33bu0 = { 1, { { -8, -8, 0, 469 } } };
sprite_pattern bu1 = { 1, { { -8, -8, 0, 419 } } };
sprite_pattern z31abu1 = { 1, { { -8, -8, 0, 466 } } };
sprite_pattern z33bu1 = { 1, { { -8, -8, 0, 470 } } };
sprite_pattern bu2 = { 1, { { -8, -8, 0, 420 } } };
sprite_pattern z31abu2 = { 1, { { -8, -8, 0, 467 } } };
sprite_pattern z33bu2 = { 1, { { -8, -8, 0, 471 } } };
sprite_pattern bu3 = { 1, { { -8, -8, 0, 421 } } };
sprite_pattern z31abu3 = { 1, { { -8, -8, 0, 468 } } };
sprite_pattern z33bu3 = { 1, { { -8, -8, 0, 472 } } };
sprite_pattern bu4 = { 1, { { -8, -8, 0, 422 } } };
sprite_pattern z31abu4 = { 1, { { -8, -8, 0, 469 } } };
sprite_pattern z33bu4 = { 1, { { -8, -8, 0, 473 } } };
sprite_pattern bu5 = { 1, { { -8, -8, 0, 423 } } };
sprite_pattern z31abu5 = { 1, { { -8, -8, 0, 470 } } };
sprite_pattern z33bu5 = { 1, { { -8, -8, 0, 474 } } };
sprite_pattern* wpkamapat[6] =
{
  &bu0,
  &bu1,
  &bu2,
  &bu3,
  &bu4,
  &bu5
};
sprite_pattern* z31awpkamapat[6] =
{
  &z31abu0,
  &z31abu1,
  &z31abu2,
  &z31abu3,
  &z31abu4,
  &z31abu5
};
sprite_pattern* z33wpkamapat[6] =
{
  &z33bu0,
  &z33bu1,
  &z33bu2,
  &z33bu3,
  &z33bu4,
  &z33bu5
};
sprite_pattern** wpkamapats[3][3] =
{
  { z31awpkamapat, z31awpkamapat, wpkamapat },
  { wpkamapat, z31awpkamapat, wpkamapat },
  { 0, 0, z33wpkamapat }
};


void ene_kama(sprite_status* pActwk) {
  unsigned char byRwk;

  if (pActwk->xposi.w.h == 4800 && pActwk->yposi.w.h == 890)
  {

    jmp_flg = 0;
  }
  if (enemy_suicide(pActwk) == -1) return;

  byRwk = pActwk->r_no0 / 2;
  kama_tbl[byRwk](pActwk);

  frameout_s(pActwk);
}











void kama_init(sprite_status* pActwk) {
  ((char*)pActwk)[50] = pActwk->userflag.b.h;
  if (((char*)pActwk)[50] >= 0)
  {
    pActwk->patno = 1;
    pActwk->patbase = kamapats[stageno_i.b.l][time_flag_i & 0x7F];
  }
  else
  {

    pActwk->patno = 2;
    pActwk->patbase = bkamapats[stageno_i.b.l][time_flag_i & 0x7F];
  }

  pActwk->actflg = 4;
  pActwk->sprpri = 3;
  pActwk->sprhsize = 16;
  pActwk->sprvsize = 20;
  pActwk->sproffset = 9202;
  pActwk->yspeed.w = 256;
  pActwk->colino = 6;
  pActwk->r_no0 += 2;

  kama_fall(pActwk);
}





void kama_disp(sprite_status* pActwk) {
  patchg(pActwk, kama_pchg);
  actionsub(pActwk);
  jmp_flg = 1;
}










void kama_fall(sprite_status* pActwk) {
  short iD1;

  movement(pActwk);
  iD1 = emycol_d(pActwk);
  if (iD1 < 0)
    pActwk->r_no0 += 2;

  kama_disp(pActwk);
}











void kama_wait(sprite_status* pActwk) {
  short iD0, iD1;
  sprite_status* pPlaywk;

  if (pActwk->actflg & 128)
  {
    pActwk->actflg &= 254;
    pActwk->cddat &= 254;

    pPlaywk = &actwk[0];
    iD0 = pActwk->xposi.w.h;
    bCarry = CCset(iD0, pPlaywk->xposi.w.h);
    iD0 -= pPlaywk->xposi.w.h;
    if (bCarry == 1)
    {
      iD0 = -iD0;
      pActwk->actflg |= 1;
      pActwk->cddat |= 1;
    }

    if ((char)pActwk->actflg < 0)
    {
      iD1 = pActwk->yposi.w.h;
      bCarry = CCset(iD1, pPlaywk->yposi.w.h);
      iD1 -= pPlaywk->yposi.w.h;
      if (bCarry == 1)
        iD1 = -iD1;

      if (iD1 < 96)
      {

        pActwk->mstno.b.h = 2;
        set_wpkama(pActwk);
        ((short*)pActwk)[24] = 120;
        pActwk->r_no0 += 2;
        kama_atck(pActwk);
        return;
      }
    }
  }

  pActwk->mstno.b.h = 1;
  kama_disp(pActwk);
}











void kama_atck(sprite_status* pActwk) {
  --((unsigned short*)pActwk)[24];
  if (((unsigned short*)pActwk)[24] != 0)
    kama_disp(pActwk);
  else
  {

    pActwk->mstno.b.h = 3;
    ((unsigned short*)pActwk)[24] = 60;
    pActwk->r_no0 += 2;
    kama_pati(pActwk);
  }
}











void kama_pati(sprite_status* pActwk) {
  --((unsigned short*)pActwk)[24];
  if (((unsigned short*)pActwk)[24] != 0)
    kama_disp(pActwk);
  else
  {

    pActwk->r_no0 += 2;
    kama_move(pActwk);
  }
}











void kama_move(sprite_status* pActwk) {
  short iD0, iD1;

  if (pActwk->userflag.b.h >= 0)
    iD0 = 256;
  else
    iD0 = 128;

  pActwk->mstno.b.h = 0;
  if (!(pActwk->cddat & 1))
    iD0 = -iD0;

  pActwk->xspeed.w = iD0;

  movement(pActwk);

  iD1 = dircol_l2(pActwk);
  if (iD1 >= 0)
  {
    iD1 = dircol_r2(pActwk);
    if (iD1 >= 0)
    {
      iD1 = emycol_d(pActwk);
      if (iD1 == 0)
      {
        kama_disp(pActwk);
        return;
      }
      if (iD1 < 7 && iD1 > -7)
      {
        pActwk->yposi.w.h += iD1;
        kama_disp(pActwk);
        return;
      }
    }
  }

  ((short*)pActwk)[24] = 72;
  pActwk->mstno.b.h = 3;
  pActwk->r_no0 += 2;
  kama_reve(pActwk);
}











void kama_reve(sprite_status* pActwk) {
  --((unsigned short*)pActwk)[24];
  if (((unsigned short*)pActwk)[24] == 0)
  {
    pActwk->actflg = bchg(0, pActwk->actflg);
    pActwk->cddat = bchg(0, pActwk->cddat);
    pActwk->r_no0 -= 2;
  }
  kama_disp(pActwk);
}











void movement(sprite_status* pActwk) {
  int lD0 = 0;

  lD0 = pActwk->xspeed.w;
  if (lD0 & 0x80000000) lD0 <<= 8, lD0 |= 0x80000000; else lD0 <<= 8;
  pActwk->xposi.l += lD0;

  lD0 = pActwk->yspeed.w;
  if (lD0 & 0x80000000) lD0 <<= 8, lD0 |= 0x80000000; else lD0 <<= 8;
  pActwk->yposi.l += lD0;
}











void set_wpkama(sprite_status* pActwk) {
  sprite_status* pActfree;

  if (pActwk->userflag.b.h >= 0)
  {

    if (actwkchk(&pActfree) == 0)
    {
      pActfree->actno = 37;

      ((unsigned short*)pActfree)[26] = pActwk - actwk;

      ((short*)pActfree)[24] = 64;
      pActfree->userflag.b.h = pActwk->userflag.b.h;

      pActfree->actfree[4] = pActwk->actflg;

      pActfree->yposi.w.h = pActwk->yposi.w.h - 4;
      if (!(pActwk->actflg & 1))
        pActfree->xposi.w.h = pActwk->xposi.w.h - 17;
      else
        pActfree->xposi.w.h = pActwk->xposi.w.h + 17;
    }

    if (actwkchk(&pActfree) == 0)
    {
      pActfree->actno = 37;

      ((unsigned short*)pActfree)[26] = pActwk - actwk;

      ((short*)pActfree)[24] = 20;
      pActfree->userflag.b.h = pActwk->userflag.b.h;

      pActfree->actfree[4] = pActwk->actflg;

      pActfree->yposi.w.h = pActwk->yposi.w.h - 6;
      if (!(pActwk->actflg & 1))
        pActfree->xposi.w.h = pActwk->xposi.w.h - 9;
      else
        pActfree->xposi.w.h = pActwk->xposi.w.h + 9;
    }
  }
}






















void tama_kama(sprite_status* pActwk) {
  jmp_flg = 0;
  wpkama_tbl[pActwk->r_no0 / 2](pActwk);
  actionsub(pActwk);
  frameout_s00(pActwk, ((short*)pActwk)[27]);
  jmp_flg = 0;
}











void wpkama_init(sprite_status* pActwk) {
  short iD1;

  pActwk->actflg = 4;
  pActwk->sprpri = 1;
  pActwk->sprhs = 4;
  pActwk->sprvsize = 4;
  pActwk->sproffset = 9202;
  pActwk->patbase = wpkamapats[stageno_i.b.l][time_flag_i & 0x7F];
  ((short*)pActwk)[27] = pActwk->xposi.w.h;

  iD1 = 768;

  if (!(pActwk->actfree[4] & 1))
  {
    pActwk->actflg |= 1;
    pActwk->cddat |= 1;
    iD1 = -iD1;
  }

  pActwk->xspeed.w = iD1;
  pActwk->r_no0 += 2;
}












void wpkama_wait(sprite_status* pActwk) {
  unsigned short wD0;
  sprite_status* pActfree;

  --((unsigned short*)pActwk)[24];
  if (((unsigned short*)pActwk)[24] == 0)
  {
    pActwk->r_no0 += 2;
    pActwk->colino = 135;
    ((short*)pActwk)[28] = 60;
  }

  wD0 = ((unsigned short*)pActwk)[26];
  pActfree = &actwk[wD0];
  if (pActfree->actno != 36)
    frameout(pActwk);
  else

    patchg(pActwk, wpkama_pchg);
  jmp_flg = 1;
}












void wpkama_move(sprite_status* pActwk) {
  sprite_status* pPlaywk;

  movement(pActwk);
  pActwk->yspeed.w += ((short*)pActwk)[23];

  if (pActwk->patno == 0)
  {
    if (pActwk->actflg & 128)
      soundset(185);
  }

  pPlaywk = &actwk[0];
  if (wpkama_colicheck(pActwk, pPlaywk) != 0)
    wpkama_reve(pActwk, pPlaywk);
  wpkama_disp(pActwk);
}












void wpkama_disp(sprite_status* pActwk) {
  --((unsigned short*)pActwk)[28];
  if (((unsigned short*)pActwk)[28] == 0)
  {
    ++((unsigned short*)pActwk)[28];
    pActwk->colino = 0;
  }

  patchg(pActwk, wpkama_pchg);
  jmp_flg = 1;
}












short wpkama_colicheck(sprite_status* pActwk, sprite_status* pPlaywk) {
  unsigned char byFlg;
  short iD0, iD1;

  if (plpower_m == 0)
  {
    if (!(pPlaywk->cddat & 4))
      return 0;
  }

  iD0 = pPlaywk->xposi.w.h - pActwk->xposi.w.h;
  iD1 = 28;
  iD0 += iD1;
  if (iD0 < 0) return 0;
  iD1 += iD1;
  byFlg = CCset(iD0, iD1);
  if (byFlg == 0) return 0;

  iD0 = pPlaywk->yposi.w.h - pActwk->yposi.w.h;
  iD1 = 28;
  iD0 += iD1;
  if (iD0 < 0) return 0;
  iD1 += iD1;
  byFlg = CCset(iD0, iD1);
  if (byFlg == 0) return 0;

  return 1;
}













void wpkama_reve(sprite_status* pActwk, sprite_status* pPlaywk) {
  pActwk->colino = 0;
  pActwk->mstno.b.h = 1;

  pActwk->xspeed.w += pPlaywk->xspeed.w;
  pActwk->yspeed.w = -2048;
  ((short*)pActwk)[23] = 64;
}
