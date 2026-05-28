#include "EQU.h"
#include "R3/PLAYSP3.h"
#include "R5/PLAYSP5.h"
#include "R7/PLAYSP7.h"
#include "R8/PLAYSP8.h"


void playsp(void) {
  switch (stageno_i.b.h) {
    case 1:
      if (actwk[0].mstno.b.h != 43) boyo();
      break;
    case 3:
      belt();
      break;
    case 5:
      playsp7();
      break;
    case 6:
      playsp8();
      break;
  }
}
