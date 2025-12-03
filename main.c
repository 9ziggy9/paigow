#include "tiles.h"
#include "analysis.h"

int main(void) {
  srand((unsigned int)time(NULL));

  Hand h = 0xAF2F;

  HandInfo info = ANALYSIS_init(h);
  info = ANALYSIS_hand(&info);
  ANALYSIS_print_info(&info);

  return 0;
}
