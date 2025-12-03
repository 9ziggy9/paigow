#ifndef GAME_H_
#define GAME_H_

#include "tiles.h"
#include <stdbool.h>

typedef enum {
  CLASS_GENERIC, CLASS_GONG, CLASS_WONG, CLASS_PAIR
} HandClassification;

HandClassification GAME_classify_subhand(Subhand *);

#endif // GAME_H_
