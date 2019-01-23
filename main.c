#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"
#include "saves.h"
#include "ai.h"


// Debug Functions
void debug_print_game(Game game);
void debug_print_board(Hole* board);
char* read_string();

int main()
{


    //Load previous saves

    Scores oldGames;
    load_scores(&oldGames);

    BOOL game_finished = FAL;
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
            //system("clear");
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
            //Replace execute move by ai_turn(&game) to test AI
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
