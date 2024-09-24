#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "mancala.h"
#include "strategy.h"

static int manual(const mancala_t *game, player_t player)
{
    assert(player == get_active_player(game));
    int pocket = -1;
    char *line = NULL;
    size_t line_len = 0;
    while (1) {
        printf("> ");
        if (getline(&line, &line_len, stdin) < 0) {
            continue;
        }
        pocket = strtol(line, NULL, 0);

        if (pocket < 0 || pocket >= NUM_POCKETS_PER_PLAYER) {
            printf("Pocket index out of bound\n");
            continue;
        }

        if (!get_pocket(game, player, pocket)) {
            printf("Cannot select an empty pocket\n");
            continue;
        }
        break;
    }
    free(line);
    return pocket;
}

static void usage(const char *prog)
{
    printf("Usage:\n");
    printf("\t%s [-h|-q] [strategy1] [strategy2]\n\n", prog);
    printf("Arguments:\n");
    printf("\tstrategy[1,2]\t{ ");
    for (size_t i = 0; i < num_strategies - 1; ++i) {
        printf("%s, ", strategy_names[i]);
    }
    printf("%s }\n\n", strategy_names[num_strategies - 1]);

    printf("Flags:\n");
    printf("\t-h, --help\tPrint this help message.\n");
    printf("\t-q, --quiet\tQuiet mode.\n");
}

int main(int argc, char *argv[])
{
    srand(time(NULL) ^ getpid());
    int quiet = 0;
    int num_players = 0;
    struct {
        strategy_t strategy;
        const char *name;
    } player[2];

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        const char *curr = argv[i];
        if (curr[0] == '-') {  // argument is a flag
            const char *rem = &curr[1];
            if (strcmp(rem, "h") == 0 || strcmp(rem, "-help") == 0) {
                usage(argv[0]);
                return 0;
            } else if (strcmp(rem, "q") == 0 || strcmp(rem, "-quiet") == 0) {
                quiet = 1;
            } else {
                printf("Unknown argument: %s\n", curr);
                usage(argv[0]);
                return 1;
            }
            continue;
        }

        if (num_players < 2) {
            strategy_t s = get_strategy_by_name(curr);
            player[num_players].strategy = s ? s : &manual;
            player[num_players].name = curr;
            ++num_players;
        } else {
            printf("Too many players\n");
            usage(argv[0]);
            return 1;
        }
    }

    if (num_players == 0) {
        // No player is specified; randomly choose 2 to match
        while (num_players < 2) {
            const char *name = strategy_names[rand() % 3];
            player[num_players].strategy = get_strategy_by_name(name);
            player[num_players].name = name;
            ++num_players;
        }
    } else if (num_players == 1) {
        // Only one player is specified; the other is the user
        player[num_players].strategy = manual;
        player[num_players].name = "(You)";
        ++num_players;
    }

    assert(num_players == 2);

    printf("# %s vs. %s\n\n", player[0].name, player[1].name);

    status_t status = OK;
    mancala_t *game = new_game(player[0].name, player[1].name);

    while (status == OK && !end_of_game(game)) {
        if (!quiet) {
            printf("[Round %d]\n", get_round(game));
            print_game(game);
        }

        player_t active = get_active_player(game);
        int pocket = (*player[active].strategy)(game, active);

        if (!quiet) {
            printf("\n>>> %s selects %d\n", player[active].name, pocket);
            puts("\n");
        }
        status = make_move(game, pocket);
    }

    puts("[Result]");
    if (status < 0) {
        player_t p = get_active_player(game);
        printf(">>> Invalid move by %s\n", player[p].name);
        return 0;
    }

    print_game(game);
    int winner = get_winner(game);
    if (winner == -1) {
        puts("\n>>> Draw game");
    } else {
        printf("\n>>> The winner is %s\n", player[winner].name);
    }

    return 0;
}
