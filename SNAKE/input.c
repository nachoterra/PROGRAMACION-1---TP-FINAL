/* 
 * File:   input.c
 * Author: Awasa 
 * Created on 29 de noviembre de 2018, 13:48
 */

#include "input.h"

void wait_for_key (uint32_t key)
{
    ALLEGRO_KEYBOARD_STATE state;
    do
    {
        al_get_keyboard_state (&state);
    } 
    while (!al_key_down(&state, key));
    usleep(300000);
}

uint32_t get_keyboard (ALLEGRO_EVENT_QUEUE *event_queue)
{
    ALLEGRO_EVENT event;
    if ((al_get_next_event(event_queue, &event)) && (event.type == ALLEGRO_EVENT_KEY_DOWN))
        return event.keyboard.keycode;
}


