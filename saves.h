#pragma once

#include "game.h"
#include <unistd.h>

typedef struct{
    char * player1_name;
    int player1_score;

    char * player2_name;
    int player2_score;
}Score;

typedef struct{
    Score * scores;
    int length;
}Scores;


void save_game(Game game, char * save_name);
int load_game(Game * game, char * save_name);

void save_scores(Scores  scores);
void load_scores(Scores * scores);
