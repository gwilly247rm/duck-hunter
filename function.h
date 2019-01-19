#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

//void MoveDog(object *DOG, int *width, int *length);
void MoveShit(object *SHIT, int *ground);
void AttackJudgeBullet(ALLEGRO_EVENT event, object *dog, int *dog_killed);
void AttackJudgeShit(object *duck, object *SHIT);
//void MoveDuck(ALLEGRO_EVENT *event, object *duck, int *width);
void DogAttack(object *DOG, object *SHIT);
void moveDOG(object*DOG);
void reverseVerticalDirection(object*DOG);
void reverseHorizontalDirection(object*DOG);
void moveduck(ALLEGRO_EVENT event,object*duck);

#endif
