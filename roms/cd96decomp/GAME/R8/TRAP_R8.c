#include "../EQU.h"
#include "TRAP_R8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../COLI.h"
#include "../DIRCOL.h"
#include "../LOADER2.h"
#include "../RIDECHK.h"

static void tr8_fout(sprite_status* trapwk);
static void togeita_ridechk(sprite_status* trapwk);
static void togeita_init(sprite_status* trapwk);
static void togeita_dataset(sprite_status* trapwk, sprite_status* new_actwk, unsigned char* togeita_data);
static void setitano(sprite_status* trapwk);
static void togeita_move1(sprite_status* trapwk);
static unsigned char togeita_plchk_1(sprite_status* trapwk, short cal_x);
static void togeita_move2(sprite_status* trapwk);
static void itaset_chk(sprite_status* trapwk);
static void togeita_move3(sprite_status* trapwk);
static void togeitax(sprite_status* trapwk);
static void dair8_init(sprite_status* trapwk);
static void dair8_move(sprite_status* trapwk);
static void harir8_init(sprite_status* trapwk);
static void harir8_move(sprite_status* trapwk);
static void harir8_ridechk(sprite_status* trapwk);
static void anar8_ridechk(sprite_status* trapwk);
static void anar8_rideclr(sprite_status* trapwk);
static void anar8_init(sprite_status* trapwk);
static void anar8_move1(sprite_status* trapwk);
static void anar8_move2(sprite_status* trapwk);
static void futagor8_ridechk(sprite_status* trapwk);
static void futagor8_init(sprite_status* trapwk);
static void futagor8_move1(sprite_status* trapwk);
static void tokusyu_init(sprite_status* trapwk); static void tokusyu_move(sprite_status* trapwk);


static void tr8_fout(sprite_status* trapwk) {
  unsigned short status;

  if ((status = trapwk->cdsts) == 0) { frameout(trapwk); return; }
  status = (unsigned short)time_flag + status * 3;
  flagwork[status] &= 127;
  frameout(trapwk);
}


void gater8(sprite_status* trapwk) {
  frameout(trapwk);
}


static unsigned char togeita_data0[12] = { 1, 204, 28, 8, 4, 188, 12, 8, 5, 220, 44, 8 };
static unsigned char togeita_data1[12] = { 3, 0, 24, 8, 3, 224, 24, 8, 3, 32, 24, 8 };
static unsigned char togeita_data2[12] = { 2, 52, 28, 8, 5, 36, 44, 8, 4, 68, 12, 8 };
static sprite_pattern tog00 = { 6, { { -80, -12, 0, 289 }, { -56, -12, 0, 288 }, { -24, -12, 0, 290 }, { 0, -12, 0, 290 }, { 24, -12, 0, 288 }, { 56, -12, 0, 288 } } };
static sprite_pattern tog01 = { 2, { { -28, -8, 0, 289 }, { -4, -8, 0, 288 } } };
static sprite_pattern tog02 = { 2, { { -28, -8, 0, 288 }, { 4, -8, 0, 289 } } };
static sprite_pattern tog03 = { 2, { { -24, -8, 0, 290 }, { 0, -8, 0, 290 } } };
static sprite_pattern tog04 = { 1, { { -12, -8, 0, 289 } } };
static sprite_pattern tog05 = { 3, { { -44, -8, 0, 288 }, { -12, -8, 0, 288 }, { 20, -8, 0, 289 } } };
static sprite_pattern tog06 = { 1, { { -16, -20, 0, 0 } } };
sprite_pattern* togeitapat[7] = {
  &tog00,
  &tog01,
  &tog02,
  &tog03,
  &tog04,
  &tog05,
  &tog06
};

void togeita(sprite_status* trapwk) {
  void(*tbl[4])(sprite_status*) = {
    &togeita_init,
    &togeita_move1,
    &togeita_move2,
    &togeita_move3
  };

  if (trapwk->userflag.b.h < 0) { togeitax(trapwk); return; }
  tbl[trapwk->r_no0 / 2](trapwk);
  togeita_ridechk(trapwk);
  actionsub(trapwk);
  frameout_s00(trapwk, ((short*)trapwk)[29]);
}


static void togeita_ridechk(sprite_status* trapwk) {
  short cal_position;

  if (trapwk->patno == 3) return;
  if (!(trapwk->actflg & 128)) return;
  if ((cal_position = actwk[0].yposi.w.h - trapwk->yposi.w.h) < 0)
    cal_position = -cal_position;
  if (cal_position < 32)
    ride_on_chk(trapwk, &actwk[0]);
}


static void togeita_init(sprite_status* trapwk) {
  unsigned char patchg_point;
  sprite_status* new_actwk;

  trapwk->r_no0 += 2;
  trapwk->actflg |= 4;
  trapwk->sprpri = 3;

  trapwk->patbase = togeitapat;

  setitano(trapwk);

  if (trapwk->actfree[19] == 0) {
    patchg_point = trapwk->actfree[18] * 4;
    trapwk->patno = togeita_data0[patchg_point];
    trapwk->sprhsize = togeita_data0[patchg_point + 2];
    trapwk->sprvsize = togeita_data0[patchg_point + 3];
    ((short*)trapwk)[29] = trapwk->xposi.w.h;
    ((short*)trapwk)[27] = trapwk->yposi.w.h;
    trapwk->xposi.w.h += (char)togeita_data0[patchg_point + 1];
    trapwk->actfree[17] = 1;

    if (actwkchk(&new_actwk) != 0) { tr8_fout(trapwk); return; }
    new_actwk->actno = 51;
    new_actwk->actfree[19] = 1;
    togeita_dataset(trapwk, new_actwk, togeita_data1);

    if (actwkchk(&new_actwk) != 0) { tr8_fout(trapwk); return; }
    new_actwk->actno = 51;
    new_actwk->actfree[19] = 2;
    togeita_dataset(trapwk, new_actwk, togeita_data2);
  }

  if (trapwk->patno == 3) return;
  if (actwkchk(&new_actwk) != 0) return;
  new_actwk->actno = 51;
  new_actwk->userflag.b.h = -1;
  new_actwk->xposi.w.h = trapwk->xposi.w.h;
  new_actwk->actfree[18] = trapwk->patno;
  ((unsigned short*)new_actwk)[28] = trapwk - actwk;
  ((unsigned short*)trapwk)[28] = new_actwk - actwk;
}


static void togeita_dataset(sprite_status* trapwk, sprite_status* new_actwk, unsigned char* togeita_data) {
  unsigned char patchg_point;

  patchg_point = trapwk->actfree[18] * 4;
  new_actwk->patno = togeita_data[patchg_point];
  new_actwk->sprhsize = togeita_data[patchg_point + 2];
  new_actwk->sprvsize = togeita_data[patchg_point + 3];
  ((short*)new_actwk)[29] = ((short*)trapwk)[29];

  new_actwk->yposi.w.h = trapwk->yposi.w.h;
  new_actwk->xposi.w.h = ((short*)trapwk)[29] + (short)(char)togeita_data[patchg_point + 1];

  new_actwk->userflag.b.h = trapwk->userflag.b.h;
}


static void setitano(sprite_status* trapwk) {
  unsigned char tbl2[56] = { 0, 1, 2, 1, 0, 2, 0, 0, 1, 2, 1, 2, 1, 2, 1, 2, 0, 2, 1, 2, 0, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 1, 0, 1, 2, 0, 1, 2, 2, 1, 0, 1, 2, 1, 1, 0, 2, 1, 0, 1, 2, 2 };
  unsigned char tbl3[56] = { 0, 1, 0, 2, 0, 0, 0, 0, 1, 2, 1, 2, 1, 2, 1, 2, 0, 2, 1, 2, 0, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 1, 0, 1, 2, 0, 1, 2, 2, 1, 0, 1, 2, 1, 1, 0, 2, 1, 0, 1, 2, 2 };
  unsigned char* tbls[2] = {
    tbl2,
    tbl3
  };

  trapwk->actfree[18] = tbls[stageno_i.b.l - 1][trapwk->userflag.b.h];
}


static void togeita_move1(sprite_status* trapwk) {
  short position_check, cal_x;

  if ((position_check = actwk[0].yposi.w.h - trapwk->yposi.w.h) < 0) return;
  if (position_check >= 256) return;

  if (trapwk->userflag.b.h == 0) cal_x = 48;
  else cal_x = 80;
  if (togeita_plchk_1(trapwk, cal_x)) trapwk->r_no0 += 2;
}


static unsigned char togeita_plchk_1(sprite_status* trapwk, short cal_x) {
  short position_check;

  if ((position_check = actwk[0].xposi.w.h - ((short*)trapwk)[29] + cal_x) < 0)
    return 0;
  if (position_check >= cal_x * 2) return 0;
  return 1;
}


static void togeita_move2(sprite_status* trapwk) {
  short col_data;
  int stack_yposi;
  short tbl[6] = { 8, 32, 56, 80, 104, 128 };

  if (trapwk->userflag.b.h == 0 && trapwk->actfree[19] == 0)
    itaset_chk(trapwk);
  if (trapwk->actfree[21] != 0) return;
  stack_yposi = trapwk->yposi.l;
  trapwk->yposi.w.h += tbl[trapwk->userflag.b.h];
  col_data = emycol_d(trapwk);
  trapwk->yposi.l = stack_yposi;
  if (col_data >= 0) {
    trapwk->yposi.l += 32768;
    trapwk->yspeed.w = 128;
  } else {
    trapwk->yspeed.w = 0;
    if (stageno_i.b.l == 1) {
      ((short*)trapwk)[28] = 0;
    }
    trapwk->actfree[21] = 255;
  }
}


static void itaset_chk(sprite_status* trapwk) {
  short cal_position;
  sprite_status* new_actwk;

  if ((cal_position = actwk[0].yposi.w.h - trapwk->yposi.w.h) < 0) {
    cal_position = -cal_position;
    if (cal_position >= 128) return;
  }
  if (togeita_plchk_1(trapwk, 160) == 0) return;
  switch (++((short*)trapwk)[26]) {
    case 300:
    case 600:
    case 840:
    case 1080:
     break;
    default:
      return;
  }

  if (trapwk->actfree[17] < 5) {
    if (actwkchk(&new_actwk) != 0) return;

    new_actwk->actno = 51;
    new_actwk->xposi.w.h = ((short*)trapwk)[29];
    new_actwk->yposi.w.h = ((short*)trapwk)[27] - (short)((char)trapwk->actfree[17] * 16);

    new_actwk->userflag.b.h = trapwk->actfree[17];
    ++trapwk->actfree[17];
  }
}


static void togeita_move3(sprite_status* trapwk) {
  trapwk->actno = trapwk->actno;
}


static void togeitax(sprite_status* trapwk) {
  unsigned short ride_number;
  unsigned char colitbl[6] = { 0, 156, 156, 0, 155, 157 };
  trapwk->actflg |= 4;
  trapwk->patbase = togeitapat;

  trapwk->patno = 6;


  ride_number = ((unsigned short*)trapwk)[28];
  if (actwk[ride_number].actno != 51)
  { frameout(trapwk); return; }
  trapwk->yspeed.w = actwk[ride_number].yspeed.w;
  trapwk->yposi.w.h = actwk[ride_number].yposi.w.h + 12;

  trapwk->colino = colitbl[trapwk->actfree[18]];
  actionsub(trapwk);
}


static sprite_pattern dai00 = { 1, { { -16, -16, 0, 288 } } };
static sprite_pattern z83dai00 = { 1, { { -16, -16, 0, 291 } } };
sprite_pattern* togedair8pat[1] = { &dai00 };
sprite_pattern* z83togedair8pat[1] = { &z83dai00 };
sprite_pattern** togedair8pats[3] = {
  togedair8pat,
  togedair8pat,
  z83togedair8pat
};

void togedair8(sprite_status* trapwk) {
  void(*tbl[2])(sprite_status*) = {
    &dair8_init,
    &dair8_move
  };

  if (stageno_i.b.l == 1 && trapwk->userflag.b.h == -8) { tokusyu_block(trapwk); return; }

  if (trapwk->userflag.b.h < 0) { harir8(trapwk); return; }

  tbl[trapwk->r_no0 / 2](trapwk);
  actionsub(trapwk);
  frameout_s00(trapwk, ((short*)trapwk)[29]);
}


static void dair8_init(sprite_status* trapwk) {
  sprite_status* new_actwk;

  if (stageno_i.b.l == 0) {
    trapwk->r_no0 += 2;
  }
  trapwk->actflg |= 4;

  trapwk->sprpri = 3;
  trapwk->patbase = togedair8pats[stageno_i.b.l];
  ((short*)trapwk)[29] = trapwk->xposi.w.h;
  ((short*)trapwk)[27] = trapwk->yposi.w.h;
  trapwk->sprhsize = trapwk->sprvsize = 16;
  if (actwkchk(&new_actwk) != 0) {
    if (stageno_i.b.l == 0) {
      frameout(trapwk);
    }
    else {
      dair8_move(trapwk);
    }
    return;
  }

  if (stageno_i.b.l != 0) {
    trapwk->r_no0 += 2;
  }
  if (trapwk->userflag.b.h != 1) {
    new_actwk->actno = 10;
    new_actwk->xposi.w.h = trapwk->xposi.w.h;
    new_actwk->yposi.w.h = trapwk->yposi.w.h;
    new_actwk->actfree[15] = 232;
    ((unsigned short*)new_actwk)[28] = trapwk - actwk;
    new_actwk->userflag.b.h = trapwk->userflag.b.h;
    dair8_move(trapwk);
  } else {
    new_actwk->actno = 54;
    new_actwk->userflag.b.h = -1;
    new_actwk->xposi.w.h = trapwk->xposi.w.h;
    new_actwk->yposi.w.h = trapwk->yposi.w.h;
    new_actwk->actfree[15] = 232;
    ((unsigned short*)new_actwk)[28] = trapwk - actwk;
    dair8_move(trapwk);
  }
}


static void dair8_move(sprite_status* trapwk) {
  short cal_position;

  if (!(trapwk->actflg & 128)) return;

  if ((cal_position = actwk[0].yposi.w.h - trapwk->yposi.w.h) < 0)
    cal_position = -cal_position;
  if (cal_position >= 32) return;

  hitchk(trapwk, &actwk[0]);
}


static sprite_pattern har00 = { 1, { { -16, -16, 0, 289 } } };
static sprite_pattern z83har00 = { 1, { { -16, -16, 0, 292 } } };
static sprite_pattern har01 = { 1, { { -16, -16, 16, 289 } } };
static sprite_pattern z83har01 = { 1, { { -16, -16, 16, 0 } } };
sprite_pattern* harir8pat[2] = {
  &har00,
  &har01
};
sprite_pattern* z83harir8pat[2] = {
  &z83har00,
  &z83har01
};
sprite_pattern** harir8pats[3] = {
  harir8pat,
  harir8pat,
  z83harir8pat
};

void harir8(sprite_status* trapwk) {
  unsigned short master;
  void(*tbl[2])(sprite_status*) = {
    &harir8_init,
    &harir8_move
  };

  tbl[trapwk->r_no0 / 2](trapwk);
  actionsub(trapwk);
  if ((master = ((unsigned short*)trapwk)[28]) != 0) {
    if (actwk[master].actno == 0) { frameout(trapwk); return; }
    trapwk->xposi.w.h = actwk[master].xposi.w.h + (short)(char)trapwk->actfree[14];

    trapwk->yposi.w.h = actwk[master].yposi.w.h + (short)(char)trapwk->actfree[15];
  }

  frameout_s00(trapwk, ((short*)trapwk)[29]);
}


static void harir8_init(sprite_status* trapwk) {
  int result;

  trapwk->r_no0 += 2;
  trapwk->actflg |= 4;
  if (stageno_i.b.l == 0) {
    trapwk->sprpri = 4;
  }
  else if (stageno_i.b.l == 1) {
    trapwk->sproffset = 0;
    trapwk->sprpri = 1;
  }
  else {
    trapwk->sprpri = 3;
  }
  trapwk->patbase = harir8pats[stageno_i.b.l];
  ((short*)trapwk)[29] = trapwk->xposi.w.h;
  ((short*)trapwk)[27] = trapwk->yposi.w.h;

  trapwk->sprhsize = 16;
  trapwk->sprvsize = 8;
  if (stageno_i.b.l == 1) {
    result = !(trapwk->userflag.b.h & 1);
  }
  else {
    result = trapwk->userflag.b.h != -1;
  }
  if (result) {
    trapwk->patno = 1;
    trapwk->colino = 131;
    trapwk->sprhsize = 18;
  }
  harir8_move(trapwk);
}


static void harir8_move(sprite_status* trapwk) {
  short cal_position;
  char needle_type;

  if (stageno_i.b.l == 1) {
    if ((needle_type = -trapwk->userflag.b.h) < 3) {
      harir8_ridechk(trapwk);
    } else if (needle_type < 5) {

      trapwk->sproffset = 32768;

      trapwk->colino = 131;
      if (prio_flag == 0) { harir8_ridechk(trapwk); return; }
      trapwk->colino = 0;
      ride_on_clr(trapwk, &actwk[0]);
    } else {
      trapwk->sprpri = 3;

      trapwk->colino = 131;
      if (prio_flag != 0) { harir8_ridechk(trapwk); return; }
      trapwk->colino = 0;
      ride_on_clr(trapwk, &actwk[0]);
    }
  }
  else {
    if (trapwk->patno == 0) {
      if ((cal_position = actwk[0].yposi.w.h - trapwk->yposi.w.h) < 0)
        cal_position = -cal_position;
      if (cal_position >= 32) return;

      if (hitchk(trapwk, &actwk[0]) == 0) return;
      if (!(trapwk->cddat & 8)) return;
      if (plpower_a || plpower_m) return;

      if (actwk[0].r_no0 >= 4) return;
      if (((short*)&actwk[0])[26] != 0) return;
      actwk[0].yposi.l -= actwk[0].yspeed.w << 8;
      playdamageset(&actwk[0], trapwk);
      return;
    }

    if (!(trapwk->actflg & 128)) return;

    if ((cal_position = actwk[0].yposi.w.h - trapwk->yposi.w.h) < 0)
      cal_position = -cal_position;
    if (cal_position >= 32) return;

    hitchk(trapwk, &actwk[0]);
  }
}


static void harir8_ridechk(sprite_status* trapwk) {
  if (trapwk->patno == 0) {
    trapwk->colino = 0;
    if (hitchk(trapwk, &actwk[0]) == 0) return;
    if (!(trapwk->cddat & 8)) return;

    if (plpower_a || plpower_m) return;

    if (actwk[0].r_no0 >= 4) return;
    if (((short*)&actwk[0])[26] != 0) return;
    actwk[0].yposi.l -= actwk[0].yspeed.w << 8;
    playdamageset(&actwk[0], trapwk);
    return;
  }

  if (trapwk->actflg & 128)
    hitchk(trapwk, &actwk[0]);
}


static unsigned char anar8pchgl[16] = { 7, 32, 6, 28, 5, 24, 4, 20, 3, 16, 2, 12, 1, 8, 0, 4 };
static unsigned char anar8pchgr[16] = { 15, 32, 14, 28, 13, 24, 12, 20, 11, 16, 10, 12, 9, 8, 8, 4 };
static unsigned char gater8pchgl[16] = { 0, 4, 1, 8, 2, 12, 3, 16, 4, 20, 5, 24, 6, 28, 7, 32 };
static unsigned char gater8pchgr[16] = { 8, 4, 9, 8, 10, 12, 11, 16, 12, 20, 13, 24, 14, 28, 15, 32 };
static sprite_pattern anal0 = { 1, { { -4, -8, 0, 290 } } };
static sprite_pattern anal1 = { 1, { { -8, -8, 0, 291 } } };
static sprite_pattern anal2 = { 1, { { -12, -8, 0, 292 } } };
static sprite_pattern anal3 = { 1, { { -16, -8, 0, 293 } } };
static sprite_pattern anal4 = { 1, { { -20, -8, 0, 294 } } };
static sprite_pattern anal5 = { 1, { { -24, -8, 0, 295 } } };
static sprite_pattern anal6 = { 1, { { -28, -8, 0, 296 } } };
static sprite_pattern anal7 = { 1, { { -32, -8, 0, 297 } } };
static sprite_pattern anar0 = { 1, { { -4, -8, 8, 290 } } };
static sprite_pattern anar1 = { 1, { { -8, -8, 8, 291 } } };
static sprite_pattern anar2 = { 1, { { -12, -8, 8, 292 } } };
static sprite_pattern anar3 = { 1, { { -16, -8, 8, 293 } } };
static sprite_pattern anar4 = { 1, { { -20, -8, 8, 294 } } };
static sprite_pattern anar5 = { 1, { { -24, -8, 8, 295 } } };
static sprite_pattern anar6 = { 1, { { -28, -8, 8, 296 } } };
static sprite_pattern anar7 = { 1, { { -32, -8, 8, 297 } } };
static sprite_pattern ana00 = { 1, { { -16, -20, 0, 0 } } };
static sprite_pattern ana01 = { 2, { { -64, -8, 0, 297 }, { 0, -8, 8, 297 } } };
sprite_pattern* anar8pat[18] = {
  &anal0,
  &anal1,
  &anal2,
  &anal3,
  &anal4,
  &anal5,
  &anal6,
  &anal7,
  &anar0,
  &anar1,
  &anar2,
  &anar3,
  &anar4,
  &anar5,
  &anar6,
  &anar7,
  &ana00,
  &ana01
};

void anar8(sprite_status* trapwk) {
  void(*tbl[3])(sprite_status*) = { &anar8_init, &anar8_move1, &anar8_move2 };

  tbl[trapwk->r_no0 / 2](trapwk);
  actionsub(trapwk);
  frameout_s00(trapwk, ((short*)trapwk)[29]);
}


static void anar8_ridechk(sprite_status* trapwk) {
  ridechk(trapwk, &actwk[0]);
}


static void anar8_rideclr(sprite_status* trapwk) {
  ride_on_clr(trapwk, &actwk[0]);
}


static void anar8_init(sprite_status* trapwk) {
  sprite_status* new_actwk;

  trapwk->r_no0 += 2;
  trapwk->actflg |= 4;
  trapwk->sprpri = 2;

  trapwk->patbase = anar8pat;
  trapwk->sprvsize = 8;
  trapwk->sprhsize = 4;
  trapwk->patno = 16;

  if (trapwk->actfree[20] != 0) { anar8_move1(trapwk); return; }

  trapwk->xposi.w.h -= 4;
  ((short*)trapwk)[29] = trapwk->xposi.w.h;
  if (actwkchk(&new_actwk) != 0) { frameout(trapwk); return; }
  new_actwk->actno = 55;
  new_actwk->xposi.w.h = trapwk->xposi.w.h + 128;
  new_actwk->yposi.w.h = trapwk->yposi.w.h;
  ((short*)new_actwk)[29] = ((short*)trapwk)[29];

  new_actwk->mstno.w = 1;
  new_actwk->actfree[20] = 1;
  anar8_move1(trapwk);
}


static void anar8_move1(sprite_status* trapwk) {
  short x_adder;
  unsigned char* patchg_data;

  if (trapwk->actfree[16] != 0) {
    --trapwk->actfree[16];
    anar8_rideclr(trapwk);
    return;
  }

  if (trapwk->actfree[20] == 0) {
    patchg_data = gater8pchgl;
    x_adder = 4;
  } else {
    patchg_data = gater8pchgr;
    x_adder = -4;
  }

  if (trapwk->actflg & 128) soundset(164);

  trapwk->patno = patchg_data[trapwk->actfree[19] * 2];
  trapwk->sprhsize = patchg_data[trapwk->actfree[19] * 2 + 1];
  trapwk->xposi.w.h += x_adder;
  if (++trapwk->actfree[19] == 8) {
    trapwk->actfree[16] = 60;
    trapwk->actfree[19] = 0;
    trapwk->r_no0 += 2;
  }
  anar8_ridechk(trapwk);
}


static void anar8_move2(sprite_status* trapwk) {
  short x_adder;
  unsigned char* patchg_data;

  if (trapwk->actfree[16] != 0) {
    --trapwk->actfree[16];
    anar8_ridechk(trapwk);
    return;
  }

  if (trapwk->actfree[20] == 0) {
    patchg_data = anar8pchgl;
    x_adder = -4;
  } else {
    patchg_data = anar8pchgr;
    x_adder = 4;
  }

  if (trapwk->actflg & 128) soundset(164);

  trapwk->patno = patchg_data[trapwk->actfree[19] * 2];
  trapwk->sprhsize = patchg_data[trapwk->actfree[19] * 2 + 1];
  trapwk->xposi.w.h += x_adder;
  if (++trapwk->actfree[19] == 8) {
    trapwk->actfree[16] = 60;
    trapwk->actfree[19] = 0;
    trapwk->patno = 16;
    trapwk->sprhsize = 0;
    trapwk->r_no0 -= 2;
    anar8_rideclr(trapwk);
    return;
  }
  anar8_ridechk(trapwk);
}


static unsigned char futagor8_pchg[48] = { 0, 120, 8, 56, 1, 4, 8, 40, 2, 4, 8, 24, 3, 32, 8, 8, 4, 4, 24, 8, 5, 4, 40, 8, 6, 120, 56, 8, 5, 4, 40, 8, 4, 4, 24, 8, 3, 32, 8, 8, 2, 4, 24, 8, 1, 4, 40, 8 };
static sprite_pattern fut00 = { 7, { { -8, -56, 0, 299 }, { -8, -40, 0, 299 }, { -8, -24, 0, 299 }, { -8, -8, 0, 298 }, { -8, 8, 0, 299 }, { -8, 24, 0, 299 }, { -8, 40, 0, 299 } } };
static sprite_pattern fut01 = { 5, { { -8, -40, 0, 299 }, { -8, -24, 0, 299 }, { -8, -8, 0, 298 }, { -8, 8, 0, 299 }, { -8, 24, 0, 299 } } };
static sprite_pattern fut02 = { 3, { { -8, -24, 0, 299 }, { -8, -8, 0, 298 }, { -8, 8, 0, 299 } } };
static sprite_pattern fut03 = { 1, { { -8, -8, 0, 298 } } };
static sprite_pattern fut04 = { 3, { { -24, -8, 0, 299 }, { -8, -8, 0, 298 }, { 8, -8, 0, 299 } } };
static sprite_pattern fut05 = { 5, { { -40, -8, 0, 299 }, { -24, -8, 0, 299 }, { -8, -8, 0, 298 }, { 8, -8, 0, 299 }, { 24, -8, 0, 299 } } };
static sprite_pattern fut06 = { 7, { { -56, -8, 0, 299 }, { -40, -8, 0, 299 }, { -24, -8, 0, 299 }, { -8, -8, 0, 298 }, { 8, -8, 0, 299 }, { 24, -8, 0, 299 }, { 40, -8, 0, 299 } } };
sprite_pattern* futagor8pat[7] = {
  &fut00,
  &fut01,
  &fut02,
  &fut03,
  &fut04,
  &fut05,
  &fut06
};

void futagor8(sprite_status* trapwk) {
  void(*tbl[2])(sprite_status*) = { &futagor8_init, &futagor8_move1 };

  tbl[trapwk->r_no0 / 2](trapwk);
  futagor8_ridechk(trapwk);
  actionsub(trapwk);
  frameout_s00(trapwk, ((short*)trapwk)[29]);
}


static void futagor8_ridechk(sprite_status* trapwk) {
  ride_on_chk(trapwk, &actwk[0]);
}


static void futagor8_init(sprite_status* trapwk) {
  trapwk->r_no0 += 2;
  trapwk->actflg |= 4;
  trapwk->sprpri = 3;

  trapwk->patbase = futagor8pat;
  ((short*)trapwk)[29] = trapwk->xposi.w.h;
  ((short*)trapwk)[27] = trapwk->yposi.w.h;
  futagor8_move1(trapwk);
}


static void futagor8_move1(sprite_status* trapwk) {
  unsigned char patchg_point;

  if (trapwk->actfree[16] == 0) {
    patchg_point = trapwk->actfree[18] * 4;
    trapwk->patno = futagor8_pchg[patchg_point];
    trapwk->actfree[16] = futagor8_pchg[patchg_point + 1];
    trapwk->sprhsize = futagor8_pchg[patchg_point + 2];
    trapwk->sprvsize = futagor8_pchg[patchg_point + 3];
  }
  else if (--trapwk->actfree[16] == 0) {
    if (++trapwk->actfree[18] >= 12) trapwk->actfree[18] = 0;
  }

  if (trapwk->patno != 0) trapwk->yspeed.w = 0;
  else trapwk->yspeed.w = 256;
}


static sprite_pattern tok00 = { 1, { { -24, -16, 0, 293 } } };
sprite_pattern* tokusyupat[1] = { &tok00 };

void tokusyu_block(sprite_status* trapwk) {
  void(*tbl[2])(sprite_status*) = { &tokusyu_init, &tokusyu_move };

  tbl[trapwk->r_no0 / 2](trapwk);
  actionsub(trapwk);
  frameout_s(trapwk);
}


static void tokusyu_init(sprite_status* trapwk) {
  trapwk->actflg |= 4;

  trapwk->sprpri = 3;
  trapwk->patbase = tokusyupat;
  trapwk->sprhsize = 24;
  trapwk->sprvsize = 16;
  tokusyu_move(trapwk);
}


static void tokusyu_move(sprite_status* trapwk) {
  if (prio_flag == 0) ride_on_clr(trapwk, &actwk[0]);
  else ride_on_chk(trapwk, &actwk[0]);
}
