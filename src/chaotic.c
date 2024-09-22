#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "strategy.h"

static int strategy(const mancala_t *game, player_t player)
{
    assert(player == get_active_player(game));
    int pocket = 0;
    do {
        pocket = rand() % NUM_POCKETS_PER_PLAYER;
    } while (!get_pocket(game, player, pocket));
    return pocket;
}

strategy_t chaotic = &strategy;
