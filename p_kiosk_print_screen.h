#ifndef _P_KIOSK_PRINT_SCREEN_
#define _P_KIOSK_PRINT_SCREEN_

#include <miniat/miniat.h>
#include "p_kiosk_sdl.h"

#define COMMAND_PRINT_NEW_LINE 0

struct p_kiosk_print_screen{
	p_sdl_data* sdl_struct;
	m_uword print_screen_start_address;
	m_bus *bus;
	int connected
	char character;
};

typedef struct p_kiosk_print_screen p_kiosk_print_screen;

extern p_kiosk_print_screen* p_kiosk_print_screen_new(p_sdl_data* init_struct, m_uword keypad_start_address);
extern void p_kiosk_print_screen_free(p_kiosk_print_screen *p);
extern void p_kiosk_print_screen_clock(p_kiosk_print_screen *p);
extern m_bus p_kiosk_print_screen_get_bus(p_kiosk_print_screen *p);
extern void p_kiosk_print_screen_set_bus(p_kiosk_print_screen *p, m_bus bus);