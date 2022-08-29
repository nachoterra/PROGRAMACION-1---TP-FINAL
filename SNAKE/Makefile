alle: main.c snake_world.c output.c menus.c input.c init_game.c file_admin.c admin_game.c snake_world.h output.h menus.h input.h init_game.h file_admin.h admin_game.h
	gcc -D ALLE -o snake main.c snake_world.c output.c menus.c input.c init_game.c file_admin.c admin_game.c -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_primitives -lallegro_acodec

rpi: main.c snake_world.c rpi_logic.c rpi_logic.h snake_world.h disdrv.o disdrv.h joydrv.h joydrv.o termlib.o termlib.h libaudio.h libaudio.c
	gcc -D RPI -Wall -o snake main.c joydrv.o disdrv.o termlib.o snake_world.c rpi_logic.c -L./SDL/Library/ -lSDL -laudio

