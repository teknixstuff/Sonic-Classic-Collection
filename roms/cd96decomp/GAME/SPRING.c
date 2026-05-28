#include "EQU.h"
#include "SPRING.h"
#include "ACTION.h"
#include "ACTSET.h"
#include "DIRCOL.h"
#include "DUMMY.h"
#include "ETC.h"
#include "LOADER2.h"
#include "PLAYSUB.h"
#include "RIDECHK.h"

static sprite_pattern spat00 = { 1, { { -16, -8, 0, 382 } }};
static sprite_pattern z1spat00 = { 1, { { -16, -8, 0, 450 } }};
static sprite_pattern z11aspat00 = { 1, { { -16, -8, 0, 467 } }};
static sprite_pattern z3spat00 = { 1, { { -16, -8, 0, 369 } }};
static sprite_pattern z33spat00 = { 1, { { -16, -8, 0, 373 } }};
static sprite_pattern z6spat00 = { 1, { { -16, -8, 0, 368 } }};
static sprite_pattern z81spat00 = { 1, { { -16, -8, 0, 358 } }};
static sprite_pattern z82spat00 = { 1, { { -16, -8, 0, 367 } }};
static sprite_pattern z83spat00 = { 1, { { -16, -8, 0, 360 } }};
static sprite_pattern spat01 = { 1, { { -16, 0, 0, 383 } }};
static sprite_pattern z1spat01 = { 1, { { -16, 0, 0, 451 } }};
static sprite_pattern z11aspat01 = { 1, { { -16, 0, 0, 468 } }};
static sprite_pattern z3spat01 = { 1, { { -16, 0, 0, 370 } }};
static sprite_pattern z33spat01 = { 1, { { -16, 0, 0, 374 } }};
static sprite_pattern z6spat01 = { 1, { { -16, 0, 0, 369 } }};
static sprite_pattern z81spat01 = { 1, { { -16, 0, 0, 359 } }};
static sprite_pattern z82spat01 = { 1, { { -16, 0, 0, 368 } }};
static sprite_pattern z83spat01 = { 1, { { -16, 0, 0, 361 } }};
static sprite_pattern spat02 = { 1, { { -16, -32, 0, 384 } }};
static sprite_pattern z1spat02 = { 1, { { -16, -32, 0, 452 } }};
static sprite_pattern z11aspat02 = { 1, { { -16, -32, 0, 469 } }};
static sprite_pattern z3spat02 = { 1, { { -16, -32, 0, 371 } }};
static sprite_pattern z33spat02 = { 1, { { -16, -32, 0, 375 } }};
static sprite_pattern z6spat02 = { 1, { { -16, -32, 0, 370 } }};
static sprite_pattern z81spat02 = { 1, { { -16, -32, 0, 360 } }};
static sprite_pattern z82spat02 = { 1, { { -16, -32, 0, 369 } }};
static sprite_pattern z83spat02 = { 1, { { -16, -32, 0, 362 } }};
static sprite_pattern spat03 = { 1, { { -8, -16, 0, 385 } }};
static sprite_pattern z1spat03 = { 1, { { -8, -16, 0, 453 } }};
static sprite_pattern z11aspat03 = { 1, { { -8, -16, 0, 470 } }};
static sprite_pattern z3spat03 = { 1, { { -8, -16, 0, 372 } }};
static sprite_pattern z33spat03 = { 1, { { -8, -16, 0, 376 } }};
static sprite_pattern z6spat03 = { 1, { { -8, -16, 0, 371 } }};
static sprite_pattern z81spat03 = { 1, { { -8, -16, 0, 361 } }};
static sprite_pattern z82spat03 = { 1, { { -8, -16, 0, 370 } }};
static sprite_pattern z83spat03 = { 1, { { -8, -16, 0, 363 } }};
static sprite_pattern spat04 = { 1, { { -8, -16, 0, 386 } }};
static sprite_pattern z1spat04 = { 1, { { -8, -16, 0, 454 } }};
static sprite_pattern z11aspat04 = { 1, { { -8, -16, 0, 471 } }};
static sprite_pattern z3spat04 = { 1, { { -8, -16, 0, 373 } }};
static sprite_pattern z33spat04 = { 1, { { -8, -16, 0, 377 } }};
static sprite_pattern z6spat04 = { 1, { { -8, -16, 0, 372 } }};
static sprite_pattern z81spat04 = { 1, { { -8, -16, 0, 362 } }};
static sprite_pattern z82spat04 = { 1, { { -8, -16, 0, 371 } }};
static sprite_pattern z83spat04 = { 1, { { -8, -16, 0, 364 } }};
static sprite_pattern spat05 = { 1, { { -8, -16, 0, 387 } }};
static sprite_pattern z1spat05 = { 1, { { -8, -16, 0, 455 } }};
static sprite_pattern z11aspat05 = { 1, { { -8, -16, 0, 472 } }};
static sprite_pattern z3spat05 = { 1, { { -8, -16, 0, 374 } }};
static sprite_pattern z33spat05 = { 1, { { -8, -16, 0, 378 } }};
static sprite_pattern z6spat05 = { 1, { { -8, -16, 0, 373 } }};
static sprite_pattern z81spat05 = { 1, { { -8, -16, 0, 363 } }};
static sprite_pattern z82spat05 = { 1, { { -8, -16, 0, 372 } }};
static sprite_pattern z83spat05 = { 1, { { -8, -16, 0, 365 } }};
static sprite_pattern spat06 = { 1, { { -16, -16, 0, 388 } }};
static sprite_pattern z1spat06 = { 1, { { -16, -16, 0, 456 } }};
static sprite_pattern z11aspat06 = { 1, { { -16, -16, 0, 473 } }};
static sprite_pattern z3spat06 = { 1, { { -16, -16, 0, 375 } }};
static sprite_pattern z33spat06 = { 1, { { -16, -16, 0, 379 } }};
static sprite_pattern z6spat06 = { 1, { { -16, -16, 0, 374 } }};
static sprite_pattern z81spat06 = { 1, { { -16, -16, 0, 364 } }};
static sprite_pattern z82spat06 = { 1, { { -16, -16, 0, 373 } }};
static sprite_pattern z83spat06 = { 1, { { -16, -16, 0, 366 } }};
static sprite_pattern spat07 = { 1, { { -16, -16, 0, 389 } }};
static sprite_pattern z1spat07 = { 1, { { -16, -16, 0, 457 } }};
static sprite_pattern z11aspat07 = { 1, { { -16, -16, 0, 474 } }};
static sprite_pattern z3spat07 = { 1, { { -16, -16, 0, 376 } }};
static sprite_pattern z33spat07 = { 1, { { -16, -16, 0, 380 } }};
static sprite_pattern z6spat07 = { 1, { { -16, -16, 0, 375 } }};
static sprite_pattern z81spat07 = { 1, { { -16, -16, 0, 365 } }};
static sprite_pattern z82spat07 = { 1, { { -16, -16, 0, 374 } }};
static sprite_pattern z83spat07 = { 1, { { -16, -16, 0, 367 } }};
static sprite_pattern spat08 = { 1, { { -16, -32, 0, 390 } }};
static sprite_pattern z1spat08 = { 1, { { -16, -32, 0, 458 } }};
static sprite_pattern z11aspat08 = { 1, { { -16, -32, 0, 475 } }};
static sprite_pattern z3spat08 = { 1, { { -16, -32, 0, 377 } }};
static sprite_pattern z33spat08 = { 1, { { -16, -32, 0, 381 } }};
static sprite_pattern z6spat08 = { 1, { { -16, -32, 0, 376 } }};
static sprite_pattern z81spat08 = { 1, { { -16, -32, 0, 366 } }};
static sprite_pattern z82spat08 = { 1, { { -16, -32, 0, 375 } }};
static sprite_pattern z83spat08 = { 1, { { -16, -32, 0, 368 } }};
static sprite_pattern kpat00 = { 1, { { -8, -8, 0, 391 } }};
static sprite_pattern z1kpat00 = { 1, { { -8, -8, 0, 459 } }};
static sprite_pattern z11akpat00 = { 1, { { -8, -8, 0, 476 } }};
static sprite_pattern z3kpat00 = { 1, { { -8, -8, 0, 378 } }};
static sprite_pattern z33kpat00 = { 1, { { -8, -8, 0, 382 } }};
static sprite_pattern z6kpat00 = { 1, { { -8, -8, 0, 377 } }};
static sprite_pattern z81kpat00 = { 1, { { -8, -8, 0, 367 } }};
static sprite_pattern z82kpat00 = { 1, { { -8, -8, 0, 376 } }};
static sprite_pattern z83kpat00 = { 1, { { -8, -8, 0, 369 } }};
static sprite_pattern kpat01 = { 1, { { -8, -8, 0, 392 } }};
static sprite_pattern z1kpat01 = { 1, { { -8, -8, 0, 460 } }};
static sprite_pattern z11akpat01 = { 1, { { -8, -8, 0, 477 } }};
static sprite_pattern z3kpat01 = { 1, { { -8, -8, 0, 379 } }};
static sprite_pattern z33kpat01 = { 1, { { -8, -8, 0, 383 } }};
static sprite_pattern z6kpat01 = { 1, { { -8, -8, 0, 378 } }};
static sprite_pattern z81kpat01 = { 1, { { -8, -8, 0, 368 } }};
static sprite_pattern z82kpat01 = { 1, { { -8, -8, 0, 377 } }};
static sprite_pattern z83kpat01 = { 1, { { -8, -8, 0, 370 } }};
static sprite_pattern ipat00 = { 1, { { -20, -16, 0, 393 } }};
static sprite_pattern z1ipat00 = { 1, { { -20, -16, 0, 461 } }};
static sprite_pattern z11aipat00 = { 1, { { -20, -16, 0, 478 } }};
static sprite_pattern z3ipat00 = { 1, { { -20, -16, 0, 380 } }};
static sprite_pattern z33ipat00 = { 1, { { -20, -16, 0, 384 } }};
static sprite_pattern z6ipat00 = { 1, { { -20, -16, 0, 379 } }};
static sprite_pattern z81ipat00 = { 1, { { -20, -16, 0, 369 } }};
static sprite_pattern z82ipat00 = { 1, { { -20, -16, 0, 378 } }};
static sprite_pattern z83ipat00 = { 1, { { -20, -16, 0, 371 } }};
static sprite_pattern spat10 = { 1, { { -16, -8, 0, 394 } }};
static sprite_pattern z1spat10 = { 1, { { -16, -8, 0, 462 } }};
static sprite_pattern z11aspat10 = { 1, { { -16, -8, 0, 479 } }};
static sprite_pattern z3spat10 = { 1, { { -16, -8, 0, 381 } }};
static sprite_pattern z33spat10 = { 1, { { -16, -8, 0, 385 } }};
static sprite_pattern z6spat10 = { 1, { { -16, -8, 0, 380 } }};
static sprite_pattern z81spat10 = { 1, { { -16, -8, 0, 370 } }};
static sprite_pattern z82spat10 = { 1, { { -16, -8, 0, 379 } }};
static sprite_pattern z83spat10 = { 1, { { -16, -8, 0, 372 } }};
static sprite_pattern spat11 = { 1, { { -16, 0, 0, 395 } }};
static sprite_pattern z1spat11 = { 1, { { -16, 0, 0, 463 } }};
static sprite_pattern z11aspat11 = { 1, { { -16, 0, 0, 480 } }};
static sprite_pattern z3spat11 = { 1, { { -16, 0, 0, 382 } }};
static sprite_pattern z33spat11 = { 1, { { -16, 0, 0, 386 } }};
static sprite_pattern z6spat11 = { 1, { { -16, 0, 0, 381 } }};
static sprite_pattern z81spat11 = { 1, { { -16, 0, 0, 371 } }};
static sprite_pattern z82spat11 = { 1, { { -16, 0, 0, 380 } }};
static sprite_pattern z83spat11 = { 1, { { -16, 0, 0, 373 } }};
static sprite_pattern spat12 = { 1, { { -16, -32, 0, 396 } }};
static sprite_pattern z1spat12 = { 1, { { -16, -32, 0, 464 } }};
static sprite_pattern z11aspat12 = { 1, { { -16, -32, 0, 481 } }};
static sprite_pattern z3spat12 = { 1, { { -16, -32, 0, 383 } }};
static sprite_pattern z33spat12 = { 1, { { -16, -32, 0, 387 } }};
static sprite_pattern z6spat12 = { 1, { { -16, -32, 0, 382 } }};
static sprite_pattern z81spat12 = { 1, { { -16, -32, 0, 372 } }};
static sprite_pattern z82spat12 = { 1, { { -16, -32, 0, 381 } }};
static sprite_pattern z83spat12 = { 1, { { -16, -32, 0, 374 } }};
static sprite_pattern spat13 = { 1, { { -8, -16, 0, 397 } }};
static sprite_pattern z1spat13 = { 1, { { -8, -16, 0, 465 } }};
static sprite_pattern z11aspat13 = { 1, { { -8, -16, 0, 482 } }};
static sprite_pattern z3spat13 = { 1, { { -8, -16, 0, 384 } }};
static sprite_pattern z33spat13 = { 1, { { -8, -16, 0, 388 } }};
static sprite_pattern z6spat13 = { 1, { { -8, -16, 0, 383 } }};
static sprite_pattern z81spat13 = { 1, { { -8, -16, 0, 373 } }};
static sprite_pattern z82spat13 = { 1, { { -8, -16, 0, 382 } }};
static sprite_pattern z83spat13 = { 1, { { -8, -16, 0, 375 } }};
static sprite_pattern spat14 = { 1, { { -8, -16, 0, 398 } }};
static sprite_pattern z1spat14 = { 1, { { -8, -16, 0, 466 } }};
static sprite_pattern z11aspat14 = { 1, { { -8, -16, 0, 483 } }};
static sprite_pattern z3spat14 = { 1, { { -8, -16, 0, 385 } }};
static sprite_pattern z33spat14 = { 1, { { -8, -16, 0, 389 } }};
static sprite_pattern z6spat14 = { 1, { { -8, -16, 0, 384 } }};
static sprite_pattern z81spat14 = { 1, { { -8, -16, 0, 374 } }};
static sprite_pattern z82spat14 = { 1, { { -8, -16, 0, 383 } }};
static sprite_pattern z83spat14 = { 1, { { -8, -16, 0, 376 } }};
static sprite_pattern spat15 = { 1, { { -8, -16, 0, 399 } }};
static sprite_pattern z1spat15 = { 1, { { -8, -16, 0, 467 } }};
static sprite_pattern z11aspat15 = { 1, { { -8, -16, 0, 484 } }};
static sprite_pattern z3spat15 = { 1, { { -8, -16, 0, 386 } }};
static sprite_pattern z33spat15 = { 1, { { -8, -16, 0, 390 } }};
static sprite_pattern z6spat15 = { 1, { { -8, -16, 0, 385 } }};
static sprite_pattern z81spat15 = { 1, { { -8, -16, 0, 375 } }};
static sprite_pattern z82spat15 = { 1, { { -8, -16, 0, 384 } }};
static sprite_pattern z83spat15 = { 1, { { -8, -16, 0, 377 } }};
static sprite_pattern spat16 = { 1, { { -16, -16, 0, 400 } }};
static sprite_pattern z1spat16 = { 1, { { -16, -16, 0, 468 } }};
static sprite_pattern z11aspat16 = { 1, { { -16, -16, 0, 485 } }};
static sprite_pattern z3spat16 = { 1, { { -16, -16, 0, 387 } }};
static sprite_pattern z33spat16 = { 1, { { -16, -16, 0, 391 } }};
static sprite_pattern z6spat16 = { 1, { { -16, -16, 0, 386 } }};
static sprite_pattern z81spat16 = { 1, { { -16, -16, 0, 376 } }};
static sprite_pattern z82spat16 = { 1, { { -16, -16, 0, 385 } }};
static sprite_pattern z83spat16 = { 1, { { -16, -16, 0, 378 } }};
static sprite_pattern spat17 = { 1, { { -16, -16, 0, 401 } }};
static sprite_pattern z1spat17 = { 1, { { -16, -16, 0, 469 } }};
static sprite_pattern z11aspat17 = { 1, { { -16, -16, 0, 486 } }};
static sprite_pattern z3spat17 = { 1, { { -16, -16, 0, 388 } }};
static sprite_pattern z33spat17 = { 1, { { -16, -16, 0, 392 } }};
static sprite_pattern z6spat17 = { 1, { { -16, -16, 0, 387 } }};
static sprite_pattern z81spat17 = { 1, { { -16, -16, 0, 377 } }};
static sprite_pattern z82spat17 = { 1, { { -16, -16, 0, 386 } }};
static sprite_pattern z83spat17 = { 1, { { -16, -16, 0, 379 } }};
static sprite_pattern spat18 = { 1, { { -16, -32, 0, 402 } }};
static sprite_pattern z1spat18 = { 1, { { -16, -32, 0, 470 } }};
static sprite_pattern z11aspat18 = { 1, { { -16, -32, 0, 487 } }};
static sprite_pattern z3spat18 = { 1, { { -16, -32, 0, 389 } }};
static sprite_pattern z33spat18 = { 1, { { -16, -32, 0, 393 } }};
static sprite_pattern z6spat18 = { 1, { { -16, -32, 0, 388 } }};
static sprite_pattern z81spat18 = { 1, { { -16, -32, 0, 378 } }};
static sprite_pattern z82spat18 = { 1, { { -16, -32, 0, 387 } }};
static sprite_pattern z83spat18 = { 1, { { -16, -32, 0, 380 } }};
sprite_pattern* springpat[3] = {
  &spat00,
  &spat01,
  &spat02
};
sprite_pattern* z1springpat[3] = {
  &z1spat00,
  &z1spat01,
  &z1spat02
};
sprite_pattern* z11aspringpat[3] = {
  &z11aspat00,
  &z11aspat01,
  &z11aspat02
};
sprite_pattern* z3springpat[3] = {
  &z3spat00,
  &z3spat01,
  &z3spat02
};
sprite_pattern* z33springpat[3] = {
  &z33spat00,
  &z33spat01,
  &z33spat02
};
sprite_pattern* z6springpat[3] = {
  &z6spat00,
  &z6spat01,
  &z6spat02
};
sprite_pattern* z81springpat[3] = {
  &z81spat00,
  &z81spat01,
  &z81spat02
};
sprite_pattern* z82springpat[3] = {
  &z82spat00,
  &z82spat01,
  &z82spat02
};
sprite_pattern* z83springpat[3] = {
  &z83spat00,
  &z83spat01,
  &z83spat02
};
sprite_pattern** springpats[7][3][3] = {
  {
    { z1springpat, z11aspringpat, z1springpat },
    { z1springpat, z1springpat, z1springpat },
    { 0, 0, z1springpat }
  },
  {
    { z3springpat, z3springpat, z3springpat },
    { z3springpat, z3springpat, z3springpat },
    { 0, 0, z33springpat },
  },
  {
    { springpat, springpat, springpat },
    { springpat, springpat, springpat },
    { 0, 0, springpat }
  },
  {
    { springpat, springpat, springpat },
    { springpat, springpat, springpat },
    { 0, 0, springpat }
  },
  {
    { z6springpat, z6springpat, z6springpat },
    { z6springpat, z6springpat, z6springpat },
    { 0, 0, z6springpat }
  },
  {
    { springpat, springpat, springpat },
    { springpat, springpat, springpat },
    { 0, 0, springpat }
  },
  {
    { z81springpat, z81springpat, z81springpat },
    { z82springpat, z82springpat, z82springpat },
    { 0, 0, z83springpat }
  }
};
sprite_pattern* spring90pat[3] = {
  &spat03,
  &spat04,
  &spat05
};
sprite_pattern* z1spring90pat[3] = {
  &z1spat03,
  &z1spat04,
  &z1spat05
};
sprite_pattern* z11aspring90pat[3] = {
  &z11aspat03,
  &z11aspat04,
  &z11aspat05
};
sprite_pattern* z3spring90pat[3] = {
  &z3spat03,
  &z3spat04,
  &z3spat05
};
sprite_pattern* z33spring90pat[3] = {
  &z33spat03,
  &z33spat04,
  &z33spat05
};
sprite_pattern* z6spring90pat[3] = {
  &z6spat03,
  &z6spat04,
  &z6spat05
};
sprite_pattern* z81spring90pat[3] = {
  &z81spat03,
  &z81spat04,
  &z81spat05
};
sprite_pattern* z82spring90pat[3] = {
  &z82spat03,
  &z82spat04,
  &z82spat05
};
sprite_pattern* z83spring90pat[3] = {
  &z83spat03,
  &z83spat04,
  &z83spat05
};
sprite_pattern** spring90pats[7][3][3] = {
  {
    { z1spring90pat, z11aspring90pat, z1spring90pat },
    { z1spring90pat, z1spring90pat, z1spring90pat },
    { 0, 0, z1spring90pat }
  },
  {
    { z3spring90pat, z3spring90pat, z3spring90pat },
    { z3spring90pat, z3spring90pat, z3spring90pat },
    { 0, 0, z33spring90pat },
  },
  {
    { spring90pat, spring90pat, spring90pat },
    { spring90pat, spring90pat, spring90pat },
    { 0, 0, spring90pat }
  },
  {
    { spring90pat, spring90pat, spring90pat },
    { spring90pat, spring90pat, spring90pat },
    { 0, 0, spring90pat }
  },
  {
    { z6spring90pat, z6spring90pat, z6spring90pat },
    { z6spring90pat, z6spring90pat, z6spring90pat },
    { 0, 0, z6spring90pat }
  },
  {
    { spring90pat, spring90pat, spring90pat },
    { spring90pat, spring90pat, spring90pat },
    { 0, 0, spring90pat }
  },
  {
    { z81spring90pat, z81spring90pat, z81spring90pat },
    { z82spring90pat, z82spring90pat, z82spring90pat },
    { 0, 0, z83spring90pat }
  }
};
sprite_pattern* spring45pat[3] = {
  &spat06,
  &spat07,
  &spat08
};
sprite_pattern* z1spring45pat[3] = {
  &z1spat06,
  &z1spat07,
  &z1spat08
};
sprite_pattern* z11aspring45pat[3] = {
  &z11aspat06,
  &z11aspat07,
  &z11aspat08
};
sprite_pattern* z3spring45pat[3] = {
  &z3spat06,
  &z3spat07,
  &z3spat08
};
sprite_pattern* z33spring45pat[3] = {
  &z33spat06,
  &z33spat07,
  &z33spat08
};
sprite_pattern* z6spring45pat[3] = {
  &z6spat06,
  &z6spat07,
  &z6spat08
};
sprite_pattern* z81spring45pat[3] = {
  &z81spat06,
  &z81spat07,
  &z81spat08
};
sprite_pattern* z82spring45pat[3] = {
  &z82spat06,
  &z82spat07,
  &z82spat08
};
sprite_pattern* z83spring45pat[3] = {
  &z83spat06,
  &z83spat07,
  &z83spat08
};
sprite_pattern** spring45pats[7][3][4] = {
  {
    { z1spring45pat, z11aspring45pat, z1spring45pat, z1spring45pat },
    { z1spring45pat, z1spring45pat, z1spring45pat, z1spring45pat },
    { z1spring45pat, z1spring45pat, z1spring45pat, z1spring45pat }
  },
  {
    { z3spring45pat, z3spring45pat, z3spring45pat, z3spring45pat },
    { z3spring45pat, z3spring45pat, z3spring45pat, z3spring45pat },
    { z33spring45pat, z33spring45pat, z33spring45pat, z33spring45pat },
  },
  {
    { spring45pat, spring45pat, spring45pat, spring45pat },
    { spring45pat, spring45pat, spring45pat, spring45pat },
    { spring45pat, spring45pat, spring45pat, spring45pat }
  },
  {
    { spring45pat, spring45pat, spring45pat, spring45pat },
    { spring45pat, spring45pat, spring45pat, spring45pat },
    { spring45pat, spring45pat, spring45pat, spring45pat }
  },
  {
    { z6spring45pat, z6spring45pat, z6spring45pat, z6spring45pat },
    { z6spring45pat, z6spring45pat, z6spring45pat, z6spring45pat },
    { z6spring45pat, z6spring45pat, z6spring45pat, z6spring45pat }
  },
  {
    { spring45pat, spring45pat, spring45pat, spring45pat },
    { spring45pat, spring45pat, spring45pat, spring45pat },
    { spring45pat, spring45pat, spring45pat, spring45pat }
  },
  {
    { z81spring45pat, z81spring45pat, z81spring45pat, z81spring45pat },
    { z82spring45pat, z82spring45pat, z82spring45pat, z82spring45pat },
    { z83spring45pat, z83spring45pat, z83spring45pat, z83spring45pat }
  }
};
sprite_pattern* springpat2[3] = {
  &spat10,
  &spat11,
  &spat12
};
sprite_pattern* z1springpat2[3] = {
  &z1spat10,
  &z1spat11,
  &z1spat12
};
sprite_pattern* z11aspringpat2[3] = {
  &z11aspat10,
  &z11aspat11,
  &z11aspat12
};
sprite_pattern* z3springpat2[3] = {
  &z3spat10,
  &z3spat11,
  &z3spat12
};
sprite_pattern* z33springpat2[3] = {
  &z33spat10,
  &z33spat11,
  &z33spat12
};
sprite_pattern* z6springpat2[3] = {
  &z6spat10,
  &z6spat11,
  &z6spat12
};
sprite_pattern* z81springpat2[3] = {
  &z81spat10,
  &z81spat11,
  &z81spat12
};
sprite_pattern* z82springpat2[3] = {
  &z82spat10,
  &z82spat11,
  &z82spat12
};
sprite_pattern* z83springpat2[3] = {
  &z83spat10,
  &z83spat11,
  &z83spat12
};
sprite_pattern** springpat2s[7][3][4] = {
  {
    { z1springpat2, z11aspringpat2, z1springpat2, z1springpat2 },
    { z1springpat2, z1springpat2, z1springpat2, z1springpat2 },
    { z1springpat2, z1springpat2, z1springpat2, z1springpat2 }
  },
  {
    { z3springpat2, z3springpat2, z3springpat2, z3springpat2 },
    { z3springpat2, z3springpat2, z3springpat2, z3springpat2 },
    { z33springpat2, z33springpat2, z33springpat2, z33springpat2 },
  },
  {
    { springpat2, springpat2, springpat2, springpat2 },
    { springpat2, springpat2, springpat2, springpat2 },
    { springpat2, springpat2, springpat2, springpat2 }
  },
  {
    { springpat2, springpat2, springpat2, springpat2 },
    { springpat2, springpat2, springpat2, springpat2 },
    { springpat2, springpat2, springpat2, springpat2 }
  },
  {
    { z6springpat2, z6springpat2, z6springpat2, z6springpat2 },
    { z6springpat2, z6springpat2, z6springpat2, z6springpat2 },
    { z6springpat2, z6springpat2, z6springpat2, z6springpat2 }
  },
  {
    { springpat2, springpat2, springpat2, springpat2 },
    { springpat2, springpat2, springpat2, springpat2 },
    { springpat2, springpat2, springpat2, springpat2 }
  },
  {
    { z81springpat2, z81springpat2, z81springpat2, z81springpat2 },
    { z82springpat2, z82springpat2, z82springpat2, z82springpat2 },
    { z83springpat2, z83springpat2, z83springpat2, z83springpat2 }
  }
};
sprite_pattern* spring90pat2[3] = {
  &spat13,
  &spat14,
  &spat15
};
sprite_pattern* z1spring90pat2[3] = {
  &z1spat13,
  &z1spat14,
  &z1spat15
};
sprite_pattern* z11aspring90pat2[3] = {
  &z11aspat13,
  &z11aspat14,
  &z11aspat15
};
sprite_pattern* z3spring90pat2[3] = {
  &z3spat13,
  &z3spat14,
  &z3spat15
};
sprite_pattern* z33spring90pat2[3] = {
  &z33spat13,
  &z33spat14,
  &z33spat15
};
sprite_pattern* z6spring90pat2[3] = {
  &z6spat13,
  &z6spat14,
  &z6spat15
};
sprite_pattern* z81spring90pat2[3] = {
  &z81spat13,
  &z81spat14,
  &z81spat15
};
sprite_pattern* z82spring90pat2[3] = {
  &z82spat13,
  &z82spat14,
  &z82spat15
};
sprite_pattern* z83spring90pat2[3] = {
  &z83spat13,
  &z83spat14,
  &z83spat15
};
sprite_pattern** spring90pat2s[7][3][4] = {
  {
    { z1spring90pat2, z11aspring90pat2, z1spring90pat2, z1spring90pat2 },
    { z1spring90pat2, z1spring90pat2, z1spring90pat2, z1spring90pat2 },
    { z1spring90pat2, z1spring90pat2, z1spring90pat2, z1spring90pat2 }
  },
  {
    { z3spring90pat2, z3spring90pat2, z3spring90pat2, z3spring90pat2 },
    { z3spring90pat2, z3spring90pat2, z3spring90pat2, z3spring90pat2 },
    { z33spring90pat2, z33spring90pat2, z33spring90pat2, z33spring90pat2 },
  },
  {
    { spring90pat2, spring90pat2, spring90pat2, spring90pat2 },
    { spring90pat2, spring90pat2, spring90pat2, spring90pat2 },
    { spring90pat2, spring90pat2, spring90pat2, spring90pat2 }
  },
  {
    { spring90pat2, spring90pat2, spring90pat2, spring90pat2 },
    { spring90pat2, spring90pat2, spring90pat2, spring90pat2 },
    { spring90pat2, spring90pat2, spring90pat2, spring90pat2 }
  },
  {
    { z6spring90pat2, z6spring90pat2, z6spring90pat2, z6spring90pat2 },
    { z6spring90pat2, z6spring90pat2, z6spring90pat2, z6spring90pat2 },
    { z6spring90pat2, z6spring90pat2, z6spring90pat2, z6spring90pat2 }
  },
  {
    { spring90pat2, spring90pat2, spring90pat2, spring90pat2 },
    { spring90pat2, spring90pat2, spring90pat2, spring90pat2 },
    { spring90pat2, spring90pat2, spring90pat2, spring90pat2 }
  },
  {
    { z81spring90pat2, z81spring90pat2, z81spring90pat2, z81spring90pat2 },
    { z82spring90pat2, z82spring90pat2, z82spring90pat2, z82spring90pat2 },
    { z83spring90pat2, z83spring90pat2, z83spring90pat2, z83spring90pat2 }
  }
};
sprite_pattern* spring45pat2[3] = {
  &spat16,
  &spat17,
  &spat18
};
sprite_pattern* z1spring45pat2[3] = {
  &z1spat16,
  &z1spat17,
  &z1spat18
};
sprite_pattern* z11aspring45pat2[3] = {
  &z11aspat16,
  &z11aspat17,
  &z11aspat18
};
sprite_pattern* z3spring45pat2[3] = {
  &z3spat16,
  &z3spat17,
  &z3spat18
};
sprite_pattern* z33spring45pat2[3] = {
  &z33spat16,
  &z33spat17,
  &z33spat18
};
sprite_pattern* z6spring45pat2[3] = {
  &z6spat16,
  &z6spat17,
  &z6spat18
};
sprite_pattern* z81spring45pat2[3] = {
  &z81spat16,
  &z81spat17,
  &z81spat18
};
sprite_pattern* z82spring45pat2[3] = {
  &z82spat16,
  &z82spat17,
  &z82spat18
};
sprite_pattern* z83spring45pat2[3] = {
  &z83spat16,
  &z83spat17,
  &z83spat18
};
sprite_pattern** spring45pat2s[7][3][4] = {
  {
    { z1spring45pat2, z11aspring45pat2, z1spring45pat2, z1spring45pat2 },
    { z1spring45pat2, z1spring45pat2, z1spring45pat2, z1spring45pat2 },
    { z1spring45pat2, z1spring45pat2, z1spring45pat2, z1spring45pat2 }
  },
  {
    { z3spring45pat2, z3spring45pat2, z3spring45pat2, z3spring45pat2 },
    { z3spring45pat2, z3spring45pat2, z3spring45pat2, z3spring45pat2 },
    { z33spring45pat2, z33spring45pat2, z33spring45pat2, z33spring45pat2 },
  },
  {
    { spring45pat2, spring45pat2, spring45pat2, spring45pat2 },
    { spring45pat2, spring45pat2, spring45pat2, spring45pat2 },
    { spring45pat2, spring45pat2, spring45pat2, spring45pat2 }
  },
  {
    { spring45pat2, spring45pat2, spring45pat2, spring45pat2 },
    { spring45pat2, spring45pat2, spring45pat2, spring45pat2 },
    { spring45pat2, spring45pat2, spring45pat2, spring45pat2 }
  },
  {
    { z6spring45pat2, z6spring45pat2, z6spring45pat2, z6spring45pat2 },
    { z6spring45pat2, z6spring45pat2, z6spring45pat2, z6spring45pat2 },
    { z6spring45pat2, z6spring45pat2, z6spring45pat2, z6spring45pat2 }
  },
  {
    { spring45pat2, spring45pat2, spring45pat2, spring45pat2 },
    { spring45pat2, spring45pat2, spring45pat2, spring45pat2 },
    { spring45pat2, spring45pat2, spring45pat2, spring45pat2 }
  },
  {
    { z81spring45pat2, z81spring45pat2, z81spring45pat2, z81spring45pat2 },
    { z82spring45pat2, z82spring45pat2, z82spring45pat2, z82spring45pat2 },
    { z83spring45pat2, z83spring45pat2, z83spring45pat2, z83spring45pat2 }
  }
};
sprite_pattern* komapat[2] = {
  &kpat00,
  &kpat01
};
sprite_pattern* z1komapat[2] = {
  &z1kpat00,
  &z1kpat01
};
sprite_pattern* z11akomapat[2] = {
  &z11akpat00,
  &z11akpat01
};
sprite_pattern* z3komapat[2] = {
  &z3kpat00,
  &z3kpat01
};
sprite_pattern* z33komapat[2] = {
  &z33kpat00,
  &z33kpat01
};
sprite_pattern* z6komapat[2] = {
  &z6kpat00,
  &z6kpat01
};
sprite_pattern* z81komapat[2] = {
  &z81kpat00,
  &z81kpat01
};
sprite_pattern* z82komapat[2] = {
  &z82kpat00,
  &z82kpat01
};
sprite_pattern* z83komapat[2] = {
  &z83kpat00,
  &z83kpat01
};
sprite_pattern** komapats[7][3][4] = {
  {
    { z1komapat, z11akomapat, z1komapat, z1komapat },
    { z1komapat, z1komapat, z1komapat, z1komapat },
    { z1komapat, z1komapat, z1komapat, z1komapat }
  },
  {
    { z3komapat, z3komapat, z3komapat, z3komapat },
    { z3komapat, z3komapat, z3komapat, z3komapat },
    { z33komapat, z33komapat, z33komapat, z33komapat },
  },
  {
    { komapat, komapat, komapat, komapat },
    { komapat, komapat, komapat, komapat },
    { komapat, komapat, komapat, komapat }
  },
  {
    { komapat, komapat, komapat, komapat },
    { komapat, komapat, komapat, komapat },
    { komapat, komapat, komapat, komapat }
  },
  {
    { z6komapat, z6komapat, z6komapat, z6komapat },
    { z6komapat, z6komapat, z6komapat, z6komapat },
    { z6komapat, z6komapat, z6komapat, z6komapat }
  },
  {
    { komapat, komapat, komapat, komapat },
    { komapat, komapat, komapat, komapat },
    { komapat, komapat, komapat, komapat }
  },
  {
    { z81komapat, z81komapat, z81komapat, z81komapat },
    { z82komapat, z82komapat, z82komapat, z82komapat },
    { z83komapat, z83komapat, z83komapat, z83komapat }
  }
};
sprite_pattern* iwapat[1] = { &ipat00 };
sprite_pattern* z1iwapat[1] = { &z1ipat00 };
sprite_pattern* z11aiwapat[1] = { &z11aipat00 };
sprite_pattern* z3iwapat[1] = { &z3ipat00 };
sprite_pattern* z33iwapat[1] = { &z33ipat00 };
sprite_pattern* z6iwapat[1] = { &z6ipat00 };
sprite_pattern* z81iwapat[1] = { &z81ipat00 };
sprite_pattern* z82iwapat[1] = { &z82ipat00 };
sprite_pattern* z83iwapat[1] = { &z83ipat00 };
sprite_pattern** iwapats[7][3][4] = {
  {
    { z1iwapat, z11aiwapat, z1iwapat, z1iwapat },
    { z1iwapat, z1iwapat, z1iwapat, z1iwapat },
    { z1iwapat, z1iwapat, z1iwapat, z1iwapat }
  },
  {
    { z3iwapat, z3iwapat, z3iwapat, z3iwapat },
    { z3iwapat, z3iwapat, z3iwapat, z3iwapat },
    { z33iwapat, z33iwapat, z33iwapat, z33iwapat },
  },
  {
    { iwapat, iwapat, iwapat, iwapat },
    { iwapat, iwapat, iwapat, iwapat },
    { iwapat, iwapat, iwapat, iwapat }
  },
  {
    { iwapat, iwapat, iwapat, iwapat },
    { iwapat, iwapat, iwapat, iwapat },
    { iwapat, iwapat, iwapat, iwapat }
  },
  {
    { z6iwapat, z6iwapat, z6iwapat, z6iwapat },
    { z6iwapat, z6iwapat, z6iwapat, z6iwapat },
    { z6iwapat, z6iwapat, z6iwapat, z6iwapat }
  },
  {
    { iwapat, iwapat, iwapat, iwapat },
    { iwapat, iwapat, iwapat, iwapat },
    { iwapat, iwapat, iwapat, iwapat }
  },
  {
    { z81iwapat, z81iwapat, z81iwapat, z81iwapat },
    { z82iwapat, z82iwapat, z82iwapat, z82iwapat },
    { z83iwapat, z83iwapat, z83iwapat, z83iwapat }
  }
};
char springchg0[12] = {
   0,  0,  1,  1,
   2,  2,  2,  2,
   2,  2,  1, -4
};
char* springchg[1] = { springchg0 };
char komachg0[4] = { 8, 0, 1, -1 };
char* komachg[1] = { komachg0 };
void(*sjump_move_tbl[13])(sprite_status*) = {
  &sjumpinit,
  &sjumpmove,
  &sjumpmove2,
  &sjumpmove3,
  &sdushmove,
  &sdushmove2,
  &sdushmove3,
  &sjump2move,
  &sjump2move2,
  &sjump2move3,
  &sjump3move,
  &sjump3move2,
  &sjump3move3
};


void iwa(sprite_status* actionwk) {
  switch (actionwk->r_no0) {

    case 0:
      iwa_init(actionwk);
    case 2:
      iwa_move(actionwk);
      break;
  }
  actionsub(actionwk);
  frameout_s(actionwk);
}

void iwa_init(sprite_status* actionwk) {
  unsigned char d0;

  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri |= 4;
  actionwk->patbase = iwapats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  actionwk->sprhsize = 16;
  actionwk->sprvsize = 16;
  actionwk->patno = 0;
  d0 = 11;
  pa_set(0, 0);
}

void iwa_move(sprite_status* actionwk) {
  sprite_status* a1;

  if (!(actionwk->actflg & 128)) return;

  a1 = &actwk[0];
  ride_on_chk(actionwk, a1);
}

void koma(sprite_status* actionwk) {
  unsigned short d0, d1;

  switch (actionwk->r_no0) {

    case 0:
      koma_init(actionwk);
    case 2:
      koma_move(actionwk);
      break;
    case 4:
      koma_move2(actionwk); break;
      break;
  }
  d0 = ((unsigned short*)actionwk)[29];
  d0 &= -128;
  d1 = (unsigned short)(scra_h_posit.w.h - 128) & 65408;
  d0 -= d1;
  if (d0 > 640) frameout(actionwk);
}

void koma_init(sprite_status* actionwk) {
  sprite_status* a1;


  actionwk->r_no0 += 2;
  actionwk->actflg |= 4;
  actionwk->sprpri = 4;
  actionwk->patbase = komapats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  actionwk->sproffset = 848;
  actionwk->sprhsize = 8;
  actionwk->sprvsize = 7;
  ((short*)actionwk)[29] = actionwk->xposi.w.h;
  actionwk->xspeed.w = 384;

  pa_set(0, 0);
  patchg(actionwk, (unsigned char**)&komachg);

  if (actwkchk(&a1) != 0) {

    frameout(actionwk);
    return;
  }
  a1->actno = 10;
  a1->xposi.w.h = actionwk->xposi.w.h;
  a1->yposi.w.h = actionwk->yposi.w.h;
  a1->yposi.w.h -= 16;
  ((char*)a1)[61] = -16;
  ((unsigned short*)a1)[28] = actionwk - actwk;
  a1->userflag.w = actwk[((unsigned short*)a1)[28]].userflag.w;
}

void koma_move(sprite_status* actionwk) {
  short d1;

  d1 = emycol_d(actionwk);
  if (d1 >= 0) {

    ++actionwk->yposi.w.h;
    return;
  }
  actionwk->yposi.w.h += d1;
  ((unsigned short*)actionwk)[27] = actionwk->yposi.w.h;
  actionwk->r_no0 += 2;

}

void koma_move2(sprite_status* actionwk) {
  short d0, d1;

  if (!time_stop) {
    d1 = emycol_d(actionwk);
    actionwk->yposi.w.h += d1;
    d0 = ((unsigned short*)actionwk)[27];
    d0 -= actionwk->yposi.w.h;
    if (d0 >= 12) actionwk->xspeed.w = -actionwk->xspeed.w;
    speedset2(actionwk);
    patchg(actionwk, (unsigned char**)&komachg);
  }
  actionsub(actionwk);
}

void spring_d(sprite_status* actionwk) {
  switch (actionwk->r_no0) {

    case 0:
      spr_d_init(actionwk);
    case 2:
      spr_d_move(actionwk);
      break;
  }
}

void spr_d_init(sprite_status* actionwk) {
  if (actionwk->userflag.b.h & 2)
    actionwk->patbase = springpats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  else
    actionwk->patbase = springpat2s[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];

  actionwk->sproffset = 34080;
  actionwk->actflg |= 4;
  actionwk->sprhsize = 16;
  actionwk->sprvsize = 8;
  actionwk->sprpri = 4;
  actionwk->r_no0 += 2;
  spr_d_move(actionwk);
}

void spr_d_move(sprite_status* actionwk) {
  actionwk->xposi.l = actwk[0].xposi.l;
  actionwk->yposi.l = actwk[0].yposi.l;
  actionsub(actionwk);
}

















void spring(sprite_status* actionwk) {
  unsigned short d1;
  sprite_status* a1;
  unsigned short d0;






  if (actionwk->r_no1 == 5) {

    spring_d(actionwk);
  }
  if (actionwk->r_no0 == 0) goto label1;
  if (actionwk->actflg & 128) {
label1:
    sjump_move_tbl[actionwk->r_no0 / 2](actionwk);
  }
  actionsub(actionwk);

  d1 = ((unsigned short*)actionwk)[28];
  if (d1 != 0) {
    a1 = &actwk[d1];
    actionwk->xposi.w.h = a1->xposi.w.h;
    actionwk->yposi.w.h = a1->yposi.w.h;
    actionwk->xposi.w.h += ((char*)actionwk)[60];
    actionwk->yposi.w.h += ((char*)actionwk)[61];
  }

  d0 = ((unsigned short*)actionwk)[29];
  d0 &= -128;
  d1 = (unsigned short)(scra_h_posit.w.h - 128) & 65408;
  d0 -= d1;
  if (d0 > 640) frameout(actionwk);
}

void sjumpinit(sprite_status* actionwk) {
  short sjumptbl[2] = { -4096, -2560 };
  unsigned char d0;


  actionwk->r_no0 += 2;
  if (actionwk->userflag.b.h & 2)
    actionwk->patbase = springpats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  else
    actionwk->patbase = springpat2s[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];

  actionwk->sproffset = 1312;
  actionwk->actflg |= 4;
  actionwk->sprhsize = 16;
  actionwk->sprvsize = 8;
  ((short*)actionwk)[29] = actionwk->xposi.w.h;
  actionwk->sprpri = 4;

  d0 = actionwk->userflag.b.h;
  if (d0 & 4) {
    actionwk->r_no0 = 8;
    actionwk->sprhsize = 8;
    actionwk->sprvsize = 16;
    if (actionwk->userflag.b.h & 2)
      actionwk->patbase = spring90pats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
    else
      actionwk->patbase = spring90pat2s[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  }
  else
  if (d0 & 8) {
    actionwk->r_no0 = 20;
    actionwk->sprhsize = 24;
    actionwk->sprvsize = 12;
    if (actionwk->userflag.b.h & 2)
      actionwk->patbase = spring45pats[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
    else
      actionwk->patbase = spring45pat2s[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
    pa_set(0, 0);
  }
  else
  if (actionwk->actflg & 2) {
    actionwk->r_no0 = 14;
    actionwk->cddat |= 1;
  }
  if (d0 & 2)
    actionwk->sproffset |= 8192;

  ((short*)actionwk)[26] = sjumptbl[(d0 & 2) / 2];

}

int ride_on_chk_s(sprite_status* actionwk, sprite_status* a1) {
  return ride_on_chk(actionwk, a1);
}

void sjumpmove(sprite_status* actionwk) {
  sprite_status* a1;

  if (!(actionwk->actflg & 128)) return;

  a1 = &actwk[0];
  if (ride_on_chk_s(actionwk, a1) == 0) return;

  actionwk->r_no0 = 4;
  a1->yposi.w.h += 8;
  a1->yspeed.w = ((short*)actionwk)[26];
  a1->cddat |= 2;
  a1->cddat &= -9;
  a1->mstno.b.h = 16;
  actionwk->cddat &= -9;
  soundset(152);
}

void sjumpmove2(sprite_status* actionwk) {
  patchg(actionwk, (unsigned char**)&springchg);
}

void sjumpmove3(sprite_status* actionwk) {
  actionwk->cddat &= 247;
  actionwk->mstno.b.l = 1;
  actionwk->r_no0 -= 4;
  actionwk->patno = 0;
}

int ride_on_chk_s1(sprite_status* actionwk, sprite_status* a1) {
  return ride_on_chk(actionwk, a1);
}


void sdushmove(sprite_status* actionwk) {
  sprite_status* a1;

  if (!(actionwk->actflg & 128)) return;

  a1 = &actwk[0];
  ride_on_chk_s1(actionwk, a1);
  if (!(actionwk->cddat & 32)) return;

  actionwk->r_no0 = 10;
  a1->xspeed.w = ((short*)actionwk)[26];
  a1->xposi.w.h += 8;
  a1->cddat |= 1;
  if (!(actionwk->cddat & 1)) {
    a1->xposi.w.h -= 16;
    a1->xspeed.w = -a1->xspeed.w;
    a1->cddat &= 254;
  }
  ((short*)a1)[33] = 15;
  a1->mspeed.w = a1->xspeed.w;
  if (!(a1->cddat & 4))
    a1->mstno.b.h = 0;

  a1->direc.b.h = 0;
  actionwk->cddat &= 223;
  a1->cddat &= 223;
  soundset(152);
}

void sdushmove2(sprite_status* actionwk) {
  patchg(actionwk, (unsigned char**)&springchg);
}

void sdushmove3(sprite_status* actionwk) {
  actionwk->mstno.b.l = 1;
  actionwk->r_no0 -= 4;
  actionwk->patno = 0;
}

int ride_on_chk_s2(sprite_status* actionwk, sprite_status* a1) {
  return hitchk_u(actionwk, a1);
}

void sjump2move(sprite_status* actionwk) {
  sprite_status* a1;

  if (!(actionwk->actflg & 128)) return;

  a1 = &actwk[0];
  if (ride_on_chk_s2(actionwk, a1) == 0) return;

  actionwk->r_no0 = 16;
  a1->yposi.w.h -= 8;
  a1->yspeed.w = ((short*)actionwk)[26];
  a1->yspeed.w = -a1->yspeed.w;
  a1->cddat |= 2;
  a1->cddat &= 247;
  actionwk->cddat &= 247;
  soundset(152);
}

void sjump2move2(sprite_status* actionwk) {
  patchg(actionwk, (unsigned char**)&springchg);
}

void sjump2move3(sprite_status* actionwk) {
  actionwk->mstno.b.l = 1;
  actionwk->r_no0 -= 4;
  actionwk->patno = 0;
}

void sjump3move(sprite_status* actionwk) {
  sprite_status* a1;
  unsigned short sin, cos;
  int sinl, cosl;
  unsigned char d0;
  short d2;

  if (!(actionwk->actflg & 128)) return;

  a1 = &actwk[0];
  if (ride_on_chk_s(actionwk, a1) == 0)
    if (!(actionwk->cddat & 32)) return;

  actionwk->r_no0 = 22;
  d0 = 224;
  sinset(d0, (short*)&sin, (short*)&cos);
  d2 = ((short*)actionwk)[26];
  d2 = -d2;
  sinl = sin * d2;
  cosl = cos * d2;
  sinl >>= 8;
  cosl >>= 8;
  a1->yspeed.w = sinl;
  a1->xspeed.w = cosl;
  a1->yposi.w.h += 8;
  if (actionwk->actflg & 2) {
    a1->yposi.w.h -= 16;
    a1->yspeed.w = -a1->yspeed.w;
  }
  a1->cddat &= 254;
  a1->xposi.w.h -= 8;
  if (actionwk->cddat & 1) {
    a1->xposi.w.h += 16;
    a1->cddat |= 1;
    a1->xspeed.w = -a1->xspeed.w;
  }
  a1->cddat |= 2;
  a1->cddat &= 247;
  a1->cddat &= 223;
  actionwk->cddat &= 247;
  actionwk->cddat &= 223;
  soundset(152);
  sjump3move2(actionwk);
}

void sjump3move2(sprite_status* actionwk) {
  patchg(actionwk, (unsigned char**)&springchg);
}

void sjump3move3(sprite_status* actionwk) {
  actionwk->mstno.b.l = 1;
  actionwk->r_no0 -= 4;
  actionwk->patno = 0;
}
