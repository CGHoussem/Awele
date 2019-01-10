#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"
#include "saves.h"

#define MAX_HOLES       12
#define DEFAULT_SEEDS   3

typedef enum {
    FALSE,
    TRUE
} BOOL;

/// Principle Functions
// Initialization Functions
Player initialize_player(char* pseudo);
Game initialize_game(char* pseudos[]);
Hole* initialize_board();
// Game Control Functions
int normalize_index(int index);
BOOL execute_move(int index, Game* game);

// Debug Functions
void debug_print_game(Game game);
void debug_print_board(Hole* board);
char* read_string();

int main()
{

    //Load previous saves

    Scores oldGames;
    load_scores(&oldGames);

    BOOL game_finished = FALSE;
    unsigned int hole = 0;
    //*** Comment either part 1 or 2 to start a new game or to load a save ***

    //**** PART 1 ****
    // Initialize Game
    //char* player_names[2];
     //printf("Player 1, Enter your name: ");
    // player_names[0] = read_string();
     //printf("Player 2, Enter your name: ");
    // player_names[1] = read_string();
    //
    // Game game = initialize_game(player_names);
    // save_game(game, "test2");
    //*****************

    //**** PART 2 ****
    Game game;
    load_game(&game, "saveGame");
    //*****************

    while (!game_finished){
        do {
            system("clear");
            printf("ENTER 99 TO SHOW GAME SUMMARY!\n");
            printf("ENTER 100 TO EXIT THE GAME!\n");
            printf("ENTER 200 TO SAVE THE GAME\n");
            printf("ENTER 250 TO LOAD A GAME\n\n");
            debug_print_board(game.board);

            printf("%s, it is your turn:\nPick a case to play: ", game.players[game.current_turn].pseudo);
            scanf("%d", &hole);

            switch (hole){
                case 99:
                    system("clear");
                    debug_print_game(game);
                    system("sleep 4");
                    break;
                case 100:
                    //**** PART 1 ****
                    //free(player_names[0]);
                    //free(player_names[1]);
                    //*****************
                    return 0;
                    break;
                case 200:
                    save_game(game, "saveGame");
                    printf("SAVE DONE !\n");
                    system("sleep 1");
                    break;
                case 250:
                    load_game(&game, "saveGame");
                    printf("LOAD DONE !\n");
                    system("sleep 2");
                    break;
                default: break;
            }
        } while (hole == 99 || hole == 200 || hole == 250 || !execute_move(hole, &game));
        debug_print_board(game.board);
    }
    printf("Game Summary\n");
    debug_print_game(game);

    //**** PART 1 ****
    // free(player_names[0]);
    // free(player_names[1]);
    //*****************
    return 0;
}

/// Principle Functions
Player initialize_player(char* pseudo)
{
    Player player;
    player.pseudo = pseudo;
    player.score = 0;
    return player;
}
Hole* initialize_board()
{
    Hole* board = (Hole*) malloc(sizeof(Hole) * MAX_HOLES);
    for (int i = 0; i < MAX_HOLES; i++)
    {
        Hole h;
        h.nb_seeds = DEFAULT_SEEDS;
        h.owner_id = (i < MAX_HOLES/2) ? 0 : 1;
        *(board+i) = h;
    }
    return board;
}
Game initialize_game(char* pseudos[])
{
    srand(time(0));
    Game game;
    game.gs = MENU;
    game.board = initialize_board();
    game.players[0] = initialize_player(pseudos[0]);
    game.players[1] = initialize_player(pseudos[1]);
    game.current_turn = rand() % 2;
    game.seeds_captured = 0;
    return game;
}
int normalize_index(int index)
{
    if (index >= MAX_HOLES){
        index -= MAX_HOLES;
        while (index > MAX_HOLES){
            index -= MAX_HOLES + 1;
        }
    }
    return index;
}
int hole_index_to_player_index(int hole_index)
{
    if (hole_index < 6)
        return 0;
    else
        return 1;
}
BOOL execute_move(int index, Game* game)
{
    // Checking if it's a valid move
    if ((game->current_turn == 0 && index < 6 && index >= 0) || (game->current_turn == 1 && index >= 6 && index < 12)){
        // Semaille
        int index_nb_seeds = (game->board+index)->nb_seeds;
        if (index_nb_seeds != 0)
        {
            printf("\n'Semaille' phase has begun...\n");
            printf("Take %d seeds\n", index_nb_seeds);
            (game->board+index)->nb_seeds = 0;
            for (int i=1; i <= index_nb_seeds; i++)
            {
                int x = (normalize_index(index + i));
                // Cas spécial
                if (index != x) {
                    (game->board+x)->nb_seeds++;
                    printf("** Put one in %d\n", x);
                } else {
                    index_nb_seeds++;
                }
            }
        } else {
            return FALSE;
        }
        printf("'Semaille' phase has been completed...\n\n");
        system("sleep 4");

        // Récolte
        int last_hole_index = normalize_index(index_nb_seeds+index);
        int last_hole_seeds_sum = (game->board+last_hole_index)->nb_seeds;

        if ((last_hole_seeds_sum == 2 || last_hole_seeds_sum == 3) && (hole_index_to_player_index(last_hole_index)) != game->current_turn)
        {
            printf("---> IL EXISTE DU RECOLTE\n");
            system("sleep 4");
            game->players[game->current_turn].score += last_hole_seeds_sum;
            (game->board+last_hole_index)->nb_seeds = 0;
            game->seeds_captured += last_hole_seeds_sum;
            printf("---> Win %d seeds\n", last_hole_seeds_sum);
            system("sleep 4");
        }
        // Change of players turn
        game->current_turn = (game->current_turn == 1) ? 0 : 1;
    } else {
        printf("Invalid move!!\n");
        system("sleep 2");
        return FALSE;
    }
    return TRUE;
}

/// Debug Functions
void debug_print_game(Game game)
{
    printf("Debug Print Game\n");
    printf("Players:\n");
    printf("Player 1: %s (%d)\n", game.players[0].pseudo, game.players[0].score);
    printf("Player 2: %s (%d)\n", game.players[1].pseudo, game.players[1].score);
    debug_print_board(game.board);
    printf("Player's Turn: %s\n", game.players[game.current_turn].pseudo);
    printf("Number of grains captured: %d\n", game.seeds_captured);
    printf("----------------------------\n");
}
void debug_print_board(Hole* board)
{
    printf("==================================================================================================================\n");
    printf("\t\tPLAYER 1\t\t\t\t|\t\tPLAYER 2\n");
    printf("==================================================================================================================\n");
    printf("index:\t");
    for (int i = 0; i < MAX_HOLES; i++)
    {
        if (i == MAX_HOLES/2)
            printf("|\t");
        printf("%d\t", i);
    }
    printf("\nseeds:\t");
    for (int i = 0; i < MAX_HOLES; i++)
    {
        Hole h = *(board+i);
        if (i == MAX_HOLES/2)
            printf("|\t");
        printf("%d\t", h.nb_seeds);
    }
    printf("\n==================================================================================================================\n\n");
}
char* read_string()
{
    unsigned int len_max = 16;
    unsigned int current_size = 16;
    char* ch = malloc(len_max);

    if (ch != NULL)
    {
        int c = EOF;
        unsigned int i = 0;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            ch[i++] =(char)c;

            if (i == current_size)
            {
                current_size = i + len_max;
                ch = realloc(ch, current_size);
            }
        }
        ch[i] = '\0';
    }

    return ch;
}
