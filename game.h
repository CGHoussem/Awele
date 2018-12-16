#pragma once

typedef struct{
    char* pseudo;
    int score;
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
}Game;
