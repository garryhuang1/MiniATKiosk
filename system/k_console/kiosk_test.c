#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "miniat/miniat.h"
#include "kiosk.h"
#include "p_kiosk_sdl.h"
#include <SDL2/SDL.h>

#define MINIAT_LOG_FILENAME "kiosk.log"

#define SCREEN_ADDRESS 0x4010
#define KEYPAD_ADDRESS 0x4011

miniat *m = NULL;
kiosk *k = NULL;

static void cleanup();

static void miniat_start(int argc, char *argv[]){
	m_bus bus_state;
	m_bus peripheral_bus_state;
	bool quit;
	SDL_Event e;

	if(argc != 2){
		fprintf(stderr, "You mus specify a bin file name to run");
		THROW(m_error_num_illegal_argument);
	}

	atexit(cleanup);

	FILE *f = fopen(argv[1], "rb");
	if(!f){
		fprintf(stderr, "File %s could not be opened \"%s\"", argv[1], strerror(errno));
		THROW(m_error_num_null_pointer);
	}

	m = miniat_new(f);
	printf("create new miniat\n");

	k = p_kiosk_new(KEYPAD_ADDRESS, SCREEN_ADDRESS);
	printf("create new kiosk\n");

	while(!quit)
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			if(e.type ==SDL_MOUSEBUTTONDOWN){
				printf("in loop click\n");
				miniat_clock(m);
				printf("in miniat clock\n");
				bus_state = miniat_pins_bus_get(m);
				printf("in miniat_pins_bus\n");
				p_kiosk_set_read_bus(k, bus_state);
				printf("in kiosk_set_bus\n");
				p_kiosk_set_write_bus(k, bus_state);

				p_kiosk_read_clock(k, &e);
				printf("in kiosk_read\n");
				p_kiosk_write_clock(k);
				printf("in kiosk_write\n");

				peripheral_bus_state = p_kiosk_get_read_bus(k);
				if(peripheral_bus_state.address == KEYPAD_ADDRESS){
					printf("keypad address is %lu\n", (long unsigned int)peripheral_bus_state.address);
					goto set_address;
				}
				peripheral_bus_state = p_kiosk_get_write_bus(k);
				if(peripheral_bus_state.address == SCREEN_ADDRESS){
					goto set_address;
				}

				if(peripheral_bus_state.address ==0){
					printf("keypad address is %lu\n", (long unsigned int)peripheral_bus_state.address);
					continue;
				}
				fprintf(stderr, "Could not find peripheral mapped to address: %lu\n",
												(long unsigned int)peripheral_bus_state.address);
				continue;

				set_address:
					miniat_pins_bus_set(m, peripheral_bus_state);				
			}
			
		}
	}
	p_kiosk_free(k);
	miniat_free(m);
}

static void cleanup(){
	if(m){
		miniat_free(m);
	}
	if(k){
		p_kiosk_free(k);
	}
}

int main(int argc, char *argv[]){
	TRY{
		miniat_start(argc, argv);
	}
		CATCHALL{
			miniat_dump_error();
	}
	FINALLY{}
	ETRY;
	return 0;
}