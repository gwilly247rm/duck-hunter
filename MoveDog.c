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

void moveDOG(object *DOG) /* moves the DOG */
{
    int i;

    for(i=0; i<=4; i++)
    {


            switch ( DOG[i].direction )
            {
            case DOWN_RIGHT:
                DOG[i].x=DOG[i].x+1; /* move the DOG to the right */
                DOG[i].y=DOG[i].y+1; /* move the DOG down */
                break;
            case UP_RIGHT:
                DOG[i].x=DOG[i].x+1; /* move the DOG to the right */
                DOG[i].y=DOG[i].y-1; /* move the DOG up */
                break;
            case DOWN_LEFT:
                DOG[i].x=DOG[i].x-1; /* move the DOG to the left */
                DOG[i].y=DOG[i].y+1; /* move the DOG down */
                break;
            case UP_LEFT:
                DOG[i].x=DOG[i].x-1; /* move the DOG to the left */
                DOG[i].y=DOG[i].y-1; /* move the DOG up */
                break;
            } /* end switch */

    }


    /* make sure the DOG doesn¡¦t go off the screen */

    /* if the DOG is going off the top or bottom... */
    for(i=0;i<=4;i++){
    if ( DOG[i].y <= 0 || DOG[i].y >= (430) ){

        reverseVerticalDirection(&DOG[i]);} /* make it go the other way */

    /* if the DOG is going off the left or right... */
    else if( DOG[i].x <= 0 || DOG[i].x >= (1080-90) ){

        reverseHorizontalDirection(&DOG[i]);} /* make it go the other way */
}} /* end function moveDOG */
