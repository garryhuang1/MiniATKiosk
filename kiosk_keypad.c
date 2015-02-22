#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "miniat/miniat.h"


miniat *miniat_instance = NULL;

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

	
	/*
	 * Peripherals will go after here
	 */
	
	

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

		/*
		 * Set peripheral bus state here
		 */
		
		/*
		 * Give peripherals clock cycle here
		 */
		 
		/*
		 * Get peripherals new bus state here 
		 */

// EXAMPLE		
//		peripheral_bus_state = p_simple_term_get_bus(term);
//		if(peripheral_bus_state.address == M_SIMPLE_TERM_ADDRESS) {
//			miniat_pins_bus_set(m, peripheral_bus_state);
//		}
		
		
		/* Ignore address 0, as it is a 'return to 0' bus design, 0 may be on the bus */
// DISABLED
//		if (peripheral_bus_state.address == 0) {
//			// Do nothing
//		} else {
//			/* Error if we got here log it, and keep going! The ugly cast keeps the compiler happy*/
//			fprintf(stderr, "Could not find peripheral mapped to address: %lu\n",
//												(long unsigned int)peripheral_bus_state.address);
//		}

	}

	/* Free the data we use before exiting */

	/*
	 * Free peripherals here
	 */
	miniat_free(miniat_instance);
}

//
static void cleanup() {
	if(miniat_instance) {
		miniat_free(miniat_instance);
	}
	/*
	 * Free peripherals here
	 */
}
