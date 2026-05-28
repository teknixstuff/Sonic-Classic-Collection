#include "../EQU.h"
#include "../SPM_EQU.h"
#include "COMMON.h"
#include "SPM_EQU.h"
#include "SPS_EQU.h"
#include "GAME.h"
#include <stdio.h>
#include <string.h>
#include "../../services.h"
#include "../COL.h"
#include "../LOADER2.h"
#include "../IO.h"
#include "ACT_S.h"
#include "BACT.h"
#include "COLI_S.h"
#include "ENS.h"
#include "ETC_M.h"
#include "ETC_S.h"
#include "KAITEN.h"

unsigned char seregiflg;
unsigned char scroll_stop;
static unsigned short hscrcnt = 256;
static unsigned int PauseIcon;
extern bmp_info SprBmp[700];
static int scoreup_setm;
static short specclchgcnt[4];











































































































void SetUseOk(short unknown1, short unknown2, short unknown3) {
}








static PALETTEENTRY colortbl[64] = {
  {  64,  96, 224, 1 }, {   0,   0,   0, 1 }, {   0,  32, 128, 1 }, {  32,  64, 192, 1 },
  {  32,  96, 224, 1 }, {  64, 160, 224, 1 }, { 224, 224, 224, 1 }, { 160, 160, 160, 1 },
  { 128, 128, 128, 1 }, {  64,  64,  64, 1 }, { 224, 160, 128, 1 }, { 160,  96,  64, 1 },
  { 224,   0,   0, 1 }, { 128,   0,   0, 1 }, {  64,   0,   0, 1 }, { 224, 224,   0, 1 },
  {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, { 128, 128, 128, 1 }, {  64,  64,  64, 1 },
  {   0,   0,   0, 1 }, { 224, 224,   0, 1 }, { 192,  32,   0, 1 }, { 224, 192, 128, 1 },
  { 192, 160,  96, 1 }, { 160, 224,   0, 1 }, {  96, 160,   0, 1 }, {  32,  96,   0, 1 },
  { 192, 224, 224, 1 }, { 128, 192, 224, 1 }, {  64, 160, 224, 1 }, {  64,  96, 224, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,  32, 1 }, {   0,   0,  64, 1 },
  {   0,   0,  96, 1 }, {   0,   0, 160, 1 }, {   0,   0, 224, 1 }, {   0,  64, 224, 1 },
  {   0,  96, 224, 1 }, {   0, 128, 224, 1 }, {  32, 160, 224, 1 }, {  64, 192, 224, 1 },
  { 128, 224, 224, 1 }, { 192, 224, 224, 1 }, { 224, 224, 224, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {  64,  32, 128, 1 }, {  96,  64, 192, 1 },
  { 128,  96, 224, 1 }, { 160, 128, 224, 1 }, { 224, 224, 224, 1 }, { 128, 192, 192, 1 },
  {  96, 160, 128, 1 }, {  32,  64,  96, 1 }, {   0,   0,   0, 1 }, { 224, 224, 224, 1 },
  { 224, 224,   0, 1 }, { 128, 128,   0, 1 }, {  64,  64,   0, 1 }, {   0,   0,   0, 1 },
};
static PALETTEENTRY dispcolor[64] = {
  { 224, 224, 224, 1 }, {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, { 128, 224,   0, 1 },
  {  64, 160,   0, 1 }, {  32,  96,   0, 1 }, { 224,   0,   0, 1 }, { 128,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {  64,   0,  32, 1 }, { 224, 224,  32, 1 },
  { 128, 128,   0, 1 }, {  64,  32,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  { 224, 224, 224, 1 }, {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, {  96,  96, 224, 1 },
  {  64,  64, 224, 1 }, {  32,  32, 192, 1 }, {  64, 224, 128, 1 }, {   0, 160, 160, 1 },
  {   0,  64,  96, 1 }, { 224,  32, 224, 1 }, { 160,   0, 224, 1 }, { 128,   0, 160, 1 },
  { 224,  96,   0, 1 }, { 224,  64,   0, 1 }, { 128,   0,   0, 1 }, {   0,   0,   0, 1 },
  { 224, 224, 224, 1 }, { 160, 224, 224, 1 }, {   0, 224, 160, 1 }, {   0, 128, 192, 1 },
  {   0,   0, 224, 1 }, { 192,  96, 224, 1 }, {  32,   0, 128, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  { 224, 224, 224, 1 }, {   0,   0,   0, 1 }, {  32,  32, 192, 1 }, {  96,  96, 224, 1 },
  { 128, 128, 224, 1 }, { 224, 224, 224, 1 }, { 128, 128, 128, 1 }, {  64,  64,  64, 1 },
  { 224, 160, 128, 1 }, { 160,  96,  64, 1 }, { 224,   0,   0, 1 }, { 128,   0,   0, 1 },
  { 192, 224, 224, 1 }, { 160, 224, 224, 1 }, { 128, 224, 224, 1 }, {  64, 224, 224, 1 },
};
static PALETTEENTRY coltbl0[32] = {
  {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 }, { 224, 128,   0, 1 },
  { 224,  32,   0, 1 }, { 160, 160, 128, 1 }, { 128, 128,  64, 1 }, {  64,  64,  32, 1 },
  {   0,   0,   0, 1 }, {   0,   0, 224, 1 }, {  96, 192, 224, 1 }, {  64, 128, 224, 1 },
  {  32,  96, 224, 1 }, {  64, 128,  32, 1 }, {  32,  96,   0, 1 }, {   0,  64,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,  32, 1 }, {   0,   0,  64, 1 }, {   0,   0,  96, 1 },
  {   0,   0, 128, 1 }, {   0,   0, 160, 1 }, {   0,   0, 192, 1 }, {   0,   0, 224, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, {   0,   0,   0, 1 },
};
static PALETTEENTRY coltbl1[32] = {
  {   0,   0, 224, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 }, { 224, 128,   0, 1 },
  { 224,  32,   0, 1 }, { 160, 160, 160, 1 }, {  96,  96,  96, 1 }, {  64,  64,  64, 1 },
  {   0,   0,   0, 1 }, {   0,   0,  96, 1 }, {   0,   0, 224, 1 }, {   0,  96, 224, 1 },
  {  96, 160, 224, 1 }, { 160, 192, 224, 1 }, {   0, 224,   0, 1 }, { 240, 240, 240, 1 },
  {  64,  96, 224, 1 }, { 224, 224, 224, 1 }, { 192, 224, 224, 1 }, { 160, 192, 224, 1 },
  { 128, 160, 224, 1 }, {  96, 128, 224, 1 }, {   0,  32, 224, 1 }, { 128, 128, 160, 1 },
  {   0,   0, 224, 1 }, { 160,  96,  64, 1 }, { 192, 128,  96, 1 }, { 224, 192, 128, 1 },
  { 224, 224, 160, 1 }, { 160,  64,   0, 1 }, {  96,  64,   0, 1 }, {   0,   0,   0, 1 },
};
static PALETTEENTRY coltbl2[32] = {
  {   0,   0, 224, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 }, { 224, 128,   0, 1 },
  { 224,  32,   0, 1 }, { 128, 160, 160, 1 }, {  64,  96,  96, 1 }, {  32,  64,  64, 1 },
  {   0,   0,   0, 1 }, {  32, 128,   0, 1 }, {   0,   0, 224, 1 }, {  32,  64, 224, 1 },
  {  64, 128, 224, 1 }, {  64, 192, 224, 1 }, {  64, 224,   0, 1 }, {   0,  64,   0, 1 },
  {   0,   0, 224, 1 }, { 224, 224, 224, 1 }, {   0,  32, 224, 1 }, {   0,  64, 224, 1 },
  {  32,  96, 224, 1 }, {  64, 128, 224, 1 }, {   0,   0, 160, 1 }, {   0,   0, 128, 1 },
  { 192, 224, 224, 1 }, {   0,   0,  32, 1 }, {  32, 224, 224, 1 }, {  96, 160, 128, 1 },
  {  64, 128,  96, 1 }, {   0,  64,  64, 1 }, { 224,  32, 128, 1 }, { 224, 224,  64, 1 },
};
static PALETTEENTRY coltbl3[32] = {
  {   0,  32, 224, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 }, { 224, 128,   0, 1 },
  { 224,  32,   0, 1 }, { 224, 192, 160, 1 }, { 160, 128,  96, 1 }, { 128,  96,  32, 1 },
  {   0,   0,   0, 1 }, {  32, 128,   0, 1 }, {   0,  32, 224, 1 }, {  32,  64, 224, 1 },
  {  64, 128, 224, 1 }, {  64, 192, 224, 1 }, {  64, 224,   0, 1 }, {   0,  64,   0, 1 },
  {   0,  32, 224, 1 }, {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, { 224, 224, 128, 1 },
  { 224, 160,  64, 1 }, { 192, 128,  64, 1 }, { 128,  96,  64, 1 }, {  64,  32,  64, 1 },
  {  96, 192, 224, 1 }, {  64, 192, 192, 1 }, {  96,  96,  96, 1 }, {   0,  32,   0, 1 },
  {  32,  64,   0, 1 }, {  64, 128,   0, 1 }, {  96, 160,  32, 1 }, { 160, 160, 160, 1 },
};
static PALETTEENTRY coltbl4[32] = {
  {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 }, { 224, 128,   0, 1 },
  { 224,  32,  32, 1 }, { 128, 128, 128, 1 }, {  96,  96,  96, 1 }, {  64,  64,  64, 1 },
  {   0,   0,   0, 1 }, {   0, 224,   0, 1 }, {   0,  32, 224, 1 }, {  32,   0,   0, 1 },
  {  96,   0,   0, 1 }, { 160,   0,   0, 1 }, { 160,  96,   0, 1 }, {  96,  32,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 },
  { 128, 192,   0, 1 }, {  64, 160,   0, 1 }, {  32,  96,   0, 1 }, {   0,  64,   0, 1 },
  {   0,   0,  64, 1 }, {   0,   0, 128, 1 }, {   0,  32, 192, 1 }, {   0,  64, 224, 1 },
  {   0, 160, 224, 1 }, { 224, 224,   0, 1 }, {   0, 224, 224, 1 }, { 224,   0,   0, 1 },
};
static PALETTEENTRY coltbl5[32] = {
  {  96,   0,  64, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 }, { 224, 128,   0, 1 },
  { 224,  32,   0, 1 }, { 128, 128, 160, 1 }, {  96,  96, 128, 1 }, {  64,  64,  96, 1 },
  {   0,   0,   0, 1 }, {  32,  64,   0, 1 }, {  64, 128,   0, 1 }, { 128, 160,   0, 1 },
  {  64, 224,   0, 1 }, {   0,   0, 224, 1 }, {  64,   0,  32, 1 }, { 160, 160, 192, 1 },
  {  96,   0,  64, 1 }, { 224,  64,   0, 1 }, { 224, 128,   0, 1 }, { 224, 192,   0, 1 },
  { 160, 224,  64, 1 }, { 128, 224, 128, 1 }, {  64, 224, 192, 1 }, {  64, 160, 224, 1 },
  { 128,  96, 224, 1 }, { 160,   0, 224, 1 }, { 224,  32, 224, 1 }, { 224,   0, 160, 1 },
  { 224,   0,  96, 1 }, { 224,   0,  32, 1 }, { 192,  64, 128, 1 }, { 224, 160, 224, 1 },
};
static PALETTEENTRY coltbl6[32] = {
  {   0,  64,   0, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 }, { 224, 128,   0, 1 },
  { 224,  32,   0, 1 }, {  96, 128, 128, 1 }, {  64,  96,  96, 1 }, {  32,  64,  64, 1 },
  {   0,   0,   0, 1 }, { 160, 224,   0, 1 }, {  96, 192,   0, 1 }, {  32, 128,   0, 1 },
  {   0,  96,   0, 1 }, { 128, 160, 160, 1 }, {   0,  64,  32, 1 }, {   0,  32, 192, 1 },
  {   0,  64,   0, 1 }, {   0,   0,   0, 1 }, {  32,  32,  32, 1 }, {   0, 192, 224, 1 },
  { 224, 224, 224, 1 }, { 224, 128, 224, 1 }, { 224,  64, 160, 1 }, { 160, 224,   0, 1 },
  { 224,   0,  64, 1 }, { 224, 192,  96, 1 }, {  32,  64,   0, 1 }, {  64, 128,   0, 1 },
  { 128, 160,   0, 1 }, { 224, 160,  32, 1 }, { 192, 128,   0, 1 }, { 128,  64,   0, 1 },
};
static PALETTEENTRY coltbl7[32] = {
  {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, { 224, 224,   0, 1 }, { 224, 128,   0, 1 },
  { 224,  32,   0, 1 }, { 160, 160, 128, 1 }, { 128, 128,  64, 1 }, {  64,  64,  32, 1 },
  {   0,   0,   0, 1 }, {   0,   0, 224, 1 }, {  96, 192, 224, 1 }, {  64, 128, 224, 1 },
  {  32,  96, 224, 1 }, {  64, 128,  32, 1 }, {  32,  96,   0, 1 }, {   0,  64,   0, 1 },
  {   0,   0,   0, 1 }, {   0,   0,   0, 1 }, { 224, 224, 224, 1 }, { 224, 224, 160, 1 },
  { 224, 192, 128, 1 }, { 224, 160, 128, 1 }, { 192, 128, 128, 1 }, { 224,  96, 160, 1 },
  {   0,   0, 192, 1 }, { 224, 224,   0, 1 }, {  96,  96,  96, 1 }, {  64,  32,   0, 1 },
  {  96,  32,   0, 1 }, { 128,  64,  32, 1 }, {  64,  96, 224, 1 }, {   0, 224, 224, 1 },
};
static unsigned char cltbl[1008] = {
  0, 32, 64, 96, 128, 160, 192, 224, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 32, 64, 96, 128, 160, 192, 0, 0, 0, 0, 0, 0, 0, 32,
  0, 0, 0, 32, 64, 96, 128, 160, 0, 0, 0, 0, 0, 0, 32, 64,
  0, 0, 0, 0, 32, 64, 96, 128, 0, 0, 0, 0, 0, 32, 64, 96,
  0, 0, 0, 0, 0, 32, 64, 96, 0, 0, 0, 0, 32, 64, 96, 128,
  0, 0, 0, 0, 0, 0, 32, 64, 0, 0, 0, 32, 64, 96, 128, 160,
  0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 32, 64, 96, 128, 160, 192,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 64, 96, 128, 160, 192, 224,
  0, 0, 0, 0, 0, 0, 0, 0, 32, 64, 96, 128, 160, 192, 224, 192,
  0, 32, 0, 0, 0, 0, 0, 0, 64, 96, 128, 160, 192, 224, 192, 160,
  0, 64, 32, 0, 0, 0, 0, 0, 96, 128, 160, 192, 224, 192, 160, 128,
  0, 96, 64, 32, 0, 0, 0, 0, 128, 160, 192, 224, 192, 160, 128, 96,
  0, 128, 96, 64, 32, 0, 0, 0, 160, 192, 224, 192, 160, 128, 96, 64,
  0, 160, 128, 96, 64, 32, 0, 0, 192, 224, 192, 160, 128, 96, 64, 32,
  0, 192, 160, 128, 96, 64, 32, 0, 224, 192, 160, 128, 96, 64, 32, 0,
  0, 224, 192, 160, 128, 96, 64, 32, 192, 160, 128, 96, 64, 32, 0, 0,
  0, 192, 224, 192, 160, 128, 96, 64, 160, 128, 96, 64, 32, 0, 0, 0,
  0, 160, 192, 224, 192, 160, 128, 96, 128, 96, 64, 32, 0, 0, 0, 0,
  0, 128, 160, 192, 224, 192, 160, 128, 96, 64, 32, 0, 0, 0, 0, 0,
  0, 96, 128, 160, 192, 224, 192, 160, 64, 32, 0, 0, 0, 0, 0, 0,
  0, 64, 96, 128, 160, 192, 224, 192, 32, 0, 0, 0, 0, 0, 0, 0,
  0, 32, 64, 96, 128, 160, 192, 224, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 32, 64, 96, 128, 160, 192, 0, 0, 0, 0, 0, 0, 0, 2,
  0, 0, 0, 32, 64, 96, 128, 160, 0, 0, 0, 0, 0, 0, 2, 4,
  0, 0, 0, 0, 32, 64, 96, 128, 0, 0, 0, 0, 0, 2, 4, 6,
  0, 0, 0, 0, 0, 32, 64, 96, 0, 0, 0, 0, 2, 4, 6, 8,
  0, 0, 0, 0, 0, 0, 32, 64, 0, 0, 0, 2, 4, 6, 8, 10,
  0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 2, 4, 6, 8, 10, 12,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 6, 8, 10, 12, 14,
  0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 6, 8, 10, 12, 14, 12,
  0, 2, 0, 0, 0, 0, 0, 0, 4, 6, 8, 10, 12, 14, 12, 10,
  0, 4, 2, 0, 0, 0, 0, 0, 6, 8, 10, 12, 14, 12, 10, 8,
  0, 6, 4, 2, 0, 0, 0, 0, 8, 10, 12, 14, 12, 10, 8, 6,
  0, 8, 6, 4, 2, 0, 0, 0, 10, 12, 14, 12, 10, 8, 6, 4,
  0, 10, 8, 6, 4, 2, 0, 0, 12, 14, 12, 10, 8, 6, 4, 2,
  0, 12, 10, 8, 6, 4, 2, 0, 14, 12, 10, 8, 6, 4, 2, 0,
  0, 14, 12, 10, 8, 6, 4, 2, 12, 10, 8, 6, 4, 2, 0, 0,
  0, 12, 14, 12, 10, 8, 6, 4, 10, 8, 6, 4, 2, 0, 0, 0,
  0, 10, 12, 14, 12, 10, 8, 6, 8, 6, 4, 2, 0, 0, 0, 0,
  0, 8, 10, 12, 14, 12, 10, 8, 6, 4, 2, 0, 0, 0, 0, 0,
  0, 6, 8, 10, 12, 14, 12, 10, 4, 2, 0, 0, 0, 0, 0, 0,
  0, 4, 6, 8, 10, 12, 14, 12, 2, 0, 0, 0, 0, 0, 0, 0,
  0, 2, 4, 6, 8, 10, 12, 14, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 2, 4, 6, 8, 10, 12, 0, 0, 0, 0, 0, 0, 0, 32,
  0, 0, 0, 2, 4, 6, 8, 10, 0, 0, 0, 0, 0, 0, 32, 64,
  0, 0, 0, 0, 2, 4, 6, 8, 0, 0, 0, 0, 0, 32, 64, 96,
  0, 0, 0, 0, 0, 2, 4, 6, 0, 0, 0, 0, 32, 64, 96, 128,
  0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 32, 64, 96, 128, 160,
  0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 32, 64, 96, 128, 160, 192,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 64, 96, 128, 160, 192, 224,
  0, 0, 0, 0, 0, 0, 0, 0, 32, 64, 96, 128, 160, 192, 224, 192,
  0, 32, 0, 0, 0, 0, 0, 0, 64, 96, 128, 160, 192, 224, 192, 160,
  0, 64, 32, 0, 0, 0, 0, 0, 96, 128, 160, 192, 224, 192, 160, 128,
  0, 96, 64, 32, 0, 0, 0, 0, 128, 160, 192, 224, 192, 160, 128, 96,
  0, 128, 96, 64, 32, 0, 0, 0, 160, 192, 224, 192, 160, 128, 96, 64,
  0, 160, 128, 96, 64, 32, 0, 0, 192, 224, 192, 160, 128, 96, 64, 32,
  0, 192, 160, 128, 96, 64, 32, 0, 224, 192, 160, 128, 96, 64, 32, 0,
  0, 224, 192, 160, 128, 96, 64, 32, 192, 160, 128, 96, 64, 32, 0, 0,
  0, 192, 224, 192, 160, 128, 96, 64, 160, 128, 96, 64, 32, 0, 0, 0,
  0, 160, 192, 224, 192, 160, 128, 96, 128, 96, 64, 32, 0, 0, 0, 0,
  0, 128, 160, 192, 224, 192, 160, 128, 96, 64, 32, 0, 0, 0, 0, 0,
  0, 96, 128, 160, 192, 224, 192, 160, 64, 32, 0, 0, 0, 0, 0, 0,
  0, 64, 96, 128, 160, 192, 224, 192, 32, 0, 0, 0, 0, 0, 0, 0,
};
static int hdatatbl4[111] = { 249856, 253952, 258048, 262144, 262144, 266240, 266240, 270336, 274432, 274432, 278528, 282624, 282624, 286720, 286720, 290816, 290816, 294912, 299008, 299008, 303104, 303104, 307200, 307200, 311296, 311296, 315392, 315392, 319488, 319488, 323584, 323584, 323584, 327680, 327680, 331776, 331776, 335872, 335872, 335872, 339968, 339968, 344064, 344064, 344064, 348160, 348160, 348160, 352256, 352256, 352256, 356352, 356352, 356352, 360448, 360448, 360448, 364544, 364544, 364544, 364544, 368640, 368640, 368640, 368640, 372736, 372736, 372736, 372736, 376832, 376832, 376832, 376832, 376832, 380928, 380928, 380928, 380928, 380928, 380928, 385024, 385024, 385024, 385024, 385024, 385024, 385024, 389120, 389120, 389120, 389120, 389120, 389120, 389120, 389120, 389120, 389120, 393216, 393216, 393216, 393216, 393216, 393216, 393216, 393216, 393216, 393216, 393216, 393216, 393216, 393216 };
static char hdatatbl5[128] = { 0, -5, -10, -15, -20, -25, -30, -35, -40, -44, -48, -52, -56, -60, -64, -67, -70, -73, -76, -78, -80, -82, -84, -86, -88, -90, -92, -93, -94, -93, -92, -90, -88, -85, -82, -80, -78, -71, -64, -56, -48, -32, -16, 0, 16, 21, 26, 30, 34, 35, 36, 37, 38, 37, 36, 34, 32, 28, 24, 20, 16, 10, 5, 0, -4, -9, -13, -18, -22, -24, -26, -28, -30, -31, -32, -33, -34, -33, -32, -31, -30, -28, -27, -25, -24, -20, -16, -12, -8, 0, 8, 15, 22, 30, 38, 47, 56, 64, 72, 80, 88, 94, 100, 106, 112, 115, 118, 120, 122, 123, 124, 125, 126, 125, 124, 122, 120, 114, 108, 102, 96, 86, 76, 66, 56, 42, 28, 14 };
static unsigned short mp01[4] = { 1, 2, 3, 4 };
static unsigned short mp02[4] = { 5, 6, 7, 8 };
static unsigned short mp03[4] = { 9, 10, 11, 12 };
static unsigned short mp04[4] = { 8201, 8202, 8203, 8204 };
static unsigned short mp05[4] = { 8205, 8206, 8207, 8208 };
static unsigned short mp06[4] = { 8209, 8210, 8211, 8212 };
static unsigned short mp07[4] = { 8213, 8214, 8215, 8216 };
static unsigned short mp08[10] = { 16409, 16410, 16411, 16412, 16413, 16414, 16414, 16414, 16415, 16416 };
static unsigned short mp09[8] = { 16423, 16424, 16425, 16426, 16415, 16427, 16428, 16414 };
static unsigned short mp10[8] = { 16417, 16418, 16419, 16413, 16420, 16421, 16422, 16416 };
static unsigned short mp11[12] = { 16423, 16411, 16525, 16526, 16527, 16528, 16529, 16414, 16530, 16531, 16532, 16533 };
static unsigned short mp14[30] = { 16413, 16534, 16535, 16536, 16537, 16538, 16539, 16540, 16541, 16542, 16543, 16544, 16545, 16546, 16547, 16416, 16548, 16549, 16550, 16551, 16552, 16553, 16554, 16555, 16556, 16557, 16558, 16556, 16559, 16553 };
static unsigned short mp21[46] = { 16444, 16445, 16446, 16447, 16448, 16449, 16450, 16451, 16452, 16453, 16454, 16455, 16384, 16384, 16384, 16456, 16457, 16458, 16459, 16460, 16461, 16462, 16463, 16464, 16465, 16466, 16467, 16468, 16469, 16470, 16471, 16472, 16473, 16474, 16475, 16476, 16384, 16384, 16477, 16478, 16479, 16480, 16481, 16482, 16483, 16484 };
static unsigned short mp22[42] = { 16485, 16486, 16487, 16488, 16489, 16462, 16463, 16384, 16384, 16444, 16445, 16490, 16491, 16492, 16493, 16494, 16495, 16448, 16449, 16444, 16445, 16496, 16497, 16498, 16499, 16500, 16483, 16484, 16384, 16384, 16464, 16465, 16501, 16502, 16503, 16504, 16505, 16506, 16468, 16469, 16464, 16465 };
static unsigned short mp23[52] = { 16507, 16508, 16458, 16459, 16490, 16509, 16384, 16384, 16490, 16509, 16510, 16511, 16448, 16449, 16512, 16513, 16384, 16384, 16453, 16454, 16455, 16384, 16514, 16384, 16514, 16514, 16515, 16516, 16479, 16480, 16501, 16517, 16384, 16384, 16501, 16517, 16518, 16519, 16468, 16469, 16520, 16521, 16384, 16384, 16473, 16474, 16475, 16476, 16522, 16523, 16524, 16524 };
bwrt_info bwrtTbl[16] = {
  { mp03, 1428, 2, 2 },
  { mp07, 1434, 2, 2 },
  { mp01, 1440, 2, 2 },
  { mp04, 1446, 2, 2 },
  { mp06, 1452, 2, 2 },
  { mp05, 1458, 2, 2 },
  { mp02, 1464, 2, 2 },
  { mp08, 1810, 5, 2 },
  { mp09, 2194, 4, 2 },
  { mp10, 2578, 4, 2 },
  { mp11, 2204, 6, 2 },
  { mp11, 2588, 6, 2 },
  { mp14, 2962, 15, 2 },
  { mp21, 914, 23, 2 },
  { mp22, 916, 21, 2 },
  { mp23, 910, 26, 2 }
};
static unsigned char stone_timer = 20;
static PALETTEENTRY stone_color_set_tbl[40] = {
  {   0,  64,   0, 1 }, { 224, 224, 224, 1 }, { 128, 224,   0, 1 }, {  64, 160,   0, 1 },
  {  32,  96,   0, 1 }, {   0,  64,   0, 1 }, { 224, 224, 224, 1 }, { 224,  96,   0, 1 },
  { 224,  64,   0, 1 }, { 128,   0,   0, 1 }, {   0,  64,   0, 1 }, { 224, 224, 224, 1 },
  { 224, 224,  32, 1 }, { 128, 128,   0, 1 }, {  64,  32,   0, 1 }, {   0,  64,   0, 1 },
  { 224, 224, 224, 1 }, {  96,  96, 224, 1 }, {  64,  64, 224, 1 }, {  32,  32, 192, 1 },
  {   0,  64,   0, 1 }, { 224, 224, 224, 1 }, {  64, 224, 128, 1 }, {   0, 160, 160, 1 },
  {   0,  64,  96, 1 }, {   0,  64,   0, 1 }, { 224, 224, 224, 1 }, { 128,   0, 224, 1 },
  {  64,   0, 128, 1 }, {  32,   0,  64, 1 }, {   0,  64,   0, 1 }, { 224, 224, 224, 1 },
  { 224,   0,   0, 1 }, { 128,   0,   0, 1 }, {  64,   0,  32, 1 }, {   0,  64,   0, 1 },
  { 224, 224, 224, 1 }, { 128, 224,   0, 1 }, {  64, 160,   0, 1 }, {  32,  96,   0, 1 },
};
static unsigned char hscrflg;
static unsigned short hscrcnt4;
static void(*hscrltbl[8])(void) = { &hscrl0, &hscrl1, &hscrl2, &hscrl3, &hscrl4, &hscrl5, &hscrl6, &hscrl7 };

void m2mainchk(void) {}



void m2subset(void) {}









int specgame(void) {
  int i;

  if (gKeepWork.SPEMode != 0 || spgmmode & 1) {
    SetUseOk(0, 103, 0);
    SetUseOk(0, 102, 0);
  } else {
    SetUseOk(0, 103, 1);
    if (spgmmode & 2)
      SetUseOk(0, 102, 1);
    else
      SetUseOk(0, 102, 0);
  }



  if (gKeepWork.SPEMode != 0) {
    switch (gKeepWork.SPEMode) {
      case 1:
        gKeepWork.SPEMode = 2;
        disp();
        if (!(spgmmode & 2)) {
          sub_sync(107);
        }
        return 0;
      case 2:
        for (i = 0; i < 3; ++i) {
          if (disp_main()) {

            gKeepWork.SPEMode = 3;
            break;
          }
        }
        game_score_disp();
        time_bonus_disp();
        ring_bonus_disp();
        sonic_disp();
        return 0;
      case 3:
        gKeepWork.SPEMode = 4;
        CDPause(2);
        return 3;
      case 5:
        gKeepWork.SPEMode = 6;

        gKeepWork.ta_time = (spe_time.l >> 16 & 255) * 60 * 60;
        gKeepWork.ta_time += (spe_time.l >> 8 & 255) * 60;
        gKeepWork.ta_time += spe_time.l & 255;
        CDPause(2);
        return 4;
      default:
        return 0;
    }
  }


  if (spgmmode & 2) {
    if ((swdata1.b.l & 112) == 112) {

      gKeepWork.ta_time = -1;
      CDPause(2);
      gKeepWork.SPEMode = 6;
      SetUseOk(0, 102, 0);
      SetUseOk(0, 103, 0);
      return 4;
    }
  }
  if (pause_chk()) return 0;

  if (spgmmode & 1) {
    if (swdata1.b.h & 240) {
      gKeepWork.ta_time = -1;
      CDPause(2);
      gKeepWork.SPEMode = 7;
      return 4;
    }
  }





  rlscrflg_save = rlscrflg;
  rlscrflg = 0;







  init_3dpara();
  speckaiten();
  scalinit();
  specaction();
  if (gKeepWork.SpecialTime == 0)
    time_dec();
  if (ufochk() != 0 && spgmmode & 2)
    pldeadflg = 1;

  if (pldeadflg) {
    clwout();
    game_over();
    if (spgmmode & 2) {
      gKeepWork.SPEMode = 5;
      return 0;
    }
    gKeepWork.SPEMode = 1;
    return 1;
  }

  if (gmclrflg) {
    game_clear();
    clwout();
    gKeepWork.SPEMode = 1;
    return 0;
  }
  hscal();
  intmode = 0;
  ringno_disp();
  ufoleft_disp();
  stone_color_set();
  spetime_disp();
  color_change();

  return 0;
}


int ufochk(void) {
  int i;

  for (i = 0; i < 6; ++i) {
    if (specactwk[i + 32].actno) return 0;
  }
  return -1;
}


void game_clear(void) {
  clrspflg |= (unsigned char)(1 << stagenm);
  clrspflg_save = clrspflg;
  game_over();
}


void game_over(void) {
  unsigned char d0;





  d0 = stagenm;
  do {
    ++d0;
    if (d0 >= 7) {
      d0 = 0;
    }
    if (clrspflg == 127) return;


  } while ((clrspflg & 1 << d0) != 0);





}












void specgame_init(void) {
  FILE* hf;
  char fn[80];
  PALETTEENTRY* lpPeDest;
  int i;

  hdatabuf = (unsigned int*)hscrollbuff;
  clrspflg = clrspflg_save;
  spgmmode = 0;
  if (ta_flag) {
    spgmmode |= 2;
  }
  memset(tv_adr, 0, sizeof(tv_adr));
  hsdata5 = 0;
  hsdata4 = 0;
  hsdata3 = 0;
  hsdata2 = 0;
  hsdata1 = 0;
  hsdata0 = 0;
  sonicup_no = 0;
  gmtime0 = 0;
  memset(hdatabuf_l, 0, sizeof(hdatabuf_l));
  rlscrflg = 0;
  se_no.l = 0;
  memset(&zoomwk, 0, sizeof(zoomwk));
  hane_cnt = 0;
  damage_cnt = 0;
  chg_timer = 0;
  pmflag = 0;
  swdata_pl.w = 0;
  jmpswcnt = 0;
  rufo_getnm = 0;
  tdecflg = 0;
  gmclrflg = 0;
  pldeadflg = 0;
  colliadr = 0;
  memset(z_buffer, 0, sizeof(z_buffer));
  seregiflg = 0;
  hscrcnt = 256;
  PauseIcon = 0;
  scoreup_setm = 0;
  memset(specclchgcnt, 0, sizeof(specclchgcnt));
  stone_timer = 20;
  hscrflg = 0;
  hscrcnt4 = 0;
  init_sonic_upcnt();
  ranum = 0;



  sprintf(fn, "SPECIAL/MAP/SP%1dMAP.MAP", stagenm);
  hf = fopen(fn, "rb");
  fread(sm_adr0, 1, sizeof(sm_adr0), hf);
  fclose(hf);



  overint = -1;

  memset(specactwk, 0, sizeof(specactwk));


  lpPeDest = lpcolorwk;
  for (i = 0; i < 64; ++i)
    *lpPeDest++ = colortbl[i];

  stage_init();






  demoflg = 1;
  pauseflg = 128;
  overint = 0;



  spe_time.l = 0;
  ringno = 0;
  ufoleft = 6;



  time_stop = 0;

  kaiten_init();
  colli_init();

  specactwk[0].actno = 1;
  specactwk[1].actno = 6;
  specactwk[3].actno = 10;
  specactwk[4].actno = 11;

  ufo_initial();

  tcnt20 = 20;
  rufo_getnm = 20;
  game_start = 1;

  if (!(spgmmode & 2)) {
    spe_time.l = 100;
  }

  CDPlay(32);

}



























void disp(void) {
  short i;
  PALETTEENTRY *lpPeSrc, *lpPeDest;

  ringbonus = ringno * 20;
  timebonus = spe_time.l * 20;

  demoflg = 0;
  special_flag = 0;



  lpPeSrc = dispcolor;
  lpPeDest = lpcolorwk;
  for (i = 0; i < 64; ++i) {
    *lpPeDest++ = *lpPeSrc++;
  }

  map_init();
  clwin_init();
  clwin();
  gmtime0 = 480;
  sonicup_no = 0;

}











int disp_main(void) {
  if ((long int)ringbonus != 0) {

    gsc_up20();
    ringbonus -= 20;
  } else {
    if ((long int)timebonus != 0) {


      timebonus -= 20;
      gsc_up20();
    }
  }
  if (seregiflg == 0) {

    if ((long int)(timebonus + ringbonus) == 0) {

      if (timebonus == 0) WaveAllStop();
      seregiflg = 1;

      soundset(154);
    }
  }

  if (--gmtime0) return 0;


  gsc_up(ringbonus + timebonus);


  WaveAllStop();
  soundset(200);
  clwout();
  return 1;
}













void gsc_up20(void) {

  if (++scoreup_setm % 6 == 0)
    key_set(189);
  gsc_up(20);
}

void gsc_up(int lScore) {


  lScore += plscore;


  while (lScore > extrascore) {

    extrascore += 5000;
    ++pl_suu;
    ++sonicup_no;
    WaveAllStop();
    sub_sync(122);
    if (pl_suu >= 250)
      pl_suu = 249;
  }

  plscore = lScore;
  if ((unsigned int)plscore >= 1000000) {
    plscore = 999999;
  }
}











short pause_chk(void) {

  if (pauseflg & 128) {
    if (pauseflg & 1) {

      if (swdata1.b.l & 128) {
        if (swdata2.w & 32896) {
          if (PauseIcon != 0) {
            pauseflg &= 254;
            PauseIcon = 0;
            return 0;
          }
        }
        else {
          pauseflg &= 254;
          CDPause(1);
          return 0;
        }
      }

      return 1;
    }


    if (!(spgmmode & 1)) {

      if (swdata1.b.l & 128) {
        if (swdata2.w & 32896) PauseIcon = 1;
        pauseflg |= 1;
        CDPause(0);
        return 1;
      }
    }
  }


  return 0;

}
















void map_init(void) {
  unsigned int d5;
  int i;

  if (timebonus != 0) {
    if (clrspflg != 127) d5 = 15;
    else d5 = 16;
  }
  else
    d5 = 14;

  bwrtset(d5);

  for (i = 0; i < 7; ++i) {

    if (clrspflg & 1 << i) {
      bwrtset(i + 1);
    }
  }
  bwrtset(134810123);
  bwrtset(3085);

}






































































































void bwrtset(unsigned int tblno4) {
  int i;
  int xbase, ybase, x, y;
  int tileno;
  unsigned short col, tblno;

  do {
    tblno = (long int)tblno4 & 255;
    if (!tblno) break;
    --tblno;
    xbase = (bwrtTbl[tblno].vadr & 127) / 2;
    ybase = bwrtTbl[tblno].vadr / 128;
    i = 0;
    for (y = 0; y < bwrtTbl[tblno].ysize; ++y) {
      for (x = 0; x < bwrtTbl[tblno].xsize; ++x) {
        tileno = bwrtTbl[tblno].tbl[i] & 2047;
        col = bwrtTbl[tblno].tbl[i] & 24576;
        ++i;
        if (col == 24576) {
          tileno += 687;
        }
        else if (col == 16384) {
          tileno += 458;
        }
        else if (col == 8192) {
          tileno += 229;
        }
        SetSpecialGrid(0, xbase + x, ybase + y, tileno, 0);
      }
    }




    tblno4 >>= 8;
  } while (1);

}























void stone_color_set(void) {
  PALETTEENTRY *lpPeSrc, *lpPeDest;
  short i;

  if (ufoleft != 0) return;
  if (stone_timer == 0) return;
  if (--stone_timer != 0) return;


  lpPeSrc = &stone_color_set_tbl[stagenm * 5 + 1];
  lpPeDest = &lpcolorwk[50];
  for (i = 0; i < 4; ++i) {
    *lpPeDest++ = *lpPeSrc++;
  }







  int_flg |= 2;

}















void panel_box(void) {}


void colset(PALETTEENTRY* lpPeSrc) {
  PALETTEENTRY* lpPeDest;
  int i;

  lpPeDest = &lpcolorwk[16];
  for (i = 0; i < 32; ++i) {
    *lpPeDest++ = *lpPeSrc++;
  }

}


void sinit0(void) {



  panel_box();

  colset(coltbl0);
}

void sinit1(void) {
  panel_box();

  colset(coltbl1);
}

void sinit2(void) {
  panel_box();

  colset(coltbl2);
}

void sinit3(void) {
  panel_box();

  colset(coltbl3);
}

void sinit4(void) {
  short i;

  panel_box();

  colset(coltbl4);

  for (i = 0; i < 128; ++i) hdatabuf[i] = 4286578688;
}

void sinit5(void) {
  panel_box();

  colset(coltbl5);
}

void sinit6(void) {
  panel_box();

  colset(coltbl6);
}

void sinit7(void) {
  panel_box();

  colset(coltbl7);
}


void stage_init(void) {
  void(*jptbl[8])(void) = {
    &sinit0, &sinit1, &sinit2, &sinit3, &sinit4, &sinit5, &sinit6, &sinit7
  };

  jptbl[stagenm]();
}
























void key_set(short ReqNo) {
  soundset(ReqNo);
}









void hscal_1(void) {
  if (!scroll_stop) {
    if (stagenm == 0) hscal1_0();
    else if (stagenm == 4) hscal1_4();
    else if (stagenm == 5) hscal1_5();
  }
}

void hscal_2(void){
  if (!scroll_stop) {
    if (stagenm == 0) hscal2_0();
    else if (stagenm == 4) hscal2_4();
    else if (stagenm == 5) hscal2_5();
  }
}




void hscal0_0(void) {
  int d0, d1;
  short *a0, *a1;
  short d3, d4, d7;

  d0 = 524288;
  d1 = 0;
  rlspd_get(&d0, &d1);
  hsdata1 += d0;
  d0 >>= 1;
  hsdata0 += d0;



  if (!hscrflg) {
    ++hscrcnt;
    if (hscrcnt >= 512) {
      hscrcnt = 511;
      hscrflg = 1;
    }
  }
  else {

    if ((short)--hscrcnt < 0) {
      hscrcnt = 0;
      hscrflg = 0;
    }
  }

  a0 = (short*)&hdatabuf[0];
  a1 = (short*)hdatabuf_l;
  d0 = 65536;
  d1 = 1024;
  d3 = 0;
  d4 = 0;
  d7 = 23;
  hscal0(a0, a1, d0, d1, d3, d4, d7);
}


void hscal1_0(void) {
  int d0, d1;
  short *a0, *a1;
  short d3, d4, d7;

  a0 = (short*)&hdatabuf[24];
  a1 = (short*)&hdatabuf_l[24];
  d0 = 40960;
  d1 = 1024;
  d3 = hsdata1 >> 16;
  d4 = 0;
  d7 = 71;

  hscal0(a0, a1, d0, d1, d3, d4, d7);
}

void hscal2_0(void) {
  int d0, d1;
  short *a0, *a1;
  short d3, d4, d7;

  a0 = (short*)&hdatabuf[96];
  a1 = (short*)&hdatabuf_l[96];
  d0 = -32768;
  d1 = 1024;
  d3 = hsdata0 >> 16;
  d4 = 0;
  d7 = 31;

  hscal0(a0, a1, d0, d1, d3, d4, d7);
}


void hscal0(short* a0, short* a1, int d0, int d1, short d3, short d4, short d7) {
  int_union d2;

  if (!hscrflg) {

    do {
      *a0++ = d3;
      *a1++ = d4;
      d2.w.h = *a0;
      d2.w.l = *a1;
      d2.l += d0;
      *a1++ = d2.w.l;
      *a0++ = d2.w.h;
      d0 -= d1;
    } while (--d7 >= 0);
  }
  else {

    do {
      *a0++ = d3;
      *a1++ = d4;
      d2.w.h = *a0;
      d2.w.l = *a1;
      d2.l -= d0;
      *a1++ = d2.w.l;
      *a0++ = d2.w.h;
      d0 -= d1;
    } while (--d7 >= 0);
  }
}



void hscal0_4(void) {
  int d0, d1;
  short *a0, *a1;
  int* a2;
  short d7;

  d0 = 0x40000;
  d1 = 0;
  rlspd_get(&d0, &d1);
  hsdata0 += d0;






  hscrflg = 0;
  if (rlscrflg_save & 4) {

    hscrflg = 1;
    ++hscrcnt4;
    hscrcnt4 &= 15;
    if (!hscrcnt4) hscrflg = 2;
  }

  if (rlscrflg_save & 8) {

    hscrflg = 255;
    --hscrcnt4;
    hscrcnt4 &= 15;
    if (!hscrcnt4) hscrflg = 2;
  }

  a0 = (short*)&hdatabuf[0];
  a1 = (short*)&hdatabuf_l[0];
  a2 = &hdatatbl4[0];
  d0 = 0;
  d7 = 16;

  do {
    *(int*)a0 = d0;
    *(int*)a1 = d0;
    a0 += 2;
    a1 += 2;
  } while (--d7 >= 0);
  d7 = 6;
  hscal4(a0, a1, a2, 0, d7);
}

void hscal1_4(void) {
  short *a0, *a1;
  int* a2;
  short d7;

  a0 = (short*)&hdatabuf[24];
  a1 = (short*)&hdatabuf_l[24];
  a2 = &hdatatbl4[7];

  d7 = 55;

  hscal4(a0, a1, a2, hsdata0 >> 16, d7);
}

void hscal2_4(void) {
  short *a0, *a1;
  int* a2;
  short d7;

  a0 = (short*)&hdatabuf[80];
  a1 = (short*)&hdatabuf_l[80];
  a2 = &hdatatbl4[63];

  d7 = 47;

  hscal4(a0, a1, a2, hsdata0 >> 16, d7);
}


void hscal4(short* a0, short* a1, int* a2, short d0, short d7) {
  int_union d2;

  if (hscrflg == 2) {

    do {
      *a0++ = d0;
      *a1++ = d0;
      *a0++ = -128;
      *a1++ = 0;
    } while (--d7 >= 0);
    return;
  }
  if (hscrflg == 0) return;
  if ((char)hscrflg > 0) {


    do {
      *a0++ = d0;
      *a1++ = d0;
      d2.w.h = *a0;
      d2.w.l = *a1;
      d2.l += *a2++;
      *a1++ = d2.w.l;
      *a0++ = d2.w.h;
    } while (--d7 >= 0);
  }
  else {


    do {
      *a0++ = d0;
      *a1++ = d0;
      d2.w.h = *a0;
      d2.w.l = *a1;
      d2.l -= *a2++;
      *a1++ = d2.w.l;
      *a0++ = d2.w.h;
    } while (--d7 >= 0);
  }
}




void hscal0_5(void) {
  int d0, d1;
  short* a0;
  char* a2;
  short d2, d7;

  d0 = 0x40000;
  d1 = 0;
  rlspd_get(&d0, &d1);
  hsdata0 += d0;

  a0 = (short*)&hdatabuf[0];
  a2 = hdatatbl5;
  d0 = 0;
  d2 = hscrcnt4;
  ++d2;
  d2 &= 127;
  hscrcnt4 = d2;
  d7 = 23;

  hscal5(a0, a2, 0, d2, d7);
}

void hscal1_5(void) {
  short* a0;
  char* a2;
  short d2, d7;

  a0 = (short*)&hdatabuf[24];
  a2 = hdatatbl5;

  d2 = hscrcnt4;
  d7 = 55;

  hscal5(a0, a2, hsdata0 >> 16, d2, d7);
}

void hscal2_5(void) {
  short* a0;
  char* a2;
  short d2, d7;

  a0 = (short*)&hdatabuf[80];
  a2 = hdatatbl5;

  d2 = hscrcnt4;
  d7 = 47;

  hscal5(a0, a2, hsdata0 >> 16, d2, d7);
}

void hscal5(short* a0, char* a2, short d0, short d2, short d7) {
  short d1;

  do {
    *a0++ = d0;
    d1 = a2[d2];
    *a0++ = d1;
    ++d2;
    d2 &= 127;
  } while (--d7 >= 0);
  hscrcnt4 = d2;
}



void rlspd_get(int* d0, int* d1) {
  if (rlscrflg_save & 4) return;
  *d0 = -*d0;
  *d1 = -*d1;
  if (rlscrflg_save & 8) return;
  *d0 = 0;
  *d1 = 0;
}

void hscrspd_get(int* lD0, int* lD1) {










  *lD0 = 0x40000;
  rlspd_get(lD0, lD1);
  hsdata2 += *lD0;
  *lD0 /= 2;
  hsdata1 += *lD0;
  *lD0 /= 2;
  hsdata0 += *lD0;

}


void hscrl0(void) {
  hscal0_0();
  hscal1_0();
  hscal2_0();

}

void hscrl1(void) {
  int lD0;
  int lD1;
  int i;












  for (i = 0; i < 3; ++i) {
    hscrspd_get(&lD0, &lD1);
    hdatabuf[0] = hsdata1;
    hdatabuf[1] = hsdata2;
  }

}

void hscrl2(void) {
  int lD0;
  int lD1;
  int i;

  for (i = 0; i < 3; ++i) {
    lD0 = 524288;
    lD1 = 65536;
    rlspd_get(&lD0, &lD1);

    hsdata0 += lD0;
    lD0 -= lD1;
    hsdata1 += lD0;
    lD0 -= lD1;
    hsdata2 += lD0;
    lD0 -= lD1;
    hsdata3 += lD0;
    lD0 -= lD1;
    hsdata4 += lD0;
    lD0 -= lD1;
    hsdata5 += lD0;


    hdatabuf[0] = hsdata4;

    hdatabuf[1] = hsdata1;
    hdatabuf[2] = hsdata2;
    hdatabuf[3] = hsdata3;
    hdatabuf[4] = hsdata5;
  }

}

void hscrl3(void) {
  int lD0;
  int lD1;
  int i;


  for (i = 0; i < 3; ++i) {
    hscrspd_get(&lD0, &lD1);
    hdatabuf[0] = hsdata1;
    hdatabuf[1] = hsdata0;
    hdatabuf[2] = hsdata2;
  }

}

void hscrl4(void) {
  hscal0_4();
  hscal1_4();
  hscal2_4();

}

void hscrl5(void) {
  hscal0_5();
  hscal1_5();
  hscal2_5();

}

void hscrl6(void) {
  int lD0;
  int lD1;
  int i;

  for (i = 0; i < 3; ++i) {
    lD0 = 524288;
    lD1 = 98304;
    rlspd_get(&lD0, &lD1);

    hsdata0 += lD0;
    lD0 -= lD1;
    hsdata1 += lD0;
    lD0 -= lD1;
    hsdata2 += lD0;
    lD0 -= lD1;
    hsdata3 += lD0;

    hdatabuf[0] = hsdata1;
    hdatabuf[1] = hsdata3;
    hdatabuf[2] = hsdata0;
    hdatabuf[3] = hsdata2;
  }

}



void hscrl7(void) {}








void hscal(void) {
  if (!scroll_stop) {
    hscrltbl[stagenm]();
  }

}







void colchg0(void) {
  unsigned short d0, d1, d5, d6, d7;
  PALETTEENTRY* lpPeDest;
  PALETTEENTRY dummy;
  int i;

  d5 = 8;
  d6 = 0;
  d7 = 1000;
  d0 = (short)cntplus((unsigned short*)&specclchgcnt[0], d5, d6, d7);
  d0 &= 65520;
  lpPeDest = &lpcolorwk[32];
  for (i = 0; i < 16; ++i) {
    d1 = cltbl[d0++];
    if (d1 > 16) d1 <<= 4;

    if (i == 0) d1 = 0;
    dummy.peRed = (d1 & 15) << 4;
    dummy.peGreen = d1 & 240;
    dummy.peBlue = (d1 & 3840) >> 4;
    dummy.peFlags = 1;
    *lpPeDest++ = dummy;
  }
}


void colchg1(void) {
  short d0;
  PALETTEENTRY* lpPeDest;
  PALETTEENTRY cltbl[8] = {
    { 0, 0, 224, 1 }, { 0, 96, 224, 1 }, { 96, 160, 224, 1 }, { 160, 192, 224, 1 },
    { 0, 0, 224, 1 }, { 0, 96, 224, 1 }, { 96, 160, 224, 1 }, { 160, 192, 224, 1 }
  };
  int i;

  d0 = specclchgcnt[0]++ & 3;
  lpPeDest = &lpcolorwk[26];

  for (i = 0; i < 4; ++i) {
    lpPeDest->peRed = cltbl[d0 + i].peRed;
    lpPeDest->peGreen = cltbl[d0 + i].peGreen;
    lpPeDest->peBlue = cltbl[d0 + i].peBlue;
  }








}

void colchg2(void) {
  unsigned short d0, d5, d6, d7;
  PALETTEENTRY* lpPeDest;
  PALETTEENTRY cltbl0[24] = {
    {  0,   0, 224, 1 }, { 32,  64, 224, 1 }, { 64, 128, 224, 1 }, { 64, 192, 224, 1 },
    { 32,  64, 224, 1 }, {  0,   0, 224, 1 }, { 64, 192, 224, 1 }, { 64, 128, 224, 1 },
    { 64, 128, 224, 1 }, { 32,  64, 224, 1 }, { 64, 128, 224, 1 }, { 32,  64, 224, 1 },
    { 64, 192, 224, 1 }, { 64, 128, 224, 1 }, { 32,  64, 224, 1 }, {  0,   0, 224, 1 },
    { 64, 128, 224, 1 }, { 64, 192, 224, 1 }, {  0,   0, 224, 1 }, { 32,  64, 224, 1 },
    { 32,  64, 224, 1 }, { 64, 128, 224, 1 }, { 32,  64, 224, 1 }, { 64, 128, 224, 1 }
  };
  PALETTEENTRY cltbl1[6] = {
    { 0, 0, 224, 1 }, { 96, 192, 224, 1 }, {  0, 128, 224, 1 },
    { 0, 0, 224, 1 }, {  0, 128, 224, 1 }, { 96, 192, 224, 1 }
  };
  d5 = 2;
  d6 = 0;
  d7 = 46;
  d0 = (short)cntplus((unsigned short*)&specclchgcnt[0], d5, d6, d7);
  d0 &= 65528;
  d0 >>= 1;
  lpPeDest = &lpcolorwk[26];
  *lpPeDest++ = cltbl0[d0];
  *lpPeDest++ = cltbl0[d0 + 1];
  *lpPeDest++ = cltbl0[d0 + 2];
  *lpPeDest = cltbl0[d0 + 3];

  d5 = 1;
  d6 = 0;
  d7 = 4;
  d0 = (short)cntplus((unsigned short*)&specclchgcnt[1], d5, d6, d7);
  if (d0 >> 1 != 0) return;
  d5 = 2;
  d6 = 0;
  d7 = 10;
  d0 = (short)cntplus((unsigned short*)&specclchgcnt[2], d5, d6, d7);
  d0 >>= 1;
  lpPeDest = &lpcolorwk[33];
  *lpPeDest = cltbl1[d0];
}

void colchg3(void) {
  short d0, d5, d6, d7;
  PALETTEENTRY* lpPeDest;
  PALETTEENTRY cltbl0[16] = {
    {  0,  32, 224, 1 }, { 32,  64, 224, 1 }, { 64, 128, 224, 1 }, { 64, 192, 224, 1 },
    { 64, 192, 224, 1 }, {  0,  32, 224, 1 }, { 32,  64, 224, 1 }, { 64, 128, 224, 1 },
    { 64, 128, 224, 1 }, { 64, 192, 224, 1 }, {  0,  32, 224, 1 }, { 32,  64, 224, 1 },
    { 32,  64, 224, 1 }, { 64, 128, 224, 1 }, { 64, 192, 224, 1 }, {  0,  32, 224, 1 }
  };
  PALETTEENTRY cltbl1[8] = {
    {  96, 192, 224, 1 }, { 128, 224, 224, 1 }, { 160, 224, 224, 1 }, { 192, 224, 224, 1 },
    { 224, 224, 224, 1 }, { 192, 224, 224, 1 }, { 160, 224, 224, 1 }, { 128, 224, 224, 1 }
  };
  d0 = specclchgcnt[0];
  specclchgcnt[0] += 2;
  d0 &= 24;
  d0 >>= 1;
  lpPeDest = &lpcolorwk[26];
  *lpPeDest++ = cltbl0[d0];
  *lpPeDest++ = cltbl0[d0 + 1];
  *lpPeDest++ = cltbl0[d0 + 2];
  *lpPeDest = cltbl0[d0 + 3];

  d5 = 1;
  d6 = 0;
  d7 = 2;
  d0 = (short)cntplus((unsigned short*)&specclchgcnt[0], (unsigned short)d5, (unsigned short)d6, (unsigned short)d7);
  if (d0) return;

  d0 = specclchgcnt[2];
  specclchgcnt[2] += 2;
  d0 &= 14;
  d0 >>= 1;

  lpPeDest = &lpcolorwk[40];
  *lpPeDest++ = cltbl1[d0];
}

void colchg4(void) {
  PALETTEENTRY tbl0[7] = {
    { 0,  32, 224, 1 }, { 0,  64, 224, 1 }, { 0, 96, 224, 1 }, { 0, 128, 224, 1 },
    { 0, 160, 224, 1 }, { 0, 128, 224, 1 }, { 0, 96, 224, 1 }
  };
  PALETTEENTRY tbl1[26] = {
    { 224, 224,   0, 1 }, { 192, 224,   0, 1 }, { 160, 224,   0, 1 }, { 128, 224,   0, 1 },
    {  96, 224,   0, 1 }, {  64, 224,   0, 1 }, {  32, 224,   0, 1 }, {   0, 224,  32, 1 },
    {   0, 224,  64, 1 }, {   0, 224,  96, 1 }, {   0, 224, 128, 1 }, {   0, 224, 160, 1 },
    {   0, 224, 192, 1 }, {   0, 224, 224, 1 }, {   0, 224, 192, 1 }, {   0, 224, 160, 1 },
    {   0, 224, 128, 1 }, {   0, 224,  96, 1 }, {   0, 224,  64, 1 }, {   0, 224,  32, 1 },
    {  32, 224,   0, 1 }, {  64, 224,   0, 1 }, {  96, 224,   0, 1 }, { 128, 224,   0, 1 },
    { 160, 224,   0, 1 }, { 192, 224,   0, 1 }
  };
  PALETTEENTRY tbl2[26] = {
    {   0, 224, 224, 1 }, {   0, 224, 192, 1 }, {   0, 224, 160, 1 }, {   0, 224, 128, 1 },
    {   0, 224,  96, 1 }, {   0, 224,  64, 1 }, {   0, 224,  32, 1 }, {  32, 224,   0, 1 },
    {  64, 224,   0, 1 }, {  96, 224,   0, 1 }, { 128, 224,   0, 1 }, { 160, 224,   0, 1 },
    { 192, 224,   0, 1 }, { 224, 224,   0, 1 }, { 192, 224,   0, 1 }, { 160, 224,   0, 1 },
    { 128, 224,   0, 1 }, {  96, 224,   0, 1 }, {  64, 224,   0, 1 }, {  32, 224,   0, 1 },
    {   0, 224,  32, 1 }, {   0, 224,  64, 1 }, {   0, 224,  96, 1 }, {   0, 224, 128, 1 },
    {   0, 224, 160, 1 }, {   0, 224, 192, 1 }
  };
  PALETTEENTRY tbl3[28] = {
    { 224, 0, 0, 1 }, { 192, 0, 0, 1 }, { 160, 0, 0, 1 }, { 128, 0, 0, 1 },
    { 96, 0, 0, 1 }, { 64, 0, 0, 1 }, { 32, 0, 0, 1 }, { 0, 0, 0, 1 },
    { 32, 0, 0, 1 }, { 64, 0, 0, 1 }, { 96, 0, 0, 1 }, { 128, 0, 0, 1 },
    { 160, 0, 0, 1 }, { 192, 0, 0, 1 }, { 224, 0, 0, 1 }, { 192, 0, 0, 1 },
    { 160, 0, 0, 1 }, { 128, 0, 0, 1 }, { 96, 0, 0, 1 }, { 64, 0, 0, 1 },
    { 32, 0, 0, 1 }, { 0, 0, 0, 1 }, { 32, 0, 0, 1 }, { 64, 0, 0, 1 },
    { 96, 0, 0, 1 }, { 128, 0, 0, 1 }, { 160, 0, 0, 1 }, { 192, 0, 0, 1 }
  };
  unsigned short d0, d5, d6, d7;
  PALETTEENTRY* lpPeDest;

  d5 = 2;
  d6 = 0;
  d7 = 12;
  d0 = (short)cntplus((unsigned short*)&specclchgcnt[0], d5, d6, d7);
  d0 >>= 1;
  lpPeDest = &lpcolorwk[26];
  *lpPeDest = tbl0[d0];

  d5 = 2;
  d6 = 0;
  d7 = 50;
  d0 = (short)cntplus((unsigned short*)&specclchgcnt[1], d5, d6, d7);
  d0 >>= 1;
  lpPeDest = &lpcolorwk[45];
  *lpPeDest = tbl1[d0];

  d5 = 1;
  d6 = 0;
  d7 = 51;
  d0 = (short)cntplus((unsigned short*)&specclchgcnt[2], d5, d6, d7);
  d0 >>= 1;
  lpPeDest = &lpcolorwk[46];
  *lpPeDest = tbl2[d0];

  d5 = 1;
  d6 = 0;
  d7 = 55;
  d0 = (short)(cntplus((unsigned short*)&specclchgcnt[3], d5, d6, d7) & 65534);
  d0 >>= 1;
  lpPeDest = &lpcolorwk[47];
  *lpPeDest = tbl3[d0];
}

void colchg5(void) {
  unsigned short d0, d5, d6, d7;
  PALETTEENTRY* lpPeDest;
  short i;
  static PALETTEENTRY tbl0[26] = {
    { 224,  64,   0, 1 }, { 224, 128,   0, 1 }, { 224, 192,   0, 1 }, { 160, 224,  64, 1 },
    { 128, 224, 128, 1 }, {  64, 224, 192, 1 }, {  64, 160, 224, 1 }, { 128,  96, 224, 1 },
    { 160,   0, 224, 1 }, { 224,  32, 224, 1 }, { 224,   0, 160, 1 }, { 224,   0,  96, 1 },
    { 224,   0,  32, 1 }, { 224,  64,   0, 1 }, { 224, 128,   0, 1 }, { 224, 192,   0, 1 },
    { 160, 224,  64, 1 }, { 128, 224, 128, 1 }, {  64, 224, 192, 1 }, {  64, 160, 224, 1 },
    { 128,  96, 224, 1 }, { 160,   0, 224, 1 }, { 224,  32, 224, 1 }, { 224,   0, 160, 1 },
    { 224,   0,  96, 1 }, { 224,   0,  32, 1 }
  };
  static PALETTEENTRY tbl1[12] = {
    {  0,  0, 224, 1 }, { 64, 0, 32, 1 }, {  0, 32, 224, 1 }, { 96, 0, 64, 1 },
    { 32, 64, 224, 1 }, { 64, 0, 32, 1 }, { 64, 96, 224, 1 }, { 32, 0, 0, 1 },
    { 32, 64, 224, 1 }, {  0, 0,  0, 1 }, {  0, 32, 224, 1 }, { 32, 0, 0, 1 }
  };

  d5 = 2;
  d6 = 0;
  d7 = 24;
  d0 = (short)(cntplus((unsigned short*)&specclchgcnt[0], d5, d6, d7) & 65534);

  d0 >>= 1;
  lpPeDest = &lpcolorwk[33];

  for (i = 0; i < 12; ++i) {
    *lpPeDest++ = tbl0[d0++];
  }
  d5 = 2;
  d6 = 0;
  d7 = 22;
  d0 = (short)(cntplus((unsigned short*)&specclchgcnt[1], d5, d6, d7) & 65532);
  d0 >>= 1;
  lpPeDest = &lpcolorwk[29];
  *lpPeDest++ = tbl1[d0++];
  *lpPeDest = tbl1[d0];
}



void colchg6(void) {
  PALETTEENTRY tbl[12] = {
    { 0, 32, 192, 1 }, { 0, 32, 192, 1 }, { 0,  64, 224, 1 }, { 0,  64, 224, 1 },
    { 0, 96, 224, 1 }, { 0, 96, 224, 1 }, { 0, 128, 224, 1 }, { 0, 128, 224, 1 },
    { 0, 96, 224, 1 }, { 0, 96, 224, 1 }, { 0,  64, 224, 1 }, { 0,  64, 224, 1 }
  };
  unsigned short d0, d5, d6, d7;
  PALETTEENTRY* lpPeDest;

  d5 = 1;
  d6 = 0;
  d7 = 23;
  d0 = (short)(cntplus((unsigned short*)&specclchgcnt[0], d5, d6, d7) & 65534);
  d0 >>= 1;
  lpPeDest = &lpcolorwk[31];
  *lpPeDest = tbl[d0];
}



void colchg7(void) {}

void color_change(void) {
  void(*jptbl[8])(void) = {
    &colchg0, &colchg1, &colchg2, &colchg3, &colchg4, &colchg5, &colchg6, colchg7
  };

  jptbl[stagenm]();
}
