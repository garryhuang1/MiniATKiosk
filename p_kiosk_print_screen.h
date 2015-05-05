#ifndef _P_KIOSK_PRINT_SCREEN_
#define _P_KIOSK_PRINT_SCREEN_

#include <miniat/miniat.h>
#include "p_kiosk_sdl.h"

#define COMMAND_PRINT_NEW_LINE 0
#define COMMAND_CUT_RECEIPT 1

struct p_kiosk_print_screen{
	p_sdl_data* sdl_struct;
	m_uword print_screen_start_address;
	m_bus *bus;
	int connected
	char character;
};

typedef struct p_kiosk_print_screen p_kiosk_print_screen;
/**
 * Create a kiosk keypad
 *
 * @param p_sdl_data and address
 *		The p_sdl_data struct and peripheral address
 *
 * @return
 *		The receipt printer screen instance
 */
extern p_kiosk_print_screen* p_kiosk_print_screen_new(p_sdl_data* init_struct, m_uword keypad_start_address);

/**
 * Destroy instance of receipt printer screen
 *
 * @param p_kiosk_print_screen
 *		Pointer to receipt printer instance
 *
 * @return
 *		Freed memory from receipt printer instance
 */
extern void p_kiosk_print_screen_free(p_kiosk_print_screen *p);

 /**
 * Give the receipt printer screen a clock cycle
 *
 * @param p_kiosk_print_screen
 *		Pointer to receipt printer screen instance
 *
 * @return
 *		Screen is read for input
 */
extern void p_kiosk_print_screen_clock(p_kiosk_print_screen *p);

/**
 * Gets the bus state for the kiosk receipt printer screen
 *
 * @param p_kiosk_print_screen
 *		Pointer to receeipt printer screen instance
 *
 * @return m_bus
 *		Bus state of receipt printer peripheral
 */
extern m_bus p_kiosk_print_screen_get_bus(p_kiosk_print_screen *p);

/**
 * Sets the bus state for the receipt printer screen
 *
 * @param p_kiosk_print_screen, m_bus
 *		Pointer to keypad instance and a bus state
 *
 * @return
 *		Set bus state for receipt printer screen to bus arg
 */
extern void p_kiosk_print_screen_set_bus(p_kiosk_print_screen *p, m_bus bus);
#endif