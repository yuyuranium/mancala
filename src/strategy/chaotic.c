#include <assert.h>
#include <stdlib.h>
#include <strategy.h>
#include <time.h>

static int eval(const mancala_t *game, player_t player)
{
    assert(player == get_active_player(game));
    int pocket = 0;
    do {
        pocket = rand() % NUM_POCKETS_PER_PLAYER;
    } while (!get_pocket(game, player, pocket));
    return pocket;
}

static const strategy_t strategy = {.name = "chaotic", .eval = &eval};

const strategy_t *chaotic()
{
    srand(time(NULL));
    return &strategy;
}
