#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "miniat/miniat.h"
#include "kiosk_screen/kiosk_screen.h"
#include "kiosk_keypad/kiosk_keypad.h"
#include "simple_term.h"

#define M_SCREEN_CONTROL_BUS_ADDRESS 0x411
#define M_SCREEN_CHAR_BUS_ADDRESS 0x412
#define M_SCREEN_X_BUS_ADDRESS 0x413
#define M_SCREEN_Y_BUS_ADDRESS 0x414
#define M_SCREEN_COLOR_BUS_ADDRESS 0x415

#define M_KEYPAD_CONTROL_BUS_ADDRESS 0x430
#define M_KEYPAD_DATA_BUS_ADDRESS 0x431

#define M_SIMPLE_TERM_ADDRESS 0x4020

miniat *miniat_instance = NULL;
p_kiosk_screen *screen_instance = NULL;
p_simple_term *term = NULL;

p_kiosk_keypad *keypad_instance = NULL;

static void cleanup();

static void miniat_start(int argc, char *argv[]);


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

static void miniat_start(int argc, char *argv[]) {

	m_bus bus_state; /* bus state from miniat */
	m_bus peripheral_bus_state; /* bus state from peripherals */

	/* Boiler plate code to just make sure you gave me a bin file to run */
	if (argc != 2) {
		fprintf(stderr, "Bin program not specified");
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

	
	
	miniat_instance = miniat_new(f);

	screen_instance = p_kiosk_screen_new(M_SCREEN_CONTROL_BUS_ADDRESS, M_SCREEN_CHAR_BUS_ADDRESS, M_SCREEN_X_BUS_ADDRESS, M_SCREEN_Y_BUS_ADDRESS, M_SCREEN_COLOR_BUS_ADDRESS);

	keypad_instance = p_kiosk_keypad_new(M_KEYPAD_CONTROL_BUS_ADDRESS, M_KEYPAD_DATA_BUS_ADDRESS);

	term = p_simple_term_new(M_SIMPLE_TERM_ADDRESS);

	/* Run the system */
	while(1) {


		/* Give the miniat a clock cycle */
		miniat_clock(miniat_instance);

		
		/*
		 * After the miniat does something, we need to get any data that could
		 * be waiting for peripherals on the bus, or other pin sources. Were using
		 * the bus in these examples.
		 */
		bus_state = miniat_pins_bus_get(miniat_instance);

		p_kiosk_screen_set_bus(screen_instance, bus_state);
		
		p_simple_term_set_bus(term, bus_state);

		p_kiosk_keypad_set_bus(keypad_instance, bus_state);
		
		p_simple_term_clock(term);
		
		p_kiosk_screen_clock(screen_instance);

		p_kiosk_keypad_clock(keypad_instance);
		 
		/*
		 * Get peripherals new bus state here 
		 */

	
		peripheral_bus_state = p_kiosk_screen_get_bus(screen_instance);
		if(peripheral_bus_state.address == M_SCREEN_CONTROL_BUS_ADDRESS) {
			miniat_pins_bus_set(miniat_instance, peripheral_bus_state);
			continue;
		}

		peripheral_bus_state = p_kiosk_keypad_get_bus(keypad_instance);
		if(peripheral_bus_state.address == M_KEYPAD_CONTROL_BUS_ADDRESS){
			miniat_pins_bus_set(miniat_instance, peripheral_bus_state);
		}

		peripheral_bus_state = p_simple_term_get_bus(term);
		if(peripheral_bus_state.address == M_SIMPLE_TERM_ADDRESS) {
			miniat_pins_bus_set(miniat_instance, peripheral_bus_state);
			continue;
		}
		
		/* Ignore address 0, as it is a 'return to 0' bus design, 0 may be on the bus */

		if (peripheral_bus_state.address == 0) {
			// Do nothing
		} else {
			/* Error if we got here log it, and keep going! The ugly cast keeps the compiler happy*/
			fprintf(stderr, "Could not find peripheral mapped to address: %lu\n",
												(long unsigned int)peripheral_bus_state.address);
		}

	}

	/* Free the data we use before exiting */
	cleanup();
}

//
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
