#include "defineform.h"

SDL_Texture *createTexture(char* chemin, tGame myGame)
{
    SDL_Surface *TempSurface = IMG_Load(chemin);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(myGame.gRenderer, TempSurface);
    SDL_FreeSurface(TempSurface);

    return texture;
}

SDL_Texture *texte(tGame myGame, char *texte, TTF_Font *police, SDL_Color couleur)
{
    SDL_Surface *dialogue;
    SDL_Texture *dialogueBox;

    dialogue = TTF_RenderText_Blended(police, texte, couleur);

    dialogueBox = SDL_CreateTextureFromSurface(myGame.gRenderer, dialogue);

    return dialogueBox;
}

void tailleTexture(SDL_Texture *texture, SDL_Rect *posTexture)
{
    int w = 0, h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    posTexture->h = h;
    posTexture->w = w;
}
