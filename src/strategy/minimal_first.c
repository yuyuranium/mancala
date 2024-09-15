#include <assert.h>
#include <strategy.h>

static int eval(const mancala_t *game, player_t player)
{
    assert(player == get_active_player(game));
    int pocket = 0;
    int min_stones = NUM_POCKETS_PER_PLAYER * INITIAL_STONES_PER_POCKET * 2;
    for (int i = 0; i < NUM_POCKETS_PER_PLAYER; ++i) {
        int stones = 0;
        if ((stones = get_pocket(game, player, i)) && stones < min_stones) {
            min_stones = stones;
            pocket = i;
        }
    }
    return pocket;
}

static const strategy_t strategy = {.name = "minimal_first", .eval = &eval};

const strategy_t *minimal_first()
{
    return &strategy;
}
