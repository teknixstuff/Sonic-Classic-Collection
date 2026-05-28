#include "../EQU.h"
#include "SIKAKE33.h"
#include "LIGHT.h"
#include "ROLLPLAT.h"
#include "STOPPER.h"











void sikake33(sprite_status* actionwk) {

  if (actionwk->userflag.b.h < 0) kaitenban(actionwk);
  else {
    if (actionwk->userflag.b.h == 0) light(actionwk);
    else stopper(actionwk);
  }
}
