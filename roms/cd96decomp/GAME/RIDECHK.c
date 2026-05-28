#include "EQU.h"
#include "RIDECHK.h"
#include "DIRCOL.h"
#include "LOADER2.h"

extern short playdieset(sprite_status* pActwk);



























































short ride_on_clr(sprite_status* pActwk, sprite_status* pPlayerwk) {
  unsigned short wActwkNo;
  unsigned char byPlwk;

  if (!(pActwk->cddat & 8))
    return -1;
  if (!(pPlayerwk->cddat & 8))
    return -1;

  wActwkNo = pPlayerwk->actfree[19];

  if ((unsigned short)(pActwk - actwk) != wActwkNo)
    return -1;

  if (pPlayerwk->actfree[0] != 0)
    soundset(171);

  pPlayerwk->actfree[14] = 0;
  pPlayerwk->cddat |= 2;
  pPlayerwk->cddat &= 247;
  pActwk->cddat &= 247;
  byPlwk = pPlayerwk->actfree[2];
  if (!(byPlwk & 64))
    if (pPlayerwk->mstno.b.h != 23)
      byPlwk &= 254;

  pPlayerwk->actfree[2] = byPlwk;
  pPlayerwk->actfree[19] = 0;
  if (pPlayerwk->mstno.b.h == 43)
    pPlayerwk->cddat &= 253;
  return 0;
}














short ride_on_set(sprite_status* pActwk, sprite_status* pPlayerwk) {
  unsigned char byCCR;
  unsigned short wActwkNo;
  sprite_status* pRideAct;

  if (pPlayerwk->r_no0 == 4)
  {
    pPlayerwk->r_no0 -= 2;
    ((short*)pPlayerwk)[26] = 120;
  }

  pActwk->r_no1 = 0;
  pPlayerwk->actfree[18] = 0;

  if (!(pActwk->cddat & 8)) byCCR = 0;
  else byCCR = 1;
  pActwk->cddat |= 8;
  if (byCCR == 0)
  {
    if (pPlayerwk->mstno.b.h == 43)
    {
      pActwk->cddat &= 247;
      return ride_on_clr(pActwk, pPlayerwk);
    }



    pPlayerwk->cddat &= 239;
    if (!(pPlayerwk->cddat & 4)) byCCR = 0;
    else byCCR = 1;
    pPlayerwk->cddat &= 251;
    if (byCCR == 1)
    {
      if (chibi_flag != 0)
      {
        pPlayerwk->sprvsize = 10;
        pPlayerwk->sprhs = 5;
        pPlayerwk->yposi.w.h -= 2;
      }
      else
      {

        pPlayerwk->sprvsize = 19;
        pPlayerwk->sprhs = 9;
        pPlayerwk->yposi.w.h -= 5;
      }

      pPlayerwk->mstno.b.h = 0;
    }
  }


  if (!(pPlayerwk->cddat & 8)) byCCR = 0;
  else byCCR = 1;
  pPlayerwk->cddat |= 8;
  if (byCCR == 1)
  {
    wActwkNo = pPlayerwk->actfree[19];
    if ((unsigned short)(pActwk - actwk) == wActwkNo)
      return -1;
    pRideAct = &actwk[wActwkNo];
    pRideAct->cddat &= 247;
  }

  pPlayerwk->actfree[19] = pActwk - actwk;
  pPlayerwk->direc.w = 0;
  pPlayerwk->yspeed.w = 0;

  if (pActwk->actno != 10 || pActwk->r_no0 != 2)
    pPlayerwk->mspeed.w = pPlayerwk->xspeed.w;

  pPlayerwk->cddat &= 253;
  return 0;
}















short hitchk_u(sprite_status* pActwk, sprite_status* pPlayerwk) {
  pActwk->r_no1 = 2;
  return ride_on_chk(pActwk, pPlayerwk);
}















short ridechk(sprite_status* pActwk, sprite_status* pPlayerwk) {
  pActwk->r_no1 = 1;
  return ride_on_chk(pActwk, pPlayerwk);
}













short ride_on_chk(sprite_status* pActwk, sprite_status* pPlayerwk) {
  return hitchk(pActwk, pPlayerwk);
}



short hitchk(sprite_status* pActwk, sprite_status* pPlayerwk) {
  short iD0, iD1, iD2;
  unsigned char byPlflg;

  if (pPlayerwk->mstno.b.h == 23)
    return hit_e(pActwk, pPlayerwk);
  byPlflg = pPlayerwk->actfree[2];
  if (byPlflg & 64)
    return hit_e(pActwk, pPlayerwk);
  if (pPlayerwk->r_no0 >= 6)
    return hit_e(pActwk, pPlayerwk);
  if (pPlayerwk->actno == 0)
    return hit_e(pActwk, pPlayerwk);
  if (!(pActwk->actflg & 128))
    return hit_e(pActwk, pPlayerwk);
  if (editmode.b.h != 0)
    return hit_e(pActwk, pPlayerwk);

  iD1 = (short)pActwk->sprhsize + 10;
  iD0 = pPlayerwk->xposi.w.h - pActwk->xposi.w.h;
  iD0 += iD1;
  if (iD0 < 0)
    return hit_e(pActwk, pPlayerwk);

  iD2 = iD1;
  iD2 += iD2;
  if ((unsigned short)iD0 >= (unsigned short)iD2)
    return hit_e(pActwk, pPlayerwk);

  if (pPlayerwk->mstno.b.h == 43)
  {
    if (pActwk->cddat & 8)
      return hit_v(pActwk, pPlayerwk, iD0, iD1);
    else
      return hit_e(pActwk, pPlayerwk);
  }

  if (pActwk->r_no1 != 1)
    return hit_v(pActwk, pPlayerwk, iD0, iD1);
  if (pPlayerwk->yspeed.w == 0)
    return hit_v(pActwk, pPlayerwk, iD0, iD1);
  if (pPlayerwk->yspeed.w < 0)
    return hit_e(pActwk, pPlayerwk);

  return hit_v(pActwk, pPlayerwk, iD0, iD1);
}
















short hit_v(sprite_status* pActwk, sprite_status* pPlayerwk, short iHitXs, short iHitHs) {
  short iHitYs;
  short iHitVs;
  short iD4, iD5;
  short iwk;

  if (pActwk->actno == 25 && actwk[0].cddat & 4)
    iwk = -2;
  else
    iwk = 2;


  iHitVs = (short)pActwk->sprvsize + (short)pPlayerwk->sprvsize + iwk;







  iHitYs = pPlayerwk->yposi.w.h - pActwk->yposi.w.h;
  iHitYs += iHitVs;
  if (iHitYs < 0)
    return hit_e(pActwk, pPlayerwk);
  iD4 = iHitVs + iHitVs;
  if (iHitYs >= iD4)
    return hit_e(pActwk, pPlayerwk);

  iD4 = iHitXs;
  if (iHitHs < iHitXs)
  {
    iHitHs += iHitHs;
    iHitXs -= iHitHs;
    iD4 = -iHitXs;
  }


  iD5 = iHitYs;
  if (iHitVs < iHitYs)
  {
    iHitVs += iHitVs;
    iHitYs -= iHitVs;
    iD5 = -iHitYs;
  }

  if (iD5 < iD4)
    return hit_y(pActwk, pPlayerwk, iHitYs);

  return hit_x(pActwk, pPlayerwk, iHitXs, iD5);
}


















short hit_x(sprite_status* pActwk, sprite_status* pPlayerwk, short iHitXs, short iD5) {
  if (pActwk->r_no1 == 1)
    return hit_e(pActwk, pPlayerwk);
  if (pActwk->actno == 10)
    if (pPlayerwk->cddat & 2)
    return hit_e(pActwk, pPlayerwk);

  if ((unsigned short)iD5 < 5)
    return hit_e(pActwk, pPlayerwk);
  hit_set(pActwk, pPlayerwk);
  ride_on_clr(pActwk, pPlayerwk);
  pActwk->r_no1 = 0;
  pPlayerwk->xposi.w.h -= iHitXs;
  if (iHitXs >= 0)
  {

    if (pPlayerwk->xspeed.w > 0)
      return push_set(pActwk, pPlayerwk);
    else
      return push_clr(pActwk, pPlayerwk);
  }



  if (pPlayerwk->xspeed.w >= 0)
    return push_clr(pActwk, pPlayerwk);
  else
    return push_set(pActwk, pPlayerwk);

}














short push_set(sprite_status* pActwk, sprite_status* pPlayerwk) {
  side_coli(pActwk, pPlayerwk);
  if (!(pPlayerwk->cddat & 2))
  {
    pActwk->cddat |= 32;
    pPlayerwk->cddat |= 32;
    pPlayerwk->mspeed.w = 0;
  }

  pPlayerwk->xspeed.w = 0;
  return 0;
}















short push_clr(sprite_status* pActwk, sprite_status* pPlayerwk) {
  hit_clr(pActwk, pPlayerwk);
  side_coli(pActwk, pPlayerwk);
  pActwk->cddat &= 223;
  pPlayerwk->cddat &= 223;
  return 0;
}
















short hit_y(sprite_status* pActwk, sprite_status* pPlayerwk, short iHitYs) {
  short iSprVchk;
  short iDirCol;
  short iD0, iD1, iD3;
  char cDirec;
  int lXspeed, lYspeed;

  if (pActwk->actno == 25 && pPlayerwk->cddat & 4)
    return hit_e(pActwk, pPlayerwk);

  iSprVchk = pActwk->sprvsize;
  iSprVchk += pPlayerwk->sprvsize;

  if (iHitYs != 0)
    if (iHitYs < 0)
      return hit_yu(pActwk, pPlayerwk, iHitYs);



  if (pPlayerwk->mstno.b.h != 43)
    if (pPlayerwk->yspeed.w != 0)
      if (pPlayerwk->yspeed.w < 0) return hit_e(pActwk, pPlayerwk);

  pPlayerwk->yposi.w.h = pActwk->yposi.w.h;
  pPlayerwk->yposi.w.h -= iSprVchk;
  lXspeed = pActwk->xspeed.w;
  lXspeed = lXspeed << 8;
  pPlayerwk->xposi.l += lXspeed;

  cDirec = -64;
  if (pActwk->xspeed.w < 0)
    cDirec = -cDirec;
  if (pActwk->xspeed.w != 0)
  {


    iDirCol = dircolm(pPlayerwk, &cDirec);
    if (iDirCol < 0)
    {
      if (pActwk->xspeed.w < 0)
        iDirCol *= -1;
      pPlayerwk->xposi.w.h += iDirCol;
    }
  }



  lYspeed = pActwk->yspeed.w << 8;
  pPlayerwk->yposi.l += lYspeed;

  if (pActwk->actno != 10)
  {
    if (pActwk->yspeed.w >= 0)
    {
      iDirCol = dircol_d(pPlayerwk, &iD0, &iD1, &iD3);
      if (iDirCol < 0)
      {
        pPlayerwk->yposi.w.h += iDirCol;
        return hit_e(pActwk, pPlayerwk);
      }
    }

    if (pActwk->yspeed.w < 0)
    {
      iDirCol = dircol_u2(pPlayerwk);
      if (iDirCol < 0)
      {
        playdieset(pPlayerwk);
        return hit_e(pActwk, pPlayerwk);
      }
    }
  }

  ride_on_set(pActwk, pPlayerwk);
  return 1;
}















short hit_yu(sprite_status* pActwk, sprite_status* pPlayerwk, short iHitYs) {
  if (pActwk->r_no1 == 1)
    return hit_e(pActwk, pPlayerwk);
  if (pActwk->actno == 9)
    return hit_e(pActwk, pPlayerwk);
  if (pActwk->actno != 10)
    return hit_yu1(pActwk, pPlayerwk, iHitYs);
  if (pActwk->r_no1 == 2)
    return hit_yu0(pActwk, pPlayerwk, iHitYs);
  if (pActwk->actflg & 2)
    return hit_yu0(pActwk, pPlayerwk, iHitYs);

  return hit_e(pActwk, pPlayerwk);
}















short hit_yu1(sprite_status* pActwk, sprite_status* pPlayerwk, short iHitYs) {
  if (pPlayerwk->cddat & 2)
    return hit_yu0(pActwk, pPlayerwk, iHitYs);
  if (pActwk->yspeed.w <= 0)
    return hit_yu0(pActwk, pPlayerwk, iHitYs);
  playdieset(pPlayerwk);
  return hit_yu0(pActwk, pPlayerwk, iHitYs);
}















short hit_yu0(sprite_status* pActwk, sprite_status* pPlayerwk, short iHitYs) {/* Line 610, Address: 0x101a900 */
  pPlayerwk->yposi.w.h -= iHitYs;/* Line 611, Address: 0x101a914 */
  pPlayerwk->yspeed.w = 0;/* Line 612, Address: 0x101a928 */
  hit_clr(pActwk, pPlayerwk);/* Line 613, Address: 0x101a930 */
  ride_on_clr(pActwk, pPlayerwk);/* Line 614, Address: 0x101a940 */
  pActwk->r_no1 = 0;/* Line 615, Address: 0x101a950 */
  return 1;/* Line 616, Address: 0x101a958 */
}/* Line 617, Address: 0x101a95c */














short hit_e(sprite_status* pActwk, sprite_status* pPlayerwk) {
  hit_clr(pActwk, pPlayerwk);
  ride_on_clr(pActwk, pPlayerwk);
  pActwk->r_no1 = 0;
  return 0;
}














void side_coli(sprite_status* pActwk, sprite_status* pPlayerwk) {
  char cDirect = -64;
  short iDirCol;

  if (pActwk->xspeed.w == 0) return;

  if (pActwk->actno == 10) return;

  if (pActwk->xspeed.w < 0)
    cDirect = -cDirect;

  iDirCol = dircol(pPlayerwk, &cDirect);
  if (iDirCol >= 0) return;

  playdieset(pPlayerwk);
}














void hit_set(sprite_status* pActwk, sprite_status* pPlayerwk) {
  short iHitActno;
  sprite_status* pHitAct;

  if (pActwk->actno == 10)
  {
    pPlayerwk->colino = 0;
    return;
  }

  iHitActno = (unsigned short)pPlayerwk->colino;
  if (iHitActno != 0)
  {
    pHitAct = &actwk[iHitActno];
    if (pHitAct == pActwk) return;

    if (pActwk->xspeed.w == 0 && pHitAct->xspeed.w == 0) return;


    if (pPlayerwk->xposi.w.h >= pActwk->xposi.w.h && pPlayerwk->xposi.w.h >= pHitAct->xposi.w.h) return;




    if (pActwk->actno == 21) return;


    if (stageno_i.b.h == 2 && stageno_i.b.l == 0 && (time_flag_i & 0x7F) == 1 && pActwk->actno == 40 && pHitAct->actno == 39) return;


    if (stageno.w == 768 && pActwk->actno == 39 && pHitAct->actno == 39) return;



    playdieset(pPlayerwk);
    return;
  }

  pPlayerwk->colino = pActwk - actwk;
}














void hit_clr(sprite_status* pActwk, sprite_status* pPlayerwk) {
  unsigned short iHitAct;

  iHitAct = pPlayerwk->colino;
  if (pActwk == &actwk[iHitAct]) return;

  pPlayerwk->colino = 0;
}
