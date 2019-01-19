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

void reverseVerticalDirection(object *DOG) /* reverse the DOG¡¦s up-down direction */
{
    int i;
    if ( DOG[i].direction == DOWN_RIGHT )
        DOG[i].direction = UP_RIGHT;
    else if ( DOG[i].direction == DOWN_LEFT )
        DOG[i].direction = UP_LEFT;
    else if ( DOG[i].direction == UP_RIGHT )
        DOG[i].direction = DOWN_RIGHT;
    else if ( DOG[i].direction == UP_LEFT )
        DOG[i].direction = DOWN_LEFT;
} /* end function reverseVerticalDirection */
