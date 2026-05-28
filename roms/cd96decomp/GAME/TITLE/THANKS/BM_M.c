#include "../../EQU.h"
#include "../COMMON/SCORE_DATA_TYPES.h"
#include "THANKS_TYPES.h"
#include "BM_M.h"
#include <string.h>
#include "../../../services.h"
#include "ACT.h"
#include "CHRSET.h"
#include "GAME.h"

static void player(void);

extern short prg_mode;
extern short actset_tm[8];
high_score_entry highscores[84];
char GreatestPlayer[4];
extern score_data g_current_score_data;
extern unsigned char quit_flg;

































void mainloop(void) {
  void(*prg_tbl[2])(void) =
  {
    &get_tmdata,
    &get_keydata
  };

  prg_tbl[prg_mode]();
}




void get_tmdata(void) {
  get_usrname();
  dsp_usrname();

  actset_tm[0] = 600;
  actset_tm[1] = 0;
  actset_tm[2] = 0;
  actset_tm[3] = 0;
  actset_tm[4] = 0;
  actset_tm[5] = 0;
  actset_tm[6] = 0;
  actset_tm[7] = 600;

  prg_mode = 1;
}




void get_keydata(void) {
  player();
  thankssprinit();
  thanksaction();
}




void get_usrname(void) {
  short round, zone;
  short i, gp;

  memset(highscores, 0, sizeof(highscores));

  for (round = 0; round < 7; ++round)
  {
    for (zone = 0; zone < 3; ++zone)
    {
      pointcnt(g_current_score_data.timeattack[round][zone][0].name, 3);
      pointcnt(g_current_score_data.timeattack[round][zone][1].name, 2);
      pointcnt(g_current_score_data.timeattack[round][zone][2].name, 1);
    }
  }
  for (round = 0; round < 7; ++round)
  {
    pointcnt(g_current_score_data.special[round][0].name, 3);
    pointcnt(g_current_score_data.special[round][1].name, 2);
    pointcnt(g_current_score_data.special[round][2].name, 1);
  }


  gp = 0;
  for (i = 0; i < 84; ++i)
  {
    if (highscores[i].pts == 0) break;
    if (highscores[i].pts >= highscores[gp].pts)
    {
      gp = i;
    }
  }
  strcpy(GreatestPlayer, highscores[gp].name);
}




void pointcnt(char* name, short pts) {
  short i;

  for (i = 0; i < 84; ++i)
  {
    if (highscores[i].pts)
    {
      if (memcmp(highscores[i].name, name, 3) != 0) continue;

      highscores[i].pts += pts;
      break;
    }



    highscores[i].pts = pts;
    memcpy(highscores[i].name, name, sizeof(highscores[i].name) - 1);
    highscores[i].name[3] = 0;
    break;

  }
}







int isdigit(int c) {
  if (c >= 48 && c < 58)
    return 1;
  else
    return 0;
}


int isupper_c(int c) {
  if (c >= 65 && c < 91)
    return 1;
  else
    return 0;
}


void dsp_usrname(void) {
  short i;
  unsigned short c;

  for (i = 0; i < 3; ++i)
  {
    if (isdigit(GreatestPlayer[i]) != 0) // goto 1000
    {
      c = GreatestPlayer[i] - 47;
    }
    else if (isupper_c(GreatestPlayer[i]) != 0) // goto 1080
    {
      c = GreatestPlayer[i] - 54;
    }
    else
    {
      continue;
    }
    PutAscii(c, i * 2 + 17, 12);
  }
}




static void player(void) {
  if ((unsigned char)swdata1.b.l & 240) quit_flg = 1;
  else quit_flg = 0;
}
