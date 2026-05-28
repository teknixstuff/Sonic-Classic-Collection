#include "../EQU.h"
#include "../ACT.h"
#include "../ACTION.h"
#include "../GOAL.h"
#include "../ITEM.h"
#include "../RING.h"
#include "../PLAYER.h"
#include "../PLAYSUB.h"
#include "../SCORE.h"
#include "../SPRING.h"
#include "../ZONE.h"
#include "BRANKO7.h"
#include "CHGBAN.h"
#include "CHGWALL7.h"
#include "DANGO7.h"
#include "ET7.h"
#include "FRIEND7.h"
#include "HOTARU7.h"
#include "KABASIRA.h"
#include "KANABUN.h"
#include "MOVIE7.h"
#include "SLIGHT7.h"
#include "TEKKYU7.h"
#include "TEKKYU7J.h"
#include "WALL7.h"

void(*z71a_act_tbl[60])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &ami,
  &noact,
  &test_act,
  &noact,
  &gun7,
  &hibana,
  &spring,
  &exit2,
  &exit2_set,
  &futa,
  &mizukiri,
  &koma,
  &ring,
  &flyring,
  &noact,
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
  &chgban,
  &spring_r,
  &flower,
  &branko7,
  &kanabun,
  &kabasira,
  &hotaru7,
  &wall7,
  &tekkyu7,
  &tekkyu7j,
  &movie7,
  &friend7,
  &et7,
  &dango7,
  &ball,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &chgwall7,
  &noact,
  &noact,
  &slight7,
  &noact,
  &clear,
  &over,
  &title
};
