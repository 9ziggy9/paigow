#include <assert.h>
#include <stdio.h>
#include <stdint.h>

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
    .hands = {0x00FF, 0xEEDD, 0xCCBB, 0xAA99, 0x8877, 0x6655, 0x4433, 0x2211}
  };
}

void print_deck_levels(const Deck *d) {
  for (size_t hand = 0; hand < 8; hand++) {
    printf("Hand at %zu: 0x%04x\n", hand, d->hands[hand]);
    for (size_t sh = 0; sh < 2; sh++) {
      printf("\tSubhand at %zu: ", hand);
      printf("0x%02x \n", (d->hands[hand] >> (sh * 8) & 0xFF));
      printf("\t\tTiles: ");
      for (size_t tl = 0; tl < 2; tl++)
        printf("%x ", ((d->hands[hand] >> (sh * 8) & 0xFF) >> (tl * 4)) & 0xF);
      printf("\n");
    }
  }
}

int main(void) {
  const Deck ordered = generate_ordered_deck();
  print_deck_levels(&ordered);
  return 0;
}
