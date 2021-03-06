#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Principle Functions
Player initialize_player(char* pseudo)
{
    Player player;
    player.pseudo = pseudo;
    player.score = 0;
    player.isAI = 0;    //Player by default
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


Game initialize_game(char * pseudo1, char * pseudo2)
{
    srand(time(0));
    Game game;
    game.board = initialize_board();
    game.players[0] = initialize_player(pseudo1);
    game.players[1] = initialize_player(pseudo2);
    game.current_turn = rand() % 2;
    game.seeds_captured = 0;
    game.turns_without_capture = 0;

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
        game->turns_without_capture++;

        // Semaille
        int index_nb_seeds = game->board[index].nb_seeds;
        if (index_nb_seeds != 0)
        {
            (game->board+index)->nb_seeds = 0;
            for (int i=1; i <= index_nb_seeds; i++)
            {
                int x = (normalize_index(index + i));
                // Cas spécial
                if (index != x) {
                    (game->board+x)->nb_seeds++;
                } else {
                    index_nb_seeds++;
                }
            }
        } else {
            return FAL;
        }

        // Récolte
        int last_hole_index = normalize_index(index_nb_seeds+index);
        int last_hole_seeds_sum = (game->board+last_hole_index)->nb_seeds;

        if ((last_hole_seeds_sum == 2 || last_hole_seeds_sum == 3) && (hole_index_to_player_index(last_hole_index)) != game->current_turn)
        {
            game->turns_without_capture = 0;
            game->players[game->current_turn].score += last_hole_seeds_sum;
            (game->board+last_hole_index)->nb_seeds = 0;
            game->seeds_captured += last_hole_seeds_sum;

        }
        // Change of players turn
        game->current_turn = (game->current_turn == 1) ? 0 : 1;

    } else {
        return FAL;
    }
    return TRU;
}



int test_end_game(Game game){
    //Returns ID of winner or -1 if there's none

        //First condition: 19 points
    if(game.players[0].score >= 19){
        return 0;
    }

    if(game.players[1].score >= 19){
        return 1;
    }


        //Second condition: Empty tiles

    BOOL lost = TRU;
    for(int i=0; i<6; i++){
        if(game.board[i].nb_seeds){
            lost = FAL;
            break;
        }
    }
    if(lost){
        return 0;
    }

    for(int i=6; i<12; i++){
        if(game.board[i].nb_seeds){
            lost = FAL;
            break;
        }
    }
    if(lost){
        return 1;
    }


        //Third condition: Turns without capture
    if(game.turns_without_capture >= 20){

        //Returns player with the biggest score
        return (game.players[0].score > game.players[1].score) ? 0 : 1;
    }

        //Game not finished
    return -1;

}
