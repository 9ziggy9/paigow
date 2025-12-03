#ifndef TILES_H_
#define TILES_H_

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_TILES 32
#define MAKE_SUBHAND(tl1, tl2) ((Subhand)(((tl1) << 4) | (tl2)))
#define MAKE_HAND(sh1, sh2) ((Hand)(((sh1) << 8) | (sh2)))
#define GET_HAND_NUMBER(N) (N / 4)
#define SHIFT_TO_NTH_TILE(N) ((3 - (N % 4)) * 4)
#define RANDOM_TILE_POS_BELOW(MAX) ((size_t) rand() % (MAX+1))

// Simple single nybble encoding from 0x0 to 0xF.
// Note order is taken for single tile rankings for comparison.
typedef enum {
  TL_GEEJUN, TL_CHOPNG, TL_CHOPCHIT, TL_CHOPBOT, TL_CHOPGOW,
  TL_LOOK, TL_CHIT, TL_PING, TL_FOO, TL_BON, TL_CHONG, TL_MOOY,
  TL_GOR, TL_YUN, TL_DAY, TL_TEEN,
} Tile;

// Two nibble (8-bit) subhands, to be utilized to make low/high hands.
typedef uint8_t Subhand;
// A full hand is 16 bits, for a total of 4 nybbles encoding 4 tiles.
typedef uint16_t Hand;
// A complete deck is 8 16 bit hands.
typedef struct { Hand hands[8]; } Deck;

Deck generate_ordered_deck(void);
void print_deck(const Deck *);
Tile copy_nth_tile(const Deck *, size_t);
Deck paste_tile_at(const Deck *, size_t, Tile);
Deck shuffle_fisher_yates(const Deck *);

#endif // TILES_H_
