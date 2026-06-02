#include "EQU.h"
#include "SCORE.h"
#include "../services.h"
#include "ACTION.h"
#include "LOADER2.h"

static void tensuu(sprite_status* pAct);
static void ten_init(sprite_status* pAct);
static void ten_move(sprite_status* pAct);
static void score_init(sprite_status* pAct);
static void score_move(sprite_status* pAct);
static void ringinit(void);
static void scoreinit(void);
static void posiwrt(void);
static void bonuswrt(sprite_data* pSprdat, unsigned int lDispVal);
static void ringwrt(sprite_data* pSprdat, unsigned int lDispVal);
static void scorewrt(sprite_data* pSprdat, unsigned int lDispVal);
static void scorewrt2(sprite_data* pSprdat, unsigned int lDispVal, unsigned int* subval, short sD6, short zero_disp);
static void posiwrt0(sprite_data* pSprdat, unsigned int lDispVal);
static void playsuuwrt(sprite_data* pSprdat);
static void timewrt1(sprite_data* pSprdat, unsigned int lDispVal);
static void timewrt(sprite_data* pSprdat, unsigned int lDispVal);
static void timewrt0(sprite_data* pSprdat, unsigned int lDispVal, unsigned int* subval, short sD6);

extern short playdieset(sprite_status* pActwk);

static unsigned int subtbl[6] = { 100000, 10000, 1000, 100, 10, 1 };
static unsigned int subtblh4[4] = { 4096, 256, 16, 1 };
static sprite_pattern tenpat0 = { 2, { { -8, 0, 0, 324 }, { 0, 0, 0, 327 } } };
static sprite_pattern z3tenpat0 = { 2, { { -8, 0, 0, 345 }, { 0, 0, 0, 348 } } };
static sprite_pattern z33tenpat0 = { 2, { { -8, 0, 0, 349 }, { 0, 0, 0, 352 } } };
static sprite_pattern z6tenpat0 = { 2, { { -8, 0, 0, 344 }, { 0, 0, 0, 347 } } };
static sprite_pattern z81tenpat0 = { 2, { { -8, 0, 0, 334 }, { 0, 0, 0, 337 } } };
static sprite_pattern z82tenpat0 = { 2, { { -8, 0, 0, 343 }, { 0, 0, 0, 346 } } };
static sprite_pattern z83tenpat0 = { 2, { { -8, 0, 0, 336 }, { 0, 0, 0, 339 } } };
static sprite_pattern tenpat1 = { 2, { { -8, 0, 0, 325 }, { 0, 0, 0, 327 } } };
static sprite_pattern z3tenpat1 = { 2, { { -8, 0, 0, 346 }, { 0, 0, 0, 348 } } };
static sprite_pattern z33tenpat1 = { 2, { { -8, 0, 0, 350 }, { 0, 0, 0, 352 } } };
static sprite_pattern z6tenpat1 = { 2, { { -8, 0, 0, 345 }, { 0, 0, 0, 347 } } };
static sprite_pattern z81tenpat1 = { 2, { { -8, 0, 0, 335 }, { 0, 0, 0, 337 } } };
static sprite_pattern z82tenpat1 = { 2, { { -8, 0, 0, 344 }, { 0, 0, 0, 346 } } };
static sprite_pattern z83tenpat1 = { 2, { { -8, 0, 0, 337 }, { 0, 0, 0, 339 } } };
static sprite_pattern tenpat2 = { 2, { { -8, 0, 0, 326 }, { 0, 0, 0, 327 } } };
static sprite_pattern z3tenpat2 = { 2, { { -8, 0, 0, 347 }, { 0, 0, 0, 348 } } };
static sprite_pattern z33tenpat2 = { 2, { { -8, 0, 0, 351 }, { 0, 0, 0, 352 } } };
static sprite_pattern z6tenpat2 = { 2, { { -8, 0, 0, 346 }, { 0, 0, 0, 347 } } };
static sprite_pattern z81tenpat2 = { 2, { { -8, 0, 0, 336 }, { 0, 0, 0, 337 } } };
static sprite_pattern z82tenpat2 = { 2, { { -8, 0, 0, 345 }, { 0, 0, 0, 346 } } };
static sprite_pattern z83tenpat2 = { 2, { { -8, 0, 0, 338 }, { 0, 0, 0, 339 } } };
static sprite_pattern tenpat3 = { 2, { { -8, 0, 0, 328 }, { 0, 0, 0, 327 } } };
static sprite_pattern z3tenpat3 = { 2, { { -8, 0, 0, 349 }, { 0, 0, 0, 348 } } };
static sprite_pattern z33tenpat3 = { 2, { { -8, 0, 0, 353 }, { 0, 0, 0, 352 } } };
static sprite_pattern z6tenpat3 = { 2, { { -8, 0, 0, 348 }, { 0, 0, 0, 347 } } };
static sprite_pattern z81tenpat3 = { 2, { { -8, 0, 0, 338 }, { 0, 0, 0, 337 } } };
static sprite_pattern z82tenpat3 = { 2, { { -8, 0, 0, 347 }, { 0, 0, 0, 346 } } };
static sprite_pattern z83tenpat3 = { 2, { { -8, 0, 0, 340 }, { 0, 0, 0, 339 } } };
static sprite_pattern tenpat4 = { 1, { { -4, 0, 0, 328 } } };
static sprite_pattern z3tenpat4 = { 1, { { -4, 0, 0, 349 } } };
static sprite_pattern z33tenpat4 = { 1, { { -4, 0, 0, 353 } } };
static sprite_pattern z6tenpat4 = { 1, { { -4, 0, 0, 348 } } };
static sprite_pattern z81tenpat4 = { 1, { { -4, 0, 0, 338 } } };
static sprite_pattern z82tenpat4 = { 1, { { -4, 0, 0, 347 } } };
static sprite_pattern z83tenpat4 = { 1, { { -4, 0, 0, 340 } } };
static sprite_pattern tenpat5 = { 3, { { -12, 0, 0, 324 }, { -4, 0, 0, 327 }, { 4, 0, 0, 327 } } };
static sprite_pattern z3tenpat5 = { 3, { { -12, 0, 0, 345 }, { -4, 0, 0, 348 }, { 4, 0, 0, 348 } } };
static sprite_pattern z33tenpat5 = { 3, { { -12, 0, 0, 349 }, { -4, 0, 0, 352 }, { 4, 0, 0, 352 } } };
static sprite_pattern z6tenpat5 = { 3, { { -12, 0, 0, 344 }, { -4, 0, 0, 347 }, { 4, 0, 0, 347 } } };
static sprite_pattern z81tenpat5 = { 3, { { -12, 0, 0, 334 }, { -4, 0, 0, 337 }, { 4, 0, 0, 337 } } };
static sprite_pattern z82tenpat5 = { 3, { { -12, 0, 0, 343 }, { -4, 0, 0, 346 }, { 4, 0, 0, 346 } } };
static sprite_pattern z83tenpat5 = { 3, { { -12, 0, 0, 336 }, { -4, 0, 0, 339 }, { 4, 0, 0, 339 } } };
static sprite_pattern* tenpat[6] = {
  &tenpat0,
  &tenpat1,
  &tenpat2,
  &tenpat3,
  &tenpat4,
  &tenpat5
};
static sprite_pattern* z3tenpat[6] = {
  &z3tenpat0,
  &z3tenpat1,
  &z3tenpat2,
  &z3tenpat3,
  &z3tenpat4,
  &z3tenpat5
};
static sprite_pattern* z33tenpat[6] = {
  &z33tenpat0,
  &z33tenpat1,
  &z33tenpat2,
  &z33tenpat3,
  &z33tenpat4,
  &z33tenpat5
};
static sprite_pattern* z6tenpat[6] = {
  &z6tenpat0,
  &z6tenpat1,
  &z6tenpat2,
  &z6tenpat3,
  &z6tenpat4,
  &z6tenpat5
};
static sprite_pattern* z81tenpat[6] = {
  &z81tenpat0,
  &z81tenpat1,
  &z81tenpat2,
  &z81tenpat3,
  &z81tenpat4,
  &z81tenpat5
};
static sprite_pattern* z82tenpat[6] = {
  &z82tenpat0,
  &z82tenpat1,
  &z82tenpat2,
  &z82tenpat3,
  &z82tenpat4,
  &z82tenpat5
};
static sprite_pattern* z83tenpat[6] = {
  &z83tenpat0,
  &z83tenpat1,
  &z83tenpat2,
  &z83tenpat3,
  &z83tenpat4,
  &z83tenpat5
};
static sprite_pattern** tenpats[7][3][3] = {
  {
    { tenpat, tenpat, tenpat },
    { tenpat, tenpat, tenpat },
    { 0, 0, tenpat }
  },
  {
    { z3tenpat, z3tenpat, z3tenpat },
    { z3tenpat, z3tenpat, z3tenpat },
    { 0, 0, z33tenpat }
  },
  {
    { tenpat, tenpat, tenpat },
    { tenpat, tenpat, tenpat },
    { 0, 0, tenpat }
  },
  {
    { tenpat, tenpat, tenpat },
    { tenpat, tenpat, tenpat },
    { 0, 0, tenpat }
  },
  {
    { z6tenpat, z6tenpat, z6tenpat },
    { z6tenpat, z6tenpat, z6tenpat },
    { 0, 0, z6tenpat }
  },
  {
    { tenpat, tenpat, tenpat },
    { tenpat, tenpat, tenpat },
    { 0, 0, tenpat }
  },
  {
    { z81tenpat, z81tenpat, z81tenpat },
    { z82tenpat, z82tenpat, z82tenpat },
    { 0, 0, z83tenpat }
  }
};
sprite_pattern scorepat0 = {
  19,
  {
    { 0, 0, 0, 329 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 0 },
    { 88, 0, 0, 308 },
    { 0, 16, 0, 330 },
    { 40, 16, 0, 308 },
    { 48, 16, 0, 331 },
    { 56, 16, 0, 308 },
    { 64, 16, 0, 308 },
    { 72, 16, 0, 332 },
    { 80, 16, 0, 308 },
    { 88, 16, 0, 308 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 308 }
  }
};
sprite_pattern z3scorepat0 = {
  19,
  {
    { 0, 0, 0, 350 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 0 },
    { 88, 0, 0, 329 },
    { 0, 16, 0, 351 },
    { 40, 16, 0, 329 },
    { 48, 16, 0, 352 },
    { 56, 16, 0, 329 },
    { 64, 16, 0, 329 },
    { 72, 16, 0, 353 },
    { 80, 16, 0, 329 },
    { 88, 16, 0, 329 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 329 }
  }
};
sprite_pattern z33scorepat0 = {
  19,
  {
    { 0, 0, 0, 354 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 0 },
    { 88, 0, 0, 333 },
    { 0, 16, 0, 355 },
    { 40, 16, 0, 333 },
    { 48, 16, 0, 356 },
    { 56, 16, 0, 333 },
    { 64, 16, 0, 333 },
    { 72, 16, 0, 357 },
    { 80, 16, 0, 333 },
    { 88, 16, 0, 333 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 333 }
  }
};
sprite_pattern z6scorepat0 = {
  19,
  {
    { 0, 0, 0, 349 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 0 },
    { 88, 0, 0, 328 },
    { 0, 16, 0, 350 },
    { 40, 16, 0, 328 },
    { 48, 16, 0, 351 },
    { 56, 16, 0, 328 },
    { 64, 16, 0, 328 },
    { 72, 16, 0, 352 },
    { 80, 16, 0, 328 },
    { 88, 16, 0, 328 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 328 }
  }
};
sprite_pattern z81scorepat0 = {
  19,
  {
    { 0, 0, 0, 339 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 0 },
    { 88, 0, 0, 318 },
    { 0, 16, 0, 340 },
    { 40, 16, 0, 318 },
    { 48, 16, 0, 341 },
    { 56, 16, 0, 318 },
    { 64, 16, 0, 318 },
    { 72, 16, 0, 342 },
    { 80, 16, 0, 318 },
    { 88, 16, 0, 318 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 318 }
  }
};
sprite_pattern z82scorepat0 = {
  19,
  {
    { 0, 0, 0, 348 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 0 },
    { 88, 0, 0, 327 },
    { 0, 16, 0, 349 },
    { 40, 16, 0, 327 },
    { 48, 16, 0, 350 },
    { 56, 16, 0, 327 },
    { 64, 16, 0, 327 },
    { 72, 16, 0, 351 },
    { 80, 16, 0, 327 },
    { 88, 16, 0, 327 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 327 }
  }
};
sprite_pattern z83scorepat0 = {
  19,
  {
    { 0, 0, 0, 341 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 0 },
    { 88, 0, 0, 320 },
    { 0, 16, 0, 342 },
    { 40, 16, 0, 320 },
    { 48, 16, 0, 343 },
    { 56, 16, 0, 320 },
    { 64, 16, 0, 320 },
    { 72, 16, 0, 344 },
    { 80, 16, 0, 320 },
    { 88, 16, 0, 320 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 320 }
  }
};
sprite_pattern scorepat1 = { 3, { { 0, 0, 0, 337 }, { 16, 8, 0, 333 }, { 24, 4, 0, 308 } } };
sprite_pattern z3scorepat1 = { 3, { { 0, 0, 0, 358 }, { 16, 8, 0, 354 }, { 24, 4, 0, 329 } } };
sprite_pattern z33scorepat1 = { 3, { { 0, 0, 0, 362 }, { 16, 8, 0, 358 }, { 24, 4, 0, 333 } } };
sprite_pattern z6scorepat1 = { 3, { { 0, 0, 0, 357 }, { 16, 8, 0, 353 }, { 24, 4, 0, 328 } } };
sprite_pattern z81scorepat1 = { 3, { { 0, 0, 0, 347 }, { 16, 8, 0, 343 }, { 24, 4, 0, 318 } } };
sprite_pattern z82scorepat1 = { 3, { { 0, 0, 0, 356 }, { 16, 8, 0, 352 }, { 24, 4, 0, 327 } } };
sprite_pattern z83scorepat1 = { 3, { { 0, 0, 0, 349 }, { 16, 8, 0, 345 }, { 24, 4, 0, 320 } } };
sprite_pattern scorepat2 = {
  15,
  {
    { 0, 0, 0, 329 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 308 },
    { 0, 16, 0, 330 },
    { 56, 16, 0, 0 },
    { 64, 16, 0, 0 },
    { 72, 16, 0, 0 },
    { 80, 16, 0, 308 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 308 }
  }
};
sprite_pattern z3scorepat2 = {
  15,
  {
    { 0, 0, 0, 350 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 329 },
    { 0, 16, 0, 351 },
    { 56, 16, 0, 0 },
    { 64, 16, 0, 0 },
    { 72, 16, 0, 0 },
    { 80, 16, 0, 329 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 329 }
  }
};
sprite_pattern z33scorepat2 = {
  15,
  {
    { 0, 0, 0, 354 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 333 },
    { 0, 16, 0, 355 },
    { 56, 16, 0, 0 },
    { 64, 16, 0, 0 },
    { 72, 16, 0, 0 },
    { 80, 16, 0, 333 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 333 }
  }
};
sprite_pattern z6scorepat2 = {
  15,
  {
    { 0, 0, 0, 349 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 328 },
    { 0, 16, 0, 350 },
    { 56, 16, 0, 0 },
    { 64, 16, 0, 0 },
    { 72, 16, 0, 0 },
    { 80, 16, 0, 328 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 328 }
  }
};
sprite_pattern z81scorepat2 = {
  15,
  {
    { 0, 0, 0, 339 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 318 },
    { 0, 16, 0, 340 },
    { 56, 16, 0, 0 },
    { 64, 16, 0, 0 },
    { 72, 16, 0, 0 },
    { 80, 16, 0, 318 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 318 }
  }
};
sprite_pattern z82scorepat2 = {
  15,
  {
    { 0, 0, 0, 348 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 327 },
    { 0, 16, 0, 349 },
    { 56, 16, 0, 0 },
    { 64, 16, 0, 0 },
    { 72, 16, 0, 0 },
    { 80, 16, 0, 327 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 327 }
  }
};
sprite_pattern z83scorepat2 = {
  15,
  {
    { 0, 0, 0, 341 },
    { 40, 0, 0, 0 },
    { 48, 0, 0, 0 },
    { 56, 0, 0, 0 },
    { 64, 0, 0, 0 },
    { 72, 0, 0, 0 },
    { 80, 0, 0, 320 },
    { 0, 16, 0, 342 },
    { 56, 16, 0, 0 },
    { 64, 16, 0, 0 },
    { 72, 16, 0, 0 },
    { 80, 16, 0, 320 },
    { 48, 32, 0, 0 },
    { 56, 32, 0, 0 },
    { 64, 32, 0, 320 }
  }
};
sprite_pattern scorepat3 = { 1, { { 0, 32, 0, 334 } } };
sprite_pattern z3scorepat3 = { 1, { { 0, 32, 0, 355 } } };
sprite_pattern z33scorepat3 = { 1, { { 0, 32, 0, 359 } } };
sprite_pattern z6scorepat3 = { 1, { { 0, 32, 0, 354 } } };
sprite_pattern z81scorepat3 = { 1, { { 0, 32, 0, 344 } } };
sprite_pattern z82scorepat3 = { 1, { { 0, 32, 0, 353 } } };
sprite_pattern z83scorepat3 = { 1, { { 0, 32, 0, 346 } } };
static sprite_pattern* scorepat[4] = {
  &scorepat0,
  &scorepat1,
  &scorepat2,
  &scorepat3
};
static sprite_pattern* z3scorepat[4] = {
  &z3scorepat0,
  &z3scorepat1,
  &z3scorepat2,
  &z3scorepat3
};
static sprite_pattern* z33scorepat[4] = {
  &z33scorepat0,
  &z33scorepat1,
  &z33scorepat2,
  &z33scorepat3
};
static sprite_pattern* z6scorepat[4] = {
  &z6scorepat0,
  &z6scorepat1,
  &z6scorepat2,
  &z6scorepat3
};
static sprite_pattern* z81scorepat[4] = {
  &z81scorepat0,
  &z81scorepat1,
  &z81scorepat2,
  &z81scorepat3
};
static sprite_pattern* z82scorepat[4] = {
  &z82scorepat0,
  &z82scorepat1,
  &z82scorepat2,
  &z82scorepat3
};
static sprite_pattern* z83scorepat[4] = {
  &z83scorepat0,
  &z83scorepat1,
  &z83scorepat2,
  &z83scorepat3
};
static sprite_pattern** scorepats[7][3][3] = {
  {
    { scorepat, scorepat, scorepat },
    { scorepat, scorepat, scorepat },
    { 0, 0, scorepat }
  },
  {
    { z3scorepat, z3scorepat, z3scorepat },
    { z3scorepat, z3scorepat, z3scorepat },
    { 0, 0, z33scorepat }
  },
  {
    { scorepat, scorepat, scorepat },
    { scorepat, scorepat, scorepat },
    { 0, 0, scorepat }
  },
  {
    { scorepat, scorepat, scorepat },
    { scorepat, scorepat, scorepat },
    { 0, 0, scorepat }
  },
  {
    { z6scorepat, z6scorepat, z6scorepat },
    { z6scorepat, z6scorepat, z6scorepat },
    { 0, 0, z6scorepat }
  },
  {
    { scorepat, scorepat, scorepat },
    { scorepat, scorepat, scorepat },
    { 0, 0, scorepat }
  },
  {
    { z81scorepat, z81scorepat, z81scorepat },
    { z82scorepat, z82scorepat, z82scorepat },
    { 0, 0, z83scorepat }
  },
};
extern sprite_pattern* bonuspats[7][3][3];
extern sprite_pattern* bonuspat0s[7][3][3];
unsigned char scoreinittbl[7] = { 255, 255, 255, 255, 255, 255, 0 };
unsigned char ringinittbl[3] = { 255, 255, 0 };
unsigned short digit0indexes[7][3] = {
  { 308, 308, 308 },
  { 329, 329, 333 },
  { 308, 308, 308 },
  { 308, 308, 308 },
  { 328, 328, 328 },
  { 308, 308, 308 },
  { 318, 327, 320 }
};


static void tensuu(sprite_status* pAct) {
  if (!pAct->r_no0) ten_init(pAct);
  ten_move(pAct);
  actionsub(pAct);


}


static void ten_init(sprite_status* pAct) {
  pAct->r_no0 = 2;
  pAct->actflg = 4;
  pAct->patbase = tenpats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  pAct->patno = pAct->userflag.b.h & 127;
  pAct->actfree[0] = 24;


}


static void ten_move(sprite_status* pAct) {
  --pAct->actfree[0];


  if (!pAct->actfree[0])
    frameout(pAct);
  pAct->yposi.w.h -= 2;


}


void score(sprite_status* pAct) {
  if ((unsigned char)pAct->userflag.b.h & 128) {
    tensuu(pAct);
    return;
  }
  if (!pAct->r_no0) score_init(pAct);
  score_move(pAct);

}


static void score_init(sprite_status* pAct) {
  unsigned short lifeicon_past_indexes[7][3] = {
    { 338, 338, 338 },
    { 359, 359, 363 },
    { 338, 338, 338 },
    { 338, 338, 338 },
    { 358, 358, 358 },
    { 338, 338, 338 },
    { 348, 357, 350 }
  };
  unsigned short lifeicon_present_indexes[7][3] = {
    { 337, 337, 337 },
    { 358, 358, 362 },
    { 337, 337, 337 },
    { 337, 337, 337 },
    { 357, 357, 357 },
    { 337, 337, 337 },
    { 347, 356, 349 }
  };
  unsigned short lifeicon_future_indexes[7][3] = {
    { 336, 336, 336 },
    { 357, 357, 361 },
    { 336, 336, 336 },
    { 336, 336, 336 },
    { 356, 356, 356 },
    { 336, 336, 336 },
    { 346, 355, 348 }
  };

  pAct->r_no0 = 2;
  pAct->patbase = scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  pAct->sproffset = 32768;
  pAct->xposi.w.h = 104;
  pAct->yposi.w.h = 136;
  if (pAct->userflag.b.l) {
    pAct->patno = 3;
    return;
  }

  if (debugflag.w) {
    pAct->patno = 2;
  }

  if (pAct->userflag.b.h) {
    pAct->yposi.w.h = 328;
    pAct->patno = 1;

    switch (time_flag & 3) {
      case 0:
        scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][1]->spr[0].index = lifeicon_past_indexes[stageno_i.b.h][stageno_i.b.l];
        break;
      case 1:
        scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][1]->spr[0].index = lifeicon_present_indexes[stageno_i.b.h][stageno_i.b.l];
        break;
      default:
        scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][1]->spr[0].index = lifeicon_future_indexes[stageno_i.b.h][stageno_i.b.l];
        break;
    }
  }


}

static void score_move(sprite_status* pAct) {
  unsigned short rings_normal_indexes[7][3] = {
    { 334, 334, 334 },
    { 355, 355, 359 },
    { 334, 334, 334 },
    { 334, 334, 334 },
    { 354, 354, 354 },
    { 334, 334, 334 },
    { 344, 353, 346 }
  };
  unsigned short rings_danger_indexes[7][3] = {
    { 335, 335, 335 },
    { 356, 356, 360 },
    { 335, 335, 335 },
    { 335, 335, 335 },
    { 355, 355, 355 },
    { 335, 335, 335 },
    { 345, 354, 347 }
  };

  if (!pAct->userflag.b.h) {
    if (pAct->userflag.b.l) {
      if (plring) {
        pAct->sproffset = 32768;
        scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][3]->spr[0].index = rings_normal_indexes[stageno_i.b.h][stageno_i.b.l];

      }
      else {

        if (!(systemtimer.b.b4 & 15)) {
          if (scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][3]->spr[0].index == rings_normal_indexes[stageno_i.b.h][stageno_i.b.l])
            scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][3]->spr[0].index = rings_danger_indexes[stageno_i.b.h][stageno_i.b.l];
          else
            scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][3]->spr[0].index = rings_normal_indexes[stageno_i.b.h][stageno_i.b.l];
        }
      }
    }
    else {

      pAct->patno = 0;
      if (debugflag.w) {
        pAct->patno = 2;
      }
    }
  }

  actionsub(pAct);


}




void scoreup(unsigned int updata) {
  plscore_f = 1;

  plscore += updata;
  if ((unsigned int)plscore > 999999) {

    plscore = 999999;
  }
  if (extrascore > (unsigned int)plscore) return;


  extrascore += 5000;
  ++pl_suu;
  ++pl_suu_f;
  WaveAllStop();
  sub_sync(122);


}





void scoreset(void) {
  sprite_data* pSprdat;
  sprite_pattern* pSprpat;

  pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][2]->spr[3];
  if (debugflag.w) {
    posiwrt();

    pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][2]->spr[12];
    timewrt0(pSprdat, blkno & 2047, &subtbl[3], 2);
  }
  else {

    if (plscore_f) {
      if (plscore_f & 128) {
        scoreinit();
      }

      plscore_f = 0;
      pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][0]->spr[1];
      scorewrt(pSprdat, plscore);
    }

    if (plring_f) {
      if (plring_f & 128) {
        ringinit();
      }

      plring_f = 0;
      if (plring > 999) plring = 999;

      pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][0]->spr[16];
      ringwrt(pSprdat, plring);
    }
  }

  if (!debugflag.w && pltime_f && !pauseflag.b.h) {
    if (pltime.l == 604987) {

      if (time_flag & 128) return;



      pltime_f = 0;
      pltime.l = 0;
      playdieset(&actwk[0]);
      pltimeover_f = 1;

      return;
    }
    if (pltime.l != 604987) {
      if (!plautoflag) {

        ++pltime.b.b4;
        if ((unsigned char)pltime.b.b4 >= 60) {
          pltime.b.b4 = 0;
          ++pltime.b.b3;
          if ((unsigned char)pltime.b.b3 >= 60) {
            pltime.b.b3 = 0;
            ++pltime.b.b2;
            if ((unsigned char)pltime.b.b2 >= 9) {
              pltime.b.b2 = 9;
            }
          }
        }
      }
    }

    pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][0]->spr[9];
    timewrt1(pSprdat, pltime.b.b2);

    pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][0]->spr[11];
    timewrt(pSprdat, pltime.b.b3);

    pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][0]->spr[14];
    if (pltime.l == 604987) {
      timewrt(pSprdat, 99);
    }
    else {
      timewrt(pSprdat, (pltime.b.b4 * 100) / 60);
    }
  }


  if (pl_suu_f) {
    pl_suu_f = 0;
    pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][1]->spr[2];
    playsuuwrt(pSprdat);
  }

  if (bonus_f) {
    bonus_f = 0;
    if (stageno.w == 1282) pSprpat = bonuspat0s[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
    else pSprpat = bonuspats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
    bonuswrt(&pSprpat->spr[8], (unsigned short)ringbonus);
    bonuswrt(&pSprpat->spr[13], (unsigned short)timebonus);
    scorewrt(&pSprpat->spr[1], plscore);
    pSprpat->spr[7].index = digit0indexes[stageno_i.b.h][stageno_i.b.l];
  }


}








static void ringinit(void) {}

static void scoreinit(void) {
  sprite_data* pSprdat;

  pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][1]->spr[2];
  playsuuwrt(pSprdat);


}













static void posiwrt(void) {
  sprite_data* pSprdat;
  int_union lwk;

  lwk.l = 0;
  lwk.w.l = actwk[0].xposi.w.h;
  pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][2]->spr[3];
  posiwrt0(pSprdat, lwk.l);

  lwk.w.l = actwk[0].yposi.w.h;
  pSprdat = &scorepats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F][2]->spr[8];
  posiwrt0(pSprdat, lwk.l);
}



static void bonuswrt(sprite_data* pSprdat, unsigned int lDispVal) {
  scorewrt2(pSprdat, lDispVal, &subtbl[1], 4, 1);

}

static void ringwrt(sprite_data* pSprdat, unsigned int lDispVal) {
  scorewrt2(pSprdat, lDispVal, &subtbl[3], 2, 1);

}


static void scorewrt(sprite_data* pSprdat, unsigned int lDispVal) {
  scorewrt2(pSprdat, lDispVal, &subtbl[0], 5, 0);

}

static void scorewrt2(sprite_data* pSprdat, unsigned int lDispVal, unsigned int* subval, short sD6, short zero_disp) {
  unsigned int lDisp1;
  int wrt = 0;

  do {
    lDisp1 = lDispVal / *subval;
    lDispVal -= lDisp1 * *subval;
    ++subval;
    if (lDisp1 != 0) {
      wrt = 1;
    }
    if (wrt != 0 || (sD6 == 0 && zero_disp)) {
      pSprdat->index = (unsigned short)lDisp1 + digit0indexes[stageno_i.b.h][stageno_i.b.l];
    }
    else {
      pSprdat->index = 0;
    }
    ++pSprdat;
  } while (--sD6 >= 0);


}





static void posiwrt0(sprite_data* pSprdat, unsigned int lDispVal) {
  timewrt0(pSprdat, lDispVal, &subtblh4[0], 3);

}


static void playsuuwrt(sprite_data* pSprdat) {
  unsigned int lDispVal;

  if (pl_suu > 9)
    lDispVal = 9;
  else
    lDispVal = pl_suu;

  timewrt0(pSprdat, lDispVal, &subtbl[5], 0);

}



static void timewrt1(sprite_data* pSprdat, unsigned int lDispVal) {
  timewrt0(pSprdat, lDispVal, &subtbl[5], 0);

}

static void timewrt(sprite_data* pSprdat, unsigned int lDispVal) {
  timewrt0(pSprdat, lDispVal, &subtbl[4], 1);

}







static void timewrt0(sprite_data* pSprdat, unsigned int lDispVal, unsigned int* subval, short sD6) {
  unsigned short lDisp1;

  do {
    lDisp1 = lDispVal / *subval;
    lDispVal -= lDisp1 * *subval;
    ++subval;
    pSprdat->index = lDisp1 + digit0indexes[stageno_i.b.h][stageno_i.b.l];
    ++pSprdat;
  } while (--sD6 >= 0);













}
