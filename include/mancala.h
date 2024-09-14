#pragma once

typedef enum player {
    A = 0,
    B = 1,
} player_t;

typedef enum status {
    ERROR_POCKET_IS_EMPTY = -2,
    ERROR_POCKET_OUT_OF_BOUND = -1,
    OK = 0,
} status_t;

typedef struct mancala mancala_t;

static const int NUM_POCKETS_PER_PLAYER = 6;
static const int INITIAL_STONES_PER_POCKET = 4;

// New and delete a game
mancala_t *new_game(const char *, const char *);
int reset_game(mancala_t *);
int delete_game(mancala_t *);

// Duplicate or save a game
mancala_t *duplicate_game(const mancala_t *);
int save_game(mancala_t *, const mancala_t *);

// Get current game status
player_t get_active_player(const mancala_t *);
int get_all_pockets(const mancala_t *, player_t);
int get_pocket(const mancala_t *, player_t, int);
int get_store(const mancala_t *, player_t);
int get_round(const mancala_t *);
int end_of_game(const mancala_t *);
player_t get_winner(const mancala_t *);

// Play
status_t make_move(mancala_t *, int);

// Print the game to stdout
void print_game(const mancala_t *);
