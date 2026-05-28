#include "EQU.h"
#include "ZONE.h"
#include "../services.h"
#include "ACTION.h"
#include "ACTSET.h"
#include "DUMMY.h"
#include "LOADER2.h"
#include "SCORE.h"

extern sprite_pattern* z1_title_pat[];
extern sprite_pattern* z3_title_pat[];
extern sprite_pattern* z33_title_pat[];
extern sprite_pattern* z4_title_pat[];
extern sprite_pattern* z5_title_pat[];
extern sprite_pattern* z6_title_pat[];
extern sprite_pattern* z7_title_pat[];
extern sprite_pattern* z8_title_pat[];
extern unsigned short z1_title_tbl[];
extern unsigned short z3_title_tbl[];
extern unsigned short z4_title_tbl[];
extern unsigned short z5_title_tbl[];
extern unsigned short z6_title_tbl[];
extern unsigned short z7_title_tbl[];
extern unsigned short z8_title_tbl[];

static void over_init(sprite_status* pAct);
static void over_move(sprite_status* pAct);
static void title_init(sprite_status* pAct);
static void title_move0(sprite_status* pAct);
static void title_move1(sprite_status* pAct);
static void title_back0(sprite_status* pAct);
static void title_back1(sprite_status* pAct);
static void title_wait(sprite_status* pAct);
static void clear_init0(sprite_status* pAct);
static void clear_init(sprite_status* pAct);
static void clear_move0(sprite_status* pAct);
static void clear_move1(sprite_status* pAct);
static void clear_move2(sprite_status* pAct);
static void clear_wait(sprite_status* pAct);

static sprite_pattern game0 = { 1, { { -72, -8, 0, 348 } } };
static sprite_pattern z3game0 = { 1, { { -72, -8, 0, 390 } } };
static sprite_pattern z33game0 = { 1, { { -72, -8, 0, 394 } } };
static sprite_pattern z6game0 = { 1, { { -72, -8, 0, 389 } } };
static sprite_pattern z81game0 = { 1, { { -72, -8, 0, 379 } } };
static sprite_pattern z82game0 = { 1, { { -72, -8, 0, 388 } } };
static sprite_pattern z83game0 = { 1, { { -72, -8, 0, 381 } } };
static sprite_pattern game1 = { 1, { { 8, -8, 0, 349 } } };
static sprite_pattern z3game1 = { 1, { { 8, -8, 0, 391 } } };
static sprite_pattern z33game1 = { 1, { { 8, -8, 0, 395 } } };
static sprite_pattern z6game1 = { 1, { { 8, -8, 0, 390 } } };
static sprite_pattern z81game1 = { 1, { { 8, -8, 0, 380 } } };
static sprite_pattern z82game1 = { 1, { { 8, -8, 0, 389 } } };
static sprite_pattern z83game1 = { 1, { { 8, -8, 0, 382 } } };
sprite_pattern* gamepat[2] = {
  &game0,
  &game1
};
sprite_pattern* z3gamepat[2] = {
  &z3game0,
  &z3game1
};
sprite_pattern* z33gamepat[2] = {
  &z33game0,
  &z33game1
};
sprite_pattern* z6gamepat[2] = {
  &z6game0,
  &z6game1
};
sprite_pattern* z81gamepat[2] = {
  &z81game0,
  &z81game1
};
sprite_pattern* z82gamepat[2] = {
  &z82game0,
  &z82game1
};
sprite_pattern* z83gamepat[2] = {
  &z83game0,
  &z83game1
};
sprite_pattern** gamepats[7][3][3] = {
  {
    { gamepat, gamepat, gamepat },
    { gamepat, gamepat, gamepat },
    { 0, 0, gamepat }
  },
  {
    { z3gamepat, z3gamepat, z3gamepat },
    { z3gamepat, z3gamepat, z3gamepat },
    { 0, 0, z33gamepat }
  },
  {
    { gamepat, gamepat, gamepat },
    { gamepat, gamepat, gamepat },
    { 0, 0, gamepat }
  },
  {
    { gamepat, gamepat, gamepat },
    { gamepat, gamepat, gamepat },
    { 0, 0, gamepat }
  },
  {
    { z6gamepat, z6gamepat, z6gamepat },
    { z6gamepat, z6gamepat, z6gamepat },
    { 0, 0, z6gamepat }
  },
  {
    { gamepat, gamepat, gamepat },
    { gamepat, gamepat, gamepat },
    { 0, 0, gamepat }
  },
  {
    { z81gamepat, z81gamepat, z81gamepat },
    { z82gamepat, z82gamepat, z82gamepat },
    { 0, 0, z83gamepat }
  }
};
static sprite_pattern time0 = { 1, { { -68, -8, 0, 350 } } };
static sprite_pattern z3time0 = { 1, { { -68, -8, 0, 392 } } };
static sprite_pattern z33time0 = { 1, { { -68, -8, 0, 396 } } };
static sprite_pattern z6time0 = { 1, { { -68, -8, 0, 391 } } };
static sprite_pattern z81time0 = { 1, { { -68, -8, 0, 381 } } };
static sprite_pattern z82time0 = { 1, { { -68, -8, 0, 390 } } };
static sprite_pattern z83time0 = { 1, { { -68, -8, 0, 383 } } };
static sprite_pattern time1 = { 1, { { 4, -8, 0, 351 } } };
static sprite_pattern z3time1 = { 1, { { 4, -8, 0, 393 } } };
static sprite_pattern z33time1 = { 1, { { 4, -8, 0, 397 } } };
static sprite_pattern z6time1 = { 1, { { 4, -8, 0, 392 } } };
static sprite_pattern z81time1 = { 1, { { 4, -8, 0, 382 } } };
static sprite_pattern z82time1 = { 1, { { 4, -8, 0, 391 } } };
static sprite_pattern z83time1 = { 1, { { 4, -8, 0, 384 } } };
sprite_pattern* timepat[2] = {
  &time0,
  &time1
};
sprite_pattern* z3timepat[2] = {
  &z3time0,
  &z3time1
};
sprite_pattern* z33timepat[2] = {
  &z33time0,
  &z33time1
};
sprite_pattern* z6timepat[2] = {
  &z6time0,
  &z6time1
};
sprite_pattern* z81timepat[2] = {
  &z81time0,
  &z81time1
};
sprite_pattern* z82timepat[2] = {
  &z82time0,
  &z82time1
};
sprite_pattern* z83timepat[2] = {
  &z83time0,
  &z83time1
};
sprite_pattern** timepats[7][3][3] = {
  {
    { timepat, timepat, timepat },
    { timepat, timepat, timepat },
    { 0, 0, timepat }
  },
  {
    { z3timepat, z3timepat, z3timepat },
    { z3timepat, z3timepat, z3timepat },
    { 0, 0, z33timepat }
  },
  {
    { timepat, timepat, timepat },
    { timepat, timepat, timepat },
    { 0, 0, timepat }
  },
  {
    { timepat, timepat, timepat },
    { timepat, timepat, timepat },
    { 0, 0, timepat }
  },
  {
    { z6timepat, z6timepat, z6timepat },
    { z6timepat, z6timepat, z6timepat },
    { 0, 0, z6timepat }
  },
  {
    { timepat, timepat, timepat },
    { timepat, timepat, timepat },
    { 0, 0, timepat }
  },
  {
    { z81timepat, z81timepat, z81timepat },
    { z82timepat, z82timepat, z82timepat },
    { 0, 0, z83timepat }
  }
};
static sprite_pattern gotpat0 = { 1, { { -68, -20, 0, 352 } } };
static sprite_pattern z3gotpat0 = { 1, { { -68, -20, 0, 394 } } };
static sprite_pattern z33gotpat0 = { 1, { { -68, -20, 0, 398 } } };
static sprite_pattern z6gotpat0 = { 1, { { -68, -20, 0, 393 } } };
static sprite_pattern z81gotpat0 = { 1, { { -68, -20, 0, 383 } } };
static sprite_pattern z82gotpat0 = { 1, { { -68, -20, 0, 392 } } };
static sprite_pattern z83gotpat0 = { 1, { { -68, -20, 0, 385 } } };
static sprite_pattern gotpat1 = { 1, { { -100, 4, 0, 353 } } };
static sprite_pattern z3gotpat1 = { 1, { { -100, 4, 0, 395 } } };
static sprite_pattern z33gotpat1 = { 1, { { -100, 4, 0, 399 } } };
static sprite_pattern z6gotpat1 = { 1, { { -100, 4, 0, 394 } } };
static sprite_pattern z81gotpat1 = { 1, { { -100, 4, 0, 384 } } };
static sprite_pattern z82gotpat1 = { 1, { { -100, 4, 0, 393 } } };
static sprite_pattern z83gotpat1 = { 1, { { -100, 4, 0, 386 } } };
static sprite_pattern gotpat2 = { 1, { { -100, 4, 0, 354 } } };
static sprite_pattern z3gotpat2 = { 1, { { -100, 4, 0, 396 } } };
static sprite_pattern z33gotpat2 = { 1, { { -100, 4, 0, 400 } } };
static sprite_pattern z6gotpat2 = { 1, { { -100, 4, 0, 395 } } };
static sprite_pattern z81gotpat2 = { 1, { { -100, 4, 0, 385 } } };
static sprite_pattern z82gotpat2 = { 1, { { -100, 4, 0, 394 } } };
static sprite_pattern z83gotpat2 = { 1, { { -100, 4, 0, 387 } } };
static sprite_pattern gotpat3 = { 1, { { -100, 4, 0, 355 } } };
static sprite_pattern z3gotpat3 = { 1, { { -100, 4, 0, 397 } } };
static sprite_pattern z33gotpat3 = { 1, { { -100, 4, 0, 401 } } };
static sprite_pattern z6gotpat3 = { 1, { { -100, 4, 0, 396 } } };
static sprite_pattern z81gotpat3 = { 1, { { -100, 4, 0, 386 } } };
static sprite_pattern z82gotpat3 = { 1, { { -100, 4, 0, 395 } } };
static sprite_pattern z83gotpat3 = { 1, { { -100, 4, 0, 388 } } };
static sprite_pattern madepat0 = { 1, { { -128, -20, 0, 356 } } };
static sprite_pattern z3madepat0 = { 1, { { -128, -20, 0, 398 } } };
static sprite_pattern z33madepat0 = { 1, { { -128, -20, 0, 402 } } };
static sprite_pattern z6madepat0 = { 1, { { -128, -20, 0, 397 } } };
static sprite_pattern z81madepat0 = { 1, { { -128, -20, 0, 387 } } };
static sprite_pattern z82madepat0 = { 1, { { -128, -20, 0, 396 } } };
static sprite_pattern z83madepat0 = { 1, { { -128, -20, 0, 389 } } };
static sprite_pattern madepat1 = { 1, { { -112, 4, 0, 357 } } };
static sprite_pattern z3madepat1 = { 1, { { -112, 4, 0, 399 } } };
static sprite_pattern z33madepat1 = { 1, { { -112, 4, 0, 403 } } };
static sprite_pattern z6madepat1 = { 1, { { -112, 4, 0, 398 } } };
static sprite_pattern z81madepat1 = { 1, { { -112, 4, 0, 388 } } };
static sprite_pattern z82madepat1 = { 1, { { -112, 4, 0, 397 } } };
static sprite_pattern z83madepat1 = { 1, { { -112, 4, 0, 390 } } };
static sprite_pattern madepat2 = { 1, { { -112, 4, 0, 358 } } };
static sprite_pattern z3madepat2 = { 1, { { -112, 4, 0, 400 } } };
static sprite_pattern z33madepat2 = { 1, { { -112, 4, 0, 404 } } };
static sprite_pattern z6madepat2 = { 1, { { -112, 4, 0, 399 } } };
static sprite_pattern z81madepat2 = { 1, { { -112, 4, 0, 389 } } };
static sprite_pattern z82madepat2 = { 1, { { -112, 4, 0, 398 } } };
static sprite_pattern z83madepat2 = { 1, { { -112, 4, 0, 391 } } };
static sprite_pattern madepat3 = { 1, { { -112, 4, 0, 359 } } };
static sprite_pattern z3madepat3 = { 1, { { -112, 4, 0, 401 } } };
static sprite_pattern z33madepat3 = { 1, { { -112, 4, 0, 405 } } };
static sprite_pattern z6madepat3 = { 1, { { -112, 4, 0, 400 } } };
static sprite_pattern z81madepat3 = { 1, { { -112, 4, 0, 390 } } };
static sprite_pattern z82madepat3 = { 1, { { -112, 4, 0, 399 } } };
static sprite_pattern z83madepat3 = { 1, { { -112, 4, 0, 392 } } };
sprite_pattern bonuspat = {
  18,
  {
    { -44, -32, 0, 360 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z3bonuspat = {
  18,
  {
    { -44, -32, 0, 402 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z33bonuspat = {
  18,
  {
    { -44, -32, 0, 406 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z6bonuspat = {
  18,
  {
    { -44, -32, 0, 401 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z81bonuspat = {
  18,
  {
    { -44, -32, 0, 391 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z82bonuspat = {
  18,
  {
    { -44, -32, 0, 400 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z83bonuspat = {
  18,
  {
    { -44, -32, 0, 393 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern* bonuspats[7][3][3] = {
  {
    { &bonuspat, &bonuspat, &bonuspat },
    { &bonuspat, &bonuspat, &bonuspat },
    { 0, 0, &bonuspat }
  },
  {
    { &z3bonuspat, &z3bonuspat, &z3bonuspat },
    { &z3bonuspat, &z3bonuspat, &z3bonuspat },
    { 0, 0, &z33bonuspat }
  },
  {
    { &bonuspat, &bonuspat, &bonuspat },
    { &bonuspat, &bonuspat, &bonuspat },
    { 0, 0, &bonuspat }
  },
  {
    { &bonuspat, &bonuspat, &bonuspat },
    { &bonuspat, &bonuspat, &bonuspat },
    { 0, 0, &bonuspat }
  },
  {
    { &z6bonuspat, &z6bonuspat, &z6bonuspat },
    { &z6bonuspat, &z6bonuspat, &z6bonuspat },
    { 0, 0, &z6bonuspat }
  },
  {
    { &bonuspat, &bonuspat, &bonuspat },
    { &bonuspat, &bonuspat, &bonuspat },
    { 0, 0, &bonuspat }
  },
  {
    { &z81bonuspat, &z81bonuspat, &z81bonuspat },
    { &z82bonuspat, &z82bonuspat, &z82bonuspat },
    { 0, 0, &z83bonuspat }
  },
};
sprite_pattern bonuspat0 = {
  18,
  {
    { -44, -32, 0, 361 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z3bonuspat0 = {
  18,
  {
    { -44, -32, 0, 403 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z33bonuspat0 = {
  18,
  {
    { -44, -32, 0, 407 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z6bonuspat0 = {
  18,
  {
    { -44, -32, 0, 402 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z81bonuspat0 = {
  18,
  {
    { -44, -32, 0, 392 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z82bonuspat0 = {
  18,
  {
    { -44, -32, 0, 401 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern z83bonuspat0 = {
  18,
  {
    { -44, -32, 0, 394 },
    { 72, -32, 0, 0 },
    { 80, -32, 0, 0 },
    { 88, -32, 0, 0 },
    { 96, -32, 0, 0 },
    { 104, -32, 0, 0 },
    { 112, -32, 0, 0 },
    { 120, -32, 0, 0 },
    { 88, -8, 0, 0 },
    { 96, -8, 0, 0 },
    { 104, -8, 0, 0 },
    { 112, -8, 0, 0 },
    { 120, -8, 0, 0 },
    { 88, 16, 0, 0 },
    { 96, 16, 0, 0 },
    { 104, 16, 0, 0 },
    { 112, 16, 0, 0 },
    { 120, 16, 0, 0 }
  }
};
sprite_pattern* bonuspat0s[7][3][3] = {
  {
    { &bonuspat0, &bonuspat0, &bonuspat0 },
    { &bonuspat0, &bonuspat0, &bonuspat0 },
    { 0, 0, &bonuspat0 }
  },
  {
    { &z3bonuspat0, &z3bonuspat0, &z3bonuspat0 },
    { &z3bonuspat0, &z3bonuspat0, &z3bonuspat0 },
    { 0, 0, &z33bonuspat0 }
  },
  {
    { &bonuspat0, &bonuspat0, &bonuspat0 },
    { &bonuspat0, &bonuspat0, &bonuspat0 },
    { 0, 0, &bonuspat0 }
  },
  {
    { &bonuspat0, &bonuspat0, &bonuspat0 },
    { &bonuspat0, &bonuspat0, &bonuspat0 },
    { 0, 0, &bonuspat0 }
  },
  {
    { &z6bonuspat0, &z6bonuspat0, &z6bonuspat0 },
    { &z6bonuspat0, &z6bonuspat0, &z6bonuspat0 },
    { 0, 0, &z6bonuspat0 }
  },
  {
    { &bonuspat0, &bonuspat0, &bonuspat0 },
    { &bonuspat0, &bonuspat0, &bonuspat0 },
    { 0, 0, &bonuspat0 }
  },
  {
    { &z81bonuspat0, &z81bonuspat0, &z81bonuspat0 },
    { &z82bonuspat0, &z82bonuspat0, &z82bonuspat0 },
    { 0, 0, &z83bonuspat0 }
  },
};
sprite_pattern* gotpat[5] = {
  &gotpat0,
  &bonuspat,
  &gotpat1,
  &gotpat2,
  &gotpat3
};
sprite_pattern* z3gotpat[5] = {
  &z3gotpat0,
  &z3bonuspat,
  &z3gotpat1,
  &z3gotpat2,
  &z3gotpat3
};
sprite_pattern* z33gotpat[5] = {
  &z33gotpat0,
  &z33bonuspat,
  &z33gotpat1,
  &z33gotpat2,
  &z33gotpat3
};
sprite_pattern* z6gotpat[5] = {
  &z6gotpat0,
  &z6bonuspat,
  &z6gotpat1,
  &z6gotpat2,
  &z6gotpat3
};
sprite_pattern* z81gotpat[5] = {
  &z81gotpat0,
  &z81bonuspat,
  &z81gotpat1,
  &z81gotpat2,
  &z81gotpat3
};
sprite_pattern* z82gotpat[5] = {
  &z82gotpat0,
  &z82bonuspat,
  &z82gotpat1,
  &z82gotpat2,
  &z82gotpat3
};
sprite_pattern* z83gotpat[5] = {
  &z83gotpat0,
  &z83bonuspat,
  &z83gotpat1,
  &z83gotpat2,
  &z83gotpat3
};
sprite_pattern** gotpats[7][3][3] = {
  {
    { gotpat, gotpat, gotpat },
    { gotpat, gotpat, gotpat },
    { 0, 0, gotpat }
  },
  {
    { z3gotpat, z3gotpat, z3gotpat },
    { z3gotpat, z3gotpat, z3gotpat },
    { 0, 0, z33gotpat }
  },
  {
    { gotpat, gotpat, gotpat },
    { gotpat, gotpat, gotpat },
    { 0, 0, gotpat }
  },
  {
    { gotpat, gotpat, gotpat },
    { gotpat, gotpat, gotpat },
    { 0, 0, gotpat }
  },
  {
    { z6gotpat, z6gotpat, z6gotpat },
    { z6gotpat, z6gotpat, z6gotpat },
    { 0, 0, z6gotpat }
  },
  {
    { gotpat, gotpat, gotpat },
    { gotpat, gotpat, gotpat },
    { 0, 0, gotpat }
  },
  {
    { z81gotpat, z81gotpat, z81gotpat },
    { z82gotpat, z82gotpat, z82gotpat },
    { 0, 0, z83gotpat }
  }
};
sprite_pattern* gotpat_0[5] = {
  &gotpat0,
  &bonuspat0,
  &gotpat1,
  &gotpat2,
  &gotpat3
};
sprite_pattern* z3gotpat_0[5] = {
  &z3gotpat0,
  &z3bonuspat0,
  &z3gotpat1,
  &z3gotpat2,
  &z3gotpat3
};
sprite_pattern* z33gotpat_0[5] = {
  &z33gotpat0,
  &z33bonuspat0,
  &z33gotpat1,
  &z33gotpat2,
  &z33gotpat3
};
sprite_pattern* z6gotpat_0[5] = {
  &z6gotpat0,
  &z6bonuspat0,
  &z6gotpat1,
  &z6gotpat2,
  &z6gotpat3
};
sprite_pattern* z81gotpat_0[5] = {
  &z81gotpat0,
  &z81bonuspat0,
  &z81gotpat1,
  &z81gotpat2,
  &z81gotpat3
};
sprite_pattern* z82gotpat_0[5] = {
  &z82gotpat0,
  &z82bonuspat0,
  &z82gotpat1,
  &z82gotpat2,
  &z82gotpat3
};
sprite_pattern* z83gotpat_0[5] = {
  &z83gotpat0,
  &z83bonuspat0,
  &z83gotpat1,
  &z83gotpat2,
  &z83gotpat3
};
sprite_pattern** gotpats_0[7][3][3] = {
  {
    { gotpat_0, gotpat_0, gotpat_0 },
    { gotpat_0, gotpat_0, gotpat_0 },
    { 0, 0, gotpat_0 }
  },
  {
    { z3gotpat_0, z3gotpat_0, z3gotpat_0 },
    { z3gotpat_0, z3gotpat_0, z3gotpat_0 },
    { 0, 0, z33gotpat_0 }
  },
  {
    { gotpat_0, gotpat_0, gotpat_0 },
    { gotpat_0, gotpat_0, gotpat_0 },
    { 0, 0, gotpat_0 }
  },
  {
    { gotpat_0, gotpat_0, gotpat_0 },
    { gotpat_0, gotpat_0, gotpat_0 },
    { 0, 0, gotpat_0 }
  },
  {
    { z6gotpat_0, z6gotpat_0, z6gotpat_0 },
    { z6gotpat_0, z6gotpat_0, z6gotpat_0 },
    { 0, 0, z6gotpat_0 }
  },
  {
    { gotpat_0, gotpat_0, gotpat_0 },
    { gotpat_0, gotpat_0, gotpat_0 },
    { 0, 0, gotpat_0 }
  },
  {
    { z81gotpat_0, z81gotpat_0, z81gotpat_0 },
    { z82gotpat_0, z82gotpat_0, z82gotpat_0 },
    { 0, 0, z83gotpat_0 }
  }
};
sprite_pattern* madepat[5] = {
  &madepat0,
  &bonuspat,
  &madepat1,
  &madepat2,
  &madepat3
};
sprite_pattern* z3madepat[5] = {
  &z3madepat0,
  &z3bonuspat,
  &z3madepat1,
  &z3madepat2,
  &z3madepat3
};
sprite_pattern* z33madepat[5] = {
  &z33madepat0,
  &z33bonuspat,
  &z33madepat1,
  &z33madepat2,
  &z33madepat3
};
sprite_pattern* z6madepat[5] = {
  &z6madepat0,
  &z6bonuspat,
  &z6madepat1,
  &z6madepat2,
  &z6madepat3
};
sprite_pattern* z81madepat[5] = {
  &z81madepat0,
  &z81bonuspat,
  &z81madepat1,
  &z81madepat2,
  &z81madepat3
};
sprite_pattern* z82madepat[5] = {
  &z82madepat0,
  &z82bonuspat,
  &z82madepat1,
  &z82madepat2,
  &z82madepat3
};
sprite_pattern* z83madepat[5] = {
  &z83madepat0,
  &z83bonuspat,
  &z83madepat1,
  &z83madepat2,
  &z83madepat3
};
sprite_pattern** madepats[7][3][3] = {
  {
    { madepat, madepat, madepat },
    { madepat, madepat, madepat },
    { 0, 0, madepat }
  },
  {
    { z3madepat, z3madepat, z3madepat },
    { z3madepat, z3madepat, z3madepat },
    { 0, 0, z33madepat }
  },
  {
    { madepat, madepat, madepat },
    { madepat, madepat, madepat },
    { 0, 0, madepat }
  },
  {
    { madepat, madepat, madepat },
    { madepat, madepat, madepat },
    { 0, 0, madepat }
  },
  {
    { z6madepat, z6madepat, z6madepat },
    { z6madepat, z6madepat, z6madepat },
    { 0, 0, z6madepat }
  },
  {
    { madepat, madepat, madepat },
    { madepat, madepat, madepat },
    { 0, 0, madepat }
  },
  {
    { z81madepat, z81madepat, z81madepat },
    { z82madepat, z82madepat, z82madepat },
    { 0, 0, z83madepat }
  }
};
sprite_pattern* madepat_0[5] = {
  &madepat0,
  &bonuspat0,
  &madepat1,
  &madepat2,
  &madepat3
};
sprite_pattern* z3madepat_0[5] = {
  &z3madepat0,
  &z3bonuspat0,
  &z3madepat1,
  &z3madepat2,
  &z3madepat3
};
sprite_pattern* z33madepat_0[5] = {
  &z33madepat0,
  &z33bonuspat0,
  &z33madepat1,
  &z33madepat2,
  &z33madepat3
};
sprite_pattern* z6madepat_0[5] = {
  &z6madepat0,
  &z6bonuspat0,
  &z6madepat1,
  &z6madepat2,
  &z6madepat3
};
sprite_pattern* z81madepat_0[5] = {
  &z81madepat0,
  &z81bonuspat0,
  &z81madepat1,
  &z81madepat2,
  &z81madepat3
};
sprite_pattern* z82madepat_0[5] = {
  &z82madepat0,
  &z82bonuspat0,
  &z82madepat1,
  &z82madepat2,
  &z82madepat3
};
sprite_pattern* z83madepat_0[5] = {
  &z83madepat0,
  &z83bonuspat0,
  &z83madepat1,
  &z83madepat2,
  &z83madepat3
};
sprite_pattern** madepats_0[7][3][3] = {
  {
    { madepat_0, madepat_0, madepat_0 },
    { madepat_0, madepat_0, madepat_0 },
    { 0, 0, madepat_0 }
  },
  {
    { z3madepat_0, z3madepat_0, z3madepat_0 },
    { z3madepat_0, z3madepat_0, z3madepat_0 },
    { 0, 0, z33madepat_0 }
  },
  {
    { madepat_0, madepat_0, madepat_0 },
    { madepat_0, madepat_0, madepat_0 },
    { 0, 0, madepat_0 }
  },
  {
    { madepat_0, madepat_0, madepat_0 },
    { madepat_0, madepat_0, madepat_0 },
    { 0, 0, madepat_0 }
  },
  {
    { z6madepat_0, z6madepat_0, z6madepat_0 },
    { z6madepat_0, z6madepat_0, z6madepat_0 },
    { 0, 0, z6madepat_0 }
  },
  {
    { madepat_0, madepat_0, madepat_0 },
    { madepat_0, madepat_0, madepat_0 },
    { 0, 0, madepat_0 }
  },
  {
    { z81madepat_0, z81madepat_0, z81madepat_0 },
    { z82madepat_0, z82madepat_0, z82madepat_0 },
    { 0, 0, z83madepat_0 }
  }
};
sprite_pattern** title_pats[7][3] = {
  { z1_title_pat, z1_title_pat, z1_title_pat },
  { z3_title_pat, z3_title_pat, z33_title_pat },
  { z4_title_pat, z4_title_pat, z4_title_pat },
  { z5_title_pat, z5_title_pat, z5_title_pat },
  { z6_title_pat, z6_title_pat, z6_title_pat },
  { z7_title_pat, z7_title_pat, z7_title_pat },
  { z8_title_pat, z8_title_pat, z8_title_pat }
};
unsigned short* title_tbls[7] = {
  z1_title_tbl,
  z3_title_tbl,
  z4_title_tbl,
  z5_title_tbl,
  z6_title_tbl,
  z7_title_tbl,
  z8_title_tbl
};
static unsigned short ClearSountWait;
static short WaitCount;
static unsigned short cleartbl[12] = {
  204,   0, 288,   0,
  272, 512, 240,   1,
  204,   0, 288,   2
};


void over(sprite_status* pAct) {
  switch (pAct->r_no0) {
    case 0:
      over_init(pAct);
      break;
    case 2:
      over_move(pAct);
      break;
  }

}


static void over_init(sprite_status* pAct) {
  sprite_status* pTmpAct;

  sub_sync(130);
  pAct->r_no0 = 2;
  pAct->yposi.w.h = 224;
  pAct->xposi.w.h = 128;
  ((short*)pAct)[23] = 288;
  pAct->sproffset = 32768;
  pAct->patbase = gamepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  plsubchg_flag = 8;
  if (pltimeover_f & 1) {
    pltimeover_f &= 254;
    if (pl_suu) {
      pAct->patbase = timepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
      plsubchg_flag = 2;
    }
  }
  else {

    pltimeover_f &= 254;
    if (pl_suu) {

      frameout(pAct);
      return;
    }
  }

  plsubchg_flag |= 128;
  if (actwkchk(&pTmpAct) != 0) {

    frameout(pAct);
    return;
  }

  pTmpAct->actno = 59;
  pTmpAct->r_no0 = pAct->r_no0;
  pTmpAct->sproffset = pAct->sproffset;
  pTmpAct->patbase = pAct->patbase;
  pTmpAct->patno = 1;
  pTmpAct->yposi.w.h = 224;
  pTmpAct->xposi.w.h = 448;
  ((short*)pTmpAct)[23] = 288;

  if (pl_suu) {
    over_move(pAct);
  }
  else {
    sub_sync(110);
  }
}


static void over_move(sprite_status* pAct) {
  if (pAct->xposi.w.h < (short)((unsigned short*)pAct)[23]) {
    pAct->xposi.w.h += 8;
  }
  else if (pAct->xposi.w.h > (short)((unsigned short*)pAct)[23]) {
    pAct->xposi.w.h -= 8;
  }
  actionsub(pAct);

}



void title(sprite_status* pAct) {
  switch (pAct->r_no0) {
    case 0:
      title_init(pAct);
      break;
    case 2:
      title_move0(pAct);
      break;
    case 4:
      title_move1(pAct);
      break;
    case 6:
      title_back0(pAct);
      break;
    case 8:
      title_back1(pAct);
      break;
    case 10:
      title_wait(pAct);
      break;
  }

}


static void title_init(sprite_status* pAct) {
  sprite_status* pTmpAct;
  unsigned short* wp;
  int i;

  pAct->r_no0 = 2;
  pAct->xposi.w.h = 280;
  pAct->yposi.w.h = 48;
  ((short*)pAct)[26] = 48;
  ((short*)pAct)[25] = 240;
  pAct->pattim = 90;
  pAct->sproffset = 32768;
  pAct->patbase = title_pats[stageno_i.b.h][stageno_i.b.l];
  pAct->sprpri = 4;



  wp = title_tbls[stageno_i.b.h];
  for (i = 0; i < 8; ++i) {
    actwkchk(&pTmpAct);
    pTmpAct->actno = 60;
    pTmpAct->r_no0 = 4;
    pTmpAct->sproffset = 32768;
    pTmpAct->patbase = title_pats[stageno_i.b.h][stageno_i.b.l];

    pTmpAct->yposi.w.h = *wp++;
    pTmpAct->xposi.w.h = *wp;
    ((short*)pTmpAct)[24] = *wp++;
    ((short*)pTmpAct)[23] = *wp++;
    pTmpAct->patno = (*wp & 65280) >> 8;
    if (i == 5) {
      pTmpAct->patno = pTmpAct->patno + (unsigned char)stageno.b.l;
    }
    pTmpAct->pattim = *wp++ & 255;
  }

}



static void title_move0(sprite_status* pAct) {
  if (pAct->yposi.w.h == (short)((unsigned short*)pAct)[25]) {
    pAct->r_no0 += 4;
  }
  else if (pAct->yposi.w.h < (short)((unsigned short*)pAct)[25]) {
    pAct->yposi.w.h += 8;
  }
  else {
    pAct->yposi.w.h -= 8;
  }
  actionsub(pAct);

}


static void title_move1(sprite_status* pAct) {
  if (pAct->xposi.w.h == (short)((unsigned short*)pAct)[23]) {
    pAct->r_no0 += 4;
  }
  else if (pAct->xposi.w.h < (short)((unsigned short*)pAct)[23]) {
    pAct->xposi.w.h += 8;
  }
  else {
    pAct->xposi.w.h -= 8;
  }
  actionsub(pAct);


}


static void title_back0(sprite_status* pAct) {
  if (pAct->pattim) {
    --pAct->pattim;
  }
  else {
    if (pAct->yposi.w.h == (short)((unsigned short*)pAct)[26]) {
      pAct->r_no0 += 4;
      scroll_start.b.h = 1;
      return;
    }
    if (pAct->yposi.w.h < (short)((unsigned short*)pAct)[26]) {
      pAct->yposi.w.h += 16;
    }
    else {
      pAct->yposi.w.h -= 16;
    }
  }
  actionsub(pAct);

}


static void title_back1(sprite_status* pAct) {
  if (pAct->pattim) {
    --pAct->pattim;
  }
  else {
    if (pAct->xposi.w.h == (short)((unsigned short*)pAct)[24]) {
      frameout(pAct);
      return;
    }
    if (pAct->xposi.w.h < (short)((unsigned short*)pAct)[24]) {
      pAct->xposi.w.h += 16;
    }
    else {
      pAct->xposi.w.h -= 16;
    }
  }
  actionsub(pAct);

}


static void title_wait(sprite_status* pAct) {
  scroll_start.b.h = 0;
  plautoflag = 0;
  frameout(pAct);

}






void clear(sprite_status* pAct) {
  switch (pAct->r_no0) {
    case 0:
      clear_init0(pAct);
      ClearSountWait = systemtimer.w.l;
      break;
    case 2:
      clear_init(pAct);
      ClearSountWait = systemtimer.w.l;
      break;
    case 4:
      clear_move0(pAct);
      break;
    case 6:
      clear_move1(pAct);
      break;

    case 8:
      if ((unsigned short)((unsigned short)systemtimer.w.l - ClearSountWait) >= 720) {
        pAct->r_no0 += 2;
      }
      actionsub(pAct);
      break;
    case 10:
      clear_move2(pAct);
      break;
    case 12:
      clear_wait(pAct);
      break;
  }

}

static void clear_init0(sprite_status* pAct) {
  --pAct->actfree[8];
  if (!pAct->actfree[8]) {
    pAct->r_no0 = 2;
    clear_init(pAct);
  }

  WaitCount = 1; pAct->r_no0 = 12;

}








static void clear_init(sprite_status* pAct) {
  sprite_status* pTmpAct;
  unsigned short* wp;
  int i;

  if (stageno.w == 1282) goto label1;
  if (actwk[0].xposi.w.h > (short)(scra_h_posit.w.h + 336)) {



label1:
    pTmpAct = pAct;
    wp = cleartbl;
    for (i = 0; i < 3; ++i) {
      ((short*)pTmpAct)[27] = 360;
      pTmpAct->actno = 58;
      pTmpAct->r_no0 = 4;
      pTmpAct->sproffset = 32768;
      if (stageno.w == 1282) {
        pTmpAct->sproffset = 32768;
        pTmpAct->patbase = gotpats_0[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
        if (generate_flag) {
          pTmpAct->patbase = madepats_0[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
        }
      }
      else {

        pTmpAct->patbase = gotpats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
        if (generate_flag) {
          pTmpAct->patbase = madepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
        }
      }

      pTmpAct->yposi.w.h = *wp++;
      pTmpAct->xposi.w.h = *wp++;
      ((short*)pTmpAct)[23] = *wp++;
      pTmpAct->patno = *wp++ & 255;

      if (i == 2) {
        pTmpAct->patno = pTmpAct->patno + stageno.b.l;
      }
      actwkchk(&pTmpAct);
    }
  }
}



static void clear_move0(sprite_status* pAct) {
  if (((unsigned short*)pAct)[27]) {
    --((unsigned short*)pAct)[27];
  }

  if (pAct->xposi.w.h == (short)((unsigned short*)pAct)[23]) {

    if (!pAct->patno) {
      pAct->r_no0 += 2;
    }
  }
  else if (pAct->xposi.w.h > (short)((unsigned short*)pAct)[23]) {
    pAct->xposi.w.h -= 8;
  }
  else {
    pAct->xposi.w.h += 8;
  }


  if (((unsigned short*)pAct)[27] < 352) {
    actionsub(pAct);
  }

}



static void clear_move1(sprite_status* pAct) {
  int_union lD0;

  lD0.l = 0;
  bonus_f = 1;
  if (!timebonus) {
    if (!ringbonus) {
      --((unsigned short*)pAct)[27];
      if (((short*)pAct)[27] < 0) {
        pAct->r_no0 += 2;
        if (systemtimer.w.l - ClearSountWait >= 540) {
          ClearSountWait = systemtimer.w.l - 540;
        }
      }

      if (((short*)pAct)[27] == 30) {
        if (special_flag) {
          soundset(200);
        }
      }

      actionsub(pAct);
      return;
    }
  }

  if (timebonus) {
    lD0.w.l += 10;
    timebonus -= 100;
  }
  if (ringbonus) {

    lD0.w.l += 10;
    ringbonus -= 100;
  }

  if (!timebonus && !ringbonus) {
    WaveAllStop();
    soundset(154);
    if (((unsigned short*)pAct)[27] >= 45) {
      ((unsigned short*)pAct)[27] = 45;
    }
  }
  else {

    if (((unsigned short*)pAct)[27]) {
      --((unsigned short*)pAct)[27];
    }

    if (pAct->actfree[8] % 2 == 0) {
      soundset(189);
    }
  }

  scoreup(lD0.l);
  actionsub(pAct);

}


static void clear_move2(sprite_status* pAct) {
  short_union wD0;

  gameflag.w = 2;
  plflag = 0;
  enecgflg = 0;

  flowercnt[0] = 0;
  flowercnt[1] = 0;
  flowercnt[2] = 0;
  tv_flag = 0;

  enkeino = 0;
  projector_flag = 0;
  markerno = 0;

  if (ta_flag) {
    play_start &= 254;
  }

  play_start &= 253;
  time_flag = 1;
  wD0.w = stageno.w;
  ++wD0.b.l;
  if (wD0.b.l == 2) {
    time_flag = 2;
  }
  if (wD0.b.l == 3) {
    ++wD0.b.h;
    wD0.b.l = 0;
  }
  stageno.w = wD0.w;

  flagwkclr();
  fadeout_s();
  actionsub(pAct);
  if (stageno.b.l == 0) {
    gf_flag = 0;
    return;
  }

  if (!ta_flag) {
    if (clrspflg_save != 127) {
      if (!generate_flag) return;
      generate_flag = 0;

      gf_flag |= 1 << stageno.b.l - 1;
      if (gf_flag != 3) return;
    }

    generate_flag = 1;
  }

}


static void clear_wait(sprite_status* pAct) {
  if (!--WaitCount) pAct->r_no0 = 2;
}
