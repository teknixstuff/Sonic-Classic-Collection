#include "score.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "GAME/TITLE/COMMON/SCORE_DATA_TYPES.h"
static int verify_score_data_checksum(char* p_score_data);
static void update_score_data_checksum(char* p_score_data);
static void init_score_data(score_data* p_score_data, int index);
static int write_default_score_data_file(void);

score_data g_current_score_data;
unsigned int g_selected_score_data_index;


static int verify_score_data_checksum(char* p_score_data) {
  int checksum = 0;
  unsigned int i;

  for (i = 0; i < sizeof(score_data) - 4; ++i) {
    checksum += (char)*p_score_data++;
  }

  return *(int*)p_score_data == checksum;
}


static void update_score_data_checksum(char* p_score_data) {
  int checksum = 0;
  unsigned int i;

  for (i = 0; i < sizeof(score_data) - 4; ++i) {
    checksum += (char)*p_score_data++;
  }

  *(int*)p_score_data = checksum;
}


int read_score_data(int index, score_data *p_old_score_data, FILE* p_existing_file) {
  score_data* p_score_data;
  int i;
  FILE* p_file;

  if (p_old_score_data == 0) {
    p_score_data = &g_current_score_data;
  }
  else {
    p_score_data = p_old_score_data;
  }
  if (p_existing_file == 0) {
    p_file = fopen("s_score.dat", "rb");
    if (p_file == 0) {
      goto error;
    }
  }
  else {
    p_file = p_existing_file;
  }
  fseek(p_file, index * sizeof(score_data) + 4, SEEK_SET);
  if (fread(p_score_data, 1, sizeof(score_data), p_file) != sizeof(score_data)) {
    goto error;
  }
  if (verify_score_data_checksum((char*)p_score_data) == 0) {
    goto error;
  }
  if (p_existing_file == 0) {
    fclose(p_file);
  }
  if (p_score_data->saved == 0) {
    init_score_data(p_score_data, index);
  }
  return 1;

error:
  if (p_existing_file == 0 && p_file != 0) {
    fclose(p_file);
  }
  init_score_data(&g_current_score_data, index);
  return 0;
}


void set_score_date(score_data *p_score_data) {
  time_t current_time;
  struct tm* p_calendar_time;

  if (p_score_data == 0) {
    p_score_data = &g_current_score_data;
  }
  time(&current_time);
  p_calendar_time = localtime(&current_time);
  p_score_data->year = p_calendar_time->tm_year + 1900;
  p_score_data->month = p_calendar_time->tm_mon + 1;
  p_score_data->date = p_calendar_time->tm_mday;
  p_score_data->hour = p_calendar_time->tm_hour;
  p_score_data->min = p_calendar_time->tm_min;
  p_score_data->sec = p_calendar_time->tm_sec;
}


int write_score_data(int index, score_data* p_new_score_data, FILE* p_existing_file) {
  score_data* p_score_data;
  int i;
  FILE* p_file;

  if (p_new_score_data == 0) {
    p_score_data = &g_current_score_data;
  }
  else {
    p_score_data = p_new_score_data;
  }
  if (p_existing_file == 0) {
    p_file = fopen("s_score.dat", "r+b");
    if (p_file == 0) {
      goto error;
    }
  }
  else {
    p_file = p_existing_file;
  }
  update_score_data_checksum((char*)p_score_data);
  fseek(p_file, index * sizeof(score_data) + 4, SEEK_SET);
  if (fwrite(p_score_data, 1, sizeof(score_data), p_file) != sizeof(score_data)) {
    goto error;
  }
  if (p_existing_file == 0) {
    fclose(p_file);
  }
  return 1;

error:
  if (p_existing_file == 0 && p_file != 0) {
    fclose(p_file);
  }
  return 0;
}


FILE* open_score_data(int mode) {
  return fopen("s_score.dat", mode == 0 ? "rb" : "wb");
}


void close_score_data(FILE* p_file) {
  fclose(p_file);
}


int read_score_index(FILE* p_existing_file) {
  int index;
  FILE* p_file;

  if (p_existing_file == 0) {
    p_file = fopen("s_score.dat", "rb");
    if (p_file == 0) {
      goto error;
    }
  }
  else {
    p_file = p_existing_file;
    rewind(p_file);
  }
  if (fread(&index, 1, 4, p_file) != 4) {
    goto error;
  }
  if (p_existing_file == 0) {
    fclose(p_file);
  }
  g_selected_score_data_index = index;
  return index;

error:
  if (p_existing_file == 0 && p_file != 0) {
    fclose(p_file);
  }
  return -1;
}


int write_score_index(int index, FILE* p_existing_file) {
  FILE* p_file;

  g_selected_score_data_index = index;
  if (p_existing_file == 0) {
    p_file = fopen("s_score.dat", "r+b");
    if (p_file == 0) {
      goto error;
    }
  }
  else {
    p_file = p_existing_file;
    rewind(p_file);
  }
  if (fwrite(&g_selected_score_data_index, 1, 4, p_file) != 4) {
    goto error;
  }
  if (p_existing_file == 0) {
    fclose(p_file);
  }
  return 1;

error:
  if (p_existing_file == 0 && p_file != 0) {
    fclose(p_file);
  }
  return 0;
}


static void init_score_data(score_data* p_score_data, int index) {
  int round, zone, time;

  p_score_data->saved = 0;
  strncpy(p_score_data->player, "PLAYER_1    ", 12);
  p_score_data->player[7] = index + '1';
  p_score_data->roundNo = 0;
  p_score_data->year = 0;
  p_score_data->month = 0;
  p_score_data->date = 0;

  for (round = 0; round < 7; ++round) {
    for (zone = 0; zone < 3; ++zone) {
      for (time = 0; time < 3; ++time) {
        p_score_data->timeattack[round][zone][time].time = 18000;
        strcpy(p_score_data->timeattack[round][zone][time].name, "AAA");
      }
    }
  }

  for (round = 0; round < 7; ++round) {
    for (time = 0; time < 3; ++time) {
      p_score_data->special[round][time].time = 18000;
      strcpy(p_score_data->special[round][time].name, "AAA");
    }
  }

  p_score_data->total = 7 * 3 * 18000;
  p_score_data->clrspflg_save = 0;
  p_score_data->clrgood = 0;
  p_score_data->stagenm = 0;
  p_score_data->reserved1 = 0;
  p_score_data->reserved2 = 0;
  p_score_data->checkSum = 0;
}


static int write_default_score_data_file(void) {
  FILE* p_file;
  int i;

  p_file = fopen("s_score.dat", "w+b");
  if (p_file == 0) {
    return 0;
  }
  write_score_index(-1, p_file);

  for (i = 0; i < 6; ++i) {
    init_score_data(&g_current_score_data, i);
    write_score_data(i, &g_current_score_data, p_file);
  }

  fclose(p_file);

  return 1;
}


int read_first_score_data(void) {
  int index = read_score_index(0);

  if (index != -1) {
    if (read_score_data(index, 0, 0) == 0) {
      index = -1;
    }
  }
  if (index == -1 || g_current_score_data.saved == 0) {
    init_score_data(&g_current_score_data, 0);
    return 0;
  }
  return 1;
}


int new_score_data(void) {
  int i;

  for (i = 0; i < 6; ++i) {
    if (read_score_data(i, 0, 0) == 0) {
      if (write_default_score_data_file() == 0) {
        init_score_data(&g_current_score_data, 0);
        set_score_date(&g_current_score_data);
        g_current_score_data.saved = 1;
        return 1;
      }
      i = 0;
    }
    if (g_current_score_data.saved == 0) {
      init_score_data(&g_current_score_data, i);
      set_score_date(&g_current_score_data);
      g_current_score_data.saved = 1;
      write_score_data(i, 0, 0);
      write_score_index(i, 0);
      break;
    }
  }

  if (i == 6) {
    return 0;
  }
  return 1;
}
