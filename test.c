#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "miniat/miniat.h"
#include "kiosk_screen/kiosk_screen.h"
#include "kiosk_keypad/kiosk_keypad.h"
#include "kiosk_keypad/keypad_read.h"

#define M_SCREEN_CONTROL_BUS_ADDRESS 0x411
#define M_SCREEN_CHAR_BUS_ADDRESS 0x412
#define M_SCREEN_X_BUS_ADDRESS 0x413
#define M_SCREEN_Y_BUS_ADDRESS 0x414
#define M_SCREEN_COLOR_BUS_ADDRESS 0x415

#define M_KEYPAD_CONTROL_BUS_ADDRESS 0x430
#define M_KEYPAD_DATA_BUS_ADDRESS 0x431

miniat *miniat_instance = NULL;
p_kiosk_screen *screen_instance = NULL;

p_kiosk_keypad *keypad_instance = NULL;

static void cleanup();

int main(int argc, char *argv[]) {
	//miniat_instance = miniat_new(f);

	screen_instance = p_kiosk_screen_new(M_SCREEN_CONTROL_BUS_ADDRESS, M_SCREEN_CHAR_BUS_ADDRESS, M_SCREEN_X_BUS_ADDRESS, M_SCREEN_Y_BUS_ADDRESS, M_SCREEN_COLOR_BUS_ADDRESS);

	keypad_instance = p_kiosk_keypad_new(M_KEYPAD_CONTROL_BUS_ADDRESS, M_KEYPAD_DATA_BUS_ADDRESS);

		uint32_t data;
		bool quit = false;
		SDL_Event e;
		while(!quit){
				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT ){
						quit = true;
					}
					else{
						data = keypad_read_getdata( &e );
					}
				}

		}
	
	cleanup();
}

static void cleanup() {
	if(screen_instance) {
		p_kiosk_screen_free(screen_instance);
	}
	if(keypad_instance){
		p_kiosk_keypad_free(keypad_instance);
	}
	if(miniat_instance) {
		miniat_free(miniat_instance);
	}
}
