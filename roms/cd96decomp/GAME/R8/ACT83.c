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
#include "../R3/BOBIN.h"
#include "BOSS_8.h"
#include "DAI8.h"
#include "EMIE8.h"
#include "FRIEND8.h"
#include "HAGURUMA.h"
#include "HOTARU8.h"
#include "JETTOGE8.h"
#include "KABUTO8.h"
#include "KOMA8.h"
#include "KONBEA.h"
#include "KUZURE8.h"
#include "NOKOGIRI.h"
#include "PISTON.h"
#include "PLAYSP8.h"
#include "SHUT.h"
#include "SW8.h"
#include "TOBIRA.h"
#include "TRAP_R8.h"

void(*z83_act_tbl[67])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &noact,
  &noact,
  &test_act,
  &noact,
  &noact,
  &chibi_coli,
  &spring,
  &exit2,
  &exit2_set,
  &futa,
  &mizukiri,
  &koma8,
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
  &bobin,
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
  &noact,
  &tobira,
  &konbea,
  &jettoge,
  &dai8,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &friend8,
  &togeita,
  &piston,
  &noact,
  &togedair8,
  &noact,
  &noact,
  &hotaru8,
  &clear,
  &over,
  &title,
  &shut,
  &kaiten,
  &egg8,
  &egg8hane,
  &egg8meca,
  &egg8hibana,
  &emie8
};
