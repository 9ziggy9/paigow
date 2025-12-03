#include "analysis.h"
#include "tiles.h"

// NOTE: presorting is redundant if we presort our hand
// from the beginning.
void ANALYSIS_print_pair_info(const PairInfo *p) {
  printf("Pair info:\n{\n");
  printf("\t .num_pairs: %d\n", p->num_pairs);
  printf("\t .paired_tiles: {");
  for (int n = 0; n < p->num_pairs; n++) {
    printf(" %x", p->paired_tiles[n]);
  }
  printf(" }\n");
  printf("}\n");
  printf("Number of pairs: %d\n", p->num_pairs);
}

PairInfo ANALYSIS_pairs(const Hand *h) {
  Hand sh = TILES_presort_hand(h);
  printf("Sorted hand: 0x%04x\n", sh);
  PairInfo info = { .num_pairs = 0 };
  for (int shift = 12; shift > 0; shift -= 4) {
    Tile curr = (sh >> shift) & 0xF;
    if (curr == ((sh >> (shift - 4)) & 0xF)) {
      info.paired_tiles[info.num_pairs] = curr;
      info.num_pairs++;
    }
  }
  return info;
}
