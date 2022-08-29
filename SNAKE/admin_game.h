/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   admin_game.h
 * Author: gonza
 *
 * Created on 15 de diciembre de 2018, 13:44
 */

#ifndef ADMIN_GAME_H
#define ADMIN_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h>

#define U_DELAY      (100000)   //0.3 seg  
#define ANY_KEY       (ALLEGRO_KEY_F)
#define RESUME        (1)
#define QUIT_GAME     (2)
#define BACK_TO_MENU  (3)
#define VERDE         (al_map_rgb(0,255,0))
#define AZUL          (al_map_rgb(0,0,255))
#define ROJO          (al_map_rgb(255,0,0))
#define MAGENTA       (al_map_rgb(200, 30, 140))
#define PRINCIPIANTE  (300000)
#define INDIANA_JONES (100000)
#define MODO_DIABLO   (50000)
#define MIN_DELAY     (1000)
#define DECIMAL       (10)


uint32_t admin_game (FILE *, FILE *,ALLEGRO_EVENT_QUEUE *);

#endif /* ADMIN_GAME_H */
