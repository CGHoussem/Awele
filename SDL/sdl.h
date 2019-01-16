#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void PlayMenu(SDL_Renderer* Renderer,SDL_Surface* Sprite,SDL_Texture* Texture,SDL_Rect dest, bool* keep);
