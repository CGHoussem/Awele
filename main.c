#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HOLES       12
#define DEFAULT_SEEDS   3

typedef enum {
    FALSE,
    TRUE
} BOOL;


typedef struct {
    char* pseudo;
    int score;
} Player;

typedef struct {
    int nb_seeds;
    int owner_id;
} Hole;

typedef struct {
    Hole* board;
    Player players[2];
    int current_turn;
    int seeds_captured;
} Game;


/// Principle Functions
// Initialization Functions
Player initialize_player(char* pseudo);
Game initialize_game(char* p1_pseudo, char* p2_pseudo);
Hole* initialize_board();
// Game Control Functions
int normalize_index(int index);
BOOL execute_move(int index, Game* game);

// Debug Functions
void debug_print_game(Game game);
void debug_print_board(Hole* board);

int main()
{
    int hole = 0;
    BOOL game_finished = FALSE;

    // Initialize Game
    Game game = initialize_game("Nom du joueur 1", "Nom du joueur 2");

    while (!game_finished){
        do {
            system("cls");
            printf("ENTER 69 TO SHOW GAME SUMMARY!\n\n");
            debug_print_board(game.board);
            if (game.current_turn == 0)
                printf("Player 1, it is your turn:\nPick a case to play: ");
            else
                printf("Player 2, it is your turn:\nPick a case to play: ");
            scanf("%d", &hole);
            if (hole == 69){
                system("cls");
                debug_print_game(game);
                system("pause");
            }
        } while (hole == 69 || !execute_move(hole, &game));
        debug_print_board(game.board);
    }
    printf("Game Summary\n");
    debug_print_game(game);
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
    Hole* board = malloc(sizeof(Hole) * MAX_HOLES);
    for (int i = 0; i < MAX_HOLES; i++)
    {
        Hole h;
        h.nb_seeds = DEFAULT_SEEDS;
        h.owner_id = (i < MAX_HOLES/2) ? 0 : 1;
        *(board+i) = h;
    }
    return board;
}
Game initialize_game(char* p1_pseudo, char* p2_pseudo)
{
    srand(time(0));
    Game game;
    game.board = initialize_board();
    game.players[0] = initialize_player(p1_pseudo);
    game.players[1] = initialize_player(p2_pseudo);
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
                (game->board+x)->nb_seeds++;
                printf("** Put one in %d\n", x);
            }
        } else {
            return FALSE;
        }
        printf("'Semaille' phase has been completed...\n\n");
        system("pause");

        // Récolte
        int last_hole_index = normalize_index(index_nb_seeds+index);
        int last_hole_seeds_sum = (game->board+last_hole_index)->nb_seeds;

        if ((last_hole_seeds_sum == 2 || last_hole_seeds_sum == 3) && (hole_index_to_player_index(last_hole_index)) != game->current_turn)
        {
            printf("---> IL EXISTE DU RECOLTE\n");
            system("pause");
            game->players[game->current_turn].score += last_hole_seeds_sum;
            (game->board+last_hole_index)->nb_seeds = 0;
            game->seeds_captured += last_hole_seeds_sum;
            printf("---> Win %d seeds\n", last_hole_seeds_sum);
            system("pause");
        }
        // Change of players turn
        game->current_turn = (game->current_turn == 1) ? 0 : 1;
    } else {
        printf("Invalid move!!\n");
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
    printf("==================================================================================================================\n");
    printf("index:\t");
    for (int i = 0; i < MAX_HOLES; i++)
    {
        if (i == MAX_HOLES/2)
            printf("|\t");
        printf("%d\t", i);
    }
    printf("\nhole:\t");
    for (int i = 0; i < MAX_HOLES; i++)
    {
        Hole h = *(game.board+i);
        if (i == MAX_HOLES/2)
            printf("|\t");
        printf("%d\t", h.nb_seeds);
    }
    printf("\n==================================================================================================================\n\n");
    printf("Player's Turn: %d\n", game.current_turn);
    printf("Number of grains captured: %d\n", game.seeds_captured);
    printf("----------------------------\n");
}
void debug_print_board(Hole* board)
{
    printf("==================================================================================================================\n");
    printf("index:\t");
    for (int i = 0; i < MAX_HOLES; i++)
    {
        if (i == MAX_HOLES/2)
            printf("|\t");
        printf("%d\t", i);
    }
    printf("\nhole:\t");
    for (int i = 0; i < MAX_HOLES; i++)
    {
        Hole h = *(board+i);
        if (i == MAX_HOLES/2)
            printf("|\t");
        printf("%d\t", h.nb_seeds);
    }
    printf("\n==================================================================================================================\n\n");
}
