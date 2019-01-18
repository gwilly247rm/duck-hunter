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

int main()
{
    //�e(��) ��(��)
    int display_wid=1080;//�ù��e
    int display_len=740;//��

    int dog_wid=90;//���e
    int dog_len=70;//��

    int duck_wid=100;//���e
    int duck_len=80;//��

    int shit_wid=40;//�˼e
    int shit_len=40;//��

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT *events = NULL;

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(9);
    al_init_font_addon();
    al_init_ttf_addon();

    timer = al_create_timer(0. 01 );
    display = al_create_display(display_wid, display_len);
    srand( time( NULL ) );

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());    /* register keyboard to event queue */
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    int run=1; //����0�������C���õ����{��
    int mode=1; //�C���e��(1:�C����� 2:�C���i�� 3:��J�m�W 4:��ܱƦ�]
    int dog_amount=5;
    int shit_amount=5;
    int dog_killed=0;
    int i=0;

    object duck;
    object DOG[dog_amount];
    object SHIT[shit_amount];

    duck.bmp=al_load_bitmap("duck.png");
    duck.kind=1;
    duck.x=display_wid/2;
    duck.y=display_len-60-80;
    duck.direction=0;
    duck.speed=1;
    duck.change_dir=0;
    duck.hp=3;

    if(i=0;i<=dog_amount-1;i++){
        DOG[i].bmp=al_load_bitmap("dog.png");
        DOG[i].kind=0;
        DOG[i].x=0;
        DOG[i].y=0;
        DOG[i].direction=0;
        DOG[i].speed=1;
        DOG[i].change_dir=0;
        DOG[i].hp=0;
    }

    if(i=0;i<=shit_amount-1;i++){
        SHIT[i].bmp=al_load_bitmap("shit.png");
        SHIT[i].kind=0;
        SHIT[i].x=0;
        SHIT[i].y=0;
        SHIT[i].direction=0;
        SHIT[i].speed=1;
        SHIT[i].change_dir=0;
        SHIT[i].hp=0;
    }

    int game_start=1;

    while(run){

        while(mode==1){//�C�����
        }
/********************************************************************************************************************************/
        while(mode==2){//�C���i��

            if(game_start==1){//�C���}�l�A��lHP
                duck.hp=3;
                game_start=0;
            }

            if (!al_is_event_queue_empty(event_queue)) {
                AttackJudgeShit(&duck, SHIT);
                MoveDog(DOG, &display_wid, &display_len);

                while (al_get_next_event(event_queue, events)) {
                    switch (*events.type) {
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        run = 0;
                        break;

                    case ALLEGRO_EVENT_KEY_DOWN:
                        if(*events.keyboard.keycode == ALLEGRO_KEY_ESCAPE){run = 0;}
                        MoveDuck(events, &duck, &display_wid);
                        break;

                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                        if(*events.mouse.buttom==1){
                            AttackJudgeBullet(events, DOG, &dog_killed);
                        }
                        break;
                    }
                        break;
                }
            }

            al_draw_bitmap(duck.bmp, duck.x, duck.y, 0);
            for(i=0;i<=dog_amount-1;i++){
                if(DOG[i].kind!=0){
                    al_draw_bitmap(DOG[i].bmp, DOG[i].x, DOG[i].y, 0);
                }
            }
            for(i=0;i<=shit_amount-1;i++){
                if(SHIT[i].kind!=0){
                    al_draw_bitmap(SHIT[i].bmp, SHIT[i].x, SHIT[i].y, 0);
                }
            }
            al_flip_display(display);

            if(duck.hp<=0){
                mode=3;
                break;
            }
        }
/********************************************************************************************************************************/
        while(mode==3){//��J�m�W
        }
/********************************************************************************************************************************/
        while(mode==4){//��ܱƦ�]
        }
    }

    al_destroy_display(display);
    al_destroy_bitmap(duck.bmp);
    for(i=0;i<=dog_amount-1;i++){
    al_destroy_bitmap(DOG[i].bmp);}
    for(i=0;i<=shit_amount-1;i++){
    al_destroy_bitmap(SHIT[i].bmp);}
    al_destroy_font( pongfont );
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return 0;
}
