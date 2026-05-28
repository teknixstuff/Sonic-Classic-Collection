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
#include "AWA.h"
#include "BANEIWA.h"
#include "DAID4.h"
#include "FRIEND4.h"
#include "LRBLK4.h"
#include "HARIR4.h"
#include "SW4.h"
#include "AMENBO.h"
#include "KOWASI4.h"
#include "KUZURE4.h"
#include "RENKETU4.h"
#include "SCREW.h"
#include "TAGAMEB4.h"
#include "TEKKYU.h"
#include "TEKKYU1.h"
#include "TEKKYU4.h"
#include "TOBIRA4.h"
#include "TOBIRAS4.h"
#include "TONBO.h"
#include "UDBLK4.h"
#include "WALL1.h"
#include "WALLS.h"
#include "YAGO.h"

void(*z42c_act_tbl[80])(sprite_status*) = {
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
  &udblk4,
  &lrblk4,
  &tobiras4,
  &noact,
  &sw4,
  &tobira4,
  &noact,
  &noact,
  &tonbo,
  &amenbo,
  &tagameb,
  &yago,
  &friend4,
  &noact,
  &noact,
  &noact,
  &walls,
  &wall1,
  &screw,
  &tekkyu,
  &tekkyu1,
  &tekkyu4,
  &kuzure4,
  &clear,
  &over,
  &title,
  &noact,
  &renketu4,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &baneiwa,
  &daid4,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &kowasi4
};
