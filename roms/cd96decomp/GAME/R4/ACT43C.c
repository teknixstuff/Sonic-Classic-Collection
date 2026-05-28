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
#include "BOSS_4.h"
#include "BOSS_4_2.h"
#include "FRIEND4.h"
#include "RENKETU4.h"
#include "TONBO.h"
#include "WALL1.h"
#include "WALL4.h"

void(*z43c_act_tbl[80])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &wave,
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
  &awa,
  &plawa,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &tonbo,
  &noact,
  &noact,
  &noact,
  &friend4,
  &noact,
  &noact,
  &noact,
  &noact,
  &wall1,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
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
  &wall4,
  &noact,
  &noact,
  &egg4air,
  &egg4airhead,
  &egg4,
  &egg4meca,
  &egg4tama,
  &egg4awa,
  &noact
};
