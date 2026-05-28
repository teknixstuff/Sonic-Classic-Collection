#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

void read_ulong_littleendian(unsigned char** pp_bytes, unsigned long* value);
void read_ulong_littleendian_file(FILE* fp, unsigned long* p_value);
void read_ulong_bigendian(unsigned char** pp_bytes, unsigned long* p_value);
void read_ulong_bigendian_file(FILE* fp, unsigned long* p_value);
void read_ushort_littleendian(unsigned char** pp_bytes, unsigned short* value);
void read_ushort_littleendian_file(FILE* fp, unsigned short* p_value);
void read_ushort_bigendian(unsigned char** pp_bytes, unsigned short* p_value);
void read_ushort_bigendian_file(FILE* fp, unsigned short* p_value);

#endif
