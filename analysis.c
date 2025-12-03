#include "analysis.h"
#include "tiles.h"

#define STR_FROM_BOOL(b) (b == true ? "true" : "false")

void ANALYSIS_print_info(const HandInfo *h) {
  printf("Hand info:\n{\n");
  printf("\t .raw: 0x%04x\n", h->raw);
  printf("\t .num_pairs: %d\n", h->num_pairs);
  printf("\t .has_teen: %s\n", STR_FROM_BOOL(h->has_teen));
  printf("\t .has_day: %s\n",  STR_FROM_BOOL(h->has_day));

  printf("\t .paired_tiles: {");
  for (int n = 0; n < h->num_pairs; n++) printf(" %x", h->paired_tiles[n]);
  printf(" }\n");

  printf("\t .tiles: {");
  for (int n = 0; n < 4; n++) printf(" %x", h->tiles[n]);
  printf(" }\n");

  printf("}\n");
}

HandInfo ANALYSIS_init(const Hand h) {
  Hand sh = TILES_presort_hand(&h);
  return (HandInfo) {
    .raw = sh,
    .num_pairs = 0, .has_day = false, .has_teen = false,
    .paired_tiles = {},
    .tiles = {
      (sh >> 12) & 0xF,
      (sh >> 8)  & 0xF,
      (sh >> 4)  & 0xF,
      (sh >> 0)  & 0xF,
    },
  };
}

HandInfo analyze_pairs(const HandInfo *info) {
  HandInfo updated_info = *info;
  for (int shift = 12; shift > 0; shift -= 4) {
    Tile curr = (info->raw >> shift) & 0xF;
    if (curr == ((info->raw >> (shift - 4)) & 0xF)) {
      updated_info.paired_tiles[info->num_pairs] = curr;
      updated_info.num_pairs++;
    }
  }
  return updated_info;
}

HandInfo analyze_teen_day(const HandInfo *info, Tile teen_or_day) {
  HandInfo updated_info = *info;
  for (int shift = 12; shift > 0; shift -= 4) {
    Tile curr = (info->raw >> shift) & 0xF;
    if (curr == teen_or_day) {
      switch (teen_or_day) {
      case TL_TEEN: updated_info.has_teen = true; break;
      case TL_DAY:  updated_info.has_day  = true; break;
      default: exit(1); break;
      }
    }
  }
  return updated_info;
}

HandInfo ANALYSIS_hand(const HandInfo *info) {
  printf("Analyzing hand for pairs ... \n");
  HandInfo updated_info = analyze_pairs(info);
  printf("Analyzing hand for teen and day ... \n");
  updated_info = analyze_teen_day(&updated_info, TL_TEEN);
  updated_info = analyze_teen_day(&updated_info, TL_DAY);
  return updated_info;
}
