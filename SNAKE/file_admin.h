/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   file_admin.h
 * Author: gonzalo
 *
 * Created on 13 de diciembre de 2018, 17:14
 */

#ifndef FILE_ADMIN_H
#define FILE_ADMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_LENGHT          (100)
#define FILE_MUSIC          ("music.txt")
#define FILE_LEVEL          ("level.txt")
#define FILE_RESOLUTION     ("resolution.txt")
#define FILE_SNAKE_COLOR    ("snake_color.txt")
#define SCORE_1             ("best_score1.txt")
#define SCORE_2             ("best_score2.txt")
#define SCORE_3             ("best_score3.txt")
#define OFF                 ("OFF\n")
#define ON                  ("ON\n")
#define LEVEL_1             ("PRINCIPIANTE\n")
#define LEVEL_2             ("INDIANA JONES\n")
#define LEVEL_3             ("MODO DIABLO\n")
#define RESOLUTION_1        ("800X600\n")       
#define RESOLUTION_2        ("1024X720\n")
#define RESOLUTION_3        ("1366X768\n")
#define COLOR_1             ("VERDE\n")
#define COLOR_2             ("AZUL\n")
#define COLOR_3             ("ROJO\n")
#define COLOR_4             ("MAGENTA\n")





uint8_t* read_config            (uint8_t *, FILE *, uint8_t *);
uint8_t  modify_config          (uint8_t *, FILE *, uint8_t *);


#endif /* FILE_ADMIN_H */
