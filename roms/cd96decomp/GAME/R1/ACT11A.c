#include "../EQU.h"
#include "../ACT.h"
#include "../BLOCK.h"
#include "../DAI_K.h"
#include "../GOAL.h"
#include "../ITEM.h"
#include "../PLAYER.h"
#include "../PLAYSUB.h"
#include "../RING.h"
#include "../SCORE.h"
#include "../SPRING.h"
#include "../ZONE.h"
#include "DAI_RD1.h"
#include "EMIE1.h"
#include "ENEMY.h"
#include "ET1.h"
#include "FRIEND1.h"
#include "KOWASI1.h"
#include "KUZURE.h"
#include "MOVIE1.h"
#include "SHOOT1.h"
#include "SIKAKE.h"
#include "TAKI.h"
#include "TREE.h"

void(*z11a_act_tbl[64])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &taki,
  &jisin,
  &noact,
  &shooter1,
  &jisin_set,
  &dai_k,
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
  &noact,
  &noact,
  &flower,
  &kuzureru_tikei,
  &dodai,
  &ene_kamemusi,
  &ene_tama,
  &friend1,
  &noact,
  &hariyama,
  &noact,
  &tobita1,
  &noact,
  &kasoku,
  &noact,
  &hoshi,
  &et1,
  &movie1,
  &emie1,
  &heart1,
  &ana,
  &noact,
  &kage,
  &ball,
  &vfuta,
  &kowasi1,
  &noact,
  &noact,
  &noact,
  &clear,
  &over,
  &title,
  &ene_ka,
  &ene_chou,
  &ene_ari,
  &ene_tagame_a
};
