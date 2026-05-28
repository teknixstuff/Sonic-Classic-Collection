#include "../../EQU.h"
#include "../../SPM_EQU.h"
#include "LPL_TYPES.h"
#include "SPM_EQU.h"
#include "SPS_EQU.h"
#include "PLS.h"

static void play0(void);
static void play1(void);
static void play2(void);

void(*player_acttbl[3])(void) =
{
  &play0,
  &play1,
  &play2
};
static unsigned char keyBuf[256];
extern pad_status*(*sPeriPadGet)(unsigned int);































void lplplayer(void) {
  player_acttbl[playwk.ACT_NO]();
}











static void play0(void) {
  playwk.x_posi.w.h = -40;
  playwk.y_posi.w.h = 24;
  playwk.z_posi.w.h = 64;
  playwk.k_kaku = 0;

  lplzoomwk.xscale = 2048;
  lplzoomwk.yscale = 1024;
  playwk.k_speed.w.h = 0;

  rotflg = 1;
  zoomflg = 1;
  rotspeed.w.h = 2;
  ++playwk.ACT_NO;
}











static void play1(void) {
  short iD0;
  short iD5;
  short iD6;

  if (swdata1.b.h & 128)
  {
    comflag_s |= 64;
    playwk.ACT_NO = 0;
    return;
  }

  if (comflag_m & 16)
    playwk.ACT_NO = 2;



  check_Bbtn();

  check_Cbtn();

  iD5 = playwk.z_posi.w.h;
  iD5 >>= 6;
  iD6 = -iD5;

  if (swdata1.b.h & 4)
  {
    playwk.x_posi.w.h += 8;
    iD5 += playwk.x_posi.w.h;
  }

  if (swdata1.b.h & 8)
  {
    playwk.x_posi.w.h -= 8;
    iD6 += playwk.x_posi.w.h;
  }

  if (swdata1.b.h & 1)
  {
    playwk.y_posi.w.h += 8;
    iD5 += playwk.y_posi.w.h;
  }

  if (swdata1.b.h & 2)
  {
    playwk.y_posi.w.h -= 8;
    iD6 += playwk.y_posi.w.h;
  }


  iD0 = playwk.z_posi.w.h + 336;
  if (iD0 <= playwk.x_posi.w.h)
    playwk.x_posi.w.h = iD0;

  iD0 = -playwk.z_posi.w.h;
  iD0 -= 336;
  if (iD0 >= playwk.x_posi.w.h)
    playwk.x_posi.w.h = iD0;

  iD0 = playwk.z_posi.w.h + 336;
  if (iD0 <= playwk.y_posi.w.h)
    playwk.y_posi.w.h = iD0;

  iD0 = -playwk.z_posi.w.h - 336;
  if (iD0 >= playwk.y_posi.w.h)
    playwk.y_posi.w.h = iD0;

  playwk.k_kaku += rotspeed.w.h;
  playwk.k_kaku &= 511;
}




void check_Bbtn(void) {
  if (!(swdata1.b.h & 16))
  {
    push_flg_s &= 239;
    return;
  }

  if (rotspeed.l != 0)
  {
    if (push_flg_s & 16) goto label1;

    rotspeed.l = 0;
    rotflg = -rotflg;
    push_flg_s |= 16;
    return;
  }




  if (push_flg_s & 16)
  {
    push_flg_s |= 16;
    return;
  }

label1:
  if ((short)rotflg >= 0)
    rotspeed.l += 32767 + 1;
  else
    rotspeed.l -= 32768;

  push_flg_s |= 16;
}




void check_Cbtn(void) {
  if (!(swdata1.b.h & 32))
  {
    push_flg_s &= 223;
    return;
  }

  if (zoomflg <= 0)
  {
    if (push_flg_s & 32) goto label1;

  }
  else
  {

    if (!(push_flg_s & 32)) goto label1;
  }


  zoomflg = 1;
  if (playwk.z_posi.w.h <= 1792)
    playwk.z_posi.w.h += 8;
  push_flg_s |= 32;
  return;

label1:
  zoomflg = -1;
  if (playwk.z_posi.w.h >= -112)
    playwk.z_posi.w.h -= 8;

  push_flg_s |= 32;
}














static void play2(void) {
  if (swdata1.b.h & 128)
  {
    comflag_s |= 64;
    playwk.ACT_NO = 0;
  }

  if (!(comflag_m & 16))
    playwk.ACT_NO = 1;
  playwk.k_kaku += rotspeed.w.h;
  playwk.k_kaku &= 511;
}
