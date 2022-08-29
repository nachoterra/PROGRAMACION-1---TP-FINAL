/* 
 * File:   snake_world.c
 * Author: Awasa 
 * Created on 29 de noviembre de 2018, 13:09
 */

#include "snake_world.h"

static uint16_t* search_for_in_world  (uint16_t [MAX_SIZE_X][MAX_SIZE_Y], uint16_t);
static uint8_t   admin_move           (uint16_t [MAX_SIZE_X][MAX_SIZE_Y],uint16_t * ,uint16_t *,uint16_t *,uint16_t,uint32_t,uint32_t *);
static uint8_t   move_snake_head      (uint16_t* , uint16_t);
static void      move_snake_body      (uint16_t*, uint16_t);
static void      put_food             (uint16_t [MAX_SIZE_X][MAX_SIZE_Y]);
static uint8_t   check_next_step      (uint16_t*);
static uint8_t   check_crash          (uint16_t*);



void game_logic (uint16_t snake_world[MAX_SIZE_X][MAX_SIZE_Y], uint32_t direction, uint32_t *last_pressed_valid_key, uint8_t *snake_life, uint32_t *score)
{
    uint16_t *snake_head_first_ubication = NULL, *previous_body_part_ubication = NULL;
    uint16_t *body_part_ubication = NULL;
    uint16_t  body_part = SNAKE_HEAD ;
    
    if (admin_move (snake_world,snake_head_first_ubication,previous_body_part_ubication,body_part_ubication,body_part,direction,score))
    {
        create_world(snake_world);
        *last_pressed_valid_key = RIGHT;
        (*snake_life)--;
        //(*score) = 0;   //
    }
    put_food (snake_world);
}

void create_world (uint16_t snake_world [MAX_SIZE_X][MAX_SIZE_Y])
{
    uint16_t i,j;
    for (i=0; i < MAX_SIZE_X; i++)
    {
        for(j=0; j < MAX_SIZE_Y; j++)
        {
            if ((i == LEFT_WALL_SPACE) || (i == RIGHT_WALL_SPACE) || (j== TOP_WALL_SPACE)  || (j == BOTTOM_WALL_SPACE ))
            {
             	 snake_world [i][j] = WALL;  // pone una pared en los extremos del mundo
	    }
            else
            {
                snake_world [i][j] = EMPTY_SPACE; //pone en 0 los espacios libre del mundo
            }
        }
        
    }
    snake_world [MAX_WORLD_HIGH/2][MAX_WORLD_WIDTH/2]     = SNAKE_HEAD;
    snake_world [MAX_WORLD_HIGH/2][(MAX_WORLD_WIDTH/2)-1] = SNAKE_HEAD+1;
 //   snake_world [MAX_WORLD_HIGH/2][(MAX_WORLD_WIDTH/2)-2] = SNAKE_HEAD+2;
    snake_world [MAX_WORLD_HIGH/2][(MAX_WORLD_WIDTH/2)-2] = END_OF_SNAKE;
}

static uint16_t* search_for_in_world (uint16_t snake_world [MAX_SIZE_X][MAX_SIZE_Y], uint16_t body_part)
{
    uint16_t i,j;
    uint16_t* part_pos = NULL;
    
    for(i = MIN_WORLD_WIDTH; i <= MAX_WORLD_WIDTH; i++)			
    {
        for(j = MIN_WORLD_HIGH; j <= MAX_WORLD_HIGH; j++)
        {
            if(snake_world[i][j] == body_part)
            {
                part_pos= &(snake_world [i][j]);     //devuelve puntero con la posicion en la que se encuentra la body
            }
        }
    }
    
    return part_pos;
}

static uint8_t admin_move (uint16_t snake_world[MAX_SIZE_X][MAX_SIZE_Y],uint16_t *snake_head_first_ubication ,uint16_t *previous_body_part_ubication,uint16_t *body_part_ubication,uint16_t body_part,uint32_t direction,uint32_t *score)
{
    bool crash = false;
    uint16_t event = false, cont = 1;
    
    while   (body_part != END_OF_SNAKE+1)
    {
        if (body_part == SNAKE_HEAD)
        {
            body_part_ubication = search_for_in_world(snake_world,body_part);
            event = move_snake_head (body_part_ubication,direction);
            if( event == CRASH)
            {
                crash = true;
            }
            snake_head_first_ubication = body_part_ubication;
        }
        else 
        {
            body_part_ubication = search_for_in_world(snake_world,body_part);
            if(body_part_ubication )
            {
                cont++;
                if (body_part == SNAKE_HEAD+1)
                {
                    move_snake_body (snake_head_first_ubication,body_part);
                }
                else
                {
                    if (event == ATE && body_part == END_OF_SNAKE)
                    {
                        move_snake_body (previous_body_part_ubication,cont);
                        (*score) += SCORE_VALUE;
                    }
                    else
                    {
                        move_snake_body (previous_body_part_ubication,body_part);
                    }
                }  
                previous_body_part_ubication = body_part_ubication;
            }
        }
        body_part++;
    }
    if (event != ATE)
    {
        *body_part_ubication = EMPTY_SPACE;
    }
    
    //printf ("\n%d\n",event);
    
    return crash;
}

static uint8_t move_snake_head ( uint16_t* body_part_ubication,uint16_t direction )
{
    uint16_t* copy_of_body_part = body_part_ubication;
    uint16_t exit = 0;
    switch (direction)
    {
        case (RIGHT):
            if(check_next_step(copy_of_body_part+1))
                exit = ATE;
            if(!check_crash(copy_of_body_part+1))
                *(copy_of_body_part+1) = *body_part_ubication;
            else
                exit = CRASH;
            break;
        case (LEFT):
            if(check_next_step(copy_of_body_part-1))
                exit = ATE;
            if(!check_crash(copy_of_body_part-1))  
                *(copy_of_body_part-1) = *body_part_ubication;
            else
                exit = CRASH;
            break;
        case (DOWN):
            if(check_next_step(copy_of_body_part+MAX_SIZE_X))
                exit = ATE;
            if(!check_crash(copy_of_body_part+MAX_SIZE_X))
                *(copy_of_body_part+MAX_SIZE_X) = *body_part_ubication;
            else
                exit = CRASH;
            break;
        case (UP):
            if(check_next_step(copy_of_body_part-MAX_SIZE_X))
                exit = ATE;
            if(!check_crash(copy_of_body_part-MAX_SIZE_X))
                *(copy_of_body_part-MAX_SIZE_X) = *body_part_ubication;
            else
                exit = CRASH;
            break;
    } 
    return exit;
}

static void move_snake_body (uint16_t* previous_body_part_ubication, uint16_t body_part)
{
    if (previous_body_part_ubication != NULL)
    {
        *previous_body_part_ubication = body_part;
    }    
}

static void put_food (uint16_t snake_world[MAX_SIZE_X][MAX_SIZE_Y])
{
    uint16_t i,j;
    
    if (search_for_in_world(snake_world,SNAKE_FOOD) == NULL)
    {
        do
        {
            i = rand() % MAX_WORLD_WIDTH + 1;
            j = rand() % MAX_WORLD_HIGH + 1;
        }
        while (snake_world[i][j] != EMPTY_SPACE); 
        
        snake_world[i][j] = SNAKE_FOOD;   
    }   
}

static uint8_t check_next_step (uint16_t* next_pos)
{
    bool ate;
    if ((*next_pos) == SNAKE_FOOD)
    {
        ate = true;
    }
    else
    {
        ate = false;
    }
    
    return ate;
}


static uint8_t check_crash (uint16_t* next_pos)
{
    bool crash;
    if ((*next_pos) == WALL || ((*next_pos) > SNAKE_HEAD && (*next_pos) <= END_OF_SNAKE))
    {
        crash = true;
    }
    else
    {
        crash = false;
    }
    
    return crash;
}

