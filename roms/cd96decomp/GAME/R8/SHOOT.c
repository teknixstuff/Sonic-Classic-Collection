#include "../EQU.h"
#include "SHOOT.h"
#include "../ACTSET.h"
#include "../LOADER2.h"

static void shoot_init(sprite_status* shootwk); static void shoot_move1(sprite_status* shootwk);
static void shooterinit(sprite_status* shootwk);
static void shootermove(sprite_status* shootwk);
static void shootermove2(sprite_status* shootwk);
static void shootermove3(sprite_status* shootwk);
static void shooterspdset(sprite_status* shootwk);
static void mspd_set(sprite_status* shootwk);

static unsigned short shooterposi_d[11] = {
  20,
  896, 1744,
  896, 1920,
  640, 1920,
  640, 896,
  1144, 896
};
static unsigned short shooterposi_e[11] = {
  20,
  1120, 896,
  640, 896,
  640, 1920,
  896, 1920,
  896, 1720
};
static unsigned short shooterposi_f[5] = {
  8,
  1152, 720,
  1152, 888
};
static unsigned short shooterposi_10[5] = {
  8,
  1152, 864,
  1152, 696
};
static unsigned short shooterposi_11[13] = {
  24,
  1152, 928,
  1152, 1152,
  1280, 1152,
  1536, 896,
  1664, 896,
  1664, 696
};
static unsigned short shooterposi_12[13] = {
  24,
  1664, 720,
  1664, 896,
  1536, 896,
  1280, 1152,
  1152, 1152,
  1152, 904
 };
static unsigned short shooterposi_13[15] = {
  28,
  1184, 896,
  1280, 896,
  1536, 1152,
  1664, 1152,
  1664, 1664,
  1920, 1664,
  1920, 1464
};
static unsigned short shooterposi_14[15] = {
  28,
  1920, 1488,
  1920, 1664,
  1664, 1664,
  1664, 1152,
  1536, 1152,
  1280, 896,
  1160, 896
};
static unsigned short shooterposi_15[7] = {
  12,
  3712, 208,
  3712, 384,
  4216, 384
};
static unsigned short shooterposi_16[7] = {
  12,
  4192, 384,
  3712, 384,
  3712, 184
};
static unsigned short shooterposi_17[5] = {
  8,
  4224, 208,
  4224, 376
};
static unsigned short shooterposi_18[5] = {
  8,
  4224, 352,
  4224, 184
};
static unsigned short shooterposi_19[9] = {
  16,
  4224, 416,
  4224, 896,
  3968, 896,
  3968, 696
};
static unsigned short shooterposi_1a[9] = {
  16,
  3968, 720,
  3968, 896,
  4224, 896,
  4224, 392
};
static unsigned short shooterposi_1b[11] = {
  20,
  4256, 384,
  4480, 384,
  4480, 1152,
  4992, 1152,
  4992, 952
};
static unsigned short shooterposi_1c[11] = {
  20,
  4992, 976,
  4992, 1152,
  4480, 1152,
  4480, 384,
  4232, 384
};
static unsigned short shooterposi_1d[9] = {
  16,
  6272, 720,
  6272, 1152,
  6528, 1152,
  6528, 952
};
static unsigned short shooterposi_1e[9] = {
  16,
  6528, 976,
  6528, 1152,
  6272, 1152,
  6272, 696
};
static unsigned short shooterposi_25[11] = {
  20,
  896, 1488,
  896, 1664,
  640, 1664,
  640, 896,
  1144, 896
};
static unsigned short shooterposi_26[11] = {
  20,
  1120, 896,
  640, 896,
  640, 1664,
  896, 1664,
  896, 1464
};
static unsigned short shooterposi_27[13] = {
  24,
  1152, 864,
  1152, 640,
  1280, 640,
  1536, 384,
  1664, 384,
  1664, 184
};
static unsigned short shooterposi_28[13] = {
  24, 1664, 208, 1664, 384, 1536, 384, 1280, 640, 1152, 640, 1152, 888
};
static unsigned short shooterposi_29[21] = {
  40,
  1152, 928,
  1152, 1152,
  1280, 1152,
  1536, 896,
  1664, 896,
  1664, 640,
  1536, 640,
  1280, 384,
  1152, 384,
  1152, 184
};
static unsigned short shooterposi_2a[21] = {
  40,
  1152, 208,
  1152, 384,
  1280, 384,
  1536, 640,
  1664, 640,
  1664, 896,
  1536, 896,
  1280, 1152,
  1152, 1152,
  1152, 904
};
static unsigned short shooterposi_2b[35] = {
  68,
  2176, 720,
  2176, 896,
  2560, 896,
  3072, 384,
  3328, 384,
  3584, 640,
  3712, 640,
  3712, 896,
  3328, 896,
  2816, 384,
  2432, 384,
  2432, 640,
  2560, 640,
  2816, 896,
  3072, 896,
  3584, 384,
  4216, 384
};
static unsigned short shooterposi_2c[35] = {
  68,
  4192, 384,
  3584, 384,
  3072, 896,
  2816, 896,
  2560, 640,
  2432, 640,
  2432, 384,
  2816, 384,
  3328, 896,
  3712, 896,
  3712, 640,
  3584, 640,
  3328, 384,
  3072, 384,
  2560, 896,
  2176, 896,
  2176, 696
};
static unsigned short shooterposi_2d[9] = {
  16,
  4224, 416,
  4224, 1664,
  3968, 1664,
  3968, 1464
};
static unsigned short shooterposi_2e[9] = {
  16,
  3968, 1488,
  3968, 1664,
  4224, 1664,
  4224, 392
};
static unsigned short shooterposi_2f[11] = {
  20,
  4256, 384,
  4480, 384,
  4480, 1152,
  4736, 1152,
  4736, 952
};
static unsigned short shooterposi_30[11] = {
  20,
  4736, 976,
  4736, 1152,
  4480, 1152,
  4480, 384,
  4232, 384
};
static unsigned short shooterposi_35[5] = {
  8,
  1152, 928,
  1152, 1144
};
static unsigned short shooterposi_36[5] = {
  8,
  1152, 1120,
  1152, 904
};
static unsigned short shooterposi_37[11] = {
  20,
  1152, 1184,
  1152, 1408,
  896, 1408,
  896, 1152,
  1144, 1152
};
static unsigned short shooterposi_38[11] = {
  20,
  1120, 1152,
  896, 1152,
  896, 1408,
  1152, 1408,
  1152, 1160
};
static unsigned short shooterposi_39[11] = {
  20,
  1184, 1152,
  1280, 1152,
  1536, 896,
  1664, 896,
  1664, 696
};
static unsigned short shooterposi_3a[11] = {
  20,
  1664, 720,
  1664, 896,
  1536, 896,
  1280, 1152,
  1160, 1152
};
static unsigned short shooterposi_3b[33] = {
  64,
  2176, 720,
  2176, 896,
  2560, 896,
  2816, 640,
  3072, 896,
  3328, 640,
  3584, 896,
  3712, 896,
  3712, 640,
  3584, 640,
  3328, 896,
  3072, 640,
  2816, 896,
  2560, 640,
  2432, 640,
  2432, 440
};
static unsigned short shooterposi_3c[33] = {
  64,
  2432, 464,
  2432, 640,
  2560, 640,
  2816, 896,
  3072, 640,
  3328, 896,
  3584, 640,
  3712, 640,
  3712, 896,
  3584, 896,
  3328, 640,
  3072, 896,
  2816, 640,
  2560, 896,
  2176, 896,
  2176, 696
};
static unsigned short* shooterpositbl[61] = {
  shooterposi_d, shooterposi_d,
  shooterposi_d, shooterposi_d,
  shooterposi_d, shooterposi_d,
  shooterposi_d, shooterposi_d,
  shooterposi_d, shooterposi_d,
  shooterposi_d, shooterposi_d,
  shooterposi_d, shooterposi_d,
  shooterposi_e, shooterposi_f,
  shooterposi_10, shooterposi_11,
  shooterposi_12, shooterposi_13,
  shooterposi_14, shooterposi_15,
  shooterposi_16, shooterposi_17,
  shooterposi_18, shooterposi_19,
  shooterposi_1a, shooterposi_1b,
  shooterposi_1c, shooterposi_1d,
  shooterposi_1e, shooterposi_25,
  shooterposi_25, shooterposi_25,
  shooterposi_25, shooterposi_25,
  shooterposi_25, shooterposi_25,
  shooterposi_26, shooterposi_27,
  shooterposi_28, shooterposi_29,
  shooterposi_2a, shooterposi_2b,
  shooterposi_2c, shooterposi_2d,
  shooterposi_2e, shooterposi_2f,
  shooterposi_30, shooterposi_35,
  shooterposi_35, shooterposi_35,
  shooterposi_35, shooterposi_35,
  shooterposi_36, shooterposi_37,
  shooterposi_38, shooterposi_39,
  shooterposi_3a, shooterposi_3b,
  shooterposi_3c
};
extern sprite_pattern* bariapat[13];























void shoot_s(sprite_status* shootwk) {
  void(*shoot_s_tbl[4])(sprite_status*) = { &shoot_init, &shootermove, &shoot_move1, &shootermove3 };


  if (actwk[0].r_no0 >= 6) return;

  swdata.w = swdata1.w;
  shoot_s_tbl[shootwk->r_no0 / 2](shootwk);
  frameout_s(shootwk);
}



static void shoot_init(sprite_status* shootwk) {
  shootwk->actflg |= 4;
  ((short*)shootwk)[31] = 4;
  ((short*)shootwk)[29] = shootwk->xposi.w.h;
  ((short*)shootwk)[30] = shootwk->yposi.w.h;
  shootwk->r_no0 += 2;
}


static void shoot_move1(sprite_status* shootwk) {
  if (swdata.b.l & 1) ((short*)shootwk)[30] -= 16;
  else if (swdata.b.l & 2) ((short*)shootwk)[30] += 16;
  else if (swdata.b.l & 4) ((short*)shootwk)[29] -= 16;
  else if (swdata.b.l & 8) ((short*)shootwk)[29] += 16;
  else return;

  shootwk->r_no0 += 2;
  actwk[0].mspeed.w = 4096;
  shooterspdset(shootwk);
}



void shooter8(sprite_status* shootwk) {
  short flag_no, addition;

  if (!(time_flag & 128)) goto label1;
  if ((flag_no = shootwk->cdsts) == 0) goto label1;
  flag_no *= 3;
  addition = (short)(time_flag & 127) - (short)time_item;
  if (addition < 0) addition = 0;
  else if (addition >= 3) addition = 2;
  flagwork[flag_no + addition] &= 127;
label1:
  if (actwk[0].mstno.b.h != 43) {
    if (actwk[0].r_no0 < 6) {
      if ((unsigned char)shootwk->userflag.b.h == 128) { shoot_s(shootwk); return; }
      switch (shootwk->r_no0) {
        case 0:
          shooterinit(shootwk);
          break;
        case 2:
          shootermove(shootwk);
          break;
        case 4:
          shootermove2(shootwk);
          break;
        case 6:
          shootermove3(shootwk);
          break;
      }
    }
  }

}


static void shooterinit(sprite_status* shootwk) {
  unsigned short** move;
  unsigned short* movetbl;

  shootwk->patbase = bariapat;
  shootwk->actflg = 4;
  shootwk->sprpri = 1;
  shootwk->sprhsize = 16;


  shootwk->r_no0 += 2;
  movetbl = shooterpositbl[shootwk->userflag.b.h & 127];
  shootwk->actfree[16] = *movetbl >> 8;
  shootwk->actfree[17] = *movetbl & 255;
  move = &((unsigned short**)shootwk)[16];
  *move = &movetbl[1];
  ((short*)shootwk)[29] = movetbl[1];
  ((short*)shootwk)[30] = movetbl[2];
  shootermove(shootwk);
}


static void shootermove(sprite_status* shootwk) {
  short cal_position;

  cal_position = actwk[0].xposi.w.h - shootwk->xposi.w.h + 16;
  if (cal_position >= 32 || cal_position < 0) return;
  cal_position = actwk[0].yposi.w.h - shootwk->yposi.w.h + 16;
  if (cal_position >= 32 || cal_position < 0) return;
  if (actwk[0].actfree[2] != 0) return;
  if (actwk[0].r_no0 == 4) {
    actwk[0].r_no0 -= 2;
    ((short*)&actwk[0])[26] = 120;
  }
  shootwk->r_no0 += 2;
  actwk[0].actfree[2] = 129;
  actwk[0].sproffset &= 32767;
  actwk[0].mstno.b.h = 2;
  mspd_set(shootwk);
  actwk[0].xspeed.w = actwk[0].yspeed.w = 0;
  shootwk->cddat &= 223;
  actwk[0].cddat &= 223;
  actwk[0].cddat |= 2;
  actwk[0].xposi.w.h = shootwk->xposi.w.h;
  actwk[0].yposi.w.h = shootwk->yposi.w.h;
  shootwk->actfree[8] = 0;
  soundset(145);
}


static void shootermove2(sprite_status* shootwk) {
  shooterspdset(shootwk);
  shootwk->r_no0 += 2;
  soundset(145);
}


static void shootermove3(sprite_status* shootwk) {
  unsigned char move_counter;
  unsigned short** move;
  unsigned short* movetbl;

  if ((char)--shootwk->actfree[4] < 0) {
    actwk[0].xposi.w.h = ((unsigned short*)shootwk)[29];
    actwk[0].yposi.w.h = ((unsigned short*)shootwk)[30];
    move_counter = shootwk->actfree[16] + 4;
    if (move_counter >= shootwk->actfree[17]) goto label1;

    shootwk->actfree[16] = move_counter;
    move = &((unsigned short**)shootwk)[16];
    movetbl = *move;
    ((short*)shootwk)[29] = movetbl[move_counter / 2];
    ((short*)shootwk)[30] = movetbl[move_counter / 2 + 1];
    shooterspdset(shootwk);
    return;
  }

  actwk[0].xposi.l += actwk[0].xspeed.w << 8;
  actwk[0].yposi.l += actwk[0].yspeed.w << 8;
  return;

label1:
  actwk[0].yposi.w.h &= 2047;
  shootwk->r_no0 = 0;
  actwk[0].actfree[2] = 0;
}


static void shooterspdset(sprite_status* shootwk) {
  short ms_work0, ms_work1, cal_position_x, cal_position_y;
  int cal_long_x, cal_long_y;

  ms_work0 = ms_work1 = actwk[0].mspeed.w;
  cal_position_x = ((short*)shootwk)[29];
  cal_position_x -= actwk[0].xposi.w.h;
  if (cal_position_x < 0) {
    cal_position_x = -cal_position_x;
    ms_work0 = -ms_work0;
  }
  cal_position_y = ((short*)shootwk)[30];
  cal_position_y -= actwk[0].yposi.w.h;
  if (cal_position_y < 0) {
    cal_position_y = -cal_position_y;
    ms_work1 = -ms_work1;
  }
  if (cal_position_x <= cal_position_y) {

    cal_position_y = ((short*)shootwk)[30];
    cal_position_y -= actwk[0].yposi.w.h;
    cal_long_y = cal_position_y << 16;
    cal_long_y /= ms_work1;

    cal_position_x = ((short*)shootwk)[29];
    cal_position_x -= actwk[0].xposi.w.h;
    cal_long_x = cal_position_x << 16;
    if (cal_long_x != 0) cal_long_x /= cal_long_y;

    actwk[0].xspeed.w = cal_long_x;
    actwk[0].yspeed.w = ms_work1;
    if (cal_long_y < 0) cal_long_y = -cal_long_y;
    shootwk->actfree[4] = cal_long_y >> 8;
    shootwk->actfree[5] = cal_long_y & 255;
    return;
  }


  cal_position_x = ((short*)shootwk)[29];
  cal_position_x -= actwk[0].xposi.w.h;
  cal_long_x = cal_position_x << 16;
  cal_long_x /= ms_work0;

  cal_position_y = ((short*)shootwk)[30];
  cal_position_y -= actwk[0].yposi.w.h;
  cal_long_y = cal_position_y << 16;
  if (cal_long_y != 0) cal_long_y /= cal_long_x;

  actwk[0].yspeed.w = cal_long_y;
  actwk[0].xspeed.w = ms_work0;
  if (cal_long_x < 0) cal_long_x = -cal_long_x;
  shootwk->actfree[4] = cal_long_x >> 8;
  shootwk->actfree[5] = cal_long_x & 255;
}


static void mspd_set(sprite_status* shootwk) {
  short mspdtbl[4] = { 4096, 3072, 3072, 2048 };
  short cal_mspeed;

  actwk[0].mspeed.w = 4096;
  if (shootwk->userflag.b.h < 0) return;
  cal_mspeed = mspdtbl[shootwk->userflag.b.h & 15];
  if (cal_mspeed > actwk[0].mspeed.w) actwk[0].mspeed.w = cal_mspeed;
}
