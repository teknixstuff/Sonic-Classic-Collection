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
#include "BEAM.h"
#include "BIGBOM8.h"
#include "DAI8.h"
#include "DANGO8.h"
#include "ET8.h"
#include "FRIEND8.h"
#include "HAGURUMA.h"
#include "JETTOGE8.h"
#include "KABUTO8.h"
#include "KOMA8.h"
#include "KUZURE8.h"
#include "LEGMECA8.h"
#include "OKUSIESO.h"
#include "PIPE8.h"
#include "PISTON.h"
#include "PLAYSP8.h"
#include "SHOOT.h"
#include "SHUT.h"
#include "SW8.h"
#include "TOBIRA.h"
#include "TRAP_R8.h"

void(*z82a_act_tbl[67])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &noact,
  &noact,
  &test_act,
  &shooter8,
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
  &beam,
  &noact,
  &flower,
  &pipe8,
  &sw,
  &haguruma,
  &bigbom,
  &kabuto,
  &kuzure8,
  &legmeca,
  &noact,
  &noact,
  &tobira,
  &noact,
  &jettoge,
  &dai8,
  &dango8,
  &noact,
  &noact,
  &gater8,
  &noact,
  &friend8,
  &togeita,
  &piston,
  &okusieso,
  &togedair8,
  &noact,
  &noact,
  &noact,
  &clear,
  &over,
  &title,
  &shut,
  &kaiten,
  &noact,
  &noact,
  &noact,
  &noact,
  &et8
};
