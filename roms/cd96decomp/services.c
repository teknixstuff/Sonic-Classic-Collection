#include "services.h"
#include <stdio.h>
#include "audio.h"
#include "graphics/sprites.h"
#include "graphics/tiles.h"
#include "score.h"
#include "GAME/TITLE/COMMON/SCORE_DATA_TYPES.h"


void CDPause(int unpause) {}


void CDPlay(short ReqNo) {
  play_bgm(ReqNo);
}


void ChangeTileBmp(int tile_id, int bmp_id) {
  change_tile_bitmap(tile_id, bmp_id);
}


void EAsprset(short x, short y, unsigned short index, unsigned short linkdata, unsigned short reverse) {
  set_sprite(x, y, index, linkdata, reverse);
}


int ReadIndx(FILE* p_existing_file) {
  return read_score_index(p_existing_file);
}


unsigned int ReadScore(int index, char* p_data, FILE* p_existing_file) {
  return read_score_data(index, (score_data*)p_data, p_existing_file);
}


void SetGrid(int base, int x, int y, int block, int frip) {
  set_plane_tile(base, x, y, block, frip);
}


void SetSpecialGrid(int base, int x, int y, int block, int frip) {
  set_special_plane_tile(x, y, block);
}


void SetStampGrid(int base, int x, int y, int block, int frip) {
  set_stamp_map_stamp(x, y, block);
}


void SetSmorph(void* p_data) {
  set_smorph_data(p_data);
}


void WaveAllStop(void) {
  stop_sounds();
}


void WaveRequest(short ReqNo) {
  play_sound(ReqNo);
}
