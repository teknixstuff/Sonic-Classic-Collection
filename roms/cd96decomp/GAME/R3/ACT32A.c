#include "../EQU.h"
#include "../ACT.h"
#include "../ACTION.h"
#include "../BLOCK.h"
#include "../PLAYER.h"
#include "../PLAYSUB.h"
#include "../GOAL.h"
#include "../ITEM.h"
#include "../RING.h"
#include "../SCORE.h"
#include "../SPRING.h"
#include "../ZONE.h"
#include "BANPA.h"
#include "BOBIN.h"
#include "BOBINB.h"
#include "ET3.h"
#include "FRIEND3.h"
#include "GA3.h"
#include "KAMA.h"
#include "MIRACLE.h"
#include "MOVIE3.h"
#include "POCKET.h"
#include "TENTOU.h"
#include "TOGEBL3.h"
#include "TRAP_R3.h"

void(*z32a_act_tbl[60])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &noact,
  &noact,
  &test_act,
  &noact,
  &noact,
  &noact,
  &spring,
  &exit2,
  &exit2_set,
  &futa,
  &mizukiri,
  &koma,
  &ring,
  &flyring,
  &block,
  &marker,
  &bigring,
  &gene,
  &mosugu,
  &goal,
  &bakuha,
  &item,
  &item2,
  &iwa,
  &score,
  &bobin,
  &frip,
  &flower,
  &harir3,
  &frdr3,
  &trapdr3,
  &for3,
  &ene_kama,
  &tama_kama,
  &getdair3,
  &gandair3,
  &drumr3,
  &bobinbreak,
  &banpa,
  &miracle,
  &togeball3,
  &ga,
  &tentou,
  &pocket,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &ball,
  &noact,
  &et3,
  &movie3,
  &friend3,
  &clear,
  &over,
  &title
};
