#include "tiles.h"
#include "analysis.h"
#include "game.h"

int main(void) {
  srand((unsigned int)time(NULL));

  Hand h = TILES_hand_from_tiles(TL_DAY, TL_YUN, TL_TEEN, TL_CHOPGOW);

  HandInfo info = ANALYSIS_init(h);
  info = ANALYSIS_hand(&info);
  ANALYSIS_print_info(&info);

  uint8_t score1 = GAME_score_subhand(&h, LOW_HAND);
  uint8_t score2 = GAME_score_subhand(&h, HIGH_HAND);

  printf("Low hand score: %d\n", score1);
  printf("High hand score: %d\n", score2);

  return 0;
}
