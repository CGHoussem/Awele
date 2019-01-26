#include "display.h"

void FreePictures(Images* images)
{
    SDL_DestroyTexture(images->menuTex);
    SDL_DestroyTexture(images->playmenuTex);
    SDL_DestroyTexture(images->pseudoIATex);
    SDL_DestroyTexture(images->pseudoTex);
    SDL_DestroyTexture(images->loadgameTex);
    SDL_DestroyTexture(images->gridTex);
}
void loadPictures(Images* images, SDL_Renderer* Renderer)
{
    SDL_Surface* picture = IMG_Load("SDL/Pictures/menu.png");

    images->menuTex = SDL_CreateTextureFromSurface(Renderer, picture);
    picture = IMG_Load("SDL/Pictures/playmenu.png");

    images->playmenuTex = SDL_CreateTextureFromSurface(Renderer, picture);
    picture = IMG_Load("SDL/Pictures/nicknameia.png");

    images->pseudoIATex = SDL_CreateTextureFromSurface(Renderer, picture);
    picture = IMG_Load("SDL/Pictures/nickname1.png");

    images->pseudoTex = SDL_CreateTextureFromSurface(Renderer, picture);
    picture = IMG_Load("SDL/Pictures/loadgame.png");

    images->loadgameTex = SDL_CreateTextureFromSurface(Renderer, picture);
    picture = IMG_Load("SDL/Pictures/grid.png");
    images->gridTex = SDL_CreateTextureFromSurface(Renderer, picture);
}

int printPicture(SDL_Renderer* Renderer, SDL_Texture* Texture)
{
    SDL_Rect dest = {0, 0, 800, 600};

    if (Texture == NULL || SDL_RenderCopy(Renderer, Texture, NULL, &dest) != 0) {
        printf("Error : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
