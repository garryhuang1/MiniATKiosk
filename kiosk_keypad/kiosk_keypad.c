#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <miniat/miniat.h>
#include "kiosk_keypad.h"
#include "SDL2/SDL.h"
#include "keypad_render2.h"

struct p_kiosk_keypad {
	m_uword keypad_command_address;
	m_uword keypad_data_address;
	m_bus *keypad_bus;

	char keypad_buffer[51];
	int buffer_index;
};

p_kiosk_keypad * p_kiosk_keypad_new(m_uword keypad_command_address,
									m_uword keypad_data_address){

	int i;
	p_kiosk_keypad *k = malloc(sizeof(p_kiosk_keypad));

	if(k){
		k ->keypad_bus = (m_bus *)malloc(sizeof(m_bus));
		if(!k -> keypad_bus){
			free(k);
			k = NULL;
		}
		else{
			k ->keypad_command_address = keypad_command_address;
			k ->keypad_data_address = keypad_data_address;
			k ->buffer_index = 0;

			i = keypad_init();
		}

	}
	return k;
}

void p_kiosk_keypad_free(p_kiosk_keypad *k){
	if(k){
		closeWindow();

		free(k);
	}
	return;
}

void p_kiosk_keypad_clock(p_kiosk_keypad *k){
	if(k->keypad_bus -> address == k -> keypad_command_address){

	}
	else if(k->keypad_bus -> address == k -> keypad_data_address){

	}
}

m_bus p_kiosk_keypad_get_bus(p_kiosk_keypad *k){
	m_bus c = {0};
	if(!k){
		return c;
	}
	return *(k->keypad_bus);
}

void p_kiosk_keypad_set_bus(p_kiosk_keypad *k, m_bus bus){
	if(k){
		memcpy(k ->keypad_bus, &bus, sizeof(bus));
	}
}