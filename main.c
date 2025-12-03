#include "tiles.h"

int main(void) {
  srand((unsigned int)time(NULL));

  printf("\nPreshuffle:\n");
  const Deck ordered_deck = generate_ordered_deck();
  print_deck(&ordered_deck);

  printf("\nPostshuffle:\n");
  const Deck shuffled_deck = shuffle_fisher_yates(&ordered_deck);
  print_deck(&shuffled_deck);

  return 0;
}
