/* 
 * File:   output.c
 * Author: Awasa
 * Created on 29 de noviembre de 2018, 13:47
 */

#include "output.h"

void display_logo (ALLEGRO_BITMAP *logo, ALLEGRO_FONT *mensaje, uint16_t width, uint16_t high)
{
    ALLEGRO_COLOR gris_claro = al_map_rgb(150,150,150);
    
    al_draw_scaled_bitmap(logo,0,0,al_get_bitmap_width(logo),al_get_bitmap_height(logo),0,0,width,high,0); //coloca el logo
    al_draw_text (mensaje, gris_claro, width*0.75, high*0.95,0, "Presione espacio para continuar");   //Crea el texto formateado
    al_flip_display();  //Envia al display lo acumulado en el buffer (logo)  
}

void display_info (ALLEGRO_BITMAP *logo, ALLEGRO_FONT *titulo, ALLEGRO_FONT *subtitulo, ALLEGRO_FONT *mensaje,  uint16_t width, uint16_t high)
{
    ALLEGRO_COLOR negro = al_map_rgb(0,0,0);
    ALLEGRO_COLOR gris_claro1 = al_map_rgb(150,150,150);
    ALLEGRO_COLOR gris_claro2 = al_map_rgb(230,230,230);
    
    al_clear_to_color(gris_claro2); //Pone el fondo gris
    al_draw_text (titulo, negro, width*0.5, high*0.1,ALLEGRO_ALIGN_CENTRE, "Trabajo Práctico");
    al_draw_text (titulo, negro, width*0.5, high*0.22,ALLEGRO_ALIGN_CENTRE, "Final");
    al_draw_text (subtitulo, negro, width*0.1, high*0.45,0, "Cátedra : Programación I");   //Crea el texto formateado
    al_draw_text (subtitulo, negro, width*0.1, high*0.55,0, "Alumnos : Pintos, Gonzalo Agustín ");   //Crea el texto formateado
    al_draw_text (subtitulo, negro, width*0.28, high*0.62,0, "Terra Brandes Britos, Ignacio");   //Crea el texto formateado
    al_draw_text (subtitulo, negro, width*0.1, high*0.72,0, "Profesores : Jacoby, Daniel Andres");   //Crea el texto formateado
    al_draw_text (subtitulo, negro, width*0.32, high*0.79,0, "Magliola, Nicolas ");   //Crea el texto formateado
    al_draw_text (subtitulo, negro, width*0.32, high*0.86,0, "Vacatello, Pablo Daniel ");   //Crea el texto formateado
    al_draw_text (mensaje, gris_claro1, width*0.75, high*0.93,0, "Presione espacio para continuar");   //Crea el texto formateado
    al_flip_display();    //Envia al display lo acumulado en el buffer (texto y fondo)                                                                                            
}

void display_menu (ALLEGRO_BITMAP *menu, ALLEGRO_FONT *titulo, ALLEGRO_FONT *opciones, uint16_t width, uint16_t high, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3)
{
    ALLEGRO_COLOR negro = al_map_rgb(0,0,0);
    ALLEGRO_COLOR rojo = al_map_rgb(255,0,0);
    
    al_clear_to_color(negro);
    al_draw_scaled_bitmap (menu,0,0,al_get_bitmap_width(menu),al_get_bitmap_height(menu),0,0,width,high,0);
    al_draw_text (titulo, negro, width/2, high/10,ALLEGRO_ALIGN_CENTRE, "SNAKE");
    al_draw_text (opciones, negro, width/2, high*0.5,ALLEGRO_ALIGN_CENTRE, "Jugar");
    al_draw_text (opciones, negro, width/2, high*0.6,ALLEGRO_ALIGN_CENTRE, "Mejores puntajes");
    al_draw_text (opciones, negro, width/2, high*0.7,ALLEGRO_ALIGN_CENTRE, "Opciones");
    al_draw_text (opciones, negro, width/2, high*0.8,ALLEGRO_ALIGN_CENTRE, "Salir");
    al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, rojo);
    al_flip_display();
}

void display_exit_message (ALLEGRO_FONT *opciones)
{
    ALLEGRO_COLOR gris_claro = al_map_rgb(150,150,150);
    ALLEGRO_COLOR negro      = al_map_rgb(0,0,0);
    ALLEGRO_COLOR rojo       = al_map_rgb(255,0,0);
    
    al_draw_filled_rectangle (RECTANGLE_X1, RECTANGLE_Y1, RECTANGLE_X2, RECTANGLE_Y2, gris_claro);
    al_draw_text (opciones, negro, MIDDLE_DISPLAY_W, DISPLAY_H*0.4,ALLEGRO_ALIGN_CENTRE, "Seguro desea salir?");
    al_draw_text (opciones, negro, MIDDLE_DISPLAY_W, DISPLAY_H*0.47,ALLEGRO_ALIGN_CENTRE, "Snake morira :_(");
    al_draw_text (opciones, rojo , MIDDLE_DISPLAY_W, DISPLAY_H*0.59,ALLEGRO_ALIGN_CENTRE, "SI(enter)      NO(escape)");

    al_flip_display();
}

void display_best_score (ALLEGRO_BITMAP *fondo, ALLEGRO_FONT *titulo, ALLEGRO_FONT *ganadores, ALLEGRO_FONT *mensaje,  uint16_t width, uint16_t high, uint8_t *score1, uint8_t *score2, uint8_t *score3)
{
    ALLEGRO_COLOR negro = al_map_rgb(0,0,0);
    ALLEGRO_COLOR gris_claro = al_map_rgb(150,150,150);
    
    al_draw_scaled_bitmap(fondo,0,0,al_get_bitmap_width(fondo),al_get_bitmap_height(fondo),0,0,width,high,0);
    al_draw_text  (titulo, negro, width*0.5, high*0.1,ALLEGRO_ALIGN_CENTRE, "Mejores Puntuaciones");
    al_draw_text  (mensaje, gris_claro, width*0.70, high*0.95,0, "Presione escape para volver al menu");   //Crea el texto formateado
    al_draw_textf (ganadores, negro, width*0.5, high*0.5,ALLEGRO_ALIGN_CENTRE, "PRIMER PUESTO : %s",  score1);   //Crea el texto formateado
    al_draw_textf (ganadores, negro, width*0.5, high*0.6,ALLEGRO_ALIGN_CENTRE, "SEGUNDO PUESTO : %s", score2);   //Crea el texto formateado
    al_draw_textf (ganadores, negro, width*0.5, high*0.7,ALLEGRO_ALIGN_CENTRE, "TERCER PUESTO : %s",  score3);   //Crea el texto formateado

    al_flip_display();    //Envia al display lo acumulado en el buffer (texto y fondo)                                                                 
}

void display_options (ALLEGRO_BITMAP *options, ALLEGRO_FONT *titulo, ALLEGRO_FONT *opciones, ALLEGRO_FONT *mensaje, uint16_t width, uint16_t high, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t *music, uint8_t *level, uint8_t *resolution, uint8_t *snake_color)
{
    ALLEGRO_COLOR violeta = al_map_rgb(200, 30, 140);
    ALLEGRO_COLOR naranja = al_map_rgb(239, 127, 26);
    ALLEGRO_COLOR gris_claro = al_map_rgb(150,150,150);
    
    al_draw_scaled_bitmap (options,0,0,al_get_bitmap_width(options),al_get_bitmap_height(options),0,0,width,high,0);
    al_draw_text  (titulo, violeta, width/2, high*0.1,ALLEGRO_ALIGN_CENTRE, "OPCIONES");
    al_draw_textf (opciones, violeta, width/2, high*0.5,ALLEGRO_ALIGN_CENTRE, "Musica : %s", music);
    al_draw_textf (opciones, violeta, width/2, high*0.6,ALLEGRO_ALIGN_CENTRE, "Nivel : %s", level);
    al_draw_textf (opciones, violeta, width/2, high*0.7,ALLEGRO_ALIGN_CENTRE, "Resolucion : %s", resolution);
    al_draw_textf (opciones, violeta, width/2, high*0.8,ALLEGRO_ALIGN_CENTRE, "Color de Snake : %s", snake_color);
    al_draw_textf  (mensaje, gris_claro, width*0.70, high*0.95,0, "Presione escape para volver al menu");
    al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, naranja);
    al_flip_display();
}


void display_world (ALLEGRO_FONT *titulo,ALLEGRO_BITMAP *background,uint16_t width, uint16_t high, uint32_t score,uint8_t life)
{
    ALLEGRO_COLOR blanco = al_map_rgb(255,255,255);
    ALLEGRO_COLOR negro = al_map_rgb(0,0,0);
    
    al_clear_to_color(negro);
    al_draw_scaled_bitmap (background,0,0,al_get_bitmap_width(background),al_get_bitmap_height(background),0,high*0.1,width,high*0.9,0);
    al_draw_textf (titulo, blanco, width*0.2, high*0.01,ALLEGRO_ALIGN_CENTRE, "VIDAS : %d",life);
    al_draw_textf (titulo, blanco, width*0.8, high*0.01,ALLEGRO_ALIGN_CENTRE, "SCORE : %d",score);
}



void display_snake (ALLEGRO_BITMAP *background,uint16_t body_part, uint16_t width, uint16_t high, uint16_t snake_head, uint16_t pos_y, uint16_t pos_x, uint16_t div_x, uint16_t div_y,ALLEGRO_COLOR color)
{ 
    al_draw_filled_circle   (((width/div_x)/2)+((width/div_x)*(pos_x-1)) , (((high*0.9)/div_y)/2)+(((high*0.9)/div_y)*(pos_y)) , ((high*0.9)/div_y)/2.02 , color);
    //al_flip_display();    
}

void display_pause_menu (ALLEGRO_BITMAP *pause, ALLEGRO_FONT *opciones, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t width, uint16_t high)
{
    ALLEGRO_COLOR azul = al_map_rgb(0,0,255);
    ALLEGRO_COLOR negro = al_map_rgb(0,0,0);
    
    al_draw_scaled_bitmap (pause,0,0,al_get_bitmap_width(pause),al_get_bitmap_height(pause),(width/2)-(width*0.4),(high/2)-(high*0.3),width * 0.8,high*0.8,0);
    al_draw_text  (opciones, negro, MIDDLE_DISPLAY_W, DISPLAY_H*0.5,ALLEGRO_ALIGN_CENTRE, "REANUDAR");
    al_draw_text  (opciones, negro, MIDDLE_DISPLAY_W, DISPLAY_H*0.6,ALLEGRO_ALIGN_CENTRE, "VOLVER AL MENU INICIO");
    al_draw_text  (opciones, negro, MIDDLE_DISPLAY_W, DISPLAY_H*0.7,ALLEGRO_ALIGN_CENTRE, "SALIR DEL JUEGO");
    al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, azul);
    al_flip_display();
}

void display_end (ALLEGRO_FONT *titulo,uint8_t *mensaje, uint16_t width,uint16_t high)
{
    ALLEGRO_COLOR gris_claro = al_map_rgb(150,150,150);
    ALLEGRO_COLOR negro = al_map_rgb(0,0,0);
    
    //al_draw_filled_rectangle (RECTANGLE_X1, RECTANGLE_Y1, RECTANGLE_X2, RECTANGLE_Y2, gris_claro);
    al_draw_textf (titulo, negro, width*0.5, high*0.5,ALLEGRO_ALIGN_CENTRE, "%s",mensaje);
    al_flip_display();
    al_rest (TIME);
}


