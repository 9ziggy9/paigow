#ifndef ANALYSIS_H_
#define ANALYSIS_H_

#include "tiles.h"
#include <stdint.h>

typedef struct {
  Hand raw;
  uint8_t num_pairs;
  bool has_teen;
  bool has_day;
  Tile paired_tiles[2];
  Tile tiles[4];
} HandInfo;

HandInfo ANALYSIS_init(Hand);
HandInfo ANALYSIS_hand(const HandInfo *);
void ANALYSIS_print_info(const HandInfo *);

#endif // ANALYSIS_H
