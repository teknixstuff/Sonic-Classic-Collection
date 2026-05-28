#include "../../EQU.h"
#include "LPL_TYPES.h"
#include "SPM_EQU.h"
#include "ETC.h"























void swclear(void) {
  swdata1.w = 65280;
}






short cos_planet(short sDir) {
  return sin_planet(sDir + 128);
}






short sin_planet(short sDir) {
  short sDirWk;
  static short sin_tbl[128] =
  {
      0,   3,   6,   9,  12,  15,  18,  22,  25,  28,  31,  34,  37,  40,  43,  47,
     50,  53,  56,  59,  62,  65,  68,  71,  74,  77,  80,  83,  86,  89,  92,  95,
     98, 101, 104, 106, 109, 112, 115, 118, 121, 123, 126, 129, 132, 134, 137, 140,
    142, 145, 147, 150, 153, 155, 158, 160, 162, 165, 167, 170, 172, 174, 177, 179,
    181, 183, 185, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 209, 211,
    213, 215, 216, 218, 220, 221, 223, 224, 226, 227, 229, 230, 231, 233, 234, 235,
    236, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 247, 248, 249, 250, 250,
    251, 251, 252, 252, 253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 256
  };

  sDir &= 511;
  sDirWk = sDir;
  if (sDir & 128) sDirWk = ~sDirWk;
  sDirWk &= 127;
  sDirWk = sin_tbl[sDirWk];
  if (sDir & 256) sDirWk = -sDirWk;
  return sDirWk;
}







void unlze(unsigned char* pSrc, unsigned char* pDst) {
  short_union sp;
  short sD5, sD4, sD3, sD2, sD1, sD0;
  unsigned char CarryFlg, XFlg;

  sp.b.l = *pSrc++;
  sp.b.h = *pSrc++;
  sD5 = sp.w;
  sD4 = 15;

  while (1)
  {
    CarryFlg = sD5 & 1;
    XFlg = 0;
    sD5 = (unsigned short)sD5 >> 1;
    if (--sD4 < 0)
    {
      sp.b.l = *pSrc++;
      sp.b.h = *pSrc++;
      sD5 = sp.w;
      sD4 = 15;
    }

    if (CarryFlg != 0)
    {
      *pDst++ = *pSrc++;
      continue;
    }

    sD3 = 0;
    CarryFlg = sD5 & 1;
    XFlg = 0;
    if (--sD4 < 0)
    {
      sp.b.l = *pSrc++;
      sp.b.h = *pSrc++;
      sD5 = sp.w;
      sD4 = 15;
    }

    if (CarryFlg == 0)
    {
      sD5 = (unsigned short)sD5 >> 1;
      if (--sD4 < 0)
      {
        sp.b.l = *pSrc++;
        sp.b.h = *pSrc++;
        sD5 = sp.w;
        sD4 = 15;
      }

      CarryFlg = (sD3 & 32768) >> 15;
      sD3 = (unsigned short)sD3 << 1 | XFlg;
      XFlg = CarryFlg;
      ++sD3;
      sD2 = -1;
      sD2 = sD2 & 65280 | *pSrc++;
    }
    else
    {

      sD0 = *pSrc++;
      sD1 = *pSrc++;
      sD2 = -1;
      sD2 = sD2 & 65280 | (sD1 & 255);
      sD2 = (unsigned short)sD2 << 5;
      sD2 = sD2 & 65280 | (sD0 & 255);
      if (!(sD1 & 7))
      {

        if ((sD1 = *pSrc++) == 0) return;
        if (sD1 == 1) continue;
        sD3 = sD1;
      }
      else
      {
        sD3 = sD1 + 1;
      }
    }

    do
    {
      sD0 = pDst[sD2];
      *pDst++ = (unsigned char)sD0;
    } while (--sD3 >= 0);
  }
}
