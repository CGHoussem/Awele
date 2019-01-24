#include "display.h"

#define MAX_NAME_LENGTH 16

int graines[2][6];



int main(int argc, char ** argv)
{
    Images images;
    gameState gs = MENU;

    unsigned int Keep = 0,
        TexteLength = 0,
        TexteLength2 = 0,
        TexteLength3 = 0;
    char* TexteInput = (char*) calloc(16,sizeof(char)),
        * TexteInput2 = (char*) calloc(16,sizeof(char)),
        * TexteInput3 = (char*) calloc(16,sizeof(char));


    bool isJ2TexteInput = false,
         isJ1TexteInput = false,
         isJIATexteInput = false,
         isLoadTexteInput = false;

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return EXIT_FAILURE;
    }

         /*Initialization of font */
        TTF_Init();
        TTF_Font* TexteFont = TTF_OpenFont("arial.ttf", 40);
        if (TexteFont == NULL){
            printf("Error : %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
        /* Creation of the window */
        SDL_Window* Window = SDL_CreateWindow("Suoer Awélé",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                800, 600, SDL_WINDOW_RESIZABLE);
        SDL_SetWindowResizable(Window, SDL_FALSE);
        if (Window == NULL) {
            printf("Error : %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }

        SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
        if (Renderer == NULL) {
            printf("Error : %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
        // Activation de l'alpha (transparence)
        SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);

        // Load of pictures
        loadPictures(&images, Renderer);

        // Creation of rect
        SDL_Rect TexteRectJ1, TexteRectJ2, TexteRectIA, TexteRectLoad;
        TexteRectJ1.x = TexteRectJ2.x = 268;
        TexteRectJ1.y = 192;
        TexteRectJ1.w = TexteRectJ2.w = TexteRectIA.w = TexteRectLoad.w = 400;
        TexteRectJ1.h = 60;
        TexteRectJ2.h = 55;
        TexteRectIA.h = TexteRectLoad.h = 55;

        TexteRectJ2.y = 329;
        TexteRectIA.x = TexteRectLoad.x = 219;
        TexteRectIA.y = TexteRectLoad.y = 247;


        SDL_Color black = {0, 0, 0};
        SDL_Color white = {255, 255, 255};

        SDL_Surface *SurfaceTexteJ1 = NULL,
                    *SurfaceTexteJ2 = NULL,
                    *SurfaceTexteIA = NULL,
                    *SurfaceTexteLoad = NULL;

        SDL_Texture* Texte1 = NULL,
                   * Texte2 = NULL,
                   * Texte3 = NULL;

        while (gs != EXIT)
        {
            switch (gs){
                case MENU:
                    if (printPicture(Renderer, images.menuTex) == EXIT_FAILURE)
                        return EXIT_FAILURE;
                break;
                case MENUP:
                    if (printPicture(Renderer, images.playmenuTex) == EXIT_FAILURE)
                        return EXIT_FAILURE;
                break;

                case JVJ:
                    if (printPicture(Renderer, images.pseudoTex) == EXIT_FAILURE)
                        return EXIT_FAILURE;
                    SDL_RenderCopy(Renderer, Texte1, NULL, &TexteRectJ1);
                    SDL_RenderCopy(Renderer, Texte2, NULL, &TexteRectJ2);
                break;
                case JVIA:
                    if (printPicture(Renderer, images.pseudoIATex) == EXIT_FAILURE)
                        return EXIT_FAILURE;
                    SDL_RenderCopy(Renderer, Texte1, NULL, &TexteRectIA);
                break;
                case LOAD:
                    if (printPicture(Renderer, images.loadgameTex) == EXIT_FAILURE)
                        return EXIT_FAILURE;
                    SDL_RenderCopy(Renderer, Texte3, NULL, &TexteRectLoad);
                break;
                default:
                break;
            }

            SDL_Event event;
            SDL_WaitEvent(&event);
            switch(event.type){
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_BACKSPACE)
                    {
                        if (gs == JVIA && TexteLength > 0)
                        {
                            TexteLength--;
                            TexteInput[strlen(TexteInput)-1] = 0;
                            SurfaceTexteIA = TTF_RenderText_Blended(TexteFont,TexteInput,black);
                            Texte1 = SDL_CreateTextureFromSurface(Renderer,SurfaceTexteIA);
                        }
                        else if (gs == JVJ)
                        {
                            // Joueur 1
                            if (isJ1TexteInput && TexteLength > 0)
                            {
                                TexteLength--;
                                TexteInput[strlen(TexteInput)-1] = 0;
                                SurfaceTexteJ1 = TTF_RenderText_Blended(TexteFont,TexteInput, black);
                                Texte1 = SDL_CreateTextureFromSurface(Renderer,SurfaceTexteJ1);
                            } // Joueur 2
                            else if (isJ2TexteInput && TexteLength2 > 0)
                            {
                                TexteLength2--;
                                TexteInput2[strlen(TexteInput2)-1] = 0;
                                SurfaceTexteJ2 = TTF_RenderText_Blended(TexteFont,TexteInput2, black);
                                Texte2 = SDL_CreateTextureFromSurface(Renderer,SurfaceTexteJ2);
                            }
                        }
                        else if (gs == LOAD && TexteLength3 > 0)
                        {
                            TexteLength3--;
                            TexteInput3[strlen(TexteInput3)-1] = 0;
                            SurfaceTexteLoad = TTF_RenderText_Blended(TexteFont,TexteInput3,black);
                            Texte3 = SDL_CreateTextureFromSurface(Renderer,SurfaceTexteLoad);
                    }
                }
                break;
                case SDL_TEXTINPUT:
                    if (gs == JVIA && TexteLength < MAX_NAME_LENGTH)
                    {
                        TexteLength++;
                        strcat(TexteInput, event.text.text);
                        SurfaceTexteIA = TTF_RenderText_Blended(TexteFont,TexteInput, black);
                        Texte1 = SDL_CreateTextureFromSurface(Renderer, SurfaceTexteIA);
                    }
                    else if (gs == JVJ)
                    {
                        // Joueur 1
                        if (isJ1TexteInput && TexteLength < MAX_NAME_LENGTH)
                        {
                            TexteLength++;
                            strcat(TexteInput, event.text.text);
                            SurfaceTexteJ1 = TTF_RenderText_Blended(TexteFont,TexteInput, black);
                            Texte1 = SDL_CreateTextureFromSurface(Renderer,SurfaceTexteJ1);
                        } // Joueur 2
                        else if (isJ2TexteInput && TexteLength2 < MAX_NAME_LENGTH)
                        {
                            TexteLength2++;
                            strcat(TexteInput2, event.text.text);
                            SurfaceTexteJ2 = TTF_RenderText_Blended(TexteFont,TexteInput2, black);
                            Texte2 = SDL_CreateTextureFromSurface(Renderer,SurfaceTexteJ2);
                        }
                    }
                    if (gs == LOAD && TexteLength3 < MAX_NAME_LENGTH)
                    {
                        TexteLength3++;
                        strcat(TexteInput3, event.text.text);
                        SurfaceTexteLoad = TTF_RenderText_Blended(TexteFont,TexteInput3, black);
                        Texte3 = SDL_CreateTextureFromSurface(Renderer, SurfaceTexteLoad);
                    }

                break;
                case SDL_MOUSEBUTTONDOWN:
                    if (gs == JVJ)
                    {
                        int x = event.button.x, y=event.button.y;
                        // Cliquer l'un des cadres du texte
                        if (x >= TexteRectJ1.x && x <= TexteRectJ1.x+TexteRectJ1.w &&
                            y >= TexteRectJ1.y && y <= TexteRectJ1.y+TexteRectJ1.h)
                        {
                            SDL_StartTextInput();
                            isJ1TexteInput = true;
                            isJ2TexteInput = false;
                        } else if (x >= TexteRectJ2.x && x <= TexteRectJ2.x+TexteRectJ2.w &&
                            y >= TexteRectJ2.y && y <=TexteRectJ2.y+TexteRectJ2.h)
                        {
                            SDL_StartTextInput();
                            isJ1TexteInput = false;
                            isJ2TexteInput = true;
                        } else {
                            isJ1TexteInput = false;
                            isJ2TexteInput = false;
                            SDL_StopTextInput();
                        }
                        // Cliquer sur la bouton 'Valider'
                        if (x >= 373 && x <= 552 && y >= 410 && y <= 467)
                        {
                            printf("Vous avez cliqué sur la bouton Valider\n");
                        }

                        // Cliquer sur la bouton 'Retour'
                        if (x >= 12 && x <= 194 && y >= 523 && y <= 584)
                        {
                            gs = MENUP;
                        }
                    }
                     else if (gs == JVIA)
                    {
                        int x = event.button.x, y=event.button.y;
                        // Cliquer sur le cadre du texte
                        if (x >= TexteRectIA.x && x <= TexteRectIA.x+TexteRectIA.w &&
                            y >= TexteRectIA.y && y <= TexteRectIA.y+TexteRectIA.h)
                        {
                            isJIATexteInput = true;

                            SDL_StartTextInput();
                        } else {
                            isJIATexteInput = false;
                            SDL_StopTextInput();
                        }

                        // Cliquer sur la bouton 'Valider'
                        if (x >= 319 && x <= 497 && y >= 354 && y <= 412)
                        {
                            printf("Vous avez cliqué sur la bouton Valider\n");
                        }
                        // Cliquer sur la bouton 'Retour'
                        if (x >= 12 && x <=194 && y >= 523 && y <= 584)
                        {
                            gs = MENUP;
                        }
                    }
                    else if (gs == LOAD)
                   {
                       int x = event.button.x, y=event.button.y;
                       // Cliquer sur le cadre du texte
                       if (x >= TexteRectLoad.x && x <= TexteRectLoad.x+TexteRectLoad.w &&
                           y >= TexteRectLoad.y && y <= TexteRectLoad.y+TexteRectLoad.h)
                       {
                           isLoadTexteInput = true;

                           SDL_StartTextInput();
                       } else {
                           isLoadTexteInput = false;
                           SDL_StopTextInput();
                       }

                       // Cliquer sur la bouton 'Valider'
                       if (x >= 319 && x <= 497 && y >= 354 && y <= 412)
                       {
                           printf("Vous avez cliqué sur la bouton Charger\n");
                       }
                       // Cliquer sur la bouton 'Retour'
                       if (x >= 12 && x <=194 && y >= 523 && y <= 584)
                       {
                           gs = MENUP;
                       }
                   }
                    else if (gs == MENUP)
                    {
                        int x = event.button.x, y=event.button.y;
                        if (x >= 485 && x <= 642 && y >= 211 && y <= 269)
                        {
                            gs = JVJ;
                        }
                        else if (x >= 195 && x <= 378 && y >= 211 && y <= 269)
                        {
                            gs = JVIA;
                        }
                        else if (x >= 12 && x <= 195 && y >= 523 && y <= 584)
                        {
                            gs = MENU;
                        }
                        else if (x >= 159 && x <= 669 && y >= 333 && y <= 403)
                        {
                            gs = LOAD;
                        }

                    }
                    else if (gs == MENU)
                    {
                        int x = event.button.x, y=event.button.y;
                        if (x >= 298 && x <= 460 && y >= 235 && y <= 308)
                        {
                            gs = MENUP;
                        }
                        else if (x >= 274 && x <= 463 && y >= 468 && y <= 542)
                        {
                            gs = EXIT;
                        }
                    }
                    break;
                case SDL_QUIT:
                    gs = EXIT;
                    break;
            }
            SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 100);
            if (isJIATexteInput)
                SDL_RenderFillRect(Renderer, &TexteRectIA);
            if (isJ1TexteInput)
                SDL_RenderFillRect(Renderer, &TexteRectJ1);
            if (isJ2TexteInput)
                SDL_RenderFillRect(Renderer, &TexteRectJ2);
            if (isLoadTexteInput)
                SDL_RenderFillRect(Renderer, &TexteRectLoad);

            /* À la place de SDL_Flip */
            SDL_RenderPresent(Renderer);
    }


    FreePictures(&images);
    SDL_FreeSurface(SurfaceTexteIA);
    SDL_FreeSurface(SurfaceTexteJ1);
    SDL_FreeSurface(SurfaceTexteJ2);
    SDL_FreeSurface(SurfaceTexteLoad);
    SDL_DestroyTexture(Texte1);
    SDL_DestroyTexture(Texte2);
    SDL_DestroyTexture(Texte3);
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    TTF_CloseFont(TexteFont);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;

}

void FreePictures(Images* images)
{
    SDL_DestroyTexture(images->menuTex);
    SDL_DestroyTexture(images->playmenuTex);
    SDL_DestroyTexture(images->pseudoIATex);
    SDL_DestroyTexture(images->pseudoTex);
    SDL_DestroyTexture(images->loadgameTex);
    //SDL_DestroyTexture(images->gridTex);
}
void loadPictures(Images* images, SDL_Renderer* Renderer)
{
    SDL_Surface* picture = IMG_Load("Pictures/menu.png");
    images->menuTex = SDL_CreateTextureFromSurface(Renderer, picture);
    picture = IMG_Load("Pictures/playmenu.png");
    images->playmenuTex = SDL_CreateTextureFromSurface(Renderer, picture);
    picture = IMG_Load("Pictures/nicknameia.png");
    images->pseudoIATex = SDL_CreateTextureFromSurface(Renderer, picture);
    picture = IMG_Load("Pictures/nickname1.png");
    images->pseudoTex = SDL_CreateTextureFromSurface(Renderer, picture);
    picture = IMG_Load("Pictures/loadgame.png");
    images->loadgameTex = SDL_CreateTextureFromSurface(Renderer, picture);
    //picture = IMG_Load("Pictures/grid.png");
    //images->gridTex = SDL_CreateTextureFromSurface(Renderer, picture);
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
