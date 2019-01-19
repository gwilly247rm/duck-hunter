#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include <stdio.h>
#include <stdlib.h>

#include "function.h"
#include "struct.h"

#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3

void moveDOG(ALLEGRO_EVENT *event,object*DOG) /* moves the DOG */
{
    int i;
    switch ( DOG[i].direction )
    {
    case DOWN_RIGHT:
        DOG[i].x=DOG[i].x+1; /* move the DOG to the right */
        ++DOG[i].y; /* move the DOG down */
        break;
    case UP_RIGHT:
        ++DOG[i].x; /* move the DOG to the right */
        --DOG[i].y; /* move the DOG up */
        break;
    case DOWN_LEFT:
        --DOG[i].x; /* move the DOG to the left */
        ++DOG[i].y; /* move the DOG down */
        break;
    case UP_LEFT:
        --DOG[i].x; /* move the DOG to the left */
        --DOG[i].y; /* move the DOG up */
        break;
    } /* end switch */

    /* make sure the DOG doesn¡¦t go off the screen */

    /* if the DOG is going off the top or bottom... */
    if ( DOG[i].y <= 0 || DOG[i].y >= (430) )//display_len - DOG_SIZE_H
        reverseVerticalDirection(DOG); /* make it go the other way */

    /* if the DOG is going off the left or right... */
    if ( DOG[i].x <= 0 || DOG[i].x >= (1080-90) )//display_wid - DOG_SIZE_W
        reverseHorizontalDirection(DOG); /* make it go the other way */
} /* end function moveDOG */
