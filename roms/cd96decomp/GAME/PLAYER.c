#include "EQU.h"
#include "PLAYER.h"
#include "../services.h"
#include "ACTION.h"
#include "ACTSET.h"
#include "COLI.h"
#include "DIRCOL.h"
#include "DUMMY.h"
#include "EDIT.h"
#include "ETC.h"
#include "FCOL.h"
#include "GAME.h"
#include "LOADER2.h"
#include "PLAYSP.h"
#include "PLAYSUB.h"

extern sprite_pattern** sncpats[6];
extern unsigned char (*mapwkas[7][3][4])[64];
extern unsigned char** playchgs[7];
extern unsigned char plchg00[8];
extern unsigned char plchg01[8];
extern unsigned char plchg49[8];
extern unsigned char plchg53[8];
extern unsigned char plchg03[8];
extern unsigned char plchg02[8];
extern unsigned char plchg54[8];
extern unsigned char plchg35[6];
extern unsigned char plchg04[8];
extern unsigned char plchg39[7];
extern unsigned char plchg33[6];
extern unsigned char plchg34[6];

static unsigned int WaveClear;
static unsigned char Brake_Sw;
static unsigned char Brake_Req;
unsigned char* playcg;
sprite_pattern** playpat;
static short tate[2] = { 426, -1 }, yoko[2] = { 449, -1 }, naname[9] = { 444, 475, 468, 465, 419, 409, 408, 418, -1 };


void bye_chk(void) {
  if (actwk[0].mstno.b.h != 5) { byecnt0.w = 0; return; }

  if (byecnt0.w == 0) byecnt0.b.l = 1;


  if (byecnt0.w < 10800) return;
  byecnt0.w = 0;
  actwk[0].mstno.b.h = 43;
  actwk[0].sproffset |= 32768;
  actwk[0].sprpri = 0;
  pl_suu = 1;
  actwk[0].yspeed.w = -1280;
  actwk[0].xspeed.w = 256;
  if (actwk[0].cddat & 1) actwk[0].xspeed.w = -actwk[0].xspeed.w;

  actwk[0].mspeed.w = 0;
  sub_sync(121);
}





void play00(sprite_status* actionwk) {
  unsigned char d0;

  Brake_Req = 0;

  if (actionwk != &actwk[0]) return;

  if (ta_flag == 0 && editmode.b.h != 0) { edit(&actwk[0]); return; }

  d0 = actwk[0].actfree[0];
  if (d0 != 0) {
    ++d0;
    if (actwk[0].cddat & 4) {
      if (d0 >= 45) d0 = 45;
    }
    else if (d0 >= 30) d0 = 30;


    actwk[0].actfree[0] = d0;
  }


  switch (actwk[0].r_no0) {
    case 0:
      play00init();
      break;
    case 2:
      play00move();
      break;
    case 4:
      play00damage();
      break;
    case 6:
      play00die();
      break;
    case 8:
      play00erase();
      break;
  }


  actwk[0].patbase = sncpats[stageno_i.b.h];

  if (Brake_Req == 0) Brake_Sw = 0;
}






void muteki_set(void) {
  if (actwk[12].actno != 0) return;
  plpower_a = 1;
  actwk[12].actno = actwk[13].actno = actwk[14].actno = actwk[15].actno = 3;

  actwk[12].mstno.b.h = 5;
  actwk[13].mstno.b.h = 6;
  actwk[14].mstno.b.h = 7;
  actwk[15].mstno.b.h = 8;

}









void test_mapwrt(void) {}





void play00init(void) {
  actwk[0].r_no0 += 2;
  actwk[0].sprvsize = 19;
  actwk[0].sprhs = 9;
  if (chibi_flag != 0) {
    actwk[0].sprvsize = 10;
    actwk[0].sprhs = 5;
  }


  actwk[0].sproffset = 1920;
  actwk[0].sprpri = 2;
  actwk[0].sprhsize = 24;
  actwk[0].actflg = 4;
  plmaxspdwk = 1536;
  pladdspdwk = 12;
  plretspdwk = 128;
}




void mizuki_set(void) {
  short d2, d3;
  unsigned int d1;
  sprite_status* new_actwk;

  if (stageno.b.h != 0) return;
  if (gametimer.b.l & 1) return;
  d2 = actwk[0].sprvsize;
  d2 += actwk[0].yposi.w.h;
  d3 = actwk[0].xposi.w.h;
  d1 = mapno_chk(d2, d3);
  if ((d1 & 255) != 47) return;
  if (actwk[0].xposi.w.h >= 5568) return;

  if (actwk[0].actfree[2] == 0) return;
  if (actwkchk(&new_actwk) != 0) return;
  new_actwk->actno = 14;
  new_actwk->xposi.w.h = actwk[0].xposi.w.h;
  new_actwk->yposi.w.h = actwk[0].yposi.w.h;
  if (actwk[0].xspeed.w < 0)
    new_actwk->actflg = new_actwk->cddat = 1;
  else
    new_actwk->actflg = new_actwk->cddat = 0;
}




unsigned int mapno_chk(short d2, short d3) {
  unsigned int d1;

  d1 = 2162688;
  d1 += mapwkas[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][d2 >> 8][d3 >> 8];
  return d1;
}



void kuru2(void) {
  unsigned short tmp_xposi;

  if (actwk[0].mstno.b.h == 43 || actwk[0].r_no0 >= 4 || actwk[0].actfree[2] & 8)
    return;

  if ((scramapad(&actwk[0], actwk[0].xposi.w.h, actwk[0].yposi.w.h) & 2047) != 259) return;


  actwk[0].actfree[2] |= 8;
  actwk[0].xspeed.w = 0;
  actwk[0].yspeed.w = actwk[0].yspeed.w < 0 ? -512 : 512;
  actwk[0].actfree[1] = 64;
  tmp_xposi = actwk[0].xposi.w.h;
  tmp_xposi = (tmp_xposi & 65520) + 8;
  *(short*)&actwk[0].actfree[20] = actwk[0].xposi.w.h = tmp_xposi;

  actwk[0].mstno.b.h = 2;
  actwk[0].cddat |= 4;
  actwk[0].sprvsize = 14;
  actwk[0].sprhs = 7;
}



void bura(void) {
  unsigned short tmp_yposi;

  if (actwk[0].mstno.b.h == 43 || plflag == 2 || actwk[0].actfree[2] & 5)
    return;

  if ((scramapad(&actwk[0], actwk[0].xposi.w.h, actwk[0].yposi.w.h - 24) & 2047) != 345) return;


  if (backto_cnt != 0) {
    plpower_a = 0;
    if (backto_cnt >= 90) time_item = 0;
    backto_cnt = 0;
  }

  actwk[0].cddat &= 251;
  actwk[0].xspeed.w = actwk[0].yspeed.w = actwk[0].mspeed.w = 0;
  actwk[0].mstno.b.h = 44;
  actwk[0].actfree[2] |= 4;
  actwk[0].pattimm = 7;
  tmp_yposi = actwk[0].yposi.w.h;
  tmp_yposi = (tmp_yposi - 24 & 65520) + 24;
  actwk[0].yposi.w.h = tmp_yposi;
}






void sibi2(void) {
  short block_no, i;
  short* block_tbl;
  short* tbl[3] = { tate, yoko, naname };

  if (actwk[0].mstno.b.h == 43 || actwk[0].r_no0 >= 4
      || plpower_a != 0 || plpower_m != 0
      || ((short*)&actwk[0])[26] != 0 || st6clrchg == 0)
    return;

  block_tbl = tbl[st6clrchg - 1];
  block_no = scramapad(&actwk[0], actwk[0].xposi.w.h, actwk[0].yposi.w.h);
  block_no &= 2047;
  i = 0;
  while (block_tbl[i] >= 0) {
    if (block_no == block_tbl[i++]) {
      playdamageset(&actwk[0], &actwk[0]); break;
    }
  }
}



void sibi(void) {
  short block_no, i;
  short* block_tbl;
  short tbl[3] = { 579, 580, 581 };
  short tbl0[3] = { 647, 648, 649 };

  if (actwk[0].mstno.b.h == 43 || plpower_a || plpower_m) return;
  if (actwk[0].xposi.w.h >= 2432 && actwk[0].xposi.w.h < 2592) return;

  if (bossflag & 128 || ((short*)&actwk[0])[26]) return;
  if (stageno.b.l == 2) {
    if (actwk[0].xposi.w.h < 2576) goto label1;
    if (boss_sound == 0) return;
    if (generate_flag) goto label1;
  }
  else {
    if (time_flag == 2) generate_flag == 0;
  }

label1:
  block_no = scramapad(&actwk[0], actwk[0].xposi.w.h, actwk[0].yposi.w.h);
  block_no &= 2047;
  if (time_flag != 2 || generate_flag) block_tbl = tbl;
  else block_tbl = tbl0;
  for (i = 0; i < 3; ++i) {
    if (block_tbl[i] == block_no) {
      playdamageset(&actwk[0], &actwk[0]); break;
    }
  }
}



void bfloor(void) {
  unsigned char counter;

  if (actwk[0].mstno.b.h == 43 || bossflag) return;
  if (time_flag < 2) {
    if (time_flag) counter = 90;
    else counter = 60;
    if (clchgcnt[3] == counter) return;
  }

  if ((scramapad(&actwk[0], actwk[0].xposi.w.h - (short)actwk[0].sprhs, actwk[0].yposi.w.h + (short)actwk[0].sprvsize + 2) & 2047) == 543) goto label1;


  if ((scramapad(&actwk[0], actwk[0].xposi.w.h + (short)actwk[0].sprhs, actwk[0].yposi.w.h + (short)actwk[0].sprvsize + 2) & 2047) != 543) return;


label1:
  actwk[0].yspeed.w = -5632;
  actwk[0].cddat |= 2;
  actwk[0].cddat &= 239;
  actwk[0].cddat &= 223;
  actwk[0].actfree[18] = 0;
  if (actwk[0].cddat & 4) return;
  actwk[0].cddat |= 4;
  actwk[0].sprvsize = 14;
  actwk[0].sprhs = 5;
  actwk[0].yposi.w.h += 5;
  actwk[0].mstno.b.h = 2;
  soundset(218);
}





void scr_h(void) {
  short d0, d1;

  if (stageno_i.b.h == 4) return;

  d1 = scra_hline;
  if ((d0 = actwk[0].mspeed.w) < 0) d0 = -d0;

  if (d0 < 1536 || ((actwk[0].actfree[2] & 2) && actwk[0].xposi.w.h < 6912)) {


    if (d1 > 160) d1 -= 2;
    if (d1 < 160) d1 += 2;
  }
  else if (actwk[0].mspeed.w < 0) {
    d1 += 2;
    if (d1 > 224) d1 = 224;
  } else {
    d1 -= 2;
    if (d1 < 96) d1 = 96;
  }


  scra_hline = d1;
}




void play00move(void) {
  scr_h();
  mizuki_set();
  if (debugflag.w != 0 && swdata1.b.l & 16) {
    editmode.b.h = 1;
    return;
  }

  if (plautoflag == 0) swdata.w = swdata1.w;
  else swdata.b.l |= swdata1.b.l & 128;




  if (actwk[0].actfree[2] & 1) {
    if (stageno.b.h == 6) backto_cnt = 0, plpower_a = 0;
    else backto_chk();
  } else {
    switch (actwk[0].cddat & 6) {
      case 0:
        play00walk();
        break;
      case 2:
        play00jump();
        break;
      case 4:
        ball00walk();
        break;
      case 6:
        ball00jump();
        break;
    }


    if (stageno_i.b.h == 4) {
      bfloor();
      sibi();
      sibi2();
      bura();
      kuru2();
    }
    playsp();
  }

  playpowercnt();
  playposiwkset();

  plwaterchk();
  actwk[0].actfree[12] = dirstk[0];
  actwk[0].actfree[13] = dirstk[2];
  if (watercoliflag != 0 && actwk[0].mstno.b.h == 0) {
    actwk[0].mstno.b.h = actwk[0].mstno.b.l;
  }
  patchgmain();
  if ((char)actwk[0].actfree[2] >= 0 && actwk[0].mstno.b.h != 43) {

    pcol(&actwk[0]);
  }
  loopchk();
}






void playpowercnt(void) {
  unsigned short d0;
  unsigned short cal;

  if (backto_cnt < 157) {
    d0 = ((unsigned short*)&actwk[0])[26];
    if (d0 != 0) {
      --((unsigned short*)&actwk[0])[26];
      if (d0 & 4) {
        d0 >>= 3;
        if (!(actwk[0].actfree[2] & 64))
          actionsub(&actwk[0]);
      } else d0 >>= 3;
    }
    else if (!(actwk[0].actfree[2] & 64)) {
      actionsub(&actwk[0]);
    }
  }


  if (plpower_m != 0) {
    d0 = ((unsigned short*)&actwk[0])[27];
    if (d0 != 0) {
      cal = d0 - 1;
      --((unsigned short*)&actwk[0])[27];
      if (cal == 0) {
        if (plpower_s == 0 && boss_sound == 0) {
          if (time_flag == 0) {
            sub_sync(14);
          }

          da_set();
        }

        plpower_m = 0;
      }
    }
  }


  if (plpower_s != 0) {
    d0 = ((unsigned short*)&actwk[0])[28];
    if (d0 != 0) {
      cal = d0 - 1;
      --((unsigned short*)&actwk[0])[28];
      if (cal == 0) {
        plmaxspdwk = 1536;
        pladdspdwk = 12;
        plretspdwk = 128;
        if (plpower_m == 0 && boss_sound == 0) {
          if (time_flag == 0) {
            sub_sync(14);
          }

          da_set();
        }

        plpower_s = 0;
      }
    }
  }
}





void playposiwkset(void) {
  playposiwk[plposiwkadr.w / 2] = actwk[0].xposi.w.h;
  playposiwk[plposiwkadr.w / 2 + 1] = actwk[0].yposi.w.h;
  plposiwkadr.b.l += 4;
}




void plwaterchk(void) {
  unsigned char gavage = 129;
  sprite_status* new_actwk;

  if (stageno.b.h != 2) return;

  if (stageno.b.l == 1 && actwk[0].xposi.w.h < 200) return;

  if (waterposi < actwk[0].yposi.w.h) {
    if (actwk[0].cddat & 64) return;
    actwk[0].cddat |= 64;
    plairset();
    actwk[7].actno = 33;
    actwk[7].userflag.b.h = gavage;
    plmaxspdwk = 768;
    pladdspdwk = 6;
    plretspdwk = 64;
    actwk[0].xspeed.w /= 2;
    actwk[0].yspeed.w /= 4;
    if (actwk[0].yspeed.w == 0) return; else goto label1;
  }

  if (actwk[0].yspeed.w > 0) return;
  if (!(actwk[0].cddat & 64)) return;
  actwk[0].cddat &= 191;
  plmaxspdwk = 1536;
  pladdspdwk = 12;
  plretspdwk = 128;
  actwk[0].yspeed.w *= 2;
  if (actwk[0].yspeed.w == 0) return;
  if (actwk[0].yspeed.w < -4096) actwk[0].yspeed.w = -4096;

label1:
  if (actwkchk(&new_actwk) != 0) return;
  new_actwk->actno = 11;
  new_actwk->xposi.w.h = actwk[0].xposi.w.h;
}




void playsave(void) {
  gKeepWork.plflag_sb = plflag;
  gKeepWork.plxposi_sb = actwk[0].xposi.w.h;
  gKeepWork.plyposi_sb = actwk[0].yposi.w.h;
  gKeepWork.plmspd_sb = actwk[0].mspeed.w;
  gKeepWork.plxspd_sb = actwk[0].xspeed.w;
  gKeepWork.plyspd_sb = actwk[0].yspeed.w;
  gKeepWork.cddat_sb = actwk[0].cddat;
  gKeepWork.cddat_sb &= 247;
  if (stageno_i.b.h != 4) {
    gKeepWork.cddat_sb &= 191;
  }
  gKeepWork.water_flag_sb = water_flag;
  gKeepWork.scralim_down_sb = scralim_down;
  gKeepWork.scra_h_posit_sb = scra_h_posit.w.h;
  gKeepWork.scra_v_posit_sb = scra_v_posit.w.h;
  gKeepWork.scrb_h_posit_sb = scrb_h_posit.w.h;
  gKeepWork.scrb_v_posit_sb = scrb_v_posit.w.h;
  gKeepWork.scrc_h_posit_sb = scrc_h_posit.w.h;
  gKeepWork.scrc_v_posit_sb = scrc_v_posit.w.h;
  gKeepWork.scrz_h_posit_sb = scrz_h_posit.w.h;
  gKeepWork.scrz_v_posit_sb = scrz_v_posit.w.h;
  gKeepWork.waterposi_m_sb = waterposi_m;
  gKeepWork.water_flag_sb = water_flag;
  gKeepWork.waterflag_sb = waterflag;
  plring_s = plring;
  plring_f2_s = plring_f2;
  if (pltime.l > 327680) gKeepWork.pltime_sb = 327680;
  else gKeepWork.pltime_sb = pltime.l;

  gKeepWork.chibi_sb = chibi_flag;
}





void backto_chk(void) {
  short d0, d1, d2;
  char cal;


  if (gKeepWork.TimeWarp == 0) return;

  if (stageno.w == -255) {
    if (time_flag == 0 || time_flag == 2) {
      if (actwk[0].xposi.w.h < 2304) {
        backto_cnt = 0;
        time_item = 0;
        plpower_a = 0;
        return;
      }
    }
  }

  if (actwk[0].actfree[0] != 0) return;
  if (time_item == 0) return;
  d2 = 1536;
  d0 = actwk[0].mspeed.w;
  if (d0 < 0) d0 = -d0;
  if (backto_cnt == 0) backto_cnt = 1;
  if ((d1 = backto_cnt) >= 165) {
    if (plflag != 2) {
      cal = time_flag;
      cal = cal + time_item;
      if (cal < 0) cal = 0;
      else if (cal > 2) cal = 2;
      time_flag = (unsigned char)cal | 128;
      playsave();
    }





    gameflag.b.h = 1;
    fadeout_s();
    return;
  }
  if (d1 >= 157) {
    if (plflag == 2) return;
    scroll_start.b.h = 1;
    cal = time_flag;
    if (cal == 0) {
      sub_sync(130);
    }

    cal = cal + time_item;
    if (cal < 0) cal = 0;
    else if (cal > 2) cal = 2;
    time_flag = (unsigned char)cal | 128;
    playsave();
    plflag = 2;
    return;
  }

  if (d1 < 90) {
    if (d0 >= d2) { muteki_set(); return; }
    backto_cnt = 0;
    plpower_a = 0;
    return;
  }
  if (d0 < d2) {
    backto_cnt = 0;
    time_item = 0;
    plpower_a = 0;
  }
}





void play00walk(void) {
  if (kusya_flag != 0) {
    if (actwk[0].mstno.b.h != 5) return;
    kusya_flag = 0;
  }
  bye_chk();
  if (actwk[0].mstno.b.h == 43) {
    if (chibi_flag != 0) {
      if (actwk[0].patno != 121) return;
    }
    else if (actwk[0].patno < 23) return;

    limitchk();
    speedset(&actwk[0]);
    return;
  }
  chk11();
  backto_chk();
  if (jumpchk() != 0) return;
  keispd();
  levermove();
  ballchk();
  limitchk();
  speedset2(&actwk[0]);
  fcol(&actwk[0]);
  fallchk();
}





void play00jump(void) {
  if (stageno_i.b.h == 4) {
    if (actwk[0].yspeed.w >= 0 && actwk[0].mstno.b.h != 44)
      actwk[0].mstno.b.h = 0;
    if (actwk[0].actfree[2] & 4) {
      buramove(); jumpcolchk(); return;
    }
  }
  else if (watercoliflag == 0 && actwk[0].mstno.b.h != 21 && actwk[0].yspeed.w >= 0) {
    actwk[0].mstno.b.h = 0;
  }
  chk11();
  backto_chk();
  jumpchk2();
  jumpmove();
  limitchk();
  speedset(&actwk[0]);
  if (actwk[0].cddat & 64) actwk[0].yspeed.w -= 40;

  direcchg();

  jumpcolchk();
}




void ball00walk(void) {
  chk11();
  backto_chk();
  if (jumpchk() != 0) return;
  keispd2();
  balllmove();
  limitchk();
  if (actwk[0].actfree[0] == 0) speedset2(&actwk[0]);

  fcol(&actwk[0]);
  fallchk();
}




void ball00jump(void) {
  if (stageno_i.b.h == 4) {
    if (actwk[0].actfree[2] & 8) {
      kuru2move();
      backto_chk();
      jumpcolchk();
      return;
    }
    if (actwk[0].actfree[2] & 4) {
      buramove();
      backto_chk();
      jumpcolchk();
      return;
    }
  }

  chk11();
  backto_chk();
  jumpchk2();
  jumpmove();
  limitchk();

  speedset(&actwk[0]);
  if (actwk[0].cddat & 64) actwk[0].yspeed.w -= 40;

  direcchg();

  jumpcolchk();
}



void kuru2move(void) {
  short tmp_sin, tmp_cos;

  if (actwk[0].actfree[2] & 16) {
    if ((actwk[0].actfree[1] & 127) == 0) {
      actwk[0].mspeed.w = (char)actwk[0].actfree[1] < 0 ? -3072 : 3072;

      actwk[0].sproffset &= 32767;
      actwk[0].actfree[2] &= 231;
      *(short*)&actwk[0].actfree[20] = 0;
      return;
    }
  }
  else if (swdata.b.l & 112) actwk[0].actfree[2] |= 16;

  if ((char)(actwk[0].actfree[1] += 8) >= 0) actwk[0].sproffset |= 32768;
  else actwk[0].sproffset &= 32767;

  sinset(actwk[0].actfree[2], &tmp_sin, &tmp_cos);
  tmp_cos = (tmp_cos * 23) / 256;
  actwk[0].xposi.w.h = *(short*)&actwk[0].actfree[20] + tmp_cos;

  actwk[0].yposi.l += actwk[0].yspeed.w << 8;

  if ((scramapad(&actwk[0], *(short*)&actwk[0].actfree[20], actwk[0].yposi.w.h) & 2047) != 259)
    actwk[0].yspeed.w = -actwk[0].yspeed.w;
}



void buramove(void) {
  if ((scramapad(&actwk[0], actwk[0].xposi.w.h, actwk[0].yposi.w.h - 24) & 2047) != 345 || (swdata.b.l & 112)) {


    actwk[0].actfree[2] &= 251;
    actwk[0].yposi.w.h += 16;
    actwk[0].sprvsize = 19;
    actwk[0].sprhs = 9;
    return;
  }

  if (swdata.b.h & 4) {
    actwk[0].cddat |= 1;
    actwk[0].actflg |= 1;
    actwk[0].xposi.w.h -= 2;
  } else if (swdata.b.h & 8) {
    actwk[0].cddat &= 254;
    actwk[0].actflg &= 254;
    actwk[0].xposi.w.h += 2;
  } else return;
  if ((char)--actwk[0].pattimm >= 0) return;
  actwk[0].pattimm = 7;
  if (++actwk[0].patcnt >= 4) actwk[0].patcnt = 0;
}



void chk11(void) {
  short d0;
  char mapdata;
  char chk11tbl[5] = { 6, 7, 8, 73, 76 };

  if (time_flag != 1) return;
  if (stageno.w != 0) return;
  d0 = ((actwk[0].yposi.w.h >> 1) & 896) + (short)(actwk[0].xposi.b.b1 & 127);

  mapdata = mapwkas[0][0][1][d0 / 128][d0 & 63];
  for (d0 = 0; d0 < 5; ++d0) {
    if (mapdata == chk11tbl[d0]) {
      actwk[0].actfree[2] |= 2;
      return;
    }
  }
  if (!(actwk[0].actfree[2] & 2)) return;
  actwk[0].actfree[2] &= 253;
  if (actwk[0].yspeed.w >= 0) return;
  if ((unsigned short)actwk[0].yspeed.w >= 63488) return;
  actwk[0].xspeed.w = 1536;
  if (!(actwk[0].cddat & 1)) return;
  actwk[0].xspeed.w = -actwk[0].xspeed.w;
}






void levermove(void) {
  short d0;
  short d1;
  short d2;
  unsigned char ride_number;
  int sin_data;
  int cos_data;
  short sin_tmp;
  short cos_tmp;




  if (mizuflag != 0) goto label12;
  if (((unsigned short*)&actwk[0])[33] != 0) goto label10;
  if (swdata.b.h & 4) plwalk_l();
  if (swdata.b.h & 8) plwalk_r();

  if ((unsigned char)actwk[0].direc.b.h + 32 & 192) goto label10;
  if (actwk[0].mspeed.w != 0 && actwk[0].actfree[0] == 0) goto label10;

  if (actwk[0].mspeed.w == 0) {
    actwk[0].cddat &= 223;
    actwk[0].mstno.b.h = 5;
  }
  if (!(actwk[0].cddat & 8)) goto label1;

  ride_number = actwk[0].actfree[19];
  if ((char)actwk[ride_number].cddat < 0) goto label4;
  if (actwk[ride_number].actno == 30) {
    actwk[0].mstno.b.h = 0;
    goto label10;
  }

  d1 = actwk[ride_number].sprhsize;
  d2 = d1 * 2 - 4;
  d1 = d1 + actwk[0].xposi.w.h - actwk[ride_number].xposi.w.h;
  if (d1 < 4) goto label3;
  if (d1 >= d2) goto label2;
  goto label4;

label1:
  d1 = emycol_d(&actwk[0]);
  if (d1 < 12) goto label4;
  if (stageno_i.b.h != 4) {
    soundset(171);
    if (WaveClear != 0) WaveAllStop(), WaveClear = 0;
    actwk[0].actfree[0] = 0;
    actwk[0].mspeed.w = 0;
  }
  if (actwk[0].actfree[12] == 3) {

label2:
    if (actwk[0].cddat & 1) actwk[0].mstno.b.h = 50;
    else actwk[0].mstno.b.h = 6;
    goto label10;
  }

  if (actwk[0].actfree[13] == 3) {

label3:
    if (!(actwk[0].cddat & 1)) actwk[0].mstno.b.h = 50;
    else actwk[0].mstno.b.h = 6;
    goto label10;
  }


label4:
  if (scr_cnt & 15) ++scr_cnt, scr_cnt &= 207;
  if (scr_cnt & 128) goto label7;
  if ((scr_cnt & 64) || (swdata.b.h & 2)) goto label8;
  if ((scr_cnt &= 15) == 0) {
    if (swdata.b.l & 1) { scr_cnt = 1; goto label11; }
  } else {
    if (swdata.b.l & 1) { scr_cnt |= 128; goto label11; }
  }

  if (!(swdata.b.h & 1)) goto label6;
  actwk[0].mstno.b.h = 7;
  if (actwk[0].actfree[0] == 0) goto label5;
  actwk[0].mstno.b.h = 0;
  d0 = 100;
  d1 = d2 = plmaxspdwk;
  if (d1 & 32768) d1 *= 2, d1 |= -32768; else d1 *= 2;
  if (plpower_s != 0) d2 /= 2, d1 -= d2;
  if (actwk[0].cddat & 1) d0 = -d0, d1 = -d1;

  actwk[0].mspeed.w += d0;
  d0 = actwk[0].mspeed.w;
  if (actwk[0].cddat & 1) {
    if (d0 < d1) d0 = d1;
  } else {
    if (d0 > d1) d0 = d1;
  }
  actwk[0].mspeed.w = d0;
  return;

label5:
  if (!(swdata.b.l & 112)) goto label11;
  actwk[0].actfree[0] = 1;
  soundset(156);
  WaveClear = 1;

  goto label11;

label6:
  if (actwk[0].actfree[0] != 30) {
    soundset(171);
    if (WaveClear != 0) WaveAllStop(), WaveClear = 0;
    actwk[0].actfree[0] = 0;
    actwk[0].mspeed.w = 0;
    goto label8;
  }
  actwk[0].actfree[0] = 0;
  soundset(145);
  WaveClear = 0;
  goto label10;



label7:
  if (swdata.b.h & 1) {
    actwk[0].mstno.b.h = 7;
    if (scra_vline != 200) scra_vline += 2;
    goto label11;
  }
label8:
  if (scr_cnt & 64) goto label9;
  if ((scr_cnt &= 15) == 0) {
    if (swdata.b.l & 2) { scr_cnt = 1; goto label11; }
  }
  else if (swdata.b.l & 2) { scr_cnt |= 64; goto label11; }


  if (!(swdata.b.h & 2)) goto label10;
  actwk[0].mstno.b.h = 8;
  if (actwk[0].actfree[0] != 0) goto label11;
  if (!(swdata.b.l & 112)) goto label11;
  actwk[0].actfree[0] = 1;
  actwk[0].mspeed.w = 22;
  if (actwk[0].cddat & 1) actwk[0].mspeed.w = -actwk[0].mspeed.w;
  soundset(156);
  WaveClear = 1;
  ballset();
  goto label11;

label9:
  if (swdata.b.h & 2) {
    actwk[0].mstno.b.h = 8;
    if (scra_vline != 8) scra_vline -= 2;
    goto label11;
  }
label10:
  if (scra_vline == 96) {
    if (!(scr_cnt & 15)) scr_cnt = 0;
    goto label11;
  }
  if (scra_vline < 96) scra_vline += 4;
  scra_vline -= 2;



label11:
  if (!(swdata.b.h & 12) && actwk[0].mspeed.w != 0) {

    if (actwk[0].mspeed.w > 0) {

      if ((actwk[0].mspeed.w -= pladdspdwk) < 0) actwk[0].mspeed.w = 0;
    }
    else {
      if ((actwk[0].mspeed.w += pladdspdwk) >= 0) actwk[0].mspeed.w = 0;
    }
  }
label12:
  sinset(actwk[0].direc.b.h, &sin_tmp, &cos_tmp);
  sin_data = sin_tmp;
  cos_data = cos_tmp;

  cos_data *= actwk[0].mspeed.w;
  cos_data >>= 8;
  actwk[0].xspeed.w = cos_data;
  sin_data *= actwk[0].mspeed.w;
  sin_data >>= 8;
  actwk[0].yspeed.w = sin_data;

  lmovecol();
}


void lmovecol(void) {
  short add_speed = 0;
  char add_dir;
  char tmp_dir;
  unsigned char sonic_dir;

  if (actwk[0].direc.b.h < -64 || actwk[0].mspeed.w == 0) return;
  add_dir = 64;
  if (actwk[0].mspeed.w > 0) add_dir = -add_dir;

  sonic_dir = actwk[0].direc.b.h + add_dir;
  tmp_dir = sonic_dir;
  if ((add_speed = (char)dircolm(&actwk[0], &tmp_dir)) >= 0) return;
  sonic_dir = tmp_dir;
  if (add_speed & 32768) add_speed <<= 8, add_speed |= -32768; else add_speed <<= 8;
  sonic_dir = sonic_dir + 32 & 192;
  switch (sonic_dir) {

    case 0:
      actwk[0].yspeed.w += add_speed;
      break;

    case 64:
      actwk[0].xspeed.w -= add_speed;
      actwk[0].cddat |= 32;
      actwk[0].mspeed.w = 0;
      break;

    case 128:
      actwk[0].yspeed.w -= add_speed;
      break;

    case 192:
      actwk[0].xspeed.w += add_speed;
      actwk[0].cddat |= 32;
      actwk[0].mspeed.w = 0;
      break;
  }


}




void plwalk_l(void) {
  short cal_speed;

  if (actwk[0].actfree[0] != 0) return;
  cal_speed = actwk[0].mspeed.w;
  if (cal_speed <= 0) {

    if (!(actwk[0].cddat & 1)) {
      actwk[0].cddat |= 1;
      actwk[0].cddat &= 223;
      actwk[0].mstno.b.l = 1;
    }

    if (cal_speed > -plmaxspdwk) {
      cal_speed -= pladdspdwk;
      if (cal_speed <= -plmaxspdwk) cal_speed = -plmaxspdwk;
    }

    actwk[0].mspeed.w = cal_speed;
    actwk[0].mstno.b.h = 0;
  }
  else {
    if ((cal_speed -= plretspdwk) < 0) cal_speed = -128;

    actwk[0].mspeed.w = cal_speed;
    if ((unsigned char)actwk[0].direc.b.h + 32 & 192) return;
    if (cal_speed < 1024) return;
    actwk[0].mstno.b.h = 13;
    actwk[0].cddat &= 254;

    if (Brake_Sw == 0) {
      soundset(144);
      Brake_Sw = 1;
    }
    Brake_Req = 1;
  }
}



void plwalk_r(void) {
  short cal_speed;

  if (actwk[0].actfree[0] != 0) return;
  cal_speed = actwk[0].mspeed.w;
  if (cal_speed >= 0) {

    if (actwk[0].cddat & 1) {
      actwk[0].cddat &= 254;
      actwk[0].cddat &= 223;
      actwk[0].mstno.b.l = 1;
    }

    if (cal_speed < plmaxspdwk) {
      cal_speed += pladdspdwk;
      if (cal_speed >= plmaxspdwk) cal_speed = plmaxspdwk;
    }

    actwk[0].mspeed.w = cal_speed;
    actwk[0].mstno.b.h = 0;
  }
  else {
    if ((cal_speed += plretspdwk) >= 0) cal_speed = 128;
    actwk[0].mspeed.w = cal_speed;
    if ((unsigned char)actwk[0].direc.b.h + 32 & 192) return;
    if (cal_speed > -1024) return;
    actwk[0].mstno.b.h = 13;
    actwk[0].cddat |= 1;

    if (Brake_Sw == 0) {
      soundset(144);
      Brake_Sw = 1;
    }
    Brake_Req = 1;
  }
}







void balllmove(void) {
  short d0;
  short d1;
  short d2;
  int sin_data;
  int cos_data;
  short sin_tmp;
  short cos_tmp;


  if (mizuflag != 0) goto label3;
  if (((unsigned short*)&actwk[0])[33] == 0) {
    if (swdata.b.h & 4) ballwalk_l();
    if (swdata.b.h & 8) ballwalk_r();
  }

  if (actwk[0].actfree[0] == 0) goto label1;
  if (stageno_i.b.h == 4) {
    d0 = 50;
  }
  else {
    d0 = 75;
  }
  d1 = d2 = plmaxspdwk;
  if (d1 & 32768) d1 <<= 1, d1 |= -32768; else d1 <<= 1;
  if (plpower_s != 0) d2 /= 2, d1 -= d2;
  if (actwk[0].cddat & 1) d0 = -d0, d1 = -d1;

  actwk[0].mspeed.w += d0;
  d0 = actwk[0].mspeed.w;
  if (actwk[0].cddat & 1) {
    if (d0 < d1) d0 = d1;
  }
  else if (d1 < d0) d0 = d1;


  actwk[0].mspeed.w = d0;
  if ((swdata.b.h & 2) != 0) return;

  if (actwk[0].actfree[0] != 45) {
    soundset(171);
    if (WaveClear != 0) WaveAllStop(), WaveClear = 0;
    actwk[0].actfree[0] = 0;
    actwk[0].mspeed.w = actwk[0].xspeed.w = actwk[0].yspeed.w = 0;
    goto label2;
  }
  actwk[0].actfree[0] = 0;
  soundset(145);
  WaveClear = 0;
  if (!(actwk[0].cddat & 1)) ballwalk_r();
  else ballwalk_l();

label1:
  d0 = actwk[0].mspeed.w;
  if (d0 != 0) {

    if (d0 > 0) {

      d0 = d0 - pladdspdwk / 2;
      if (d0 < 0) d0 = 0;
      actwk[0].mspeed.w = d0;
    }
    else {
      d0 = d0 + pladdspdwk / 2;
      if (d0 > 0) d0 = 0;
      actwk[0].mspeed.w = d0;
    }
  }



  if (actwk[0].mspeed.w != 0) goto label3;



  if (stageno_i.b.h != 4) {
    soundset(171);
    if (WaveClear != 0) WaveAllStop(), WaveClear = 0;
  }

label2:
  actwk[0].cddat &= 251;
  if (chibi_flag != 0) {
    actwk[0].sprvsize = 10;
    actwk[0].sprhs = 5;
    actwk[0].yposi.w.h -= 2;
  } else {
    actwk[0].sprvsize = 19;
    actwk[0].sprhs = 9;
    actwk[0].yposi.w.h -= 5;
  }
  actwk[0].mstno.b.h = 5;

label3:
  sinset(actwk[0].direc.b.h, &sin_tmp, &cos_tmp);
  sin_data = sin_tmp;
  cos_data = cos_tmp;

  sin_data *= actwk[0].mspeed.w;
  sin_data = sin_data >> 8;
  actwk[0].yspeed.w = sin_data;
  cos_data *= actwk[0].mspeed.w;
  cos_data = cos_data >> 8;
  if (cos_data > 4096) cos_data = 4096;
  if (cos_data < -4096) cos_data = -4096;
  actwk[0].xspeed.w = cos_data;

  lmovecol();
}



void ballwalk_l(void) {
  short cal_speed;

  if ((cal_speed = actwk[0].mspeed.w) <= 0) {

    actwk[0].cddat |= 1;
    actwk[0].mstno.b.h = 2;
  }
  else {
    cal_speed = cal_speed - plretspdwk / 4;
    if (cal_speed < 0) cal_speed = -128;
    actwk[0].mspeed.w = cal_speed;
  }
}


void ballwalk_r(void) {
  short cal_speed;

  if ((cal_speed = actwk[0].mspeed.w) >= 0) {

    actwk[0].cddat &= 254;
    actwk[0].mstno.b.h = 2;
  }
  else {
    cal_speed = cal_speed + plretspdwk / 4;
    if (cal_speed > 0) cal_speed = 128;
    actwk[0].mspeed.w = cal_speed;
  }
}



void jumpmove(void) {
  short cal_speed;
  short cmp_speed;





  cal_speed = actwk[0].xspeed.w;
  if (time_flag == 1 && stageno.w == 0) {

    if (actwk[0].xposi.w.h < 1736 || actwk[0].xposi.w.h >= 2112) {
      if (actwk[0].actfree[2] & 2) goto label2; else goto label1;
    } else {
      return;
    }
  }
label1:
  cal_speed = actwk[0].xspeed.w;
  if (swdata.b.h & 4) {
    actwk[0].cddat |= 1;
    cal_speed = cal_speed - pladdspdwk * 2;
    cmp_speed = -plmaxspdwk;
    if (cal_speed <= cmp_speed) cal_speed = cmp_speed;
  }

  if (swdata.b.h & 8) {
    actwk[0].cddat &= 254;
    cal_speed = cal_speed + pladdspdwk * 2;
    if (cal_speed >= plmaxspdwk) cal_speed = plmaxspdwk;
  }

label2:
  actwk[0].xspeed.w = cal_speed;

  if (scra_vline < 96) scra_vline += 2;
  else if (scra_vline > 96) scra_vline -= 2;
  if ((unsigned short)actwk[0].yspeed.w < 64512) return;
  cal_speed = actwk[0].xspeed.w;
  if (cal_speed / 32 == 0) return;
  if (cal_speed > 0) {

    cal_speed = cal_speed - cal_speed / 32;
    if (cal_speed < 0) cal_speed = 0;
  }
  else {
    cal_speed = cal_speed - cal_speed / 32;
    if (cal_speed >= 0) cal_speed = 0;
  }
  actwk[0].xspeed.w = cal_speed;
}




void hedcolchk(void) {
  short tmp_d0, tmp_d1, tmp_d3;
  unsigned char cal_direc;

  cal_direc = (unsigned char)actwk[0].direc.b.h + 32 & 192;
  if (cal_direc == 0) {
    if (dircol_u(&actwk[0], &tmp_d0, &tmp_d1, &tmp_d3) < 0) {
      actwk[0].mspeed.w = actwk[0].xspeed.w = actwk[0].yspeed.w = 0;
      actwk[0].mstno.b.h = 11;
    }
  }
}




void limitchk(void) {
  short cal_limit_l, cal_limit_r, position_wk;
  int cal_position, cal_speed;

  cal_position = actwk[0].xposi.l;
  cal_speed = actwk[0].xspeed.w;
  if (cal_speed & 0x80000000) cal_speed <<= 8, cal_speed |= 0x80000000; else cal_speed <<= 8;
  cal_position += cal_speed;
  position_wk = cal_position >> 16;
  cal_limit_l = scralim_left + 16;
  cal_limit_r = scralim_right + 304;
  if (bossstart == 0) cal_limit_r += 56;
  if (position_wk < cal_limit_l) {

    actwk[0].xposi.w.h = cal_limit_l;
    actwk[0].xposi.w.l = actwk[0].xspeed.w = actwk[0].mspeed.w = 0;
  }
  if (position_wk >= cal_limit_r) {

    actwk[0].xposi.w.h = cal_limit_r;
    actwk[0].xposi.w.l = actwk[0].xspeed.w = actwk[0].mspeed.w = 0;
  }

  if (scralim_down + 224 >= actwk[0].yposi.w.h) return;

  if (actwk[0].mstno.b.h != 43) playdieset(&actwk[0]);
  else actwk[0].r_no0 = 6;
}




void ballchk(void) {
  if (mizuflag != 0) return;

  if (actwk[0].mspeed.w < 128 && actwk[0].mspeed.w > -128) return;
  if ((swdata.b.h & 12) || !(swdata.b.h & 2)) return;
  ballset();
}


void ballset(void) {
  if (!(actwk[0].cddat & 4)) {

    actwk[0].cddat |= 4;
    if (chibi_flag != 0) {
      actwk[0].sprvsize = 8;
      actwk[0].sprhs = 5;
      actwk[0].yposi.w.h += 2;
    }
    else {
      actwk[0].sprvsize = 14;
      actwk[0].sprhs = 7;
      actwk[0].yposi.w.h += 5;
    }
  }
  else if (stageno_i.b.h == 4) return;

  actwk[0].mstno.b.h = 2;
  if (actwk[0].mspeed.w >= 0 && (actwk[0].mspeed.w < 512 || stageno_i.b.h == 4))
    actwk[0].mspeed.w = 512;
}




unsigned char jumpchk(void) {
  char cal_char;
  unsigned char cal_direc, ret_flag;
  int cal_jump, sin_data, cos_data;
  short sin_tmp, cos_tmp;

  cal_direc = 0;
  cal_jump = 0;
  ret_flag = 0;

  if (actwk[0].actfree[0] != 0) return ret_flag;
  if ((swdata.b.h & 3) && actwk[0].mspeed.w == 0) return ret_flag;

  if (!(swdata.b.l & 112)) return ret_flag;
  if ((actwk[0].cddat & 8) && frip_spd(&cal_jump, &cal_direc) == 0) goto label1;


  cal_direc = (unsigned char)actwk[0].direc.b.h + 128;
  cal_char = cal_direc;
  if (dircol2(&actwk[0], &cal_char) < 6) return ret_flag;
  cal_jump = 1664;
  if (actwk[0].cddat & 64) cal_jump = 896;
  cal_direc = (unsigned char)actwk[0].direc.b.h - 64;

label1:
  sinset(cal_direc, &sin_tmp, &cos_tmp);
  sin_data = sin_tmp;
  cos_data = cos_tmp;

  cos_data *= cal_jump;
  cos_data = cos_data >> 8;
  actwk[0].xspeed.w += cos_data;
  sin_data *= cal_jump;
  sin_data = sin_data >> 8;
  actwk[0].yspeed.w += sin_data;
  actwk[0].cddat |= 2;
  actwk[0].cddat &= 223;
  ret_flag = 255;

  actwk[0].actfree[18] = 1;
  actwk[0].actfree[14] = 0;

  scr_cnt = 0;
  soundset(146);

  if (actwk[0].cddat & 4) {
    actwk[0].cddat |= 16;
    return ret_flag;
  }
  if (chibi_flag != 0) {
    actwk[0].sprvsize = 8;
    actwk[0].sprhs = 5;
    actwk[0].yposi.w.h += 2;
  } else {
    actwk[0].sprvsize = 14;
    actwk[0].sprhs = 7;
    actwk[0].yposi.w.h += 5;
  }
  actwk[0].cddat |= 4;
  actwk[0].mstno.b.h = 2;
  return ret_flag;
}


void jumpchk2(void) {
  short cal_speed;

  if (actwk[0].actfree[18] != 0) {
    cal_speed = -1024;
    if (actwk[0].cddat & 64) cal_speed = -512;
    if (cal_speed > actwk[0].yspeed.w) {
      if (!(swdata.b.h & 112)) {
        actwk[0].actfree[0] = 0;
        actwk[0].yspeed.w = cal_speed;
      }
    }
  }
  else if (stageno_i.b.h != 4) {
    if (actwk[0].yspeed.w < -4032) actwk[0].yspeed.w = -4032;
  }
}




void keispd(void) {
  unsigned char cal_direc;
  int sin_data;
  short sin_tmp, cos_tmp;

  if (actwk[0].actfree[0] != 0) return;
  cal_direc = (unsigned char)actwk[0].direc.b.h + 96;
  if (cal_direc >= 192) return;
  cal_direc = actwk[0].direc.b.h;

  sinset(actwk[0].direc.b.h, &sin_tmp, &cos_tmp);
  sin_data = sin_tmp;

  sin_data *= 32;
  sin_data = sin_data >> 8;
  if (actwk[0].mspeed.w == 0) return;
  if (actwk[0].mspeed.w > 0) {
    if (sin_data != 0) actwk[0].mspeed.w += sin_data;;
  } else {
    actwk[0].mspeed.w += sin_data;
  }
}


void keispd2(void) {
  unsigned char cal_direc;
  int sin_data;
  short sin_tmp, cos_tmp;

  if (actwk[0].actfree[0] != 0) return;
  cal_direc = (unsigned char)actwk[0].direc.b.h + 96;
  if (cal_direc >= 192) return;
  cal_direc = actwk[0].direc.b.h;

  sinset(actwk[0].direc.b.h, &sin_tmp, &cos_tmp);
  sin_data = sin_tmp;

  sin_data *= 80;
  sin_data = sin_data >> 8;
  if (actwk[0].mspeed.w >= 0) {
    if (sin_data < 0) sin_data /= 4;
    actwk[0].mspeed.w += sin_data;
  } else {
    if (sin_data >= 0) sin_data /= 4;
    actwk[0].mspeed.w += sin_data;
  }
}




void fallchk(void) {
  if (actwk[0].actfree[14] != 0) return;
  if (((unsigned short*)&actwk[0])[33] == 0) {

    if (!((unsigned char)actwk[0].direc.b.h + 32 & 192)) return;
    if (actwk[0].mspeed.w > 640 || actwk[0].mspeed.w < -640)
      return;
    actwk[0].mspeed.w = 0;
    actwk[0].cddat |= 2;
    ((unsigned short*)&actwk[0])[33] = 30;
  } else {
    --((unsigned short*)&actwk[0])[33];
  }
}




void direcchg(void) {
  char cal_direc;

  if ((actwk[0].actfree[2] & 2) != 0) return;
  if ((cal_direc = actwk[0].direc.b.h) == 0) return;
  if (cal_direc < 0) {
    if ((cal_direc += 2) > 0) cal_direc = 0;
  } else {
    if ((cal_direc -= 2) < 0) cal_direc = 0;
  }
  actwk[0].direc.b.h = cal_direc;
}







void jumpcolchk(void) {
  short chk_d0, chk_d1, tmp_d3;
  char chk_d2, chk_d3;
  unsigned char cal_direc;

  cal_direc = atan_sonic(actwk[0].xspeed.w, actwk[0].yspeed.w);
  debugwork.b.b1 = cal_direc;
  cal_direc -= 32;
  debugwork.b.b2 = cal_direc;
  cal_direc &= 192;
  debugwork.b.b3 = cal_direc;
  switch (cal_direc) {

    case 0:
      chk_d1 = dircol_l2(&actwk[0]);
      if (chk_d1 < 0) {
        actwk[0].xposi.w.h -= chk_d1;
        actwk[0].xspeed.w = 0;
      }
      chk_d1 = dircol_r2(&actwk[0]);
      if (chk_d1 < 0) {
        actwk[0].xposi.w.h += chk_d1;
        actwk[0].xspeed.w = 0;
      }
      dircol_d(&actwk[0], &chk_d0, &chk_d1, &tmp_d3);
      chk_d3 = tmp_d3;
      debugwork.b.b4 = chk_d1;
      if (chk_d1 >= 0) return;
      chk_d2 = -(actwk[0].yspeed.b.h + 8);
      if ((char)chk_d1 < chk_d2 && (char)chk_d0 < chk_d2) return;

      actwk[0].yposi.w.h += chk_d1;
      actwk[0].direc.b.h = chk_d3;
      jumpcolsub();
      actwk[0].mstno.b.h = 0;
      if ((unsigned char)chk_d3 + 32 & 64) {

        actwk[0].xspeed.w = 0;
        if (actwk[0].yspeed.w > 4032) actwk[0].yspeed.w = 4032;
      } else {
        if (!((unsigned char)chk_d3 + 16 & 32)) {

          actwk[0].yspeed.w = 0;
          actwk[0].mspeed.w = actwk[0].xspeed.w;
          return;
        }
        actwk[0].yspeed.w /= 2;
      }

      actwk[0].mspeed.w = actwk[0].yspeed.w;
      if (chk_d3 < 0) actwk[0].mspeed.w = -actwk[0].mspeed.w;
      break;


    case 64:
      chk_d1 = dircol_l2(&actwk[0]);
      if (chk_d1 < 0) {
        actwk[0].xposi.w.h -= chk_d1;
        actwk[0].xspeed.w = 0;
        actwk[0].mspeed.w = actwk[0].yspeed.w;
        return;
      }
      dircol_u(&actwk[0], &chk_d0, &chk_d1, &tmp_d3);
      if (chk_d1 < 0) {
        actwk[0].yposi.w.h -= chk_d1;
        if (actwk[0].yspeed.w < 0) actwk[0].yspeed.w = 0;
        return;
      }

      if (actwk[0].yspeed.w < 0) return;
      dircol_d(&actwk[0], &chk_d0, &chk_d1, &tmp_d3);
      chk_d3 = tmp_d3;
      if (chk_d1 >= 0) return;
      actwk[0].yposi.w.h += chk_d1;
      actwk[0].direc.b.h = chk_d3;
      jumpcolsub();
      actwk[0].mstno.b.h = 0;
      actwk[0].yspeed.w = 0;
      actwk[0].mspeed.w = actwk[0].xspeed.w;
      break;


    case 128:
      chk_d1 = dircol_l2(&actwk[0]);
      if (chk_d1 < 0) {
        actwk[0].xposi.w.h -= chk_d1;
        actwk[0].xspeed.w = 0;
      }
      chk_d1 = dircol_r2(&actwk[0]);
      if (chk_d1 < 0) {
        actwk[0].xposi.w.h += chk_d1;
        actwk[0].xspeed.w = 0;
      }

      dircol_u(&actwk[0], &chk_d0, &chk_d1, &tmp_d3);
      chk_d3 = tmp_d3;
      if (chk_d1 >= 0) return;
      actwk[0].yposi.w.h -= chk_d1;
      if (!((unsigned char)chk_d3 + 32 & 64)) {
        actwk[0].yspeed.w = 0;
        return;
      }
      actwk[0].direc.b.h = chk_d3;
      jumpcolsub0();
      actwk[0].mspeed.w = actwk[0].yspeed.w;
      if (chk_d3 < 0) actwk[0].mspeed.w = -actwk[0].mspeed.w;
      break;


    case 192:
      chk_d1 = dircol_r2(&actwk[0]);
      if (chk_d1 < 0) {
        actwk[0].xposi.w.h += chk_d1;
        actwk[0].xspeed.w = 0;
        actwk[0].mspeed.w = actwk[0].xspeed.w;
        return;
      }
      dircol_u(&actwk[0], &chk_d0, &chk_d1, &tmp_d3);
      if (chk_d1 < 0) {
        actwk[0].yposi.w.h -= chk_d1;
        if (actwk[0].yspeed.w < 0) actwk[0].yspeed.w = 0;
        return;
      }

      if (actwk[0].yspeed.w < 0) return;
      dircol_d(&actwk[0], &chk_d0, &chk_d1, &tmp_d3);
      chk_d3 = tmp_d3;
      if (chk_d1 >= 0) return;
      actwk[0].yposi.w.h += chk_d1;
      actwk[0].direc.b.h = chk_d3;
      jumpcolsub();
      actwk[0].mstno.b.h = 0;
      actwk[0].yspeed.w = 0;
      actwk[0].mspeed.w = actwk[0].xspeed.w;
      break;
  }



}


void jumpcolsub(void) {


  actwk[0].cddat &= 205;
  if (actwk[0].cddat & 4) {
    actwk[0].cddat &= 251;
    if (chibi_flag != 0) {
      actwk[0].sprvsize = 10;
      actwk[0].sprhs = 5;
      actwk[0].yposi.w.h -= 2;
    } else {
      actwk[0].sprvsize = 19;
      actwk[0].sprhs = 9;
      actwk[0].yposi.w.h -= 5;
    }
    actwk[0].mstno.b.h = 0;
    if (stageno_i.b.h != 4) {
      soundset(171);
      if (WaveClear != 0) WaveAllStop(), WaveClear = 0;
    }
  }

  actwk[0].actfree[18] = 0;
  emyscorecnt = 0;
}


void jumpcolsub0(void) {
  actwk[0].cddat &= 205;
  actwk[0].actfree[18] = 0;
  emyscorecnt = 0;
}



void play00damage(void) {
  speedset2(&actwk[0]);
  actwk[0].yspeed.w += 48;
  if (actwk[0].cddat & 64) actwk[0].yspeed.w -= 32;
  playsp();
  play00damage_sub();
  limitchk();
  playposiwkset();
  patchgmain();
  actionsub(&actwk[0]);
}


void play00damage_sub(void) {
  if (scralim_down + 224 < actwk[0].yposi.w.h) {
    playdieset(&actwk[0]);
    return;
  }
  jumpcolchk();
  if (actwk[0].cddat & 2) return;
  actwk[0].yspeed.w = actwk[0].xspeed.w = actwk[0].mspeed.w = 0;
  actwk[0].mstno.b.h = 0;
  actwk[0].r_no0 -= 2;
  ((short*)&actwk[0])[26] = 120;
}



void play00die(void) {
  play00die_sub();
  speedset(&actwk[0]);
  playposiwkset();
  patchgmain();
  actionsub(&actwk[0]);
}


void play00die_sub(void) {
  sprite_status* new_actwk;

  if (scralim_down + 256 >= actwk[0].yposi.w.h) return;
  actwk[0].yspeed.w = -56;
  actwk[0].r_no0 += 2;
  pltime_f = 0;
  ++pl_suu_f;
  if ((char)--pl_suu < 0) pl_suu = 0;

  if (actwk[0].mstno.b.h == 43 || ta_flag == 0) {
    actwkchk(&new_actwk);
    new_actwk->actno = 59;
    ((short*)&actwk[0])[31] = 480;
    if (pl_suu == 0) return;
  } else {
    pl_suu = 0;
  }
  ((short*)&actwk[0])[31] = 60;
}



void play00erase(void) {
  if (((unsigned short*)&actwk[0])[31] == 0) return;
  --((unsigned short*)&actwk[0])[31];
  if (((unsigned short*)&actwk[0])[31] != 0) return;
  gameflag.w = 1;




  flagwkclr();
  flowercnt[0] = flowercnt[1] = flowercnt[2] = tv_flag = 0;
  if (markerno == 0 && time_flag == 1) play_start &= 253;


  if (pl_suu != 0) {
    if (time_flag == 1) {
      if (markerno != 0) plflag = 1;
    } else {
      plflag = 0;
    }
  }
  sub_sync(14);

}








void loopchk(void) {
  short index;
  unsigned char mapdata;

  if (stageno.b.h != 3 && stageno.b.h != 5 && stageno.b.h != 2 && stageno.b.h != 0) return;


  index = (actwk[0].yposi.w.h >> 1 & 896) + ((short)actwk[0].xposi.b.b1 & 127);

  mapdata = mapwkas[stageno_i.b.h][stageno_i.b.l][(time_flag_i & 0x7F) + ((time_flag_i & 0x7F) == 2 ? generate_flag : 0)][index / 128][index & 63];
  if (mapdata == ballmapno) {
    if (stageno.b.h != 0 || (actwk[0].yposi.w.h & 255) >= 144) {
      ballset(); return;
    }
  }
  else {
    if (mapdata == ballmapno2) { ballset(); return; }
  }

  if (mapdata != loopmapno && mapdata != loopmapno2) {
    actwk[0].actflg &= 191;
    return;
  }
  if (mapdata == loopmapno2) {

    if (stageno.b.h == 5) { st7_x(); return; }
    if (actwk[0].cddat & 2) {
      actwk[0].actflg &= 191;
      return;
    }
  }

  if ((unsigned char)actwk[0].xposi.b.b2 < 44) {
    actwk[0].actflg &= 191;
    return;
  }

  if ((unsigned char)actwk[0].xposi.b.b2 >= 224) {
    actwk[0].actflg |= 64;
    return;
  }

  if (!(actwk[0].actflg & 64)) {
    if (actwk[0].direc.b.h != 0 && (unsigned char)actwk[0].direc.b.h <= 128)
      actwk[0].actflg |= 64;
    return;
  }

  if ((unsigned char)actwk[0].direc.b.h <= 128) return;
  actwk[0].actflg &= 191;
}



void st7_x(void) {
  short y_position;


  if (actwk[0].yspeed.w >= 0) {
    y_position = (unsigned short)actwk[0].yposi.w.h & 255;
    if ((actwk[0].xposi.w.h & 255) < 128) {

      if (y_position < 56) actwk[0].actflg |= 64;
      else if (y_position >= 128) actwk[0].actflg &= 191;
    }
    else if (y_position < 56) actwk[0].actflg &= 191;
    else if (y_position >= 128) actwk[0].actflg |= 64;
  }
}





void patchgmain(void) {
  char pat_index;
  unsigned char* pat_pointer;

  if (actwk[0].mstno.b.h != actwk[0].mstno.b.l) {
    actwk[0].mstno.b.l = actwk[0].mstno.b.h;
    actwk[0].patcnt = actwk[0].pattim = 0;
  }

  pat_index = little_patchg(actwk[0].mstno.b.h);
  pat_pointer = playchgs[stageno_i.b.h][pat_index];
  if (*pat_pointer >= 128) { playrunchg(*pat_pointer); return; }

  actwk[0].actflg = (actwk[0].actflg & 252) | (actwk[0].cddat & 1);
  if ((char)--actwk[0].pattim >= 0) return;
  actwk[0].pattim = *pat_pointer;
  patchgmain2(pat_pointer);
}


void patchgmain2(unsigned char* pat_pointer) {
  unsigned char pat_no;

  if ((pat_no = pat_pointer[actwk[0].patcnt + 1]) < 253) {
    actwk[0].patno = pat_no;
    ++actwk[0].patcnt;
  }
  else {

    switch (pat_no) {
      case 255:
        actwk[0].patcnt = 1;
        actwk[0].patno = pat_pointer[1];
        break;
      case 254:
        actwk[0].patno = pat_pointer[actwk[0].patcnt + 1
                       - pat_pointer[actwk[0].patcnt + 2]];
        actwk[0].patcnt = actwk[0].patcnt
                        - (pat_pointer[actwk[0].patcnt + 2] - 1);
        break;
      case 253:
        actwk[0].mstno.b.h = pat_pointer[actwk[0].patcnt + 2];
        break;
    }
  }


}



void playrunchg(unsigned char pat_no) {
  unsigned char direction, cal_data, chara_data;
  unsigned char* pat_pointer;
  short cal_speed;

  if ((char)--actwk[0].pattim >= 0) return;
  if (pat_no != 255) { playrunchg2(pat_no); return; }
  if (chibi_flag != 0) { little_runchg(); return; }

  cal_data = 0;
  direction = actwk[0].direc.b.h;
  chara_data = actwk[0].cddat & 1;
  if (chara_data == 0) direction = 255 - direction;
  if (!(actwk[0].actfree[2] & 2)) direction += 16;
  else direction += 8;
  if ((char)direction < 0) cal_data = 3;

  actwk[0].actflg &= 252;
  chara_data ^= cal_data;
  actwk[0].actflg |= chara_data;
  if (actwk[0].cddat & 32) { playrunchg3(253); return; }

  if ((cal_speed = actwk[0].mspeed.w) < 0) cal_speed = -cal_speed;

  if (actwk[0].actfree[2] & 2) {
    direction >>= 4, direction &= 15;
    direction <<= 1;
    direction &= 14;
    pat_pointer = plchg53;
  } else {
    direction >>= 4;
    direction &= 6;
    if ((stageno_i.b.h != 4 && cal_speed >= 2560) || (stageno_i.b.h == 4 && cal_speed > 2560)) pat_pointer = plchg49;
    else if ((stageno_i.b.h != 4 && cal_speed >= 1536) || (stageno_i.b.h == 4 && cal_speed > 1536)) pat_pointer = plchg01;
    else {
      pat_pointer = plchg00;
      direction = direction + direction / 2;
    }
  }

  cal_speed = 2048 - cal_speed;
  if (cal_speed < 0) cal_speed = 0;
  cal_speed /= 256;
  actwk[0].pattim = cal_speed;
  patchgmain2(pat_pointer);
  actwk[0].patno = actwk[0].patno + direction * 2;
}


void playrunchg2(unsigned char pat_no) {
  unsigned char direction;
  unsigned char* pat_pointer;
  short cal_speed;

  if (pat_no != 254) { playrunchg3(pat_no); return; }
  if ((cal_speed = actwk[0].mspeed.w) < 0) cal_speed = -cal_speed;
  if (chibi_flag != 0) pat_pointer = plchg35;
  else {
    if (actwk[0].actfree[2] & 2) {
      direction = (char)actwk[0].direc.b.h;
      direction = direction + 16 & 192;
      if (direction != 0) pat_pointer = plchg54;
      else pat_pointer = plchg03;
    }
    else if (cal_speed < 1536) pat_pointer = plchg02;
    else pat_pointer = plchg03;
  }


  cal_speed = 1024 - cal_speed;
  if (cal_speed < 0) cal_speed = 0;
  cal_speed /= 256;
  actwk[0].pattim = cal_speed;
  actwk[0].actflg &= 252;
  actwk[0].actflg |= actwk[0].cddat & 1;
  patchgmain2(pat_pointer);
}


void playrunchg3(unsigned char pat_no) {
  unsigned char* pat_pointer;
  short cal_speed;

  if (pat_no != 253) { playetc_chg(); return; }
  if ((cal_speed = actwk[0].mspeed.w) >= 0) cal_speed = -cal_speed;
  cal_speed += 2048;
  if (cal_speed < 0) cal_speed = 0;
  cal_speed >>= 6;
  actwk[0].pattim = cal_speed;
  if (chibi_flag != 0) pat_pointer = plchg39;
  else pat_pointer = plchg04;
  actwk[0].actflg &= 252;
  actwk[0].actflg |= actwk[0].cddat & 1;
  patchgmain2(pat_pointer);
}


void playetc_chg(void) {
  char pat_index;
  unsigned char* pat_pointer;

  pat_index = little_patchg(actwk[0].mstno.b.h);
  pat_pointer = playchgs[stageno_i.b.h][pat_index];

  actwk[0].patno = pat_pointer[actwk[0].patcnt + 1];
  actwk[0].pattim = 0;
}



void little_runchg(void) {
  unsigned char direction;
  unsigned char* pat_pointer;
  short cal_speed;

  direction = actwk[0].direc.b.h;
  if (!(actwk[0].cddat & 1)) direction = 255 - direction;
  direction += 16;

  actwk[0].actflg &= 252;
  actwk[0].actflg |= actwk[0].cddat & 1;
  if ((direction += 48) >= 96) {
    actwk[0].cddat |= 4;
    actwk[0].sprvsize = 10;
    actwk[0].sprhs = 5;
    playrunchg2(254);
    return;
  }

  if ((cal_speed = actwk[0].mspeed.w) < 0) cal_speed = -cal_speed;
  if (cal_speed >= 1536) pat_pointer = plchg34;
  else pat_pointer = plchg33;
  cal_speed = 2048 - cal_speed;
  if (cal_speed < 0) cal_speed = 0;
  cal_speed /= 256;
  actwk[0].pattim = cal_speed;
  patchgmain2(pat_pointer);
}



char little_patchg(char pat_index) {
  char tbl[80] =
  {
    33, 24, 35, 35, 39, 31, 38, 40, 32,  9,
    10, 11, 12, 36, 14, 15, 40, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 37, 37, 28, 29,
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 48, 44, 45, 46, 47,  0,  0,
     0,  0,  0,  0,  0,  0, 57,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  };

  if (chibi_flag != 0) return tbl[pat_index];
  return pat_index;
}


























void playwrt(void) {}





unsigned char frip_spd(int* cal_jump, unsigned char* cal_direc) {
  short cal_x;
  char ride_no;

  ride_no = actwk[0].actfree[19];
  if (actwk[ride_no].actno != 30) return 255;


  actwk[ride_no].mstno.b.h = 1;
  *cal_direc = atan_sonic(
    actwk[ride_no].xposi.w.h - actwk[0].xposi.w.h,
    actwk[ride_no].yposi.w.h + 24 - actwk[0].yposi.w.h
  );
  cal_x = (actwk[0].xposi.w.h - actwk[ride_no].xposi.w.h) + (short)actwk[ride_no].sprhsize;

  if (!(actwk[ride_no].cddat & 1)) cal_x = 64 - cal_x;

  *cal_jump = -((cal_x * 2560) / 64) - 2560;
  return 0;
}
