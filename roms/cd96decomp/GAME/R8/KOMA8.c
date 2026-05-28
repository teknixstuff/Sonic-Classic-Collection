#include "../EQU.h"
#include "KOMA8.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../DIRCOL.h"
#include "../DUMMY.h"
#include "../PLAYSUB.h"

static void koma_init(sprite_status* komawk);
static void koma_move(sprite_status* komawk);
static void koma_move2(sprite_status* komawk);

static unsigned char komachg0[4] = { 8, 0, 1, 255 };
static unsigned char* komachg[1] = { komachg0 };
static sprite_pattern z81kom00 = { 1, { { -8, -8, 0, 304 } } };
static sprite_pattern z82kom00 = { 1, { { -8, -8, 0, 313 } } };
static sprite_pattern z83kom00 = { 1, { { -8, -8, 0, 306 } } };
static sprite_pattern z81kom01 = { 1, { { -8, -8, 0, 305 } } };
static sprite_pattern z82kom01 = { 1, { { -8, -8, 0, 314 } } };
static sprite_pattern z83kom01 = { 1, { { -8, -8, 0, 307 } } };
sprite_pattern* z81koma8pat[2] = {
  &z81kom00,
  &z81kom01
};
sprite_pattern* z82koma8pat[2] = {
  &z82kom00,
  &z82kom01
};
sprite_pattern* z83koma8pat[2] = {
  &z83kom00,
  &z83kom01
};
sprite_pattern** koma8pats[3] = {
  z81koma8pat,
  z82koma8pat,
  z83koma8pat
};





void koma8(sprite_status* komawk) {
  void(*tbl[3])(sprite_status*) = { &koma_init, &koma_move, &koma_move2 };
  tbl[komawk->r_no0 / 2](komawk);
  frameout_s00(komawk, ((short*)komawk)[29]);
}



static void koma_init(sprite_status* komawk) {
  sprite_status* sprwk;

  komawk->r_no0 += 2;
  komawk->actflg |= 4;
  komawk->sprpri = 4;
  komawk->patbase = koma8pats[stageno_i.b.l];
  komawk->sprhsize = 8;
  komawk->sprvsize = 6;
  ((short*)komawk)[29] = komawk->xposi.w.h;
  komawk->xspeed.w = 256;
  pa_set(0, 0);
  if (actwkchk2(komawk, &sprwk) != 0) { frameout(komawk); return; };
  sprwk->actno = 10;
  sprwk->xposi.w.h = komawk->xposi.w.h;
  sprwk->yposi.w.h = komawk->yposi.w.h - 16;
  sprwk->actfree[15] = 240;
  ((unsigned short*)sprwk)[28] = komawk - actwk;
  sprwk->userflag.b.h = komawk->userflag.b.h & 15;

  ((short*)komawk)[31] = 80;
  if (komawk->userflag.b.h < 0) ((short*)komawk)[31] = 64;
  koma_move(komawk);
}


static void koma_move(sprite_status* komawk) {
  short colli_data;

  if ((colli_data = emycol_d(komawk)) < 0) {
    komawk->yposi.w.h += colli_data;
    ((short*)komawk)[27] = komawk->yposi.w.h;
    komawk->r_no0 += 2;
  } else {
    ++komawk->yposi.w.h;
  }
}


static void koma_move2(sprite_status* komawk) {
  short colli_data, pos_data;

  if (komawk->xspeed.w >= 0) colli_data = emycol_r(komawk, 32);
  else colli_data = emycol_l(komawk, 232);
  if (colli_data < 7) goto label1;

  if ((pos_data = komawk->xposi.w.h - ((short*)komawk)[29]) < 0)
    pos_data = -pos_data;
  if (pos_data >= ((short*)komawk)[31]) goto label1;

  if ((colli_data = emycol_d(komawk)) < -7) goto label1;
  if (colli_data > 7) goto label1;
  komawk->yposi.w.h += colli_data;
  goto label2;
label1:
    komawk->xspeed.w = -komawk->xspeed.w;
label2:
  speedset2(komawk);
  patchg(komawk, komachg);
  actionsub(komawk);
}
