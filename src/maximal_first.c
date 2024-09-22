#include <assert.h>

#include "strategy.h"

static int strategy(const mancala_t *game, player_t player)
{
    assert(player == get_active_player(game));
    int pocket = 0;
    int max_stones = 0;
    for (int i = 0; i < NUM_POCKETS_PER_PLAYER; ++i) {
        int stones = 0;
        if ((stones = get_pocket(game, player, i)) > max_stones) {
            max_stones = stones;
            pocket = i;
        }
    }
    return pocket;
}

strategy_t maximal_first = &strategy;
