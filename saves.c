//WARNING Need json-c library: https://github.com/json-c/json-c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "saves.h"


//Game saves

void save_game(Game game, char * save_name){

    json_object * j_game = json_object_new_object();

        //game.current_turn
    json_object * j_current_turn = json_object_new_int(game.current_turn);
    json_object_object_add(j_game, "current_turn", j_current_turn);


        //game.seeds_captured
    json_object * j_seeds_captured = json_object_new_int(game.seeds_captured);
    json_object_object_add(j_game, "seeds_captured", j_seeds_captured);


        //game.board
    json_object * j_board_array = json_object_new_array();
    json_object **  j_holes = (json_object**) malloc(12 * sizeof(json_object*));


    json_object **  j_hole_nb_seeds = (json_object**) malloc(12 * sizeof(json_object*));
    json_object **  j_hole_owner_id = (json_object**) malloc(12 * sizeof(json_object*));

    for(int i=0; i<12; i++){
        j_holes[i] = json_object_new_object();

            //hole.nb_seeds
        j_hole_nb_seeds[i] = json_object_new_int(game.board[i].nb_seeds);
        json_object_object_add(j_holes[i], "nb_seeds", j_hole_nb_seeds[i]);

            //hole.owner_id
        j_hole_owner_id[i] = json_object_new_int(game.board[i].owner_id);
        json_object_object_add(j_holes[i], "owner_id", j_hole_owner_id[i]);

            //Appending to array
        json_object_array_add(j_board_array, j_holes[i]);
    }
    json_object_object_add(j_game, "board", j_board_array);


        //game.players
    json_object * j_players_array = json_object_new_array();
    json_object **  j_players = (json_object**) malloc(2 * sizeof(json_object*));

    json_object ** j_player_pseudo = (json_object**) malloc(2 * sizeof(json_object*));
    json_object ** j_player_score = (json_object**) malloc(2 * sizeof(json_object*));

    for(int i=0; i<2; i++){
        j_players[i] = json_object_new_object();

            //player.pseudo
        j_player_pseudo[i] = json_object_new_string(game.players[i].pseudo);
        json_object_object_add(j_players[i], "pseudo", j_player_pseudo[i]);

            //player.score
        j_player_score[i] = json_object_new_int(game.players[i].score);
        json_object_object_add(j_players[i], "score", j_player_score[i]);

            //Appending to array
        json_object_array_add(j_players_array, j_players[i]);
    }
    json_object_object_add(j_game, "players", j_players_array);


        //Copy of string to the JSON file
    char *  path = (char*) malloc(1000 * sizeof(char));
    path[0] = '\0';
    path = strcat(path, "saves/");
    path = strcat(path, save_name);
    path = strcat(path, ".json");

    FILE * save = fopen(path, "w");

    fputs(json_object_to_json_string(j_game), save);


        //Freeing
    json_object_put(j_game); //All children object are alsoo freed
    free(path);
    fclose(save);

    free(j_holes);
    free(j_hole_owner_id);
    free(j_hole_nb_seeds);

    free(j_players);
    free(j_player_score);
    free(j_player_pseudo);

}



void load_game(Game * game, char * save_name){
        //Access to the JSON file
    char *  path = (char*) malloc(100 * sizeof(char));
    path[0] = '\0';
    path = strcat(path, "saves/");
    path = strcat(path, save_name);
    path = strcat(path, ".json");

    FILE * save = fopen(path, "r");

    char j_string [1000];
    j_string[0] = '\0';
    fgets(j_string, 1000, save);
    fclose(save);
    free(path);

    json_object * j_game = json_tokener_parse(j_string);


        //Parsing
        //game.current_turn
    json_object * j_current_turn;
    json_object_object_get_ex(j_game, "current_turn", &j_current_turn);
    game->current_turn = json_object_get_int(j_current_turn);


        //game.seeds_captured
    json_object * j_seeds_captured;
    json_object_object_get_ex(j_game, "seeds_captured", &j_seeds_captured);
    game->seeds_captured = json_object_get_int(j_seeds_captured);


        //game.board
    game->board = (Hole*) malloc(12* sizeof(Hole));
    json_object * j_board_array;
    json_object_object_get_ex(j_game, "board", &j_board_array);

    for(int i=0; i<12; i++){
        json_object * j_holes = json_object_array_get_idx(j_board_array, i);

            //hole.nb_seeds
        json_object * j_hole_nb_seeds;
        json_object_object_get_ex(j_holes, "nb_seeds", &j_hole_nb_seeds);
        game->board[i].nb_seeds = json_object_get_int(j_hole_nb_seeds);

            //hole.owner_id
        json_object * j_hole_owner_id;
        json_object_object_get_ex(j_holes, "owner_id", &j_hole_owner_id);
        game->board[i].owner_id = json_object_get_int(j_hole_owner_id);
    }


        //game.players
    json_object * j_players_array;
    json_object_object_get_ex(j_game, "players", &j_players_array);

    for(int i=0; i<2; i++){
        json_object * j_players = json_object_array_get_idx(j_players_array, i);

            //player.pseudo
        json_object * j_player_pseudo;
        json_object_object_get_ex(j_players, "pseudo", &j_player_pseudo);
        game->players[i].pseudo = (char*) malloc((json_object_get_string_len(j_player_pseudo)+1) * sizeof(char));
        memset(game->players[i].pseudo, '\0', (json_object_get_string_len(j_player_pseudo)+1));
        strcpy(game->players[i].pseudo, json_object_get_string(j_player_pseudo));

            //player.seeds_captured
        json_object * j_player_score;
        json_object_object_get_ex(j_players, "score", &j_player_score);
        game->players[i].score = json_object_get_int(j_player_score);
    }


    json_object_put(j_game);
}



//Score saves
//TODO
