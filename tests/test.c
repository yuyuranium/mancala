#include <mancala.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int round = 0;
    char *player_name[2] = {"jumha", "yuyu"};
    status_t status = OK;
    mancala_t *game = new_game(player_name[0], player_name[1]);

    while (status == OK && !end_of_game(game)) {
        int pocket = 0;
        player_t player = get_active_player(game);
        do {
            pocket = rand() % NUM_POCKETS_PER_PLAYER;
        } while (!get_pocket(game, player, pocket));
        status = make_move(game, pocket);

        printf("[Round %d] %s selects pocket %d\n", round++,
               player_name[player], pocket);
        print_game(game);
        puts("\n");
    }

    if (status < 0) {
        return -1;
    }

    player_t winner = get_winner(game);
    if (winner == -1) {
        puts("Draw game");
    } else {
        printf("The winner is %s\n", player_name[winner]);
    }

    return 0;
}
