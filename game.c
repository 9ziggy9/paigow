#include "game.h"
#include "tiles.h"

uint8_t tile_to_points(Tile t) {
  switch (t) {
  case TL_GEEJUN:   return 6;
  case TL_CHOPNG:   return 5;
  case TL_CHOPCHIT: return 7;
  case TL_CHOPBOT:  return 8;
  case TL_CHOPGOW:  return 9;
  case TL_LOOK:     return 6;
  case TL_CHIT:     return 7;
  case TL_PING:     return 10;
  case TL_FOO:      return 11;
  case TL_BON:      return 4;
  case TL_CHONG:    return 6;
  case TL_MOOY:     return 10;
  case TL_GOR:      return 4;
  case TL_YUN:      return 8;
  case TL_DAY:      return 2;
  case TL_TEEN:     return 12;
  }
  return 0;
}

uint8_t GAME_score_subhand(const Hand *h, SubhandVariant v) {
  Tile t1, t2;
  switch (v) {
  case LOW_HAND:
    t1 = (*h >> SHIFT_TO_NTH_TILE(0)) & 0xF;
    t2 = (*h >> SHIFT_TO_NTH_TILE(1)) & 0xF;
    break;
  case HIGH_HAND:
    t1 = (*h >> SHIFT_TO_NTH_TILE(2)) & 0xF;
    t2 = (*h >> SHIFT_TO_NTH_TILE(3)) & 0xF;
    break;
  default: exit(1);
  }
  if ((t1 == TL_TEEN || t1 == TL_DAY) && (tile_to_points(t2) == 9))
    return 11;
  if ((t1 == TL_TEEN || t1 == TL_DAY) && (tile_to_points(t2) == 8))
    return 10;
  return (uint8_t) (tile_to_points(t1) + tile_to_points(t2)) % 10;
}
