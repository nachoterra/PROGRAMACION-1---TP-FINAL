#include "snake_world.h"
#include "rpi_logic.h"

#define ANY_KEY                 (6)
#define MIN_DELAY     (1000)

#define JOY_AXIS_INVERT J_INV_TRUE 
#define JOY_THRESHOLD 100     // 10-100 Joystick threshold (sensitivity)

static void init_rpi (void); //incializa el display y el joystick
static uint32_t menu_play (uint32_t actividad); //menu de incio espera a que se aprete el joystick
static void print_disp (uint16_t snake_world [MAX_SIZE_X][MAX_SIZE_Y]); //imprime en el display el mundo
static void all_display(dlevel_t state);
static void play_draw(void);
static void exit_draw(void);
static void level_speed(uint32_t score,uint32_t speed);

static uint32_t check_key (uint32_t key, uint32_t last_pressed_valid_key);


void admin_rpi(void)
{
    
        uint32_t key=RIGHT,pausa=false,actividad=true,score = 0,speed=300000;
        uint16_t snake_world [MAX_SIZE_X][MAX_SIZE_Y];
 static uint32_t last_pressed_valid_key = RIGHT;
        jcoord_t joy_coordinates1;
        jswitch_t joy_switch1=J_NOPRESS;
        
        uint8_t  snake_life = SNAKE_LIFE;
        
        set_file_to_play("audio.wav");
        
        init_rpi ();
        create_world (snake_world);
        
        actividad=menu_play (actividad);   //  Wait until joystick switch is presed to start
        
        
      
        play_sound();

       
        
       
        while(actividad && snake_life)
{
        if (player_status() == FINISHED) 
        {
            printf("musi: no");
            //set_file_to_play("audio.wav");
            end_play();
            set_file_to_play("audio.wav");
            play_sound();
            
        }
        else
            printf("musi: si");
            
        system("clear");
        printf("Score:%d\n",score);
        printf("Vidas:%d\n",snake_life);
        
        print_disp(snake_world);
        joystick_update(); // Read joystick Hardware
        joy_coordinates1 = joystick_get_coord(); //And get coordinate values
        joy_switch1 = joystick_get_switch_value();

        if (joy_coordinates1.x > JOY_THRESHOLD)
            key = DOWN;
        else if (joy_coordinates1.x < -JOY_THRESHOLD)
            key = UP;
        else if (joy_coordinates1.y > JOY_THRESHOLD)
        {
            key = RIGHT;
            
        }
        else if (joy_coordinates1.y < -JOY_THRESHOLD)
        {
            key = LEFT;
            
        }
        else if (joy_switch1 == J_PRESS) 
        {
            

            while (joy_switch1 == J_PRESS) 
            {
                joystick_update(); // Read joystick Hardware
                joy_switch1 = joystick_get_switch_value(); // And get switch value
            }

            if (pausa == false) 
            {
                pausa = true;
                pause_sound();
            } 
            else {
                pausa = false;
                play_sound();

            }
        }
        
          if(pausa==false)
          {
          key=check_key (key, last_pressed_valid_key);
            switch (key)
            {
                case (RIGHT) :

                     game_logic (snake_world,RIGHT,&last_pressed_valid_key,&snake_life,&score);
                    last_pressed_valid_key = RIGHT;
                    
                    break;
                case (LEFT) :
                    game_logic (snake_world,LEFT,&last_pressed_valid_key,&snake_life,&score);
                    last_pressed_valid_key = LEFT;
                    break;
                case (DOWN) :
                    game_logic (snake_world,DOWN,&last_pressed_valid_key,&snake_life,&score);
                    last_pressed_valid_key = DOWN;
                    break;
                case (UP) :
                    game_logic (snake_world,UP,&last_pressed_valid_key,&snake_life,&score);
                    last_pressed_valid_key = UP;
                    break;   
                default:
                    game_logic (snake_world,last_pressed_valid_key,&last_pressed_valid_key,&snake_life,&score);
            }
            print_disp(snake_world);
            
            level_speed(score,speed);
  
        }
          else
          {
            actividad=menu_play(actividad);
             
          }
        }
        display_clear();
        if (snake_life==0 || pausa==true)
        {
            if (snake_life==0)
            {
            all_display(D_ON);
            all_display(D_OFF);
            }
            end_play();
            admin_rpi();
        }
        display_clear();
        end_play();
        
}




static void init_rpi (void)
{
            //INCIALIZA
	clrscr();					//Termlib Clear Screen (see termlib.h for more info)
	joy_init();					// Initialize Joystick Hardware
	display_init();				// Initialize Display Hardware 
	set_joy_axis(JOY_ROTATE);	// Set joystick axis orientaton  
	set_display_axis(NORMAL);	// Set display axis orientation 
	set_joy_direction(J_INV_TRUE,J_INV_TRUE); // Invert both x and y joystick axis direction
        
        
    if(player_status()==NO_INIT)
    {
        init_sound();
        
    }
	//
}
static uint32_t menu_play (uint32_t actividad)
{
    jswitch_t joy_switch1=J_NOPRESS;
jcoord_t joy_coordinates1;
    play_draw();
    
    do
    { 
         joy_coordinates1 = joystick_get_coord(); //And get coordinate values
        if((joy_coordinates1.y < -JOY_THRESHOLD))
        {
           play_draw(); 
           actividad=true;
        }
        else if((joy_coordinates1.y > JOY_THRESHOLD))
        {
            exit_draw();
            actividad=false;
        }
        joystick_update();						 // Read joystick Hardware
	joy_switch1=joystick_get_switch_value(); // And get switch value
    }
    while(joy_switch1==J_NOPRESS);
    
   display_clear();			// Clears Display buffer and Hardware Display 
    

   
    //usleep(500000);
    //display_clear();
   return actividad;

}
static void print_disp (uint16_t snake_world [MAX_SIZE_X][MAX_SIZE_Y])
{
 

    int i,j;
    for(i=1;i<(MAX_SIZE_X -1);i++)			// All Dots on (write to display buffer)
    {
        for(j=1;j<(MAX_SIZE_Y-1);j++)
        {
            if(snake_world[i][j]==EMPTY_SPACE)
            {
                display_write(i-1,j-1,D_OFF);
            }
            else
            {
                display_write(i-1,j-1,D_ON);
            }
        }
    }
			
    display_update();			// Send display buffer to display 
    
}

static uint32_t check_key (uint32_t key, uint32_t last_pressed_valid_key)
{
    if ((key == RIGHT || key == LEFT) && (last_pressed_valid_key == RIGHT || last_pressed_valid_key == LEFT))
    {
        key= ANY_KEY;
    }
    else if ((key == DOWN || key == UP) && (last_pressed_valid_key == UP || last_pressed_valid_key == DOWN))
    {
        key= ANY_KEY;
    }
    return key;
}


static void all_display(dlevel_t state)
{
       int i,j;
    
    for(j=1;j<15;j++)	// All Dots on (write to display buffer)
    {
	for(i=1;i<15;i++)
        {
		display_write(i,j,state);
                
        }	
    display_update();			// Send display buffer to display 
    }
}


static void play_draw(void)
{
    int i,j,ic,jc=0;
    
    display_clear();
    all_display(D_ON);
    for(i=1;i<15;i++)       //play
    {
        ic=i;
        if((i>7) && (jc<7))
        {
            ++jc;
        }
        for(j=1;j<15;j++)
        {
            
            if((j>4) && (j<11) && (i>(1)) && (i<13))
            {
                if(ic>1 && i<8)
                {
                    display_write(i,j,D_OFF);
                    --ic;
                }
                else if((i>7) && (jc<6) && (j<(11-jc)))
                {
                    display_write(i,j,D_OFF);
                }
            }
            else
            {
                display_write(i,j,D_ON);
            }
        }
        
       display_update(); 
    }
}

static void exit_draw(void)
{
    int i,j;
    display_clear();
    all_display(D_ON);
    for(i=1;i<15;i++)       //cruz
    {
        for(j=1;j<15;j++)
        {
            if((i==j) || ((i+j)==15))
            {
                
                display_write(i,j,D_OFF);
                display_write(1,1,D_ON);
                display_write(1,14,D_ON);
                display_write(14,1,D_ON);
                display_write(14,14,D_ON);
            }
            else
                display_write(i,j,D_ON);
        }
    display_update();
    }
}

static void level_speed(uint32_t score,uint32_t time)
{
  
    if ((time-(score*200)) >= MIN_DELAY)
    {
        usleep (time-(score*200));
    }
    else
    {
        usleep (MIN_DELAY);
    }   
}