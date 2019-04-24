#include "defineform.h"

int collision(int curseurX, int curseurY, SDL_Rect box)
{
    if((curseurX >= box.x) && (curseurX <= box.x + box.w)
        && (curseurY >= box.y) && (curseurY <= box.y + box.h))
    {
        return 1;
    }

    return 0;
}
