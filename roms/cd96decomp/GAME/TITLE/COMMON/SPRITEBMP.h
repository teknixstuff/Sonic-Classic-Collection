#ifndef SPRITEBMP_H
#define SPRITEBMP_H

typedef struct sprite_bmp {
  unsigned short w;
  unsigned short h;
  POINT point;
  int order;
  unsigned char palOff;
  unsigned short index;
  unsigned short reverse;
  unsigned short timing;
}
sprite_bmp;

#endif
