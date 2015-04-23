#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "miniat/miniat.h"
#include "p_kiosk_screen.h"
#include "p_kiosk_keypad.h"

#define M_SCREEN_COMMAND   0x4012
#define M_SCREEN_ADD_BUFFER 0x4013
#define M_SCREEN_DRAW_5 0x401D
#define M_KEYPAD 0x4000
miniat *m = NULL;

p_kiosk_screen *s = NULL;
p_kiosk_keypad *k = NULL;

static void cleanup();

static void miniat_start(int argc, char *argv[]) {

	m_bus bus_state; /* bus state from miniat */
	m_bus peripheral_bus_state; /* bus state from peripherals */

	/* Boiler plate code to just make sure you gave me a bin file to run */
	if (argc != 2) {
		fprintf(stderr, "You must specify a bin file name to run");
		THROW(m_error_num_illegal_argument);
	}

	/* Register a cleanup function to at exit, this gets called on ctrl^c */
	atexit(cleanup);

	/* More boiler plate code just to open the file you gave me */
	FILE *f = fopen(argv[1], "rb");
	if(!f) {
		fprintf(stderr, "File %s could not be opened \"%s\"", argv[1], strerror(errno));
		THROW(m_error_num_null_pointer);
	}

	/*
	 * We need instances of the peripherals and a miniat that we want to use. Since this
	 * system uses a keyboard and terminal, we create those objects to use in our system.
	 */
	m = miniat_new(f);

	p_sdl_data* sdl_data = p_sdl_new();
	s = p_kiosk_screen_new(sdl_data, M_SCREEN_COMMAND);
	k = p_kiosk_keypad_new(sdl_data, M_KEYPAD);


	while(1) {

		/* Give the miniat a clock cycle */
		miniat_clock(m);
		
		bus_state = miniat_pins_bus_get(m);

		p_kiosk_screen_set_bus(s, bus_state);
		
		p_kiosk_keypad_set_bus(k, bus_state);
		
		
		p_kiosk_screen_clock(s);
		
		p_kiosk_keypad_clock(k);

		peripheral_bus_state = p_kiosk_screen_get_bus(s);
		if(peripheral_bus_state.address >= M_SCREEN_COMMAND && peripheral_bus_state.address <= M_SCREEN_DRAW_5) {
			miniat_pins_bus_set(m, peripheral_bus_state);
			continue;
		}
		
		peripheral_bus_state = p_kiosk_keypad_get_bus(k);
		if (peripheral_bus_state.address == M_KEYPAD) {
			miniat_pins_bus_set(m, peripheral_bus_state);
			continue;
		} 
		
		if (peripheral_bus_state.address == 0) {
			continue;
		} else { 
			/* Error if we got here log it, and keep going! The ugly cast keeps the compiler happy*/
			fprintf(stderr, "Could not find peripheral mapped to address: %x\n",
													(long unsigned int)peripheral_bus_state.address);
			continue;
		} 
		
	}

	/* Free the data we use before exiting */
	cleanup();
}

static void cleanup() {

	if(m) {
		miniat_free(m);
	}
	if(s) {
		p_kiosk_screen_free(s);
	}
}

int main(int argc, char *argv[]) {
	TRY {
		miniat_start(argc, argv);
	}
        CATCHALL {
		miniat_dump_error();
	}
	FINALLY {}
	ETRY;
	return 0;
}
