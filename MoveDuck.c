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

#define PADDLE_MOVE 10

void moveduck(ALLEGRO_EVENT *event,object*duck)
{
    //if (al_key_down(&KBstate, ALLEGRO_KEY_LEFT)){al_draw_bitmap( duck2, duck.x, 0, 0);/* draw the bitmap */};
    //if (al_key_down(&KBstate, ALLEGRO_KEY_RIGHT)){al_draw_bitmap( duck1, duck.x, 0, 0);/* draw the bitmap */};
    //else if (al_draw_bitmap( duck3, duck.x, 0, 0));

    if ((*event).keyboard.keycode==ALLEGRO_KEY_A) (*duck).x -= PADDLE_MOVE;
    if ((*event).keyboard.keycode==ALLEGRO_KEY_D) (*duck).x += PADDLE_MOVE;

    /* make sure the paddles don go off screen */

    if ((*duck).x < 0)        (*duck).x = 0;
    if ((*duck).x > 980)       (*duck).x = 980;
}
