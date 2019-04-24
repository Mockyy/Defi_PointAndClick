#include "defineform.h"

int init(tGame *myGame)
{
    //-----Initialisation de la SDL-----//
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) // Initialisation de la SDL
    {
        printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());
        return EXIT_FAILURE;
    }

    if(TTF_Init() == -1)
    {
        printf("Erreur d'init TTF : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    //-----Création de la fenêtre-----//
    myGame->gWindow = SDL_CreateWindow("Une fenetre SDL" , 300, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    if(myGame->gWindow == NULL) // Gestion des erreurs
    {
        printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
        return EXIT_FAILURE;
    }

    //-----Création du renderer-----//
    myGame->gRenderer = SDL_CreateRenderer(myGame->gWindow, -1, 0);
    if(myGame->gRenderer == NULL)
    {
        printf("Erreur de création du renderer : %s,",SDL_GetError());
    }

    return 1;
}

void couleur(SDL_Window* fenetre, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    //Choix de la couleur
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    //"Peint" l'écran de la couleur choisie
    SDL_RenderClear(renderer);
}
