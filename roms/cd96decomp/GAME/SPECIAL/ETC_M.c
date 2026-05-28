#include "../EQU.h"
#include "COMMON.h"
#include "SPM_EQU.h"
#include "ETC_M.h"
#include "../../services.h"

static short sonic_upcnt;
static short sonic_upcnt2;
static int subtbl[8] = { 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1 };
static unsigned char nullflg;
static unsigned short disp_ascii[20] = {
  503, 505, 507, 509, 510, 512, 514, 515, 516, 517,
  504, 506, 508, 504, 511, 513, 504, 506, 504, 504
};
static int chrtbl[24] = {
  32769, 32770, 32771, 32772, 32773, 32774, 32775, 32776,
  32777, 32769, 32778, 32779, 32780, 32781, 32782, 32783,
  32784, 32785, 32786, 32787, 32788, 32789,     0,     0
};










void sonic_disp(void) {
  unsigned short sonic_extend;

  if ((sonic_upcnt2 = sonic_upcnt2 + 1 & 7) == 0) {
    sonic_upcnt = sonic_upcnt + 1 & 1;
    if ((sonic_extend = sonicup_no) != 0) {
      if (--sonic_extend >= 5) sonic_extend = 4;
      switch (sonic_extend) {
        case 4:
          sonic_disp_disp(8);
        case 3:
          sonic_disp_disp(6);
        case 2:
          sonic_disp_disp(4);
        case 1:
          sonic_disp_disp(2);
        case 0:
          sonic_disp_disp(0);
      }
    }
  }
}


void sonic_disp_disp(short tbl_no) {
  int x;
  int y;
  static unsigned short chibi_sonic_map[2][3][2] = {
    {
      { 863, 864 },
      { 869, 870 },
      { 871, 872 }
    },
    {
      { 863, 864 },
      { 869, 870 },
      { 871, 873 }
    }
  };


  for (y = 0; y < 3; ++y) {
    for (x = 0; x < 2; ++x) {
      SetSpecialGrid(0, x + 26 + tbl_no, y + 23, chibi_sonic_map[sonic_upcnt][y][x], 0);

    }
  }

}























void time_bonus_disp(void) {
  nullflg = 0;

  cset(subtbl, 24, 20, timebonus, 7);
}


void ring_bonus_disp(void) {
  nullflg = 0;

  cset(subtbl, 24, 17, ringbonus, 7);
}


void game_score_disp(void) {
  nullflg = 0;

  cset(subtbl, 24, 14, plscore, 7);
}













void cset(int* subtbl, unsigned short x, unsigned short y, int disp_data, short counter) {
  short one_number, i;

  if ((disp_data *= 10) != 0) {
    for (i = 0; i <= counter; ++i) {
      one_number = disp_data / subtbl[i];

      disp_data %= subtbl[i];
      if (nullflg != 0 || one_number != 0) {

        nullflg = 1;
        SetSpecialGrid(0, x, y, disp_ascii[one_number], 0);
        SetSpecialGrid(0, x, y + 1, disp_ascii[one_number + 10], 0);
      }
      else {
        SetSpecialGrid(0, x, y, 0, 0);
        SetSpecialGrid(0, x, y + 1, 0, 0);
      }
      ++x;
    }
  }
  else {

    for (i = 0; i < counter; ++i) {

      SetSpecialGrid(0, x, y, 0, 0);
      SetSpecialGrid(0, x, y + 1, 0, 0);
      ++x;
    }

    SetSpecialGrid(0, x, y, disp_ascii[0], 0);
    SetSpecialGrid(0, x, y + 1, disp_ascii[10], 0);
  }
}














unsigned short cntminus(unsigned short* work, unsigned short minus_data, unsigned short under_limit, unsigned short upper_limit) {
  if ((short)(*work -= minus_data) < (short)under_limit) *work = upper_limit;
  return *work;
}


unsigned short cntplus(unsigned short* work, unsigned short plus_data, unsigned short under_limit, unsigned short upper_limit) {
  if ((*work += plus_data) > upper_limit) *work = under_limit;
  return *work;
}





void spetime_disp(void) {
  if (!(spgmmode & 2)) {

    sset(&subtbl[5], 19, 0, spe_time.l, 2);
  }
  else {
    sset(&subtbl[6], 17, 0, spe_time.l >> 16 & 255, 1);
    sset(&subtbl[6], 20, 0, spe_time.l >> 8 & 255, 1);
    sset(&subtbl[6], 23, 0, (spe_time.l & 255) * 100 / 60, 1);
  }

}


void ringno_disp(void) {
  sset(&subtbl[5], 33, 0, ringno, 2);
}


void ufoleft_disp(void) {
  sset(&subtbl[6], 7, 0, ufoleft, 1);
}































void sset(int* subtbl, unsigned short x, unsigned short y, int disp_data, short counter) {
  short one_number, i = 0;
  int disp_x, disp_y;

  disp_x = (short)x, disp_y = (short)y;

  do {
    one_number = disp_data / subtbl[i];
    disp_data %= subtbl[i++];
    SetSpecialGrid(0, disp_x, disp_y, chrtbl[one_number], 0);
    SetSpecialGrid(0, disp_x, disp_y + 1, chrtbl[one_number + 12], 0);
    ++disp_x;
  } while (i <= counter);
}



































void rfill(unsigned int* address, unsigned int data, short size) {
  for (size /= 4; size >= 0; --size) *address++ = data;
}

void rcopy(unsigned int* address1, unsigned int* address2, short size) {
  for (size /= 4; size >= 0; --size) *address2++ = *address1++;
}

void init_sonic_upcnt(void) {
  sonic_upcnt = 0;
  sonic_upcnt2 = 0;
}
