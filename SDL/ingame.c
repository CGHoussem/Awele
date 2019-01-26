#include "ingame.h"

void gameLoop(Game game, SDL_Renderer *Renderer, SDL_Texture* gridTex, TTF_Font* TexteFont){

    SDL_Event event;

    int correctInput = 0;
    int quit = 0;
    int x, y;

        //Game level loop
    do{

        displayGrid(game, Renderer, gridTex, TexteFont);

        if(game.players[game.current_turn].isAI == 0){    //If human player

            //SDL level loop
            correctInput = 0;
            while(!correctInput){
                correctInput = 0;

                SDL_WaitEvent(&event);

                switch(event.type){
                    case SDL_MOUSEBUTTONDOWN:
                        x = event.button.x;
                        y = event.button.y;

                        //Quit button
                        if(x > 15 && y > 523 && x < 157 && y < 573){
                            quit = 1;
                            correctInput = 1;
                        }

                        //Save button
                        if(x > 234 && y > 523 && x < 508 && y < 573){
                            correctInput = 1;
                            char saveName [100];
                            saveName[0] = '\0';

                            strcat(saveName, game.players[0].pseudo);
                            strcat(saveName, "Vs");
                            strcat(saveName, game.players[1].pseudo);
                            save_game(game, saveName);
                        }

                        else{
                            int holeId = getHoleId(x, y);

                            //Player 1
                            if(holeId >= 0 && holeId < 11){
                                correctInput = execute_move(holeId, &game);
                            }
                        }

                        break;
                }

            }
        }

        else{   //AI turn
            ai_turn(&game);
        }


        displayGrid(game, Renderer, gridTex, TexteFont);


    }while(test_end_game(game) == -1 && !quit);

}



void displayGrid(Game game, SDL_Renderer *Renderer, SDL_Texture* gridTex, TTF_Font* TexteFont){

        //Background
    printPicture(Renderer, gridTex);


    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};
    SDL_Surface  * textSurface = NULL;
    SDL_Texture * textTexture = NULL;
    char nSeeds [4];
    SDL_Rect rect;
    rect.w = 55;
    rect.h = 75;


        //Number of seeds
    for(int i=0; i<12; i++){
        int xCoord = i;
        if(i > 5){
            xCoord = 11 - xCoord;
        }

        rect.x = 190 + 75 * (xCoord);



        if(i < 6){
            rect.y = 224;
        } else {
            rect.y = 317;
        }

        nSeeds[0] = '\0';
        sprintf(nSeeds,"%d", game.board[i].nb_seeds);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        textSurface =  TTF_RenderText_Blended(TexteFont, nSeeds, white);
        textTexture = SDL_CreateTextureFromSurface(Renderer,textSurface);

        SDL_RenderCopy(Renderer, textTexture, NULL, &rect);
    }


        //Pseudos
    int length;

    rect.x = 60;
    rect.y = 210;
    for(length = 0; game.players[0].pseudo[length] != '\0'; ++length);
    rect.w = length * 15;
    rect.h = 35;

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    textSurface =  TTF_RenderText_Blended(TexteFont, game.players[0].pseudo, black);
    textTexture = SDL_CreateTextureFromSurface(Renderer,textSurface);
    SDL_RenderCopy(Renderer, textTexture, NULL, &rect);


    rect.x = 650;
    for(length = 0; game.players[1].pseudo[length] != '\0'; ++length);
    rect.w = length * 15;

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    textSurface =  TTF_RenderText_Blended(TexteFont, game.players[1].pseudo, black);
    textTexture = SDL_CreateTextureFromSurface(Renderer,textSurface);
    SDL_RenderCopy(Renderer, textTexture, NULL, &rect);


        //Scores
    rect.w = 18;
    rect.h = 40;

    rect.x = 101;
    rect.y = 286;

    nSeeds[0] = '\0';
    sprintf(nSeeds,"%d", game.players[0].score);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    textSurface =  TTF_RenderText_Blended(TexteFont, nSeeds, black);
    textTexture = SDL_CreateTextureFromSurface(Renderer,textSurface);
    SDL_RenderCopy(Renderer, textTexture, NULL, &rect);


    rect.x = 663;

    nSeeds[0] = '\0';
    sprintf(nSeeds,"%d", game.players[0].score);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    textSurface =  TTF_RenderText_Blended(TexteFont, nSeeds, black);
    textTexture = SDL_CreateTextureFromSurface(Renderer,textSurface);
    SDL_RenderCopy(Renderer, textTexture, NULL, &rect);


        //Current player
    rect.x = 290;
    rect.y = 430;
    rect.w = (length + 9) * 15;
    rect.h = 35;

    char currentPlayer [70] = "Playing: ";
    strcat(currentPlayer, game.players[game.current_turn].pseudo);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    textSurface =  TTF_RenderText_Blended(TexteFont, currentPlayer, black);
    textTexture = SDL_CreateTextureFromSurface(Renderer,textSurface);
    SDL_RenderCopy(Renderer, textTexture, NULL, &rect);


    SDL_RenderPresent(Renderer);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);


}



int getHoleId(int x, int y){
    int clickedHole = -1;

    if(x > 180 && x < 620){
        if(y > 223 && y < 293){
            clickedHole = ((x-180)/73)%6;

        }


        if(y > 316 && y < 387){
            clickedHole = 11 - (((x-180)/73)%6);
        }
    }

    return clickedHole;
}
