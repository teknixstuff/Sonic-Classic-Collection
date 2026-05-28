#include "../EQU.h"
#include "HOTARU7.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void a_init(sprite_status* pActwk);
static void a_wait(sprite_status* pActwk);
static void a_make(sprite_status* pActwk);
static void ini_b(sprite_status* pActwk, sprite_status* pNewact);
static void a_move(sprite_status* pActwk);
static void b_init(sprite_status* pActwk);
static void b_fly(sprite_status* pActwk);
static void b_near(sprite_status* pActwk);
static void b_fix(sprite_status* pActwk);
static void b_fix1(sprite_status* pActwk);
static void b_start(sprite_status* pActwk);
static void b_com(sprite_status* pActwk);
static void b_com1(sprite_status* pActwk);
static void b_kill_v(sprite_status* pActwk);
static void b_die_v(sprite_status* pActwk, sprite_status* pMainwk);
static void b_light(sprite_status* pActwk);
static void b_up(sprite_status* pActwk);
static void b_up1(sprite_status* pActwk);
static void b_make_c(sprite_status* pActwk);
static void c_init(sprite_status* pActwk);
static void c_move(sprite_status* pActwk);
static unsigned int area(sprite_status* pActwk, sprite_status* pPlayerwk, unsigned short Ypos, unsigned short Ylen, unsigned short Xpos, unsigned short Xlen);

static short tbl_hotaru7[8] = { 36, 60, 8, -68, 56, -56, 80, 16 };
static unsigned char pchg_e00[12] = { 9, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 252 };
static unsigned char pchg_e01[14] = { 3, 4, 2, 2, 2, 4, 4, 2, 2, 4, 4, 4, 2, 252 };
static unsigned char pchg_e02[12] = { 9, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 252 };
static unsigned char pchg_e03[4] = { 9, 3, 4, 255 };
static unsigned char* pchg_hotaru7_e[4] = {
  pchg_e00,
  pchg_e01,
  pchg_e02,
  pchg_e03
};
static unsigned char pchg_b00[12] = { 19, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 252 };
static unsigned char pchg_b01[14] = { 9, 4, 2, 2, 2, 4, 4, 2, 2, 4, 4, 4, 2, 252 };
static unsigned char pchg_b02[12] = { 19, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 252 };
static unsigned char pchg_b03[4] = { 19, 3, 4, 255 };
static unsigned char* pchg_hotaru7_b[4] = {
  pchg_b00,
  pchg_b01,
  pchg_b02,
  pchg_b03
};
static unsigned char pchg_tama00[5] = { 1, 0, 1, 2, 255 };
static unsigned char* pchg_tama[1] = { pchg_tama00 };
static sprite_pattern pat_e00 = {
  1,
  { { -20, -12, 32, 508 } }
};
static sprite_pattern pat_e01 = {
  1,
  { { -12, -20, 32, 509 } }
};
static sprite_pattern pat_e02 = {
  1,
  { { -12, -20, 32, 510 } }
};
static sprite_pattern pat_e03 = {
  2,
  {
    { -12, -20, 32, 511 },
    { -11, -7, 32, 521 }
  }
};
static sprite_pattern pat_e04 = {
  2,
  {
    { -12, -20, 32, 512 },
    { -11, -7, 32, 521 }
  }
};
sprite_pattern* pat_hotaru7_e[5] = {
  &pat_e00,
  &pat_e01,
  &pat_e02,
  &pat_e03,
  &pat_e04
};
static sprite_pattern pat_b00 = {
  1,
  { { -20, -12, 32, 513 } }
};
static sprite_pattern pat_b01 = {
  1,
  { { -12, -20, 32, 514 } }
};
static sprite_pattern pat_b02 = {
  1,
  { { -12, -20, 32, 515 } }
};
static sprite_pattern pat_b03 = {
  2,
  {
    { -12, -20, 32, 516 },
    { -11, -7, 32, 521 }
  }
};
static sprite_pattern pat_b04 = {
  2,
  {
    { -12, -20, 32, 517 },
    { -11, -7, 32, 521 }
  }
};
sprite_pattern* pat_hotaru7_b[5] = {
  &pat_b00,
  &pat_b01,
  &pat_b02,
  &pat_b03,
  &pat_b04
};
static sprite_pattern pat_tama00 = {
  1,
  { { -12, -12, 0, 518 } }
};
static sprite_pattern pat_tama01 = {
  1,
  { { -12, -12, 0, 519 } }
};
static sprite_pattern pat_tama02 = {
  1,
  { { -12, -12, 0, 520 } }
};
sprite_pattern* pat_tama[3] = {
  &pat_tama00,
  &pat_tama01,
  &pat_tama02
};
static void(*a_act_tbl[4])(sprite_status*) = {
  &a_init,
  &a_wait,
  &a_make,
  &a_move
};
static void(*b_act_tbl[11])(sprite_status*) = {
  &b_init,
  &b_fly,
  &b_near,
  &b_fix,
  &b_fix1,
  &b_start,
  &b_com,
  &b_light,
  &b_com,
  &b_up,
  &b_up1
};
static void(*c_act_tbl[3])(sprite_status*) = {
  &c_init,
  &c_move,
  &frameout
};


























































































































































void hotaru7(sprite_status* pActwk) {
  switch (pActwk->userflag.b.l) {
    sprite_status* pMainact;
    sprite_status* pBact1;
    sprite_status* pBact2;

    case -1:
      pMainact = &actwk[((short*)pActwk)[23]];
      if (pMainact->actno != 35 || pMainact->cdsts != pActwk->actfree[12])

        frameout(pActwk);
      else {

        if (!enemy_suicide(pActwk)) {
          b_act_tbl[pActwk->r_no0 / 2](pActwk);
        }
      }
      break;





    case -2:
      pBact1 = &actwk[((short*)pActwk)[24]];
      pBact2 = &actwk[((short*)pActwk)[23]];

      if (pBact1->actno != 35 || pBact2->actno != 35
          || pBact1->r_no0 != 16 || pBact2->r_no0 != 16)
        frameout(pActwk);
      else {

        c_act_tbl[pActwk->r_no0 / 2](pActwk);
      }
      break;


    default:
      a_act_tbl[pActwk->r_no0 / 2](pActwk);
      break;
  }
}





void a_init(sprite_status* pActwk) {
  unsigned short flagwk;
  unsigned char* pFlagwork;
  int idx;

  pActwk->r_no0 += 2;
  flagwk = pActwk->cdsts;
  idx = time_flag + flagwk * 3;
  pFlagwork = &flagwork[idx];
  *(unsigned char**)&pActwk->actfree[0] = &flagwork[idx];

  idx = pActwk->userflag.b.h & 12;
  *(short**)&pActwk->actfree[4] = &tbl_hotaru7[idx / 2];

  if (pActwk->userflag.b.h & 1) {
    pActwk->userflag.b.h = 1;
  } else {
    pActwk->userflag.b.h = 0;
  }

  if (stageno.b.l != 2) {
    pActwk->sproffset = 33885;
  } else {
    pActwk->sproffset = 33568;
  }

  a_wait(pActwk);
}





void a_wait(sprite_status* pActwk) {
  if (area(pActwk, &actwk[0], 65296, 480, 65296, 480) != 0)
  {

    pActwk->r_no0 += 2;
  }

  frameout_s(pActwk);
}





void a_make(sprite_status* pActwk) {
  unsigned char* pFlagWork;
  sprite_status* pNewact;
  short* pTbl;

  pActwk->r_no0 += 2;
  pFlagWork = *(unsigned char**)&pActwk->actfree[0];

  if (!(*pFlagWork & 1)) {
    if (actwkchk2(pActwk, &pNewact) != 0)
    { frameout_s0(pActwk); return; }


    ((short*)pActwk)[28] = pNewact - actwk;

    ini_b(pActwk, pNewact);
    pTbl = *(short**)&pActwk->actfree[4];
    pNewact->xposi.w.h += *pTbl++;
    pNewact->yposi.w.h += *pTbl;
  }


  if (!(*pFlagWork & 2)) {
    if (actwkchk2(pActwk, &pNewact) != 0)
    { frameout_s0(pActwk); return; }


    ((short*)pActwk)[27] = pNewact - actwk;

    ini_b(pActwk, pNewact);
    pTbl = *(short**)&pActwk->actfree[4];
    pNewact->xposi.w.h -= *pTbl++;
    pNewact->yposi.w.h -= *pTbl;
  }


}





void ini_b(sprite_status* pActwk, sprite_status* pNewact) {
  ((short*)pNewact)[23] = pActwk - actwk;
  pNewact->actno = pActwk->actno;
  pNewact->userflag.b.h = pActwk->userflag.b.h;
  pNewact->userflag.b.l = -1;
  pNewact->xposi.w.h = pActwk->xposi.w.h;
  pNewact->yposi.w.h = pActwk->yposi.w.h;
  pNewact->sproffset = pActwk->sproffset;
  pNewact->actfree[12] = pActwk->cdsts;
}





void a_move(sprite_status* pActwk) {
  unsigned char* pFlagWork;
  sprite_status* pChildact;
  short idx;

  pFlagWork = *(unsigned char**)&pActwk->actfree[0];

  if (!(*pFlagWork & 1)) {
    idx = ((short*)pActwk)[28];
    if (idx) {
      pChildact = &actwk[idx];
      if (pChildact->actno != pActwk->actno) {

        *pFlagWork |= 1;
        ((short*)pActwk)[28] = 0;
      }
    }
  }






  if (!(*pFlagWork & 2)) {
    idx = ((short*)pActwk)[27];
    if (idx) {
      pChildact = &actwk[idx];
      if (pChildact->actno != pActwk->actno) {

        *pFlagWork |= 2;
        ((short*)pActwk)[27] = 0;
      }
    }
  }






  if (*pFlagWork == 131)
    frameout(pActwk);
  else
  {
    if (*(int*)&pActwk->actfree[8] == 0)
      frameout_s0(pActwk);
  }
}








void b_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 1;
  pActwk->sprhs = pActwk->sprhsize = 20;
  pActwk->sprvsize = 12;
  pActwk->colino = 50;
  ((short*)pActwk)[24] = pActwk->xposi.w.h;

  if (!pActwk->userflag.b.h) {

    pActwk->patbase = pat_hotaru7_e;
    *(unsigned char***)&pActwk->actfree[8] = pchg_hotaru7_e;
    *(int*)&pActwk->actfree[4] = -65536;
  }
  else {
    pActwk->patbase = pat_hotaru7_b;
    *(unsigned char***)&pActwk->actfree[8] = pchg_hotaru7_b;
    *(int*)&pActwk->actfree[4] = -32768;
  }


  if (actwk[0].xposi.w.h >= pActwk->xposi.w.h) {
    *(int*)&pActwk->actfree[4] *= -1;
    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;
  }


}





void b_fly(sprite_status* pActwk) {
  short xPos, idx;
  sprite_status *pMainwk, *pSubwk;

  pActwk->xposi.l += *(int*)&pActwk->actfree[4];

  xPos = pActwk->xposi.w.h - ((short*)pActwk)[24];
  if (xPos < 0) {
    xPos *= -1;
  }


  if ((long int)(int)xPos >= 80) {
    pActwk->xposi.l -= *(int*)&pActwk->actfree[4];
    *(int*)&pActwk->actfree[4] *= -1;
    pActwk->actflg ^= 1;
    pActwk->cddat ^= 1;
  }


  if (area(pActwk, &actwk[0], 65480, 112, 65456, 160) != 0) {



    pMainwk = &actwk[((short*)pActwk)[23]];

    idx = ((short*)pMainwk)[28];
    if (idx) {
      pSubwk = &actwk[idx];
      pSubwk->r_no0 = 4;
    }


    idx = ((short*)pMainwk)[27];
    if (idx) {
      pSubwk = &actwk[idx];
      pSubwk->r_no0 = 4;
    }
  }




  b_com1(pActwk);
}





void b_near(sprite_status* pActwk) {
  sprite_status *pMainwk, *pSubwk1, *pSubwk2;
  short idx, xwk, ywk;
  unsigned int flag1, flag2;
  int speedwk;

  idx = ((short*)pActwk)[23];
  pMainwk = &actwk[idx];

  if ((idx = ((short*)pMainwk)[28]) != 0) {
    pSubwk1 = &actwk[idx];

    if ((idx = ((short*)pMainwk)[27]) != 0) {
      pSubwk2 = &actwk[idx];
      flag1 = 0;

      xwk = (pSubwk1->xposi.w.h + pSubwk2->xposi.w.h >> 1) - scra_h_posit.w.h;


      if (xwk < 152) {

        pSubwk1->actflg |= 1;
        pSubwk2->actflg |= 1;
        pSubwk1->cddat |= 1;
        pSubwk2->cddat |= 1;

        if ((speedwk = *(int*)&pActwk->actfree[4]) < 0) {
          speedwk = -speedwk;
        }


        pSubwk1->xposi.l += speedwk;
        pSubwk2->xposi.l += speedwk;
      } else if (xwk > 168) {

        pSubwk1->actflg &= 254;
        pSubwk2->actflg &= 254;
        pSubwk1->cddat &= 254;
        pSubwk2->cddat &= 254;

        if ((speedwk = *(int*)&pActwk->actfree[4]) < 0) {
          speedwk = -speedwk;
        }


        pSubwk1->xposi.l -= speedwk;
        pSubwk2->xposi.l -= speedwk;
      } else {
        flag1 = 1;
      }


      flag2 = 0;

      ywk = (pSubwk1->yposi.w.h + pSubwk2->yposi.w.h >> 1) - scra_v_posit.w.h;


      if (ywk < 104) {

        if ((speedwk = *(int*)&pActwk->actfree[4]) < 0) {
          speedwk = -speedwk;
        }


        pSubwk1->yposi.l += speedwk;
        pSubwk2->yposi.l += speedwk;
      } else if (ywk > 120) {

        if ((speedwk = *(int*)&pActwk->actfree[4]) < 0) {
          speedwk = -speedwk;
        }


        pSubwk1->yposi.l -= speedwk;
        pSubwk2->yposi.l -= speedwk;
      } else {
        flag2 = 1;
      }


      if (flag1 != 0 && flag2 != 0) {
        pSubwk1->r_no0 = pSubwk2->r_no0 = 6;
      }


      b_com1(pActwk);
      return;
    }
  }


  pActwk->r_no0 += 2;
  b_fix(pActwk);
}





void b_fix(sprite_status* pActwk) {
  short hwk, vwk;

  pActwk->r_no0 += 2;
  pActwk->sprhs = pActwk->sprhsize = 12;
  pActwk->sprvsize = 20;
  pActwk->colino = 51;

  pActwk->actflg = 1;
  hwk = pActwk->xposi.w.h - scra_h_posit.w.h + 128;
  vwk = pActwk->yposi.w.h - scra_v_posit.w.h + 128;



  pActwk->xposi.w.h = hwk;
  pActwk->yposi.w.h = vwk;

  b_fix1(pActwk);
}





void b_fix1(sprite_status* pActwk) {
  patchg(pActwk, *(unsigned char***)&pActwk->actfree[8]);
  actionsub(pActwk);
}





void b_start(sprite_status* pActwk) {
  short xwk, ywk;

  pActwk->r_no0 += 2;
  pActwk->mstno.w = 511;

  pActwk->actflg = 4;


  xwk = pActwk->xposi.w.h - 128 + scra_h_posit.w.h;
  ywk = pActwk->yposi.w.h - 128 + scra_v_posit.w.h;

  pActwk->xposi.w.h = xwk;
  pActwk->yposi.w.h = ywk;

  b_com(pActwk);
}





void b_com(sprite_status* pActwk) {
  patchg(pActwk, *(unsigned char***)&pActwk->actfree[8]);
  b_com1(pActwk);
}





void b_com1(sprite_status* pActwk) {
  sprite_status* pMainwk;

  actionsub(pActwk);
  pMainwk = &actwk[((short*)pActwk)[23]];
  frameout_s(pActwk);

  if (!pActwk->actno) {
    b_die_v(pActwk, pMainwk);
  }
}





void b_kill_v(sprite_status* pActwk) {
  sprite_status* pMainwk;

  pMainwk = &actwk[((short*)pActwk)[23]];
  frameout(pActwk);
  b_die_v(pActwk, pMainwk);
}


void b_die_v(sprite_status* pActwk, sprite_status* pMainwk) {
  short idx;

  idx = ((short*)pMainwk)[28];
  if (idx == (short)(pActwk - actwk)) {
    ((short*)pMainwk)[28] = 0;
  } else {
    ((short*)pMainwk)[27] = 0;
  }
}





void b_light(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->mstno.w = 767;
  if (!pActwk->userflag.b.h) {
    b_make_c(pActwk);
  }


  b_com(pActwk);
}





void b_up(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->mstno.w = 1023;
  b_com(pActwk);
}





void b_up1(sprite_status* pActwk) {
  pActwk->yposi.w.h -= 2;
  if (!(pActwk->actflg & 128)) {
    if ((long int)(actwk[0].yposi.w.h - pActwk->yposi.w.h) > 160) {
      b_kill_v(pActwk);
      return;
    }
  }


  b_com(pActwk);
}





void b_make_c(sprite_status* pActwk) {
  short idx1, idx2, xPos, xWk, yPos, yWk;
  sprite_status *pMainwk, *pSubwk1, *pSubwk2, *pNewact;
  int i;

  pMainwk = &actwk[((short*)pActwk)[23]];
  idx1 = ((short*)pMainwk)[28];
  idx2 = ((short*)pMainwk)[27];
  if (!idx1 || !idx2) {

    return;
  }

  pSubwk1 = &actwk[idx1];
  pSubwk2 = &actwk[idx2];
  if (pActwk == pSubwk1) {




    if (!(pSubwk1->actflg & 128) || !(pSubwk2->actflg & 128)) {

      return;
    }

    xPos = pSubwk1->xposi.w.h;
    yPos = pSubwk1->yposi.w.h;
    xWk = pSubwk2->xposi.w.h;
    yWk = pSubwk2->yposi.w.h;
    xWk = xWk - xPos >> 2;
    yWk = yWk - yPos >> 2;
    yPos += 7;
    for (i = 0; i < 3; ++i) {
      if (actwkchk(&pNewact) != 0) return;



      ((short*)pNewact)[24] = pSubwk1 - actwk;

      ((short*)pNewact)[23] = pSubwk2 - actwk;

      pNewact->actno = pSubwk1->actno;
      pNewact->userflag.b.h = pSubwk1->userflag.b.h;
      pNewact->userflag.b.l = -2;
      pNewact->sproffset = pSubwk1->sproffset;
      xPos += xWk;
      yPos += yWk;
      pNewact->xposi.w.h = xPos;
      pNewact->yposi.w.h = yPos;
    }
  }

}








void c_init(sprite_status* pActwk) {
  pActwk->r_no0 += 2;
  pActwk->actflg |= 4;
  pActwk->sprpri = 2;
  pActwk->sprhs = pActwk->sprhsize = 12;
  pActwk->sprvsize = 12;
  pActwk->colino = 180;
  pActwk->patbase = pat_tama;
  c_move(pActwk);
}





void c_move(sprite_status* pActwk) {
  patchg(pActwk, pchg_tama);
  actionsub(pActwk);
}
























unsigned int area(sprite_status* pActwk, sprite_status* pPlayerwk, unsigned short Ypos, unsigned short Ylen, unsigned short Xpos, unsigned short Xlen) {
  unsigned short len;

  len = (unsigned short)pPlayerwk->yposi.w.h - (unsigned short)pActwk->yposi.w.h - Ypos;
  if (len >= Ylen) {
    return 0;
  }

  len = (unsigned short)pPlayerwk->xposi.w.h - (unsigned short)pActwk->xposi.w.h - Xpos;
  if (len >= Xlen) {
    return 0;
  }

  return 1;
}
