#include "../EQU.h"
#include "PISTON.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../ETC.h"
#include "../RIDECHK.h"

static void piston_init(sprite_status* pistonwk);
static void init_piston0(sprite_status* pistonwk);
static void init_piston1(sprite_status* pistonwk);
static void piston_move(sprite_status* pistonwk);

static sprite_pattern z81pis00 = { 1, { { -32, -31, 0, 308 } } };
static sprite_pattern z82pis00 = { 1, { { -32, -31, 0, 317 } } };
static sprite_pattern z83pis00 = { 1, { { -32, -31, 0, 310 } } };
static sprite_pattern z81pis01 = { 3, { { -32, -95, 0, 308 }, { -32, -31, 0, 308 }, { -32, 33, 0, 308 } } };
static sprite_pattern z82pis01 = { 3, { { -32, -95, 0, 317 }, { -32, -31, 0, 317 }, { -32, 33, 0, 317 } } };
static sprite_pattern z83pis01 = { 3, { { -32, -95, 0, 310 }, { -32, -31, 0, 310 }, { -32, 33, 0, 310 } } };
static sprite_pattern z81pis02 = { 1, { { -32, -19, 0, 309 } } };
static sprite_pattern z82pis02 = { 1, { { -32, -19, 0, 318 } } };
static sprite_pattern z83pis02 = { 1, { { -32, -19, 0, 311 } } };
static sprite_pattern pis03 = { 1, { { -16, -20, 0, 0 } } };
sprite_pattern* z81pistonpat[4] = {
  &z81pis00,
  &z81pis01,
  &z81pis02,
  &pis03
};
sprite_pattern* z82pistonpat[4] = {
  &z82pis00,
  &z82pis01,
  &z82pis02,
  &pis03
};
sprite_pattern* z83pistonpat[4] = {
  &z83pis00,
  &z83pis01,
  &z83pis02,
  &pis03
};
sprite_pattern** pistonpats[3] = {
  z81pistonpat,
  z82pistonpat,
  z83pistonpat
};















void piston(sprite_status* pistonwk) {
  void(*piston_tbl[2])(sprite_status*) = { &piston_init, &piston_move };
  piston_tbl[pistonwk->r_no0 / 2](pistonwk);
  actionsub(pistonwk);
  frameout_s(pistonwk);
}



static void piston_init(sprite_status* pistonwk) {
  char tbl_index;
  short cal_rad, cal_radius, sin_tmp, cos_tmp;
  int sin_data;
  void(*act_tbl[3])(sprite_status*) = {
    &init_piston0,
    &init_piston1,
    &init_piston0
  };
  short rad_tbl[4] = { 0, 256, 512, 768 };

  short radius_tbl[2] = { 32, 48 };

  pistonwk->r_no0 += 2;
  pistonwk->actflg |= 4;
  pistonwk->patbase = pistonpats[stageno_i.b.l];

  pistonwk->sprpri = 3;
  ((short*)pistonwk)[26] = pistonwk->yposi.w.h;
  pistonwk->yspeed.w = pistonwk->xspeed.w = 0;




  tbl_index = pistonwk->userflag.b.h & 48;
  tbl_index >>= 4;

  cal_rad = ((short*)pistonwk)[27] = rad_tbl[tbl_index];
  tbl_index = pistonwk->userflag.b.h & 64;
  tbl_index >>= 6;
  cal_radius = ((short*)pistonwk)[29] = radius_tbl[tbl_index];
  sinset((char)(cal_rad >> 2), &sin_tmp, &cos_tmp);
  sin_data = sin_tmp;
  sin_data *= cal_radius;
  sin_data >>= 8;
  sin_data += ((short*)pistonwk)[26];
  act_tbl[pistonwk->userflag.b.h & 3](pistonwk);
}





static short spd_tbl[4] = { 4, 8, 16, 32 };

static void init_piston0(sprite_status* pistonwk) {
  pistonwk->patno = 0;
  pistonwk->sprhsize = pistonwk->sprvsize = 32;
  ((short*)pistonwk)[28] = spd_tbl[(pistonwk->userflag.b.h & 12) / 4];

}




static void init_piston1(sprite_status* pistonwk) {
  unsigned char delay_time_tbl[2] = { 60, 90 };

  pistonwk->patno = 1;
  pistonwk->sprhsize = 32;
  pistonwk->sprvsize = 96;
  ((short*)pistonwk)[28] = spd_tbl[(pistonwk->userflag.b.h & 4) / 4];

  pistonwk->actfree[14] = delay_time_tbl[(pistonwk->userflag.b.h & 8) / 8];

  pistonwk->actfree[20] = 0;
}





static void piston_move(sprite_status* pistonwk) {
  short cal_posi, cal_rad, sin_tmp, cos_tmp;
  int stack_yposi, sin_data, cal_yposi;
  short jump_tbl[2] = {
    -4096, -2560
  };

  if (pistonwk->yspeed.w < 0) ride_on_chk(pistonwk, &actwk[0]);
  stack_yposi = pistonwk->yposi.l;
  if ((pistonwk->userflag.b.h & 3) == 1) {

    if (pistonwk->actfree[20] & 128) {
      cal_posi = pistonwk->yposi.w.h;
      if ((char)--pistonwk->actfree[16] >= 0) goto label1;

      pistonwk->actfree[20] &= 127;
    }
    else {
      cal_posi = ((short*)pistonwk)[27];
      if (cal_posi == 256 || cal_posi == 768) {

        pistonwk->actfree[20] |= 128;
        pistonwk->actfree[16] = pistonwk->actfree[14];
        cal_posi = pistonwk->yposi.w.h;
        goto label1;
      }
    }
  }

  cal_rad = ((short*)pistonwk)[27] + ((short*)pistonwk)[28];

  cal_rad &= 1023;
  ((short*)pistonwk)[27] = cal_rad;
  sinset((char)(cal_rad >> 2), &sin_tmp, &cos_tmp);
  sin_data = sin_tmp;
  sin_data *= ((short*)pistonwk)[29];
  sin_data >>= 8;
  sin_data += ((short*)pistonwk)[26];
  cal_posi = sin_data;
label1:
  pistonwk->yposi.w.h = cal_posi;
  cal_yposi = (cal_posi << 16) - stack_yposi;
  pistonwk->yspeed.w = cal_yposi >> 8;
  if ((pistonwk->userflag.b.h & 3) == 1) {


    if (((short*)pistonwk)[27] == 528) {

      if (ride_on_chk(pistonwk, &actwk[0]) == 0) return;

      actwk[0].yspeed.w = jump_tbl[((unsigned char)pistonwk->userflag.b.h & 128) >> 7];
      actwk[0].cddat |= 2;
      actwk[0].cddat &= 247;
      actwk[0].mstno.b.h = 16;
      pistonwk->cddat &= 247;
    }
  }
  if (pistonwk->yspeed.w >= 0)
    ride_on_chk(pistonwk, &actwk[0]);
}
