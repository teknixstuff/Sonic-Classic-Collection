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
#include "DAI8.h"
#include "ET8.h"
#include "FRIEND8.h"
#include "HACHI8.h"
#include "HAGURUMA.h"
#include "KABUTO8.h"
#include "KOMA8.h"
#include "KONBEA.h"
#include "KUZURE8.h"
#include "NOKOGIRI.h"
#include "OKUSIESO.h"
#include "PISTON.h"
#include "PROPERA8.h"
#include "SCARAB.h"
#include "SW8.h"
#include "TOBIRA.h"
#include "TRAP_R8.h"

void(*z81a_act_tbl[67])(sprite_status*) = {
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
  &koma8,
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
  &noact,
  &sw,
  &haguruma,
  &noact,
  &kabuto,
  &kuzure8,
  &noact,
  &nokogiri,
  &propera,
  &tobira,
  &konbea,
  &noact,
  &dai8,
  &noact,
  &hachi8,
  &scarab,
  &noact,
  &noact,
  &friend8,
  &noact,
  &piston,
  &okusieso,
  &togedair8,
  &anar8,
  &futagor8,
  &noact,
  &clear,
  &over,
  &title,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &et8
};
