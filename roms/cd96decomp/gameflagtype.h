#ifndef GAMEFLAGTYPE_H
#define GAMEFLAGTYPE_H

typedef enum gameflag_type {
  GAMEFLAG_NONE = 0,
  GAMEFLAG_RESTART = 1,
  GAMEFLAG_NEXT_STAGE = 2,
  GAMEFLAG_NEXT_TIME = 256
}
gameflag_type;

#endif
