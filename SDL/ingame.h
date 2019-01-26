#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../game.h"
#include "../saves.h"
#include "../ai.h"
#include "display.h"

void gameLoop(Game game, SDL_Renderer *Renderer, SDL_Texture* gridTex, TTF_Font* TexteFont);
void displayGrid(Game game, SDL_Renderer *Renderer, SDL_Texture* gridTex, TTF_Font* TexteFont);
int getHoleId(int x, int y);
