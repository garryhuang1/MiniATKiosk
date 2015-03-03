#ifndef _KIOSK_SCREEN_H_
#define _KIOSK_SCREEN_H_

#include "miniat/miniat.h"

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
extern p_kiosk_screen* p_kiosk_screen_new(m_uword screen_command_address, 	
									m_uword screen_char_address, 
									m_uword screen_x_address, 
									m_uword screen_y_address, 
									m_uword screen_color_address;);

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
