#include "../TYPES.h"

extern sprite_pattern* z41bharir4pat[];
extern sprite_pattern* z41drenketu4pat[];
extern sprite_pattern* z41d_pat_tekkyu4[];
extern sprite_pattern* z41d_pat_screw0c[];
extern sprite_pattern* z41d_pat_screw1c[];
extern sprite_pattern* awapat[];
extern sprite_pattern* springpat[];
extern sprite_pattern* spring90pat[];
extern sprite_pattern* z41d_pat_wall1[];
extern sprite_pattern* z41d_pat_tonbo_e[];
extern sprite_pattern* z41d_pat_tonbo_b[];
extern sprite_pattern* z41c_pat_amenbo_e[];
extern sprite_pattern* z41c_pat_amenbo_b[];
extern sprite_pattern* z41c_pat_tagameb_e[];
extern sprite_pattern* z41c_pat_tagameb_b[];
extern sprite_pattern* z41c_pat_yago_e[];
extern sprite_pattern* z41c_pat_yago_b[];
extern sprite_pattern* z41c_pat_friend0[];
extern sprite_pattern* z41c_pat_friend1[];
extern sprite_pattern* itempat[];
extern sprite_pattern* boupat[];

edit_data z41c_edit_tbl = {
  25,
  0,
  {
    { 34, 1, z41bharir4pat,        928 },
    { 62, 1, z41drenketu4pat,    17216 },
    { 56, 1, z41d_pat_tekkyu4,     880 },
    { 53, 1, z41d_pat_screw0c,   17280, 128, 0, 0, 0 },
    { 53, 1, z41d_pat_screw0c,   17280, 129, 3, 0, 0 },
    { 53, 1, z41d_pat_screw1c,   17280, 130, 0, 0, 0 },
    { 53, 1, z41d_pat_screw1c,   17280, 131, 3, 0, 0 },
    { 32, 4, awapat,             33930, 130, 0, 0, 0 },
    { 10, 1, springpat,           1312 },
    { 10, 1, springpat,           1312, 0, 2, 0, 0 },
    { 10, 1, spring90pat,         1312, 4, 0, 0, 0 },
    { 10, 1, spring90pat,         1312, 4, 1, 0, 0 },
    { 52, 1, z41d_pat_wall1,     17514 },
    { 43, 1, z41d_pat_tonbo_e,    9238 },
    { 43, 1, z41d_pat_tonbo_b,    9238, 1, 0, 0, 0 },
    { 44, 1, z41c_pat_amenbo_e,   9136 },
    { 44, 1, z41c_pat_amenbo_b,   9136, 1, 0, 0, 0 },
    { 45, 1, z41c_pat_tagameb_e,  9168 },
    { 45, 1, z41c_pat_tagameb_b,  9168, 1, 0, 0, 0 },
    { 46, 1, z41c_pat_yago_e,     9200 },
    { 46, 1, z41c_pat_yago_b,     9200, 1, 0, 0, 0 },
    { 47, 1, z41c_pat_friend0,    9296 },
    { 47, 1, z41c_pat_friend1,    9296, 1, 0, 0, 1 },
    { 25, 4, itempat,             1448 },
    {  5, 4, boupat,               760 }
  }
};
