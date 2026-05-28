#include "../../EQU.h"
#include "LPL_TYPES.h"
#include "SPM_EQU.h"
#include "SPS_EQU.h"
#include "KAITEN.h"
#include "ETC.h"









































void kaiten0(void) {
  lplzoomwk.az = playwk.k_kaku;
  lplzoomwk.x = playwk.x_posi.w.h;
  lplzoomwk.y = playwk.y_posi.w.h;
  lplzoomwk.z = playwk.z_posi.w.h;
  k_3d();


}














void k_3d(void) {
  int_union lD0, lD1;
  short i;
  short* ptv_adr;

  k_wk.k_msx = 128;
  k_wk.k_msy = 112;
  k_wk.k_rx = 128;
  k_wk.k_ry = 112;


  lD0.l = 0;
  lD0.w.l = lplzoomwk.z + 128;
  lD0.l = lD0.w.l;
  if (lD0.l & 0x80000000) lD0.l <<= 8, lD0.l |= 0x80000000; else lD0.l <<= 8;
  lD0.w.l = lD0.l / 128;
  k_wk.k_s = lD0.w.l;

  lD0.l = 0;
  lD0.w.l = lplzoomwk.z + 128;
  lD0.l = lD0.w.l;
  lD1.l = 32768;
  lD1.w.l = lD1.l / lD0.l;
  k_wk.k_s2 = lD0.w.l;


  k_wk.k_cos = cos_planet(lplzoomwk.az);

  k_wk.k_sin = sin_planet(lplzoomwk.az);


  lD0.l = k_wk.k_cos * k_wk.k_s;

  lD0.l >>= 5;
  k_wk.k_dx = lD0.w.l;


  lD0.l = k_wk.k_sin * k_wk.k_s;

  lD0.l >>= 5;
  k_wk.k_dy = lD0.w.l;


  lD0.w.l = lplzoomwk.x - k_wk.k_rx;
  k_wk.k_x_rx = lD0.w.l;

  lD0.w.l = lplzoomwk.y - k_wk.k_ry;
  k_wk.k_y_ry = lD0.w.l;

  k_wk.k_y_ry += 88;
  lD0.l = calc_xt_r();
  lD0.l >>= 3;
  k_wk.k_xt_c = lD0.w.l;
  lD0.l = calc_yt_r();
  lD0.l >>= 3;
  k_wk.k_yt_c = lD0.w.l;





  lD0.l = k_wk.k_cos << 7;
  lD0.l >>= 8;

  lD0.w.l += k_wk.k_xt_c;
  k_wk.k_msx = lD0.w.l;


  lD0.l = k_wk.k_sin << 7;
  lD0.l >>= 8;

  lD0.w.l += k_wk.k_yt_c;
  k_wk.k_msy = lD0.w.l;


  k_wk.k_x_rx = lplzoomwk.x - k_wk.k_rx;
  k_wk.k_y_ry = lplzoomwk.y - k_wk.k_ry;

  ptv_adr = (short*)tv_adr;

  for (i = 0; i < 176; ++i) {

    lD0.l = calc_xt_r();
    lD0.l = calc_xt_s(lD0.l);
    *ptv_adr++ = lD0.w.l;

    lD0.l = calc_yt_r();
    lD0.l = calc_yt_s(lD0.l);
    *ptv_adr++ = lD0.w.l;

    *ptv_adr++ = k_wk.k_dx;
    *ptv_adr++ = k_wk.k_dy;
    ++k_wk.k_y_ry;
  }
}











int calc_xt_r(void) {
  int_union lD0, lD1, lD2;


  lD1.l = k_wk.k_cos * k_wk.k_x_rx;

  lD2.l = k_wk.k_sin * k_wk.k_y_ry;

  lD1.l -= lD2.l;


  lD0.l = 0;
  lD0.w.l = k_wk.k_rx;
  lD0.l = lD0.w.l;
  if (lD0.l & 0x80000000) lD0.l <<= 8, lD0.l |= 0x80000000; else lD0.l <<= 8;
  lD0.l += lD1.l;
  lD0.l >>= 5;
  return lD0.l;
}











int calc_xt_s(int scale) {
  int_union lD0, lD1, lD2;

  lD0.l = k_wk.k_s * scale;
  lD0.l >>= 8;

  lD2.l = k_wk.k_msx * k_wk.k_s;

  lD1.w.l = k_wk.k_msx;
  lD1.l = lD1.w.l;
  if (lD1.l & 0x80000000) lD1.l <<= 8, lD1.l |= 0x80000000; else lD1.l <<= 8;


  lD1.l -= lD2.l;
  lD1.l >>= 5;


  lD0.l += lD1.l;
  return lD0.l;
}











int calc_yt_r(void) {
  int_union lD0, lD1, lD2;


  lD1.l = k_wk.k_x_rx * k_wk.k_sin;


  lD2.l = k_wk.k_y_ry * k_wk.k_cos;


  lD2.l += lD1.l;


  lD0.l = 0;
  lD0.w.l = k_wk.k_ry;
  lD0.l = lD0.w.l;
  if (lD0.l & 0x80000000) lD0.l <<= 8, lD0.l |= 0x80000000; else lD0.l <<= 8;

  lD0.l += lD2.l;
  lD0.l >>= 5;
  return lD0.l;
}











int calc_yt_s(int scale) {
  int_union lD0, lD1, lD2;


  lD0.l = k_wk.k_s * scale;
  lD0.l >>= 8;

  lD2.l = k_wk.k_msy * k_wk.k_s;

  lD1.w.l = k_wk.k_msy;
  lD1.l = lD1.w.l;
  if (lD1.l & 0x80000000) lD1.l <<= 8, lD1.l |= 0x80000000; else lD1.l <<= 8;


  lD1.l -= lD2.l;
  lD1.l >>= 5;


  lD0.l += lD1.l;
  return lD0.l;
}
