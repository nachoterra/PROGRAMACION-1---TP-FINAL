/* 
 * File:   input.h
 * Author: Awasa
 * Created on 29 de noviembre de 2018, 13:48
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <allegro5/allegro.h>

void wait_for_key (uint32_t key);
uint32_t get_keyboard (ALLEGRO_EVENT_QUEUE *);

#endif /* INPUT_H */
