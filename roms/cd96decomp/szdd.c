#include "szdd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "util.h"
#include "boxreader.h"

unsigned char* szdd_decompress(char* p_filename) {
  unsigned char* p_decompressed = 0;
  unsigned long decompressed_cnt = 0;
  unsigned int decompressed_pos = 0;
  unsigned char dictionary[SZDD_DICTIONARY_SIZE];
  unsigned int literal_pos = SZDD_DICTIONARY_SIZE - 16;
  unsigned char* file_data = NULL;
  int file_size = box_read((void**)&file_data, p_filename);
  if (file_size < 1) {
	fprintf(stderr, "Could not read %s, error %i.\n", p_filename, file_size);
    abort();
  }
  unsigned char* file_data_start = file_data;
  
  if (*file_data++ != 'S') return 0; /* magic */
  if (*file_data++ != 'Z') return 0;
  if (*file_data++ != 'D') return 0;
  if (*file_data++ != 'D') return 0;
  if (*file_data++ != 0x88) return 0;
  if (*file_data++ != 0xF0) return 0;
  if (*file_data++ != 0x27) return 0;
  if (*file_data++ != 0x33) return 0;
  if (*file_data++ != 'A') return 0; /* mode */
  file_data++; /* last character of filename */

  read_ulong_littleendian(&file_data, &decompressed_cnt);
  p_decompressed = malloc(decompressed_cnt);
  if (p_decompressed == 0) {
    fprintf(stderr, "Could not allocate memory for SZDD decompression.\n");
    abort();
  }
  memset(dictionary, ' ', SZDD_DICTIONARY_SIZE);

  do {
    unsigned int control = *file_data++;
    unsigned int bit;
    if (file_data >= file_data_start + file_size) break;

    for (bit = 1; bit & 0xFF; bit <<= 1) {
	  printf("%i\n", file_size - (file_data - file_data_start));
      if (control & bit) {
        p_decompressed[decompressed_pos] = dictionary[literal_pos] = *file_data++;
        if (file_data >= file_data_start + file_size) break;
        ++literal_pos;
        literal_pos %= SZDD_DICTIONARY_SIZE;
        ++decompressed_pos;
      }
      else {
        unsigned int match_pos = *file_data++;
        unsigned int match_len = *file_data++;
        if (file_data >= file_data_start + file_size) break;
        match_pos |= (match_len & 0xF0) << 4;
        match_len = (match_len & 0x0F) + 3;

        while (match_len-- != 0) {
          p_decompressed[decompressed_pos] = dictionary[literal_pos] = dictionary[match_pos];
          ++literal_pos;
          literal_pos %= SZDD_DICTIONARY_SIZE;
          ++match_pos;
          match_pos %= SZDD_DICTIONARY_SIZE;
          ++decompressed_pos;
        }
      }
    }
  }
  while (1);
		
  free(file_data_start);

  return p_decompressed;
}
