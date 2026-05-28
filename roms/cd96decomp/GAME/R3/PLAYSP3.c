#include "../EQU.h"
#include "PLAYSP3.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../FCOL.h"
#include "../LOADER2.h"
#include "../SCR.h"

static short fcol3a[17] = { 15, 316, 326, 411, 430, 131, 132, 137, 138, 119, 118, 128, 127, 126, 125, 124, 130 };
static short fcol3b[3] = { 1, 325, 326 };
static short fcol3c[17] = { 15, 316, 326, 0, 0, 131, 132, 137, 138, 119, 118, 128, 127, 126, 125, 124, 130 };
static short fcol3d[17] = { 15, 316, 326, 357, 358, 131, 132, 137, 138, 119, 118, 128, 127, 126, 125, 124, 130 };
static short* fcol_tbl[4] = { fcol3b, fcol3a, fcol3d, fcol3c };
static unsigned char bump_sound_off;



void boyo(void) {
  unsigned char direc_speed;

  direc_speed = (char)atan_sonic(actwk[0].xspeed.w, actwk[0].yspeed.w);

  direc_speed = direc_speed - 32 & 192;
  switch (direc_speed) {

    case 0:
      if (!bycol_sub0(actwk[0].xposi.w.h - (short)actwk[0].sprhs, actwk[0].yposi.w.h + (short)actwk[0].sprvsize)) {

        bycol_sub0(actwk[0].xposi.w.h + (short)actwk[0].sprhs, actwk[0].yposi.w.h + (short)actwk[0].sprvsize);
      }
      break;

    case 128:
      if (!bycol_sub0(actwk[0].xposi.w.h - (short)actwk[0].sprhs, actwk[0].yposi.w.h - (short)actwk[0].sprvsize)) {

        bycol_sub0(actwk[0].xposi.w.h + (short)actwk[0].sprhs, actwk[0].yposi.w.h - (short)actwk[0].sprvsize);
      }
      break;

    case 192:
      if (!bycol_sub0(actwk[0].xposi.w.h + (short)actwk[0].sprhs, actwk[0].yposi.w.h - (short)(actwk[0].sprvsize - 6))) {


        bycol_sub0(actwk[0].xposi.w.h + (short)actwk[0].sprhs, actwk[0].yposi.w.h + (short)actwk[0].sprvsize);
      }
      break;

    case 64:
      if (!bycol_sub0(actwk[0].xposi.w.h - (short)actwk[0].sprhs, actwk[0].yposi.w.h - (short)(actwk[0].sprvsize - 6))) {


        bycol_sub0(actwk[0].xposi.w.h - (short)actwk[0].sprhs, actwk[0].yposi.w.h + (short)actwk[0].sprvsize);
      }
      break;
  }


}



















char bycol_sub0(short cal_x, short cal_y) {
  void(*jump_no[16])(short, short, short, short) = {
    &bob, &bob, &bob_s, &bob_s, &bob5, &bob0, &bob1, &bob1,
    &bob4, &bob3, &bob3, &bob3, &bob2, &bob0, &bob0, &bob_s0
  };
  unsigned char now_time;
  short block_no, block_back, *fcol3, i;

  block_no = block_back = scramapad(&actwk[0], cal_x, cal_y);
  if ((block_no &= 2047) == 0) { bump_sound_off = 1; return 0; }
  if ((now_time = time_flag & 127) == 2)
    now_time = now_time + generate_flag;
  fcol3 = fcol_tbl[now_time];
  for (i = 0; i <= *fcol3; ++i) if (block_no == fcol3[i + 1]) goto label1;
  bump_sound_off = 1;
  return 0;

label1:
  if (actwk[0].r_no0 == 4) {
    actwk[0].r_no0 -= 2;
    ((short*)&actwk[0])[26] = 120;
  }
  col_y.b.h = 0;
  jump_no[i](i, cal_x, cal_y, block_back);
  if (i >= 2) {
    if (bump_sound_off) {
      if (i == 2 || i == 3) soundset(190);
      else soundset(181);
    }
    bump_sound_off = 0;
  }
  if (col_y.b.h != 0) return 0;
  return 1;
}


void bob(short i, short cal_x, short cal_y, short block_back) {
  short tmp_sin, tmp_cos, tmp_x, tmp_y;
  int cal_sin, cal_cos;
  sprite_status* new_actwk;

  cal_y = (unsigned short)cal_y & 65520;
  if (i == 0) cal_y += 16;
  cal_x = (unsigned short)cal_x & 65520;
  if (!(block_back & 2048)) cal_x += 16;
  tmp_x = cal_x, tmp_y = cal_y;
  sinset((char)atan_sonic(cal_x - actwk[0].xposi.w.h, cal_y - actwk[0].yposi.w.h), &tmp_sin, &tmp_cos);

  cal_sin = tmp_sin * -1792 >> 8;
  cal_cos = tmp_cos * -1792 >> 8;
  actwk[0].xspeed.w = cal_cos;
  actwk[0].yspeed.w = cal_sin;
  actwk[0].cddat |= 2;
  actwk[0].cddat &= 207;
  actwk[0].actfree[18] = 0;
  if (actwkchk(&new_actwk) == 0) {
    new_actwk->actno = 41;
    new_actwk->xposi.w.h = tmp_x;
    new_actwk->yposi.w.h = tmp_y;
  }

  block_wrt(0, tmp_x, tmp_y);
  block_wrt(0, tmp_x -= 16, tmp_y);
  block_wrt(0, tmp_x, tmp_y -= 16);
  block_wrt(0, tmp_x += 16, tmp_y);
  sub_sync(146);
}


void bob_s(short i, short cal_x, short cal_y, short block_back) {
  short tmp_sin, tmp_cos;
  int cal_sin, cal_cos;

  cal_y = (unsigned short)cal_y & 65528;
  cal_x = (unsigned short)cal_x & 65528;
  sinset((char)atan_sonic(cal_x - actwk[0].xposi.w.h, cal_y - actwk[0].yposi.w.h), &tmp_sin, &tmp_cos);

  cal_sin = tmp_sin * -1792 >> 9;
  cal_cos = tmp_cos * -1792 >> 9;
  actwk[0].xspeed.w = cal_cos;
  actwk[0].yspeed.w = cal_sin;
  bob_j();
  block_back = block_back, i = i;
}


void bob_j(void) {
  actwk[0].cddat |= 2;
  actwk[0].cddat &= 207;
  actwk[0].actfree[18] = 0;
}


void bob0(short i, short cal_x, short cal_y, short block_back) {
  if (actwk[0].yspeed.w >= 0) actwk[0].yspeed.w = -1792;
  else actwk[0].yspeed.w = 1792;
  bob_j();
  i = i, cal_x = cal_x, cal_y = cal_y, block_back = block_back;
}


void bob1(short i, short cal_x, short cal_y, short block_back) {
  if (actwk[0].xspeed.w >= 0) actwk[0].xspeed.w = -1792;
  else actwk[0].xspeed.w = 1792;
  bob_j();
  i = i, cal_x = cal_x, cal_y = cal_y, block_back = block_back;
}


void bob_s0(short i, short cal_x, short cal_y, short block_back) {
  short tmp_sin, tmp_cos;
  int cal_sin, cal_cos;

  cal_y = (unsigned short)cal_y & 65528;
  cal_x = (unsigned short)cal_x & 65528;
  sinset((char)atan_sonic(cal_x - actwk[0].xposi.w.h, cal_y - actwk[0].yposi.w.h), &tmp_sin, &tmp_cos);

  cal_sin = tmp_sin * -1792 >> 8;
  cal_cos = tmp_cos * -1792 >> 8;
  actwk[0].xspeed.w = cal_cos;
  actwk[0].yspeed.w = cal_sin;
  bob_j();
  block_back = block_back, i = i;
}


void bob2(short i, short cal_x, short cal_y, short block_back) {
  if (((unsigned short)cal_x & 15) < 8) {
    if (block_back & 2048) bob0(i, cal_x, cal_y, block_back);
    else bob1(i, cal_x, cal_y, block_back);
  } else {
    if (block_back & 2048) bob1(i, cal_x, cal_y, block_back);
    else bob0(i, cal_x, cal_y, block_back);
  }
}


void bob3(short i, short cal_x, short cal_y, short block_back) {
  static unsigned char bydcol0[16] = {
    1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6
  };
  static unsigned char bydcol1[16] = {
    6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11
  };
  static unsigned char bydcol2[16] = {
    11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16
  };
  unsigned char* tbl[3] = { bydcol0, bydcol1, bydcol2 };
  unsigned char* bydcol;
  unsigned char cal_direc;
  short tmp_sin, tmp_cos;
  int cal_sin, cal_cos;

  if ((i -= 9) >= 0) {
    bydcol = tbl[i];
    cal_y = (unsigned short)cal_y & 15;
    cal_x = (unsigned short)cal_x & 15;
    if (!(block_back & 2048)) cal_x = 15 - cal_x;
    if (cal_y < (short)bydcol[cal_x]) { col_y.b.h = 1; return; }
  }

  cal_direc = atan_sonic(actwk[0].xspeed.w, actwk[0].yspeed.w);
  cal_direc = -(char)(cal_direc + 128);
  cal_direc -= 32;
  if (block_back & 2048) cal_direc += 64;
  sinset(cal_direc, &tmp_sin, &tmp_cos);
  cal_sin = tmp_sin * -1792 >> 8;
  cal_cos = tmp_cos * -1792 >> 8;
  actwk[0].xspeed.w = cal_cos;
  actwk[0].yspeed.w = cal_sin;
  bob_j();
}


void bob4(short i, short cal_x, short cal_y, short block_back) {
  if (((unsigned short)cal_x & 15) < 8) {
    if (block_back & 2048) bob1(i, cal_x, cal_y, block_back);
    else bob3(i, cal_x, cal_y, block_back);
  } else {
    if (block_back & 2048) bob0(i, cal_x, cal_y, block_back);
    else bob3(i, cal_x, cal_y, block_back);
  }
}


void bob5(short i, short cal_x, short cal_y, short block_back) {
  if (((unsigned short)cal_x & 15) < 8) {
    if (block_back & 2048) bob0(i, cal_x, cal_y, block_back);
    else bob_s0(i, cal_x, cal_y, block_back);
  } else {
    if (block_back & 2048) bob_s0(i, cal_x, cal_y, block_back);
    else bob0(i, cal_x, cal_y, block_back);
  }
}


void bob6(short i, short cal_x, short cal_y, short block_back) {
  if (((unsigned short)cal_y & 15) < 8) {
    if (block_back & 2048) bob1(i, cal_x, cal_y, block_back);
    else bob_s0(i, cal_x, cal_y, block_back);
  } else {
    if (block_back & 2048) bob_s0(i, cal_x, cal_y, block_back);
    else bob1(i, cal_x, cal_y, block_back);
  }
}
