#include "../EQU.h"
#include "BANPA.h"
#include "../ACTION.h"
#include "../ACTSET.h"
#include "../LOADER2.h"

static void act_init(sprite_status* bumperwk);
static void act_move(sprite_status* bumperwk);

static sprite_pattern bmp00 = {
  1,
  { { -32, -16, 0, 315 } }
};
sprite_pattern* banpa_pat[1] = { &bmp00 };















void banpa(sprite_status* bumperwk) {
  void(*act_tbl[2])(sprite_status*) = { &act_init, &act_move };

  act_tbl[bumperwk->r_no0 / 2](bumperwk);
  actionsub(bumperwk);
  frameout_s00(bumperwk, ((short*)bumperwk)[33]);
}



static void act_init(sprite_status* bumperwk) {
  ((short*)bumperwk)[33] = bumperwk->xposi.w.h;

  bumperwk->r_no0 += 2;
  bumperwk->patbase = banpa_pat;

  bumperwk->actflg = 4;
  bumperwk->sprhsize = 32;
  bumperwk->sprvsize = 16;
  bumperwk->sprpri = 1;
  bumperwk->colino = 231;

  ((short*)bumperwk)[26] = 192;
  ((short*)bumperwk)[25] = 96;
  if (!((unsigned char)bumperwk->userflag.b.h & 128)) {
    ((short*)bumperwk)[26] = 160;
    ((short*)bumperwk)[25] = 80;
  }
  if (bumperwk->userflag.b.h & 64)
    *(int*)&bumperwk->actfree[0] = 65536;
  else
    *(int*)&bumperwk->actfree[0] = -65536;
}



static void act_move(sprite_status* bumperwk) {
  if (bumperwk->colicnt != 0) {
    if ((char)bumperwk->actflg < 0) soundset(181);

    bumperwk->colicnt = 0;


    if ((unsigned short)(actwk[0].yposi.w.h - bumperwk->yposi.w.h + 8) < 16) {
      actwk[0].xspeed.w = 0;
    }
    else {


      if ((unsigned short)(actwk[0].xposi.w.h - bumperwk->xposi.w.h + 24) < 48) {
        if (actwk[0].yposi.w.h >= bumperwk->yposi.w.h)
          actwk[0].yspeed.w = 1792;
        else
          actwk[0].yspeed.w = -1792;
      }
      else {

        if (actwk[0].xposi.w.h >= bumperwk->xposi.w.h) actwk[0].xspeed.w = 1267;
        else actwk[0].xspeed.w = -1267;
        if (actwk[0].yposi.w.h >= bumperwk->yposi.w.h) actwk[0].yspeed.w = 1267;
        else actwk[0].yspeed.w = -1267;
      }

      actwk[0].cddat |= 2;
      actwk[0].cddat &= 207;
    }
  }
  if (bumperwk->userflag.b.h < 0)
    bumperwk->xposi.l += *(int*)&bumperwk->actfree[0];
  else
    bumperwk->yposi.l += *(int*)&bumperwk->actfree[0];

  if (--((unsigned short*)bumperwk)[25] == 0) {
    ((unsigned short*)bumperwk)[25] = ((unsigned short*)bumperwk)[26];

    *(int*)&bumperwk->actfree[0] *= -1;
  }
}
