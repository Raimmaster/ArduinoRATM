#include <iostream>

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_primitives.h>
using namespace std;

/**
    Inicialización de las funciones de Allegro
**/

const float FPS = 60;
const int SCREEN_W = 720;
const int SCREEN_H = 640;
int BOUNCER_SIZE_W = 32;
int BOUNCER_SIZE_H = 32;

int main()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    /*float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE_W / 2.0;
    float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE_H / 2.0;
    float bouncer_dx = -4.0, bouncer_dy = 4.0;*/
    bool redraw = true;
    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if(!al_init_primitives_addon())
        return -1;

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    al_set_target_bitmap(al_get_backbuffer(display));

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0,0,0));

    ALLEGRO_COLOR color_blue = al_map_rgb(0, 128, 255);
    float widt = 300;
    al_flip_display();

    al_start_timer(timer);

    //rect_1
    float pos_x1 = 50, pos_y1 = 40;
    float pos_x2 = 50, pos_y2 = 45;//fin_x2 = 250, 1.1 fin_x2 = 500
    //rect_2
    float pos_x3 = 249, pos_y3 = 40;
    float pos_x4 = 255, pos_y4 = 40;//fin_y4 = 300, 2.2 fin_y4 = 320

    //rect_3
    float pos_x5 = 249, pos_y5 = 299;
    float pos_x6 = 249, pos_y6 = 305;
    //rect_4
    float pos_x7 = 269, pos_y7 = 269;
    float pos_x8 = 269, pos_y8 = 275;

    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;


            if(widt < 500)
                al_draw_filled_rectangle(50, 20, widt++, 25, color_blue);

            al_draw_filled_rectangle(499, 20, 505, 45, color_blue);

            if(widt > 350){
                if(pos_x2 < 250)
                    al_draw_filled_rectangle(pos_x1, pos_y1, pos_x2++, pos_y2, color_blue);//rect_1
            }

            if(pos_x2 >= 250){
                if(pos_x1 < 270){
                    pos_x1 = 270;
                    pos_x2 = pos_x1;
                }
                if(pos_x2 < 500)
                        al_draw_filled_rectangle(pos_x1, pos_y1, pos_x2++, pos_y2, color_blue);//rect_1.1

                if(pos_y4 < 300){
                    al_draw_filled_rectangle(pos_x3, pos_y3, pos_x4, pos_y4++, color_blue);//rect_2
                    std::cout<<"X: "<<pos_x3<<" Y: "<<pos_y4<<std::endl;
                    if(pos_y4 < 270)
                        al_draw_filled_rectangle(pos_x3 + 20, pos_y3, pos_x4 + 20, pos_y4, color_blue);//rect_2.2
                }
            }

            if(pos_y4 == 300){
                if(pos_x6 < 650){
                    al_draw_filled_rectangle(pos_x5, pos_y5, pos_x6++, pos_y6, color_blue);//rect_3
                }
                if(pos_x8 < 650)
                    al_draw_filled_rectangle(pos_x7, pos_y7, pos_x8++, pos_y8, color_blue);//rect_4
            }
            al_flip_display();
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}

/**
    Una clase para el Path (el arreglo para ir appending las coordenadas).
    {
        funciones:
            append(), remove(), insert(), draw(), clear();
    }
    Tener un path loader, del archivo que creó el Arduino del laberinto.

    Un struct para coordenadas.
    Constante para el width del rectángulo a dibujar.
**/
