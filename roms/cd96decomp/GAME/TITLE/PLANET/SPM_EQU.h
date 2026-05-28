extern unsigned char cgchg_end;
extern unsigned char cgchg_timer;
extern unsigned char flash_flg;
extern short lplanet_no;
extern short flash_timer;
extern unsigned char actset_wk;
extern unsigned char actset_flg;
extern short spr_colno;
extern short spr_coltimer;
extern short main_lpcnt;
extern short funka_patno;
extern short funka_pctimer;
extern sprite_status_lpl lplactwk[18];
extern int_union* lphscrollbuff;
extern unsigned char music_selflg;
extern unsigned char m2save[22528];

void lplWorkRamClear(void);
