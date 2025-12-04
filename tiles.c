#include "tiles.h"

void TILES_print_deck(const Deck *d) {
  for (size_t hand_idx = 0; hand_idx < 8; hand_idx++) {
    for (size_t nth_tile = 0; nth_tile < 4; nth_tile++) {
      printf("%x ", (d->hands[hand_idx] >> SHIFT_TO_NTH_TILE(nth_tile)) & 0xF);
    }
    if (hand_idx % 2 || hand_idx == 7) printf("\n");
  }
}

Hand TILES_presort_hand(const Hand *h) {
  Tile tiles[4] = {
    (*h >> 12) & 0xF,
    (*h >> 8)  & 0xF,
    (*h >> 4)  & 0xF,
    (*h >> 0)  & 0xF
  };
  
  // bubble sort (only 4 elements, very fast)
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3 - i; j++) {
      if (tiles[j] < tiles[j + 1]) {
        Tile temp = tiles[j];
        tiles[j] = tiles[j + 1];
        tiles[j + 1] = temp;
      }
    }
  }

  return (Hand)((tiles[0] << 12) | (tiles[1] << 8) |
                (tiles[2] << 4)  | tiles[3]);
}

Hand TILES_hand_from_tiles(Tile t1, Tile t2, Tile t3, Tile t4) {
  return ((t1 << 12) & 0xF000)
    | ((t2 << 8) & 0x0F00)
    | ((t3 << 4) & 0x00F0)
    | ((t4 << 0) & 0x000F);
}

Tile TILES_copy_nth(const Deck *d, size_t n) {
  assert(n < NUM_TILES);
  return (Tile) (d->hands[GET_HAND_NUMBER(n)] >> SHIFT_TO_NTH_TILE(n)) & 0xF;
}

Deck TILES_paste_at(const Deck *d, size_t n, Tile tl) {
  assert(n < NUM_TILES);
  Deck new_deck = *d;
  uint16_t shift = SHIFT_TO_NTH_TILE(n);
  new_deck.hands[GET_HAND_NUMBER(n)] &= (Hand) ~(0xF << shift);
  new_deck.hands[GET_HAND_NUMBER(n)] |= (Hand) ((uint16_t) tl << shift);
  return new_deck;
}

Deck TILES_shuffle(const Deck *d) {
  Deck tmp_deck = *d;
  for (size_t n = NUM_TILES - 1; n > 0; n--) {
    size_t rand_pos = RANDOM_TILE_POS_BELOW(n);
    Tile curr_tl = TILES_copy_nth(&tmp_deck, n);
    Tile rand_tl = TILES_copy_nth(&tmp_deck, rand_pos);
    tmp_deck = TILES_paste_at(&tmp_deck, n, rand_tl);
    tmp_deck = TILES_paste_at(&tmp_deck, rand_pos, curr_tl);
  }
  return tmp_deck;
}

Deck TILES_generate_ordered_deck(void) {
  return (Deck) {
    .hands = {0xFFEE, 0xDDCC, 0xBBAA, 0x9988, 0x7766, 0x5544, 0x3322, 0x1100}
  };
}
