#include <mancala.h>
#include <stdio.h>
#include <stdlib.h>
#include <strategy.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    const strategy_t *strategies[3] = {chaotic(), maximal_first(),
                                       minimal_first()};

    const strategy_t *player[2] = {strategies[rand() % 3],
                                   strategies[rand() % 3]};

    printf("[%s vs. %s]\n\n", player[0]->name, player[1]->name);

    status_t status = OK;
    mancala_t *game = new_game(player[0]->name, player[1]->name);

    while (status == OK && !end_of_game(game)) {
        player_t p = get_active_player(game);

        int pocket = (*player[p]->eval)(game, p);
        printf("[Round %d]\n\n", get_round(game));
        print_game(game);
        printf("\n%s selects %d\n", player[p]->name, pocket);

        status = make_move(game, pocket);
        puts("\n");
    }

    if (status < 0) {
        return -1;
    }

    player_t winner = get_winner(game);
    if (winner == -1) {
        puts("Draw game");
    } else {
        printf("The winner is %s\n", player[winner]->name);
    }
    print_game(game);

    return 0;
}
