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

int main(void) {
  Subhand shand1 = MAKE_SUBHAND(TL_GEEJUN, TL_CHOPNG);
  Subhand shand2 = MAKE_SUBHAND(TL_TEEN, TL_DAY);
  printf("Subhands are: 0x%02x 0x%02x\n", shand1, shand2);

  Hand hand = MAKE_HAND(shand1, shand2);
  printf("Hand is: 0x%04x\n", hand);
  return 0;
}
