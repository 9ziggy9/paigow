#include "tiles.h"

int main(void) {
  srand((unsigned int)time(NULL));

  printf("\nPreshuffle:\n");
  const Deck ordered_deck = TILES_generate_ordered_deck();
  TILES_print_deck(&ordered_deck);

  printf("\nPostshuffle:\n");
  const Deck shuffled_deck = TILES_shuffle(&ordered_deck);
  TILES_print_deck(&shuffled_deck);

  return 0;
}
