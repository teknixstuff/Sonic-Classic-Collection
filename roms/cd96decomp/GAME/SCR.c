#include "EQU.h"
#include "SCR.h"
#include <string.h>
#include "../services.h"
#include "COL.h"
#include "ETC.h"
#include "SAVE.h"
#include "SCRCHK.h"

#define STAGE_IS_R11A (stageno_i.w == 0x0000 && (time_flag_i & 0x7F) == 1)
#define STAGE_IS_R12A (stageno_i.w == 0x0001 && (time_flag_i & 0x7F) == 1)
#define STAGE_IS_R12B (stageno_i.w == 0x0001 && (time_flag_i & 0x7F) == 0)
#define STAGE_IS_R12C (stageno_i.w == 0x0001 && (time_flag_i & 0x7F) == 0 && generate_flag != 0)
#define STAGE_IS_R12D (stageno_i.w == 0x0001 && (time_flag_i & 0x7F) == 0 && generate_flag == 0)
#define STAGE_IS_R13C (stageno_i.w == 0x0002 && (time_flag_i & 0x7F) == 2 && generate_flag != 0)
#define STAGE_IS_R13D (stageno_i.w == 0x0002 && (time_flag_i & 0x7F) == 2 && generate_flag == 0)
#define STAGE_IS_R31B (stageno_i.w == 0x0100 && (time_flag_i & 0x7F) == 0)
#define STAGE_IS_R32B (stageno_i.w == 0x0101 && (time_flag_i & 0x7F) == 0)
#define STAGE_IS_R41A (stageno_i.w == 0x0200 && (time_flag_i & 0x7F) == 1)
#define STAGE_IS_R43C (stageno_i.w == 0x0202 && (time_flag_i & 0x7F) == 2 && generate_flag != 0)
#define STAGE_IS_R51A (stageno_i.w == 0x0300 && (time_flag_i & 0x7F) == 1)
#define STAGE_IS_R51B (stageno_i.w == 0x0300 && (time_flag_i & 0x7F) == 0)
#define STAGE_IS_R53C (stageno_i.w == 0x0302 && (time_flag_i & 0x7F) == 2 && generate_flag != 0)
#define STAGE_IS_R62A (stageno_i.w == 0x0401 && (time_flag_i & 0x7F) == 1)
#define STAGE_IS_R82A (stageno_i.w == 0x0601 && (time_flag_i & 0x7F) == 1)

extern unsigned char awasintbl[];
extern unsigned char* mapwkas[7][3][4];
extern unsigned char* mapwkbs[7][3][4];
extern map_init_data* mapinittbls[7][3][4];
extern unsigned char** zmaptbls[2][3];

static void enecginit(void);
static void playposiset(void);
static void z11ascrbinit(short xwk, short ywk);
static void z11bscrbinit(short xwk, short ywk);
static void z11cscrbinit(short xwk, short ywk);
static void z12ascrbinit(short xwk, short ywk);
static void z12bscrbinit(short xwk, short ywk);
static void z12cscrbinit(short xwk, short ywk);
static void z13cscrbinit(short xwk, short ywk);
static void z3scrbinit(short xwk, short ywk);
static void z4scrbinit(short xwk, short ywk);
static void z5ascrbinit(short sXpos, short sYpos);
static void z5bscrbinit(short sXpos, short sYpos);
static void z5cscrbinit(short sXpos, short sYpos);
static void z5dscrbinit(short sXpos, short sYpos);
static void z6scrbinit(short sXpos, short sYpos);
static void z7scrbinit(short ywk, short xwk);
static void z8scrbinit(short sXpos, short sYpos);
static void z11ascroll(void);
static void z11bscroll(void);
static void z11cscroll(void);
static void z11dscroll(void);
static void z12ascroll(void);
static void z12bscroll(void);
static void z12cscroll(void);
static void z12dscroll(void);
static void z13cscroll(void);
static void z13dscroll(void);
static void z31ascroll(void);
static void z31bscroll(void);
static void z31cscroll(void);
static void z31dscroll(void);
static void z32ascroll(void);
static void z32bscroll(void);
static void z32cscroll(void);
static void z32dscroll(void);
static void z33cscroll(void);
static void z33dscroll(void);
static void z4scroll(void);
static void z41ascroll(void);
static void z5ascroll(void);
static void z5bscroll(void);
static void z5cscroll(void);
static void z5dscroll(void);
static void z53cscroll(void);
static void z53dscroll(void);
static void z6scroll(void);
static void z7scroll(void);
static void z81scroll(void);
static void z82scroll(void);
static void z82bscroll(void);
static void z82cscroll(void);
static void z83cscroll(void);
static void z83dscroll(void);
static int z41aline(int hsCount);
static void z5aline0(short** ppHscw);
static void z5aline1(short** ppHscw);
static void z5aline2(short** ppHscw);
static void z5aline3(short** ppHscw);
static void z5bline0(short** ppHscw);
static void z5bline1(short** ppHscw);
static void z5bline2(short** ppHscw);
static void z5bline3(short** ppHscw);
static void z5cline(short** ppHscw);
static void z5dline(short** ppHscw);
static void z5dline0(short** ppHscw);
static void z6line(short** ppHscw);
static int z7line(int hsCount);
static int z7line0(int hsCount);
static int z7line1(int hsCount);
static void z81line(short** ppHscw, char* pScrTbl, short AddrOffs, short LoopNum);
static void z82line0(short** ppHscw);
static void z82line1(short** ppHscw);
static void z83cline0(short** ppHscw);
static void z83cline1(short** ppHscw);
static void line_div(int hWk1, int* hWk2, short sD6);
static void zone1scrsetsub0(short yoffs, short yline, int_union** pHscrbuf, short* pHscrwk);
static void zone3scrsetsub0(int_union** ppA1, unsigned short** ppA2, unsigned short* pA3, unsigned char* pA4, unsigned short wD1, unsigned short* pwD2, unsigned short* pwD4);
static void zone4scrsetsub0(short HPosi, short VPosi, unsigned short offs);
static void zone5scrsetsub0(short yoffs, short yline, int_union** pHscrbuf, short* pHscrwk);
static void zone6scrsetsub0(short yoffs, short yline, int_union** pHscrbuf, short* pHscrwk);
static void zone7scrsetsub0(short VPosi, unsigned short offs);
static void zone8scrsetsub0(short yoffs, short yline, int_union** pHscrbuf, short* pHscrwk);
static void scroll_h(void);
static void scrh_move(void);
static void scroll_v(void);
static void sv_move_main(short yPos);
static void sv_move_main2(short yPos);
static void sv_move_sub(short yPos);
static void sv_move_sub2(void);
static void sv_move_minus(short speed);
static void scrv_up_ch(int_union lSpd);
static void sv_move_plus(short sSpd);
static void scrv_down_ch(int_union lSpd);
static void scrv_move(int_union lSpd);
static void scrollb_hv(int xOffs, int yOffs);
static void scrollb_h(int lD4, int flagb);
static void scrollb_v(short wD0);
static void scrollc_h(int xoffs, int flagc);
static void scrollz_h(int xoffs, int flagz);
static void scrollwrtb(unsigned char* pScrFlag, unsigned char* pMapWk, int VramBase);
static void z4scrollwrtb(unsigned char* pScrFlag, unsigned char* pMapWk, int VramBase, unsigned short wH_posiw, unsigned short wV_posiw);
static void hblockwrt(POINT* pTilePoint, int VramBase, unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int lpcnt);
static void hblockwrt1(POINT* pTilePoint, int VramBase, unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int lpcnt);
static void vblockwrt(POINT* pTilePoint, int VramBase, unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int lpcnt);
static void blockwrt(int VramBase, POINT* pTilePoint, int BlkIndex);
static int mapadrset(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int* pIndex);
static int mapadrset1(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int* pIndex);
static int mapadrset99(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int* pIndex);
static int mapadrset2(unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int* pIndex, unsigned short** ppBlockNo);
static int block_chk(unsigned short xOffs, unsigned short yOffs);
static int z3_block_chk(unsigned short xOffs, unsigned short yOffs);
static int z83_block_chk(unsigned short xOffs, unsigned short yOffs);
static void vramadrset(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint);
static void vramadrset0(unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint);
static void vramadrset1(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint);
static void vramadrset2(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint);
static void vramadrset99(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint);
static void mapwrt2(unsigned short wH_posiw, unsigned short wV_posiw, unsigned char* pMapWk, int VramBase);
static void mapwrt3(unsigned short wH_posiw, unsigned short wV_posiw, unsigned char* pMapWk, int VramBase, unsigned short wD4, unsigned short wD6);
static void mapwrt_z(unsigned char* pMapWk, int VramBase);
static void mapwrt_z41a(unsigned char* pMapWk, int VramBase);
static void mapwrt_sub(unsigned char* pWrttbl, unsigned short wD0, unsigned short wD4, unsigned char* pMapWk, int VramBase);
static void mapset(void);
static void mapset2(unsigned char* pMapDst, int idx);

static unsigned char z11awrttbl[129] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z11bwrttbl[33] = { 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
static unsigned char z11cwrttbl[33] = { 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 2, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z11dwrttbl[33] = { 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 2, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z12awrttbl[33] = { 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z12bwrttbl[33] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z12cwrttbl[33] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 2, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z31awrttbl[49] = { 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 6, 6, 4, 4, 4, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z31bwrttbl[49] = { 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 6, 6, 4, 4, 4, 4, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z31dwrttbl[49] = { 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 6, 6, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z32awrttbl[49] = { 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 6, 6, 4, 4, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z32bwrttbl[49] = { 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 6, 6, 4, 4, 4, 4, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z33cwrttbl[49] = { 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 6, 6, 4, 4, 4, 4, 4, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z33dwrttbl[49] = { 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z4wrttbl[129] = { 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
static unsigned char z5wrttbl[65];
static unsigned char z51awrttbl[65] = { 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
static unsigned char z52awrttbl[65] = { 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z5awrttbl2[49];
static unsigned char z6awrttbl[49] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
static unsigned char z6cwrttbl[49] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
static unsigned char z61bwrttbl[49] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 6, 4, 4, 6, 6, 6, 6, 6, 6, 4, 4, 6, 6, 6, 6, 6, 6, 4, 4, 6, 6, 6, 6, 6, 6, 4, 4 };
static unsigned char z61dwrttbl[49];
static unsigned char z62bwrttbl[49] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 6, 4, 4, 6, 6, 6, 6, 6, 6, 4, 4, 6, 6, 6, 6, 6, 6, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z7awrttbl[65] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z7bwrttbl[65] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z7cwrttbl[65];
static unsigned char z7dwrttbl[65] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z81wrttbl[49] = { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4 };
static unsigned char z81bwrttbl[49] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4 };
static unsigned char z82wrttbl[33] = { 0, 2, 2, 2, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2 };
static unsigned char z82bwrttbl[33];
static unsigned char z82cwrttbl[33] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4 };
static unsigned char z83cwrttbl[33] = { 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned char z83dwrttbl[33] = { 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
static unsigned char* wrttbls[7][3][4] = {
  {
    { z11bwrttbl, z11awrttbl, z11dwrttbl, z11cwrttbl },
    { z12bwrttbl, z12awrttbl, z11dwrttbl, z12cwrttbl },
    { 0, 0, z11dwrttbl, z12cwrttbl }
  },
  {
    { z31bwrttbl, z31awrttbl, z31dwrttbl, z31awrttbl },
    { z32bwrttbl, z32awrttbl, z31dwrttbl, z32awrttbl },
    { 0, 0, z33dwrttbl, z33cwrttbl }
  },
  {
    { z4wrttbl, z4wrttbl, z4wrttbl, z4wrttbl },
    { z4wrttbl, z4wrttbl, z4wrttbl, z4wrttbl},
    { 0, 0, z4wrttbl, z4wrttbl}
  },
  {
    { z5wrttbl, z51awrttbl, z5wrttbl, z5wrttbl },
    { z5wrttbl, z52awrttbl, z5wrttbl, z5wrttbl },
    { 0, 0, z5wrttbl, z5wrttbl }
  },
  {
    { z61bwrttbl, z6awrttbl, z61dwrttbl, z6cwrttbl },
    { z62bwrttbl, z6awrttbl, z6cwrttbl, z6cwrttbl },
    { 0, 0, z6cwrttbl, z6cwrttbl }
  },
  {
    { z7bwrttbl, z7awrttbl, z7dwrttbl, z7cwrttbl },
    { z7bwrttbl, z7awrttbl, z7dwrttbl, z7cwrttbl },
    { 0, 0, z7dwrttbl, z7cwrttbl }
  },
  {
    { z81bwrttbl, z81wrttbl, z81wrttbl, z81wrttbl },
    { z82bwrttbl, z82wrttbl, z82wrttbl, z82cwrttbl },
    { 0, 0, z83dwrttbl, z83cwrttbl }
  }
};
static int_union* vblockwrtbtbl[8] = {
  &scrb_h_posiw,
  &scrb_v_posiw,
  &scrb_h_posiw,
  &scrb_v_posiw,
  &scrc_h_posiw,
  &scrc_v_posiw,
  &scrz_h_posiw,
  &scrz_v_posiw
};
static int_union* mapwrt_tbl[8] = {
  &scrb_h_posiw,
  &scrb_v_posiw,
  &scrb_h_posiw,
  &scrb_v_posiw,
  &scrc_h_posiw,
  &scrc_v_posiw,
  &scrz_h_posiw,
  &scrz_v_posiw
};
unsigned short z1_scr_dir_tbl[6] = { 4, 0, 10391, 0, 784, 96 };
unsigned short z11a_scr_dir_tbl[6] = { 4, 0, 10391, 0, 1808, 96 };
unsigned short z13c_scr_dir_tbl[6] = { 4, 0, 3479, 0, 784, 96 };
unsigned short z31_scr_dir_tbl[6] = { 4, 0, 11927, 0, 1296, 96 };
unsigned short z32_scr_dir_tbl[6] = { 4, 0, 9879, 0, 1296, 96 };
unsigned short z33_scr_dir_tbl[6] = { 4, 0, 1175, 48, 1296, 96 };
unsigned short z41_scr_dir_tbl[6] = { 4, 0, 7319, 0, 1296, 96 };
unsigned short z42_scr_dir_tbl[6] = { 4, 0, 7319, 0, 2048, 96 };
unsigned short z43_scr_dir_tbl[6] = { 4, 0, 3479, 0, 2048, 96 };
unsigned short z5_scr_dir_tbl[6] = { 4, 0, 10903, 0, 784, 96 };
unsigned short z52a_scr_dir_tbl[6] = { 4, 0, 10903, 0, 800, 96 };
unsigned short z53_scr_dir_tbl[6] = { 4, 0, 3735, 0, 800, 96 };
unsigned short z61_scr_dir_tbl[6] = { 4, 0, 8855, 0, 1808, 96 };
unsigned short z62_scr_dir_tbl[6] = { 4, 0, 9111, 0, 1808, 96 };
unsigned short z63_scr_dir_tbl[6] = { 4, 0, 3479, 0, 1808, 96 };
unsigned short z7_scr_dir_tbl[6] = { 4, 0, 11927, 0, 1296, 96 };
unsigned short z72a_scr_dir_tbl[6] = { 4, 0, 11927, 0, 1808, 96 };
unsigned short z73_scr_dir_tbl[6] = { 4, 0, 16023, 0, 1296, 96 };
unsigned short z8_scr_dir_tbl[6] = { 4, 0, 7831, 0, 1808, 96 };
unsigned short z83_scr_dir_tbl[6] = { 4, 0, 3735, 0, 784, 96 };
static int tile_change[4][4] = {
  { 523, 175, 168, 168 },
  { 603, 84, 114, 113 },
  { 597, 88, 96, 96 },
  { 592, 99, 95, 95 }
};


static void enecginit(void) {}


void divdevset(int param) {}


void enkeichg(void) {
  short z51tbl[9] = {
    3584, 8960, -1,
    3584, 8960, -1,
    3584, 8960, -1
  };
  short z52tbl[6] = {
    3584, 7168, -1,
    3584, 8960, -1
  };
  short* tbls[2] = {
    z51tbl,
    z52tbl
  };
  char tbl0[3] = {
    2, 4, 2
  };
  int EnkeiNo, TileNo, BmpNo, i;
  short *pTbl, poswk;

  if (scrflaga.b.h) return;

  EnkeiNo = 0;
  pTbl = tbls[stageno_i.b.l];

  while ((poswk = *pTbl++) >= 0) {
    if (actwk[0].xposi.w.h <= poswk) break;

    ++EnkeiNo;
  }

  if (enkeino == EnkeiNo) return;

  enkeino = EnkeiNo;

  TileNo = tile_change[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][0];
  if (EnkeiNo == 1) {
    i = tile_change[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1];
    BmpNo = tile_change[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][2];
  } else {
    i = tile_change[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][3];
    BmpNo = 0;
  }
  for ( ; i > 0; --i) {
    ChangeTileBmp(TileNo++, BmpNo++);
  }

  colorset2((tbl0[EnkeiNo] >> 2) + 4);
  colorset((tbl0[EnkeiNo] >> 2) + 4);

  mapset2(mapwkbs[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)], tbl0[EnkeiNo] / 2);
  scrbinit(scra_h_posit.w.h, scra_v_posit.w.h);
  mapwrt_cnt = 1;
}


void scr_set(void) {
  unsigned short* scr_dir_tbls[7][3][3] = {
    {
      { z1_scr_dir_tbl, z11a_scr_dir_tbl, z1_scr_dir_tbl },
      { z1_scr_dir_tbl, z1_scr_dir_tbl, z1_scr_dir_tbl },
      { 0, 0, z13c_scr_dir_tbl }
    },
    {
      { z31_scr_dir_tbl, z31_scr_dir_tbl, z31_scr_dir_tbl },
      { z32_scr_dir_tbl, z32_scr_dir_tbl, z32_scr_dir_tbl },
      { 0, 0, z33_scr_dir_tbl }
    },
    {
      { z41_scr_dir_tbl, z41_scr_dir_tbl, z41_scr_dir_tbl },
      { z42_scr_dir_tbl, z42_scr_dir_tbl, z42_scr_dir_tbl },
      { 0, 0, z43_scr_dir_tbl }
    },
    {
      { z5_scr_dir_tbl, z5_scr_dir_tbl, z5_scr_dir_tbl },
      { z5_scr_dir_tbl, z52a_scr_dir_tbl, z5_scr_dir_tbl },
      { 0, 0, z53_scr_dir_tbl }
    },
    {
      { z61_scr_dir_tbl, z61_scr_dir_tbl, z61_scr_dir_tbl },
      { z62_scr_dir_tbl, z62_scr_dir_tbl, z62_scr_dir_tbl },
      { 0, 0, z63_scr_dir_tbl }
    },
    {
      { z7_scr_dir_tbl, z7_scr_dir_tbl, z7_scr_dir_tbl },
      { z7_scr_dir_tbl, z72a_scr_dir_tbl, z7_scr_dir_tbl },
      { 0, 0, z73_scr_dir_tbl }
    },
    {
      { z8_scr_dir_tbl, z8_scr_dir_tbl, z8_scr_dir_tbl },
      { z8_scr_dir_tbl, z8_scr_dir_tbl, z8_scr_dir_tbl },
      { 0, 0, z83_scr_dir_tbl }
    }
  };
  unsigned short* scr_dir_tbl = scr_dir_tbls[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  int i;

  scrh_flag = scrv_flag = scr_die.b.h = scr_timer.b.h = zone_flag.b.h = 0;

  i = 0;
  scrar_no = scr_dir_tbl[i++];
  scralim_left = scralim_n_left = scr_dir_tbl[i++];
  scralim_right = scralim_n_right = scr_dir_tbl[i++];
  scralim_up = scralim_n_up = scr_dir_tbl[i++];
  scralim_down = scralim_n_down = scr_dir_tbl[i++];

  scra_h_keep = scralim_left + 576;
  if (STAGE_IS_R12B || STAGE_IS_R13C || STAGE_IS_R13D || stageno_i.b.h == 3 || stageno_i.b.h == 6) {
    scra_h_keep = scralim_down + 576;
  }
  scra_h_count = 16;
  scra_v_count = 16;

  scra_vline = scr_dir_tbl[i++];
  scra_hline = 160;

  playposiset();
}


static void playposiset(void) {
  unsigned short z11playpositbl[1][2] = { { 80, 488 } };
  unsigned short z11aplaypositbl[1][2] = { { 64, 1899 } };
  unsigned short z12playpositbl[1][2] = { { 80, 389 } };
  unsigned short z13playpositbl[1][2] = { { 64, 674 } };
  unsigned short z31playpositbl[1][2] = { { 96, 1004 } };
  unsigned short z32playpositbl[1][2] = { { 32, 428 } };
  unsigned short z33playpositbl[1][2] = { { 80, 268 } };
  unsigned short z41playpositbl[1][2] = { { 80, 64 } };
  unsigned short z42playpositbl[1][2] = { { 80, 1260 } };
  unsigned short z43playpositbl[2][2] = { { 80, 364 }, { 976, 940 } };
  unsigned short z51playpositbl[1][2] = { { 64, 620 } };
  unsigned short z52playpositbl[1][2] = { { 64, 364 } };
  unsigned short z61playpositbl[1][2] = { { 48, 1196 } };
  unsigned short z61bplaypositbl[1][2] = { { 160, 1196 } };
  unsigned short z62playpositbl[1][2] = { { 48, 412 } };
  unsigned short z63playpositbl[1][2] = { { 48, 1580 } };
  unsigned short z7playpositbl[1][2] = { { 64, 396 } };
  unsigned short z72playpositbl[1][2] = { { 64, 652 } };
  unsigned short z81playpositbl[1][2] = { { 48, 1696 } };
  unsigned short z82playpositbl[2][2] = { { 46, 1164 }, { 6942, 1484 } };
  unsigned short z83playpositbl[1][2] = { { 48, 588 } };
  unsigned short (*playpositbls[7][3][4])[2] = {
    {
      { z11playpositbl, z11aplaypositbl, z11playpositbl, z11playpositbl },
      { z12playpositbl, z12playpositbl, z12playpositbl, z12playpositbl },
      { 0, 0, z13playpositbl, z13playpositbl }
    },
    {
      { z31playpositbl, z31playpositbl, z31playpositbl, z31playpositbl },
      { z32playpositbl, z32playpositbl, z32playpositbl, z32playpositbl },
      { 0, 0, z33playpositbl, z33playpositbl }
    },
    {
      { z41playpositbl, z41playpositbl, z41playpositbl, z41playpositbl },
      { z42playpositbl, z42playpositbl, z42playpositbl, z42playpositbl },
      { 0, 0, z43playpositbl, z43playpositbl }
    },
    {
      { z51playpositbl, z51playpositbl, z51playpositbl, z51playpositbl },
      { z52playpositbl, z52playpositbl, z52playpositbl, z52playpositbl },
      { 0, 0, z51playpositbl, z51playpositbl }
    },
    {
      { z61bplaypositbl, z61playpositbl, z61playpositbl, z61playpositbl },
      { z62playpositbl, z62playpositbl, z62playpositbl, z62playpositbl },
      { 0, 0, z63playpositbl, z63playpositbl }
    },
    {
      { z7playpositbl, z7playpositbl, z7playpositbl, z7playpositbl },
      { z72playpositbl, z72playpositbl, z7playpositbl, z72playpositbl },
      { 0, 0, z7playpositbl, z7playpositbl }
    },
    {
      { z81playpositbl, z81playpositbl, z81playpositbl, z81playpositbl },
      { z82playpositbl, z82playpositbl, z82playpositbl, z82playpositbl },
      { 0, 0, z83playpositbl, z83playpositbl }
    }
  };
  unsigned short (*playpositbl)[2] = playpositbls[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
  unsigned short endplpositbl[8][2] = {
    {   80,  944 },
    { 3744, 1132 },
    { 5968,  189 },
    { 2560, 1580 },
    { 2992,   76 },
    { 5488,  364 },
    {  432, 1836 },
    { 5120,  684 }
  };
  unsigned char z11playmapnotbl[4] = { 140, 127, 30, 30 };
  unsigned char z11aplaymapnotbl[4] = { 127, 127, 127, 127 };
  unsigned char z12playmapnotbl[4] = { 145, 182, 127, 127 };
  unsigned char z13playmapnotbl[4] = { 145, 127, 30, 30 };
  unsigned char z3playmapnotbl[4] = { 127, 127, 127, 127 };
  unsigned char z4playmapnotbl[4] = { 127, 127, 127, 127 };
  unsigned char z5aplaymapnotbl[4] = { 127, 127, 21, 91 };
  unsigned char z51bplaymapnotbl[4] = { 127, 127, 9, 127 };
  unsigned char z51cplaymapnotbl[4] = { 127, 127, 98, 24 };
  unsigned char z51dplaymapnotbl[4] = { 127, 127, 24, 98 };
  unsigned char z52bplaymapnotbl[4] = { 127, 127, 21, 25 };
  unsigned char z52cplaymapnotbl[4] = { 127, 127, 21, 127 };
  unsigned char z52dplaymapnotbl[4] = { 127, 127, 127, 127 };
  unsigned char z6playmapnotbl[4] = { 127, 127, 127, 127 };
  unsigned char z7playmapnotbl[4] = { 132, 134, 127, 127 };
  unsigned char z8playmapnotbl[4] = { 127, 127, 127, 127 };
  unsigned char* playmapnotbls[7][3][4] = {
    {
      { z11playmapnotbl, z11aplaymapnotbl, z11playmapnotbl, z11playmapnotbl },
      { z12playmapnotbl, z12playmapnotbl, z12playmapnotbl, z12playmapnotbl },
      { 0, 0, z13playmapnotbl, z13playmapnotbl },
    },
    {
      { z3playmapnotbl, z3playmapnotbl, z3playmapnotbl, z3playmapnotbl },
      { z3playmapnotbl, z3playmapnotbl, z3playmapnotbl, z3playmapnotbl },
      { 0, 0, z3playmapnotbl, z3playmapnotbl }
    },
    {
      { z4playmapnotbl, z4playmapnotbl, z4playmapnotbl, z4playmapnotbl },
      { z4playmapnotbl, z4playmapnotbl, z4playmapnotbl, z4playmapnotbl },
      { 0, 0, z4playmapnotbl, z4playmapnotbl }
    },
    {
      { z51bplaymapnotbl, z5aplaymapnotbl, z51dplaymapnotbl, z51cplaymapnotbl },
      { z52bplaymapnotbl, z5aplaymapnotbl, z52dplaymapnotbl, z52cplaymapnotbl },
      { 0, 0, z52dplaymapnotbl, z52dplaymapnotbl }
    },
    {
      { z6playmapnotbl, z6playmapnotbl, z6playmapnotbl, z6playmapnotbl },
      { z6playmapnotbl, z6playmapnotbl, z6playmapnotbl, z6playmapnotbl },
      { 0, 0, z6playmapnotbl, z6playmapnotbl }
    },
    {
      { z7playmapnotbl, z7playmapnotbl, z7playmapnotbl, z7playmapnotbl },
      { z7playmapnotbl, z7playmapnotbl, z7playmapnotbl, z7playmapnotbl },
      { 0, 0, z7playmapnotbl, z7playmapnotbl }
    },
    {
      { z8playmapnotbl, z8playmapnotbl, z8playmapnotbl, z8playmapnotbl },
      { z8playmapnotbl, z8playmapnotbl, z8playmapnotbl, z8playmapnotbl },
      { 0, 0, z8playmapnotbl, z8playmapnotbl }
    }
  };
  unsigned char* playmapnotbl = playmapnotbls[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  unsigned char usedemodata[7][3][4] = {
    { { 1, 0, 1, 1 }, { 1, 1, 1, 1 }, { 0, 0, 1, 1 } },
    { { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 0, 0, 1, 1 } },
    { { 1, 0, 1, 1 }, { 1, 1, 1, 1 }, { 0, 0, 1, 1 } },
    { { 0, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 1, 1 } },
    { { 1, 1, 1, 1 }, { 1, 0, 0, 0 }, { 0, 0, 1, 1 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 1, 1, 1, 1 }, { 1, 0, 1, 1 }, { 0, 0, 0, 1 } }
  };
  short xwk, ywk;
  int i;

  if ((STAGE_IS_R43C || STAGE_IS_R82A) && demoflag.w) {
    xwk = actwk[0].xposi.w.h = playpositbl[1][0];
    ywk = actwk[0].yposi.w.h = playpositbl[1][1];
  }
  else if (plflag != 0) {
    playload();
    xwk = actwk[0].xposi.w.h;
    ywk = actwk[0].yposi.w.h;
    if (ywk < 0 && !STAGE_IS_R41A) {
      ywk = 0;
    }
  }
  else {
    xwk = actwk[0].xposi.w.h = playpositbl[0][0];
    ywk = actwk[0].yposi.w.h = playpositbl[0][1];
    if (usedemodata[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)] != 0) {
      if (demoflag.w < 0) {
        xwk = actwk[0].xposi.w.h = endplpositbl[enddemono - 1][0];
        ywk = actwk[0].yposi.w.h = endplpositbl[enddemono - 1][1];
      }
      else {
        xwk = actwk[0].xposi.w.h = playpositbl[demoflag.w][0];
        ywk = actwk[0].yposi.w.h = playpositbl[demoflag.w][1];
      }
    }
  }

  if (xwk > 160) {
    xwk -= 160;
  }
  else {
    xwk = 0;
  }

  if (xwk > scralim_right) {
    xwk = scralim_right;
  }

  scra_h_posit.w.h = xwk;

  if (ywk > 96) {
    ywk -= 96;
  }
  else {
    ywk = 0;
  }

  if (ywk > scralim_down) {
    ywk = scralim_down;
  }

  scra_v_posit.w.h = ywk;

  scrbinit(xwk, ywk);

  loopmapno = playmapnotbl[0];
  loopmapno2 = playmapnotbl[1];
  ballmapno = playmapnotbl[2];
  ballmapno2 = playmapnotbl[3];
}


void scrbinit(short xwk, short ywk) {
  static void(*scrbinits[7][3][4])(short,short) = {
    {
      { &z11bscrbinit, &z11ascrbinit, &z11cscrbinit, &z11cscrbinit },
      { &z12bscrbinit, &z12ascrbinit, &z12cscrbinit, &z12cscrbinit },
      { 0, 0, &z13cscrbinit, &z13cscrbinit }
    },
    {
      { &z3scrbinit, &z3scrbinit, &z3scrbinit, &z3scrbinit },
      { &z3scrbinit, &z3scrbinit, &z3scrbinit, &z3scrbinit },
      { 0, 0, &z3scrbinit, &z3scrbinit }
    },
    {
      { &z4scrbinit, &z4scrbinit, &z4scrbinit, &z4scrbinit },
      { &z4scrbinit, &z4scrbinit, &z4scrbinit, &z4scrbinit },
      { 0, 0, &z4scrbinit, &z4scrbinit }
    },
    {
      { &z5bscrbinit, &z5ascrbinit, &z5dscrbinit, &z5cscrbinit },
      { &z5bscrbinit, &z5ascrbinit, &z5dscrbinit, &z5cscrbinit },
      { 0, 0, &z5dscrbinit, &z5cscrbinit }
    },
    {
      { &z6scrbinit, &z6scrbinit, &z6scrbinit, &z6scrbinit },
      { &z6scrbinit, &z6scrbinit, &z6scrbinit, &z6scrbinit },
      { 0, 0, &z6scrbinit, &z6scrbinit }
    },
    {
      { &z7scrbinit, &z7scrbinit, &z7scrbinit, &z7scrbinit },
      { &z7scrbinit, &z7scrbinit, &z7scrbinit, &z7scrbinit },
      { 0, 0, &z7scrbinit, &z7scrbinit }
    },
    {
      { &z8scrbinit, &z8scrbinit, &z8scrbinit, &z8scrbinit },
      { &z8scrbinit, &z8scrbinit, &z8scrbinit, &z8scrbinit },
      { 0, 0, &z8scrbinit, &z8scrbinit }
    }
  };

  scrbinits[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)](xwk, ywk);
}


static void z11ascrbinit(short xwk, short ywk) {
  if ((unsigned short)actwk[0].xposi.w.h >= 2048) {
    if ((unsigned short)ywk >= 480) {
      ywk = (ywk - 480) / 2 + 480;
    }
  }

  scrb_v_posit.w.h = ywk;
  scrb_v_posit.w.l = 0;
  scrc_v_posit.w.h = ywk;
  scrz_v_posit.w.h = ywk;

  scrb_h_posit.w.h = (unsigned short)(xwk / 2);
  scrc_h_posit.w.h = (unsigned short)(xwk / 16 * 3);
  scrz_h_posit.w.h = (unsigned short)(xwk / 8 * 3);

  memset(linework, 0, 19);
}


static void z11bscrbinit(short xwk, short ywk) {
  int_union lYwk;

  lYwk.w.h = ywk;
  lYwk.w.l = 0;
  lYwk.l = (lYwk.l >> 4) * 2;

  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = lYwk.w.h;
  scrz_v_posit.w.h = lYwk.w.h;

  scrb_h_posit.w.h = (unsigned short)(xwk / 2);
  scrc_h_posit.w.h = (unsigned short)(xwk / 16 * 3);
  scrz_h_posit.w.h = (unsigned short)(xwk / 8);

  memset(hscrollwork, 0, 16);
}


static void z11cscrbinit(short xwk, short ywk) {
  int_union lYwk;

  lYwk.w.h = ywk;
  lYwk.w.l = 0;
  lYwk.l = (lYwk.l >> 4) * 2;

  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = (unsigned short)(ywk / 16) * 2;
  scrz_v_posit.w.h = (unsigned short)(ywk / 16) * 2;

  scrb_h_posit.w.h = (unsigned short)(xwk / 16 * 3);
  scrc_h_posit.w.h = (unsigned short)(xwk / 4);
  scrz_h_posit.w.h = (unsigned short)(xwk / 8);

  memset(hscrollwork, 0, 16);
}


static void z12ascrbinit(short xwk, short ywk) {
  int_union lYwk;

  lYwk.w.h = ywk;
  lYwk.w.l = 0;
  lYwk.l = (long int)(lYwk.l >> 4) * 3;

  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = (unsigned short)(ywk / 16) * 2;
  scrz_v_posit.w.h = (unsigned short)(ywk / 16) * 2;

  scrb_h_posit.w.h = (unsigned short)(xwk / 16 * 3);
  scrc_h_posit.w.h = (unsigned short)(xwk / 4);
  scrz_h_posit.w.h = (unsigned short)(xwk / 8);

  memset(hscrollwork, 0, 6);
}


static void z12bscrbinit(short xwk, short ywk) {
  int_union lYwk;

  lYwk.w.h = ywk;
  lYwk.w.l = 0;
  lYwk.l = (lYwk.l >> 4) * 3;

  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = lYwk.w.h;
  scrz_v_posit.w.h = lYwk.w.h;

  xwk = (unsigned short)xwk >> 1;
  scrb_h_posit.w.h = xwk;

  xwk = (unsigned short)xwk >> 2;
  scrz_h_posit.w.h = xwk;

  xwk = (unsigned short)xwk >> 1;
  scrc_h_posit.w.h = xwk * 3;

  memset(hscrollwork, 0, 32);
}


static void z12cscrbinit(short xwk, short ywk) {
  int_union lYwk;

  lYwk.w.h = ywk;
  lYwk.w.l = 0;
  if (generate_flag != 0) {
    lYwk.l = (lYwk.l >> 4) * 3;
  }
  else {
    lYwk.l = (lYwk.l >> 4) * 2;
  }

  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = (unsigned short)(ywk / 16) * 2;
  scrz_v_posit.w.h = (unsigned short)(ywk / 16) * 2;

  scrb_h_posit.w.h = (unsigned short)(xwk / 8);
  scrc_h_posit.w.h = (unsigned short)(xwk / 16 * 3);
  scrz_h_posit.w.h = (unsigned short)(xwk / 32 * 3);

  if (generate_flag != 0) {
    memset(hscrollwork, 0, 20);
  }
  else {
    memset(hscrollwork, 0, 16);
  }
}


static void z13cscrbinit(short xwk, short ywk) {
  int_union lYwk;

  lYwk.w.h = ywk;
  lYwk.w.l = 0;
  lYwk.l = (lYwk.l >> 4) * 3;

  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = lYwk.w.h;
  scrz_v_posit.w.h = lYwk.w.h;

  xwk >>= 3;
  scrb_h_posit.w.h = xwk;

  xwk >>= 1;
  scrc_h_posit.w.h = xwk * 3;

  xwk >>= 1;
  scrz_h_posit.w.h = xwk * 3;

  if (generate_flag != 0) {
    memset(hscrollwork, 0, 20);
  }
  else {
    memset(hscrollwork, 0, 16);
  }
}


static void z3scrbinit(short xwk, short ywk) {
  int i;
  short wD2;
  int cnts[3][4] = {
    { 13, 15, 15, 14 },
    { 10, 14, 16, 14 },
    { 0, 0, 12, 12 }
  };

  ywk = 536;
  wD2 = 1312 - scra_v_posit.w.h;
  if ((unsigned short)scra_v_posit.w.h <= 1312) {
    ywk -= wD2 / 2;
    if (ywk < 0) {
      ywk = 0;
    }
  }

  scrb_v_posit.w.h = ywk;
  scrb_v_posit.w.l = 0;
  scrc_v_posit.w.h = ywk;
  scrz_v_posit.w.h = ywk;

  scrz_h_posit.w.h = (unsigned short)(xwk / 16);
  scrc_h_posit.w.h = (unsigned short)(xwk / 32 * 3);
  scrb_h_posit.w.h = (unsigned short)(xwk / 64 * 3);

  for (i = 0; i < cnts[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)]; ++i) {
    ((int*)hscrollwork)[i] = 0;
  }
}


static void z4scrbinit(short xwk, short ywk) {
  uint_union data;
  int i;

  data.l = 0;
  data.w.l = scra_v_posit.w.h;
  if (!STAGE_IS_R41A) {
    data.w.l >>= 1;
  }
  if (!STAGE_IS_R41A || (unsigned short)scra_v_posit.w.h < 512) {
    if (STAGE_IS_R41A && (unsigned short)scra_h_posit.w.h >= 640) {
      data.w.l = 512;
    }
    scrb_v_posit.w.h = data.w.l;
    scrb_v_posit.w.l = 0;
  }
  else {
    data.w.l -= 512;
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
    data.l >>= 2;
    data.l *= 3;
    data.l += 0x2000000;
    scrb_v_posit.w.h = data.w.h;
    scrb_v_posit.w.l = data.w.l;
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
  }

  scrb_v_posit.w.h = data.w.l;
  scrb_v_posit.w.l = 0;
  scrc_v_posit.w.h = data.w.l;
  scrz_v_posit.w.h = data.w.l;

  scrz_h_posit.w.h = (unsigned short)(ywk >> 4);
  scrc_h_posit.w.h = (unsigned short)((ywk >> 5) * 3);
  scrb_h_posit.w.h = (unsigned short)((ywk >> 6) * 3);
  if (stageno_i.b.l == 0) {
    for (i = 0; i < 30; ++i) {
      hscrollwork[i] = 0;
    }
  }
}


static void z5ascrbinit(short sXpos, short sYpos) {
  int_union lYwk;

  lYwk.w.h = sYpos;
  lYwk.w.l = 0;

  if (enkeino & 1) {
    lYwk.l = (unsigned int)lYwk.l >> 2;
  } else {
    lYwk.l = (unsigned int)lYwk.l >> 1;
    if (stageno_i.b.l == 1) {
      lYwk.l += (lYwk.l >> 2) + (lYwk.l >> 3);
    }
    else {
      lYwk.l += (lYwk.l >> (lYwk.l + 2)) >> 3;
    }
  }
  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = lYwk.w.h;
  scrz_v_posit.w.h = lYwk.w.h;

  scrb_h_posit.w.h = (short)((unsigned short)sXpos >> 2) + sXpos;

  sXpos = (unsigned short)sXpos >> 1;
  scrc_h_posit.w.h = sXpos;

  sXpos >>= 1;
  scrz_h_posit.w.h = sXpos;
}


static void z5bscrbinit(short sXpos, short sYpos) {
  int_union lYwk;

  lYwk.w.h = sYpos;
  lYwk.w.l = 0;

  lYwk.l = (unsigned int)lYwk.l >> 3;
  lYwk.l += lYwk.l >> 1;

  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = lYwk.w.h;
  scrz_v_posit.w.h = lYwk.w.h;

  sXpos = (unsigned short)sXpos >> 1;
  scrb_h_posit.w.h = sXpos + (sXpos >> 1);

  sXpos = (unsigned short)sXpos >> 1;
  scrc_h_posit.w.h = sXpos;

  sXpos >>= 2;
  scrz_h_posit.w.h = sXpos * 3;
}


static void z5cscrbinit(short sXpos, short sYpos) {
  int_union lYwk;

  lYwk.w.h = sYpos;
  lYwk.w.l = 0;

  lYwk.l = (unsigned int)lYwk.l >> 2;

  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = lYwk.w.h;
  scrz_v_posit.w.h = lYwk.w.h;

  sXpos = (unsigned short)sXpos >> 1;
  scrb_h_posit.w.h = sXpos;

  sXpos = (unsigned short)sXpos >> 1;
  scrc_h_posit.w.h = sXpos;

  sXpos >>= 2;
  scrz_h_posit.w.h = sXpos * 3;
}


static void z5dscrbinit(short sXpos, short sYpos) {
  int_union lYwk;

  lYwk.w.h = sYpos;
  lYwk.w.l = 0;

  lYwk.l = (unsigned int)lYwk.l >> 3;
  lYwk.l += (lYwk.l >> 2) * 3;

  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = lYwk.w.h;
  scrz_v_posit.w.h = lYwk.w.h;

  sXpos = (unsigned short)sXpos >> 1;
  scrb_h_posit.w.h = sXpos;

  sXpos = (unsigned short)sXpos >> 1;
  scrc_h_posit.w.h = sXpos;

  sXpos >>= 1;
  scrz_h_posit.w.h = sXpos;
}


static void z6scrbinit(short sXpos, short sYpos) {
  int_union lYwk;

  lYwk.w.h = sYpos;
  lYwk.w.l = 0;

  lYwk.l = (unsigned int)lYwk.l >> 2;
  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = lYwk.w.h;
  scrz_v_posit.w.h = lYwk.w.h;

  sXpos = (unsigned short)sXpos >> 1;
  scrc_h_posit.w.h = sXpos;

  sXpos = (unsigned short)sXpos >> 1;
  scrz_h_posit.w.h = sXpos;

  sXpos = (unsigned short)sXpos >> 2;
  scrb_h_posit.w.h = sXpos * 3;
}


static void z7scrbinit(short ywk, short xwk) {
  uint_union data;

  data.l = 0;
  data.w.h = ywk;
  if (stageno_i.b.l == 0) {
    data.l = (data.l >> 2) + (data.l >> 3);
  }
  else if (stageno_i.b.l == 1) {
    data.l = (data.l >> 2) + (data.l >> 5);
  }
  scrb_v_posit.l = data.w.l;
  if (stageno_i.b.l == 2) {
    scrc_v_posit.w.h = data.w.l;
    scrz_v_posit.w.h = data.w.l;
  }
  else {
    scrc_v_posit.w.h = data.w.h;
    scrz_v_posit.w.h = data.w.h;
  }

  if (stageno_i.b.l == 2) {
    if (generate_flag != 0) {
      scrc_h_posit.w.h = (unsigned short)((xwk >> 1) + (xwk >> 2));
      scrz_h_posit.w.h = (unsigned short)(xwk >> 1);
    }
    else {
      scrc_h_posit.w.h = (unsigned short)((xwk >> 2) + (xwk >> 4));
      scrz_h_posit.w.h = (unsigned short)((xwk >> 3) + (xwk >> 4) + (xwk >> 5));
    }
  }
  else {
    scrc_h_posit.w.h = (unsigned short)(xwk >> 1);
    if ((time_flag_i & 0x7F) == 1) {
      scrz_h_posit.w.h = (unsigned short)(xwk >> 2);
    }
    else {
      scrz_h_posit.w.h = (unsigned short)((xwk >> 2) + (xwk >> 3));
    }
  }
  scrb_h_posit.w.h = (unsigned short)((xwk >> 4) * 3);
}


static void z8scrbinit(short sXpos, short sYpos) {
  int_union lYwk;

  lYwk.w.h = sYpos;
  lYwk.w.l = 0;

  if (stageno_i.b.l == 0) {
    lYwk.l = (unsigned int)lYwk.l >> 2;
  }
  else {
    lYwk.l = (unsigned int)lYwk.l >> 3;
  }
  scrb_v_posit.l = lYwk.l;
  scrc_v_posit.w.h = lYwk.w.h;
  scrz_v_posit.w.h = lYwk.w.h;

  if (stageno_i.b.l == 2 && generate_flag == 0) {
    scrc_h_posit.w.h = sXpos + 112;
  }
  else {
    sXpos = (unsigned short)sXpos >> 1;
    scrc_h_posit.w.h = sXpos;
  }

  if (stageno_i.b.l == 2) {
    if (generate_flag != 0) {
      scrz_h_posit.w.h = sXpos + 112;
    }
    else {
      sXpos = (unsigned short)sXpos >> 2;
      scrz_h_posit.w.h = sXpos * 3 + 112;
    }
  }
  else {
    sXpos = (unsigned short)sXpos >> 1;
    scrz_h_posit.w.h = sXpos;
  }

  if (stageno_i.b.l == 2 && generate_flag == 0) {
    sXpos = (unsigned short)sXpos * 2;
    scrb_h_posit.w.h = sXpos + 112;
  }
  else {
    sXpos = (unsigned short)sXpos >> 2;
    scrb_h_posit.w.h = sXpos * 3;
  }
}


void scroll(void) {
  static void(*scrolls[7][3][4])(void) = {
    {
      { &z11bscroll, &z11ascroll, &z11dscroll, &z11cscroll },
      { &z12bscroll, &z12ascroll, &z12dscroll, &z12cscroll },
      { 0, 0, &z13dscroll, &z13cscroll }
    },
    {
      { &z31bscroll, &z31ascroll, &z31dscroll, &z31cscroll },
      { &z32bscroll, &z32ascroll, &z32dscroll, &z32cscroll },
      { 0, 0, &z33dscroll, &z33cscroll }
    },
    {
      { &z4scroll, &z41ascroll, &z4scroll, &z4scroll },
      { &z4scroll, &z4scroll, &z4scroll, &z4scroll },
      { 0, 0, &z4scroll, &z4scroll }
    },
    {
      { &z5bscroll, &z5ascroll, &z5dscroll, &z5cscroll },
      { &z5bscroll, &z5ascroll, &z5dscroll, &z5cscroll },
      { 0, 0, &z53dscroll, &z53cscroll }
    },
    {
      { &z6scroll, &z6scroll, &z6scroll, &z6scroll },
      { &z6scroll, &z6scroll, &z6scroll, &z6scroll },
      { 0, 0, &z6scroll, &z6scroll }
    },
    {
      { &z7scroll, &z7scroll, &z7scroll, &z7scroll },
      { &z7scroll, &z7scroll, &z7scroll, &z7scroll },
      { 0, 0, &z7scroll, &z7scroll }
    },
    {
      { &z81scroll, &z81scroll, &z81scroll, &z81scroll },
      { &z82bscroll, &z82scroll, &z82scroll, &z82cscroll },
      { 0, 0, &z83dscroll, &z83cscroll }
    }
  };

  scrolls[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)]();
}


static void z11ascroll(void) {
  int LineSpdTbl[19] = {
    65536, 57344, 49152,
    40960, 32768, 24576,
    18432, 16384, 10240,
     8192,  8192, 16384,
    32768, 49152, 65536,
    49152, 32768, 16384,
    8192
  };
  unsigned char z11a_cnttbl[10] = {
    3, 5, 5, 3,
    7, 7, 7, 5,
    3, 1
  };
  unsigned char z11a_cnttbl2[9] = {
    1, 3, 9, 3, 15,
    7, 5, 3, 1
  };
  unsigned short lposi_tbl[6] = {
    640, 224, 1920, 128, 32767, 864
  };
  int HspdWk;
  int* pLinework;
  short* pHScrollWork;
  short wWk;
  int_union* pHScrollBuff;
  short yWk;
  int i, j;
  int Lposi_TblCnt;
  unsigned short wD1, wD4, wD5, wD6;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h != 0) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  if ((actwk[0].actfree[2] & 2) != 0 && scra_hz != 0) {
    HspdWk = actwk[0].xspeed.w << 8;
  }
  else {
    HspdWk = 0;
  }

  scrollz_h((scra_hz << 5) + HspdWk, 64);
  scrollc_h((long int)(scra_hz << 4) * 3 + (long int)HspdWk * 2, 16);
  scrollb_h((scra_hz << 7) + HspdWk, 16);

  yWk = scra_v_posit.w.h;
  if ((unsigned short)actwk[0].xposi.w.h >= 2048) {
    if ((unsigned short)yWk >= 480) {
      yWk = (yWk - 480) / 2 + 480;
    }
  }

  scrollb_v(yWk);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  for (i = 0; i < 19; ++i) {
    linework[i] += LineSpdTbl[i];
  }

  lD0.w.h = (unsigned short)-scra_h_posit.w.h;

  pHScrollWork = hscrollwork;
  pLinework = linework;

  for (i = 0; i < 10; ++i) {
    wWk = (((unsigned int)(*pLinework++ & -65536) >> 16) + scrz_h_posit.w.h) * -1;

    for (j = 0; z11a_cnttbl[i] >= j; ++j) {
      *pHScrollWork++ = wWk;
    }
  }

  for (i = 0; i < 20; ++i) {
    *pHScrollWork++ = -scrc_h_posit.w.h;
  }

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = -scrb_h_posit.w.h;
  }

  for (i = 0; i < 56; ++i) {
    *pHScrollWork++ = -scrb_h_posit.w.h;
  }

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = -scrb_h_posit.w.h;
  }

  for (i = 0; i < 20; ++i) {
    *pHScrollWork++ = -scrc_h_posit.w.h;
  }

  for (i = 0; i < 9; ++i) {
    wWk = (((unsigned int)(*pLinework++ & -65536) >> 16) + scrz_h_posit.w.h) * -1;

    for (j = 0; z11a_cnttbl2[i] >= j; ++j) {
      *pHScrollWork++ = wWk;
    }
  }

  for (i = 0; i < 20; ++i) {
    *pHScrollWork++ = -scrc_h_posit.w.h;
  }

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = -scrb_h_posit.w.h;
  }

  for (i = 0; i < 16; ++i) {
    *pHScrollWork++ = -scrb_h_posit.w.h;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = hscrollwork;
  Lposi_TblCnt = 0;
  lD2.w.l = wD4 = scrb_v_posit.w.h;
  pHScrollWork += (scrb_v_posit.w.h & 2040) / 8;
  wD1 = 29;

  if (lposi_tbl[Lposi_TblCnt] > wD4) {
label1:
    lD2.w.l &= 7;
    wD4 -= lD2.w.l;
    wD4 += 8;
    lD0.w.l = *pHScrollWork++;

    i = 8 - lD2.w.l;
    goto label3;

label2:
    do {
      if ((short)wD1 < 0) break;

      if (lposi_tbl[Lposi_TblCnt] <= wD4) goto label4;

      wD4 += 8;
      lD0.l = *pHScrollWork++;

      i = 8;
label3:
      for ( ; i > 0; --i) {
        pHScrollBuff->l = lD0.l;
        ++pHScrollBuff;
      }
    } while ((short)--wD1 >= 0);

      return;
  }

label4:
  wD5 = wD4 - lposi_tbl[Lposi_TblCnt];
  wD6 = lposi_tbl[Lposi_TblCnt + 1];
  if (wD5 > wD6) {
    wD6 -= wD5;
  }
  else {
    if (wD5 == wD6) {
      wD6 -= wD5;
    }
    else {
      wD6 -= wD5;

      lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
      lD2.l = lD2.l << 8;

      lD2.w.l = (unsigned short)(lD2.l / 224);
      lD2.l = lD2.w.l;
      lD2.l = lD2.l << 8;

      lD3.l = 0;
      lD3.w.l = scrb_h_posit.w.h;
      if ((short)--wD5 >= 0) {
        do {
          lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
          lD3.l += lD2.l;
          lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
        } while ((short)--wD5 >= 0);
      }

      wD5 = wD6;
      wD5 >>= 3;
      if (wD5 > wD1) {
        wD1 -= wD5;
        wD5 = -(short)wD1;
        wD5 <<= 3;
        wD6 -= wD5;
        if (wD6 == 0) goto label5;
      }
      else {
        wD1 -= wD5;
      }

      --wD6;

      do {
        pHScrollBuff->w.h = 0;
        pHScrollBuff->w.l = (unsigned short)-lD3.w.l;
        ++pHScrollBuff;
        lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
        lD3.l += lD2.l;
        lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
        ++wD4;
        if ((wD4 & 7) == 0) {
          ++pHScrollWork;
        }

      } while ((short)--wD6 >= 0);
    }
label5:
    Lposi_TblCnt += 2;
    goto label2;
  }

  Lposi_TblCnt += 2;
  lD2.w.l = wD4;
  goto label1;
}


static void z11bscroll(void) {
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int i;
  unsigned short wD0, wD1;
  int_union lD2;
  int lD4, lD5;
  short* psHscr;
  static int scaddtbl[4] = {
    65536, 49152, 32768, 16384
  };

  if (scroll_start.b.h) return;

  scrflaga.w = 0;
  scrflagb.w = 0;
  scrflagc.w = 0;
  scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 5, 64);
  scrollc_h((scra_hz << 4) * 3, 16);

  lD4 = scra_hz << 7;
  lD5 = (scra_vz << 4) * 2;
  scrollb_hv(lD4, lD5);

  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  for (i = 0, psHscr = hscrollwork; i < 4; ++i) {
    lD2.w.l = psHscr[0];
    lD2.w.h = psHscr[1];
    lD2.l += scaddtbl[i];
    psHscr[0] = lD2.w.l;
    psHscr[1] = lD2.w.h;
    psHscr += 2;
  }

  pHScrollWork = &hscrollwork[8];

  for (i = 0; i < 2; ++i) *pHScrollWork++ = -(hscrollwork[1] + scrz_h_posit.w.h);
  for (i = 0; i < 2; ++i) *pHScrollWork++ = -(hscrollwork[3] + scrz_h_posit.w.h);
  for (i = 0; i < 2; ++i) *pHScrollWork++ = -(hscrollwork[5] + scrz_h_posit.w.h);
  for (i = 0; i < 2; ++i) *pHScrollWork++ = -(hscrollwork[7] + scrz_h_posit.w.h);

  for (i = 0; i < 10; ++i) *pHScrollWork++ = -scrz_h_posit.w.h;
  for (i = 0; i < 24; ++i) *pHScrollWork++ = -scrc_h_posit.w.h;

  pHScrollBuff = hscrollbuff;

  wD0 = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  wD1 = 29;
  pHScrollWork = &hscrollwork[wD0 / 2] + 8;

  i = 8 - ((unsigned short)scrb_v_posit.w.h & 7);
  goto label2;

  do {
    i = 8;
label2:
    wD0 = *pHScrollWork++;

    for ( ; i > 0; --i) {
      pHScrollBuff->w.h = 0;
      pHScrollBuff->w.l = wD0;
      ++pHScrollBuff;
    }
  } while ((short)--wD1 != -1);
}


static void z11cscroll(void) {
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int i;
  unsigned short wD0, wD1, wD3;
  int_union lD2, lD3;
  int lD4, lD5;
  short* psHscr;
  static int scaddtbl[4] = {
    65536, 49152, 32768, 16384
  };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 5, 64);
  scrollc_h(scra_hz << 6, 16);

  lD4 = (scra_hz << 4) * 3;
  lD5 = (scra_vz << 4) * 2;
  scrollb_hv(lD4, lD5);

  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  for (i = 0, psHscr = hscrollwork; i < 4; ++i) {
    lD2.w.l = psHscr[0];
    lD2.w.h = psHscr[1];
    lD2.l += scaddtbl[i];
    psHscr[0] = lD2.w.l;
    psHscr[1] = lD2.w.h;
    psHscr += 2;
  }

  pHScrollWork = &hscrollwork[8];

  for (i = 0; i < 4; ++i) *pHScrollWork++ = -(hscrollwork[1] + scrz_h_posit.w.h);
  for (i = 0; i < 4; ++i) *pHScrollWork++ = -(hscrollwork[3] + scrz_h_posit.w.h);
  for (i = 0; i < 2; ++i) *pHScrollWork++ = -(hscrollwork[5] + scrz_h_posit.w.h);
  for (i = 0; i < 2; ++i) *pHScrollWork++ = -(hscrollwork[7] + scrz_h_posit.w.h);

  for (i = 0; i < 6; ++i) *pHScrollWork++ = -scrz_h_posit.w.h;
  for (i = 0; i < 2; ++i) *pHScrollWork++ = -scrb_h_posit.w.h;
  for (i = 0; i < 8; ++i) *pHScrollWork++ = -scrc_h_posit.w.h;

  pHScrollBuff = hscrollbuff;

  lD5 = 28;
  wD0 = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  wD3 = (wD0 < 2) ^ 1;
  wD1 = 27 - wD3;
  if (wD1 >= 0) {
    lD5 -= wD1;
    pHScrollWork = &hscrollwork[wD0 / 2] + 8;

    lD2.w.l = scrb_v_posit.w.h & 7;
    wD0 = *pHScrollWork++;

    i = 8 - lD2.w.l;
    goto label1;

    do {
      wD0 = *pHScrollWork++;
      i = 8;
label1:
      for ( ; i > 0; --i) {
        pHScrollBuff->w.h = 0;
        pHScrollBuff->w.l = wD0;
        ++pHScrollBuff;
      };
    } while ((short)--wD1 != -1);
  }

  lD2.l = (scra_h_posit.w.h - scrc_h_posit.w.h) * 256 / 256 * 256;
  lD3.w.l = 0;
  lD3.w.h = wD0;
  wD1 = lD5 * 8 - 1;
  do {
    pHScrollBuff->w.h = 0;
    pHScrollBuff->w.l = -(unsigned short)lD3.w.h;
    ++pHScrollBuff;
    lD3.l += lD2.l;
  } while ((short)--wD1 != -1);
}


static void z11dscroll(void) {
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int i;
  unsigned short wD0, wD1;
  int_union lD2;
  int lD4, lD5;
  short* psHscr;
  static int scaddtbl[4] = {
    65536, 49152, 32768, 16384
  };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 5, 64);
  scrollc_h(scra_hz << 6, 16);

  lD4 = (scra_hz << 4) * 3;
  lD5 = (scra_vz << 4) * 2;
  scrollb_hv(lD4, lD5);

  vscroll.w.l = scrc_v_posit.w.h = scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  for (i = 0, psHscr = hscrollwork; i < 4; ++i) {
    lD2.w.l = psHscr[0];
    lD2.w.h = psHscr[1];
    lD2.l += scaddtbl[i];
    psHscr[0] = lD2.w.l;
    psHscr[1] = lD2.w.h;
    psHscr += 2;
  }

  pHScrollWork = &hscrollwork[8];

  for (i = 0; i < 4; ++i) *pHScrollWork++ = -(hscrollwork[1] + scrz_h_posit.w.h);
  for (i = 0; i < 6; ++i) *pHScrollWork++ = -(hscrollwork[3] + scrz_h_posit.w.h);
  for (i = 0; i < 4; ++i) *pHScrollWork++ = -(hscrollwork[5] + scrz_h_posit.w.h);

  for (i = 0; i < 8; ++i) *pHScrollWork++ = -scrz_h_posit.w.h;
  for (i = 0; i < 2; ++i) *pHScrollWork++ = -scrb_h_posit.w.h;
  for (i = 0; i < 6; ++i) *pHScrollWork++ = -scrc_h_posit.w.h;

  pHScrollBuff = hscrollbuff;

  wD0 = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  pHScrollWork = &hscrollwork[wD0 / 2] + 8;
  wD1 = 28;

  lD2.w.l = scrb_v_posit.w.h & 7;
  wD0 = *pHScrollWork++;

  i = 8 - lD2.w.l;
  goto label1;

  do {
    wD0 = *pHScrollWork++;
    i = 8;
label1:
    for ( ; i > 0; --i) {
      pHScrollBuff->w.h = 0;
      pHScrollBuff->w.l = wD0;
      ++pHScrollBuff;
    };
  } while ((short)--wD1 != -1);
}


static void z12ascroll(void) {
  int_union d0, d1, d2, d3, d4, d5, tmp;
  int l4, l5;
  int_union* pHscrollbuff;
  short *p, *pHscrollwork;
  short s;
  int i, j;
  int cnt, temp;
  static int hs[3] = { 65536, 49152, 32768 };

  d0.l = d1.l = d2.l = d3.l = d4.l = d5.l = 0;

  if (scroll_start.b.h) return;
  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 5, 64);
  scrollc_h((long int)(scra_hz << 4) * 3, 16);

  l4 = scra_hz << 7;
  l5 = (long int)(scra_vz << 4) * 3;
  scrollb_hv(l4, l5);

  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  for (i = 0, p = hscrollwork; i < 3; ++i) {
    tmp.w.l = p[0];
    tmp.w.h = p[1];
    tmp.l += hs[i];
    p[0] = tmp.w.l;
    p[1] = tmp.w.h;
    p += 2;
  }

  pHscrollwork = &hscrollwork[6];

  d0.w.h = -scra_h_posit.w.h;
  d0.w.l = -(hscrollwork[1] + scrz_h_posit.w.h);
  for (i = 0; i < 4; ++i) *pHscrollwork++ = d0.w.l;

  d0.w.l = -(hscrollwork[3] + scrz_h_posit.w.h);
  for (i = 0; i < 4; ++i) *pHscrollwork++ = d0.w.l;

  d0.w.l = -(hscrollwork[5] + scrz_h_posit.w.h);
  for (i = 0; i < 4; ++i) *pHscrollwork++ = d0.w.l;

  d0.w.l = -scrz_h_posit.w.h;
  for (i = 0; i < 20; ++i) *pHscrollwork++ = d0.w.l;

  d0.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 4; ++i) *pHscrollwork++ = d0.w.l;

  pHscrollbuff = hscrollbuff;
  pHscrollwork = &hscrollwork[6];
  d0.w.l = scrb_v_posit.w.h;
  d2.w.l = d0.w.l;
  d0.w.l &= 504;
  d0.w.l >>= 2;
  d3.w.l = d0.w.l;
  d3.w.l = (unsigned short)d3.w.l >> 1;
  d1.w.l = 35;
  d5.w.l = 28;
  if (d1.w.l >= d3.w.l) {
    d1.w.l -= d3.w.l;
    if (d1.w.l >= 27) {
      d1.w.l = 27;
    }
    d5.w.l -= d1.w.l;
    pHscrollwork = &hscrollwork[d0.w.l / 2 + 6];

    d2.w.l &= 7;
    d2.w.l += d2.w.l;
    d0.w.h = 0;
    d0.w.h = -scra_h_posit.w.h;
    d0.w.l = *pHscrollwork++;
    cnt = 8 - d2.w.l / 2;
    temp = d1.w.l;
    if (d1.w.l == 27) ++temp;

    for (i = 0; temp >= i; ++i) {
      if (i != 0) {
        cnt = 8;
      }
      for (j = 0; j < cnt; ++j) {
        *pHscrollbuff++ = d0;
      }
      d0.w.l = *pHscrollwork++;
    }
  }

  d0.w.l = scrc_h_posit.w.h;
  d2.w.l = scra_h_posit.w.h;
  d2.w.l -= d0.w.l;
  d2.l = d2.w.l;
  d2.l *= 256;
  d2.w.l = (long int)d2.l / 256;
  d2.l = d2.w.l;
  d2.l *= 256;
  d3.l = 0;
  d3.w.l = d0.w.l;
  d1.w.l = d5.w.l;
  d1.w.l = (unsigned short)d1.w.l * 8;
  --d1.w.l;

  do {
    d0.w.l = d3.w.l;
    d0.w.l *= -1;
    *pHscrollbuff++ = d0;
    s = d3.w.h;
    d3.w.h = d3.w.l;
    d3.w.l = s;
    d3.l += d2.l;
    s = d3.w.h;
    d3.w.h = d3.w.l;
    d3.w.l = s;
  } while (d1.w.l--);
}


static void z12bscroll(void) {
  int_union ldwk;
  int_union ldwk2;
  int_union* pHscrbuf;
  int i, j;
  int lXwk, lYwk;
  short sYline;
  short sYnum;
  short *psHscr, *psHscw;
  static unsigned char z12b_cnttbl[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
  static int scaddtbl[8] = { 65536, 57344, 49152, 40960, 32768, 24576, 20480, 16384 };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz << 5;
  scrollz_h(lXwk, 64);

  lXwk = (scra_hz << 4) * 3;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz << 7;
  lYwk = (scra_vz << 4) * 3;
  scrollb_hv(lXwk, lYwk);
  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  for (i = 0, psHscr = hscrollwork; i < 8; ++i) {
    ldwk.w.l = psHscr[0];
    ldwk.w.h = psHscr[1];
    ldwk.l += scaddtbl[i];
    psHscr[0] = ldwk.w.l;
    psHscr[1] = ldwk.w.h;
    psHscr += 2;
  }

  ldwk.w.l = -scra_h_posit.w.h;
  { short wk = ldwk.w.l; ldwk.w.l = ldwk.w.h; ldwk.w.h = wk; }
  psHscr = &hscrollwork[0];
  psHscw = &hscrollwork[16];

  for (i = 7; i >= 0; --i) {
    ldwk2.w.l = *psHscr;
    ++psHscr;
    ldwk2.w.h = *psHscr;
    ++psHscr;
    { short wk = ldwk2.w.l; ldwk2.w.l = ldwk2.w.h; ldwk2.w.h = wk; }
    ldwk2.w.l = -(ldwk2.w.l + scrz_h_posit.w.h);

    for (j = z12b_cnttbl[i]; j >= 0; --j) {
      *psHscw = ldwk2.w.l;
      ++psHscw;
    }
  }

  ldwk.w.l = -scrz_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *psHscw = ldwk.w.l;
    ++psHscw;
  }

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 8; ++i) {
    *psHscw = ldwk.w.l;
    ++psHscw;
  }

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 32; ++i) {
    *psHscw = ldwk.w.l;
    ++psHscw;
  }

  sYnum = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  psHscr = &hscrollwork[sYnum / 2] + 16;

  sYline = 29;
  pHscrbuf = hscrollbuff;
  zone1scrsetsub0(scrb_v_posit.w.h, sYline, &pHscrbuf, psHscr);
}


static void z12cscroll(void) {
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* psHscr;
  int i;
  int j;
  unsigned short wD1;
  unsigned short temp;
  int_union lD0, lD2, lD3;
  int lD4, lD5;
  unsigned char z12c_cnttbl[5] = { 1, 3, 3, 3, 1 };
  static int scaddtbl[5] = { 65536, 57344, 49152, 40960, 32768 };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h((scra_hz << 3) * 3, 64);
  scrollc_h((scra_hz << 4) * 3, 16);

  lD4 = scra_hz << 5;
  lD5 = (scra_vz << 4) * 3;
  scrollb_hv(lD4, lD5);

  vscroll.w.l = scrc_v_posit.w.h = scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscr = (int_union*)hscrollwork;
  for (i = 0; i < 5; ++i) {
    psHscr->l += scaddtbl[i];
    ++psHscr;
  }

  lD0.w.h = -scra_h_posit.w.h;
  psHscr = (int_union*)hscrollwork;
  pHScrollWork = &hscrollwork[10];
  for (i = 4; i >= 0; --i) {
    wD1 = -(psHscr->w.h + scrz_h_posit.w.h);
    ++psHscr;
    for (j = z12c_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = -scrz_h_posit.w.h;
  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < 2; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[10];
  lD2.w.l = lD0.w.l = scrb_v_posit.w.h;
  lD0.w.l = (unsigned short)(lD0.w.l & 504) >> 2;
  lD3.w.l = lD0.w.l >> 1;
  wD1 = 31;
  lD5 = 28;
  if (wD1 >= (unsigned short)lD3.w.l) {
    wD1 -= lD3.w.l;

    if (wD1 >= 27) {
      wD1 = 27;
    }

    lD5 -= wD1;
    pHScrollWork += lD0.w.l / 2;

    temp = wD1;
    if (temp == 27)
      ++temp;
    zone1scrsetsub0(lD2.w.l, temp, &pHScrollBuff, pHScrollWork);
  } else {
    wD1 -= lD3.w.l;
  }

  lD0.w.l = scrc_h_posit.w.h;
  lD2.l = scra_h_posit.w.h - lD0.w.l;
  lD2.l *= 256;
  lD2.l /= 256;
  lD2.l *= 256;
  lD3.l = (unsigned short)lD0.w.l;
  wD1 = ((unsigned short)lD5 * 8 - 1);

  do {
    lD0.w.l = -lD3.w.l;
    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  } while ((short)--wD1 >= 0);
}


static void z12dscroll(void) {
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* psHscr;
  int i;
  int j;
  unsigned short wD1;

  int_union lD0, lD2;
  int lD4, lD5;
  unsigned char z12d_cnttbl[4] = { 0, 4, 3, 3 };
  static int scaddtbl[4] = { 65536, 49152, 32768, 16384 };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h((scra_hz << 3) * 3, 64);
  scrollc_h((scra_hz << 4) * 3, 16);

  lD4 = scra_hz << 5;
  lD5 = (scra_vz << 4) * 2;
  scrollb_hv(lD4, lD5);

  vscroll.w.l = scrc_v_posit.w.h = scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscr = (int_union*)hscrollwork;
  for (i = 0; i < 4; ++i) {
    psHscr->l += scaddtbl[i];
    ++psHscr;
  }

  lD0.w.h = -scra_h_posit.w.h;
  psHscr = (int_union*)hscrollwork;
  pHScrollWork = &hscrollwork[8];
  for (i = 3; i >= 0; --i) {
    wD1 = -(psHscr->w.h + scrz_h_posit.w.h);
    ++psHscr;
    for (j = z12d_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = -scrz_h_posit.w.h;
  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < 2; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[8];
  lD2.w.l = lD0.w.l = scrb_v_posit.w.h;
  lD0.w.l = (unsigned short)(lD0.w.l & 504) >> 2;
  wD1 = 28;
  pHScrollWork += lD0.w.l / 2;
  zone1scrsetsub0(lD2.w.l, wD1, &pHScrollBuff, pHScrollWork);
}


static void z13cscroll(void) {
  int_union ldwk, ldwk2, ldwk3;
  int_union* pHscrbuf;
  int i, j;
  int lXwk, lYwk;
  short sYline;
  short sYnum, sYnumsv;
  short *psHscr, *psHscw;
  short temp;
  static unsigned char z12c_cnttbl[5] = { 1, 3, 3, 3, 1 };
  static int scaddtbl[5] = { 65536, 57344, 49152, 40960, 32768 };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = (scra_hz << 3) * 3;
  scrollz_h(lXwk, 64);

  lXwk = (scra_hz << 4) * 3;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz << 5;
  lYwk = (scra_vz << 4) * 3;
  scrollb_hv(lXwk, lYwk);
  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  for (i = 0, psHscr = hscrollwork; i < 5; ++i) {
    ldwk.w.l = psHscr[0];
    ldwk.w.h = psHscr[1];
    ldwk.l += scaddtbl[i];
    psHscr[0] = ldwk.w.l;
    psHscr[1] = ldwk.w.h;
    psHscr += 2;
  }

  ldwk.w.l = -scra_h_posit.w.h;
  { short wk = ldwk.w.l; ldwk.w.l = ldwk.w.h; ldwk.w.h = wk; }
  psHscr = &hscrollwork[0];
  psHscw = &hscrollwork[10];

  for (i = 4; i >= 0; --i) {
    ldwk2.w.l = *psHscr;
    ++psHscr;
    ldwk2.w.h = *psHscr;
    ++psHscr;
    { short wk = ldwk2.w.l; ldwk2.w.l = ldwk2.w.h; ldwk2.w.h = wk; }
    ldwk2.w.l = -(ldwk2.w.l + scrz_h_posit.w.h);

    for (j = z12c_cnttbl[i]; j >= 0; --j) {
      *psHscw = ldwk2.w.l;
      ++psHscw;
    }
  }

  ldwk.w.l = -scrz_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *psHscw = ldwk.w.l;
    ++psHscw;
  }

  ldwk.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < 2; ++i) {
    *psHscw = ldwk.w.l;
    ++psHscw;
  }

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 8; ++i) {
    *psHscw = ldwk.w.l;
    ++psHscw;
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  psHscr = &hscrollwork[sYnum / 2] + 10;
  sYnum = (unsigned short)sYnum >> 1;
  sYnumsv = 28;

  if ((sYline = 31 - sYnum) >= 0) {
    if (sYline > 27) {
      sYline = 27;
    }
    sYnumsv -= sYline;

    temp = sYline;
    if (temp == 27)
      ++temp;
    zone1scrsetsub0(scrb_v_posit.w.h, temp, &pHscrbuf, psHscr);
  }

  ldwk.w.l = scrc_h_posit.w.h;
  ldwk2.l = (scra_h_posit.w.h - ldwk.w.l) * 256 / 256 * 256;
  ldwk3.l = 0;
  ldwk3.w.l = ldwk.w.l;
  for (i = sYnumsv * 8 - 1; i >= 0; --i) {
    ldwk.w.l = -ldwk3.w.l;
    pHscrbuf->l = ldwk.l;
    ++pHscrbuf;
    { short wk = ldwk3.w.l; ldwk3.w.l = ldwk3.w.h; ldwk3.w.h = wk; }
    ldwk3.l += ldwk2.l;
    { short wk = ldwk3.w.l; ldwk3.w.l = ldwk3.w.h; ldwk3.w.h = wk; }
  }
}


static void z13dscroll(void) {
  int_union ldwk;
  int_union ldwk2;
  int_union* pHscrbuf;
  int i, j;
  int lXwk, lYwk;
  short sYline;
  short sYnum;
  short *psHscr, *psHscw;
  static unsigned char z12d_cnttbl[4] = { 0, 4, 3, 3 };
  static int scaddtbl[4] = { 65536, 49152, 32768, 16384 };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = (scra_hz << 3) * 3;
  scrollz_h(lXwk, 64);

  lXwk = (scra_hz << 4) * 3;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz << 5;
  lYwk = (scra_vz << 4) * 3;
  scrollb_hv(lXwk, lYwk);
  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  for (i = 0, psHscr = hscrollwork; i < 4; ++i) {
    ldwk.w.l = psHscr[0];
    ldwk.w.h = psHscr[1];
    ldwk.l += scaddtbl[i];
    psHscr[0] = ldwk.w.l;
    psHscr[1] = ldwk.w.h;
    psHscr += 2;
  }

  ldwk.w.l = -scra_h_posit.w.h;
  { short wk = ldwk.w.l; ldwk.w.l = ldwk.w.h; ldwk.w.h = wk; }
  psHscr = &hscrollwork[0];
  psHscw = &hscrollwork[8];

  for (i = 3; i >= 0; --i) {
    ldwk2.w.l = *psHscr;
    ++psHscr;
    ldwk2.w.h = *psHscr;
    ++psHscr;
    { short wk = ldwk2.w.l; ldwk2.w.l = ldwk2.w.h; ldwk2.w.h = wk; }
    ldwk2.w.l = -(ldwk2.w.l + scrz_h_posit.w.h);

    for (j = z12d_cnttbl[i]; j >= 0; --j) {
      *psHscw = ldwk2.w.l;
      ++psHscw;
    }
  }

  ldwk.w.l = -scrz_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *psHscw = ldwk.w.l;
    ++psHscw;
  }

  ldwk.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < 2; ++i) {
    *psHscw = ldwk.w.l;
    ++psHscw;
  }

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 6; ++i) {
    *psHscw = ldwk.w.l;
    ++psHscw;
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  psHscr = &hscrollwork[sYnum / 2] + 8;
  sYline = 28;
  zone1scrsetsub0(scrb_v_posit.w.h, sYline, &pHscrbuf, psHscr);
}


static void z31ascroll(void) {
  int LineSpdTbl[15] = {
    49152, 32768, 24576,
    16384, 12288,  8192,
     4096,  2048,  4096,
     8192, 12288, 16384,
    24576, 32768, 49152
  };
  unsigned char z31a_cnttbl[15] = {
    1, 3, 1, 1, 1, 1, 1, 1,
    3, 1, 3, 3, 3, 3, 1
  };
  unsigned short z31a_kawatbl[3] = {
    56, 592, 32767
  };
  unsigned short lposi_tbl[6] = {
    640, 224, 1920, 128, 32767, 864
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5, wD6;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 15; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for (i = 0; i < 64; ++i) {
    lD2.l = ((long int)(int)wD1 << 10) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  lD2.l = scra_h_posit.w.h - scrb_h_posit.w.h;
  lD2.l <<= 8;
  lD2.l /= 28;
  lD2.l <<= 10;

  lD3.l = 0;
  lD3.w.l = scrb_h_posit.w.h;

  pHScrollWork = &hscrollwork[165];
  for (i = 0; i < 7; ++i) {
    lD0.w.l = -lD3.w.l;
    --pHScrollWork;
    *pHScrollWork = lD0.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  pHScrollWork = &hscrollwork[165];
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 3; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 14; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z31a_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 40;
  lD2.l <<= 10;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 0; i < 10; ++i) {
    *pHScrollWork++ = (unsigned short)-lD3.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[158];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 29;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z31a_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHscrWk = (int_union*)&hscrollwork[30];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  do {
    lD2.l = pHscrWk->l;
    ++pHscrWk;
    lD2.l = (unsigned int)lD2.l >> 16 & 65535 | lD2.l << 16 & -65536;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l *= -1;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 127;
      wD6 = wD5 << 1;
      wD3 = (short)(char)awasintbl[wD6];
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  } while ((short)--wD1 >= 0);
}


static void z31bscroll(void) {
  int LineSpdTbl[13] = {
    32768, 24576, 16384,
    12288,  8192,  4096,
     2048,  4096,  8192,
    12288, 16384, 24576,
    32768
  };
  unsigned char z31b_cnttbl[13] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1
  };
  unsigned char z31b_cnttbl0[3] = {
    3, 1, 1
  };
  unsigned char z31b_cnttbl1[6] = {
    5, 1, 1,
    3, 1, 1
  };
  unsigned short z31b_kawatbl[3] = {
    64, 528, 32767
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 13; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for ( ; i < 77; ++i) {
    lD2.l = ((long int)(int)wD1 << 8) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  lD2.l = scra_h_posit.w.h - scrb_h_posit.w.h;
  lD2.l <<= 5;
  lD2.l /= 12;
  lD2.l <<= 11;

  lD3.l = 0;
  lD3.w.l = scrb_h_posit.w.h;

  pHScrollWork = &hscrollwork[161];
  for (i = 2; i >= 0; --i) {
    lD0.w.l = -lD3.w.l;

    for (j = z31b_cnttbl0[i]; j >= 0; --j) {
      *pHScrollWork-- = lD0.w.l;
    }

    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  pHScrollWork = &hscrollwork[162];
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 12; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z31b_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 24;
  lD2.l <<= 10;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 5; i >= 0; --i) {
    lD0.w.l = -lD3.w.l;
    for (j = z31b_cnttbl1[i]; j >= 0; --j) {
      *pHScrollWork++ = lD0.w.l;
    }
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[154];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 28;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z31b_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHScrollWork = &hscrollwork[17];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  for ( ; (short)wD1 >= 0; --wD1) {
    lD2.w.h = *pHScrollWork++;
    lD2.w.l = *pHScrollWork++;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l *= -1;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 255;
      wD3 = (short)(char)awasintbl[wD5] * 2;
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  }
}


static void z31cscroll(void) {
  int LineSpdTbl[14] = {
    49152, 32768, 24576,
    16384, 12288,  8192,
     4096,  4096,  8192,
    12288, 16384, 24576,
    32768, 49152
  };
  unsigned char z31c_cnttbl[14] = {
    1, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 3, 3
  };
  unsigned short z31c_kawatbl[3] = {
    56, 592, 32767
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 14; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for ( ; i < 78; ++i) {
    lD2.l = ((long int)(int)wD1 << 8) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  lD2.l = scra_h_posit.w.h - scrb_h_posit.w.h;
  lD2.l <<= 6;
  lD2.l /= 28;
  lD2.l <<= 10;

  lD3.l = 0;
  lD3.w.l = scrb_h_posit.w.h;

  pHScrollWork = &hscrollwork[162];
  for (i = 0; i < 7; ++i) {
    lD0.w.l = -lD3.w.l;
    *pHScrollWork-- = lD0.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  pHScrollWork = &hscrollwork[163];
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 3; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 13; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z31c_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 44;
  lD2.l <<= 11;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 0; i < 10; ++i) {
    *pHScrollWork++ = (unsigned short)-lD3.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[156];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 29;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z31c_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHScrollWork = &hscrollwork[28];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  do {
    lD2.w.h = *pHScrollWork++;
    lD2.w.l = *pHScrollWork++;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l = (unsigned short)-lD2.w.l;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 255;
      wD3 = (short)(char)awasintbl[wD5];
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  } while ((short)--wD1 >= 0);
}


static void z31dscroll(void) {
  int LineSpdTbl[15] = {
    49152, 32768, 24576,
    16384, 12288,  8192,
     4096,  2048,  4096,
     8192, 12288, 16384,
    24576, 32768, 49152
  };
  unsigned char z31d_cnttbl[15] = {
    1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 3, 3, 3, 3, 1
  };
  unsigned char z31d_cnttbl1[3] = {
    6, 1, 0
  };
  unsigned short z31d_kawatbl[3] = {
    8, 32767, 32767
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 15; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for ( ; i < 79; ++i) {
    lD2.l = ((long int)(int)wD1 << 8) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  pHScrollWork = &hscrollwork[158];
  lD0.w.h = -scra_h_posit.w.h;
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;
  *pHScrollWork++ = lD0.w.l;

  for (i = 0; i < 3; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 10; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 14; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z31d_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 12; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 24;
  lD2.l <<= 10;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 2; i >= 0; --i) {
    lD0.w.l = -lD3.w.l;
    for (j = z31d_cnttbl1[i]; j >= 0; --j) {
      *pHScrollWork++ = lD0.w.l;
    }
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[158];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 29;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z31d_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHScrollWork = &hscrollwork[30];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  do {
    lD2.w.h = *pHScrollWork++;
    lD2.w.l = *pHScrollWork++;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l = (unsigned short)-lD2.w.l;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 255;
      wD3 = (short)(char)awasintbl[wD5];
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  } while ((short)--wD1 >= 0);
}


static void z32ascroll(void) {
  int LineSpdTbl[14] = {
    49152, 32768, 24576,
    16384, 12288,  8192,
     4096,  4096,  8192,
    12288, 16384, 24576,
    32768, 49152
  };
  unsigned char z32a_cnttbl[14] = {
    1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 3, 5
  };
  unsigned short z32a_kawatbl[3] = {
    56, 592, 32767
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 14; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for ( ; i < 78; ++i) {
    lD2.l = ((long int)(int)wD1 << 8) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  lD2.l = scra_h_posit.w.h - scrb_h_posit.w.h;
  lD2.l <<= 6;
  lD2.l /= 28;
  lD2.l <<= 10;

  lD3.l = 0;
  lD3.w.l = scrb_h_posit.w.h;

  pHScrollWork = &hscrollwork[162];
  for (i = 0; i < 7; ++i) {
    lD0.w.l = -lD3.w.l;
    *pHScrollWork-- = lD0.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  pHScrollWork = &hscrollwork[163];
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 3; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 13; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z32a_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 44;
  lD2.l <<= 11;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 0; i < 10; ++i) {
    *pHScrollWork++ = (unsigned short)-lD3.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[156];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 29;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z32a_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHScrollWork = &hscrollwork[28];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  do {
    lD2.w.h = *pHScrollWork++;
    lD2.w.l = *pHScrollWork++;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l = (unsigned short)-lD2.w.l;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 255;
      wD3 = (short)(char)awasintbl[wD5];
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  } while ((short)--wD1 >= 0);
}


static void z32bscroll(void) {
  int LineSpdTbl[10] = {
    32768, 24576, 16384,
    12288,  8192,  8192,
    12288, 16384, 24576,
    32768
  };
  unsigned char z32b_cnttbl[10] = {
    1, 1, 1, 1, 1, 5, 1, 1, 3, 1
  };
  unsigned char z32b_cnttbl0[3] = {
    3, 1, 1
  };
  unsigned char z32b_cnttbl1[6] = {
    5, 1, 1, 3, 1, 1
  };
  unsigned short z32b_kawatbl[3] = {
    64, 528, 32767
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 10; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for ( ; i < 74; ++i) {
    lD2.l = ((long int)(int)wD1 << 8) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  lD2.l = scra_h_posit.w.h - scrb_h_posit.w.h;
  lD2.l <<= 5;
  lD2.l /= 12;
  lD2.l <<= 11;

  lD3.l = 0;
  lD3.w.l = scrb_h_posit.w.h;

  pHScrollWork = &hscrollwork[155];
  for (i = 2; i >= 0; --i) {
    lD0.w.l = -lD3.w.l;

    for (j = z32b_cnttbl0[i]; j >= 0; --j) {
      *pHScrollWork-- = lD0.w.l;
    }

    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  pHScrollWork = &hscrollwork[156];
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 9; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z32b_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 10; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 24;
  lD2.l <<= 10;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 5; i >= 0; --i) {
    lD0.w.l = -lD3.w.l;
    for (j = z32b_cnttbl1[i]; j >= 0; --j) {
      *pHScrollWork++ = lD0.w.l;
    }
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[148];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 28;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z32b_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHScrollWork = &hscrollwork[20];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  for ( ; (short)wD1 >= 0; --wD1) {
    lD2.w.h = *pHScrollWork++;
    lD2.w.l = *pHScrollWork++;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l *= -1;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 255;
      wD3 = (short)(char)awasintbl[wD5] * 2;
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  }
}


static void z32cscroll(void) {
  int LineSpdTbl[14] = {
    49152, 32768, 24576,
    16384, 12288,  8192,
     4096,  4096,  8192,
    12288, 16384, 24576,
    32768, 49152
  };
  unsigned char z32c_cnttbl[14] = {
    1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 3, 3, 3, 5
  };
  unsigned short z32c_kawatbl[3] = {
    56, 592, 32767
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 14; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for ( ; i < 78; ++i) {
    lD2.l = ((long int)(int)wD1 << 8) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  lD2.l = scra_h_posit.w.h - scrb_h_posit.w.h;
  lD2.l <<= 6;
  lD2.l /= 28;
  lD2.l <<= 10;

  lD3.l = 0;
  lD3.w.l = scrb_h_posit.w.h;

  pHScrollWork = &hscrollwork[162];
  for (i = 0; i < 7; ++i) {
    lD0.w.l = -lD3.w.l;
    *pHScrollWork-- = lD0.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  pHScrollWork = &hscrollwork[163];
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 3; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 13; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z32c_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 44;
  lD2.l <<= 11;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 0; i < 10; ++i) {
    *pHScrollWork++ = (unsigned short)-lD3.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[156];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 29;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z32c_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHScrollWork = &hscrollwork[28];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  do {
    lD2.w.h = *pHScrollWork++;
    lD2.w.l = *pHScrollWork++;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l = (unsigned short)-lD2.w.l;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 255;
      wD3 = (short)(char)awasintbl[wD5];
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  } while ((short)--wD1 >= 0);
}


static void z32dscroll(void) {
  int LineSpdTbl[16] = {
    49152, 32768, 24576,
    16384, 12288,  8192,
     4096,  3072,  3072,  4096,
     8192, 12288, 16384,
    24576, 32768, 49152
  };
  unsigned char z32d_cnttbl[16] = {
    1, 3, 1, 1, 1, 3, 1, 3, 1, 1, 1, 3, 3, 1, 1, 1
  };
  unsigned char z32d_cnttbl1[3] = {
    6, 1, 0
  };
  unsigned short z32d_kawatbl[3] = {
    8, 32767, 32767
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 16; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for ( ; i < 80; ++i) {
    lD2.l = ((long int)(int)wD1 << 8) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  pHScrollWork = &hscrollwork[160];
  lD0.w.h = -scra_h_posit.w.h;
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;
  *pHScrollWork++ = lD0.w.l;

  for (i = 0; i < 3; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 10; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 15; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z32d_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 12; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 24;
  lD2.l <<= 10;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 2; i >= 0; --i) {
    lD0.w.l = -lD3.w.l;
    for (j = z32d_cnttbl1[i]; j >= 0; --j) {
      *pHScrollWork++ = lD0.w.l;
    }
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[160];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 29;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z32d_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHScrollWork = &hscrollwork[28];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  do {
    lD2.w.h = *pHScrollWork++;
    lD2.w.l = *pHScrollWork++;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l = (unsigned short)-lD2.w.l;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 255;
      wD3 = (short)(char)awasintbl[wD5];
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  } while ((short)--wD1 >= 0);
}


static void z33cscroll(void) {
  int LineSpdTbl[12] = {
    49152, 32768, 24576,
    16384, 12288,  8192,
     8192, 12288, 16384,
    24576, 32768, 49152
  };
  unsigned char z33c_cnttbl[12] = {
    1, 3, 1, 3, 1, 3, 1, 3, 3, 3, 3, 3
  };
  unsigned short z33c_kawatbl[3] = {
    56, 592, 32767
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 12; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for ( ; i < 76; ++i) {
    lD2.l = ((long int)(int)wD1 << 8) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  lD2.l = scra_h_posit.w.h - scrb_h_posit.w.h;
  lD2.l <<= 6;
  lD2.l /= 28;
  lD2.l <<= 10;

  lD3.l = 0;
  lD3.w.l = scrb_h_posit.w.h;

  pHScrollWork = &hscrollwork[158];
  for (i = 0; i < 7; ++i) {
    lD0.w.l = -lD3.w.l;
    *pHScrollWork-- = lD0.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  pHScrollWork = &hscrollwork[159];
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 3; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 2; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 11; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z33c_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 12; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 4; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 44;
  lD2.l <<= 11;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 0; i < 10; ++i) {
    *pHScrollWork++ = (unsigned short)-lD3.w.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[160];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 29;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z33c_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHScrollWork = &hscrollwork[24];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  do {
    lD2.w.h = *pHScrollWork++;
    lD2.w.l = *pHScrollWork++;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l = (unsigned short)-lD2.w.l;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 255;
      wD3 = (short)(char)awasintbl[wD5];
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  } while ((short)--wD1 >= 0);
}


static void z33dscroll(void) {
  int LineSpdTbl[12] = {
    49152, 32768, 24576,
    16384, 12288,  8192,
     8192, 12288, 16384,
    24576, 32768, 49152
  };
  unsigned char z33d_cnttbl[12] = {
    1, 3, 3, 1, 1, 3, 1, 3, 3, 3, 3, 3
  };
  unsigned char z33d_cnttbl1[3] = {
    5, 1, 0
  };
  unsigned short z33d_kawatbl[3] = {
    24, 32767, 32767
  };
  short* pHScrollWork;
  int_union* pHScrollBuff;
  int_union* pHscrWk;
  int i, j;
  unsigned short wD1, wD3, wD4, wD5;
  int_union lD0, lD2, lD3;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  lD0.w.l = 536;
  wD1 = 1312;
  if ((unsigned short)scra_v_posit.w.h <= wD1) {
    wD1 -= scra_v_posit.w.h;
    wD1 >>= 1;
    lD0.w.l -= wD1;
    if (lD0.w.l < 0) {
      lD0.w.l = 0;
    }
  }
  else {
    wD1 -= scra_v_posit.w.h;
  }

  scrollb_v(lD0.w.l);
  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h;
  scrflagb.b.h |= scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  pHscrWk = (int_union*)hscrollwork;
  for (i = 0; i < 12; ++i) {
    pHscrWk->l += LineSpdTbl[i];
    ++pHscrWk;
  }
  wD1 = 0;
  for ( ; i < 76; ++i) {
    lD2.l = ((long int)(int)wD1 << 8) + 32768;
    pHscrWk->l += lD2.l;
    ++pHscrWk;
    ++wD1;
  }

  pHScrollWork = &hscrollwork[152];
  lD0.w.h = -scra_h_posit.w.h;
  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 3; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  for (i = 0; i < 3; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHscrWk = (int_union*)hscrollwork;
  for (i = 11; i >= 0; --i) {
    wD1 = -(pHscrWk->w.h + scrb_h_posit.w.h);
    ++pHscrWk;
    for (j = z33d_cnttbl[i]; j >= 0; --j) {
      *pHScrollWork++ = wD1;
    }
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrz_h_posit.w.h;

  for (i = 0; i < 6; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD0.w.l = (unsigned short)-scrc_h_posit.w.h;

  for (i = 0; i < 14; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  lD2.l = (short)(scra_h_posit.w.h - scrb_h_posit.w.h);
  lD2.l <<= 6;
  lD2.l /= 24;
  lD2.l <<= 10;
  lD3.w.l = scrb_h_posit.w.h;

  for (i = 2; i >= 0; --i) {
    lD0.w.l = -lD3.w.l;
    for (j = z33d_cnttbl1[i]; j >= 0; --j) {
      *pHScrollWork++ = lD0.w.l;
    }
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
    lD3.l += lD2.l;
    lD3.l = (unsigned int)lD3.l >> 16 & 65535 | lD3.l << 16 & -65536;
  }

  lD0.w.l = (unsigned short)-scrb_h_posit.w.h;

  for (i = 0; i < 8; ++i) {
    *pHScrollWork++ = lD0.w.l;
  }

  pHScrollBuff = hscrollbuff;
  pHScrollWork = &hscrollwork[152];
  lD0.w.l = scrb_v_posit.w.h;
  lD2.w.l = lD0.w.l;
  wD4 = lD0.w.l;
  lD0.w.l = (unsigned short)((lD0.w.l & 1016) >> 2);
  wD3 = lD0.w.l >> 1;
  wD1 = 87;
  wD5 = 29;
  if (wD3 <= wD1) {
    wD1 -= wD3;
    if (wD1 >= 27) {
      wD1 = 28;
    }

    wD5 -= wD1;
    pHScrollWork += (unsigned int)lD0.w.l / 2;
    waterdirec.w += 64;

    zone3scrsetsub0(&pHScrollBuff, (unsigned short**)&pHScrollWork, z33d_kawatbl, awasintbl, wD1, (unsigned short*)&lD2.w.l, &wD4);
  }
  else {
    wD1 -= wD3;
  }

  wD1 = (wD5 << 3) - 1;
  pHScrollWork = &hscrollwork[24];
  wD5 = (unsigned char)waterdirec.b.h;
  wD4 -= (unsigned short)scrb_v_posit.w.h;

  do {
    lD2.w.h = *pHScrollWork++;
    lD2.w.l = *pHScrollWork++;
    lD2.w.l += scrb_h_posit.w.h;
    lD2.w.l = (unsigned short)-lD2.w.l;
    lD0.w.l = lD2.w.l;
    wD3 = 1472 - scra_v_posit.w.h;
    if (wD3 <= wD4) {
      wD5 &= 255;
      wD3 = (short)(char)awasintbl[wD5];
      wD3 += scra_h_posit.w.h;
      wD3 = -(short)wD3;
      lD0.w.h = wD3;
    }

    pHScrollBuff->l = lD0.l;
    ++pHScrollBuff;
    ++wD4;
    ++wD5;
  } while ((short)--wD1 >= 0);
}


static void z4scroll(void) {
  uint_union data;
  int_union temp1, temp2;
  int hsCount;
  int i;

  if (scroll_start.b.h) return;

  scrflaga.w = 0;
  scrflagb.w = 0;
  scrflagc.w = 0;
  scrflagz.w = 0;

  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  temp1.l = (long int)(scra_hz << 2) * 3;
  temp2.l = scra_vz << 7;
  scrollb_hv(temp1.l, temp2.l);

  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;

  scrflagb.b.h |= scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;
  hsCount = 0;

  for (i = 0; i < 192; ++i) {
    hscrollwork[hsCount] = -scrb_h_posit.w.h;
    ++hsCount;
  }

  data.w.l = -scra_h_posit.w.h;
  data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
  data.w.l = scrb_v_posit.w.h;
  if (stageno_i.b.l == 0) {
    data.w.l &= 2040;
  }
  else {
    data.w.l &= 1016;
  }
  data.w.l >>= 2;

  zone4scrsetsub0(-scra_h_posit.w.h, scrb_v_posit.w.h, data.w.l / 2);
}


static void z41ascroll(void) {
  uint_union data;
  int hsCount;
  int i;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  scrollz_h(scra_hz << 4, 64);
  scrollc_h((long int)(scra_hz << 3) * 3, 16);
  scrollb_h((long int)(scra_hz << 2) * 3, 4);

  data.l = 0;
  data.w.l = scra_v_posit.w.h;
  if ((unsigned short)scra_v_posit.w.h < 512) {
    if ((unsigned short)scra_h_posit.w.h >= 640)
      data.w.l = 512;
  }
  else {
    data.w.l -= 512;
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
    data.l >>= 2;
    data.l *= 3;
    data.l += 0x2000000;
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
  }

  scrollb_v(data.w.l);

  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;
  scrflagb.b.h |= scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  hsCount = 0;
  for (i = 0; i < 16; ++i) {
    hscrollwork[hsCount] = -scrb_h_posit.w.h;
    ++hsCount;
  }

  hsCount = z41aline(hsCount);

  for (i = 0; i < 144; ++i) {
    hscrollwork[hsCount] = -scrc_h_posit.w.h;
    ++hsCount;
  }

  data.w.l = -scra_h_posit.w.h;
  data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
  data.w.l = scrb_v_posit.w.h;
  data.w.l &= 2040;
  data.w.l >>= 2;
  zone4scrsetsub0(-scra_h_posit.w.h, scrb_v_posit.w.h, data.w.l / 2);
}


static void z5ascroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz * 64;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz * 128;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz * 64;
  lXwk += lXwk * 4;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h;
  if (enkeino & 1) {
    lYwk >>= 2;
  }
  else {
    lYwk >>= 1;
    if (stageno_i.b.l == 1) {
      lYwk += (lYwk >> 2) + (lYwk >> 3);
    }
    else {
      lYwk += (lYwk >> 2) + (lYwk >> 4);
    }
  }

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;
  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  if (enkeino & 1) {
    z5aline2(&psHscw);
    z5aline3(&psHscw);
  }
  else {
    ldwk.w.l = -scrz_h_posit.w.h;

    for (i = 0; i < 8; ++i) {
      *psHscw++ = ldwk.w.l;
    }

    z5aline0(&psHscw);
    z5aline1(&psHscw);

    ldwk.w.l = -scrz_h_posit.w.h;

    for (i = 0; i < 8; ++i) {
      *psHscw++ = ldwk.w.l;
    }
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 1016) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone5scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


static void z5bscroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz * 16 * 3;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz * 64;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz * 64;
  lXwk += lXwk * 2;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned int)scra_v_posit.l >> 3;
  lYwk += lYwk >> 1;
  lYwk = (unsigned int)lYwk >> 16 & 65535 | lYwk << 16 & -65536;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;
  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  if (enkeino & 1) {
    z5bline2(&psHscw);
    z5bline3(&psHscw);
    ldwk.w.l = -scrb_h_posit.w.h;
    for (i = 0; i < 18; ++i) {
      *psHscw++ = ldwk.w.l;
    }
  }
  else {
    z5bline0(&psHscw);
    z5bline1(&psHscw);
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone5scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


static void z5cscroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz * 16 * 3;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz * 64;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz * 128;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 2;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;
  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  if (enkeino & 1) {
    ldwk.w.l = -scrz_h_posit.w.h;
    for (i = 0; i < 14; ++i) {
      *psHscw++ = ldwk.w.l;
    }
    z5cline(&psHscw);
  }
  else {
    ldwk.w.l = -scrb_h_posit.w.h;
    for (i = 0; i < 10; ++i) {
      *psHscw++ = ldwk.w.l;
    }

    ldwk.w.l = -scrz_h_posit.w.h;
    for (i = 0; i < 22; ++i) {
      *psHscw++ = ldwk.w.l;
    }

    ldwk.w.l = -scrc_h_posit.w.h;
    for (i = 0; i < 4; ++i) {
      *psHscw++ = ldwk.w.l;
    }

    ldwk.w.l = -scrb_h_posit.w.h;
    for (i = 0; i < 12; ++i) {
      *psHscw++ = ldwk.w.l;
    }
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone5scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


static void z5dscroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int_union ldwk2, ldwk3;
  int i;
  int lXwk, lYwk;
  short sYnum;
  short *psHscr, *psHscw;
  short sYline, sYnumsv;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz * 32;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz * 64;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz * 128;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 3;
  lYwk += (lYwk >> 2) * 3;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;
  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;
  ldwk.w.h = -scra_h_posit.w.h;

  if (enkeino & 1) {
    ldwk.w.l = -scrc_h_posit.w.h;
    for (i = 0; i < 11; ++i) {
      *psHscw++ = ldwk.w.l;
    }
    z5dline0(&psHscw);
  }
  else {
    z5dline(&psHscw);

    ldwk.w.l = -scrb_h_posit.w.h;
    for (i = 0; i < 16; ++i) {
      *psHscw++ = ldwk.w.l;
    }
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  sYline = 39;
  sYnumsv = 29;
  if (enkeino & 1) {
    sYline = 28;

    sYnumsv -= sYline;
    psHscr = &hscrollwork[sYnum / 2];
    zone5scrsetsub0(scrb_v_posit.w.h, sYline, &pHscrbuf, psHscr);
  } else {
    if (sYline >= sYnum >> 1) {
      sYline -= sYnum >> 1;

      if (sYline > 28) {
        sYline = 28;
      }

      sYnumsv -= sYline;
      psHscr = &hscrollwork[sYnum / 2];
      zone5scrsetsub0(scrb_v_posit.w.h, sYline, &pHscrbuf, psHscr);
    }
  }

  if (!(enkeino & 1)) {
    ldwk.w.l = scrb_h_posit.w.h;
    ldwk2.w.l = scra_h_posit.w.h;
    ldwk2.w.l -= ldwk.w.l;
    ldwk2.l = ldwk2.w.l * 256 / 256 * 256;
    ldwk3.l = 0;
    ldwk3.w.l = ldwk.w.l;

    for (sYnumsv = sYnumsv * 8 - 1; sYnumsv >= 0; --sYnumsv) {
      ldwk.w.l = -ldwk3.w.l;
      pHscrbuf->l = ldwk.l;
      ++pHscrbuf;
      ldwk3.l = (unsigned int)ldwk3.l >> 16 & 65535 | ldwk3.l << 16 & -65536;
      ldwk3.l += ldwk2.l;
      ldwk3.l = (unsigned int)ldwk3.l >> 16 & 65535 | ldwk3.l << 16 & -65536;
    }
  }
}


static void z53cscroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;
  static int scaddtbl[5] = { 65536, 57344, 49152, 40960, 32768 };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz * 16 * 3;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz * 64;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz * 128;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 2;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;
  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  ldwk.w.l = -scrz_h_posit.w.h;
  for (i = 0; i < 14; ++i) {
    *psHscw++ = ldwk.w.l;
  }
  z5cline(&psHscw);

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone5scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


static void z53dscroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int_union ldwk2, ldwk3;
  int i;
  int lXwk, lYwk;
  short sYnum;
  short *psHscr, *psHscw;
  short sYline, sYnumsv;
  static int scaddtbl[5] = { 65536, 57344, 49152, 40960, 32768 };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz * 32;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz * 64;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz * 128;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 3;
  lYwk += (lYwk >> 2) * 3;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;
  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;
  ldwk.w.h = -scra_h_posit.w.h;

  z5dline(&psHscw);

  ldwk.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < 16; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 504) >> 2;
  sYline = 39;
  sYnumsv = 29;
  if (enkeino & 1) {
    sYline = 28;

    sYnumsv -= sYline;
    psHscr = &hscrollwork[sYnum / 2];
    zone5scrsetsub0(scrb_v_posit.w.h, sYline, &pHscrbuf, psHscr);
  } else {
    if ((sYline -= sYnum >> 1) >= 0) {
      if (sYline > 28) {
        sYline = 28;
      }

      sYnumsv -= sYline;
      psHscr = &hscrollwork[sYnum / 2];
      zone5scrsetsub0(scrb_v_posit.w.h, sYline, &pHscrbuf, psHscr);
    }
  }

  if (!(enkeino & 1)) {
    ldwk.w.l = scrb_h_posit.w.h;
    ldwk2.w.l = scra_h_posit.w.h;
    ldwk2.w.l -= ldwk.w.l;
    ldwk2.l = ldwk2.w.l * 256 / 256 * 256;
    ldwk3.l = 0;
    ldwk3.w.l = ldwk.w.l;

    for (sYnumsv = (sYnumsv >> 3) - 1; sYnumsv >= 0; --sYnumsv) {
      ldwk.w.l = -ldwk3.w.l;
      pHscrbuf->l = ldwk.l;
      ++pHscrbuf;
      ldwk3.l = (unsigned int)ldwk3.l >> 16 & 65535 | ldwk3.l << 16 & -65536;
      ldwk3.l += ldwk2.l;
      ldwk3.l = (unsigned int)ldwk3.l >> 16 & 65535 | ldwk3.l << 16 & -65536;
    }
  }
}


void z6scroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;
  int scrzloops[3] = { 2, 20, 24 };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz << 6;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz << 7;
  scrollc_h(lXwk, 16);

  lXwk = (scra_hz << 4) * 3;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 2;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  z6line(&psHscw);

  if ((time_flag_i & 0x7F) == 0) {
    ldwk.w.l = -scrb_h_posit.w.h;
    for (i = 0; i < 14; ++i) {
      *psHscw++ = ldwk.w.l;
    }
  }

  ldwk.w.l = -scrz_h_posit.w.h;
  for (i = 0; i < scrzloops[time_flag_i & 0x7F]; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  if ((time_flag_i & 0x7F) == 0) {
    ldwk.w.l = -scrc_h_posit.w.h;
    for (i = 0; i < 4; ++i) {
      *psHscw++ = ldwk.w.l;
    }

    ldwk.w.l = -scrz_h_posit.w.h;
    for (i = 0; i < 12; ++i) {
      *psHscw++ = ldwk.w.l;
    }

    ldwk.w.l = -scrc_h_posit.w.h;
    for (i = 0; i < 4; ++i) {
      *psHscw++ = ldwk.w.l;
    }

    ldwk.w.l = -scrz_h_posit.w.h;
    for (i = 0; i < 12; ++i) {
      *psHscw++ = ldwk.w.l;
    }

    ldwk.w.l = -scrc_h_posit.w.h;
    for (i = 0; i < 4; ++i) {
      *psHscw++ = ldwk.w.l;
    }

    if (stageno_i.b.l == 0) {
      ldwk.w.l = -scrz_h_posit.w.h;
      for (i = 0; i < 12; ++i) {
        *psHscw++ = ldwk.w.l;
      }

      ldwk.w.l = -scrc_h_posit.w.h;
      for (i = 0; i < 4; ++i) {
        *psHscw++ = ldwk.w.l;
      }
    }
  }
  else {
    ldwk.w.l = -scrc_h_posit.w.h;
    for (i = 0; i < 46; ++i) {
      *psHscw++ = ldwk.w.l;
    }
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 1016) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone6scrsetsub0(scrb_v_posit.w.h, 29, &pHscrbuf, psHscr);
}


static void z7scroll(void) {
  uint_union data;
  int hsCount;
  int i;
  int bloops[4] = { 4, 4, 8, 4 };
  int zloops[4] = { 20, 16, 16, 0 };
  int cloops[4] = { 0, 0, 18, 12 };

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;
  scrchk();
  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  if (stageno_i.b.l == 2) {
    if (generate_flag != 0) {
      scrollz_h(scra_hz << 7, 64);
      scrollc_h((long int)(scra_hz << 7) * 3, 16);
    }
    else {
      scrollz_h((long int)(scra_hz << 5) * 7, 64);
      scrollc_h((long int)(scra_hz << 6) * 5, 16);
    }
  }
  else {
    if ((time_flag_i & 0x7F) == 1) {
      scrollz_h(scra_hz << 6, 64);
    }
    else {
      scrollz_h((scra_hz << 6) + (scra_hz << 5), 64);
    }
    scrollc_h(scra_hz << 7, 16);
  }
  scrollb_h((long int)(scra_hz << 4) * 3, 4);

  data.l = 0;
  data.w.l = scra_v_posit.w.h;
  if (stageno_i.b.l == 0) {
    data.w.l = (data.w.l >> 2) + (data.w.l >> 3);
  }
  else if (stageno_i.b.l == 1) {
    data.w.l = (data.w.l >> 2) + (data.w.l >> 5);
  }
  scrollb_v(data.w.l);

  vscroll.w.l = scrb_v_posit.w.h;
  scrc_v_posit.w.h = scrb_v_posit.w.h;
  scrz_v_posit.w.h = scrb_v_posit.w.h;
  scrflagb.b.h |= scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = 0;
  scrflagc.b.h = 0;

  hsCount = 0;

  hsCount = z7line(hsCount);

  for (i = 0; i < bloops[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)]; ++i) {
    hscrollwork[hsCount] = -scrb_h_posit.w.h;
    ++hsCount;
  }

  hsCount = z7line0(hsCount);

  for (i = 0; i < zloops[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)]; ++i) {
    hscrollwork[hsCount] = -scrz_h_posit.w.h;
    ++hsCount;
  }

  for (i = 0; i < cloops[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)]; ++i) {
    hscrollwork[hsCount] = -scrc_h_posit.w.h;
    ++hsCount;
  }

  if ((time_flag_i & 0x7F) == 1) {
    hsCount = z7line1(hsCount);
  }

  data.w.l = scrb_v_posit.w.h;
  data.w.l &= 1016;
  data.w.l >>= 2;
  if ((time_flag_i & 0x7F) == 0) {
    waterdirec.w += 128;
  }
  zone7scrsetsub0(scrb_v_posit.w.h, data.w.l / 2);
}


static void z81scroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;
  static char z81scrtbl[5] = { 3, 4, 2, 0, 0 };
  static char z81bscrtbl0[9] = { 3, 3, 1, 5, 1, 1, 1, 1, 1 };
  static char z81bscrtbl1[7] = { 3, 1, 1, 3, 1, 1, 1 };
  int b0loops[3] = { 4, 16, 16 };
  int b1loops[3] = { 8, 12, 12 };
  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz << 6;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz << 7;
  scrollc_h(lXwk, 16);

  lXwk = (scra_hz << 4) * 3;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 2;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  if ((time_flag_i & 0x7F) == 0) {
    z81line(&psHscw, z81bscrtbl0, 26, 8);
  }
  else {
    z81line(&psHscw, z81scrtbl, 14, 4);
  }

  ldwk.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < b0loops[time_flag_i & 0x7F]; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 28; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  if ((time_flag_i & 0x7F) == 0) {
    z81line(&psHscw, z81bscrtbl1, 18, 6);
  }
  else {
    z81line(&psHscw, z81scrtbl, 14, 4);
  }

  ldwk.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < b0loops[time_flag_i & 0x7F]; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 12; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 1016) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone8scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


void z82scroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz << 6;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz << 7;
  scrollc_h(lXwk, 16);

  lXwk = (scra_hz << 4) * 3;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 3;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  ldwk.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < 6; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  z82line0(&psHscw);

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 18; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  z82line1(&psHscw);

  ldwk.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < 10; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 1016) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone8scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


static void z82bscroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz << 6;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz << 7;
  scrollc_h(lXwk, 16);

  lXwk = (scra_hz << 4) * 3;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 3;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  z82line1(&psHscw);

  ldwk.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < 4; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  z82line0(&psHscw);

  ldwk.w.l = -scrz_h_posit.w.h;
  for (i = 0; i < 10; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 12; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 1016) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone8scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


static void z82cscroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz << 6;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz << 7;
  scrollc_h(lXwk, 16);

  lXwk = (scra_hz << 4) * 3;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 3;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  z82line1(&psHscw);

  ldwk.w.l = -scrz_h_posit.w.h;
  for (i = 0; i < 14; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  z82line0(&psHscw);

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 12; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 1016) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone8scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


static void z83cscroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = scra_hz << 7;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz << 7;
  scrollc_h(lXwk, 16);

  lXwk = (scra_hz << 4) * 3;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned int)scra_v_posit.l >> 3;
  lYwk = (unsigned int)lYwk >> 16 & 65535 | lYwk << 16 & -65536;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  z83cline1(&psHscw);

  ldwk.w.l = -scrz_h_posit.w.h;
  for (i = 0; i < 18; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  z83cline0(&psHscw);

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 1016) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone8scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


static void z83dscroll(void) {
  int_union ldwk;
  int_union* pHscrbuf;
  int i;
  int lXwk;
  int lYwk;
  short sYnum;
  short* psHscr;
  short* psHscw;

  if (scroll_start.b.h) return;

  scrflaga.w = scrflagb.w = scrflagc.w = scrflagz.w = 0;

  scrchk();

  scroll_h();
  scroll_v();

  vscroll.w.h = scra_v_posit.w.h;
  vscroll.w.l = scrb_v_posit.w.h;

  lXwk = (scra_hz << 6) * 3;
  scrollz_h(lXwk, 64);

  lXwk = scra_hz << 8;
  scrollc_h(lXwk, 16);

  lXwk = scra_hz << 7;
  scrollb_h(lXwk, 4);

  lYwk = (unsigned short)scra_v_posit.w.h >> 3;

  scrollb_v(lYwk);

  scrc_v_posit.w.h = scrz_v_posit.w.h = vscroll.w.l = scrb_v_posit.w.h;

  scrflagb.b.h = scrflagb.b.h | scrflagz.b.h | scrflagc.b.h;
  scrflagz.b.h = scrflagc.b.h = 0;

  psHscw = hscrollwork;

  ldwk.w.l = -scrb_h_posit.w.h;
  for (i = 0; i < 34; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  ldwk.w.l = -scrz_h_posit.w.h;
  for (i = 0; i < 6; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  ldwk.w.l = -scrc_h_posit.w.h;
  for (i = 0; i < 8; ++i) {
    *psHscw++ = ldwk.w.l;
  }

  pHscrbuf = hscrollbuff;
  sYnum = (unsigned short)(scrb_v_posit.w.h & 1016) >> 2;
  psHscr = &hscrollwork[sYnum / 2];
  zone8scrsetsub0(scrb_v_posit.w.h, 28, &pHscrbuf, psHscr);
}


static int z41aline(int hsCount) {
  int temp;
  int_union data;
  int i, j;
  int z41ascrtbl[5] = { 14, 10, 4, 2, 2 };

  temp = scra_h_posit.w.h - scrz_h_posit.w.h;
  temp <<= 7;
  temp /= 5;
  temp <<= 9;
  data.l = 0;
  data.w.l = scrz_h_posit.w.h;
  for (i = 0; i < 5; ++i) {
    for (j = 0; j < z41ascrtbl[4 - i]; ++j) {
      hscrollwork[hsCount] = -data.w.l;
      ++hsCount;
    }
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
    data.l += temp;
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
  }
  return hsCount;
}


static void z5aline0(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51ascrtbl0[6] = { 13, 11, 1, 1, 1, 1 };

  lHwk = scra_h_posit.w.h - scrz_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 64 / 12;
  lHwk *= 1024;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrz_h_posit.w.h;

  *ppHscw += 34;

  for (i = 5; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51ascrtbl0[i]; j >= 0; --j) {
      --*ppHscw;
      **ppHscw = wk;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
  *ppHscw += 34;
}


static void z5aline1(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51ascrtbl1[7] = { 15, 19, 1, 1, 1, 1, 1 };

  lHwk = scra_h_posit.w.h - scrz_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 64 / 14;
  lHwk *= 1024;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrz_h_posit.w.h;

  for (i = 6; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51ascrtbl1[i]; j >= 0; --j) {
      **ppHscw = wk;
      ++*ppHscw;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
}


static void z5aline2(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51ascrtbl2[11] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

  lHwk = scra_h_posit.w.h - scrz_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 128 / 22;
  lHwk *= 512;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrz_h_posit.w.h;
  *ppHscw += 22;

  for (i = 10; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51ascrtbl2[i]; j >= 0; --j) {
      --*ppHscw;
      **ppHscw = wk;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
  *ppHscw += 22;
}


static void z5aline3(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51ascrtbl3[3] = {
    31, 3, 5
  };

  lHwk = scra_h_posit.w.h - scrz_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 64 / 12;
  lHwk *= 1024;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrz_h_posit.w.h;

  for (i = 2; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51ascrtbl3[i]; j >= 0; --j) {
      **ppHscw = wk;
      ++*ppHscw;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
}


static void z5bline0(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51bscrtbl0[4] = { 7, 3, 1, 5 };

  lHwk = scra_h_posit.w.h - scrz_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 64 / 8;
  lHwk *= 1024;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrz_h_posit.w.h;
  *ppHscw += 20;

  for (i = 3; i >= 0; --i) {
    wk = -ldHposwk.w.l;


    for (j = z51bscrtbl0[i]; j >= 0; --j) {
      --*ppHscw;
      **ppHscw = wk;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
  *ppHscw += 20;
}


static void z5bline1(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51bscrtbl1[12] = { 1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 0, 6 };

  lHwk = scra_h_posit.w.h - scrc_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 64 / 12;
  lHwk *= 1024;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrc_h_posit.w.h;

  for (i = 11; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51bscrtbl1[i]; j >= 0; --j) {
      **ppHscw = wk;
      ++*ppHscw;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
}


static void z5bline2(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51bscrtbl2[4] = { 3, 1, 1, 4 };

  lHwk = scra_h_posit.w.h - scrz_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 64 / 8;
  lHwk *= 1024;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrz_h_posit.w.h;
  *ppHscw += 13;

  for (i = 3; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51bscrtbl2[i]; j >= 0; --j) {
      --*ppHscw;
      **ppHscw = wk;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
  *ppHscw += 13;
}


static void z5bline3(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51bscrtbl3[10] = { 0, 2, 0, 2, 0, 2, 1, 1, 1, 2 };

  lHwk = scrb_h_posit.w.h - scrc_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 64 / 14;
  lHwk *= 1024;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrc_h_posit.w.h;

  for (i = 9; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51bscrtbl3[i]; j >= 0; --j) {
      **ppHscw = wk;
      ++*ppHscw;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
}


static void z5cline(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51cscrtbl[3] = { 39, 3, 9 };

  lHwk = scra_h_posit.w.h - scrc_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 128 / 12;
  lHwk *= 512;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrc_h_posit.w.h;

  for (i = 2; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51cscrtbl[i]; j >= 0; --j) {
      **ppHscw = wk;
      ++*ppHscw;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
}


static void z5dline(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51dscrtbl[3] = { 5, 11, 5 };

  lHwk = scra_h_posit.w.h - scrb_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 64 / 6;
  lHwk *= 1024;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrb_h_posit.w.h;
  *ppHscw += 24;

  for (i = 2; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51dscrtbl[i]; j >= 0; --j) {
      --*ppHscw;
      **ppHscw = wk;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }

  *ppHscw += 24;
}


static void z5dline0(short** ppHscw) {
  int lHwk;
  int_union ldHposwk;
  int i, j;
  short wk;
  char z51dscrtbl0[6] = { 13, 7, 5, 3, 3, 0 };

  lHwk = scra_h_posit.w.h - scrc_h_posit.w.h;
  lHwk = (unsigned int)lHwk * 128 / 12;
  lHwk *= 512;

  ldHposwk.l = 0;
  ldHposwk.w.l = scrc_h_posit.w.h;

  for (i = 5; i >= 0; --i) {
    wk = -ldHposwk.w.l;

    for (j = z51dscrtbl0[i]; j >= 0; --j) {
      **ppHscw = wk;
      ++*ppHscw;
    }

    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
    ldHposwk.l += lHwk;
    ldHposwk.l = (unsigned int)ldHposwk.l >> 16 & 65535 | ldHposwk.l << 16 & -65536;
  }
}


static void z6line(short** ppHscw) {
  char z6ascrtbl[10] = { 5, 3, 3, 2, 2, 1, 1, 1, 1, 1 };
  char z6bscrtbl[17] = { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0 };
  char z6cscrtbl[9] = { 5, 3, 2, 2, 1, 1, 1, 1, 1 };
  char* z6scrtbls[3] = { z6bscrtbl, z6ascrtbl, z6cscrtbl };
  int i, j;
  short sXwk, sinwk, coswk, hwk;
  int_union radwk;
  int lXwk, lHwk;
  int values[3][2] = { { 28, 16 }, { 30, 9 }, { 26, 8 } };
  lXwk = scra_h_posit.w.h - scrb_h_posit.w.h;
  if ((time_flag_i & 0x7F) == 0) {
    lXwk <<= 7;
    lXwk /= 17;
    lXwk <<= 9;
  }
  else {
    radwk.w.l = 0;
    sXwk = scrb_h_posit.w.h;
  }

  *ppHscw += values[time_flag_i & 0x7F][0];

  for (i = values[time_flag_i & 0x7F][1]; i >= 0; --i) {
    if ((time_flag_i & 0x7F) != 0) {
      sinset(radwk.w.l, &sinwk, &coswk);
      lHwk = (256 - coswk) * lXwk;
      lHwk = (unsigned int)lHwk >> 8;
      hwk = -(lHwk + sXwk);
    }
    for (j = z6scrtbls[time_flag_i & 0x7F][i]; j >= 0; --j) {
      --*ppHscw;
      if ((time_flag_i & 0x7F) != 0) {
        **ppHscw = hwk;
      }
      else {
        **ppHscw = -radwk.w.l;
      }
    }

    if ((time_flag_i & 0x7F) == 0) {
      radwk.l = (unsigned int)radwk.l >> 16 & 65535 | radwk.l << 16 & -65536;
      radwk.l += lXwk;
      radwk.l = (unsigned int)radwk.l >> 16 & 65535 | radwk.l << 16 & -65536;
    }
    else {
      radwk.w.l += 6;
    }
  }

  *ppHscw += values[time_flag_i & 0x7F][0];
}


static int z7line(int hsCount) {
  int temp;
  int_union data;
  int i, j;
  int z7scrtbl[37] = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int z7cscrtbl[39] = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int z7dscrtbl[16] = { 3, 3, 1, 1, 0, 0, 3, 3, 1, 3, 1, 1, 1, 1, 0, 0 };
  int* z7scrtbls[4] = { z7scrtbl, z7scrtbl, z7dscrtbl, z7cscrtbl };
  int values[3][4][4] = {
    { { 7, 37, 9, 44 }, { 7, 37, 9, 44 }, { 6, 16, 10, 38 }, { 6, 39, 10, 46 } },
    { { 7, 37, 9, 44 }, { 7, 37, 9, 44 }, { 6, 16, 10, 38 }, { 6, 39, 10, 46 } },
    { { 0 }, { 0 }, { 5, 16, 11, 38 }, { 6, 39, 10, 46 }
    }
  };

  if (stageno_i.b.l == 2) {
    temp = scra_h_posit.w.h * 2 - scrb_h_posit.w.h;
  }
  else {
    temp = scra_h_posit.w.h - scrb_h_posit.w.h;
  }
  temp <<= values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][0];
  temp /= values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1];
  temp <<= values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][2];
  data.l = 0;
  data.w.l = scrb_h_posit.w.h;
  hsCount += values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][3];
  for (i = 0; i < values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1]; ++i) {
    for (j = -1; j < z7scrtbls[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1] - 1 - i]; ++j) {
      --hsCount;
      hscrollwork[hsCount] = -data.w.l;
    }
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
    data.l += temp;
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
  }
  hsCount += values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][3];
  return hsCount;
}


static int z7line0(int hsCount) {
  int temp;
  int_union data;
  int i, j;
  int z7ascrtbl0[12] = { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int z7bscrtbl0[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  int z7cscrtbl0[10] = { 7, 3, 3, 5, 3, 3, 0, 0, 0, 0 };
  int z7dscrtbl0[16] = { 3, 3, 1, 1, 0, 0, 3, 3, 1, 3, 1, 1, 1, 1, 0, 0 };
  int z72dscrtbl0[11] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 };
  int* z7scrtbl0s[3][4] = {
    { z7bscrtbl0, z7ascrtbl0, z7dscrtbl0, z7cscrtbl0 },
    { z7bscrtbl0, z7ascrtbl0, z72dscrtbl0, z7cscrtbl0 },
    { 0, 0, z7dscrtbl0, z7cscrtbl0 }
  };
  int values[3][4][3] = {
    { { 7, 8, 9 }, { 7, 12, 9 }, { 6, 16, 10 }, { 6, 10, 10 } },
    { { 7, 8, 9 }, { 7, 12, 9 }, { 6, 11, 10 }, { 6, 10, 10 } },
    { { 0 }, { 0 }, { 5, 16, 11 }, { 4, 10, 12 } }
  };

  temp = scrz_h_posit.w.h - scrb_h_posit.w.h;
  temp <<= values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][0];
  temp /= values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1];
  temp <<= values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][2];
  data.l = 0;
  data.w.l = scrb_h_posit.w.h;
  for (i = 0; i < values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1]; ++i) {
    for (j = -1; j < z7scrtbl0s[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][values[stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1] - 1 - i]; ++j) {
      hscrollwork[hsCount] = -data.w.l;
      ++hsCount;
    }
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
    data.l += temp;
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
  }
  return hsCount;
}


static int z7line1(int hsCount) {
  int temp;
  int_union data;
  int i, j;
  int z71ascrtbl1[2] = { 9, 7 };

  temp = scrc_h_posit.w.h - scra_h_posit.w.h;
  temp <<= 7;
  temp /= 8;
  temp <<= 9;
  data.l = 0;
  data.w.l = scrc_h_posit.w.h;
  for (i = 0; i < 2; ++i) {
    for (j = -1; j < z71ascrtbl1[1 - i]; ++j) {
      hscrollwork[hsCount] = -data.w.l;
      ++hsCount;
    }
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
    data.l += temp;
    data.l = (unsigned int)data.l >> 16 & 65535 | data.l << 16 & -65536;
  }
  return hsCount;
}


static void z81line(short** ppHscw, char* pScrTbl, short AddrOffs, short LoopNum) {
  int i, j;
  int lXwk;
  int_union ldwk;
  short wk;

  lXwk = scrc_h_posit.w.h - scrz_h_posit.w.h;
  lXwk = (unsigned int)(lXwk << 7) / 5 << 9;
  ldwk.w.h = -scra_h_posit.w.h;
  ldwk.w.l = scrz_h_posit.w.h;
  *ppHscw += AddrOffs;

  for (i = LoopNum; i >= 0; --i) {
    wk = -ldwk.w.l;

    for (j = pScrTbl[i]; j >= 0; --j) {
      --*ppHscw;
      **ppHscw = wk;
    }

    ldwk.l = (unsigned int)ldwk.l >> 16 & 65535 | ldwk.l << 16 & -65536;
    ldwk.l += lXwk;
    ldwk.l = (unsigned int)ldwk.l >> 16 & 65535 | ldwk.l << 16 & -65536;
  }

  *ppHscw += AddrOffs;
}


static void z82line0(short** ppHscw) {
  int i, j;
  int lXwk;
  int_union ldwk;
  short wk;
  static char z82scrtbl0[7] = { 0, 0, 0, 0, 1, 1, 1 };
  static char z82bscrtbl0[8] = { 1, 1, 0, 0, 0, 0, 0, 0 };
  static char z82cscrtbl0[7] = { 9, 1, 1, 0, 0, 0, 0 };
  static char* z82scrtbl0s[4] = {
    z82bscrtbl0,
    z82scrtbl0,
    z82scrtbl0,
    z82cscrtbl0
  };
  int values[4][4] = {
    { 6, 8, 10, 7 },
    { 7, 5, 9, 6 },
    { 7, 5, 9, 6 },
    { 5, 7, 11, 6 }
  };

  if ((time_flag_i & 0x7F) == 0) {
    lXwk = scrz_h_posit.w.h - scrb_h_posit.w.h;
  }
  else {
    lXwk = scrc_h_posit.w.h - scrz_h_posit.w.h;
  }
  lXwk = (unsigned int)(lXwk << values[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][0]) / values[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1] << values[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][2];
  if ((time_flag_i & 0x7F) != 1) {
    ldwk.w.h = -scra_h_posit.w.h;
  }
  if ((time_flag_i & 0x7F) == 0) {
    ldwk.w.l = scrb_h_posit.w.h;
  }
  else {
    ldwk.w.l = scrz_h_posit.w.h;
  }

  for (i = values[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][3]; i >= 0; --i) {
    wk = -ldwk.w.l;

    for (j = z82scrtbl0s[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][i]; j >= 0; --j) {
      **ppHscw = wk;
      ++*ppHscw;
    }

    ldwk.l = (unsigned int)ldwk.l >> 16 & 65535 | ldwk.l << 16 & -65536;
    ldwk.l += lXwk;
    ldwk.l = (unsigned int)ldwk.l >> 16 & 65535 | ldwk.l << 16 & -65536;
  }
}


static void z82line1(short** ppHscw) {
  int i, j;
  int lXwk;
  int_union ldwk;
  short wk;
  static char z82scrtbl1[7] = { 0, 0, 0, 0, 1, 9, 1 };
  static char z82bscrtbl1[12] = { 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1 };
  static char z82cscrtbl1[5] = { 3, 3, 3, 3, 3 };
  static char* z82scrtbl1s[4] = {
    z82bscrtbl1,
    z82scrtbl1,
    z82scrtbl1,
    z82cscrtbl1
  };
  int values[4][5] = {
    { 6, 12, 10, 28, 11 },
    { 7, 5, 9, 18, 6 },
    { 7, 5, 9, 18, 6 },
    { 5, 5, 11, 20, 4 }
  };
  if ((time_flag_i & 0x7F) == 1 || ((time_flag_i & 0x7F) == 2 && generate_flag == 0)) {
    lXwk = scrc_h_posit.w.h - scrz_h_posit.w.h;
  }
  else {
    lXwk = scra_h_posit.w.h - scrb_h_posit.w.h;
  }
  lXwk = (unsigned int)(lXwk << values[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][0]) / values[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1] << values[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][2];
  if ((time_flag_i & 0x7F) != 1) {
    ldwk.w.h = -scra_h_posit.w.h;
  }
  if ((time_flag_i & 0x7F) == 0) {
    ldwk.w.l = scrb_h_posit.w.h;
  }
  else {
    ldwk.w.l = scrz_h_posit.w.h;
  }
  *ppHscw += values[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][3];

  for (i = values[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][4]; i >= 0; --i) {
    wk = -ldwk.w.l;

    for (j = z82scrtbl1s[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][i]; j >= 0; --j) {
      --*ppHscw;
      **ppHscw = wk;
    }

    ldwk.l = (unsigned int)ldwk.l >> 16 & 65535 | ldwk.l << 16 & -65536;
    ldwk.l += lXwk;
    ldwk.l = (unsigned int)ldwk.l >> 16 & 65535 | ldwk.l << 16 & -65536;
  }
  *ppHscw += 18;
}


static void z83cline0(short** ppHscw) {
  int lWk1, lWk2;
  int_union ldWk1, ldWk2;
  int i, j;
  static char z83cscrtbl0[5] = { 3, 3, 3, 1, 1 };

  lWk1 = scrz_h_posit.w.h;
  lWk2 = scra_h_posit.w.h;
  line_div(lWk1, &lWk2, 5);

  ldWk1.w.h = -scra_h_posit.w.h;
  ldWk2.l = scrz_h_posit.w.h;

  for (i = 4; i >= 0; --i) {
    ldWk1.w.l = -ldWk2.w.l;

    for (j = z83cscrtbl0[i]; j >= 0; --j) {
      **ppHscw = ldWk1.w.l;
      ++*ppHscw;
    }

    ldWk2.l = (unsigned int)ldWk2.l >> 16 & 65535 | ldWk2.l << 16 & -65536;
    ldWk2.l += lWk2;
    ldWk2.l = (unsigned int)ldWk2.l >> 16 & 65535 | ldWk2.l << 16 & -65536;
  }
}


static void z83cline1(short** ppHscw) {
  int lWk1, lWk2;
  int_union ldWk1, ldWk2;
  int i, j;
  static char z83cscrtbl1[5] = { 1, 3, 1, 3, 1 };

  lWk1 = scrb_h_posit.w.h;
  lWk2 = scra_h_posit.w.h;
  line_div(lWk1, &lWk2, 5);

  ldWk1.w.h = -scra_h_posit.w.h;
  ldWk2.l = scrb_h_posit.w.h;
  *ppHscw += 14;

  for (i = 4; i >= 0; --i) {
    ldWk1.w.l = -ldWk2.w.l;

    for (j = z83cscrtbl1[i]; j >= 0; --j) {
      --*ppHscw;
      **ppHscw = ldWk1.w.l;
    }

    ldWk2.l = (unsigned int)ldWk2.l >> 16 & 65535 | ldWk2.l << 16 & -65536;
    ldWk2.l += lWk2;
    ldWk2.l = (unsigned int)ldWk2.l >> 16 & 65535 | ldWk2.l << 16 & -65536;
  }

  *ppHscw += 14;
}


static void line_div(int hWk1, int* hWk2, short sD6) {
  *hWk2 = (unsigned int)(*hWk2 - hWk1 << 6) / sD6 << 10;
}


static void zone1scrsetsub0(short yoffs, short yline, int_union** pHscrbuf, short* pHscrwk) {
  int i, j;
  int_union ldwk;

  ldwk.l = 0;
  if (stageno_i.b.l == 1) {
    ldwk.w.h = -scra_h_posit.w.h;
  }

  for (i = 0, j = yoffs & 7; yline >= i; ++i, j = 0) {
    ldwk.w.l = *pHscrwk;
    ++pHscrwk;

    for ( ; j < 8; ++j, ++*pHscrbuf) {
      (*pHscrbuf)->l = ldwk.l;
    }
  }
}


static void zone3scrsetsub0(int_union** ppA1, unsigned short** ppA2, unsigned short* pA3, unsigned char* pA4, unsigned short wD1, unsigned short* pwD2, unsigned short* pwD4) {
  int_union* pA1;
  unsigned short* pA2;
  unsigned short wD3, wD6;
  int_union lD0;
  int i;

  lD0.w.h = -scra_h_posit.w.h;
  pA1 = *ppA1;
  pA2 = *ppA2;

  if (*pA3 <= *pwD4) goto label6;

label1:
  *pwD2 &= 7;
  *pwD4 = *pwD4 + 8 - *pwD2;

  lD0.w.l = *pA2++;
  i = 8 - *pwD2;
  goto label4;

label2:
  if ((short)wD1 < 0) goto label5;

  if (*pA3 <= *pwD4) goto label7;

label3:
  lD0.w.l = *pA2++;
  *pwD4 += 8;

  i = 8;
label4:
  for ( ; i > 0; --i) {
    pA1->l = lD0.l;
    ++pA1;
  }
  if ((short)--wD1 >= 0) goto label2;

label5:
  *ppA1 = pA1;
  *ppA2 = pA2;
  return;

label6:
  if (STAGE_IS_R31B || STAGE_IS_R32B) {
    wD3 = *pA3++ + 32 - *pwD4;
  }
  else {
    wD3 = *pA3++ + 24 - *pwD4;
  }
  if ((short)wD3 > 0) goto label8;

  if (*pA3 > *pwD4) goto label1;

  if (STAGE_IS_R31B || STAGE_IS_R32B) {
    wD3 = *pA3++ + 32 - *pwD4;
  }
  else {
    wD3 = *pA3++ + 24 - *pwD4;
  }
  if ((short)wD3 > 0) goto label8;
  goto label1;

label7:
  wD3 = *pA3++ + 24 - *pwD4;
  if ((short)wD3 <= 0) goto label3;

label8:
  --wD3;
  wD6 = wD3;
  *pwD2 = (unsigned char)waterdirec.b.h;

  do {
    *pwD2 &= 255;
    lD0.w.l = (char)pA4[*pwD2];
    lD0.w.l += scrb_h_posit.w.h;
    lD0.w.l = -lD0.w.l;
    pA1->w.h = lD0.w.h;
    pA1->w.l = lD0.w.l;
    ++pA1;
    ++*pwD4;
    ++*pwD2;
  } while ((short)--wD3 >= 0);

  wD6 >>= 3;

  do {
    lD0.w.l = *pA2++;
    --wD1;
  } while ((short)--wD6 >= 0);
  goto label2;
}


static void zone4scrsetsub0(short HPosi, short VPosi, unsigned short offs) {
  int_union* pHScrollBuff;
  int_union hsw;
  short_union data1, data2;
  short avp;
  int i;

  pHScrollBuff = hscrollbuff;
  data1.b.l = waterdirec.b.h;
  data2.b.l = waterdirec.b.h;
  waterdirec.w += 128;
  data1.w += scrb_v_posit.w.h;
  data1.b.h = 0;
  data2.w += scra_v_posit.w.h;
  data2.b.h = 0;

  VPosi &= 7;
  hsw.w.l = hscrollwork[offs++];
  avp = scra_v_posit.w.h;
  i = 232;

  do {
    if (avp > waterposi) {
      do {
        pHScrollBuff->w.h = HPosi;
        pHScrollBuff->w.l = (short)(char)awasintbl[data1.w] + hsw.w.l;
        ++pHScrollBuff;
        ++data1.b.l;
        ++data2.b.l;
        ++VPosi;
        if (VPosi == 8) {
          VPosi = 0;
          hsw.w.l = hscrollwork[offs++];
        }
      } while (--i > 0);

      return;
    }
    pHScrollBuff->l = hsw.l;
    ++pHScrollBuff;
    ++avp;
    ++data1.b.l;
    ++data2.b.l;
    ++VPosi;
    if (VPosi == 8) {
      VPosi = 0;
      hsw.w.l = hscrollwork[offs++];
    }
  } while (--i > 0);
}


static void zone5scrsetsub0(short yoffs, short yline, int_union** pHscrbuf, short* pHscrwk) {
  int i, j;
  int_union ldwk;

  ldwk.l = 0;
  if (STAGE_IS_R51A) {
    ldwk.w.h = -scra_h_posit.w.h;
  }
  else if (STAGE_IS_R51B) {
    ldwk.w.h = -scrb_h_posit.w.h;
  }

  for (i = 0, j = yoffs & 7 ; yline >= i; ++i, j = 0) {
    ldwk.w.l = *pHscrwk;
    ++pHscrwk;

    for ( ; j < 8; ++j, ++*pHscrbuf) {
      (*pHscrbuf)->l = ldwk.l;
    }
  }
}


static void zone6scrsetsub0(short yoffs, short yline, int_union** pHscrbuf, short* pHscrwk) {
  int i, j;
  int_union ldwk;

  ldwk.l = 0;
  ldwk.w.h = -scra_h_posit.w.h;

  for (i = 0, j = yoffs & 7 ; yline >= i; ++i, j = 0) {
    ldwk.w.l = *pHscrwk;
    ++pHscrwk;

    for ( ; j < 8; ++j, ++*pHscrbuf) {
      (*pHscrbuf)->l = ldwk.l;
    }
  }
}


static void zone7scrsetsub0(short VPosi, unsigned short offs) {
  int_union* pHScrollBuff;
  int_union hsw;
  int i, j;
  short VPosi2;
  short wD2;
  short sin;
  short cos;

  pHScrollBuff = hscrollbuff;

  if ((time_flag_i & 0x7F) == 0) {
    VPosi2 = VPosi + 8;
  }
  VPosi &= 7;
  if ((time_flag_i & 0x7F) == 0) {
    VPosi2 -= VPosi;
  }
  hsw.l = 0;
  hsw.w.l = hscrollwork[offs++];

  j = VPosi;
  while (j < 8) {
    pHScrollBuff->l = hsw.l;
    ++pHScrollBuff;
    ++j;
  }
  for (i = 29; i > 0; --i) {
    if ((time_flag_i & 0x7F) == 0 && (unsigned short)VPosi2 >= 616) {
      ++i;
      i *= 8;
      --i;
      wD2 = (unsigned short)waterdirec.b.h;

      do {
        sinset(wD2 & 255, &sin, &cos);
        sin = (unsigned short)sin >> 5;
        sin += scrz_h_posit.w.h;
        sin *= -1;
        pHScrollBuff->l = (unsigned short)sin;
        ++pHScrollBuff;
        wD2 += 2;
        --i;
      } while (i >= 0);
      break;
    }
    hsw.w.l = hscrollwork[offs++];
    for (j = 0; j < 8; ++j) {
      pHScrollBuff->l = hsw.l;
      ++pHScrollBuff;
    }
    if ((time_flag_i & 0x7F) == 0) {
      VPosi2 += 8;
    }
  }
}


static void zone8scrsetsub0(short yoffs, short yline, int_union** pHscrbuf, short* pHscrwk) {
  int i, j;
  int_union ldwk;

  ldwk.l = 0;
  ldwk.w.h = -scra_h_posit.w.h;

  for (i = 0, j = yoffs & 7 ; yline >= i; ++i, j = 0) {
    ldwk.w.l = *pHscrwk;
    ++pHscrwk;

    for ( ; j < 8; ++j, ++*pHscrbuf) {
      (*pHscrbuf)->l = ldwk.l;
    }
  }
}


static void scroll_h(void) {
  short xwk;
  unsigned char bXwk;
  unsigned char flipcondition[7][3][3] = {
    { { 0, 0, 0 }, { 1, 0, 1 }, { 0, 0, 1 } },
    { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
    { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
    { { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 1 } },
    { { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 1 } },
    { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
    { { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 1 } }
  };

  xwk = scra_h_posit.w.h;

  scrh_move();
  bXwk = (unsigned char)(scra_h_posit.w.h & 16) ^ scra_h_count;
  if (flipcondition[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F] != 0) {
    bXwk = !bXwk;
  }
  if (bXwk != 0) {
    scra_h_count ^= 16;
    if (scra_h_posit.w.h - xwk < 0) {
      scrflaga.b.h |= 4;
    }
    else scrflaga.b.h |= 8;
  }
}


static void scrh_move(void) {
  short xwk;

  xwk = actwk[0].xposi.w.h - scra_h_posit.w.h - scra_hline;
  if (xwk == 0) {
    scra_hz = 0;
  }
  else {
    if (xwk < 0) {
      /* left_check */
      if (xwk < -16) {
        xwk = -16;
      }

      xwk += scra_h_posit.w.h;
      if (xwk < scralim_left) {
        xwk = scralim_left;
      }
    }
    else {
      /* right_check */
      if (xwk > 16) {
        xwk = 16;
      }

      xwk += scra_h_posit.w.h;
      if (xwk > scralim_right) {
        xwk = scralim_right;
      }
    }

    scra_hz = xwk - scra_h_posit.w.h << 8;
    scra_h_posit.w.h = xwk;
  }
}


static void scroll_v(void) {
  short ywk;

  ywk = actwk[0].yposi.w.h - scra_v_posit.w.h;
  if (actwk[0].cddat & 4) {
    ywk -= 5;
  }

  if (actwk[0].cddat & 2) {
    ywk += 32;
    if (scra_vline > ywk) {
      ywk -= scra_vline;
      sv_move_main2(ywk);
      return;
    }
    ywk -= scra_vline;
    if (ywk >= 64) {
      ywk -= 64;
      sv_move_main2(ywk);
      return;
    }
    ywk -= 64;
    if (!limmoveflag) goto label1;
    sv_move_sub2();
    return;
  }

  ywk -= scra_vline;
  if (ywk != 0) {
    sv_move_main(ywk);
    return;
  }
  if (limmoveflag != (STAGE_IS_R11A || stageno_i.b.h == 1 || stageno_i.b.h == 2 || stageno_i.b.h == 5)) {
    sv_move_sub2();
    return;
  }

label1:
  scra_vz = 0;
}


static void sv_move_main(short yPos) {
  short spdwk;

  if (scra_vline == 96) {
    if (actwk[0].mspeed.w < 0) {
      spdwk = -actwk[0].mspeed.w;
    }
    else {
      spdwk = actwk[0].mspeed.w;
    }

    if (spdwk >= 2048) {
      sv_move_main2(yPos);
    }
    else {
      if (yPos > 6) {
        sv_move_plus(1536);
      }
      else if (yPos < -6) {
        sv_move_minus(1536);
      }
      else {
        sv_move_sub(yPos);
      }
    }
  }
  else {
    /* sv_move_main1 */
    if (yPos > 2) {
      sv_move_plus(512);
    }
    else if (yPos < -2) {
      sv_move_minus(512);
    }
    else {
      sv_move_sub(yPos);
    }
  }
}


static void sv_move_main2(short yPos) {
  if (yPos > 16) {
    sv_move_plus(4096);
  }
  else if (yPos < -16) {
    sv_move_minus(4096);
  }
  else {
    sv_move_sub(yPos);
  }
}


static void sv_move_sub(short yPos) {
  int_union lSpd;
  int result;

  lSpd.w.h = 0;
  lSpd.w.l = yPos + scra_v_posit.w.h;
  if (STAGE_IS_R11A || stageno_i.b.h == 1 || stageno_i.b.h == 2 || stageno_i.b.h == 5) {
    result = yPos <= 0;
  }
  else {
    result = yPos < 0;
  }
  if (result) {
    scrv_up_ch(lSpd);
  }
  else {
    scrv_down_ch(lSpd);
  }
}


static void sv_move_sub2(void) {
  limmoveflag = 0;
  sv_move_sub(0);
}


static void sv_move_minus(short sSpd) {
  int_union lSpd;
  short wk;

  lSpd.l = (-sSpd << 8) + scra_v_posit.l;

  wk = lSpd.w.h;
  lSpd.w.h = lSpd.w.l;
  lSpd.w.l = wk;
  scrv_up_ch(lSpd);
}


static void scrv_up_ch(int_union lSpd) {
  if (lSpd.w.l <= scralim_up) {
    if (lSpd.w.l > -256) {
      lSpd.w.l = scralim_up;
    }
    else if (stageno_i.b.h == 2 && stageno_i.b.l == 1) {
      lSpd.w.l += 2048;
      actwk[0].yposi.w.h += 2048;
      scra_v_posit.w.h += 2048;
      scrb_v_posit.w.h &= 1023;
    }
    else if (stageno_i.b.h == 2 && stageno_i.b.l == 2) {
      lSpd.w.l &= 2047;
      actwk[0].yposi.w.h &= 2048;
      scra_v_posit.w.h &= 2048;
      scrb_v_posit.w.h &= 2048;
    }
    else {
      lSpd.w.l &= 2047;
      if (STAGE_IS_R11A || stageno_i.b.h == 1) {
        actwk[0].yposi.w.h &= 32767;
      }
      else {
        actwk[0].yposi.w.h &= 2047;
      }
      scra_v_posit.w.h &= 2047;
      scrb_v_posit.w.h &= 1023;
    }
  }
  scrv_move(lSpd);
}


static void sv_move_plus(short sSpd) {
  int_union lSpd;
  short wk;

  lSpd.l = (sSpd << 8) + scra_v_posit.l;

  wk = lSpd.w.h;
  lSpd.w.h = lSpd.w.l;
  lSpd.w.l = wk;
  scrv_down_ch(lSpd);
}


static void scrv_down_ch(int_union lSpd) {
  int result;

  if (lSpd.w.l >= scralim_down) {
    lSpd.w.l -= 2048;
    if (STAGE_IS_R11A || stageno_i.b.h == 1 || stageno_i.b.h == 2 || stageno_i.b.h == 5) {
      result = lSpd.w.l <= 0;
    }
    else {
      result = lSpd.w.l < 0;
    }
    if (result) {
      lSpd.w.l = scralim_down;
    }
    else {
      actwk[0].yposi.w.h &= 2047;
      scra_v_posit.w.h -= 2048;
      scrb_v_posit.w.h &= 1023;
    }
  }
  scrv_move(lSpd);
}


static void scrv_move(int_union lSpd) {
  short ysv, wk;
  uint_union spdwk;

  ysv = scra_v_posit.w.h;

  wk = lSpd.w.h;
  lSpd.w.h = lSpd.w.l;
  lSpd.w.l = wk;

  if (STAGE_IS_R11A || stageno_i.b.h == 1 || stageno_i.b.h == 2 || stageno_i.b.h == 5) {
    scra_vz = (unsigned short)((lSpd.l - scra_v_posit.l) >> 8);
  }
  else {
    spdwk.l = lSpd.l - scra_v_posit.l;
    spdwk.l = (spdwk.l >> 8) | (spdwk.l << 24);
    scra_vz = spdwk.w.l;
  }

  scra_v_posit.l = lSpd.l;

  wk = (unsigned char)(scra_v_posit.w.h & 16) ^ scra_v_count;
  if (wk == 0) {
    scra_v_count ^= 16;
    wk = scra_v_posit.w.h - ysv;
    if (wk < 0) {
      scrflaga.b.h |= 1;
    }
    else {
      scrflaga.b.h |= 2;
    }
  }
}


static void scrollb_hv(int xoffs, int yoffs) {
  int lwk, lsv;
  int_union ldwk;

  lsv = scrb_h_posit.l;
  ldwk.l = scrb_h_posit.l = lwk = lsv + xoffs;
  if (((unsigned char)(ldwk.w.h & 16) ^ scrb_h_count) == 0) {
    scrb_h_count ^= 16;
    if (lwk - lsv < 0) {
      scrflagb.b.h |= 4;
    }
    else {
      scrflagb.b.h |= 8;
    }
  }

  lsv = scrb_v_posit.l;
  if (stageno_i.b.h == 1) {
    ldwk.l = scrb_h_posit.l = lwk = lsv + yoffs;
  }
  else if ((stageno_i.b.h == 2 && stageno_i.b.l != 2) || stageno_i.b.h == 5) {
    lwk = lsv + yoffs;
    if (lwk < 0) {
      lwk = 0;
    }
    ldwk.l = scrb_v_posit.l = lwk;
  }
  else {
    ldwk.l = scrb_v_posit.l = lwk = lsv + yoffs;
  }
  if (((unsigned char)(ldwk.w.h & 16) ^ scrb_v_count) == 0) {
    scrb_v_count ^= 16;
    if (lwk - lsv < 0) {
      scrflagb.b.h |= 1;
    }
    else {
      scrflagb.b.h |= 2;
    }
  }
}


static void scrollb_h(int xoffs, int flagb) {
  int lXsv;
  int_union lXwk, ldXwk;

  lXsv = scrb_h_posit.l;
  lXwk.l = lXsv + xoffs;
  scrb_h_posit.l = lXwk.l;

  ldXwk.w.h = lXwk.w.l;
  ldXwk.w.l = lXwk.w.h;
  ldXwk.w.l &= 16;

  ldXwk.b.b4 ^= scrb_h_count;
  if (ldXwk.b.b4 == 0) {
    scrb_h_count ^= 16;
    if (lXwk.l - lXsv < 0) {
      scrflagb.b.h |= flagb;
    }
    else {
      scrflagb.b.h |= flagb * 2;
    }
  }
}


static void scrollb_v(short yPos) {
  short ysv, ywk;

  ysv = scrb_v_posit.w.h;
  scrb_v_posit.w.h = yPos;
  ywk = (unsigned char)(yPos & 16) ^ scrb_v_count;

  if (ywk == 0) {
    scrb_v_count ^= 16;
    if (ysv > yPos) {
      scrflagb.b.h |= 1;
    }
    else {
      scrflagb.b.h |= 2;
    }
  }
}


static void scrollc_h(int xoffs, int flagc) {
  int lXsv;
  int_union lXwk, ldXwk;

  lXsv = scrc_h_posit.l;
  lXwk.l = lXsv + xoffs;
  scrc_h_posit.l = lXwk.l;
  if (STAGE_IS_R12B) {
    lXsv = lXwk.l;
  }

  ldXwk.w.h = lXwk.w.l;
  ldXwk.w.l = lXwk.w.h;
  ldXwk.w.l &= 16;

  ldXwk.b.b4 ^= scrc_h_count;
  if (ldXwk.b.b4 == 0) {
    scrc_h_count ^= 16;
    if (lXwk.l - lXsv < 0) {
      scrflagc.b.h |= flagc;
    }
    else {
      scrflagc.b.h |= flagc * 2;
    }
  }
}


static void scrollz_h(int xoffs, int flagz) {
  int lXsv;
  int_union lXwk, ldXwk;

  lXsv = scrz_h_posit.l;
  lXwk.l = lXsv + xoffs;
  scrz_h_posit.l = lXwk.l;
  if (STAGE_IS_R12B) {
    lXsv = lXwk.l;
  }

  ldXwk.w.h = lXwk.w.l;
  ldXwk.w.l = lXwk.w.h;
  ldXwk.w.l &= 16;

  ldXwk.b.b4 ^= scrz_h_count;
  if (ldXwk.b.b4 == 0) {
    scrz_h_count ^= 16;
    if (lXwk.l - lXsv < 0) {
      scrflagz.b.h |= flagz;
    }
    else {
      scrflagz.b.h |= flagz * 2;
    }
  }
}


void scrollwrt(void) {
  unsigned short wH_posiw, wV_posiw;
  int VramBase;
  POINT TilePoint;
  unsigned char* pScrFlag;
  unsigned char* pMapWk;
  int_union lD4;
  unsigned short wD5;

  pScrFlag = &scrflagbw.b.h;
  wH_posiw = scrb_h_posiw.w.h;
  wV_posiw = scrb_v_posiw.w.h;
  pMapWk = mapwkbs[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  VramBase = 24576;
  if (stageno_i.b.h == 2 && (stageno_i.b.l != 0 || (time_flag_i & 0x7F) != 1)) {
    z4scrollwrtb(pScrFlag, pMapWk, VramBase, wH_posiw, wV_posiw);
  }
  else {
    scrollwrtb(pScrFlag, pMapWk, VramBase);
  }

  pScrFlag = &scrflagaw.b.h;
  wH_posiw = scra_h_posiw.w.h;
  wV_posiw = scra_v_posiw.w.h;
  pMapWk = mapwkas[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  VramBase = 16384;

  if (*pScrFlag) {
    if (*pScrFlag & 1) {
      *pScrFlag &= 254;

      lD4.l = -16;
      wD5 = 65520;
      vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);
      hblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 21);
    }
    if (*pScrFlag & 2) {
      *pScrFlag &= 253;

      lD4.l = 224;
      wD5 = 65520;
      vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);
      hblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 21);
    }
    if (*pScrFlag & 4) {
      *pScrFlag &= 251;

      lD4.l = -16;
      wD5 = 65520;
      vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);
      vblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 15);
    }
    if (*pScrFlag & 8) {
      *pScrFlag &= 247;

      lD4.l = -16;
      wD5 = 320;
      vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);
      vblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 15);
    }
  }
}


static void scrollwrtb(unsigned char* pScrFlag, unsigned char* pMapWk, int VramBase) {
  int_union lD4;
  int WrtTblCnt;
  unsigned short wD0;
  unsigned short wD5;
  unsigned short wH_posiw;
  unsigned short wV_posiw;
  POINT TilePoint;
  int BlkIndex;
  int i;

  lD4.l = -16;

  if (*pScrFlag & 1) {
    *pScrFlag &= 254;
  }
  else {
    *pScrFlag &= 254;

    if (*pScrFlag & 2) {
      *pScrFlag &= 253;
      lD4.w.l = 224;
    }
    else {
      *pScrFlag &= 253;
      goto label1;
    }
  }

  wD0 = (short)(scrb_v_posit.w.h + lD4.w.l) / 16;
  if (!STAGE_IS_R12B && !STAGE_IS_R13D) {
    wD0 &= 127;
  }
  if (STAGE_IS_R12A) {
    wD0 &= 31;
  }
  if (enkeino & 1) {
    wD0 = (z5awrttbl2 + (short)wD0)[1];
  }
  else {
    wD0 = wrttbls[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][wD0 + 1];
  }

  wH_posiw = vblockwrtbtbl[wD0]->w.h;
  wV_posiw = vblockwrtbtbl[wD0 + 1]->w.h;
  if (wD0 != 0) {
    wD5 = 65520;
    vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);

    hblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 21);
  }
  else {
    wD5 = 0;
    vramadrset1(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);

    hblockwrt1(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 31);
  }

label1:
  if (*pScrFlag != 0) {
    lD4.l = -16;
    wD5 = 65520;
    if (*pScrFlag & 168) {
      *pScrFlag = (*pScrFlag & 168) >> 1;
      wD5 = 320;
    }

    WrtTblCnt = (unsigned short)(scrb_v_posit.w.h / 16);

    if (WrtTblCnt < 0) WrtTblCnt = 0;
    if (WrtTblCnt > 113) WrtTblCnt = 113;

    for (i = 0; i < 16; ++i) {
      if (enkeino & 1) {
        wD0 = z5awrttbl2[WrtTblCnt++];
      }
      else {
        wD0 = wrttbls[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][WrtTblCnt++];
      }
      if ((!STAGE_IS_R11A && stageno_i.b.h != 3 && stageno_i.b.h != 4 && stageno_i.b.h != 5 && stageno_i.b.h != 6) || wD0 != 0) {
        if (*pScrFlag & (unsigned char)(1 << wD0)) {
          wH_posiw = vblockwrtbtbl[wD0]->w.h;
          wV_posiw = vblockwrtbtbl[wD0 + 1]->w.h;

          mapadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, &BlkIndex);


          vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);

          blockwrt(VramBase, &TilePoint, BlkIndex);
        }
      }
      lD4.w.l += 16;
    }
    *pScrFlag = 0;
  }
}


static void z4scrollwrtb(unsigned char* pScrFlag, unsigned char* pMapWk, int VramBase, unsigned short wH_posiw, unsigned short wV_posiw) {
  POINT TilePoint;
  int_union lD4;
  unsigned short wD5;

  if (*pScrFlag) {
    if (*pScrFlag & 1) {
      *pScrFlag &= 254;

      lD4.l = -16;
      wD5 = 65520;

      vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);

      hblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 21);
    }

    if (*pScrFlag & 2) {
      *pScrFlag &= 253;

      lD4.l = 224;
      wD5 = 65520;
      vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);

      hblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 21);
    }

    if (*pScrFlag & 4) {
      *pScrFlag &= 251;

      lD4.l = -16;
      wD5 = 65520;
      vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);

      vblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 15);
    }

    if (*pScrFlag & 8) {
      *pScrFlag &= 247;

      lD4.l = -16;
      wD5 = 320;
      vramadrset(wH_posiw, wV_posiw, wD5, lD4.w.l, &TilePoint);

      vblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, lD4.w.l, pMapWk, 15);
    }
  }
}


static void hblockwrt(POINT* pTilePoint, int VramBase, unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int lpcnt) {
  int BlkIndex;

  do {
    mapadrset(wH_posiw, wV_posiw, xOffs, yOffs, pMapWk, &BlkIndex);
    blockwrt(VramBase, pTilePoint, BlkIndex);
    pTilePoint->x += 2;
    if (pTilePoint->x >= 64) {
      pTilePoint->x -= 64;
    }
    xOffs += 16;
  } while (--lpcnt >= 0);
}


static void hblockwrt1(POINT* pTilePoint, int VramBase, unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int lpcnt) {
  int BlkIndex;

  do {
    mapadrset1(wH_posiw, wV_posiw, xOffs, yOffs, pMapWk, &BlkIndex);
    blockwrt(VramBase, pTilePoint, BlkIndex);
    pTilePoint->x += 2;
    if (pTilePoint->x >= 64) {
      pTilePoint->x -= 64;
    }
    xOffs += 16;
  } while (--lpcnt >= 0);
}


static void vblockwrt(POINT* pTilePoint, int VramBase, unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int lpcnt) {
  int BlkIndex;

  do {
    mapadrset(wH_posiw, wV_posiw, xOffs, yOffs, pMapWk, &BlkIndex);
    blockwrt(VramBase, pTilePoint, BlkIndex);
    pTilePoint->y += 2;
    if (pTilePoint->y >= 32) {
      pTilePoint->y -= 32;
    }
    yOffs += 16;
  } while (--lpcnt >= 0);
}


static void blockwrt(int VramBase, POINT* pTilePoint, int BlkIndex) {
  int base = 0;
  int frip;
  int p0, p1, p2, p3;
  int x, y;

  if (VramBase == 24576) {
    base = 1;
  }
  else if (VramBase == 16384) {
    base = 0;
  }
  x = pTilePoint->x;
  y = pTilePoint->y;

  frip = BlkIndex & 6144;
  BlkIndex &= 1023;
  if (frip == 6144) {
    p0 = 3;
    p1 = 2;
    p2 = 1;
    p3 = 0;
  }
  else if (frip & 4096) {
    p0 = 2;
    p1 = 3;
    p2 = 0;
    p3 = 1;
  }
  else if (frip & 2048) {
    p0 = 1;
    p1 = 0;
    p2 = 3;
    p3 = 2;
  }
  else {
    p0 = 0;
    p1 = 1;
    p2 = 2;
    p3 = 3;
  }

  SetGrid(base, x, y, blockwk[BlkIndex][p0], frip);
  SetGrid(base, x + 1, y, blockwk[BlkIndex][p1], frip);
  SetGrid(base, x, y + 1, blockwk[BlkIndex][p2], frip);
  SetGrid(base, x + 1, y + 1, blockwk[BlkIndex][p3], frip);
}


static int mapadrset(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int* pIndex) {
  return mapadrset99(wH_posiw, wV_posiw, xOffs, yOffs, pMapWk, pIndex);
}


static int mapadrset1(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int* pIndex) {
  wH_posiw = 0;
  return mapadrset99(wH_posiw, wV_posiw, xOffs, yOffs, pMapWk, pIndex);
}


static int mapadrset99(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int* pIndex) {
  int xBlk, yBlk;
  int i;
  unsigned char ScreenNo;
  unsigned short* lpw;

  xOffs += wH_posiw;
  yOffs += wV_posiw;

  if ((short)xOffs < 0) {
    xOffs = 0;
  }
  if ((short)yOffs < 0) {
    if (stageno_i.b.h == 2 && stageno_i.b.l != 0) {
      yOffs = (short)yOffs + 2048;
    }
    else {
      yOffs = 0;
    }
  }
  if ((short)xOffs >= 16384) {
    xOffs = 16383;
  }
  if ((short)yOffs >= 2048) {
    if (stageno_i.b.h == 2 && stageno_i.b.l != 0) {
      yOffs = (short)yOffs - 2048;
    }
    else {
      yOffs = 2047;
    }
  }
  i = xOffs / 256 + yOffs / 256 * 64;
  if (i < 0) i = 0;

  if (STAGE_IS_R11A) {
    ScreenNo = pMapWk[i];
  }
  else {
    ScreenNo = pMapWk[i] & 127;
  }

  if (ScreenNo) {
    xOffs &= 32767;
    yOffs &= 32767;

    xBlk = xOffs;
    xBlk %= 256;
    xBlk /= 16;
    yBlk = yOffs;
    yBlk %= 256;
    yBlk /= 16;

    lpw = mapwk;
    lpw += xBlk;
    lpw += yBlk * 16;
    lpw += (ScreenNo - 1 << 4) << 4;
    *pIndex = *lpw;

    return 1;
  }

  *pIndex = 0;
  return 0;
}


static int mapadrset2(unsigned short xOffs, unsigned short yOffs, unsigned char* pMapWk, int* pIndex, unsigned short** ppBlockNo) {
  int xBlk, yBlk;
  unsigned char ScreenNo;
  unsigned short* lpw;

  ScreenNo = pMapWk[xOffs / 256 + yOffs / 256 * 64] & 127;
  if (ScreenNo) {
    xBlk = xOffs;
    xBlk %= 256;
    xBlk /= 16;
    yBlk = yOffs;
    yBlk %= 256;
    yBlk /= 16;

    lpw = mapwk;
    lpw += xBlk;
    lpw += yBlk * 16;
    lpw += (ScreenNo - 1 << 4) << 4;
    *ppBlockNo = lpw;
    *pIndex = *lpw;

    return 1;
  }
  *pIndex = 0;
  return 0;
}


void block_wrt(unsigned short BlockNo, unsigned short xOffs, unsigned short yOffs) {
  int VramBase;
  POINT TilePoint;
  unsigned char* pMapWk;
  unsigned short* pBlockIndex;
  int Index;

  VramBase = 16384;
  pMapWk = mapwkas[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + generate_flag];
  if (mapadrset2(xOffs, yOffs, pMapWk, &Index, &pBlockIndex) != 0) {
    if (stageno.w != 0x0602) {
      *pBlockIndex = BlockNo;
    }
    if (block_chk(xOffs, yOffs) == 0) {
      vramadrset0(xOffs, yOffs, &TilePoint);
      blockwrt(VramBase, &TilePoint, BlockNo);
    }
  }
}


static int block_chk(unsigned short xOffs, unsigned short yOffs) {
  if (stageno_i.b.h == 1) {
    return z3_block_chk(xOffs, yOffs);
  }
  else if (stageno_i.b.h == 6 && stageno_i.b.l == 2) {
    return z83_block_chk(xOffs, yOffs);
  }

  if ((scra_v_posit.w.h & 65520) - 16 > yOffs) {
    if ((short)(scra_v_posit.w.h + 240 & 65520) - 16 <= (short)yOffs) {
      if ((scra_h_posit.w.h & 65520) - 16 > xOffs) {
        if ((short)(scra_v_posit.w.h + 336 & 65520) - 16 <= (short)xOffs) {
          return 0;
        }
      }
    }
  }

  return 1;
}


static int z3_block_chk(unsigned short xOffs, unsigned short yOffs) {
  if ((scra_v_posit.w.h & 65520) - 16 < yOffs) {
    if ((short)(scra_v_posit.w.h + 240 & 65520) - 16 >= (short)yOffs) {
      if ((scra_h_posit.w.h & 65520) - 16 < xOffs) {
        if ((short)(scra_h_posit.w.h + 336 & 65520) - 16 >= (short)xOffs) {
          return 0;
        }
      }
    }
  }

  return 1;
}


static int z83_block_chk(unsigned short xOffs, unsigned short yOffs) {
  if ((unsigned short)((scra_v_posit.w.h & 65520) - 16) <= yOffs) {
    if ((short)((scra_v_posit.w.h + 240 & 65520) - 16) > (short)yOffs) {
      if ((unsigned short)((scra_h_posit.w.h & 65520) - 16) < xOffs) {
        if ((short)(scra_h_posit.w.h + 336 & 65520) - 16 >= (short)xOffs) {
          return 0;
        }
      }
    }
  }

  return 1;
}


static void vramadrset(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint) {
  vramadrset99(wH_posiw, wV_posiw, xOffs, yOffs, lpTilePoint);
}


static void vramadrset0(unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint) {
  vramadrset99(0, 0, xOffs, yOffs, lpTilePoint);
}


static void vramadrset1(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint) {
  wH_posiw = 0;
  vramadrset99(wH_posiw, wV_posiw, xOffs, yOffs, lpTilePoint);
}


static void vramadrset2(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint) {
  vramadrset99(wH_posiw, wV_posiw, xOffs, yOffs, lpTilePoint);
}


static void vramadrset99(unsigned short wH_posiw, unsigned short wV_posiw, unsigned short xOffs, unsigned short yOffs, POINT* lpTilePoint) {
  xOffs += wH_posiw;
  yOffs += wV_posiw;
  yOffs &= 240;
  xOffs &= 496;

  lpTilePoint->x = xOffs / 16 * 2;
  lpTilePoint->y = yOffs / 16 * 2;
}


void mapwrt(void) {
  int VramBase;
  unsigned short wH_posiw, wV_posiw;
  unsigned char* pMapWk;

  if (stageno_i.b.h == 6) {
    wH_posiw = scra_h_posit.w.h;
    wV_posiw = scra_v_posit.w.h;
  }
  else {
    wH_posiw = scra_h_posiw.w.h;
    wV_posiw = scra_v_posiw.w.h;
  }
  pMapWk = mapwkas[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  VramBase = 16384;
  mapwrt2(wH_posiw, wV_posiw, pMapWk, VramBase);

  mapwrtb();
}


void mapwrtb(void) {
  int VramBase;
  unsigned short wH_posiw, wV_posiw;
  unsigned char* pMapWk;

  if (stageno_i.b.h == 4) {
    wH_posiw = scra_h_posit.w.h;
    wV_posiw = scra_v_posit.w.h;
  }
  else {
    wH_posiw = scrb_h_posiw.w.h;
    wV_posiw = scrb_v_posiw.w.h;
  }
  pMapWk = mapwkbs[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];
  VramBase = 24576;
  if (STAGE_IS_R41A) {
    mapwrt_z41a(pMapWk, VramBase);
  }
  else if (stageno_i.b.h == 2) {
    mapwrt2(wH_posiw, wV_posiw, pMapWk, VramBase);
  }
  else {
    mapwrt_z(pMapWk, VramBase);
  }
}


static void mapwrt2(unsigned short wH_posiw, unsigned short wV_posiw, unsigned char* pMapWk, int VramBase) {
  mapwrt3(wH_posiw, wV_posiw, pMapWk, VramBase, 65520, 15);
}


static void mapwrt3(unsigned short wH_posiw, unsigned short wV_posiw, unsigned char* pMapWk, int VramBase, unsigned short wD4, unsigned short wD6) {
  POINT TilePoint;

  do {
    vramadrset(wH_posiw, wV_posiw, 0, wD4, &TilePoint);
    hblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, 0, wD4, pMapWk, 31);
    wD4 += 16;
  } while ((short)--wD6 >= 0);
}


static void mapwrt_z(unsigned char* pMapWk, int VramBase) {
  unsigned short wD0, wD4, wD6;
  unsigned short limits[7][3][3] = {
    { { 496, 2032, 496 }, { 496, 496, 496 }, { 0, 0, 496 } },
    { { 752, 752, 752 }, { 752, 752, 752 }, { 0, 0, 752 } },
    { { 496, 2032, 496 }, { 496, 496, 496 }, { 0, 0, 496 } },
    { { 1008, 65520, 1008 }, { 1008, 65520, 1008 }, { 0, 0, 1008 } },
    { { 496, 496, 496 }, { 496, 496, 496 }, { 0, 0, 496 } },
    { { 496, 496, 496 }, { 496, 496, 496 }, { 0, 0, 496 } },
    { { 496, 496, 496 }, { 496, 496, 496 }, { 0, 0, 496 } }
  };
  wD4 = 65520;
  wD6 = 15;

  do {
    if (stageno_i.b.h == 1 && stageno_i.b.l == 0 && actwk[0].xposi.w.h == 96) {
      wD0 = scrb_v_posit.w.h + wD4 & 1008;
    }
    else {
      wD0 = scrb_v_posit.w.h + wD4 & limits[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F];
    }
    if (enkeino & 1) {
      mapwrt_sub(&z5awrttbl2[1], wD0, wD4, pMapWk, VramBase);
    }
    else {
      mapwrt_sub(&wrttbls[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][1], wD0, wD4, pMapWk, VramBase);
    }
    wD4 += 16;
  } while ((short)--wD6 >= 0);
}


static void mapwrt_z41a(unsigned char* pMapWk, int VramBase) {
  unsigned short wD0, wD4, wD6;
  int_union temp;
  uint_union temp2;

  wD4 = 65520;
  wD6 = 15;

  do {
    temp.l = 0;
    temp.w.l = scrb_v_posit.w.h;
    wD0 = scrb_v_posit.w.h;
    if ((long int)temp.l >= 512) {


      wD0 -= 512;
      temp2.l = 0;
      temp2.w.l = wD0;
      temp2.l = (unsigned int)temp2.l >> 16 & 65535 | temp2.l << 16 & -65536;
      temp2.l >>= 2;
      temp2.l *= 3;
      temp2.l += 0x2000000;
      temp2.l = (unsigned int)temp2.l >> 16 & 65535 | temp2.l << 16 & -65536;
      wD0 = temp2.w.l;
    }
    else {

      temp.l = 0;
      temp.w.l = scra_h_posit.w.h;
      if ((long int)temp.l >= 640) {
        wD0 = 512;
      }
    }
    wD0 += wD4;
    wD0 &= 2032;

    mapwrt_sub(&z4wrttbl[1], wD0, wD4, pMapWk, VramBase);
    wD4 += 16;
  } while ((short)--wD6 >= 0);
}


static void mapwrt_sub(unsigned char* pWrttbl, unsigned short wD0, unsigned short wD4, unsigned char* pMapWk, int VramBase) {
  POINT TilePoint;
  unsigned short wH_posiw, wV_posiw;
  unsigned short wD5;

  wD0 /= 16;
  wD0 = pWrttbl[wD0];
  wH_posiw = mapwrt_tbl[wD0]->w.h;
  wV_posiw = mapwrt_tbl[wD0 + 1]->w.h;
  if (wD0) {
    wD5 = 65520;
    vramadrset(wH_posiw, wV_posiw, wD5, wD4, &TilePoint);
    hblockwrt(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, wD4, pMapWk, 21);
  }
  else {
    wD5 = 0;
    vramadrset1(wH_posiw, wV_posiw, wD5, wD4, &TilePoint);
    hblockwrt1(&TilePoint, VramBase, wH_posiw, wV_posiw, wD5, wD4, pMapWk, 31);
  }
}


void mapinit(void) {
  short tbl[9] = {
    3584, 8960, -1,
    3584, 8960, -1,
    3584, 8960, -1
  };
  char tbl0[3] = {
    2, 4, 2
  };
  int EnkeiNo, TileNo, BmpNo, i;
  short *pTbl, poswk;
  unsigned char callenecginit[7][3][3] = {
    { { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 0 } },
    { { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 1 } },
    { { 1, 1, 0 }, { 1, 1, 0 }, { 0, 0, 0 } },
    { { 0, 1, 1 }, { 0, 1, 1 }, { 0, 0, 1 } },
    { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
    { { 1, 1, 0 }, { 1, 1, 0 }, { 0, 0, 0 } },
    { { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 1 } }
  };

  if (stageno_i.b.h != 3) {
    mapset();
  }
  else if (!STAGE_IS_R53C) {
    EnkeiNo = 0;
    pTbl = tbl;

    while ((poswk = *pTbl++) >= 0) {
      if (actwk[0].xposi.w.h <= poswk) break;

      ++EnkeiNo;
    }

    TileNo = tile_change[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][0];
    if (EnkeiNo == 0) {
      i = tile_change[(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][3];
      BmpNo = 0;

      for ( ; i > 0; --i) {
        ChangeTileBmp(TileNo++, BmpNo++);
      }
    }
  }
  else {
    TileNo = tile_change[(time_flag_i & 0x7F) + generate_flag][0];
    i = tile_change[(time_flag_i & 0x7F) + generate_flag][1];
    BmpNo = tile_change[(time_flag_i & 0x7F) + generate_flag][2];
    for ( ; i > 0; --i) {
      ChangeTileBmp(TileNo++, BmpNo++);
    }
  }

  colorset2(mapinittbls[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)]->colorno2);
  colorset(mapinittbls[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)]->colorno2);

  if (plflag != 0 && callenecginit[stageno_i.b.h][stageno_i.b.l][time_flag_i & 0x7F] != 0) {
    enecginit();
  }
  if (play_start & 2) {
    divdevset(0);
  }
}


static void mapset(void) {}


static void mapset2(unsigned char* pMapDst, int idx) {
  int h, v, hwk;
  unsigned char *pZonetbl, *pMapwk;

  pZonetbl = zmaptbls[stageno_i.b.l][time_flag_i & 0x7F][idx];
  h = *pZonetbl++;
  v = *pZonetbl++;
  for ( ;v >= 0; --v) {
    pMapwk = pMapDst;

    for (hwk = h; hwk >= 0; --hwk) {
      *pMapwk++ = *pZonetbl++;
    }

    pMapDst += 64;
  }
}
