#pragma once

#define MAX_HOLES       12
#define DEFAULT_SEEDS   3

typedef enum {
    //Had to change aliases because overwrited json.c alias

    FAL,
    TRU
}BOOL;

typedef struct{
    char* pseudo;
    int score;
    int isAI;
}Player;

typedef struct{
    int nb_seeds;
    int owner_id;
}Hole;



typedef struct{
    Hole* board;
    Player players[2];
    int current_turn;
    int seeds_captured;
    int turns_without_capture;
}Game;


Player initialize_player(char* pseudo);
Hole* initialize_board();
Game initialize_game(char * pseudo1, char * pseudo2);
int normalize_index(int index);
int hole_index_to_player_index(int hole_index);
BOOL execute_move(int index, Game* game);
int test_end_game(Game game);
