#include <stdio.h>
#include "audio.h"
#include "constants.h"
#include "graphics/screen.h"
#include "input/input.h"
#include "opening.h"
#include "options.h"
#include "score.h"

void cd96_main() {
  init_screen();
  init_audio();
  init_input();
  load_sounds();
  play_audio();
  read_first_score_data();

  opening();

  unload_sounds();
  term_input();
  term_audio();
  term_screen();
}
