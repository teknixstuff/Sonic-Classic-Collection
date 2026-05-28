#include "../TYPES.h"

extern sprite_pattern* z82_pat_kuzure_a[];
extern sprite_pattern* z82koma8pat[];
extern sprite_pattern* z82_pat_et[];

edit_data z82_edit_tbl = {
  10,
  0,
  {
    { 37, 3, z82_pat_kuzure_a, 17624, 1, 0, 0, 0 },
    { 37, 3, z82_pat_kuzure_a, 17624, 2, 0, 0, 1 },
    { 37, 3, z82_pat_kuzure_a, 17624, 3, 0, 0, 2 },
    { 37, 3, z82_pat_kuzure_a, 17624, 4, 0, 0, 3 },
    { 37, 3, z82_pat_kuzure_a, 17624, 5, 0, 0, 4 },
    { 37, 3, z82_pat_kuzure_a, 17624, 6, 0, 0, 5 },
    { 37, 3, z82_pat_kuzure_a, 17624, 7, 0, 0, 6 },
    { 37, 3, z82_pat_kuzure_a, 17624, 8, 0, 0, 7 },
    { 15, 4, z82koma8pat,      1258 },
    { 67, 1, z82_pat_et,        768 }
  }
};
