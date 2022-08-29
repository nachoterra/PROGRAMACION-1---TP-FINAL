/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menus.h
 * Author: gonza
 *
 * Created on 15 de diciembre de 2018, 13:25
 */

#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define ANY_KEY     (ALLEGRO_KEY_F)
#define LOOP_EXIT   (2)
#define GAME_EXIT   (1)

uint8_t create_menu     (ALLEGRO_DISPLAY *, ALLEGRO_FONT *, ALLEGRO_FONT *, ALLEGRO_FONT *, ALLEGRO_EVENT_QUEUE *,FILE *,FILE *);

#endif /* MENUS_H */
