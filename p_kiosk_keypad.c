#include <stdio.h>
#include <stdlib.h>

#include <miniat/miniat.h>
#include "p_kiosk_keypad.h"
#include "p_kiosk_sdl.h"


p_kiosk_keypad* p_kiosk_keypad_new(p_sdl_data* init_struct, m_uword keypad_start_address) {
	p_kiosk_keypad *k = malloc(sizeof(p_kiosk_keypad));

	if (k) {
		k->bus = (m_bus *)malloc(sizeof(m_bus));
		if (!k->bus) {
			free(k);
			k = NULL;
		}
		else {
			k->keypad_start_address = keypad_start_address;
			k->sdl_struct = init_struct;
			// k->keypad_port = KEYPAD_PORT_ID;		// GPIO Not Used
			k->connected = 0;
		}
	}

	return k;
}

void p_kiosk_keypad_free(p_kiosk_keypad *k) {

	/* Keypad must not be connected when trying to destroy it */
	if (k) {
		if (!k->connected) {
			free(k->bus);
		}
		free(k);
	}

	return;
}

void p_kiosk_keypad_clock(p_kiosk_keypad *k) {

	uint32_t data;

	/* keypad instance is not initialized */
	if (!k) {
		return;
	}

	/* Read/Write request to kiosk keypad peripheral
	 * If the read/write and request wire is on and acknowledge 
	 * wire is low, get mouse click and record as data
	 */
	if (k->bus->rW == M_HIGH && k->bus->req && !k->bus->ack) {
		data = p_sdl_get_mouse_click(k->sdl_struct);
		k->bus->data = data;
		k->bus->ack = M_HIGH;
	}
	/* Data hasn't been read yet */
	else if (k->bus->ack) {
		k->bus->ack = M_LOW;
	}
	return;
}

m_bus p_kiosk_keypad_get_bus(p_kiosk_keypad *k) {
	m_bus empty_bus = { 0 };
	/* keypad instance is not initialized */
	if (!k) {
		return empty_bus;
	}
	return *(k->bus);
}

void p_kiosk_keypad_set_bus(p_kiosk_keypad *k, m_bus bus) {
	if (k) {
		memcpy(k->bus, &bus, sizeof(bus));
	}
}
