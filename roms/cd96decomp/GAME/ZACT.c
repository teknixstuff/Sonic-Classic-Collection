#include "TYPES.h"

extern aset_info z11asettbl[1];
extern aset_info z12asettbl[1];
extern aset_info z13asettbl[1];
extern aset_info z31asettbl[1];
extern aset_info z32asettbl[1];
extern aset_info z33asettbl[1];
extern aset_info z41asettbl[1];
extern aset_info z42asettbl[1];
extern aset_info z43asettbl[1];
extern aset_info z51asettbl[1];
extern aset_info z52asettbl[1];
extern aset_info z53asettbl[1];
extern aset_info z61asettbl[1];
extern aset_info z62asettbl[1];
extern aset_info z63asettbl[1];
extern aset_info z71asettbl[1];
extern aset_info z72asettbl[1];
extern aset_info z73asettbl[1];
extern aset_info z81asettbl[1];
extern aset_info z82asettbl[1];
extern aset_info z83asettbl[1];

unsigned char dummyarea[16] = {
  1, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0
};
aset_info* asettbl[7][3] = {
  { z11asettbl, z12asettbl, z13asettbl },
  { z31asettbl, z32asettbl, z33asettbl },
  { z41asettbl, z42asettbl, z43asettbl },
  { z51asettbl, z52asettbl, z53asettbl },
  { z61asettbl, z62asettbl, z63asettbl },
  { z71asettbl, z72asettbl, z73asettbl },
  { z81asettbl, z82asettbl, z83asettbl }
};
asetz_info asettblz[1] = { { 65535, 0, 0, 0 } };
