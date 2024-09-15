#pragma once

#include <mancala.h>

typedef struct {
    const char *name;
    int (*const eval)(const mancala_t *, player_t);
} strategy_t;

// Strategy factories
const strategy_t *chaotic();
const strategy_t *maximal_first();
const strategy_t *minimal_first();
