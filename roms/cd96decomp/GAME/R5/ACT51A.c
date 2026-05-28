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
#include "BELTSW5.h"
#include "BURANKO5.h"
#include "DAI_RD5.h"
#include "DENDEN.h"
#include "ET5.h"
#include "FRIEND5.h"
#include "HARI5F.h"
#include "HARIR5.h"
#include "HASHI5.h"
#include "HASIRA5.h"
#include "IWA5.h"
#include "IWA5ROLL.h"
#include "IWA5WAVE.h"
#include "KEMUSI.h"
#include "KOWASI5.h"
#include "KUMO.h"
#include "KUZURE5.h"
#include "MOVIE5.h"
#include "SASORI.h"
#include "SHOOT5.h"

void(*z51a_act_tbl[60])(sprite_status*) = {
  &play00,
  &play00,
  &baria,
  &noact,
  &noact,
  &test_act,
  &shooter5,
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
  &denden,
  &sasori,
  &kemusi,
  &kumo,
  &iwa5,
  &hari5f,
  &harir5,
  &iwa5roll,
  &kuzure5,
  &iwa5wave,
  &buranko5,
  &hasira5,
  &movie5,
  &friend5,
  &et5,
  &hashi5,
  &dair5,
  &beltsw5,
  &kowasi5,
  &noact,
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
