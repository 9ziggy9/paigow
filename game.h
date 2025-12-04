#ifndef GAME_H_
#define GAME_H_

#include "tiles.h"
#include "analysis.h"
#include <stdbool.h>

typedef enum { LOW_HAND, HIGH_HAND } SubhandVariant;

uint8_t GAME_score_subhand(const Hand *, SubhandVariant);

#endif // GAME_H_
