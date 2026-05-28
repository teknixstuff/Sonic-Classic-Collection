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
#include "BOSS_5.h"
#include "DAI_RD5.h"
#include "KUZURE5.h"
#include "SHOOT5.h"

void(*z53_act_tbl[60])(sprite_status*) = {
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
  &egg5hibana,
  &egg5hari,
  &egg5belt,
  &egg5bakuha,
  &noact,
  &noact,
  &noact,
  &noact,
  &kuzure5,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &noact,
  &dair5,
  &noact,
  &egg5,
  &egg5meca1,
  &egg5meca2,
  &egg5meca3,
  &egg5pipe,
  &egg5catch,
  &egg5bomb,
  &egg5bomb2,
  &clear,
  &over,
  &title
};
