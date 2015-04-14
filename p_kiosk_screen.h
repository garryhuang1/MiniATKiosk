#ifndef _KIOSK_SCREEN_H_
#define _KIOSK_SCREEN_H_

#include "miniat/miniat.h"
#include "p_kiosk_sdl.h"


#define DRAWMODE_PIXEL  0
#define DRAWMODE_LINE  1
#define DRAWMODE_RECT  2
#define DRAWMODE_CIRCLE  3

#define STR_BUFFER_SIZE 50

#define COMMAND_DRAW_STRING 0
#define COMMAND_DRAW_SHAPE 1
#define COMMAND_DRAW_CLEAR 2
#define COMMAND_DRAW_RESET 3
#define COMMAND_DRAW_CLEAR_RESET 4

struct p_kiosk_screen {
	p_sdl_data* sdl_struct;
	int draw_buffer[5];
	char string_buffer[STR_BUFFER_SIZE + 1];
	int string_buffer_location;
	m_uword screen_start_address;
	m_bus *screen_bus;
	int drawmode;
	int last_status;
};


typedef struct p_kiosk_screen p_kiosk_screen;

/**
 * Create a kiosk screen.
 *
 * @param address
 * 	The address to register this peripheral too
 *
 * @return
 *  The kiosk screen instance
 */
extern p_kiosk_screen* p_kiosk_screen_new(p_sdl_data* init_struct, m_uword screen_start_address);

/**
 * Free an instance of a kiosk screen
 * @param s
 * 	The instance to free
 */
extern void p_kiosk_screen_free(p_kiosk_screen *s);

/**
 * Give the kiosk screen a clock. 
 *
 * @param s
 * 	Free a kiosk screen.
 */
extern void p_kiosk_screen_clock(p_kiosk_screen *s);

/**
 * Get the state of the bus as known by the peripheral.
 *
 * @param s
 *  The kiosk screen to get the bus state from.
 * @return
 * 	The bus state.
 */
extern m_bus p_kiosk_screen_get_bus(p_kiosk_screen *s);


/**
 * Set the bus state to the peripheral.
 * @param s
 *  The kiosk screen to set the bus state on.
 * @param bus
 * 	The bus state to set.
 */
extern void p_kiosk_screen_set_bus(p_kiosk_screen *s, m_bus bus);


#endif /*  _KIOSK_SCREEN_H_ */
