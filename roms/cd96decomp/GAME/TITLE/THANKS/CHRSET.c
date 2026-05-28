#include "../../TYPES.h"
#include "THANKS_TYPES.h"
#include "CHRSET.h"
#include "../../IO.h"
#include "ACT.h"
#include "ETC_M.h"

static void flick_set(void);

extern unsigned char animal_flg;
extern short actset_tm[8];
extern sprite_status_thanks thanksactwk[66];

























void thankssprinit(void) {
  short *a1, *a2;
  int ld0;
  short d0, d1, d5;

  short actset_tbl[16] =
  {
    120, 180,
    180, 300,
    240, 600,
    720, 1800,
    840, 2280,
    600, 2160,
    240, 600,
    300, 600
  };

  short manyact_tbl[16] =
  {
    10, 25,
    15, 20,
    10, 25,
    20, 50,
    30, 60,
    20, 60,
    40, 70,
    900, 1500
  };

  void(*sprinit_tbl[8])(void) =
  {
    &flick_set,
    &inco_set,
    &hato_set,
    &pocky_set,
    &pecky_set,
    &ricky_set,
    &sheep_set,
    &sonic_set
  };

  a2 = actset_tm;

  d5 = 7;
  if (animal_flg == 2)
  {
    --d5;
  }
  do
  {
    if ((unsigned short)*a2 <= 0)
    {
      --*a2;
      goto label1;
    }
    --*a2;
    ++a2;
  } while (d5--);

  return;


label1:
  d0 = d5;
  d0 *= 2;
  if (animal_flg != 2) a1 = &actset_tbl[d0];
  else a1 = &manyact_tbl[d0];
  *a2 = *a1++;

  ld0 = random2();
  ld0 &= 65535;
  d1 = *a1;
  d0 = ld0 % d1;
  *a2 += d0;

  sprinit_tbl[d5]();
}




void sonic_set(void) {
  thanksactwk[0].ACT_NO = 1;
}




static void flick_set(void) {
  sprite_status_thanks* pNewActwk;

  if (thanks_get_actwk(&pNewActwk) == 0)
  {
    pNewActwk->ACT_NO = 4;
  }
}




void pocky_set(void) {
  sprite_status_thanks* pNewActwk;

  if (thanks_get_actwk(&pNewActwk) == 0)
  {
    pNewActwk->ACT_NO = 5;
  }
}




void pecky_set(void) {
  sprite_status_thanks* pNewActwk;

  if (thanks_get_actwk(&pNewActwk) == 0)
  {
    pNewActwk->ACT_NO = 11;
  }
}




void ricky_set(void) {
  sprite_status_thanks* pNewActwk;

  if (thanks_get_actwk(&pNewActwk) == 0)
  {
    pNewActwk->ACT_NO = 6;
  }
}




void inco_set(void) {
  sprite_status_thanks* pNewActwk;

  if (thanks_get_actwk(&pNewActwk) == 0)
  {
    pNewActwk->ACT_NO = 8;
  }
}




void hato_set(void) {
  sprite_status_thanks* pNewActwk;

  if (thanks_get_actwk(&pNewActwk) == 0)
  {
    pNewActwk->ACT_NO = 9;
  }
}




void sheep_set(void) {
  sprite_status_thanks* pNewActwk;

  if (thanks_get_actwk(&pNewActwk) == 0)
  {
    pNewActwk->ACT_NO = 10;
  }
}
