/* 
 * File:   main.c
 * Author: Awasa
 * Created on 28 de noviembre de 2018, 17:13
 */
//#define ALLE
#ifdef ALLE
#include "init_game.h"
#include "menus.h"
#include "admin_game.h"
#endif

#ifdef RPI
#include "rpi_logic.h"
#endif


int main(int argc, char** argv) 
{
#ifdef ALLE
    FILE *options_files;
    FILE *best_scores;
    
    ALLEGRO_DISPLAY *snake_game =  NULL;   //declaro el display
    ALLEGRO_FONT *font0 = NULL, *font1 = NULL, *font2 = NULL;  //declaro la fuente
    ALLEGRO_EVENT_QUEUE *event = NULL;
    
    uint32_t do_exit;
    
    if(!init_allegro() && !create_intro(snake_game,font0,font1,font2))      //Inicializa los servicios de allegro
    {                       //Crea el display, el logo y la presentacion
        do
        {
            if(!(create_menu(snake_game,font0,font1,font2,event,options_files,best_scores) == GAME_EXIT))
            {   
                do_exit = admin_game(options_files,best_scores,event);
            }
            else
            {
                do_exit = QUIT_GAME;
            }
        }
        while (do_exit != QUIT_GAME); 
    }
    
    al_destroy_display (snake_game);
    al_destroy_font (font0);
    al_destroy_font (font1);
    al_destroy_font (font2);
    //al_destroy_event_queue (event);
    return (EXIT_SUCCESS);
    
#endif
    
#ifdef RPI
         admin_rpi();
        
	return 0;
#endif
}

