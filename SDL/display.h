#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
typedef enum gameState {
    MENU, LOAD,MENUP,JVJ, JVIA, EXIT
} gameState;

typedef struct Images{
    SDL_Texture* menuTex;
    SDL_Texture* pseudoTex;
    SDL_Texture* pseudoIATex;
    SDL_Texture* playmenuTex;
    SDL_Texture* loadgameTex;
//    SDL_Texture* gridTex;
} Images;
void FreePictures(Images* images);
void loadPictures(Images* images, SDL_Renderer* Renderer);
int printPicture(SDL_Renderer* Renderer, SDL_Texture* texture);
