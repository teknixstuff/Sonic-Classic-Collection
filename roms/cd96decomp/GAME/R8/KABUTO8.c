#include "../EQU.h"
#include "KABUTO8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../LOADER2.h"
#include "../PLAYSUB.h"
#include "../SUICIDE.h"

static void kabuto0(sprite_status* kabutowk); static void a_init(sprite_status* kabutowk); static void a_fall(sprite_status* kabutowk); static void a_move(sprite_status* kabutowk);
static void kabuto1(sprite_status* tunowk); static void b_init(sprite_status* tunowk); static void b_move(sprite_status* tunowk);





void kabuto(sprite_status* kabutowk) {
  if (kabutowk->userflag.b.l >= 0) kabuto0(kabutowk);
  else kabuto1(kabutowk);
}




static sprite_pattern z81cub00 = { 1, { { -24, -16, 0, 300 } } };
static sprite_pattern z82cub00 = { 1, { { -24, -16, 0, 309 } } };
static sprite_pattern z83cub00 = { 1, { { -24, -16, 0, 302 } } };
sprite_pattern* z81_pat_kabuto[1] = { &z81cub00 };
sprite_pattern* z82_pat_kabuto[1] = { &z82cub00 };
sprite_pattern* z83_pat_kabuto[1] = { &z83cub00 };
sprite_pattern** pats_kabuto[3] = {
  z81_pat_kabuto,
  z82_pat_kabuto,
  z83_pat_kabuto
};

static void kabuto0(sprite_status* kabutowk) {
  void(*tbl[3])(sprite_status*) = { &a_init, &a_fall, &a_move };
  if (enemy_suicide(kabutowk)) return;
  tbl[kabutowk->r_no0 / 2](kabutowk);
  actionsub(kabutowk);
  frameout_s00(kabutowk, ((short*)kabutowk)[26]);
}



static void a_init(sprite_status* kabutowk) {
  sprite_status* new_actwk;

  ((short*)kabutowk)[26] = kabutowk->xposi.w.h;

  kabutowk->actflg |= 4;
  kabutowk->sprpri = 4;

  kabutowk->patbase = pats_kabuto[stageno_i.b.l];
  kabutowk->sprhsize = 24;
  kabutowk->sprvsize = 14;
  kabutowk->colino = 42;
  ((int*)kabutowk)[12] = -20480;
  kabutowk->r_no0 += 2;
  if (actwkchk2(kabutowk, &new_actwk) != 0) {
    frameout(kabutowk);
    return;
  }
  new_actwk->actno = kabutowk->actno;
  new_actwk->userflag.b.h = kabutowk->userflag.b.h;
  new_actwk->userflag.b.l = -1;
  new_actwk->xposi.w.h = kabutowk->xposi.w.h;
  new_actwk->yposi.w.h = kabutowk->yposi.w.h;
  ((unsigned short*)new_actwk)[33] = kabutowk - actwk;
  if (kabutowk->userflag.b.l != 0) {
    kabutowk->actflg |= 1;
    kabutowk->cddat |= 1;
    new_actwk->actflg |= 1;
    new_actwk->cddat |= 1;
  }
  a_fall(kabutowk);
}



static void a_fall(sprite_status* kabutowk) {
  short colli_data;

  kabutowk->yposi.l += 65536;
  if ((colli_data = emycol_d(kabutowk)) < 0) {
    kabutowk->yposi.w.h += colli_data;
    kabutowk->r_no0 += 2;
  }
}



static void a_move(sprite_status* kabutowk) {
  if ((char)kabutowk->actflg < 0 && !(++((short*)kabutowk)[27] & 31)) {

    soundset(177);
  }
  kabutowk->xposi.l += ((int*)kabutowk)[12];

  kabutowk->yposi.w.h += emycol_d(kabutowk);

  if (--((short*)kabutowk)[23] < 0) {
    ((short*)kabutowk)[23] = 409;
    ((int*)kabutowk)[12] = -((int*)kabutowk)[12];
  }

}









static unsigned char p00[4] = { 2, 0, 1, 255 };
static unsigned char p01[4] = { 2, 2, 3, 255 };
static unsigned char* pchg[2] = { p00, p01 };
static sprite_pattern z81hea00 = { 2, { { -8, -8, 0, 302 }, { -12, -16, 0, 301 } } };
static sprite_pattern z82hea00 = { 2, { { -8, -8, 0, 311 }, { -12, -16, 0, 310 } } };
static sprite_pattern z83hea00 = { 2, { { -8, -8, 0, 304 }, { -12, -16, 0, 303 } } };
static sprite_pattern z81hea01 = { 2, { { -8, -8, 0, 302 }, { -12, -17, 16, 301 } } };
static sprite_pattern z82hea01 = { 2, { { -8, -8, 0, 311 }, { -12, -17, 16, 310 } } };
static sprite_pattern z83hea01 = { 2, { { -8, -8, 0, 304 }, { -12, -17, 16, 303 } } };
static sprite_pattern z81hea02 = { 2, { { -4, -2, 0, 303 }, { -12, -16, 0, 301 } } };
static sprite_pattern z82hea02 = { 2, { { -4, -2, 0, 312 }, { -12, -16, 0, 310 } } };
static sprite_pattern z83hea02 = { 2, { { -4, -2, 0, 305 }, { -12, -16, 0, 303 } } };
static sprite_pattern z81hea03 = { 2, { { -4, -2, 0, 303 }, { -12, -17, 16, 301 } } };
static sprite_pattern z82hea03 = { 2, { { -4, -2, 0, 312 }, { -12, -17, 16, 310 } } };
static sprite_pattern z83hea03 = { 2, { { -4, -2, 0, 305 }, { -12, -17, 16, 303 } } };
static sprite_pattern* z81pat[4] = {
  &z81hea00,
  &z81hea01,
  &z81hea02,
  &z81hea03
};
static sprite_pattern* z82pat[4] = {
  &z82hea00,
  &z82hea01,
  &z82hea02,
  &z82hea03
};
static sprite_pattern* z83pat[4] = {
  &z83hea00,
  &z83hea01,
  &z83hea02,
  &z83hea03
};
static sprite_pattern** pats[3] = {
  z81pat,
  z82pat,
  z83pat
};

void kabuto1(sprite_status* tunowk) {
  void(*tbl[2])(sprite_status*) = { &b_init, &b_move };
  tbl[tunowk->r_no0 / 2](tunowk);
  actionsub(tunowk);
}



static void b_init(sprite_status* tunowk) {
  tunowk->r_no0 += 2;
  tunowk->actflg |= 4;
  tunowk->sprpri = 3;
  tunowk->patbase = pats[stageno_i.b.l];
  tunowk->sprhsize = 12;
  tunowk->sprvsize = 16;
  tunowk->colino = 171;
}



static void b_move(sprite_status* tunowk) {
  sprite_status* bodywk;

  bodywk = &actwk[((unsigned short*)tunowk)[33]];
  if (bodywk->actno != 36) { frameout(tunowk); return; }
  if (tunowk->userflag.b.h) goto label1;

  if (--((short*)tunowk)[23] < 0) {
    ((short*)tunowk)[23] = 60;
    tunowk->mstno.b.h ^= 1;
label1:
    ((short*)tunowk)[24] = -25;
    ((short*)tunowk)[25] = 0;
    if (tunowk->mstno.b.h) {
      ((short*)tunowk)[24] = -19;
      ((short*)tunowk)[25] = -15;
    }
    if (tunowk->actflg & 1) {
      ((short*)tunowk)[24] = -((short*)tunowk)[24];
    }
  }

  tunowk->xposi.w.h = bodywk->xposi.w.h + ((short*)tunowk)[24];
  tunowk->yposi.w.h = bodywk->yposi.w.h + ((short*)tunowk)[25];

  patchg(tunowk, pchg);
}
