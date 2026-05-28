#include "../EQU.h"
#include "../ACT.h"
#include "../BLOCK.h"
#include "../GOAL.h"
#include "../ITEM.h"
#include "../PLAYER.h"
#include "../PLAYSUB.h"
#include "../RING.h"
#include "../SCORE.h"
#include "../SPRING.h"
#include "../ZONE.h"
#include "BANPA.h"
#include "BOBIN.h"
#include "BOBINB.h"
#include "BOSS_3.h"
#include "ET3.h"
#include "FRIEND3.h"
#include "GA3.h"
#include "GATE.h"
#include "KAMA.h"
#include "MIRACLE.h"
#include "MOVIE3.h"
#include "POCKET.h"
#include "SIKAKE33.h"
#include "TENTOU.h"
#include "TOGEBL3.h"
#include "TRAP_R3.h"

void(*z33c_act_tbl[63])(sprite_status*) = {
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
  &noact,
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
  &egg3dai_s,
  &egg3dai_l,
  &egg3haguruma,
  &egg3,
  &noact,
  &ball,
  &sikake33,
  &et3,
  &movie3,
  &friend3,
  &clear,
  &over,
  &title,
  &egg3cannon,
  &punchbom,
  &gate
};
