#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "defineform.h"

extern SDL_Texture *createTexture(char* chemin, tGame myGame);

extern SDL_Texture *texte(tGame myGame, char *texte, TTF_Font *police, SDL_Color couleur);

void tailleTexture(SDL_Texture *texture, SDL_Rect *posTexture);

#endif // TEXTURE_H_INCLUDED
