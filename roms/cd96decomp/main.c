#include <stdio.h>
#include "audio.h"
#include "constants.h"
#include "graphics/screen.h"
#include "input/input.h"
#include "opening.h"
#include "score.h"
#include "boxreader.h"

void cd96_main() {
  box_open();
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
  box_close();
}
