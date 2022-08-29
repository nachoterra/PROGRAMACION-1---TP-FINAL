/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   admin_game.c
 * Author: gonza
 * 
 * Created on 15 de diciembre de 2018, 13:44
 */

#include "admin_game.h"
#include "snake_world.h"
#include "output.h"
#include "file_admin.h"
#include "input.h"

//static uint8_t  create_display           (ALLEGRO_DISPLAY *, uint16_t, uint16_t);
static void             get_resolution           (FILE *, uint16_t *,uint16_t *);
static uint32_t         get_level                (FILE *);
static ALLEGRO_COLOR    get_color                (FILE *);
static uint8_t          is_music_set             (FILE *);
static uint32_t         game_loop                (ALLEGRO_FONT *,ALLEGRO_EVENT_QUEUE *, uint32_t,uint32_t ,uint8_t , uint32_t , uint16_t ,uint16_t , ALLEGRO_COLOR , uint16_t  [MAX_SIZE_X][MAX_SIZE_Y], uint32_t,FILE *);
static void             delay                    (uint32_t, uint32_t);
static void             admin_display_world      (ALLEGRO_FONT *, uint16_t [MAX_SIZE_X][MAX_SIZE_Y], uint16_t, uint16_t,ALLEGRO_COLOR,uint32_t,uint8_t);
static uint32_t         check_key                (uint32_t, uint32_t);
static uint32_t         pause_menu               (ALLEGRO_FONT *, ALLEGRO_EVENT_QUEUE *,uint16_t, uint16_t);
static void             move_pause_menu_pointer  (uint16_t *, uint16_t *, uint16_t *, uint32_t);
static uint32_t         admin_pause_menu         (uint16_t *,ALLEGRO_EVENT_QUEUE *,ALLEGRO_FONT *);
static uint8_t          check_exit               (ALLEGRO_EVENT_QUEUE *, ALLEGRO_FONT *);
static void             save_scores              (FILE *,uint32_t);          

uint32_t admin_game (FILE *options_files, FILE *best_scores,ALLEGRO_EVENT_QUEUE *event_queue)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP  *background = NULL;
    ALLEGRO_FONT *opciones = NULL;
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_COLOR color;
  
    uint32_t last_pressed_valid_key = RIGHT;
    uint32_t key,score = 0;
    uint16_t snake_world [MAX_SIZE_X][MAX_SIZE_Y];
    uint16_t width, high;
    uint8_t  snake_life = SNAKE_LIFE;
    uint32_t speed;
     
    get_resolution (options_files,&width,&high);
    speed = get_level(options_files);
    color = get_color(options_files);
    //create_display (display,width,high);
     if (!(event_queue = al_create_event_queue()))
    {
        fprintf(stderr, "Creacion de fila de eventos fallida \n");
        al_destroy_event_queue(event_queue);
        return QUIT_GAME;
    }
     else if(!(opciones = al_load_ttf_font("SuperMario256.ttf",25,0)))  //Elijo la fuente deseada
    {
        fprintf(stderr,"Creacion de fuente erronea \n");
        al_destroy_font(opciones);
        return QUIT_GAME;
    }
    sample = al_load_sample( "audio.wav" );
    if (!sample)
    {
        printf( "Audio clip sample not loaded!\n" ); 
        return QUIT_GAME;
    }
    
    if (is_music_set(options_files))
    {
        al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    }
    else
    {
        al_stop_samples();
    }
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    srand(time(NULL));
    create_world (snake_world);
    key = game_loop (opciones,event_queue,key,last_pressed_valid_key,snake_life,score,\
                     width,high,color,snake_world,speed,best_scores);
    
    return key; 
}

static uint8_t create_display (ALLEGRO_DISPLAY *display,uint16_t width, uint16_t high)
{
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    if (!(display = al_create_display (width,high))) //Creo el display con medidas "DISPLAY_W" y "DISPLAY_H"
    {
        fprintf (stderr, "Creacion de display erronea \n");    //Mensaje de error al usuario
        al_destroy_display(display);  //destruye el display
        return 1;      //Condicion de salida con error
    }
    return 0;   //Ejecucion exitosa de la funcion
}


static void get_resolution (FILE *options_files, uint16_t *width, uint16_t *high)
{
    uint8_t resolution[MAX_LENGHT];
    
    read_config (FILE_RESOLUTION,options_files,resolution);
    if (strcmp (resolution,RESOLUTION_1) == 0)
    {
        *width = 800;
        *high  = 600;
    }
    else if (strcmp (resolution,RESOLUTION_2) == 0)  
    {
       *width = 1024;
       *high  = 720; 
    }
    else if (strcmp (resolution,RESOLUTION_3) == 0)  
    { 
       *width = 1366;
       *high  = 768; 
    }   
}

static uint32_t get_level (FILE *options_files)
{
    uint8_t level[MAX_LENGHT];
    uint32_t speed;
    
    read_config (FILE_LEVEL,options_files,level);
    if (strcmp (level,LEVEL_1) == 0)
    {
        speed = PRINCIPIANTE;
    }
    else if (strcmp (level,LEVEL_2) == 0)  
    {
        speed = INDIANA_JONES;
    }
    else if (strcmp (level,LEVEL_3) == 0)  
    { 
        speed = MODO_DIABLO;
    }   
    
    return speed;
}

static ALLEGRO_COLOR get_color (FILE *options_files)
{
    uint8_t color_array[MAX_LENGHT];
    ALLEGRO_COLOR color;
    
    read_config (FILE_SNAKE_COLOR,options_files,color_array);
    if (strcmp (color_array,COLOR_1) == 0)
    {
        color = VERDE;
    }
    else if (strcmp (color_array,COLOR_2) == 0)  
    {
        color = AZUL;
    }
    else if (strcmp (color_array,COLOR_3) == 0)  
    { 
        color = ROJO;
    } 
    else if (strcmp (color_array,COLOR_4) == 0)  
    { 
        color = MAGENTA;
    }
    
    return color;
}
    
static uint8_t is_music_set (FILE *options_files)
{
    uint8_t music[MAX_LENGHT];
    bool state;
    
    read_config (FILE_MUSIC,options_files,music);
    if (strcmp (music,ON) == 0)
    {
        state = true;
    }
    else if (strcmp (music,OFF) == 0)  
    {
        state = false;
    }
    
    return state;
}

static uint32_t game_loop (ALLEGRO_FONT *opciones,ALLEGRO_EVENT_QUEUE *event_queue, \
                           uint32_t key, uint32_t last_pressed_valid_key, \
                           uint8_t snake_life, uint32_t score, uint16_t width, \
                           uint16_t high, ALLEGRO_COLOR color, \
                           uint16_t snake_world [MAX_SIZE_X][MAX_SIZE_Y], uint32_t speed, \
                           FILE *best_scores)
{
    do
    {
        key = get_keyboard(event_queue);
        if (check_key (key,last_pressed_valid_key) == ANY_KEY)
        {
            key = ANY_KEY;
        }
        switch (key)
        {
            case (ALLEGRO_KEY_RIGHT) :
                game_logic (snake_world,RIGHT,&last_pressed_valid_key,&snake_life,&score);
                last_pressed_valid_key = RIGHT;
                break;
            case (ALLEGRO_KEY_LEFT) :
                game_logic (snake_world,LEFT,&last_pressed_valid_key,&snake_life,&score);
                last_pressed_valid_key = LEFT;
                break;
            case (ALLEGRO_KEY_DOWN) :
                game_logic (snake_world,DOWN,&last_pressed_valid_key,&snake_life,&score);
                last_pressed_valid_key = DOWN;
                break;
            case (ALLEGRO_KEY_UP) :
                game_logic (snake_world,UP,&last_pressed_valid_key,&snake_life,&score);
                last_pressed_valid_key = UP;
                break;  
            case (ALLEGRO_KEY_ESCAPE):
                key = pause_menu(opciones,event_queue,width,high);
                break;
            default:
                game_logic (snake_world,last_pressed_valid_key,&last_pressed_valid_key,&snake_life,&score);
        }
        al_flush_event_queue(event_queue);
        if (score == WIN_SCORE)
        {
            display_end(opciones,"GANASTE :D",width,high);
            key = BACK_TO_MENU;
        }
        if (!snake_life)
        {
            save_scores (best_scores,score);
            display_end(opciones,"PERDISTE :(",width,high);
            key = BACK_TO_MENU;
        }
        else
        {
            admin_display_world (opciones,snake_world,width,high,color,score,snake_life);
            delay(speed,score);
        }
    }	
    while (key != BACK_TO_MENU && key != QUIT_GAME);
    
    return key;
}

static void delay (uint32_t time, uint32_t score)
{
    if (time-(score*50) > MIN_DELAY)
    {
        usleep (time-(score*50));
    }
    else
    {
        usleep (MIN_DELAY);
    }   
}


static void    admin_display_world  (ALLEGRO_FONT *opciones,uint16_t snake_world [MAX_SIZE_X][MAX_SIZE_Y], uint16_t width, uint16_t high,ALLEGRO_COLOR color,uint32_t score,uint8_t life)
{
    uint16_t i,j;
    ALLEGRO_BITMAP  *background = NULL;
    ALLEGRO_COLOR color1 = al_map_rgb (255,0,0);
    ALLEGRO_COLOR color2 = al_map_rgb (0,0,255);
    
    if(!(background = al_load_bitmap ("grass2.jpg")))
    {
        fprintf(stderr,"Creacion de fondo fallida \n");  ///Mensaje de error al usuario
        al_destroy_bitmap(background);    //destruye el bitmap del logo
        //return 1;  //Condicion de salida con error
    }
    display_world (opciones,background,width,high,score,life);
    for(i = MIN_WORLD_WIDTH; i <= MAX_WORLD_WIDTH; i++)			
    {
        for(j = MIN_WORLD_HIGH; j <= MAX_WORLD_HIGH; j++)
        {
            if(snake_world[i][j] >= SNAKE_HEAD && snake_world[i][j] <= END_OF_SNAKE)
            {
                display_snake (background,snake_world [i][j],width,high,SNAKE_HEAD,i,j,MAX_WORLD_WIDTH,MAX_WORLD_HIGH,color);
            }
            else if (snake_world[i][j] == SNAKE_FOOD)
            {
                display_snake (background,snake_world [i][j],width,high,SNAKE_HEAD,i,j,MAX_WORLD_WIDTH,MAX_WORLD_HIGH,color1);
            }
            else if (snake_world[i][j] == WALL)
            {
                display_snake (background,snake_world [i][j],width,high,SNAKE_HEAD,i,j,MAX_WORLD_WIDTH,MAX_WORLD_HIGH,color2);
            }
        }
    }
    al_flip_display();
  
	/*for (i=1; i<20;i++)
    	{
       		for(j=1; j<20; j++)
       		 {
		 	printf (" %d ",snake_world [i][j]);   
      		 }
	printf ("\n");
	}*/
    al_destroy_bitmap(background);
}
  

static uint32_t check_key (uint32_t key, uint32_t last_pressed_valid_key)
{
    if ((key == ALLEGRO_KEY_RIGHT || key == ALLEGRO_KEY_LEFT) && (last_pressed_valid_key == RIGHT || last_pressed_valid_key == LEFT))
    {
        return ANY_KEY;
    }
    else if ((key == ALLEGRO_KEY_DOWN || key == ALLEGRO_KEY_UP) && (last_pressed_valid_key == UP || last_pressed_valid_key == DOWN))
    {
        return ANY_KEY;
    }
}

static uint32_t pause_menu (ALLEGRO_FONT *opciones, ALLEGRO_EVENT_QUEUE *event_queue, uint16_t width, uint16_t high)
{
    ALLEGRO_BITMAP *pause = NULL;
    
    uint32_t key;
    uint16_t x1 = TRIAN_POINT_X1, y1 = TRIAN_POINT_Y1; 
    uint16_t x2 = TRIAN_POINT_X2, y2 = TRIAN_POINT_Y2;
    uint16_t x3 = TRIAN_POINT_X3, y3 = TRIAN_POINT_Y3;
  
    
    if(!(pause = al_load_bitmap ("sleep_snake.jpg")))
    {
        fprintf(stderr,"Creacion de fondo fallida \n");  ///Mensaje de error al usuario
        al_destroy_bitmap(pause);    //destruye el bitmap del logo
        al_destroy_font(opciones);
        return 1;  //Condicion de salida con error
    }
    do
    {
        key = get_keyboard (event_queue);
        switch (key)
        {
            case (ALLEGRO_KEY_DOWN):
                move_pause_menu_pointer (&y1,&y2,&y3,key);
                display_pause_menu (pause,opciones,x1,y1,x2,y2,x3,y3,width,high);
                break;
            case (ALLEGRO_KEY_UP):
                move_pause_menu_pointer (&y1,&y2,&y3,key);
                display_pause_menu (pause,opciones,x1,y1,x2,y2,x3,y3,width,high);
                break; 
            case (ALLEGRO_KEY_ENTER):
                key = admin_pause_menu (&y1,event_queue,opciones);
                break;
            default:
                display_pause_menu (pause,opciones,x1,y1,x2,y2,x3,y3,width,high);
                break;    
        }
    }
    while (key != RESUME && key != QUIT_GAME && key != BACK_TO_MENU);
    
    return key;   
}

static void move_pause_menu_pointer (uint16_t *y1, uint16_t *y2, uint16_t *y3, uint32_t key)
{
    if (key == ALLEGRO_KEY_UP && *y1 != TRIAN_POINT_Y1)
    {
        *y1 -= LINE_DISTANCE;
        *y2 -= LINE_DISTANCE;
        *y3 -= LINE_DISTANCE;
    }
    else if (key == ALLEGRO_KEY_DOWN && *y1 != PAUSE_MENU_POINT_Y1_EXT_DOWN)
    {
        *y1 += LINE_DISTANCE;
        *y2 += LINE_DISTANCE;
        *y3 += LINE_DISTANCE;
    }   
}

static uint32_t admin_pause_menu (uint16_t *y_pos, ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *opciones)
{
    if (*y_pos == TRIAN_POINT_Y1)
    {
        return (RESUME);
    }
    else if (*y_pos == TRIAN_POINT_Y1_ONE_STEP)
    {
        return (BACK_TO_MENU) ;
    }
    else if (*y_pos == TRIAN_POINT_Y1_TWO_STEP)
    {
        if(check_exit (event_queue,opciones))
        {
            return (QUIT_GAME);
        }    
    }
    return 0;
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


static void save_scores (FILE *best_scores,uint32_t score)
{
    uint8_t score1[MAX_LENGHT];
    uint8_t score2[MAX_LENGHT];
    uint8_t score3[MAX_LENGHT];
    uint8_t score_array [MAX_LENGHT];
    
    read_config (SCORE_1,best_scores,score1);
    read_config (SCORE_2,best_scores,score2);
    read_config (SCORE_3,best_scores,score3);
    sprintf (score_array,"%d",score);
    
   
    
    if (score > (atoi(score1)))
    {
        
        modify_config(SCORE_1,best_scores,score_array);
    }
    else if (score > (atoi(score2)))
    {
        modify_config(SCORE_2,best_scores,score_array); 
    }
    else if (score > (atoi(score3)))
    {
        modify_config(SCORE_3,best_scores,score_array);
    }
}
