#include "EQU.h"
#include "IO.h"









int random(void) {
  int_union lD0, lD1;
  unsigned short w;

  lD1.l = ranum;
  if (ranum == 0) lD1.l = 711800410;
  lD0.l = lD1.l;
  if (lD1.l < 0) {
    lD1.l *= 4;
    lD1.l |= 0x80000000;
  }
  else {
    lD1.l *= 4;
  }
  lD1.l += lD0.l;
  if (lD1.l < 0) {
    lD1.l *= 8;
    lD1.l |= 0x80000000;
  }
  else {
    lD1.l *= 8;
  }
  lD1.l += lD0.l;
  lD0.w.l += lD1.w.l;

  w = lD1.w.h;
  lD1.w.h = lD1.w.l;
  lD1.w.l = w;

  lD0.w.l += lD1.w.l;
  lD1.w.l = lD0.w.l;

  w = lD1.w.h;
  lD1.w.h = lD1.w.l;
  lD1.w.l = w;

  ranum = lD1.l;
  return lD0.l;
}


int random2(void) {
  int_union d0, d1;
  short tmp;

  d1.l = ranum;
  if (d1.l == 0)
  {
    d1.l = 711800410;
  }
  d0.l = d1.l;
  d1.l <<= 2;
  d1.l += d0.l;
  d1.l <<= 3;
  d1.l += d0.l;
  d0.l = d1.l;
  tmp = d1.w.h;
  d1.w.h = d1.w.l;
  d0.w.l = tmp;
  d0.w.l += d1.w.l;
  d1.w.l = d0.w.l;
  tmp = d1.w.h;
  d1.w.h = d1.w.l;
  d0.w.l = tmp;
  ranum = d1.l;

  return d0.l;
}


void scrinit(void) {
  vscroll.l = 0;
  hscroll.l = 0;
}
