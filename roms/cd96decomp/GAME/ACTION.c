#include "EQU.h"
#include "ACTION.h"
#include <string.h>
#include "../services.h"

extern void(*(*act_tbls[7][3][3]))(sprite_status*);
extern bmp_info SprBmp[700];
































void action(void) {
  sprite_status* pActwk;
  int i;

  pActwk = &actwk[0];
  for (i = 0; i < 128; ++i, ++pActwk) {
    if (pActwk->actno) {






      act_tbls[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][pActwk->actno - 1](pActwk);
    }

  }
}







void speedset(sprite_status* pActwk) {
  int_union xpos, ypos;
  short_union spd;

  xpos.l = pActwk->xposi.l;
  ypos.l = pActwk->yposi.l;
  spd.w = pActwk->xspeed.w;
  xpos.l += spd.w << 8;
  spd.w = pActwk->yspeed.w;
  if (pActwk->actfree[2] & 8) goto label2;
  if (spd.w >= 0) goto label1;
  if (!(pActwk->actfree[2] & 2)) goto label1;
  if (pActwk->yspeed.w < -2048) goto label2;
label1:
  if (pActwk->actfree[2] & 4) goto label2;
  pActwk->yspeed.w += 56;
label2:
  if (pActwk->yspeed.w < 0) goto label3;
  if (pActwk->yspeed.w < 4096) goto label3;
  pActwk->yspeed.w = 4096;
label3:
  ypos.l += spd.w << 8;
  pActwk->xposi.l = xpos.l;
  pActwk->yposi.l = ypos.l;
}







void speedset2(sprite_status* pActwk) {
  int_union xpos, ypos;
  int spd;
  int actwkno;
  short d1;

  xpos.l = pActwk->xposi.l;
  ypos.l = pActwk->yposi.l;
  spd = pActwk->xspeed.w;
  if (pActwk->cddat & 8) {

    d1 = 0;
    actwkno = pActwk->actfree[19];
    if (actwk[actwkno].actno == 30) {

      d1 = -256;


      if (actwk[actwkno].cddat & 1) d1 = -d1;

      spd += d1;
    }
  }
  spd = spd << 8;
  xpos.l += spd;
  spd = pActwk->yspeed.w;
  spd = spd << 8;
  ypos.l += spd;
  pActwk->xposi.l = xpos.l;
  pActwk->yposi.l = ypos.l;
}







void actionsub(sprite_status* pActwk) {
  int i;
  unsigned short flag;
  short hsiz, vsiz;
  short xpos, ypos;
  unsigned char pri;

  if (gKeepWork.GamePass != 0) return;

  pActwk->actflg &= 127;
  flag = pActwk->actflg;
  flag &= 12;
  if (flag) {

    hsiz = (unsigned short)pActwk->sprhsize;
    xpos = pActwk->xposi.w.h;
    xpos -= scra_h_posit.w.h;
    if (xpos + hsiz < 0) return;
    if (xpos - hsiz >= 320) return;

    vsiz = (unsigned short)pActwk->sprvsize;
    ypos = pActwk->yposi.w.h;
    if ((unsigned short)scra_v_posit.w.h < 256) {

      if ((unsigned short)ypos >= 2048) ypos -= 2048;
    }
    else if ((unsigned short)scra_v_posit.w.h >= 1792) {

      if ((unsigned short)ypos < 256) ypos += 2048;
    }
    ypos -= scra_v_posit.w.h;
    if (ypos + vsiz < 0) return;
    if (ypos - vsiz >= 224) return;
  }

  pri = pActwk->sprpri;
  i = pbuffer[pri].cnt;
  if (i < 63) {

    pbuffer[pri].pActwk[i] = pActwk;
    pbuffer[pri].cnt += 1;
  }
}







void frameout(sprite_status* pActwk) {

  memset(pActwk, 0, sizeof(*pActwk));
}









void patset(void) {
  sprite_status* pActwk;
  unsigned char flag;
  short i;
  short act;
  short xposi, yposi;
  short patno;
  short cnt;
  sprite_pattern* patadr;
  sprite_pattern** patbase;
  sprite_data* sprdat;
  int_union *pScrHposi, *pScrVposi;
  int_union* patsettbl[8] =
  {
    0,
    &scra_h_posit,
    &scrb_h_posit,
    &scrc_h_posit,
    0,
    &scra_v_posit,
    &scrb_v_posit,
    &scrc_v_posit
  };

  if (gKeepWork.GamePass != 0) return;

  linkdata = 0;
  for (i = 0; i < 8; ++i) {

    if (pbuffer[i].cnt == 0) continue;
    act = 0;
    do {

      pActwk = pbuffer[i].pActwk[act];
      if (pActwk->actno && pActwk->patbase != 0) {
        flag = pActwk->actflg >> 2;
        flag &= 3;
        if (flag) {

          pScrHposi = patsettbl[flag];
          pScrVposi = patsettbl[flag + 4];
          xposi = pActwk->xposi.w.h;
          xposi -= pScrHposi->w.h;
          xposi += 128;
          yposi = pActwk->yposi.w.h;
          if ((unsigned short)pScrVposi->w.h < 256) {

            if ((unsigned short)yposi >= 2048) yposi -= 2048;
          }
          else if ((unsigned short)pScrVposi->w.h >= 1792) {

            if ((unsigned short)yposi < 256) yposi += 2048;
          }
          yposi -= pScrVposi->w.h;
          yposi += 128;
        }
        else {

          xposi = pActwk->xposi.w.h;
          yposi = pActwk->yposi.w.h;
        }

        patbase = pActwk->patbase;
        patno = pActwk->patno;
        patadr = patbase[patno];
        cnt = patadr->cnt;
        sprdat = &patadr->spr[0];
        if (pActwk->actflg & 32) {
          cnt = 1;
        }
        if (cnt > 0) {
          spatset(xposi, yposi, pActwk, sprdat, cnt);
        }
        pActwk->actflg |= 128;
      }
      ++act;
    }
    while (--pbuffer[i].cnt > 0);
  }

  for (i = (unsigned short)linkdata; i < 80; ++i) {
    EAsprset(0, 0, 0, i, 0);
  }
}










void spatset(short xposi, short yposi, sprite_status* pActwk, sprite_data* sprdat, short cnt) {
  unsigned char flag;
  short x, y;
  unsigned short reverse;

  flag = pActwk->actflg;
  flag &= 3;
  for ( ; cnt > 0; --cnt) {
    if (sprdat->index) {
      if (linkdata >= 80) return;

      switch (flag) {
        case 0:
          x = xposi + (short)sprdat->xoff;
          y = yposi + (short)sprdat->yoff;
          break;
        case 1:
          x = xposi + (short)(-sprdat->xoff - (short)SprBmp[sprdat->index].xs);
          y = yposi + (short)sprdat->yoff;
          break;
        case 2:
          x = xposi + (short)sprdat->xoff;
          y = yposi + (short)(-sprdat->yoff - (short)SprBmp[sprdat->index].ys);
          break;
        case 3:
          x = xposi + (short)(-sprdat->xoff - (short)SprBmp[sprdat->index].xs);
          y = yposi + (short)(-sprdat->yoff - (short)SprBmp[sprdat->index].ys);
          break;
      }
      reverse = 0;
      if (pActwk->sproffset & 32768 || (sprdat->etc & 128) != 0) {
        reverse |= 32768;
      }
      if (((flag & 1) != 0) ^ ((sprdat->etc & 8) != 0)) {
        ++reverse;
      }
      if (((flag & 2) != 0) ^ ((sprdat->etc & 16) != 0)) {
        reverse += 2;
      }

      EAsprset(x, y, sprdat->index, linkdata, reverse);
      ++linkdata;
    }
    ++sprdat;
  }

}









int scronchk(sprite_status* pActwk) {
  short xposi, yposi;

  xposi = pActwk->xposi.w.h;
  xposi -= scra_h_posit.w.h;
  if (xposi < 0 || xposi >= 320) return -1;
  yposi = pActwk->yposi.w.h;
  yposi -= scra_v_posit.w.h;
  if (yposi < 0 || yposi >= 224) return -1;
  return 0;
}







int scronchk2(sprite_status* pActwk) {
  short xposi, yposi;
  short hsize;

  hsize = pActwk->sprhsize;
  xposi = pActwk->xposi.w.h;
  xposi -= scra_h_posit.w.h;
  xposi += hsize;
  if (xposi < 0) return -1;
  hsize += hsize;
  xposi -= hsize;
  if (xposi >= 320) return -1;
  yposi = pActwk->yposi.w.h;
  yposi -= scra_v_posit.w.h;
  if (yposi < 0 || yposi >= 224) return -1;
  return 0;
}
