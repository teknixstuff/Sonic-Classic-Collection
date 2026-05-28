#include "../EQU.h"
#include "../ACT.h"
#include "../GOAL.h"
#include "../ITEM.h"
#include "../PLAYER.h"
#include "../PLAYSUB.h"
#include "../RING.h"
#include "../SCORE.h"
#include "../SPRING.h"
#include "../ZONE.h"
#include "BOSS_1.h"
#include "DAI_RD1.h"
#include "ENEMY.h"
#include "FRIEND1.h"
#include "SIKAKE.h"

void(*z13c_act_tbl[64])(sprite_status*) = {
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
  &noact,
  &dodai,
  &ene_kamemusi,
  &ene_tama,
  &friend1,
  &noact,
  &hariyama,
  &noact,
  &tobita1,
  &noact,
  &egg1,
  &egg1body,
  &egg1leg1,
  &egg1leg2,
  &egg1leg3,
  &egg1arm1,
  &egg1arm2,
  &egg1arm3,
  &egg1arm4,
  &noact,
  &ball,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &clear,
  &over,
  &title,
  &ene_ka,
  &ene_chou,
  &ene_ari,
  &ene_tagame_a,
};
