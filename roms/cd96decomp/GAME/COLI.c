#include "EQU.h"
#include "COLI.h"
#include "ACTSET.h"
#include "FCOL.h"
#include "LOADER2.h"
#include "PLAYER.h"
#include "PLAYSUB.h"
#include "SCORE.h"

extern unsigned char z1colitbl[64][2];
extern unsigned char z3colitbl[64][2];
extern unsigned char z4colitbl[64][2];
extern unsigned char z5colitbl[64][2];
extern unsigned char z6colitbl[64][2];
extern unsigned char z7colitbl[64][2];
extern unsigned char z8colitbl[64][2];

static short CollitblDataXchk(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iYposi, short iD5);
static short CollitblDataYchk(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iYposi, short iColiNo, short iD5);
static short ColliHitChk(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iChkPosi, short iD5);
static short pcolitem(sprite_status* pActwk, sprite_status* pColliAct);
static short pcolnomal(sprite_status* pActwk, sprite_status* pColliAct);
static short pcolplay2(sprite_status* pActwk, sprite_status* pColliAct);
static short pcolplay(sprite_status* pActwk, sprite_status* pColliAct);
static void playdamagechk(sprite_status* pActwk, sprite_status* pColliAct);
static short pcolspecial(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iChkPosi, short iD5);
static short eggman_chk(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo);
static short z3_eggman_chk(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo);
static short yago(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iChkPosi, short iD5);
static void boss_1(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo);
static void boss_4(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo);
static void boss_5(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo);
static short main_attack(sprite_status* pActwk, sprite_status* pColliAct);

unsigned short escoretbl[4] = { 10, 20, 50, 100 };
unsigned char (*colitbls[7])[2] = {
  z1colitbl,
  z3colitbl,
  z4colitbl,
  z5colitbl,
  z6colitbl,
  z7colitbl,
  z8colitbl
};
static unsigned char bCarry;


short pcol(sprite_status* pActwk) {
  short iXwork = pActwk->xposi.w.h,
        iYwork = pActwk->yposi.w.h,
        iSprvs = pActwk->sprvsize - 3;
  short iXcollichk = 16;
  short i, iRet, iColino;
  sprite_status* pColliAct;

  if ((stageno_i.b.h == 1 && (pActwk->actfree[2] & 64)) || (stageno_i.b.h == 6 && (pActwk->actfree[2] & 1)))
    return 0;

  iXwork -= 8;
  iYwork -= iSprvs;

  if (pActwk->patno == 57) {
    iYwork += 12;
    iSprvs = 10;
  }

  iXcollichk = 16;
  iSprvs += iSprvs;

  pColliAct = &actwk[32];

  for (i = 0; i < 96; ++i, ++pColliAct) {
    if (pColliAct->actflg & 128) {
      iColino = pColliAct->colino;
      if (iColino != 0) {
        iRet = CollitblDataXchk(pActwk, pColliAct, iXwork, iYwork, iSprvs);
        if (iRet == -1)
          return iRet;
      }
    }
  }
  iColino = 0;
  return iColino;
}


static short CollitblDataXchk(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iYposi, short iD5) {
  short iColiNo = pColliAct->colino;
  short iColiwk;
  short iColiData;

  iColiNo = (iColiNo & 63) - 1;
  iColiData = colitbls[stageno_i.b.h][iColiNo][0];

  iColiwk = pColliAct->xposi.w.h - iColiData;
  bCarry = CCset(iColiwk, iXposi);
  iColiwk = iColiwk - iXposi;

  if (bCarry == 1)
  {
    iColiData += iColiData;
    bCarry = CSset(iColiwk, iColiData);
    iColiwk += iColiData;
    if (bCarry == 1)
      return CollitblDataYchk(pActwk, pColliAct, iXposi, iYposi, iColiNo, iD5);
    else
      return 0;
  }

  if (iColiwk > 16)
    return 0;

  return CollitblDataYchk(pActwk, pColliAct, iXposi, iYposi, iColiNo, iD5);
}


static short CollitblDataYchk(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iYposi, short iColiNo, short iD5) {
  short iColiData;
  short iYwork;

  iColiData = colitbls[stageno_i.b.h][iColiNo][1];

  iYwork = pColliAct->yposi.w.h - iColiData;
  bCarry = CCset(iYwork, iYposi);
  iYwork = iYwork - iYposi;
  if (bCarry == 1) {
    iColiData += iColiData;
    bCarry = CSset(iColiData, iYwork);
    iColiData += iYwork;
    if (bCarry == 1)
      return ColliHitChk(pActwk, pColliAct, iXposi, iYwork, iD5);
    else
      return 0;
  }

  if (iYwork > iD5)
    return 0;

  return ColliHitChk(pActwk, pColliAct, iXposi, iYwork, iD5);
}


static short ColliHitChk(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iChkPosi, short iD5) {
  unsigned char iColino = pColliAct->colino & 192;

  if (iColino == 0) {
    pcolnomal(pActwk, pColliAct);
    return 1;
  }
  if (iColino == 192) {
    pcolspecial(pActwk, pColliAct, iXposi, iChkPosi, iD5);
    return 1;
  }
  if ((char)iColino < 0) {
    if (stageno_i.b.h == 6 && plpower_m) {
      return 0;
    }
    pcolplay(pActwk, pColliAct);
    return 1;
  }

  return pcolitem(pActwk, pColliAct);
}


static short pcolitem(sprite_status* pActwk, sprite_status* pColliAct) {
  short iD0;

  if (stageno_i.b.h == 6 && ((prio_flag && !pColliAct->userflag.b.l) || (!prio_flag && pColliAct->userflag.b.l))) {
    return -1;
  }
  if ((pColliAct->colino & 63) != 6) {
    if (((unsigned short*)pActwk)[26] < 90)
      pColliAct->r_no0 += 2;
  }
  else {
    if (pActwk->yspeed.w < 0) {
      iD0 = pActwk->yposi.w.h - 16;
      bCarry = CCset(iD0, pColliAct->yposi.w.h);
      if (bCarry == 0) {
        pActwk->yspeed.w = -pActwk->yspeed.w;
        pColliAct->yspeed.w = -384;
        if (pColliAct->r_no1 == 0)
          pColliAct->r_no1 += 4;
      }
    }
    else {
      if (pActwk->mstno.b.h == 2) {
        pActwk->yspeed.w = -pActwk->yspeed.w;
        pColliAct->r_no0 += 2;
      }
    }
  }
  return -1;
}


static short pcolnomal(sprite_status* pActwk, sprite_status* pColliAct) {
  short iScoreCntwk;
  short iScoreData;

  if (plpower_a == 0 && plpower_m == 0 && pActwk->mstno.b.h != 2) {
    pcolplay(pActwk, pColliAct);
    return -1;
  }

  if (pColliAct->colicnt != 0) {
    pActwk->xspeed.w = -pActwk->xspeed.w;
    pActwk->yspeed.w = -pActwk->yspeed.w;
    pActwk->xspeed.w /= 2;
    pActwk->yspeed.w /= 2;
    pColliAct->colino = 0;
    --pColliAct->colicnt;
    if (pColliAct->colicnt == 0)
      pColliAct->cddat |= 128;
  }
  else {
    pColliAct->cddat |= 128;
    iScoreCntwk = emyscorecnt;
    emyscorecnt += 2;
    if ((unsigned short)iScoreCntwk >= 6)
      iScoreCntwk = 6;

    ((short*)pColliAct)[33] = iScoreCntwk;
    iScoreData = escoretbl[iScoreCntwk / 2];
    if (emyscorecnt >= 32) {
      iScoreData = 1000;
      ((short*)pColliAct)[33] = 10;
    }

    scoreup(iScoreData);
    soundset(150);
    pColliAct->actno = 24;
    pColliAct->r_no0 = 0;
    pColliAct->userflag.b.h = 1;

    if (pActwk->yspeed.w >= 0) {
      if (pActwk->yposi.w.h < pColliAct->yposi.w.h)
        pActwk->yspeed.w = -pActwk->yspeed.w;
      else
        pActwk->yspeed.w -= 256;
    }
    else
      pActwk->yspeed.w += 256;
  }
  return -1;
}


static short pcolplay2(sprite_status* pActwk, sprite_status* pColliAct) {
  pColliAct->cddat |= 128;
  return pcolplay(pActwk, pColliAct);
}


static short pcolplay(sprite_status* pActwk, sprite_status* pColliAct) {
  if (stageno_i.b.h == 6 && ((pActwk->actfree[2] & 1) || plpower_a || plpower_m)) {
    return -1;
  }
  if (plpower_m == 0)
    return pcole(pActwk, pColliAct);

  return -1;
}


short pcole(sprite_status* pActwk, sprite_status* pColliAct) {
  if (((unsigned short*)pActwk)[26] != 0)
    return -1;

  return playdamageset(pActwk, pColliAct);
}


static void playdamagechk(sprite_status* pActwk, sprite_status* pColliAct) {
  if (stageno_i.b.h != 4) {
    pActwk->actfree[0] = 0;
  }
  if (!(plpower_b & 1))
    conbine_flag = 0;
  plpower_b &= 254;

  pActwk->r_no0 = 4;
  jumpcolsub();
  pActwk->cddat |= 2;

  if (pActwk->cddat & 64) {
    pActwk->yspeed.w = -512;
    pActwk->xspeed.w = -256;
  }
  else {
    pActwk->yspeed.w = -1024;
    pActwk->xspeed.w = -512;
  }

  if ((unsigned short)pColliAct->xposi.w.h <= (unsigned short)pActwk->xposi.w.h)
    pActwk->xspeed.w = -pActwk->xspeed.w;

  pActwk->mspeed.w = 0;
  pActwk->mstno.b.h = 26;
  ((short*)pActwk)[26] = 120;
}


short playdamageset(sprite_status* pActwk, sprite_status* pColliAct) {
  sprite_status* pFreeAct;
  int iRet;

  if (stageno_i.b.h == 4) {
    pActwk->actfree[0] = 0;
    pActwk->actfree[2] &= 231;
    ((short*)pActwk)[33] = 0;
  }

  if (plpower_b != 0) {
    playdamagechk(pActwk, pColliAct);
    return -1;
  }
  if (plring != 0) {
    iRet = actwkchk(&pFreeAct);
    if (iRet == 0) {
      pFreeAct->actno = 17;
      pFreeAct->xposi.w.h = pActwk->xposi.w.h;
      pFreeAct->yposi.w.h = pActwk->yposi.w.h;

      if (stageno_i.b.h == 6 && prio_flag) {
        pFreeAct->userflag.b.l = 1;
      }
    }

    playdamagechk(pActwk, pColliAct);
    return -1;
  }

  if (debugflag.w != 0) {
    playdamagechk(pActwk, pColliAct);
    return -1;
  }
  return playdieset(pActwk);
}


short playdieset(sprite_status* pActwk) {
  if (editmode.w != 0)
    return -1;
  plpower_m = 0;
  pActwk->r_no0 = 6;
  jumpcolsub();
  pActwk->cddat |= 2;
  pActwk->yspeed.w = -1792;
  pActwk->xspeed.w = 0;
  pActwk->mspeed.w = 0;
  ((short*)pActwk)[30] = pActwk->yposi.w.h;
  pActwk->mstno.b.h = 24;
  pActwk->sproffset |= 32768;
  pActwk->sprpri = 0;
  soundset(147);
  return -1;
}


static short pcolspecial(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iChkPosi, short iD5) {
  unsigned char flgwk;
  char cColiNo = pColliAct->colino & 63;

  switch (stageno_i.b.h) {
    case 0:
      switch (cColiNo) {
        case 11:
          pcolplay2(pActwk, pColliAct);
          break;
        case 12:
          yago(pActwk, pColliAct, iXposi, iChkPosi, iD5);
          break;
        case 23:
        case 33:
        case 31:
        case 35:
          ++pColliAct->colicnt;
          break;
        case 47:
        case 58:
        case 59:
          main_attack(pActwk, pColliAct);
          break;
        default:
          if (cColiNo < 60) return -1;
          if (cColiNo > 63) return -1;
          eggman_chk(pActwk, pColliAct, cColiNo);
      }
      break;
    case 1:
      switch (cColiNo) {
        case 23:
        case 31:
        case 35:
        case 39:
          ++pColliAct->colicnt;
          break;
        case 58:
        case 59:
          main_attack(pActwk, pColliAct);
          break;
        default:
          z3_eggman_chk(pActwk, pColliAct, cColiNo);
          break;
      }
      break;
    case 2:
      switch (cColiNo) {
        case 31:
        case 35:
          ++pColliAct->colicnt;
          goto label1;
        case 51:
        case 58:
        case 59:
          main_attack(pActwk, pColliAct);
          goto label1;
      }

      switch (bossstart) {
        case 0:
          return -1;
        case 1:
          if (cColiNo < 60) return -1;
          if (cColiNo > 63) return -1;
          eggman_chk(pActwk, pColliAct, cColiNo);
          goto label1;
        case 4:
          if (cColiNo == 63) {
            if (pActwk->cddat & 20) {
              pActwk->cddat &= 251;
              pActwk->cddat &= 239;
              pColliAct->colino = 0;
              pActwk->mstno.b.h = 21;
              soundset(173);
              plairset();
              pActwk->yspeed.w = 1024;
              pActwk->xspeed.w = -512;
              if (pActwk->xposi.w.h >= pColliAct->xposi.w.h) {
                pActwk->xspeed.w *= -1;
              }
            }
          }
          else if (cColiNo == 62) {
            pcolplay(pActwk, pColliAct);
            ++pColliAct->colicnt;
          }
          else {
            return -1;
          }
          break;
        case 5:
          if (cColiNo == 61) {
            pcolplay(pActwk, pColliAct);
            ++pColliAct->colicnt;
          }
          break;
      }
      break;
    case 3:
      switch (cColiNo) {
        case 31:
        case 35:
        case 55:
          ++pColliAct->colicnt;
          goto label1;
        case 56:
          ++pColliAct->colicnt;
          pcolplay(pActwk, pColliAct);
          goto label1;
        case 46:
        case 58:
        case 59:
        case 60:
          main_attack(pActwk, pColliAct);
          goto label1;
      }

      switch (bossstart) {
        case 0: return -1;
        case 4:
          if (cColiNo == 63) {
            if (pActwk->cddat & 20) {
              pActwk->cddat &= 235;
              pColliAct->colino = 0;
              pActwk->mstno.b.h = 21;
              pActwk->yspeed.w = 1024;
              if (pActwk->xposi.w.h < pColliAct->xposi.w.h) {
                pActwk->xspeed.w = -512;
              } else {
                pActwk->xspeed.w = 512;
              }
              break;
            } else return -1;
          }
          else if (cColiNo == 62) {
            pcolplay(pActwk, pColliAct);
            ++pColliAct->colicnt;
          }
          else return -1;
          break;
        case 5:
          if (cColiNo == 61) {
            pcolplay(pActwk, pColliAct);
            ++pColliAct->colicnt;
          }
          else return -1;
          break;
        case 1:
        default:
          if (cColiNo >= 60 && cColiNo > 63) {
            return -1;
          }
          pcolnomal(pActwk, pColliAct);
          if (pColliAct->colino == 0)
            pColliAct->colicnt += 3;
          pColliAct->colino = 0;


          ++pColliAct->colicnt;
          break;
      }
      break;
    case 4:
      switch (cColiNo) {
        case 31:
        case 35:
          ++pColliAct->colicnt;
          break;
        case 56:
        case 58:
        case 59:
          main_attack(pActwk, pColliAct);
          break;
        default:
          z3_eggman_chk(pActwk, pColliAct, cColiNo);
          break;
      }
      break;
    case 5:
      switch (cColiNo) {
        case 45:
        case 49:
          if (!(pActwk->cddat & 4)) {
            pcolnomal(pActwk, pColliAct);
            break;
          }
        case 31:
        case 35:
          ++pColliAct->colicnt;
          break;
        case 53:
        case 58:
        case 59:
          main_attack(pActwk, pColliAct);
          break;
      }
      default:
        switch (bossstart) {
          case 0:
            return -1;
          case 1:
            if (cColiNo < 60 || cColiNo > 63) {
              return -1;
            }

            pcolnomal(pActwk, pColliAct);
            if (pColliAct->colino == 0) {
              pColliAct->colicnt += 3;
            }

            pColliAct->colino = 0;

            ++pColliAct->colicnt;
            break;
          case 4:
            if (cColiNo == 63) {
              if (pActwk->cddat & 20) {
                pActwk->cddat &= 235;
                pColliAct->colino = 0;

                pActwk->mstno.b.h = 21;
                pActwk->yspeed.w = 1024;
                if (pActwk->xposi.w.h < pColliAct->xposi.w.h) {
                  pActwk->xspeed.w = -512;
                } else {
                  pActwk->xspeed.w = 512;
                }
              } else {
                return -1;
              }
            } else if (cColiNo == 62) {
              pcolplay(pActwk, pColliAct);

              ++pColliAct->colicnt;
            } else {
              return -1;
            }
            break;
          case 5:
            if (cColiNo == 61) {
              pcolplay(pActwk, pColliAct);

              ++pColliAct->colicnt;
            } else {
              return -1;
            }
            break;
        }
      break;
    case 6:
      switch (cColiNo) {
        case 45:
          if (!(pActwk->cddat & 4)) {
            pcolnomal(pActwk, pColliAct);
            break;
          }
        case 23:
        case 31:
        case 35:
          ++pColliAct->colicnt;
          break;
        case 6:
          if (pActwk->yspeed.w < 0) {
            if (pActwk->yposi.w.h - 16 >= pColliAct->yposi.w.h) {
              pActwk->yspeed.w *= -1;
              pColliAct->yspeed.w = -384;

              if (!pColliAct->r_no1) {
                pColliAct->r_no1 += 4;
              }
            }
          }
          else {
            if (pActwk->mstno.b.h == 2) {
              pActwk->yspeed.w *= -1;
              pColliAct->r_no0 += 2;
            }
          }
          break;
        case 34:
          main_attack(pActwk, pColliAct);
          break;
        case 48:
          if (pActwk->xposi.w.h - pColliAct->xposi.w.h < 0) {
            flgwk = 255;
          } else {
            flgwk = 0;
          }

          if (!((unsigned char)pColliAct->userflag.b.l ^ flgwk)) {
            pcolnomal(pActwk, pColliAct);
          }
          else {
            ++pColliAct->colicnt;
          }
          break;
        default:
          switch (bossstart) {
            case 0:
              break;
            case 4:
              if (cColiNo == 63) {
                if (pActwk->cddat & 20) {
                  pActwk->cddat &= 235;
                  pColliAct->colino = 0;

                  pActwk->mstno.b.h = 21;
                  pActwk->yspeed.w = 1024;
                  if (pActwk->xposi.w.h < pColliAct->xposi.w.h) {
                    pActwk->xspeed.w = -512;
                  } else {
                    pActwk->xspeed.w = 512;
                  }
                } else {
                  return -1;
                }
              } else if (cColiNo == 62) {
                pcolplay(pActwk, pColliAct);

                ++pColliAct->colicnt;
              } else {
                return -1;
              }
              break;
            case 5:
              if (cColiNo == 61) {
                pcolplay(pActwk, pColliAct);

                ++pColliAct->colicnt;
              } else {
                return -1;
              }
              break;
            case 1:
            default:
              if (cColiNo < 60 || cColiNo > 63) {
                return -1;
              }

              pcolnomal(pActwk, pColliAct);
              if (pColliAct->colino == 0) {
                pColliAct->colicnt += 3;
              }

              pColliAct->colino = 0;

              ++pColliAct->colicnt;
              break;
          }
          break;
      }
      break;
  }

label1:
  return -1;
}


static short eggman_chk(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo) {
  if (bossstart != 1) return -1;
  pcolnomal(pActwk, pColliAct);
  if (pColliAct->colino == 0) pColliAct->colicnt += 3;
  pColliAct->colino = 0;
  ++pColliAct->colicnt;
  return 1;
}


static short z3_eggman_chk(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo) {
  if (bossstart != 1) return -1;
  switch (bossstart) {
    case 1:
      boss_1(pActwk, pColliAct, cColiNo);
      break;
    case 4:
      boss_4(pActwk, pColliAct, cColiNo);
      break;
    case 5:
      boss_5(pActwk, pColliAct, cColiNo);
      break;
    default:
      boss_1(pActwk, pColliAct, cColiNo);
      break;
  }
  return 1;
}


static short yago(sprite_status* pActwk, sprite_status* pColliAct, short iXposi, short iChkPosi, short iD5) {
  iD5 -= iChkPosi;
  if (iD5 >= 8)
    return pcolnomal(pActwk, pColliAct);
  iChkPosi = pColliAct->xposi.w.h - 4;
  if (pColliAct->cddat & 1)
    iChkPosi -= 16;

  bCarry = CCset(iChkPosi, iXposi);
  iChkPosi -= iXposi;
  if (bCarry == 1) {
    bCarry = CSset(iChkPosi, 24);
    iChkPosi += 24;
    if (bCarry == 1)
      return pcolplay(pActwk, pColliAct);
    else
      return pcolnomal(pActwk, pColliAct);
  }

  if ((unsigned short)iChkPosi >= 16)
    return pcolplay(pActwk, pColliAct);
  else
    return pcolnomal(pActwk, pColliAct);
}


static void boss_1(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo) {
  if (cColiNo < 60 || cColiNo > 63)
    return;

  pcolnomal(pActwk, pColliAct);
  if (pColliAct->colino == 0)
    pColliAct->colicnt += 3;
  pColliAct->colino = 0;

  ++pColliAct->colicnt;
}


static void boss_4(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo) {
  if (cColiNo == 63) {
    if (!(pActwk->cddat & 20)) return;

    pActwk->cddat &= 251;
    pActwk->cddat &= 239;
    pActwk->colino = 0;
    pActwk->mstno.b.h = 21;

    pActwk->yspeed.w = 1024;
    pActwk->xspeed.w = -512;
    if (pActwk->xposi.w.h >= pColliAct->xposi.w.h)
      pActwk->xspeed.w = -pActwk->xspeed.w;
  }
  else if (cColiNo == 62) {
    pcolplay(pActwk, pColliAct);
    ++pColliAct->colicnt;
  }
}


static void boss_5(sprite_status* pActwk, sprite_status* pColliAct, char cColiNo) {
  if (cColiNo == 61) {
    pcolplay(pActwk, pColliAct);
    ++pColliAct->colicnt;
  }
}


static short main_attack(sprite_status* pActwk, sprite_status* pColliAct) {
  if (pActwk->mstno.b.h == 2)
    ++pColliAct->colicnt;
  return 1;
}
