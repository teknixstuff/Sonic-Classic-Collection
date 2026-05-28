#ifndef BITMAPMANIPULATION_H
#define BITMAPMANIPULATION_H

void hflip_bitmap(unsigned char* p_output, unsigned char* p_input, int width, int height);
void vflip_bitmap(unsigned char* p_output, unsigned char* p_input, int width, int height);
void hvflip_bitmap(unsigned char* p_output, unsigned char* p_input, int width, int height);
void rot90r_bitmap(unsigned char* p_output, unsigned char* p_input, int width, int height);

#endif
