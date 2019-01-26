#include "ai.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


void game_assignment(Game source, Game * dest){

    //WARNING Pseudos use the same memory emplacement as source Game

    dest->current_turn = source.current_turn;
    dest->seeds_captured = source.seeds_captured;

    dest->board = (Hole*) malloc(12 * sizeof(Hole));
    for(int i=0; i<12; i++){
        dest->board[i].nb_seeds = source.board[i].nb_seeds;
        dest->board[i].owner_id = source.board[i].owner_id;
    }

    for(int i=0; i<2; i++){
        dest->players[i].pseudo = source.players[i].pseudo;
        dest->players[i].score = source.players[i].score;
    }
}



void ai_turn(Game * game){

    //Assumes that the player is indeed AI
    //Verification must be done before calling

    srand(time(NULL));

    int minIndex;
    int maxIndex;

    if(game->current_turn == 0){
        minIndex = 0;
        maxIndex = 5;
    }
    else if(game->current_turn == 1){
        minIndex = 6;
        maxIndex = 11;
    }


    bool canPlay = 0;

    //Trying all moves on testing structure until scoring

    Game testGame;
    int i = minIndex;
    int previousScore = game->players[game->current_turn].score;
    while(i <= maxIndex){

        if(game->board[i].nb_seeds){
            canPlay = 1;
        }

        game_assignment(*game, &testGame);
        execute_move(i, &testGame);
        free(testGame.board);


        if(previousScore < testGame.players[testGame.current_turn].score){
            execute_move(i, game);
            break;
        }

        i++;
    }

    //If no way to score i found, pick random
    if(i > maxIndex){

        bool hasPlayed = false;
        int tileId = rand() %6;
        int testId = tileId;

            //Selecting random tile and cycling all until playable
        do{

            if(game->current_turn == 1){
                testId += 6;
            }

            if(game->board[testId].nb_seeds){ //Test if tile playable
                hasPlayed = execute_move(testId, game);
                break;
            }

            if(game->current_turn == 1){
                testId -= 6;
            }

            testId = (testId + 1) % 6;

        }while(testId != tileId);
    }

}
