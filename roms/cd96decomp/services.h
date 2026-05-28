#ifndef SERVICES_H
#define SERVICES_H

#include <stdio.h>

void CDPause(int unpause);
void CDPlay(short ReqNo);
void ChangeTileBmp(int tile_id, int bmp_id);
void EAsprset(short x, short y, unsigned short index, unsigned short linkdata, unsigned short reverse);
int ReadIndx(FILE* p_existing_file);
unsigned int ReadScore(int index, char* p_data, FILE* p_existing_file);
void SetGrid(int base, int x, int y, int block, int frip);
void SetSpecialGrid(int base, int x, int y, int block, int frip);
void SetStampGrid(int base, int x, int y, int block, int frip);
void SetSmorph(void* p_data);
void WaveAllStop(void);
void WaveRequest(short ReqNo);

#endif
