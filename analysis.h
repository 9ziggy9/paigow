#ifndef ANALYSIS_H_
#define ANALYSIS_H_

#include "tiles.h"
#include <stdint.h>

typedef struct {
  uint8_t num_pairs;
  Tile paired_tiles[2];
} PairInfo;

void ANALYSIS_print_pair_info(const PairInfo *);
PairInfo ANALYSIS_pairs(const Hand *);

#endif // ANALYSIS_H
