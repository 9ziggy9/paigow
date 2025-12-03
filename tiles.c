#include "tiles.h"

Deck generate_ordered_deck(void) {
  return (Deck) {
    .hands = {0xFFEE, 0xDDCC, 0xBBAA, 0x9988, 0x7766, 0x5544, 0x3322, 0x1100}
  };
}

void print_deck(const Deck *d) {
  for (size_t hand_idx = 0; hand_idx < 8; hand_idx++) {
    for (size_t nth_tile = 0; nth_tile < 4; nth_tile++) {
      printf("%x ", (d->hands[hand_idx] >> SHIFT_TO_NTH_TILE(nth_tile)) & 0xF);
    }
    if (hand_idx % 2 || hand_idx == 7) printf("\n");
  }
}

Tile copy_nth_tile(const Deck *d, size_t n) {
  assert(n < NUM_TILES);
  return (Tile) (d->hands[GET_HAND_NUMBER(n)] >> SHIFT_TO_NTH_TILE(n)) & 0xF;
}

Deck paste_tile_at(const Deck *d, size_t n, Tile tl) {
  assert(n < NUM_TILES);
  Deck new_deck = *d;
  uint16_t shift = SHIFT_TO_NTH_TILE(n);
  new_deck.hands[GET_HAND_NUMBER(n)] &= (Hand) ~(0xF << shift);
  new_deck.hands[GET_HAND_NUMBER(n)] |= (Hand) ((uint16_t) tl << shift);
  return new_deck;
}

Deck shuffle_fisher_yates(const Deck *d) {
  Deck tmp_deck = *d;
  for (size_t n = NUM_TILES - 1; n > 0; n--) {
    size_t rand_pos = RANDOM_TILE_POS_BELOW(n);
    Tile curr_tl = copy_nth_tile(&tmp_deck, n);
    Tile rand_tl = copy_nth_tile(&tmp_deck, rand_pos);
    tmp_deck = paste_tile_at(&tmp_deck, n, rand_tl);
    tmp_deck = paste_tile_at(&tmp_deck, rand_pos, curr_tl);
  }
  return tmp_deck;
}
