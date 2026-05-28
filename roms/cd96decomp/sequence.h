#ifndef SEQUENCE_H
#define SEQUENCE_H

void init_sequence(void);
unsigned short get_sequencenum(void);
void set_sequencenum(unsigned short num);
int get_timercount(void);
void update_sequence_timer(void);
void key_wait(int time);
void wait_key_off(int time);
void wait(int time);
int wait2(void);

#endif
