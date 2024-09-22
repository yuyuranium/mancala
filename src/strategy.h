#pragma once

#include <stdlib.h>
#include <string.h>

#include "mancala.h"

typedef int (*strategy_t)(const mancala_t *, player_t);

#define STRATEGY(s) extern strategy_t s;
#include "strategies.inc"
#undef STRATEGY

#define STRATEGY(s) #s,
const static char *strategy_names[] = {
#include "strategies.inc"
};
#undef STRATEGY

#define STRATEGY(s) &s,
static strategy_t *strategies[] = {
#include "strategies.inc"
};
#undef STRATEGY

const static size_t num_strategies = sizeof(strategies) / sizeof(strategy_t *);

strategy_t get_strategy_by_name(const char *name);
