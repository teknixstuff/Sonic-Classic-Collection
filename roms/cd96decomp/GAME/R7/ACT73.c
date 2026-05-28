#include "../EQU.h"
#include "../ACT.h"
#include "../ACTION.h"
#include "../GOAL.h"
#include "../ITEM.h"
#include "../PLAYER.h"
#include "../PLAYSUB.h"
#include "../RING.h"
#include "../SCORE.h"
#include "../SPRING.h"
#include "../ZONE.h"
#include "BOSS_7.h"
#include "BRANKO7.h"
#include "CHGBAN.h"
#include "CHGWALL7.h"
#include "EMIE7.h"
#include "FRIEND7.h"
#include "GAITOU73.h"
#include "HARI73.h"
#include "MOVIE7.h"
#include "TEKKYU7.h"
#include "TEKKYU7J.h"
#include "WALL7.h"
#include "WALL73.h"

void(*z73_act_tbl[60])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &ami,
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
  &noact,
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
  &noact,
  &noact,
  &flower,
  &branko7,
  &noact,
  &noact,
  &noact,
  &wall7,
  &tekkyu7,
  &tekkyu7j,
  &movie7,
  &friend7,
  &noact,
  &noact,
  &wall73,
  &egg7,
  &egg7jet,
  &egg7beam,
  &msnc,
  &msnc_ele,
  &msnc_bara,
  &hari73,
  &emie7,
  &heart7,
  &chgwall7,
  &gaitou73,
  &hahen73,
  &noact,
  &noact,
  &clear,
  &over,
  &title
};
