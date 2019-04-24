#include "defineform.h"

void nouvellePage(tGame myGame, SDL_Texture *textureBackground, SDL_Texture *textureTimer, SDL_Rect *posTimer);

int main(int argc, char *argv[])
{
    tGame myGame;
    SDL_Color couleurNoire = {0, 0, 0};

///--------------------------------------------------------------------------------------------------------------------------------------///

    ///-----Initialisation-----//
    if(init(&myGame)==0)
    {
        printf("Erreur d'initialisation");
    }

    ///Background livre
    SDL_Texture *textureBackground = createTexture("./Assets/Sprites/book_background.png", myGame);

    ///Livvre couverture
    SDL_Texture *textureCover = createTexture("./Assets/Sprites/bookcover.jpg", myGame);

    ///Background image
    SDL_Texture *textureBackgroundImage = createTexture("./Assets/Sprites/background1.png", myGame);

    ///Temoin1
    SDL_Texture *textureTemoin1 = createTexture("./Assets/Sprites/temoin1.png", myGame);

    ///Fils
    SDL_Texture *textureFils = createTexture("./Assets/Sprites/fils1.png", myGame);

    ///Bouton objection
    SDL_Texture *textureObjection = createTexture("./Assets/Sprites/objection.png", myGame);

    ///Bouton next
    SDL_Texture *textureNext = createTexture("./Assets/Sprites/next.png", myGame);

    //-----Création de la texture du texte-----//
    TTF_Font *KenneyPixel = NULL;
    KenneyPixel = TTF_OpenFont("./Assets/Fonts/KenneyPixel.ttf", 64);
    SDL_Texture *textureTexte;
    int cpt = 0;
    int PhaseTemoignage = 1;
    int Page = 0;

    SDL_Rect posCover = {800, 0, 0, 0};
    SDL_Rect posBackground = {250, 100, 0, 0};
    SDL_Rect posTemoin1 = {350, 250, 0, 0};
    SDL_Rect posDialogue = {175, 475, 0, 0};
    SDL_Rect posObjection = {300, 600, 0, 0};
    SDL_Rect posNext = {1450, 350, 0, 0};
    SDL_Rect posBack = {50, 350, 0, 0};
    SDL_Rect posFils = {1000, 250, 0, 0};


///--------------------------------------------------------------------------------------------------------------------------------------///

    ///---BOUCLE PRINCIPALE---///
    if(myGame.gWindow)
    {
        int fin = 0;
        char* temoignage[4] = {"Le 20 aout j'étais seul chez moi.","Je connais James depuis l'école de commerce.",
        "Il est le grand frère que je n'ai jamais eu.","On partage tout !"};
        char* temoignage2[2] = {"Il est vrai que j'ai eu une relation avec Katerine avant qu'elle ne soit avec James.",
        "Mais c'était il y a plus 20 ans !"};

        while(fin!=1){

        ///Events
            SDL_Event event;
            if(SDL_PollEvent(&event)){
                switch(event.type)
                {
                    case SDL_QUIT:
                        printf("\nFermeture");
                        fin = 1;
                        break;
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            printf("\nFermeture");
                            fin = 1;
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(event.button.button == SDL_BUTTON_LEFT)
                        {
                            if(collision(event.button.x, event.button.y, posDialogue))
                            {
                                if(cpt!=3)
                                {
                                    cpt++;
                                }
                                else
                                {
                                    cpt=0;
                                }
                            }
                            if(collision(event.button.x, event.button.y, posObjection))
                            {
                                if((cpt==3) && (PhaseTemoignage==1))
                                {
                                    printf("Bonne reponse\n");
                                    textureTemoin1 = createTexture("./Assets/Sprites/temoin2.png", myGame);
                                    PhaseTemoignage++;
                                    cpt=0;
                                }
                                if((cpt==1) && (PhaseTemoignage==2))
                                {
                                    printf("Bonne reponse\n");
                                    Page++;
                                }
                            }
                            if(collision(event.button.x, event.button.y, posNext))
                            {
                                Page++;
                                printf("Page %d\n",Page);
                            }
                            if(collision(event.button.x, event.button.y, posBack))
                            {
                                Page--;
                                printf("Page %d\n",Page);
                            }
                        }
                        break;
                    }
                }

            switch(PhaseTemoignage)
            {
                case 1 :
                    textureTexte = texte(myGame, temoignage[cpt], KenneyPixel, couleurNoire);
                    break;
                case 2 :
                    textureTexte = texte(myGame, temoignage2[cpt], KenneyPixel, couleurNoire);
                    break;
            }

            tailleTexture(textureCover, &posCover);
            posCover.w = posCover.w/2;
            posCover.h = posCover.h/2;

            tailleTexture(textureBackgroundImage, &posBackground);

            tailleTexture(textureNext, &posNext);
            posNext.w = posNext.w/2;
            posNext.h = posNext.h/2;
            posBack.w = posNext.w;
            posBack.h = posNext.h;

            tailleTexture(textureObjection, &posObjection);

            tailleTexture(textureTemoin1, &posTemoin1);

            tailleTexture(textureFils, &posFils);

            tailleTexture(textureTexte, &posDialogue);


        ///Couleur de fond (blanc)
            couleur(myGame.gWindow, myGame.gRenderer, 255, 255, 255, 255);

        ///Copie de toutes les textures sur le renderer
        switch(Page)
        {
            case 0 :
                SDL_RenderCopy(myGame.gRenderer, textureCover, NULL, &posCover);
                SDL_RenderCopy(myGame.gRenderer, textureNext, NULL, &posNext);
                break;

            case 1 :
                //Fond livre
                SDL_RenderCopy(myGame.gRenderer, textureBackground, NULL, NULL);
                //Background image
                SDL_RenderCopy(myGame.gRenderer, textureBackgroundImage, NULL, &posBackground);
                //Sprite
                SDL_RenderCopy(myGame.gRenderer, textureTemoin1, NULL, &posTemoin1);
                //Objection
                SDL_RenderCopy(myGame.gRenderer, textureObjection, NULL, &posObjection);
                //Texte
                SDL_RenderCopy(myGame.gRenderer, textureTexte, NULL, &posDialogue);
                //Back
                SDL_RenderCopyEx(myGame.gRenderer, textureNext, NULL, &posBack, 180, NULL, SDL_FLIP_VERTICAL);
                break;

            case 2 :
                //Fond livre
                SDL_RenderCopy(myGame.gRenderer, textureBackground, NULL, NULL);
                //Background image
                SDL_RenderCopy(myGame.gRenderer, textureBackgroundImage, NULL, &posBackground);
                //Sprite
                SDL_RenderCopy(myGame.gRenderer, textureTemoin1, NULL, &posTemoin1);
                //Objection
                SDL_RenderCopy(myGame.gRenderer, textureObjection, NULL, &posObjection);
                //Texte
                SDL_RenderCopy(myGame.gRenderer, textureTexte, NULL, &posDialogue);
                //Back
                SDL_RenderCopyEx(myGame.gRenderer, textureNext, NULL, &posBack, 180, NULL, SDL_FLIP_VERTICAL);
                //Fils
                SDL_RenderCopy(myGame.gRenderer, textureFils, NULL, &posFils);
                break;

            default :
                Page=0;
        }

        ///Affichage du renderer
            SDL_RenderPresent(myGame.gRenderer);
        }
    }

///--------------------------------------------------------------------------------------------------------------------------------------///

    ///-----FERMETURE------///
    SDL_DestroyTexture(textureBackground);
    SDL_DestroyRenderer(myGame.gRenderer);
    SDL_DestroyWindow(myGame.gWindow);

    TTF_CloseFont(KenneyPixel);

    TTF_Quit();
    SDL_Quit();

    return 0;
}

void nouvellePage(tGame myGame, SDL_Texture *textureBackground, SDL_Texture *textureTimer, SDL_Rect *posTimer)
{
    ///Couleur de fond (blanc)
    couleur(myGame.gWindow, myGame.gRenderer, 255, 0, 255, 255);

    ///Copie de toutes les textures sur le renderer
    //Fond livre
    SDL_RenderCopy(myGame.gRenderer, textureBackground, NULL, NULL);
    //Timer
    SDL_RenderCopy(myGame.gRenderer, textureTimer, NULL, posTimer);
}
