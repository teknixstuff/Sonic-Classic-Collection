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
#include "AMENBO.h"
#include "AWA.h"
#include "BRUNKO4.h"
#include "ESCAL4.h"
#include "ET4.h"
#include "FRIEND4.h"
#include "FUNSUI4.h"
#include "HARID4.h"
#include "HARIR4.h"
#include "KUZURE4.h"
#include "SCREW.h"
#include "SW4.h"
#include "SWBLK4.h"
#include "TAGAMEB4.h"
#include "TEKKYU.h"
#include "TOBIRA4.h"
#include "TONBO.h"
#include "WALL1.h"
#include "WALLS.h"
#include "YAGO.h"

void(*z41a_act_tbl[82])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &wave,
  &bou,
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
  &noact,
  &noact,
  &flower,
  &awa,
  &plawa,
  &harir4,
  &noact,
  &noact,
  &noact,
  &escal4,
  &sw4,
  &tobira4,
  &brunko4,
  &funsui4,
  &tonbo,
  &amenbo,
  &tagameb,
  &yago,
  &friend4,
  &swblkr4,
  &switchr4,
  &harid4,
  &walls,
  &wall1,
  &screw,
  &tekkyu,
  &noact,
  &noact,
  &kuzure4,
  &clear,
  &over,
  &title,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &et4,
  &noact
};
