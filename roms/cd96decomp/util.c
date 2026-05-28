#include "util.h"
#include <stdio.h>
#include "constants.h"


void read_ulong_littleendian(unsigned char** pp_bytes, unsigned long* p_value) {
  unsigned char* p_bytes = *pp_bytes;

  *p_value = *p_bytes++;
  *p_value += *p_bytes++ << 8;
  *p_value += *p_bytes++ << 16;
  *p_value += *p_bytes++ << 24;

  *pp_bytes = p_bytes;
}


void read_ulong_littleendian_file(FILE* fp, unsigned long* p_value) {
  unsigned char bytes[FILE_ULONG_SIZE];
  unsigned char* p_bytes = bytes;

  fread(bytes, 1, sizeof(bytes), fp);
  read_ulong_littleendian(&p_bytes, p_value);
}


void read_ulong_bigendian(unsigned char** pp_bytes, unsigned long* p_value) {
  unsigned char* p_bytes = *pp_bytes;

  *p_value = *p_bytes++ << 24;
  *p_value += *p_bytes++ << 16;
  *p_value += *p_bytes++ << 8;
  *p_value += *p_bytes++;

  *pp_bytes = p_bytes;
}


void read_ulong_bigendian_file(FILE* fp, unsigned long* p_value) {
  unsigned char bytes[FILE_ULONG_SIZE];
  unsigned char* p_bytes = bytes;

  fread(bytes, 1, sizeof(bytes), fp);
  read_ulong_bigendian(&p_bytes, p_value);
}


void read_ushort_littleendian(unsigned char** pp_bytes, unsigned short* p_value) {
  unsigned char* p_bytes = *pp_bytes;

  *p_value = *p_bytes++;
  *p_value += *p_bytes++ << 8;

  *pp_bytes = p_bytes;
}


void read_ushort_littleendian_file(FILE* fp, unsigned short* p_value) {
  unsigned char bytes[FILE_USHORT_SIZE];
  unsigned char* p_bytes = bytes;

  fread(bytes, 1, sizeof(bytes), fp);
  read_ushort_littleendian(&p_bytes, p_value);
}


void read_ushort_bigendian(unsigned char** pp_bytes, unsigned short* p_value) {
  unsigned char* p_bytes = *pp_bytes;

  *p_value = *p_bytes++ << 8;
  *p_value += *p_bytes++;

  *pp_bytes = p_bytes;
}


void read_ushort_bigendian_file(FILE* fp, unsigned short* p_value) {
  unsigned char bytes[FILE_USHORT_SIZE];
  unsigned char* p_bytes = bytes;

  fread(bytes, 1, sizeof(bytes), fp);
  read_ushort_bigendian(&p_bytes, p_value);
}
