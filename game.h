#pragma once

typedef struct{
    char* pseudo;
    int score;
}Player;

typedef struct{
    int nb_seeds;
    int owner_id;
}Hole;

typedef enum{
	MENU, P1_INPUT, P2_INPUT, LOAD, SAVE, PVP, PVC
} GameState;

typedef struct{
	GameState gs;
    Hole* board;
    Player players[2];
    int current_turn;
    int seeds_captured;
}Game;
