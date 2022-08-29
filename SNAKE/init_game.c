/* 
 * File:   init_game.c
 * Author: Awasa
 * Created on 28 de noviembre de 2018, 17:28
 */

#include "init_game.h"
#include "output.h"
#include "input.h"
#include "file_admin.h"

static uint8_t  create_display  (ALLEGRO_DISPLAY *);    //Esta funcion inicia exclusivamente el display

uint8_t init_allegro (void)
{
    //Declaro todos los servicios de allegro que utilizare en el juego como la fuente,
    //el sistema de imagen,sonido y primitivas,teclado, e inicializo allegro
    
    if(!al_init()) //Inicializo allegro 
    {
        fprintf(stderr, "Fallo el inicio de allegro \n"); //Mensaje de error al usuario
        al_uninstall_system();  //"apaga allegro"
        return 1;   //Condicion de salida con error
    }
    else if(!al_init_image_addon()) //inicializo el sistema de imagen
    {
        fprintf(stderr,"Creacion de sistema de imagen erronea \n");  ///Mensaje de error al usuario
        al_uninstall_system();  //"apaga" allegro
        al_shutdown_image_addon;    //Destruye el sistema de imagen
        return 1;  //Condicion de salida con error
    }
    else if(!al_install_keyboard()) 
    {
        fprintf(stderr, "Fallo el inicio del teclado \n");
        al_uninstall_system();  //"apaga" allegro
        al_shutdown_image_addon;    //Destruye el sistema de imagen
        return 1;
    }
    else if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Fallo el inicio de las primitivas \n");
        al_uninstall_system();  //"apaga" allegro
        al_shutdown_image_addon;    //Destruye el sistema de imagen
        return 1;
    }
    else if(!al_install_audio())
    {
      fprintf(stderr, "failed to initialize audio!\n");
      return 1;
    }
   if(!al_init_acodec_addon())
    {
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return 1;
    }
 
   if (!al_reserve_samples(1))
    {
      fprintf(stderr, "failed to reserve samples!\n");
      return 1;
    }
    
    al_init_font_addon();   //Inicializo el sistema para la fuente
    al_init_ttf_addon();    //Inicializo el "true type font" 
    
    return 0;    //Ejecucion exitosa de la funcion
}


uint8_t create_intro (ALLEGRO_DISPLAY *display, ALLEGRO_FONT *titulo, ALLEGRO_FONT *subtitulo, ALLEGRO_FONT *mensaje)
{
    ALLEGRO_BITMAP  *logo = NULL;       //declaro el bitmap logo
    
    //Creo el diseño del logo del juego
    if (create_display(display))
    {
        al_destroy_bitmap(logo);
        return 1;
    }  
    if(!(logo = al_load_bitmap ("itba_logo2.jpg")))
    {
        fprintf(stderr,"Creacion de logo erronea \n");  ///Mensaje de error al usuario
        al_destroy_bitmap(logo);    //destruye el bitmap del logo
        al_destroy_display(display);    //Destruye el display
        return 1;  //Condicion de salida con error
    }
    else if((!(titulo = al_load_ttf_font("ComfortaaBold.ttf",60,0 ))) || \
            (!(subtitulo = al_load_ttf_font("CCKeni.ttf",30,0))) || \
            (!(mensaje = al_load_ttf_font("Spongeboy.ttf",10,0))))  //Elijo la fuente deseada
    {
        fprintf(stderr,"Creacion de fuente erronea \n");
        al_destroy_bitmap(logo);    //destruye el bitmap del logo
        al_destroy_display(display);    //Destruye el display
        al_destroy_font(titulo);
        return 1;
    }
        
    display_logo (logo,mensaje,DISPLAY_W,DISPLAY_H); //Llamo a la funcion que muestra un bitmap y texto en el display
    wait_for_key(ALLEGRO_KEY_SPACE);
    display_info (logo,titulo,subtitulo,mensaje,DISPLAY_W,DISPLAY_H);
    wait_for_key(ALLEGRO_KEY_SPACE);
    
    al_destroy_bitmap (logo);
    return 0;   //Ejecucion exitosa de la funcion  
}


static uint8_t create_display (ALLEGRO_DISPLAY *display)
{
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    if (!(display = al_create_display (DISPLAY_W, DISPLAY_H))) //Creo el display con medidas "DISPLAY_W" y "DISPLAY_H"
    {
        fprintf (stderr, "Creacion de display erronea \n");    //Mensaje de error al usuario
        al_destroy_display(display);  //destruye el display
        return 1;      //Condicion de salida con error
    }
    return 0;   //Ejecucion exitosa de la funcion
}