#ifndef SDL_H_INCLUDED
#define SDL_H_INCLUDED

#include "defineform.h"

typedef struct tGame{
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
}tGame;

typedef struct tTaille{
    int nW;
    int nH;
}tTaille;

extern int init(tGame *myGame);

void couleur(SDL_Window* fenetre, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

#endif // SDL_H_INCLUDED
