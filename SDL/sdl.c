#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    /* Initialization */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Creation of the window */
        SDL_Window* Window = NULL;
        SDL_Renderer* Renderer = NULL;
        SDL_Surface* Sprite = NULL;
        SDL_Texture* Texture = NULL;

        SDL_Event event;
        int keep = 1;

        Window = SDL_CreateWindow("Super Awélé",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  800,
                                                                  600,
                                                                  SDL_WINDOW_SHOWN);

        if( Window )
        {
            Renderer=SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED);
            if(Renderer)
            {
                Sprite=IMG_Load("Pictures/menu.png");
                if(Sprite)
                {
                    Texture=SDL_CreateTextureFromSurface(Renderer,Sprite);
                    if(Texture)
                    {
                        SDL_Rect dest = { 0 , 0, 800 , 600 };
                        SDL_RenderCopy(Renderer,Texture,NULL,&dest);
                        SDL_RenderPresent(Renderer);

                            while(keep)
                            {
                              SDL_WaitEvent(&event);
                              switch(event.type)
                              {
                                case SDL_QUIT:
                                keep = 0;
                                break;
                              }
                            }
                            SDL_DestroyTexture(Texture);
                    }
                    else
                    {
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                    }

                    SDL_FreeSurface(Sprite);

                }
                else
                {
                    fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
                }

                SDL_DestroyRenderer(Renderer); // Libération de la mémoire du SDL_Renderer
            }
            else
            {
                fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
            }


        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
        SDL_DestroyWindow(Window);
    }

    SDL_Quit();

    return 0;
}
