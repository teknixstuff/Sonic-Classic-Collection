#include "EQU.h"
#include "GAME.h"
#include <string.h>
#include "../services.h"
#include "ACTION.h"
#include "ACTSET.h"
#include "COL.h"
#include "DEV.h"
#include "ETC.h"
#include "FCOL.h"
#include "IO.h"
#include "LOADER2.h"
#include "SCORE.h"
#include "SCR.h"

static void back_to_cnt(void);
static void bye_cnt(void);

static short Interupt_Counter;
static unsigned int PauseIcon;
extern bmp_info SprBmp[700];
extern unsigned char* scds[7][3][4];
extern short_union* watercolitbls[3][3];


void SetDebugFlag(unsigned int NewVal) {
  if (NewVal == 1) debugflag.w |= 256;
  else debugflag.w &= -257;

}




int game(void) {

  if (swdata1.b.l & 128) {
    if (pauseflag.b.h) {
      if (swdata2.w & 32896) {
        if (PauseIcon) pauseflag.b.h = 0, PauseIcon = 0;
      } else pauseflag.b.h = 0;
      CDPause(1);
    } else {
      if (swdata2.w & 32896) pauseflag.b.h = 1, PauseIcon = 1;
      else pauseflag.b.h = 1;
      CDPause(0);
    }
  }




















  if (pauseflag.b.h & 1) {
    sdfdout();
  }
  if ((swdata1.b.l & 112) == 112) {

    pauseflag.b.h = 0;
    markerno = 0;
    demoflag.w = 0;
    gameflag.w = 1;
    gKeepWork.ta_time = -1;
    --pl_suu;
    if ((char)pl_suu < 0) {
      pl_suu = 0;
    }
    sub_sync(14);
    flagwkclr();
    plflag = 0;
  }

  if (pauseflag.b.h & 1) return 0;


  if (gameflag.w != 1) {
    sdfdin();
    ++gametimer.w;
    actsetchk();
    action();
  }
  if (demo_cnt == 2048) {

    enkeino = 0;
  }
  if (gameflag.w) {



    if (gameflag.b.h != 1) {
      flagwkclr();
    }

    if (gameflag.w == 2) {

      gKeepWork.ta_time = pltime.b.b3 * 60 + pltime.b.b2 * 60 * 60 + pltime.b.b4;
    }
    else if (gameflag.w == 1) {
      gKeepWork.ta_time = -1;
    }
    return gameflag.w;
  }
  if (editmode.w) {
    scroll();
  }
  else {
    if (actwk[0].r_no0 >= 6) {
      scralim_down = scra_v_posit.w.h;
      scralim_n_down = scra_v_posit.w.h;
    }
    else {

      scroll();
    }
  }


  if (stageno_i.b.h == 2) {
    watercoli();
  }
  patset();
  if (!time_stop) {
    clchgctr();
  }

  syspatchg();


  if (stageno_i.b.h == 2) {
    watercnt();

    if (!time_stop) {
      cg_change();
    }
  }


  scra_h_posiw.l = scra_h_posit.l;
  scra_v_posiw.l = scra_v_posit.l;
  scrb_h_posiw.l = scrb_h_posit.l;
  scrb_v_posiw.l = scrb_v_posit.l;
  scrc_h_posiw.l = scrc_h_posit.l;
  scrc_v_posiw.l = scrc_v_posit.l;
  scrz_h_posiw.l = scrz_h_posit.l;
  scrz_v_posiw.l = scrz_v_posit.l;
  scrflagaw.w = scrflaga.w;
  scrflagbw.w = scrflagb.w;
  scrflagcw.w = scrflagc.w;
  scrflagzw.w = scrflagz.w;
  if (stageno_i.b.h == 3 && stageno_i.b.l != 2) {
    if (mapwrt_cnt & 1) {
      mapwrt_cnt &= 254;
      mapwrtb();
    }
    else enkeichg();
  }
  scrollwrt();
  scoreset();
  if (stageno_i.b.h != 2) {
    cg_change();
  }

  if (!pauseflag.b.h) {
    bye_cnt();
    back_to_cnt();
  }

  ++systemtimer.l;
  return 0;
}



void game_init(void) {

  unsigned short waterpositbl[12] = {
     768,  640,  464,
    4095, 1456, 1328,
    1296, 4095, 1168,
    1168, 1168, 4095
  };


  ReadScrolMap();
  ReadBlockMap();


  demoflag.w = 0;
  if (clrspflg_save == 127 && ta_flag == 0) {
    generate_flag = 1;
  }


  init_flag = 0;
  int_flg = 0;
  main_play = 0;
  pauseflag.b.h = 0;

  if (!(play_start & 1)) {
    play_start |= 1;
    start_flag = 0;
    markerno = 0;
    extrascore = 5000;
    flagwkclr();
    plflag = 0;
    gf_flag = 0;
    plscore = 0;
    pl_suu = 3;
    if (ta_flag != 0) {
      pl_suu = 1;
    }
  }
  else {
    play_start |= 1;
  }


  da_set();



  plsubchg_flag = 0;
  memset(flowercnt, 0, sizeof(flowercnt));
  memset(pbuffer, 0, sizeof(pbuffer));
  memset(flowerposi, 0, sizeof(flowerposi));
  memset(actwk, 0, sizeof(actwk));
  memset(flowwk, 0, sizeof(flowwk));



  intcnt.w = 0;
  int_flg = 0;
  linkdata = 0;
  cltbladr = 0;
  ranum = 0;
  pauseflag.w = 0;
  cgwrtcnt = 0;
  cgwrttim = 0;
  dmastack = 0;
  waterposi = 0;
  waterposi_m = 0;
  watermoveposi = 0;
  waterspeed = 0;
  water_flag = 0;
  waterflag = 0;
  waterflag2 = 0;
  memset(cgchgcnt, 0, sizeof(cgchgcnt));
  memset(cgchgtim, 0, sizeof(cgchgtim));


  scra_h_posit.l = 0;
  scra_v_posit.l = 0;
  scrb_h_posit.l = 0;
  scrb_v_posit.l = 0;
  scrc_h_posit.l = 0;
  scrc_v_posit.l = 0;
  scrz_h_posit.l = 0;
  scrz_v_posit.l = 0;
  scralim_n_left = 0;
  scralim_n_right = 0;
  scralim_n_up = 0;
  scralim_n_down = 0;
  scralim_left = 0;
  scralim_right = 0;
  scralim_up = 0;
  scralim_down = 0;
  scrar_no = 0;
  scra_h_keep = 0;
  scra_v_keep = 0;
  scra_hz = 0;
  scra_vz = 0;
  scra_vline = 0;
  scrh_flag = 0;
  scrv_flag = 0;
  zone_flag.w = 0;
  scroll_start.w = 0;
  scr_die.w = 0;
  scr_timer.w = 0;
  scra_h_count = 0;
  scra_v_count = 0;
  scrb_h_count = 0;
  scrb_v_count = 0;
  scrc_h_count = 0;
  scrc_v_count = 0;
  scrz_h_count = 0;
  scrz_v_count = 0;
  scrflaga.w = 0;
  scrflagb.w = 0;
  scrflagc.w = 0;
  scrflagz.w = 0;
  limmoveflag = 0;
  playpatno1 = 0;
  kusya_flag = 0;
  plmaxspdwk = 0;
  pladdspdwk = 0;
  plretspdwk = 0;
  playpatno = 0;
  playwrtflag = 0;
  memset(dirstk, 0, sizeof(dirstk));
  actset_rno.w = 0;
  asetposi = 0;
  asetadr = 0;
  asetadr2 = 0;
  asetadrz = 0;
  asetadrz2 = 0;
  byecnt0.w = 0;
  byecnt1.w = 0;
  time_item = 0;
  backto_cnt = 0;
  scr_cnt = 0;
  demo_adr = 0;
  demo_cnt = 0;
  swbufcnt = 0;
  scdadr = 0;
  scra_hline = 0;
  bossflag = 0;
  plposiwkadr.w = 0;
  bossstart = 0;
  loopmapno = 0;
  loopmapno2 = 0;
  ballmapno = 0;
  ballmapno2 = 0;
  memset(clchgcnt, 0, sizeof(clchgcnt));
  memset(clchgtim, 0, sizeof(clchgtim));
  watercoliflag = 0;
  waterstop = 0;
  mizuflag = 0;
  sekichyuflag = 0;
  plautoflag = 0;
  specflag = 0;
  dai2rmvflag = 0;
  emyscorecnt = 0;
  timebonus = 0;
  ringbonus = 0;
  bonus_f = 0;
  edplayflag = 0;
  waterdirec.w = 0;
  ms_wflg = 0;
  memset(switchflag, 0, sizeof(switchflag));


  demo_cnt = 0;


  tv_flag = 0;
  editno.w = 0;
  editmode.w = 0;
  edittimer = 0;
  systemtimer.l = 0;
  time_stop = 0;
  sys_pattim = 0;
  sys_patno = 0;
  sys_pattim2 = 0;
  sys_patno2 = 0;
  sys_pattim3 = 0;
  sys_patno3 = 0;
  sys_pattim4 = 0;
  sys_patno4 = 0;
  sys_ringtimer = 0;
  editstack = 0;
  editstack2 = 0;
  mapcheck = 0;
  scra_h_posiw.l = 0;
  scra_v_posiw.l = 0;
  scrb_h_posiw.l = 0;
  scrb_v_posiw.l = 0;
  scrc_h_posiw.l = 0;
  scrc_v_posiw.l = 0;
  scrz_h_posiw.l = 0;
  scrz_v_posiw.l = 0;
  scrflagaw.w = 0;
  scrflagbw.w = 0;
  scrflagcw.w = 0;
  scrflagzw.w = 0;
  blkno = 0;
  col_y.w = 0;
  col_x.w = 0;
  edit_user = 0;
  sysdirec = 0;
  prio_flag = 0;
  init_flag = 0;
  boss_sound = 0;
  shut_flag = 0;
  st6clrchg = 0;
  chibi_flag = 0;
  mapwrt_cnt = 0;
  memset(linework, 0, sizeof(linework));

  scrinit();


  if (stageno_i.b.h == 2) {


    waterposi = waterpositbl[(time_flag & 127) + stageno.b.l * 4];
    waterposi_m = waterpositbl[(time_flag & 127) + stageno.b.l * 4];
    watermoveposi = waterpositbl[(time_flag & 127) + stageno.b.l * 4];

    water_flag = 0;
    waterflag = 0;
    waterspeed = 1;

    watercnt();
  }


  pl_air = 30;

  if (stageno_i.b.h != 3 || stageno_i.b.l == 2) {
    colorset2(3);
    colorset(3);
  }


  scr_set();
  scroll();
  scrflaga.b.h |= 4;

  mapinit();
  mapwrt();

  scdcnv();
  scdset();




  play_act_set();
  actwk[2].actno = 28;
  actwk[3].actno = 28;
  actwk[3].userflag.b.h = 1;
  actwk[5].actno = 28;
  actwk[5].userflag.b.l = 1;



  actwk[31].actno = 25;
  actwk[31].userflag.b.h = 10;

  if (!(play_start & 2)) {
    play_start |= 2;
    actwk[4].actno = 60;
    plautoflag = 1;
    enecgflg = 0;
  }

  if (stageno_i.b.h == 2 || (stageno_i.b.h == 3 && stageno_i.b.l != 2)) {
    actwk[32].actno = 4;
  }
  swdata.w = 0;
  swdata1.w = 0;
  swdata2.w = 0;
  byecnt0.w = 0;
  byecnt1.w = 0;
  enkeino = 0;

  if (plflag == 0) {
    plring = 0;
    pltime.l = 0;
    plring_f2 = 0;
  }

  pltimeover_f = plpower_b = plpower_m = plpower_s = plpower_a = 0;
  editmode.w = gameflag.w = gametimer.w = 0;
  plflag = 0;
  plscore_f = plring_f = pltime_f = pl_suu_f = 1;
  plring_f = 128;

  plscore_f = 128;

  swbufcnt = 0;
  startcolor = 32;
  colorcnt = 47;
  if (stageno_i.b.h == 3 && stageno_i.b.l != 2) {
    scrflaga.b.h = 0;
    enkeichg();

    colorset2(3);
    colorset(3);

    if (enkeino == 1) {
      colorset2(5);
      colorset(5);
    }

    mapwrt_cnt = 0;
    mapwrtb();
  }
  else {
    cg_change();
  }
  tv_flag = 1;


  if (stageno_i.b.h == 2) colorset3(0);
  gmmode.b.h &= 127;
  init_flag = 1;


  game();
  scra_h_posiw.w.h -= 16;
  mapwrt();
  scra_h_posiw.w.h += 16;

  if (time_flag & 128) {

    flashin();
  }
  else {



    fadein0();
  }

}




void play_act_set(void) {
  actwk[0].actno = 1;
  if (plflag) {
    *(short*)&actwk[0].actfree[6] = 120;
  }
}


void flow_act_set(void) {
  int i, time, fcnt;
  sprite_status* pAct;

  if (stageno_i.b.h == 2) return;
  time = time_flag & 127;
  fcnt = flowercnt[time];
  if (fcnt != 0) {
    --fcnt;
    pAct = &actwk[32];
    i = 0;
    do {
      pAct->actno = 31;

      pAct->xposi.w.h = flowerposi[i + (time * 64)].w.h;
      pAct->yposi.w.h = flowerposi[i + (time * 64)].w.l;
      --fcnt;
      ++pAct;
      ++i;
    } while (fcnt > 0);
  }

}



void scdset(void) {
  scdadr = scds[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)];

}


void syspatchg(void) {
  if ((--sys_pattim & 128) && (stageno_i.b.h != 3 || stageno_i.b.l != 2)) {
    sys_pattim = 11;
    sys_patno = (sys_patno - 1) & 7;
  }
  if (--sys_pattim2 & 128) {
    sys_pattim2 = 7;
    sys_patno2 = (sys_patno2 + 1) & 3;
  }
  if ((--sys_pattim3 & 128) && (stageno_i.b.h != 3 || stageno_i.b.l != 2)) {
    sys_pattim3 = 7;
    if (++sys_patno3 >= 6) sys_patno3 = 0;
  }
  if (sys_pattim4) {
    sys_ringtimer += (unsigned short)sys_pattim4;


    sys_patno4 = (sys_ringtimer >> 9) & 3;
    --sys_pattim4;
  }

}


static void back_to_cnt(void) {
  if (!actwk[0].actfree[0]) {
    if (backto_cnt) {
      ++backto_cnt;
    }
  }

}




static void bye_cnt(void) {
  if (byecnt0.w) {
    ++byecnt0.w;
  }

  if (byecnt1.w) {
    ++byecnt1.w;
  }


}




void sdfdout(void) {
  soundset(171);
  if (!(pauseflag.b.h | 128)) {


    pauseflag.b.h |= 128;
    if (!(time_flag & 127)) {

      if (plpower_m || plpower_s) {
        sub_sync(144);
        return;
      }
    }

    sub_sync(213);
  }
}


void sdfdin(void) {
  if (pauseflag.b.h & 128) {


    pauseflag.b.h &= 127;
    if (!(time_flag & 127)) {

      if (plpower_m || plpower_s) {
        sub_sync(145);
        return;
      }
    }

    sub_sync(214);
  }
}






void da_set(void) {
  unsigned short wD0;
  static unsigned char da_tbl[7][4] = {
    { 48, 15, 17, 16 },
    { 49, 18, 20, 19 },
    { 50, 21, 23, 22 },
    { 51, 24, 26, 25 },
    { 52, 27, 29, 28 },
    { 53, 30, 32, 31 },
    { 54, 33, 102, 34 }
  };

  wD0 = time_flag & 127;
  if (!ta_flag) {
    if (wD0 == 2) {
      wD0 += generate_flag;
    }
  }

  sub_sync((unsigned short)da_tbl[stageno.b.h][wD0]);


}






void water1chk(void) {
  short wD1;

  if (!(time_flag & 127)) return;

  if ((time_flag & 127) == 1) {
    wD1 = 640;
    if ((unsigned short)actwk[0].xposi.w.h >= 1504) wD1 = 608;
  }
  else {

    wD1 = 464;
    if (actwk[0].xposi.w.h >= 2336) {
      wD1 = 272;
      if (actwk[0].xposi.w.h >= 6528) {
        wD1 = 576;
        waterspeed = 3;
      }
    }
  }

  watermoveposi = wD1;
}



void water2chk(void) {
  short wD1;

  wD1 = scra_v_posit.w.h + 232;

  if (actwk[0].xposi.w.h < 512) {
    waterposi_m = wD1;
    watermoveposi = wD1;
    return;
  }
  if (actwk[0].yposi.w.h >= 1536) {
    if (actwk[0].yposi.w.h < 1728) {
      if (actwk[0].xposi.w.h < 672) {
        waterposi_m = wD1;
        watermoveposi = wD1;
        return;
      }
    }
  }

  if (!(time_flag & 127)) {
    wD1 = 1456;
    waterposi_m = wD1;
    watermoveposi = wD1;
    return;
  }

  if ((time_flag & 127) == 1) {
    wD1 = 1328;
    if (actwk[0].xposi.w.h >= 3072) {
      wD1 = 1920;
      if (actwk[0].xposi.w.h >= 3520) {
        wD1 = 1280;
        if (actwk[0].xposi.w.h < 4992) {
          if (actwk[0].yposi.w.h >= 1024) return;
          wD1 = 960;
          if (actwk[0].xposi.w.h < 4352) return;
        }
      }
    }
  }
  else {

    wD1 = 1296;
    if (actwk[0].xposi.w.h >= 1024) {
      wD1 = 912;
      if (actwk[0].xposi.w.h >= 5632) {
        wD1 = 1040;
        if (actwk[0].xposi.w.h >= 6400) wD1 = 1280;
      }
    }
  }

  watermoveposi = wD1;
}



void water3chk(void) {
  short wD1;

  wD1 = scra_v_posit.w.h + 232;
  if (actwk[0].xposi.w.h < 1984) waterposi_m = wD1;
  else {

    wD1 = 1168;
    if (actwk[0].xposi.w.h >= 2800) {
      waterspeed = 2;
      wD1 = 1472;
    }
  }

  watermoveposi = wD1;
}



void watercntsub(void) {
  unsigned short wD1;

  void(*watertbl[3])(void) = {
    &water1chk,
    &water2chk,
    &water3chk
  };

  watertbl[stageno.b.l]();

  wD1 = waterspeed;
  if (watermoveposi != waterposi_m) {
    if (watermoveposi < waterposi_m) wD1 *= -1;

    waterposi_m += wD1;
  }

}



void watercnt(void) {
  short wD0, wD1;

  if (!pauseflag.b.h) {
    if (actwk[0].r_no0 < 6) watercntsub();

    waterflag = 0;
    sysdirec += 2;
    sinset(sysdirec, &wD0, &wD1);
    waterposi = (short)(char)((unsigned short)wD0 >> 6) + waterposi_m;

    wD0 = waterposi - scra_v_posit.w.h;
    if ((unsigned short)waterposi < (unsigned short)scra_v_posit.w.h) {
      if (wD0 < 0) {
        hintposi.b.l = -33;
        waterflag = 1;
      }
    }

    if ((unsigned short)wD0 >= 223) wD0 = 223;

    hintposi.b.l = (unsigned char)wD0;
  }
}



void watercoli(void) {
  int i;

  if (actwk[0].mstno.b.h == 43) return;

  if (actwk[0].actfree[2] & 1) return;

  if (!actwk[0].actno) return;

  if (editmode.w) return;

  if (stageno.b.l >= 2) return;



  for (i = 0; watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i].w >= 0; i += 7) {
    if (actwk[0].xposi.w.h < watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i].w) continue;
    if (actwk[0].xposi.w.h >= watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i + 2].w) continue;
    if (actwk[0].yposi.w.h < watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i + 1].w) continue;
    if (actwk[0].yposi.w.h >= watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i + 3].w) continue;

    if (((char*)&watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i + 6])[1] == 1) {
      if (!(switchflag[((char*)&watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i + 6])[0]] & 64)) return;
    }

    if (actwk[0].r_no0 >= 4) {
      watercoliflag = 0;
      return;
    }
    watercoliflag = 1;
    actwk[0].actfree[18] = 0;
    actwk[0].xspeed.w = watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i + 4].w;
    actwk[0].yspeed.w = watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i + 5].w;
    actwk[0].mstno.b.h = 15;
    actwk[0].cddat |= 2;

    if (((char*)&watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i + 6])[1] == 2) {
      if (switchflag[((char*)&watercolitbls[stageno_i.b.l][time_flag_i & 0x7F][i + 6])[0]] & 32) {
        actwk[0].xspeed.w *= -1;
        actwk[0].yspeed.w *= -1;
      }
    }

    if (swdata.b.h & 1) --actwk[0].yposi.w.h;

    if (swdata.b.h & 2) ++actwk[0].yposi.w.h;

    if (swdata.b.h & 4) --actwk[0].xposi.w.h;

    if (swdata.b.h & 8) ++actwk[0].xposi.w.h;

    return;




  }

  if (!watercoliflag) return;

  actwk[0].mstno.b.h = 0;

  watercoliflag = 0;
}
