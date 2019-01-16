#include "sdl.h"

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
        SDL_Rect dest;
        SDL_Event event;
        bool keep = 1;

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
                         dest.x = 0;
                         dest.y = 0;
                         dest.w = 800;
                         dest.h = 600;
                        SDL_RenderCopy(Renderer,Texture,NULL,&dest);
                        SDL_RenderPresent(Renderer);

                            while(keep)//boucle principale
                            {
                              SDL_WaitEvent(&event);
                              switch(event.type)
                              {
                                case SDL_QUIT:
                                keep = 0;
                                break;

                                case SDL_MOUSEBUTTONUP :
                                if (event.button.y>235 && event.button.y<=308 && event.button.x>298 && event.button.x<=460)
                                    {
                                        PlayMenu(Renderer,Sprite,Texture,dest,&keep);
                                    }


                                //Button Quit
                                    if (event.button.y>468 && event.button.y<=542 && event.button.x>274 && event.button.x<=463)
                                        {
                                            keep = 0;
                                        }
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



void PlayMenu(SDL_Renderer* Renderer,SDL_Surface* Sprite,SDL_Texture* Texture,SDL_Rect dest,bool* keep )
{
    Sprite=IMG_Load("Pictures/playmenu.png");
    bool keep2=1;
    SDL_Event event2;
    if(Sprite)
    {
        Texture=SDL_CreateTextureFromSurface(Renderer,Sprite);
        if(Texture)
        {
             dest.x = 0;
             dest.y = 0;
             dest.w = 800;
             dest.h = 600;
            SDL_RenderCopy(Renderer,Texture,NULL,&dest);
            SDL_RenderPresent(Renderer);

            while(keep2) //boule secondaire
            {
              SDL_WaitEvent(&event2);
              switch(event2.type)
              {
                case SDL_QUIT:
                keep2 = 0; // quitte la boucle secondaire
                *keep=0; //permet de quitter la boucle principale => ferme la fenêtre
                break;

                case SDL_MOUSEBUTTONUP :
                //Load Button
                if (event2.button.y>332 && event2.button.y<=401 && event2.button.x>159 && event2.button.x<=670)
                    {
                        fprintf(stderr, "click on Load \n");

                    }
                //1vs1 Button
                    if (event2.button.y>211 && event2.button.y<=269 && event2.button.x>485 && event2.button.x<=642)
                        {
                            fprintf(stderr, "click on 1 vs 1 \n");

                        }

                //1vsIA Button
                    if (event2.button.y>211 && event2.button.y<=269 && event2.button.x>195 && event2.button.x<=378)
                        {
                            fprintf(stderr, "click on 1 vs IA \n");
                        }


                //ReturnButton
                    if (event2.button.y>521&& event2.button.y<=582 && event2.button.x>12 && event2.button.x<=195)
                        {
                            Sprite=IMG_Load("Pictures/menu.png");
                            Texture=SDL_CreateTextureFromSurface(Renderer,Sprite);
                            SDL_RenderCopy(Renderer,Texture,NULL,&dest);
                            SDL_RenderPresent(Renderer);
                            keep2 = 0;
                        }
                break;
              }
            }
        }
    }
}
