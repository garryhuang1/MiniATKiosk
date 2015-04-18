#ifndef _P_KIOSK_KEYPAD_
#define _P_KIOSK_KEYPAD_

#include "miniat/miniat.h"
#include "p_kiosk_sdl.h"

// #define KEYPAD_PORT_ID m_gpio_id_A;		// Not Being Used

struct p_kiosk_keypad {
	p_sdl_data* sdl_struct;
	// m_gpio_id keypad_port;		// Not Being Used
	m_uword keypad_start_address;
	m_bus *bus;
	int connected;
};

typedef struct p_kiosk_keypad p_kiosk_keypad;

/**
 * Create a kiosk keypad
 *
 * @param p_sdl_data and address
 *		The p_sdl_data struct and peripheral address
 *
 * @return
 *		The kiosk keypad instance
 */
extern p_kiosk_keypad* p_kiosk_keypad_new(p_sdl_data* init_struct, m_uword keypad_start_address);

/**
 * Destroy instance of kiosk keypad
 *
 * @param p_kiosk_keypad
 *		Pointer to keypad instance
 *
 * @return
 *		Freed memory from keypad instance
 */
 extern void p_kiosk_keypad_free(p_kiosk_keypad *k);

 /**
 * Give the kiosk keypad a clock cycle
 *
 * @param p_kiosk_keypad
 *		Pointer to keypad instance
 *
 * @return
 *		Keypad is read for input
 */
 extern void p_kiosk_keypad_clock(p_kiosk_keypad *k);

/**
 * Gets the bus state for the kiosk keypad
 *
 * @param p_kiosk_keypad
 *		Pointer to keypad instance
 *
 * @return m_bus
 *		Bus state of keypad peripheral
 */
 extern m_bus p_kiosk_keypad_get_bus(p_kiosk_keypad *k);

/**
 * Sets the bus state for the kiosk keypad
 *
 * @param p_kiosk_keypad, m_bus
 *		Pointer to keypad instance and a bus state
 *
 * @return
 *		Set bus state for keypad to bus arg
 */
extern void p_kiosk_keypad_set_bus(p_kiosk_keypad *k, m_bus bus);

 #endif
