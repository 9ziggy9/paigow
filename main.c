#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define NUM_TILES 32

// Simple single nybble encoding from 0x0 to 0xF.
// Note order is taken for single tile rankings for comparison.
typedef enum {
  TL_GEEJUN, TL_CHOPNG, TL_CHOPCHIT, TL_CHOPBOT, TL_CHOPGOW,
  TL_LOOK, TL_CHIT, TL_PING, TL_FOO, TL_BON, TL_CHONG, TL_MOOY,
  TL_GOR, TL_YUN, TL_DAY, TL_TEEN,
} Tile;

// Two nibble (8-bit) subhands, to be utilized to make low/high hands.
typedef uint8_t Subhand;
#define MAKE_SUBHAND(tl1, tl2) ((Subhand)(((tl1) << 4) | (tl2)))

// A full hand is 16 bits, for a total of 4 nybbles encoding 4 tiles.
typedef uint16_t Hand;
#define MAKE_HAND(sh1, sh2) ((Hand)(((sh1) << 8) | (sh2)))

// A complete deck is 8 16 bit hands.
typedef struct { Hand hands[8]; } Deck;

Deck generate_ordered_deck(void) {
  return (Deck) {
    .hands = {0xFFEE, 0xDDCC, 0xBBAA, 0x9988, 0x7766, 0x5544, 0x3322, 0x1100}
  };
}

#define GET_HAND_NUMBER(N) (N / 4)
#define SHIFT_TO_NTH_TILE(N) ((3 - (N % 4)) * 4)

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

#define RANDOM_TILE_BELOW(MAX) ((size_t) rand() % (MAX+1))

int main(void) {
  srand((unsigned int)time(NULL));
  const Deck ordered_deck = generate_ordered_deck();
  Tile tl_teen = copy_nth_tile(&ordered_deck, 0);
  const Deck new_deck = paste_tile_at(&ordered_deck, 31, tl_teen);
  print_deck(&new_deck);
  while (1) {
    printf("%zu\n", RANDOM_TILE_BELOW(NUM_TILES));
  }
  return 0;
}
