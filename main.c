#include "tiles.h"
#include "analysis.h"

int main(void) {
  srand((unsigned int)time(NULL));

  Hand h = 0xAF21;

  PairInfo pinfo = ANALYSIS_pairs(&h);

  ANALYSIS_print_pair_info(&pinfo);

  return 0;
}
