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
#include "BATTA.h"
#include "BEEM6.h"
#include "BLOCK6.h"
#include "DAIR6.h"
#include "EGG6.h"
#include "ET6.h"
#include "FRIEND6.h"
#include "HACHI6.h"
#include "KDAI6.h"
#include "MINOMUSI.h"
#include "MOVIE6.h"
#include "PISTON6.h"
#include "SEESAW6.h"
#include "SEMI.h"
#include "SHOOT6.h"
#include "SW6.h"
#include "TOBIDAI6.h"
#include "TOBIRA6.h"
#include "TOGEBL6.h"
#include "TRAP_R6.h"
#include "UDBLK6.h"

void(*z62a_act_tbl[60])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &catapalt,
  &gas,
  &test_act,
  &shooter6,
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
  &ball,
  &flower,
  &piston6,
  &beem6,
  &dair6,
  &tobidai6,
  &sw6,
  &tobira6,
  &udblk6,
  &optbr6,
  &kdai6,
  &friend6,
  &block6,
  &eggz6,
  &seesaw6,
  &togeball6,
  &et6,
  &movie6,
  &batta,
  &hachi6,
  &semi,
  &minomusi,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &clear,
  &over,
  &title
};
