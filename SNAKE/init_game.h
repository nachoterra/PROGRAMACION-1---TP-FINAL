/* 
 * File:   init_game.h
 * Author: Awasa
 * Created on 28 de noviembre de 2018, 19:02
 */

#ifndef INIT_GAME_H
#define INIT_GAME_H

#include <stdio.h>
#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_acodec.h>


uint8_t         init_allegro    (void);     //Funcion que inicializa todas los sistemas de allegro que se utilizaran
uint8_t         create_intro    (ALLEGRO_DISPLAY *, ALLEGRO_FONT *, ALLEGRO_FONT *, ALLEGRO_FONT *); //Diseño del logo. Fuente y bitmap


#endif /* INIT_GAME_H */

