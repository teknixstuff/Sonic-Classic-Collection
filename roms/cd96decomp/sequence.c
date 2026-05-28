#include "sequence.h"
#include "GAME/EQU.h"

static int timercount;
static unsigned short sequencenum;
static int waittime;
static unsigned short savesequencenum;
static unsigned int waitkeyoff;


void init_sequence(void) {
  sequencenum = 1;
  timercount = 0;
}


unsigned short get_sequencenum(void) {
  return sequencenum;
}


void set_sequencenum(unsigned short num) {
  sequencenum = num;
  timercount = -1;
}


int get_timercount(void) {
  return timercount;
}


void update_sequence_timer(void) {
  if (timercount == 0x7FFFFFFF) {
    timercount = 0x4F1A00;
  }
  else {
    ++timercount;
  }
}


void key_wait(int time) {
  savesequencenum = sequencenum;
  waittime = time;
  set_sequencenum(3);
}


void wait_key_off(int time) {
  savesequencenum = sequencenum;
  waitkeyoff = 1;
  waittime = time;
  set_sequencenum(3);
}


void wait(int time) {
  savesequencenum = sequencenum;
  waitkeyoff = 0;
  waittime = time;
  set_sequencenum(3);
}


int wait2(void) {
  int resume = 0;

  if (waitkeyoff == 0 && timercount > waittime) {
    set_sequencenum(savesequencenum);
    resume = 1;
  }
  if (waitkeyoff != 0 && swdata1.w == 0) {
    waitkeyoff = 0;
  }

  return resume;
}
