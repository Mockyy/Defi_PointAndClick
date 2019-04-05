#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 800

typedef struct tGame{
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
}tGame;

typedef struct tTaille{
    int nW;
    int nH;
}tTaille;

int init(tGame *myGame);
void events(int *fin);
SDL_Texture *texte(tGame myGame, char *texte, TTF_Font *police, SDL_Color couleur);
void couleur(SDL_Window* fenetre, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void nouvellePage(tGame myGame, SDL_Texture *textureBackground, SDL_Texture *textureTimer, SDL_Rect *posTimer);
void tailleTexture(SDL_Texture *texture, SDL_Rect *posTexture);
int collision(int curseurX, int curseurY, SDL_Rect box);

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
    SDL_Surface *TempSurface = IMG_Load("./Assets/Sprites/book_background.png");

    SDL_Texture *textureBackground = SDL_CreateTextureFromSurface(myGame.gRenderer, TempSurface);

    SDL_free(TempSurface);

    ///Livvre couverture
    TempSurface = IMG_Load("./Assets/Sprites/bookcover.jpg");

    SDL_Texture *textureCover = SDL_CreateTextureFromSurface(myGame.gRenderer, TempSurface);

    ///Background image
    TempSurface = IMG_Load("./Assets/Sprites/background1.png");

    SDL_Texture *textureBackgroundImage = SDL_CreateTextureFromSurface(myGame.gRenderer, TempSurface);

    ///Temoin1
    TempSurface = IMG_Load("./Assets/Sprites/temoin1.png");

    SDL_Texture *textureTemoin1 = SDL_CreateTextureFromSurface(myGame.gRenderer, TempSurface);

    SDL_free(TempSurface);

    ///Fils
    TempSurface = IMG_Load("./Assets/Sprites/fils1.png");

    SDL_Texture *textureFils = SDL_CreateTextureFromSurface(myGame.gRenderer, TempSurface);

    SDL_FreeSurface(TempSurface);

    ///Bouton objection
    TempSurface = IMG_Load("./Assets/Sprites/objection.png");
    SDL_Texture *textureObjection = SDL_CreateTextureFromSurface(myGame.gRenderer, TempSurface);

    ///Bouton next
    TempSurface = IMG_Load("./Assets/Sprites/next.png");
    SDL_Texture *textureNext = SDL_CreateTextureFromSurface(myGame.gRenderer, TempSurface);

    //-----Création de la texture du texte-----//
    TTF_Font *KenneyPixel = NULL;
    KenneyPixel = TTF_OpenFont("./Assets/Fonts/KenneyPixel.ttf", 64);
    SDL_Texture *textureTexte;
    int cpt = 0;
    int PhaseTemoignage = 1;

    int Page = 0;

    //-----Timer-----//
    int currentFrame, lastSecond = 0, seconds = 0;
    char cTime[4];
    SDL_Color colorTimer = {0, 0, 0, 255};
    SDL_Surface* surfaceTimer;
    SDL_Texture* textureTimer;


    SDL_Rect posTimer = {10, 0, 0, 0};
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
        char* temoignage[4] = {"J'ai vu un homme sur l'aile", "Un homme, d'une telle laideur", "Il ressemblait à Killian", "Mais en plus beau"};
        char* temoignage2[4] = {"Incoyable du cul", "Quel ramdam !", "J'adore le zboub", "Pipe et jambe de bois"};

        while(fin!=1){

        ///Timer
            //Calcul des secondes
            currentFrame = SDL_GetTicks();
            seconds = currentFrame / 1000;
            if(seconds != lastSecond)
            {
                lastSecond = seconds;
//                printf("Secondes : %d\n", lastSecond);
            }
            //Copie du timer dans une chaine
            sprintf(cTime, "%d", lastSecond);
            //Écriture du texte sur une surface
            surfaceTimer = TTF_RenderText_Blended(KenneyPixel, cTime, colorTimer);
            //Conversion de la surface en texture
            textureTimer = SDL_CreateTextureFromSurface(myGame.gRenderer, surfaceTimer);


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
//                            if(event.button.clicks == 2)
//                            {
//                                printf("Double click\n");
//                            }
//                            if(event.type == SDL_MOUSEBUTTONDOWN)
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
                                    if((cpt==2) && (PhaseTemoignage==1))
                                    {
                                        printf("Bonne reponse\n");
                                        TempSurface = IMG_Load("./Assets/Sprites/temoin2.png");
                                        textureTemoin1 = SDL_CreateTextureFromSurface(myGame.gRenderer, TempSurface);
                                        PhaseTemoignage++;
                                        cpt=0;
                                    }
                                    if((cpt==3) && (PhaseTemoignage==2))
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

            tailleTexture(textureTimer, &posTimer);

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
                //Timer
                SDL_RenderCopy(myGame.gRenderer, textureTimer, NULL, &posTimer);
                //Sprite
                SDL_RenderCopy(myGame.gRenderer, textureTemoin1, NULL, &posTemoin1);
                //Objection
                SDL_RenderCopy(myGame.gRenderer, textureObjection, NULL, &posObjection);
//                //Next
//                SDL_RenderCopy(myGame.gRenderer, textureNext, NULL, &posNext);
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
                //Timer
                SDL_RenderCopy(myGame.gRenderer, textureTimer, NULL, &posTimer);
                //Sprite
                SDL_RenderCopy(myGame.gRenderer, textureTemoin1, NULL, &posTemoin1);
                //Objection
                SDL_RenderCopy(myGame.gRenderer, textureObjection, NULL, &posObjection);
//                //Next
//                SDL_RenderCopy(myGame.gRenderer, textureNext, NULL, &posNext);
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
    SDL_DestroyTexture(textureTimer);
    SDL_DestroyRenderer(myGame.gRenderer);
    SDL_DestroyWindow(myGame.gWindow);

    TTF_CloseFont(KenneyPixel);

    TTF_Quit();
    SDL_Quit();

    return 0;
}

///--------------------------------------------------------------------------------------------------------------------------------------///

    ///-----METHODES-----///

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

int collision(int curseurX, int curseurY, SDL_Rect box)
{
    if((curseurX >= box.x) && (curseurX <= box.x + box.w)
        && (curseurY >= box.y) && (curseurY <= box.y + box.h))
    {
//        printf("Collision\n");
        return 1;
    }

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

void tailleTexture(SDL_Texture *texture, SDL_Rect *posTexture)
{
    int w = 0, h = 0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    posTexture->h = h;
    posTexture->w = w;
}

void events(int *fin)
{
    //Gestion d'événement
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type)
        {
            case SDL_QUIT:
                printf("\nFermeture");
                *fin = 1;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        *fin = 1;
                        break;
                    case SDLK_z:
                        printf("Z\n");
                        break;
                    case SDLK_s:
                        printf("S\n");
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("LOL\n");
                break;
        }
    }
}

SDL_Texture *texte(tGame myGame, char *texte, TTF_Font *police, SDL_Color couleur)
{
    SDL_Surface *dialogue;
    SDL_Texture *dialogueBox;

    dialogue = TTF_RenderText_Blended(police, texte, couleur);

    dialogueBox = SDL_CreateTextureFromSurface(myGame.gRenderer, dialogue);

    return dialogueBox;
}

void couleur(SDL_Window* fenetre, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    //Choix de la couleur
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    //"Peint" l'écran de la couleur choisie
    SDL_RenderClear(renderer);
}
