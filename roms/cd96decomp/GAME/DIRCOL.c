#include "EQU.h"
#include "DIRCOL.h"
#include "FCOL.h"






















unsigned int swap(int lSrc) {
  unsigned short iHi = (unsigned int)(lSrc & -65536) >> 16, iLow;
  iLow = lSrc & 65535;
  return (iHi << 16) | iLow;
}















short dircolm(sprite_status* pActwk, char* cpDirec) {
  return dircol(pActwk, cpDirec);
}

short dircol(sprite_status* pActwk, char* cpDirec) {
  unsigned char bDirwk, bDirSave;
  short iXposi, iYposi;
  int_union lXposi, lYposi;
  int_union iXspeed, iYspeed;

  lXposi.l = pActwk->xposi.l;
  lYposi.l = pActwk->yposi.l;
  iXspeed.l = pActwk->xspeed.w << 8;
  iYspeed.l = pActwk->yspeed.w << 8;
  lXposi.l += iXspeed.l;
  lYposi.l += iYspeed.l;

  iXposi = lXposi.w.h;
  iYposi = lYposi.w.h;

  bDirwk = *cpDirec;
  bDirSave = bDirwk;
  dirstk[0] = bDirwk;
  dirstk[2] = bDirwk;
  if ((char)(bDirwk + 32) < 0)
  {
    if ((char)bDirwk < 0) --bDirwk;
    bDirwk += 32;
  }
  else
  {
    if ((char)bDirwk < 0) ++bDirwk;
    bDirwk += 31;
  }


  bDirwk = bDirwk & 192;

  if (bDirwk == 0)
    return dircol_d3(pActwk, iXposi, iYposi);
  if (bDirwk == 128)
    return dircol_u3(pActwk, iXposi, iYposi);
  bDirSave &= 56;
  if (bDirSave == 0) iYposi += 8;
  if (bDirwk == 64)
    return dircol_l3(pActwk, iXposi, iYposi);

  return dircol_r3(pActwk, iXposi, iYposi);
}












short dircol2(sprite_status* pActwk, char* cpDirec) {
  short iDirect;
  short iD0, iD1, iD3;
  unsigned char bDirwk;

  dirstk[0] = *cpDirec;
  dirstk[2] = *cpDirec;
  *cpDirec = *cpDirec + 32;
  *cpDirec = *cpDirec & 192;
  bDirwk = *cpDirec;

  switch (bDirwk)
  {
    case 64:
      iDirect = dircol_l(pActwk, &iD0, &iD1, &iD3);
      break;
    case 128:
      iDirect = dircol_u(pActwk, &iD0, &iD1, &iD3);
      break;
    case 192:
      iDirect = dircol_r(pActwk, &iD0, &iD1, &iD3);
      break;
    default:
      iDirect = dircol_d(pActwk, &iD0, &iD1, &iD3);
      break;
  }
  return iDirect;
}


















short dircol_d(sprite_status* pActwk, short* ipD0, short* ipD1, short* ipD3) {
  short iXwork;
  short iYwork;
  char cDirect;
  char* cpDirStk;

  iYwork = pActwk->yposi.w.h + (short)pActwk->sprvsize;
  iXwork = pActwk->xposi.w.h + (short)pActwk->sprhs;
  cpDirStk = &dirstk[0];
  *ipD0 = scdchk(pActwk, iXwork, iYwork, 16, 0, 13, cpDirStk);


  iYwork = pActwk->yposi.w.h + pActwk->sprvsize;
  iXwork = pActwk->xposi.w.h - pActwk->sprhs;
  cpDirStk = &dirstk[2];
  *ipD1 = scdchk(pActwk, iXwork, iYwork, 16, 0, 13, cpDirStk);

  cDirect = 0;
  return dircolchk(ipD0, ipD1, ipD3, &cDirect);
}
















short dircol_d3(sprite_status* pActwk, short iXposi, short iYposi) {
  short iScd;
  char* cpDirStk = &dirstk[0];

  iYposi += 10;
  iScd = scdchk(pActwk, iXposi, iYposi, 16, 0, 14, cpDirStk);
  dircolchk1(0);
  return iScd;
}


















short dircol_r(sprite_status* pActwk, short* ipD0, short* ipD1, short* ipD3) {
  short iXwork;
  short iYwork;
  char cDirect;
  char* cpDirStk;

  iYwork = pActwk->yposi.w.h - (short)pActwk->sprhs;
  iXwork = pActwk->xposi.w.h + (short)pActwk->sprvsize;
  cpDirStk = &dirstk[0];
  *ipD0 = scdchk_r(pActwk, iXwork, iYwork, 16, 0, 14, cpDirStk);


  iYwork = pActwk->yposi.w.h + (short)pActwk->sprhs;
  iXwork = pActwk->xposi.w.h + (short)pActwk->sprvsize;
  cpDirStk = &dirstk[2];
  *ipD1 = scdchk_r(pActwk, iXwork, iYwork, 16, 0, 14, cpDirStk);

  cDirect = -64;
  return dircolchk(ipD0, ipD1, ipD3, &cDirect);
}











short dircol_r2(sprite_status* pActwk) {
  return dircol_r3(pActwk, pActwk->xposi.w.h, pActwk->yposi.w.h);
}
















short dircol_r3(sprite_status* pActwk, short iXposi, short iYposi) {
  short iScd = 0;
  char* cpDirStk = &dirstk[0];

  iXposi += 10;
  iScd = scdchk_r(pActwk, iXposi, iYposi, 16, 0, 14, cpDirStk);
  dircolchk1(-64);
  return iScd;
}



















short dircol_l(sprite_status* pActwk, short* ipD0, short* ipD1, short* ipD3) {
  short iXwork;
  short iYwork;
  char cDirect;
  char* cpDirstk;

  iYwork = pActwk->yposi.w.h - (short)pActwk->sprhs;
  iXwork = (pActwk->xposi.w.h - (short)pActwk->sprvsize) ^ 15;
  cpDirstk = &dirstk[0];
  *ipD0 = scdchk_r(pActwk, iXwork, iYwork, -16, 2048, 14, cpDirstk);


  iYwork = pActwk->yposi.w.h + (short)pActwk->sprhs;
  iXwork = (pActwk->xposi.w.h - (short)pActwk->sprvsize) ^ 15;
  cpDirstk = &dirstk[2];
  *ipD1 = scdchk_r(pActwk, iXwork, iYwork, -16, 2048, 14, cpDirstk);

  cDirect = 64;
  return dircolchk(ipD0, ipD1, ipD3, &cDirect);
}











short dircol_l2(sprite_status* pActwk) {
  return dircol_l3(pActwk, pActwk->xposi.w.h, pActwk->yposi.w.h);
}
















short dircol_l3(sprite_status* pActwk, short iXposi, short iYposi) {
  char* cpDirStk = &dirstk[0];
  short iScd;

  iXposi = (iXposi - 10) ^ 15;
  iScd = scdchk_r(pActwk, iXposi, iYposi, -16, 2048, 14, cpDirStk);
  dircolchk1(64);
  return iScd;
}


















short dircol_u(sprite_status* pActwk, short* ipD0, short* ipD1, short* ipD3) {
  short iXwork;
  short iYwork;
  char cDirect;
  char* cpDirStk;

  iYwork = (pActwk->yposi.w.h - (short)pActwk->sprvsize) ^ 15;
  iXwork = pActwk->xposi.w.h + (short)pActwk->sprhs;
  cpDirStk = &dirstk[0];
  *ipD0 = scdchk(pActwk, iXwork, iYwork, -16, 4096, 14, cpDirStk);


  iYwork = (pActwk->yposi.w.h - (short)pActwk->sprvsize) ^ 15;
  iXwork = pActwk->xposi.w.h - (short)pActwk->sprhs;
  cpDirStk = &dirstk[2];
  *ipD1 = scdchk(pActwk, iXwork, iYwork, -16, 4096, 14, cpDirStk);

  cDirect = -128;
  return dircolchk(ipD0, ipD1, ipD3, &cDirect);
}











short dircol_u2(sprite_status* pActwk) {
  return dircol_u3(pActwk, pActwk->xposi.w.h, pActwk->yposi.w.h);
}
















short dircol_u3(sprite_status* pActwk, short iXposi, short iYposi) {
  short iScd;
  char* cpDirStk = &dirstk[0];

  iYposi = (iYposi - 10) ^ 15;
  iScd = scdchk(pActwk, iXposi, iYposi, -16, 4096, 14, cpDirStk);
  dircolchk1(-128);
  return iScd;
}











short emycol_u(sprite_status* pActwk) {
  short iXwork, iYwork, iScd;
  char* cpDirStk = &dirstk[0];

  iYwork = (pActwk->yposi.w.h - pActwk->sprvsize) ^ 15;
  iXwork = pActwk->xposi.w.h;
  iScd = scdchk(pActwk, iXwork, iYwork, -16, 4096, 14, cpDirStk);


  return iScd;
}











short emycol_d(sprite_status* pActwk) {
  return emycol_d2(pActwk, pActwk->xposi.w.h);
}











short emycol_d2(sprite_status* pActwk, short iXposi) {
  short iYposi;

  iYposi = pActwk->yposi.w.h + (short)(char)pActwk->sprvsize;
  return emycol_d3(pActwk, iXposi, iYposi);
}












short emycol_d3(sprite_status* pActwk, short iXposi, short iYposi) {
  short iScd;
  char* cpDirStk = &dirstk[0];

  *cpDirStk = 0;
  iScd = scdchk(pActwk, iXposi, iYposi, 16, 0, 13, cpDirStk);


  return iScd;
}












short emycol_l(sprite_status* pActwk, unsigned char sprhs) {
  short iXwork;
  char cSprhs;

  cSprhs = sprhs;
  iXwork = pActwk->xposi.w.h + (short)cSprhs;
  return emycol_l3(pActwk, iXwork, pActwk->yposi.w.h);
}













short emycol_l3(sprite_status* pActwk, short iXposi, short iYposi) {
  short iScd;
  char* cpDirStk = &dirstk[0];

  *cpDirStk = 0;
  iScd = scdchk_r(pActwk, iXposi, iYposi, -16, 2048, 14, cpDirStk);


  return iScd;
}











short emycol_r(sprite_status* pActwk, unsigned char sprhs) {
  short iXwork;
  char cSprhs;

  cSprhs = sprhs;
  iXwork = pActwk->xposi.w.h + (short)cSprhs;
  return emycol_r3(pActwk, iXwork, pActwk->yposi.w.h);
}












short emycol_r3(sprite_status* pActwk, short iXposi, short iYposi) {
  short iScd;
  char* cpDirStk = &dirstk[0];

  iScd = scdchk_r(pActwk, iXposi, iYposi, 16, 0, 14, cpDirStk);


  return iScd;
}



















short dircolchk(short* ipD0, short* ipD1, short* ipD3, char* cpDirec) {
  short iWork;


  if (*ipD1 > *ipD0)
  {
    iWork = *ipD1;
    *ipD1 = *ipD0;
    *ipD0 = iWork;
    *ipD3 = dirstk[0];
  }
  else
    *ipD3 = dirstk[2];

  if (*ipD3 & 1)
    *ipD3 = *cpDirec;
  return *ipD1;
}











short dircolchk1(char cDirec) {
  char cDirWk = dirstk[0];

  if (cDirWk & 1) cDirWk = cDirec;
  return cDirWk;
}
