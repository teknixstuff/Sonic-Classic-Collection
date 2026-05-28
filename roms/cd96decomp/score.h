#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include "GAME/TITLE/COMMON/SCORE_DATA_TYPES.h"

int read_score_data(int index, score_data* p_old_score_data, FILE* p_existing_file);
void set_score_date(score_data* p_score_data);
int write_score_data(int index, score_data* p_new_score_data, FILE* p_existing_file);
FILE* open_score_data(int mode);
void close_score_data(FILE* p_file);
int read_score_index(FILE* p_existing_file);
int write_score_index(int index, FILE* p_existing_file);
int read_first_score_data(void);
int new_score_data(void);

#endif
