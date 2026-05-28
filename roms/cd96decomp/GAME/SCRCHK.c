#include "EQU.h"
#include "SCRCHK.h"







































void scrchk(void) {
  short ywk;

  switch (stageno.b.h) {
    case 0:
      zone1chk(); break;
    case 1:
      zone3chk(); break;
    case 2:
      zone4chk(); break;
    case 3:
      zone5chk(); break;
    case 4:
      zone6chk(); break;
    case 5:
      zone7chk(); break;
    case 6:
      zone8chk(); break;
  }


  if (actwk[0].mstno.b.h == 43 && !(stageno_i.b.h == 2 && (time_flag_i & 0x7F) == 1)) {
    scralim_down = scra_v_posit.w.h;
    scralim_n_down = scra_v_posit.w.h;
  }
  ywk = 4;
  if (scralim_n_down == scralim_down) return;



  if ((unsigned short)scralim_n_down < (unsigned short)scralim_down) {

    ywk *= -1;
    if ((unsigned short)scralim_n_down < (unsigned short)scra_v_posit.w.h) {
      scralim_down = scra_v_posit.w.h & 65534;
    }

    scralim_down += ywk;
    limmoveflag = 1;

    return;
  }

  if ((unsigned short)(scra_v_posit.w.h + 8) >= (unsigned short)scralim_down) {

    if (actwk[0].cddat & 2) {
      ywk *= 4;
    }
  }

  if (stageno_i.b.h == 2 && (time_flag_i & 0x7F) == 1) {
    scralim_down = ywk;
  }
  else {
    scralim_down += ywk;
  }
  limmoveflag = 1;
}



void zone1chk(void) {
  switch (stageno.b.l) {
    case 0:
      zone11chk(); break;
    case 1:
      zone12chk(); break;
    case 2:
      zone13chk(); break;
  }


}


void zone11chk(void) {
  if (time_flag != 1) {
    zone12chk();
  }
  else {
    if ((unsigned short)actwk[0].xposi.w.h >= 7190) {
      if ((unsigned short)actwk[0].xposi.w.h < 8646) {
        scra_vline = 136;
      }
    }

    scralim_n_down = 1808;
    if ((unsigned short)scra_h_posit.w.h >= 2112) {



      if (pltime_f != 0 && (unsigned short)scralim_left < 2080) {

        scralim_left = scralim_n_left = 2080;

      }
      if ((unsigned short)scra_h_posit.w.h >= 3584) {
        scralim_n_down = 784;
      }
      else {
        scralim_n_down = 1040;
      }
    }
  }
}


void zone12chk(void) {
  scralim_n_down = 784;

}


void zone13chk(void) {
  if (bossflag) return;
  scralim_n_down = 784;
  bossclr_scr(3440, 784);
}


void zone3chk(void) {
  switch (stageno.b.l) {
    case 0:
      zone31chk(); break;
    case 1:
      zone31chk(); break;
    case 2:
      zone33chk(); break;
  }


}


void zone31chk(void) {
  scralim_n_down = 1296;

}


void zone33chk(void) {
  if (bossflag) {
    bossclr_scrset(96);
  }
  else {
    scralim_n_down = 1296;
  }

}


void zone6chk(void) {
  unsigned short wD0, wD1;

  if (!(bossflag & 16)) {
    scralim_n_down = 1808;
    return;
  }

  if (bossclr_scr(2976, 464) == 0) {




    if (actwk[0].yposi.w.h <= 664) {

      wD0 = 464;
    }
    else if (actwk[0].yposi.w.h <= 1176) {

      wD0 = 976;
    }
    else {

      wD0 = 1488;
    }

    wD1 = wD0;
    scralim_n_down = wD0;
    wD0 -= scralim_down;
    if ((short)wD0 < 0) {
      wD0 = -(short)wD0;
    }
    if (wD0 < 3) {
      scralim_down = wD1;
    }
  }
}


void zone5chk(void) {
  switch (stageno.b.l) {
    case 0:
      zone51chk(); break;
    case 1:
      zone51chk(); break;
    case 2:
      zone53chk(); break;
  }


}

void zone51chk(void) {
  scralim_n_down = 784;

}

void zone53chk(void) {
  if (bossclr_scr(3600, 504) == 0) {



    if (bossflag) {

      scralim_down = 504;
      scralim_n_down = 504;

    }
    else {
      scralim_n_down = 800;
    }
  }
}



void zone8chk(void) {
  switch (stageno.b.l) {
    case 0:
      zone81chk(); break;
    case 1:
      zone81chk(); break;
    case 2:
      zone83chk(); break;
  }


}


void zone81chk(void) {
  scralim_n_down = 1808;

}

void zone83chk(void) {
  if (bossflag) {

    scralim_down = scralim_n_down = 268;


  }
  else {
    scralim_n_down = 784;
  }

}




void zone4chk(void) {
  switch (stageno.b.l) {
    case 0:
      zone41chk(); break;
    case 1:
      zone42chk(); break;
    case 2:
      zone43chk(); break;
  }


}



void zone41chk(void) {
  scralim_n_down = 1296;

}

void zone42chk(void) {
  if (actwk[0].mstno.b.h == 43 || actwk[0].r_no0 >= 6) {

    scralim_down = 1808;
    scralim_n_down = 1808;
  }
  else {

    scralim_down = 2048;
    scralim_n_down = 2048;
    if (scra_h_posit.w.h >= 512) {
      scralim_down = 1808;
      scralim_n_down = 1808;
    }
  }

}

void zone43chk(void) {
  if (bossclr_scr(2808, 1216) == 0) {


    if (bossflag) {

      scralim_down = 1264;
      scralim_n_down = 1264;
    }
  }
}




void zone7chk(void) {
  switch (stageno.b.l) {
    case 0:
      zone71chk(); break;
    case 1:
      zone72chk(); break;
    case 2:
      zone73chk(); break;
  }


}



void zone71chk(void) {
  scralim_n_down = 1296;

}

void zone72chk(void) {
  scralim_n_down = 1808;

}

void zone73chk(void) {
  unsigned short wD1;

  if (actwk[0].xposi.w.h < 2352) {
    scralim_n_down = 528;
    return;
  }

  if (actwk[0].xposi.w.h >= 3520) {

    scralim_n_down = 528;
  }
  else {

    scralim_n_down = 288;
    wD1 = 288 - (unsigned short)scralim_down;
    if ((short)wD1 < 0) {
      wD1 = -(short)wD1;
    }
    if (wD1 < 4) {
      scralim_down = 288;
    }
  }
}










int bossclr_scr(short XPosi, short DownLim) {
  if (actwk[0].xposi.w.h >= XPosi) {
    return bossclr_scrset(DownLim);
  }
  return 0;
}


int bossclr_scrset(short DownLim) {
  short temp;

  scralim_n_down = DownLim;
  DownLim -= scralim_down;
  if (DownLim < 0) {
    DownLim *= -1;
  }
  if (DownLim < 4) {
    scralim_down = scralim_n_down;
  }
  temp = actwk[0].xposi.w.h - 160;
  if (temp >= scralim_left) {
    if (temp > scralim_right) {
      temp = scralim_right;
    }
    scralim_left = temp;
    scralim_n_left = temp;
  }
  return 1;
}
