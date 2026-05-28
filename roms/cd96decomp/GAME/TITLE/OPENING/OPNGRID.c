#include "../../TYPES.h"
#include "../../../services.h"
#include "../COMMON/GRID.h"


int OEGridCreate(unsigned short indx) {
  unsigned short x;
  unsigned short y;

  if (indx == 0) {
    for (y = 0; y < 28; ++y) {
      for (x = 0; x < 40; ++x) {
        SetGrid(1, x, y, 0, 0);
      }
    }
  }
  else if (indx == 1) {
    int tileh[320];
    int i;

    for (y = 0, i = 0; y < 8; y++) {
      for (x = 0; x < 40; ++x) {
        tileh[i++] = x + y * 40 + 1;
      }
    }
    for (y = 0; y < 8; ++y) {
      for (x = 0; x < 80; ++x) {
        SetGrid(1, x, 20 + y, tileh[x % 40 + (7 - y) * 40], 0);
      }
    }
  }
  else if (indx == 2) {
    int tileh[512];
    int i;

    for (y = 0, i = 0; y < 16; ++y) {
      for (x = 0; x < 32; ++x) {
        tileh[i++] = x + y * 32 + 321;
      }
    }
    for (y = 0; y < 16; ++y) {
      for (x = 0; x < 32; ++x) {
        SetGrid(0, x, y, tileh[x + (15 - y) * 32] + 0x8000, 0);
      }
      for ( ; x < 40; ++x) {
        SetGrid(0, x, y, tileh[x + (15 - y) * 32 - 32] + 0x8000, 0);
      }
    }
  }

  return 0;
}
