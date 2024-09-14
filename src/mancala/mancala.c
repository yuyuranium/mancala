#include <assert.h>
#include <mancala.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mancala {
    player_t active_player;
    char *player_name[2];

    // The game board
    const int num_holes;
    int *const holes;
    int *const pocket[2];  // Pointer to player's first pocket
    int *const store[2];   // Pointer to player's store

    int round;
    int end_of_game;
    player_t winner;
};

static int check_end_of_game(mancala_t *game)
{
    int pockets_a = get_all_pockets(game, A);
    int pockets_b = get_all_pockets(game, B);
    if (pockets_a && pockets_b) {  // Both players still have stones left
        return 0;
    }

    // Move all stones to store
    *game->store[A] += pockets_a;
    *game->store[B] += pockets_b;

    // Clear pockets
    for (int i = 0; i < NUM_POCKETS_PER_PLAYER; ++i) {
        game->pocket[A][i] = 0;
        game->pocket[B][i] = 0;
    }

    // Check winner
    if (*game->store[A] > *game->store[B]) {
        game->winner = A;
    } else if (*game->store[A] < *game->store[B]) {
        game->winner = B;
    }
    game->end_of_game = 1;
    return 1;
}

mancala_t *new_game(const char *player_name_a, const char *player_name_b)
{
    mancala_t init = {
        .player_name[A] = player_name_a ? strdup(player_name_a) : NULL,
        .player_name[B] = player_name_b ? strdup(player_name_b) : NULL,

        // Allocate memory for holes
        .num_holes = NUM_POCKETS_PER_PLAYER * 2 + 2,
        .holes = malloc(init.num_holes * sizeof(int)),

        // Set pointer to players pocket
        .pocket[A] = init.holes,
        .pocket[B] = &init.holes[NUM_POCKETS_PER_PLAYER + 1],

        // Set pointer to players store
        .store[A] = &init.holes[NUM_POCKETS_PER_PLAYER],
        .store[B] = &init.holes[init.num_holes - 1]};
    reset_game(&init);

    // Move initialized game struct to the allocated game pointer
    mancala_t *game = malloc(sizeof(mancala_t));
    memcpy(game, &init, sizeof(mancala_t));

    return game;
}

int reset_game(mancala_t *game)
{
    if (!game)
        return -1;

    // Initialize the pocket and the active player
    game->active_player = A;
    for (player_t p = A; p <= B; ++p) {
        *game->store[p] = 0;
        for (int i = 0; i < NUM_POCKETS_PER_PLAYER; ++i) {
            game->pocket[p][i] = INITIAL_STONES_PER_POCKET;
        }
    }

    game->round = 0;
    game->end_of_game = 0;
    game->winner = -1;

    return 0;
}

int delete_game(mancala_t *game)
{
    if (!game)
        return -1;

    if (game->player_name[A])
        free(game->player_name[A]);
    if (game->player_name[B])
        free(game->player_name[B]);

    game->player_name[A] = 0;
    game->player_name[B] = 0;

    free(game->holes);
    free(game);
    return 0;
}

mancala_t *duplicate_game(const mancala_t *src)
{
    mancala_t *game = new_game(NULL, NULL);
    save_game(game, src);
    return game;
}

int save_game(mancala_t *dst, const mancala_t *src)
{
    if (!dst || !src)
        return -1;

    dst->active_player = src->active_player;
    for (int i = 0; i < 2; ++i) {
        // Clear dst's player name
        if (dst->player_name[i]) {
            free(dst->player_name[i]);
            dst->player_name[i] = 0;
        }

        // Copy player name if exists
        if (src->player_name[i]) {
            dst->player_name[i] = strdup(src->player_name[i]);
        }
    }

    // Must be properly initialized
    assert(dst->num_holes == NUM_POCKETS_PER_PLAYER * 2 + 2);
    assert(dst->holes);
    assert(dst->pocket[0] && dst->pocket[1]);
    assert(dst->store[0] && dst->store[1]);

    // Copy all stones in holes
    memcpy(dst->holes, src->holes, dst->num_holes * sizeof(int));

    // Copy game status
    dst->round = src->round;
    dst->end_of_game = src->end_of_game;
    dst->winner = src->winner;

    return 0;
}

player_t get_active_player(const mancala_t *mancala)
{
    return mancala->active_player;
}

int get_all_pockets(const mancala_t *game, player_t player)
{
    int sum = 0;
    for (int i = 0; i < NUM_POCKETS_PER_PLAYER; ++i) {
        sum += game->pocket[player][i];
    }
    return sum;
}

int get_pocket(const mancala_t *game, player_t player, int pocket)
{
    if (pocket >= NUM_POCKETS_PER_PLAYER)
        return -1;
    return game->pocket[player][pocket];
}

int get_store(const mancala_t *game, player_t player)
{
    return *game->store[player];
}

int get_round(const mancala_t *game)
{
    return game->round;
}

int end_of_game(const mancala_t *game)
{
    return game->end_of_game;
}

player_t get_winner(const mancala_t *game)
{
    return game->winner;
}

status_t make_move(mancala_t *game, int pocket)
{
    if (pocket >= NUM_POCKETS_PER_PLAYER)
        return ERROR_POCKET_OUT_OF_BOUND;

    player_t active_player = game->active_player;
    player_t opponent = !active_player;
    int *start_pocket = &game->pocket[active_player][pocket];
    int num_stones = *start_pocket;
    if (!num_stones)
        return ERROR_POCKET_IS_EMPTY;

    // Simulate the process of a round
    game->round++;

    // 1. Grab all stones from the pocket
    *start_pocket = 0;

    // 2. Sow the stones to the holes CCW
    int index = start_pocket - game->holes;
    while (num_stones) {
        // Skip opponent's store or not
        index += &game->holes[index] == game->store[opponent] ? 2 : 1;
        index %= game->num_holes;
        num_stones--;
        game->holes[index] += 1;
    }

    // 3. Game may end after the move
    if (check_end_of_game(game))
        return OK;

    // 4. If the player's last stone is sowed in their store, they get a free
    //    turn
    if (&game->holes[index] == game->store[active_player])
        return OK;  // Do not toggle game->active_player

    // 5. If the player's last stone is sowed in their empty pocket, then they
    //    can capture all of the opponent's stones in the opposite hole
    player_t onwer_of_last_pocket = &game->holes[index] > game->store[A];
    if (game->holes[index] == 1 && active_player == onwer_of_last_pocket) {
        int pocket_index = index % (NUM_POCKETS_PER_PLAYER + 1);
        int *opposite_hole =
            &game->pocket[opponent][NUM_POCKETS_PER_PLAYER - pocket_index - 1];

        // Capture all stones in opposite hole and the last one sowed
        *game->store[active_player] += *opposite_hole + game->holes[index];

        // Clear both captured holes
        game->holes[index] = 0;
        *opposite_hole = 0;
    }

    // 6. Game may end after opponent's stones are captured
    if (check_end_of_game(game))
        return OK;

    // Otherwise, it's opponent's turn
    game->active_player ^= 1;
    return OK;
}

void print_game(const mancala_t *game)
{
#define DUP(n, ...)                   \
    do {                              \
        for (int i = 0; i < n; ++i) { \
            printf(__VA_ARGS__);      \
        }                             \
    } while (0)

    char *player_name[2] = {
        game->player_name[A] ? game->player_name[A] : "A",
        game->player_name[B] ? game->player_name[B] : "B",
    };

    if (game->end_of_game) {
        if (game->winner != -1) {
            printf("%s wins the game\n", player_name[game->winner]);
        } else {
            printf("Game ties\n");
        }
    } else {
        printf("%s's turn\n", player_name[game->active_player]);
    }

    // First line: Player A's pockets
    DUP(strlen(player_name[A]), " ");
    printf(" ┌───┐ ");
    DUP(NUM_POCKETS_PER_PLAYER, "(%3d) ",
        game->pocket[A][NUM_POCKETS_PER_PLAYER - i - 1]);
    printf("┌───┐ ");
    printf("\n");

    // Second line: Stores
    printf("%s │%3d│ ", player_name[A], *game->store[A]);
    DUP(NUM_POCKETS_PER_PLAYER, "      ");
    printf("│%3d│ %s", *game->store[B], player_name[B]);
    printf("\n");

    // First line: Player B's pockets
    DUP(strlen(player_name[A]), " ");
    printf(" └───┘ ");
    DUP(NUM_POCKETS_PER_PLAYER, "(%3d) ", game->pocket[B][i]);
    printf("└───┘ ");
    printf("\n");
#undef DUP
}
