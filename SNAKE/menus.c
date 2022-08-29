/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menus.c
 * Author: gonza
 * 
 * Created on 15 de diciembre de 2018, 13:25
 */

#include "menus.h"
#include "output.h"
#include "input.h"
#include "file_admin.h"

static uint32_t  admin_menu         (ALLEGRO_BITMAP *,ALLEGRO_FONT *,ALLEGRO_FONT*, ALLEGRO_FONT *,ALLEGRO_EVENT_QUEUE *, FILE *, FILE *);
static void      move_menu_pointer  (uint16_t *, uint16_t *, uint16_t *, uint32_t);
static uint32_t  admin_submenu      (ALLEGRO_FONT *, ALLEGRO_FONT *, ALLEGRO_FONT *,ALLEGRO_EVENT_QUEUE *, FILE *, FILE *,uint16_t *);
static uint8_t   create_best_score  (ALLEGRO_FONT *, ALLEGRO_FONT *, ALLEGRO_FONT *, FILE *);
static uint8_t   create_options     (ALLEGRO_FONT *, ALLEGRO_FONT *, ALLEGRO_FONT *, ALLEGRO_EVENT_QUEUE *, FILE *);
static uint8_t   admin_options      (ALLEGRO_BITMAP *, ALLEGRO_FONT *, ALLEGRO_FONT *, ALLEGRO_FONT *, ALLEGRO_EVENT_QUEUE *, FILE *);
static void      set_options        (uint16_t *, FILE *);
static void      switch_music       (FILE *);
static void      switch_level       (FILE *);
static void      switch_resolution  (FILE *);
static void      switch_snake_color (FILE *);
static uint8_t   check_exit         (ALLEGRO_EVENT_QUEUE *, ALLEGRO_FONT *);


uint8_t create_menu (ALLEGRO_DISPLAY *display, ALLEGRO_FONT *titulo, \
                     ALLEGRO_FONT *opciones, ALLEGRO_FONT *mensaje, ALLEGRO_EVENT_QUEUE *event_queue, \
                     FILE *options_file, FILE *best_scores)
{
    ALLEGRO_BITMAP *menu = NULL;
    uint32_t exit_type;
    
    if(!(menu = al_load_bitmap ("menu3.png")))
    {
        fprintf(stderr,"Creacion de logo erronea \n");  ///Mensaje de error al usuario
        al_destroy_bitmap(menu);    //destruye el bitmap del logo
        al_destroy_display(display);    //Destruye el display
        al_destroy_font(titulo);
        al_destroy_font(opciones);
        al_destroy_event_queue(event_queue);
        return 1;  //Condicion de salida con error
    }
    else if((!(titulo = al_load_ttf_font("Turtles.otf",60,0 ))) || \
            (!(opciones = al_load_ttf_font("SuperMario256.ttf",30,0))))  //Elijo la fuente deseada
    {
        fprintf(stderr,"Creacion de fuente erronea \n");
        al_destroy_bitmap(menu);    //destruye el bitmap del logo
        al_destroy_display(display);    //Destruye el display
        al_destroy_font(titulo);
        al_destroy_font(opciones);
        al_destroy_event_queue(event_queue);
        return 1;
    }                 

    display_menu(menu, titulo, opciones, DISPLAY_W, DISPLAY_H,TRIAN_POINT_X1,TRIAN_POINT_Y1,TRIAN_POINT_X2,TRIAN_POINT_Y2,TRIAN_POINT_X3,TRIAN_POINT_Y3);
    exit_type = admin_menu(menu, titulo, opciones, mensaje, event_queue, options_file, best_scores);
    
    al_destroy_bitmap (menu);
    return (exit_type);
}

static uint32_t admin_menu (ALLEGRO_BITMAP *menu, ALLEGRO_FONT *titulo,ALLEGRO_FONT *opciones, ALLEGRO_FONT *mensaje, ALLEGRO_EVENT_QUEUE *event_queue, FILE *options_file, FILE *best_scores)
{
    uint32_t key;
    uint16_t x1 = TRIAN_POINT_X1, y1 = TRIAN_POINT_Y1; 
    uint16_t x2 = TRIAN_POINT_X2, y2 = TRIAN_POINT_Y2;
    uint16_t x3 = TRIAN_POINT_X3, y3 = TRIAN_POINT_Y3;
   
    if (!(event_queue = al_create_event_queue()))
    {
        fprintf(stderr, "Creacion de fila de eventos fallida \n");
        al_destroy_event_queue(event_queue);
        return 1;
    }
    do
    {
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        key = get_keyboard (event_queue);
        switch (key)
        {
            case (ALLEGRO_KEY_DOWN):
                move_menu_pointer (&y1,&y2,&y3,key);
                display_menu(menu, titulo, opciones, DISPLAY_W, DISPLAY_H,x1,y1,x2,y2,x3,y3);
                break;
            case (ALLEGRO_KEY_UP):
                move_menu_pointer (&y1,&y2,&y3,key);
                display_menu(menu, titulo, opciones, DISPLAY_W, DISPLAY_H,x1,y1,x2,y2,x3,y3);
                break; 
            case (ALLEGRO_KEY_ENTER):
                key = admin_submenu (titulo,opciones,mensaje,event_queue,options_file,best_scores,&y1);
                al_unregister_event_source(event_queue, al_get_keyboard_event_source());
                break;
            default:
                display_menu(menu, titulo, opciones, DISPLAY_W, DISPLAY_H,x1,y1,x2,y2,x3,y3);
                break;    
        }
    }
    while (key != LOOP_EXIT && key != GAME_EXIT); 
    
    return key;
}

static void move_menu_pointer (uint16_t *y1, uint16_t *y2, uint16_t *y3, uint32_t key)
{
    if (key == ALLEGRO_KEY_UP && *y1 != TRIAN_POINT_Y1)
    {
        *y1 -= LINE_DISTANCE;
        *y2 -= LINE_DISTANCE;
        *y3 -= LINE_DISTANCE;
    }
    else if (key == ALLEGRO_KEY_DOWN && *y1 != TRIAN_POINT_Y1_EXT_DOWN)
    {
        *y1 += LINE_DISTANCE;
        *y2 += LINE_DISTANCE;
        *y3 += LINE_DISTANCE;
    }   
}

static uint32_t admin_submenu (ALLEGRO_FONT *titulo, ALLEGRO_FONT *opciones, ALLEGRO_FONT *mensaje, ALLEGRO_EVENT_QUEUE *event, FILE *options_files, FILE *best_scores, uint16_t *y_pos)
{
        if (*y_pos == TRIAN_POINT_Y1)
        {
            return (LOOP_EXIT);
        }
        else if (*y_pos == TRIAN_POINT_Y1_ONE_STEP)
        {
            if(create_best_score(titulo,opciones,mensaje,best_scores))
            {
                return(GAME_EXIT);
            }     
        }
        else if (*y_pos == TRIAN_POINT_Y1_TWO_STEP)
        {
            if(create_options(titulo,opciones,mensaje,event,options_files))
            {
                return(GAME_EXIT);
            }
        }
        else if (*y_pos == TRIAN_POINT_Y1_EXT_DOWN)
        {
            if(check_exit (event,opciones))
            {
                return (GAME_EXIT);
            }
            else
            {
                return (ANY_KEY);
            }
        }   
}

static uint8_t create_best_score(ALLEGRO_FONT *titulo, ALLEGRO_FONT *opciones, ALLEGRO_FONT *mensaje, FILE *best_scores)
{ 
    ALLEGRO_BITMAP *scores = NULL;
    uint8_t first_pos[MAX_LENGHT], second_pos[MAX_LENGHT], third_pos[MAX_LENGHT];
    
    if(!(scores = al_load_bitmap ("trofeo.jpg")))
    {
        fprintf(stderr,"Creacion de logo erronea \n");  ///Mensaje de error al usuario
        al_destroy_bitmap(scores);    //destruye el bitmap del logo
        return 1;  //Condicion de salida con error
    }
    else if((!(titulo = al_load_ttf_font("Turtles.otf",60,0 ))) || \
            (!(opciones = al_load_ttf_font("SuperMario256.ttf",30,0))) || \
            (!(mensaje = al_load_ttf_font("Spongeboy.ttf",10,0))))  //Elijo la fuente deseada
    {
        fprintf(stderr,"Creacion de fuente erronea \n");
        al_destroy_bitmap(scores);    //destruye el bitmap del logo
        return 1;
    }
    else if ((!read_config ("best_score1.txt",best_scores,first_pos)) || (!read_config("best_score2.txt",best_scores,second_pos)) || (!read_config ("best_score3.txt",best_scores,third_pos)))
    {
        fprintf (stderr,"Archivo de puntuacion inexistente/corrupto");
        return 1;
    }
    
    display_best_score (scores, titulo, opciones, mensaje, DISPLAY_W, DISPLAY_H, first_pos, second_pos, third_pos);
    wait_for_key(ALLEGRO_KEY_ESCAPE);

    al_destroy_bitmap(scores);
    return 0;
}

static uint8_t create_options(ALLEGRO_FONT *titulo, ALLEGRO_FONT *opciones, ALLEGRO_FONT *mensaje, ALLEGRO_EVENT_QUEUE *event_queue, FILE *options_files)
{ 
    ALLEGRO_BITMAP *options = NULL;
    uint8_t  music[MAX_LENGHT], level[MAX_LENGHT], resolution[MAX_LENGHT], snake_color[MAX_LENGHT];
    
    if(!(options = al_load_bitmap ("engranajes.jpg")))
    {
        fprintf(stderr,"Creacion de logo erronea \n");  ///Mensaje de error al usuario
        al_destroy_bitmap(options);    //destruye el bitmap del logo
        return 1;  //Condicion de salida con error
    }
    else if((!(titulo = al_load_ttf_font("Turtles.otf",60,0 ))) || \
            (!(opciones = al_load_ttf_font("SuperMario256.ttf",30,0)))  || \
            (!(mensaje = al_load_ttf_font("Spongeboy.ttf",10,0))))  //Elijo la fuente deseada
    {
        fprintf(stderr,"Creacion de fuente erronea \n");
        al_destroy_bitmap(options);    //destruye el bitmap del logo
        return 1;
    }
    else if ((!read_config (FILE_MUSIC,options_files,music)) || (!read_config(FILE_LEVEL,options_files,level)) || (!read_config ("resolution.txt",options_files,resolution)) || (!read_config ("snake_color.txt",options_files,snake_color)))
    {
        fprintf (stderr,"Archivo de configuracion inexistente/corrupto");
        return 1;
    }
    
    display_options(options, titulo, opciones, mensaje, DISPLAY_W, DISPLAY_H,TRIAN_POINT_X1B,TRIAN_POINT_Y1,TRIAN_POINT_X2B,TRIAN_POINT_Y2,TRIAN_POINT_X3B,TRIAN_POINT_Y3,music,level,resolution,snake_color);
    if (admin_options(options,titulo,opciones,mensaje,event_queue,options_files))
    {
        return 1;
    }
    
    return 0;
}


static uint8_t admin_options(ALLEGRO_BITMAP *options,ALLEGRO_FONT *titulo, ALLEGRO_FONT *opciones, ALLEGRO_FONT *mensaje, ALLEGRO_EVENT_QUEUE *event_queue, FILE *options_file)
{
    uint32_t key;
    uint16_t x1 = TRIAN_POINT_X1B, y1 = TRIAN_POINT_Y1;
    uint16_t x2 = TRIAN_POINT_X2B, y2 = TRIAN_POINT_Y2;
    uint16_t x3 = TRIAN_POINT_X3B, y3 = TRIAN_POINT_Y3;
    uint8_t  music[MAX_LENGHT],level[MAX_LENGHT],resolution[MAX_LENGHT],snake_color[MAX_LENGHT];
    
    do
    {
        key = get_keyboard (event_queue);
        switch (key)
        {
            case (ALLEGRO_KEY_DOWN):
                move_menu_pointer (&y1,&y2,&y3,key);
                display_options(options, titulo, opciones, mensaje, DISPLAY_W, DISPLAY_H,x1,y1,x2,y2,x3,y3,read_config ("music.txt",options_file,music),read_config ("level.txt",options_file,level),read_config ("resolution.txt",options_file,resolution),read_config ("snake_color.txt",options_file,snake_color));
                break;
            case (ALLEGRO_KEY_UP):
                move_menu_pointer (&y1,&y2,&y3,key);
                display_options(options, titulo, opciones, mensaje, DISPLAY_W, DISPLAY_H,x1,y1,x2,y2,x3,y3,read_config ("music.txt",options_file,music),read_config ("level.txt",options_file,level),read_config ("resolution.txt",options_file,resolution),read_config ("snake_color.txt",options_file,snake_color));
                break; 
            case (ALLEGRO_KEY_ENTER):
                set_options (&y1,options_file);
                break;
            default:
                display_options(options, titulo, opciones, mensaje, DISPLAY_W, DISPLAY_H,x1,y1,x2,y2,x3,y3,read_config ("music.txt",options_file,music),read_config ("level.txt",options_file,level),read_config ("resolution.txt",options_file,resolution),read_config ("snake_color.txt",options_file,snake_color));
                break;    
        }
    }
    while (key != ALLEGRO_KEY_ESCAPE );
    
    return 0;
}

static void set_options (uint16_t *y_pos, FILE *options_files)
{
    if (*y_pos == TRIAN_POINT_Y1)
    {
        switch_music (options_files);
    }
    else if (*y_pos == TRIAN_POINT_Y1_ONE_STEP)
    {
        switch_level (options_files);
    }
    else if (*y_pos == TRIAN_POINT_Y1_TWO_STEP)
    {
        switch_resolution (options_files);
    }
    else if (*y_pos == TRIAN_POINT_Y1_EXT_DOWN)
    {
        switch_snake_color (options_files);
    }  
}


static void switch_music (FILE *options_files)
{
    uint8_t music[MAX_LENGHT];
    
    read_config (FILE_MUSIC,options_files,music);
    if (strcmp (music,OFF) == 0)
    {
        modify_config (FILE_MUSIC,options_files,ON);
    }
    else
    {
       modify_config (FILE_MUSIC,options_files,OFF); 
    }
}

static void switch_level (FILE *options_files)
{
    uint8_t level[MAX_LENGHT];
    
    read_config (FILE_LEVEL,options_files,level);
    if (strcmp (level,LEVEL_1) == 0)
    {
        modify_config (FILE_LEVEL,options_files,LEVEL_2);
    }
    else if (strcmp (level,LEVEL_2) == 0)  
    {
       modify_config (FILE_LEVEL,options_files,LEVEL_3); 
    }
    else if (strcmp (level,LEVEL_3) == 0)  
    {
       modify_config (FILE_LEVEL,options_files,LEVEL_1); 
    }   
}


static void   switch_resolution  (FILE *options_files)
{
    uint8_t resolution[MAX_LENGHT];
    
    read_config (FILE_RESOLUTION,options_files,resolution);
    //printf ("%s",resolution);
    if (strcmp (resolution,RESOLUTION_1) == 0)
    {
        modify_config (FILE_RESOLUTION,options_files,RESOLUTION_2);
    }
    else if (strcmp (resolution,RESOLUTION_2) == 0)  
    {
       modify_config (FILE_RESOLUTION,options_files,RESOLUTION_3); 
    }
    else if (strcmp (resolution,RESOLUTION_3) == 0)  
    {
       modify_config (FILE_RESOLUTION,options_files,RESOLUTION_1); 
    }   
}

static void   switch_snake_color (FILE *options_files)
{
    uint8_t snake_color[MAX_LENGHT];
    
    read_config (FILE_SNAKE_COLOR,options_files,snake_color);
    if (strcmp (snake_color,COLOR_1) == 0)
    {
        modify_config (FILE_SNAKE_COLOR,options_files,COLOR_2);
    }
    else if (strcmp (snake_color,COLOR_2) == 0)  
    {
       modify_config (FILE_SNAKE_COLOR,options_files,COLOR_3); 
    }
    else if (strcmp (snake_color,COLOR_3) == 0)  
    {
       modify_config (FILE_SNAKE_COLOR,options_files,COLOR_4); 
    } 
    else if (strcmp (snake_color,COLOR_4) == 0)  
    {
       modify_config (FILE_SNAKE_COLOR,options_files,COLOR_1); 
    } 
    
}

static uint8_t check_exit (ALLEGRO_EVENT_QUEUE *event, ALLEGRO_FONT *opciones)
{
    uint32_t key;
    
    display_exit_message(opciones);
    do
    {
        key = get_keyboard (event);
    }
    while (key != ALLEGRO_KEY_ENTER && key != ALLEGRO_KEY_ESCAPE);
    
    if (key == ALLEGRO_KEY_ENTER)
    {
        return 1;
    }
    else
    {
       return 0; 
    }
}