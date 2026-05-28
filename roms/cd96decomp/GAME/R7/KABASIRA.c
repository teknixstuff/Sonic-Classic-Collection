#include "../EQU.h"
#include "KABASIRA.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void act_init(sprite_status* pActwk);
static void act_init_sub(sprite_status* pActwk);
static void act_move(sprite_status* pActwk);
static unsigned int kabasira_area(sprite_status* pActwk, sprite_status* pPlayerwk, short* pX, short* pY);

static unsigned char pchg_00[18] = { 15, 4, 5, 6, 7, 8, 9, 10, 11, 10, 11, 0, 1, 2, 3, 4, 5, 255 };
static unsigned char pchg_01[130] = {
  0, 4, 12, 4, 12, 4, 12, 4, 12, 5,
  12, 5, 12, 5, 12, 5, 12, 4, 12, 4,
  12, 4, 12, 4, 12, 5, 12, 5, 12, 5,
  12, 5, 12, 6, 12, 6, 12, 6, 12, 6,
  12, 7, 12, 7, 12, 7, 12, 7, 12, 8,
  12, 8, 12, 8, 12, 8, 12, 9, 12, 9,
  12, 9, 12, 9, 12, 10, 12, 10, 12, 10,
  12, 10, 12, 11, 12, 11, 12, 11, 12, 11,
  12, 10, 12, 10, 12, 10, 12, 10, 12, 11,
  12, 11, 12, 11, 12, 11, 12, 0, 12, 0,
  12, 0, 12, 0, 12, 1, 12, 1, 12, 1,
  12, 1, 12, 2, 12, 2, 12, 2, 12, 2,
  12, 3, 12, 3, 12, 3, 12, 3, 12, 255
};
static unsigned char pchg_02[130] = {
  0, 2, 12, 12, 12, 2, 12, 12, 12, 3,
  12, 12, 12, 3, 12, 12, 12, 4, 12, 12,
  12, 4, 12, 12, 12, 5, 12, 12, 12, 5,
  12, 12, 12, 4, 12, 12, 12, 4, 12, 12,
  12, 5, 12, 12, 12, 5, 12, 12, 12, 6,
  12, 12, 12, 6, 12, 12, 12, 7, 12, 12,
  12, 7, 12, 12, 12, 8, 12, 12, 12, 8,
  12, 12, 12, 9, 12, 12, 12, 9, 12, 12,
  12, 10, 12, 12, 12, 10, 12, 12, 12, 11,
  12, 12, 12, 11, 12, 12, 12, 10, 12, 12,
  12, 10, 12, 12, 12, 11, 12, 12, 12, 11,
  12, 12, 12, 0, 12, 12, 12, 0, 12, 12,
  12, 1, 12, 12, 12, 1, 12, 12, 12, 255
};
static unsigned char pchg_03[130] = {
  0, 0, 12, 12, 12, 12, 12, 12, 12, 1,
  12, 12, 12, 12, 12, 12, 12, 2, 12, 12,
  12, 12, 12, 12, 12, 3, 12, 12, 12, 12,
  12, 12, 12, 4, 12, 12, 12, 12, 12, 12,
  12, 5, 12, 12, 12, 12, 12, 12, 12, 4,
  12, 12, 12, 12, 12, 12, 12, 5, 12, 12,
  12, 12, 12, 12, 12, 6, 12, 12, 12, 12,
  12, 12, 12, 7, 12, 12, 12, 12, 12, 12,
  12, 8, 12, 12, 12, 12, 12, 12, 12, 9,
  12, 12, 12, 12, 12, 12, 12, 10, 12, 12,
  12, 12, 12, 12, 12, 11, 12, 12, 12, 12,
  12, 12, 12, 10, 12, 12, 12, 12, 12, 12,
  12, 11, 12, 12, 12, 12, 12, 12, 12, 255
};
static unsigned char pchg_04[18] = { 7, 4, 5, 6, 7, 8, 9, 10, 11, 10, 11, 0, 1, 2, 3, 4, 5, 255 };
static unsigned char pchg_05[66] = {
  0, 5, 12, 5, 12, 4, 12, 4, 12, 5,
  12, 5, 12, 6, 12, 6, 12, 7, 12, 7,
  12, 8, 12, 8, 12, 9, 12, 9, 12, 10,
  12, 10, 12, 11, 12, 11, 12, 10, 12, 10,
  12, 11, 12, 11, 12, 0, 12, 0, 12, 1,
  12, 1, 12, 2, 12, 2, 12, 3, 12, 3,
  12, 4, 12, 4, 12, 255
};
static unsigned char pchg_06[66] = {
  0, 4, 12, 12, 12, 5, 12, 12, 12, 4,
  12, 12, 12, 5, 12, 12, 12, 6, 12, 12,
  12, 7, 12, 12, 12, 8, 12, 12, 12, 9,
  12, 12, 12, 10, 12, 12, 12, 11, 12, 12,
  12, 10, 12, 12, 12, 11, 12, 12, 12, 0,
  12, 12, 12, 1, 12, 12, 12, 2, 12, 12,
  12, 3, 12, 12, 12, 255
};
static unsigned char pchg_07[66] = {
  0, 3, 12, 12, 12, 4, 12, 12, 12, 5,
  12, 12, 12, 4, 12, 12, 12, 5, 12, 12,
  12, 6, 12, 12, 12, 7, 12, 12, 12, 8,
  12, 12, 12, 9, 12, 12, 12, 10, 12, 12,
  12, 11, 12, 12, 12, 10, 12, 12, 12, 11,
  12, 12, 12, 0, 12, 12, 12, 1, 12, 12,
  12, 2, 12, 12, 12, 255
};
static unsigned char pchg_08[4] = { 0, 13, 12, 255 };
static unsigned char* pchg[9] = {
  pchg_00,
  pchg_01,
  pchg_02,
  pchg_03,
  pchg_04,
  pchg_05,
  pchg_06,
  pchg_07,
  pchg_08
};
static sprite_pattern pat00 = {
  2,
  {
    { -8, -8, 0, 468 },
    { -8, -6, 0, 481 }
  }
};
static sprite_pattern pat01 = {
  2,
  {
    { -8, -8, 0, 469 },
    { -8, -6, 0, 482 }
  }
};
static sprite_pattern pat02 = {
  2,
  {
    { -8, -8, 0, 470 },
    { -12, -6, 0, 483 }
  }
};
static sprite_pattern pat03 = {
  2,
  {
    { -8, -8, 0, 471 },
    { -12, -6, 0, 484 }
  }
};
static sprite_pattern pat04 = {
  2,
  {
    { -10, -5, 0, 485 },
    { -8, -8, 0, 472 }
  }
};
static sprite_pattern pat05 = {
  2,
  {
    { -10, -5, 0, 486 },
    { -8, -8, 0, 473 }
  }
};
static sprite_pattern pat06 = {
  2,
  {
    { -12, -6, 0, 487 },
    { -8, -8, 0, 474 }
  }
};
static sprite_pattern pat07 = {
  2,
  {
    { -12, -6, 0, 488 },
    { -8, -8, 0, 475 }
  }
};
static sprite_pattern pat08 = {
  2,
  {
    { -8, -6, 0, 489 },
    { -8, -8, 0, 476 }
  }
};
static sprite_pattern pat09 = {
  2,
  {
    { -8, -6, 0, 490 },
    { -8, -8, 0, 477 }
  }
};
static sprite_pattern pat0a = {
  2,
  {
    { -1, -5, 0, 491 },
    { -8, -8, 0, 478 }
  }
};
static sprite_pattern pat0b = {
  2,
  {
    { -1, -5, 0, 492 },
    { -8, -8, 0, 479 }
  }
};
static sprite_pattern pat0c;
static sprite_pattern pat0d = {
  2,
  {
    { -10, -5, 0, 493 },
    { -8, -8, 0, 480 }
  }
};
sprite_pattern* pat_kabasira[14] = {
  &pat00,
  &pat01,
  &pat02,
  &pat03,
  &pat04,
  &pat05,
  &pat06,
  &pat07,
  &pat08,
  &pat09,
  &pat0a,
  &pat0b,
  &pat0c,
  &pat0d
};
static void(*kabasira_act_tbl[2])(sprite_status*) = {
  &act_init,
  &act_move
};



























































































































































































































































































void kabasira(sprite_status* pActwk) {
  sprite_status* pMainact;
  short xsv, ysv, len;
  if (pActwk->userflag.b.l < 0) {
    if (pActwk->userflag.b.l == -1) {

      pMainact = &actwk[((short*)pActwk)[33]];
      if (pMainact->actno == 34) goto label1;

      frameout(pActwk);
      return;
    }




    pActwk->xposi.l += *(int*)&pActwk->actfree[0];
    pActwk->yposi.l += *(int*)&pActwk->actfree[4];

    if (pActwk->colicnt) {
      xsv = pActwk->xposi.w.h;
      ysv = pActwk->yposi.w.h;
      frameout(pActwk);
      pActwk->xposi.w.h = xsv;
      pActwk->yposi.w.h = ysv;
      pActwk->actno = 24;
      pActwk->r_no1 = 1;
      soundset(158);
    }
    else {
      if ((len = actwk[0].yposi.w.h - pActwk->yposi.w.h) < 0) {
        len *= -1;
      }


      if (len > 224) {

        frameout(pActwk);
      } else {
        patchg(pActwk, pchg);
        actionsub(pActwk);
        frameout_s(pActwk);
      }
    }

    return;
  }


  if (enemy_suicide(pActwk)) return;




label1:
  kabasira_act_tbl[pActwk->r_no0 / 2](pActwk);
  patchg(pActwk, pchg);
  actionsub(pActwk);
  frameout_s(pActwk);
}





static void act_init(sprite_status* pActwk) {
  short anglewk1, anglewk2, xangle, yangle;
  unsigned char mstnowk;
  int i;
  sprite_status* pNewact;

  pActwk->colino = 49;
  ((short*)pActwk)[24] = pActwk->xposi.w.h;
  ((short*)pActwk)[26] = pActwk->yposi.w.h;
  ((short*)pActwk)[23] = -32768;
  ((short*)pActwk)[25] = -32768;

  if (!pActwk->userflag.b.h) {
    ((short*)pActwk)[29] = 512;
    ((short*)pActwk)[30] = 256;
    pActwk->mstno.b.h = 4;
    anglewk1 = 4096;
    anglewk2 = 2048;
  } else {
    ((short*)pActwk)[29] = 256;
    ((short*)pActwk)[30] = 128;
    pActwk->mstno.b.h = 0;
    anglewk1 = 8192;
    anglewk2 = 4096;
  }

  act_init_sub(pActwk);

  xangle = 0;
  yangle = 0;
  mstnowk = 0;

  for (i = 0; i < 3; ++i) {

    if (actwkchk2(pActwk, &pNewact) != 0) {

      frameout(pActwk);
      return;
    }

    ((short*)pNewact)[33] = pActwk - actwk;
    ++mstnowk;
    pNewact->mstno.b.h = (unsigned char)(mstnowk + pActwk->mstno.b.h);
    xangle -= anglewk1;
    yangle -= anglewk2;
    ((short*)pNewact)[27] = xangle;
    ((short*)pNewact)[28] = yangle;
    pNewact->userflag.b.l = -1;
    pNewact->actno = pActwk->actno;
    pNewact->xposi.w.h = pActwk->xposi.w.h;
    pNewact->yposi.w.h = pActwk->yposi.w.h;
    *(int*)&pNewact->actfree[0] = *(int*)&pActwk->actfree[0];

    *(int*)&pNewact->actfree[4] = *(int*)&pActwk->actfree[4];

    ((short*)pNewact)[29] = ((short*)pActwk)[29];

    ((short*)pNewact)[30] = ((short*)pActwk)[30];

    act_init_sub(pNewact);
  }
}





static void act_init_sub(sprite_status* pActwk) {
  pActwk->r_no0 = 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 3;
  pActwk->sprhs = 12;
  pActwk->sprhsize = 12;
  pActwk->sprvsize = 8;
  pActwk->sproffset = 9158;
  pActwk->patbase = pat_kabasira;
}





static void act_move(sprite_status* pActwk) {
  sprite_status* pTamaact;
  short xlen, ylen, anglewk;
  int_union sinwk, coswk;

  sinwk.l = coswk.l = 0;

  if (!pActwk->userflag.b.h && pActwk->userflag.b.l >= 0) {
    if (((short*)pActwk)[31]) {
      --((short*)pActwk)[31];
    }
    else {
      if (kabasira_area(pActwk, &actwk[0], &xlen, &ylen) != 0) {

        ((short*)pActwk)[31] = 240;
        if (actwkchk(&pTamaact) == 0) {
          pTamaact->mstno.b.h = 8;
          pTamaact->userflag.b.l = -2;
          pTamaact->colino = 241;
          pTamaact->actno = pActwk->actno;
          pTamaact->xposi.w.h = pActwk->xposi.w.h;
          pTamaact->yposi.w.h = pActwk->yposi.w.h;
          act_init_sub(pTamaact);
          sinset(atan_sonic(xlen, ylen), &sinwk.w.l, &coswk.w.l);
          sinwk.l = (unsigned int)sinwk.l >> 16 & 65535 | sinwk.l << 16 & -65536;
          coswk.l = (unsigned int)coswk.l >> 16 & 65535 | coswk.l << 16 & -65536;
          sinwk.l >>= 7;
          coswk.l >>= 7;
          *(int*)&pTamaact->actfree[4] = sinwk.l;
          *(int*)&pTamaact->actfree[0] = coswk.l;

          if (coswk.l < 0) {
            pTamaact->actflg ^= 1;
            pTamaact->cddat ^= 1;
          }


          if (pActwk->actflg & 128) {
            soundset(160);
          }
        }
      }
    }
  }




  anglewk = ((short*)pActwk)[27] + ((short*)pActwk)[29];

  ((short*)pActwk)[27] = anglewk;
  anglewk = (unsigned short)anglewk >> 8;
  sinwk.l = coswk.l = 0;
  sinset(anglewk, &sinwk.w.l, &coswk.w.l);
  sinwk.l = (unsigned int)sinwk.l >> 16 & 65535 | sinwk.l << 16 & -65536;
  sinwk.l >>= 4;
  pActwk->xposi.l = sinwk.l + *(int*)&pActwk->actfree[0];

  anglewk = ((short*)pActwk)[28] + ((short*)pActwk)[30];

  ((short*)pActwk)[28] = anglewk;
  anglewk = (unsigned short)anglewk >> 8;
  sinwk.l = coswk.l = 0;
  sinset(anglewk, &sinwk.w.l, &coswk.w.l);
  coswk.l = (unsigned int)coswk.l >> 16 & 65535 | coswk.l << 16 & -65536;
  coswk.l >>= 2;
  pActwk->yposi.l = coswk.l + *(int*)&pActwk->actfree[4];
}

















static unsigned int kabasira_area(sprite_status* pActwk, sprite_status* pPlayerwk, short* pX, short* pY) {
  *pY = pPlayerwk->yposi.w.h - pActwk->yposi.w.h;
  if ((unsigned short)(*pY + 96) >= 192) {
    return 0;
  }

  *pX = pPlayerwk->xposi.w.h - pActwk->xposi.w.h;
  if ((unsigned short)(*pX + 120) >= 240) {
    return 0;
  }

  return 1;
}
