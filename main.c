#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"
#include "struct.h"

/* symbolic constants for the DOG’s possible directions */
#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3
#define PADDLE_MOVE 10

int main()
{
    //寬(橫) 長(直)
    int display_wid=1080;//螢幕寬
    int display_len=740;//長

    int DOG_wid=90;//狗寬
    int DOG_len=70;//長

    int duck_wid=100;//狗寬
    int duck_len=80;//長

    int shit_wid=40;//屎寬
    int shit_len=40;//長

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT events;
    ALLEGRO_KEYBOARD_STATE KBstate;

    /***/
    ALLEGRO_BITMAP* windows = NULL;
    ALLEGRO_BITMAP* B_start = NULL;
    ALLEGRO_BITMAP* B_explain = NULL;
    ALLEGRO_BITMAP* B_ranking = NULL;
    ALLEGRO_BITMAP* B_back = NULL;
    ALLEGRO_BITMAP* B_exit = NULL;
    ALLEGRO_BITMAP* P_explain = NULL;
    ALLEGRO_BITMAP* P_ranking = NULL;

    ALLEGRO_BITMAP* background = NULL;

    /*DOG and duck*/
    ALLEGRO_BITMAP *DOG1 = NULL; /* pointer to the DOG's image bitmap */
    ALLEGRO_BITMAP *DOG2 = NULL;
    ALLEGRO_BITMAP *DOG3 = NULL;
    ALLEGRO_BITMAP *DOG4 = NULL;
    ALLEGRO_BITMAP *DOG5 = NULL;
    ALLEGRO_BITMAP *DOG11 = NULL; /* pointer to the DOG's image bitmap */
    ALLEGRO_BITMAP *DOG12 = NULL;
    ALLEGRO_BITMAP *DOG13 = NULL;
    ALLEGRO_BITMAP *DOG14 = NULL;
    ALLEGRO_BITMAP *DOG15 = NULL;
    ALLEGRO_BITMAP *duck1 = NULL;
    ALLEGRO_BITMAP *duck2 = NULL;
    ALLEGRO_BITMAP *duck3 = NULL;

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(9);
    al_init_font_addon();
    al_init_ttf_addon();



    timer = al_create_timer(0.01);
    display = al_create_display(display_wid, display_len);
    srand( time( NULL ) );
    ALLEGRO_MOUSE_STATE MSstate;

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());    /* register keyboard to event queue */
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    int run=1; //等於0時關掉遊戲並結束程式
    int mode=1; //遊戲畫面(1:遊戲選單 2:遊戲進行 3:輸入姓名 4:顯示排行榜5.操作說明
    int DOG_amount=5;
    int shit_amount=5;
    int DOG_killed=0;
    int i=0;
    int x=0;
    int y=0;
    int xr=1000,yr=1000;
    /********************************/
    windows = al_load_bitmap("Window2.png");
    B_start = al_load_bitmap("B_Start.png");
    B_ranking = al_load_bitmap("B_ranking.png");
    B_explain = al_load_bitmap("B_explain.png");
    B_exit = al_load_bitmap("B_exit.png");
    P_ranking = al_load_bitmap("P_ranking.png");
    B_back = al_load_bitmap("B_back.png");
    P_explain = al_load_bitmap("P_explain.png");

    /*******************************/
    DOG1 = al_load_bitmap( "DOG1.png"); /* load the DOG bitmap */
    DOG2 = al_load_bitmap( "DOG2.png");
    DOG3 = al_load_bitmap( "DOG3.png");
    DOG4 = al_load_bitmap( "DOG4.png");
    DOG5 = al_load_bitmap( "DOG5.png");
    DOG11 = al_load_bitmap( "DOG11.png"); /* load the DOG bitmap */
    DOG12 = al_load_bitmap( "DOG12.png");
    DOG13 = al_load_bitmap( "DOG13.png");
    DOG14 = al_load_bitmap( "DOG14.png");
    DOG15 = al_load_bitmap( "DOG15.png");

    duck1 = al_load_bitmap( "duck1.png");
    duck2 = al_load_bitmap( "duck2.png");
    duck3 = al_load_bitmap( "duck3.png");

    object duck;
    object DOG[DOG_amount];
    object SHIT[shit_amount];

    duck.bmp=al_load_bitmap("duck.png");
    duck.kind=1;
    duck.x=display_wid/2;
    duck.y=display_len-60-80;
    duck.direction=0;
    duck.speed=1;
    duck.change_dir=0;
    duck.hp=3;

    for(i=0;i<=DOG_amount-1;i++){
        DOG[i].bmp=al_load_bitmap("DOG.png");
        DOG[i].kind=0;
        DOG[i].x=0;
        DOG[i].y=0;
        DOG[i].direction=0;
        DOG[i].speed=1;
        DOG[i].change_dir=0;
        DOG[i].hp=0;
    }

    for(i=0;i<=shit_amount-1;i++){
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

        while(mode==1){//遊戲選單

        x=0;
        y=0;
        xr=1000,yr=1000;

        al_draw_bitmap(windows, 0, 0, 0);
        al_draw_bitmap(B_start, 430, 360, 0);
        al_draw_bitmap( B_ranking, 430, 440, 0);
        al_draw_bitmap(B_explain, 430, 520, 0);
        al_draw_bitmap(B_exit, 430, 600, 0);

        al_flip_display();

        al_get_mouse_state(&MSstate);
            if(al_mouse_button_down(&MSstate,1))

            {
                x=al_get_mouse_state_axis(&MSstate,0);
                y=al_get_mouse_state_axis(&MSstate,1);

            }

            while(1)
            {
                al_get_mouse_state(&MSstate);

                if(al_mouse_button_down(&MSstate,1)==0)
                {
                    xr=al_get_mouse_state_axis(&MSstate,0);
                    yr=al_get_mouse_state_axis(&MSstate,1);
                    break;
                }

            }
            if(x>=430&&y>=360&&x<=650&&y<=420){//選項框:開始
                mode=2;
                break;
            }
            if(x>=430&&y>=440&&x<=650&&y<=500)//排行
            {
                mode=4;
                printf("排行\n");
                x=0;
                y=0;
                xr=1000,yr=1000;

                al_draw_bitmap( P_ranking, 140, 70, 0);
                al_draw_bitmap( B_back, 430, 610, 0);
                al_flip_display();



                break;
            }//排行
            if(x>=430&&y>=520&&x<=650&&y<=580)
            {
                mode=5;
                printf("operate explaining\n");
                x=0;
                y=0;
                xr=1000,yr=1000;
                al_draw_bitmap( P_explain, 140, 70, 0);
                al_draw_bitmap( B_back, 430, 610, 0);
                al_flip_display();
                break;
            }//選項框:操作說明
            if(x>=430&&y>=600&&x<=650&&y<=660)
            {
                run=0;
                break;
            }//退出

        }

/********************************************************************************************************************************/
        while(mode==2){//遊戲進行

            if(game_start==1){//遊戲開始，初始HP
                duck.hp=3;
                game_start=0;

            if (!al_is_event_queue_empty(event_queue))
            {
                AttackJudgeShit(&duck, SHIT);
                moveDOG(DOG);

                while (al_get_next_event(event_queue, &events))
                {
                    switch (events.type)
                    {
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        run = 0;
                        break;

                    case ALLEGRO_EVENT_KEY_DOWN:
                        if(events.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                        {
                            run = 0;
                        }
                        moveduck(events, &duck);
                        break;

                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                        if(events.mouse.button==1)
                        {
                            AttackJudgeBullet(events,DOG, &DOG_killed);
                        }
                        break;
                    }
                    break;
                }
            }

            /*DOG and duck move*/

                for(i=0; i<5; i++)
                {
                    DOG[i].x = display_wid / 2; /* give the DOG its initial x-coordinate */
                    DOG[i].y = display_len / 2; /* give the DOG its initial y-coordinate */
                    DOG[i].direction = rand() % 4; /* and then make a random initial direction */
                }
                srand( time( NULL ) ); /* seed the random function */

                background = al_load_bitmap("fon.png");

                al_draw_bitmap(background, 0, 0, 0);

                int x_dd=1;
                int y_dd=1;

                int a_dd;
                int b_dd;

                moveduck(events,&duck); /* move the paddles */printf("1");
                if (al_key_down(&KBstate, ALLEGRO_KEY_A))
                {
                    al_draw_bitmap( duck2, duck.x, 600, 0);/* draw the bitmap */
                }
                else if (al_key_down(&KBstate, ALLEGRO_KEY_D))
                {
                    al_draw_bitmap( duck1, duck.x, 600, 0);/* draw the bitmap */
                }
                else
                    al_draw_bitmap( duck3, duck.x, 600, 0);
printf("1");

                if (al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE))
                    break;

                for(i=0; i<5; i++)
                {
                    moveDOG(DOG);
                } /* move the DOG */

                for(i=0; i<5; i++)
                {
                    if(DOG[i].direction==0||DOG[i].direction==1)
                    {
                        if(x>0&&x<=50)
                            al_draw_bitmap( DOG1, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */
                        else if(x>50&&x<=100)
                            al_draw_bitmap( DOG2, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */
                        else if(x>100&&x<=150)
                            al_draw_bitmap( DOG3, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */
                        else if(x>150&&x<=200)
                            al_draw_bitmap( DOG4, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */
                        else if(x>200&&x<=250)
                            al_draw_bitmap( DOG5, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */

                        x=x+1;
                        if(x==251)
                            x=1;
                    }
                }

                for(i=0; i<5; i++)
                {
                    if(DOG[i].direction==2||DOG[i].direction==3)
                    {
                        if(y>0&&y<=50)
                            al_draw_bitmap( DOG11, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */
                        else if(y>50&&y<=100)
                            al_draw_bitmap( DOG12, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */
                        else if(y>100&&y<=150)
                            al_draw_bitmap( DOG13, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */
                        else if(y>150&&y<=200)
                            al_draw_bitmap( DOG14, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */
                        else if(y>200&&y<=250)
                        al_draw_bitmap( DOG15, DOG[i].x, DOG[i].y, 0);/* draw the bitmap */

                        y=y+1;
                        if(y==251)
                            y=1;
                    }
                }

                a_dd = rand() % 1200+1;

                for(i=0; i<5; i++)
                {
                    if(a_dd<20 && b_dd%8==0)
                    {
                        if ( DOG[i].direction == DOWN_RIGHT )
                            DOG[i].direction = UP_LEFT;
                        else if ( DOG[i].direction == DOWN_LEFT )
                            DOG[i].direction = UP_RIGHT;
                        else if ( DOG[i].direction == UP_RIGHT )
                            DOG[i].direction = DOWN_LEFT;
                        else if ( DOG[i].direction == UP_LEFT )
                            DOG[i].direction = DOWN_RIGHT;
                    }
                    b_dd=b_dd+1;
                }

                al_rest(0.003);


            /*********************************/
            al_draw_bitmap(duck.bmp, duck.x, duck.y, 0);
            for(i=0;i<=DOG_amount-1;i++){
                if(DOG[i].kind!=0){
                    al_draw_bitmap(DOG[i].bmp, DOG[i].x, DOG[i].y, 0);
                }
            }
            for(i=0;i<=shit_amount-1;i++){
                if(SHIT[i].kind!=0){
                    al_draw_bitmap(SHIT[i].bmp, SHIT[i].x, SHIT[i].y, 0);
                }
            }
            al_flip_display();

            if(duck.hp<=0){
                mode=3;
                break;
            }
        }
        }
/********************************************************************************************************************************/
        while(mode==3){//輸入姓名
        }
/********************************************************************************************************************************/
        while(mode==4){//顯示排行榜

            al_get_mouse_state(&MSstate);
            if(al_mouse_button_down(&MSstate,1)==1)
            {
                x=al_get_mouse_state_axis(&MSstate,0);
                y=al_get_mouse_state_axis(&MSstate,1);

            }

            while(1)
            {
                al_get_mouse_state(&MSstate);
                al_rest(0.01);
                if(al_mouse_button_down(&MSstate,1)==0)
                {
                    xr=al_get_mouse_state_axis(&MSstate,0);
                    yr=al_get_mouse_state_axis(&MSstate,1);
                    break;
                }

            }
            if(x>=430&&y>=610&&x<=650&&y<=670)
            {
                mode=1;
                break;
        }
    }

/**********************************************************************/

        while(mode==5){//操作說明

            al_get_mouse_state(&MSstate);
            if(al_mouse_button_down(&MSstate,1)==1)
            {
                x=al_get_mouse_state_axis(&MSstate,0);
                y=al_get_mouse_state_axis(&MSstate,1);

            }

            while(1)
            {
                al_get_mouse_state(&MSstate);
                al_rest(0.01);
                if(al_mouse_button_down(&MSstate,1)==0)
                {
                    xr=al_get_mouse_state_axis(&MSstate,0);
                    yr=al_get_mouse_state_axis(&MSstate,1);
                    break;
                }

            }
            if(x>=430&&y>=610&&x<=650&&y<=670)
            {
                mode=1;
                break;
        }
    }
    }

   /***************************************/
    al_destroy_display(display);
    al_destroy_bitmap(duck.bmp);
    al_destroy_bitmap(windows);
    al_destroy_bitmap(B_start);
    al_destroy_bitmap(B_ranking);
    al_destroy_bitmap(B_explain);
    al_destroy_bitmap(B_exit);
    al_destroy_bitmap(P_ranking);
    al_destroy_bitmap(P_explain);

    /*************************************/
    al_destroy_bitmap(DOG1); /* destroy the DOG bitmap */
    al_destroy_bitmap(DOG2);
    al_destroy_bitmap(DOG3);
    al_destroy_bitmap(DOG4);
    al_destroy_bitmap(DOG5);
    al_destroy_bitmap(DOG11); /* destroy the DOG bitmap */
    al_destroy_bitmap(DOG12);
    al_destroy_bitmap(DOG13);
    al_destroy_bitmap(DOG14);
    al_destroy_bitmap(DOG15);
    al_destroy_bitmap(duck1);
    al_destroy_bitmap(duck2);
    al_destroy_bitmap(duck3);

    for(i=0;i<=DOG_amount-1;i++){
    al_destroy_bitmap(DOG[i].bmp);}
    for(i=0;i<=shit_amount-1;i++){
    al_destroy_bitmap(SHIT[i].bmp);}
    al_destroy_font( font );
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return 0;
}
